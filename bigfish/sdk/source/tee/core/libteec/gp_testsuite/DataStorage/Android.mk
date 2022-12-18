LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_AES.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_AES
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_DES.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_DES
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_DES3.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_DES3
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_DH_KEYPAIR.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_DH_KEYPAIR
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_GENERIC_SECRET.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_GENERIC_SECRET
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_MD5.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_MD5
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA1
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA224.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA224
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA256.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA256
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA384.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA384
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA512.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_HMAC_SHA512
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_RSA_KEYPAIR.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_RSA_KEYPAIR
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_RSA_PUBLIC_KEY.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_correct_size_TEE_TYPE_RSA_PUBLIC_KEY
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_AES.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_AES
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DES.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DES
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DES3.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DES3
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DH_KEYPAIR.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DH_KEYPAIR
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_KEYPAIR.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_KEYPAIR
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_PUBLIC_KEY.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_DSA_PUBLIC_KEY
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_GENERIC_SECRET.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_GENERIC_SECRET
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_MD5.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_MD5
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA1
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA224.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA224
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA256.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA256
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA384.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA384
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA512.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_HMAC_SHA512
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_RSA_KEYPAIR.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_RSA_KEYPAIR
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_RSA_PUBLIC_KEY.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_AllocateTransientChain_incorrect_size_object_TEE_TYPE_RSA_PUBLIC_KEY
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CloseAndDeletePersistentObjectPanic_object_is_not_a_valid_opened_object_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CloseAndDeletePersistentObjectPanic_object_is_not_a_valid_opened_object_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CloseFreeAndResetObjectSuccessHandleNull_handle_equal_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CloseFreeAndResetObjectSuccessHandleNull_handle_equal_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CloseObjectPanic_handle_not_correct_and_not_equal_to_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CloseObjectPanic_handle_not_correct_and_not_equal_to_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CreatePersistentObject_ItemNotFound_storageID_not_found.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CreatePersistentObject_ItemNotFound_storageID_not_found
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CreatePersistentObject_Success_object_created_with_access_read.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CreatePersistentObject_Success_object_created_with_access_read
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CreatePersistentObject_Success_object_created_with_access_write.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CreatePersistentObject_Success_object_created_with_access_write
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CreatePersistentObject_Success_object_created_with_access_write_meta.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CreatePersistentObject_Success_object_created_with_access_write_meta
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CreatePersistentObject_Success_object_created_with_sharing_read.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CreatePersistentObject_Success_object_created_with_sharing_read
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_CreatePersistentObject_Success_object_created_with_sharing_write.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_CreatePersistentObject_Success_object_created_with_sharing_write
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_EnumeratorOnPersistentObjects_success.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_EnumeratorOnPersistentObjects_success
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_FreeCloseAndDeletePersistentObjectSuccessHandleNull.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_FreeCloseAndDeletePersistentObjectSuccessHandleNull
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_FreePersistentObjectEnumerator_handle_not_valid.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_FreePersistentObjectEnumerator_handle_not_valid
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_FreeTransientObjectPanic_handle_not_correct_and_not_equal_to_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_FreeTransientObjectPanic_handle_not_correct_and_not_equal_to_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_AES_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_AES_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_DES3_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_DES3_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_DES_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_DES_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_DH_KEYPAIR_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_DH_KEYPAIR_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_GENERIC_SECRET_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_GENERIC_SECRET_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_HMAC_MD5_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_HMAC_MD5_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA1_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA1_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA224_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA224_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA256_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA256_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA384_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA384_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA512_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_HMAC_SHA512_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GenerateKey_TEE_TYPE_RSA_KEYPAIR_correct_size_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetBufferAttribute_object_uninitialized.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetBufferAttribute_object_uninitialized
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetDHAttributes_success_DH_BASE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetDHAttributes_success_DH_BASE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetDHAttributes_success_DH_PRIME.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetDHAttributes_success_DH_PRIME
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetDHAttributes_success_DH_PRIVATE_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetDHAttributes_success_DH_PRIVATE_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetDHAttributes_success_DH_PUBLIC_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetDHAttributes_success_DH_PUBLIC_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetDHAttributes_success_DH_X_BITS.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetDHAttributes_success_DH_X_BITS
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetNextPersistentObject_handle_not_valid.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetNextPersistentObject_handle_not_valid
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetObjectInfoPanic_object_is_not_a_valid_opened_object_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetObjectInfoPanic_object_is_not_a_valid_opened_object_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetObjectValueAttribute_panic.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetObjectValueAttribute_panic
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetRSAAttributes_success_COEFFICIENT.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetRSAAttributes_success_COEFFICIENT
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetRSAAttributes_success_EXPONENT1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetRSAAttributes_success_EXPONENT1
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetRSAAttributes_success_EXPONENT2.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetRSAAttributes_success_EXPONENT2
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetRSAAttributes_success_PRIME1.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetRSAAttributes_success_PRIME1
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetRSAAttributes_success_PRIME2.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetRSAAttributes_success_PRIME2
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_GetValueAttribute_itemNotFound.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_GetValueAttribute_itemNotFound
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_AES_success_attribute_TEE_ATTR_SECRET_VALUE_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_AES_success_attribute_TEE_ATTR_SECRET_VALUE_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_DES3_success_attribute_TEE_ATTR_SECRET_VALUE_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_DES3_success_attribute_TEE_ATTR_SECRET_VALUE_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_DES_success_attribute_TEE_ATTR_SECRET_VALUE_correct_size.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_DES_success_attribute_TEE_ATTR_SECRET_VALUE_correct_size
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_DH_KEYPAIR_success_attribute_TEE_ATTR_DH_BASE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_DH_KEYPAIR_success_attribute_TEE_ATTR_DH_BASE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_DH_KEYPAIR_success_attribute_TEE_ATTR_DH_SUBPRIME.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_DH_KEYPAIR_success_attribute_TEE_ATTR_DH_SUBPRIME
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_GENERIC_SECRET_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_GENERIC_SECRET_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_MD5_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_MD5_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA1_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA1_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA224_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA224_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA256_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA256_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA384_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA384_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA512_success_attribute_TEE_ATTR_SECRET_VALUE.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_HMAC_SHA512_success_attribute_TEE_ATTR_SECRET_VALUE
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_RSA_KEYPAIR_success_attribute_TEE_ATTR_RSA_MODULUS.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_RSA_KEYPAIR_success_attribute_TEE_ATTR_RSA_MODULUS
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_TEE_TYPE_RSA_PUBLIC_KEY_success_attribute_TEE_ATTR_RSA_MODULUS.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_TEE_TYPE_RSA_PUBLIC_KEY_success_attribute_TEE_ATTR_RSA_MODULUS
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_attribute_not_found.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_attribute_not_found
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_buffer_too_small.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_buffer_too_small
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_handle_different_from_TEE_HANDLE_NULL.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_handle_different_from_TEE_HANDLE_NULL
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_invalid_object.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_invalid_object
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_object_is_not_initialized.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_object_is_not_initialized
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_populate_invalid_object.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_populate_invalid_object
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitObjectAndAttributes_src_is_persistent.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitObjectAndAttributes_src_is_persistent
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_InitValueAttribute_success.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_InitValueAttribute_success
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_Access_conflict.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_Access_conflict
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_ItemNotFound_object_not_existing.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_ItemNotFound_object_not_existing
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_ItemNotFound_storageID_not_found.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_ItemNotFound_storageID_not_found
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_Success_object_created_with_access_read.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_Success_object_created_with_access_read
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_Success_object_created_with_access_share_read.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_Success_object_created_with_access_share_read
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_Success_object_created_with_access_share_write.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_Success_object_created_with_access_share_write
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_Success_object_created_with_access_write.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_Success_object_created_with_access_write
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_OpenPersistentObject_Success_object_created_with_access_write_meta.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_OpenPersistentObject_Success_object_created_with_access_write_meta
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_ReadObjectDataAttribute_above_count.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_ReadObjectDataAttribute_above_count
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_ReadObjectDataAttribute_below_count.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_ReadObjectDataAttribute_below_count
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_ReadObjectDataAttribute_panic_bad_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_ReadObjectDataAttribute_panic_bad_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_RenamePersistentObject_AccessConflict.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_RenamePersistentObject_AccessConflict
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_RenamePersistentObject_Success_object_created_with_access_read_object_created_with_access_wri.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_RenamePersistentObject_Success_object_created_with_access_read_object_created_with_access_wri
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_ResetPersistentObjectEnumerator_handle_not_valid.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_ResetPersistentObjectEnumerator_handle_not_valid
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_ResetTransientObjectPanic_handle_not_correct.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_ResetTransientObjectPanic_handle_not_correct
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_RestrictObjectUsagePanic_object_is_not_a_valid_opened_object_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_RestrictObjectUsagePanic_object_is_not_a_valid_opened_object_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekObjectDataAttribute_panic_bad_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekObjectDataAttribute_panic_bad_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_CUR_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_CUR_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_CUR_Offset_High.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_CUR_Offset_High
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_CUR_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_CUR_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_END_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_END_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_END_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_END_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_SET_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_SET_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_SET_Offset_High.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_SET_Offset_High
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_0_SEEK_SET_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_0_SEEK_SET_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_High_SEEK_CUR_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_High_SEEK_CUR_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_High_SEEK_CUR_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_High_SEEK_CUR_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_High_SEEK_SET_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_CUR_Offset_High.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_CUR_Offset_High
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_CUR_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_CUR_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_END_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_END_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_END_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_END_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_SET_Offset_0.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_SET_Offset_0
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_SET_Offset_High.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_SET_Offset_High
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_SeekWriteRead_Offset_Low_SEEK_SET_Offset_Low.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_SeekWriteRead_Offset_Low_SEEK_SET_Offset_Low
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_StartNGetPersistentObjectEnumerator_itemNotFound.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_StartNGetPersistentObjectEnumerator_itemNotFound
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_StartPersistentObjectEnumerator_handle_not_valid.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_StartPersistentObjectEnumerator_handle_not_valid
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_TruncateObjectDataAttribute_panic_bad_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_TruncateObjectDataAttribute_panic_bad_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)

include $(CLEAR_VARS)
LOCAL_SRC_FILES:= Invoke_WriteObjectDataAttribute_panic_bad_handle.c
LOCAL_C_INCLUDES:= $(LOCAL_PATH)/../../inc
LOCAL_C_INCLUDES+= $(LOCAL_PATH)/..
LOCAL_MODULE_TAGS:= eng
LOCAL_MODULE:= Invoke_WriteObjectDataAttribute_panic_bad_handle
LOCAL_SHARED_LIBRARIES := libcutils libteec
include $(BUILD_EXECUTABLE)
