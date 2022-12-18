#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>
#include <utils/Log.h>
#include <binder/Parcel.h>
#include "HiNSService.h"
#include "netShareHal.h"
#include <cutils/properties.h>
#include <pthread.h>
#ifdef PRODUCT_DPT
#include <HiTVManager.h>
#endif

namespace android
{
    HiNSService::HiNSService()
    {
    }
    HiNSService::~HiNSService()
    {
    }
    void HiNSService::instantiate()
    {
        defaultServiceManager()->addService(String16("HinetshareBService"), new HiNSService());
    }

    int HiNSService::sambaChangePassword(const char *buf)
	{
		int ret = -3 ;
		ALOGI("sambaChangePassword(server) buf=%s",buf);
		ret = netShareChangePassword(buf);
		ALOGI("sambaChangePassword(server) ret=%d",ret);
		return ret;
	}

    int HiNSService::sambaStop()
	{
		int ret = -3 ;
		ALOGI("sambaStop(server)");
		ret = netShareSambaStop();
		ALOGI("sambaStop(server) ret = %d",ret);
		return ret;
	}

    int HiNSService::sambaStart()
	{
		int ret = -3 ;
		ALOGI("sambaStart(server)");
		ret = netShareSambaStart();
		ALOGI("sambaStart(server) ret = %d",ret);
		return ret;
	}

    int HiNSService::NSUnMount(const char *buf)
	{
		int ret = -3 ;
		ALOGI("NSUnMount(server) buf=%s",buf);
		ret = netShareUnMount(buf);
		ALOGI("NSUnMount(server) ret=%d",ret);
		return ret;
	}

    int HiNSService::NSMount(const char *buf)
	{
		int ret = -3 ;
		ALOGI("NSMount(server) buf=%s",buf);
		ret = netShareMount(buf);
		ALOGI("NSMount(server) ret=%d",ret);
		return ret;
	}

    int HiNSService::nssh(HI_NS_CMD_TYPE_E cmd , const char *buf)
	{
		int ret = -3 ;
		ALOGI("nssh(server) cmd=%d, buf=%s",cmd,buf);
		ret = netShareNssh(cmd,buf);
		ALOGI("nssh(server) ret=%d",ret);
		return ret;
	}

};
