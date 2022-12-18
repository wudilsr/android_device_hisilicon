/******************************************************************************
 *    COPYRIGHT (C) 2013 Czyong. Hisilicon
 *    All rights reserved.
 * ***
 *    Create by Czyong 2013-02-07
 *
******************************************************************************/

#include "hifmc100_os.h"
#include "hifmc100.h"

/*****************************************************************************/
static int hifmc100_os_add_paratitions(struct hifmc_host *host)
{
	int ix;
	int nr_parts = 0;
	int ret = 0;
	struct mtd_partition *parts = NULL;

#ifdef CONFIG_MTD_CMDLINE_PARTS
	static const char *part_probes[] = {"cmdlinepart", NULL, };
	nr_parts = parse_mtd_partitions(host->mtd, part_probes, &parts, 0);
#endif /* CONFIG_MTD_CMDLINE_PARTS */

	if (nr_parts <= 0)
		return 0;

	for (ix = 0; ix < nr_parts; ix++)
		pr_debug("partitions[%d] = {.name = %s, .offset = 0x%.8x, "
			 ".size = 0x%08x (%uKiB) }\n",
			 ix, parts[ix].name,
			 (unsigned int)parts[ix].offset,
			 (unsigned int)parts[ix].size,
			 (unsigned int)parts[ix].size/1024);

	host->add_partition = 1;
	ret = add_mtd_partitions(host->mtd, parts, nr_parts);

	if (parts) {
		kfree(parts);
		parts = NULL;
	}

	return ret;
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

static int hifmc100_driver_probe(struct platform_device *pltdev)
{
	u32 regval;
	int ret;
	int result = -EIO;
	struct hifmc_host *host;
	struct mtd_info   *mtd;
	struct resource *res;

	host = kmalloc(sizeof(struct hifmc_host), GFP_KERNEL);
	if (!host) {
		PR_OUT("failed to allocate host structure.\n");
		return -ENOMEM;
	}
	memset(host, 0, sizeof(struct hifmc_host));

	platform_set_drvdata(pltdev, host);

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

	res = platform_get_resource_byname(pltdev, IORESOURCE_MEM, "buffer");
	if (!res) {
		PR_OUT("Can't get resource for FMC buffer address.\n");
		goto fail;
	}

	host->iobase = ioremap_nocache(res->start, res->end - res->start + 1);
	if (!host->iobase) {
		PR_OUT("FMC buffer ioremap failed.\n");
		goto fail;
	}

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

	host->buffer = dma_alloc_coherent(host->dev, HIFMC100_DMA_MAX_SIZE,
		&host->dma_buffer, GFP_KERNEL);
	if (!host->buffer) {
		PR_OUT("spi alloc dma buffer failed.\n");
		goto fail;
	}

	mutex_init(&host->lock);
	mtd = host->mtd;
	mtd->name = (char *)pltdev->name;
	mtd->type = MTD_NORFLASH;
	mtd->writesize = 1;
	mtd->flags = MTD_CAP_NORFLASH;
	mtd->owner = THIS_MODULE;

	mtd->_erase = hifmc100_reg_erase;
#ifdef HIFMC100_SPI_NOR_SUPPORT_REG_WRITE
	mtd->_write = hifmc100_reg_write;
#else
	mtd->_write = hifmc100_dma_write;
#endif
	
#ifdef HIFMC100_SPI_NOR_SUPPORT_REG_READ
	mtd->_read  = hifmc100_reg_read;
#else
	mtd->_read  = hifmc100_dma_read;
#endif

	if (hifmc100_probe(host)) {
		result = -ENODEV;
		goto fail;
	}

	mtd->size      = host->chipsize;
	mtd->erasesize = host->erasesize;

	result = hifmc100_os_add_paratitions(host);
	if (host->add_partition)
		return result;

	if (!add_mtd_device(host->mtd))
		return 0;
	result = -ENODEV;

fail:
	if (host->regbase)
		iounmap(host->regbase);
	if (host->iobase)
		iounmap(host->iobase);
	if (host->sysreg)
		iounmap(host->sysreg);
	if (host->buffer)
		dma_free_coherent(host->dev, HIFMC100_DMA_MAX_SIZE,
			host->buffer, host->dma_buffer);
	kfree(host);
	platform_set_drvdata(pltdev, NULL);

	return result;
}
/*****************************************************************************/

static int hifmc100_driver_remove(struct platform_device *pltdev)
{
	struct hifmc_host *host = platform_get_drvdata(pltdev);
	mtd_device_unregister(host->mtd);

	if (host->regbase)
		iounmap(host->regbase);
	if (host->iobase)
		iounmap(host->iobase);
	if (host->buffer)
		dma_free_coherent(host->dev, HIFMC100_DMA_MAX_SIZE,
			host->buffer, host->dma_buffer);
	if (host->sysreg)
		iounmap(host->sysreg);
	kfree(host);
	platform_set_drvdata(pltdev, NULL);

	return 0;
}
/*****************************************************************************/

static void hifmc100_driver_shutdown(struct platform_device *pltdev)
{
	int ix;
	struct hifmc_host *host = platform_get_drvdata(pltdev);
	struct hifmc_spi *spi = host->spi;
	u32 regval = hifmc_read(host, HIFMC100_CFG);

	if (regval & HIFMC100_SPI_NOR_ADDR_MODE_MASK && IS_SPI_NOR_4B(host))
		return;

	for (ix = 0; ix < host->num_chip; ix++, spi++) {
		if (spi->addrcycle == 4) {
			spi->driver->wait_ready(spi);
			spi->driver->entry_4addr(spi, DISABLE);
		}
	}
}

static void hifmc100_pltdev_release(struct device *dev)
{
}
/*****************************************************************************/

#ifdef CONFIG_PM
static int hifmc100_driver_suspend(struct platform_device *dev,
		pm_message_t state)
{
	return 0;
}
/*****************************************************************************/

static int hifmc100_driver_resume(struct platform_device *dev)
{
	return 0;
}
#endif /* CONFIG_PM */
/*****************************************************************************/

static struct platform_driver hifmc100_driver_pltdrv = {
	.probe		= hifmc100_driver_probe,
	.remove		= hifmc100_driver_remove,
	.shutdown	= hifmc100_driver_shutdown,
#ifdef CONFIG_PM
	.suspend	= hifmc100_driver_suspend,
	.resume		= hifmc100_driver_resume,
#endif /* CONFIG_PM */
	.driver.name	= "hi_sfc",
	.driver.owner	= THIS_MODULE,
	.driver.bus	= &platform_bus_type,
};
/*****************************************************************************/

static struct resource hifmc100_device_resources[] = {
	[0] = {
		.start = CONFIG_HIFMC100_REG_BASE_ADDRESS,
		.end   = CONFIG_HIFMC100_REG_BASE_ADDRESS
			+ CONFIG_HIFMC100_REG_BASE_ADDRESS_LEN - 1,
		.flags = IORESOURCE_MEM,
		.name	= "base"
	},

	[1] = {
		.start = CONFIG_HIFMC100_BUFFER_BASE_ADDRESS,
		.end   = CONFIG_HIFMC100_BUFFER_BASE_ADDRESS
			+ CONFIG_HIFMC100_BUFFER_BASE_LEN - 1,
		.flags = IORESOURCE_MEM,
		.name	= "buffer"
	},

	[2] = {
		.start = CONFIG_HIFMC100_PERIPHERY_REGBASE,
		.end   = CONFIG_HIFMC100_PERIPHERY_REGBASE
			+ CONFIG_HIFMC100_PERIPHERY_REG_LEN - 1,
		.flags = IORESOURCE_MEM,
		.name	= "peri"
	},
	[3] = {
		.start = 86, 
		.end   = 86,
		.flags = IORESOURCE_IRQ,
		.name	= "irq"
	},
};
/*****************************************************************************/

static u64 hifmc_dmamask = DMA_BIT_MASK(32);

static struct platform_device hifmc100_device_pltdev = {
	.name           = "hi_sfc",
	.id             = -1,

	.dev.release    = hifmc100_pltdev_release,
	.dev.dma_mask = &hifmc_dmamask,
	.dev.coherent_dma_mask = DMA_BIT_MASK(32),
	.num_resources  = ARRAY_SIZE(hifmc100_device_resources),
	.resource       = hifmc100_device_resources,
};
/*****************************************************************************/

static int __init hifmc100_module_init(void)
{
	int result = 0;
	u32 regval;
	unsigned int flash_type;
	struct resource *res;
	void __iomem *regbase;

	/* check boot flash type */
	res = platform_get_resource_byname(&hifmc100_device_pltdev,
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
	if (flash_type != HIFMC100_FLASH_TYPE_SPI_NOR) {
		/* no 'goto fail', incase shutdown coredump */
		iounmap(regbase);
		return -ENODEV;
	}

	pr_notice("Found Flash Memory Controller V100.\n");
	iounmap(regbase);

	result = platform_driver_register(&hifmc100_driver_pltdrv);
	if (result < 0)
		return result;

	result = platform_device_register(&hifmc100_device_pltdev);
	if (result < 0) {
		platform_driver_unregister(&hifmc100_driver_pltdrv);
		return result;
	}

	return result;
}
/*****************************************************************************/

static void __exit hifmc100_module_exit(void)
{
	platform_device_unregister(&hifmc100_device_pltdev);
	platform_driver_unregister(&hifmc100_driver_pltdrv);
}
/*****************************************************************************/

module_init(hifmc100_module_init);
module_exit(hifmc100_module_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Czyong");
MODULE_DESCRIPTION("Hisilicon Flash Memory Controller V100 Device Driver,"
	" Version 1.30");

/*****************************************************************************/
