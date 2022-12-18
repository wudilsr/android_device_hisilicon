
/**
 * \file hi_hls_intf.h
 * \brief Describes the information about HiSilicion Transcoder hls module (HiHls).
*/

#ifndef _HI_PROTOCOL_HLS_INTF_H_

#define _HI_PROTOCOL_HLS_INTF_H_

#include "hi_protocol.h"

#ifdef __cplusplus
extern "C"{
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      HiHls */
/** @{ */  /** <!—[HiHls]*/

#define MAX_M3U8_FILE_LEN  (1024)

#define MEDIA_SEGMENT_LEN  (2)

#define TS_FILE_TIME_LEN  (2)

#define TS_SEGMENT_MAXLEN  (TS_FILE_TIME_LEN*1024*1024)

#define SEGMENT_SLIDE_NUM  (5)

#define MAX_HTTP_ETAG_LEN (32)

#define FILENAME_PRFIX "fileSequence"

/*1.5M buffer SIZE*/
#define BUF_SIZE_1_5M  (((3)*(1024)*(1024))/(2))


/** @} */  /*! <!-- Macro Definition End */

/*************************** Structure Definition ****************************/
/** \addtogroup      HiHls */
/** @{*/  /** <!—[HiHls]*/

/**HLS ts data frame structure*//** CNcomment:HLS ts封装过帧数据*/
typedef struct _TsFrameInfo
{
    HI_U8* pBuf;
    HI_U32 nBufLen;
    HI_U32 pts;
    HI_S32 payloadtype;
}TsFrameInfo;

/**HLS ts related media attribute*//** CNcomment:HLS 相关媒体属性信息*/
typedef struct _TsMediaInfo
{
    HI_S32 s32Gop;
    HI_S32 s32FrameRate;
    /*ts file time length, measured in seconds */
    HI_S32 s32TsDuration;
    /*max valid ts file in m3u8 file*/
    HI_S32 s32MaxTsFileCnt;
}TsMediaInfo;

/**HLS sliced ts file Info*//** CNcomment:HLS ts分片文件数据*/
typedef struct _TsFileInfo
{
    HI_U8* pBuf;
    HI_U32 nBufLen;
    HI_BOOL bPtsExceptionFlag;
    HI_CHAR ETAG[MAX_HTTP_ETAG_LEN+1];
}TsFileInfo;

/**HLS m3u8 file Info*//** CNcomment:HLS m3u8 文件数据*/
typedef struct _M3U8FileInfo
{
    HI_U8 pBuf[MAX_M3U8_FILE_LEN];
    HI_U32 nBufLen;
    HI_CHAR ETAG[MAX_HTTP_ETAG_LEN+1];
}M3U8FileInfo;

/** @}*/  /** <!-- ==== Structure Definition End ====*/


/******************************* API Declaration *****************************/
/** \addtogroup      HiHls */
/** @{ */  /** <!—[HiHls]*/



/**-----Standard Functions--------*/
/**
\brief create HLS function .CNcomment:打开HLS 协议实例
\attention \n
Hls create handle.must set TsMediaInfo attr
CNcomment:当业务需要使用HLS协议能力时调用，
需要设置TsMediaInfo给HLS协议。

\param[in] pAttr hls handle attr.CNcomment:设置HLS协议的属性。
\param[out] pHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. create error happened.CNcomment:创建失败。
\see \n

\par example
\code
HI_HANDLE pHandle;
TsMediaInfo pstAttr;
if (HI_Protocol_HLS_Create(&hlsHandle, &pAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_Create(HI_HANDLE* hlsHandle, const TsMediaInfo* pAttr);



/**-----Standard Functions--------*/
/**
\brief destroy Hls handle.CNcomment:模块销毁hls实例句柄
\attention \n
when call this function,pls make clear the hlshandle if there multi hls handle
CNcomment:当业务需要关闭Hls实例时调用，如有多个hls实例在
同时运行，请注意销毁正确的句柄。
\param[in] hlsHandle created hls handle.CNcomment:已创建的hls句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:销毁失败。
\see \n

\par example
\code
if (HI_Protocol_HLS_Destroy(hlsHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_Destroy(HI_HANDLE hlsHandle);



/**-----Standard Functions--------*/
/**
\brief write Ts frame to HLS protocol.CNcomment:向协议内写入Ts帧数据
\attention \n
need afford extra payloadtype, pts of frame, and make sure the data measured in frame
CNcomment:写入的ts数据需要保证以帧为单位，并提供
帧的负载类型，时间戳信息

\param[in] pFrameInfo ts frame info.CNcomment:ts数据帧数据。
\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. create error happened.CNcomment:创建失败。
\see \n

\par example
\code
TsFrameInfo pFrameInfo;
if (HI_Protocol_HLS_WriteTsFrame(hlsHandle, &pFrameInfo) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_WriteTsFrame(HI_HANDLE hlsHandle, const TsFrameInfo* pFrameInfo);



/**-----Standard Functions--------*/
/**
\brief check if there m3u8 file.CNcomment:检测是否有m3u8文件可读
\attention \n
better to do timeout checking, m3u8 file will be generated after some ts frames being writed
CNcomment:m3u8文件仅在足够长度的ts帧数据写入后，才会生成
，并最好进行接口的超时检测

\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\retval 0  HI_TRUE ready .CNcomment:m3u8文件已生成。
\retval ::HI_FALSE  -1. not ready.CNcomment:m3u8文件还未生成。
\see \n

\par example
\code
if (!HI_Protocol_HLS_IsM3U8FileReady(hlsHandle))
{
    return -1;
}

\endcode
*/
HI_BOOL HI_Protocol_HLS_IsM3U8FileReady(HI_HANDLE hlsHandle);



/**-----Standard Functions--------*/
/**
\brief get latest m3u8 file.CNcomment:获取最新的m3u8文件内容
\attention \n
better to do file existing checking before geting m3u8 file
CNcomment:最好在获取m3u8文件之前，进行m3u8文件存在的检测

\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\param[out] pfile  m3u8 file content.CNcomment:m3u8文件内容。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. get error happened.CNcomment:获取失败。
\see \n

\par example
\code
M3U8FileInfo m3u8file;
if (HI_Protocol_HLS_GetLatestM3U8File(hlsHandle, &m3u8file) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_GetLatestM3U8File(HI_HANDLE hlsHandle, M3U8FileInfo* pfile);



/**-----Standard Functions--------*/
/**
\brief get ts file with Seq.CNcomment:获取指定seqnum的ts文件内容
\attention \n
pls make sure the ts frame writing have been called
CNcomment:在获取ts文件前，请确认ts帧内容被持续写入

\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\param[in] nSeq  sequence num of ts file.CNcomment:要获取的ts文件对应的序号。
\param[out] pfile  ts file content.CNcomment:ts文件内容。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. get error happened.CNcomment:获取失败。
\see \n

\par example
\code
TsFileInfo tsfile;
if (HI_Protocol_HLS_GetTsFileBySeq(hlsHandle, nSeq, &tsfile) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_GetTsFileBySeq(HI_HANDLE hlsHandle, HI_U32 nSeq, TsFileInfo* pfile);


/**-----Standard Functions--------*/
/**
\brief reset the hls working enviroment.CNcomment:重置hls工作上下文
\attention \n
after being reset, ts frameinfo being writed will be erased, ts file and m3u8 file wiil be refreshed
CNcomment:重置后，之前写入的ts帧信息不再可访问，m3u8文件
和ts文件重新被刷新

\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\retval HI_SUCCESS  0  Success.CNcomment:成功返回。
\retval HI_FAILURE  -1. error happened.CNcomment:操作失败。
\see \n

\par example
\code
if (!HI_Protocol_HLS_Reset(hlsHandle))
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_Reset (HI_HANDLE hlsHandle);



/**-----Standard Functions--------*/
/**
\brief get hls media attribute.CNcomment:获取Hls媒体属性信息
\attention \n

\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\param[out] pAttr  hls media attribute.CNcomment:hls 媒体属性信息。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. get error happened.CNcomment:获取失败。
\see \n

\par example
\code
TsMediaInfo mediaInfo;
if (HI_Protocol_HLS_GetAttr(hlsHandle, &mediaInfo) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_GetAttr(HI_HANDLE hlsHandle, TsMediaInfo* pAttr);



/**-----Standard Functions--------*/
/**
\brief set hls media attribute.CNcomment:设置Hls媒体属性信息
\attention \n
pls make sure calling the function before ts writing beiginning, or after the reset
CNcomment:请确认该接口调用，在ts帧信息之前，或者在
reset接口调用后。

\param[in] hlsHandle  created the handle of Hls.CNcomment:建立的协议实例句柄。
\param[in] pAttr  hls media attribute.CNcomment:hls 媒体属性信息。
\retval 0  HI_SUCCESS Success.CNcomment:成功返回。
\retval ::HI_FAILURE  -1. get error happened.CNcomment:获取失败。
\see \n

\par example
\code
TsMediaInfo mediaInfo;
if (HI_Protocol_HLS_SetAttr(hlsHandle, &mediaInfo) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Protocol_HLS_SetAttr(HI_HANDLE hlsHandle, const TsMediaInfo* pAttr);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
}
#endif /* __cplusplus*/

#endif
