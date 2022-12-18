/**
 \file
 \brief Server smoothstreaming module. CNcomment:HiSmoothStreaming高安模块
 \author HiSilicon Technologies Co., Ltd.
 \date 2008-2018
 \version 1.0.0.1
 \author
 \date 2013-02-19
 */

#ifndef _HI_SVR_SMOOTHSTREAMING_ADP_H
#define _HI_SVR_SMOOTHSTREAMING_ADP_H

#include "hi_type.h"

/*************************** Structure Definition ****************************/

/** Type of the stream data that is parsed by the file DEMUX */
/** CNcomment:流类型，文件解析器解析出来的流数据类型 */
typedef enum hiSMOOTHSTREAMINGFORMAT_DATA_TYPE_E
{
    HI_SMOOTHSTREAMING_FORMAT_DATA_NULL = 0x0,
    HI_SMOOTHSTREAMING_FORMAT_DATA_AUD,          /**< Audio stream *//**< CNcomment:音频流 */
    HI_SMOOTHSTREAMING_FORMAT_DATA_VID,          /**< Video stream *//**< CNcomment:视频流 */
    HI_SMOOTHSTREAMING_FORMAT_DATA_SUB,          /**< Subtitle stream *//**< CNcomment:字幕流 */
    HI_SMOOTHSTREAMING_FORMAT_DATA_RAW,          /**< Byte stream *//**< CNcomment:字节流 */
    HI_SMOOTHSTREAMING_FORMAT_DATA_BUTT
} HI_SMOOTHSTREAMING_FORMAT_DATA_TYPE_E;


/** Frame data */
/** CNcomment:帧数据 */
typedef struct hiSMOOTHSTREAMING_FORMAT_FRAME_S
{
    HI_SMOOTHSTREAMING_FORMAT_DATA_TYPE_E eType;          /**< Data type *//**< CNcomment:数据类型 */
    HI_S32  s32StreamIndex;               /**< Stream index *//**< CNcomment:流索引 */
    HI_BOOL bKeyFrame;                    /**< Whether the frame is a key frame *//**< CNcomment:是否为关键帧 */
    HI_U32  u32Len;                       /**< Length of frame data, in the unit of byte. This parameter is an input or output parameter in RAW mode. It indicates the number of bytes to be read if it is an input parameter, and indicates the number of
                                                                  bytes that are actually read if it is an output parameter. */
                                          /**< CNcomment:帧数据长度，单位字节，对于raw方式，该参数为输入/输出参数，
                                                                 输入为要读取的字节数，输出为实际读取的字节数 */
    HI_U8   *pu8Addr;                     /**< Address of the frame data *//**< CNcomment:帧数据地址 */
    HI_U8   *pu8FrameHeader;              /**< Frame data header address *//**< CNcomment:帧数据前的头数据地址，如果不需要，则设置为NULL */
    HI_U32  u32FrameHeaderLen;            /**< Frame data header data length  *//**< CNcomment:帧数据前的头数据长度 */
    HI_S64  s64Pts;                       /**< Presentation time stamp (PTS), IN the unit of ms. If there is no PTS, it is set to ::HI_FORMAT_NO_PTS. *//**< CNcomment:时间戳，单位ms，如果没有时间戳，设置为::HI_FORMAT_NO_PTS */
    HI_S64  s64Pos;                       /**< position of this frame in the media file.*//**< CNcomment:该帧数据在媒体文件中的字节偏移位置 */
    HI_U32  u32Duration;                  /**< Display duration, in the unit of ms. It is set to 0 if there is no duration. *//**< CNcomment:显示时长，单位ms，没有duration，设置为0 */
    HI_U32  u32UserData;                  /**< Private data. The DEMUX can transparently transmit private data by using this parameter. *//**< CNcomment:私有数据，解析器可以通过该参数回带私有数据 */
    HI_U64  u64SampleID;
} HI_SMOOTHSTREAMING_FORMAT_FRAME_S;

/******************************* API declaration *****************************/
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
/**
\brief Read one frame data. CNcomment:读取一帧数据CNend
\attention \n
\param[in] phPlayer handle of the created player. CNcomment:创建的播放器句柄CNend
\param [in/out] ppstFmtFrame media data. CNcomment:媒体数据信息指针CNend

\retval ::HI_SUCCESS The operation is successful. CNcomment:操作成功CNend
\retval ::HI_FAILURE The parameters are invalid. CNcomment:参数非法CNend
\retval ::HI_FORMAT_ERRO_ENDOFFILE The file ends. CNcomment:文件结束CNend

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_ReadFrame(HI_HANDLE hPlayer, HI_SMOOTHSTREAMING_FORMAT_FRAME_S **ppstFmtFrame);

/**
\brief Release frame data. CNcomment:释放帧数据CNend
\attention \n
\param[in] phPlayer handle of the created player. CNcomment:创建的播放器句柄CNend
\param [in] ppstFmtFrame media data read by the fmt_read interface. CNcomment:fmt_read接口读取的媒体数据信息指针CNend

\retval ::HI_SUCCESS The operation is successful. CNcomment:操作成功CNend
\retval ::HI_FAILURE The parameters are invalid. CNcomment:参数非法CNend

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_FreeFrame(HI_HANDLE hPlayer, HI_SMOOTHSTREAMING_FORMAT_FRAME_S **ppstFmtFrame);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif

