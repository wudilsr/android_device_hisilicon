#include <utils/Log.h>
#include <binder/IServiceManager.h>
#include <utils/threads.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include "HiAoServiceClient.h"

namespace android
{
    sp<IHiAoService> HiAoServiceClient::mAoService;
    const sp<IHiAoService>& HiAoServiceClient::getAoService()
    {
      if(mAoService.get() == 0)
      {
        sp<IServiceManager> sm = defaultServiceManager();
        sp<IBinder> binder ;
        do
        {
          binder = sm->getService(String16("hiaoservice"));
          if (binder != 0)
          {
            break;
          }
          usleep(500000);
        } while(true);
        mAoService = interface_cast<IHiAoService>(binder);
      }
      return mAoService;
    }

    int HiAoServiceClient::setAudioOutput(int port,int mode)
    {
      int ret = -1;
      const sp<IHiAoService>& ps = getAoService();
      if(ps != 0)
      {
        ret = ps->setUnfAudioPort(port,mode);
      }
      return ret;
    }

    int HiAoServiceClient::getAudioOutput(int port)
    {
      int ret = -1;
      const sp<IHiAoService>& ps = getAoService();
      if(ps != 0)
      {
        ret = ps->getUnfAudioPort(port);
      }
      return ret;
    }

	int HiAoServiceClient::setEnterSmartSuspend(int status)
    {
      int ret = -1;
      const sp<IHiAoService>& ps = getAoService();
      if(ps != 0)
      {
        ret = ps->setEnterSmartSuspend(status);
      }
      return ret;
    }

};
