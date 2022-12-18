/*
 * Copyright (c) (2014 - ...) Device Chipset Source Algorithm and Chipset Platform Development Dept
 * Hisilicon. All rights reserved.
 *
 * File:    processor_vpss.c
 *
 * Purpose: omxvdec processor vpss functions
 *
 * Author:  yangyichang 00226912
 *
 * Date:    26, 11, 2014
 *
 */
 
 
#include "hi_drv_module.h"
#include "drv_vpss_ext.h"
#include "drv_vdec_ext.h"
#include "processor.h"

#include "hi_math.h"

/*================ EXTERN VALUE ================*/
extern HI_BOOL  g_SaveYuvEnable;
extern HI_CHAR  g_SavePath[];
extern HI_CHAR  g_SaveName[];
extern OMXVDEC_FUNC g_stOmxFunc;
extern OMXVDEC_ENTRY *g_OmxVdec;


/*=================== MACRO ====================*/
#define  REALID(id)           (id%100+2)


/*================ GLOBAL VALUE ================*/
HI_BOOL  g_FrameRateLimit        = HI_TRUE;
HI_BOOL  g_DeInterlaceEnable     = HI_FALSE;


/*================ STATIC VALUE ================*/
static VPSS_EXPORT_FUNC_S* pVpssFunc = HI_NULL;


/*============== INTERNAL FUNCTION =============*/
static HI_S32 processor_get_frame(OMXVDEC_CHAN_CTX *pchan, EXTERNAL_FRAME_STORE_S *frame, HI_U32 expect_length)
{
	unsigned long flags;
	OMXVDEC_BUF_S *pbuf = HI_NULL;
	HI_S32 ret = HI_FAILURE;

	spin_lock_irqsave(&pchan->chan_lock, flags);
	if (pchan->state != CHAN_STATE_WORK)
    {
		spin_unlock_irqrestore(&pchan->chan_lock, flags);
        OmxPrint(OMX_VPSS, "VPSS: pchan->state != CHAN_STATE_WORK\n");
		return HI_FAILURE;
	}
	spin_unlock_irqrestore(&pchan->chan_lock, flags);

	if (pchan->output_flush_pending)
    {
        OmxPrint(OMX_VPSS, "VPSS: output_flush_pending\n");
		return HI_FAILURE;
	}

	spin_lock_irqsave(&pchan->yuv_lock, flags);
	if (list_empty(&pchan->yuv_queue))
    {
        OmxPrint(OMX_VPSS, "VPSS: List is empty!\n");
        goto empty;
    }

	list_for_each_entry(pbuf, &pchan->yuv_queue, list)
    {
        if(BUF_STATE_USING == pbuf->status)
        {
            continue;
        }

        if (expect_length > pbuf->buf_len)
        {
            OmxPrint(OMX_VPSS, "VPSS: expect_length(%d) > buf_len(%d)\n", expect_length, pbuf->buf_len);
            continue;
        }

        pbuf->status   = BUF_STATE_USING;
        frame->PhyAddr = pbuf->phy_addr + pbuf->offset;
        frame->VirAddr = pbuf->kern_vaddr + pbuf->offset;
        frame->Length  = pbuf->buf_len;

        pchan->yuv_use_cnt++;

        ret = HI_SUCCESS;

        OmxPrint(OMX_OUTBUF, "VPSS got frame: phy addr = 0x%08x\n", frame->PhyAddr);

        break;
	}

empty:
	spin_unlock_irqrestore(&pchan->yuv_lock, flags);

	return ret;
}

static HI_S32 processor_release_frame(OMXVDEC_CHAN_CTX *pchan, HI_U32 phyaddr)
{
	HI_S32 is_find = 0;
	unsigned long flags;
	OMXVDEC_BUF_S *pbuf = HI_NULL;
	OMXVDEC_BUF_S *ptmp = HI_NULL;
	OMXVDEC_BUF_DESC user_buf;
    memset(&user_buf, 0, sizeof(OMXVDEC_BUF_DESC));

	if (HI_NULL == pchan || 0 == phyaddr)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

	/* for we del list during, so use safe means */
	spin_lock_irqsave(&pchan->yuv_lock, flags);
	if (list_empty(&pchan->yuv_queue))
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        OmxPrint(OMX_ERR, "%s: list is empty\n", __func__);
        return 0;
    }

	list_for_each_entry_safe(pbuf, ptmp, &pchan->yuv_queue, list)
    {
        if (phyaddr == (pbuf->phy_addr + pbuf->offset))
        {
           if (pbuf->status != BUF_STATE_USING)
           {
               OmxPrint(OMX_ERR, "%s: buffer(0x%08x) flags confused!\n",__func__, phyaddr);
           }

           is_find = 1;
           pbuf->status =  BUF_STATE_IDLE;
           break;
        }
	}
	spin_unlock_irqrestore(&pchan->yuv_lock, flags);

	if (!is_find)
    {
        OmxPrint(OMX_ERR, "%s: buffer(0x%08x) not in queue!\n",__func__,  phyaddr);
        return HI_FAILURE;
    }

    pchan->yuv_use_cnt = (pchan->yuv_use_cnt > 0) ? (pchan->yuv_use_cnt-1) : 0;

    if (pchan->output_flush_pending || pchan->pause_pending)
    {
        spin_lock_irqsave(&pchan->yuv_lock, flags);
        list_del(&pbuf->list);
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);

        user_buf.dir = PORT_DIR_OUTPUT;
        user_buf.bufferaddr = pbuf->user_vaddr;
        user_buf.buffer_len =  pbuf->buf_len;
        user_buf.client_data = pbuf->client_data;
        user_buf.data_len = 0;
        user_buf.timestamp = 0;

        message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_S_SUCCESS, (HI_VOID *)&user_buf);

        if (0 == pchan->yuv_use_cnt)
        {
            if (pchan->output_flush_pending)
            {
                message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_OUTPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
                pchan->output_flush_pending = 0;
            }

            if (pchan->pause_pending)
            {
                message_queue(pchan->msg_queue, VDEC_MSG_RESP_PAUSE_DONE, VDEC_S_SUCCESS, HI_NULL);
                pchan->pause_pending = 0;
            }
        }

        OmxPrint(OMX_OUTBUF, "VPSS release frame: phy addr = 0x%08x (delete)\n", phyaddr);
    }
    else
    {
        pbuf->status = BUF_STATE_QUEUED;
        OmxPrint(OMX_OUTBUF, "VPSS release frame: phy addr = 0x%08x (requeue)\n", phyaddr);
    }

    return HI_SUCCESS;

}

static HI_S32 processor_report_frame(OMXVDEC_CHAN_CTX *pchan, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
	HI_U32 phyaddr = 0;
	unsigned long flags;
	HI_S32 is_find = 0;
	OMXVDEC_BUF_S *pbuf = HI_NULL;
	OMXVDEC_BUF_S *ptmp = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = HI_NULL;
	OMXVDEC_BUF_DESC user_buf;
    memset(&user_buf, 0, sizeof(OMXVDEC_BUF_DESC));

    phyaddr = pstFrame->stBufAddr[0].u32PhyAddr_Y;
    pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)(pstFrame->u32Priv);

	if (HI_NULL == pchan || 0 == phyaddr)
    {
        OmxPrint(OMX_FATAL, "%s param invalid!\n", __func__);
        return HI_FAILURE;
    }

	/* for we del list during, so use safe means */
	spin_lock_irqsave(&pchan->yuv_lock, flags);
	if (list_empty(&pchan->yuv_queue))
    {
        spin_unlock_irqrestore(&pchan->yuv_lock, flags);
        OmxPrint(OMX_ERR, "%s: list is empty\n", __func__);
        return HI_FAILURE;
	}
    
	list_for_each_entry_safe(pbuf, ptmp, &pchan->yuv_queue, list)
    {
       if (phyaddr == (pbuf->phy_addr + pbuf->offset))
       {
           if (pbuf->status != BUF_STATE_USING)
           {
               OmxPrint(OMX_ERR, "%s: buffer(0x%08x) flags confused!\n", __func__, phyaddr);
           }

           is_find = 1;
           pbuf->status = BUF_STATE_IDLE;
           list_del(&pbuf->list);
           break;
       }
	}
	spin_unlock_irqrestore(&pchan->yuv_lock, flags);

	if (!is_find)
    {
       OmxPrint(OMX_ERR, "%s: buffer(0x%08x) not in queue!\n", __func__,  phyaddr);
       return HI_FAILURE;
	}

	/* let out msg to inform application */
	user_buf.dir			                = PORT_DIR_OUTPUT;
	user_buf.bufferaddr		                = pbuf->user_vaddr;
	user_buf.buffer_len		                = pbuf->buf_len;
	user_buf.client_data	                = pbuf->client_data;
	user_buf.flags			                = VDEC_BUFFERFLAG_ENDOFFRAME;
    user_buf.phyaddr                        = phyaddr;
    user_buf.out_frame.phyaddr_Y            = pstFrame->stBufAddr[0].u32PhyAddr_Y;
    user_buf.out_frame.phyaddr_C            = pstFrame->stBufAddr[0].u32PhyAddr_C;
    user_buf.out_frame.stride               = pstFrame->stBufAddr[0].u32Stride_Y;
    user_buf.out_frame.width                = pstFrame->u32Width;
    user_buf.out_frame.height               = pstFrame->u32Height;
    user_buf.out_frame.save_yuv             = g_SaveYuvEnable;
    if (HI_TRUE == user_buf.out_frame.save_yuv)
    {
       snprintf(user_buf.out_frame.save_path, sizeof(user_buf.out_frame.save_path),
                "%s/%s_%dx%d.yuv", g_SavePath, g_SaveName, pstFrame->u32Width, pstFrame->u32Height);
                user_buf.out_frame.save_path[PATH_LEN-1] = '\0';
    }

	if (pchan->output_flush_pending)
    {
        OmxPrint(OMX_OUTBUF, "output flush pending, unrelease buffer num: %d\n", pchan->yuv_use_cnt-1);
		user_buf.data_len 	= 0;
		user_buf.timestamp	= 0;
	}
    else
    {
        user_buf.timestamp = pstFrame->s64OmxPts;
        user_buf.data_len = (pstFrame->stBufAddr[0].u32Stride_Y * pstFrame->u32Height * 3) / 2;
	}
    pbuf->act_len = user_buf.data_len;
    OmxPrint(OMX_PTS, "Put Time Stamp: %lld\n", user_buf.timestamp);

    if (VPSS_GOT_LAST_FRAME == pchan->last_frame_info[0])
    {
       /* vpss last frame flag */
       if (DEF_HI_DRV_VPSS_LAST_FRAME_FLAG == pstPriv->u32LastFlag)
       {
           user_buf.flags |= VDEC_BUFFERFLAG_EOS;
           pchan->last_frame_info[0] = LAST_FRAME_FLAG_NULL;
           pchan->eof_send_flag++;
           OmxPrint(OMX_INFO, "VPSS report last frame, phyaddr = %x, timestamp = %lld\n", phyaddr, user_buf.timestamp);
       }
    }

	message_queue(pchan->msg_queue, VDEC_MSG_RESP_OUTPUT_DONE, VDEC_S_SUCCESS, &user_buf);

	pchan->yuv_use_cnt = (pchan->yuv_use_cnt > 0) ? (pchan->yuv_use_cnt-1) : 0;

	if (0 == pchan->yuv_use_cnt)
    {
       if (pchan->output_flush_pending)
       {
           message_queue(pchan->msg_queue, VDEC_MSG_RESP_FLUSH_OUTPUT_DONE, VDEC_S_SUCCESS, HI_NULL);
           pchan->output_flush_pending = 0;
       }

       if (pchan->pause_pending)
       {
           message_queue(pchan->msg_queue, VDEC_MSG_RESP_PAUSE_DONE, VDEC_S_SUCCESS, HI_NULL);
           pchan->pause_pending = 0;
       }
	}

    OmxPrint(OMX_OUTBUF, "VPSS report frame: phy addr = 0x%08x, data_len: %d\n", phyaddr, user_buf.data_len);

	return HI_SUCCESS;
}

static HI_S32 processor_get_frame_buffer(OMXVDEC_CHAN_CTX *pchan, HI_VOID *pstArgs)
{
    HI_S32 ret = HI_FAILURE;
    HI_S32 hPort;
    HI_S32 hVpss;
    HI_U32 ExpectedSize;
	OMXVDEC_IMG_SIZE ImgSize;
    EXTERNAL_FRAME_STORE_S OutFrame;
    HI_DRV_VPSS_FRMBUF_S * pVpssFrm = (HI_DRV_VPSS_FRMBUF_S*)pstArgs;

    hPort = ((HI_DRV_VPSS_FRMBUF_S*)pstArgs)->hPort;
    hVpss = (HI_HANDLE)PORTHANDLE_TO_VPSSID(hPort);
    if (hVpss != pchan->processor_id || hPort != pchan->port_id)
    {
        OmxPrint(OMX_FATAL, "%s hVpss/hPort Not Match!\n", __func__);
        return HI_FAILURE;
    }

    // 检测输出宽高变化，进行上报
    if (pVpssFrm->u32FrmW != pchan->out_width || pVpssFrm->u32FrmH != pchan->out_height)
    {
        OmxPrint(OMX_INFO, "Image size changed: %dx%d stride:%d change to %dx%d stride:%d\n", pchan->out_width, pchan->out_height, pchan->out_stride, pVpssFrm->u32FrmW, pVpssFrm->u32FrmH, pVpssFrm->u32Stride);
        
        pchan->out_width  = ImgSize.frame_width  = pVpssFrm->u32FrmW;
        pchan->out_height = ImgSize.frame_height = pVpssFrm->u32FrmH;
        pchan->out_stride = ImgSize.frame_stride = HI_SYS_GET_STRIDE(pchan->out_width);

        pchan->recfg_flag = 1;
        channel_report_message(pchan, VDEC_EVT_REPORT_IMG_SIZE_CHG, (HI_VOID *)&ImgSize);


        return HI_FAILURE;
    }

	if (pchan->out_stride >= pchan->out_width)
	{
		pVpssFrm->u32Stride = pchan->out_stride;
	}
	else
	{
		OmxPrint(OMX_FATAL, " %s stride(%d) < width(%d)!\n", __func__, pchan->out_stride, pchan->out_width);
		
		return HI_FAILURE;
	}

    ExpectedSize = FRAME_SIZE(pVpssFrm->u32Stride, pVpssFrm->u32FrmH);

    ret = processor_get_frame(pchan, &OutFrame, ExpectedSize);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_VPSS, "VPSS call vpss_get_frame failed!\n");
        return HI_FAILURE;
    }

    if (OutFrame.PhyAddr != 0 && OutFrame.VirAddr != 0)
    {
        pVpssFrm->u32StartPhyAddr = (HI_U32)OutFrame.PhyAddr;
        pVpssFrm->u32StartVirAddr = (HI_U32)OutFrame.VirAddr;
    }

    OmxPrint(OMX_VPSS, "VPSS get frame buffer success!\n");

    return HI_SUCCESS;

}

static HI_S32 processor_release_frame_buffer(OMXVDEC_CHAN_CTX *pchan, HI_VOID *pstArgs)
{
    HI_S32 ret = HI_FAILURE;
    VPSS_HANDLE hPort;
    VPSS_HANDLE hVpss;
    HI_U32 PhyAddr;
    HI_DRV_VIDEO_FRAME_S *pstFrame = &((HI_DRV_VPSS_FRMINFO_S*)pstArgs)->stFrame;
    HI_DRV_VIDEO_PRIVATE_S *pstPriv = (HI_DRV_VIDEO_PRIVATE_S *)(pstFrame->u32Priv);

    hPort = ((HI_DRV_VPSS_FRMINFO_S*)pstArgs)->hPort;
    hVpss = (HI_HANDLE)PORTHANDLE_TO_VPSSID(hPort);
    if (hVpss != pchan->processor_id || hPort != pchan->port_id)
    {
        OmxPrint(OMX_FATAL, "%s hVpss/hPort Not Match!\n", __func__);
        return HI_FAILURE;
    }

    if (VPSS_GOT_LAST_FRAME == pchan->last_frame_info[0])
    {
      /* vpss last frame flag */
       if (DEF_HI_DRV_VPSS_LAST_FRAME_FLAG == pstPriv->u32LastFlag)
       {
           OmxPrint(OMX_ERR, "VPSS release last frame!!\n");
           pchan->last_frame_info[0] = LAST_FRAME_FLAG_NULL;
       }
    }

    PhyAddr = ((HI_DRV_VPSS_FRMBUF_S*)pstArgs)->u32StartPhyAddr;
    ret = processor_release_frame(pchan, PhyAddr);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s call vpss_release_frame failed\n", __func__);
        return HI_FAILURE;
    }

    OmxPrint(OMX_VPSS, "VPSS release frame buffer success!\n");

    return HI_SUCCESS;

}

static HI_S32 processor_report_new_frame(OMXVDEC_CHAN_CTX *pchan, HI_VOID *pstArgs)
{
    HI_S32 ret = HI_FAILURE;
    VPSS_HANDLE hPort;
    VPSS_HANDLE hVpss;
    HI_DRV_VIDEO_FRAME_S *pstFrame;
    HI_DRV_VID_FRAME_ADDR_S stBakBufAddr;

    hPort = ((HI_DRV_VPSS_FRMINFO_S*)pstArgs)->hPort;
    hVpss = (HI_HANDLE)PORTHANDLE_TO_VPSSID(hPort);
    if (hVpss != pchan->processor_id || hPort != pchan->port_id)
    {
        OmxPrint(OMX_FATAL, "%s hVpss/hPort Not Match!\n", __func__);
        return HI_FAILURE;
    }

    pstFrame = &((HI_DRV_VPSS_FRMINFO_S*)pstArgs)->stFrame;
    //g_SaveYuvEnable = HI_TRUE;
    ret = processor_report_frame(pchan, pstFrame);
    if(ret != HI_SUCCESS)
    {
        OmxPrint(OMX_ERR, "%s report frame failed!\n", __func__);
        return HI_FAILURE;
    }
    if (pstFrame->eFrmType != HI_DRV_FT_NOT_STEREO)
    {
        memcpy(&stBakBufAddr, &pstFrame->stBufAddr[0], sizeof(HI_DRV_VID_FRAME_ADDR_S));
        memcpy(&pstFrame->stBufAddr[0], &pstFrame->stBufAddr[1], sizeof(HI_DRV_VID_FRAME_ADDR_S));
        //g_SaveYuvEnable = HI_FALSE;
        ret = processor_report_frame(pchan, pstFrame);
        memcpy(&pstFrame->stBufAddr[0], &stBakBufAddr, sizeof(HI_DRV_VID_FRAME_ADDR_S));
        if(ret != HI_SUCCESS)
        {
            OmxPrint(OMX_ERR, "%s report right frame failed!\n", __func__);
            return HI_FAILURE;
        }
    }

    OmxPrint(OMX_VPSS, "VPSS report new frame success!\n");

    return HI_SUCCESS;

}

static HI_S32 processor_report_last_frame(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret = HI_FAILURE;
    EXTERNAL_FRAME_STORE_S stFrameStore;
    HI_DRV_VIDEO_FRAME_S stLastFrame;
    HI_DRV_VIDEO_PRIVATE_S *pVideoPri = (HI_DRV_VIDEO_PRIVATE_S *)(stLastFrame.u32Priv);
	HI_S32 FailedNum = 0;

    do
    {
        ret = processor_get_frame(pchan, &stFrameStore, 0);
        if (HI_SUCCESS == ret)
        {
            memset(&stLastFrame, 0, sizeof(HI_DRV_VIDEO_FRAME_S));
            pVideoPri->u32LastFlag = DEF_HI_DRV_VPSS_LAST_FRAME_FLAG;
            stLastFrame.stBufAddr[0].u32PhyAddr_Y = stFrameStore.PhyAddr;

            if (HI_SUCCESS == processor_report_frame(pchan, &stLastFrame))
            {
                OmxPrint(OMX_INFO, "VPSS report a fade last frame.\n");
            }
			else
			{
                OmxPrint(OMX_INFO, "VPSS report fade last frame failed!\n");
			}
        }
		else
		{
			FailedNum++;		
            OmxPrint(OMX_INFO, "Get last frame buffer failed, retry!\n");
		    msleep(5);
		}

		if (FailedNum > 100)
		{
			return HI_FAILURE;
		}
		
    }while(ret != HI_SUCCESS);

    return HI_SUCCESS;
}

static HI_S32 processor_event_handler(HI_HANDLE ChanId, HI_DRV_VPSS_EVENT_E enEventID, HI_VOID *pstArgs)
{
    HI_S32 ret = HI_FAILURE;
    OMXVDEC_CHAN_CTX *pchan = HI_NULL;

    if (HI_NULL == pstArgs)
    {
        OmxPrint(OMX_FATAL, "%s enEventID = %d, pstArgs = NULL!\n", __func__, enEventID);
        return HI_FAILURE;
    }

    pchan = channel_find_inst_by_channel_id(g_OmxVdec, ChanId);
    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s can't find Chan(%d).\n", __func__, ChanId);
    	 return HI_FAILURE;
    }

    /* Event handle */
    switch (enEventID)
    {
        case VPSS_EVENT_CHECK_FRAMEBUFFER:
            ret = channel_check_avaible_frame_buffer(pchan);
		    if (HI_SUCCESS == ret)
		    {
		        ((HI_DRV_VPSS_BUFINFO_S*)pstArgs)->bAvailable = HI_TRUE;
		    }
		    else
		    {
			    ((HI_DRV_VPSS_BUFINFO_S*)pstArgs)->bAvailable = HI_FALSE;
		    }
	        break;

        case  VPSS_EVENT_BUFLIST_FULL:
            //VPSS使用外部BUFFER，不应该报这个消息
            OmxPrint(OMX_WARN, "%s, VPSS_EVENT_BUFLIST_FULL, not expected.\n", __func__);
            break;

        case  VPSS_EVENT_GET_FRMBUFFER:
            ret = processor_get_frame_buffer(pchan, pstArgs);
            if(ret != HI_SUCCESS)
            {
                return HI_FAILURE;
            }
            break;

        case  VPSS_EVENT_REL_FRMBUFFER:
            ret = processor_release_frame_buffer(pchan, pstArgs);
            if(ret != HI_SUCCESS)
            {
                return HI_FAILURE;
            }
            break;

        case  VPSS_EVENT_NEW_FRAME:
            ret = processor_report_new_frame(pchan, pstArgs);
            if(ret != HI_SUCCESS)
            {
                return HI_FAILURE;
            }
            break;

        default:
            OmxPrint(OMX_ERR, "%s Unknow enEventID: %d\n", __func__, enEventID);
            return HI_FAILURE;
    }

    return HI_SUCCESS;

}

static HI_S32 processor_get_image(HI_S32 VpssId, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_S32 ret = HI_FAILURE;
    OMXVDEC_CHAN_CTX *pchan = HI_NULL;
    IMAGE stImage;
    HI_U32 u32fpsInteger = 0;
	HI_U32 u32fpsDecimal = 0;
    HI_DRV_VIDEO_PRIVATE_S *pstPrivInfo = HI_NULL;
    HI_VDEC_PRIV_FRAMEINFO_S *pstvdecPrivInfo = HI_NULL;

    if (HI_NULL == pstFrame)
    {
        OmxPrint(OMX_FATAL, "%s pstFrame = NULL!\n", __func__);
        return HI_FAILURE;
    }

	pchan = channel_find_inst_by_processor_id(g_OmxVdec, VpssId);
	if (HI_NULL == pchan)
    {
        OmxPrint(OMX_WARN, "%s can't find %d vpss channel\n", __func__, VpssId);
        return HI_FAILURE;
	}

    if (pchan->reset_pending)
    {
        OmxPrint(OMX_WARN, "%s chanel reset pending...\n", __func__);
        return HI_FAILURE;
    }

	/* read ready image struct from vfmw. */
    memset(&stImage, 0, sizeof(IMAGE));
    ret = pchan->image_ops.read_image(pchan->decoder_id, &stImage);
	if(ret != HI_SUCCESS)
    {
        if (VFMW_REPORT_LAST_FRAME == pchan->last_frame_info[0])
        {
            /* 最后一帧已经被拿走 / 最后一帧上报失败的情况处理 */
            if((pchan->last_frame_vpss_got == pchan->last_frame_image_id)
            || (REPORT_LAST_FRAME_FAIL == pchan->last_frame_info[1]))
            {
               OmxPrint(OMX_INFO, "VPSS got no frame to handle, report a fake one!\n");
               pchan->last_frame_info[0] = VPSS_GOT_LAST_FRAME;
               ret = processor_report_last_frame(pchan); /* 输出假的最后一帧 */

			   if (ret != HI_SUCCESS)
			   {
			       OmxPrint(OMX_ERR, "VPSS report fade last frame failed!\n");
			   }			   
            }
        }
        OmxPrint(OMX_VPSS, "VPSS read_image failed!\n");
        return HI_FAILURE;
	}

    pstPrivInfo                                 = (HI_DRV_VIDEO_PRIVATE_S*)(pstFrame->u32Priv);
    pstPrivInfo->u32BufferID                    = stImage.image_id;

    pstvdecPrivInfo                             = (HI_VDEC_PRIV_FRAMEINFO_S*)(pstPrivInfo->u32Reserve);
    pstvdecPrivInfo->image_id                   = stImage.image_id;
    pstvdecPrivInfo->image_id_1                 = stImage.image_id_1;
    pstvdecPrivInfo->stBTLInfo.u32BTLImageID    = stImage.BTLInfo.btl_imageid;
    pstvdecPrivInfo->stBTLInfo.u32Is1D          = stImage.BTLInfo.u32Is1D;

    /*Change IMAGE to HI_DRV_VIDEO_FRAME_S*/
    if ((stImage.format & 0x3000) != 0)
    {
        pstFrame->bTopFieldFirst = HI_TRUE;
    }
    else
    {
        pstFrame->bTopFieldFirst = HI_FALSE;
    }

    if(STD_H263 == pchan->protocol || STD_SORENSON == pchan->protocol )
    {
        pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21;
    }
    else
    {
        if(0 == stImage.is_1Dcompress)
        {
            switch ((stImage.format>>2)&7)
            {
                case 0:
                    pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_TILE;
                    break;
                case 1:
                    pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_TILE;
                    break;
                default:
                    pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_TILE;
                    break;
            }
        }
        else
        {
            switch ((stImage.format>>2)&7)
            {
                case 0:
                    pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_TILE_CMP;
                    break;
                case 1:
                    pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_TILE_CMP;
                    break;
                default:
                    pstFrame->ePixFormat = HI_DRV_PIX_FMT_NV21_TILE_CMP;
                    break;
            }
        }
    }

    switch (stImage.format & 0x300)
    {
        case 0x0: /* PROGRESSIVE */
            pstFrame->bProgressive = HI_TRUE;
            break;
        case 0x100: /* INTERLACE */
        case 0x200: /* INFERED_PROGRESSIVE */
        case 0x300: /* INFERED_INTERLACE */
        default:
            pstFrame->bProgressive = HI_FALSE;
            break;
    }
    if (stImage.disp_height <= 288)
    {
        pstFrame->bProgressive= HI_TRUE;
    }
    
    pchan->progress = pstFrame->bProgressive;

    switch (stImage.format & 0xC00)
    {
        case 0x400:
            pstFrame->enFieldMode = HI_DRV_FIELD_TOP;
            break;
        case 0x800:
            pstFrame->enFieldMode = HI_DRV_FIELD_BOTTOM;
            break;
        case 0xC00:
            pstFrame->enFieldMode = HI_DRV_FIELD_ALL;
            break;
        default:
            pstFrame->enFieldMode = HI_DRV_FIELD_BUTT;
            break;
    }

    if(STD_H263 == pchan->protocol || STD_SORENSON == pchan->protocol || STD_MJPEG == pchan->protocol)
    {
        pstFrame->stBufAddr[0].u32PhyAddr_Y        = stImage.top_luma_phy_addr;
        pstFrame->stBufAddr[0].u32Stride_Y         = stImage.image_stride;
        pstFrame->stBufAddr[0].u32PhyAddr_C        = stImage.top_chrom_phy_addr;
        pstFrame->stBufAddr[0].u32Stride_C         = pstFrame->stBufAddr[0].u32Stride_Y;
    }
    else
    {
        pstFrame->stBufAddr[0].u32PhyAddr_Y        = stImage.top_luma_phy_addr;
        pstFrame->stBufAddr[0].u32Stride_Y         = stImage.image_stride/16;
        pstFrame->stBufAddr[0].u32PhyAddr_C        = stImage.top_chrom_phy_addr;
        pstFrame->stBufAddr[0].u32Stride_C         = pstFrame->stBufAddr[0].u32Stride_Y;
    }

    //FOR MVC DEBUG
    if (stImage.is_3D)
    {
        pstFrame->stBufAddr[1].u32PhyAddr_Y        = stImage.top_luma_phy_addr_1;
        pstFrame->stBufAddr[1].u32Stride_Y         = stImage.image_stride/16;
        pstFrame->stBufAddr[1].u32PhyAddr_C        = stImage.top_chrom_phy_addr_1;
        pstFrame->stBufAddr[1].u32Stride_C         = pstFrame->stBufAddr[1].u32Stride_Y;
    }

    pstFrame->u32AspectWidth                   = stImage.u32AspectWidth;
    pstFrame->u32AspectHeight                  = stImage.u32AspectHeight;
    pstFrame->u32Width                         = stImage.disp_width;
    pstFrame->u32Height                        = stImage.disp_height;

    pstFrame->u32ErrorLevel                    = stImage.error_level;
    pstFrame->s64OmxPts                        = stImage.SrcPts;
    pstFrame->u32FrameIndex                    = stImage.seq_img_cnt;
    
    if (STD_MVC == pchan->protocol)
    {
        switch(stImage.eFramePackingType)
        {
        case FRAME_PACKING_TYPE_NONE:
            pstFrame->eFrmType = HI_DRV_FT_NOT_STEREO;
            break;
        case FRAME_PACKING_TYPE_SIDE_BY_SIDE:
            pstFrame->eFrmType = HI_DRV_FT_SBS;
            break;
        case FRAME_PACKING_TYPE_TOP_BOTTOM:
            pstFrame->eFrmType = HI_DRV_FT_TAB;
            break;
        case FRAME_PACKING_TYPE_TIME_INTERLACED:
            pstFrame->eFrmType = HI_DRV_FT_FPK;
            break;
        default:
            pstFrame->eFrmType = FRAME_PACKING_TYPE_BUTT;
            break;
        }
    }

    u32fpsInteger                               = stImage.frame_rate/1000;
    u32fpsDecimal                               = stImage.frame_rate%1000;
    pstFrame->u32FrameRate                      = u32fpsInteger*1000 + (u32fpsDecimal + 500) / 1000;

    if (1 == stImage.last_frame)
    {
        pchan->last_frame_image_id = REALID(stImage.image_id);
    }

    pchan->last_frame_vpss_got = REALID(stImage.image_id);
    OmxPrint(OMX_VPSS, "VPSS read image success!\n");

    return 0;
}

static HI_S32 processor_release_image(HI_S32 VpssId, HI_DRV_VIDEO_FRAME_S *pstFrame)
{
    HI_S32 ret = HI_FAILURE;
    IMAGE stImage;
    OMXVDEC_CHAN_CTX *pchan = HI_NULL;
    HI_DRV_VIDEO_PRIVATE_S* pstPrivInfo = HI_NULL;
    HI_VDEC_PRIV_FRAMEINFO_S* pstVdecPrivInfo = HI_NULL;

    if (HI_NULL == pstFrame)
    {
        OmxPrint(OMX_FATAL, "%s pstFrame = NULL!\n", __func__);
        return HI_FAILURE;
    }

	pchan = channel_find_inst_by_processor_id(g_OmxVdec, VpssId);
	if (HI_NULL == pchan)
    {
         OmxPrint(OMX_FATAL, "%s can't find vpss(%d) Chan.\n", __func__, VpssId);
         return HI_FAILURE;
	}

    pstPrivInfo = (HI_DRV_VIDEO_PRIVATE_S*)(pstFrame->u32Priv);
    pstVdecPrivInfo = (HI_VDEC_PRIV_FRAMEINFO_S*)(pstPrivInfo->u32Reserve);

    memset(&stImage, 0, sizeof(IMAGE));
    stImage.image_stride         = pstFrame->stBufAddr[0].u32Stride_Y;
    stImage.disp_height          = pstFrame->u32Height;
    stImage.disp_width           = pstFrame->u32Width;
    stImage.luma_phy_addr        = pstFrame->stBufAddr[0].u32PhyAddr_Y;
    stImage.top_luma_phy_addr    = pstFrame->stBufAddr[0].u32PhyAddr_Y;

    stImage.image_id             = pstVdecPrivInfo->image_id;
    stImage.image_id_1           = pstVdecPrivInfo->image_id_1;
    stImage.BTLInfo.btl_imageid  = pstVdecPrivInfo->stBTLInfo.u32BTLImageID;
    stImage.BTLInfo.u32Is1D      = pstVdecPrivInfo->stBTLInfo.u32Is1D;

	ret = pchan->image_ops.release_image(pchan->decoder_id, &stImage);
	if (ret != HI_SUCCESS)
    {
         OmxPrint(OMX_ERR, "%s call release_image failed!\n", __func__);
	     return HI_FAILURE;
	}

	OmxPrint(OMX_VPSS, "VPSS release image success!\n");
    return HI_SUCCESS;
}


/*============== EXPORT FUNCTION =============*/
HI_S32 processor_init(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;

	OmxPrint(OMX_TRACE, "%s enter!\n", __func__);
    
    pVpssFunc = HI_NULL;
    
    /*Get vpss functions*/
    ret = HI_DRV_MODULE_GetFunction(HI_ID_VPSS, (HI_VOID**)&g_stOmxFunc.pProcessorFunc);
    if (HI_SUCCESS != ret || HI_NULL == g_stOmxFunc.pProcessorFunc)
    {
        OmxPrint(OMX_FATAL, "%s get vpss function failed!\n", __func__);
        return HI_FAILURE;
    }

    pVpssFunc = (VPSS_EXPORT_FUNC_S *)(g_stOmxFunc.pProcessorFunc);

    ret = (pVpssFunc->pfnVpssGlobalInit)();
    if (ret != HI_SUCCESS)
    {
        pVpssFunc = g_stOmxFunc.pProcessorFunc = HI_NULL;
        OmxPrint(OMX_FATAL, "%s init vpss failed!\n", __func__);
        return HI_FAILURE;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 processor_exit(HI_VOID)
{
    HI_S32 ret = HI_FAILURE;
    
	OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    ret = (pVpssFunc->pfnVpssGlobalDeInit)();
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s exit vpss failed!\n", __func__);
        return HI_FAILURE;
    }
    
    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 processor_create_inst(OMXVDEC_CHAN_CTX *pchan, HI_U32 color_format)
{
    HI_S32 ret;
    HI_DRV_VPSS_CFG_S stVpssCfg;
    HI_DRV_VPSS_SOURCE_FUNC_S stRegistSrcFunc;
    HI_DRV_VPSS_PORT_CFG_S stVpssPortCfg;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL!\n", __func__);
        return HI_FAILURE;
    }

	pchan->processor_id  = VPSS_INVALID_HANDLE;
	pchan->port_id       = VPSS_INVALID_HANDLE;

    ret = (pVpssFunc->pfnVpssGetDefaultCfg)(&stVpssCfg);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_GetDefaultCfg failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }

    stVpssCfg.bProgRevise = g_DeInterlaceEnable; //开关DEI
    ret = (pVpssFunc->pfnVpssCreateVpss)(&stVpssCfg, &pchan->processor_id);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_CreateVpss failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssRegistHook)(pchan->processor_id, pchan->channel_id, processor_event_handler);
    if (ret != HI_SUCCESS)
    {
         OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_RegistHook failed, ret = %d\n", __func__, ret);
         goto error;
    }

    stRegistSrcFunc.VPSS_GET_SRCIMAGE = processor_get_image;
    stRegistSrcFunc.VPSS_REL_SRCIMAGE = processor_release_image;
    ret = (pVpssFunc->pfnVpssSetSourceMode)(pchan->processor_id, VPSS_SOURCE_MODE_VPSSACTIVE, &stRegistSrcFunc);
    if (ret != HI_SUCCESS)
    {
         OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_SetSourceMode failed, ret = %d\n", __func__, ret);
         goto error;
    }

    ret = (pVpssFunc->pfnVpssGetDefaultPortCfg)(&stVpssPortCfg);
    if (ret != HI_SUCCESS)
    {
         OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_GetDefaultPortCfg failed, ret = %d\n", __func__, ret);
         goto error;
    }
	OmxPrint(OMX_FATAL, "%s color_format = %d\n", __func__, color_format);
    pchan->color_format                 = color_format;
    stVpssPortCfg.s32OutputWidth        = 0;    // 宽高设为0表示根据输入自适应配置
    stVpssPortCfg.s32OutputHeight       = 0;
    stVpssPortCfg.eFormat               = color_format;
    stVpssPortCfg.stBufListCfg.eBufType = HI_DRV_VPSS_BUF_USER_ALLOC_MANAGE;
    if (HI_TRUE == g_FrameRateLimit)
    {
        // 因为后级GPU处理不了P60，这里做一下限制
        stVpssPortCfg.u32MaxFrameRate = 30;
    }
    else
    {
        stVpssPortCfg.u32MaxFrameRate = 30000;
    }
    if (STD_MVC == pchan->protocol)
    {
        stVpssPortCfg.b3Dsupport = HI_TRUE;
    }

    ret = (pVpssFunc->pfnVpssCreatePort)(pchan->processor_id, &stVpssPortCfg, &pchan->port_id);
    if (ret != HI_SUCCESS)
    {
         OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_CreatePort failed, ret = %d\n", __func__, ret);
         goto error;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;

error:
    (pVpssFunc->pfnVpssDestroyVpss)(pchan->processor_id);
    pchan->processor_id = VPSS_INVALID_HANDLE;

    return HI_FAILURE;
}

HI_S32 processor_release_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL!\n", __func__);
        return HI_FAILURE;
    }

    if (VPSS_INVALID_HANDLE == pchan->port_id)
    {
        OmxPrint(OMX_FATAL, "%s port_id = VPSS_INVALID_HANDLE\n", __func__);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssDestroyPort)(pchan->port_id);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_DestroyPort failed, ret = %d\n", __func__, ret);
    }

    pchan->port_id = VPSS_INVALID_HANDLE;
    
    if (VPSS_INVALID_HANDLE == pchan->processor_id)
    {
        OmxPrint(OMX_FATAL, "%s hVpss = VPSS_INVALID_HANDLE\n", __func__);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssDestroyVpss)(pchan->processor_id);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_DestroyVpss failed, ret = %d\n", __func__, ret);
    }

    pchan->processor_id = VPSS_INVALID_HANDLE;

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 processor_start_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL!\n", __func__);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssEnablePort)(pchan->port_id, HI_TRUE);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_EnablePort failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssSendCommand)(pchan->processor_id, HI_DRV_VPSS_USER_COMMAND_START, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call start vpss failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }
    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 processor_stop_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL!\n", __func__);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssEnablePort)(pchan->port_id, HI_FALSE);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call HI_DRV_VPSS_EnablePort failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssSendCommand)(pchan->processor_id, HI_DRV_VPSS_USER_COMMAND_STOP, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call stop vpss failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }
    
    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

HI_S32 processor_reset_inst(OMXVDEC_CHAN_CTX *pchan)
{
    HI_S32 ret;

    OmxPrint(OMX_TRACE, "%s enter!\n", __func__);

    if (HI_NULL == pchan)
    {
        OmxPrint(OMX_FATAL, "%s pchan = NULL!\n", __func__);
        return HI_FAILURE;
    }

    ret = (pVpssFunc->pfnVpssSendCommand)(pchan->processor_id, HI_DRV_VPSS_USER_COMMAND_RESET, HI_NULL);
    if (ret != HI_SUCCESS)
    {
        OmxPrint(OMX_FATAL, "%s call reset vpss failed, ret = %d\n", __func__, ret);
        return HI_FAILURE;
    }

    OmxPrint(OMX_TRACE, "%s exit normally!\n", __func__);

    return HI_SUCCESS;
}

