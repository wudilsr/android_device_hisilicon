include $(DEV_ROOT)/cfg.mak

ccflags-y := -I$(KCOM_DIR)/drv/include
ccflags-y += -I$(KCOM_DIR)/include
EXTRA_CFLAGS += $(KCFG_CFLAGS) 

obj-y += hi_mmz_k.o
ifeq ($(MMZ_V2_SUPPORT),YES)
hi_mmz_k-y  :=  media-mem-v2.o
else
hi_mmz_k-y  :=  media-mem.o
endif   
hi_mmz_k-y  +=	mmz_intf.o 
ifeq ($(CFG_CHIP_TYPE),fpga_arm9)
hi_mmz_k-y  +=	chip_fpga_arm9/arm926-cacheflush.o
endif
