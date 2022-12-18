ifneq ($(CFG_HI_LOADER_APPLOADER),y)
OMX_MODULE := omx_core omx_vdec omx_venc
include $(call all-named-subdir-makefiles,$(OMX_MODULE))
endif
