/*
 * Copyright (c) (2014 - ...) Device Chipset Source Algorithm and Chipset Platform Development Dept
 * Hisilicon. All rights reserved.
 *
 * File:    task.c
 *
 * Purpose: omxvdec task functions
 *
 * Author:  yangyichang 00226912
 *
 * Date:    26, 11, 2014
 *
 */

 
#include "task.h"
#include "channel.h"


/*================ EXTERN VALUE ================*/
extern HI_U32   g_DispNum;


/*============== INTERNAL FUNCTION =============*/
static inline const HI_PCHAR task_show_state(eTASK_STATE state)
{
	switch (state)
    {
       case TASK_STATE_INVALID:
            return "invalid";
            break;
    
       case TASK_STATE_SLEEPING:
            return "sleeping";
            break;
    
       case TASK_STATE_ONCALL:
            return "oncall";
            break;
            
       case TASK_STATE_RUNNING:
            return "running";
            break;
    
       default:
            return "unkown";
            break;
	}
}

static HI_S32 task_alloc_channel_mem(OMXVDEC_CHAN_CTX *pchan)
{		
    HI_S32 ret = HI_FAILURE;
    HI_U32 u32DoneTime = 0;
    VDEC_CHAN_FRAME_STORE_PARAM_S stFsParam;
    HI_U32 u32NeededMemSize  = 0;
    HI_U32 u32NeededFrameNum = 0;

    if (pchan->decoder_vdh_buf.u32Size != 0 && pchan->decoder_vdh_buf.u32StartPhyAddr != 0)
    {
        omxvdec_release_mem(&pchan->decoder_vdh_buf);
    }

    u32NeededFrameNum = pchan->ref_frame_num + g_DispNum;
    u32NeededMemSize  = pchan->ref_frame_size * u32NeededFrameNum;

	ret = HI_DRV_MMZ_AllocAndMap("OMXVDEC_DFS", "OMXVDEC", u32NeededMemSize, 0, &pchan->decoder_vdh_buf);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "Alloc DFS Mem(size = %d) failed!\n", u32NeededMemSize);
        ret = HI_FAILURE;
        goto exit;
    }

	stFsParam.PhyAddr  = pchan->decoder_vdh_buf.u32StartPhyAddr;
    stFsParam.VirAddr  = pchan->decoder_vdh_buf.u32StartVirAddr;
    stFsParam.Length   = pchan->decoder_vdh_buf.u32Size;
    stFsParam.FrameNum = u32NeededFrameNum;
    stFsParam.NeedMMZ  = 1;

    ret = VDEC_Control(pchan->decoder_id, VDEC_CID_ALLOC_MEM_TO_CHANNEL, (HI_VOID*)&stFsParam);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "Call VDEC_CID_ALLOC_MEM_TO_CHANNEL failed!\n");
        omxvdec_release_mem(&pchan->decoder_vdh_buf);
        ret = HI_FAILURE;
        goto exit;
    }

    HI_DRV_SYS_GetTimeStampMs(&u32DoneTime);
    pchan->dfs_delay_time = u32DoneTime - pchan->dfs_delay_time;

exit:
    pchan->dfs_alloc_flag = DFS_ALREADY_ALLOC;
    
    return ret;
}

HI_S32 task_func_entry(VOID* param)
{
    HI_S32            ret     = HI_SUCCESS;
    OMXVDEC_CHAN_CTX *pchan   = HI_NULL;
    OMXVDEC_ENTRY    *omxvdec = (OMXVDEC_ENTRY*)param;
    OMXVDEC_TASK     *task    = &(omxvdec->task);
    
    OmxPrint(OMX_TRACE, "omx task start!\n");

    while(!kthread_should_stop())
    {
        task->task_state = TASK_STATE_SLEEPING;
        ret = wait_event_timeout(task->task_wait, (TASK_STATE_ONCALL == task->task_state), msecs_to_jiffies(500)); 
        task->task_state = TASK_STATE_RUNNING;
        
        // 非中断或超时唤醒
        if (ret > 0)
        {
            do {
                pchan = HI_NULL;
                pchan = channel_find_inst_wait_alloc(omxvdec);
                if (HI_NULL == pchan)
                {
                    break;
                }
                
                ret = task_alloc_channel_mem(pchan);
                if (ret != HI_SUCCESS)
                {
                    OmxPrint(OMX_FATAL, "Alloc mem for chan %d failed\n", pchan->channel_id);
                    message_queue(pchan->msg_queue, VDEC_ERR_DYNAMIC_ALLOC_FAIL, HI_FAILURE, NULL);
                    break;
                }
            }while(1);
        }
    }
    
    task->task_state = TASK_STATE_INVALID;
    
    OmxPrint(OMX_TRACE, "omx task exit!\n");

    return ret;
}


/*============== EXPORT FUNCTION =============*/
HI_S32 task_create_thread(OMXVDEC_ENTRY* omxvdec)
{
    OMXVDEC_TASK *task = HI_NULL;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    if (HI_NULL == omxvdec)
    {
        OmxPrint(OMX_FATAL, "%s ppTask = NULL!\n", __func__);
        return HI_FAILURE;
    }
    task = &(omxvdec->task);
    
    init_waitqueue_head(&task->task_wait);
    task->task_thread = kthread_create(task_func_entry, (VOID *)omxvdec, "OmxVdecTask");
    if(HI_NULL == task->task_thread)
    {
        OmxPrint(OMX_FATAL, "%s create task failed!\n", __func__);
        return HI_FAILURE;
    }
    wake_up_process(task->task_thread);

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 task_destroy_thread(OMXVDEC_ENTRY* omxvdec)
{
    OMXVDEC_TASK *task = HI_NULL;
    
    if (HI_NULL == omxvdec)
    {
        OmxPrint(OMX_FATAL, "%s omxvdec = NULL!\n", __func__);
        return HI_FAILURE;
    }
    task = &(omxvdec->task);
    
    if(task->task_thread != HI_NULL)
    {
        if (task->task_state != TASK_STATE_INVALID)
        {
            kthread_stop(task->task_thread);
        }
        task->task_thread = HI_NULL;
    }
    
    return HI_SUCCESS;
}

HI_VOID task_proc_entry(struct seq_file *p, OMXVDEC_TASK *ptask)
{
    PROC_PRINT(p, "%-25s :%s\n", "TaskState",         task_show_state(ptask->task_state));
}


