
/**
 * \file hi_proto_intf.h
 * \brief Describes the information about HiSilicion Transcoder Protocol (HiProto).
*/

#ifndef __HI_PROTO_INTF_H__
#define __HI_PROTO_INTF_H__

#include "hi_type.h"
#include "hi_protocol.h"
#include "hi_muxer.h"

/***************************** Macro Definition ******************************/
/** \addtogroup      HiProto */
/** @{ */  /** <!—[HiProto]*/

#define RTSP_DEFAULT_PROTOCOL "rtsp_default"
#define HTTP_DEFAULT_PROTOCOL "http_default"
#define MAX_IP_LEN 64

typedef HI_S32 HI_SOCKET;
typedef HI_CHAR HI_IP_ADDR[MAX_IP_LEN];
typedef HI_U16  HI_PORT;

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!—[HiProto]*/

typedef struct tagHI_ProtocolInfo_S
{
    const HI_PCHAR szName;                  /**<protocol name*//**<CNcomment:由用户定义的协议的名称 */
    const HI_U32 enProtocolType;         /**<protocol type*//**<CNcomment:由用户定义的协议的类型，不能与Transcoder_ProtocolType中的重复 */
    const HI_PCHAR pszDescription;   /**<protocol description, unify this protocol.*//**<CNcomment:用户定义的唯一标示协议的描述 */
    HI_VOID  * pDllModule;                      /**<set NULL*//**<CNcomment:由用户置空 */
    HI_S32 (*ProtocolCreate)(HI_HANDLE* hProtocolHandle,const ProtocolAttr* pstTranAttr);   /**<protocol create*//**<CNcomment:协议创建接口 */
    HI_S32 (*ProtocolDestroy)(HI_HANDLE hProtocolHandle);   /**<protocol destroy*//**<CNcomment:协议销毁接口 */
    HI_S32 (*ProtocolRegist)(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);  /**<protocol regist*//**<CNcomment:协议注册接口 */
    HI_S32 (*ProtocolDeRegist)(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);    /**<protocol deregist*//**<CNcomment:协议去注册接口 */
    struct tagHI_ProtocolInfo_S* next;   /**<protocol linklist, set NULL*//**<CNcomment:当前协议链表 ，用户置空*/
}HI_ProtocolInfo_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!—[HiProto]*/

/**-----Standard Functions--------*/
/**
\brief get the actual instance of protocol handle.CNcomment:获取协议句柄的实例
\attention \n
called after HI_Protocol_Create.CNcomment:此函数需在HI_Protocol_Create后才能调用。

\param[in] hProtocolHandle created protocol handle.CNcomment:已创建的协议句柄。
\param[out] pInstanceHandle returned protocol instance.CNcomment:返回的协议实例。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1.  get instance of protocol error happened.CNcomment:获取协议实例失败。
\see \n

\par example
\code
HI_HANDLE pInstanceHandle ;
if (HI_Protocol_GetInstance(pLibMuxerName) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_GetInstance(HI_HANDLE hProtocolHandle,HI_HANDLE* pInstanceHandle);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#endif/* __HI_PROTO_INTF_H__*/
