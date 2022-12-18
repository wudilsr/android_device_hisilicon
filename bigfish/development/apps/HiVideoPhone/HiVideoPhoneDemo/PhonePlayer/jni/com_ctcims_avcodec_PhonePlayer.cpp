#define LOG_NDEBUG 0

#include "utils/Log.h"

#include <stdio.h>
#include <assert.h>
#include <limits.h>
#include <unistd.h>
#include <fcntl.h>
#include <utils/threads.h>
#include <cutils/properties.h>
#include "jni.h"
#include <utils/Log.h>
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>
#include "utils/Errors.h"  // for status_t
#include "utils/KeyedVector.h"
#include "utils/String8.h"
#include <binder/Parcel.h>
#include "vp_adpt.h"

// ----------------------------------------------------------------------------

using namespace android;

// ----------------------------------------------------------------------------
struct fields_t {
    jfieldID    context;
};
static fields_t fields;

static jint com_ctcims_avcodec_PhonePlayer_AVInit(JNIEnv *env, jobject clazz)
{
	jint ret = 0;

	ret = Hi_Adp_Video_Init();
	ret |= Hi_Adp_Audio_Init();

	return ret;
}

static jint com_ctcims_avcodec_PhonePlayer_AVDeinit(JNIEnv *env, jobject clazz)
{
	jint ret = 0;

	ret = Hi_Adp_Video_Deinit();
	Hi_Adp_Audio_Deinit();

	return ret;
}

static jint com_ctcims_avcodec_PhonePlayer_setPacketCheckSpan(JNIEnv *env, jobject clazz, jint checkspan)
{
	jint ret = 0;

	ret = Hi_Adp_Video_SetCheckSpan(checkspan);
	ret |= Hi_Adp_Audio_SetCheckSpan(checkspan);

	return ret;
}

static jint com_ctcims_avcodec_PhonePlayer_checkPacket(JNIEnv *env, jobject clazz, jint audioorvideo)
{
	
	if (0 == audioorvideo) //audio
	{
		return Hi_Adp_Audio_CheckPacket();
	}
	else if (1 == audioorvideo) //video
	{
		return Hi_Adp_Video_CheckPacket();
	}
	else
	{
		return -1;
	}
}

static jdouble com_ctcims_avcodec_PhonePlayer_getStatics(JNIEnv *env, jobject clazz, jstring item)
{
	const char *Staticitem;
	HI_ADP_STATICS_E enVideoStatic;

    Staticitem = (char*)env->GetStringUTFChars(item,NULL);

	if (0 == strncmp(Staticitem, "PACKET_INRATE", sizeof("PACKET_INRATE")))
	{
		enVideoStatic = PACKET_INRATE;
	}
	else if (0 == strncmp(Staticitem, "PACKET_OUTRATE", sizeof("PACKET_OUTRATE")))
	{
		enVideoStatic = PACKET_OUTRATE;
	}
	else if (0 == strncmp(Staticitem, "PACKET_INLOSTRATE", sizeof("PACKET_INLOSTRATE")))
	{
		enVideoStatic = PACKET_INLOSTRATE;
	}
	else if (0 == strncmp(Staticitem, "PACKET_INDELAYTIME", sizeof("PACKET_INDELAYTIME")))
	{
		enVideoStatic = PACKET_INDELAYTIME;
	}
	else if (0 == strncmp(Staticitem, "VIDEO_WIDTH", sizeof("VIDEO_WIDTH")))
	{
		enVideoStatic = VIDEO_WIDTH;
	}
	else if (0 == strncmp(Staticitem, "VIDEO_HEIGHT", sizeof("VIDEO_HEIGHT")))
	{
		enVideoStatic = VIDEO_HEIGHT;
	}
	else
	{
		return -1;
	}

	return Hi_Adp_Video_GetVideoStatics(enVideoStatic);
}

static jint com_ctcims_avcodec_PhonePlayer_initVideo(JNIEnv *env, jobject clazz, jint resolution,
                                        jint inX, jint inY, jint inWidth, jint inHeight,
                                        jint outX, jint outY, jint outWidth, jint outHeight,
                                        jint displayInit, jint localFramerate)
{
    HI_RECT_S stLocalWinRect;
    HI_RECT_S stRemotewinRect;
    HI_ADP_RESOLUTION_E eSetRes;
	
	stLocalWinRect.s32X = inX ;
	stLocalWinRect.s32Y  = inY;
	stLocalWinRect.s32Height = inHeight;
    stLocalWinRect.s32Width = inWidth;

	stRemotewinRect.s32X = outX ;
	stRemotewinRect.s32Y  = outY;
	stRemotewinRect.s32Height = outHeight;
	stRemotewinRect.s32Width = outWidth;

    eSetRes = (HI_ADP_RESOLUTION_E)resolution;
	//eSetRes = HI_RESOLUTION_1920_1080;
    return Hi_Adp_Video_Open(stLocalWinRect,stRemotewinRect,eSetRes,displayInit,localFramerate);
}

static jint com_ctcims_avcodec_PhonePlayer_videoStart(JNIEnv *env, jobject clazz, jstring localIp,
										jint localPort, jstring remoteIp, jint remotePort,
										jint frmRate, jint payload, jint vbrrate, jint gop)
{
    const char * plocalip, *premoteip;
    plocalip = env->GetStringUTFChars(localIp,NULL);
    premoteip = env->GetStringUTFChars(remoteIp,NULL);
    return Hi_Adp_Video_Start(plocalip,localPort,premoteip,remotePort,frmRate,payload,vbrrate,gop);
}

static jint com_ctcims_avcodec_PhonePlayer_videoStop(JNIEnv *env, jobject clazz)
{
    return Hi_Adp_Video_Stop();
}

static jint com_ctcims_avcodec_PhonePlayer_deInitVideo(JNIEnv *env, jobject clazz)
{
	return Hi_Adp_Video_Close();
}

static jint com_ctcims_avcodec_PhonePlayer_disableLocalVideo(JNIEnv *env, jobject clazz)
{
    return Hi_Adp_Video_EnableLocal(HI_FALSE);
}

static jint com_ctcims_avcodec_PhonePlayer_enableLocalVideo(JNIEnv *env, jobject clazz)
{
    return Hi_Adp_Video_EnableLocal(HI_TRUE);
}

static jint com_ctcims_avcodec_PhonePlayer_disableRemoteVideo(JNIEnv *env, jobject clazz)
{
    return Hi_Adp_Video_EnableRemote(HI_FALSE);
}

static jint com_ctcims_avcodec_PhonePlayer_enableRemoteVideo(JNIEnv *env, jobject clazz)
{
    return Hi_Adp_Video_EnableRemote(HI_TRUE);
}

static jint com_ctcims_avcodec_PhonePlayer_showWindow(JNIEnv *env, jobject clazz, jint window, jint showorhide)
{
	return Hi_Adp_Video_SetWindowShow(window, showorhide);
}

static jint com_ctcims_avcodec_PhonePlayer_setWindowZorder(JNIEnv *env, jobject clazz, jint window, jint zorder)
{
    return Hi_Adp_Video_SetWindowZorder(window,zorder);
}

static jint com_ctcims_avcodec_PhonePlayer_moveWindow(JNIEnv *env, jobject clazz, jint window, jint destx,
															jint desty, jint destWidth, jint height)
{
    return Hi_Adp_Video_SetWindowPos(window,destx,desty,destWidth,height);
}

static jint com_ctcims_avcodec_PhonePlayer_GetOptionalConfig(JNIEnv *env, jobject clazz, jint optionaltype)
{
    return Hi_Adp_Video_GetOptionalConfig(optionaltype);
}

static jint com_ctcims_avcodec_PhonePlayer_SetOptionalConfig(JNIEnv *env, jobject clazz, jint optionaltype, jint value)
{
    return Hi_Adp_Video_SetOptionalConfig(optionaltype, value);
}

static jint com_ctcims_avcodec_PhonePlayer_initAudio(JNIEnv *env, jobject clazz)
{
    HI_AUD_DEV_INFO_S stAudInDevList,stAudOutDevList;
    Hi_Adp_Audio_GetAudDevList(&stAudInDevList, &stAudOutDevList);
    return Hi_Adp_Audio_Open(AUD_DEV_DEF_INDEV_NUM, AUD_DEV_DEF_OUTDEV_NUM);
}

static jint com_ctcims_avcodec_PhonePlayer_deInitAudio(JNIEnv *env, jobject clazz)
{
    return Hi_Adp_Audio_Close();;
}

static jint com_ctcims_avcodec_PhonePlayer_audioStart(JNIEnv *env, jobject clazz, jstring localip,
								jint localport, jstring remoteip, jint remoteport)
{
	const char * plocalip, *premoteip;
    plocalip = env->GetStringUTFChars(localip,NULL);
    premoteip = env->GetStringUTFChars(remoteip,NULL);

    return Hi_Adp_Audio_Start(plocalip, (HI_U32)localport, premoteip, (HI_U32)remoteport);
}

static jint com_ctcims_avcodec_PhonePlayer_audioStop(JNIEnv *env, jobject clazz)
{

    return Hi_Adp_Audio_Stop();
}

static jint com_ctcims_avcodec_PhonePlayer_setAudioCodec(JNIEnv *env, jobject clazz, jstring codecname,
												jint codecnumber, jint samlerate, jint samplesize,
												jint framerate, jint framesize, jint channelcount)
{
    return 0;
}

static jint com_ctcims_avcodec_PhonePlayer_setAudioParam(JNIEnv *env, jobject clazz,
														jstring paramname, jstring paramvalue)
{
	const char *DeviceName, *Gain;
	int DeviceDirection;

	DeviceName = (char*)env->GetStringUTFChars(paramname,NULL);
	Gain = (char*)env->GetStringUTFChars(paramvalue, NULL);

	if (0 == strncmp(DeviceName, "eargain", sizeof("eargain")))
	{
		DeviceDirection = AUD_DEV_PLAYBACK_DIRECTION;
	}
	else if (0 == strncmp(DeviceName, "micgain", sizeof("micgain")))
	{
		DeviceDirection = AUD_DEV_CAPTURE_DIRECTION;
	}
	else if (0 == strncmp(DeviceName, "heargain", sizeof("heargain")))
	{
		DeviceDirection = AUD_DEV_PLAYBACK_DIRECTION;
	}
	else if (0 == strncmp(DeviceName, "hmicgain", sizeof("hmicgain")))
	{
		DeviceDirection = AUD_DEV_CAPTURE_DIRECTION;
	}
	else
	{
		return -1;
	}

		
    return Hi_Adp_Audio_SetGain(DeviceDirection, atoi(Gain));
}

static jint com_ctcims_avcodec_PhonePlayer_setVolume(JNIEnv *env, jobject clazz, jint stream, jint volume)
{
	int Device;

	switch (stream)
	{
		case 0:			//
			Device = AUD_DEV_PLAYBACK_DIRECTION;
			break;
		case 1:			//MIC
			Device = AUD_DEV_CAPTURE_DIRECTION;
			break;
		case 2:			//earphone
			Device = AUD_DEV_PLAYBACK_DIRECTION;
			break;
		default:
			return -1;
	}
	return Hi_Adp_Audio_SetVolume(Device, volume);
}

static jint com_ctcims_avcodec_PhonePlayer_getVolume(JNIEnv *env, jobject clazz, jint stream)
{
    return 0;
}

static jint com_ctcims_avcodec_PhonePlayer_mute(JNIEnv *env, jobject clazz, jint stream)
{
    return Hi_Adp_Audio_SetMute(stream);
}

static jint com_ctcims_avcodec_PhonePlayer_unmute(JNIEnv *env, jobject clazz, jint stream)
{
    return Hi_Adp_Audio_SetUnMute(stream);
}

static jint com_ctcims_avcodec_PhonePlayer_enableAEC(JNIEnv *env, jobject clazz, jint enable)
{
    return Hi_Adp_Audio_EnableAEC(enable);
}

static jint com_ctcims_avcodec_PhonePlayer_enableANS(JNIEnv *env, jobject clazz, jint enable)
{
    return Hi_Adp_Audio_EnableANS(enable);
}

static jint com_ctcims_avcodec_PhonePlayer_enableAGC(JNIEnv *env, jobject clazz, jint enable)
{
    return Hi_Adp_Audio_EnableAGC(enable);
}

static jint com_ctcims_avcodec_PhonePlayer_enableVAD(JNIEnv *env, jobject clazz, jint enable)
{
    return Hi_Adp_Audio_EnableVAD(enable);
}

static jint com_ctcims_avcodec_PhonePlayer_sendDTMF(JNIEnv *env, jobject clazz, jint type,
															jint payloadtype, jchar dtmf)
{
    return 0;
}

static JNINativeMethod gMethods[] = {
    {"AVInit", "()I", (void *)com_ctcims_avcodec_PhonePlayer_AVInit},
	{"AVDeinit", "()I", (void *)com_ctcims_avcodec_PhonePlayer_AVDeinit},
	{"setPacketCheckSpan", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_setPacketCheckSpan},
	{"checkPacket", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_checkPacket},
	{"getStatics", "(Ljava/lang/String;)D", (void *)com_ctcims_avcodec_PhonePlayer_getStatics},
	{"initVideo", "(IIIIIIIIIII)I", (void *)com_ctcims_avcodec_PhonePlayer_initVideo},
	{"videoStart", "(Ljava/lang/String;ILjava/lang/String;IIIII)I", (void *)com_ctcims_avcodec_PhonePlayer_videoStart},
	{"videoStop", "()I", (void *)com_ctcims_avcodec_PhonePlayer_videoStop},
	{"deInitVideo", "()I", (void *)com_ctcims_avcodec_PhonePlayer_deInitVideo},
	{"disableLocalVideo", "()I", (void *)com_ctcims_avcodec_PhonePlayer_disableLocalVideo},
	{"enableLocalVideo", "()I", (void *)com_ctcims_avcodec_PhonePlayer_enableLocalVideo},
	{"disableRemoteVideo", "()I", (void *)com_ctcims_avcodec_PhonePlayer_disableRemoteVideo},
	{"enableRemoteVideo", "()I", (void *)com_ctcims_avcodec_PhonePlayer_enableRemoteVideo},
	{"showWindow", "(II)I", (void *)com_ctcims_avcodec_PhonePlayer_showWindow},
	{"setWindowZorder", "(II)I", (void *)com_ctcims_avcodec_PhonePlayer_setWindowZorder},
	{"moveWindow", "(IIIII)I", (void *)com_ctcims_avcodec_PhonePlayer_moveWindow},
	{"getOptionalConfig", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_GetOptionalConfig},
	{"setOptionalConfig", "(II)I", (void *)com_ctcims_avcodec_PhonePlayer_SetOptionalConfig},	
	{"initAudio", "()I", (void *)com_ctcims_avcodec_PhonePlayer_initAudio},
	{"deInitAudio", "()I", (void *)com_ctcims_avcodec_PhonePlayer_deInitAudio},
	{"audioStart", "(Ljava/lang/String;ILjava/lang/String;I)I", (void *)com_ctcims_avcodec_PhonePlayer_audioStart},
	{"audioStop", "()I", (void *)com_ctcims_avcodec_PhonePlayer_audioStop},
	{"setAudioCodec", "(Ljava/lang/String;IIIIII)I", (void *)com_ctcims_avcodec_PhonePlayer_setAudioCodec},
	{"setAudioParam", "(Ljava/lang/String;Ljava/lang/String;)I", (void *)com_ctcims_avcodec_PhonePlayer_setAudioParam},
	{"setVolume", "(II)I", (void *)com_ctcims_avcodec_PhonePlayer_setVolume},
	{"getVolume", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_getVolume},
	{"mute", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_mute},
	{"unmute", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_unmute},
	{"enableAEC", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_enableAEC},
	{"enableANS", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_enableANS},
	{"enableAGC", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_enableAGC},
	{"enableVAD", "(I)I", (void *)com_ctcims_avcodec_PhonePlayer_enableVAD},
	{"sendDTMF", "(IIC)I", (void *)com_ctcims_avcodec_PhonePlayer_sendDTMF},
};

static int register_com_ctcims_avcodec_PhonePlayer(JNIEnv *env)
{
	jclass clazz;
    clazz = env->FindClass("com/ctcims/avcodec/PhonePlayer");
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, gMethods, NELEM(gMethods)) < 0)
        return JNI_FALSE;
    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;
	if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK) {
    	return result;
  	}

  	if(register_com_ctcims_avcodec_PhonePlayer(env) < 0) {
    	return result;
  	}

  	/* success -- return valid version number */
  	result = JNI_VERSION_1_4;
  	return result;
}
