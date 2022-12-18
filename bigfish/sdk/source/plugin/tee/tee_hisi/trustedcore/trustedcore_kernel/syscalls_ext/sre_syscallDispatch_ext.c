#include "drv_cipher_intf.h"
#include <hi_type.h>
#include "vfmw.h"
#include <drv_cipher_define.h>

#include <sre_syscalls_ext.h>
#include <sre_syscalls_id_ext.h>

#ifdef STB_CIPHER_DRIVER
#include "crys_hmac.h"
#include "crys_aes.h"
#include "crys_rsa_types.h"
#include "crys_des.h"
#endif
void swi_handler_ext(int swi_id, stSWITempRegs_ext *regs)
{

    UINT32 uwRet = 0;
    switch(swi_id)
    {
        case SW_SYSCALL_CIPHER_INIT:
            Cipher_Init();
            //regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_DEINIT:
            Cipher_DeInit();
            //regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_CREATEHANDLE:
            uwRet = Cipher_CreateHandle((HI_HANDLE*)regs->regs[0], (const HI_UNF_CIPHER_ATTS_S *)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_DESTROYHANDLE:
            uwRet = Cipher_DestroyHandle((HI_HANDLE)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_CONFIGHANDLE:
            uwRet = Cipher_ConfigHandle((HI_HANDLE)regs->regs[0], (HI_UNF_CIPHER_CTRL_S*)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_GETHANDLECONFIG:
            uwRet = Cipher_GetHandleConfig((HI_HANDLE)regs->regs[0], (HI_UNF_CIPHER_CTRL_S*)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_ENCRYPT:
            uwRet = Cipher_Encrypt((HI_HANDLE)regs->regs[0], (HI_U32)regs->regs[1], (HI_U32)regs->regs[2], (HI_U32)regs->regs[3]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_DECRYPT:
            uwRet = Cipher_Decrypt((HI_HANDLE)regs->regs[0], (HI_U32)regs->regs[1], (HI_U32)regs->regs[2], (HI_U32)regs->regs[3]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_ENCRYPTMULTI:
            uwRet = Cipher_EncryptMulti((HI_HANDLE)regs->regs[0], (HI_UNF_CIPHER_DATA_S *)regs->regs[1], (HI_U32)regs->regs[2]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_DECRYPTMULTI:
            uwRet = Cipher_DecryptMulti((HI_HANDLE)regs->regs[0], (HI_UNF_CIPHER_DATA_S *)regs->regs[1], (HI_U32)regs->regs[2]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_HASHINIT:
            uwRet = Cipher_HashInit((HI_UNF_CIPHER_HASH_ATTS_S *)regs->regs[0], (HI_HANDLE *)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_HASHUPDATE:
            uwRet = Cipher_HashUpdate((HI_HANDLE)regs->regs[0], (HI_U8 *)regs->regs[1], (HI_U32)regs->regs[2]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_HASHFINAL:
            uwRet = Cipher_HashFinal((HI_HANDLE)regs->regs[0], (HI_U8 *)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CIPHER_GETRANDOMNUMBER:
            uwRet = Cipher_GetRandomNumber((HI_U32 *)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
		
	case SW_SYSCALL_CIPHER_ECNCRYPTHDCPKEY:
			uwRet = Cipher_EncryptHDCPKey((OTP_HDCP_KEY_TRANSFER_S *)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
		
	case SW_SYSCALL_CIPHER_LOADHDCPKEY:
			uwRet = Cipher_LoadHdcpKey((HI_DRV_CIPHER_FLASH_ENCRYPT_HDCPKEY_S *)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
		
        case SW_SYSCALL_CIPHER_GETIVOUT:
            uwRet = Cipher_GetIVOut((HI_HANDLE)regs->regs[0], (HI_U8 *)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CIPHER_TEST:
            uwRet = Cipher_Test(regs->regs[0], &regs->regs[1], regs->regs[2], regs->regs[3]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VDEC_SUSPEND:
            uwRet = SEC_VDEC_Suspend();
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VDEC_INIT:
            uwRet = SEC_VDEC_Init(regs->regs[0]);
                regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VDEC_RESUME:
            uwRet = SEC_VDEC_Resume();
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VFMW_THREADPROC:
            uwRet = SEC_VCTRL_RunProcess();
			//uart_printf_func("uwRet = %d\n", uwRet);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VDEC_CONTROL:
            uwRet = SEC_VDEC_Control((HI_S32)regs->regs[0], regs->regs[1], regs->regs[2]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VDEC_INITWITHOPERATION:
            uwRet = SEC_VDEC_InitWithOperation(regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VFMW_WRITEPROC:
            uwRet = SEC_VCTRL_WriteProc(regs->regs[0], (HI_S32)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VFMW_READPROC:
            uwRet = SEC_VCTRL_ReadProc(regs->regs[0], (HI_S32)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VCTRL_SETDBGOPTION:
            uwRet = SEC_VCTRL_SetDbgOption(regs->regs[0], regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VFMW_GETCHANIMAGE:
            uwRet = SEC_VCTRL_GetChanImage((HI_S32)regs->regs[0], regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VFMW_RELEASECHANIMAGE:
            uwRet = SEC_VCTRL_ReleaseChanImage((HI_S32)regs->regs[0], regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_VDEC_EXIT:
            uwRet = SEC_VDEC_Exit();
            regs->regs[0] = uwRet;
            break;			
        case SW_SYSCALL_MMZ_NEW:
            MMZ_NEW((HI_MMZ_BUF_S *)regs->regs[0], (char *)regs->regs[1], (char *)regs->regs[2]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MMZ_DEL:
            MMZ_DEL((unsigned long)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MMZ_MALLOC:
            uwRet = MMZ_MALLOC((HI_MMZ_BUF_S *)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MMZ_FREE:
            uwRet = MMZ_FREE((HI_MMZ_BUF_S *)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MMZ_MAP:
            uwRet = MMZ_MAP((unsigned long)regs->regs[0], (unsigned long)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MMZ_UNMAP:
            uwRet = MMZ_UNMAP((unsigned long)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MMZ_FLUSH:
            uwRet = MMZ_FLUSH((unsigned long)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_MEM_COPY:
//            uart_printf_func("parm1:%x,parm2:%x,parm3:%x\n", (unsigned long)regs->regs[0], (unsigned long)regs->regs[1], (int)regs->regs[2]);
            uwRet = mem_copy((unsigned long)regs->regs[0], (unsigned long)regs->regs[1], (int)regs->regs[2]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_TEE_ISSECMEM:
            uwRet = TEE_IsSecMem((unsigned long)regs->regs[0], (unsigned long)regs->regs[1]);
            regs->regs[0] = (unsigned long)uwRet;
            break;
        case SW_SYSCALL_TEE_ISNONSECMEM:
            uwRet = TEE_IsNonSecMem((unsigned long)regs->regs[0], (unsigned long)regs->regs[1]);
            regs->regs[0] = (unsigned long)uwRet;
            break;
	case SW_SYSCALL_DEBUG:
            uwRet = call_debug((unsigned long)regs->regs[0], (unsigned long)regs->regs[1], (unsigned long)regs->regs[2], (unsigned long)regs->regs[3]);
            regs->regs[0] = (unsigned long)uwRet;
            break;
        case SW_SYSCALL_CC_CRYS_HMAC_INIT:
            uwRet = CRYS_HMAC_Init(
                (CRYS_HMACUserContext_t *)regs->regs[0],
                (CRYS_HASH_OperationMode_t)regs->regs[1],
                (DxUint8_t *)regs->regs[2],
                (DxUint16_t)regs->regs[3]);
            regs->regs[0] = uwRet;
            break;
		 case SW_SYSCALL_CC_CRYS_HMAC_UPDATE:
            uwRet = CRYS_HMAC_Update(
                (CRYS_HMACUserContext_t *)regs->regs[0],
                (DxUint8_t *)regs->regs[1],
                (DxUint16_t)regs->regs[2]);
            regs->regs[0] = uwRet;
            break;
			
		 case SW_SYSCALL_CC_CRYS_HMAC_FINISH:
            uwRet = CRYS_HMAC_Finish(
                (CRYS_HMACUserContext_t *)regs->regs[0],
                (DxUint32_t*)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
			
	        case SW_SYSCALL_CC_CRYS_AES_INIT:
            uwRet = CRYS_AES_Init(
                (CRYS_AESUserContext_t *)regs->regs[0],
                (DxUint8_t*)regs->regs[1],
                (DxUint8_t*)regs->regs[2],
                (CRYS_AES_KeySize_t)regs->regs[3],
                (CRYS_AES_EncryptMode_t)regs->args[0],
                (CRYS_AES_OperationMode_t)regs->args[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_AES_BLOCK:
            uwRet = CRYS_AES_Block(
                (CRYS_AESUserContext_t *)regs->regs[0],
                (DxUint8_t *)regs->regs[1],
                (DxUint32_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_AES_FINISH:
            uwRet = CRYS_AES_Finish(
                (CRYS_AESUserContext_t *)regs->regs[0],
                (DxUint8_t *)regs->regs[1],
                (DxUint32_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3]);
            regs->regs[0] = uwRet;
            break;
		case SW_SYSCALL_CC__DX_RSA_SCHEMES_ENCRYPT:
            uwRet = _DX_RSA_SCHEMES_Encrypt(
                (CRYS_RSAUserPubKey_t *)regs->regs[0],
                (CRYS_RSAPrimeData_t *)regs->regs[1],
                (CRYS_RSA_HASH_OpMode_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3],
                (DxUint16_t)regs->args[0],
                (CRYS_PKCS1_MGF_t)regs->args[1],
                (DxUint8_t *)regs->args[2],
                (DxUint16_t)regs->args[3],
                (DxUint8_t *)regs->args[4],
                (CRYS_PKCS1_version)regs->args[5]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CC__DX_RSA_SCHEMES_DECRYPT:
            uwRet = _DX_RSA_SCHEMES_Decrypt(
                (CRYS_RSAUserPrivKey_t *)regs->regs[0],
                (CRYS_RSAPrimeData_t *)regs->regs[1],
                (CRYS_RSA_HASH_OpMode_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3],
                (DxUint16_t)regs->args[0],
                (CRYS_PKCS1_MGF_t)regs->args[1],
                (DxUint8_t *)regs->args[2],
                (DxUint16_t)regs->args[3],
                (DxUint8_t *)regs->args[4],
                (DxUint16_t *)regs->args[5],
                (CRYS_PKCS1_version)regs->args[6]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CC_CRYS_RSA_PRIM_ENCRYPT:
            uwRet = CRYS_RSA_PRIM_Encrypt(
                (CRYS_RSAUserPubKey_t *)regs->regs[0],
                (CRYS_RSAPrimeData_t *)regs->regs[1],
                (DxUint8_t *)regs->regs[2],
                (DxUint16_t)regs->regs[3],
                (DxUint8_t *)regs->args[0]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_RSA_PRIM_DECRYPT:
            uwRet = CRYS_RSA_PRIM_Decrypt(
                (CRYS_RSAUserPrivKey_t *)regs->regs[0],
                (CRYS_RSAPrimeData_t *)regs->regs[1],
                (DxUint8_t *)regs->regs[2],
                (DxUint16_t)regs->regs[3],
                (DxUint8_t *)regs->args[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CC__DX_RSA_SIGN:
            uwRet = _DX_RSA_Sign(
                (CRYS_RSAPrivUserContext_t *)regs->regs[0],
                (CRYS_RSAUserPrivKey_t *)regs->regs[1],
                (CRYS_RSA_HASH_OpMode_t)regs->regs[2],
                (CRYS_PKCS1_MGF_t)regs->regs[3],
                (DxUint16_t)regs->args[0],
                (DxUint8_t *)regs->args[1],
                (DxUint32_t)regs->args[2],
                (DxUint8_t *)regs->args[3],
                (DxUint16_t *)regs->args[4],
                (CRYS_PKCS1_version)regs->args[5]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC__DX_RSA_VERIFY:
            uwRet = _DX_RSA_Verify(
                (CRYS_RSAPubUserContext_t *)regs->regs[0],
                (CRYS_RSAUserPubKey_t *)regs->regs[1],
                (CRYS_RSA_HASH_OpMode_t)regs->regs[2],
                (CRYS_PKCS1_MGF_t)regs->regs[3],
                (DxUint16_t)regs->args[0],
                (DxUint8_t *)regs->args[1],
                (DxUint32_t)regs->args[2],
                (DxUint8_t *)regs->args[3],
                (CRYS_PKCS1_version)regs->args[4]);
            regs->regs[0] = uwRet;
            break;
		        case SW_SYSCALL_CC_CRYS_RSA_KG_GENERATEKEYPAIRCRT:
            uwRet = CRYS_RSA_KG_GenerateKeyPairCRT(
                (DxUint8_t *)regs->regs[0],
                (DxUint16_t)regs->regs[1],
                (DxUint32_t)regs->regs[2],
                (CRYS_RSAUserPrivKey_t *)regs->regs[3],
                (CRYS_RSAUserPubKey_t *)regs->args[0],
                (CRYS_RSAKGData_t *)regs->args[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_RSA_KG_GENERATEKEYPAIR:
            uwRet = CRYS_RSA_KG_GenerateKeyPair(
                (DxUint8_t *)regs->regs[0],
                (DxUint16_t)regs->regs[1],
                (DxUint32_t)regs->regs[2],
                (CRYS_RSAUserPrivKey_t *)regs->regs[3],
                (CRYS_RSAUserPubKey_t *)regs->args[0],
                (CRYS_RSAKGData_t *)regs->args[1]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_RSA_BUILD_PUBKEY:
            uwRet = CRYS_RSA_Build_PubKey(
                (CRYS_RSAUserPubKey_t *)regs->regs[0],
                (DxUint8_t *)regs->regs[1],
                (DxUint16_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3],
                (DxUint16_t)regs->args[0]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_RSA_BUILD_PRIVKEY:
            uwRet = CRYS_RSA_Build_PrivKey(
                (CRYS_RSAUserPrivKey_t *)regs->regs[0],
                (DxUint8_t *)regs->regs[1],
                (DxUint16_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3],
                (DxUint16_t)regs->args[0],
                (DxUint8_t *)regs->args[1],
                (DxUint16_t)regs->args[2]);
            regs->regs[0] = uwRet;
            break;

        case SW_SYSCALL_CC_CRYS_RSA_BUILD_PRIVKEYCRT:
            uwRet = CRYS_RSA_Build_PrivKeyCRT(
                (CRYS_RSAUserPrivKey_t *)regs->regs[0],
                (DxUint8_t *)regs->regs[1],
                (DxUint16_t)regs->regs[2],
                (DxUint8_t *)regs->regs[3],
                (DxUint16_t)regs->args[0],
                (DxUint8_t *)regs->args[1],
                (DxUint16_t)regs->args[2],
                (DxUint8_t *)regs->args[3],
                (DxUint16_t)regs->args[4],
                (DxUint8_t *)regs->args[5],
                (DxUint16_t)regs->args[6]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CC_CRYS_HASH_INIT:
            uwRet = CRYS_HASH_Init(
                (CRYS_HASHUserContext_t *)regs->regs[0],
                (CRYS_HASH_OperationMode_t)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CC_CRYS_DES_FREE:
            uwRet = CRYS_DES_Free(
                (CRYS_DESUserContext_t *)regs->regs[0]);
            regs->regs[0] = uwRet;
            break;
        case SW_SYSCALL_CC_CRYS_RND_GENERATEVECTOR:
            uwRet = CRYS_RND_GenerateVector(
                (DxUint16_t)regs->regs[0],
                (DxUint8_t *)regs->regs[1]);
            regs->regs[0] = uwRet;
            break;
		default:
            break;
    }

}
