#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/Log.h>
#include <binder/Parcel.h>
#include "media/AudioTrack.h"
#include "HiAoService.h"
#include <cutils/properties.h>
#include "hi_unf_sound.h"
#include <pthread.h>
#define  LOG_TAG "AOService"
#define MAX_BUFFER_SIZE (64*1024)
#define HDMI_OUTPUT_DEFAULT "1"     //default auto mode
#define SPDIF_OUTPUT_DEFAULT "3"    //default raw
#define HBR2LBR_DEFAULT "0"         //default auto mode

namespace android
{
    static int AUDIO_OUTPUT_PORT_HDMI = 1;
    static int AUDIO_OUTPUT_PORT_SPDIF = 2;
    static int AUDIO_OUTPUT_PORT_BLUERAY = 3;

    static int AUDIO_OUTPUT_MODE_OFF = 0;
    static int AUDIO_OUTPUT_MODE_AUTO = 1;
    static int AUDIO_OUTPUT_MODE_LPCM = 2;
    static int AUDIO_OUTPUT_MODE_RAW = 3;

    static int TWO_CHANNEL = 2;
    static int SIX_CHANNEL = 6;
    static int EIGHT_CHANNEL = 8;

    static int EDID_CAP = TWO_CHANNEL ;//default 2 channel

    static int BLUERAY_POSITION  = 0; //blueray status ,default auto BLUERAY_POSITION

    static int BLUERAY_AUTO = 0;
    static int BLUERAY_H2L = 1;
    static int BLUERAY_RAW = 2;

    static pthread_t g_CastThread;
    pthread_t g_DestroyThread;
    HI_HANDLE g_hCast;
    HI_BOOL g_StopThread = HI_TRUE;
	HI_BOOL g_EnterSmartSuspend = HI_FALSE;

    typedef struct AF_AUDIOTRACK_ATTR_S{
        sp<AudioTrack> pAudioTrack;
        unsigned char *pBuffer;
        unsigned int u32WritePos;
        unsigned int u32ReadPos;
        pthread_mutex_t  tMutex;
    }AUDIOTRACK_ATTR_S;

    static AUDIOTRACK_ATTR_S stAudioTrackAttr;

  static int cast_pushdata(AUDIOTRACK_ATTR_S *pstAudioTrackAttr,unsigned char *pdata, unsigned int bytes)
  {
      unsigned char *buffer = NULL;
      unsigned int readpos,writepos;
      unsigned int freesize = 0;
      /* The pstAudioTrackAttr and pdata have been checked outside */
      buffer = (unsigned char *)pstAudioTrackAttr->pBuffer;
      if(NULL == buffer)
      {
          ALOGE("%s %d, Null buffer pointer.\n ",__FUNCTION__, __LINE__);
          return -1;
      }

      readpos = pstAudioTrackAttr->u32ReadPos;
      writepos = pstAudioTrackAttr->u32WritePos;
      if(readpos >= MAX_BUFFER_SIZE)
      {
          ALOGE("%s %d, Invalid readpos %d\n ",__FUNCTION__, __LINE__,readpos);
          return -1;
      }

      if(writepos >= MAX_BUFFER_SIZE)
      {
          ALOGE("%s %d, Invalid writepos %d\n ",__FUNCTION__, __LINE__,writepos);
          return -1;
      }

      if(writepos >= readpos)
      {
          freesize = MAX_BUFFER_SIZE - writepos + readpos;
      }
      else
      {
          freesize = readpos - writepos;
      }

      if(bytes > freesize)
      {
          ALOGE("%s %d, not enough, need %d, free %d.\n ",__FUNCTION__, __LINE__,bytes,freesize);
          return -1;
      }

      freesize = bytes;
      while(freesize > 0)
      {
          *(buffer+writepos) = *pdata++;
          writepos = (writepos+1)%MAX_BUFFER_SIZE;
          freesize--;
      }
      pstAudioTrackAttr->u32WritePos = writepos;
      return bytes;
  }


  static int cast_getdata(AUDIOTRACK_ATTR_S *pstAudioTrackAttr, unsigned char* pdest, unsigned int request)
  {
      unsigned char *buffer = NULL;
      unsigned int readpos,writepos;
      unsigned int datasize = 0;

      /* The pstAudioTrackAttr and pdata have been checked outside */
      buffer = (unsigned char*)pstAudioTrackAttr->pBuffer;
      if(NULL == buffer)
      {
          ALOGE("%s %d, Null buffer pointer.\n ",__FUNCTION__, __LINE__);
          return -1;
      }

      readpos = pstAudioTrackAttr->u32ReadPos;
      writepos = pstAudioTrackAttr->u32WritePos;
      if(readpos >= MAX_BUFFER_SIZE)
      {
          ALOGE("%s %d, Invalid readpos %d\n ",__FUNCTION__, __LINE__,readpos);
          return -1;
      }

      if(writepos >= MAX_BUFFER_SIZE)
      {
          ALOGE("%s %d, Invalid writepos %d\n ",__FUNCTION__, __LINE__,writepos);
          return -1;
      }
      datasize = 0;
      while(1)
      {
          if(readpos == writepos)
              break;
          if(datasize >= request)
              break;
          *pdest++ = *(buffer + readpos);
          readpos = (readpos+1)%MAX_BUFFER_SIZE;
          datasize++;
      }

      pstAudioTrackAttr->u32ReadPos = readpos;
      return datasize;
  }

  static void AudioTrackCallback(int event, void* user, void *info)
  {
      if (event != AudioTrack::EVENT_MORE_DATA) return;
      if ((NULL == user)||(NULL == info)) return;

      AudioTrack::Buffer *buffer = static_cast<AudioTrack::Buffer *>(info);
      size_t size = buffer->size;
      //ALOGE("AudioTrackCallback size %d",size);
      unsigned char* pDestBuffer = (unsigned char*) buffer->raw;
      AUDIOTRACK_ATTR_S * pstAudioTrackAttr = (AUDIOTRACK_ATTR_S *)user;
      size_t chunksize;

      if (size == 0)
      {
          return;
      }

      if(NULL == pDestBuffer)
      {
          return;
      }
      pthread_mutex_lock(&pstAudioTrackAttr->tMutex);
      chunksize = cast_getdata(pstAudioTrackAttr, pDestBuffer, size);
      buffer->size = chunksize;
      if(size != chunksize)
      {
          //ALOGI("%s %d, track %x, need %d bytes, get %d bytes, read pos %d, write pos %d.\n ",__FUNCTION__, __LINE__,(unsigned int)pstAudioTrackAttr->pAudioTrack,size,chunksize,pstAudioTrackAttr->u32ReadPos,pstAudioTrackAttr->u32WritePos);
      }
      pthread_mutex_unlock(&pstAudioTrackAttr->tMutex);

      return ;
  }


  HiAoService::HiAoService()
  {
      int ret = 0;
      HI_UNF_SND_ATTR_S pAttr;
      HI_UNF_SND_Init();
      ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0,&pAttr);
      if (ret != HI_SUCCESS)
      {
          ALOGE("get Attr  err");
          return;
      }
      ret = HI_UNF_SND_Open(HI_UNF_SND_0,&pAttr);
      if(ret != HI_SUCCESS)
      {
          ALOGE("Open snd0 err");
          return;
      }
      char stHdmi[PROP_VALUE_MAX];
      char stSpdif[PROP_VALUE_MAX];
      char stBlueray[PROP_VALUE_MAX];
      ret = property_get("persist.sys.audio.hdmi.output", stHdmi, HI_NULL);
      if(0 == ret)
      {
          memcpy(stHdmi, HDMI_OUTPUT_DEFAULT, strlen(HDMI_OUTPUT_DEFAULT) + 1);
          property_set("persist.sys.audio.hdmi.output",HDMI_OUTPUT_DEFAULT);
          ALOGD("Hdmi use default output %s", stHdmi);
      }
      else
      {
          ALOGD("Hdmi get last output value %s", stHdmi);
      }
      ret = property_get("persist.sys.audio.spdif.output", stSpdif, HI_NULL);
      if(0 == ret)
      {
          memcpy(stSpdif, SPDIF_OUTPUT_DEFAULT, strlen(SPDIF_OUTPUT_DEFAULT) + 1);
          property_set("persist.sys.audio.spdif.output",SPDIF_OUTPUT_DEFAULT);
          ALOGD("Spdif use default output %s", stSpdif);
      }
      else
      {
          ALOGD("Spdif get last output value %s", stSpdif);
      }
      ret = property_get("persist.sys.audio.blueray",stBlueray, HI_NULL);
      if(0 == ret)
      {
          memcpy(stBlueray, HBR2LBR_DEFAULT, strlen(HBR2LBR_DEFAULT) + 1);
          property_set("persist.sys.audio.blueray",HBR2LBR_DEFAULT);
          ALOGD("Hbr2lbr use default output %s", stBlueray);
      }
      else
      {
          ALOGD("Hbr2lbr get last output value %s", stBlueray);
      }

      setUnfAudioPort(AUDIO_OUTPUT_PORT_HDMI,stHdmi[0]-'0');
      setUnfAudioPort(AUDIO_OUTPUT_PORT_SPDIF,stSpdif[0]-'0');
      BLUERAY_POSITION = stBlueray[0]-'0';
      if((stHdmi[0]-'0')!= AUDIO_OUTPUT_MODE_LPCM)
           setBluerayHbr(BLUERAY_POSITION);
  }
  HiAoService::~HiAoService()
  {
  }
  void HiAoService::instantiate()
  {
      defaultServiceManager()->addService(String16("hiaoservice"), new HiAoService());
  }

  void  CastThread(HI_VOID *args)
  {
      HI_S32 Ret;
      sp<AudioTrack> pTrack;
      HI_UNF_AO_FRAMEINFO_S  sAoFrame;
      HI_UNF_AO_FRAMEINFO_S *pstAOFrame = &sAoFrame;
      HI_U32 FrameSize = 0;
      HI_U32 u32TotalCounter=0;
      HI_U32 Frame=0;
      HI_U8 *pu8Data = NULL;
      unsigned char *pBuffer = NULL;
      HI_HANDLE hCast = *(HI_HANDLE *)args;
      unsigned int frameCount;
      memset(&stAudioTrackAttr,0,sizeof(AUDIOTRACK_ATTR_S));
      pBuffer = (unsigned char *)malloc(MAX_BUFFER_SIZE);
      memset(pBuffer,0,MAX_BUFFER_SIZE);
      AudioTrack::getMinFrameCount(&frameCount, AUDIO_STREAM_MUSIC,48000);// getMinBufferSize(48000, 2);
      uint32_t nativeChannelMask = ((uint32_t)2) >> 2;
      ALOGE("frameCount %d",frameCount);
      pTrack = new AudioTrack(AUDIO_STREAM_MUSIC,
              48000,
              AUDIO_FORMAT_PCM_16_BIT,
              nativeChannelMask,
              frameCount*2,
              AUDIO_OUTPUT_FLAG_NONE,
              &AudioTrackCallback,
              (void*)&stAudioTrackAttr,
              0,
              0);
      if(NULL == pTrack.get())
      {
         g_StopThread = HI_TRUE;
         free(pBuffer);
      }
      else{
         stAudioTrackAttr.pAudioTrack = pTrack;
         stAudioTrackAttr.pBuffer = pBuffer;
         pthread_mutex_init(&stAudioTrackAttr.tMutex,NULL);
      }

      if(NULL != pTrack.get())
      {
         usleep(50*1000);//wait Device Policy Process;
         stAudioTrackAttr.pAudioTrack->start();
      }

      while(!g_StopThread)
      {
         if(g_EnterSmartSuspend == HI_FALSE)
         {
              Ret = HI_UNF_SND_AcquireCastFrame(hCast, pstAOFrame, 0);		  
              if((HI_SUCCESS != Ret) || (pstAOFrame->u32PcmSamplesPerFrame == 0))
              {
                //  ALOGE("HI_UNF_SND_AcquireCastFrame %d \n",Ret);
                  usleep(5000);   //1024(PcmSamplesPerFrame)/192K(Max Samplerate)*1000
                  continue;
              }
              pu8Data = (HI_U8 *)pstAOFrame->ps32PcmBuffer;
              FrameSize = pstAOFrame->u32PcmSamplesPerFrame*pstAOFrame->u32Channels*pstAOFrame->s32BitPerSample/8;
              pthread_mutex_lock(&stAudioTrackAttr.tMutex);
              cast_pushdata(&stAudioTrackAttr,pu8Data,FrameSize);
              pthread_mutex_unlock(&stAudioTrackAttr.tMutex);
              HI_UNF_SND_ReleaseCastFrame(hCast, pstAOFrame);
         }
		 else
		 {
			 usleep(5000);

		 }
      }

      if(NULL != pTrack.get()){
          usleep(50*1000);//wait Device Policy Process;
          stAudioTrackAttr.pAudioTrack->stop();
          free(pBuffer);
      }
  }

  void  HiAoService::startCardPlay()
  {
      ALOGE("AOService::startCardPlay()");
      HI_S32 Ret;
      HI_UNF_SND_CAST_ATTR_S stCastAttr;
	  char stPolicy[PROP_VALUE_MAX];
      Ret = HI_UNF_SND_GetDefaultCastAttr(HI_UNF_SND_0, &stCastAttr);
      if(HI_SUCCESS != Ret)
      {
          ALOGE("Get Default Cast Attr Failed \n");
      }
      stCastAttr.u32PcmSamplesPerFrame = 512;
	  stCastAttr.bAddMute = HI_FALSE;
	  if(NULL == g_hCast)
      {
          ALOGI("AoService CreateCast");
          Ret = HI_UNF_SND_CreateCast(HI_UNF_SND_0,  &stCastAttr, &g_hCast);

          if(HI_SUCCESS != Ret)
          {
              ALOGE("Create Cast fail \n");
              HI_UNF_SND_DestroyCast(g_hCast);
          }
          Ret = HI_UNF_SND_SetCastEnable(g_hCast, HI_TRUE);

          if(HI_SUCCESS != Ret)
          {
              ALOGE("Set CastEnable fail \n");
          }
          property_get("persist.sys.audio.policy",stPolicy,"0");
          if(!(stPolicy[0]-'0')){
              HI_UNF_SND_SetMute(HI_UNF_SND_0,HI_UNF_SND_OUTPUTPORT_ALL,HI_TRUE);
          }
          g_StopThread = HI_FALSE;
          pthread_create(&g_CastThread, HI_NULL,(void* (*)(void*)) CastThread, &g_hCast);
      }
  }

  void  HiAoService::stopCardPlay()
  {
      int Ret;
      ALOGE("AOService::stopCardPlay()");
      g_StopThread = HI_TRUE;
      pthread_join(g_CastThread, HI_NULL);
      Ret = HI_UNF_SND_SetCastEnable(g_hCast, HI_FALSE);
      if(HI_SUCCESS != Ret)
      {
         ALOGE("Set Cast fail");
      }
      if(g_hCast)
      {
          ALOGE("Cast Destroy");
          Ret = HI_UNF_SND_DestroyCast(g_hCast);
          if(HI_SUCCESS != Ret)
          {
              ALOGE("DestroyCast fail");
          }
      }
	  g_hCast = NULL;
      char stHdmi[PROP_VALUE_MAX];
      char stSpdif[PROP_VALUE_MAX];
      char stBlueray[PROP_VALUE_MAX];
	  char stPolicy[PROP_VALUE_MAX];
      property_get("persist.sys.audio.hdmi.output", stHdmi, "1");//default auto mode
      property_get("persist.sys.audio.spdif.output", stSpdif, "3");//default raw
      property_get("persist.sys.audio.blueray",stBlueray,"0");//default auto mode
	  property_get("persist.sys.audio.policy",stPolicy,"0");
      setUnfAudioPort(AUDIO_OUTPUT_PORT_HDMI,stHdmi[0]-'0');
      setUnfAudioPort(AUDIO_OUTPUT_PORT_SPDIF,stSpdif[0]-'0');
      BLUERAY_POSITION = stBlueray[0]-'0';
      if(!(stPolicy[0]-'0')){
          if((stHdmi[0]-'0')!= AUDIO_OUTPUT_MODE_LPCM)
              setBluerayHbr(BLUERAY_POSITION);
          if(stHdmi[0]-'0'){
              HI_UNF_SND_SetMute(HI_UNF_SND_0,HI_UNF_SND_OUTPUTPORT_ALL,HI_FALSE);
          }
          else{
              HI_UNF_SND_SetMute(HI_UNF_SND_0,HI_UNF_SND_OUTPUTPORT_ALL,HI_FALSE);
              HI_UNF_SND_SetMute(HI_UNF_SND_0,HI_UNF_SND_OUTPUTPORT_HDMI0,HI_TRUE);
          }
	  }
  }

    int HiAoService::setUnfAudioPort(int port,int mode)
    {
      ALOGI("setUnfAudioPort port%d,mode %d",port,mode);
      int ret;
	  char stPolicy[PROP_VALUE_MAX];
	  property_get("persist.sys.audio.policy",stPolicy,"0");
      if(port == AUDIO_OUTPUT_PORT_HDMI)
      {
          if(mode == AUDIO_OUTPUT_MODE_OFF)//close
          {
              if(!g_StopThread && !(stPolicy[0]-'0')){
                  ret = HI_SUCCESS;
              }
              else{
                  ret = HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_TRUE);
              }
              if(ret == HI_SUCCESS)
              {
                 property_set("persist.sys.audio.hdmi.output","0");
                 property_set("persist.sys.audio.truehd", "0");
              }

          }
          if(mode == AUDIO_OUTPUT_MODE_LPCM)//pcm
          {
              if(!g_StopThread && !(stPolicy[0]-'0')){
                  ret = HI_SUCCESS;
              }
              else{
                  HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE);
                  ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0,HI_UNF_SND_HDMI_MODE_LPCM);
              }
              if(ret == HI_SUCCESS)
              {
                 property_set("persist.sys.audio.truehd", "0");
                 property_set("persist.sys.audio.hdmi.output","2");
              }
          }
          if(mode == AUDIO_OUTPUT_MODE_AUTO)//auto
          {
              if(BLUERAY_AUTO == BLUERAY_POSITION)
              {
                  if(!g_StopThread && !(stPolicy[0]-'0')){
                      ret = HI_SUCCESS;
                  }
                  else{
                      HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE);
                      ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_AUTO);
                  }
                  if(ret == HI_SUCCESS)
                  {
                    //property_set("persist.sys.audio.truehd", "0");
                    property_set("persist.sys.audio.hdmi.output","1");
                  }
                  if((TWO_CHANNEL == EDID_CAP)  )
                  {
                       ALOGE("HDMI AUTO ,EDID <=6");
                       property_set("persist.sys.audio.truehd", "0");//AC3
                  }
                  if( (EIGHT_CHANNEL == EDID_CAP) || (SIX_CHANNEL == EDID_CAP))
                  {
                      ALOGE("HDMI AUTO EDID 8");
                      property_set("persist.sys.audio.truehd", "1");//TRUEHD
                  }
              }
              if(BLUERAY_H2L == BLUERAY_POSITION)
              {
                  if(!g_StopThread && !(stPolicy[0]-'0')){
                      ret = HI_SUCCESS;
                  }
                  else{
                      HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE);
                      ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_HBR2LBR);
                  }
                  if(ret == HI_SUCCESS)
                  {
                      property_set("persist.sys.audio.truehd", "0");
                      property_set("persist.sys.audio.hdmi.output","1");//Auto
                  }
              }
              if(BLUERAY_RAW == BLUERAY_POSITION)
              {
                  if(!g_StopThread && !(stPolicy[0]-'0')){
                      ret = HI_SUCCESS;
                  }
                  else{
                      HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE);
                      ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
                  }
                  if(ret == HI_SUCCESS)
                  {
                      property_set("persist.sys.audio.truehd", "1");
                      property_set("persist.sys.audio.hdmi.output","1");//Auto
                  }
              }

          }
          if(mode == AUDIO_OUTPUT_MODE_RAW)//raw
          {
              ALOGE("AUDIO_OUTPUT : HDMI  Mode:RAW");
              if( (BLUERAY_AUTO == BLUERAY_POSITION) || (BLUERAY_RAW == BLUERAY_POSITION))
              {
                  if(!g_StopThread && !(stPolicy[0]-'0')){
                      ret = HI_SUCCESS;
                  }
                  else{
                      HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE);
                      ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
                  }
                  if(ret == HI_SUCCESS)
                  {
                      ALOGE("set HDMI Mode Success");
                      property_set("persist.sys.audio.truehd", "1");//TRUEHD
                      property_set("persist.sys.audio.hdmi.output","3");//RAW
                  }
              }
              if(BLUERAY_H2L == BLUERAY_POSITION)
              {
                  if(!g_StopThread && !(stPolicy[0]-'0')){
                      ret = HI_SUCCESS;
                  }
                  else{
                      HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_FALSE);
                      ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0,HI_UNF_SND_HDMI_MODE_HBR2LBR );
                  }
                  if(ret == HI_SUCCESS)
                  {
                      property_set("persist.sys.audio.truehd", "0");//AC3
                      property_set("persist.sys.audio.hdmi.output","3");//H2L
                  }
              }
           }
      }

      if(port == AUDIO_OUTPUT_PORT_SPDIF)
      {
          if(mode == AUDIO_OUTPUT_MODE_OFF)//close
          {
              if(!g_StopThread && !(stPolicy[0]-'0')){
                  ret = HI_SUCCESS;
              }
              else{
                  ret = HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_TRUE);
              }
              if(ret == HI_SUCCESS)
              {
                 property_set("persist.sys.audio.spdif.output","0");
              }
          }
          if(mode == AUDIO_OUTPUT_MODE_LPCM)
          {
              if(!g_StopThread && !(stPolicy[0]-'0')){
                 ret = HI_SUCCESS;
              }
              else{
                  HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_FALSE);
                  ret = HI_UNF_SND_SetSpdifMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_UNF_SND_SPDIF_MODE_LPCM);
              }
              if(ret == HI_SUCCESS)
              {
                  property_set("persist.sys.audio.spdif.output","2");//lpcm port
              }
          }
          if(mode == AUDIO_OUTPUT_MODE_RAW)
          {
              if(!g_StopThread && !(stPolicy[0]-'0')){
                  ret = HI_SUCCESS;
              }
              else{
                  HI_UNF_SND_SetMute(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_FALSE);
                  ret = HI_UNF_SND_SetSpdifMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_SPDIF0, HI_UNF_SND_SPDIF_MODE_RAW);
              }
              if(ret == HI_SUCCESS)
              {
                  property_set("persist.sys.audio.spdif.output","3");//raw port
              }
          }
      }

    return 0;
  }

  int HiAoService::getUnfAudioPort(int port)
  {
      ALOGI(" AOService::getUnfAudioPort");
      char stHdmi[PROP_VALUE_MAX];
      char stSpdif[PROP_VALUE_MAX];
      char stBlueray[PROP_VALUE_MAX];
      if(port == AUDIO_OUTPUT_PORT_HDMI)
      {
          property_get("persist.sys.audio.hdmi.output", stHdmi, "1");
          return stHdmi[0]-'0';
      }
      if(port == AUDIO_OUTPUT_PORT_SPDIF)
      {
          property_get("persist.sys.audio.spdif.output", stSpdif, "1");
          return stSpdif[0]-'0';
      }
      if(port == AUDIO_OUTPUT_PORT_BLUERAY)
      {
          property_get("persist.sys.audio.blueray", stBlueray, "0");
          return stBlueray[0]-'0';
      }
      ALOGE(" ERR PORT VALUE");
      return 0;
  }

  void HiAoService::setAudEdidCap(int channel)
  {
      EDID_CAP = channel;
      ALOGE("EDID CAP %d",channel);
      int mode = 0;
      char stHdmi[PROP_VALUE_MAX];
      property_get("persist.sys.audio.hdmi.output", stHdmi, "1");
      mode = stHdmi[0]-'0';
      ALOGI("get port sthdmi setting %d",stHdmi[0]-'0');
      if(mode == AUDIO_OUTPUT_MODE_AUTO)//AUTO mode
      {
          if(EDID_CAP < SIX_CHANNEL)
          {
              property_set("persist.sys.audio.truehd", "0");//AC3
          }
          if( (EIGHT_CHANNEL == EDID_CAP) || (SIX_CHANNEL == EDID_CAP) )
          {
              property_set("persist.sys.audio.truehd", "1");//TRUEHD
          }
      }
  }

  int HiAoService::setBluerayHbr(int status)
  {
      ALOGE("setBluerayHbr %d",status);
	  char stPolicy[PROP_VALUE_MAX];
	  property_get("persist.sys.audio.policy",stPolicy,"0");
      if(status == BLUERAY_AUTO)//AUTO mode
      {
          property_set("persist.sys.audio.blueray", "0");
          BLUERAY_POSITION  = BLUERAY_AUTO;
          int mode = 0;
          mode = getUnfAudioPort(AUDIO_OUTPUT_PORT_HDMI);
          ALOGI("get mode %d",mode);
          if(mode == AUDIO_OUTPUT_MODE_AUTO)
          {
              if(g_StopThread ||!(stPolicy[0]-'0')){
                  HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_AUTO);
              }
              if(TWO_CHANNEL == EDID_CAP)
              {
                  property_set("persist.sys.audio.truehd", "0");//AC3
              }
              if( (EIGHT_CHANNEL == EDID_CAP) || (SIX_CHANNEL == EDID_CAP))
              {
                  property_set("persist.sys.audio.truehd", "1");//TRUEHD
              }

          }
          if(mode == AUDIO_OUTPUT_MODE_RAW)
          {
              property_set("persist.sys.audio.truehd", "1");//TRUEHD
              if(g_StopThread ||!(stPolicy[0]-'0')){
                  HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
              }
          }
       }
       if(status == BLUERAY_H2L)
       {
           property_set("persist.sys.audio.blueray", "1");
           BLUERAY_POSITION = BLUERAY_H2L;
           property_set("persist.sys.audio.truehd", "0");//AC3
           if(g_StopThread ||!(stPolicy[0]-'0')){
               HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_HBR2LBR);
           }
       }
       if(status == BLUERAY_RAW)
       {
          property_set("persist.sys.audio.blueray", "2");
          BLUERAY_POSITION = BLUERAY_RAW;
          property_set("persist.sys.audio.truehd", "1");//TRUEHD
          if(g_StopThread ||!(stPolicy[0]-'0')){
               HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
          }
       }
      return 0;
  }
  int HiAoService::setEnterSmartSuspend(int status)
  {    
    g_EnterSmartSuspend = (HI_BOOL)status;
	return 0;
  }
    int HiAoService::setSndVolume(int volume)
    {
        int ret;
        ALOGE("HiAoService setSndVolume = %d", volume);
        HI_UNF_SND_GAIN_ATTR_S sGain;
        sGain.bLinearMode = HI_TRUE;
        sGain.s32Gain = volume;
        ret = HI_UNF_SND_SetVolume(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_ALL, &sGain);
        return ret;
    }
};
