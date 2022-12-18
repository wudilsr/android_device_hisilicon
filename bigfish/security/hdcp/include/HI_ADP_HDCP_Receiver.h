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
\brief HDCP 2.2 Receiver Init. CNcomment:HDCP Receiver初始化 CNend
\attention \n
N/A
\param[in] HI_VOID
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failed CNcomment:失败 CNend
\see \n
N/A
*/

HI_S32 HI_ADP_HDCP2_Rcv_Init(HI_VOID);

/**
\brief HDCP2.2 Receiver Deinit. CNcomment:HDCP2.2 Receiver去初始化 CNend
\attention \n
N/A
\param[in] HI_VOID
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failed CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_DeInit(HI_VOID);

/**
\brief Waiting for the connection request of HDCP2.2 client . CNcomment:等待客户端的HDCP连接请求 CNend
\attention \n
N/A
\param[in] ipAddr local ipaddress CNcomment:本地IP地址 CNend
\param[in] port local port id CNcomment:本地端口号 CNend
\param[out] handle listen socket id CNcomment:监听Socket句柄 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failed CNcomment:失败 CNend
\see \n
N/A
*/

HI_HANDLE* HI_ADP_HDCP2_Rcv_Open(HI_U8 *ipAddr, HI_U32 port);

/**
\brief close listen socket CNcomment:关闭监听的Socket CNend
\attention \n
N/A
\param[in] handle listen socket id. CNcomment:监听Socket句柄 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failed CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_Close(HI_HANDLE *handle);

/**
\brief decrypt stream. CNcomment:解密数据流 CNend
\attention \n
N/A
\param[in] handle the handle of HDCP2.2  CNcomment:打开的HDCP句柄 CNend
\param[in] pesPrivateData[16] pes stream private data CNcomment:PES码流中Private字段 CNend
\param[in] inputData input data address CNcomment:输入数据的地址 CNend
\param[out] outputData output data address CNcomment:输出数据的地址 CNend
\param[in] dataLen input datalen. CNcomment:输入数据的长度 CNend
\param[in] type stream type CNcomment:媒体类型 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failed CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_Decrypt(HI_HANDLE *handle, const HI_U8 pesPrivateData[16], const HI_U8 *inputData, HI_U8 *outputData, HI_U32 dataLen, HI_ADP_HDCP_STRESM_TYPE_E type);

/**
\brief get software version. CNcomment:获取软件版本 CNend
\attention \n
N/A
\param[out] currentVersion current sw version. CNcomment:当前软件版本 CNend
\retval ::HI_SUCCESS Success CNcomment:成功 CNend
\retval ::HI_FAILURE Failed CNcomment:失败 CNend
\see \n
N/A
*/
HI_S32 HI_ADP_HDCP2_Rcv_Get_Version(HI_U8 currentVersion[32]);

#ifdef  __cplusplus
}
#endif

#endif
