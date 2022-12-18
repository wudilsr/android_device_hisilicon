#define LOG_NDEBUG 0
#define LOG_TAG "HisiSurfaceSetting"


#include <cutils/properties.h>
#include "hi_unf_vo.h"
#include "DisplayClient.h"
#include "hidisplay.h"
#include "HiSurfaceSetting.h"

namespace android {
// surfaceSetting Class Impl

surfaceSetting::surfaceSetting( HI_HANDLE window)
                            : mWindow(window)
{
    init();
}

void surfaceSetting::init()
{
    LOGV("surfaceSetting::init");
    char buffer[PROP_VALUE_MAX];
    DisplayClient dispClient;

    char buffer_orientation[PROP_VALUE_MAX];
    memset(buffer_orientation, 0, sizeof(buffer_orientation));
    property_get("persist.sys.screenorientation", buffer_orientation, "landscape");
    int cmpRet = strcmp("landscape", buffer_orientation);
    if (cmpRet == 0)
    {
        screen_orientation = 0;  // landscape
    }
    else
    {
        screen_orientation = 1;  // portrait
    }

    mSurfaceX = 0;
    mSurfaceY = 0;

    dispClient.GetVirtScreenSize(&mSurfaceWidth, &mSurfaceHeight);

    mRatio.width = -1;
    mRatio.height = -1;

    mCvrs = dispClient.GetAspectCvrs(); //HIMEDIAPLAYER_CURVE_DEFAUL;
    LOGV("init mCvrs is %d", mCvrs);

    setVideoWindowAttr(mSurfaceX, mSurfaceY, mSurfaceWidth, mSurfaceHeight, mRatio, mCvrs);
}

status_t surfaceSetting::updateSurfacePosition()
{
    return setVideoWindowAttr(mSurfaceX, mSurfaceY, mSurfaceWidth, mSurfaceHeight, mRatio, mCvrs);
}

status_t surfaceSetting::setVideoWindowAttr(int x, int y,
                                              int w, int h, HI_ASPECT_RATIO_S ratio, int cvrs)
{
    HI_S32 s32Ret = NO_ERROR;
    HI_UNF_WINDOW_ATTR_S WinAttr;
    //LOGV("HI_UNF_VO_SetWindowAttr x[%d] y[%d] w[%d] h[%d] mCvrs[%d]", x, y, w, h, cvrs);

    if (screen_orientation == 0)
    {  // landscape
        mSurfaceX      = x;
        mSurfaceY      = y;
        mSurfaceWidth  = w;
        mSurfaceHeight = h;
    }
    else
    {  // portrait
        if (x == mSurfaceX && y == mSurfaceY && w == mSurfaceWidth && h == mSurfaceHeight)
        {
            mSurfaceX      = x;
            mSurfaceY      = y;
            mSurfaceWidth  = w;
            mSurfaceHeight = h;
        }
        else
        {
            mSurfaceX      = y;
            mSurfaceY      = x;
            mSurfaceWidth  = h;
            mSurfaceHeight = w;
        }
    }
    //LOGV("HI_UNF_VO_SetWindowAttr mSurfaceX[%d] mSurfaceY[%d] mSurfaceWidth[%d] mSurfaceHeight[%d] mCvrs[%d]",
    //        mSurfaceX, mSurfaceY, mSurfaceWidth, mSurfaceHeight, cvrs);
    mRatio.width = ratio.width;
    mRatio.height = ratio.height;
    mCvrs          = cvrs;

    if (HI_SVR_PLAYER_INVALID_HDL == mWindow
      || HI_SUCCESS != HI_UNF_VO_GetWindowAttr(mWindow, &WinAttr))
    {
        LOGV("setVideoWindowAttr mWindow or GetWindowAttr error");
        return UNKNOWN_ERROR;
    }

    if (screen_orientation == 1)
    {  // portrait
        //HI_UNF_VO_ROTATION_E enRotation;
        //HI_UNF_VO_GetRotation(mWindow, &enRotation);
        HI_UNF_VO_SetRotation(mWindow, HI_UNF_VO_ROTATION_90);
    }
    WinAttr.stOutputRect.s32X = mSurfaceX;
    WinAttr.stOutputRect.s32Y = mSurfaceY;
    WinAttr.stOutputRect.s32Width = mSurfaceWidth;
    WinAttr.stOutputRect.s32Height = mSurfaceHeight;

    if (-1 != mRatio.width && -1 != mRatio.height)
    {
        WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_TRUE;
        WinAttr.stWinAspectAttr.u32UserAspectHeight = mRatio.height;
        WinAttr.stWinAspectAttr.u32UserAspectWidth = mRatio.width;
    }
    else
    {
        WinAttr.stWinAspectAttr.bUserDefAspectRatio = HI_FALSE;
    }

    WinAttr.stWinAspectAttr.enAspectCvrs  = (HI_UNF_VO_ASPECT_CVRS_E)mCvrs;
    LOGV("HI_UNF_VO_SetWindowAttr x[%d] y[%d] w[%d] h[%d] mCvrs[%d] ratio [w %d] [h %d] bUserDefAspectRatio is %d",
        WinAttr.stOutputRect.s32X, WinAttr.stOutputRect.s32Y, WinAttr.stOutputRect.s32Width,
        WinAttr.stOutputRect.s32Height, mCvrs, WinAttr.stWinAspectAttr.u32UserAspectWidth, WinAttr.stWinAspectAttr.u32UserAspectHeight,
                WinAttr.stWinAspectAttr.bUserDefAspectRatio);
    s32Ret = HI_UNF_VO_SetWindowAttr(mWindow, &WinAttr);

    return ((HI_SUCCESS == s32Ret) ? NO_ERROR : UNKNOWN_ERROR);
}

status_t surfaceSetting::updateSurfacePosition(int x, int y, int w, int h)
{
    if ( w < 0 || h < 0 )
        return UNKNOWN_ERROR;
    if ( x < 0 || y < 0)
        return UNKNOWN_ERROR;
    if (x == mSurfaceX && y == mSurfaceY && w == mSurfaceWidth && h == mSurfaceHeight)
        return NO_ERROR;

    return setVideoWindowAttr(x, y, w, h, mRatio, mCvrs);
}

status_t surfaceSetting::setVideoRatio(HI_ASPECT_RATIO_S Ratio)
{
    if (Ratio.width == mRatio.width && Ratio.height == mRatio.height)
    {
        LOGV("Ratio setting w %d h %d is same with current setting", Ratio.width, Ratio.height);
        return NO_ERROR;
    }

    if (Ratio.width < 0 || Ratio.width > HIMEDIA_ASPECTRATIO_WIDTH_MAX || Ratio.height < 0
        || Ratio.height > HIMEDIA_ASPECTRATIO_HEIGHT_MAX)
    {
        LOGV("Ratio setting is illegal,w %d h %d,width range is 0--%d height range is 0--%d", Ratio.width, Ratio.height, HIMEDIA_ASPECTRATIO_WIDTH_MAX,
            HIMEDIA_ASPECTRATIO_HEIGHT_MAX);
    }
    return setVideoWindowAttr(mSurfaceX, mSurfaceY, mSurfaceWidth,
                                             mSurfaceHeight, Ratio, mCvrs);
}

status_t surfaceSetting::setVideoCvrs(int cvrs)
{
    if (cvrs == mCvrs || cvrs < 0)
        return NO_ERROR;

    mCvrs = cvrs;

    if (HI_SVR_PLAYER_INVALID_HDL == mWindow)
    {
        return NO_ERROR;
    }

    return setVideoWindowAttr(mSurfaceX, mSurfaceY, mSurfaceWidth,
                                             mSurfaceHeight, mRatio, cvrs);
}

status_t surfaceSetting::setVideoZOrder(int ZOrder)
{
    HI_S32 s32Ret = HI_FAILURE;
    LOGV("Call surfaceSetting::setVideoZOrder IN");

    if (HI_SVR_PLAYER_INVALID_HDL == mWindow)
    {
        LOGE("setVideoZOrder window is null");
        return UNKNOWN_ERROR;
    }

    HI_LAYER_ZORDER_E       ZOrderToSet = HI_LAYER_ZORDER_BUTT;
    switch (ZOrder)
    {
        case HI_MEDIAPLAYER_ZORDER_MOVETOP:
        {
            ZOrderToSet = HI_LAYER_ZORDER_MOVETOP;
            LOGV("VO Move Top");
            break;
        }
        case HI_MEDIAPLAYER_ZORDER_MOVEUP:
        {
            ZOrderToSet = HI_LAYER_ZORDER_MOVEUP;
            LOGV("VO Move Up");
            break;
        }
        case HI_MEDIAPLAYER_ZORDER_MOVEBOTTOM:
        {
            ZOrderToSet = HI_LAYER_ZORDER_MOVEBOTTOM;
            LOGV("VO Move Buttom");
            break;
        }
        case HI_MEDIAPLAYER_ZORDER_MOVEDOWN:
        {
            ZOrderToSet = HI_LAYER_ZORDER_MOVEDOWN;
            LOGV("VO Move Down");
            break;
        }
        default:
        {
            ZOrderToSet = HI_LAYER_ZORDER_BUTT;
            break;
        }
    }

    if (HI_LAYER_ZORDER_BUTT == ZOrderToSet)
    {
        LOGE("setVideoZOrder,Invalid args, the input arg is %d", ZOrder);
        return UNKNOWN_ERROR;
    }

    s32Ret = HI_UNF_VO_SetWindowZorder(mWindow, ZOrderToSet);
    return ((HI_SUCCESS == s32Ret) ? NO_ERROR : UNKNOWN_ERROR);
}

status_t  surfaceSetting::setWindowFreezeStatus(int flag)
{
    HI_S32 s32Ret = HI_FAILURE;
    LOGV("Call surfaceSetting::setWindowFreezeStatus IN");

    if (HI_SVR_PLAYER_INVALID_HDL == mWindow)
    {
        LOGE("setWindowFreeze window is null");
        return UNKNOWN_ERROR;
    }

    HI_BOOL bFlag = (0 == flag) ? HI_FALSE : HI_TRUE;

    LOGV("Call surfaceSetting::setWindowFreezeStatus flag = %d, bFlag = %d\n",flag,bFlag);

    s32Ret = HI_UNF_VO_FreezeWindow(mWindow, bFlag, HI_UNF_WINDOW_FREEZE_MODE_BLACK);

    return ((HI_SUCCESS == s32Ret) ? NO_ERROR : UNKNOWN_ERROR);
}

} // end namespace android
