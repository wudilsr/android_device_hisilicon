#include "hi_loader_info.h"
#include "loaderdb_info.h"
#include "hi_flash.h"
#include "ca_ssd.h"
#include "hi_error_mpi.h"

/* for avoid conflict with libhiloader.a & so */
/* bootloader has no advca support,just apploader support advca  */
#if defined(HI_LOADER_BOOTLOADER)
#include "hi_drv_pdm.h"
#include "upgrd_common.h"
#define LOADER_GetDeviceInfo HI_DRV_PDM_GetDeviceInfo
#define LOADER_GetDeviceSN HI_DRV_PDM_GetDeviceInfo
#elif defined(HI_LOADER_APPLOADER) && defined(HI_ADVCA_TYPE_NAGRA)
#include "hi_drv_pdm.h"
#include "hi_unf_pdm.h"
#include "upgrd_common.h"
#define LOADER_GetDeviceInfo  GetCADeviceInfo
#define LOADER_GetDeviceSN HI_UNF_PDM_GetDeviceInfo
#elif defined(HI_LOADER_APPLOADER) && !defined(HI_ADVCA_SUPPORT)
#include "hi_unf_pdm.h"
#include "upgrd_common.h"
#define LOADER_GetDeviceInfo  HI_UNF_PDM_GetDeviceInfo
#define LOADER_GetDeviceSN HI_UNF_PDM_GetDeviceInfo
#elif defined(HI_LOADER_APPLOADER) && defined(HI_ADVCA_TYPE_VERIMATRIX)
#include "hi_unf_pdm.h"
#include "upgrd_common.h"
#define LOADER_GetDeviceInfo  HI_UNF_PDM_GetDeviceInfo
#define LOADER_GetDeviceSN HI_UNF_PDM_GetDeviceInfo


#else /* libhiloader.a &so */
#include <string.h>
#include <stdlib.h>
#include "hi_unf_pdm.h"
#define  LOADER_strtoul strtoul
#define LOADER_GetDeviceInfo  HI_UNF_PDM_GetDeviceInfo
#define LOADER_GetDeviceSN HI_UNF_PDM_GetDeviceInfo

#undef HI_FATAL_LOADER 
#undef HI_ERR_LOADER        
#undef HI_WARN_LOADER     
#undef HI_INFO_LOADER
#undef HI_DBG_LOADER  

 /* for debug libhiloader.a */
 #define HI_ERR_LOADER(arg...) HI_PRINT(arg)
 #define HI_DBG_LOADER(arg...) 
#endif

static const HI_CHAR s_szLoaderVersion[] __attribute__((used)) = "SDK_VERSION:["\
                            MKMARCOTOSTR(SDK_VERSION)"] Build Time:["\
                            __DATE__", "__TIME__"]";

HI_S32 HI_LOADER_ReadParameters(HI_LOADER_PARAMETER_S* info)
{
	UPGRD_LOADER_INFO_S stUpgrdLoaderInfo;

	if (HI_NULL == info)
	{
		HI_ERR_LOADER("Invaled params.");
		return HI_FAILURE;
	}

	if (HI_SUCCESS != Upgrd_ReadLoaderDBInfo(&stUpgrdLoaderInfo))
	{
		HI_ERR_LOADER("Failed to read loaderdb info.\n");
		return HI_FAILURE;
	}

	memcpy(info, &stUpgrdLoaderInfo.stLoaderParam, sizeof(HI_LOADER_PARAMETER_S));
	return HI_SUCCESS;
}

HI_S32 HI_LOADER_WriteParameters(HI_LOADER_PARAMETER_S* info)
{
	UPGRD_LOADER_INFO_S stUpgrdLoaderInfo;

	if (HI_NULL == info)
	{
		HI_ERR_LOADER("Invaled params.");
		return HI_FAILURE;
	}

	if (HI_SUCCESS != Upgrd_ReadLoaderDBInfo(&stUpgrdLoaderInfo))
	{
		HI_ERR_LOADER("Failed to read loaderdb info.");
		return HI_FAILURE;
	}

	if (HI_LOADER_TYPE_BUTT > info->eUpdateType)
	{
		stUpgrdLoaderInfo.stTagPara.bTagNeedUpgrd = HI_TRUE;
		stUpgrdLoaderInfo.stTagPara.bTagManuForceUpgrd = HI_FALSE;
	}
	else
	{
		info->eUpdateType = HI_LOADER_TYPE_BUTT;
		stUpgrdLoaderInfo.stTagPara.bTagNeedUpgrd = HI_FALSE;
		stUpgrdLoaderInfo.stTagPara.bTagManuForceUpgrd = HI_FALSE;
	}

	/*clear loader history data*/
	stUpgrdLoaderInfo.stLoaderPrivate.u32FailedCnt = 0;
	stUpgrdLoaderInfo.stLoaderPrivate.bTagDestroy = HI_FALSE;

	memcpy(&stUpgrdLoaderInfo.stLoaderParam, info, sizeof(HI_LOADER_PARAMETER_S));

	if (HI_SUCCESS != Upgrd_WriteLoaderDBInfo(&stUpgrdLoaderInfo))
	{
		HI_ERR_LOADER("Failed to write loaderdb info.");
		return HI_FAILURE;
	}

	return HI_SUCCESS;
}


#if defined(HI_ADVCA_TYPE_NAGRA) && !defined(HI_LOADER_BOOTLOADER)
#include "hi_drv_pdm.h"
#include "hi_unf_pdm.h"
#define LOADER_GetDeviceInfo  GetCADeviceInfo
#define LOADER_GetDeviceSN HI_UNF_PDM_GetDeviceInfo
static HI_S32 VerifyCADeviceInfo(HI_CHAR * pDevInfoBuf, HI_U32 u32DevInfoBufLen, HI_U32 *pu32ValidDevInfoLen)
{
    HI_U32 u32PosIndex = 0;
    HI_S32 s32Ret = HI_FAILURE;
    
    /* locate magic num */
    while(u32PosIndex < u32DevInfoBufLen)
    {
        HI_CHAR *pCurPos = strstr(&pDevInfoBuf[u32PosIndex], "MAGICNUM");

        if (pCurPos && '=' == *(pCurPos + strlen("MAGICNUM")))
        {
            if (!strncmp(pCurPos + strlen("MAGICNUM") + 1, STBINFO, strlen(STBINFO)+1)) /* +1 for skip '=' */
            {
                /* magic num is ok ,get device info valid length */
                u32PosIndex += strlen(&pDevInfoBuf[u32PosIndex]) + 1;   /* +1 for skip \0 */
                pCurPos = strstr(&pDevInfoBuf[u32PosIndex], "LENGTH");
                if (pCurPos && '=' == *(pCurPos + strlen("LENGTH")))
                {
                    *pu32ValidDevInfoLen = strtoul(pCurPos + strlen("LENGTH") + 1, HI_NULL, 16); /* +1 for skip '=' */
                    s32Ret = HI_SUCCESS;
                    goto out;
                }
                else
                {
                    HI_ERR_PDM("invalid device info part, no found valid length.\n");
                    goto out;
                }
            }
            else
            {
                HI_ERR_PDM("invalid device info part, magicnum dismatched.\n");
                goto out;
            }
        }
        else
        {
            u32PosIndex += strlen(&pDevInfoBuf[u32PosIndex]) + 1;   /* +1 for skip \0 */
        }
    }
    
out:
    return s32Ret;
}

/*
 * raw data example(MAC+\0+SN+\0+MAGICNUM+\0+LENGTH+\0+OUI+\0+HW+\0):
 * fc:48:ef:c9:35:36\0ab56fe98\0MAGICNUM=deviceinfo\0LENGTH=12345678\0OUI=
12345678\0HW=98765432\0
 */
static HI_S32 GetCADeviceCfgItem(HI_CHAR *pstrCfgName,  HI_CHAR * pOutBuf, HI_U32 u32OutBuflen, HI_CHAR * pInBuf, HI_U32 u32InBuflen)
{
    HI_U32 u32PosIndex = 0, u32DevInfoLen = 0;
    HI_S32 s32Ret = HI_FAILURE;

    /* verify device info data */
    s32Ret = VerifyCADeviceInfo( pInBuf, u32InBuflen, &u32DevInfoLen);
    if (HI_SUCCESS != s32Ret)
    {
        goto out;
    }

    /* because of compatibility reasons mac and sn do a special deal */
     if (!strncmp(pstrCfgName, "MAC", sizeof("MAC")))
    {
        strncpy(pOutBuf, &pInBuf[u32PosIndex], u32OutBuflen);
        pOutBuf[u32OutBuflen - 1] = '\0';
        s32Ret = HI_SUCCESS;
        goto out;
    }
    else  /* locate next cfg item */
    {
        u32PosIndex += strlen(&pInBuf[u32PosIndex]) + 1; /* +1 for skip \0 */
        if (u32PosIndex > u32DevInfoLen)         /* pos index overflow */
        {
            HI_ERR_PDM("pos index(%u) overflowed.\n", u32PosIndex);
            s32Ret = HI_FAILURE;
            goto out;
        }
    }

     if (!strncmp(pstrCfgName, "SN", sizeof("SN")))
     {
        strncpy(pOutBuf, &pInBuf[u32PosIndex], u32OutBuflen);
        pOutBuf[u32OutBuflen - 1] = '\0';
        s32Ret = HI_SUCCESS;
        goto out;
     }
     else /* locate next cfg item */
     {
        u32PosIndex += strlen(&pInBuf[u32PosIndex]) + 1; /* +1 for skip \0 */
        if (u32PosIndex > u32DevInfoLen) /* pos index overflow */
        {
            HI_ERR_PDM("pos index(%u) overflowed.\n", u32PosIndex);
            s32Ret = HI_FAILURE;
            goto out;
        }
     }

    /* search XXX=YYY style cfg item */
    while(u32PosIndex < u32DevInfoLen)
    {
        HI_CHAR *pCurPos = strstr(&pInBuf[u32PosIndex], pstrCfgName);

        if (pCurPos && '=' == *(pCurPos + strlen(pstrCfgName)))
        {
            strncpy(pOutBuf, pCurPos + strlen(pstrCfgName) + 1, u32OutBuflen); /* + 1 for skip '=' */
            pOutBuf[u32OutBuflen - 1] = '\0';
            s32Ret = HI_SUCCESS;
            break;    
        }
        else /* locate next cfg item */
        {
            u32PosIndex += strlen(&pInBuf[u32PosIndex]) + 1;   /* +1 for skip \0 */
        }    
    }
    
out:
    return s32Ret;
     
}

HI_S32 GetCADeviceInfo(HI_CHAR * pstrCfgName, HI_CHAR * pstrCfgValue, HI_U32 u32Size)
{
    HI_HANDLE hFlash = HI_INVALID_HANDLE;
    HI_CHAR  *pDevInfoBuf = HI_NULL;
    HI_CHAR  *pDevInfoBufTmp = HI_NULL;
    HI_U32 u32DevInfoBufLen = 0;
    PDM_FLASH_INFO_S stPartInfo;
    HI_S32 s32Ret = HI_FAILURE;
    
    if(HI_NULL == pstrCfgName || HI_NULL == pstrCfgValue || 0 == u32Size)
    {
        HI_ERR_PDM("ERR: param is invalid!\n");
        s32Ret = HI_ERR_PDM_PARAM_INVALID;
        goto out0;
    }

    s32Ret = PDM_GetFlashInfo(CADEVICEINFO, &stPartInfo);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PDM("ERR: no found '%s' partition.\n", CADEVICEINFO);
        s32Ret = HI_ERR_PDM_PARAM_INVALID;
        goto out0;
    }

    hFlash = HI_Flash_OpenByName(stPartInfo.Name);
    if(HI_INVALID_HANDLE == hFlash)
    {
        HI_ERR_PDM("ERR: HI_Flash_Open!\n");
        s32Ret = HI_ERR_PDM_MTD_OPEN;
        goto out0;
    }

    u32DevInfoBufLen = stPartInfo.u32Offset + stPartInfo.u32Size;
    
    if (NULL == (pDevInfoBuf = (HI_CHAR*)malloc(u32DevInfoBufLen)))
    {
        HI_ERR_PDM("Failed to malloc space(%u bytes).", u32DevInfoBufLen);
        s32Ret =  HI_ERR_PDM_MEM_ALLC;
        goto out1;
    }

    if (0 >= HI_Flash_Read(hFlash, (HI_U64)0, (HI_U8 *)pDevInfoBuf, u32DevInfoBufLen, HI_FLASH_RW_FLAG_RAW))
    {
        HI_ERR_PDM("Failed to read block.");
        s32Ret = HI_ERR_PDM_MTD_READ;
        goto out2;
    }

     /* according to the requirements of hisecurity, need decrypt here*/
    /* achieve encrypt data length*/
    s32Ret = CA_SSD_DecryptImage(pDevInfoBuf, u32DevInfoBufLen, CA_SSD_KEY_GROUP1);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_PDM("Failed to decrypt block.\n");
        goto out2;
    }

    s32Ret = CA_SSD_AuthenticateEx(pDevInfoBuf, &u32DevInfoBufLen);
    if ( HI_SUCCESS != s32Ret )
    {
        HI_ERR_PDM("Failed to authenticate block.\n");
        goto out2;
    }
    
#ifdef HI_ADVCA_SUPPORT
#ifdef HI_ADVCA_TYPE_NAGRA
        /*  considering the sbp signature header(4Bytes) */
        pDevInfoBufTmp = pDevInfoBuf + 4;
#else
#ifndef HI_ADVCA_TYPE_VERIMATRIX
        /*  considering the sbp signature header */
        HI_CAImgHead_S stCAImgHead;

        memset(&stCAImgHead, 0x0, sizeof(HI_CAImgHead_S));
        memcpy(&stCAImgHead,(HI_CAImgHead_S *)pDevInfoBuf,sizeof(HI_CAImgHead_S));
        pDevInfoBufTmp = pDevInfoBuf + stCAImgHead.u32CodeOffset;
#else
        pDevInfoBufTmp = pDevInfoBuf;
#endif
#endif
#endif

    s32Ret = GetCADeviceCfgItem(pstrCfgName, pstrCfgValue, u32Size, pDevInfoBufTmp + stPartInfo.u32Offset, stPartInfo.u32Size);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_PDM("parse device cfg item failed.\n");
        s32Ret = HI_ERR_PDM_GET_DEVINFO_ERR;
        goto out2;
    }

out2:
    free(pDevInfoBuf);
    pDevInfoBuf = HI_NULL;
    pDevInfoBufTmp = HI_NULL;
    
out1:
    HI_Flash_Close(hFlash);  
out0:
    return s32Ret;
}
#endif

HI_S32 HI_LOADER_ReadSTBInfo(HI_LOADER_STB_INFO_S* pstStbinfo)
{
    HI_CHAR ac8Buf[128];
    HI_S32 s32Ret = HI_FAILURE;

    if (NULL == pstStbinfo)
    {
        HI_ERR_LOADER("pointer is null.");
        return HI_FAILURE;
    }
    
    /* OUI */
    memset(ac8Buf, 0, sizeof(ac8Buf));
    s32Ret = LOADER_GetDeviceInfo("OUI", ac8Buf, sizeof(ac8Buf));
    if (HI_SUCCESS == s32Ret)
    {
        pstStbinfo->u32OUI = LOADER_strtoul(ac8Buf, HI_NULL, 16);
    }
    else
    {
        HI_ERR_LOADER("get OUI failed.\n");
        goto out;
    }

    /* HW */
    memset(ac8Buf, 0, sizeof(ac8Buf));
    s32Ret = LOADER_GetDeviceInfo("HW", ac8Buf, sizeof(ac8Buf));
    if (HI_SUCCESS == s32Ret)
    {
        pstStbinfo->u32HWVersion = LOADER_strtoul(ac8Buf, HI_NULL, 16);
    }
    else
    {
        HI_ERR_LOADER("get HW version failed.\n");
        goto out;
    }

    /* SN */
    memset(ac8Buf, 0, sizeof(ac8Buf));
    s32Ret = LOADER_GetDeviceSN("SN", ac8Buf, sizeof(ac8Buf));
    if (HI_SUCCESS == s32Ret)
    {
        if (strlen(ac8Buf) > 8)
        {
            pstStbinfo->u32HWSerialNum = LOADER_strtoul(ac8Buf+strlen(ac8Buf)-8, HI_NULL, 16);
        }
        else
        {
            pstStbinfo->u32HWSerialNum = LOADER_strtoul(ac8Buf, HI_NULL, 16);
        }
    }
    else
    {
        HI_ERR_LOADER("get SN failed.\n");
        goto out;
    }
    
out:
    return s32Ret;
}
/*
 * MAC\0SN\0MAGICNUM=xxx\0LENGTH=xxxxxxxx\0OUI=xxx\0HW=xxx\0 
 */
static HI_S32 UpdateDeviceInfo(HI_CHAR * pstrNewDevInfo, HI_U32 u32Size)
{
    HI_HANDLE hFlash = HI_INVALID_HANDLE;
    HI_CHAR  *pDevInfoBuf = HI_NULL;
    HI_U32 u32RegionSize, u32Offset, u32Len;
    HI_S32 s32Ret = HI_FAILURE;
    
    if(HI_NULL == pstrNewDevInfo || 0 == u32Size )
    {
        HI_ERR_LOADER("ERR: param is invalid!");
        s32Ret = HI_ERR_PDM_PARAM_INVALID;
        goto out0;
    }

    s32Ret = Upgrd_OpenDataBlock(STBINFO, &hFlash, &u32RegionSize, &u32Offset, &u32Len);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("ERR: no found '%s' partition.\n", STBINFO);
        s32Ret = HI_ERR_PDM_PARAM_INVALID;
        goto out0;
    }

    pDevInfoBuf = malloc(u32RegionSize);
    if (!pDevInfoBuf )
    {
        HI_ERR_LOADER("Failed to malloc space(%u bytes).", u32RegionSize);
        s32Ret =  HI_ERR_PDM_MEM_ALLC;
        goto out1;
    }

    if (0 >= HI_Flash_Read(hFlash, (HI_U64)0, (HI_U8 *)pDevInfoBuf, u32RegionSize, HI_FLASH_RW_FLAG_RAW))
    {
        HI_ERR_LOADER("Failed to read block.");
        s32Ret = HI_ERR_PDM_MTD_READ;
        goto out2;
    }
    
    /* avoid data corrupt in part shared mode */
    memcpy(pDevInfoBuf + u32Offset, pstrNewDevInfo, u32Len > u32Size ? u32Size :u32Len);
    
    if (0 >= HI_Flash_Write(hFlash, (HI_U64)0, (HI_U8*)pDevInfoBuf, u32RegionSize, HI_FLASH_RW_FLAG_ERASE_FIRST))
    {
        HI_ERR_LOADER("Failed to write block.");
        s32Ret =  HI_ERR_PDM_MTD_WRITE;
        goto out2;
    }

out2:
    free(pDevInfoBuf);
    
out1:
    HI_Flash_Close(hFlash);  
out0:
    return s32Ret;
}

#if defined(HI_ADVCA_SUPPORT) && !defined(HI_LOADER_BOOTLOADER) && !defined(HI_ADVCA_TYPE_VERIMATRIX)
HI_S32 HI_LOADER_WriteSTBInfo(HI_LOADER_STB_INFO_S* pstStbinfo)
{
    HI_ERR_LOADER("STB info is not allowed to write!\n");
    return HI_SUCCESS;
}
#else
HI_S32 HI_LOADER_WriteSTBInfo(HI_LOADER_STB_INFO_S* pstStbinfo)
{
    HI_CHAR ac8DevInfoStr[128];
    HI_CHAR ac8TmpBuf[128];
    HI_CHAR *pCurPos = ac8DevInfoStr;
    HI_CHAR *pPosLength = HI_NULL;
    HI_S32 s32Ret = HI_FAILURE;

    if (NULL == pstStbinfo)
    {
        HI_ERR_LOADER("pointer is null.");
        goto out;;
    }
    
    /* reserve MAC , but unused for loader */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "%s", "FFFFFFFFFFFF");
    strncpy(pCurPos, ac8TmpBuf, strlen(ac8TmpBuf) + 1);
    pCurPos += strlen(ac8TmpBuf) + 1; /* skip \0 */

    /* SN */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "%08x", pstStbinfo->u32HWSerialNum);
    strncpy(pCurPos, ac8TmpBuf, strlen(ac8TmpBuf) + 1);
    pCurPos += strlen(ac8TmpBuf) + 1; /* skip \0 */
    
    /* MAGICNUM */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "MAGICNUM=%s", STBINFO);
    strncpy(pCurPos, ac8TmpBuf, strlen(ac8TmpBuf) + 1);
    pCurPos += strlen(ac8TmpBuf) + 1; /* skip \0 */

    /* reserve LENGTH(LENGTH=xxxxxxxx) space */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "LENGTH=12345678");
    strncpy(pCurPos, ac8TmpBuf, strlen(ac8TmpBuf) + 1);
    pPosLength = pCurPos ;
    pCurPos += strlen(ac8TmpBuf) + 1; /* skip \0 */
    
    /* OUI */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "OUI=%08x", pstStbinfo->u32OUI);
    strncpy(pCurPos, ac8TmpBuf, strlen(ac8TmpBuf) + 1);
    pCurPos += strlen(ac8TmpBuf) + 1; /* skip \0 */
    
    /* HW */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "HW=%08x", pstStbinfo->u32HWVersion
);
    strncpy(pCurPos, ac8TmpBuf, strlen(ac8TmpBuf) + 1);
    pCurPos += strlen(ac8TmpBuf) + 1; /* skip \0 */

    /* update LENGTH */
    snprintf(ac8TmpBuf, sizeof(ac8TmpBuf), "LENGTH=%08x", pCurPos - ac8DevInfoStr);
    strncpy(pPosLength, ac8TmpBuf, strlen(ac8TmpBuf) + 1);

    s32Ret = UpdateDeviceInfo(ac8DevInfoStr, pCurPos - ac8DevInfoStr);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_LOADER("update device info failed.\n");
        goto out;
    }
    
out:
    return s32Ret;
}
#endif

