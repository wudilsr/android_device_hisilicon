#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <sys/time.h>
#include <fcntl.h>
#include <errno.h>
#include <pthread.h>
#include <linux/types.h>

#include "hi_module.h"
#include "hi_mpi_mem.h"

#include "msg_trace.h"

#ifdef __cplusplus
#if __cplusplus
extern "C"
{
#endif
#endif

/* BEGIN: Added by zhangcheng, 2011/1/27   PN:msg trace code*/
static MSF_CAP_S  g_uiMsgCapStatus [HME_MAX_CHANNEL_COUNT];  /*message track describle*/
VOIP_HME_TRACE_S g_stHmeTrace;

static char strOutputFileName[HME_MAX_USER_MSG_TRACE_PATH] = "";
static FILE *fp_OUT =NULL;

static uint16 g_usDbgCapMsgSeq;

/* END:   Added by zhangcheng, 2011/1/27 */

/* BEGIN: Added by zhangcheng, 2011/1/27   PN:msg trace code*/
/*****************************************************************************
 Prototype    : VOIP_HME_InitCapMsg
 Description  : initialize user mode message capture
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/2/9
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID VOIP_HME_InitCapMsg( )
{
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN:A9B02_ZC_0211_02 */
    VOIP_HME_ClearAllMsgCapFlag();
    /* END:   Modified by zhangcheng, 2011/2/12 */
    g_usDbgCapMsgSeq = 0;
    g_stHmeTrace.pTraceSendMsg = VOIP_HME_CapSendMsg;
    g_stHmeTrace.pTraceRecvMsg = VOIP_HME_CapRecvMsg;
    fp_OUT = NULL;
    return;
}

/*****************************************************************************
 Prototype    : VOIP_HME_DeInitCapMsg
 Description  : deinitialize user mode message capture
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/2/9
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID VOIP_HME_DeInitCapMsg()
{
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN:A9B02_ZC_0211_02 */
    VOIP_HME_ClearAllMsgCapFlag();
    /* END:   Modified by zhangcheng, 2011/2/12 */
    /* BEGIN: Added by caizhigang, 2011/2/28   PN:DTS2011022801935 */
    if (NULL != fp_OUT)
    /* END:   Added by caizhigang, 2011/2/28 */        
    {
        fclose(fp_OUT);
        fp_OUT = NULL;        
    }
    return;
}




/*****************************************************************************
 Prototype    : VOIP_HME_CapMsg
 Description  : capture sendMsg
 Input        : HI_S32 iChnId       
                HI_U8 *pDataCapBuf  
                HI_U16 uwLen    
                HI_U16  uwDirection
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/1/27
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID VOIP_HME_CapMsg(HI_HANDLE hVoipHme, HI_U8 *pucDataCapBuf, HI_U16 uwLen, HI_U16  uwDirection)
{
    HI_U8  *pucMemoryAddr;
    HI_U32  uiChnId;

    MSG_FRAME_S  *pstMsgFrameStru;

    if (NULL == pucDataCapBuf)
    {  
        /* BEGIN: Added by wangjuan, 2010/10/20   PN:czg_review_1018_10*/
        HI_ERR_HME("Err pucDataCapBuf pointer is null!");
        /* END:   Added by wangjuan, 2010/10/20 */
        return;
    }  
    
    uiChnId = hVoipHme&0x000000ff;
    if (hVoipHme != HI_INVALID_HANDLE)
    {
        if (!VOIP_HME_GetMsgCapFlag(uiChnId))
        {
            return;
        }
    }
   
    /*reserve mac, ethernet, UDP head*/
    pucMemoryAddr = (uint8  *)HI_MALLOC(HI_ID_VOIP_HME, CAP_MSG_HEAD_LEN + uwLen);
    /* BEGIN: Modified by wangjuan, 2010/10/20   PN:czg_review_1018_13*/
    if (NULL == pucMemoryAddr)
    {
        HI_ERR_HME("Err No Free Memory to Alloc!");        
        return ;
    }
    /* END:   Modified by wangjuan, 2010/10/20 */

    pstMsgFrameStru = (MSG_FRAME_S*)pucMemoryAddr;
    pstMsgFrameStru->acKeyWord[0] = 'M';
    pstMsgFrameStru->acKeyWord[1] = 'S';
    pstMsgFrameStru->acKeyWord[2] = 'G';
    pstMsgFrameStru->acKeyWord[3] = '8';
    pstMsgFrameStru->uwFrmLen = CAP_MSG_HEAD_LEN + uwLen;
    pstMsgFrameStru->stRecord.uiCnxId = uiChnId;   
    pstMsgFrameStru->stRecord.uwSeq = g_usDbgCapMsgSeq++;
    pstMsgFrameStru->stRecord.uwTick = VOIP_HME_TimeGetTime();  //get system run time
    pstMsgFrameStru->stRecord.uwDspTs = HME_NULL_WORD;
    pstMsgFrameStru->stRecord.uwLen = uwLen; 
    pstMsgFrameStru->stRecord.uwDirection = uwDirection;
    
    memcpy((pucMemoryAddr + CAP_MSG_HEAD_LEN), pucDataCapBuf, uwLen);
    if (NULL != fp_OUT)
    {
        if (pstMsgFrameStru->uwFrmLen != fwrite(pucMemoryAddr, sizeof(uint8), pstMsgFrameStru->uwFrmLen, fp_OUT))
        {
            HI_ERR_HME("Err VOIP_HME_CapMsg fwrite!");
        }
    }
    else
    {
         /* BEGIN: Modified by wangjuan, 2011/3/28   PN:DTS2011032404856*/
         if (HI_INVALID_HANDLE != hVoipHme)
         {
             HI_ERR_HME("Err VOIP_HME_CapMsg fp_OUT is NULL!");
         }
         /* END:   Modified by wangjuan, 2011/3/28 */
    }
   
    HI_FREE(HI_ID_VOIP_HME, pucMemoryAddr);   
    return;
}

/*****************************************************************************
 Prototype    : VOIP_HME_CapSendMsg
 Description  : 
 Input        : HI_S32 iChnId       
                HI_U8 *pDataCapBuf  
                HI_U16 uwLen   
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/1/28
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID  VOIP_HME_CapSendMsg(HI_HANDLE hVoipHme, HI_U8 *pucDataCapBuf, HI_U16 uwLen)
{
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN:wj_code_0211_02 */
    VOIP_HME_CapMsg(hVoipHme, pucDataCapBuf, uwLen, MSG_SEND);
    /* END:   Modified by zhangcheng, 2011/2/12 */
    return;
}

/*****************************************************************************
 Prototype    : VOIP_HME_CapRecvMsg
 Description  : 
 Input        : HI_S32 iChnId       
                HI_U8 *pDataCapBuf  
                HI_U16 uwLen   
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/1/28
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID  VOIP_HME_CapRecvMsg(HI_HANDLE hVoipHme, HI_U8 *pucDataCapBuf, HI_U16 uwLen)
{
    /* BEGIN: Modified by zhangcheng, 2011/2/12   PN:wj_code_0211_02 */
    VOIP_HME_CapMsg(hVoipHme, pucDataCapBuf, uwLen, MSG_RSP);
    /* END:   Modified by zhangcheng, 2011/2/12 */
    return;
}

/* BEGIN: Modified by zhangcheng, 2011/2/26   PN:msg trace set*/
/*****************************************************************************
 Prototype    : VOIP_HME_SetMsgCapFlag
 Description  : set message capture flag
 Input        : int32 iChnId      
                uint32 uiFlag     
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/1/30
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID VOIP_HME_SetMsgCapFlag(HI_S32 iChnId, HI_U32 uiFlag, HI_U8 *aucUsersPath)
{
    FILE *fp_tmp;
    if ((HI_U32)iChnId >= HME_MAX_CHANNEL_COUNT)
    {
        HI_ERR_HME("Err iChnId:%d in VOIP_HME_SetMsgCapFlag!",
            iChnId);
        return;
    }  
    if ((uiFlag != true) && (uiFlag != false) )
    {
        HI_ERR_HME("Err uiFlag:%d in VOIP_HME_SetMsgCapFlag!",
            uiFlag);
        return;
    }
    /*start capture*/
    if (true == uiFlag)
    {
        /*saving direction of user mode message trace file is changed or the file is opened first*/
        if ((strcmp(strOutputFileName, (HI_CHAR *)aucUsersPath)) || (NULL == fp_OUT))
        {
            fp_tmp = fopen((char *)aucUsersPath, "wb");
            if (!fp_tmp)
            {
                HI_ERR_HME("fopen%s err in VOIP_HME_SetMsgCapFlag",strOutputFileName);
                return;
            }
            else
            {
            	if (NULL != fp_OUT)
            	{
					fclose(fp_OUT); //for fix MOTO
				}
                strncpy(strOutputFileName, (HI_CHAR *)aucUsersPath, HME_MAX_USER_MSG_TRACE_PATH);
                fp_OUT = fp_tmp;
            }
        }
    }
    g_uiMsgCapStatus[iChnId].uiMsgCapFlag = uiFlag;
    return;
}
/* END:   Modified by zhangcheng, 2011/2/26 */

/*****************************************************************************
 Prototype    : VOIP_HME_GetMsgCapFlag
 Description  : set message capture flag
 Input        : int32 iChnId      
                uint32 uiFlag     
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/1/30
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_U32 VOIP_HME_GetMsgCapFlag(HI_U32 uiChnId)
{
    if (uiChnId >= HME_MAX_CHANNEL_COUNT)
    {
        HI_ERR_HME("Err uiChnId:%d in VOIP_HME_SetMsgCapFlag!",
            uiChnId);
        return false;
    }  
    return g_uiMsgCapStatus[uiChnId].uiMsgCapFlag ;
}

/*****************************************************************************
 Prototype    : VOIP_HME_ClearAllMsgCapFlag
 Description  : clear all message capture
 Output       : None
 Return Value : 
 Calls        : 
 Called By    : 
 
  History        :
  1.Date         : 2011/1/30
    Author       : zhangcheng
    Modification : Created function

*****************************************************************************/
HI_VOID VOIP_HME_ClearAllMsgCapFlag()
{   
    int32 i;
    for(i = 0; i < HME_MAX_CHANNEL_COUNT; i++)
    {
       VOIP_HME_SetMsgCapFlag(i, false, NULL);
    }
    return;
}
HI_U32 VOIP_HME_TimeGetTime(void)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (HI_U32)(tv.tv_sec * 1000 + tv.tv_usec/1000);
}
/* END:   Added by zhangcheng, 2011/1/27 */

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
