#ifndef _HIKARAOKESERVICE_H_
#define _HIKARAOKESERVICE_H_


#include "IHiKaraokeService.h"
#include "HiCircleBuf.h"
#include "HiKaraokeProxy.h"

namespace android
{

    class HiKaraokeService : public BnHiKaraokeService
    {
    public:
        static void instantiate();

        virtual int32_t  initMic();
        virtual int32_t  startMic();
        virtual int32_t  stopMic();
        virtual int32_t  releaseMic();

        virtual int32_t  setReverbMode(uint32_t mode);
        virtual uint32_t getReverbMode();

        virtual uint32_t getMicNumber();

        virtual int32_t  setMicVolume(uint32_t volume);
        virtual uint32_t getMicVolume();

        virtual int32_t setOutputFile(int fd, int64_t offset, int64_t length);
        virtual int32_t initHiKaraokeMediaRecord(uint32_t outputFormat,
                uint32_t audioEncoder, uint32_t sampleRate, uint32_t bitRate,
                uint32_t channels);

        virtual int32_t setHiKaraokeMediaRecordState(uint32_t state);

        virtual sp<IHiKaraokeRecord> openKaraokeRecord(uint32_t sampleRate, uint32_t channels,
                uint32_t frameCounts);

        virtual int32_t getInitState();

        virtual int32_t setKarAlg(uint32_t alg, uint32_t status);

        virtual status_t onTransact(
            uint32_t code,
            const Parcel& data,
            Parcel* reply,
            uint32_t flags = 0);

    private:
        HiKaraokeService();
        virtual ~HiKaraokeService();
        sp<HiKaraokeProxy> mHiKaraokeProxy;

        int32_t mInitState;

    };

    class KaraokeRecordHandle : public android::BnHiKaraokeRecord
    {
    public:
        virtual sp<IMemory> getCblk() const;
        virtual int32_t     start();
        virtual int32_t     stop();
        virtual status_t    onTransact( uint32_t code,
                                        const Parcel& data,
                                        Parcel* reply,
                                        uint32_t flags = 0);

    public:
        KaraokeRecordHandle(sp<HiKaraokeProxy>& proxy, uint32_t sampleRate, uint32_t channels
                            , uint32_t frameCounts);
        virtual ~KaraokeRecordHandle();
        virtual uint32_t read(int8_t* data, uint32_t size);
        static void* InitRecordProcess(void* param);
        virtual uint32_t recordThreadProc();

    private:
        bool mbStopFlag;
        pthread_t  mpthid;
        uint32_t mSampleRate;
        uint32_t mChannels;
        uint32_t mFrameCounts;
        sp<IMemory>  mRecordMemory;
        sp<HiCircleBufExeCutor> mBufExeCutor;
        sp<HiKaraokeProxy> mHiKaraokeProxy;
    };
};

#endif
