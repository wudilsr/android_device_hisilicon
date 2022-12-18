#===============================================================================
# export variables
#===============================================================================
ifeq ($(CFG_HI_EXPORT_FLAG),)
SDK_DIR := $(CURDIR)/..
include $(SDK_DIR)/base.mak
endif

#***********************************************************************************
#   varibale
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++

ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
    ADVCA_MOD_NAME := hi_advca.ko
else
    CFG_HI_ADVCA_SUPPORT :=
endif

JPGE_SUPPORT := y
SATA_SUPPORT := y
USB3_SUPPORT := n

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3716mv400 hi3718mv100 hi3719mv100 hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100),)
SATA_SUPPORT := n
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3718mv100 hi3719mv100),)
JPGE_SUPPORT := n
endif

ifneq ($(findstring $(CFG_HI_CHIP_TYPE), hi3796cv100 hi3798cv100 hi3798mv100 hi3796mv100 hi3798cv200 hi3798cv200_a),)
USB3_SUPPORT := y
endif

#***********************************************************************************
#   rule
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++
.PHONY: load load_install load_uninstall
#+++++++++++++++++++++++++++++++++++++++++++++++++++++++
load_install: load $(if $(CFG_HI_ADVCA_SUPPORT),,unload)

load:
	$(AT)rm -rf load
ifneq ($(CFG_HI_MSP_BUILDIN),y)
    ifeq ($(CFG_HI_MCE_SUPPORT)_$(CFG_HI_KEYLED_CT1642_KERNEL_SUPPORT),_)
		$(AT)echo "insmod hi_media.ko"          >> load
    endif

	$(AT)echo "insmod hi_mmz.ko"                >> load
	$(AT)echo "insmod hi_common.ko"             >> load

	$(AT)echo "insmod hi_gpio.ko"               >> load

    ifeq ($(CFG_HI_GPIOI2C_SUPPORT),y)
		$(AT)echo "insmod hi_gpio_i2c.ko i2cmode=2" >> load
    endif

	$(AT)echo "insmod hi_i2c.ko"                >> load

    ifeq ($(CFG_HI_GPU_MALI400_SUPPORT),y)
		$(AT)echo "insmod mali.ko"              >> load
    else ifeq ($(CFG_HI_GPU_MALI450_SUPPORT),y)
		$(AT)echo "insmod mali.ko"              >> load
    else ifeq ($(CFG_HI_GPU_MALI700_SUPPORT),y)
		$(AT)echo "insmod kds.ko"               >> load
		$(AT)echo "insmod mali_kbase.ko"        >> load
    endif

	$(AT)echo "insmod hi_tde.ko"                >> load
	$(AT)echo "insmod hi_otp.ko"                >> load
	$(AT)echo "insmod hi_demux.ko"              >> load
	$(AT)echo "insmod hi_adec.ko"               >> load
	$(AT)echo "insmod hi_vfmw.ko"               >> load

    ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
		$(AT)echo "insmod hi_svdec.ko"          >> load
    endif

	$(AT)echo "insmod hi_pdm.ko"                >> load
	$(AT)echo "insmod hi_pq.ko"                 >> load
	$(AT)echo "insmod hi_vpss.ko"               >> load
	$(AT)echo "insmod hi_vdec.ko"               >> load

    ifeq ($(CFG_HI_VDEC_VPU_SUPPORT),y)
		$(AT)echo "insmod hi_vpu.ko"            >> load
    endif

	$(AT)echo "insmod hi_cipher.ko"             >> load
	$(AT)echo "insmod hi_hdmi.ko"               >> load
	$(AT)echo "insmod hi_adsp.ko"               >> load
	$(AT)echo "insmod hi_aiao.ko"               >> load
#	$(AT)echo "insmod hi_dmac.ko"               >> load
	$(AT)echo "insmod hi_vou.ko"                >> load
	$(AT)echo "insmod hi_sync.ko"               >> load

    ifeq ($(CFG_HI_PVR_SUPPORT),y)
		$(AT)echo "insmod hi_pvr.ko"            >> load
    endif

	$(AT)echo "insmod hi_avplay.ko"             >> load
	$(AT)echo "insmod hi_mce.ko"                >> load

    ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
		$(AT)echo "insmod hi_tuner.ko"          >> load
    endif

	$(AT)echo "insmod hi_pwm.ko"                >> load

    ifndef CFG_HI_ADVCA_FUNCTION
		$(AT)echo "# About hi_fb:"                  >> load
		$(AT)echo "#  For 1920*1080, triple buffer, ARGB8888 format, use:" >> load
		$(AT)echo "#  insmod hi_fb.ko video=\"hi_fb:vram0_size:16200, vram4_size:2430\""    >> load
		$(AT)echo "#  For 1280*720, use:"    >> load
		$(AT)echo "#  insmod hi_fb.ko video=\"hi_fb:vram0_size:7200, vram2_size:2430\""     >> load
		$(AT)echo "#  Insmod hi_fb.ko with no args will use defaule value,The defaule value is set by cfg.mak."  >> load
		$(AT)echo "#  vram0 is memory size for HD and vram4 is for SD0. The size is calculated as below:" >> load
		$(AT)echo "#  vram0_size = (1920*1080*4*2/1024)KB; vram4_size = (720*576*2*2/1024)KB" >> load
    endif
	$(AT)echo "insmod hi_fb.ko"                 >> load

    ifneq ($(CFG_HI_IR_TYPE_LIRC),y)
		$(AT)echo "insmod hi_ir.ko"             >> load
    endif

    ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
		$(AT)echo "insmod hi_wdg.ko"            >> load
    endif

	$(AT)echo "insmod hi_jpeg.ko"               >> load

    ifeq ($(JPGE_SUPPORT),y)
		$(AT)echo "insmod hi_jpge.ko"           >> load
    endif

	$(AT)echo "insmod hi_png.ko"                >> load

    ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
		$(AT)echo "insmod $(ADVCA_MOD_NAME)"    >> load
    endif

    ifeq ($(CFG_HI_VENC_SUPPORT),y)
		$(AT)echo "insmod hi_venc.ko"           >> load
    endif

    ifeq ($(CFG_HI_AENC_SUPPORT),y)
		$(AT)echo "insmod hi_aenc.ko"           >> load
    endif

    ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
		$(AT)echo "insmod hi_keyled.ko"         >> load
    endif

    ifeq ($(CFG_HI_SCI_SUPPORT),y)
		$(AT)echo "insmod hi_sci.ko"            >> load
    endif

    ifeq ($(CFG_HI_VI_SUPPORT),y)
		$(AT)echo "insmod hi_vi.ko"             >> load
        ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
			$(AT)echo "insmod hi_hdmirx.ko"     >> load
        endif
    endif

	$(AT)echo "insmod hi_pmoc.ko"               >> load

    ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
		$(AT)echo "insmod hi_spi.ko"            >> load
    endif
    ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
		$(AT)echo "insmod hi_slic.ko"            >> load
    endif
endif   # End of ifneq ($(CFG_HI_MSP_BUILDIN),y)

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
	$(AT)echo "insmod lirc_dev.ko"              >> load
	$(AT)echo "insmod lirc_serial.ko"           >> load
	$(AT)echo "mkdir -p /var/run/lirc"          >> load
	$(AT)echo "mkdir -p /var/log"               >> load
	$(AT)echo "cat > /var/log/lircd << EOF"     >> load
	$(AT)echo "EOF"                             >> load
	$(AT)echo "ln -fs /dev/lirc0 /dev/lirc"     >> load
	$(AT)echo "lircd -d /dev/lirc0 -o /dev/lircd -r__up" >> load
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
	$(AT)echo "insmod hi_ndpt.ko"           >> load
endif

ifeq ($(CFG_HI_ADAC_TVL320AIC31_SUPPORT),y)
	$(AT)echo "insmod hi_tlv320.ko"         >> load
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
	$(AT)echo "insmod voip_hme.ko"          >> load
	$(AT)echo "insmod hi_aud_adp.ko"        >> load
endif

ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
	$(AT)echo "insmod hi_ci.ko"             >> load
endif

ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
	$(AT)echo "insmod hi_cimaxplus.ko" >> load
endif

	$(AT)echo "insmod ./usb/ehci-hcd.ko"        >> load
	$(AT)echo "insmod ./usb/ohci-hcd.ko"        >> load

ifeq ($(USB3_SUPPORT),y)
	$(AT)echo "insmod ./usb/xhci-hcd.ko"        >> load
endif

ifeq ($(SATA_SUPPORT),y)
	$(AT)echo "insmod ./sata/libahci.ko"        >> load
	$(AT)echo "insmod ./sata/ahci_platform.ko"  >> load
endif

ifeq ($(CFG_HI_NTFS_MODULE_SUPPORT),y)
	$(AT)echo "insmod tntfs.ko"                 >> load
endif

ifndef CFG_HI_ADVCA_FUNCTION
	$(AT)echo "echo 6 > /proc/sys/vm/dirty_ratio"           >> load # see source/msp/component/hifat/how to use.txt for detail
	$(AT)echo "echo 1 > /proc/sys/vm/overcommit_memory"     >> load
	$(AT)echo "echo 8192 > /proc/sys/vm/min_free_kbytes"    >> load
endif

ifeq ($(CFG_HI_DVFS_CPU_SUPPORT),y)
	$(AT)echo "echo interactive > /sys/devices/system/cpu/cpu0/cpufreq/scaling_governor"    >> load
	$(AT)echo "echo 1200000 >/sys/devices/system/cpu/cpu0/cpufreq/scaling_max_freq"  >> load
endif

	$(AT)(chmod +x load; mv ./load $(MODULE_DIR)/load)

unload:
	$(AT)rm -rf unload
ifeq ($(CFG_HI_NTFS_MODULE_SUPPORT),y)
	$(AT)echo "rmmod tntfs"                 >> unload
endif

ifeq ($(SATA_SUPPORT),y)
	$(AT)echo "rmmod ahci_platform"         >> unload
	$(AT)echo "rmmod libahci"               >> unload
endif

ifeq ($(USB3_SUPPORT),y)
	$(AT)echo "rmmod xhci-hcd"              >> unload
endif

	$(AT)echo "rmmod ohci-hcd"              >> unload
	$(AT)echo "rmmod ehci-hcd"              >> unload

ifeq ($(CFG_HI_CI_DEV_CIMAXPLUS),y)
	$(AT)echo "rmmod hi_cimaxplus"     >> unload
endif

ifeq ($(CFG_HI_CIPLUS_SUPPORT),y)
	$(AT)echo "rmmod hi_ci"                 >> unload
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
	$(AT)echo "rmmod hi_aud_adp"            >> unload
	$(AT)echo "rmmod voip_hme"              >> unload
endif

ifeq ($(CFG_HI_ADAC_TVL320AIC31_SUPPORT),y)
	$(AT)echo "rmmod hi_tlv320"             >> unload
endif

ifeq ($(CFG_HI_VOIP_SUPPORT),y)
	$(AT)echo "rmmod hi_ndpt"               >> unload
endif

ifeq ($(CFG_HI_IR_TYPE_LIRC),y)
	$(AT)echo "rmmod lirc_serial"           >> unload
	$(AT)echo "rmmod lirc_dev"              >> unload
endif
ifneq ($(CFG_HI_MSP_BUILDIN),y)

    ifeq ($(CFG_HI_ADAC_SLIC_SUPPORT),y)
		$(AT)echo "rmmod hi_slic.ko"            >> unload
    endif
    ifeq ($(CFG_HI_SPI_BUS_SUPPORT),y)
		$(AT)echo "rmmod hi_spi"                >> unload
    endif

	$(AT)echo "rmmod hi_pmoc"               >> unload

    ifeq ($(CFG_HI_VI_SUPPORT),y)
        ifeq ($(CFG_HI_HDMI_RX_SUPPORT),y)
			$(AT)echo "rmmod hi_hdmirx"         >> unload
        endif
		$(AT)echo "rmmod hi_vi"                 >> unload
    endif

    ifeq ($(CFG_HI_SCI_SUPPORT),y)
		$(AT)echo "rmmod hi_sci"                >> unload
    endif

    ifeq ($(CFG_HI_KEYLED_SUPPORT),y)
		$(AT)echo "rmmod hi_keyled"             >> unload
    endif

    ifeq ($(CFG_HI_AENC_SUPPORT),y)
		$(AT)echo "rmmod hi_aenc"               >> unload
    endif

    ifeq ($(CFG_HI_VENC_SUPPORT),y)
		$(AT)echo "rmmod hi_venc"               >> unload
    endif

    ifeq ($(CFG_HI_ADVCA_SUPPORT),y)
		$(AT)echo "rmmod $(ADVCA_MOD_NAME)"     >> unload
    endif

	$(AT)echo "rmmod hi_png"                    >> unload

    ifeq ($(JPGE_SUPPORT),y)
		$(AT)echo "rmmod hi_jpge"               >> unload
    endif

	$(AT)echo "rmmod hi_jpeg"                   >> unload

    ifeq ($(findstring $(CFG_HI_CHIP_TYPE), hi3798mv100 hi3796mv100),)
		$(AT)echo "rmmod hi_wdg"                >> unload
    endif

    ifneq ($(CFG_HI_IR_TYPE_LIRC),y)
		$(AT)echo "rmmod hi_ir"                 >> unload
    endif

	$(AT)echo "rmmod hi_fb"                     >> unload
	$(AT)echo "rmmod hi_pwm"                    >> unload

    ifeq ($(CFG_HI_FRONTEND_SUPPORT),y)
		$(AT)echo "rmmod hi_tuner"              >> unload
    endif

	$(AT)echo "rmmod hi_mce"                    >> unload
	$(AT)echo "rmmod hi_avplay"                 >> unload

    ifeq ($(CFG_HI_PVR_SUPPORT),y)
		$(AT)echo "rmmod hi_pvr"                >> unload
    endif

	$(AT)echo "rmmod hi_sync"                   >> unload
	$(AT)echo "rmmod hi_vou"                    >> unload
#	$(AT)echo "rmmod hi_dmac"                   >> unload
	$(AT)echo "rmmod hi_aiao"                   >> unload
	$(AT)echo "rmmod hi_adsp"                   >> unload
	$(AT)echo "rmmod hi_hdmi"                   >> unload

	$(AT)echo "rmmod hi_cipher"                 >> unload

    ifeq ($(CFG_HI_VDEC_VPU_SUPPORT),y)
		$(AT)echo "rmmod hi_vpu"		        >> unload
    endif

	$(AT)echo "rmmod hi_vdec"                   >> unload
	$(AT)echo "rmmod hi_vpss"                   >> unload

	$(AT)echo "rmmod hi_pq"                     >> unload
	$(AT)echo "rmmod hi_pdm"                    >> unload

    ifeq ($(CFG_HI_VDEC_SVDEC_SUPPORT),y)
		$(AT)echo "rmmod hi_svdec"              >> unload
    endif

	$(AT)echo "rmmod hi_vfmw"                   >> unload
	$(AT)echo "rmmod hi_adec"                   >> unload
	$(AT)echo "rmmod hi_demux"                  >> unload
	$(AT)echo "rmmod hi_otp"                    >> unload
	$(AT)echo "rmmod hi_tde"                    >> unload

    ifeq ($(CFG_HI_GPU_MALI400_SUPPORT),y)
		$(AT)echo "rmmod mali"                  >> unload
    else ifeq ($(CFG_HI_GPU_MALI450_SUPPORT),y)
		$(AT)echo "rmmod mali"                  >> unload
    else ifeq ($(CFG_HI_GPU_MALI700_SUPPORT),y)
		$(AT)echo "rmmod mali_kbase"            >> unload
		$(AT)echo "rmmod kds"                   >> unload
    endif

	$(AT)echo "rmmod hi_i2c"                    >> unload

    ifeq ($(CFG_HI_GPIOI2C_SUPPORT),y)
		$(AT)echo "rmmod hi_gpio_i2c"           >> unload
    endif

	$(AT)echo "rmmod hi_gpio"                   >> unload

	$(AT)echo "rmmod hi_common"                 >> unload
	$(AT)echo "rmmod hi_mmz"                    >> unload

    ifeq ($(CFG_HI_MCE_SUPPORT)_$(CFG_HI_KEYLED_CT1642_KERNEL_SUPPORT),_)
		$(AT)echo "rmmod hi_media"              >> unload
    endif
endif   # End of ifneq ($(CFG_HI_MSP_BUILDIN),y)
	$(AT)(chmod +x unload; mv ./unload $(MODULE_DIR)/unload)

load_uninstall:
	$(AT)rm -rf $(MODULE_DIR)/load $(MODULE_DIR)/unload

