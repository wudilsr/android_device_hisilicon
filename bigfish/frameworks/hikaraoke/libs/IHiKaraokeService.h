#ifndef _IHIKARAOKESERVICE_H_
#define _IHIKARAOKESERVICE_H_

#include <utils/RefBase.h>
#include <binder/IInterface.h>

#include "IHiKaraokeRecord.h"

namespace android
{
    class IHiKaraokeService : public IInterface
    {
    public:
        DECLARE_META_INTERFACE(HiKaraokeService);

        virtual int32_t initMic() = 0;
        virtual int32_t startMic() = 0;
        virtual int32_t stopMic() = 0;
        virtual int32_t releaseMic() = 0;

        virtual int32_t  setReverbMode(uint32_t mode) = 0;
        virtual uint32_t getReverbMode() = 0;

        virtual uint32_t getMicNumber() = 0;

        virtual int32_t setMicVolume(uint32_t volume) = 0;
        virtual uint32_t getMicVolume() = 0;

        virtual int32_t setOutputFile(int fd, int64_t offset, int64_t length) = 0;
        virtual int32_t initHiKaraokeMediaRecord(uint32_t outputFormat,
                uint32_t audioEncoder, uint32_t sampleRate, uint32_t bitRate,
                uint32_t channels) = 0;
        virtual int32_t setHiKaraokeMediaRecordState(uint32_t state) = 0;

        virtual sp<IHiKaraokeRecord> openKaraokeRecord(uint32_t sampleRate, uint32_t channels,
                uint32_t frameCounts) = 0;

        virtual int32_t getInitState() = 0;

        virtual int32_t setKarAlg(uint32_t alg, uint32_t status) = 0;
    };

    class BnHiKaraokeService : public BnInterface<IHiKaraokeService>
    {
    public:
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& data,
                                        Parcel* reply,
                                        uint32_t flags = 0);
    };

};

#endif
