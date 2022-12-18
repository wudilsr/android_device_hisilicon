#include <utils/Log.h>
#include <utils/Trace.h>
#include <gralloc_priv.h>
#include <hardware/gralloc.h>
#include <ui/GraphicBufferMapper.h>
#include <ui/Rect.h>
#include "HiVSink.h"

#define LOG_TAG "VSINK"

namespace android {

static HiVSink* getSelf(HI_SVR_VSINK_S* vsink)
{
    return static_cast<HiVSink*>(vsink);
}

static HI_HANDLE getBufferHandle(ANativeWindowBuffer* buf)
{
    private_handle_t *p_private_handle = const_cast<private_handle_t*>(
            reinterpret_cast<const private_handle_t*>(buf->handle));
    return (HI_HANDLE)p_private_handle->ion_phy_addr;
}

HiVSink::HiVSink(sp<ANativeWindow> w) :
        mNativeWindow(w), mUsage(GRALLOC_USAGE_HW_RENDER),
        mFormat(HAL_PIXEL_FORMAT_YCrCb_420_SP),
        mWidth(0), mHeight(0)
{
    // Initialize the HI_SVR_VSINK_S function pointers.
    HI_SVR_VSINK_S::cancel      = hook_cancel;
    HI_SVR_VSINK_S::dequeue     = hook_dequeue;
    HI_SVR_VSINK_S::prepare     = hook_prepare;
    HI_SVR_VSINK_S::queue       = hook_queue;
    HI_SVR_VSINK_S::control     = hook_control;
}

int HiVSink::setNativeWindow(const sp<ANativeWindow> &window)
{
    ANativeWindow* w = NULL;
    mNativeWindow.clear();
    mNativeWindow = window;
    w = mNativeWindow.get();

    if (!w)
    {
        ALOGD("native window has cleared");
        return OK;
    }
//    (void)native_window_api_connect(w, NATIVE_WINDOW_API_MEDIA);
    (void)native_window_set_usage(w, mUsage);// | GRALLOC_USAGE_HW_TEXTURE | GRALLOC_USAGE_EXTERNAL_DISP);
    native_window_set_buffers_format(w, mFormat);
    native_window_set_scaling_mode(w,
                    NATIVE_WINDOW_SCALING_MODE_SCALE_TO_WINDOW);
    ALOGD("vsink set native window %p ok", window.get());
    return OK;
}

HiVSink::~HiVSink()
{
    ALOGD("destroying HiVSink");

    if (mNativeWindow.get())
    {
        (void)native_window_api_disconnect(mNativeWindow.get(), NATIVE_WINDOW_API_MEDIA);
    }

    if (mBufMap.size())
    {
        ALOGE("Error! VSink buffer mapper crashed");
    }
    mBufMap.clear();
    mNativeWindow.clear();
    ALOGD("destroying HiVSink OK");
}

int HiVSink::hook_cancel(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pics, HI_U32 cnt)
{
    HiVSink* s = getSelf(vsink);
    return s->cancel(pics, cnt);
}

int HiVSink::hook_dequeue(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pics, HI_U32 cnt)
{
    HiVSink* s = getSelf(vsink);
    return s->dequeue(pics, cnt);
}

int HiVSink::hook_prepare(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pic)
{
    HiVSink* s = getSelf(vsink);
    return s->prepare(pic);
}

int HiVSink::hook_queue(HI_SVR_VSINK_S* vsink, HI_SVR_PICTURE_S* pic)
{
    HiVSink* s = getSelf(vsink);
    return s->queue(pic);
}

int HiVSink::hook_control(HI_SVR_VSINK_S* vsink, HI_U32 cmd, ...)
{
    va_list args;
    HiVSink* s = getSelf(vsink);

    va_start(args, cmd);
    return s->control(cmd, args);
}

int HiVSink::cancel(HI_SVR_PICTURE_S* pics, HI_U32 cnt)
{
    int err;
    uint32_t i;
    ANativeWindowBuffer* buf;
    int index;
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }

    for (i = 0; i < cnt; i++) {
        index = mBufMap.indexOfKey(pics[i].hBuffer);
        if (index < 0)
        {
            ALOGE("Invalid picture to cancel, handle:%d", pics[i].hBuffer);
            continue;
        }
        buf = mBufMap.valueAt(index);
        if (!buf) {
            ALOGE("Invalid buf to cancel, handle:%d", pics[i].hBuffer);
            continue;
        }
        err = mNativeWindow->cancelBuffer(w, buf, -1);
        if (err != 0) {
            ALOGE("cancel buffer to native window failed");
        }
        mBufMap.removeItem(pics[i].hBuffer);
    }
    return OK;
}

static inline HI_S64 SVR_CurrentClock()
{
    clock_t c = clock();
    return (HI_S64)(c * 1000 / CLOCKS_PER_SEC);
}

int HiVSink::dequeue(HI_SVR_PICTURE_S* pics, HI_U32 cnt)
{
    int err;
    HI_U32 i;
    HI_SVR_PICTURE_S tmp;
    ANativeWindowBuffer* buf = NULL;
    HI_S64 time_used = 0;

    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }

    for (i = 0; i < cnt; i++)
    {
        time_used = SVR_CurrentClock();
        err = native_window_dequeue_buffer_and_wait(w, &buf);
        ALOGV("dequeue used time:%lld", SVR_CurrentClock() - time_used);
        if (err) {
            ALOGE("dequeue buffer from native window failed");
            goto failed;
        }
        pics[i].hBuffer = getBufferHandle(buf);
        pics[i].u32Height = mHeight;
        pics[i].u32Width = mWidth;
        pics[i].s64Pts = -1;
        mBufMap.add(pics[i].hBuffer, buf);
    }
    return OK;
failed:
    (void)cancel(pics, i);
    return UNKNOWN_ERROR;
}

int HiVSink::prepare(HI_SVR_PICTURE_S* picIn)
{
    return OK;
}

int HiVSink::queue(HI_SVR_PICTURE_S* picIn)
{
    int err;
    int index;
    ANativeWindowBuffer* buf;
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }
    index = mBufMap.indexOfKey(picIn->hBuffer);
    if (index < 0)
    {
        ALOGE("Invalid picture to display, handle:%d", picIn->hBuffer);
        return UNKNOWN_ERROR;
    }
    buf = mBufMap.valueAt(index);
    if (!buf) {
        ALOGE("Invalid picture to display");
        return UNKNOWN_ERROR;
    }

//    dumpYUVFrame(buf);

    err = mNativeWindow->queueBuffer(w, buf, -1);
    if (err == 0)
    {
        mBufMap.removeItem(picIn->hBuffer);
    }
    return err;
}

int HiVSink::dispatchSetDimations(va_list args)
{
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }

    mWidth = va_arg(args, int);
    mHeight = va_arg(args, int);

    return native_window_set_buffers_dimensions(w, mWidth, mHeight);
}

int HiVSink::dispatchSetFormat(va_list args)
{
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }
    mFormat = va_arg(args, int);
    return native_window_set_buffers_format(w, mFormat);
}

int HiVSink::dispatchSetPicCnt(va_list args)
{
    int cnt;
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }
    cnt = va_arg(args, int);

    return native_window_set_buffer_count(w, cnt);
}

int HiVSink::dispatchWritePic(va_list args)
{
    HI_SVR_PICTURE_S* pic = NULL;
    HI_U8* data;
    HI_U32 size;
    ANativeWindowBuffer* buf;

    pic = va_arg(args, HI_SVR_PICTURE_S*);
    data = va_arg(args, HI_U8*);
    size = va_arg(args, HI_U32);
    buf = mBufMap.valueFor(pic->hBuffer);
    writeYUVFrame(buf, data, size);
    return OK;
}

int HiVSink::dispatchSetCrop(va_list args)
{
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }

    mCrop.left = va_arg(args, HI_S32);
    mCrop.top = va_arg(args, HI_S32);
    mCrop.right = va_arg(args, HI_S32);
    mCrop.bottom = va_arg(args, HI_S32);

    ALOGD("set native window crop, left:%d, top:%d, right:%d, bottom:%d",
            mCrop.left, mCrop.top, mCrop.right, mCrop.bottom);

    return native_window_set_crop(w, &mCrop);
}

int HiVSink::dispatchGetMinBufNb(va_list args)
{
    int err;
    int minUndequeuedBuffers;
    HI_U32* pstMinBufNb;
    ANativeWindow* w = mNativeWindow.get();

    if (!w)
    {
        ALOGE("native window did not set");
        return UNKNOWN_ERROR;
    }

    pstMinBufNb = va_arg(args, HI_U32*);


    err = mNativeWindow->query(
            mNativeWindow.get(), NATIVE_WINDOW_MIN_UNDEQUEUED_BUFFERS,
            &minUndequeuedBuffers);
    if (err)
    {
        ALOGE("query mini undequeued buffer failed");
        return HI_FAILURE;
    }
    ALOGD("undequeue cnt:%d", minUndequeuedBuffers);
    *pstMinBufNb = (HI_U32)minUndequeuedBuffers;

    return OK;
}

int HiVSink::control(HI_U32 cmd, va_list args)
{
    switch (cmd) {
    case HI_SVR_VSINK_SET_DIMENSIONS:
        return dispatchSetDimations(args);
        break;
    case HI_SVR_VSINK_SET_FORMAT:
        return dispatchSetFormat(args);
        break;
    case HI_SVR_VSINK_SET_PICNB:
        return dispatchSetPicCnt(args);
        break;
    case HI_SVR_VSINK_WRITE_PIC:
        return dispatchWritePic(args);
        break;
    case HI_SVR_VSINK_SET_CROP:
        return dispatchSetCrop(args);
        break;
    case HI_SVR_VSINK_GET_MINBUFNB:
        return dispatchGetMinBufNb(args);
        break;
    default:
        return UNKNOWN_ERROR;
        break;
    }
    return OK;
}

void HiVSink::dumpYUVFrame(ANativeWindowBuffer* buf)
{
    GraphicBufferMapper &mapper = GraphicBufferMapper::get();

    HI_U32 size;
    void *src;
    Rect bounds(mWidth, mHeight);
    if (mFormat != HAL_PIXEL_FORMAT_YCrCb_420_SP)
    {
        ALOGE("Unsupported format:%d!", mFormat);
        return;
    }

    size = mWidth * mHeight * 3 / 2;

    if (mapper.lock(
                buf->handle, GRALLOC_USAGE_SW_WRITE_OFTEN, bounds, &src))
    {
        ALOGE("Lock graphic buffer failed");
        return;
    }

    static FILE* fp = NULL;
    if (!fp)
    {
        fp = fopen("/sdcard/VSinkDumped.yuv", "wb+");
    }
    if (fp)
    {
        if (fwrite(src, size, 1, fp) != size)
        {
            ALOGE("dump file error");
        }
        ALOGD("dump file success!");
    }

    if (mapper.unlock(buf->handle))
    {
        ALOGE("unlock buffer failed");
    }
}

void HiVSink::writeYUVFrame(ANativeWindowBuffer* buf, HI_U8* src, HI_U32 size)
{
    GraphicBufferMapper &mapper = GraphicBufferMapper::get();
    void *dst;
    Rect bounds(mWidth, mHeight);
    if (mFormat != HAL_PIXEL_FORMAT_YCrCb_420_SP)
    {
        ALOGE("Unsupported format:%d!", mFormat);
        return;
    }

    if (mapper.lock(
                buf->handle, GRALLOC_USAGE_SW_WRITE_OFTEN, bounds, &dst))
    {
        ALOGE("Lock graphic buffer failed");
        return;
    }
#if 0
    HI_U8* y_addr = (HI_U8*)dst;
    HI_U8* uv_addr = (HI_U8*)dst + mHeight * mWidth;
    int corp_width = mCrop.right - mCrop.left;
    int i;
    memset(dst, 0, size);
    /* fill Y */
    for (i = mCrop.top; i < mCrop.bottom; i++)
    {
        memcpy(y_addr + i * mWidth, src, corp_width);
        src += corp_width;
    }
    /* fill UV */
    for (i = mCrop.top; i < mCrop.bottom / 2; i++) //TODO bottom not correct
    {
        memcpy(uv_addr + i * mWidth, src, corp_width);
        src += corp_width;
    }
#else
    memcpy(dst, src, size);
#endif

    if (mapper.unlock(buf->handle))
    {
        ALOGE("unlock buffer failed");
    }
}
}; //namespace android
