/**
 \file
 \brief Server smoothstreaming module. CNcomment:HiSmoothStreaming�߰�ģ��
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
/** CNcomment:�����ͣ��ļ��������������������������� */
typedef enum hiSMOOTHSTREAMINGFORMAT_DATA_TYPE_E
{
    HI_SMOOTHSTREAMING_FORMAT_DATA_NULL = 0x0,
    HI_SMOOTHSTREAMING_FORMAT_DATA_AUD,          /**< Audio stream *//**< CNcomment:��Ƶ�� */
    HI_SMOOTHSTREAMING_FORMAT_DATA_VID,          /**< Video stream *//**< CNcomment:��Ƶ�� */
    HI_SMOOTHSTREAMING_FORMAT_DATA_SUB,          /**< Subtitle stream *//**< CNcomment:��Ļ�� */
    HI_SMOOTHSTREAMING_FORMAT_DATA_RAW,          /**< Byte stream *//**< CNcomment:�ֽ��� */
    HI_SMOOTHSTREAMING_FORMAT_DATA_BUTT
} HI_SMOOTHSTREAMING_FORMAT_DATA_TYPE_E;


/** Frame data */
/** CNcomment:֡���� */
typedef struct hiSMOOTHSTREAMING_FORMAT_FRAME_S
{
    HI_SMOOTHSTREAMING_FORMAT_DATA_TYPE_E eType;          /**< Data type *//**< CNcomment:�������� */
    HI_S32  s32StreamIndex;               /**< Stream index *//**< CNcomment:������ */
    HI_BOOL bKeyFrame;                    /**< Whether the frame is a key frame *//**< CNcomment:�Ƿ�Ϊ�ؼ�֡ */
    HI_U32  u32Len;                       /**< Length of frame data, in the unit of byte. This parameter is an input or output parameter in RAW mode. It indicates the number of bytes to be read if it is an input parameter, and indicates the number of
                                                                  bytes that are actually read if it is an output parameter. */
                                          /**< CNcomment:֡���ݳ��ȣ���λ�ֽڣ�����raw��ʽ���ò���Ϊ����/���������
                                                                 ����ΪҪ��ȡ���ֽ��������Ϊʵ�ʶ�ȡ���ֽ��� */
    HI_U8   *pu8Addr;                     /**< Address of the frame data *//**< CNcomment:֡���ݵ�ַ */
    HI_U8   *pu8FrameHeader;              /**< Frame data header address *//**< CNcomment:֡����ǰ��ͷ���ݵ�ַ���������Ҫ��������ΪNULL */
    HI_U32  u32FrameHeaderLen;            /**< Frame data header data length  *//**< CNcomment:֡����ǰ��ͷ���ݳ��� */
    HI_S64  s64Pts;                       /**< Presentation time stamp (PTS), IN the unit of ms. If there is no PTS, it is set to ::HI_FORMAT_NO_PTS. *//**< CNcomment:ʱ�������λms�����û��ʱ���������Ϊ::HI_FORMAT_NO_PTS */
    HI_S64  s64Pos;                       /**< position of this frame in the media file.*//**< CNcomment:��֡������ý���ļ��е��ֽ�ƫ��λ�� */
    HI_U32  u32Duration;                  /**< Display duration, in the unit of ms. It is set to 0 if there is no duration. *//**< CNcomment:��ʾʱ������λms��û��duration������Ϊ0 */
    HI_U32  u32UserData;                  /**< Private data. The DEMUX can transparently transmit private data by using this parameter. *//**< CNcomment:˽�����ݣ�����������ͨ���ò����ش�˽������ */
    HI_U64  u64SampleID;
} HI_SMOOTHSTREAMING_FORMAT_FRAME_S;

/******************************* API declaration *****************************/
#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif
/**
\brief Read one frame data. CNcomment:��ȡһ֡����CNend
\attention \n
\param[in] phPlayer handle of the created player. CNcomment:�����Ĳ��������CNend
\param [in/out] ppstFmtFrame media data. CNcomment:ý��������Ϣָ��CNend

\retval ::HI_SUCCESS The operation is successful. CNcomment:�����ɹ�CNend
\retval ::HI_FAILURE The parameters are invalid. CNcomment:�����Ƿ�CNend
\retval ::HI_FORMAT_ERRO_ENDOFFILE The file ends. CNcomment:�ļ�����CNend

\see \n
None.
*/
extern HI_S32 HI_SVR_SMOOTHSTREAMING_ReadFrame(HI_HANDLE hPlayer, HI_SMOOTHSTREAMING_FORMAT_FRAME_S **ppstFmtFrame);

/**
\brief Release frame data. CNcomment:�ͷ�֡����CNend
\attention \n
\param[in] phPlayer handle of the created player. CNcomment:�����Ĳ��������CNend
\param [in] ppstFmtFrame media data read by the fmt_read interface. CNcomment:fmt_read�ӿڶ�ȡ��ý��������Ϣָ��CNend

\retval ::HI_SUCCESS The operation is successful. CNcomment:�����ɹ�CNend
\retval ::HI_FAILURE The parameters are invalid. CNcomment:�����Ƿ�CNend

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

