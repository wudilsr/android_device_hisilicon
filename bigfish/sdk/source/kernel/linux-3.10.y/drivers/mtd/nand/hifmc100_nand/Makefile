ccflags-y += -Idrivers/mtd/nand

obj-$(CONFIG_MTD_NAND_HIFMC100_NAND) += hifmc100.o hifmc100_os.o hifmc100_dbg_inf.o \
	hifmc100_ecc_info.o hifmc100_rw_latch.o \
	hifmc100_read_retry_hynix_bg_cdie.o \
	hifmc100_read_retry_hynix_bg_bdie.o \
	hifmc100_read_retry_hynix_cg_adie.o \
	hifmc100_read_retry_micron.o  \
	hifmc100_read_retry_samsung.o \
	hifmc100_read_retry_toshiba_24nm.o \
	hifmc100_read_retry_toshiba_19nm.o \
	hifmc100_read_retry.o


obj-$(CONFIG_ARCH_HI3798MX) += hifmc100_rw_latch_hi3798mv100.o
obj-$(CONFIG_ARCH_S40)      += hifmc100_rw_latch_s40.o

obj-$(CONFIG_HIFMC100_NAND_CACHE_ENABLE) += hifmc100_cache.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_DEBUG) += hifmc100_dbg.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_DUMP) += hifmc100_dbg_dump.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_ERASE_COUNT) += hifmc100_dbg_erase_count.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_READ_COUNT) += hifmc100_dbg_read_count.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_ECC_COUNT) += hifmc100_dbg_ecc_count.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_READ_RETRY) += hifmc100_dbg_read_retry.o
obj-$(CONFIG_HIFMC100_NAND_DBG_NAND_CACHE) += hifmc100_dbg_cache.o

