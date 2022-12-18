LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
        com_hisilicon_android_hibdinfo_HiBDInfo.cpp \
        ./hibdinfo/HiBDInfo.cpp

LOCAL_C_INCLUDES += \
        $(JNI_H_INCLUDE) \
        $(TOP)/device/hisilicon/bigfish/hidolphin/external/libbluray/src/libbluray \
        $(TOP)/device/hisilicon/bigfish/hidolphin/external/libbluray/src/libbluray/bdnav \
        $(TOP)/device/hisilicon/bigfish/external/libbluray/src/libbluray \
        $(TOP)/device/hisilicon/bigfish/external/libbluray/src/libbluray/bdnav \
        $(TOP)/frameworks/base/core/jni \
        $(TOP)/device/hisilicon/bigfish/frameworks/hibdinfo/jni/hibdinfo

LOCAL_SHARED_LIBRARIES := libandroid_runtime \
            libnativehelper \
            libutils \
            libbluray_ex \
            libmedia \
            libbinder \
            liblog \

LOCAL_MODULE := libbdinfo_jni

LOCAL_MODULE_TAGS := optional

LOCAL_PRELINK_MODULE := false

ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_SHARED_LIBRARY)

include $(call all-makefiles-under,$(LOCAL_PATH))
