LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= InitializeContext_concurrentContext.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= InitializeContext_concurrentContext
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= InitializeContext_NotExistingTEE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= InitializeContext_NotExistingTEE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= FinalizeContext_null.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= FinalizeContext_null
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_In.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Allocate_In
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_InOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Allocate_InOut
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_Out.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Allocate_Out
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Allocate_out_of_memory.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Allocate_out_of_memory
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_In.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Register_In
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_InOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Register_InOut
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_notZeroLength_Out.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Register_notZeroLength_Out
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Register_zeroLength_Out.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Register_zeroLength_Out
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= ReleaseSharedMemory_null.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= ReleaseSharedMemory_null
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_error_notExistingTA.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= OpenSession_error_notExistingTA
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_error_originTEE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= OpenSession_error_originTEE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_success_nullReturnOrigin.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= OpenSession_success_nullReturnOrigin
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_success_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= OpenSession_success_originTrustedApp
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_error_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= OpenSession_error_originTrustedApp
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= OpenSession_with_operation_parameters.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= OpenSession_with_operation_parameters
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= CloseSession_null.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= CloseSession_null
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_error_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_error_originTrustedApp
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_success_originTrustedApp.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_success_originTrustedApp
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_0param.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_0param
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefPartialInOut_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_1param_memrefPartialInOut_allocated
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefPartialInOut_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_1param_memrefPartialInOut_registered
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefTempInOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_1param_memrefTempInOut
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefWhole_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_1param_memrefWhole_allocated
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_memrefWhole_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_1param_memrefWhole_registered
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_1param_valueInOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_1param_valueInOut
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_allocated
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_registered
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_withTooShortBuffer.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_withTooShortBuffer
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memRefTempIn_memRefTempOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_memRefTempIn_memRefTempOut
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_valueIn_valueOut.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_valueIn_valueOut
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_allocated.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_allocated
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_registered.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_2param_memrefPartialIn_memrefPartialOut_withZeroSize_registered
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_3param.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_3param
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_4param.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_4param
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
