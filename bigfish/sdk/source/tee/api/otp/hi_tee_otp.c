/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : hi_tee_otp.c
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/

#include "hi_tee_otp.h"
#include "sre_syscalls_ext.h"
#include "hi_type.h"
#include "tee_log.h"

#define HI_ERR_OTP(fmt...)	uart_printf_func(fmt)
#define HI_INFO_OTP(fmt...)	uart_printf_func(fmt)

HI_S32 HI_TEE_OTP_Init(HI_VOID)
{
	return __OTP_Init();
}

HI_S32 HI_TEE_OTP_DeInit(HI_VOID)
{
	return __OTP_DeInit();
}

HI_S32 HI_TEE_OTP_Reset(HI_VOID)
{
	return __OTP_Reset();
}

HI_S32 HI_TEE_OTP_GetChipID(HI_U8 *pu8ChipID)
{
	return __OTP_GetChipID(pu8ChipID);
}

HI_S32 HI_TEE_OTP_ReadWord(HI_U32 Addr, HI_U32 *pu32Value)
{
	return __OTP_ReadWord(Addr, pu32Value);
}

HI_S32 HI_TEE_OTP_ReadByte(HI_U32 Addr, HI_U8 *pu8Value)
{
	return __OTP_ReadByte(Addr, pu8Value);
}

HI_S32 HI_TEE_OTP_WriteWord(HI_U32 Addr, HI_U32 u32Value)
{
	return __OTP_WriteWord(Addr, u32Value);
}

HI_S32 HI_TEE_OTP_WriteByte(HI_U32 Addr, HI_U8 u8Value)
{
	return __OTP_WriteByte(Addr, u8Value);
}

#if 0
HI_S32 HI_TEE_OTP_TEST(HI_TEE_OTP_OPERATE_MODE_E OTP_Mode, HI_U32 Addr, HI_U32 *pValue, HI_U32 count)
{
	HI_S32 ret = HI_SUCCESS;
	HI_U32 u32ChipID = 0xabcd;
	HI_U8 u8Byte = 0x55;
	HI_U32 u32Word = 0;
    HI_U32 i = 0;

	if ( pValue == NULL )
	{
		HI_ERR_OTP("Invalid param, NULL!\n");
		return HI_FAILURE;
	}

	if ( OTP_Mode >= OTP_MODE_INVALID )
	{
		HI_ERR_OTP("Invalid otp mode!\n");
		return HI_FAILURE;
	}

	(HI_VOID)HI_TEE_OTP_Init();
#if 0
	if ( HI_SUCCESS != ret )
	{
		HI_ERR_OTP("HI_TEE_OTP_Init Failed!\n");
		return HI_FAILURE;
	}
#endif
	
	switch ( OTP_Mode )
	{
	    case OTP_READ_BYTE:
	    {
            HI_U8 * pu8Value = (HI_U8 *)pValue;
			HI_INFO_OTP("RRBB\n");
            for(i=0; i<count; i++ )
            {
    			ret = HI_TEE_OTP_ReadByte(Addr+i, pu8Value+i);
    			if ( HI_SUCCESS != ret)
    			{
    			    return HI_FAILURE;
    			}
            }
			HI_INFO_OTP("RR%xBB\n", *pValue);
			break;
		}
	    case OTP_READ_WORD:
	    {
			HI_INFO_OTP("RRWW\n");
            for(i=0; i<count; i++ )
            {
    			ret = HI_TEE_OTP_ReadWord(Addr+i*4, pValue+i);
    			if ( HI_SUCCESS != ret)
    			{
    			    return HI_FAILURE;
    			}
            }
			HI_INFO_OTP("RR%xWW\n", *pValue);
			break;
		}
	    case OTP_WRITE_BYTE:
	    {
            HI_U8 * pu8Value = (HI_U8 *)pValue;
			HI_INFO_OTP("WWBB\n");
            for(i=0; i<count; i++)
            {
    			ret = HI_TEE_OTP_WriteByte(Addr+i, pu8Value[i]);
    			if ( HI_SUCCESS != ret)
    			{
    			    return HI_FAILURE;
    			}
            }
			break;
		}
	    case OTP_WRITE_WORD:
	    {
			HI_INFO_OTP("WWWW\n");
            for(i=0; i<count; i++)
            {
    			ret = HI_TEE_OTP_WriteWord(Addr+i*4, pValue[i]);
    			if ( HI_SUCCESS != ret)
    			{
    			    return HI_FAILURE;
    			}
            }
			break;
		}
		case OTP_GET_CHIPID:
	    {
			HI_INFO_OTP("GGCHIPID\n");
			ret = HI_TEE_OTP_GetChipID(pValue);
			if ( HI_SUCCESS != ret)
			{
			    return HI_FAILURE;
			}
			HI_INFO_OTP("GG%xCHIPID\n", *pValue);
			break;
		}
        case OTP_RESET:
        {
			HI_INFO_OTP("OTPRESET\n");
            ret = HI_TEE_OTP_Reset();
            break;
        }
	    default:
	    {
			HI_ERR_OTP("Not supported\n");
			break;
		}
	}


	(HI_VOID)HI_TEE_OTP_DeInit();

	HI_INFO_OTP("HI_TEE_OTP_TEST success!\n");
	return ret;
}
#endif

