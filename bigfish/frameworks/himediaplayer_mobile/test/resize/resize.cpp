/*
 * Copyright (C) 2010 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <cutils/memory.h>

#include <utils/Log.h>

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#include <gui/Surface.h>
#include <gui/SurfaceComposerClient.h>
#include <android/native_window.h>

using namespace android;

namespace android {


static inline int CurrentTime()
{
    struct timeval tv;
    gettimeofday(&tv,0);
    return (int)(tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

extern "C" int main(int argc, char** argv)
{
    // set up the thread-pool
    sp<ProcessState> proc(ProcessState::self());
    ProcessState::self()->startThreadPool();

    // create a client to surfaceflinger
    sp<SurfaceComposerClient> client = new SurfaceComposerClient();

    sp<SurfaceControl> surfaceControl = client->createSurface(String8("resize"),
            1920, 1080, PIXEL_FORMAT_RGB_565, 0);

    sp<Surface> surface = surfaceControl->getSurface();

    SurfaceComposerClient::openGlobalTransaction();
    surfaceControl->setLayer(100000);
    SurfaceComposerClient::closeGlobalTransaction();

    ANativeWindow_Buffer outBuffer;
    int time_start;
    while (1)
    {
        time_start = CurrentTime();
        surface->lock(&outBuffer, NULL);
        time_start = CurrentTime() - time_start;
        ALOGD("lock time:%d", time_start);
        ssize_t bpr = outBuffer.stride * bytesPerPixel(outBuffer.format);
        android_memset16((uint16_t*)outBuffer.bits, 0xF800, bpr*outBuffer.height);
        surface->unlockAndPost();

        time_start = CurrentTime();
        surface->lock(&outBuffer, NULL);
        time_start = CurrentTime() - time_start;
        ALOGD("lock time2:%d", time_start);
        android_memset16((uint16_t*)outBuffer.bits, 0x07E0, bpr*outBuffer.height);
        surface->unlockAndPost();
    }


    SurfaceComposerClient::openGlobalTransaction();
    surfaceControl->setSize(320, 240);
    SurfaceComposerClient::closeGlobalTransaction();


    IPCThreadState::self()->joinThreadPool();

    return 0;
}
}
