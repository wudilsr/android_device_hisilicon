#ifndef _IHIKARAOKETRACK_H_
#define _IHIKARAOKETRACK_H_

#include <stdint.h>
#include <sys/types.h>

#include <utils/RefBase.h>
#include <utils/Errors.h>
#include <binder/IInterface.h>
#include <binder/IMemory.h>

namespace android
{
    class IHiKaraokeRecord : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(HiKaraokeRecord);

        /* get this tracks control block */
        virtual sp<IMemory> getCblk() const = 0;

        virtual int32_t    start() = 0;

        virtual int32_t    stop() = 0;
    };

    class BnHiKaraokeRecord : public BnInterface<IHiKaraokeRecord>
    {
    public:
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& data,
                                        Parcel* reply,
                                        uint32_t flags = 0);
    };
};
#endif
