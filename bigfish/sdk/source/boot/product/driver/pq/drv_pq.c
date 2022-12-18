#include <uboot.h>
#include "hi_drv_pdm.h"
#include "hi_common.h"
#include "hi_drv_pq.h"
#include "hi_flash.h"


static HI_BOOL sg_bInitState = HI_FALSE;
static HI_BOOL sg_bGetBinState = HI_FALSE;

#ifndef HI_PQ_VERSION_V1
static HI_U32 u32PQ_Brightness[HI_UNF_DISPLAY_BUTT] = {50, 50, 50};
static HI_U32 u32PQ_Contrast[HI_UNF_DISPLAY_BUTT] =  {50, 50, 50};
static HI_U32 u32PQ_Saturation[HI_UNF_DISPLAY_BUTT] = {50, 50, 50};
static HI_U32 u32PQ_HuePlus[HI_UNF_DISPLAY_BUTT] = {50, 50, 50};
#else
static PQ_PARAM_S sg_stPqParam;
#endif


HI_S32 PQ_ReadPQ(HI_U32* pAddr)
{
    HI_S32              Ret = HI_SUCCESS;
    HI_HANDLE           hFlash = HI_INVALID_HANDLE;
    HI_S32              s32ReadLen = 0;
    HI_U32              u32StartPhyAddr = 0;
    HI_Flash_InterInfo_S    stFlashInfo = {0};

    hFlash = HI_Flash_OpenByName(PQ_DEF_NAME);

    if (HI_INVALID_HANDLE == hFlash)
    {
        HI_WARN_PQ("PQ_DRV_ReadPQ fail\r\n");
        Ret = HI_FAILURE;
        goto RET;
    }

    (HI_VOID)HI_Flash_GetInfo(hFlash, &stFlashInfo);

    Ret = HI_DRV_PDM_AllocReserveMem(PQ_DEF_NAME, MCE_DEF_PQPARAM_SIZE, &u32StartPhyAddr);

    if (HI_SUCCESS != Ret)
    {
        HI_ERR_PQ("Alloc Reserve pq Mem err!, Ret = %#x\n", Ret);
        Ret = HI_FAILURE;
        goto FLASH_CLOSE;
    }

    s32ReadLen = HI_Flash_Read(hFlash, 0, (HI_U8*)u32StartPhyAddr, MCE_DEF_PQPARAM_SIZE, HI_FLASH_RW_FLAG_RAW);

    if (0 > s32ReadLen)
    {
        HI_ERR_PQ("PQ_DRV_ReadPQ read fail,s32ReadLen = %d\r\n", s32ReadLen);
        Ret = HI_FAILURE;
        goto FLASH_CLOSE;
    }


    *pAddr = u32StartPhyAddr;

FLASH_CLOSE:
    HI_Flash_Close(hFlash);
RET:

    return Ret;
}

#ifdef HI_PQ_VERSION_V1
HI_S32 HI_PQ_GetPQData(PQ_PARAM_S** pAddr)
{
    if (HI_FALSE == sg_bInitState)
    {
        HI_PQ_Init();
    }

    if (HI_FALSE == sg_bGetBinState)
    {
        HI_ERR_PQ( "\r\nError,get pq bin failed\r\n" );
        return HI_FAILURE;
    }

    *pAddr = &sg_stPqParam;
    return HI_SUCCESS;
}

HI_S32 PQ_GetPQData()
{
    PQ_PARAM_S*       pstPdmPqParam;
    HI_U32 u32PqParaAddr;
    HI_S32 s32Ret;
    PQ_TOP_OFST_TABLE_S* pstPqTopOfst;
    PQ_FILE_HEADER_S* pstPqFileHead;
    HI_U32 u32CheckSize;
    HI_U32 u32CheckPos;
    HI_U32 u32CheckSum = 0;

    s32Ret = PQ_ReadPQ(&u32PqParaAddr);

    if (s32Ret)
    {
        HI_ERR_PQ("\r\nPQ_ReadPQ failed\r\n");
        return HI_FAILURE;
    }

    //check pq bin isvalid
    pstPdmPqParam = (PQ_PARAM_S*)u32PqParaAddr;
    pstPqTopOfst = (PQ_TOP_OFST_TABLE_S*)(pstPdmPqParam);

    if ((pstPqTopOfst->u32FileHeaderOfst) != sizeof(PQ_TOP_OFST_TABLE_S))
    {
        HI_ERR_PQ("\r\nPQ bin param is not burned\r\n");
        return HI_FAILURE;
    }

    pstPqFileHead = (PQ_FILE_HEADER_S*)((HI_U8*)(pstPdmPqParam) + pstPqTopOfst->u32FileHeaderOfst);
    u32CheckPos = pstPqTopOfst->u32DefaltOptOfst;
    u32CheckSize = pstPqFileHead->u32ParamSize;


    while (u32CheckPos < u32CheckSize)
    {
        u32CheckSum += *(HI_U8*)(((HI_U8*)pstPdmPqParam) + u32CheckPos);
        u32CheckPos++;
    }

    if (u32CheckSum != pstPqFileHead->u32FileCheckSum)
    {
        HI_ERR_PQ( "Error,checksum error,declare checksum = %d,calcsum = %d\r\n", pstPqFileHead->u32FileCheckSum, u32CheckSum);
        return HI_FAILURE;
    }

    memcpy((HI_VOID*)(&sg_stPqParam), (HI_VOID*)u32PqParaAddr, sizeof(sg_stPqParam));
    //version compare
    /*if (0 == HI_OSAL_Strncmp(pstPdmPqParam->stPQFileHeader.u8Version, PQ_VERSION, strlen(PQ_VERSION)))
    {
        memcpy((HI_VOID*)(&sg_stPqParam), (HI_VOID*)u32PqParaAddr, sizeof(sg_stPqParam));
    }
    else if (0 < HI_OSAL_Strncmp(pstPdmPqParam->stPQFileHeader.u8Version, PQ_VERSION, strlen(PQ_VERSION)))
    {
        HI_ERR_PQ("\r\n---Error,check version failed-----------Pq bin version = %s,Pq driver version = %s----------------\r\n", pstPdmPqParam->stPQFileHeader.u8Version, PQ_VERSION);
        return HI_FAILURE;
    }
    else
    {
        //convert version
        HI_ERR_PQ("\r\n--Error,check version failed------------Pq bin version = %s,Pq driver version = %s----------------\r\n", pstPdmPqParam->stPQFileHeader.u8Version, PQ_VERSION);
        return HI_FAILURE;
    }*/

    sg_bGetBinState = HI_TRUE;
    return HI_SUCCESS;
}
#endif

HI_VOID HI_PQ_Init(HI_VOID)
{
    HI_S32  s32Ret;
#ifndef HI_PQ_VERSION_V1
    HI_U32  u32PqParaAddr = 0;
    HI_DISP_PARAM_S stDispParam0 = {0};
    HI_DISP_PARAM_S stDispParam1 = {0};    
#endif

    if (HI_TRUE == sg_bInitState)
    {
        return;
    }

    sg_bInitState = HI_TRUE;

#ifndef HI_PQ_VERSION_V1
    s32Ret = PQ_ReadPQ(&u32PqParaAddr);
    if (s32Ret)
    {
        HI_ERR_PQ("\r\nPQ_ReadPQ failed\r\n");
        return;
    }

    s32Ret = HI_DRV_PDM_GetDispParam(HI_UNF_DISPLAY0, &stDispParam0);
    s32Ret |= HI_DRV_PDM_GetDispParam(HI_UNF_DISPLAY1, &stDispParam1);
    if (s32Ret)
    {
        HI_ERR_PQ("DISP get param failed!\n");
        u32PQ_Brightness[HI_UNF_DISPLAY0] =  50;
        u32PQ_Brightness[HI_UNF_DISPLAY1] =  50;

        u32PQ_Contrast[HI_UNF_DISPLAY0] =  50;
        u32PQ_Contrast[HI_UNF_DISPLAY1] =  50;

        u32PQ_Saturation[HI_UNF_DISPLAY0] =  50;
        u32PQ_Saturation[HI_UNF_DISPLAY1] =  50;

        u32PQ_HuePlus[HI_UNF_DISPLAY0] =  50;
        u32PQ_HuePlus[HI_UNF_DISPLAY1] =  50;
    }
    else
    {
        u32PQ_Brightness[HI_UNF_DISPLAY0] =  stDispParam0.u32Brightness;
        u32PQ_Brightness[HI_UNF_DISPLAY1] =  stDispParam1.u32Brightness;

        u32PQ_Contrast[HI_UNF_DISPLAY0] =  stDispParam0.u32Contrast;
        u32PQ_Contrast[HI_UNF_DISPLAY1] =  stDispParam1.u32Contrast;

        u32PQ_Saturation[HI_UNF_DISPLAY0] =  stDispParam0.u32Saturation;
        u32PQ_Saturation[HI_UNF_DISPLAY1] =  stDispParam1.u32Saturation;

        u32PQ_HuePlus[HI_UNF_DISPLAY0] =  stDispParam0.u32HuePlus;
        u32PQ_HuePlus[HI_UNF_DISPLAY1] =  stDispParam1.u32HuePlus;
    }
#else
    s32Ret = PQ_GetPQData();
    if (s32Ret)
    {
        HI_ERR_PQ("\r\nPQ_GetPQData failed\r\n");
        return;
    }
#endif

    return;
}

#ifndef HI_PQ_VERSION_V1
HI_S32 HI_PQ_GetBrightness(HI_U32 enChan, HI_U32* pu32Brightness)
{
    if (enChan > HI_UNF_DISPLAY1)
    {
        return HI_FAILURE;
    }

    *pu32Brightness = u32PQ_Brightness[enChan];
    return HI_SUCCESS;
}

HI_S32 HI_PQ_GetContrast(HI_U32 enChan, HI_U32* pu32Contrast)
{
    if (enChan > HI_UNF_DISPLAY1)
    {
        return HI_FAILURE;
    }

    *pu32Contrast = u32PQ_Contrast[enChan];
    return HI_SUCCESS;
}

HI_S32 HI_PQ_GetHue(HI_U32 enChan, HI_U32* pu32Hue)
{
    if (enChan > HI_UNF_DISPLAY1)
    {
        return HI_FAILURE;
    }

    *pu32Hue = u32PQ_HuePlus[enChan];
    return HI_SUCCESS;
}

HI_S32 HI_PQ_GetSaturation(HI_U32 enChan, HI_U32* pu32Saturation)
{
    if (enChan > HI_UNF_DISPLAY1)
    {
        return HI_FAILURE;
    }

    *pu32Saturation = u32PQ_Saturation[enChan];
    return HI_SUCCESS;
}

#if 0
HI_S32 HI_PQ_SetBrightness(HI_U32 enChan, HI_U32 u32Brightness)
{
    if (enChan > HI_UNF_DISPLAY1)
    { return HI_FAILURE; }

    if (u32Brightness > 100)
    { return HI_FAILURE; }

    u32PQ_Brightness[enChan] = u32Brightness;

    return HI_SUCCESS;
}

HI_S32 HI_PQ_SetContrast(HI_U32 enChan, HI_U32 u32Contrast)
{
    if (enChan > HI_UNF_DISPLAY1)
    { return HI_FAILURE; }

    if (u32Contrast > 100)
    { return HI_FAILURE; }

    u32PQ_Contrast[enChan] = u32Contrast;

    return HI_SUCCESS;
}

HI_S32 HI_PQ_SetHue(HI_U32 enChan, HI_U32 u32Hue)
{
    if (enChan > HI_UNF_DISPLAY1)
    { return HI_FAILURE; }

    if (u32Hue > 100)
    { return HI_FAILURE; }

    u32PQ_HuePlus[enChan] = u32Hue;

    return HI_SUCCESS;
}

HI_S32 HI_PQ_SetSaturation(HI_U32 enChan, HI_U32 u32Saturation)
{
    if (enChan > HI_UNF_DISPLAY1)
    { return HI_FAILURE; }

    if (u32Saturation > 100)
    { return HI_FAILURE; }

    u32PQ_Saturation[enChan] = u32Saturation;

    return HI_SUCCESS;
}

HI_S32 Num2Level(HI_U32 u32Number)
{
    if (u32Number)
    {
        return (u32Number * 100 + 127) / 255;
    }
    else
    {
        return u32Number;
    }
}

HI_S32 Level2Num(HI_U32 Level)
{
    if (Level)
    {
        return (Level * 255 + 50) / 100;
    }
    else
    {
        return Level;
    }
}

/**
 \brief ��ȡ����
 \attention \n
��

 \param[out] pu32Brightness ����ֵ,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetBrightness(HI_U32 enChan , HI_U32* pu32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (!pu32Brightness)
    {
        HI_ERR_PQ("null !\n", pu32Brightness);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Brightness = stPictureSetting.u16Hue;
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Brightness = stPictureSetting.u16Hue;
    }
    return HI_SUCCESS;
}


/**
 \brief ��������
 \attention \n
��

 \param[in] u32Brightness, ����ֵ,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_SetBrightness(HI_U32 enChan , HI_U32 u32Brightness)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (u32Brightness > 255)
    {
        HI_ERR_PQ("%d:u32Contrast is over range!\n", u32Brightness);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Brightness;
        PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Brightness;
        PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    }

    HI_ERR_PQ("Set Contrast level %d\n", u32Brightness);
    return HI_SUCCESS;
}


/**
 \brief ��ȡ�Աȶ�
 \attention \n
��

 \param[out] pu32Contrast �Աȶ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetContrast(HI_U32 enChan , HI_U32* pu32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (!pu32Contrast)
    {
        HI_ERR_PQ("null !\n", pu32Contrast);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Contrast = stPictureSetting.u16Hue;
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Contrast = stPictureSetting.u16Hue;
    }
    return HI_SUCCESS;
}


/**
 \brief ���öԱȶ�
 \attention \n
��
 \param[in] u32Contrast, �Աȶ�, ��Ч��Χ: 0~255;
 \retval ::HI_SUCCESS
 */
HI_S32 DRV_PQ_SetContrast(HI_U32 enChan , HI_U32 u32Contrast)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (u32Contrast > 255)
    {
        HI_ERR_PQ("%d:u32Contrast is over range!\n", u32Contrast);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Contrast;
        PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Contrast;
        PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    }

    HI_ERR_PQ("Set Contrast level %d\n", u32Contrast);
    return HI_SUCCESS;
}

/**
 \brief ��ȡɫ��
 \attention \n
��

 \param[out] pu32Hue  ɫ��, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetHue(HI_U32 enChan , HI_U32* pu32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (!pu32Hue)
    {
        HI_ERR_PQ("null !\n", pu32Hue);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Hue = stPictureSetting.u16Hue;
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Hue = stPictureSetting.u16Hue;
    }
    return HI_SUCCESS;
}

/**
 \brief ����ɫ��
 \attention \n
��

 \param[in] u32Hue   ɫ��, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetHue(HI_U32 enChan , HI_U32 u32Hue)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (u32Hue > 255)
    {
        HI_ERR_PQ("%d:u32Contrast is over range!\n", u32Hue);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Hue;
        PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Hue;
        PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    }

    HI_ERR_PQ("Set Contrast level %d\n", u32Hue);
    return HI_SUCCESS;
}

/**
 \brief ��ȡ���Ͷ�
 \attention \n
��

 \param[out] pu32Saturation  ���Ͷ�, ��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */

HI_S32 DRV_PQ_GetSaturation(HI_U32 enChan , HI_U32* pu32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (!pu32Saturation)
    {
        HI_ERR_PQ("null !\n", pu32Saturation);
        return HI_FAILURE;
    }

    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Saturation = stPictureSetting.u16Hue;
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        *pu32Saturation = stPictureSetting.u16Hue;
    }
    return HI_SUCCESS;
}


/**
 \brief ���ñ��Ͷ�
 \attention \n
��

 \param[in] u32Saturation ���Ͷ�,��Ч��Χ: 0~255;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSaturation(HI_U32 enChan , HI_U32 u32Saturation)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (enChan > 2)
    {
        HI_ERR_PQ("%d:chan is err !\n", enChan);
        return HI_FAILURE;
    }

    if (u32Saturation > 255)
    {
        HI_ERR_PQ("%d:u32Contrast is over range!\n", u32Saturation);
        return HI_FAILURE;
    }


    if ( enChan )
    {
        PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Saturation;
        PQ_MNG_SetSDPictureSetting(&stPictureSetting, &stColorTemp);
    }
    else
    {
        PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
        stPictureSetting.u16Contrast = u32Saturation;
        PQ_MNG_SetHDPictureSetting(&stPictureSetting, &stColorTemp);
    }

    HI_ERR_PQ("Set Contrast level %d\n", u32Saturation);
    return HI_SUCCESS;
}


/**
 \brief ��ȡ����/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��
 \param[out] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�;
 \retval ::HI_SUCCESS
 */
HI_S32 DRV_PQ_GetSDPictureSetting(PICTURE_SETTING_S* pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    pstPictureSetting->u16Brightness = stPictureSetting.u16Brightness;
    pstPictureSetting->u16Contrast = stPictureSetting.u16Contrast;
    pstPictureSetting->u16Hue = stPictureSetting.u16Hue;
    pstPictureSetting->u16Saturation = stPictureSetting.u16Saturation;

    return HI_SUCCESS;
}
HI_S32 DRV_PQ_GetHDPictureSetting(PICTURE_SETTING_S* pstPictureSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    pstPictureSetting->u16Brightness = stPictureSetting.u16Brightness;
    pstPictureSetting->u16Contrast = stPictureSetting.u16Contrast;
    pstPictureSetting->u16Hue = stPictureSetting.u16Hue;
    pstPictureSetting->u16Saturation = stPictureSetting.u16Saturation;

    return HI_SUCCESS;
}

/**
 \brief ��������/�Աȶ�/ɫ��/���Ͷ�
 \attention \n
��

 \param[in] u32Hue   ����/�Աȶ�/ɫ��/���Ͷ�;

 \retval ::HI_SUCCESS

 */
HI_S32 DRV_PQ_SetSDPictureSetting(PICTURE_SETTING_S* pstPictureSetting, HI_BOOL bFormalSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (HI_NULL == pstPictureSetting)
    {
        HI_ERR_PQ( "pstPictureSetting is NULL!\n");
        return HI_FAILURE;
    }

    PQ_MNG_GetSDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Brightness = pstPictureSetting->u16Brightness;
    stPictureSetting.u16Contrast = pstPictureSetting->u16Contrast;
    stPictureSetting.u16Hue = pstPictureSetting->u16Hue;
    stPictureSetting.u16Saturation = pstPictureSetting->u16Saturation;

    return HI_SUCCESS;
}
HI_S32 DRV_PQ_SetHDPictureSetting(PICTURE_SETTING_S* pstPictureSetting, HI_BOOL bFormalSetting)
{
    PICTURE_SETTING_S stPictureSetting;
    COLOR_TEMPERATURE_S stColorTemp;

    if (HI_NULL == pstPictureSetting)
    {
        HI_ERR_PQ( "pstPictureSetting is NULL!\n");
        return HI_FAILURE;
    }

    PQ_MNG_GetHDPictureSetting(&stPictureSetting, &stColorTemp);
    stPictureSetting.u16Brightness = pstPictureSetting->u16Brightness;
    stPictureSetting.u16Contrast = pstPictureSetting->u16Contrast;
    stPictureSetting.u16Hue = pstPictureSetting->u16Hue;
    stPictureSetting.u16Saturation = pstPictureSetting->u16Saturation;

    return HI_SUCCESS;
}
#endif

#else
HI_S32 HI_PQ_GetBrightness(HI_U32 enChan, HI_U32* pu32Brightness)
{

    return HI_SUCCESS;
}

HI_S32 HI_PQ_GetContrast(HI_U32 enChan, HI_U32* pu32Contrast)
{

    return HI_SUCCESS;
}

HI_S32 HI_PQ_GetHue(HI_U32 enChan, HI_U32* pu32Hue)
{

    return HI_SUCCESS;
}

HI_S32 HI_PQ_GetSaturation(HI_U32 enChan, HI_U32* pu32Saturation)
{

    return HI_SUCCESS;
}
#if 0
HI_S32 HI_PQ_SetBrightness(HI_U32 enChan, HI_U32 u32Brightness)
{
    return HI_SUCCESS;
}

HI_S32 HI_PQ_SetContrast(HI_U32 enChan, HI_U32 u32Contrast)
{
    return HI_SUCCESS;
}

HI_S32 HI_PQ_SetHue(HI_U32 enChan, HI_U32 u32Hue)
{
    return HI_SUCCESS;
}

HI_S32 HI_PQ_SetSaturation(HI_U32 enChan, HI_U32 u32Saturation)
{
    return HI_SUCCESS;
}
#endif
#endif

