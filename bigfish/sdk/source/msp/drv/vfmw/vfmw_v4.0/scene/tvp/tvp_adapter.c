/*-----------------------------------------------------------------------*/
/*!!Warning: Huawei key information asset. No spread without permission. */
/*CODEMARK:EG4uRhTwMmgcVFBsBnYHCEm2UPcyllv4D4NOje6cFLSYglw6LvPA978sGAr3yTchgOI0M46H
HZIZCDLcNqR1rYgDnWEYHdqiWpPUq+8h0NJ5vAPu/oxljuTsvJQOTqM/rc+aZJCW69Jife4y
0B+Jv2E9pVcAbsiUtRUS0X56YPPEbwpbfTFsO36QWbHDOiefPXk21cJ3KBTdKbMTKrn8sY0B
YBuFa0u3dOcN2dQ/ojqyXIgyeGNTeFH6X31g4HuwSkJcU019yOCvo+So6oRt+Q==#*/
/*--!!Warning: Deleting or modifying the preceding information is prohibited.--*/












/******************************************************************************

  ��Ȩ���� (C), 2001-2013, ��Ϊ�������޹�˾

******************************************************************************
    �� �� ��   : drv_firmware.c
    �� �� ��   : ����
    ��    ��   :
    ��������   :
    ����޸�   :
    ��������   : firmware�Ķ���ӿ�ʵ��


    �޸���ʷ   :
    1.��    �� : 2013-10-22
    ��    ��   : 
    �޸�����   :

******************************************************************************/
	
#include "hi_osal.h"
#include "hi_drv_proc.h"
#include "hi_drv_module.h"
#include "public.h"
#include "vfmw.h"
#include "vfmw_debug.h"
#include "vfmw_osal.h"
#include "tvp_adapter.h"


#include <tc_ns_client.h>
#include <tee_client_type.h>
#include <tee_client_api.h>
#include <tee_client_id.h>

#if (1 == DEBUG_SAVE_SUPPORT)
#include "sec_mmz.h"
#endif

#define PATH_LEN              (64)
#define PROC_CMD_LEN          (16)

#define PROC_NAME             "sec_vfmw"
#define PROC_CMD_HELP         "help"
#define PROC_CMD_SAVERAW      "saveraw"
#define PROC_CMD_SAVEYUV      "saveyuv"
#define PROC_CMD_START        "start"
#define PROC_CMD_STOP         "stop"
#define PROC_CMD_SETPRINT     (0x000)

#ifdef CFG_MAX_CHAN_NUM
#define TOTAL_MAX_CHAN_NUM    (CFG_MAX_CHAN_NUM)
#else
#define TOTAL_MAX_CHAN_NUM    (32)
#endif
#define TRUSTED_CHAN_BEGIN    (TOTAL_MAX_CHAN_NUM/2)

#define INVALID_HANDLE        (-1)

#define PRINT_TEE_TIME        (0)

#ifndef HI_ADVCA_FUNCTION_RELEASE
#define SecPrint(type, fmt, arg...)             \
do{                                             \
	if (PRN_ALWS == type                        \
     || 0 != (g_SecPrintEnable & (1 << type)))  \
	{                                           \
		printk("<SEC VFMW> " fmt, ##arg);       \
	}                                           \
}while(0)
#else
// �߰����ܼ�⵽�ַ�����printk
#define SecPrint(type, fmt, arg...)             \
do{                                             \
}while(0)
#endif

typedef enum hiCHAN_STATE_E
{      
    CHAN_INVALID = 0, 
    CHAN_START,          
    CHAN_STOP,           
    CHAN_BUTT,
} CHAN_STATE_E;

typedef enum hiTHREAD_STATE_E
{            
    THREAD_INVALID = 0, 
    THREAD_SLEEP, 
    THREAD_RUN,    
    THREAD_EXIT,            
    THREAD_BUTT,
} THREAD_STATE_E;

typedef enum 
{
    VFMW_CMD_ID_INVALID = 0x0,
    VFMW_CMD_ID_VDEC_INIT,
    VFMW_CMD_ID_VDEC_EXIT, 
    VFMW_CMD_ID_VDEC_RESUME,
    VFMW_CMD_ID_VDEC_SUSPEND,
    VFMW_CMD_ID_VDEC_CONTROL,
    VFMW_CMD_ID_VFMW_READPROC, 
    VFMW_CMD_ID_VFMW_WRITEPROC,
    VFMW_CMD_ID_VFMW_THREADPROC,
    VFMW_CMD_ID_VCTRL_SETDBGOPTION,
    VFMW_CMD_ID_VFMW_GETCHANIMAGE,
    VFMW_CMD_ID_VFMW_RELEASECHANIMAGE,
    VFMW_CMD_ID_VDEC_INITWITHOPERATION,
} TEE_VFMW_CMD_ID;

typedef struct 
{
    HI_BOOL            bIsSecMode;
    HI_S32             ChanID;
    CHAN_STATE_E       ChanState;
    OSAL_SEMA          ChanSema;

    struct file*       pRawFile;
    
} CHAN_CONTEXT_S;

typedef struct
{
    CALLBACK_ARRAY_NS  CallBackBuf;  
    VDEC_CHAN_OPTION_S ChanOption;
    RAW_ARRAY_NS       StreamBuf[TOTAL_MAX_CHAN_NUM];
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    HI_U8              ProcBuf[MAX_PROC_SIZE];
#endif
#if (1 == DEBUG_SAVE_SUPPORT)
    HI_U8              SaveStreamBuf[3*1024*1024];
#else
    HI_U8              Reserve[1*1024*1024];  // y00226912
#endif
} MEMORY_NEEDED_SECVFMW_S;

/*ָ��ȫ�ֱ���*/ 
MEMORY_NEEDED_SECVFMW_S *g_pSecVfmwMem  = HI_NULL;
CALLBACK_ARRAY_NS       *g_pCallbackBuf = HI_NULL;
RAW_ARRAY_NS            *g_pStreamBuf   = HI_NULL; 
VDEC_CALLBACK            g_pCallBack    = HI_NULL;
#if (1 == DEBUG_SAVE_SUPPORT)
HI_U8                   *g_pSaveStreamBuf = HI_NULL;
#endif
#ifndef  HI_ADVCA_FUNCTION_RELEASE
HI_U8                   *g_pProcBuf     = HI_NULL;
#endif

/*TEE ͨ����ر���*/
static TEEC_Context      g_TeeContext;
static TEEC_Session      g_TeeSession;
static HI_U32            g_TeeDeviceId;

/*��̬ȫ�ֱ���*/
static MEM_DESC_S        g_SecVfmwMem;
static HI_S32            g_SecPrintEnable       = 0x0;
static HI_S32            g_SecureInstNum        = 0;
static HI_S32            g_TrustDecoderInitCnt  = 0;
static HI_BOOL           g_bSecEnvSetUp    = HI_FALSE;
static THREAD_STATE_E    g_THREAD_STATE         = THREAD_INVALID;
static OSAL_SEMA         g_stSem_s;
#if (1 == DEBUG_SAVE_SUPPORT)
static HI_BOOL           g_RawSaveEnable        = HI_FALSE;
static HI_CHAR           g_SavePath[PATH_LEN]   = {'/','m','n','t','\0'};
#endif

/*ͨ�����ȫ�ֱ���*/
static STREAM_INTF_S     g_StreamIntf[TOTAL_MAX_CHAN_NUM];
static CHAN_CONTEXT_S    g_ChanContext[TOTAL_MAX_CHAN_NUM];


#if (1 == DEBUG_SAVE_SUPPORT)
HI_VOID TVP_VDEC_SaveStream(HI_S32 ChanID, HI_BOOL bSaveEnable, HI_U32 PhyAddr, HI_S32 Length)
{
    mm_segment_t       oldfs; 
    HI_CHAR FilePath[PATH_LEN];
    struct file **ppFile = &g_ChanContext[ChanID].pRawFile;
    
    if (HI_TRUE == bSaveEnable && *ppFile == HI_NULL)
    {
        snprintf(FilePath, sizeof(FilePath), "%s/trusted_vfmw_chan%d.raw", g_SavePath, ChanID);
        *ppFile = filp_open(FilePath, O_RDWR|O_CREAT|O_TRUNC, S_IRWXO);
        if (IS_ERR(*ppFile))
        {
            SecPrint(PRN_ERROR, "%s open raw file failed, ret=%ld\n", __func__, PTR_ERR(*ppFile));
            *ppFile = HI_NULL;
        }
        else
        { 
            SecPrint(PRN_ALWS, "Start to save stream of inst_%d in %s\n", ChanID, FilePath);
        }
    }
    else if (HI_FALSE == bSaveEnable && *ppFile != HI_NULL)
    {           
        filp_close(*ppFile, HI_NULL);
        *ppFile = HI_NULL;
        SecPrint(PRN_ALWS, "Stop saving stream of inst_%d.\n", ChanID); 
    }
    
    if (*ppFile != HI_NULL)
    {
        HI_SEC_MMZ_TA2CA(PhyAddr, __pa(g_pSaveStreamBuf), Length);
        oldfs = get_fs();
        set_fs(KERNEL_DS);
        (*ppFile)->f_op->write(*ppFile, g_pSaveStreamBuf, Length, &(*ppFile)->f_pos);
        set_fs(oldfs); 
        SecPrint(PRN_ALWS, "Saving stream of inst_%d\n", ChanID);
    }

    return;
}
#endif

HI_S32 TVP_VDEC_GetChanImage( HI_S32 ChanID, IMAGE *pImage )
{
	TEEC_Result result;                                                    
    TEEC_Operation operation;                                              
    HI_U32 phy_addr;
    
#if (1 == PRINT_TEE_TIME)  
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count = 0;
#endif
                   
    Down_Interruptible_with_Option(&g_stSem_s);
    
    if(!g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "%s: TrustedDecoder not creat yet!\n", __func__);
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_ERR;  
    }

    phy_addr = __pa((HI_U32)pImage);                                                       
                                                
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);                                                       

    operation.started = 1;                                                
    operation.params[0].value.a = ChanID;                                    
    operation.params[0].value.b = phy_addr;                   
    
#if (1 == PRINT_TEE_TIME)  
    StartTime = OSAL_GetTimeInUs();
    if (Count == 0)
    {
        BeginTime = StartTime;
    }
#endif

    result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VFMW_GETCHANIMAGE, &operation, HI_NULL, g_TeeDeviceId);
    if (result != TEEC_SUCCESS)                                            
    {  
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VFMW_GETCHANIMAGE Failed!\n");
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_ERR;                                                         
    }
    
#if (1 == PRINT_TEE_TIME)  
    EndTime = OSAL_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;
    
    if (EndTime - BeginTime >= 1000000)
    {
        SecPrint(PRN_ALWS, "GetChanImage Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime/Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }
#endif
    
    Up_Interruptible_with_Option(&g_stSem_s);
    return (operation.params[0].value.a);

}                                


HI_S32 TVP_VDEC_ReleaseChanImage(HI_S32 ChanID, IMAGE *pImage )
{
    TEEC_Result result;                                                    
    TEEC_Operation operation;                                              
    HI_U32 phy_addr;
    
#if (1 == PRINT_TEE_TIME)  
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count = 0;
#endif
             
    Down_Interruptible_with_Option(&g_stSem_s);
    
    if(!g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "%s: TrustedDecoder not creat yet!\n", __func__);
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_ERR; 
    }
    
    phy_addr = __pa((HI_U32)pImage); 
                                                        
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);                                                       

    operation.started = 1;                                                
    operation.params[0].value.a = ChanID;                                    
    operation.params[0].value.b = phy_addr;                    
    
#if (1 == PRINT_TEE_TIME)  
    StartTime = OSAL_GetTimeInUs();
    if (Count == 0)
    {
        BeginTime = StartTime;
    }
#endif

    result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VFMW_RELEASECHANIMAGE, &operation, HI_NULL, g_TeeDeviceId);    
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VFMW_RELEASECHANIMAGE Failed!\n");
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_ERR;                                                         
    }   
	
#if (1 == PRINT_TEE_TIME)  
    EndTime = OSAL_GetTimeInUs();
    TotalTime += EndTime - StartTime;
    Count++;
    
    if (EndTime - BeginTime >= 1000000)
    {
        SecPrint(PRN_ALWS, "ReleaseChanImage Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime/Count);
        TotalTime = BeginTime = StartTime = EndTime = 0;
        Count = 0;
    }
#endif
    
    Up_Interruptible_with_Option(&g_stSem_s);      
    return (operation.params[0].value.a); 
    
}



/************************************************************************
   �ǰ�ȫ���̣߳�����������callback��Ϣ z00241305
 ************************************************************************/
HI_S32 TVP_VDEC_MiddleWare(HI_VOID *pArgs)
{
    HI_S32 NextInstID;
    STREAM_DATA_S *pStrRawPacket;
    TEEC_Operation operation;
    TEEC_Result result; 
    
#if (1 == PRINT_TEE_TIME)  
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count = 0;
#endif

    while(1)
    {
    //SecPrint(PRN_FATAL, "%s:%d\n", __func__, __LINE__);
		switch (g_THREAD_STATE)
	    {
	    case THREAD_RUN:
			break;
			
	    case THREAD_SLEEP:
			goto sleep;
			
	    case THREAD_EXIT:
			goto exit;

		default:;
	    }
    	
        /*������*/
        for( NextInstID=TRUSTED_CHAN_BEGIN; NextInstID < TOTAL_MAX_CHAN_NUM; NextInstID++ )
        {
            if (HI_NULL != g_StreamIntf[NextInstID].read_stream 
		   	    && CHAN_START == g_ChanContext[NextInstID].ChanState)
            {
                Down_Interruptible_with_Option(&g_ChanContext[NextInstID].ChanSema);
                while (1)
                {   
                    if (((g_pStreamBuf[NextInstID].Head_NS+1)%MAX_RAW_NUM) != g_pStreamBuf[NextInstID].Tail_NS)
                    {  
                        pStrRawPacket = &(g_pStreamBuf[NextInstID].RawPacket[g_pStreamBuf[NextInstID].Head_NS]);
                        if(0 == g_StreamIntf[NextInstID].read_stream(g_StreamIntf[NextInstID].stream_provider_inst_id, pStrRawPacket))
                        {
                            //SecPrint(PRN_FATAL, "g_pStreamBuf[%d].Head_S = %d Head_NS = %d \n", \
							//	     NextInstID, g_pStreamBuf[NextInstID].Head_S, g_pStreamBuf[NextInstID].Head_NS);
    		                g_pStreamBuf[NextInstID].Head_NS = (g_pStreamBuf[NextInstID].Head_NS+1) % MAX_RAW_NUM;
                            
                          #if (1 == DEBUG_SAVE_SUPPORT)
                            TVP_VDEC_SaveStream(NextInstID, g_RawSaveEnable, pStrRawPacket->PhyAddr, pStrRawPacket->Length);
                          #endif
                        }
    		            else
    		            {
    		                break;
    		            } 
                    }
    	            else
    	            {
                        break;
    	            }  
                }
                Up_Interruptible_with_Option(&g_ChanContext[NextInstID].ChanSema);
            }
        }
    
#if (1 == PRINT_TEE_TIME)  
        StartTime = OSAL_GetTimeInUs();
        if (Count == 0)
        {
            BeginTime = StartTime;
        }
#endif

        /*���ð�ȫ������̺߳���*/
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_NONE, TEEC_NONE, TEEC_NONE, TEEC_NONE);
        operation.started = 1; 
        result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VFMW_THREADPROC, &operation, HI_NULL, g_TeeDeviceId);
        if (TEEC_SUCCESS != result)
        {
            SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VFMW_THREADPROC Failed!\n");
            return VDEC_ERR;                                                         
        }
  
#if (1 == PRINT_TEE_TIME)       
        EndTime = OSAL_GetTimeInUs();
        TotalTime += EndTime - StartTime;
        Count++;
        
        if (EndTime - BeginTime >= 1000000)
        {
            SecPrint(PRN_ALWS, "THREADPROC Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime/Count);
            TotalTime = BeginTime = StartTime = EndTime = 0;
            Count = 0;
        }
#endif
        /*�ϱ�callback��Ϣ*/
        if (HI_NULL != g_pCallBack)
        {
            while (g_pCallbackBuf->Tail != g_pCallbackBuf->Head)
            { 
                if (g_pCallbackBuf->Message[g_pCallbackBuf->Tail].IsValid)
                {
                    //HI_FATAL_VFMW("Event Pointer:%p\n", (HI_U8 *)g_pCallbackBuf->Message[g_pCallbackBuf->Head].para);
                    
                    g_pCallBack(g_pCallbackBuf->Message[g_pCallbackBuf->Tail].ChanID,
                                g_pCallbackBuf->Message[g_pCallbackBuf->Tail].Type,
                                (HI_U8 *)g_pCallbackBuf->Message[g_pCallbackBuf->Tail].para);
                }
                g_pCallbackBuf->Tail = (g_pCallbackBuf->Tail+1) % MAX_EVENT_NUM;
            }
        }

        /*�ͷ�����*/
        for( NextInstID=TRUSTED_CHAN_BEGIN; NextInstID < TOTAL_MAX_CHAN_NUM; NextInstID++ )
        {
            if(HI_NULL != g_StreamIntf[NextInstID].release_stream 
		   	&& (CHAN_START == g_ChanContext[NextInstID].ChanState))
            {
                Down_Interruptible_with_Option(&g_ChanContext[NextInstID].ChanSema);
                while (1)
                {
                    if (g_pStreamBuf[NextInstID].Tail_NS != g_pStreamBuf[NextInstID].Tail_S)
                    {
                        pStrRawPacket = &(g_pStreamBuf[NextInstID].RawPacket[g_pStreamBuf[NextInstID].Tail_NS]);
                        if(0 == g_StreamIntf[NextInstID].release_stream(g_StreamIntf[NextInstID].stream_provider_inst_id, pStrRawPacket))
                        {
                            //SecPrint(PRN_FATAL, "g_pStreamBuf[%d].Tail_S = %d Tail_NS = %d \n", NextInstID, g_pStreamBuf[NextInstID].Tail_S, g_pStreamBuf[NextInstID].Tail_NS);
                            g_pStreamBuf[NextInstID].Tail_NS = (g_pStreamBuf[NextInstID].Tail_NS+1) % MAX_RAW_NUM;  
                        }
                        else
                        {
                            break;
                        }
                    }
                    else
                    {
                        break;
                    }
                }
                Up_Interruptible_with_Option(&g_ChanContext[NextInstID].ChanSema);
            }
        }
  
sleep:
        OSAL_MSLEEP(10);   
    }
	
exit:
	g_THREAD_STATE = THREAD_INVALID;
	return VDEC_OK;
}	   

/************creat thread*******************/ 
HI_S32 TVP_VDEC_Thread_Init(HI_VOID)
{
    OSAL_TASK pTask;
    
	OSAL_CreateTask(&pTask, "SecVideoDec", TVP_VDEC_MiddleWare);
	if( HI_NULL == pTask)													  
    {	        																	  
		SecPrint(PRN_FATAL, "Creat thread SecVideoDec Failed!\n");
		return VDEC_ERR;					 
	}					 

	g_THREAD_STATE = THREAD_SLEEP;

	return VDEC_OK;
} 

/************reset chan release_stream*******************/ 
HI_S32 TVP_VDEC_Release_Stream(HI_S32 ChanID)
{
    STREAM_DATA_S *pStrRawPacket; 

    /*�廹δ����ȫ���ȡ������*/
    if(HI_NULL != g_StreamIntf[ChanID].release_stream)
    {
        while (1)
        {
            if (g_pStreamBuf[ChanID].Tail_NS != g_pStreamBuf[ChanID].Head_NS)
            {       
                pStrRawPacket = &(g_pStreamBuf[ChanID].RawPacket[g_pStreamBuf[ChanID].Tail_NS]);
                if(0 == g_StreamIntf[ChanID].release_stream(g_StreamIntf[ChanID].stream_provider_inst_id, pStrRawPacket))
                {
                    g_pStreamBuf[ChanID].Tail_NS = (g_pStreamBuf[ChanID].Tail_NS+1) % MAX_RAW_NUM;  
                }
                else
                {
                    break;
                }
            }
            else
            {
                break;
            }
        }
    }
    memset(&g_pStreamBuf[ChanID], 0, sizeof(RAW_ARRAY_NS));

    return VDEC_OK;
}

/********����Ӧͨ����callback��Ϣ******/
HI_S32 TVP_VDEC_Release_Callback(HI_S32 ChanID)
{
    HI_S32 Tail;
    
    Tail = g_pCallbackBuf->Tail;
    while (Tail != g_pCallbackBuf->Head)
    {
        if (ChanID == g_pCallbackBuf->Message[Tail].ChanID)
        {
            g_pCallbackBuf->Message[Tail].IsValid = 0;
        }
        Tail = (Tail+1) % MAX_EVENT_NUM; 
    }
    
    return VDEC_OK;
}

HI_S32 TVP_VDEC_Suspend(HI_VOID)
{
	TEEC_Result result;  
    TEEC_Operation operation;
    HI_S32 ret;
	
    ret = VDEC_Suspend();
    if (ret != VDEC_OK)
    {
        SecPrint(PRN_ERROR, "%s Call VDEC_Suspend Failed!\n", __func__);
        return VDEC_ERR;
    }

	Down_Interruptible_with_Option(&g_stSem_s);
    if(HI_TRUE == g_bSecEnvSetUp)
    {
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    
        operation.started = 1;
        operation.params[0].value.a = 0;
        operation.params[0].value.b = TEEC_VALUE_UNDEF;
    
        result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VDEC_SUSPEND, &operation, HI_NULL, g_TeeDeviceId);
        if (result != TEEC_SUCCESS)
        {
            SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_SUSPEND Failed!\n");
            Up_Interruptible_with_Option(&g_stSem_s);
            return VDEC_ERR;
        }
      
    	g_THREAD_STATE = THREAD_SLEEP;
        ret = operation.params[0].value.a;
    }
    Up_Interruptible_with_Option(&g_stSem_s);
    
    return ret;
}

HI_S32 TVP_VDEC_Resume(HI_VOID)
{
	HI_S32 ret;
	TEEC_Result result;  
    TEEC_Operation operation;
	    
    ret = VDEC_Resume();
    if (ret != VDEC_OK)
    {
        SecPrint(PRN_ERROR, "%s Call VDEC_Resume Failed!\n", __func__);
        return VDEC_ERR;
    }
    
	Down_Interruptible_with_Option(&g_stSem_s);
    if(HI_TRUE == g_bSecEnvSetUp)
    {
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
        
        operation.started = 1;
        operation.params[0].value.a = 0;
        operation.params[0].value.b = TEEC_VALUE_UNDEF;
        
        result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VDEC_RESUME, &operation, HI_NULL, g_TeeDeviceId);
        if (result != TEEC_SUCCESS)
        {
            SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_RESUME Failed!\n");
            Up_Interruptible_with_Option(&g_stSem_s);
            return VDEC_ERR;
        }
        
        g_THREAD_STATE = THREAD_RUN;
        ret = operation.params[0].value.a;
    }
    Up_Interruptible_with_Option(&g_stSem_s);
    
    return ret;
}

HI_S32 TVP_VDEC_SetDbgOption(HI_U32 opt, UINT8* p_args)
{
    return VCTRL_SetDbgOption(opt, p_args); 
}


/************************************************************************
    VDEC��������
    ChanID:  ��Ҫ������ͨ����(����ͨ���޹ز������˲�����Ϊ����ֵ)
    eCmdID:  ������룬ָ����ҪVDECִ�к��ֶ���
    pArgs:   ������������ʽ��eCmdID���
 ************************************************************************/
HI_S32 TVP_VDEC_Control( HI_S32 ChanID, VDEC_CID_E eCmdID, HI_VOID *pArgs )
{
	TEEC_Result result;  
	HI_S32      ret = VDEC_ERR;  
    TEEC_Operation operation;  
    IMAGE_INTF_S *pImgIntf;
    VDEC_CHAN_RESET_OPTION_S *opt;
    HI_U32 phy_addr = 0;
    HI_S32 *vir_addr = NULL;
    HI_S32 *p32 = NULL;
    HI_S32 IsSecFlag = 0;
    
#if (1 == PRINT_TEE_TIME)  
    static HI_U32 BeginTime = 0;
    static HI_U32 StartTime = 0;
    static HI_U32 EndTime = 0;
    static HI_U32 TotalTime = 0;
    static HI_U32 Count = 0;
#endif

    if (VDEC_CID_CREATE_CHAN_WITH_OPTION == eCmdID || VDEC_CID_CREATE_CHAN == eCmdID)
    {
        IsSecFlag = ((VDEC_CHAN_OPTION_S*)((HI_S32*)pArgs)[1])->s32IsSecMode;
    }
    else if(INVALID_HANDLE != ChanID)
    {
        IsSecFlag = g_ChanContext[ChanID].bIsSecMode;
    }

    if (IsSecFlag)
    {
        if (eCmdID != VDEC_CID_GET_CHAN_STATE)
        {
            //SecPrint(PRN_ERROR, "Secure Command: ChanId = %d, CmdID = %d\n", ChanID, eCmdID);
        }
          
        Down_Interruptible_with_Option(&g_stSem_s); 
        
        if(HI_FALSE == g_bSecEnvSetUp)  
        {
            SecPrint(PRN_FATAL, "Trusted Decoder Invalid!!\n");
            Up_Interruptible_with_Option(&g_stSem_s);
            return VDEC_ERR;
        }
        
        phy_addr = __pa((HI_U32)pArgs);
        
        switch(eCmdID)
        {
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:    
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
            p32 = (SINT32*)pArgs;
            vir_addr = (HI_S32 *)p32[1];
            p32[1] = __pa((HI_U32)(&g_pSecVfmwMem->ChanOption));      
            memcpy(&g_pSecVfmwMem->ChanOption, vir_addr, sizeof(VDEC_CHAN_OPTION_S));
            break;       
            
        case VDEC_CID_SET_STREAM_INTF:  /* ����ͨ���������ӿ� */
            if (HI_NULL != pArgs)
            {
                STREAM_LIST_S stStreamList;
                memcpy(&g_StreamIntf[ChanID], (STREAM_INTF_S*)pArgs, sizeof(STREAM_INTF_S));
                stStreamList.stream_list_phy_addr = __pa((HI_U32)g_pStreamBuf); 
                phy_addr = __pa(&stStreamList); 
            }
            else
            {
                SecPrint(PRN_FATAL, "VDEC_CID_SET_STREAM_INTF Invalid Param\n");
                goto Exit_Entry; 
            }
            break;

        case VDEC_CID_GET_IMAGE_INTF:  /* ��ȡͨ����ͼ��ӿ� */
            if (HI_NULL != pArgs)
            {
                pImgIntf = (IMAGE_INTF_S*)pArgs;
                pImgIntf->image_provider_inst_id = ChanID;
                pImgIntf->read_image = TVP_VDEC_GetChanImage;
                pImgIntf->release_image = TVP_VDEC_ReleaseChanImage; 
                ret = VDEC_OK;
            }
            else
            {
                SecPrint(PRN_FATAL, "VDEC_CID_GET_IMAGE_INTF Invalid Param\n");
            }
            goto Exit_Entry; 
            break;
                        
         default:
            break;
        }

        operation.started = 1;  
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_VALUE_INPUT, TEEC_NONE, TEEC_NONE);                                               
        operation.params[0].value.a = ChanID;                                 
        operation.params[0].value.b = eCmdID;
        operation.params[1].value.a = phy_addr;
        operation.params[1].value.b = TEEC_VALUE_UNDEF; 
        
#if (1 == PRINT_TEE_TIME)  
        StartTime = OSAL_GetTimeInUs();
        if (Count == 0)
        {
            BeginTime = StartTime;
        }
#endif
        
        result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VDEC_CONTROL, &operation, HI_NULL, g_TeeDeviceId);
        if (TEEC_SUCCESS != result)                                            
        {
            SecPrint(PRN_FATAL, "TEEC_InvokeCommand VFMW_CMD_ID_VDEC_CONTROL Failed!\n");
            goto Exit_Entry; 
        }   
        
#if (1 == PRINT_TEE_TIME)  
        EndTime = OSAL_GetTimeInUs();
        TotalTime += EndTime - StartTime;
        Count++;
        
        if (EndTime - BeginTime >= 1000000)
        {
            SecPrint(PRN_ALWS, "Control Total: %d, Count: %d, Avg: %d us\n", TotalTime, Count, TotalTime/Count);
            TotalTime = BeginTime = StartTime = EndTime = 0;
            Count = 0;
        }
#endif
        
        ret = operation.params[0].value.a;

        switch(eCmdID)
        {            
        case VDEC_CID_CREATE_CHAN_WITH_OPTION:
            if (VDEC_OK == ret)
            {
                g_ChanContext[p32[0]].ChanID = p32[0];
                g_ChanContext[p32[0]].bIsSecMode = HI_TRUE;
                Sema_Init_with_Option(&g_ChanContext[p32[0]].ChanSema);
                g_SecureInstNum++;
            }
            if (HI_NULL != vir_addr)
            {
                memcpy(vir_addr, &g_pSecVfmwMem->ChanOption, sizeof(VDEC_CHAN_OPTION_S));
                p32[1] = (HI_S32)vir_addr;
            }
            break;
            
        case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
            if (HI_NULL != vir_addr)
            {
                memcpy(vir_addr, &g_pSecVfmwMem->ChanOption, sizeof(VDEC_CHAN_OPTION_S));
                p32[1] = (HI_S32)vir_addr;
            }
            break;

        case VDEC_CID_START_CHAN:
            g_ChanContext[ChanID].ChanState = CHAN_START;
    	    g_THREAD_STATE = THREAD_RUN;
    	    break;
    		
        case VDEC_CID_STOP_CHAN:
            g_ChanContext[ChanID].ChanState = CHAN_STOP;
    	    break;

        case VDEC_CID_DESTROY_CHAN:
        case VDEC_CID_DESTROY_CHAN_WITH_OPTION:
            Down_Interruptible_with_Option(&g_ChanContext[ChanID].ChanSema);
            TVP_VDEC_Release_Callback(ChanID);
            TVP_VDEC_Release_Stream(ChanID);
            
            g_SecureInstNum--;
            if (g_SecureInstNum <= 0)
            {
                g_SecureInstNum = 0;
    	        g_THREAD_STATE = THREAD_SLEEP;
            }
    
            if (g_ChanContext[ChanID].pRawFile != HI_NULL)
            {
                filp_close(g_ChanContext[ChanID].pRawFile, HI_NULL);
                g_ChanContext[ChanID].pRawFile = HI_NULL;
            }
            
            g_ChanContext[ChanID].ChanState = CHAN_INVALID;
            Up_Interruptible_with_Option(&g_ChanContext[ChanID].ChanSema);
    	    break;	    
            
        case VDEC_CID_RESET_CHAN:
            Down_Interruptible_with_Option(&g_ChanContext[ChanID].ChanSema);
            TVP_VDEC_Release_Callback(ChanID);
            TVP_VDEC_Release_Stream(ChanID);
            Up_Interruptible_with_Option(&g_ChanContext[ChanID].ChanSema);
    	    break;	
            
        case VDEC_CID_RESET_CHAN_WITH_OPTION:
            opt = (VDEC_CHAN_RESET_OPTION_S *)pArgs;
            if (opt->s32KeepBS == 0)
            {
                Down_Interruptible_with_Option(&g_ChanContext[ChanID].ChanSema);
                TVP_VDEC_Release_Stream(ChanID);//�ͷŻ�δ����ȫ���ȡ������
                TVP_VDEC_Release_Callback(ChanID);
                Up_Interruptible_with_Option(&g_ChanContext[ChanID].ChanSema);
            }   
            break;      

        default:
            break;
        } 

    Exit_Entry:
        Up_Interruptible_with_Option(&g_stSem_s);
        return ret;
    }
    else
    {
        ret = VDEC_Control(ChanID, eCmdID, pArgs);
        if (ret == VDEC_OK) 
        {
            switch(eCmdID)
            {
            case VDEC_CID_CREATE_CHAN:
            case VDEC_CID_CREATE_CHAN_WITH_OPTION:
                p32 = (SINT32*)pArgs;
                g_ChanContext[p32[0]].ChanID = p32[0];
                g_ChanContext[p32[0]].bIsSecMode = HI_FALSE;
                break;
            case VDEC_CID_START_CHAN:
                g_ChanContext[ChanID].ChanState = CHAN_START;
                break;
            case VDEC_CID_STOP_CHAN:
                g_ChanContext[ChanID].ChanState = CHAN_STOP;
                break;
            case VDEC_CID_DESTROY_CHAN:
            case VDEC_CID_DESTROY_CHAN_WITH_OPTION:
                g_ChanContext[ChanID].ChanState = CHAN_INVALID;
                break;

            default:
                break;
            }
        }
        
        return ret;
    }
    
    
}
 
#ifndef  HI_ADVCA_FUNCTION_RELEASE
static inline HI_S32 TVP_VDEC_String2Value(HI_PCHAR str, HI_U32 *data)
{
    HI_U32 i, d, dat, weight;

    dat = 0;
    if(str[0] == '0' && (str[1] == 'x' || str[1] == 'X'))
    {
        i = 2;
        weight = 16;
    }
    else
    {
        i = 0;
        weight = 10;
    }
    
    for(; i < 10; i++)
    {
        if(str[i] < 0x20)
        {
            break;
        }
        else if (weight == 16 && str[i] >= 'a' && str[i] <= 'f')
        {
            d = str[i] - 'a' + 10;
        }
        else if (weight == 16 && str[i] >= 'A' && str[i] <= 'F')
        {
            d = str[i] - 'A' + 10;
        }
        else if (str[i] >= '0' && str[i] <= '9')
        {
            d = str[i] - '0';
        }
        else
        {
            return -1;
        }
    
        dat = dat * weight + d;
    }
    
    *data = dat;
    
    return 0;
}

HI_VOID TVP_VDEC_HelpProc(HI_VOID)
{
HI_DRV_PROC_EchoHelper("\n"
    "================= SEC_VFMW HELP =================\n"
    "USAGE:echo [cmd] [para] >/proc/sec_vfmw\n"
    "  help,     [not_care]    :read help infomation\n"
    "  saveraw,  [start/stop]  :enable/disable raw save,debug only\n"
    "  saveyuv,  [start/stop]  :enable/disable yuv save,debug only\n"
    "\n");
HI_DRV_PROC_EchoHelper(""
    "Further command avalible in trusted decoder:\n"
    "  0x0,      [print_word]  :set print enable word\n"
    "  0x2,      [0~100]       :set err thr\n"
    "  0x4,      [0/1]         :set output order(0/1=DISP/DEC)\n"
    "  0x5,      [0/1/2]       :set dec mode(0/1/2=IPB/IP/I)\n"
    "  0x7,      [0~100]       :set discard before dec thr\n");
HI_DRV_PROC_EchoHelper(""
    "  0xb,      [0/1]         :set frame/adaptive(0/1) storage\n"
    "  0xd,      [8~15]        :set to abserve specify channel\n"
    "  0x400,    [ms]          :set dec task schedule delay\n"
    "  0x402,    [0/1]         :start/stop syntax proccess\n"
    "  0x501,    [ms]          :set scd state period\n"
    "  0x502,    [ms]          :set vdh state period\n"
    "  0x503,    [ms]          :set rcv/rls frame period\n"
    "=================================================\n"
    "\n");

	return;
}

HI_S32 TVP_VDEC_ParamProccess(const HI_S8 __user *buffer, size_t count, HI_U32 *p_option, HI_U32 *p_value)
{  
    HI_S32  i,j;
    HI_S32  ret = HI_FAILURE;
    HI_CHAR buf[PROC_CMD_LEN*2];
    HI_CHAR str1[PROC_CMD_LEN];
    HI_CHAR str2[PROC_CMD_LEN];

    if(count < 1 || count >= sizeof(buf)) 
    {
        SecPrint(PRN_ALWS, "Parameter count(%d) Invalid!\n", count);
        return HI_FAILURE;
    }

    memset(buf, 0, sizeof(buf));
    if (copy_from_user(buf, buffer, count))
    {
        SecPrint(PRN_ALWS, "Copy from user Failed!\n"); 
        return HI_FAILURE;
    }
    buf[count] = 0;

    /* 1.��ȡ����1 */
    i = 0;
    j = 0;
    for(; i < count; i++)
    {
        if(j==0 && buf[i]==' ')
        {
            continue;
        }
        if(buf[i] > ' ')
        {
            str1[j++] = buf[i];
        }
        if(j>0 && buf[i]==' ')
        {
            break;
        }
    }
    str1[j] = 0;
            
    /* 2.��ȡ����2 */
    j = 0;
    for(; i < count; i++)
    {
        if(j==0 && buf[i]==' ')
        {
            continue;
        }
        if(buf[i] > ' ')
        {
            str2[j++] = buf[i];
        }
        if(j>0 && buf[i]==' ')
        {
            break;
        }
    }
    str2[j] = 0;

    /* 3.�����ж� */
	if (!HI_OSAL_Strncmp(str1, PROC_CMD_HELP, PROC_CMD_LEN))
    {
        TVP_VDEC_HelpProc();
    }
  #if (1 == DEBUG_SAVE_SUPPORT)
    else if (!HI_OSAL_Strncmp(str1, PROC_CMD_SAVERAW, PROC_CMD_LEN))
    {
        if (!HI_OSAL_Strncmp(str2, PROC_CMD_START, PROC_CMD_LEN))
        {
            SecPrint(PRN_ALWS, "Enable Raw Stream Save.\n"); 
            g_RawSaveEnable = HI_TRUE;
        }
        else if (!HI_OSAL_Strncmp(str2, PROC_CMD_STOP, PROC_CMD_LEN))
        {
            SecPrint(PRN_ALWS, "Disable Raw Stream Save.\n"); 
            g_RawSaveEnable = HI_FALSE;
        }
    }
  #endif
	else
	{
        /*ת������1*/
        if(TVP_VDEC_String2Value(str1, p_option) != 0)
        {
            SecPrint(PRN_ALWS, "Unknown param %s\n", str1); 
        }
        /*ת������2*/
        else if(TVP_VDEC_String2Value(str2, p_value) != 0)
        {
            SecPrint(PRN_ALWS, "Unknown param %s\n", str2);
        }
        /*������������Ч*/
        else
        {
            switch (*p_option)
            {
            case PROC_CMD_SETPRINT:
                g_SecPrintEnable = *p_value;
                SecPrint(PRN_ALWS, "SecPrintEnable = 0x%x\n", g_SecPrintEnable);
                break;
                
            default: /*Ĭ�ϲ�������ͨ��TEE����*/
                if (HI_FALSE == g_bSecEnvSetUp)
                {
                    SecPrint(PRN_ALWS, "Trusted decoder NOT create yet!\n");
                }
                break;
            } 

            /*��ȫ��������Чʱ�ŷ���HI_SUCCESS*/
            if (HI_TRUE == g_bSecEnvSetUp)
            {
                ret = HI_SUCCESS;
            }
        }
	}
    
    return ret;
}

HI_S32 TVP_VDEC_SendProcCommand(HI_U32 option, HI_U32 value)
{
    TEEC_Result result; 
    TEEC_Operation operation;
    
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;                                                
    operation.params[0].value.a = option;                                 
    operation.params[0].value.b = value;
    
    result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VFMW_WRITEPROC, &operation, HI_NULL, g_TeeDeviceId);
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_ALWS, "InvokeCommand VFMW_CMD_ID_VFMW_WRITEPROC Failed!\n");
        return VDEC_ERR;
    }
    
    return operation.params[0].value.a;
}

static HI_S32 TVP_VDEC_ReadProc(struct seq_file *p, HI_VOID *v)
{
    HI_U32 i;
    TEEC_Result result;  
    TEEC_Operation operation;
    HI_S32 ret_len = 0;
	HI_S8 *proc_buf = (HI_S8 *)(g_pProcBuf);

    Down_Interruptible_with_Option(&g_stSem_s);
    
    //��û����������֮ǰӦ�������ѯ������Ϣ
    PROC_PRINT(p, "\n");
    PROC_PRINT(p, "======================= Global Info ========================\n");
    PROC_PRINT(p, "Version            :%-5s  \n", SEC_VFMW_VERSION);
    PROC_PRINT(p, "SecEnvSetUp        :%-5d  | SecPrintEnable        :0x%-5x\n", g_bSecEnvSetUp,  g_SecPrintEnable);
    PROC_PRINT(p, "ThreadState        :%-5d  | VfmwMemPhyAddr        :0x%-5x\n", g_THREAD_STATE,  g_SecVfmwMem.PhyAddr);
    PROC_PRINT(p, "SecureInstNum      :%-5d  | VfmwMemLength         :%d\n",     g_SecureInstNum, g_SecVfmwMem.Length);
  #if (1 == DEBUG_SAVE_SUPPORT)
    PROC_PRINT(p, "RawSaveEnable      :%-5d  | SavePath              :%s\n",     g_RawSaveEnable, g_SavePath);
  #endif
    PROC_PRINT(p, "\n");
    
    for (i=0; i<TOTAL_MAX_CHAN_NUM; i++)
    {
        if (g_ChanContext[i].ChanState != CHAN_INVALID)
        {
    		PROC_PRINT(p, "ChanID             :%-5d  \n", i);
    		PROC_PRINT(p, "State              :%-5d  | SecMode               :%d\n", g_ChanContext[i].ChanState, g_ChanContext[i].bIsSecMode);
            if (HI_TRUE == g_ChanContext[i].bIsSecMode)
            {
    			PROC_PRINT(p, "StreamList         :%d/%d (%d,%d,%d,%d)\n", 
                                                             (g_pStreamBuf[i].Head_S-g_pStreamBuf[i].Tail_S+MAX_RAW_NUM)%MAX_RAW_NUM,
                                                             (g_pStreamBuf[i].Head_NS-g_pStreamBuf[i].Tail_NS+MAX_RAW_NUM)%MAX_RAW_NUM, 
                                                              g_pStreamBuf[i].Head_S, g_pStreamBuf[i].Tail_S, g_pStreamBuf[i].Head_NS, g_pStreamBuf[i].Tail_NS);
            }
    		PROC_PRINT(p, "\n");
        }
    }

    if (g_bSecEnvSetUp && g_SecureInstNum > 0)
    {
        operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
        operation.started = 1;                                                
        operation.params[0].value.a = __pa((HI_U32)g_pProcBuf);                                 
        operation.params[0].value.b = MAX_PROC_SIZE;
        
        result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VFMW_READPROC, &operation, HI_NULL, g_TeeDeviceId);
        if (result != TEEC_SUCCESS)
        {
            SecPrint(PRN_ALWS, "InvokeCommand VFMW_CMD_ID_VFMW_READPROC Failed!\n");
            Up_Interruptible_with_Option(&g_stSem_s);
            return VDEC_ERR;
        }
    	PROC_PRINT(p, proc_buf);
    }
    PROC_PRINT(p, "============================================================\n");
    
    Up_Interruptible_with_Option(&g_stSem_s);
	SecPrint(PRN_ALWS, "enter read proc SUCCESS!\n");

	return 0;
}

HI_S32 TVP_VDEC_WriteProc(struct file *file, const char __user *buffer, unsigned long count, void *data)
{
    HI_U32 option, value;
    HI_S32 ret;
    SecPrint(PRN_ALWS, "enter write proc!\n");

    Down_Interruptible_with_Option(&g_stSem_s);
    
	ret = TVP_VDEC_ParamProccess(buffer, count, &option, &value);
	if (HI_SUCCESS != ret)
	{
        Up_Interruptible_with_Option(&g_stSem_s);
        return count;
	}
    
    if(HI_TRUE == g_bSecEnvSetUp)
    {
        ret = TVP_VDEC_SendProcCommand(option, value);
        if (HI_SUCCESS != ret)
        {
            SecPrint(PRN_ALWS, "Invalid CMD(%d %d), refer to help.\n", option, value);
            TVP_VDEC_HelpProc();
        }
    }
    
    Up_Interruptible_with_Option(&g_stSem_s);
    SecPrint(PRN_ALWS, "enter write proc SUCCESS!\n");	
    return count;
}
#endif

HI_VOID TVP_VDEC_ContextInit(HI_VOID)
{
    /*ȫ��ָ���ʼ��*/
    g_pSecVfmwMem         = HI_NULL;
    g_pCallbackBuf        = HI_NULL;
    g_pStreamBuf          = HI_NULL; 
    g_pCallBack           = HI_NULL;
#if (1 == DEBUG_SAVE_SUPPORT)
    g_pSaveStreamBuf      = HI_NULL;
#endif
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    g_pProcBuf            = HI_NULL;
#endif
    
    /*��̬ȫ�ֱ�����ʼ��*/
    g_SecureInstNum       = 0;
    g_TrustDecoderInitCnt = 0;
    g_bSecEnvSetUp        = HI_FALSE;
    g_THREAD_STATE        = THREAD_INVALID;
    
    /*ȫ�ֽṹ���ʼ��*/
    memset(&g_SecVfmwMem, 0, sizeof(MEM_DESC_S));
    memset(g_StreamIntf,  0, sizeof(STREAM_INTF_S)*TOTAL_MAX_CHAN_NUM);

    //��Ϊ����ṹ��ͷǰ�ͨ����أ���Ӧ�÷��������ʼ��
    //memset(g_ChanContext, 0, sizeof(CHAN_CONTEXT_S)*TOTAL_MAX_CHAN_NUM);
}

HI_S32 TVP_VDEC_TrustDecoderInit(VDEC_OPERATION_S *pArgs)
{
	TEEC_Result result;  
    TEEC_Operation operation;
    TEEC_UUID svc_id = {0x79b77788, 0x9789, 0x4a7a,
                        {0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf4}    
                       };
    HI_U32 phy_addr = 0;
    VDEC_OPERATION_S stInitArgs;
    HI_S32 ret;
	
    SecPrint(PRN_ERROR, "%s Enter\n", __func__);
    
    Down_Interruptible_with_Option(&g_stSem_s);
    
    if (HI_NULL == pArgs || HI_NULL == pArgs->VdecCallback)
    {
        SecPrint(PRN_FATAL, "%s: Param Invalid!\n", __func__);
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_ERR;
    }
    
    if (HI_TRUE == g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "TrustedDecoder already init(%d), return OK.\n", g_TrustDecoderInitCnt);
        g_TrustDecoderInitCnt++;
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_OK;
    }

    /* 1. ����ͨ�Ż��� */                                                   
    result = TEEC_InitializeContext(HI_NULL, &g_TeeContext, &g_TeeDeviceId);
    if(result != TEEC_SUCCESS) 
    {
        SecPrint(PRN_FATAL, "TEEC_InitializeContext Failed!\n");
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_ERR;
    }
    
    /* 2. �����Ự*/
    result = TEEC_OpenSession(&g_TeeContext, &g_TeeSession, &svc_id, TEEC_LOGIN_PUBLIC, HI_NULL, HI_NULL, HI_NULL, g_TeeDeviceId);
    if(result != TEEC_SUCCESS) 
    {
        SecPrint(PRN_FATAL, "TEEC_OpenSession Failed!\n");
        TEEC_FinalizeContext(&g_TeeContext, g_TeeDeviceId);
        goto InitWithfree_0;
    }
    
    /* 3. ��ʼ��ȫ����Ϣ*/
    TVP_VDEC_ContextInit();
       
    /* 4. �����ڴ棬ȫ����Ϣ��ֵ*/ 
    ret = KernelMemMalloc("Sec Vfmw Buffer", sizeof(MEMORY_NEEDED_SECVFMW_S), 4, 1, &g_SecVfmwMem);
    if (ret != HI_SUCCESS)
    {
        SecPrint(PRN_FATAL, "Alloc Sec Vfmw Buffer Failed!\n");
        goto InitWithfree_1;
    }
    memset(g_SecVfmwMem.VirAddr, 0, sizeof(MEMORY_NEEDED_SECVFMW_S));
    g_pSecVfmwMem  = (MEMORY_NEEDED_SECVFMW_S *) g_SecVfmwMem.VirAddr;
    g_pCallbackBuf = (CALLBACK_ARRAY_NS *)(&g_pSecVfmwMem->CallBackBuf);
    g_pStreamBuf   = (RAW_ARRAY_NS *)(g_pSecVfmwMem->StreamBuf);
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    g_pProcBuf     = (HI_U8 *)(g_pSecVfmwMem->ProcBuf);
#endif
#if (1 == DEBUG_SAVE_SUPPORT) 
    g_pSaveStreamBuf = (HI_U8 *)(g_pSecVfmwMem->SaveStreamBuf);
#endif
    
    SecPrint(PRN_ERROR, "SecVfmwMem  = 0x%x, Len = 0x%x\n", g_SecVfmwMem.PhyAddr, g_SecVfmwMem.Length);
    SecPrint(PRN_ERROR, "StreamBuf   = 0x%x, Len = 0x%x\n", __pa((HI_U32)g_pStreamBuf),   sizeof(RAW_ARRAY_NS)*TOTAL_MAX_CHAN_NUM);
    SecPrint(PRN_ERROR, "CallbackBuf = 0x%x, Len = 0x%x\n", __pa((HI_U32)g_pCallbackBuf), sizeof(CALLBACK_ARRAY_NS));
#ifndef  HI_ADVCA_FUNCTION_RELEASE
    SecPrint(PRN_ERROR, "ProcBuf     = 0x%x, Len = 0x%x\n", __pa((HI_U32)g_pProcBuf),     MAX_PROC_SIZE);
#endif
	
    memcpy(&stInitArgs, pArgs, sizeof(VDEC_OPERATION_S));
    stInitArgs.VdecCallback = (HI_VOID *)(__pa((HI_U32)g_pCallbackBuf));
    printk("stInitArgs.eAdapterType=%d, stInitArgs.VdecCallback=%p\n", stInitArgs.eAdapterType, stInitArgs.VdecCallback);
    phy_addr = __pa((HI_U32)(&stInitArgs));
    g_pCallBack = pArgs->VdecCallback;

	SecPrint(PRN_FATAL, "%s g_SecPrintEnable:%d \n", __func__, g_SecPrintEnable);

    /* 5. ͬ����ȫ��ӡ������*/
    ret = TVP_VDEC_SendProcCommand(PROC_CMD_SETPRINT, g_SecPrintEnable);
    if (HI_SUCCESS != ret)
    {
        SecPrint(PRN_ERROR, "Init proc SecPrintEnable(%d) Failed!\n", g_SecPrintEnable);
        goto InitWithfree_2;  
    }

    /* 6. ���ð�ȫ���ʼ���ӿ�*/
	operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_INOUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;                                                
    operation.params[0].value.a = phy_addr;                       
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
                                                                     
    result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VDEC_INITWITHOPERATION, &operation, HI_NULL, g_TeeDeviceId); 

    if (result != TEEC_SUCCESS || operation.params[0].value.a != VDEC_OK)                                            
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_INITWITHOPERATION failed, result_val=%d\n", operation.params[0].value.a);
        goto InitWithfree_2;                                                         
    }

    /* 7. ������ȫ�����߳�*/
    ret = TVP_VDEC_Thread_Init();
    if (ret != VDEC_OK)
    {
        SecPrint(PRN_FATAL, "Call VDEC_Thread_Init() Failed!\n");
        goto InitWithfree_3;
    }

    g_TrustDecoderInitCnt = 1;
    g_bSecEnvSetUp = HI_TRUE;
    
    SecPrint(PRN_ERROR, "TrustedDecoder init Success.\n");
    
    Up_Interruptible_with_Option(&g_stSem_s);     
    return VDEC_OK; 
    
InitWithfree_3:
    //���ð�ȫ��ȥ��ʼ������
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].value.a = 0;
    operation.params[0].value.b = TEEC_VALUE_UNDEF;
    TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VDEC_EXIT, &operation, HI_NULL, g_TeeDeviceId); 
InitWithfree_2:
    KernelMemFree(&g_SecVfmwMem);
    TVP_VDEC_ContextInit();
InitWithfree_1:
    TEEC_CloseSession(&g_TeeSession, g_TeeDeviceId);
InitWithfree_0:
    //��Ϊclose����finalize�ᵼ�¹�����������δ������ȹ�ܣ�ֻ��close����
    //TEEC_FinalizeContext(&g_TeeContext, g_TeeDeviceId); 
    
    Up_Interruptible_with_Option(&g_stSem_s);
    return VDEC_ERR;
    
}

HI_S32 TVP_VDEC_TrustDecoderExit(HI_VOID)
{
    HI_U32 i = 0;
	TEEC_Result result;
    TEEC_Operation operation;
    HI_S32 ret;
	
    SecPrint(PRN_ERROR, "%s Enter\n", __func__);
    
	Down_Interruptible_with_Option(&g_stSem_s);
	
    if(HI_FALSE == g_bSecEnvSetUp)
    {
        SecPrint(PRN_ERROR, "TrustedDecoder not init, return OK.\n");
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_OK;
    }

    if (g_SecureInstNum > 0)
    {
        SecPrint(PRN_ERROR, "SecureInstNum(%d) > 0, return OK.\n", g_SecureInstNum);
        Up_Interruptible_with_Option(&g_stSem_s);
        return VDEC_OK;
    }
    
	g_THREAD_STATE = THREAD_EXIT;
    for (i=0; i<50; i++)
    {
        if (THREAD_INVALID == g_THREAD_STATE)
        {
            break;
        }
        else
        {
	        OSAL_MSLEEP(10); 
        }
    }  
    
    operation.paramTypes = TEEC_PARAM_TYPES(TEEC_VALUE_OUTPUT, TEEC_NONE, TEEC_NONE, TEEC_NONE);
    operation.started = 1;
    operation.params[0].value.a = 0;
    operation.params[0].value.b = TEEC_VALUE_UNDEF;

    result = TEEC_InvokeCommand(&g_TeeSession, VFMW_CMD_ID_VDEC_EXIT, &operation, HI_NULL, g_TeeDeviceId); 
    if (result != TEEC_SUCCESS)
    {
        SecPrint(PRN_FATAL, "InvokeCommand VFMW_CMD_ID_VDEC_EXIT Failed!\n");
    }

    /*�ر�VFMW��TEECͨ��*/
    TEEC_CloseSession(&g_TeeSession, g_TeeDeviceId);
    // ��Ϊclose����finalize�ᵼ�¹�����������δ������ȹ�ܣ�ֻ��close����
    //TEEC_FinalizeContext(&g_TeeContext, g_TeeDeviceId);

    KernelMemFree(&g_SecVfmwMem);
        
    g_TrustDecoderInitCnt = 0;
	g_bSecEnvSetUp = HI_FALSE;

    ret = operation.params[0].value.a;

    SecPrint(PRN_ERROR, "TrustedDecoder deinit Success.\n");

    Up_Interruptible_with_Option(&g_stSem_s);
    return ret; 
}

HI_S32 TVP_VDEC_Init(HI_S32 (*VdecCallback)(HI_S32, HI_S32, HI_VOID*))
{
    SecPrint(PRN_ERROR, "%s Enter\n", __func__);
    memset(g_ChanContext, 0, sizeof(CHAN_CONTEXT_S)*TOTAL_MAX_CHAN_NUM);
    return VDEC_Init(VdecCallback);
}

HI_S32 TVP_VDEC_InitWithOperation(VDEC_OPERATION_S *pArgs)
{
    SecPrint(PRN_ERROR, "%s Enter\n", __func__);
    memset(g_ChanContext, 0, sizeof(CHAN_CONTEXT_S)*TOTAL_MAX_CHAN_NUM);
    return VDEC_InitWithOperation(pArgs);
}

HI_S32 TVP_VDEC_Exit(HI_VOID)
{
    SecPrint(PRN_ERROR, "%s Enter\n", __func__);
    return VDEC_Exit();
}

HI_S32 TVP_VDEC_init_proc (HI_VOID)
{
    HI_CHAR aszBuf[16];
    DRV_PROC_ITEM_S *pstItem;

    /* Create proc */
    snprintf(aszBuf, sizeof(aszBuf), PROC_NAME);
    pstItem = HI_DRV_PROC_AddModule(aszBuf, HI_NULL, HI_NULL);
    if (!pstItem)
    {
        SecPrint(PRN_ALWS, "Create TVP VDEC proc entry fail!\n");
        return HI_FAILURE;
    }

    /* Set functions */
    pstItem->read  = TVP_VDEC_ReadProc;
    pstItem->write = TVP_VDEC_WriteProc;

    SecPrint(PRN_ALWS, "Create TVP VDEC proc entry SUCCESS!\n");

	return HI_SUCCESS;
}

HI_VOID TVP_VDEC_exit_proc(HI_VOID)
{
    HI_CHAR aszBuf[16];

    snprintf(aszBuf, sizeof(aszBuf), PROC_NAME);
    HI_DRV_PROC_RemoveModule(aszBuf);

    return;
}

/************************************************************************
  ��/�˳�VDEC���: ��insmod/rmmodʱ�������º�����
  ��Ҫְ���Ǵ���/����proc�ļ�ϵͳ
************************************************************************/
HI_VOID TVP_VDEC_OpenModule(HI_VOID)
{	
	HI_S32 ret = 0;
#ifndef  HI_ADVCA_FUNCTION_RELEASE

	ret = TVP_VDEC_init_proc();
/*
    struct proc_dir_entry *p;
    
    p = create_proc_entry(PROC_NAME, 0644, HI_NULL); 
    if(HI_NULL == p)
    {
        SecPrint(PRN_ALWS, "Create proc %s Failed!\n", PROC_NAME);
    	return;
    }
    
    p->read_proc = TVP_VDEC_ReadProc;
    p->write_proc = TVP_VDEC_WriteProc;
*/   
#endif

    Sema_Init_with_Option(&g_stSem_s);  

	return;
	
}

HI_VOID TVP_VDEC_ExitModule(HI_VOID)
{   
#ifndef  HI_ADVCA_FUNCTION_RELEASE
	TVP_VDEC_exit_proc();
	//remove_proc_entry(PROC_NAME, HI_NULL);
#endif

    return;
}

 
