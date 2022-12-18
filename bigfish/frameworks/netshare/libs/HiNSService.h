#ifndef NETSHARESETTINGSERVICE_H
#define  NETSHARESETTINGSERVICE_H

#include <cutils/memory.h>
#include <utils/Log.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include "IHiNSService.h"


namespace android
{
  class HiNSService: public BnHiNSService
  {
    public:
      HiNSService();
      ~HiNSService();
	  static void instantiate();
	  virtual int sambaChangePassword(const char *buf);
	  virtual int sambaStop();
	  virtual int sambaStart();
	  virtual int NSUnMount(const char *buf);
	  virtual int NSMount(const char *buf);
	  virtual int nssh(HI_NS_CMD_TYPE_E cmd ,const char *buf);
  };

};

#endif
