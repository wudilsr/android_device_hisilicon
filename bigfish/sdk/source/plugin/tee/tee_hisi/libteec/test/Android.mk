LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_sess.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE:= tee_test_sess
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_invoke.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE:= tee_test_invoke
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_mem.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE:= tee_test_mem
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_storage.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_test_store
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_ut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_test_ut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_elfload.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_elfload
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_login.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_login_test
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginwrite.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_login_write
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginwrite1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_login_write1
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginwrite1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_login_write2
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginread.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_login_read
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_random.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= tee_test_random
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


ifeq ($(CFG_HI_TZINFRA_ENABLE), y)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= dx_test_contentpath.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= dx_test_cp
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
endif

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= tee_test_time.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE:= tee_test_time
LOCAL_MODULE_TAGS := optional
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_hello.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= teec_hello
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= test_otp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= teec_otp
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)
LOCAL_SRC_FILES:= test_cipher.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc $(LOCAL_PATH)/../../trustedcore/include/HS_API
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= teec_cipher
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
