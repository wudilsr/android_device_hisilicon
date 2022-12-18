LOCAL_PATH:= $(call my-dir)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
    main_pq.cpp

LOCAL_MODULE_TAGS := optional

LOCAL_SHARED_LIBRARIES := \
    libbinder\
    libpqservice\
    libutils\

LOCAL_C_INCLUDES := \
    $(LOCAL_PATH)/../hal\
    $(LOCAL_PATH)/../libs

LOCAL_MODULE:= pqsetting
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)

include $(BUILD_EXECUTABLE)
