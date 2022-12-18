
#ifndef _HI_PROTOCOL_HTTP_INTF_H_

#define _HI_PROTOCOL_HTTP_INTF_H_

#include "hi_protocol.h"

typedef  HI_S32 (*Http_Req_Handler_Callback)(HI_S32 socket, HI_CHAR* pHttpReq, HI_U32  ReqLen, HI_VOID* pUserData, HI_U32 dataLen);

HI_S32 HTTP_Protocol_Create(HI_HANDLE* hProtocolHandle,const ProtocolAttr* pstTranAttr);



HI_S32 HTTP_Protocol_Destroy(HI_HANDLE hProtocolHandle);



HI_S32 HTTP_Protocol_Regist(HI_HANDLE ProtocolHandle,HI_HANDLE hTranHandle);



HI_S32 HTTP_Protocol_DeRegist(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);


HI_VOID HTTP_Protocol_GetReplyHeader(HI_S32 statusCode, HI_S32 contentLen,
    HI_CHAR* pContentType, HI_CHAR* pEtag, HI_CHAR* pHeader, HI_U32 headBufLen);

HI_S32 HTTP_Protocol_RegistHttpCallback(HI_HANDLE ProtocolHandle,Http_Req_Handler_Callback callback,
    HI_VOID* pUserData, HI_U32 dataLen);

HI_S32 HTTP_Protocol_Send(HI_S32 s32WritSock,HI_CHAR* pszBuff, HI_U32 u32DataLen);

#endif
