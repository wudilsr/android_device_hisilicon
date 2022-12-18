#include <utils/Log.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>
#include <stdint.h>
#include "IHiNSService.h"
namespace android
{
  enum {
    CHANGEPASSWORD = IBinder::FIRST_CALL_TRANSACTION,
    SAMBASTOP,
    SAMBASTART,
    NSUNMOUNT,
    NSMOUNT,
	NSSH,
  };

  class BpHiNSService : public BpInterface<IHiNSService>
  {
    public :

      BpHiNSService(const sp<IBinder>& impl)
        : BpInterface<IHiNSService>(impl)
      {
      }

	 virtual int sambaChangePassword(const char *buf)
	  {
          ALOGI("samba(IClient) change password buf=(%s)",buf);
          Parcel data,reply;
          data.writeInterfaceToken(IHiNSService::getInterfaceDescriptor());
          data.writeCString(buf);
		  remote()->transact(CHANGEPASSWORD,data, &reply);
		  int32_t ret = reply.readInt32();
		  if(ret == 0)
		  {
			  ret = reply.readInt32();
		  }
		  else
		  {
			  ret = -1;
		  }
		  return ret;
	  }

      virtual int sambaStop()
      {
          ALOGI("sambaStop(IClient)");
          Parcel data,reply;
		  data.writeInterfaceToken(IHiNSService::getInterfaceDescriptor());
		  remote()->transact(SAMBASTOP,data, &reply,IBinder::FLAG_ONEWAY);
		  int32_t ret = reply.readInt32();
		  if(ret == 0)
		  {
			  ret = reply.readInt32();
		  }
		  else
		  {
			  ret = -1;
		  }
		  return ret;
	  }

      virtual int sambaStart()
      {
          ALOGI("sambaStart(IClient)");
          Parcel data,reply;
          data.writeInterfaceToken(IHiNSService::getInterfaceDescriptor());
		  remote()->transact(SAMBASTART,data, &reply,IBinder::FLAG_ONEWAY);
		  int32_t ret = reply.readInt32();
		  if(ret == 0)
		  {
			  ret = reply.readInt32();
		  }
		  else
		  {
			  ret = -1;
		  }
		  return ret;
	  }

      virtual int NSUnMount(const char *buf)
      {
        ALOGI("NSUnMount(IClient) buf=(%s)",buf);
        Parcel data,reply;
        data.writeInterfaceToken(IHiNSService::getInterfaceDescriptor());
        data.writeCString(buf);
        remote()->transact(NSUNMOUNT,data, &reply);
        int32_t ret = reply.readInt32();
        if(ret == 0)
        {
          ret = reply.readInt32();
        }
        else
        {
          ret = -1;
        }
        return ret;
      }

      virtual int NSMount(const char *buf)
      {
        ALOGI("NSMount(IClient) buf=(%s)",buf);
        Parcel data,reply;
        data.writeInterfaceToken(IHiNSService::getInterfaceDescriptor());
        data.writeCString(buf);
        remote()->transact(NSMOUNT,data, &reply);
        int32_t ret = reply.readInt32();
        if(ret == 0)
        {
          ret = reply.readInt32();
        }
        else
        {
          ret = -1;
        }
        return ret;
      }

      virtual int nssh(HI_NS_CMD_TYPE_E cmd ,const char *buf)
      {
        ALOGI("nssh(IClient)cmd=%d,buf=(%s)",cmd,buf);
        Parcel data,reply;
        data.writeInterfaceToken(IHiNSService::getInterfaceDescriptor());
		data.writeInt32(cmd);
        data.writeCString(buf);
        remote()->transact(NSSH,data, &reply);
        int32_t ret = reply.readInt32();
        if(ret == 0)
        {
          ret = reply.readInt32();
        }
        else
        {
          ret = -1;
        }
        return ret;
      }
  };

   IMPLEMENT_META_INTERFACE(HiNSService, "IHiNSService");
   status_t BnHiNSService::onTransact( uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
  {
    int ret = -1;
	HI_NS_CMD_TYPE_E cmd ;
	const char *buf;
    switch(code)
    {
      case CHANGEPASSWORD:
         CHECK_INTERFACE(IHiNSService, data, reply);
         buf = data.readCString();
         ret = sambaChangePassword(buf);
         reply->writeInt32(ret);
         return NO_ERROR;
      case SAMBASTOP:
         CHECK_INTERFACE(IHiNSService, data, reply);
         ret = sambaStop();
         reply->writeInt32(ret);
         return NO_ERROR;
      case SAMBASTART:
         CHECK_INTERFACE(IHiNSService, data, reply);
         ret = sambaStart();
         reply->writeInt32(ret);
         return NO_ERROR;
      case NSUNMOUNT:
         CHECK_INTERFACE(IHiNSService, data, reply);
         buf = data.readCString();
         ret = NSUnMount(buf);
         reply->writeInt32(ret);
         return NO_ERROR;
      case NSMOUNT:
         CHECK_INTERFACE(IHiNSService, data, reply);
         buf = data.readCString();
         ret = NSMount(buf);
         reply->writeInt32(ret);
         return NO_ERROR;
      case NSSH:
         CHECK_INTERFACE(IHiNSService, data, reply);
		 cmd = (HI_NS_CMD_TYPE_E)data.readInt32();
         buf = data.readCString();
         ret = nssh(cmd ,buf);
         reply->writeInt32(ret);
         return NO_ERROR;
	  default:
         return BBinder::onTransact(code, data, reply, flags);
    }
   }
};//namespace android
