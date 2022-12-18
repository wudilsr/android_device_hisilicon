
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
/** @{ */  /** <!—[HiProto]*/

#define TRANSCODER_PROTOCOL_MEM_MAX     (16)
#define TRANSCODER_COMMAND_BASE 0xA0000000

/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!—[HiProto]*/

/**transcoder module status machine enum*//** CNcomment:转码模块协议状态机 */
typedef enum eTran_ProtocolStatus
{
    TRANSCODER_PROTOCOL_INIT = 0,
    TRANSCODER_PROTOCOL_STOP,
    TRANSCODER_PROTOCOL_START,
    TRANSCODER_PROTOCOL_STATUS_BUTT,
}Transcoder_ProtocolStatus;

/**transcoder module protocol server type*//** CNcomment:转码模块转码协议服务器类型*/
typedef enum eTran_ProtocolType
{
    TRANSCODER_PROTOCOL_HTTP = 1,
    TRANSCODER_PROTOCOL_RTSP = 2,
    TRANSCODER_PROTOCOL_VTRL_DRV = 4,
    TRANSCODER_PROTOCOL_FAST_STREAM = 8,
    TRANSCODER_PROTOCOL_SAMPLE = 16,
    TRANSCODER_PROTOCOL_BUTT,
}Transcoder_ProtocolType;

/**transcoder module protocol control type*//** CNcomment:转码模块转码协议控制信令类型*/
typedef enum eWFD_External_Method
{
    WFD_SOURCE_METHOD_INIT = 0,
    WFD_SOURCE_METHOD_RESET = 1,
    WFD_SOURCE_METHOD_SEEK = 2,
    WFD_SOURCE_METHOD_CHANGE = 3,
    WFD_SOURCE_METHOD_PAUSE = 4,
    WFD_SOURCE_METHOD_BUTT,
}WFD_External_Method_E;

/**Protocol send Command to Transcoder type*//** CNcomment:转码模块Protocol 向主模块提交的命令集合*/
typedef enum eProto_CallBackCommand
{
    PROTOCOL_COMMAND_PAUSE = TRANSCODER_COMMAND_BASE + 1,
    PROTOCOL_COMMAND_SEEK = TRANSCODER_COMMAND_BASE + 2,
    PROTOCOL_COMMAND_SETATTR = TRANSCODER_COMMAND_BASE + 3,
    PROTOCOL_COMMAND_SETSOURCE = TRANSCODER_COMMAND_BASE + 4,
    PROTOCOL_COMMAND_SETMUTE = TRANSCODER_COMMAND_BASE + 5,
}Protocol_CallBackCommand;

/**Protocol create handle Protocol Attr*//** CNcomment:转码模块转码协议服务器打开参数*/
typedef struct tagProtocolAttr
{
    HI_S32 s32Port;                         /**<port of protocol*//**<CNcomment:协议的端口 */
    HI_U32 u32ProtocolType;       /**<type of protocol*//**<CNcomment:协议的类型*/
    HI_HANDLE SourceHandle;   /**<source handle of protocol*//**<CNcomment:协议数据来源*/
    HI_S32 s32UserNum;              /**<max user num of protocol*//**<CNcomment:协议支持的用户数量 */
}ProtocolAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiProto */
/** @{*/  /** <!—[HiProto]*/

/**-----Standard Functions--------*/
/**
\brief Protocol  initialization function.CNcomment:模块初始化
\attention \n

\param[in] void.CNcomment:void。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. init error happened.CNcomment:初始化失败。
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
\brief Protocol  uninitialization function.CNcomment:模块去初始化
\attention \n

\param[in] void.CNcomment:void。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:去初始化失败。
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
\brief Protocol  module create Protocol handle.CNcomment:Protocol模块生成Protocol句柄
\attention \n
this function called by user, not have relationship with transcoder.
CNcomment:此接口由用户调用，和Transcoder没有必然的先后顺序。

\param[in] pstTranAttr protocol create attr.CNcomment:设置的Protocol的属性。
\param[out] hProtocolHandle  created protocol handle.CNcomment:生成的Protocol句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. create error happened.CNcomment:创建失败。
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
\brief Protocol  module destroy protocol handle.CNcomment:Protocol模块销毁Protocol句柄
\attention \n
this function called by user, not have relationship with transcoder.
CNcomment:此接口由用户调用，和Transcoder没有必然的先后顺序。

\param[in] hProtocolHandle protocol handle.CNcomment:已创建的Protocol句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:销毁失败。
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
\brief Protocol regist handle function.CNcomment:Protocol注册函数
\attention \n
this function called by user, must after called after transcoder create function
when the source of HiTranscoder happens large change,need called HI_Protocol_UnRegistHandle then this
function,for example:when play local file,happens rewind,need play from begin,or dvb change channel.
CNcomment:此函数需在Transcoder_create后才能调用,当用户的输入源发生较大
变化，需要先调用HI_Protocol_UnRegistHandle，然后调用本函数，例如：播放
本地文件时，本地文件播放完成，又从头播放的情况，或者dvb出现换台的情况。

\param[in] pProtocolHandle need regist Protocol handle.CNcomment:要绑定的Protocol句柄。
\param[in] hTranHandle need regist Transcoder handle.CNcomment:要绑定的Transcoder句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. RegistHandle error happened.CNcomment:注册失败。
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
\brief Protocol unregist handle function.CNcomment:Protocol去注册函数
\attention \n
this function called by user, must after called after transcoder create function,
when the source of HiTranscoder happens large change,need called this function
for example:when play local file,happens rewind,need play from begin,or dvb change channel.
CNcomment:此函数需在Transcoder_create后才能调用,当用户的输入源发生较大变化，
需要先调用本函数例如：播放本地文件时，本地文件播放完成，
又从头播放的情况，或者dvb出现换台的情况。

\param[in] pProtocolHandle need unregist Protocol handle.CNcomment:要去绑定的Protocol句柄。
\param[in] hTranHandle need unregist Transcoder handle.CNcomment:要去绑定的Transcoder句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. UnRegistHandle error happened.CNcomment:去注册失败。
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
\brief  Protocol regist external protocol server.CNcomment:Protocol 注册外部协议函数
\attention \n
this function called by user, must after called after protocol init function.
CNcomment:此函数需在HI_Protocol_Init后才能调用。

\param[in] pLibProtocolName need regist external .so name.CNcomment:要注册的库名称。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. RegistProtocol error happened.CNcomment:注册外接协议成功。
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
\brief Protocol unregist external protocol server.CNcomment:Protocol 去注册外部协议函数
\attention \n
this function this function called by user, must after called after protocol init function.
CNcomment:此函数需在HI_Protocol_Init后才能调用。

\param[in] pLibProtocolName need unregist external .so name.CNcomment:要去注册的库名称。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. DeRegistProtocol error happened.CNcomment:去注册外接协议成功。
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
\brief Protocol control from external module.CNcomment:从外部模块执行协议控制指令
\attention \n
this function must be called after the protocol already been registered.
CNcomment:这个函数必须在协议模块已经被注册起来后调用。

\param[in] hProtocolHandle protocol handle to execute instruction.so name.CNcomment:执行指令的协议句柄。
\param[in] u32Command  command type to be executed, could be one of enum WFD_External_Method_E.CNcomment:命令类型，可以是
                  WFD_External_Method_E 中类型之一。
\param[in] bBufferFlag  flag to distinguish the ts input and dvb input because the delay of fileread end delay only when command type is RESET
                  CNcomment:用于区分输入是TS流还是DVB，仅用于RESET命令类型。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. extern command send error happened.CNcomment:发送控制指令失败。
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