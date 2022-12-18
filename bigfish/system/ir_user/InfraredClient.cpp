#include <jni.h>
#include <JNIHelp.h>

#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include <utils/threads.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IInterface.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <arpa/inet.h>


#include <android_runtime/AndroidRuntime.h>
#include "InfraredClient.h"


namespace android {

sp<IInfraredInterface> InfraredClient::infrared_service;

//static const char* JAVA_CLASS_NAME = "com/hisi/web/BrowserActivity";
static const char* JAVA_CLASS_NAME = "android/webkit/WebView";
static bool s_isStartService = true;

int32_t InfraredClient::getInfraredState() {
    const sp<IInfraredInterface>& service = getInfraredService();
    if (service.get())
        return service->getInfraredState();
    else
        return 0;
}


void InfraredClient::setInfraredState(int32_t s) {
    const sp<IInfraredInterface>& service = getInfraredService();

    if (service.get())
        service->setInfraredState(s);
}


sp<IInfraredInterface> InfraredClient::getInfraredService() {

    if (s_isStartService){
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder;
        binder = sm->getService(String16("service.infrared"));
        if (0 != binder.get()) {
            XLOGD("InfraredClient", "Got service.infrared!");
        } else {
            XLOGE("InfraredClient", "Failed to get service.infrared!");
            s_isStartService = false;
        }
        infrared_service = interface_cast<IInfraredInterface>(binder);
    }

    return infrared_service;
}

}

using namespace android;
static int GetInfraredState(JNIEnv *env, jobject thiz) {
    XLOGD("InfraredClient", "GetInfraredState...!");
    sp<InfraredClient> client = new InfraredClient();
    return static_cast<int>(client->getInfraredState());
}

static void SetInfraredState(JNIEnv *env, jobject thiz, int s) {
    XLOGD("InfraredClient", "SetInfraredState - %d!", s);
    sp<InfraredClient> client = new InfraredClient();
    client->setInfraredState(static_cast<int32_t>(s));
}

static JNINativeMethod gMethods[] = {
    {"SetInfraredState", "(I)V", (void *)SetInfraredState},
    {"GetInfraredState", "()I", (void *)GetInfraredState},
};

static int register_com_android_browser_infraredservice(JNIEnv *env) {
    return AndroidRuntime::registerNativeMethods(env, JAVA_CLASS_NAME, gMethods, NELEM(gMethods));
}

jint JNI_OnLoad(JavaVM *vm, void *reserved) {
    JNIEnv *env = NULL;
    jint result = -1;
    //gJVM = vm;

    if (vm->GetEnv((void**)&env, JNI_VERSION_1_4) != JNI_OK) {
        XLOGE("InfraredClient", "ERROR: GetEnv failed\n");
        goto bail;
    }

    assert(env != NULL);
    if (register_com_android_browser_infraredservice(env) < 0) {
        XLOGE("InfraredClient", "register_com_android_browser_infraredservice failed!\n");
        goto bail;
    }
    result = JNI_VERSION_1_4;

bail:
    return result;
}
