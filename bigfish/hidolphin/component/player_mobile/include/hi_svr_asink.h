#ifndef __HI_SVR_ASINK_H__
#define __HI_SVR_ASINK_H__

typedef struct hiSVR_ASINK_OPEN_PARAM
{
    HI_U32 u32SampleRate;/**<Sampling rate*/ /**<CNcomment: ������*/
    HI_U16 u16Channels;/**<Number of channels*/ /**<CNcomment: ͨ������*/
    /** u16BitPerSample: (PCM) Data depth, and format of storing the output data
          If the data depth is 16 bits, 16-bit word memory is used.
          If the data depth is greater than 16 bits, 32-bit word memory is used, and data is stored as left-aligned data. That is, the valid data is at upper bits.
     */
    /**CNcomment: u16BitPerSample: (PCM) ����λ������. �����Ÿ�ʽ
          ����16bit:   ռ��16bit word�ڴ�
          ����16bit:   ռ��32bit word�ڴ�, ��������뷽ʽ���(��Ч�����ڸ�λ)
     */
    HI_U16 u16BitPerSample;/**<Data depth*/ /**<CNcomment: ����λ��*/
}HI_SVR_ASINK_OPEN_PARAM;

typedef enum hiSVR_ASINK_EVENT_E
{
    HI_SVR_ASINK_EVENT_STREAM_END = 0,/**<Sent after all the buffers queued in AF and HW are played, refer to Android::MediaPlayerBase::AudioSink::cb_event_t*/ /**<CNcomment: ��AF��Ӳ���е����ݲ�����ɺ��ͣ���ο�:Android::MediaPlayerBase::AudioSink::cb_event_t*/
    HI_SVR_ASINK_EVENT_FILL_BUFFER,/**<Request to write more data to buffer.*/ /**<CNcomment: ������buffer��д���������*/
}HI_SVR_ASINK_EVENT_E;


typedef struct hiSVR_ASINK_S HI_SVR_ASINK_S;

/** Callback returns the number of bytes actually written to the buffer.. */
/** CNcomment:�ص�����������buffer��д����ֽ���*/
typedef HI_SIZE_T (*HI_SVR_ASINK_Callback)(
        HI_SVR_ASINK_S *asink, HI_VOID *buffer, HI_SIZE_T size, HI_VOID *cookie,
                HI_SVR_ASINK_EVENT_E event);

struct hiSVR_ASINK_S
{
    HI_S32 (*open)(HI_SVR_ASINK_S *asink, HI_SVR_ASINK_OPEN_PARAM *param,HI_SVR_ASINK_Callback cb, HI_VOID *cookie);
    HI_S32 (*close)(HI_SVR_ASINK_S *asink);
    HI_S32 (*start)(HI_SVR_ASINK_S *asink);
    HI_S32 (*stop)(HI_SVR_ASINK_S *asink);
    HI_S32 (*pause)(HI_SVR_ASINK_S *asink);
    HI_S32 (*flush)(HI_SVR_ASINK_S *asink);
    HI_S32 (*control)(HI_SVR_ASINK_S* asink, HI_U32 cmd, ...);
    HI_VOID* opaque;/**<private data pointer*/ /**<CNcomment: ˽������*/
};

#endif

