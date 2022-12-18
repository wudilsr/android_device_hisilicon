LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(HISI_PLATFORM_PATH)/hidolphin/component/player_mobile/include
LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libhiplayer_utils
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
LOCAL_MODULE_TAGS := optional
LOCAL_CFLAGS := $(CFG_CFLAGS)
LOCAL_CFLAGS += -DANDROID_VERSION
LOCAL_SHARED_LIBRARIES :=  libutils liblog libcutils
LOCAL_SRC_FILES += svr_log.c svr_log_android.c svr_sys.c svr_sys_android.c
include $(BUILD_SHARED_LIBRARY)
