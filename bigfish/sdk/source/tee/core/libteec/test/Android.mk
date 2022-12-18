LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
include $(SDK_DIR)/Android.def

LOCAL_SRC_FILES:= tee_test_sess.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_sess
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_kernel_api.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc \
    $(LOCAL_PATH)/../src
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:=tee_test_kernel_api
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_invoke.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_invoke
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_mem.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_mem
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_storage.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_store
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_ut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_ut
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_elfload.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_elfload
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_login.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_login_test
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginwrite.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_login_write
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginwrite1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_login_write1
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginwrite1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_login_write2
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_loginread.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_login_read
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)


include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_random.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_random
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= dx_test_contentpath.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= dx_test_cp
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_time.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_time
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_hello.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= teec_hello
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_secure_timer.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_secure_timer
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_CA.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_CA
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_cancellation.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_requsetcancel
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_hdcp_storekey.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_hdcp_storekey
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_hdcp_write.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_hdcp_write
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_store_default_hdcp_key.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= optional
LOCAL_MODULE:= storedefaultkey
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_query_storekey.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_query_storekey
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_agent.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_agent
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= tee_test_hwi_ipc.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= tee_test_hwi_ipc
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_permission_control.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= teec_permctrl
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)
include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_otp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= teec_otp
ifeq ($(CFG_HI_TEE_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec

include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= test_advca.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../inc
LOCAL_C_INCLUDES+= $(HI_TEE_API_DIR)/include
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= teec_advca
ifeq ($(CFG_HI_TEE_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec


include $(BUILD_EXECUTABLE)
