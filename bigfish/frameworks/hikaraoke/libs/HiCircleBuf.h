#ifndef _HICIRCLEBUF_H_
#define _HICIRCLEBUF_H_

#include <utils/RefBase.h>

namespace android
{
    struct HiCircleBufCtrl
    {
        volatile int32_t mWritePos;
        volatile int32_t mReadPos;
        int32_t  mBufLenght;
    };

    class HiCircleBufExeCutor : public RefBase
    {
    public:
        HiCircleBufExeCutor(HiCircleBufCtrl* pCtrl, int8_t* pBuf);
        virtual ~HiCircleBufExeCutor() {};
        int circleBufWrite(int8_t* data, int32_t length);
        int circleBufRead(int8_t* data, int32_t length);
    private:
        int circleBufQueryFree();
        int circleBufQueryBusy();
        HiCircleBufCtrl* pHiCircleBufCtrl;
        int8_t*   pRealDataBuf;

    };


};

#endif
