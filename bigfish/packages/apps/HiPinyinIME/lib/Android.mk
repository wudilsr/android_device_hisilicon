LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES := \
         $(call all-subdir-java-files) \
         com/hisilicon/android/inputmethod/remote/IPinyinDecoderService.aidl

LOCAL_MODULE := com.hisilicon.android.inputmethod.remote.lib
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_STATIC_JAVA_LIBRARY)
