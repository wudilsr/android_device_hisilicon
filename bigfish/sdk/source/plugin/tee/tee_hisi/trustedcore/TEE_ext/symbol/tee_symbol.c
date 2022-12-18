/*******************************************************************************
 * All rights reserved, Copyright (C) huawei LIMITED 2012
 *------------------------------------------------------------------------------
 * File Name   : tee_symbol.c
 * Description : TEE export API list
 * Author      : h00206996
 * Date        : 2013.5.25
 * Notes       :
 *
 *------------------------------------------------------------------------------
 * Modifications:
 *   Date        Author          Modifications
 *******************************************************************************/
/*******************************************************************************
 * This source code has been made available to you by HUAWEI on an
 * AS-IS basis. Anyone receiving this source code is licensed under HUAWEI
 * copyrights to use it in any way he or she deems fit, including copying it,
 * modifying it, compiling it, and redistributing it either with or without
 * modifications. Any person who transfers this source code or any derivative
 * work must include the HUAWEI copyright notice and this paragraph in
 * the transferred software.
 *******************************************************************************/

#include <stdarg.h>
#include "ta_framework.h"
#include "tee_fs.h"
#include "tee_mem_mgmt_api.h"
#include "tee_trusted_storage_api.h"
#include "tee_c_env.h"
#include "sre_syscall.h"
#include "libc_private.h"
#include "tee_log.h"
#include "tee_crypto_api.h"
#include "tee_property_api.h"
#include "tee_time_api.h"
#include "tee_init.h"
#include "tee_core_api.h"
#include "sre_syscalls_ext.h"
#include "tz_unf_cipher.h"
#include "boot.h"

//add DX_API export
#include "DxTzServiceAPI.h"
#include "DxTzServiceSfs.h"
#include "infra_api.h"

#include "mmz.h"
#include "sec_mmz.h"
#include "sec_mem.h"

//lint -e10
//lint -e19
//lint -e31
//lint -e64
//lint -e509
//lint -e1055

/* for STB platform change TA number*/
#ifdef STB_CIPHER_DRIVER
#define DEFAULT_STACK_SIZE      0x4000
#else
#define DEFAULT_STACK_SIZE      0x1000
#endif
#define DEFAULT_HEAP_SIZE       0x20000

TA_property_t build_in_service_property[] = {
    /* uuid               stack  heap    instance  sessin  alive*/
    {TEE_SERVICE_ECHO,    DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true,     true,   false},
    {TEE_SERVICE_STORAGE, DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true,     true,   true},
    {TEE_SERVICE_UT,      DEFAULT_STACK_SIZE, DEFAULT_HEAP_SIZE, true,     false,  false},
    {TEE_SERVICE_CRYPT,   200*1024,           900*1024,          true,     true,   true},
    {TEE_SERVICE_DEMO,    200*1024,           900*1024,          true,     true,   true},
    {TEE_SERVICE_DEMO1,    200*1024,           900*1024,          true,     true,   true},
    {TEE_SERVICE_DEMO2,    200*1024,           900*1024,          true,     true,   true},
    {TEE_SERVICE_DEMO3,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
    {TEE_SERVICE_DEMO4,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
    {TEE_SERVICE_DEMO5,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
    {TEE_SERVICE_DEMO6,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
    {TEE_SERVICE_DEMO7,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
    {TEE_SERVICE_DEMO8,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
    {TEE_SERVICE_DEMO9,    DEFAULT_STACK_SIZE,           DEFAULT_HEAP_SIZE,          true,     true,   true},
};
TEE_UUID build_in_uuid[] = {TEE_SERVICE_GLOBAL, TEE_SERVICE_ECHO,
                                TEE_SERVICE_STORAGE, TEE_SERVICE_UT, TEE_SERVICE_CRYPT,
                                TEE_SERVICE_DEMO,TEE_SERVICE_DEMO1,TEE_SERVICE_DEMO2,
                                TEE_SERVICE_DEMO3,TEE_SERVICE_DEMO4,TEE_SERVICE_DEMO5,
                                TEE_SERVICE_DEMO6,TEE_SERVICE_DEMO7,TEE_SERVICE_DEMO8,
                                TEE_SERVICE_DEMO9};
uint32_t task_num = 14;

//dynamic load elf added
struct tee_symbol
{
    unsigned long addr;
    const char *symbol;
};

/* For every exported symbol, place a struct in the __tee_symtab section */
#define __EXPORT_SYMBOL(sym, sec)                                       \
    extern typeof(sym) sym;                                             \
    const char __tee_strtab_##sym[]           \
    __attribute__((section("__tee_symstr"), aligned(1)))              \
         =  #sym;                                    \
    const struct tee_symbol __tee_symtab_##sym \
    __attribute__((section("__tee_symtab" sec), unused)) \
         = { (unsigned long)&sym, __tee_strtab_##sym }

#define EXPORT_SYMBOL(sym)  \
    __EXPORT_SYMBOL(sym, "")


//#define SRVX_EXPORT __attribute__(section(".srvx.text"))

EXPORT_SYMBOL(__test_sys);
//map
EXPORT_SYMBOL(__map_to_ns);
EXPORT_SYMBOL(__unmap_from_ns);
EXPORT_SYMBOL(__map_to_s);
EXPORT_SYMBOL(__unmap_from_s);
EXPORT_SYMBOL(__map_to_ns_nocache);
EXPORT_SYMBOL(__unmap_from_ns_nocache);
EXPORT_SYMBOL(__map_to_s_nocache);
EXPORT_SYMBOL(__unmap_from_s_nocache);

//tee_init.c
EXPORT_SYMBOL(tee_init);
EXPORT_SYMBOL(tee_exit);
EXPORT_SYMBOL(tee_init_context);
EXPORT_SYMBOL(get_current_uuid);
EXPORT_SYMBOL(get_current_session_id);
EXPORT_SYMBOL(get_current_dev_id);

//tee_trusted_storage_api.c
EXPORT_SYMBOL(tee_storage_init);
EXPORT_SYMBOL(tee_storage_exit);
EXPORT_SYMBOL(TEE_GetObjectInfo);
EXPORT_SYMBOL(TEE_RestrictObjectUsage);
EXPORT_SYMBOL(TEE_GetObjectBufferAttribute);
EXPORT_SYMBOL(TEE_GetObjectValueAttribute);
EXPORT_SYMBOL(TEE_CloseObject);
EXPORT_SYMBOL(TEE_AllocateTransientObject);
EXPORT_SYMBOL(TEE_FreeTransientObject);
EXPORT_SYMBOL(TEE_ResetTransientObject);
EXPORT_SYMBOL(TEE_PopulateTransientObject);
EXPORT_SYMBOL(TEE_InitRefAttribute);
EXPORT_SYMBOL(TEE_InitValueAttribute);
EXPORT_SYMBOL(TEE_CopyObjectAttributes);
EXPORT_SYMBOL(TEE_GenerateKey);
EXPORT_SYMBOL(TEE_CreatePersistentObject);
EXPORT_SYMBOL(TEE_OpenPersistentObject);
EXPORT_SYMBOL(TEE_ReadObjectData);
EXPORT_SYMBOL(TEE_WriteObjectData);
EXPORT_SYMBOL(TEE_TruncateObjectData);
EXPORT_SYMBOL(TEE_SeekObjectData);
EXPORT_SYMBOL(TEE_CloseAndDeletePersistentObject);
EXPORT_SYMBOL(TEE_RenamePersistentObject);
EXPORT_SYMBOL(TEE_AllocatePersistentObjectEnumerator);
EXPORT_SYMBOL(TEE_FreePersistentObjectEnumerator);
EXPORT_SYMBOL(TEE_ResetPersistentObjectEnumerator);
EXPORT_SYMBOL(TEE_StartPersistentObjectEnumerator);
EXPORT_SYMBOL(TEE_GetNextPersistentObject);


//tee_fs.c
EXPORT_SYMBOL(dump_current_fd_map);

EXPORT_SYMBOL(faccess);
EXPORT_SYMBOL(faccess2);
EXPORT_SYMBOL(fcreate);
EXPORT_SYMBOL(fopen);
EXPORT_SYMBOL(fwrite);
EXPORT_SYMBOL(fread);
EXPORT_SYMBOL(fseek);
EXPORT_SYMBOL(fclose);
EXPORT_SYMBOL(finfo);
EXPORT_SYMBOL(fremove);
EXPORT_SYMBOL(ftruncate);

EXPORT_SYMBOL(s_fwrite);
EXPORT_SYMBOL(s_fread);
EXPORT_SYMBOL(s_fopen);
EXPORT_SYMBOL(s_fremove);
EXPORT_SYMBOL(s_ftruncate);
EXPORT_SYMBOL(s_frename);
EXPORT_SYMBOL(s_fcreate);
EXPORT_SYMBOL(s_faccess);

//tee_mem_mgmt_api.c
EXPORT_SYMBOL(TEE_Free);
EXPORT_SYMBOL(TEE_Malloc);
EXPORT_SYMBOL(TEE_MemCompare);
EXPORT_SYMBOL(TEE_MemFill);
EXPORT_SYMBOL(TEE_MemMove);
EXPORT_SYMBOL(TEE_Realloc);
EXPORT_SYMBOL(TEE_GetInstanceData);
EXPORT_SYMBOL(TEE_SetInstanceData);
EXPORT_SYMBOL(get_mem_usage);

//others
#ifndef STB_CIPHER_DRIVER
extern int memcmp(void *_a, void *_b, unsigned len);
extern size_t strlen(const char *s);
#endif

void __aeabi_memcpy(void *dest, const void *src, size_t n){
    (void)memcpy(dest, (void*)src, n);
}

void __aeabi_memcpy4(void *dest, const void *src, size_t n){
    (void)memcpy(dest, (void*)src, n);
}

extern void *memcpy(void *_dst, const void *_src, unsigned len);
extern char *strcpy(char *dest, const char *src);
extern void *memset(void *_p, unsigned v, unsigned count);
extern uint8_t* SHA(const void *data, int len, uint8_t *digest);
extern int snprintf(char *str, int sz, const char *fmt, ...);
EXPORT_SYMBOL(memcmp);
EXPORT_SYMBOL(memcpy);
EXPORT_SYMBOL(strcpy);
EXPORT_SYMBOL(strlen);
EXPORT_SYMBOL(memset);
EXPORT_SYMBOL(snprintf);
EXPORT_SYMBOL(SHA);
EXPORT_SYMBOL(__aeabi_memcpy);
EXPORT_SYMBOL(__aeabi_memcpy4);
extern __aeabi_uidivmod();
EXPORT_SYMBOL(__aeabi_uidivmod);

void uart_printf_func(const char *fmt, ...)
{
    va_list ap = {0};
    (void)va_start(ap, fmt);
    __xprintf(fmt, ap, __console_putc, 0);
    va_end(ap);

}
EXPORT_SYMBOL(uart_printf_func);

//syscalls
#if 0
EXPORT_SYMBOL(__SRE_MsgReceive);
EXPORT_SYMBOL(__SRE_MsgQSend);
EXPORT_SYMBOL(__SRE_MsgAlloc);
EXPORT_SYMBOL(__SRE_MsgDelete);
#endif
EXPORT_SYMBOL(__SRE_HuntByName);
EXPORT_SYMBOL(__SRE_MsgRcv);
EXPORT_SYMBOL(__SRE_MsgSnd);
EXPORT_SYMBOL(cinit00);
#if 1
EXPORT_SYMBOL(__SRE_HwiCreate);
EXPORT_SYMBOL(__SRE_HwiDelete);
EXPORT_SYMBOL(__SRE_HwiTrigger);
EXPORT_SYMBOL(__SRE_HwiClearPendingBit);
EXPORT_SYMBOL(__SRE_HwiDisable);
EXPORT_SYMBOL(__SRE_HwiEnable);

EXPORT_SYMBOL(__SRE_SwiCreate);
EXPORT_SYMBOL(__SRE_SwiDelete);
EXPORT_SYMBOL(__SRE_SwiEnable);
EXPORT_SYMBOL(__SRE_SwiDisable);
EXPORT_SYMBOL(__SRE_SwiActivate);

EXPORT_SYMBOL(__VDEC_Suspend);
EXPORT_SYMBOL(__VDEC_Init);
EXPORT_SYMBOL(__VDEC_Resume);
EXPORT_SYMBOL(__VFMW_CTRL_thread_sec);
EXPORT_SYMBOL(__VDEC_Control);
EXPORT_SYMBOL(__VDEC_InitWithOperation);
EXPORT_SYMBOL(__VCTRL_WriteProc);
EXPORT_SYMBOL(__VCTRL_ReadProc);
EXPORT_SYMBOL(__VCTRL_SetDbgOption);
EXPORT_SYMBOL(__VCTRL_GetChanImage);
EXPORT_SYMBOL(__VCTRL_ReleaseChanImage);
EXPORT_SYMBOL(__VDEC_Exit);

#endif
//for ut temporary
EXPORT_SYMBOL(__SRE_MemUsageGet);


// tee_log.c
EXPORT_SYMBOL(SLog);

// tee_crypto_api.c
EXPORT_SYMBOL(TEE_AllocateOperation);
EXPORT_SYMBOL(TEE_FreeOperation);
EXPORT_SYMBOL(TEE_GetOperationInfo);
EXPORT_SYMBOL(TEE_ResetOperation);
EXPORT_SYMBOL(TEE_SetOperationKey);
EXPORT_SYMBOL(TEE_SetOperationKey2);
EXPORT_SYMBOL(TEE_CopyOperation);
EXPORT_SYMBOL(TEE_CipherInit);
EXPORT_SYMBOL(TEE_CipherUpdate);
EXPORT_SYMBOL(TEE_CipherDoFinal);
EXPORT_SYMBOL(TEE_DigestUpdate);
EXPORT_SYMBOL(TEE_DigestDoFinal);
EXPORT_SYMBOL(TEE_MACInit);
EXPORT_SYMBOL(TEE_MACUpdate);
EXPORT_SYMBOL(TEE_MACComputeFinal);
EXPORT_SYMBOL(TEE_MACCompareFinal);
EXPORT_SYMBOL(TEE_DeriveKey);
EXPORT_SYMBOL(TEE_GenerateRandom);
EXPORT_SYMBOL(TEE_AEInit);
EXPORT_SYMBOL(TEE_AEUpdateAAD);
EXPORT_SYMBOL(TEE_AEUpdate);
EXPORT_SYMBOL(TEE_AEEncryptFinal);
EXPORT_SYMBOL(TEE_AEDecryptFinal);
EXPORT_SYMBOL(TEE_AsymmetricEncrypt);
EXPORT_SYMBOL(TEE_AsymmetricDecrypt);
EXPORT_SYMBOL(TEE_AsymmetricSignDigest);
EXPORT_SYMBOL(TEE_AsymmetricVerifyDigest);

// tee_property_api.c
extern void init_non_std_property(char *buff, uint32_t len);
EXPORT_SYMBOL(init_non_std_property);
EXPORT_SYMBOL(TEE_GetPropertyAsString);
EXPORT_SYMBOL(TEE_GetPropertyAsBool);
EXPORT_SYMBOL(TEE_GetPropertyAsU32);
EXPORT_SYMBOL(TEE_GetPropertyAsBinaryBlock);
EXPORT_SYMBOL(TEE_GetPropertyAsUUID);
EXPORT_SYMBOL(TEE_GetPropertyAsIdentity);
EXPORT_SYMBOL(TEE_AllocatePropertyEnumerator);
EXPORT_SYMBOL(TEE_FreePropertyEnumerator);
EXPORT_SYMBOL(TEE_StartPropertyEnumerator);
EXPORT_SYMBOL(TEE_ResetPropertyEnumerator);
EXPORT_SYMBOL(TEE_GetPropertyName);
EXPORT_SYMBOL(TEE_GetNextProperty);

// tee_time_api.c
EXPORT_SYMBOL(TEE_GetSystemTime);
EXPORT_SYMBOL(TEE_Wait);
EXPORT_SYMBOL(TEE_GetTAPersistentTime);
EXPORT_SYMBOL(TEE_SetTAPersistentTime);
EXPORT_SYMBOL(TEE_GetREETime);
EXPORT_SYMBOL(get_sys_rtc_time);

//memcpy
EXPORT_SYMBOL(__mem_copy);

// MMZ interface
EXPORT_SYMBOL(__MMZ_MALLOC);
EXPORT_SYMBOL(__MMZ_FREE);
EXPORT_SYMBOL(__MMZ_NEW);
EXPORT_SYMBOL(__MMZ_DEL);
EXPORT_SYMBOL(__MMZ_MAP);
EXPORT_SYMBOL(__MMZ_UNMAP);
EXPORT_SYMBOL(__MMZ_FLUSH);

EXPORT_SYMBOL(__TEE_IsSecMem);
EXPORT_SYMBOL(__TEE_IsNonSecMem);
EXPORT_SYMBOL(__call_debug);


EXPORT_SYMBOL(HI_MMZ_Malloc);
EXPORT_SYMBOL(HI_MMZ_Free);
EXPORT_SYMBOL(HI_MMZ_New);
EXPORT_SYMBOL(HI_MMZ_Delete);
EXPORT_SYMBOL(HI_MMZ_Map);
EXPORT_SYMBOL(HI_MMZ_Unmap);
EXPORT_SYMBOL(HI_MMZ_Flush);

EXPORT_SYMBOL(HI_SEC_MMZ_New);
EXPORT_SYMBOL(HI_SEC_MMZ_Delete);
EXPORT_SYMBOL(HI_SEC_MMZ_Map);
EXPORT_SYMBOL(HI_SEC_MMZ_Unmap);
EXPORT_SYMBOL(HI_SEC_MMZ_Flush);
EXPORT_SYMBOL(HI_SEC_MMZ_NewAndMap);
EXPORT_SYMBOL(HI_SEC_MMZ_DelAndUnmap);

EXPORT_SYMBOL(HI_TEE_IsSecureMem);
EXPORT_SYMBOL(HI_TEE_IsNonSecureMem);

EXPORT_SYMBOL(__Cipher_Init);
EXPORT_SYMBOL(__Cipher_DeInit);
EXPORT_SYMBOL(__Cipher_CreateHandle);
EXPORT_SYMBOL(__Cipher_DestroyHandle);
EXPORT_SYMBOL(__Cipher_ConfigHandle);
EXPORT_SYMBOL(__Cipher_GetHandleConfig);
EXPORT_SYMBOL(__Cipher_Encrypt);
EXPORT_SYMBOL(__Cipher_Decrypt);
EXPORT_SYMBOL(__Cipher_EncryptMulti);
EXPORT_SYMBOL(__Cipher_DecryptMulti);
EXPORT_SYMBOL(__Cipher_HashInit);
EXPORT_SYMBOL(__Cipher_HashUpdate);
EXPORT_SYMBOL(__Cipher_HashFinal);
EXPORT_SYMBOL(__Cipher_GetRandomNumber);
EXPORT_SYMBOL(__Cipher_GetIVOut);
EXPORT_SYMBOL(__Cipher_EncryptHDCPKey);
EXPORT_SYMBOL(__Cipher_LoadHDCPKey);
EXPORT_SYMBOL(__Cipher_Test);

EXPORT_SYMBOL(TZ_UNF_CIPHER_Init);
EXPORT_SYMBOL(TZ_UNF_CIPHER_DeInit);
EXPORT_SYMBOL(TZ_UNF_CIPHER_Encrypt);
EXPORT_SYMBOL(TZ_UNF_CIPHER_Decrypt);
EXPORT_SYMBOL(TZ_UNF_CIPHER_EncryptMulti);
EXPORT_SYMBOL(TZ_UNF_CIPHER_DecryptMulti);
EXPORT_SYMBOL(TZ_UNF_CIPHER_ConfigHandle);
EXPORT_SYMBOL(TZ_UNF_CIPHER_CreateHandle);
EXPORT_SYMBOL(TZ_UNF_CIPHER_DestroyHandle);
EXPORT_SYMBOL(TZ_UNF_CIPHER_GetHandleConfig);
EXPORT_SYMBOL(TZ_UNF_CIPHER_GetRandomNumber);
EXPORT_SYMBOL(TZ_UNF_CIPHER_EncryptHdcpKey);
EXPORT_SYMBOL(TZ_UNF_CIPHER_LoadHdcpKey);
EXPORT_SYMBOL(TZ_UNF_CIPHER_GetIVOut);
EXPORT_SYMBOL(TZ_UNF_CIPHER_HashInit);
EXPORT_SYMBOL(TZ_UNF_CIPHER_HashUpdate);
EXPORT_SYMBOL(TZ_UNF_CIPHER_HashFinal);
EXPORT_SYMBOL(TZ_UNF_CIPHER_Test);

// tee_core_api.c
EXPORT_SYMBOL(TEE_Panic);


//for dx export
extern DxUint32  DxTzService_IsDeviceRooted(void);
extern DxBool DxTzService_IsBootLoaderUnlocked(void);
extern DxStatus DxTzService_InitSecureContentPath(void);
extern DxStatus DxTzService_TerminateSecureContentPath(void);
extern DxStatus DxTzService_IsSecureContentMemory(DxTzServiceSharedMemRef *ptr, DxUint32 dataOffset, DxUint32 size, DxBool *res);
EXPORT_SYMBOL(g_dx_content_path_addr);
EXPORT_SYMBOL(DxTzService_IsDeviceRooted);
EXPORT_SYMBOL(DxTzService_IsBootLoaderUnlocked);
EXPORT_SYMBOL(DxTzService_InitSecureContentPath);
EXPORT_SYMBOL(DxTzService_TerminateSecureContentPath);
EXPORT_SYMBOL(DxTzService_IsSecureContentMemory);

// DxTzServiceAPI.c
EXPORT_SYMBOL(sfs_init);
EXPORT_SYMBOL(DxTzService_SetGlobalInstance);
EXPORT_SYMBOL(DxTzService_GetGlobalInstance);
EXPORT_SYMBOL(DxTzService_ReadFromSecureStorage);
EXPORT_SYMBOL(DxTzService_WriteToSecureStorage);
EXPORT_SYMBOL(DxTzService_GetSecureStorageFileSize);
EXPORT_SYMBOL(DxTzService_Malloc);
EXPORT_SYMBOL(DxTzService_Realloc);
EXPORT_SYMBOL(DxTzService_Free);
EXPORT_SYMBOL(DxTzService_MemCpy);
EXPORT_SYMBOL(DxTzService_MemCpyReverse);
EXPORT_SYMBOL(DxTzService_MemSet);
EXPORT_SYMBOL(DxTzService_MemCmp);
EXPORT_SYMBOL(DxTzService_GetDeviceKey);
EXPORT_SYMBOL(DxTzService_Get_Device_UniqueId);
EXPORT_SYMBOL(DxTzService_GetTimestamp);
EXPORT_SYMBOL(DxTzService_DurationSinceTimestamp);
EXPORT_SYMBOL(DxTzService_Get_HDMI_HDCP1_Status);
EXPORT_SYMBOL(DxTzService_GetHDCP2ConnectionStatus);
EXPORT_SYMBOL(DxTzService_SetHDCP2ConnectionStatus);
EXPORT_SYMBOL(DxTzService_HDCP1RelaxationCycles);
EXPORT_SYMBOL(DxTzService_GetAppName);
EXPORT_SYMBOL(DxTzService_GetSfsRootPath);
EXPORT_SYMBOL(DxTzService_ConvertToSharedMemRef);
EXPORT_SYMBOL(DxTzService_MemCpyEx);
EXPORT_SYMBOL(DxTzService_MemSetEx);
EXPORT_SYMBOL(DxTzService_MemCmpEx);
EXPORT_SYMBOL(DxTzService_IsNonSecureContentMemory);
EXPORT_SYMBOL(DxTzService_IsAudioPacket);
EXPORT_SYMBOL(DxTzService_StrNCopy);
EXPORT_SYMBOL(DxTzService_StrNLen);
EXPORT_SYMBOL(DxTzService_StrNCmp);
EXPORT_SYMBOL(DxTzService_MemMove);

// DxTzServiceCryptoAPI.c
EXPORT_SYMBOL(DxTzService_RandomGenerate);
EXPORT_SYMBOL(DxTzService_AES128_CreateContext);
EXPORT_SYMBOL(DxTzService_AES128_TerminateContext);
EXPORT_SYMBOL(DxTzService_AES128CTR_Init);
EXPORT_SYMBOL(DxTzService_AES128CTR_DecryptData);
EXPORT_SYMBOL(DxTzService_AES128CTR_EncryptData);
EXPORT_SYMBOL(DxTzService_AES128CTR_DecryptDataEx);
EXPORT_SYMBOL(DxTzService_AES128CTR_EncryptDataEx);
EXPORT_SYMBOL(DxTzService_AES128CTR_Finish);
EXPORT_SYMBOL(DxTzService_AES128CBC_Init);
EXPORT_SYMBOL(DxTzService_AES128CBC_DecryptData);
EXPORT_SYMBOL(DxTzService_AES128CBC_EncryptData);
EXPORT_SYMBOL(DxTzService_AES128CBC_DecryptDataEx);
EXPORT_SYMBOL(DxTzService_AES128CBC_EncryptDataEx);
EXPORT_SYMBOL(DxTzService_AES128CBC_Finish);
EXPORT_SYMBOL(DxTzService_AES128ECB_Init);
EXPORT_SYMBOL(DxTzService_AES128ECB_DecryptData);
EXPORT_SYMBOL(DxTzService_AES128ECB_EncryptData);
EXPORT_SYMBOL(DxTzService_AES128ECB_Finish);
EXPORT_SYMBOL(DxTzService_SHA1Init);
EXPORT_SYMBOL(DxTzService_SHA1Update);
EXPORT_SYMBOL(DxTzService_SHA1Final);
EXPORT_SYMBOL(DxTzService_SHA1Terminate);
EXPORT_SYMBOL(DxTzService_SHA256Init);
EXPORT_SYMBOL(DxTzService_SHA256Update);
EXPORT_SYMBOL(DxTzService_SHA256Final);
EXPORT_SYMBOL(DxTzService_SHA256Terminate);
EXPORT_SYMBOL(DxTzService_MD5Init);
EXPORT_SYMBOL(DxTzService_MD5Update);
EXPORT_SYMBOL(DxTzService_MD5Final);
EXPORT_SYMBOL(DxTzService_MD5Terminate);
EXPORT_SYMBOL(DxTzService_HMAC_SHA256Init);
EXPORT_SYMBOL(DxTzService_HMAC_SHA256Update);
EXPORT_SYMBOL(DxTzService_HMAC_SHA256Final);
EXPORT_SYMBOL(DxTzService_HMAC_SHA256Terminate);
EXPORT_SYMBOL(DxTzService_RSA_OAEP_DecryptData);
EXPORT_SYMBOL(DxTzService_RSA_OAEP_EncryptData);
EXPORT_SYMBOL(DxTzService_RSA_PKCS1v15_DecryptData);
EXPORT_SYMBOL(DxTzService_RSA_PKCS1v15_EncryptData);
EXPORT_SYMBOL(DxTzService_RSA_PSS_VerifyDataSignature);
EXPORT_SYMBOL(DxTzService_RSA_PKCS1v15_VerifyDataSignature);

// DxTzServiceSfs.c
EXPORT_SYMBOL(DxSfsInitialize);
EXPORT_SYMBOL(DxSfsFinalize);
EXPORT_SYMBOL(DxSfsGetSize);
EXPORT_SYMBOL(DxSfsRead);
EXPORT_SYMBOL(DxSfsWrite);
EXPORT_SYMBOL(DxSfsDelete);
EXPORT_SYMBOL(DxSfsCreateContainer);

//stub.c
extern DxUint DxTzService_IsNotMemEqualSecured (const void *p1, const void * p2, DxUint32 nBytes);
extern DxUint DxTzService_EstimateUnwrappedSize (DxUint wrappedSize);
extern DxUint DxTzService_EstimateWrappedSize (DxUint clearSize);
extern DxStatus DxTzService_UnwrapBuffer (const void* pSrc, DxUint srcLen, void* pDst, DxUint *pDstLen);
extern DxStatus DxTzService_WrapBuffer (const void* pSrc, DxUint srcLen, void* pDst, DxUint *pDstLen);
EXPORT_SYMBOL(DxTzService_IsNotMemEqualSecured);
EXPORT_SYMBOL(DxTzService_EstimateUnwrappedSize);
EXPORT_SYMBOL(DxTzService_EstimateWrappedSize);
EXPORT_SYMBOL(DxTzService_UnwrapBuffer);
EXPORT_SYMBOL(DxTzService_WrapBuffer);

//lint +e10
//lint +e19
//lint +e31
//lint +e64
//lint +e509
//lint +e1055
