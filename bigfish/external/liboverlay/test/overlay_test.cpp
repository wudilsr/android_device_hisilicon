/*
 * overlay_test.cpp
 *
 *  Created on: 2014Äê8ÔÂ13ÈÕ
 *      Author: z00187490
 */

#include <ui/GraphicBuffer.h>
#include <ui/GraphicBufferMapper.h>
#include <ui/PixelFormat.h>
#include <utils/Vector.h>
#include <utils/KeyedVector.h>
#include <utils/Log.h>
#include <gralloc_priv.h>
#include <ui/Fence.h>
#include <utils/StopWatch.h>

#include "../overlay.h"

#define LOG_TAG "OverlayTest"
#define HI_SYS_GET_STRIDE(w)   ((((w)%256)==0)?(w):(((((w)/256)%2)==0)?((((w)/256)+1)*256):((((w)/256)+2)*256)))
#define    GRALLOC_USAGE_HISI_VDH0              (0x10000000)

using namespace android;

static FILE* s_file = NULL;

class OverlayDrive
{
public:
    OverlayDrive() {
        OverlayDrive(1920, 1080, 0, 0, 1920, 1080);
    }
    OverlayDrive(int w, int h, int dispX, int dispY, int dispW, int dispH) :
        mDev(0), mWidth(w), mHeight(h),
        mFmt(HAL_PIXEL_FORMAT_YCrCb_420_SP), mUsage(GRALLOC_USAGE_HISI_VDH0),
        mDispX(dispX), mDispY(dispY), mDispWidth(dispW), mDispHeight(dispH) {
        init();
    }
    ~OverlayDrive() {
        deinit();
    }
    int run() {
        const int cnt = 4;
        const int disp_cnt = 100;
        int i = 0;
        int j = 0;

        allocBuffer(cnt);

        for (i = 0; ; i++) {
            sp<GraphicBuffer>& buf = mBuffers.editItemAt(i % cnt);

            if (readBuffer(buf)) {
                ALOGE("read buffer failed");
                break;
            }
            if (setDispAttr(buf, mDispX, mDispY, mDispWidth, mDispHeight)) {
                ALOGE("set display attribute failed");
                return -1;
            }
            j = 0;
//            while (j++ < 2)
            {
                if (dispBuffer(buf)) {
                    ALOGE("display buffer failed");
                    return -1;
                }

//                usleep(16 * 1000);
            }

        }
        freeBuffer();
        if (mDev->prepareOverlayLayers(mDev, 0, NULL)) {
            ALOGE("prepare buffer failed");
            return -1;
        }
        return 0;
    }
private:
    int init() {
        return loadOverLayModule();
    }

    void deinit() {
        unloadOverLayModule();
    }

    int loadOverLayModule() {
        ALOGD("==============%s, %d", __func__, __LINE__);
//
//        hw_module_t const* module;
//
//        int err = hw_get_module(OVERLAY_HARDWARE_MODULE_ID, &module);
//        if (err != 0) {
//            ALOGE("20140416 %s module not found", OVERLAY_HARDWARE_MODULE_ID);
//            return err;
//        }
//
//        return overlay_open(module, &mDev);
        mDev = overlay_singleton();
        return 0;
    }

    void unloadOverLayModule() {
//        overlay_close(mDev);
    }

    int allocBuffer(int cnt) {
        for (int i = 0; i < cnt; i++) {
            sp<GraphicBuffer> buf = new GraphicBuffer(mWidth, mHeight, mFmt, mUsage);
            mBuffers.add(buf);
            mBufferFence.add(buf->handle, -1);
        }
        ALOGD("total %d buffer allocated", cnt);
        return 0;
    }

    int freeBuffer() {
        mBuffers.clear();
        mBufferFence.clear();
        ALOGD("Free all buffer done");
        return 0;
    }

    int readBuffer(sp<GraphicBuffer>& graphicBuffer) {
        StopWatch watch("readwatch");
        char *buf = NULL;
        int ret;
        int blockWidth = mWidth > 16 ? mWidth / 16 : 1;
        int blockHeight = mHeight > 16 ? mHeight / 16 : 1;
        const int yuvTexOffsetY = 0;
        const int yuvTexStrideY = graphicBuffer->stride;//(mWidth + 0xff) & ~0xff;
        const int yuvTexOffsetV = yuvTexStrideY * mHeight;
        const int yuvTexStrideV = yuvTexStrideY / 2;//HI_SYS_GET_STRIDE(yuvTexStrideY / 2);//(yuvTexStrideY/2 + 0xff) & ~0xff;
        const int yuvTexOffsetU = yuvTexOffsetV + yuvTexStrideV * mHeight/2;
        const int yuvTexStrideU = yuvTexStrideV;
        const bool yuvTexSameUV = false;
        int fenceFd = -1;

        fenceFd = mBufferFence.valueFor(graphicBuffer->handle);
        if (fenceFd != -1) {
            sp<Fence> fence = new Fence(fenceFd);
            fence->waitForever("wait befor write buffer");
            mBufferFence.replaceValueFor(graphicBuffer->handle, -1);
        }

        ret = graphicBuffer->lock(GRALLOC_USAGE_SW_WRITE_OFTEN, (void**)&buf);
        if (ret) {
            ALOGE("lock graphic buffer failed");
            return -1;
        }

    if (s_file) {
        ret = fread(buf, yuvTexStrideY * mHeight * 3/ 2, 1, s_file);
        if (ret == 0) {
            return -1;
        }
    } else {
        for (int x = 0; x < mWidth; x++) {
            for (int y = 0; y < mHeight; y++) {
                int parityX = (x / blockWidth) & 1;
                int parityY = (y / blockHeight) & 1;
                unsigned char intensity = (parityX ^ parityY) ? 63 : 191;
                buf[yuvTexOffsetY + (y * yuvTexStrideY) + x] = intensity;
                if (x < mWidth / 2 && y < mHeight / 2) {
                    buf[yuvTexOffsetU + (y * yuvTexStrideU) + x] = intensity;
                    if (yuvTexSameUV) {
                        buf[yuvTexOffsetV + (y * yuvTexStrideV) + x] = intensity;
                    } else if (x < mWidth / 4 && y < mHeight / 4) {
                        buf[yuvTexOffsetV + (y*2 * yuvTexStrideV) + x*2 + 0] =
                        buf[yuvTexOffsetV + (y*2 * yuvTexStrideV) + x*2 + 1] =
                        buf[yuvTexOffsetV + ((y*2+1) * yuvTexStrideV) + x*2 + 0] =
                        buf[yuvTexOffsetV + ((y*2+1) * yuvTexStrideV) + x*2 + 1] = intensity;
                    }
                }
            }
        }
    }
        ret = graphicBuffer->unlock();
        if (ret) {
            ALOGE("unlock graphic buffer failed");
            return -1;
        }
        return 0;
    }

    int dispBuffer(sp<GraphicBuffer>& buf) {
        int ret;
        int fenceFd = -1;
        buffer_handle_t handle;

        ANativeWindowBuffer* nativeWindowBuffer = buf->getNativeBuffer();
        handle = nativeWindowBuffer->handle;

        ret = mDev->queueBuffer(mDev, handle, &fenceFd);
        if (ret < 0) {
            ALOGE("queue graphic buffer failed");
            return -1;
        }

        if (fenceFd != -1) {
            mBufferFence.add(handle, fenceFd);
        }
        return 0;
    }

    int setDispAttr(sp<GraphicBuffer>& buf, int x, int y, int w, int h) {
        int ret;
        overlay_layer_t layers;
        overlay_rect_t displayFrame;
        buffer_handle_t handle = buf->handle;
        layers.handle = buf->handle;
        layers.visible = 1;
        displayFrame.left = x;
        displayFrame.top = y;
        displayFrame.right = x + w;
        displayFrame.bottom = y + h;

        if (mDev->prepareOverlayLayers(mDev, 1, &layers)) {
            ALOGE("prepare buffer failed");
            return -1;
        }

        mDev->setPosition(mDev, handle, displayFrame);

        return 0;
    }

    Vector< sp<GraphicBuffer> > mBuffers;
    KeyedVector<buffer_handle_t ,int> mBufferFence;
    struct overlay_device_t* mDev;
    int mWidth;
    int mHeight;
    int mFmt;
    int mUsage;
    int mDispX;
    int mDispY;
    int mDispWidth;
    int mDispHeight;
};
int main(int argc, char** argv)
{
    if (argc != 8) {
        printf("usage: test-overlay buffer_w, buffer_h, disp_x disp_y, disp_w, disp_h path.yuv\n");
        return -1;
    }
    int buffer_w = atoi(argv[1]);
    int buffer_h = atoi(argv[2]);
    int disp_x = atoi(argv[3]);
    int disp_y = atoi(argv[4]);
    int disp_w = atoi(argv[5]);
    int disp_h = atoi(argv[6]);

    s_file = fopen(argv[7], "rb+");
    if (!s_file) {
        printf("open file %s failed", argv[7]);
        return -1;
    }
    OverlayDrive ov(buffer_w, buffer_h, disp_x, disp_y, disp_w, disp_h);
    ov.run();
    return 0;
}
