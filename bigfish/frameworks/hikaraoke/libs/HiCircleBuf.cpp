//#define  LOG_NDEBUG 0
#define  LOG_TAG "HiCircleBufExeCutor"
#include <utils/Log.h>

#include "HiCircleBuf.h"

namespace android
{
    HiCircleBufExeCutor::HiCircleBufExeCutor(HiCircleBufCtrl* pCtrl, int8_t* pBuf)
    {
        pHiCircleBufCtrl = pCtrl;
        pRealDataBuf = pBuf;
    }

    int HiCircleBufExeCutor::circleBufWrite(int8_t* data, int32_t length)
    {
        if (circleBufQueryFree() <  length)
        {
            return 0;
        }

        int32_t i, readPos, writePos;

        readPos = pHiCircleBufCtrl->mReadPos;
        writePos = pHiCircleBufCtrl->mWritePos;

        if (writePos >= readPos)
        {
            if (writePos + length <= pHiCircleBufCtrl->mBufLenght)
            {
                memcpy(pRealDataBuf + writePos, data, length);
                pHiCircleBufCtrl->mWritePos += length;
                return length;
            }
            else
            {
                memcpy(pRealDataBuf + writePos, data, pHiCircleBufCtrl->mBufLenght - writePos);
                memcpy(pRealDataBuf, data + pHiCircleBufCtrl->mBufLenght - writePos,
                       length - (pHiCircleBufCtrl->mBufLenght - writePos));
                pHiCircleBufCtrl->mWritePos = length - (pHiCircleBufCtrl->mBufLenght - writePos);
                return length;
            }
        }
        else
        {
            memcpy(pRealDataBuf + writePos, data, length);
            pHiCircleBufCtrl->mWritePos += length;
            return length;
        }

    }

    int HiCircleBufExeCutor::circleBufRead(int8_t* data, int32_t length)
    {
        if (circleBufQueryBusy() <  length)
        {
            return 0;
        }
        int32_t i, readPos, writePos;

        readPos = pHiCircleBufCtrl->mReadPos;
        writePos = pHiCircleBufCtrl->mWritePos;

        if (writePos > readPos)
        {
            memcpy(data, pRealDataBuf + readPos, length);
            pHiCircleBufCtrl->mReadPos += length;
            return length;
        }
        else
        {
            if (readPos + length <= pHiCircleBufCtrl->mBufLenght)
            {
                memcpy(data, pRealDataBuf + readPos, length);
                pHiCircleBufCtrl->mReadPos += length;
                return length;
            }
            else
            {
                memcpy(data, pRealDataBuf + readPos, pHiCircleBufCtrl->mBufLenght - readPos);
                memcpy(data + pHiCircleBufCtrl->mBufLenght - readPos, pRealDataBuf,
                       length - (pHiCircleBufCtrl->mBufLenght - readPos));
                pHiCircleBufCtrl->mReadPos = length - (pHiCircleBufCtrl->mBufLenght - readPos);
                return length;
            }
        }
    }

    int HiCircleBufExeCutor::circleBufQueryFree()
    {
        int32_t readPos, writePos, freeLen = 0;
        readPos = pHiCircleBufCtrl->mReadPos;
        writePos = pHiCircleBufCtrl->mWritePos;
        if (readPos > writePos)
        {
            freeLen = readPos - writePos;
        }
        else
        {
            freeLen = pHiCircleBufCtrl->mBufLenght - (writePos - readPos);
        }
        //   ALOGD("HiCircleBufExeCutor::circleBufQueryFree = %d", freeLen);
        return freeLen;
    }

    int HiCircleBufExeCutor::circleBufQueryBusy()
    {
        int32_t readPos, writePos, BusyLen = 0;
        readPos = pHiCircleBufCtrl->mReadPos;
        writePos = pHiCircleBufCtrl->mWritePos;
        if (writePos > readPos)
        {
            BusyLen = writePos - readPos;
        }
        else if (writePos < readPos)
        {
            BusyLen = pHiCircleBufCtrl->mBufLenght - (readPos - writePos);
        }
        //      ALOGD("HiCircleBufExeCutor::circleBufQueryBusy = %d", BusyLen);
        return BusyLen;
    }

};
