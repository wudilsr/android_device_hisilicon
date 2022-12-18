/*******************************************************************************
 *              Copyright 2004 - 2014, Hisilicon Tech. Co., Ltd.
 *                           ALL RIGHTS RESERVED
 * FileName: drv_aiao_alsa_func.h
 * Description: drv aiao alsa func h
 *
 * History:
 * Version   Date         Author     DefectNum    Description
 * main\1    
 ********************************************************************************/

#ifndef __DRV_AIAO_ALSA_FUNC_H__
#define __DRV_AIAO_ALSA_FUNC_H__

#include "hi_type.h"
#include <linux/fs.h>
#include "hi_unf_sound.h"
#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

//Playback
//��ָͣ��AE DMA  ͨ�� ����
int aoe_dma_stop(int dma_Index, void * p);
//ʹ��ָ��AE DMA  ͨ�� ����
int aoe_dma_start(int dma_Index, void * p);
// prepare ÿ�ζ�дǰ/ XRUN �ָ�  ���ᱻ���ñ����ýӿ�
int aoe_dma_prepare(int dma_Index, void * p);
//��ȡָ��AE DMA  ͨ����/д ��Ե�ַ(����period_size����)
//int aoe_dma_offsetpos(int dma_Index, int *offset);
//Ϊָ��AE DMA  ͨ������dma �жϻص�����
//Dma_Index ָ��AE DMA  ͨ��
//stream : captrue / palyback
//func: �жϻص�����
//data: �ص��������������
//int aoe_dma_setbufperiodsize(int dma_Index, int stream, int buffer_size, int period_size);

int aoe_dma_sethwparam(int dma_Index, void *hw_param);
//����/�ͷ�һ·AE DMA ��Դ
//Stream: DMA ���䷽��
//Dma_Index: ����ͨ����
int aoe_dma_requestchan(int *dma_index, struct file *file, void *arg);
int aoe_dma_releasechan(int dma_index);
//Playback
void clr_dsp_int(void);
void set_dsp_int(void);
int  aoe_dma_open(struct file *file);
int  aoe_dma_close(struct file *file);
int aoe_update_writeptr(int dma_index, HI_U32 *pu32WritePos);
int aoe_update_readptr(int dma_index, HI_U32 *pu32ReadPos);
int aoe_get_AipReadPos(int dma_index, HI_U32 *pu32ReadPos);
int aoe_dma_flushbuf(int dma_index);
//SND Control  set global port volume 
int aoe_set_volume(HI_UNF_SND_E enSound, HI_UNF_SND_OUTPUTPORT_E enOutPort, HI_UNF_SND_GAIN_ATTR_S stGain);

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif 
