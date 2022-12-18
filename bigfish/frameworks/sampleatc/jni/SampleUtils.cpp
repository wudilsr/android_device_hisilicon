#include <string.h>
#include <android/log.h>
#include <jni.h>
#include "hdmi_test_cmd.h"
#include "hi_unf_hdmi.h"
#include "hi_unf_disp.h"

#include <sys/types.h>
#include <fcntl.h>
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>

JNIEnv* jniEnv;

static jint com_sample_atc_utils_SampleUtils_hdmiInit(JNIEnv* env){
    int Ret = -1;
    Ret = HI_SYS_Init();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_SYS_Init failed.\n");
        return Ret;
    }
    Ret = HI_UNF_DISP_Init();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_DISP_Init failed.\n");
        return Ret;
    }
    Ret = HI_UNF_HDMI_Init();
    if (Ret != HI_SUCCESS)
    {
        ALOGE("call HI_UNF_HDMI_Init failed.\n");
        return Ret;
    }
    return Ret;
}

static jint com_sample_atc_utils_SampleUtils_hdmiOpen(JNIEnv* env){
    int Ret = -1;
    HI_UNF_HDMI_OPEN_PARA_S stOpenPara;
    stOpenPara.enDefaultMode = HI_UNF_HDMI_DEFAULT_ACTION_HDMI;
    Ret = HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0,&stOpenPara);
    return Ret;
}

static jint com_sample_atc_utils_SampleUtils_hdmiTestCMD(JNIEnv* env, jobject clazz, jstring cmd){
    int Ret = -1;
    const char *myCmd = env->GetStringUTFChars(cmd, NULL);
    Ret = HDMI_Test_CMD((HI_CHAR*)myCmd);
    env->ReleaseStringUTFChars(cmd, myCmd);
    return Ret;
}

static jintArray com_sample_atc_utils_SampleUtils_hdmiDisplayEdit(JNIEnv* env, jobject clazz){
    HI_U32     u32Len = 0;
    HI_U32     RetError = HI_SUCCESS;
    HI_U32     index;
    HI_U8      u8Edid[512] = {0};

    printf("hdmi_display_edid enter with HI_UNF_HDMI_Force_GetEDID \n");
    RetError = HI_UNF_HDMI_Force_GetEDID(HI_UNF_HDMI_ID_0,u8Edid,&u32Len);

    if (RetError != HI_SUCCESS)
    {
        printf("can not get sink Attribute\n");
    }

    if(u32Len > 512)
    {
        printf("Edid Len %d is biger than 512! \n",u32Len);
        u32Len = 512;
    }

    jint temp[u32Len];
    for (index = 0; index < u32Len; index ++)
    {
        temp[index] = (jint)u8Edid[index];
    }

    jintArray result = env->NewIntArray(u32Len);
    env->SetIntArrayRegion(result, 0, u32Len, temp);
    free(u8Edid);

    return result;
}

static jint com_sample_atc_utils_SampleUtils_setHdmiMode(JNIEnv* env, jobject clazz, jint mode){
    HI_S32                  Ret;
    HI_UNF_SND_ATTR_S       stAttr;

    Ret = HI_UNF_SND_Init();
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Init failed.\n");
        return Ret;
    }
    Ret = HI_UNF_SND_GetDefaultOpenAttr(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_GetDefaultOpenAttr failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_Open(HI_UNF_SND_0, &stAttr);
    if (Ret != HI_SUCCESS)
    {
        printf("call HI_UNF_SND_Open failed.\n");
        return Ret;
    }

    if(mode == 1){
        Ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_RAW);
        ALOGE("****************** mode = 1");
        ALOGE("****************** Ret = %d",Ret);
    }else{
        Ret = HI_UNF_SND_SetHdmiMode(HI_UNF_SND_0, HI_UNF_SND_OUTPUTPORT_HDMI0, HI_UNF_SND_HDMI_MODE_LPCM);
        ALOGE("****************** mode = 2");
        ALOGE("****************** Ret = %d",Ret);
    }
    Ret = HI_UNF_SND_Close(HI_UNF_SND_0);
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_SND_Close failed.\n");
        return Ret;
    }

    Ret = HI_UNF_SND_DeInit();
    if (Ret != HI_SUCCESS )
    {
        printf("call HI_UNF_SND_DeInit failed.\n");
        return Ret;
    }

    return Ret;
}

static jint com_sample_atc_utils_SampleUtils_getRGBMode(JNIEnv* env){
    int Ret = -1;
    HI_UNF_HDMI_INFOFRAME_S info;
    Ret = HI_UNF_HDMI_GetInfoFrame(HI_UNF_HDMI_ID_0,HI_INFOFRAME_TYPE_AVI,&info);
    if(Ret != HI_SUCCESS)
        return -1;
    return info.unInforUnit.stAVIInfoFrame.enRGBQuantization;
}

static jint com_sample_atc_utils_SampleUtils_getYCCMode(JNIEnv* env){
    int Ret = -1;
    HI_UNF_HDMI_INFOFRAME_S info;
    Ret = HI_UNF_HDMI_GetInfoFrame(HI_UNF_HDMI_ID_0,HI_INFOFRAME_TYPE_AVI,&info);
    if(Ret != HI_SUCCESS)
        return -1;
    return info.unInforUnit.stAVIInfoFrame.enYCCQuantization;
}

static jint com_sample_atc_utils_SampleUtils_getReverseMode(JNIEnv* env){
    int Ret = -1;
    HI_UNF_HDMI_INFOFRAME_S info;
    Ret = HI_UNF_HDMI_GetInfoFrame(HI_UNF_HDMI_ID_0,HI_INFOFRAME_TYPE_AVI,&info);
    if(Ret != HI_SUCCESS)
        return -1;
    return info.unInforUnit.stAVIInfoFrame.enColorimetry;
}

static const JNINativeMethod g_methods[] = {
    { "hdmiInit", "()I", (void *)com_sample_atc_utils_SampleUtils_hdmiInit },
    { "hdmiOpen", "()I", (void *)com_sample_atc_utils_SampleUtils_hdmiOpen },
    { "hdmiTestCMD", "(Ljava/lang/String;)I", (void *)com_sample_atc_utils_SampleUtils_hdmiTestCMD },
    { "hdmiDisplayEdit", "()[I", (void *)com_sample_atc_utils_SampleUtils_hdmiDisplayEdit },
    { "setHdmiMode", "(I)I", (void *)com_sample_atc_utils_SampleUtils_setHdmiMode },
    { "getRGBMode", "()I", (void *)com_sample_atc_utils_SampleUtils_getRGBMode },
    { "getYCCMode", "()I", (void *)com_sample_atc_utils_SampleUtils_getYCCMode },
    { "getReverseMode", "()I", (void *)com_sample_atc_utils_SampleUtils_getReverseMode },
};

static int register_com_sample_atc_utils_SampleUtils(JNIEnv* env)
{
    jclass clazz;
    clazz = env->FindClass("com/sample/atc/utils/SampleUtils");
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, g_methods, NELEM(g_methods)) < 0)
        return JNI_FALSE;
    return JNI_TRUE;
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
     JNIEnv* env = NULL;

     jint Ret = -1;

     if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
         goto bail;
     if (!register_com_sample_atc_utils_SampleUtils(env))
         goto bail;

     Ret = JNI_VERSION_1_4;
 bail:
     return Ret;
}