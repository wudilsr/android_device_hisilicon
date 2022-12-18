/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-02-07
 *
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"
#include "hifmc100_cache.h"

/*****************************************************************************/
#define MAX_MTD_PARTITIONS		(32)

struct partition_entry
{
	char name[16];
	unsigned long long start;
	unsigned long long length;
	unsigned int flags;
};

struct partition_info
{
	int parts_num;
	struct partition_entry entry[MAX_MTD_PARTITIONS];
	struct mtd_partition parts[MAX_MTD_PARTITIONS];
};

#ifdef CONFIG_MTD_PART_CHANGE
extern int register_mtd_partdev(struct mtd_info *mtd);
extern int unregister_mtd_partdev(struct mtd_info *mtd);
#else
static int register_mtd_partdev(struct mtd_info *mtd){ return 0; };
static int unregister_mtd_partdev(struct mtd_info *mtd){return 0;};
#endif

static const char *part_probes_type[] = { "cmdlinepart", NULL, };

static struct partition_info ptn_info = {0};

/*****************************************************************************/
static int __init parse_nand_partitions(const struct tag *tag)
{
	int i;

	if (tag->hdr.size <= 2) {
		PR_OUT("tag->hdr.size <= 2\n");
		return 0;
	}
	ptn_info.parts_num = (tag->hdr.size - 2)
		/ (sizeof(struct partition_entry)/sizeof(int));
	memcpy(ptn_info.entry,
		&tag->u,
		ptn_info.parts_num * sizeof(struct partition_entry));

	for (i = 0; i < ptn_info.parts_num; i++) {
		ptn_info.parts[i].name   = ptn_info.entry[i].name;
		ptn_info.parts[i].size   = (ptn_info.entry[i].length);
		ptn_info.parts[i].offset = (ptn_info.entry[i].start);
		ptn_info.parts[i].mask_flags = 0;
		ptn_info.parts[i].ecclayout  = 0;
	}

	return 0;
}

/* turn to ascii is "HiNp" */
__tagtable(0x48694E70, parse_nand_partitions);
/*****************************************************************************/
static unsigned int  nand_otp_len = 0;
static unsigned char nand_otp[128] = {0};

/* Get NAND parameter table. */
static int __init parse_nand_param(const struct tag *tag)
{
	if (tag->hdr.size <= 2)
		return 0;

	nand_otp_len = ((tag->hdr.size << 2) - sizeof(struct tag_header));

	if (nand_otp_len > sizeof(nand_otp)) {
		PR_OUT("tag->hdr.size <= 2\n");
		return 0;
	}
	memcpy(nand_otp, &tag->u, nand_otp_len);
	return 0;
}
/* 0x48694E77 equal to fastoot ATAG_NAND_PARAM */
__tagtable(0x48694E77, parse_nand_param);
/*****************************************************************************/

static int hifmc100_os_enable(struct hifmc_host *host, int enable)
{
	if (enable == ENABLE)
		clk_enable(host->clk);
	else
		clk_disable(host->clk);
	return 0;
}
/*****************************************************************************/

static irqreturn_t hifmc100_irq_handle(int irq, void *dev_id)
{
	u32 regval;
	struct hifmc_host *host = (struct hifmc_host *)dev_id;

	regval = hifmc_read(host, HIFMC100_INT);
	if (regval & HIFMC100_INT_OP_DONE) {
		hifmc_write(host,
			    HIFMC100_INT_CLR_OP_DONE, HIFMC100_INT_CLR);
		complete(&host->dma_done);
	}

	return IRQ_HANDLED;
}
/*****************************************************************************/

static int hifmc100_os_probe(struct platform_device *pltdev)
{
	int size;
	int result = -EIO;
	u32 regval;
	int ret;
	struct hifmc_host *host;
	struct nand_chip *chip;
	struct mtd_info *mtd;
	struct resource *res;

	size = sizeof(struct hifmc_host) + sizeof(struct nand_chip)
		+ sizeof(struct mtd_info);
	host = kmalloc(size, GFP_KERNEL);
	if (!host) {
		PR_OUT("failed to allocate host structure.\n");
		return -ENOMEM;
	}
	memset((char *)host, 0, size);

	platform_set_drvdata(pltdev, host);

	host->dev  = &pltdev->dev;
	host->chip = chip = (struct nand_chip *)&host[1];
	host->mtd  = mtd  = (struct mtd_info *)&chip[1];

	res = platform_get_resource_byname(pltdev, IORESOURCE_MEM, "base");
	if (!res) {
		PR_OUT("Can't get resource for FMC reg address.\n");
		goto fail;
	}

	host->regbase = ioremap_nocache(res->start, res->end - res->start + 1);
	if (!host->regbase) {
		PR_OUT("FMC base reg ioremap failed.\n");
		goto fail;
	}

	res = platform_get_resource_byname(pltdev, IORESOURCE_MEM, "peri");
	if (!res) {
		PR_OUT("Can't get resource for FMC peri address.\n");
		goto fail;
	}

	host->sysreg = ioremap_nocache(res->start, res->end - res->start + 1);
	if (!host->sysreg) {
		PR_OUT("FMC peri ioremap failed.\n");
		goto fail;
	}

	mtd->priv  = chip;
	mtd->owner = THIS_MODULE;
	mtd->name  = (char *)(pltdev->name);

	res = platform_get_resource_byname(pltdev, IORESOURCE_MEM, "buffer");
	if (!res) {
		PR_OUT("Can't get resource for FMC buffer address.\n");
		goto fail;
	}

	chip->IO_ADDR_R = chip->IO_ADDR_W = ioremap_nocache(res->start,
		res->end - res->start + 1);
	if (!chip->IO_ADDR_R) {
		PR_OUT("io remap buffer address failed\n");
		goto fail;
	}
	memset(chip->IO_ADDR_R, 0xff, res->end - res->start + 1);

	res = platform_get_resource_byname(pltdev, IORESOURCE_IRQ, "irq");
	if (!res) {
		PR_OUT("Can't get irq resource.\n");
		goto fail;
	}

	host->irq = res->start;

	/* disable all interrupt. */
	regval = hifmc_read(host, HIFMC100_INT_EN);
	regval &= ~HIFMC100_INT_EN_ALL;
	hifmc_write(host, regval, HIFMC100_INT_EN);

	/* clear all interrupt. */
	regval = hifmc_read(host, HIFMC100_INT_CLR);
	regval |= HIFMC100_INT_CLR_ALL;
	hifmc_write(host, regval, HIFMC100_INT_CLR);

	ret = request_irq(host->irq, hifmc100_irq_handle, 0,
			  "hifmc100_irq", host);
	if (ret) {
		pr_err("Unable to allocate IRQ\n");
		return -EIO;
	}

	chip->priv        = host;
	host->chip        = chip;
	chip->cmd_ctrl    = hifmc100_cmd_ctrl;
	chip->dev_ready   = hifmc100_dev_ready;
	chip->select_chip = hifmc100_select_chip;
	chip->read_byte   = hifmc100_read_byte;
	chip->read_word   = hifmc100_read_word;
	chip->write_buf   = hifmc100_write_buf;
	chip->read_buf    = hifmc100_read_buf;

	chip->chip_delay = HIFMC100_CHIP_DELAY;
	chip->options    = NAND_NEED_READRDY | NAND_SKIP_BBTSCAN;
	chip->ecc.layout = NULL;
	chip->ecc.mode   = NAND_ECC_NONE;

	host->clk = clk_get_sys("hifmc100", NULL);
	if (IS_ERR(host->clk)) {
		PR_OUT("hifmc100 clock not found.\n");
		goto fail;
	}
	host->enable = hifmc100_os_enable;

	if (hifmc100_nand_init(host, chip)) {
		PR_OUT("failed to allocate device buffer.\n");
		goto fail;
	}

	if (nand_otp_len) {
		PR_OUT("Copy Nand read retry parameter from boot,"
		       " parameter length %d.\n", nand_otp_len);
		memcpy(host->rr_data, nand_otp, nand_otp_len);
	}

	if (nand_scan(mtd, CONFIG_HIFMC100_NAND_MAX_CHIP)) {
		result = -ENXIO;
		goto fail;
	}

	register_mtd_partdev(host->mtd);

	if (!mtd_device_parse_register(mtd, part_probes_type,
		NULL, ptn_info.parts, ptn_info.parts_num))
		return 0;

	unregister_mtd_partdev(host->mtd);

	result = -ENODEV;
	nand_release(mtd);

fail:
	hifmc100_nand_destory(host);

	if (chip->IO_ADDR_W)
		iounmap(chip->IO_ADDR_W);
	if (host->regbase)
		iounmap(host->regbase);
	if (host->sysreg)
		iounmap(host->sysreg);
	kfree(host);
	platform_set_drvdata(pltdev, NULL);

	return result;
}
/*****************************************************************************/

static int hifmc100_os_remove(struct platform_device *pltdev)
{
	struct hifmc_host *host = platform_get_drvdata(pltdev);

	host->enable(host, DISABLE);

	hifmc100_nand_destory(host);

	unregister_mtd_partdev(host->mtd);

	nand_release(host->mtd);

	iounmap(host->chip->IO_ADDR_W);
	iounmap(host->regbase);
	iounmap(host->sysreg);
	kfree(host);
	platform_set_drvdata(pltdev, NULL);

	return 0;
}
/*****************************************************************************/

static void hifmc100_pltdev_release(struct device *dev)
{
}
/*****************************************************************************/

#ifdef CONFIG_PM
static int hifmc100_os_suspend(struct platform_device *pltdev,
			       pm_message_t state)
{
	struct hifmc_host *host = platform_get_drvdata(pltdev);

	while (hifmc_read(host, HIFMC100_OP ) & HIFMC100_OP_REG_OP_START)
		;

	while ((hifmc_read(host, HIFMC100_OP_CTRL))
		& HIFMC100_OP_CTRL_DMA_OP_READY)
		_cond_resched();

	host->enable(host, DISABLE);

	return 0;
}
/*****************************************************************************/

static int hifmc100_os_resume(struct platform_device *pltdev)
{
	int cs;
	struct hifmc_host *host = platform_get_drvdata(pltdev);
	struct nand_chip *chip = host->chip;

	host->enable(host, ENABLE);
	for (cs = 0; cs < chip->numchips; cs++)
		host->send_cmd_reset(host, cs);
	hifmc_write(host,
		SET_HIFMC100_PWIDTH(CONFIG_HIFMC100_W_LATCH,
			CONFIG_HIFMC100_R_LATCH, CONFIG_HIFMC100_RW_LATCH),
		HIFMC100_PND_PWIDTH_CFG);

	return 0;
}
#endif /* CONFIG_PM */
/*****************************************************************************/

static struct platform_driver hifmc100_os_pltdrv =
{
	.driver.name   = "hinand",
	.probe  = hifmc100_os_probe,
	.remove = hifmc100_os_remove,
#ifdef CONFIG_PM
	.suspend  = hifmc100_os_suspend,
	.resume   = hifmc100_os_resume,
#endif /* CONFIG_PM */
};
/*****************************************************************************/
static u64 hifmc_dmamask = DMA_BIT_MASK(32);

static struct platform_device hifmc100_os_pltdev =
{
	.name           = "hinand",
	.id             = -1,

	.dev.platform_data     = NULL,
	.dev.dma_mask          = &hifmc_dmamask,
	.dev.coherent_dma_mask = DMA_BIT_MASK(32),
	.dev.release           = hifmc100_pltdev_release,
};
/*****************************************************************************/

static int __init hifmc100_os_module_init(void)
{
	int result = 0;
	u32 regval;
	unsigned int flash_type;
	struct resource *res;
	void __iomem *regbase;

	result = find_cpu_resource("hifmc100", &hifmc100_os_pltdev.resource,
		&hifmc100_os_pltdev.num_resources);
	if (result)
		return result;

	/* check boot flash type */
	res = platform_get_resource_byname(&hifmc100_os_pltdev, IORESOURCE_MEM, "base");
	if (!res) {
		PR_OUT("Can't get reg base resource.\n");
		return -EIO;
	}
	regbase = ioremap_nocache(res->start, res->end - res->start + 1);
	if (!regbase) {
		PR_OUT("ioremap failed\n");
		return -EIO;
	}

	regval = readl(regbase + HIFMC100_CFG);
	flash_type = (regval & HIFMC100_FLASH_SEL_MASK)
		>> HIFMC100_FLASH_SEL_SHIFT;
	if (flash_type != HIFMC100_FLASH_TYPE_NAND) {
		/* no 'goto fail', incase shutdown coredump */
		iounmap(regbase);
		return -ENODEV;
	}

	pr_notice("Found Flash Memory Controller V100.\n");
	iounmap(regbase);

	result = platform_driver_register(&hifmc100_os_pltdrv);
	if (result < 0)
		return result;

	result = platform_device_register(&hifmc100_os_pltdev);
	if (result < 0) {
		platform_driver_unregister(&hifmc100_os_pltdrv);
		return result;
	}

	return result;
}
/*****************************************************************************/
static void __exit hifmc100_os_module_exit(void)
{
	platform_driver_unregister(&hifmc100_os_pltdrv);
	platform_device_unregister(&hifmc100_os_pltdev);
}
/*****************************************************************************/

module_init(hifmc100_os_module_init);
module_exit(hifmc100_os_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Czyong");
MODULE_DESCRIPTION("Hisilicon Flash Memory Controller V100 Device Driver,"
	" Version 1.30");

/*****************************************************************************/
