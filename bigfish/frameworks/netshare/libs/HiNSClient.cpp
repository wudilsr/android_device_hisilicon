#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include <utils/threads.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "HiNSClient.h"

namespace android
{
    sp<IHiNSService> HiNSClient::mNSService;
    const sp<IHiNSService>& HiNSClient::getNSService()
    {
      if(mNSService.get() == 0)
      {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder ;
        do
        {
          binder = sm->getService(String16("HinetshareBService"));
          if (binder != 0)
          {
            break;
          }
          usleep(500000);
        } while(true);
        mNSService = interface_cast<IHiNSService>(binder);
      }
      return mNSService;
    }

    int HiNSClient::sambaChangePassword(const char *buf)
    {
      int ret = -1;
      const sp<IHiNSService>& ps = getNSService();
      if(ps != 0)
      {
        ret = ps->sambaChangePassword(buf);
      }
      return ret;
    }

    int HiNSClient::sambaStop()
    {
      int ret = -1;
      const sp<IHiNSService>& ps = getNSService();
      if(ps != 0)
      {
        ret = ps->sambaStop();
      }
      return ret;
    }

    int HiNSClient::sambaStart()
    {
      int ret = -1;
      const sp<IHiNSService>& ps = getNSService();
      if(ps != 0)
      {
        ret = ps->sambaStart();
      }
      return ret;
    }

    int HiNSClient::NSUnMount(const char *buf)
    {
      int ret = -1;
      const sp<IHiNSService>& ps = getNSService();
      if(ps != 0)
      {
        ret = ps->NSUnMount(buf);
      }
      return ret;
    }

    int HiNSClient::NSMount(const char *buf)
    {
      int ret = -1;
      const sp<IHiNSService>& ps = getNSService();
      if(ps != 0)
      {
        ret = ps->NSMount(buf);
      }
      return ret;
    }

    int HiNSClient::NSSh(HI_NS_CMD_TYPE_E cmd ,const char *buf)
    {
      int ret = -1;
      const sp<IHiNSService>& ps = getNSService();
      if(ps != 0)
      {
        ret = ps->nssh(cmd ,buf);
      }
      return ret;
    }

};
