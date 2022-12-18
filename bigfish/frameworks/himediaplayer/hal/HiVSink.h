#ifndef HI_VSINK_H
#define HI_VSINK_H

#include <utils/RefBase.h>
#include <cutils/native_handle.h>
#include <android/native_window.h>
#include <utils/KeyedVector.h>
#include <hi_svr_vsink.h>
#include <hi_type.h>

namespace android {
/**
 * An Android implementation of HI_SVR_VSINK_S.
 * Adapt ANativeWindow interface to HI_SVR_VSINK_S interface.
 */
class HiVSink
    : public HI_SVR_VSINK_S, public RefBase
{
public:
    HiVSink(sp<ANativeWindow> window);
    int setNativeWindow(const sp<ANativeWindow>& window);
protected:
    ~HiVSink();
private:
    HiVSink& operator = (const HiVSink& rhs);
    HiVSink(HiVSink&);

    /**
     * hi_svr_sink implementations hooks
     */
    static int hook_cancel(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pics, HI_U32 cnt);
    static int hook_dequeue(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pics, HI_U32 cnt);
    static int hook_prepare(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pic);
    static int hook_queue(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pic);
    static int hook_control(HI_SVR_VSINK_S* vsink, HI_U32 cmd, ...);

    /**
     * hi_svr_sink implementations
     */
    int cancel(HI_SVR_PICTURE_S* pics, HI_U32 cnt);
    int dequeue(HI_SVR_PICTURE_S* pics, HI_U32 cnt);
    int prepare(HI_SVR_PICTURE_S* pic);
    int queue(HI_SVR_PICTURE_S* pic);
    int control(HI_U32 cmd, va_list);

    int dispatchSetDimations(va_list args);
    int dispatchSetFormat(va_list args);
    int dispatchSetPicCnt(va_list args);
    int dispatchWritePic(va_list args);
    int dispatchSetCrop(va_list args);
    int dispatchGetMinBufNb(va_list args);
    int dispatchCheckFence(va_list args);
    int dispatchSetUsage(va_list args);

    void dumpYUVFrame(ANativeWindowBuffer* buf);
    void writeYUVFrame(ANativeWindowBuffer* buf, HI_U8* src, HI_U32 size);

    sp<ANativeWindow> mNativeWindow;
    int mUsage;
    int mFormat;
    int mWidth;
    int mHeight;
    int mQueueToSurfaceFlinger;
    KeyedVector<HI_HANDLE, struct ANativeWindowBuffer*> mBufMap;
    KeyedVector<HI_HANDLE, int> mFenceMap;
    android_native_rect_t mCrop;
};
}; // namespace android
#endif
