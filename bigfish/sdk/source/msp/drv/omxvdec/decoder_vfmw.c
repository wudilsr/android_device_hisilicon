/*
 * Copyright (c) (2014 - ...) Device Chipset Source Algorithm and Chipset Platform Development Dept
 * Hisilicon. All rights reserved.
 *
 * File:    decoder_vfmw.c
 *
 * Purpose: omxvdec decoder vfmw functions
 *
 * Author:  yangyichang 00226912
 *
 * Date:    26, 11, 2014
 *
 */

#include "hi_drv_module.h"  // HI_DRV_MODULE_GetFunction 依赖
#include "decoder.h"
#include "vfmw_ext.h"


/*================ EXTERN VALUE ================*/
extern OMXVDEC_ENTRY *g_OmxVdec;
extern OMXVDEC_FUNC g_stOmxFunc;


/*================ STATIC VALUE ================*/
static VFMW_EXPORT_FUNC_S* pVfmwFunc = HI_NULL;


/*=================== MACRO ====================*/
#define SOFT_DEC_MIN_MEM_SD     (22*1024*1024)
#define SOFT_DEC_MIN_MEM_HD     (45*1024*1024)


/*================ GLOBAL VALUE ================*/
HI_U32   g_DispNum               = 4;
HI_U32   g_SegSize               = 2;         // (M)
HI_BOOL  g_DynamicFsEnable       = HI_TRUE;
HI_BOOL  g_RawMoveEnable         = HI_TRUE;   // 码流搬移使能标志，解决scd切割失败不释放码流的情况


/*================== DATA TYPE =================*/
typedef enum {
	CFG_CAP_SD = 0,
	CFG_CAP_HD,
	CFG_CAP_UHD,
	CFG_CAP_BUTT,
}eCFG_CAP;


/*============== INTERNAL FUNCTION =============*/
static HI_S32 decoder_event_handler(HI_S32 chan_id, HI_S32 event_type, HI_VOID *pargs)
{
	HI_S32  ret = HI_SUCCESS;
	OMXVDEC_CHAN_CTX  *pchan = HI_NULL;

	pchan = channel_find_inst_by_decoder_id(g_OmxVdec, chan_id);
	if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
	}

	switch (event_type)
    {
        case EVNT_NEED_ARRANGE:
            pchan->dfs_alloc_flag  = DFS_WAIT_ALLOC;
            HI_DRV_SYS_GetTimeStampMs(&pchan->dfs_delay_time);
            pchan->ref_frame_num   = ((HI_U32*)pargs)[0];
            pchan->ref_frame_size  = ((HI_U32*)pargs)[1];
            
            g_OmxVdec->task.task_state = TASK_STATE_ONCALL;
	        wake_up(&g_OmxVdec->task.task_wait);
            break;
              
		case EVNT_LAST_FRAME:
        {
            HI_U32 *ptemp = HI_NULL;

            OmxPrint(OMX_INFO, "Get Last Frame Report!\n");
            if (HI_NULL == pargs)
            {
                OmxPrint(OMX_ERR, "Last frame report but pargs = NULL\n");
                ret = HI_FAILURE;
                break;
            }

            /* pargs[0]-> 0: success, 1: fail,  2+: report last frame image id */
            ptemp = pargs;
            pchan->last_frame_info[0] = VFMW_REPORT_LAST_FRAME;
            pchan->last_frame_info[1] = ptemp[0];
            if (REPORT_LAST_FRAME_SUCCESS == ptemp[0])
            {
                OmxPrint(OMX_INFO, "Last frame report success!\n");
            }
            else if (REPORT_LAST_FRAME_FAIL == ptemp[0])
            {
                OmxPrint(OMX_ERR, "Last frame report failed!\n");
            }
            else
            {
                pchan->last_frame_info[1]  = REPORT_LAST_FRAME_WITH_ID;
                pchan->last_frame_image_id = ptemp[0];
                OmxPrint(OMX_ERR, "Last frame report image id %d!\n", pchan->last_frame_image_id);
            }
            break;
        }

       	default:
        {
            //OmxPrint(OMX_INFO, "\nUnsupport Event Type: 0x%4.4x, arg=%p\n", event_type, pargs);
            break;
        }
	}

	return ret;
}

static HI_S32 decoder_init_option(OMXVDEC_CHAN_CTX *pchan, VDEC_CHAN_CFG_S *pchan_cfg, VDEC_CHAN_CAP_LEVEL_E *pFmwCap, VDEC_CHAN_OPTION_S *pstOption)
{
    eCFG_CAP  ConfigCap = CFG_CAP_HD;

    if (HI_NULL == pchan || HI_NULL == pchan_cfg || HI_NULL == pFmwCap || HI_NULL == pstOption)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }
    
    if (STD_VC1 == pchan_cfg->eVidStd
     && 0 == pchan_cfg->StdExt.Vc1Ext.IsAdvProfile)
    {
        pchan->protocol = STD_WMV;
    }
    else
    {
        pchan->protocol = pchan_cfg->eVidStd;
    }

    pstOption->eAdapterType         = ADAPTER_TYPE_OMXVDEC;
    pstOption->Purpose              = PURPOSE_DECODE;
    pstOption->MemAllocMode         = MODE_PART_BY_SDK;
    pstOption->s32SupportBFrame     = 1;
    pstOption->s32ReRangeEn         = 1;
    pstOption->s32DisplayFrameNum   = g_DispNum;

    if (pchan->out_width*pchan->out_height > HD_FRAME_WIDTH*HD_FRAME_HEIGHT)
    {
        ConfigCap = CFG_CAP_UHD;
        pstOption->s32MaxWidth   = MAX(UHD_FRAME_WIDTH, pchan->out_width); 
        pstOption->s32MaxHeight  = MAX(UHD_FRAME_HEIGHT, pchan->out_height);
        pstOption->s32SCDBufSize = 4*g_SegSize*1024*1024;
        pstOption->s32MaxRefFrameNum = 4;
    }
    else if(pchan->out_width*pchan->out_height > SD_FRAME_WIDTH*SD_FRAME_HEIGHT)
    {
        ConfigCap = CFG_CAP_HD;
        pstOption->s32MaxWidth   = MAX(HD_FRAME_WIDTH, pchan->out_width); 
        pstOption->s32MaxHeight  = MAX(HD_FRAME_HEIGHT, pchan->out_height);
        pstOption->s32SCDBufSize = g_SegSize*1024*1024;
        pstOption->s32MaxRefFrameNum = 10;
    }
    else
    {
        ConfigCap = CFG_CAP_SD;
        pstOption->s32MaxWidth   = MAX(SD_FRAME_WIDTH, pchan->out_width); 
        if (STD_HEVC == pchan_cfg->eVidStd)
        {
            //HEVC能力集宽高要64对齐
			pstOption->s32MaxHeight  = MAX(SD_HEVC_FRAME_HEIGHT, pchan->out_height);
        }
        else
        {
            pstOption->s32MaxHeight  = MAX(SD_FRAME_HEIGHT, pchan->out_height);
        }
        pstOption->s32SCDBufSize = g_SegSize*1024*1024;
        pstOption->s32MaxRefFrameNum = 12;
    }
    
    if (STD_HEVC == pchan_cfg->eVidStd)
    {
        switch (ConfigCap)
        {
            case CFG_CAP_SD:
    	        *pFmwCap = CAP_LEVEL_HEVC_720;				
                break;
            case CFG_CAP_HD:
            default:
    	        *pFmwCap = CAP_LEVEL_HEVC_FHD;
                break;
            case CFG_CAP_UHD:
    	        *pFmwCap = CAP_LEVEL_HEVC_UHD;
                break;
        }
    }
    else if (STD_H264 == pchan_cfg->eVidStd || STD_MVC == pchan_cfg->eVidStd)
    {
        if (STD_MVC == pchan_cfg->eVidStd)
        {
            *pFmwCap = CAP_LEVEL_MVC_FHD;
        }
        else
        {
            switch (ConfigCap)
            {
                case CFG_CAP_SD:
        	        *pFmwCap = CAP_LEVEL_H264_720;
                    break;
                case CFG_CAP_HD:
                default:
        	        *pFmwCap = CAP_LEVEL_H264_FHD;
                    break;
                case CFG_CAP_UHD:
        	        *pFmwCap = CAP_LEVEL_4096x2160;
                    break;
            }
        }
        
        pstOption->s32SupportH264    = 1;
        pstOption->s32MaxSliceNum    = 136;
        pstOption->s32MaxSpsNum      = 32;
        pstOption->s32MaxPpsNum      = 256;
    }
    else
    {
        switch (ConfigCap)
        {
            case CFG_CAP_SD:
    	        *pFmwCap = CAP_LEVEL_MPEG_720;
                break;
            case CFG_CAP_HD:
            default:
    	        *pFmwCap = CAP_LEVEL_MPEG_FHD;
                break;
            case CFG_CAP_UHD:
    	        *pFmwCap = CAP_LEVEL_4096x2160;
                break;
        }

        if (STD_VP8 == pchan_cfg->eVidStd)
        {
            pstOption->s32MaxRefFrameNum = 3;
        }
        else
        {
            pstOption->s32MaxRefFrameNum = 2;
        }
    }

    if (HI_TRUE == g_DynamicFsEnable)
    {
        pstOption->u32DynamicFrameStoreAllocEn = 1;
        pstOption->s32ExtraFrameStoreNum       = g_DispNum;
        pstOption->u32SelfAdaptionDFS          = 1;
        pstOption->u32CfgFrameNum              = 0;
        pstOption->s32DelayTime                = 0;
        pstOption->u32NeedMMZ                  = 1;
        pstOption->u32MaxMemUse                = -1;
    }

    return HI_SUCCESS;
}

static HI_S32 decoder_get_stream(HI_S32 chan_id, STREAM_DATA_S *stream_data)
{
	HI_S32 ret = HI_FAILURE;
	unsigned long flags;
	OMXVDEC_BUF_S *pbuf     = HI_NULL;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;

	pchan = channel_find_inst_by_channel_id(g_OmxVdec, chan_id);
	if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
	}

	spin_lock_irqsave(&pchan->chan_lock, flags);
	if (pchan->state != CHAN_STATE_WORK)
    {
		spin_unlock_irqrestore(&pchan->chan_lock, flags);
		return HI_FAILURE;
	}
	spin_unlock_irqrestore(&pchan->chan_lock, flags);

	if (pchan->input_flush_pending)
    {
        OmxPrint(OMX_INBUF, "Invalid: input_flush_pending\n");
		return HI_FAILURE;
	}

	spin_lock_irqsave(&pchan->raw_lock, flags);
	if (list_empty(&pchan->raw_queue))
    {
		spin_unlock_irqrestore(&pchan->raw_lock, flags);
		return HI_FAILURE;
	}

	list_for_each_entry(pbuf, &pchan->raw_queue, list)
    {
		if(BUF_STATE_USING == pbuf->status)
        {
			continue;
        }

        memset(stream_data, 0, sizeof(STREAM_DATA_S));

        pbuf->status                      = BUF_STATE_USING;
		stream_data->PhyAddr	          = pbuf->phy_addr + pbuf->offset;
		stream_data->VirAddr	          = pbuf->kern_vaddr + pbuf->offset;
		stream_data->Length	              = pbuf->act_len;
		stream_data->Pts	              = pbuf->time_stamp;
		stream_data->RawExt.Flags         = pbuf->flags;
		stream_data->RawExt.BufLen        = pbuf->buf_len;
		stream_data->RawExt.CfgWidth      = pchan->out_width;
		stream_data->RawExt.CfgHeight     = pchan->out_height;

        if (pchan->seek_pending)
        {
            stream_data->RawExt.IsSeekPending = 1;
            pchan->seek_pending = 0;
        }

        if (pbuf->flags & VDEC_BUFFERFLAG_ENDOFFRAME)
        {
            stream_data->is_not_last_packet_flag = 0;
        }
        else
        {
            stream_data->is_not_last_packet_flag = 1;
        }

        if (pbuf->buf_id == LAST_FRAME_BUF_ID)
        {
            OmxPrint(OMX_INFO, "vfmw read last frame.\n");
            stream_data->is_stream_end_flag = 1;
        }

		pchan->raw_use_cnt++;

        OmxPrint(OMX_PTS, "Get Time Stamp: %lld\n", stream_data->Pts);

		ret = HI_SUCCESS;

        OmxPrint(OMX_INBUF, "VFMW got stream: PhyAddr = 0x%08x, VirAddr = %p, Len = %d\n",
                            stream_data->PhyAddr, stream_data->VirAddr, stream_data->Length);

		break;
	}

	spin_unlock_irqrestore(&pchan->raw_lock, flags);

	return ret;
}

static HI_S32 decoder_release_stream(HI_S32 chan_id, STREAM_DATA_S *stream_data)
{
	unsigned long flags;
	HI_S32        is_find = 0;
	OMXVDEC_BUF_S    *pbuf  = HI_NULL; 
    OMXVDEC_BUF_S    *ptmp  = HI_NULL;
	OMXVDEC_CHAN_CTX *pchan = HI_NULL;
	OMXVDEC_BUF_DESC  user_buf;

	pchan = channel_find_inst_by_channel_id(g_OmxVdec, chan_id);
	if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, chan_id);
        return HI_FAILURE;
	}

	/* for we del element during, so use safe methods for list */
	spin_lock_irqsave(&pchan->raw_lock, flags);
	list_for_each_entry_safe(pbuf, ptmp, &pchan->raw_queue, list)
    {
		if (stream_data->PhyAddr == (pbuf->phy_addr + pbuf->offset))
        {
			if (BUF_STATE_USING != pbuf->status)
            {
               OmxPrint(OMX_ERR, "%s: buf(0x%08x) flag confused!\n",__func__,  stream_data->PhyAddr);
            }

            pbuf->status = BUF_STATE_IDLE;
			list_del(&pbuf->list);
			is_find = 1;
			break;
		}
	}
	spin_unlock_irqrestore(&pchan->raw_lock, flags);

	if (!is_find)
    {
        OmxPrint(OMX_ERR, "%s: buffer(0x%08x) not in queue!\n", __func__, stream_data->PhyAddr);
        return HI_FAILURE;
	}

    if (pbuf->buf_id != LAST_FRAME_BUF_ID)
    {
        /* let msg to indicate buffer was given back */

        user_buf.dir         = PORT_DIR_INPUT;
        user_buf.bufferaddr  = pbuf->user_vaddr;
        user_buf.buffer_len  = pbuf->buf_len;
        user_buf.client_data = pbuf->client_data;
        user_buf.data_len    = 0;
        user_buf.timestamp   = 0;
        user_buf.phyaddr     = pbuf->phy_addr;

        pbuf->act_len        = user_buf.data_len;
        message_queue(pchan->msg_queue, VDEC_MSG_RESP_INPUT_DONE, VDEC_S_SUCCESS, &user_buf);
    }
	else
	{
        pchan->eos_in_list = 0;
	    OmxPrint(OMX_INFO, "vfmw release last frame.\n");
	}

	pchan->raw_use_cnt = (pchan->raw_use_cnt > 0) ? (pchan->raw_use_cnt-1) : 0;

	if (pchan->input_flush_pending && (pchan->raw_use_cnt == 0))
    {
        OmxPrint(OMX_INBUF, "%s: input flush done!\n", __func__);
		message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_INPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
		pchan->input_flush_pending = 0;
	}

    OmxPrint(OMX_INBUF, "VFMW release stream: PhyAddr = 0x%08x, VirAddr = %p, Len = %d\n",
                        stream_data->PhyAddr, stream_data->VirAddr, stream_data->Length);

    return HI_SUCCESS;

}


/*============ EXPORT INTERFACE =============*/
HI_S32 decoder_init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    VDEC_OPERATION_S stInitParam;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    pVfmwFunc = HI_NULL;
    
    ret = HI_DRV_MODULE_GetFunction(HI_ID_VFMW, (HI_VOID**)&g_stOmxFunc.pDecoderFunc);
    if (HI_SUCCESS != ret || HI_NULL == g_stOmxFunc.pDecoderFunc)
    {
        OmxPrint(OMX_FATAL, "%s get vfmw function failed!\n", __func__);
        return HI_FAILURE;
    }

    pVfmwFunc = (VFMW_EXPORT_FUNC_S *)(g_stOmxFunc.pDecoderFunc);

    memset(&stInitParam, 0, sizeof(VDEC_OPERATION_S));
    
    stInitParam.eAdapterType = ADAPTER_TYPE_OMXVDEC;
    stInitParam.mem_malloc   = HI_NULL;
    stInitParam.mem_free     = HI_NULL;
    stInitParam.VdecCallback = decoder_event_handler;

    ret = (pVfmwFunc->pfnVfmwInitWithOperation)(&stInitParam);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s init vfmw failed!\n", __func__);
        return ret;
    }
    
    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 decoder_exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = (pVfmwFunc->pfnVfmwExit)();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit vfmw failed!\n", __func__);
        return ret;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

#ifdef HI_TVP_SUPPORT 
HI_S32 decoder_init_trusted(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    VDEC_OPERATION_S stInitParam;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);
    
    memset(&stInitParam, 0, sizeof(VDEC_OPERATION_S));
    
    stInitParam.eAdapterType = ADAPTER_TYPE_OMXVDEC;
    stInitParam.VdecCallback = decoder_event_handler;
    stInitParam.mem_malloc   = HI_NULL;
    stInitParam.mem_free     = HI_NULL; 
    ret = (pVfmwFunc->pfnVfmwTrustDecoderInit)(&stInitParam);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "Init trusted decoder failed!n");
        return ret;
    }
    
    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 decoder_exit_trusted(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = (pVfmwFunc->pfnVfmwTrustDecoderExit)();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "Exit trusted decoder failed\n");
        return ret;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}
#endif

HI_S32 decoder_create_inst(OMXVDEC_CHAN_CTX *pchan, OMXVDEC_DRV_CFG *pdrv_cfg)
{
    HI_S32 ret = HI_FAILURE;
    HI_S8 as8TmpBuf[128];
    VDEC_CHAN_CAP_LEVEL_E enFmwCap;
    HI_U32                u32VDHSize = 0;
    VDEC_CHAN_OPTION_S    stOption;
    DETAIL_MEM_SIZE       stMemSize;
    VDEC_CHAN_CFG_S      *pchan_cfg = HI_NULL;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);
    
    memset(&stOption,  0, sizeof(VDEC_CHAN_OPTION_S));
    memset(&stMemSize, 0, sizeof(DETAIL_MEM_SIZE));
    
#ifdef HI_TVP_SUPPORT
    if (HI_TRUE == pchan->is_tvp)
    {
        ret = decoder_init_trusted();
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s call decoder_init_trusted failed\n", __func__);
            return HI_FAILURE;
        }
    }
#endif

    pchan_cfg = &pdrv_cfg->chan_cfg;
    ret = decoder_init_option(pchan, pchan_cfg, &enFmwCap, &stOption);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call decoder_init_option failed\n", __func__);
        goto error0;
    }

    ((HI_S32*)as8TmpBuf)[0] = (HI_S32)enFmwCap;
    ((HI_S32*)as8TmpBuf)[1] = (HI_S32)&stOption;

    ret = (pVfmwFunc->pfnVfmwControl)(-1, VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION, as8TmpBuf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call GET_CHAN_DETAIL_MEMSIZE failed\n", __func__);
        goto error0;
    }

    stMemSize = *(DETAIL_MEM_SIZE *)as8TmpBuf;
    
#ifdef HI_TVP_SUPPORT
    if (HI_TRUE == pchan->is_tvp)
    {
        stOption.s32IsSecMode = 1;
        stOption.MemAllocMode = MODE_ALL_BY_MYSELF;
        stOption.MemDetail.ChanMemScd.Length  = 0;
        stOption.MemDetail.ChanMemScd.PhyAddr = 0;
        stOption.MemDetail.ChanMemScd.VirAddr = HI_NULL;
        stOption.MemDetail.ChanMemCtx.Length  = 0;
        stOption.MemDetail.ChanMemCtx.PhyAddr = 0;
        stOption.MemDetail.ChanMemCtx.VirAddr = HI_NULL;
        stOption.MemDetail.ChanMemScd.Length  = 0;
        stOption.MemDetail.ChanMemScd.PhyAddr = 0;
        stOption.MemDetail.ChanMemScd.VirAddr = HI_NULL;
    }
    else 
#endif
{
    /* Allocate frame buffer memory(VDH) */
    if (STD_H263 == pchan->protocol || STD_SORENSON == pchan->protocol)  // 内核态软解所需帧存大小指定
    {
        if (enFmwCap < CAP_LEVEL_MPEG_FHD)
        {
            u32VDHSize = SOFT_DEC_MIN_MEM_SD;
        }
        else
        {
            u32VDHSize = SOFT_DEC_MIN_MEM_HD;
        }
    }
    else
    {
        u32VDHSize = stMemSize.VdhDetailMem;
    }

    if (1 == stOption.u32DynamicFrameStoreAllocEn
     && STD_H263     != pchan->protocol
     && STD_SORENSON != pchan->protocol)
    {
        stOption.MemDetail.ChanMemVdh.Length  = 0;
        stOption.MemDetail.ChanMemVdh.PhyAddr = 0;
        stOption.MemDetail.ChanMemVdh.VirAddr = HI_NULL;
    }
    else
    {
        ret = HI_DRV_MMZ_AllocAndMap("OMXVDEC_VDH", "OMXVDEC", u32VDHSize, 0, &pchan->decoder_vdh_buf);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc mem for VDH failed\n", __func__);
            goto error0;
        }      
        
        stOption.MemDetail.ChanMemVdh.Length  = pchan->decoder_vdh_buf.u32Size;
        stOption.MemDetail.ChanMemVdh.PhyAddr = pchan->decoder_vdh_buf.u32StartPhyAddr;
        stOption.MemDetail.ChanMemVdh.VirAddr = (HI_VOID*)pchan->decoder_vdh_buf.u32StartVirAddr;
    }

    /* Alloc SCD buffer */
    if (stMemSize.ScdDetailMem > 0)
    {
        ret = HI_DRV_MMZ_AllocAndMap("OMXVDEC_SCD", "OMXVDEC", stMemSize.ScdDetailMem, 0, &pchan->decoder_scd_buf);
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "%s alloc mem for SCD failed\n", __func__);
            goto error1;
        }
         
        /*pstChan->stSCDMMZBuf.u32SizeD的大小就是从vfmw获取的大小:pstChan->stMemSize.ScdDetailMem*/
        stOption.MemDetail.ChanMemScd.Length  = pchan->decoder_scd_buf.u32Size;
        stOption.MemDetail.ChanMemScd.PhyAddr = pchan->decoder_scd_buf.u32StartPhyAddr;
        stOption.MemDetail.ChanMemScd.VirAddr = (HI_VOID*)pchan->decoder_scd_buf.u32StartVirAddr;
    }

    /* Context memory allocated by VFMW */
    /*这部分由vfmw自己进行分配，scd和vdh的内存由vdec进行分配*/
    stOption.MemDetail.ChanMemCtx.Length  = 0;
    stOption.MemDetail.ChanMemCtx.PhyAddr = 0;
    stOption.MemDetail.ChanMemCtx.VirAddr = HI_NULL;
}

    ((HI_S32*)as8TmpBuf)[0] = (HI_S32)enFmwCap;
    ((HI_S32*)as8TmpBuf)[1] = (HI_S32)&stOption;

    ret = (pVfmwFunc->pfnVfmwControl)(-1, VDEC_CID_CREATE_CHAN_WITH_OPTION, as8TmpBuf);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s CREATE_CHAN_WITH_OPTION failed:%#x\n", __func__, ret);
        goto error2;
    }

    pchan->decoder_id = *(HI_U32 *)as8TmpBuf;
    OmxPrint(OMX_INFO, "Create decoder %d success!\n", pchan->decoder_id);

    // 如果不使能码流移动功能，将码流包个数设置最大即可
    if (HI_FALSE == g_RawMoveEnable)
    {
        pchan_cfg->s32MaxRawPacketNum = -1;
    }

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_CFG_CHAN, pchan_cfg);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s CFG_CHAN failed\n", __func__);
        goto error3;
    }

    pchan->stream_ops.stream_provider_inst_id = pchan->channel_id;
    pchan->stream_ops.read_stream = decoder_get_stream;
    pchan->stream_ops.release_stream = decoder_release_stream;
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_SET_STREAM_INTF, &pchan->stream_ops);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s SET_STREAM_INTF failed\n", __func__);
        goto error3;
    }

    pchan->image_ops.image_provider_inst_id = pchan->channel_id;
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_GET_IMAGE_INTF, &pchan->image_ops);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s GET_IMAGE_INTF failed\n", __func__);
        goto error3;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;

error3:
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_DESTROY_CHAN, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s DESTROY_CHAN failed\n", __func__);
    }
error2:
    omxvdec_release_mem(&pchan->decoder_scd_buf);
error1:
    omxvdec_release_mem(&pchan->decoder_vdh_buf);
error0:
#ifdef HI_TVP_SUPPORT
    if (HI_TRUE == pchan->is_tvp)
    {
        ret = decoder_exit_trusted();
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "decoder_exit_trusted failed\n");
        }
    }
#endif

    return HI_FAILURE;
}

HI_S32 decoder_release_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_DESTROY_CHAN, HI_NULL);
    if (ret != HI_SUCCESS)
    {
       OmxPrint(OMX_FATAL, "%s destroy vfmw failed\n", __func__);
       //return ret;  /* 不退出，强制释放资源 */
    }
    
#ifdef HI_TVP_SUPPORT
    if (HI_TRUE == pchan->is_tvp)
    {
        ret = decoder_exit_trusted();
        if (ret != HI_SUCCESS)
        {
            OmxPrint(OMX_FATAL, "decoder_exit_trusted failed\n");
        }
    }
#endif

    if (pchan->decoder_scd_buf.u32Size != 0 && pchan->decoder_scd_buf.u32StartPhyAddr != 0)
    {
        omxvdec_release_mem(&pchan->decoder_scd_buf);
    }

    if (pchan->decoder_vdh_buf.u32Size != 0 && pchan->decoder_vdh_buf.u32StartPhyAddr != 0)
    {
        omxvdec_release_mem(&pchan->decoder_vdh_buf);
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return ret;
}

HI_S32 decoder_start_inst(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret = HI_FAILURE;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);
    
	ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_START_CHAN, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s start vfmw failed\n", __func__);
        return ret;
	}

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

	return HI_SUCCESS;
}

HI_S32 decoder_stop_inst(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret = HI_FAILURE;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_STOP_CHAN, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s stop vfmw failed\n", __func__);
        return ret;
	}

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

	return HI_SUCCESS;
}

HI_S32 decoder_reset_inst(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret = HI_FAILURE;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

	ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_RESET_CHAN, HI_NULL);
	if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s reset vfmw failed\n", __func__);
        return ret;
	}

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

	return HI_SUCCESS;
}

HI_S32 decoder_reset_inst_with_option(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret = HI_FAILURE;
    VDEC_CHAN_RESET_OPTION_S  Option;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    Option.s32KeepBS     = 0;
    Option.s32KeepSPSPPS = 1;
    ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_RESET_CHAN_WITH_OPTION, &Option);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s reset vfmw with option failed\n", __func__);
        return ret;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

	return HI_SUCCESS;
}

HI_S32 decoder_clear_stream(OMXVDEC_CHAN_CTX *pchan)
{
	HI_S32 ret = HI_FAILURE;
    
    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);
    
	ret = (pVfmwFunc->pfnVfmwControl)(pchan->decoder_id, VDEC_CID_RELEASE_STREAM, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s release stream failed\n", __func__);
        return ret;
    }
    
    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

	return HI_SUCCESS;
}


