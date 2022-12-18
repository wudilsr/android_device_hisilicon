#ifndef _CTC_MEDIACONTROL_H_
#define _CTC_MEDIACONTROL_H_

#include "IIPTVPlayer.h"

class RenderTarget;
class TsPlayerAdapter;
class WPLAYER;
class PPPoEConnect;

class CTC_MediaControl : public CTsPlayer{
    public:
        CTC_MediaControl();
        virtual ~CTC_MediaControl();
    public:
        //取得播放模式
        virtual int  GetPlayMode();
        //显示窗口
        virtual int  SetVideoWindow(int x,int y,int width,int height);
        //x显示视频
        virtual int  VideoShow(void);
        //隐藏视频
        virtual int  VideoHide(void);
        //初始化视频参数
        virtual void InitVideo(PVIDEO_PARA_T pVideoPara);
        //初始化音频参数
        virtual void InitAudio(PAUDIO_PARA_T pAudioPara);
        //开始播放
        virtual bool StartPlay();
        //把ts流写入
        virtual int WriteData(unsigned char* pBuffer, unsigned int nSize);
        //暂停
        virtual bool Pause();
        //继续播放
        virtual bool Resume();
        //快进快退
        virtual bool Fast();
        //停止快进快退
        virtual bool StopFast();
        //停止
        virtual bool Stop();
        //定位
        virtual bool Seek();
        //设定音量
        //设定音量
        virtual bool SetVolume(int volume);
        //获取音量
        virtual int GetVolume();
        //设定视频显示比例
        virtual bool SetRatio(int nRatio);
        //获取当前声道
        virtual int GetAudioBalance();
        //设置声道
        virtual bool SetAudioBalance(int nAudioBalance);
        //获取视频分辩率
        virtual void GetVideoPixels(int& width, int& height);
        virtual bool IsSoftFit();
        virtual void SetEPGSize(int w, int h);
        //  virtual void SetSurface(Surface* pSurface);
    public: // member functions
        TsPlayerAdapter* GetTsPlayerAdapter()
        {
            return _adapter;
        }
        WPLAYER* GetWPLAYER() { return _wplayer; }
        void Initialize(bool fastMode = false, bool useAudioSink = true);
        void Cleanup();
        void Reinitialize(bool fastMode);
    protected:  // member variable
        WPLAYER* _wplayer;
        TsPlayerAdapter* _adapter;
        wiptv_callback* mCallback;
        bool mInitialized;
        RenderTarget* mRenderTarget;
        PPPoEConnect* _mPPPoEConnect;
};

CTC_MediaControl* GetMediaProcessor();
int GetMediaControlVersion();

#endif
