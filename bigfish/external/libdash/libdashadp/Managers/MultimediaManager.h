/*
 * MultimediaManager.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef QTSAMPLEPLAYER_MANAGERS_MULTIMEDIAMANAGER_H_
#define QTSAMPLEPLAYER_MANAGERS_MULTIMEDIAMANAGER_H_

#include "IMPD.h"
#include "MultimediaStream.h"
#include "../libdashframework/Adaptation/IAdaptationLogic.h"
#include "../libdashframework/Adaptation/AdaptationLogicFactory.h"
#include "../libdashframework/Buffer/IBufferObserver.h"
#include "AdaptationSetHelper.h"
#include "../../libdash/source/mpd/Segment.h"
#include "IMSPR.h"

namespace sampleplayer
{
    namespace managers
    {
        enum SubtitleType
        {
            Subtitle_UNSUPPROTED    = 0x00,
            Subtitle_TTML           = 0x01,     //TTML Subtitle is a xml plain file
            Subtitle_WEBVTT         = 0x02,     //HLS subtitle not supproted yet
            Subtitle_TX3G           = 0x04,     //3GPP Timed Text not supported yet
            Subtitle_CC             = 0x08,     //ClosedCaption not supported yet
        };

        const int Subtitle_ISO_Mask = 0x80;

        class BreakPoint
        {
            public:
                void *logicBreakPoint;
                void *streamBreakPoint;
        };

        class BreakPoints
        {
            public:
                std::vector<BreakPoint>                         videoBreakPoints;
                std::vector<BreakPoint>                         audioBreakPoints;
                std::vector<BreakPoint>                         subtitleBreakPoints;
        };

        enum MangerState
        {
            MANAGER_STATE_IDLE = 0,
            MANAGER_STATE_STOPPED,
            MANAGER_STATE_RUNNING
        };

        enum MANAGER_INVOKE
        {
            MANAGER_INVOKE_UNKNOWN = 0,
            MANAGER_INVOKE_SET_HTTP_HEADERS,
            MANAGER_INVOKE_BUTT
        };

        class MultimediaManager : public IStreamObserver
        {
            public:
                MultimediaManager           (void *breakpoint);
                virtual ~MultimediaManager  ();

                bool                Init    (const std::string& url, int *err);
                void                Start   ();
                void                Stop    ();
                bool                 Create ();
                void                 Destroy ();

                //must make sure that Pause()/Resume And ReadFrame can't be do in the same time.
                void *             Pause();
                bool                Resume(void *breakpoint);
                bool                StartVideo(int adaptationSetIndex);
                void                StopVideo(int adaptationSetIndex);
                bool                StartAudio(int adaptationSetIndex);
                void                StopAudio(int adaptationSetIndex);
                bool                StartSubtitle(int adaptationSetIndex);
                void                StopSubtitle(int adaptationSetIndex);
                dash::mpd::IMPD*    GetMPD  ();

                int  Invoke(MANAGER_INVOKE invokeID, void *arg);

                bool SetVideoQuality      (dash::mpd::IPeriod* period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation);
                bool SetAudioQuality      (dash::mpd::IPeriod* period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation);
                bool SetSubtitleQuality   (dash::mpd::IPeriod* period, dash::mpd::IAdaptationSet *adaptationSet, dash::mpd::IRepresentation *representation);
                bool SetVideoAdaptationLogic    (libdash::framework::adaptation::LogicType type);
                bool SetAudioAdaptationLogic    (libdash::framework::adaptation::LogicType type);

                void AttachVideoBufferObserver  (libdash::framework::buffer::IBufferObserver *videoBufferObserver);
                void AttachAudioBufferObserver  (libdash::framework::buffer::IBufferObserver *audioBufferObserver);

                void OnVideoSegmentDecodingStarted  ();
                void OnVideoSegmentDownloaded       ();

                void NotifyVideoObservers       ();
                void NotifyAudioObservers       ();

                void NotifyVideoBufferObservers ();
                void NotifyAudioBufferObservers ();

                libdash::framework::mpd::RepresentationStreamType GetRepresentationStreamType();
                uint32_t    GetVideoSegmentDuration();
                uint32_t    GetAudioSegmentDuration();
                uint32_t    GetSubtitleSegmentDuration();
                uint32_t    GetVideoSegmentDuration(int adaptationSetIndex);
                uint32_t    GetAudioSegmentDuration(int adaptationSetIndex);
                uint32_t    GetSubtitleSegmentDuration(int adaptationSetIndex);

                //get current presentation's segemnt end time in ms, position must be >=1, if return 0, the result is unbelievable.
                uint64_t    GetVideoSegmentEndTime(int adaptationSetIndex, uint32_t position);
                uint64_t    GetAudioSegmentEndTime(int adaptationSetIndex, uint32_t position);
                uint64_t    GetSubtitleSegmentEndTime(int adaptationSetIndex, uint32_t position);

                uint64_t    GetVideoSegmentStartTime(int adaptationSetIndex, uint32_t position);
                uint64_t    GetAudioSegmentStartTime(int adaptationSetIndex, uint32_t position);
                uint64_t    GetSubtitleSegmentStartTime(int adaptationSetIndex, uint32_t position);

                //ms is the time elapsed from the start of period
                uint32_t    GetVideoPositionFromTime(int adaptationSetIndex, int64_t ms, int direct);
                uint32_t    GetAudioPositionFromTime(int adaptationSetIndex, int64_t ms, int direct);
                uint32_t    GetSubtitlePositionFromTime(int adaptationSetIndex, int64_t ms, int direct);


                bool        IsISOFF();

                void *      GetVideoAVIOContext(int videoAdaptationSetIndex);
                void *      GetAudioAVIOContext(int audioAdaptationSetIndex);
                void *      GetSubtitleAVIOContext(int subtitleAdaptationSetIndex);

                bool        SetQuality();
                uint32_t    GetBandWidth();
                uint32_t    GetVideoBandWidth();
                uint32_t    GetAudioBandWidth();
                uint32_t    GetSubtitleBandWidth();

                int         CheckVideoCurrentIndex(uint32_t bandWidth);
                int         CheckAudioCurrentIndex(uint32_t bandWidth);
                int         CheckSubtitleCurrentIndex(uint32_t bandWidth);
                bool        IsLive();
                bool        IsStarted();
                int64_t     GetDuration();
                uint32_t    GetFetchTime();
                uint32_t    GetCheckTime();
                uint32_t    GetCurrentTime();

                uint32_t    GetVideoAdaptationSetNum();
                uint32_t    GetAudioAdaptationSetNum();
                uint32_t    GetSubtitleAdaptationSetNum();
                dash::mpd::IAdaptationSet  *GetVideoAdaptionSet(int adaptationSetIndex);
                dash::mpd::IAdaptationSet  *GetAudioAdaptionSet(int adaptationSetIndex);
                dash::mpd::IAdaptationSet  *GetSubtitleAdaptionSet(int adaptationSetIndex);

                uint32_t    GetVideoPosition();
                uint32_t    GetAudioPosition();
                uint32_t    GetSubtitlePosition();
                uint32_t    GetVideoPosition(int adaptationSetIndex);
                uint32_t    GetAudioPosition(int adaptationSetIndex);
                uint32_t    GetSubtitlePosition(int adaptationSetIndex);
                //set to 0xffffffff to start play from latest segment if live, from 0 if vod;set to other to start play from the specified position
                void        SetVideoPosition(int videoAdaptationSetIndex, uint32_t position);
                void        SetAudioPosition(int audioAdaptationSetIndex, uint32_t position);
                void        SetSubtitlePosition(int subtitleAdaptationSetIndex, uint32_t position);

                void        SetVideoIndex(int adaptationSetIndex,int representationIndex, bool invokeInitSegment);
                void        SetAudioIndex(int adaptationSetIndex,int representationIndex, bool invokeInitSegment);
                void        SetSubtitleIndex(int adaptationSetIndex,int representationIndex, bool invokeInitSegment);

                void        SetVideoRepresentation(int adaptationSetIndex,int representationIndex, bool invokeInitSegment);
                void        SetAudioRepresentation(int adaptationSetIndex,int representationIndex, bool invokeInitSegment);
                void        SetSubtitleRepresentation(int adaptationSetIndex,int representationIndex, bool invokeInitSegment);

                int           GetVideoCurrentPresentationIndex(int adaptationSetIndex);
                int           GetAudioCurrentPresentationIndex(int adaptationSetIndex);
                int           GetSubtitleCurrentPresentationIndex(int adaptationSetIndex);

                int           SetVideoRepresentationSAPs(int adaptationSetIndex, int representationIndex, std::vector<uint64_t> &saps);
                int           SetAudioRepresentationSAPs(int adaptationSetIndex, int representationIndex, std::vector<uint64_t> &saps);
                int           SetSubtitleRepresentationSAPs(int adaptationSetIndex, int representationIndex, std::vector<uint64_t> &saps);

                bool        VideoEosReached();
                bool        AudioEosReached();
                bool        SubtitleEosReached();
                bool        SetCurrentPeriod(dash::mpd::IPeriod *period);

                std::string&    GetVideoIndexSegment();
                std::string&    GetAudioIndexSegment();
                std::string&    GetSubtitleIndexSegment();
                std::string&    GetVideoRating();
                std::string&    GetAudioRating();
                std::string&    GetSubtitleRating();
                int             GetSubtitleType(int subtitleAdaptationSetIndex);
                void            Interrupt();
                std::string&    GetVideoSegmentURL(int videoAdaptationSetIndex, int videoRepresentationIndex, uint32_t position);
                std::string&    GetAudioSegmentURL(int audioAdaptationSetIndex, int audioRepresentationIndex, uint32_t position);
                std::string&    GetSubtitleSegmentURL(int subtitleAdaptationSetIndex, int subtitleRepresentationIndex, uint32_t position);
                dash::mpd::IPeriod *GetCurrentPeriod();
                bool            CheckUUID(std::string &uuid);
                std::string     GetPRO();
            private:
                dash::IDASHManager                                          *manager;
                dash::mpd::IMPD                                             *mpd;
                dash::mpd::IPeriod                                          *period;
                dash::mpd::IAdaptationSet                                   *videoAdaptationSet;
                dash::mpd::IRepresentation                                  *videoRepresentation;
                libdash::framework::adaptation::IAdaptationLogic            *videoLogic;
                MultimediaStream                                            *videoStream;
                dash::mpd::IAdaptationSet                                   *audioAdaptationSet;
                dash::mpd::IRepresentation                                  *audioRepresentation;
                libdash::framework::adaptation::IAdaptationLogic            *audioLogic;
                MultimediaStream                                            *audioStream;
                dash::mpd::IAdaptationSet                                   *subtitleAdaptationSet;
                dash::mpd::IRepresentation                                  *subtitleRepresentation;
                libdash::framework::adaptation::IAdaptationLogic            *subtitleLogic;
                MultimediaStream                                            *subtitleStream;

                std::vector<MultimediaStream *>                             videoStreams;
                std::vector<libdash::framework::adaptation::IAdaptationLogic *> videoLogics;
                std::vector<dash::mpd::IAdaptationSet *>                    videoAdaptationSets;

                std::vector<MultimediaStream *>                             audioStreams;
                std::vector<libdash::framework::adaptation::IAdaptationLogic *> audioLogics;
                std::vector<dash::mpd::IAdaptationSet *>                    audioAdaptationSets;

                std::vector<MultimediaStream *>                             subtitleStreams;
                std::vector<libdash::framework::adaptation::IAdaptationLogic *> subtitleLogics;
                std::vector<dash::mpd::IAdaptationSet *>                    subtitleAdaptationSets;

                std::vector<bool>                                                      videoForceInvokeInitSeg;
                std::vector<bool>                                                      audioForceInvokeInitSeg;
                std::vector<bool>                                                      subtitleForceInvokeInitSeg;

                std::vector<MangerState>                                           videoState;
                std::vector<MangerState>                                           audioState;
                std::vector<MangerState>                                           subtitleState;

                std::string                                                 videoRating;
                std::string                                                 audioRating;
                std::string                                                 subtitleRating;
                std::string                                                 indexSegmentURL;
                std::string                                                 segmentURL;
                std::string                                                 httpHeaders;

                bool                                                        isLive;
                bool                                                        isISOFF;
                std::vector<libdash::framework::buffer::IBufferObserver* >  videoBufferObservers;
                bool                                                        isStarted;
                uint64_t                                                    framesDisplayed;
                uint64_t                                                    videoSegmentsDecodingStarted;
                uint64_t                                                    videoSegmentsDownloaded;
                CRITICAL_SECTION                                            monitorMutex;

                std::vector<uint32_t>                               videoPosition;
                std::vector<uint32_t>                               audioPosition;
                std::vector<uint32_t>                               subtitlePosition;
                std::vector<int>                                       videoRepresentationIndexes;
                std::vector<int>                                       audioRepresentationIndexes;
                std::vector<int>                                       subtitleRepresentationIndexes;

                uint32_t                                                  bandWidth;
                int                                                         videoAdaptationSetIndex;
                int                                                         audioAdaptationSetIndex;
                int                                                         subtitleAdaptationSetIndex;
                BreakPoints                                             *breakpoints;

                void    InitSubtitleParsing ();
                void    DestroySubtitle();
                void    InitVideoRendering();
                void    InitAudioPlayback   ();
                void    DestroyVideo           ();
                void    DestroyAudio           ();
                bool    _SetCurrentPeriod(dash::mpd::IPeriod *period);
                int      InitAdaptionSets();
                int     _GetPresentationFromBandWidth(std::vector<dash::mpd::IRepresentation *> represenations, uint32_t bandWidth);
                bool   _findFFSignInAdaptationSet(dash::mpd::IAdaptationSet * adaptationSet);
                bool   _IsISOFF();

        };
    }
}

#endif /* QTSAMPLEPLAYER_MANAGERS_MULTIMEDIAMANAGER_H_ */
