/*
 **************************************************************************************
 *       Filename:  SkJpegEncoder.h
 *    Description:  rgb565 to jpeg header file
 *
 *        Version:  1.0
 *        Created:  2012-06-06 15:33:36
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef SKJPEGENCODER__H_INCLUDED
#define SKIPEGENCODER_H_INCLUDED

#include "SkImageEncoder.h"
#include "SkStream.h"
#include "SkBitmap.h"
#include "SkImageDecoder.h"


class SkJpegImageEncoder : public SkImageEncoder
{
protected:
        virtual bool onEncode(SkWStream* stream, const SkBitmap& bm, int quality);
};

class SkJpegImageSWEncoder : public SkJpegImageEncoder
{
public:
    bool Encode(SkDynamicMemoryWStream* stream, SkBitmap& bm, int quality)
    {
        if(SkJpegImageEncoder::onEncode((SkWStream *)stream,bm,quality))
        {
            return true;
        }
        else
        {
            return false;
        }
    }
};

#endif /*SKJPEGENCODER_H_INCLUDED*/

/********************************* END ***********************************************/
