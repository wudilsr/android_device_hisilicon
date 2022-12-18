
OMX_MODULE := normal 

ifeq ($(CFG_HI_TEE_SUPPORT),y)
OMX_MODULE += secure
endif

include $(call all-named-subdir-makefiles,$(OMX_MODULE))
