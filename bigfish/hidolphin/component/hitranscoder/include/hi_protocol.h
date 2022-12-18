
/**
 * \file Hi_protocol.h
 * \brief Describes the information about HiSilicion Transcoder protocol (HiProto).
*/

#ifndef __HI_PROTOCOL_H__
#define __HI_PROTOCOL_H__

#include "hi_type.h"

#ifdef __cplusplus
extern "C"{
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      HiProto */
/** @{ */  /** <!��[HiProto]*/

#define TRANSCODER_PROTOCOL_MEM_MAX     (16)
#define TRANSCODER_COMMAND_BASE 0xA0000000

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!��[HiProto]*/

/**transcoder module status machine enum*//** CNcomment:ת��ģ��Э��״̬�� */
typedef enum eTran_ProtocolStatus
{
    TRANSCODER_PROTOCOL_INIT = 0,
    TRANSCODER_PROTOCOL_STOP,
    TRANSCODER_PROTOCOL_START,
    TRANSCODER_PROTOCOL_STATUS_BUTT,
}Transcoder_ProtocolStatus;

/**transcoder module protocol server type*//** CNcomment:ת��ģ��ת��Э�����������*/
typedef enum eTran_ProtocolType
{
    TRANSCODER_PROTOCOL_HTTP = 1,
    TRANSCODER_PROTOCOL_RTSP = 2,
    TRANSCODER_PROTOCOL_VTRL_DRV = 4,
    TRANSCODER_PROTOCOL_FAST_STREAM = 8,
    TRANSCODER_PROTOCOL_SAMPLE = 16,
    TRANSCODER_PROTOCOL_BUTT,
}Transcoder_ProtocolType;

/**transcoder module protocol control type*//** CNcomment:ת��ģ��ת��Э�������������*/
typedef enum eWFD_External_Method
{
    WFD_SOURCE_METHOD_INIT = 0,
    WFD_SOURCE_METHOD_RESET = 1,
    WFD_SOURCE_METHOD_SEEK = 2,
    WFD_SOURCE_METHOD_CHANGE = 3,
    WFD_SOURCE_METHOD_PAUSE = 4,
    WFD_SOURCE_METHOD_BUTT,
}WFD_External_Method_E;

/**Protocol send Command to Transcoder type*//** CNcomment:ת��ģ��Protocol ����ģ���ύ�������*/
typedef enum eProto_CallBackCommand
{
    PROTOCOL_COMMAND_PAUSE = TRANSCODER_COMMAND_BASE + 1,
    PROTOCOL_COMMAND_SEEK = TRANSCODER_COMMAND_BASE + 2,
    PROTOCOL_COMMAND_SETATTR = TRANSCODER_COMMAND_BASE + 3,
    PROTOCOL_COMMAND_SETSOURCE = TRANSCODER_COMMAND_BASE + 4,
    PROTOCOL_COMMAND_SETMUTE = TRANSCODER_COMMAND_BASE + 5,
}Protocol_CallBackCommand;

/**Protocol create handle Protocol Attr*//** CNcomment:ת��ģ��ת��Э��������򿪲���*/
typedef struct tagProtocolAttr
{
    HI_S32 s32Port;                         /**<port of protocol*//**<CNcomment:Э��Ķ˿� */
    HI_U32 u32ProtocolType;       /**<type of protocol*//**<CNcomment:Э�������*/
    HI_HANDLE SourceHandle;   /**<source handle of protocol*//**<CNcomment:Э��������Դ*/
    HI_S32 s32UserNum;              /**<max user num of protocol*//**<CNcomment:Э��֧�ֵ��û����� */
}ProtocolAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!��[HiProto]*/

/**-----Standard Functions--------*/
/**
\brief Protocol  initialization function.CNcomment:ģ���ʼ��
\attention \n

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. init error happened.CNcomment:��ʼ��ʧ�ܡ�
\see \n

\par example
\code
if (HI_Protocol_Init() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_Init();

/**-----Standard Functions--------*/
/**
\brief Protocol  uninitialization function.CNcomment:ģ��ȥ��ʼ��
\attention \n

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:ȥ��ʼ��ʧ�ܡ�
\see \n

\par example
\code
if (HI_Protocol_DeInit() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_DeInit();


/**-----Standard Functions--------*/
/**
\brief Protocol  module create Protocol handle.CNcomment:Protocolģ������Protocol���
\attention \n
this function called by user, not have relationship with transcoder.
CNcomment:�˽ӿ����û����ã���Transcoderû�б�Ȼ���Ⱥ�˳��

\param[in] pstTranAttr protocol create attr.CNcomment:���õ�Protocol�����ԡ�
\param[out] hProtocolHandle  created protocol handle.CNcomment:���ɵ�Protocol�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. create error happened.CNcomment:����ʧ�ܡ�
\see \n

\par example
\code
HI_HANDLE hProtocolHandle;
ProtocolAttr pstTranAttr;
if (HI_Protocol_Create(&hProtocolHandle, &pstTranAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_Create(HI_HANDLE* hProtocolHandle,const ProtocolAttr* pstTranAttr);


/**-----Standard Functions--------*/
/**
\brief Protocol  module destroy protocol handle.CNcomment:Protocolģ������Protocol���
\attention \n
this function called by user, not have relationship with transcoder.
CNcomment:�˽ӿ����û����ã���Transcoderû�б�Ȼ���Ⱥ�˳��

\param[in] hProtocolHandle protocol handle.CNcomment:�Ѵ�����Protocol�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:����ʧ�ܡ�
\see \n

\par example
\code
if (HI_Protocol_destory(hProtocolHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_destory(HI_HANDLE hProtocolHandle);


/**-----Standard Functions--------*/
/**
\brief Protocol regist handle function.CNcomment:Protocolע�ắ��
\attention \n
this function called by user, must after called after transcoder create function
when the source of HiTranscoder happens large change,need called HI_Protocol_UnRegistHandle then this
function,for example:when play local file,happens rewind,need play from begin,or dvb change channel.
CNcomment:�˺�������Transcoder_create����ܵ���,���û�������Դ�����ϴ�
�仯����Ҫ�ȵ���HI_Protocol_UnRegistHandle��Ȼ����ñ����������磺����
�����ļ�ʱ�������ļ�������ɣ��ִ�ͷ���ŵ����������dvb���ֻ�̨�������

\param[in] pProtocolHandle need regist Protocol handle.CNcomment:Ҫ�󶨵�Protocol�����
\param[in] hTranHandle need regist Transcoder handle.CNcomment:Ҫ�󶨵�Transcoder�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. RegistHandle error happened.CNcomment:ע��ʧ�ܡ�
\see \n

\par example
\code
if (HI_Protocol_RegistHandle(hProtocolHandle, hTranHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_RegistHandle(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);


/**-----Standard Functions--------*/
/**
\brief Protocol unregist handle function.CNcomment:Protocolȥע�ắ��
\attention \n
this function called by user, must after called after transcoder create function,
when the source of HiTranscoder happens large change,need called this function
for example:when play local file,happens rewind,need play from begin,or dvb change channel.
CNcomment:�˺�������Transcoder_create����ܵ���,���û�������Դ�����ϴ�仯��
��Ҫ�ȵ��ñ��������磺���ű����ļ�ʱ�������ļ�������ɣ�
�ִ�ͷ���ŵ����������dvb���ֻ�̨�������

\param[in] pProtocolHandle need unregist Protocol handle.CNcomment:Ҫȥ�󶨵�Protocol�����
\param[in] hTranHandle need unregist Transcoder handle.CNcomment:Ҫȥ�󶨵�Transcoder�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. UnRegistHandle error happened.CNcomment:ȥע��ʧ�ܡ�
\see \n

\par example
\code
if (HI_Protocol_UnRegistHandle(hProtocolHandle, hTranHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_UnRegistHandle(HI_HANDLE pProtocolHandle,HI_HANDLE hTranHandle);


/**-----Standard Functions--------*/
/**
\brief  Protocol regist external protocol server.CNcomment:Protocol ע���ⲿЭ�麯��
\attention \n
this function called by user, must after called after protocol init function.
CNcomment:�˺�������HI_Protocol_Init����ܵ��á�

\param[in] pLibProtocolName need regist external .so name.CNcomment:Ҫע��Ŀ����ơ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. RegistProtocol error happened.CNcomment:ע�����Э��ɹ���
\see \n

\par example
\code
HI_CHAR pLibProtocolName = {lib*.so};
if (HI_Protocol_RegistProtocol(pLibProtocolName) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_RegistProtocol(const HI_CHAR* pLibProtocolName);


/**-----Standard Functions--------*/
/**
\brief Protocol unregist external protocol server.CNcomment:Protocol ȥע���ⲿЭ�麯��
\attention \n
this function this function called by user, must after called after protocol init function.
CNcomment:�˺�������HI_Protocol_Init����ܵ��á�

\param[in] pLibProtocolName need unregist external .so name.CNcomment:Ҫȥע��Ŀ����ơ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. DeRegistProtocol error happened.CNcomment:ȥע�����Э��ɹ���
\see \n

\par example
\code
HI_CHAR pLibProtocolName = {lib*.so};
if (HI_Protocol_DeRegistProtocol(pLibProtocolName) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_DeRegistProtocol(const HI_CHAR* pLibProtocolName);


/**-----Standard Functions--------*/
/**
\brief Protocol control from external module.CNcomment:���ⲿģ��ִ��Э�����ָ��
\attention \n
this function must be called after the protocol already been registered.
CNcomment:�������������Э��ģ���Ѿ���ע����������á�

\param[in] hProtocolHandle protocol handle to execute instruction.so name.CNcomment:ִ��ָ���Э������
\param[in] u32Command  command type to be executed, could be one of enum WFD_External_Method_E.CNcomment:�������ͣ�������
                  WFD_External_Method_E ������֮һ��
\param[in] bBufferFlag  flag to distinguish the ts input and dvb input because the delay of fileread end delay only when command type is RESET
                  CNcomment:��������������TS������DVB��������RESET�������͡�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. extern command send error happened.CNcomment:���Ϳ���ָ��ʧ�ܡ�
\see \n

\par example
\code
HI_U32 u32Command = WFD_SOURCE_METHOD_RESET;
HI_BOOL bBufferFlag = HI_TRUE;
if (HI_Protocol_WFD_SetClientCommand(hProtocolHandle, u32Command, bBufferFlag) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_WFD_SetClientCommand(HI_HANDLE hProtocolHandle,HI_U32 u32Command,HI_BOOL bBufferFlag);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
}
#endif /* __cplusplus*/


#endif /* __HI_PROTOCOL_H__*/