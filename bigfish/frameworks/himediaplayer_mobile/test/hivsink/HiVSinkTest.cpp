/*
 * HiVSinkTest.cpp
 *
 *  Created on: 2014Äê4ÔÂ24ÈÕ
 *      Author: z00187490
 */
#include <stdlib.h>
#include <gtest/gtest.h>
#include <utils/Log.h>

#include <binder/IMemory.h>
#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <gui/BufferItemConsumer.h>
#include <utils/String8.h>

#include <private/gui/ComposerService.h>
#include <binder/ProcessState.h>
#include <HiVSink.h>

#define LOG_TAG "HiVSinkTest"

namespace android {

static inline int CurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,0);
    return (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

class HiVSinkTest : public ::testing::Test {
protected:
    HiVSinkTest() : mWidth(kWidth), mHeight(kHeight){
        ProcessState::self()->startThreadPool();
    }

    virtual void SetUp() {
        mComposerClient = new SurfaceComposerClient;
        ASSERT_EQ(NO_ERROR, mComposerClient->initCheck());

        mSurfaceControl = mComposerClient->createSurface(
                String8("Test Surface"), kWidth, kHeight, PIXEL_FORMAT_RGB_565, 0x00000020);

        ASSERT_TRUE(mSurfaceControl != NULL);
        ASSERT_TRUE(mSurfaceControl->isValid());

        SurfaceComposerClient::openGlobalTransaction();
        ASSERT_EQ(NO_ERROR, mSurfaceControl->setLayer(0x7fffffff));
        ASSERT_EQ(NO_ERROR, mSurfaceControl->show());
        SurfaceComposerClient::closeGlobalTransaction();

        mSurface = mSurfaceControl->getSurface();
        ASSERT_TRUE(mSurface != NULL);
    }
    virtual void TearDown() {
        mComposerClient->dispose();
    }

    sp<Surface> mSurface;
    sp<SurfaceComposerClient> mComposerClient;
    sp<SurfaceControl> mSurfaceControl;
    int mWidth;
    int mHeight;
    static const int kWidth = 480;
    static const int kHeight = 320;
};

TEST_F(HiVSinkTest, DequeueToQueue) {

    HI_S32 ret;
    HI_U32 i;
    HI_U32 cnt = 6;
    int pic_size = mWidth * mHeight * 3 / 2;
    HI_SVR_PICTURE_S aPics[cnt];
    HI_U32 aPicList[cnt];
    HI_U8 pic_data[pic_size];
    sp<HiVSink> sink = new HiVSink(mSurface);
    HI_SVR_VSINK_S* pstVsink = sink.get();

    memset(aPics, 0, sizeof(aPics));
    memset(pic_data, 0, sizeof(pic_data));

    ret = HI_SVR_VSINK_SetDimensions(pstVsink, kWidth, kHeight);
    EXPECT_EQ(HI_SUCCESS, ret);

    ret = HI_SVR_VSINK_SetPictCnt(pstVsink, cnt);
    EXPECT_EQ(HI_SUCCESS, ret);

    ret = HI_SVR_VSINK_SetCrop(pstVsink, 0, 0, kWidth, kHeight);
    EXPECT_EQ(HI_SUCCESS, ret);

    FILE* file = fopen("/sdcard/VSinkDumped.yuv", "r");
    ASSERT_TRUE(file != NULL);
    for (i = 0; i < cnt; i++)
    {
        ret = HI_SVR_VSINK_Dequeue(pstVsink, aPics + i, 1);
        EXPECT_EQ(HI_SUCCESS, ret);

        aPicList[i] = 1;
    }

    /**
     * keep at least one frame in vsink
     */
    do {
        i = rand() % cnt;
    } while (aPicList[i] == 0);

    ret = fread(pic_data, sizeof(pic_data), 1, file);
    EXPECT_EQ (ret, 1);

    ret = HI_SVR_VSINK_WritePicture(pstVsink, aPics + i, pic_data, sizeof(pic_data));
    EXPECT_EQ(HI_SUCCESS, ret);

    ret = HI_SVR_VSINK_Queue(pstVsink, aPics + i);
    EXPECT_EQ(HI_SUCCESS, ret);
    aPicList[i] = 0;

    int time;

    while (1)
    {
        ret = fread(pic_data, sizeof(pic_data), 1, file);
        if (ret != 1)
        {
            rewind(file);
            continue;
//            break;
        }

        do {
            i = rand() % cnt;
        } while (aPicList[i] == 0);

        time = CurrentTime();
        ret = HI_SVR_VSINK_WritePicture(pstVsink, aPics + i, pic_data, sizeof(pic_data));
        EXPECT_EQ(HI_SUCCESS, ret);

        ret = HI_SVR_VSINK_Queue(pstVsink, aPics + i);
        EXPECT_EQ(HI_SUCCESS, ret);
        time = CurrentTime() - time;
        ALOGD("queue handle %d index:%d using time:%d", aPics[i].hBuffer, i, time);
        aPicList[i] = 0;

        time = CurrentTime();
        ret = HI_SVR_VSINK_Dequeue(pstVsink, aPics + i, 1);
        EXPECT_EQ(HI_SUCCESS, ret);
        time = CurrentTime() - time;
        ALOGD("dequeue handle %d using time:%d", aPics[i].hBuffer, time);

        aPicList[i] = 1;
    }
    fclose(file);
}

TEST_F(HiVSinkTest, DequeueToCancel) {

    HI_S32 ret;
    HI_U32 w = 1920;
    HI_U32 h = 1080;
    HI_U32 cnt = 6;
    HI_SVR_PICTURE_S aPics[cnt];
    sp<HiVSink> sink = new HiVSink(mSurface);
    HI_SVR_VSINK_S* pstVsink = sink.get();

    memset(aPics, 0, sizeof(aPics));
    ret = HI_SVR_VSINK_SetDimensions(pstVsink, w, h);
    EXPECT_EQ(HI_SUCCESS, ret);

    ret = HI_SVR_VSINK_SetPictCnt(pstVsink, cnt);
    EXPECT_EQ(HI_SUCCESS, ret);

    ret = HI_SVR_VSINK_Dequeue(pstVsink, aPics, cnt);
    EXPECT_EQ(HI_SUCCESS, ret);

    ret = HI_SVR_VSINK_Cancel(pstVsink, aPics, cnt);
    EXPECT_EQ(HI_SUCCESS, ret);
}
} /*namespace android*/
