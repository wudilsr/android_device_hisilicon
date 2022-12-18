#ifndef _ANDROID_SURFACESETTING_H_
#define _ANDROID_SURFACESETTING_H_

#include <utils/threads.h>
#include <gui/Surface.h>
#include "hi_svr_player.h"
#include "mediaplayer.h"
#include "HiMediaDefine.h"

namespace android {
    //aspect ratio
    typedef struct hiASPECT_RATIO_S
    {
        int width;
        int height;
    } HI_ASPECT_RATIO_S;

    class surfaceSetting : virtual public RefBase
    {
    public:
        surfaceSetting( HI_HANDLE window = HI_SVR_PLAYER_INVALID_HDL);
        ~surfaceSetting() { };
        void init();

        void setWindow(HI_HANDLE window) { mWindow = window; }
        HI_HANDLE getWindow() { return mWindow; }

        status_t updateSurfacePosition();

        int updateSurfacePosition(int x, int y, int w, int h);

        int setVideoRatio(HI_ASPECT_RATIO_S Ratio);
        HI_ASPECT_RATIO_S getVideoRatio() { return mRatio; }
        status_t setVideoZOrder(int ZOrder);
        status_t  setWindowFreezeStatus(int flag);
        int setVideoCvrs(int cvrs);
        int getVideoCvrs()  { return mCvrs;  }

        static int getScreenResolution(int& w, int& h)
        {
            w = HIMEDIA_VIRTUAL_SCREEN_W;
            h = HIMEDIA_VIRTUAL_SCREEN_H;
            return 0;
        }

    private:
        HI_HANDLE mWindow;

        int mSurfaceX;
        int mSurfaceY;
        int mSurfaceWidth;
        int mSurfaceHeight;

        int mCvrs;
        HI_ASPECT_RATIO_S mRatio;

        status_t setVideoWindowAttr(int x, int y, int w, int h, HI_ASPECT_RATIO_S ratio, int cvrs);
    };
} // end namespace android
#endif
