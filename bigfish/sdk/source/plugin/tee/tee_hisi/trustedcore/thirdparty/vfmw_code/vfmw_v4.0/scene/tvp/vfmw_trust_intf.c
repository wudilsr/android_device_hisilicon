
#include "vfmw_trust_intf.h"
#include "vfmw_osal.h"
#include "vfmw_ctrl.h"

/* SECURE MARK */
RAW_ARRAY_NS *g_pStreamList = NULL; //manage stream buffer 
CALLBACK_ARRAY_NS *g_pCallBackList = NULL;//manage callback buffer

/************************************************************************
    TEE 通信封装接口
*************************************************************************/
SINT32 SEC_VDEC_Init( UINT32 pVdecCallback)
{
    SINT32 ret = 0;
    ret = OSAL_Map_To_Ns(pVdecCallback, sizeof(UINT32), 1);
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VDEC_Init((VOID *)pVdecCallback);
    }
     OSAL_UnMap_To_Ns(pVdecCallback, sizeof(UINT32), 1);
    return ret;
}

SINT32 SEC_VDEC_InitWithOperation(UINT32 pArgs)
{
    SINT32 ret = 0;
    ret = OSAL_Map_To_Ns(pArgs, sizeof(VDEC_OPERATION_S), 1);
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VDEC_InitWithOperation((VDEC_OPERATION_S *)pArgs);
    }
    OSAL_UnMap_To_Ns(pArgs, sizeof(VDEC_OPERATION_S), 1);
    return ret;
}

SINT32 SEC_VDEC_Control(SINT32 ChanID, UINT32 eCmdID, UINT32 pArgs)
{
    SINT32 ret = 0;
    ret = OSAL_Map_To_Ns(pArgs, 1<<10, 1);//指针所指的内容长度未知，暂映射1K
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VDEC_Control(ChanID, eCmdID, (VOID *)pArgs);
    }
    OSAL_UnMap_To_Ns(pArgs, 1<<10, 1);
    return ret;
}

SINT32 SEC_VDEC_Exit(VOID)
{
    SINT32 ret = 0;
    ret = VDEC_Exit();
    OSAL_UnMap_To_Ns(g_pCallBackList, sizeof(CALLBACK_ARRAY_NS), 1);
    OSAL_UnMap_To_Ns(g_pStreamList, sizeof(RAW_ARRAY_NS)*MAX_CHAN_NUM, 1);
    g_pStreamList = NULL;
    g_pCallBackList = NULL;

    return ret;
}

SINT32 SEC_VDEC_Suspend(VOID)
{
    return VDEC_Suspend();
}

SINT32 SEC_VDEC_Resume(VOID)
{
    return VDEC_Resume();
}

SINT32 SEC_VCTRL_RunProcess(VOID)
{
   	SINT32 ret =0;

    ret = VCTRL_RunProcess();
    return ret;
}

SINT32 SEC_VCTRL_ReadProc(UINT32 page, SINT32 count)
{
    SINT32 ret = 0;
    //dprint(PRN_ERROR, "Proc: Phy=0x%x, Size=0x%x\n", page, MAX_PROC_SIZE);  
    ret = OSAL_Map_To_Ns(page, MAX_PROC_SIZE, 1);
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VCTRL_ReadProc((SINT8 *)page, count);
    }
    OSAL_UnMap_To_Ns(page, MAX_PROC_SIZE, 1);
    return ret;
}

SINT32 SEC_VCTRL_WriteProc(UINT32 option, SINT32 value)
{
    return VCTRL_WriteProc(option, value);
}

SINT32 SEC_VCTRL_SetDbgOption (UINT32 opt, UINT32 p_args)
{
    SINT32 ret = 0;
    ret = OSAL_Map_To_Ns(p_args, sizeof(UINT32), 1);
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VCTRL_SetDbgOption(opt, (UINT8 *)p_args);
    }
    OSAL_UnMap_To_Ns(p_args, sizeof(UINT32), 1);
    return ret;
}

SINT32 SEC_VCTRL_GetChanImage( SINT32 ChanID, UINT32 pImage )
{
    //dprint(PRN_FATAL, "%s %d, enter\n", __func__,__LINE__);
    SINT32 ret = 0;
    ret = OSAL_Map_To_Ns(pImage, sizeof(IMAGE), 1);
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VCTRL_GetChanImage(ChanID, (IMAGE *)pImage);
    }
    OSAL_UnMap_To_Ns(pImage, sizeof(IMAGE), 1);
    //dprint(PRN_FATAL, "%s %d, exit\n", __func__,__LINE__);
	
    return ret;
}

SINT32 SEC_VCTRL_ReleaseChanImage( SINT32 ChanID, UINT32 pImage )
{
    SINT32 ret = 0;
    ret = OSAL_Map_To_Ns(pImage, sizeof(IMAGE), 1);
    if (VDEC_ERR == ret)
    {
        dprint(PRN_FATAL, "%s %d, map_section_entry failed ret=%d\n", __func__,__LINE__,ret);
    }
    else
    {
        ret = VCTRL_ReleaseChanImage(ChanID, (IMAGE *)pImage);
    }
    OSAL_UnMap_To_Ns(pImage, sizeof(IMAGE), 1);
    return ret;
}


