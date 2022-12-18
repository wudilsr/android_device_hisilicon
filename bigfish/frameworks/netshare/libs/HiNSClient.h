#ifndef _HINS_NSSHCLIENT_H_
#define _HINS_NSSHCLIENT_H_

#include <utils/RefBase.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/IServiceManager.h>
#include <binder/ProcessState.h>
#include <binder/IMemory.h>
#include <binder/Parcel.h>
#include "IHiNSService.h"

namespace android
{
	class HiNSClient: public RefBase
	{
		public:
			static int sambaChangePassword(const char *buf) ;
			static int sambaStop() ;
			static int sambaStart() ;
			static int NSUnMount(const char *buf) ;
			static int NSMount(const char *buf) ;
			static int NSSh(HI_NS_CMD_TYPE_E cmd ,const char *buf) ;
		private:
			const static sp<IHiNSService> & getNSService();
			static sp<IHiNSService> mNSService;

	};
};
#endif
