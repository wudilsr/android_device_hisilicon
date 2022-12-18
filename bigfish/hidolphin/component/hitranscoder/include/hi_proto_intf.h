
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
/** @{ */  /** <!��[HiProto]*/

#define RTSP_DEFAULT_PROTOCOL "rtsp_default"
#define HTTP_DEFAULT_PROTOCOL "http_default"
#define MAX_IP_LEN 64

typedef HI_S32 HI_SOCKET;
typedef HI_CHAR HI_IP_ADDR[MAX_IP_LEN];
typedef HI_U16  HI_PORT;

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!��[HiProto]*/

typedef struct tagHI_ProtocolInfo_S
{
    const HI_PCHAR szName;                  /**<protocol name*//**<CNcomment:���û������Э������� */
    const HI_U32 enProtocolType;         /**<protocol type*//**<CNcomment:���û������Э������ͣ�������Transcoder_ProtocolType�е��ظ� */
    const HI_PCHAR pszDescription;   /**<protocol description, unify this protocol.*//**<CNcomment:�û������Ψһ��ʾЭ������� */
    HI_VOID  * pDllModule;                      /**<set NULL*//**<CNcomment:���û��ÿ� */
    HI_S32 (*ProtocolCreate)(HI_HANDLE* hProtocolHandle,const ProtocolAttr* pstTranAttr);   /**<protocol create*//**<CNcomment:Э�鴴���ӿ� */
    HI_S32 (*ProtocolDestroy)(HI_HANDLE hProtocolHandle);   /**<protocol destroy*//**<CNcomment:Э�����ٽӿ� */
    HI_S32 (*ProtocolRegist)(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);  /**<protocol regist*//**<CNcomment:Э��ע��ӿ� */
    HI_S32 (*ProtocolDeRegist)(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);    /**<protocol deregist*//**<CNcomment:Э��ȥע��ӿ� */
    struct tagHI_ProtocolInfo_S* next;   /**<protocol linklist, set NULL*//**<CNcomment:��ǰЭ������ ���û��ÿ�*/
}HI_ProtocolInfo_S;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!��[HiProto]*/

/**-----Standard Functions--------*/
/**
\brief get the actual instance of protocol handle.CNcomment:��ȡЭ������ʵ��
\attention \n
called after HI_Protocol_Create.CNcomment:�˺�������HI_Protocol_Create����ܵ��á�

\param[in] hProtocolHandle created protocol handle.CNcomment:�Ѵ�����Э������
\param[out] pInstanceHandle returned protocol instance.CNcomment:���ص�Э��ʵ����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1.  get instance of protocol error happened.CNcomment:��ȡЭ��ʵ��ʧ�ܡ�
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
