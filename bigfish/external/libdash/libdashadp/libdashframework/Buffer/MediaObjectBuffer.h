/*
 * MediaObjectBuffer.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_BUFFER_MEDIAOBJECTBUFFER_H_
#define LIBDASH_FRAMEWORK_BUFFER_MEDIAOBJECTBUFFER_H_

#include "../Input/MediaObject.h"
#include "../Portable/MultiThreading.h"
#include "IBufferObserver.h"
#include <deque>

namespace libdash
{
    namespace framework
    {
        namespace buffer
        {
            class MediaObjectBuffer
            {
                public:
                    MediaObjectBuffer                           (uint32_t maxcapacity);
                    virtual ~MediaObjectBuffer                  ();

                    bool                        PushBack        (input::MediaObject *media);
                    bool                        PushBack        (input::MediaObject *media, bool force);
                    input::MediaObject*         Front           ();
                    input::MediaObject*         GetFront        ();
                    void                        PopFront        ();
                    input::MediaObject*         Back           ();
                    input::MediaObject*         GetBack       ();
                    void                        PopBack        ();
                    void                        ClearTail       ();
                    void                        Clear           ();
                    void                        SetEOS          (bool value);
                    void                        SetEOS          ();
                    uint32_t                    Length          ();
                    uint32_t                    Capacity        ();
                    void                        AttachObserver  (IBufferObserver *observer);
                    void                        Notify          ();
                private:
                    std::deque<input::MediaObject *>    mediaobjects;
                    std::vector<IBufferObserver*>       observer;
                    bool                                eos;
                    uint32_t                            maxcapacity;
                    uint64_t                            bufferSize;
                    mutable CRITICAL_SECTION            monitorMutex;
                    mutable CONDITION_VARIABLE          full;
                    mutable CONDITION_VARIABLE          empty;
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_BUFFER_MEDIAOBJECTBUFFER_H_ */