/*******************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: had-dma.c
 * Description: aiao alsa dma interface
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main\1    HISI Audio Team
 ********************************************************************************/
#include <linux/module.h>
#include <linux/moduleparam.h>
#include <linux/init.h>
#include <linux/err.h>
#include <linux/platform_device.h>
#include <linux/errno.h>
#include <linux/ioctl.h>
#include <linux/delay.h>
#include <linux/slab.h>
#include <linux/timer.h>
#include <linux/kthread.h>
#include <linux/interrupt.h>
#include <linux/dma-mapping.h>
#include <asm/io.h>
#include <linux/jiffies.h>
#include <linux/time.h>
#include <linux/wait.h>
#ifdef CONFIG_PM
 #include <linux/pm.h>
#endif
#include <sound/core.h>
#include <sound/pcm.h>
#include <sound/control.h>
#include <sound/initval.h>
#include <sound/pcm_params.h>
#include <sound/soc.h>

#include "drv_ao_hw_func.h"
#include "alsa_aiao_hw_proc_func.h"
#include "alsa_aiao_hw_comm.h"
#include "hi_drv_ao.h"

#include "hi_drv_ai.h"
#include "drv_ai_ioctl.h"
#include "drv_ai_func.h"
#include "hi_drv_mmz.h"
#include "hi_drv_proc.h"
#include "hi_drv_dev.h"
#include "drv_ai_private.h"

#include "drv_ao_ioctl.h"
#include "drv_ao_private.h"

#define DSP0TOA9_IRQ_NUM  51
#define AO_BUFFER_SIZE    1024*32
#define INITIAL_VALUE  0xffffffff
#define AIAO_DF_PeriodBufSize 2048

//#define AIAO_ALSA_DEBUG
#ifdef AIAO_ALSA_DEBUG
#define ATRP()    printk(KERN_ALERT"\nfunc:%s line:%d \n", __func__, __LINE__)
#define ATRC    printk
#else
#define ATRP() 
#define ATRC(fmt, ...) 
#endif

//#define ALSA_TIME_DEBUG
#ifdef  ALSA_TIME_DEBUG
static struct timespec curtime;
static struct timeval end_time,start_time;
static unsigned long time_coast;
static struct timeval end_time_free,start_time_free;
static unsigned long time_coast_free;
#endif

#ifdef CONFIG_AIAO_ALSA_PROC_SUPPORT
#define ALSA_PROC_AO_NAME "hi_hw_i2s_ao_data"
#define ALSA_PROC_AI_NAME "hi_hw_i2s_ai_data"
#endif

static const struct snd_pcm_hardware aiao_hw_hardware = {
	.info			= SNDRV_PCM_INFO_MMAP |
				  SNDRV_PCM_INFO_MMAP_VALID |
				  SNDRV_PCM_INFO_INTERLEAVED |
				  SNDRV_PCM_INFO_BLOCK_TRANSFER |
				  SNDRV_PCM_INFO_PAUSE |
				  SNDRV_PCM_INFO_RESUME,
	.formats		= SNDRV_PCM_FMTBIT_S16_LE |
				  SNDRV_PCM_FMTBIT_S24_LE,
    .rates = AIAO_RATES,
	.channels_min		= 2,
	.channels_max	= 2,
	.period_bytes_min	= 960,     
    .period_bytes_max	= 4096,    
	.periods_min		= 4,
	.periods_max		= 8,
	.buffer_bytes_max	= AO_BUFFER_SIZE,
};

#define I2S_ONLY_SND HI_UNF_SND_0
static AO_ALSA_I2S_Param_S stAOI2sAlsaAttr;
void hi_setup_dma(struct hii2saudio_data *had )
{
    unsigned int real_size = had->sthwparam.period_size*had->sthwparam.frame_size;

    hi_ao_alsa_update_writeptr(I2S_ONLY_SND,&(real_size));  

}
void hi_start_dma(struct hii2saudio_data *had )
{
    unsigned int real_size = (had->sthwparam.period_size*had->sthwparam.frame_size)*3;
    hi_ao_alsa_update_writeptr(I2S_ONLY_SND,&(real_size));  
}
static irqreturn_t IsrAOFunc(AIAO_PORT_ID_E enPortID,HI_U32 u32IntRawStatus,void * dev_id)
{
    struct snd_pcm_substream *substream = dev_id;
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
  //  ATRP();
     had->aiao_isr_num++;
     hi_ao_alsa_query_readpos(I2S_ONLY_SND,&(had->hw_readpos));
     had->runtime_appl_offset = (had->sthwparam.period_size*had->sthwparam.frame_size)*(had->aiao_isr_num);;

     hi_setup_dma(had);
	 snd_pcm_period_elapsed(substream); 

     had->IsrAoProc(enPortID,u32IntRawStatus,NULL);
	 return IRQ_HANDLED;
}

static AI_ALSA_Param_S stAII2sAlsaAttr;
static irqreturn_t IsrAIFunc(AIAO_PORT_ID_E enPortID,HI_U32 u32IntRawStatus,void * dev_id)
{
    struct snd_pcm_substream *substream = dev_id;
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
   // unsigned int readpos = AIAO_DF_PeriodBufSize;
    unsigned int readpos = had->sthwparam_ai.period_size*had->sthwparam_ai.frame_size;
    had->isr_total_cnt_c++;

    hi_ai_alsa_query_writepos(had->ai_handle,&(had->ai_writepos));
    hi_ai_alsa_query_readpos(had->ai_handle,&(had->ai_readpos));
    hi_ai_alsa_update_readptr(had->ai_handle, &(readpos));

    if(had->isr_total_cnt_c <= 8)
    {
        ATRC("get write pos is %d,and get readpos is %d,update read ptr is %d\n ",had->ai_writepos,had->ai_readpos,readpos);
    }
    
	 snd_pcm_period_elapsed(substream); 	
     had->IsrAiProc(enPortID,u32IntRawStatus,NULL);
	 return IRQ_HANDLED;
}

static int hi_hw_dma_prepare(struct snd_pcm_substream *substream)
{
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);

    ATRP();
 
	if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
	{
		had->ai_writepos = 0;
        had->ai_readpos = 0;
        had->isr_total_cnt_c = 0;
        return hi_ai_alsa_flush_buffer(had->ai_handle);
	}
	else
	{
        had->local_isr_num = 0;
        had->aiao_isr_num  =0;          
        return ao_dma_flushbuf(I2S_ONLY_SND);    
    }
}
static int hi_hw_dma_trigger(struct snd_pcm_substream *substream, int cmd)
{
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
    int ret = 0;

    ATRC("trigger cmd id %d\n",cmd);
    switch(cmd) 
    {
    case SNDRV_PCM_TRIGGER_START:
    case SNDRV_PCM_TRIGGER_RESUME:
    case SNDRV_PCM_TRIGGER_PAUSE_RELEASE:
        if(substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
        {           

           ret = ao_dma_start(I2S_ONLY_SND, NULL);
            if(ret)
            {   
                ATRC("AIAO ALSA start dma Fail \n");
            }
            hi_start_dma(had);
        }
        if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
        {
          ret =  hi_ai_alsa_setEnable(had->ai_handle,&had->cfile,HI_TRUE);
          if(ret)
          {   
               ATRC("AI ALSA start dma Fail \n");
          }
        }
        break;
    case SNDRV_PCM_TRIGGER_STOP:
    case SNDRV_PCM_TRIGGER_SUSPEND:
    case SNDRV_PCM_TRIGGER_PAUSE_PUSH:
        if(substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
        {
            ret = ao_dma_stop(I2S_ONLY_SND, NULL);
          if(ret)
            {
              ATRC("AIAO ALSA stop dma Fail \n");
            }
        }
        if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
        {
            ret = hi_ai_alsa_setEnable(had->ai_handle,&had->cfile,HI_FALSE);
            if(ret)
            {   
               ATRC("AI ALSA stop dma Fail \n");
            }

        }
        break;        
    default:
        ret = -EINVAL;
        break;
    }
    return 0;
}

static int hi_hw_dma_mmap(struct snd_pcm_substream *substream,
	struct vm_area_struct *vma)
{
    //TODO 
#if 1   
    struct snd_pcm_runtime *runtime = substream->runtime;
    int ret;
    unsigned int size;
    ATRP();

    vma->vm_flags |= VM_IO;
    vma->vm_page_prot = pgprot_noncached(vma->vm_page_prot);
    size = vma->vm_end - vma->vm_start;

    //here  just for kernel ddr linear area
    ret = io_remap_pfn_range(vma,
                vma->vm_start,
                runtime->dma_addr >> PAGE_SHIFT,
                size, 
                vma->vm_page_prot);

    if (ret)
        return -EAGAIN;
#endif
	return 0;
}

static snd_pcm_uframes_t hi_hw_dma_pointer(struct snd_pcm_substream *substream)
{
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
    snd_pcm_uframes_t frame_offset = 0;
    unsigned int bytes_offset = 0;

    had->local_isr_num++;
	if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
	{
		bytes_offset = had->ai_writepos;
	}
	else
	{
        bytes_offset = had->hw_readpos;
	}    
	
    if(bytes_offset >= snd_pcm_lib_buffer_bytes(substream))
 	   bytes_offset = 0;
     
    frame_offset = bytes_to_frames(runtime, bytes_offset);
    return frame_offset;
}



static void hi_aiao_set_params(struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params,struct snd_pcm_runtime *runtime)
{
     if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
     {
        stAII2sAlsaAttr.IsrFunc                 =(AIAO_IsrFunc*)IsrAIFunc;
        stAII2sAlsaAttr.substream               =(void*)substream;
        stAII2sAlsaAttr.stBuf.u32BufPhyAddr     = runtime->dma_addr;    // for dma buffer
        stAII2sAlsaAttr.stBuf.u32BufVirAddr     = (int)runtime->dma_area;
        stAII2sAlsaAttr.stBuf.u32BufSize        = runtime->dma_bytes;
        stAII2sAlsaAttr.stBuf.u32PeriodByteSize = params_buffer_bytes(params)/params_periods(params);
        stAII2sAlsaAttr.stBuf.u32Periods        = params_periods(params);
     
     }
     else
     {
         stAOI2sAlsaAttr.IsrFunc                 =(AIAO_IsrFunc*)IsrAOFunc;
         stAOI2sAlsaAttr.substream               =(void*)substream;
         stAOI2sAlsaAttr.stBuf.u32BufPhyAddr     = runtime->dma_addr;    // for dma buffer
         stAOI2sAlsaAttr.stBuf.u32BufVirAddr     = (int)runtime->dma_area;
         stAOI2sAlsaAttr.stBuf.u32BufSize        = runtime->dma_bytes; 
         stAOI2sAlsaAttr.stBuf.u32PeriodByteSize = params_buffer_bytes(params)/params_periods(params);
         stAOI2sAlsaAttr.stBuf.u32Periods        = params_periods(params);
         stAOI2sAlsaAttr.enRate                  = params_rate(params);
         stAOI2sAlsaAttr.bAlsaI2sUse             = HI_TRUE;    
     
     }
}


static int hi_hw_dma_hwparams(struct snd_pcm_substream *substream,
    struct snd_pcm_hw_params *params)
{
    unsigned int buffer_bytes;
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_pcm_runtime *runtime = substream->runtime;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
    HI_UNF_SND_ATTR_S stAttr;
    int ret = 0;
	HI_UNF_AI_ATTR_S pstAiAttr;
	AI_Create_Param_S stAiParam;
    AO_SND_Open_Param_S stAoParam;
    
    ATRP();
    buffer_bytes = params_buffer_bytes(params);
    
    if(snd_pcm_lib_malloc_pages(substream, buffer_bytes) < 0)
        return -ENOMEM;

   if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
   	{   
   		memset(&pstAiAttr,0,sizeof(pstAiAttr));
		memset(&stAiParam,0,sizeof(stAiParam));
		
   		ret = hi_ai_alsa_get_attr(HI_UNF_AI_I2S0,&pstAiAttr);
		if(HI_SUCCESS != ret)
		{
			ret = -EINVAL;
			goto err_AllocateDma;
		}  

        pstAiAttr.enSampleRate =  params_rate(params);
        pstAiAttr.unAttr.stI2sAttr.stAttr.enChannel = params_channels(params);
         switch (params_format(params)) {
         case SNDRV_PCM_FORMAT_S16_LE:
         	pstAiAttr.unAttr.stI2sAttr.stAttr.enBitDepth = HI_UNF_I2S_BIT_DEPTH_16;
         	break;
         case SNDRV_PCM_FMTBIT_S24_LE:
         	pstAiAttr.unAttr.stI2sAttr.stAttr.enBitDepth = HI_UNF_I2S_BIT_DEPTH_24;
         	break;
         default:
             break;
         }
#ifdef AIAO_ALSA_DEBUG
       printk("rate : %d\n", pstAiAttr.enSampleRate);
       printk("channel : %d\n", pstAiAttr.unAttr.stI2sAttr.stAttr.enChannel);
       printk("bitdepth : %d\n", pstAiAttr.unAttr.stI2sAttr.stAttr.enBitDepth);
#endif
       ret = hi_ai_alsa_get_proc_func(&had->IsrAiProc);//get proc func
       if(HI_SUCCESS != ret)
       {
            ret = -EINVAL;
            goto err_AllocateDma;
       }
       
       hi_aiao_set_params(substream,params,runtime);

       stAiParam.pAlsaPara = (void *)&stAII2sAlsaAttr;
       stAiParam.enAiPort = HI_UNF_AI_I2S0;
       memcpy(&stAiParam.stAttr, &pstAiAttr, sizeof(HI_UNF_AI_ATTR_S));    

	   ret = hi_ai_alsa_open(&stAiParam,&had->cfile);
	   if(HI_SUCCESS != ret)
	   {
		    ret = -EINVAL;
            goto err_AllocateDma;
	   }
       
		had->ai_handle = stAiParam.hAi; 
        
#ifdef AIAO_ALSA_DEBUG
		ATRC("\nbuffer_bytes : 0x%x \n", buffer_bytes);
		ATRC("\n pstAiAttr.enSampleRate : 0x%d \n", (int)pstAiAttr.enSampleRate);
		ATRC("\n pstAiAttr.u32PcmFrameMaxNum : 0x%d \n", pstAiAttr.u32PcmFrameMaxNum);
		ATRC("\n pstAiAttr.u32PcmSamplesPerFrame : 0x%d \n", pstAiAttr.u32PcmSamplesPerFrame);
        ATRC("\n pstAiAttr.bAlsaUse : 0x%d \n", stAiParam.bAlsaUse);
		ATRC("\nruntime->dma_addr : %d \n", runtime->dma_addr);
		ATRC("\(int)runtime->dma_area : %d \n", (int)runtime->dma_area);
		ATRC("\nruntime->dma_bytes : %d \n", runtime->dma_bytes);
		ATRC("\nhad->ai_handle is %d\n", had->ai_handle);
#endif
        had->sthwparam_ai.channels = params_channels(params);
        had->sthwparam_ai.rate = params_rate(params);
        had->sthwparam_ai.format = params_format(params);
        had->sthwparam_ai.periods = params_periods(params);
        had->sthwparam_ai.period_size = params_period_size(params);
        had->sthwparam_ai.buffer_size = params_buffer_size(params);
        had->sthwparam_ai.buffer_bytes = params_buffer_bytes(params);
        
        switch (had->sthwparam_ai.format) 
		{
            case SNDRV_PCM_FORMAT_S16_LE:
                had->sthwparam_ai.frame_size = 2 * had->sthwparam_ai.channels;
                break;
            case SNDRV_PCM_FMTBIT_S24_LE:
                had->sthwparam_ai.frame_size = 3 * had->sthwparam_ai.channels;
                break;
            default:
                break;
        }
        
#ifdef AIAO_ALSA_DEBUG
        printk("\nhad->sthwparam_ai.channels : %d", had->sthwparam_ai.channels);
        printk("\nhad->sthwparam_ai.rate : %d", had->sthwparam_ai.rate);
        printk("\nhad->sthwparam_ai.periods : %d", had->sthwparam_ai.periods);
        printk("\nhad->sthwparam_ai.period_size : %d", (int)had->sthwparam_ai.period_size);
        printk("\nhad->sthwparam_ai.buffer_size : %d", (int)had->sthwparam_ai.buffer_size);
        printk("\nhad->sthwparam_ai.frame_size : %d", had->sthwparam_ai.frame_size);
#endif       

   	}
   else
   	{
       if(had->open_cnt == 0)
       {            
         ao_dma_gethwparam(&stAttr);
 
         stAttr.enSampleRate =  params_rate(params);
         stAttr.stOutport[0].unAttr.stI2sAttr.stAttr.enChannel = params_channels(params);
          switch (params_format(params)) 
		  {
              case SNDRV_PCM_FORMAT_S16_LE:
              	stAttr.stOutport[0].unAttr.stI2sAttr.stAttr.enBitDepth = HI_UNF_I2S_BIT_DEPTH_16;
              	break;
              case SNDRV_PCM_FMTBIT_S24_LE:
              	stAttr.stOutport[0].unAttr.stI2sAttr.stAttr.enBitDepth = HI_UNF_I2S_BIT_DEPTH_24;
              	break;
              default:
                  break;
          }
          ret = hi_ao_alsa_get_proc_func(&had->IsrAoProc);//get proc func
          hi_aiao_set_params(substream,params,runtime);
#ifdef AIAO_ALSA_DEBUG
        printk("rate : %d\n", stAttr.enSampleRate);
        printk("PortNum : %d\n", stAttr.u32PortNum );
        printk("enOutPort : %d\n", stAttr.stOutport[0].enOutPort);
        printk("\nbuffer byte : %d", params_buffer_bytes(params));
        printk("\nperiods is %d\n", params_periods(params));
#endif
        stAoParam.pAlsaPara = (void *)&stAOI2sAlsaAttr; 
        stAoParam.enSound = I2S_ONLY_SND;    
        memcpy(&stAoParam.stAttr, &stAttr, sizeof(HI_UNF_SND_ATTR_S)); 
        ret = ao_dma_open(&stAoParam, &had->file);
        if(HI_SUCCESS != ret)
        {
            ret =  -EINVAL;             //TODO  different sample rete  
            goto err_AllocateDma;
        }    
  
        had->open_cnt++;
      }
 
    had->sthwparam.channels = params_channels(params);
    had->sthwparam.rate = params_rate(params);
    had->sthwparam.format = params_format(params);
    had->sthwparam.periods = params_periods(params);
    had->sthwparam.period_size = params_period_size(params);
    had->sthwparam.buffer_size = params_buffer_size(params);
    had->sthwparam.buffer_bytes = params_buffer_bytes(params);

    switch (had->sthwparam.format) 
	{
        case SNDRV_PCM_FORMAT_S16_LE:
        	had->sthwparam.frame_size = 2 * had->sthwparam.channels;
        	break;
        case SNDRV_PCM_FMTBIT_S24_LE:
        	had->sthwparam.frame_size = 3 * had->sthwparam.channels;
        	break;
        default:
            break;
    }
    
    #ifdef AIAO_ALSA_DEBUG
    printk("\nhad->sthwparam.channels : %d", had->sthwparam.channels);
    printk("\nhad->sthwparam.rate : %d", had->sthwparam.rate);
    printk("\nhad->sthwparam.periods : %d", had->sthwparam.periods);
    printk("\nhad->sthwparam.period_size : %d", (int)had->sthwparam.period_size);
    printk("\nhad->sthwparam.buffer_size : %d", (int)had->sthwparam.buffer_size);
    printk("\nhad->sthwparam.frame_size : %d", had->sthwparam.frame_size);
    #endif   
 }

 return ret;
err_AllocateDma:
 ret = snd_pcm_lib_free_pages(substream);
 return HI_FAILURE;
}

static int hi_hw_dma_hwfree(struct snd_pcm_substream *substream)
{
    int ret = HI_SUCCESS;
    return ret;
}
static int hi_hw_dma_open(struct snd_pcm_substream *substream)
{
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
    int ret = 0;
 
    ATRP();
    ret = snd_soc_set_runtime_hwparams(substream, &aiao_hw_hardware);
    if(ret)
        return ret;

    ret = snd_pcm_hw_constraint_integer(substream->runtime, SNDRV_PCM_HW_PARAM_PERIODS);
    if(substream->stream == SNDRV_PCM_STREAM_PLAYBACK)
    {    

        had->open_cnt = 0;
        had->hw_readpos = 0;
        //isr
        had->aiao_isr_num = 0;
        had->local_isr_num = 0;    
        had->runtime_appl_offset = 0;      
    }
    return ret;
}

static int hi_hw_dma_close(struct snd_pcm_substream *substream)
{
    struct snd_soc_pcm_runtime *soc_rtd = substream->private_data;
    struct snd_soc_platform *platform = soc_rtd->platform;
    struct hii2saudio_data *had = snd_soc_platform_get_drvdata(platform);
    int ret;

    ATRP();
    #ifdef CONFIG_AIAO_ALSA_PROC_SUPPORT
    hiaudio_hw_proc_cleanup((void*)had);
    #endif

	if(substream->stream == SNDRV_PCM_STREAM_CAPTURE)
	{
       if(INITIAL_VALUE != had->ai_handle)
  		{
           ret = hi_ai_alsa_destroy(had->ai_handle,&had->cfile);
  			if(ret)
               ATRC("ai destroy fail  num =%d fail !\n", had->ai_handle);
  			else 
               had->ai_handle = INITIAL_VALUE;
  		}
        had->isr_total_cnt_c = 0;       
	}		
    else
    {
       if(had->open_cnt ==1)
       {  
          ret = ao_dma_close(&had->file,I2S_ONLY_SND);
          if(ret)
              ATRC("\n  ao_dma_close fail !\n");
          else
               had->open_cnt = 0;
        
          hi_ao_alsa_set_proc_func(had->IsrAoProc);
       }
    }
    snd_pcm_lib_free_pages(substream);
    return HI_SUCCESS;
}

static struct snd_pcm_ops hi_hw_dma_ops = {
    .open = hi_hw_dma_open,
    .close = hi_hw_dma_close,
    .ioctl  = snd_pcm_lib_ioctl,
    .hw_params = hi_hw_dma_hwparams,
    .hw_free = hi_hw_dma_hwfree,
    .prepare = hi_hw_dma_prepare,
    .trigger = hi_hw_dma_trigger,
    .pointer = hi_hw_dma_pointer,
    .mmap = hi_hw_dma_mmap,
//    .ack = hi_hw_dma_ack,
};

static int hi_hw_dma_pcm_new(struct snd_soc_pcm_runtime *rtd)
{
    struct snd_pcm *pcm = rtd->pcm;
    int ret = 0;
    if(pcm->streams[SNDRV_PCM_STREAM_PLAYBACK].substream || 
        pcm->streams[SNDRV_PCM_STREAM_CAPTURE].substream)
    {
        ret = snd_pcm_lib_preallocate_pages_for_all(pcm, SNDRV_DMA_TYPE_DEV,NULL,
        AO_BUFFER_SIZE, AO_BUFFER_SIZE / 2);
        if(ret)
        {
            ATRC("dma buffer allocation fail \n");
            return ret;
        }
    }
    return ret;
}

static void hi_hw_dma_pcm_free(struct snd_pcm *pcm)
{
    snd_pcm_lib_preallocate_free_for_all(pcm);
}

static int hi_hw_dma_probe(struct snd_soc_platform *soc_platform)
{
    int ret = 0;
    
#ifdef CONFIG_AIAO_ALSA_PROC_SUPPORT
    struct hii2saudio_data *had = dev_get_drvdata(soc_platform->dev);
    ret = hiaudio_ao_hw_proc_init(soc_platform->card->snd_card, ALSA_PROC_AO_NAME, had);
    ret = hiaudio_ai_hw_proc_init(soc_platform->card->snd_card, ALSA_PROC_AI_NAME, had);   
#endif    
    return ret;
}

static struct snd_soc_platform_driver aiao_soc_hw_platform_drv =
{
    .ops         = &hi_hw_dma_ops,
    .pcm_new   = hi_hw_dma_pcm_new,
    .pcm_free   = hi_hw_dma_pcm_free,
    .probe      = hi_hw_dma_probe,
};


static int __init soc_hw_snd_platform_probe(struct platform_device *pdev)
{
    struct hii2saudio_data *had;
    int ret = -EINVAL;

    had = kzalloc(sizeof(struct hii2saudio_data), GFP_KERNEL);
    if(had == NULL)
        return -ENOMEM;

    dev_set_drvdata(&pdev->dev, had);

    //init had data struct
    mutex_init(&had->mutex);
    had->open_cnt = 0;
    had->hw_readpos = 0;
    had->local_isr_num = 0;
    had->aiao_isr_num = 0;
	had->ai_writepos = 0;
    had->ai_readpos = 0;
	had->ai_handle = INITIAL_VALUE;
    had->isr_total_cnt_c = 0;
    memset(&had->sthwparam, 0, sizeof(struct hisi_aiao_hw_hwparams));
    memset(&had->sthwparam_ai, 0, sizeof(struct hisi_aiao_hw_hwparams));

#ifdef CONFIG_AIAO_ALSA_PROC_SUPPORT
    had->entry = NULL;
#endif
    ret = snd_soc_register_platform(&pdev->dev, &aiao_soc_hw_platform_drv);
    if (ret < 0)
        goto err;

    return ret;
err:
    kfree(had);
    return ret;
}

static int __exit soc_hw_snd_platform_remove(struct platform_device *pdev)
{
    struct hii2saudio_data *had = dev_get_drvdata(&pdev->dev);

    if(had)
        kfree(had);

#ifdef CONFIG_AIAO_ALSA_PROC_SUPPORT
  ///  hiaudio_hw_proc_cleanup();
#endif
    snd_soc_unregister_platform(&pdev->dev);
    return 0;
}

static struct platform_driver hiaudio_hw_dma_driver = {
    .driver = {
        .name = "hisi-audio-i2s",
        .owner = THIS_MODULE,
    },
    .probe = soc_hw_snd_platform_probe,
    .remove = __exit_p(soc_hw_snd_platform_remove),
};

static struct platform_device *hiaudio_hw_dma_device;

int hiaudio_hw_dma_init(void)
{
    int ret =0;
    
    hiaudio_hw_dma_device = platform_device_alloc("hisi-audio-i2s", -1);
    if (!hiaudio_hw_dma_device) {
    	HI_FATAL_AO(KERN_ERR "hiaudio-dma SoC platform device: Unable to register\n");
    	return -ENOMEM;
    }
    
    ret = platform_device_add(hiaudio_hw_dma_device);
    if (ret) {
    	HI_FATAL_AO(KERN_ERR "hiaudio-dma SoC platform device: Unable to add\n");
    	platform_device_put(hiaudio_hw_dma_device);
       return ret;
    }

    return platform_driver_register(&hiaudio_hw_dma_driver);
}

void hiaudio_hw_dma_deinit(void)
{
    platform_device_unregister(hiaudio_hw_dma_device);
    platform_driver_unregister(&hiaudio_hw_dma_driver);
}
