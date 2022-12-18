#include "sre_syscalls_id_ext.h"
/*STB Cipher begin*/
    .global __Cipher_Init
    .global __Cipher_DeInit
    .global __Cipher_CreateHandle
    .global __Cipher_DestroyHandle
    .global __Cipher_ConfigHandle
    .global __Cipher_GetHandleConfig
    .global __Cipher_Encrypt
    .global __Cipher_Decrypt
    .global __Cipher_EncryptMulti
    .global __Cipher_DecryptMulti
    .global __Cipher_CalcMAC
    .global __Cipher_HashInit
    .global __Cipher_HashUpdate
    .global __Cipher_HashFinal
    .global __Cipher_GetRandomNumber
    .global __Cipher_EncryptHDCPKey
    .global __Cipher_LoadHDCPKey
    .global __Cipher_GetIVOut
    .global __Cipher_Test
    .global __VDEC_Suspend
    .global __VDEC_Init
    .global __VDEC_Resume
    .global __VFMW_CTRL_thread_sec
    .global __VDEC_Control
    .global __VDEC_InitWithOperation
    .global __VCTRL_WriteProc  
    .global __VCTRL_ReadProc
    .global __VCTRL_SetDbgOption
    .global __VCTRL_GetChanImage	
    .global __VCTRL_ReleaseChanImage
    .global __VDEC_Exit
    .global __MMZ_NEW
    .global __MMZ_DEL
    .global __MMZ_MALLOC
    .global __MMZ_FREE
    .global __MMZ_MAP
    .global __MMZ_UNMAP
    .global __MMZ_FLUSH

    .global __mem_copy

    .global __TEE_IsSecMem
    .global __TEE_IsNonSecMem
    .global __call_debug
    .global __CC_CRYS_HMAC_Init
    .global __CC_CRYS_HMAC_Update
    .global __CC_CRYS_HMAC_Finish
    .global __CC_CRYS_AES_Init
    .global __CC_CRYS_AES_Block
    .global __CC_CRYS_AES_Finish
    .global __CC__DX_RSA_SCHEMES_Encrypt
    .global __CC__DX_RSA_SCHEMES_Decrypt
    .global __CC__DX_RSA_Sign
    .global __CC__DX_RSA_Verify
    .global __CC_CRYS_RSA_KG_GenerateKeyPairCRT
    .global __CC_CRYS_RSA_KG_GenerateKeyPair
    .global __CC_CRYS_RSA_Build_PubKey
    .global __CC_CRYS_RSA_Build_PrivKey
    .global __CC_CRYS_RSA_Build_PrivKeyCRT
    .global __CC__DX_RSA_SCHEMES_Encrypt
    .global __CC__DX_RSA_SCHEMES_Decrypt
    .global __CC_CRYS_RSA_PRIM_Encrypt
    .global __CC_CRYS_RSA_PRIM_Decrypt
    .global __CC_CRYS_DES_Free
    .global __CC_CRYS_HASH_Init
    .global __CC_CRYS_RND_GenerateVector
    
/*STB Cipher end*/
    .align 5

//#ifdef STB_CIPHER_DRIVER
__Cipher_Init:
    push {lr}
    swi SW_SYSCALL_CIPHER_INIT
    pop {lr}
    bx lr

__Cipher_DeInit:
    push {lr}
    swi SW_SYSCALL_CIPHER_DEINIT
    pop {lr}
    bx lr

__Cipher_CreateHandle:
    push {lr}
    swi SW_SYSCALL_CIPHER_CREATEHANDLE
    pop {lr}
    bx lr

__Cipher_DestroyHandle:
    push {lr}
    swi SW_SYSCALL_CIPHER_DESTROYHANDLE
    pop {lr}
    bx lr

__Cipher_ConfigHandle:
    push {lr}
    swi SW_SYSCALL_CIPHER_CONFIGHANDLE
    pop {lr}
    bx lr

__Cipher_GetHandleConfig:
    push {lr}
    swi SW_SYSCALL_CIPHER_GETHANDLECONFIG
    pop {lr}
    bx lr

__Cipher_Encrypt:
    push {lr}
    swi SW_SYSCALL_CIPHER_ENCRYPT
    pop {lr}
    bx lr

__Cipher_Decrypt:
    push {lr}
    swi SW_SYSCALL_CIPHER_DECRYPT
    pop {lr}
    bx lr

__Cipher_EncryptMulti:
    push {lr}
    swi SW_SYSCALL_CIPHER_ENCRYPTMULTI
    pop {lr}
    bx lr

__Cipher_DecryptMulti:
    push {lr}
    swi SW_SYSCALL_CIPHER_DECRYPTMULTI
    pop {lr}
    bx lr


__Cipher_HashInit:
    push {lr}
    swi SW_SYSCALL_CIPHER_HASHINIT
    pop {lr}
    bx lr
	
__Cipher_HashUpdate:
    push {lr}
    swi SW_SYSCALL_CIPHER_HASHUPDATE
    pop {lr}
    bx lr

__Cipher_HashFinal:
    push {lr}
    swi SW_SYSCALL_CIPHER_HASHFINAL
    pop {lr}
    bx lr

__Cipher_GetRandomNumber:
    push {lr}
    swi SW_SYSCALL_CIPHER_GETRANDOMNUMBER
    pop {lr}
    bx lr

__Cipher_EncryptHDCPKey:
    push {lr}
    swi SW_SYSCALL_CIPHER_ECNCRYPTHDCPKEY 
    pop {lr}
    bx lr

__Cipher_LoadHDCPKey:
    push {lr}
    swi SW_SYSCALL_CIPHER_LOADHDCPKEY 
    pop {lr}
    bx lr

__Cipher_GetIVOut:
    push {lr}
    swi SW_SYSCALL_CIPHER_GETIVOUT
    pop {lr}
    bx lr
	
__Cipher_Test:
    push {lr}
    swi SW_SYSCALL_CIPHER_TEST
    pop {lr}
    bx lr	


__VDEC_Suspend:
    push {lr}
    swi SW_SYSCALL_VDEC_SUSPEND
    pop {lr}
    bx lr 

__VDEC_Init:
    push {lr}
    swi SW_SYSCALL_VDEC_INIT
    pop {lr}
    bx lr

__VDEC_Resume:
    push {lr}
    swi SW_SYSCALL_VDEC_RESUME
    pop {lr}
    bx lr
    
__VFMW_CTRL_thread_sec:
    push {lr}
    swi SW_SYSCALL_VFMW_THREADPROC
    pop {lr}
    bx lr

__VDEC_Control:
    push {lr}
    swi SW_SYSCALL_VDEC_CONTROL
    pop {lr}
    bx lr

__VDEC_InitWithOperation:
    push {lr}
    swi SW_SYSCALL_VDEC_INITWITHOPERATION
    pop {lr}
    bx lr

__VCTRL_WriteProc:
    push {lr}
    swi SW_SYSCALL_VFMW_WRITEPROC
    pop {lr}
    bx lr

__VCTRL_ReadProc:
    push {lr}
    swi SW_SYSCALL_VFMW_READPROC
    pop {lr}
    bx lr

__VCTRL_SetDbgOption:
    push {lr}
    swi SW_SYSCALL_VCTRL_SETDBGOPTION
    pop {lr}
    bx lr

__VCTRL_GetChanImage:
    push {lr}
    swi SW_SYSCALL_VFMW_GETCHANIMAGE
    pop {lr}
    bx lr

__VCTRL_ReleaseChanImage:
    push {lr}
    swi SW_SYSCALL_VFMW_RELEASECHANIMAGE
    pop {lr}
    bx lr
     
__VDEC_Exit:
    push {lr}
    swi SW_SYSCALL_VDEC_EXIT
    pop {lr}
    bx lr
	
__MMZ_NEW:
    push {lr}
    swi SW_SYSCALL_MMZ_NEW
    pop {lr}
    bx lr

__MMZ_DEL:
    push {lr}
    swi SW_SYSCALL_MMZ_DEL
    pop {lr}
    bx lr

__MMZ_MALLOC:
    push {lr}
    swi SW_SYSCALL_MMZ_MALLOC
    pop {lr}
    bx lr

__MMZ_FREE:
    push {lr}
    swi SW_SYSCALL_MMZ_FREE
    pop {lr}
    bx lr

__MMZ_MAP:
    push {lr}
    swi SW_SYSCALL_MMZ_MAP
    pop {lr}
    bx lr

__MMZ_UNMAP:
    push {lr}
    swi SW_SYSCALL_MMZ_UNMAP
    pop {lr}
    bx lr

__MMZ_FLUSH:
    push {lr}
    swi SW_SYSCALL_MMZ_FLUSH
    pop {lr}
    bx lr

__mem_copy:
    push {lr}
    swi SW_SYSCALL_MEM_COPY
    pop {lr}
    bx lr

__TEE_IsSecMem:
    push {lr}
    swi SW_SYSCALL_TEE_ISSECMEM
    pop {lr}
    bx lr

__TEE_IsNonSecMem:
    push {lr}
    swi SW_SYSCALL_TEE_ISNONSECMEM
    pop {lr}
    bx lr

__call_debug:
    push {lr}
    swi SW_SYSCALL_DEBUG
    pop {lr}
    bx lr

__CC_CRYS_HMAC_Init:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_HMAC_INIT
    pop {lr}
    bx lr
__CC_CRYS_HMAC_Update:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_HMAC_UPDATE
    pop {lr}
    bx lr
__CC_CRYS_HMAC_Finish:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_HMAC_FINISH
    pop {lr}
    bx lr
__CC_CRYS_AES_Init:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_AES_INIT
    pop {lr}
    bx lr
__CC_CRYS_AES_Block:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_AES_BLOCK
    pop {lr}
    bx lr
__CC_CRYS_AES_Finish:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_AES_FINISH
    pop {lr}
    bx lr    
__CC__DX_RSA_Sign:
    push {lr}
    swi SW_SYSCALL_CC__DX_RSA_SIGN
    pop {lr}
    bx lr
__CC__DX_RSA_Verify:
    push {lr}
    swi SW_SYSCALL_CC__DX_RSA_VERIFY
    pop {lr}
    bx lr
__CC__DX_RSA_SCHEMES_Encrypt:
    push {lr}
    swi SW_SYSCALL_CC__DX_RSA_SCHEMES_ENCRYPT
    pop {lr}
    bx lr
__CC__DX_RSA_SCHEMES_Decrypt:
    push {lr}
    swi SW_SYSCALL_CC__DX_RSA_SCHEMES_DECRYPT
    pop {lr}
    bx lr
__CC_CRYS_RSA_PRIM_Encrypt:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_PRIM_ENCRYPT
    pop {lr}
    bx lr

__CC_CRYS_RSA_PRIM_Decrypt:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_PRIM_DECRYPT
    pop {lr}
    bx lr
__CC_CRYS_RSA_KG_GenerateKeyPairCRT:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_KG_GENERATEKEYPAIRCRT
    pop {lr}
    bx lr

__CC_CRYS_RSA_KG_GenerateKeyPair:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_KG_GENERATEKEYPAIR
    pop {lr}
    bx lr

__CC_CRYS_RSA_Build_PubKey:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_BUILD_PUBKEY
    pop {lr}
    bx lr

__CC_CRYS_RSA_Build_PrivKey:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_BUILD_PRIVKEY
    pop {lr}
    bx lr

__CC_CRYS_RSA_Build_PrivKeyCRT:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RSA_BUILD_PRIVKEYCRT
    pop {lr}
    bx lr
__CC_CRYS_RND_GenerateVector:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_RND_GENERATEVECTOR
    pop {lr}
    bx lr
__CC_CRYS_DES_Free:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_DES_FREE
    pop {lr}
    bx lr
__CC_CRYS_HASH_Init:
    push {lr}
    swi SW_SYSCALL_CC_CRYS_HASH_INIT
    pop {lr}
    bx lr

//#endif

