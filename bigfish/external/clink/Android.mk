LOCAL_PATH := $(my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES := $(call all-subdir-java-files)
LOCAL_MODULE := libhttpformultiscreen
LOCAL_STATIC_JAVA_LIBRARIES := httpformultiscreenlib
LOCAL_MODULE_TAGS := optional
include $(BUILD_STATIC_JAVA_LIBRARY)

include $(CLEAR_VARS)
LOCAL_PREBUILT_STATIC_JAVA_LIBRARIES := httpformultiscreenlib:src/libHiHttpForMultiscreen.jar
LOCAL_MODULE_TAGS := optional
include $(BUILD_MULTI_PREBUILT)
