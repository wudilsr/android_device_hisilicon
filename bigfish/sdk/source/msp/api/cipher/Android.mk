TVP_DIR=${SDK_DIR}/source/plugin/tvp
CIPHER_DIR := cipher
LOCAL_SRC_FILES += $(CIPHER_DIR)/unf_cipher.c
CFG_HI_CIPHER_TVP_TEST=n
ifeq ($(CFG_HI_CIPHER_TVP_TEST),y)
LOCAL_SRC_FILES += $(CIPHER_DIR)/mpi_cipher_tz.c
LOCAL_C_INCLUDES += $(TVP_DIR)/libteec/inc
LOCAL_C_INCLUDES += $(TVP_DIR)/trustedcore/include/HS_API
LOCAL_C_INCLUDES += $(TVP_DIR)/trustedcore/thirdparty
LOCAL_C_INCLUDES += $(TVP_DIR)/trustedcore/thirdparty/cipher_code
LOCAL_C_INCLUDES += $(TVP_DIR)/trustedcore/include_kernel
LOCAL_SHARED_LIBRARIES += libteec
else
LOCAL_SRC_FILES += $(CIPHER_DIR)/mpi_cipher.c
endif