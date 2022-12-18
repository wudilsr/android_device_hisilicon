/*
 * DASHManager.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_INPUT_DASHMANAGER_H_
#define LIBDASH_FRAMEWORK_INPUT_DASHMANAGER_H_

#include "IDataReceiver.h"
#include "../Buffer/MediaObjectBuffer.h"
#include "../Adaptation/IAdaptationLogic.h"

#include "IDASHReceiverObserver.h"
#include "IDownloadObserver.h"
#include "libdash.h"
#include <string>
#include <queue>
#include "CurlManager.h"
#include "ManualAdaptation.h"

namespace libdash
{
    namespace framework
    {
        namespace input
        {
             typedef enum
            {
                DASH_MANAGER_STATE_STOPPED = 0,
                DASH_MANAGER_STATE_REQUEST_STOP,
                DASH_MANAGER_STATE_RUN,
                DASH_MANAGER_STATE_REQUEST_PAUSE,
                DASH_MANAGER_STATE_PAUSED,
                DASH_MANAGER_STATE_EOS,
            }DASH_MANAGER_STATE;

            class DASHManagerBreakPoint
            {
                public:
                    uint32_t                                       downloadSegmentNum;
                    uint32_t                                       readSegmentNum;
                    buffer::MediaObjectBuffer               *buffer;
                    MediaObject *pausedMedia;
            };

            class DASHManager : public IDataReceiver,public dash::network::IDownloadObserver
            {
                public:
                    DASHManager        (uint32_t maxcapacity, adaptation::IAdaptationLogic *logic, void*breakpoint);
                    virtual ~DASHManager    ();

                    bool        Start                           ();
                    void        Stop                            ();
                    void *     Pause                     ();/*return breakpoint*/
                    bool        Resume                   (void *breakpoint);
                    uint32_t    GetPosition                     ();
                    void        Clear                           ();
                    void        AttachBufferObserver            (buffer::IBufferObserver *observer);
                    void        AttachDownloadObserver          (IDASHReceiverObserver *observer);
                    void        NotifySegmentDecodingStarted    ();
                    void        NotifySegmentDownloaded         ();
                    void        NotifyEos                       ();
                    void        NotifyBandwidth        (uint32_t bandWidth);
                    virtual int Read                            (uint8_t *buf, int buf_size);
                    void        Interrupt();
                    bool        isLive();
                    bool        SetHttpHeaders(std::string &headers);
                    virtual void    OnDownloadStateChanged  (dash::network::DownloadState state);
                    virtual void    OnBytesDownloaded(dash::network::DownloadInfo &info);
                    virtual void    OnErrorHappened         (bool errorHappened);

                private:
                    static uint32_t DOWNLOADSIZE;

                    std::vector<IDASHReceiverObserver *>    observers;
                    buffer::MediaObjectBuffer               *buffer;
                    buffer::MediaObjectBuffer               *eventBuffer;
                    uint32_t                                readSegmentNum;//this posiotion,not the count
                    uint32_t                                downloadSegmentNum;
                    uint32_t                                maxcapacity;
                    adaptation::IAdaptationLogic            *logic;
                    THREAD_HANDLE                           bufferingThread;
                    bool                                    isDownloading;
                    int                                      state;/*0-not care, 1-pausing, 2-paused*/
                    int                                      errcode;
                    mpd::RepresentationStreamType           representationStreamType;
                    CurlManager                             *mCurlmanager;
                    std::string                                 httpHeaders;
                    DASHManagerBreakPoint             *breakpoint;
                    MediaObject *pausedMedia;
                    std::deque<dash::network::DownloadInfo>    downloadInfoNodes;
                    uint32_t  totalDownloadBytes;
                    uint32_t  totalConsumedUS;
                    /* Thread that does the buffering of segments */
                    static void* DoBuffering (void *receiver);
                    bool DispatchMediaObject(MediaObject *media, bool force);
                    void CheckEvent();
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_INPUT_DASHMANAGER_H_ */