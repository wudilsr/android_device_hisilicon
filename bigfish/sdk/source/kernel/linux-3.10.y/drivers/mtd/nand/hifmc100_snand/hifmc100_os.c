/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-02-07
 *
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100_spi_ids.h"
#include "hifmc100.h"

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
	int size, result = -EIO;
	int ret;
	u32 regval;
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

	host->iobase = chip->IO_ADDR_R = chip->IO_ADDR_W =
			ioremap_nocache(res->start, res->end - res->start + 1);
	if (!host->iobase) {
		PR_OUT("io remap buffer address failed\n");
		goto fail;
	}
	memset((char *)host->iobase, 0xff, res->end - res->start + 1);

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

	size = SPI_NAND_MAX_PAGESIZE + SPI_NAND_MAX_OOBSIZE;
	host->buffer = dma_alloc_coherent(host->dev, size, &host->dma_buffer,
					  GFP_KERNEL);
	if (!host->buffer) {
		PR_OUT("Can't malloc memory for FMC spi-nand driver.");
		result = -ENOMEM;
		goto fail;
	}
	memset(host->buffer, 0xff, size); 

	/* hifmc host init */
	result = hifmc100_host_init(host);
	if (result)
		return result;

	/* hifmc nand_chip struct init */
	hifmc100_spi_nand_init(host, chip);

	spi_nand_ids_register();

	if (nand_scan(mtd, CONFIG_HIFMC100_MAX_CHIP)) {
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
	if (host->buffer) {
		dma_free_coherent(host->dev, size, host->buffer, 
				  host->dma_buffer);
		host->buffer = NULL;
	}

	if (host->iobase)
		iounmap(host->iobase);
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

	host->set_system_clock(host, NULL, DISABLE);

	nand_release(host->mtd);
	dma_free_coherent(host->dev,
				(SPI_NAND_MAX_PAGESIZE + SPI_NAND_MAX_OOBSIZE),
				host->buffer, host->dma_buffer);
	iounmap(host->regbase);
	iounmap(host->sysreg);
	iounmap(host->iobase);
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
	return 0;
}
/*****************************************************************************/

static int hifmc100_os_resume(struct platform_device *pltdev)
{
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

static struct resource hifmc100_resources[] = {
	{
		.start  = CONFIG_HIFMC100_REG_BASE_ADDRESS,
		.end    = CONFIG_HIFMC100_REG_BASE_ADDRESS
			+ CONFIG_HIFMC100_REG_BASE_ADDRESS_LEN - 1, 
		.flags  = IORESOURCE_MEM,
		.name	= "base"
	},

	{
		.start  = CONFIG_HIFMC100_BUFFER_BASE_ADDRESS,
		.end    = CONFIG_HIFMC100_BUFFER_BASE_ADDRESS
			+ CONFIG_HIFMC100_BUFFER_BASE_LEN - 1,
		.flags  = IORESOURCE_MEM,
		.name	= "buffer"
	},
	{
		.start = CONFIG_HIFMC100_PERIPHERY_REGBASE,
		.end   = CONFIG_HIFMC100_PERIPHERY_REGBASE 
			+ CONFIG_HIFMC100_PERIPHERY_REG_LEN - 1,
		.flags = IORESOURCE_MEM,
		.name	= "peri"
	},
	{
		.start = 86,
		.end   = 86,
		.flags = IORESOURCE_IRQ,
		.name	= "irq"
	},
};

static u64 hifmc_dmamask = DMA_BIT_MASK(32);

static struct platform_device hifmc100_os_pltdev =
{
	.name           = "hinand",
	.id             = -1,

	.dev.platform_data     = NULL,
	.dev.dma_mask          = &hifmc_dmamask,
	.dev.coherent_dma_mask = DMA_BIT_MASK(32),
	.dev.release           = hifmc100_pltdev_release,

	.num_resources  = ARRAY_SIZE(hifmc100_resources),
	.resource       = hifmc100_resources,
};
/*****************************************************************************/

static int __init hifmc100_os_module_init(void)
{
	int result = 0;
	u32 regval;
	unsigned int flash_type;
	struct resource *res;
	void __iomem *regbase;

	/* check boot flash type */
	res = platform_get_resource_byname(&hifmc100_os_pltdev, 
					   IORESOURCE_MEM, "base");
	if (!res) {
		PR_OUT("Can't get resource.\n");
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
	if (flash_type != HIFMC100_FLASH_TYPE_SPI_NAND) {
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
