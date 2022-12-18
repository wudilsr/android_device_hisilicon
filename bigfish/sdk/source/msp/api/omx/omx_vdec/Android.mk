
OMX_MODULE := normal 

ifeq ($(CFG_HI_TVP_SUPPORT),y)
OMX_MODULE += secure
endif

include $(call all-named-subdir-makefiles,$(OMX_MODULE))
