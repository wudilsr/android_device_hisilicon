#ifndef _INetShareSettingService_H
#define _INetShareSettingService_H

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <utils/Errors.h>

typedef enum HI_NS_CMD_TYPE
{
	HI_NS_CMD_TYPE_RMM =1010,
	HI_NS_CMD_TYPE_PSM ,
	HI_NS_CMD_TYPE_SCANM ,
	HI_NS_CMD_TYPE_CPM ,
	HI_NS_CMD_TYPE_ISOMKNODM ,
	HI_NS_CMD_TYPE_LOSETUPM ,
} HI_NS_CMD_TYPE_E;

namespace android
{
  class IHiNSService : public IInterface
  {
    public:
      DECLARE_META_INTERFACE(HiNSService);
	  virtual int sambaChangePassword(const char *buf) = 0;
	  virtual int sambaStop() = 0;
	  virtual int sambaStart() = 0 ;
	  virtual int NSUnMount(const char *buf) = 0;
	  virtual int NSMount(const char *buf) = 0;
	  virtual int nssh(HI_NS_CMD_TYPE_E cmd ,const char *buf) = 0;
  };

  class BnHiNSService : public BnInterface<IHiNSService>
  {
    public:
      virtual status_t onTransact( uint32_t code,
          const Parcel& data,
          Parcel* reply,
          uint32_t flags = 0);
  };
};

#endif
