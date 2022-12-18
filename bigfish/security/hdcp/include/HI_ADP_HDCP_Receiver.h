#ifndef _HI_ADP_HDCP_RECEIVER_H
#define _HI_ADP_HDCP_RECEIVER_H

#include "hi_type.h"

#ifdef __cplusplus
extern "C"
{
#endif

typedef enum hiADP_HDCP_STRESM_TYPE_E
{
	HI_ADP_HDCP_STRESM_TYPE_VIDEO,
	HI_ADP_HDCP_STRESM_TYPE_AUDIO,
	HI_ADP_HDCP_STRESM_TYPE_BUTT,
} HI_ADP_HDCP_STRESM_TYPE_E;

/**
\brief HDCP 2.2 Receiver Init. CNcomment:HDCP Receiver��ʼ�� CNend
\attention \n
N/A
\param[in] HI_VOID
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failed CNcomment:ʧ�� CNend
\see \n
N/A
*/

HI_S32 HI_ADP_HDCP2_Rcv_Init(HI_VOID);

/**
\brief HDCP2.2 Receiver Deinit. CNcomment:HDCP2.2 Receiverȥ��ʼ�� CNend
\attention \n
N/A
\param[in] HI_VOID
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failed CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_DeInit(HI_VOID);

/**
\brief Waiting for the connection request of HDCP2.2 client . CNcomment:�ȴ��ͻ��˵�HDCP�������� CNend
\attention \n
N/A
\param[in] ipAddr local ipaddress CNcomment:����IP��ַ CNend
\param[in] port local port id CNcomment:���ض˿ں� CNend
\param[out] handle listen socket id CNcomment:����Socket��� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failed CNcomment:ʧ�� CNend
\see \n
N/A
*/

HI_HANDLE* HI_ADP_HDCP2_Rcv_Open(HI_U8 *ipAddr, HI_U32 port);

/**
\brief close listen socket CNcomment:�رռ�����Socket CNend
\attention \n
N/A
\param[in] handle listen socket id. CNcomment:����Socket��� CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failed CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_Close(HI_HANDLE *handle);

/**
\brief decrypt stream. CNcomment:���������� CNend
\attention \n
N/A
\param[in] handle the handle of HDCP2.2  CNcomment:�򿪵�HDCP��� CNend
\param[in] pesPrivateData[16] pes stream private data CNcomment:PES������Private�ֶ� CNend
\param[in] inputData input data address CNcomment:�������ݵĵ�ַ CNend
\param[out] outputData output data address CNcomment:������ݵĵ�ַ CNend
\param[in] dataLen input datalen. CNcomment:�������ݵĳ��� CNend
\param[in] type stream type CNcomment:ý������ CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failed CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_Decrypt(HI_HANDLE *handle, const HI_U8 pesPrivateData[16], const HI_U8 *inputData, HI_U8 *outputData, HI_U32 dataLen, HI_ADP_HDCP_STRESM_TYPE_E type);

/**
\brief get software version. CNcomment:��ȡ����汾 CNend
\attention \n
N/A
\param[out] currentVersion current sw version. CNcomment:��ǰ����汾 CNend
\retval ::HI_SUCCESS Success CNcomment:�ɹ� CNend
\retval ::HI_FAILURE Failed CNcomment:ʧ�� CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_Get_Version(HI_U8 currentVersion[32]);

#ifdef  __cplusplus
}
#endif

#endif
