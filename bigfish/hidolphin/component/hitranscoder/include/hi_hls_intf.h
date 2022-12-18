
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
/** @{ */  /** <!��[HiHls]*/

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
/** @{*/  /** <!��[HiHls]*/

/**HLS ts data frame structure*//** CNcomment:HLS ts��װ��֡����*/
typedef struct _TsFrameInfo
{
    HI_U8* pBuf;
    HI_U32 nBufLen;
    HI_U32 pts;
    HI_S32 payloadtype;
}TsFrameInfo;

/**HLS ts related media attribute*//** CNcomment:HLS ���ý��������Ϣ*/
typedef struct _TsMediaInfo
{
    HI_S32 s32Gop;
    HI_S32 s32FrameRate;
    /*ts file time length, measured in seconds */
    HI_S32 s32TsDuration;
    /*max valid ts file in m3u8 file*/
    HI_S32 s32MaxTsFileCnt;
}TsMediaInfo;

/**HLS sliced ts file Info*//** CNcomment:HLS ts��Ƭ�ļ�����*/
typedef struct _TsFileInfo
{
    HI_U8* pBuf;
    HI_U32 nBufLen;
    HI_BOOL bPtsExceptionFlag;
    HI_CHAR ETAG[MAX_HTTP_ETAG_LEN+1];
}TsFileInfo;

/**HLS m3u8 file Info*//** CNcomment:HLS m3u8 �ļ�����*/
typedef struct _M3U8FileInfo
{
    HI_U8 pBuf[MAX_M3U8_FILE_LEN];
    HI_U32 nBufLen;
    HI_CHAR ETAG[MAX_HTTP_ETAG_LEN+1];
}M3U8FileInfo;

/** @}*/  /** <!-- ==== Structure Definition End ====*/


/******************************* API Declaration *****************************/
/** \addtogroup      HiHls */
/** @{ */  /** <!��[HiHls]*/



/**-----Standard Functions--------*/
/**
\brief create HLS function .CNcomment:��HLS Э��ʵ��
\attention \n
Hls create handle.must set TsMediaInfo attr
CNcomment:��ҵ����Ҫʹ��HLSЭ������ʱ���ã�
��Ҫ����TsMediaInfo��HLSЭ�顣

\param[in] pAttr hls handle attr.CNcomment:����HLSЭ������ԡ�
\param[out] pHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. create error happened.CNcomment:����ʧ�ܡ�
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
\brief destroy Hls handle.CNcomment:ģ������hlsʵ�����
\attention \n
when call this function,pls make clear the hlshandle if there multi hls handle
CNcomment:��ҵ����Ҫ�ر�Hlsʵ��ʱ���ã����ж��hlsʵ����
ͬʱ���У���ע��������ȷ�ľ����
\param[in] hlsHandle created hls handle.CNcomment:�Ѵ�����hls�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:����ʧ�ܡ�
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
\brief write Ts frame to HLS protocol.CNcomment:��Э����д��Ts֡����
\attention \n
need afford extra payloadtype, pts of frame, and make sure the data measured in frame
CNcomment:д���ts������Ҫ��֤��֡Ϊ��λ�����ṩ
֡�ĸ������ͣ�ʱ�����Ϣ

\param[in] pFrameInfo ts frame info.CNcomment:ts����֡���ݡ�
\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. create error happened.CNcomment:����ʧ�ܡ�
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
\brief check if there m3u8 file.CNcomment:����Ƿ���m3u8�ļ��ɶ�
\attention \n
better to do timeout checking, m3u8 file will be generated after some ts frames being writed
CNcomment:m3u8�ļ������㹻���ȵ�ts֡����д��󣬲Ż�����
������ý��нӿڵĳ�ʱ���

\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\retval 0  HI_TRUE ready .CNcomment:m3u8�ļ������ɡ�
\retval ::HI_FALSE  -1. not ready.CNcomment:m3u8�ļ���δ���ɡ�
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
\brief get latest m3u8 file.CNcomment:��ȡ���µ�m3u8�ļ�����
\attention \n
better to do file existing checking before geting m3u8 file
CNcomment:����ڻ�ȡm3u8�ļ�֮ǰ������m3u8�ļ����ڵļ��

\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\param[out] pfile  m3u8 file content.CNcomment:m3u8�ļ����ݡ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. get error happened.CNcomment:��ȡʧ�ܡ�
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
\brief get ts file with Seq.CNcomment:��ȡָ��seqnum��ts�ļ�����
\attention \n
pls make sure the ts frame writing have been called
CNcomment:�ڻ�ȡts�ļ�ǰ����ȷ��ts֡���ݱ�����д��

\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\param[in] nSeq  sequence num of ts file.CNcomment:Ҫ��ȡ��ts�ļ���Ӧ����š�
\param[out] pfile  ts file content.CNcomment:ts�ļ����ݡ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. get error happened.CNcomment:��ȡʧ�ܡ�
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
\brief reset the hls working enviroment.CNcomment:����hls����������
\attention \n
after being reset, ts frameinfo being writed will be erased, ts file and m3u8 file wiil be refreshed
CNcomment:���ú�֮ǰд���ts֡��Ϣ���ٿɷ��ʣ�m3u8�ļ�
��ts�ļ����±�ˢ��

\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\retval HI_SUCCESS  0  Success.CNcomment:�ɹ����ء�
\retval HI_FAILURE  -1. error happened.CNcomment:����ʧ�ܡ�
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
\brief get hls media attribute.CNcomment:��ȡHlsý��������Ϣ
\attention \n

\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\param[out] pAttr  hls media attribute.CNcomment:hls ý��������Ϣ��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. get error happened.CNcomment:��ȡʧ�ܡ�
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
\brief set hls media attribute.CNcomment:����Hlsý��������Ϣ
\attention \n
pls make sure calling the function before ts writing beiginning, or after the reset
CNcomment:��ȷ�ϸýӿڵ��ã���ts֡��Ϣ֮ǰ��������
reset�ӿڵ��ú�

\param[in] hlsHandle  created the handle of Hls.CNcomment:������Э��ʵ�������
\param[in] pAttr  hls media attribute.CNcomment:hls ý��������Ϣ��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. get error happened.CNcomment:��ȡʧ�ܡ�
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
