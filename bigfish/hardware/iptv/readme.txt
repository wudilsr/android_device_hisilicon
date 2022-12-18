playback TS stream(TS is one synced with 0x47  stream format )

CTsPlayer :
class CTC_MediaProcessor{
    public:
        CTC_MediaProcessor(){}
        virtual ~CTC_MediaProcessor(){}
    public:
        //get the play mode
        virtual int  GetPlayMode()=0;
        //set window coordinate
        virtual int  SetVideoWindow(int x,int y,int width,int height)=0;
        //display video
        virtual int  VideoShow(void)=0;
        //hide video
        virtual int  VideoHide(void)=0;
        //init video para
        virtual void InitVideo(VIDEO_PARA_T* pVideoPara)=0;
        //init audio para, pAudioParam is the track list,  
        virtual void InitAudio(AUDIO_PARA_T* pAudioPara)=0;
        //start play
        virtual bool StartPlay()=0;
        //put tsbuf
        virtual int WriteData(unsigned char* pBuffer, unsigned int nSize)=0;
        //pause play
        virtual bool Pause()=0;
        //resume play
        virtual bool Resume()=0;
        //trick play
        virtual bool Fast()=0;
        //stop trick play
        virtual bool StopFast()=0;
        //stop
        virtual bool Stop()=0;
        //seek
        virtual bool Seek()=0;
        //set the volume
        virtual bool SetVolume(int volume)=0;
        //get the volume
        virtual int GetVolume()=0;
        //set the window ratio
        virtual bool SetRatio(int nRatio)=0;
        //get current audio channel
        virtual int GetAudioBalance()=0;
        //set audio channel
        virtual bool SetAudioBalance(int nAudioBalance)=0;
        //get the video resolution ratio
        virtual void GetVideoPixels(int& width, int& height)=0;

        virtual bool IsSoftFit()=0;
        virtual void SetEPGSize(int w, int h)=0;
        virtual void SetSurface(Surface* pSurface)=0;
        //switch audio track, pid is the new audio PID
        virtual void SwitchAudioTrack(int pid) = 0;
        //switch subtitle, pid is the new subtitle PID,
        virtual void SwitchSubtitle(int pid) = 0;
        //setting of audio and video attr
        virtual void SetProperty(int nType, int nSub, int nValue) = 0;
        //get the play time, ms
        virtual long GetCurrentPlayTime() = 0;
        //leave channel
        virtual void leaveChannel() = 0;

        virtual void playerback_register_evt_cb(IPTV_PLAYER_EVT_CB pfunc, void *hander) = 0;
};
