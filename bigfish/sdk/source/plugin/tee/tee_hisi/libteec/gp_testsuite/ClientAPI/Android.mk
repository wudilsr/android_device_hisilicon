LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= InitializeContext_concurrentContext.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= InitializeContext_concurrentContext
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= InitializeContext_NotExistingTEE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= InitializeContext_NotExistingTEE
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= FinalizeContext_null.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= FinalizeContext_null
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_In.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Allocate_In
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_InOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Allocate_InOut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_Out.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Allocate_Out
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_out_of_memory.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Allocate_out_of_memory
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_In.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Register_In
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_InOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Register_InOut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_notZeroLength_Out.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Register_notZeroLength_Out
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_zeroLength_Out.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Register_zeroLength_Out
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= ReleaseSharedMemory_null.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= ReleaseSharedMemory_null
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_error_notExistingTA.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= OpenSession_error_notExistingTA
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_error_originTEE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= OpenSession_error_originTEE
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_success_nullReturnOrigin.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= OpenSession_success_nullReturnOrigin
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_success_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= OpenSession_success_originTrustedApp
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_error_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= OpenSession_error_originTrustedApp
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_with_operation_parameters.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= OpenSession_with_operation_parameters
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= CloseSession_null.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= CloseSession_null
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_error_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_error_originTrustedApp
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_success_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_success_originTrustedApp
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_0param.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_0param
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefPartialInOut_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_1param_memrefPartialInOut_allocated
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefPartialInOut_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_1param_memrefPartialInOut_registered
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefTempInOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_1param_memrefTempInOut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefWhole_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_1param_memrefWhole_allocated
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefWhole_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_1param_memrefWhole_registered
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_valueInOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_1param_valueInOut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_allocated
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_registered
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_withTooShortBuffer.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_withTooShortBuffer
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memRefTempIn_memRefTempOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_memRefTempIn_memRefTempOut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_valueIn_valueOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_valueIn_valueOut
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_allocated
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_registered
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_3param.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_3param
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_4param.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS := optional
LOCAL_MODULE:= Invoke_4param
ifeq ($(CFG_HI_TVP_SUPPORT), y)
ALL_DEFAULT_INSTALLED_MODULES += $(LOCAL_MODULE)
endif
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
