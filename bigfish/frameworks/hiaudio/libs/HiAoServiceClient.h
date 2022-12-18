#ifndef _AUDIOSETTINGCLIENT_H_
#define _AUDIOSETTINGCLIENT_H_

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include "IHiAoService.h"

namespace android
{
  class HiAoServiceClient: public RefBase
  {
    public:

      int setAudioOutput(int port,int mode);
      int getAudioOutput(int port);
      int setEnterSmartSuspend(int status);

    private:

      const sp<IHiAoService> & getAoService();
      static sp<IHiAoService> mAoService;

  };
};
#endif
