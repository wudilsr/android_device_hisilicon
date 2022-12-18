/*
 * MultimediaStream.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef QTSAMPLEPLAYER_MANAGERS_MULTIMEDIASTREAM_H_
#define QTSAMPLEPLAYER_MANAGERS_MULTIMEDIASTREAM_H_

#include "IMPD.h"
#include "IStreamObserver.h"
#include "DecodingThread.h"
#include "../libdashframework/Input/DASHManager.h"
#include "../libdashframework/Input/IDASHReceiverObserver.h"
#include "../libdashframework/Buffer/IBufferObserver.h"
#include "../libdashframework/Adaptation/IAdaptationLogic.h"
#include "../Decoder/IAudioObserver.h"
#include "../Decoder/IVideoObserver.h"
#include <vector>

namespace sampleplayer
{
    namespace managers
    {
        class MultimediaStream : public decoder::IAudioObserver, public decoder::IVideoObserver, public libdash::framework::input::IDASHReceiverObserver
        {
            public:
                MultimediaStream          (dash::mpd::IAdaptationSet *adaptationSet, libdash::framework::adaptation::IAdaptationLogic *logic, uint32_t bufferSize, void* breakpoint);
                virtual ~MultimediaStream   ();

                bool        Start                   ();
                void        Stop                    ();
                void*      Pause                      ();
                bool       Resume                     (void *breakpoint);
                void        StopDownload            ();
                bool        StartDecoding           ();
                bool        StartDownload           ();
                void        Clear                   ();
                uint32_t    GetPosition             ();
                uint32_t    GetBandWidth            ();
                void        AttachStreamObserver    (IStreamObserver *observer);
                void        AttachBufferObserver    (libdash::framework::buffer::IBufferObserver *observer);
                void        NotifyVideoObservers(void * data);
                void        NotifyAudioObservers(void * data);
                bool        CheckEosReached();
                bool        SetHttpHeaders(std::string &headers);
                virtual void OnAudioDataAvailable       (const uint8_t **data, decoder::audioFrameProperties* props);
                virtual void OnVideoDataAvailable       (const uint8_t **data, decoder::videoFrameProperties* props);
                virtual void OnSegmentDecodingStarted   ();
                virtual void OnSegmentDownloaded        ();
                virtual void OnBandWidthChanged      (uint32_t bw);
                virtual void OnEosReached();
                DecodingThread* GetDecodingThread();
                libdash::framework::input::DASHManager* GetReceiver();
            private:
                std::vector<IStreamObserver *>                      observers;
                dash::mpd::IAdaptationSet                           *adaptationSet;
                libdash::framework::adaptation::IAdaptationLogic    *logic;
                libdash::framework::input::DASHManager              *receiver;
                DecodingThread                                      *decodingThread;
                uint32_t                                            bufferSize;
                bool                                                eos;
                uint32_t                                            bandWidth;

                void Init (void* breakpoint);
        };
    }
}

#endif /* QTSAMPLEPLAYER_MANAGERS_MULTIMEDIASTREAM_H_ */
