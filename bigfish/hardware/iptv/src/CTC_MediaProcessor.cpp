/**
 * @file         iptv_player_jni.cpp
 * @author        zhouyj
 * @date          2012/9/5
 * @version       ver 1.0
 * @brief         定义CTC_MediaProcessor类中方法的jni接口，供上层调用。
 * @attention
 */

#define  LOG_TAG    "CTC_MediaControl"
#define DEBUG false
#include "CTC_MediaControl.h"
#include "vformat.h"
#include "aformat.h"
#include "Common.h"
#include "android_runtime/AndroidRuntime.h"
#include <gui/Surface.h>
#include "CTC_MediaProcessor.h"
using namespace android;



#include "android/log.h"
#include "jni.h"
#include "stdio.h"
#include <string.h>

#define BUFF_SIZE (32*1024)

Mutex    gMutexLock;

static FILE * g_TestResultLogHandle = NULL;

static FILE * GetTestResultLogHandle()
{
    if(g_TestResultLogHandle == NULL)
    {
        g_TestResultLogHandle = fopen("/data/data/com.ctc/mediaTestSuite.txt", "wb");
        if(g_TestResultLogHandle == NULL)
        {
            ALOGE("create file :error");
            return NULL;
        }
        else
        {
            char  writebuf[2000];
            unsigned int buflen = 2000;
            memset(writebuf,0,buflen);
            snprintf(writebuf,buflen,"%s\r\n%s\r\n","ctc_player test result:","*********************");
            writebuf[buflen -1] = 0;
            fwrite(writebuf,1,strlen(writebuf),g_TestResultLogHandle);
            fflush(g_TestResultLogHandle);
        }
    }


    return g_TestResultLogHandle;

}

#ifdef __cplusplus
extern "C" {
#endif

    CTC_MediaControl* ctc_MediaControl = GetMediaProcessor();
    FILE *fp;
    int isPause = 0;

    //将test结果输入文件
    void Java_com_ctc_MediaProcessorDemoActivity_nativeWriteFile(JNIEnv* env, jobject thiz, jstring Function, jstring Return, jstring Result)
    {
        FILE *result_fp = GetTestResultLogHandle();

        if(result_fp == NULL)
        {
            ALOGE("create file :error");
            return;
        }
        const char* Function_t = (*env).GetStringUTFChars(Function, NULL);
        const char* Return_t = (*env).GetStringUTFChars(Return, NULL);
        const char* Result_t = (*env).GetStringUTFChars(Result, NULL);
        char divide_str[] = "*********************";
        char  writebuf[2000];
        unsigned int buflen = 2000;
        memset(writebuf,0,buflen);
        snprintf(writebuf,buflen,"%s\r\n%s\r\n%s\r\n%s\r\n",Function_t, Return_t, Result_t, divide_str);
        writebuf[buflen -1] = 0;
        fwrite(writebuf,1,strlen(writebuf),result_fp);
        fflush(result_fp);
        return;
    }

    //从java层获取surface
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeCreateSurface(JNIEnv* env, jobject thiz, jobject pSurface, int w, int h)
    {
        if(DEBUG) ALOGI("get the surface");
        if(DEBUG) ALOGI("success: get surface");
        if(DEBUG) ALOGI("success: set surface ");

        return 0;
    }

    //设置EPG大小
    void Java_com_ctc_MediaProcessorDemoActivity_nativeSetEPGSize(JNIEnv* env, jobject thiz, int w, int h)
    {
        ctc_MediaControl->SetEPGSize(w, h);
        return;
    }

    //根据音视频参数初始化播放器
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeInit(JNIEnv* env, jobject thiz)
    {
        VIDEO_PARA_T  videoPara;
        videoPara.pid = 101;
        videoPara.nVideoWidth = 544;
        videoPara.nVideoHeight = 576;
        videoPara.nFrameRate = 25;
        videoPara.vFmt = VFORMAT_H264;
        videoPara.cFmt = 0;

        AUDIO_PARA_T audioPara[2];
        audioPara[0].pid = 144;
        audioPara[0].nChannels = 1;
        audioPara[0].nSampleRate = 48000;
        audioPara[0].aFmt = FORMAT_HI_MPEG;
        audioPara[0].nExtraSize = 0;
        audioPara[0].pExtraData = NULL;

        audioPara[1].pid = 0;

        ctc_MediaControl->InitVideo(&videoPara);
        ctc_MediaControl->InitAudio(&audioPara[0]);
        return 0;
    }

    //开始播放
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeStartPlay(JNIEnv* env, jobject thiz)
    {
        jboolean result = ctc_MediaControl->StartPlay();
        return result;
    }

    //写入数据播放
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeWriteData(JNIEnv* env, jobject thiz, jstring url)
    {
        const char* URL = (*env).GetStringUTFChars(url, NULL);

        int rd_result = 0;
        fp = fopen(URL, "rb+");
        if (fp == NULL)
        {
            ALOGE("open file:error!");
            return -1;
        }

        char* buffer = (char* )malloc(BUFF_SIZE);

        while(true)
        {
            {
                Mutex::Autolock l(gMutexLock);
                rd_result = fread(buffer, BUFF_SIZE, 1, fp);
                if (rd_result <= 0)
                {
                    ALOGE("read the end of file");
                    exit(1);
                }

                int wd_result = ctc_MediaControl->WriteData((unsigned char*) buffer, (unsigned int) BUFF_SIZE);
                if(DEBUG) ALOGI("the wd_result[%d]", wd_result);
            }

            usleep(130*1000);
        }

        free(buffer);

        return 0;
    }


    //取得播放模式
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeGetPlayMode(JNIEnv* env, jobject thiz)
    {
        int result = ctc_MediaControl->GetPlayMode();
        if(DEBUG) ALOGI("step:1");

        return (jint)result;
    }

    //设置播放区域的位置和播放区域的宽高
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeSetVideoWindow(JNIEnv* env, jobject thiz ,jint x, jint y, jint width, jint height)
    {
        int result = ctc_MediaControl->SetVideoWindow(x, y, width, height);
        if(DEBUG) ALOGI("SetVideoWindow result:[%d]", result);
        return result;
    }

    //播放器暂停
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativePause(JNIEnv* env, jobject thiz)
    {
        if(DEBUG) ALOGI("NEXT:Pause");
        isPause = 1;
        jboolean result = ctc_MediaControl->Pause();
        return result;
    }
    //播放器继续播放
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeResume(JNIEnv* env, jobject thiz)
    {
        if(DEBUG) ALOGI("NEXT:Resume");
        isPause = 0;
        jboolean result = ctc_MediaControl->Resume();
        return result;
    }

    //播放器选时
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeSeek(JNIEnv* env, jobject thiz)
    {
        if(DEBUG) ALOGI("nativeSeek---0");
        Mutex::Autolock l(gMutexLock);
        if(DEBUG) ALOGI("nativeSeek---1");
        fseek(fp, 0, 0);
        if(DEBUG) ALOGI("nativeSeek---2");
        jboolean result = ctc_MediaControl->Seek();
        if(DEBUG) ALOGI("nativeSeek---3");
        return result;
    }

    //显示视频
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeVideoShow(JNIEnv* env, jobject thiz)
    {
        jint result = ctc_MediaControl->VideoShow();
        return result;
    }

    //隐藏视频
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeVideoHide(JNIEnv* env, jobject thiz)
    {
        jint result = ctc_MediaControl->VideoHide();
        return result;
    }

    //快进快退
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeFast(JNIEnv* env, jobject thiz)
    {
        jboolean result = ctc_MediaControl->Fast();
        return result;
    }

    //停止快进快退
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeStopFast(JNIEnv* env, jobject thiz)
    {
        jboolean result = ctc_MediaControl->StopFast();
        return result;
    }

    //停止播放
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeStop(JNIEnv* env, jobject thiz)
    {
        jboolean result = ctc_MediaControl->Stop();

        return result;
    }

    //获取音量
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeGetVolume(JNIEnv* env, jobject thiz)
    {
        jint result = ctc_MediaControl->GetVolume();
        if(DEBUG) ALOGI("the volume is [%d]",result);
        return result;
    }

    //设定音量
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeSetVolume(JNIEnv* env, jobject thiz,jint volume)
    {
        jboolean result = ctc_MediaControl->SetVolume(volume);
        return result;
    }

    //设定视频显示比例
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeSetRatio(JNIEnv* env, jobject thiz,jint nRatio)
    {
        jboolean result = ctc_MediaControl->SetRatio(nRatio);
        return result;
    }

    //获取当前声道
    jint Java_com_ctc_MediaProcessorDemoActivity_nativeGetAudioBalance(JNIEnv* env, jobject thiz)
    {
        jint result = ctc_MediaControl->GetAudioBalance();
        return result;
    }

    //设置声道
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeSetAudioBalance(JNIEnv* env, jobject thiz, jint nAudioBalance)
    {
        jboolean result = ctc_MediaControl->SetAudioBalance(nAudioBalance);
        return result;
    }

    //获取视频分辨率
    void Java_com_ctc_MediaProcessorDemoActivity_nativeGetVideoPixels(JNIEnv* env, jobject thiz)
    {
        int width;
        int height;
        if(DEBUG) ALOGI("the video prixels ");
        ctc_MediaControl->GetVideoPixels(width, height);
        if(DEBUG) ALOGI("the video prixels :[%d]*[%d]",width, height);
        return;
    }

    //获取是否由软件拉伸，如果由硬件拉伸，返回false
    jboolean Java_com_ctc_MediaProcessorDemoActivity_nativeIsSoftFit(JNIEnv* env, jobject thiz)
    {
        jboolean result = ctc_MediaControl->IsSoftFit();
        return result;
    }

#ifdef __cplusplus
}
#endif
