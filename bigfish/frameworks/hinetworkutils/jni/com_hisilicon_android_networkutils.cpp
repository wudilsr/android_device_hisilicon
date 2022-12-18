/*
 * Copyright 2008, The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#define LOG_TAG "HiNetUtils"

#include "jni.h"
#include <utils/Log.h>
#include <utils/misc.h>
#include <cutils/properties.h>

extern "C" {
int ifc_get_default_route(const char *ifname);

int dhcp_do_request(const char * const ifname,
                    const char *ipaddr,
                    const char *gateway,
                    uint32_t *prefixLength,
                    const char *dns[],
                    const char *server,
                    uint32_t *lease,
                    const char *vendorInfo,
                    const char *domains,
                    const char *mtu);

int dhcp_do_request_renew(const char * const ifname,
                    const char *ipaddr,
                    const char *gateway,
                    uint32_t *prefixLength,
                    const char *dns[],
                    const char *server,
                    uint32_t *lease,
                    const char *vendorInfo,
                    const char *domains,
                    const char *mtu);

int dhcp_stop(const char *ifname);
int dhcp_release_lease(const char *ifname);
char *dhcp_get_errmsg();
const char *ifc_get_ipaddr(const char *ifname);
const char *ifc_get_netmask(const char *ifname);
int ifc_get_netlink_status(const char *ifname);
}

#define HINETUTILS_PKG_NAME "com/hisilicon/android/networkutils/HiNetworkUtils"


jboolean com_hisilicon_android_networkutils_hinetworkutils_runDhcpCommon(JNIEnv* env, jobject clazz, jstring ifname, bool renew)
{
    int result;
    char  ipaddr[PROPERTY_VALUE_MAX];
    uint32_t prefixLength;
    char gateway[PROPERTY_VALUE_MAX];
    char    dns1[PROPERTY_VALUE_MAX];
    char    dns2[PROPERTY_VALUE_MAX];
    char    dns3[PROPERTY_VALUE_MAX];
    char    dns4[PROPERTY_VALUE_MAX];
    const char *dns[5] = {dns1, dns2, dns3, dns4, NULL};
    char  server[PROPERTY_VALUE_MAX];
    uint32_t lease;
    char vendorInfo[PROPERTY_VALUE_MAX];
    char domains[PROPERTY_VALUE_MAX];
    char mtu[PROPERTY_VALUE_MAX];

    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    if (nameStr == NULL) return (jboolean)false;

    if (renew) {
        result = ::dhcp_do_request_renew(nameStr, ipaddr, gateway, &prefixLength,
                dns, server, &lease, vendorInfo, domains, mtu);
    } else {
        result = ::dhcp_do_request(nameStr, ipaddr, gateway, &prefixLength,
                dns, server, &lease, vendorInfo, domains, mtu);
    }
    if (result != 0) {
        ALOGD("dhcp_do_request failed : %s (%s)", nameStr, renew ? "renew" : "new");
    }

    env->ReleaseStringUTFChars(ifname, nameStr);
    return (jboolean)(result == 0);
}

jboolean com_hisilicon_android_networkutils_hinetworkutils_startDhcp(JNIEnv* env, jobject clazz, jstring ifname)
{
    return com_hisilicon_android_networkutils_hinetworkutils_runDhcpCommon(env, clazz, ifname, false);
}

jboolean com_hisilicon_android_networkutils_hinetworkutils_stopDhcp(JNIEnv* env, jobject clazz, jstring ifname)
{
    int result;

    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    result = ::dhcp_stop(nameStr);
    env->ReleaseStringUTFChars(ifname, nameStr);
    return (jboolean)(result == 0);
}

jboolean com_hisilicon_android_networkutils_hinetworkutils_releaseDhcpLease(JNIEnv* env, jobject clazz, jstring ifname)
{
    int result;

    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    result = ::dhcp_release_lease(nameStr);
    env->ReleaseStringUTFChars(ifname, nameStr);
    return (jboolean)(result == 0);
}

jstring com_hisilicon_android_networkutils_hinetworkutils_getDhcpError(JNIEnv* env, jobject clazz)
{
    return env->NewStringUTF(::dhcp_get_errmsg());
}

jstring com_hisilicon_android_networkutils_hinetworkutils_getIpaddr(JNIEnv* env, jobject clazz, jstring ifname)
{
    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    return env->NewStringUTF(::ifc_get_ipaddr(nameStr));
}

jstring com_hisilicon_android_networkutils_hinetworkutils_getNetmask(JNIEnv* env, jobject clazz, jstring ifname)
{
    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    return env->NewStringUTF(::ifc_get_netmask(nameStr));
}

jint com_hisilicon_android_networkutils_hinetworkutils_getNetlinkStatus(JNIEnv* env, jobject clazz, jstring ifname)
{
    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    return (jint)(::ifc_get_netlink_status(nameStr));
}

jint com_hisilicon_android_networkutils_hinetworkutils_getDefaultRoute(JNIEnv* env, jobject clazz, jstring ifname)
{
    int result;

    const char *nameStr = env->GetStringUTFChars(ifname, NULL);
    result = ::ifc_get_default_route(nameStr);
    env->ReleaseStringUTFChars(ifname, nameStr);
    return (jint)result;
}

/*
 * JNI registration.
 */

static const JNINativeMethod gHiNetworkUtilMethods[] = {
    /* name, signature, funcPtr */

    { "startDhcp", "(Ljava/lang/String;)Z",  (void *)com_hisilicon_android_networkutils_hinetworkutils_startDhcp },
    { "stopDhcp", "(Ljava/lang/String;)Z",  (void *)com_hisilicon_android_networkutils_hinetworkutils_stopDhcp },
    { "getDhcpError", "()Ljava/lang/String;", (void*) com_hisilicon_android_networkutils_hinetworkutils_getDhcpError },
    { "getIpaddr", "(Ljava/lang/String;)Ljava/lang/String;", (void*) com_hisilicon_android_networkutils_hinetworkutils_getIpaddr },
    { "getNetmask", "(Ljava/lang/String;)Ljava/lang/String;", (void*) com_hisilicon_android_networkutils_hinetworkutils_getNetmask },
    { "getDefaultRoute", "(Ljava/lang/String;)I",  (void *)com_hisilicon_android_networkutils_hinetworkutils_getDefaultRoute },
    { "getNetlinkStatus", "(Ljava/lang/String;)I",  (void *)com_hisilicon_android_networkutils_hinetworkutils_getNetlinkStatus},
};

static int register_com_hisilicon_android_networkutils_hinetworkutils(JNIEnv* env)
{
    jclass clazz;
    clazz = env->FindClass(HINETUTILS_PKG_NAME);
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, gHiNetworkUtilMethods, NELEM(gHiNetworkUtilMethods)) < 0)
        return JNI_FALSE;
    return JNI_TRUE;
}


jint JNI_OnLoad(JavaVM* vm, void* reserved) {
     JNIEnv* env = NULL;
     jint result = -1;

     if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
         goto bail;
     if (!register_com_hisilicon_android_networkutils_hinetworkutils(env))
         goto bail;
     result = JNI_VERSION_1_4;
bail:
     return result;
}
