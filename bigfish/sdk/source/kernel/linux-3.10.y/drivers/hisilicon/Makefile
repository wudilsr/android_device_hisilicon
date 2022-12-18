
obj-$(CONFIG_APP_CAPABLE)		+= capable/
obj-y					+= kapi/
obj-$(CONFIG_APP_SEMAPHORE_API)		+= semaphore/
obj-$(CONFIG_BLK_DEV_INITRD)		+= initmrd/
obj-$(CONFIG_BLK_DEV_LOOP)		+= initfile/

ccflags-y += -I$(srctree)/drivers/hisilicon/tee/include
obj-$(CONFIG_TEE_DRIVER)                += tee/
obj-$(CONFIG_TEE_DRIVER)                += sec_mmz/
