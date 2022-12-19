#ifndef NDPT_EXT
#define NDPT_EXT

#include "hi_type.h"

#include "hi_drv_ndpt.h"

/*create link according to net parameter, used to receive and send RTP/RTCP data. CNcomment:������������������ӣ����ڷ��ͺͽ���RTP/RTCP���ݡ�
input parameter:
     pNetPara:struct pointer of net communication protocol parameter,NDPT_NET_CONFIG_PARA_S CNcomment:RTP������ͨ��Э������ṹ��ָ�룬NDPT_NET_CONFIG_PARA_S
return:
     0:failure CNcomment:ʧ��
     other:handle of net adapter layer channel CNcomment:���� ���������ͨ�����
*/
extern HI_U32 HI_DRV_NDPT_CreateLink(HI_VOID *pNetCfgPara);

/*
modify parameter of net adapter layer channel CNcomment:�޸���������ͨ��������
input parameter:
      handle:handle of net adapter layer channel CNcomment:���������ͨ�������
      pstNetPara:struct pointer of net parameter config, NDPT_NET_CONFIG_PARA_S CNcomment:����������ýṹ��ָ�룬NDPT_NET_CONFIG_PARA_S ��
return:
      0:success CNcomment:�ɹ�
      other:failure CNcomment:���� ʧ��
*/
extern HI_S32 HI_DRV_NDPT_ModifyNetPara(HI_U32 handle,HI_VOID * pNetCfgPara);

/*
cancellation link interface CNcomment:ע����·�ӿڣ�
input parameter:
      handle:handle of net adapter layer channel CNcomment:���������ͨ�������
return:
      0:success CNcomment:�ɹ�
      other:failure CNcomment:���� ʧ��
*/
extern HI_S32 HI_DRV_NDPT_DestroyLink(HI_U32 handle);


/*
sent-received callbacks function of register data from RTP to net adapter CNcomment:RTP����������ע�����ݽ��ջص�����
input parameter:
      handle:handle of net adapter layer channel CNcomment:���������ͨ�������
      TransId:RTP layer channel ID,return when net adapter call RTP layer's sent-received callbacks CNcomment:RTP��ͨ��ID�������������RTP����ջص�����ʱ�ش���
      funptr:receive callbacks function pointer CNcomment: CNcomment:���ջص�����ָ�룻
return:
      0:success CNcomment:�ɹ���
      other:failure CNcomment:���� ʧ�ܣ�
*/
extern HI_S32 HI_DRV_NDPT_RevFun(HI_U32 handle, HI_U32 TransId, ndpt_rtp_revfrom funptr);

/*
send RTP/RTCP data CNcomment:����RTP/RTCP���ݡ�
input parameter:
      handle:handle of net adapter layer channel CNcomment:���������ͨ�������
      even_odd:port mode CNcomment:�˿�ģʽ��
      data_buffer:data struct pointer CNcomment:���ݽṹ��ָ�롣
return:
      0:success CNcomment:�ɹ���
      other:failure CNcomment:���� ʧ�ܣ�
*/
extern HI_S32 HI_DRV_NDPT_SendRtp(HI_U32 handle, HI_U32 even_odd, RTP_NET_BUFFER_STRU *data_buffer);


typedef HI_S32 (*FN_NDPT_RegRevfun)(HI_U32, HI_U32, ndpt_rtp_revfrom);
typedef HI_S32 (*FN_NDPT_RtpSendto)(HI_U32, HI_U32, RTP_NET_BUFFER_STRU *);
typedef HI_U32 (*FN_NDPT_CreateLink)(HI_VOID *);
typedef HI_S32 (*FN_NDPT_ModifyNetPara)(HI_U32, HI_VOID *);
typedef HI_S32 (*FN_NDPT_DestroyLink)(HI_U32);
	
typedef struct
{
    FN_NDPT_RegRevfun       pfnNdptRegRevfun;
    FN_NDPT_RtpSendto       pfnNdptRtpSendto;
    FN_NDPT_CreateLink      pfnNdptCreateLink;
    FN_NDPT_ModifyNetPara   pfnNdptModifyNetPara;
    FN_NDPT_DestroyLink     pfnNdptDestroyLink;
} NDPT_EXPORT_FUNC_S;

HI_S32 NDPT_ModeInit(HI_VOID);
HI_VOID NDPT_ModeExit(HI_VOID);
#endif


