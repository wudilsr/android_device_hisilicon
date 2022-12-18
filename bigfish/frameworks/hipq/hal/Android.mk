LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SHARED_LIBRARIES :=\
                            libhi_common\
                            libcutils \
                            libhi_msp

LOCAL_SRC_FILES := pqsetting.c

LOCAL_C_INCLUDES := \
                    $(LOCAL_PATH)/../../../sdk/source/msp/include \
                    $(LOCAL_PATH)/../../../sdk/source/common/include \
                    $(LOCAL_PATH)/../../../sdk/source/msp/api/include \
                    $(LOCAL_PATH)/../../../sdk/source/msp/api/higo/include \

LOCAL_MODULE_TAGS := optional

LOCAL_MODULE := libpqhal
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)
