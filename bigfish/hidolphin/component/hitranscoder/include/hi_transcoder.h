
/**
 * \file hi_transcoder.h
 * \brief Describes the information about HiSilicion Transcoder trans module (HiTran).
*/

#ifndef __HI_TRANSCODER_H__
#define __HI_TRANSCODER_H__

#include "hi_type.h"
#include "hi_unf_venc.h"
#include "hi_unf_aenc.h"

#ifdef __cplusplus
extern "C"{
#endif

/***************************** Macro Definition ******************************/
/** \addtogroup      HiTran */
/** @{ */  /** <!��[HiTran]*/

/**software platform define*//** CNcomment:��ȡ���ƽ̨ */
#ifdef ANDROID_TOOLCHAIN
#define SOFT_BOARD_VERSION_ANDROID
#else
#define SOFT_BOARD_VERSION_LINUX
#endif

/** @} */  /*! <!-- Macro Definition End */


/*************************** Structure Definition ****************************/
/** \addtogroup      HiTran */
/** @{*/  /** <!��[HiTran]*/

/**transcoder media data type*//** CNcomment:��ȡ֡�������� */
typedef enum eTran_PAYLOAD
{
    PAYLOAD_VIDEO_NORMAL_FRAME = 1,
    PAYLOAD_VIDEO_KEY_FRAME = 5, //��Ƶ�ؼ�֡
    PAYLOAD_VIDEO_SPS_FRAME = 7,
    PAYLOAD_VIDEO_PPS_FRAME = 8,
    PAYLOAD_AUDIO_FRAME = 10, //��Ƶ֡
    PAYLOAD_MD_FRAME, //MD����
    PAYLOAD_BUTT
}TRANSCODER_PAYLOAD_E;

/**transcoder video/audio type*//** CNcomment:ת��ģ��ת������Ƶ���� */
typedef enum eTran_MediaCodec
{
    TRANSCODER_CODEC_ID_H264 = 0,
    TRANSCODER_CODEC_ID_H263,
    TRANSCODER_CODEC_ID_MPEG4,
    TRANSCODER_CODEC_ID_AACLC,
    TRANSCODER_CODEC_ID_AMRNB,
    TRANSCODER_CODEC_ID_G711A,
    TRANSCODER_CODEC_ID_NONE,
    TRANSCODER_CODEC_ID_BUTT
}Transcoder_MediaCodec;

/**transcoder attribute set of diff type*//** CNcomment:ת��ģ����������Լ�*/
typedef enum eTran_Attr_ID_E
{
    TRANSCODER_ALL_ATTR,
    TRANSCODER_VIDEO_ATTR,
    TRANSCODER_AUDIO_ATTR,
    TRANSCODER_BACKGND_ATTR,
    TRANSCODER_ATTR_BUTT
}Transcoder_Attr_ID_E;

/**transcoder source type*//** CNcomment:ת��ģ������Դ����*/
typedef enum eTran_Src_Type_E
{
    TRANSCODER_SOURCE_AVPLAY,
    TRANSCODER_SOURCE_OSD_VO_PCM,
    TRANSCODER_SOURCE_BUTT
}Transcoder_Src_Type_E;

/**media data payload data structure*//** CNcomment:ý������payLoad��������*/
typedef union hiTranscoder_DATA_TYPE_U
{
    HI_UNF_VENC_STREAM_S stVencStream;  /**<video stream encoded data *//**<CNcomment:��Ƶ���������� */
    HI_UNF_ES_BUF_S      stAencStream;            /**<audio stream encoded data *//**<CNcomment:��Ƶ���������� */
}HI_TRAN_DATA_TYPE_U;

/**transcoder data frame structure*//** CNcomment:ý������֡�ṹ*/
typedef struct tagTran_STREAM_S
{
    TRANSCODER_PAYLOAD_E ePayloadType;  /**<stream payload type *//**<CNcomment:PayLoad�������� */
    HI_TRAN_DATA_TYPE_U  enDataStream;             /**<stream data *//**<CNcomment:ý��������*/
}TRANSCODER_STRAM;


/**supply for user callback function, modified by user, set by source module*/
/** CNcomment:�ṩ���û���ָ��ص��ӿڣ����ݲ�ͬ��ָ��������Ժ���Դ��ģ�飬
��Դ��ģ��ȷ������Ӧ��ʽ����Ϊ��̨ת�룬�˺������� Transcoderʵ��*/
typedef HI_S32 (*HI_TRANSCODER_NODIFY_CALLBACK)(HI_HANDLE Handle,HI_U32 u32Command,HI_VOID* stAttr,HI_S32 s32Len );

/**transcoder module create attr*//** CNcomment:ת��ģ��ת���������*/
typedef struct tagTran_HandleAttr
{
    Transcoder_MediaCodec audioCodec;   /**<audio codec id*//**<CNcomment:��ƵCodecID */
    Transcoder_MediaCodec videoCodec;   /**<video codec id*//**<CNcomment:��ƵCodecID */
 //   HI_U32 u32ProtocolMask;                       /**<protocol types mask*//**<CNcomment:��ʱ�Ĵ�Э���mask ֵ���ɴ򿪶��Э��*/
    HI_U32 SourceType;                                   /**<source types ,reserve*//**<CNcomment:ת��ģ��Դ������ƵԴ���ͣ�Ϊ����������չԤ��*/
//    HI_S32 s32X;                                            /**<X coordinate*//**<CNcomment:ת�����ʼλ�� X ����*/
//    HI_S32 s32Y;                                            /**<Y coordinate*//**<CNcomment:ת�����ʼλ�� Y ����*/
    HI_S32 s32Width;                    /**<video resolution --width*//**<CNcomment:��Ƶ�ֱ���--�� */
    HI_S32 s32Height;                     /**<video resolution --height*//**<CNcomment:��Ƶ�ֱ���--�� */
    HI_U32 u32VideoBitRate;                /**<video bitrate*//**<CNcomment:��Ƶ������ */
    HI_S32 s32VideoFrameRate;            /**<video frame rate*//**<CNcomment:��Ƶ֡�� */
    HI_S32 s32AudioSampleRate;            /**<audio sample rate*//**<CNcomment:��Ƶ������ */
    HI_S32 s32AudioBandWidth;            /**<audio band width*//**<CNcomment:��Ƶ������� */
    HI_S32 s32AudioChannels;                    /**<audio channel num*//**<CNcomment:��Ƶ�������������� */
    HI_S32 s32Gop;                     /**<video resolution --gop,can be set dynamically*//**<CNcomment:I֡������ɽ��ж�̬���� */
    HI_BOOL bCycle;                                       /**<cycle flag for file input*//**<CNcomment:�����ļ������Ƿ�Ҫѭ�� */
    HI_HANDLE hSrc;                   /**<transcoder input source handle*//**<CNcomment:ת������Դ�����ΪNULL����ȫ��ת�� */
    HI_TRANSCODER_NODIFY_CALLBACK pNodifySrcFunc;  /**<callback from transcode to source caller*//**<CNcomment:ת��ģ���ṩ������ģ��Ļص�����,��˶˿ڻص���Դ�� */
}Transcoder_HandleAttr;

/** @}*/  /** <!-- ==== Structure Definition End ====*/

/******************************* API Declaration *****************************/
/** \addtogroup      HiTran */
/** @{ */  /** <!��[HiTran]*/

/**-----Standard Functions--------*/
/**
\brief transcoder module initialization function.CNcomment:��ʼ��ת����
\attention \n
HiTranscoder module must init function.CNcomment:����ת��Ҫ�����ȵ��øýӿڡ�

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. init error happened.CNcomment:��ʼ��ʧ�ܡ�
\see \n

\par example
\code
if (HI_Transcoder_Init() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Init(void);


/**-----Standard Functions--------*/
/**
\brief transcoder  uninitialization function.CNcomment:ȥ��ʼ��ת����
\attention \n
HiTranscoder module all clear function must called behind.CNcomment:ת���˳�Ҫ�������øýӿڡ�

\param[in] void.CNcomment:void��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. deinit error happened.CNcomment:ȥ��ʼ��ʧ�ܡ�
\see \n

\par example
\code
if (HI_Transcoder_DeInit() < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_DeInit(void);


/**-----Standard Functions--------*/
/**
\brief create transcoder function .CNcomment:��ת��ͨ��
\attention \n
transcoder create handle.must set Transcoder_HandleAttr attr,could call Transcoder_getDefaultAttr
when attr's property hsrc is NULL ,now version return failure.CNcomment:��ҵ����Ҫʹ��ת������ʱ���ã�
��Ҫ����Transcoder_HandleAttr��ת��ͨ������ת�������е�hsrcΪ��ʱ�����ڰ汾���ش���
���Ҿ�����

\param[in] pstAttr transcoder handle attr.CNcomment:����ת��ͨ�������ԡ�
\param[out] pHandle  created the handle of transcoder.CNcomment:������ת��ͨ�������
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. create error happened.CNcomment:����ʧ�ܡ�
\see \n

\par example
\code
HI_HANDLE pHandle;
Transcoder_HandleAttr pstAttr;
if (HI_Transcoder_Create(&pHandle, &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Create(HI_HANDLE* pHandle,const Transcoder_HandleAttr *pstAttr);


/**-----Standard Functions--------*/
/**
\brief destroy transcoder handle.CNcomment:ģ������transcoder���
\attention \n
called this function,need destroy all protocol.
CNcomment:��ҵ����Ҫ�ر�ת������ʱ���ã���Ҫע���ʱ��״̬��Ҫ�������е�Э�飬����������

\param[in] pHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. destroy error happened.CNcomment:����ʧ�ܡ�
\see \n

\par example
\code
if (HI_Transcoder_Destroy(pHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Destroy(HI_HANDLE pHandle);


/**-----Standard Functions--------*/
/**
\brief get the attr of transcoder handle.CNcomment:��ȡת����������
\attention \n
this function called after transcoder create handle function.
CNcomment:��ҵ����Ҫ��ȡת���������ԣ���Ҫע��˽ӿ���Ҫ��create�������ú�ʹ�á�

\param[in] pHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����
\param[in] eTranAttr attribute set type.CNcomment:ָ�����ص����Լ����͡�
\param[out] pstAttr returned attribute set content.CNcomment:ָ�����ص����Լ����ݡ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. get attribute error happened.CNcomment:��ȡ���Լ�ʧ�ܡ�
\see \n

\par example
\code
Transcoder_Attr_ID_E eTranAttr = TRANSCODER_ALL_ATTR��
Transcoder_HandleAttr pstAttr��
if (HI_Transcoder_GetAttr(pHandle, eTranAttr,  &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_GetAttr(HI_HANDLE pHandle,Transcoder_Attr_ID_E eTranAttr,Transcoder_HandleAttr *pstAttr);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle attr.CNcomment:����ת����������
\attention \n
need called after transcoder create function.
CNcomment:��ҵ����Ҫ����ת������������Ҫע��˽ӿ���Ҫ��create�������ú�ʹ�á�

\param[in] pHandle the handle who need set attr.CNcomment:�Ѵ�����transcoder�����
\param[in] eTranAttr attribute set type.CNcomment:ָ�����ص����Լ����͡�
\param[in] pstAttr the attr will set to handle.CNcomment:����ת��ͨ�������ԡ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. set attribute error happened.CNcomment:�������Լ�ʧ�ܡ�
\see \n

\par example
\code
Transcoder_Attr_ID_E eTranAttr = TRANSCODER_ALL_ATTR��
Transcoder_HandleAttr pstAttr��
if (HI_Transcoder_SetAttr(pHandle, eTranAttr,  &pstAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_SetAttr(HI_HANDLE pHandle,Transcoder_Attr_ID_E eTranAttr,const Transcoder_HandleAttr *pstAttr);


/**-----Standard Functions--------*/
/**
\brief get the resource info of transcoder module.CNcomment:��ȡת��ʹ����Դ���
\attention \n
this function called after transcoder initial function.
CNcomment:��ҵ����Ҫ��ȡת����Դ�����Ҫע��˽ӿ���Ҫ��init�������ú�ʹ�á�

\param[in] pHandle the handle who need set attr.CNcomment:�Ѵ�����transcoder�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. GetResourceInfo error happened.CNcomment:��ȡ��Դ��Ϣʧ�ܡ�
\see \n

\par example
\code
if (HI_Transcoder_GetResourceInfo(pHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_GetResourceInfo(HI_HANDLE pHandle);


/**-----Standard Functions--------*/
/**
\brief get the resource info of transcoder module.CNcomment:��ȡת��Debug ��Ϣ
\attention \n
this function called after transcoder initial function.
CNcomment:��ҵ����Ҫ��ȡת��Debug ��Ϣ��Ҫע��˽ӿ���Ҫ��init�������ú�ʹ�á�

\param[in] pHandle the handle who need set attr.CNcomment:�Ѵ�����transcoder�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. GetDebugInfo error happened.CNcomment:��ȡDebug��Ϣʧ�ܡ�
\see \n

\par example
\code
if (HI_Transcoder_GetDebugInfo(pHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_GetDebugInfo(HI_HANDLE pHandle);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle status --- start.CNcomment:����ת����״̬������start
\attention \n
when transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:��ת��������Stop-start״̬���ոýӿڵ�״̬��ת������

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����
\param[in] bBlock blocked called or not .CNcomment:�Ƿ�������
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. transcoder start error happened.CNcomment:ת������ʧ�ܡ�
\see \n

\par example
\code
HI_BOOL bBlock = HI_TRUE;
if (HI_Transcoder_Start(hTranHandle, bBlock) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Start(HI_HANDLE hTranHandle,HI_BOOL bBlock);


/**-----Standard Functions--------*/
/**
\brief set transcoder handle status --- stop.CNcomment:����ת����״̬������stop
\attention \n
transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:��ת��������Stop-start״̬���ոýӿڵ�״̬��ת������

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����
\param[in] bBlock blocked called or not .CNcomment:�Ƿ�������
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. transcoder stop error happened.CNcomment:ת��ر�ʧ�ܡ�
\see \n

\par example
\code
HI_BOOL bBlock = HI_TRUE;
if (HI_Transcoder_Stop(hTranHandle, bBlock) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_Stop(HI_HANDLE hTranHandle,HI_BOOL bBlock);


/**-----Standard Functions--------*/
/**
\brief sync called Transcoder module callback function,different because of command.CNcomment:ͬ������Transcoderģ��Ļص�������
��ص����̸��� Command��ͬ�����û�ָ����ͬ��ʵ�ַ�֧
\attention \n
transcoder enter stop-start status machine ,after transcoder create handle.
CNcomment:��ת��������Stop-start״̬���ոýӿڵ�״̬��ת������

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����
\param[in] u32Command transcoder callback command.CNcomment:ת��ص���ָ�
\param[in] pstAttr callback attr .CNcomment:ָ��Ĳ�����
\param[in] s32AttrLen callback attr len.CNcomment: ָ������ĳ��ȡ�
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. SetCommand error happened.CNcomment:�ص�callerʧ�ܡ�
\see \n

\par example
\code
HI_BOOL bBlock = HI_TRUE;
HI_U32 u32Command = 0;
if (HI_Transcoder_SetCommand(hTranHandle, u32Command, pstAttr, s32AttrLen) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_SetCommand(HI_HANDLE hTranHandle,HI_U32 u32Command,HI_VOID* pstAttr,HI_S32 s32AttrLen);


/**-----Standard Functions--------*/
/**
\brief register media data read handle.CNcomment:ע��ý�����ݶ�ȡ���
\attention \n
register media data read handle,this function called by protocol and user.
CNcomment:ע��ý�����ݶ����ӿڣ��ýӿ���protocolģ����е��á�

\param[in] hTranHandle created transcoder handle.CNcomment:�Ѵ�����transcoder�����
\param[out] phMbufReadHandle media data read handle.CNcomment:ý�����ݵĶ�ȡ�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. Register media Handle error happened.CNcomment:ע��ý���д���ʧ�ܡ�
\see \n

\par example
\code
HI_HANDLE phMbufReadHandle;
if (HI_Transcoder_RegisterHandle(hTranHandle, phMbufReadHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_RegisterHandle(HI_HANDLE hTranHandle,HI_HANDLE* phMbufReadHandle);


/**-----Standard Functions--------*/
/**
\brief unregister media data read handle.CNcomment:ȥע��ý�����ݶ�ȡ���
\attention \n
unregister media data read handle,this function called by protocol and user.
CNcomment:ȥע��ý�����ݶ����ӿڣ��ýӿ���protocolģ����е��á�

\param[in] phMbufReadHandle registed media data read handle.CNcomment:��ע���ý�����ݵĶ�ȡ�����
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. DeRegister media Handle error happened.CNcomment:ȥע��ý���д���ʧ�ܡ�
\see \n

\par example
\code
HI_HANDLE phMbufReadHandle;
if (HI_Transcoder_DeRegisterHandle(phMbufReadHandle) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_DeRegisterHandle(HI_HANDLE hMbufReadHandle);


/**-----Standard Functions--------*/
/**
\brief read media data from mbuf handle.CNcomment:��ȡý������
\attention \n
when there no data in buffer, will return HI_FAILURE.
CNcomment:��ȡ�����ݿ�������MBUF����Ϊ�գ��޷���������ʱ����HI_FAILURE��

\param[in] hReadHandle registed media data read handle.CNcomment:��ע���ý�����ݵĶ�ȡ�����
\param[out] pstTranFrame returned media data from read handle.CNcomment:��MBUF�ж�ȡ������֡�ṹ��
\retval 0  HI_SUCCESS Success.CNcomment:�ɹ����ء�
\retval ::HI_FAILURE  -1. read media stream error happened.CNcomment:��ȡý�����ݷ��ؿա�
\see \n

\par example
\code
TRANSCODER_STRAM pstTranFrame;
if (HI_Transcoder_ReadStream(&pstTranFrame) < 0)
{
    return -1;
}

\endcode
*/
HI_S32 HI_Transcoder_ReadStream(HI_HANDLE hReadHandle,TRANSCODER_STRAM* pstTranFrame);


/**-----Standard Functions--------*/
/**
\brief get the default attribute set of transcoder.CNcomment:��ȡת��Ĭ�����Լ�
\attention \n

\param[out] stTranHandleAttr returned default transcoder attribute set.CNcomment:����ת���Ĭ�����Լ���
\retval void.CNcomment:void��
\see \n

\par example
\code
Transcoder_HandleAttr pstTranFrame;
if (Transcoder_getDefaultAttr(&stTranHandleAttr) < 0)
{
    return -1;
}

\endcode
*/
HI_VOID Transcoder_getDefaultAttr(Transcoder_HandleAttr* stTranHandleAttr);

/** @}*/  /** <!-- ==== API Declaration End ====*/

#ifdef __cplusplus
}
#endif /* __cplusplus*/


#endif /* __HI_TRANSCODER_H__*/