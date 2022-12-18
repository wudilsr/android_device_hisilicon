#include <utils/Log.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>

#include "IHiKaraokeRecord.h"

namespace android
{
    enum
    {
        GET_CBLK = IBinder::FIRST_CALL_TRANSACTION,
        START,
        STOP
    };

    class BpHiKaraokeRecord : public BpInterface<IHiKaraokeRecord>
    {
    public:
        BpHiKaraokeRecord(const sp<IBinder>& impl)
            : BpInterface<IHiKaraokeRecord>(impl)
        {

        }

        virtual sp<IMemory> getCblk() const
        {
            Parcel data, reply;
            sp<IMemory> memory;

            data.writeInterfaceToken(IHiKaraokeRecord::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(GET_CBLK, data, &reply);
            if (lStatus != NO_ERROR)
            {
                ALOGE("getCblk error: %s", strerror(-lStatus));
            }
            else
            {
                memory = interface_cast<IMemory>(reply.readStrongBinder());
                if (memory == 0)
                {
                    ALOGE("getCblk should have returned an IMemory");
                }
            }
            return memory;
        }

        virtual int32_t start()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeRecord::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(START, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t stop()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeRecord::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(STOP, data, &reply);
            return reply.readInt32();
        }


    };

    IMPLEMENT_META_INTERFACE(HiKaraokeRecord, "android.os.IHiKaraokeRecord");

    status_t BnHiKaraokeRecord::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {

        switch (code)
        {
            case GET_CBLK:
            {
                CHECK_INTERFACE(IHiKaraokeRecord, data, reply);
                sp<IMemory> memory = getCblk();
                reply->writeStrongBinder(memory->asBinder());
                return NO_ERROR;
            }
            case START:
                CHECK_INTERFACE(IHiKaraokeRecord, data, reply);
                reply->writeInt32(start());
                return NO_ERROR;
            case STOP:
                CHECK_INTERFACE(IHiKaraokeRecord, data, reply);
                reply->writeInt32(stop());
                return NO_ERROR;
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }

};
