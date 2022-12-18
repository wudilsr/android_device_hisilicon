#include "tee_common.h"
#include "tee_internal_api.h"
#include "tee_mem_mgmt_api.h"
#define TA_DEBUG
#include "tee_log.h"
#include "tee_fs.h"
#include "tee_trusted_storage_api.h"
#include "tee_time_api.h"

#include <sre_syscalls_ext.h>

typedef enum 
{
    VFMW_CMD_ID_INVALID = 0x0,
    VFMW_CMD_ID_VDEC_INIT,               // 1 
    VFMW_CMD_ID_VDEC_EXIT,               // 2 
    VFMW_CMD_ID_VDEC_RESUME,             // 3
    VFMW_CMD_ID_VDEC_SUSPEND,            // 4
    VFMW_CMD_ID_VDEC_CONTROL,              // 5
    VFMW_CMD_ID_VFMW_READPROC,             // 6
    VFMW_CMD_ID_VFMW_WRITEPROC,            // 7
    VFMW_CMD_ID_VFMW_THREADPROC,         // 8
    VFMW_CMD_ID_VCTRL_SETDBGOPTION,      // 9
    VFMW_CMD_ID_VFMW_GETCHANIMAGE,       // 10
    VFMW_CMD_ID_VFMW_RELEASECHANIMAGE,      // 11
    VFMW_CMD_ID_VDEC_INITWITHOPERATION,     // 12
} VFMW_CMD_ID;

TEE_Result TA_vfmw_VDEC_Suspend(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VDEC_Suspend();
	
    return TEE_SUCCESS;
}

TEE_Result TA_vfmw_vdec_init(uint32_t paramTypes, TEE_Param params[4])
{

    params[0].value.a = __VDEC_Init(params[0].value.a);
    
    return TEE_SUCCESS;
}

TEE_Result TA_vfmw_VDEC_Resume(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VDEC_Resume();
	
    return TEE_SUCCESS;

}

TEE_Result TA_VCTRL_thread_proc(uint32_t paramTypes, TEE_Param params[4])
{
    __VFMW_CTRL_thread_sec(); 
	//ta_debug("exit!\n");

    return TEE_SUCCESS;  
}

TEE_Result TA_vfmw_vdec_control(uint32_t paramTypes, TEE_Param params[4])
{
    //ta_debug("Enter:%d; %d\n",params[0].value.a, params[0].value.b);
    params[0].value.a = __VDEC_Control(params[0].value.a, params[0].value.b, params[1].value.a);
    //ta_debug("Exit ret:%d\n",params[0].value.a); 
    return TEE_SUCCESS;
}

TEE_Result TA_vfmw_VDEC_InitWithOperation(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VDEC_InitWithOperation(params[0].value.a);
	//ta_debug("TA_ret = %d\n",params[0].value.a);
    return TEE_SUCCESS;
}

TEE_Result TA_VCTRL_WriteProc(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VCTRL_WriteProc(params[0].value.a, params[0].value.b);
    
    return TEE_SUCCESS;
}

TEE_Result TA_VCTRL_ReadProc(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VCTRL_ReadProc(params[0].value.a, params[0].value.b);
	
    return TEE_SUCCESS;
}

TEE_Result  TA_VCTRL_SetDbgOption(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VCTRL_SetDbgOption(params[0].value.a, params[0].value.b);
   
    return TEE_SUCCESS;
}

TEE_Result  TA_VCTRL_GetChanImage(uint32_t paramTypes, TEE_Param params[4])
{
	//ta_debug("Enter params[0].value.a:%d, params[0].value.b:%d \n", params[0].value.a, params[0].value.b);
    params[0].value.a = __VCTRL_GetChanImage(params[0].value.a, params[0].value.b);
	//ta_debug("Exit ret = %d\n", params[0].value.a);	
    return TEE_SUCCESS;
}

TEE_Result  TA_VCTRL_ReleaseChanImage(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VCTRL_ReleaseChanImage(params[0].value.a, params[0].value.b);
    
    return TEE_SUCCESS;
}

TEE_Result TA_VDEC_Exit(uint32_t paramTypes, TEE_Param params[4])
{
    params[0].value.a = __VDEC_Exit();
    
    return TEE_SUCCESS;   
}

TEE_Result TA_CreateEntryPoint(void)
{
    TEE_Result ret=TEE_SUCCESS;
    return ret;
}


TEE_Result TA_OpenSessionEntryPoint(uint32_t paramTypes, TEE_Param params[4], void** sessionContext)
{
    TEE_Result ret=TEE_SUCCESS;
    return ret;
}

TEE_Result TA_InvokeCommandEntryPoint(void* session_context, uint32_t cmd_id, uint32_t paramTypes, TEE_Param params[4])
{
    TEE_Result ret=TEE_SUCCESS;
    //ta_debug("cmd_id = %d\n",cmd_id);

    switch (cmd_id) 
    {
    case  VFMW_CMD_ID_VDEC_SUSPEND:
          TA_vfmw_VDEC_Suspend(paramTypes, params);
          break;
    
    case  VFMW_CMD_ID_VDEC_INIT:
          TA_vfmw_vdec_init(paramTypes, params);
          break;
          
    case  VFMW_CMD_ID_VDEC_RESUME:
          TA_vfmw_VDEC_Resume(paramTypes, params);
          break;

    case  VFMW_CMD_ID_VFMW_THREADPROC:
          TA_VCTRL_thread_proc(paramTypes, params);
	  //    ta_debug("TA_VCTRL_thread_proc\n");
		  
          break;
                   
    case  VFMW_CMD_ID_VDEC_CONTROL:
          TA_vfmw_vdec_control(paramTypes, params);
          break;
           
    case  VFMW_CMD_ID_VDEC_INITWITHOPERATION:
          TA_vfmw_VDEC_InitWithOperation(paramTypes, params);
          break;
          
    case  VFMW_CMD_ID_VFMW_WRITEPROC:
          TA_VCTRL_WriteProc(paramTypes, params);
          break;
         
    case  VFMW_CMD_ID_VFMW_READPROC:
          TA_VCTRL_ReadProc(paramTypes, params);
          break;
          
    case  VFMW_CMD_ID_VCTRL_SETDBGOPTION:
          TA_VCTRL_SetDbgOption(paramTypes, params);
          break;
          
    case  VFMW_CMD_ID_VFMW_GETCHANIMAGE:
          TA_VCTRL_GetChanImage(paramTypes, params);
          break;
          
    case  VFMW_CMD_ID_VFMW_RELEASECHANIMAGE:
          TA_VCTRL_ReleaseChanImage(paramTypes, params);
          break;
                
    case  VFMW_CMD_ID_VDEC_EXIT:
          TA_VDEC_Exit(paramTypes, params);
          break;
          
    default:
          break;
    }
  
    return  ret;
}

void TA_CloseSessionEntryPoint(void* session_context)
{
    ta_debug("VFMW Session Close!\n");
}

void TA_DestroyEntryPoint(void)
{
    ta_debug("VFMW Context Close!\n");
}
