/*
 * MediaObject.h
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_INPUT_MEDIAOBJECT_H_
#define LIBDASH_FRAMEWORK_INPUT_MEDIAOBJECT_H_

#include "IMPD.h"
#include "IDownloadObserver.h"
#include "../Portable/MultiThreading.h"

namespace libdash
{
    namespace framework
    {
        namespace input
        {
            enum MediaSegmentType
            {
                MEDIA_SEGMENT_TYPE_UNKNOWN = 0,
                MEDIA_SEGMENT_TYPE_INIT,
                MEDIA_SEGMENT_TYPE_NORMAL,
                MEDIA_SEGMENT_TYPE_EVENT
            };

            class MediaObject : public dash::network::IDownloadObserver
            {
                public:
                    MediaObject             (dash::mpd::ISegment *segment, dash::mpd::IRepresentation *rep);
                    MediaObject             (dash::mpd::ISegment *segment, dash::mpd::IRepresentation *rep, MediaSegmentType segmentType);
                    MediaObject             (int event);
                    virtual ~MediaObject    ();

                    bool    StartDownload   ();
                    void    AbortDownload   ();
                    void    PauseDownload();
                    void    WaitFinished    ();
                    bool    WaitDownloadFinished  ();
                    //return the data  len readed when this is a normal object, or return event
                    //when this is a event object.
                    int     Read            (uint8_t *data, size_t len);
                    int     Peek            (uint8_t *data, size_t len);

                    virtual void    OnDownloadStateChanged  (dash::network::DownloadState state);
                    virtual void    OnDownloadRateChanged   (uint32_t bandWidth, uint64_t bytesDownloaded);
                    virtual void    OnBytesDownloaded(dash::network::DownloadInfo &info);
                    virtual void    OnErrorHappened         (bool errorHappened);
                    void    AttachDownloadObserver  (dash::network::IDownloadObserver *observer);
                    void    DetachDownloadObserver  (dash::network::IDownloadObserver *observer);
                    bool    StartDownload                   (void *easyHandle, void *multiHandle);
                    uint32_t        GetDownloadBandWidth();
                    bool            ErrorHappened();
                    void            UpdateInfo();
                    bool            CheckDownloadFinished();
                    void            SetDownloadFinished(bool value);
                    dash::network::DownloadState GetDownloadState();
                    int              PeekEvent();
                    MediaSegmentType GetSegmentType();
                private:
                    dash::mpd::ISegment             *segment;
                    dash::mpd::IRepresentation      *rep;
                    dash::network::DownloadState    state;
                    uint64_t                        bytesDownloaded;
                    uint32_t                        bandWidth;
                    bool                            errorHappened;
                    bool                            downloadFinished;
                    int                              event;
                    MediaSegmentType        segType;
                    mutable CRITICAL_SECTION    stateLock;
                    mutable CONDITION_VARIABLE  stateChanged;
            };
        }
    }
}

#endif /* LIBDASH_FRAMEWORK_INPUT_MEDIAOBJECT_H_ */