#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"
#include "tz_unf_cipher.h"
#include "hi_tz_common.h"
#include "hi_drv_cipher.h"

TEE_Result TA_CreateEntryPoint(void)
{
    TEE_Result ret=TEE_SUCCESS;

 //   ta_debug("task3 - TA_CreateEntryPoint test\n");
    return ret;
}

TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4], void** sessionContext)
{
    TEE_Result ret=TEE_SUCCESS;
    
 //   ta_debug("--test\n");

    return ret;
}

TEE_Result TA_InvokeCommandEntryPoint(void* session_context, uint32_t cmd_id, uint32_t paramTypes, TEE_Param params[4])
{
    HI_S32 ret = TEE_SUCCESS;

//    ta_debug("TA invoke cmd = %d!\n", cmd_id);
	switch(cmd_id)
	{
#ifdef HI_CIPHER_TEST
		case CMD_TZ_CIPHER_INIT:
		{
			ret = TZ_UNF_CIPHER_Init();
			break;
		}
		case CMD_TZ_CIPHER_DEINIT:
		{
			TZ_UNF_CIPHER_DeInit();
			break;
		}
		case CMD_TZ_CIPHER_ENCRYPT:
		{
			ret = TZ_UNF_CIPHER_Encrypt(params[0].value.a, params[0].value.b, params[1].value.a, params[1].value.b);
			break;
		}
		case CMD_TZ_CIPHER_ENCRYPTMULTI:
		{
			ret = TZ_UNF_CIPHER_EncryptMulti(params[0].value.a, params[1].memref.buffer, params[2].value.a);
			break;
		}
		case CMD_TZ_CIPHER_DECRYPT:
		{
			ret = TZ_UNF_CIPHER_Decrypt(params[0].value.a, params[0].value.b, params[1].value.a, params[1].value.b);
			break;
		}
		case CMD_TZ_CIPHER_DECRYPTMULTI:
		{
			ret = TZ_UNF_CIPHER_DecryptMulti(params[0].value.a, params[1].memref.buffer, params[2].value.a);
			break;
		}
		case CMD_TZ_CIPHER_CONFIGHANDLE:
		{
			ret = TZ_UNF_CIPHER_ConfigHandle(params[0].value.a, params[1].memref.buffer);
			break;
		}
		case CMD_TZ_CIPHER_CREATEHANDLE:
		{
			ret = TZ_UNF_CIPHER_CreateHandle(&params[0].value.a, params[1].memref.buffer);
            break;
		}
		case CMD_TZ_CIPHER_DESTROYHANDLE:
		{
			ret = TZ_UNF_CIPHER_DestroyHandle(params[0].value.a);
			break;
		}
		case CMD_TZ_CIPHER_GETHANDLECONFIG:
		{
			ret = TZ_UNF_CIPHER_GetHandleConfig(params[0].value.a, params[1].memref.buffer);
			break;
		}
		case CMD_TZ_CIPHER_GETRANDOMNUMBER:
		{
			ret = TZ_UNF_CIPHER_GetRandomNumber(&params[0].value.a);
			break;
		}
		case CMD_TZ_CIPHER_ENCRYPTHDCPKEY:
		{
			ret = TZ_UNF_CIPHER_EncryptHdcpKey(params[0].memref.buffer);
		    break;
		}
		case CMD_TZ_CIPHER_LOADHDCPKEY:
		{
			ret = TZ_UNF_CIPHER_LoadHdcpKey(params[0].memref.buffer);
			break;
		}
        case CMD_TZ_CIPHER_HASHINIT:
        {
            HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr = (HI_UNF_CIPHER_HASH_ATTS_S *)params[0].memref.buffer;
            if (pstHashAttr->pu8HMACKey != HI_NULL)
            {
                pstHashAttr->pu8HMACKey = params[2].memref.buffer;
                pstHashAttr->u32HMACKeyLen = params[2].memref.size;
            }
            ret = TZ_UNF_CIPHER_HashInit(pstHashAttr, &params[1].value.a);
			break;
		}  
        case CMD_TZ_CIPHER_HASHUPDATE:
        { 
			ret = TZ_UNF_CIPHER_HashUpdate(params[0].value.a, params[1].memref.buffer, params[1].memref.size);
            break;
		}
        case CMD_TZ_CIPHER_HASHFINAL:
        {
			ret = TZ_UNF_CIPHER_HashFinal(params[0].value.a, params[1].memref.buffer);
			break;
		}
        case CMD_TZ_TEST:
        {
			ret = TZ_UNF_CIPHER_Test(params[0].value.a, params[1].value.a, params[2].value.a, params[2].value.b);
			break;
		}     
#endif
    default:
        {
            ta_debug("Invalid TA invoke command, cmd = %d!\n", cmd_id);
            ret = HI_FAILURE;
            break;
        }
    }

    if(HI_SUCCESS != ret)
    {
        ta_debug("TA Invoke command falied, ret = 0x%x!\n", ret);
        return TEE_FAIL;
    }
    else
    {
#ifdef HI_CIPHER_TEST
        HI_U32 i;
        HI_UNF_CIPHER_DATA_S* pstCIData;
        OTP_HDCP_KEY_TRANSFER_S *pstHdcpKeyTransfer;
        HI_UNF_CIPHER_HASH_ATTS_S *pstHashAttr;
        
        switch(cmd_id)
	    {
    		case CMD_TZ_CIPHER_ENCRYPT:
            {
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, params[0].value.b, params[1].value.b);
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, params[1].value.a, params[1].value.b);
                break;
            }
    		case CMD_TZ_CIPHER_ENCRYPTMULTI:
    		{
                pstCIData = (HI_UNF_CIPHER_DATA_S*)params[1].memref.buffer;
                for(i=0; i<params[2].value.a; i++)
                {
                    TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, pstCIData->u32DestPhyAddr, pstCIData->u32ByteLength);
                    pstCIData++;
                }
    			break;
    		}
    		case CMD_TZ_CIPHER_DECRYPT:
            {
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, params[1].value.a, params[1].value.b);
                break;
            }
    		case CMD_TZ_CIPHER_DECRYPTMULTI:
    		{
                pstCIData = (HI_UNF_CIPHER_DATA_S*)params[1].memref.buffer;
                for(i=0; i<params[2].value.a; i++)
                {
                    TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, pstCIData->u32DestPhyAddr, pstCIData->u32ByteLength);
                    pstCIData++;
                }
    			break;
    		}
    		case CMD_TZ_CIPHER_ENCRYPTHDCPKEY:
            {
                pstHdcpKeyTransfer = (OTP_HDCP_KEY_TRANSFER_S *)params[0].memref.buffer;
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, (HI_U32)pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey, 332);
                break;
            }
    		case CMD_TZ_CIPHER_LOADHDCPKEY:
            {
                pstHdcpKeyTransfer = (OTP_HDCP_KEY_TRANSFER_S *)params[0].memref.buffer;
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, (HI_U32)pstHdcpKeyTransfer->u8FlashEncryptedHdcpKey, 332);
                break;
            } 
            /*
            case CMD_TZ_CIPHER_GETRANDOMNUMBER:
            {
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_PHY, HI_NULL, params[1].value.a, params[1].value.b);
                break;
            }
            case CMD_TZ_CIPHER_HASHUPDATE:
            {
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_VIA, HI_NULL, (HI_U32)params[1].memref.buffer, params[1].memref.size);
                break;
            } 
            case CMD_TZ_CIPHER_HASHFINAL:
            {
                TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_VIA, HI_NULL, (HI_U32)params[1].memref.buffer, params[1].memref.size);
                break;
            }
            case CMD_TZ_CIPHER_HASHINIT:
            {
                pstHashAttr = (HI_UNF_CIPHER_HASH_ATTS_S *)params[0].memref.buffer;
                if (pstHashAttr->pu8HMACKey != HI_NULL)
                {
                    TZ_UNF_CIPHER_Test(CIPHER_TEST_PRINT_VIA, HI_NULL, pstHashAttr->pu8HMACKey, pstHashAttr->u32HMACKeyLen);
                    break;

                }
    			break;
    		}
    		*/
        default:
            {
                break;
            }
        }
#endif
    }

//    ta_debug("TA Invoke ret = 0x%x!\n", ret);

    return TEE_SUCCESS;
}

void TA_CloseSessionEntryPoint(void* session_context)
{
    //ta_debug("test\n");
}

void TA_DestroyEntryPoint(void)
{
    //ta_debug("test\n");
}

