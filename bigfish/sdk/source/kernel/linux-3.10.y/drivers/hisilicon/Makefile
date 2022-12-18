
obj-$(CONFIG_APP_CAPABLE)		+= capable/
obj-y					+= kapi/
obj-$(CONFIG_APP_SEMAPHORE_API)		+= semaphore/
obj-$(CONFIG_BLK_DEV_INITRD)		+= initmrd/
obj-$(CONFIG_BLK_DEV_LOOP)		+= initfile/
obj-$(CONFIG_ANDROID)			+= verify_hash/

#ccflags-y += -I$(srctree)/drivers/hisilicon/tee/include
ifdef CONFIG_ARCH_HI3798MX
obj-$(CONFIG_TEE)			+= sec_mmz/
endif
obj-$(CONFIG_TEE)			+= tee/
obj-y					+= sdcardfs/
