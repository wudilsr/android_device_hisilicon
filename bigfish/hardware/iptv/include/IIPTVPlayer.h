#ifndef _IIPTVPLAYER_H_
#define _IIPTVPLAYER_H_


//using namespace android;

#include "Common.h"

class CTsPlayer{
    public:
        CTsPlayer(){}
        virtual ~CTsPlayer(){}
    public:
        //取得播放模式
        virtual int  GetPlayMode()=0;
        //显示窗口
        virtual int  SetVideoWindow(int x,int y,int width,int height)=0;
        //x显示视频
        virtual int  VideoShow(void)=0;
        //隐藏视频
        virtual int  VideoHide(void)=0;
        //初始化视频参数
        virtual void InitVideo(PVIDEO_PARA_T pVideoPara)=0;
        //初始化音频参数
        virtual void InitAudio(PAUDIO_PARA_T pAudioPara)=0;
        //开始播放
        virtual bool StartPlay()=0;
        //把ts流写入
        virtual int WriteData(unsigned char* pBuffer, unsigned int nSize)=0;
        //暂停
        virtual bool Pause()=0;
        //继续播放
        virtual bool Resume()=0;
        //快进快退
        virtual bool Fast()=0;
        //停止快进快退
        virtual bool StopFast()=0;
        //停止
        virtual bool Stop()=0;
        //定位
        virtual bool Seek()=0;
        //设定音量
        virtual bool SetVolume(int volume)=0;
        //获取音量
        virtual int GetVolume()=0;
        //设定视频显示比例
        virtual bool SetRatio(int nRatio)=0;
        //获取当前声道
        virtual int GetAudioBalance()=0;
        //设置声道
        virtual bool SetAudioBalance(int nAudioBalance)=0;
        //获取视频分辩率
        virtual void GetVideoPixels(int& width, int& height)=0;
        virtual bool IsSoftFit()=0;
        virtual void SetEPGSize(int w, int h)=0;
        //virtual void SetSurface(Surface* pSurface)=0;
};

#endif
