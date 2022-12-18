LOCAL_DIR :=$(call my-dir)

HA_MODULE := 

ifeq (y,$(CFG_HI_HAEFFECT_BASE_SUPPORT))
HA_MODULE += src/baseaef
endif

ifeq (y,$(CFG_HI_HAEFFECT_SRS_SUPPORT))
HA_MODULE += src/srsaef
endif

include $(call all-named-subdir-makefiles,$(HA_MODULE))
