/*
 * HiMediaPlayerTest.cpp
 *
 *  Created on: 2014Äê4ÔÂ26ÈÕ
 *      Author: z00187490
 */


//#include <gtest/gtest.h>
#include <utils/Log.h>

#include <binder/IMemory.h>
#include <gui/ISurfaceComposer.h>
#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <gui/BufferItemConsumer.h>
#include <utils/String8.h>

#include <private/gui/ComposerService.h>
#include <binder/ProcessState.h>
#include <HiMediaPlayer.h>

#define ASSERT_EQ(a, b) if((a) != (b)) {\
    ALOGE("Error at [%s,%d]", __FUNCTION__, __LINE__);\
    exit(-1);\
}
#define ASSERT_TRUE(a) ASSERT_EQ((a), 1)
#define LOG_TAG "HimediaPlayerTest"

namespace android {

class HiMediaPlayerTest
{
public:
    HiMediaPlayerTest() {
        ProcessState::self()->startThreadPool();
        SetUp();
    }
    int run(const char* url);
    int mainloop();
    ~HiMediaPlayerTest() {
        TearDown();
    }
    static void notify_callback(void* cookie, int msg, int ext1, int ext2, const Parcel *obj);

private:
    void SetUp() {
        mComposerClient = new SurfaceComposerClient;
        ASSERT_EQ(NO_ERROR, mComposerClient->initCheck());

        mSurfaceControl = mComposerClient->createSurface(
                String8("Test Surface"), 1280, 720, PIXEL_FORMAT_RGB_565, 0);

        ASSERT_TRUE(mSurfaceControl != NULL);
        ASSERT_TRUE(mSurfaceControl->isValid());

        SurfaceComposerClient::openGlobalTransaction();
        ASSERT_EQ(NO_ERROR, mSurfaceControl->setLayer(0x7fffffff));
        ASSERT_EQ(NO_ERROR, mSurfaceControl->show());
        ASSERT_EQ(NO_ERROR, mSurfaceControl->setFlags(0x00000020, 0xffffffff));
        SurfaceComposerClient::closeGlobalTransaction();

        mSurface = mSurfaceControl->getSurface();
        ASSERT_TRUE(mSurface != NULL);
        ALOGD("Setup Himediaplayer test done!");
    }
    void TearDown() {
        mComposerClient->dispose();
    }

    sp<Surface> mSurface;
    sp<SurfaceComposerClient> mComposerClient;
    sp<SurfaceControl> mSurfaceControl;
    HiMediaPlayer* mPlayer;
};
void HiMediaPlayerTest::notify_callback(void* cookie, int msg, int ext1, int ext2, const Parcel *obj)
{
    switch (msg)
    {
    case android::MEDIA_PLAYBACK_COMPLETE:
        ALOGD("MEDIA_PLAYBACK_COMPLETE received, exit");
        fputs("q\n", stdin);
        break;
    default:
        ALOGD("event %d recevied, ext1:%d, ext2:%d", msg, ext1, ext2);
        break;
    }
}

int HiMediaPlayerTest::run(const char* url)
{
    ALOGD("play url:%s", url);

    mPlayer = new HiMediaPlayer();

    ASSERT_TRUE(mPlayer->initCheck() == OK);
    mPlayer->setNotifyCallback(this, notify_callback);
    ASSERT_TRUE(OK == mPlayer->setSurfaceTexture(mSurface->getIGraphicBufferProducer()));
    ASSERT_TRUE(OK == mPlayer->setDataSource(url, 0));
    ASSERT_TRUE(mPlayer->prepare() == OK);
    ASSERT_TRUE(mPlayer->start() == OK);

    mainloop();

    ASSERT_TRUE(mPlayer->stop() == OK);
    ASSERT_TRUE(mPlayer->reset() == OK);
    delete mPlayer;
    return 0;
}

int HiMediaPlayerTest::mainloop()
{
    char* c;
    char input_buf[1024];
    memset(input_buf, 0, sizeof(input_buf));

    for (;;)
    {
        c = fgets(input_buf, sizeof(input_buf), stdin);
        if (!c) {
            continue;
        }
        else if (c[0] == 'q') {
            /*quit play*/
            ALOGD("quit playback");
            break;
        }
        else if (c[0] == 's')
        {
            /*seeking*/
            c++;
            while(*c == ' ')
                c++;
            int seek_time = atoi(c);
            ALOGD("going to seek to %dms", seek_time);
            mPlayer->seekTo(seek_time);
        }
    }
    return 0;
}

extern "C" int main(int argc, char* argv[]) {
    HiMediaPlayerTest mpt;
    if (argc != 2)
    {
        printf("usage: test-himediaplayer url");
        return -1;
    }
    return mpt.run(argv[1]);
}
} /*namespace android*/
