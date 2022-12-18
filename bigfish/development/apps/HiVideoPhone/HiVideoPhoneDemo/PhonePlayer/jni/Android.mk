LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_MODULE := libvideophone
UNF_INCLUDE := device/hisilicon/bigfish/sdk/source/msp/include/
HAD_INCLUDE := device/hisilicon/bigfish/sdk/source/component/ha_codec/include
COM_INCLUDE := device/hisilicon/bigfish/sdk/source/common/include
VOIP_INCLUDE := device/hisilicon/bigfish/sdk/source/component/voip/include
VP_INCLUDE := device/hisilicon/bigfish/sdk/source/component/vp/include
SAMPLE_INCLUDE:= device/hisilicon/bigfish/sdk/sample/
HIGO_INCLUDE:= device/hisilicon/bigfish/sdk/source/msp/api/higo/include/
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := -DANDROID_NDK $(CFG_HI_CFLAGS) $(CFG_HI_BOARD_CONFIGS)
#$(CFG_CFLAGS)
LOCAL_SRC_FILES := \
  com_ctcims_avcodec_PhonePlayer.cpp \
  vp_adpt.cpp

LOCAL_LDLIBS := -ldl -llog
LOCAL_C_INCLUDES += $(JNI_H_INCLUDE) \
		$(UNF_INCLUDE)\
		$(HAD_INCLUDE)\
		$(COM_INCLUDE)\
		$(VOIP_INCLUDE)\
		$(VP_INCLUDE)\
		$(SAMPLE_INCLUDE) \
		$(HIGO_INCLUDE)

LOCAL_SHARED_LIBRARIES := \
  libandroid_runtime \
  libbinder \
  libutils \
  libcutils \
  libhi_common \
  libhi_voip \
  libhi_vp \
  libhi_msp \
  libhi_sample_common


LOCAL_PRELINK_MODULE := false
include $(BUILD_SHARED_LIBRARY)

###############################################
