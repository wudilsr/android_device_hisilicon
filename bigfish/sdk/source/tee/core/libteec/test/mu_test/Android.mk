LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tclient.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= mu_new
LOCAL_SHARED_LIBRARIES := libcutils

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tclient-rm.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= mu_rm
LOCAL_SHARED_LIBRARIES := libcutils

include $(BUILD_EXECUTABLE)

