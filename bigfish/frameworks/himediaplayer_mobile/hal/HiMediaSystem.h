#ifndef _ANDROID_HI_MEDIA_SYSTEM_H_
#define _ANDROID_HI_MEDIA_SYSTEM_H_
#include <utils/threads.h>
namespace android
{
    class HiMediaSystem
    {
public:
#define MAX_INSTANCE_NUM (15)
        static int         initDevice();
        static int         deInitDevice();
        static int         initCharset();
        static int         deInitCharset();
        static int         initPlayer();
        static int         deInitPlayer();
        static int         setDemuxerFQSize(int handle, unsigned int index, int size);
private:
        static bool        mRegisterFormat;
        static int         mInstCount;
        static Mutex       mInstMutex;
        static int         mPlayerInstCount;
        static Mutex       mPlayerInstMutex;
        static int         mCharsetInstCount;
        static Mutex       mCharsetInstMutex;
        static int         mDeviceInstCount;
        static Mutex       mDeviceInstMutex;
        static int         initMediaDevice();
        static int         destroyMediaDevice();
    };
};
#endif
