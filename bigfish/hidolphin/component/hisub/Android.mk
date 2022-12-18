LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_PRELINK_MODULE := false
LOCAL_MODULE := libhi_subparse
ifeq (4.4,$(findstring 4.4,$(PLATFORM_VERSION)))
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
else
LOCAL_32_BIT_ONLY := true
endif
LOCAL_MODULE_TAGS := optional

#SUB_TRANSCODE_SUPPORT := true
LOCAL_C_INCLUDES := $(COMMON_UNF_INCLUDE)
LOCAL_C_INCLUDES += $(MSP_DIR)/include
LOCAL_C_INCLUDES += $(LOCAL_PATH)/include \
                    $(LOCAL_PATH)/tinyxml \
                    $(LOCAL_PATH)/src

LOCAL_CFLAGS := $(CFG_CFLAGS)

#LOCAL_SHARED_LIBRARIES := 

SRCS  :=  tinyxml/tinyxml.cpp \
          tinyxml/tinyxmlparser.cpp \
          tinyxml/tinyxmlerror.cpp \
          tinyxml/tinystr.cpp
SRCS  +=  src/hi_svr_subparse.c \
          src/subparse.c \
          src/ttml_parse.cpp

ifdef SUB_TRANSCODE_SUPPORT
LOCAL_C_INCLUDES += $(COMPONENT_DIR)/charset/include
LOCAL_CFLAGS += -DSUB_TRANSCODE_SUPPORT
SRCS  +=  src/sub_transcode.c
LOCAL_SHARED_LIBRARIES += libcharset  libcharsetMgr
endif

LOCAL_SRC_FILES := $(SRCS)

include $(BUILD_SHARED_LIBRARY)
#include $(BUILD_STATIC_LIBRARY)
