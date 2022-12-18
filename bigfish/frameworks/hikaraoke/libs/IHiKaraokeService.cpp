#define  LOG_NDEBUG 0
#define  LOG_TAG "HikaraokeService"

#include <utils/Log.h>
#include <binder/IBinder.h>
#include <binder/IInterface.h>
#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/Parcel.h>
#include "IHiKaraokeService.h"


namespace android
{
    enum
    {
        INIT_MIC = IBinder::FIRST_CALL_TRANSACTION,
        START_MIC,
        STOP_MIC,
        RELEASE_MIC,
        SET_REVERB_MODE,
        GET_REVERB_MODE,
        GET_MIC_NUMBER,
        SET_MIC_VOLUME,
        GET_MIC_VOLUME,
        SET_OUTPUT_FILE_FD,
        INIT_HIKARAOKEMEDIARECORD,
        SET_HIKARAOKEMEDIARECORD_STATE,
        OPEN_KARAOKE_RECORD,
        GET_INITSTATE,
        SET_KARAOKE_ALG,
    };

    class BpHiKaraokeService : public BpInterface<IHiKaraokeService>
    {
    public:
        BpHiKaraokeService(const sp<IBinder>& impl)
            : BpInterface<IHiKaraokeService>(impl)
        {
        }

        virtual int32_t initMic()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(INIT_MIC, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t startMic()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(START_MIC, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t stopMic()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(STOP_MIC, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t releaseMic()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(RELEASE_MIC, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t  setReverbMode(uint32_t mode)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            data.writeInt32((int32_t)mode);
            status_t lStatus = remote()->transact(SET_REVERB_MODE, data, &reply);
            return reply.readInt32();
        }
        virtual uint32_t getReverbMode()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(GET_REVERB_MODE, data, &reply);
            return (uint32_t)reply.readInt32();
        }

        virtual uint32_t getMicNumber()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(GET_MIC_NUMBER, data, &reply);
            return (uint32_t)reply.readInt32();
        }

        virtual int32_t setMicVolume(uint32_t volume)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            data.writeInt32((int32_t)volume);
            status_t lStatus = remote()->transact(SET_MIC_VOLUME, data, &reply);
            return reply.readInt32();
        }

        virtual uint32_t getMicVolume()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(GET_MIC_VOLUME, data, &reply);
            return (uint32_t)reply.readInt32();
        }

        virtual int32_t setOutputFile(int fd, int64_t offset, int64_t length)
        {
            ALOGV("setOutputFile(%d, %lld, %lld)", fd, offset, length);
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            data.writeFileDescriptor(fd);
            data.writeInt64(offset);
            data.writeInt64(length);
            remote()->transact(SET_OUTPUT_FILE_FD, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t initHiKaraokeMediaRecord(uint32_t outputFormat,
                uint32_t audioEncoder, uint32_t sampleRate, uint32_t bitRate,
                uint32_t channels)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            //  data.writeFileDescriptor(fd);
            data.writeInt32((int32_t)outputFormat);
            data.writeInt32((int32_t)audioEncoder);
            data.writeInt32((int32_t)sampleRate);
            data.writeInt32((int32_t)bitRate);
            data.writeInt32((int32_t)channels);
            status_t lStatus = remote()->transact(INIT_HIKARAOKEMEDIARECORD, data, &reply);
            return reply.readInt32();
        }

        virtual int32_t setHiKaraokeMediaRecordState(uint32_t state)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            data.writeInt32((int32_t)state);
            status_t lStatus = remote()->transact(SET_HIKARAOKEMEDIARECORD_STATE, data, &reply);
            return reply.readInt32();
        }

        virtual sp<IHiKaraokeRecord> openKaraokeRecord(uint32_t sampleRate, uint32_t channels,
                uint32_t frameCounts)
        {
            Parcel data, reply;
            sp<IHiKaraokeRecord> record;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            data.writeInt32((int32_t)sampleRate);
            data.writeInt32((int32_t)channels);
            data.writeInt32((int32_t)frameCounts);
            status_t lStatus = remote()->transact(OPEN_KARAOKE_RECORD, data, &reply);
            if (lStatus != NO_ERROR)
            {
                ALOGE("openKaraokeRecord error: %s", strerror(-lStatus));
            }
            else
            {
                record = interface_cast<IHiKaraokeRecord>(reply.readStrongBinder());
                if (record == 0)
                {
                    ALOGE("openKaraokeRecord should have returned an IHiKaraokeRecord");
                }

            }
            return record;
        }

        virtual int32_t getInitState()
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            status_t lStatus = remote()->transact(GET_INITSTATE, data, &reply);

            int32_t ret = reply.readInt32();
            ALOGD("getInitState ret = %d", ret);
            return ret;
        }

        virtual int32_t setKarAlg(uint32_t alg, uint32_t status)
        {
            Parcel data, reply;
            data.writeInterfaceToken(IHiKaraokeService::getInterfaceDescriptor());
            data.writeInt32((int32_t)alg);
            data.writeInt32((int32_t)status);
            status_t lStatus = remote()->transact(SET_KARAOKE_ALG, data, &reply);
            int32_t ret = reply.readInt32();
            ALOGD("getInitState ret = %d", ret);
            return ret;
        }



    };

    IMPLEMENT_META_INTERFACE(HiKaraokeService, "android.os.HiKaraokeService");

    status_t BnHiKaraokeService::onTransact(
        uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
    {
        int32_t ret = -1;
        int32_t volume;
        int32_t sampleRate;
        int32_t channels;
        int32_t frameCounts;
        int32_t reverbMode;
        switch (code)
        {
            case INIT_MIC:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = initMic();
                reply->writeInt32(ret);
                return NO_ERROR;
            case START_MIC:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = startMic();
                reply->writeInt32(ret);
                return NO_ERROR;
            case STOP_MIC:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = stopMic();
                reply->writeInt32(ret);
                return NO_ERROR;
            case RELEASE_MIC:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = releaseMic();
                reply->writeInt32(ret);
                return NO_ERROR;
            case SET_REVERB_MODE:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                reverbMode = data.readInt32();
                ret = setReverbMode(reverbMode);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GET_REVERB_MODE:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = getReverbMode();
                reply->writeInt32(ret);
                return NO_ERROR;
            case GET_MIC_NUMBER:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = getMicNumber();
                reply->writeInt32(ret);
                return NO_ERROR;
            case SET_MIC_VOLUME:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                volume = data.readInt32();
                ret = setMicVolume(volume);
                reply->writeInt32(ret);
                return NO_ERROR;
            case GET_MIC_VOLUME:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = getMicVolume();
                reply->writeInt32(ret);
                return NO_ERROR;
            case SET_OUTPUT_FILE_FD:
            {
                ALOGV("SET_OUTPUT_FILE_FD");
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                int fd = dup(data.readFileDescriptor());
                int64_t offset = data.readInt64();
                int64_t length = data.readInt64();
                reply->writeInt32(setOutputFile(fd, offset, length));
                ::close(fd);
                return NO_ERROR;
            }
            case INIT_HIKARAOKEMEDIARECORD:
            {
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                //  int32_t fd = dup(data.readFileDescriptor());
                uint32_t outputFormat = data.readInt32();
                uint32_t audioEncoder = data.readInt32();
                uint32_t sampleRate = data.readInt32();
                uint32_t bitRate = data.readInt32();
                uint32_t channels = data.readInt32();
                ret = initHiKaraokeMediaRecord(outputFormat, audioEncoder,
                                               sampleRate, bitRate, channels);

                reply->writeInt32(ret);
                return NO_ERROR;
            }
            case SET_HIKARAOKEMEDIARECORD_STATE:
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = setHiKaraokeMediaRecordState(data.readInt32());
                reply->writeInt32(ret);
                return NO_ERROR;
            case OPEN_KARAOKE_RECORD:
            {
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                sp<IHiKaraokeRecord> record;
                sampleRate = data.readInt32();
                channels = data.readInt32();
                frameCounts = data.readInt32();
                record = openKaraokeRecord(sampleRate, channels, frameCounts);
                reply->writeStrongBinder(record->asBinder());
                return NO_ERROR;
            }
            case GET_INITSTATE:
            {
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                ret = getInitState();
                reply->writeInt32(ret);
                return NO_ERROR;
            }
            case SET_KARAOKE_ALG:
            {
                CHECK_INTERFACE(IHiKaraokeService, data, reply);
                uint32_t alg = data.readInt32();
                uint32_t status = data.readInt32();
                ret = setKarAlg(alg, status);
                reply->writeInt32(ret);
                return NO_ERROR;
            }
            default:
                return BBinder::onTransact(code, data, reply, flags);
        }
    }
};
