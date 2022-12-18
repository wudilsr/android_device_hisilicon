/*
 * IAdaptationLogic.h
 *****************************************************************************
 * Copyright (C) 2013, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#ifndef LIBDASH_FRAMEWORK_ADAPTATION_IADAPTATIONLOGIC_H_
#define LIBDASH_FRAMEWORK_ADAPTATION_IADAPTATIONLOGIC_H_

#include "../Input/MediaObject.h"
#include "IRepresentation.h"

namespace libdash
{
    namespace framework
    {
        namespace adaptation
        {
            enum LogicType
            {
                Manual,
                AlwaysLowest
            };

            enum SegmentType
            {
                SEG_TYPE_ALL = 0,
                SEG_TYPE_EVENT = (1 << 0),//urgent event , report as quickly as possible
            };

            //logic event  = (LOGIC_EVENT_XX | LOGIC_EVENT_DATA)
            #define LOGIC_EVENT_MASK (0xff000000)
            #define LOGIC_EVENT_DATA_MASK (0x00ffffff) // = (LOGIC_ERROR_TYPE_MASK | LOGIC_ERROR_CODE_MASK)
            //logic error = (LOGIC_EVENT_ERROR | LOGIC_ERROR_TYPE_XX | LOGIC_ERROR_CODE)
            #define LOGIC_ERROR_TYPE_MASK  (0x00ff0000)
            #define LOGIC_ERROR_CODE_MASK (0x0000ffff)

            enum LogicEvent
            {
                LOGIC_EVENT_NONE = 0,//normal object with segment in it.
                LOGIC_EVENT_PRE_INITSEGMENT = 0x10000000,//this is just a event show that a init segment will flow,this event is wrapped in mediaobject
                LOGIC_EVENT_EOS                      = 0x11000000,//this is just a event show that a eos happened,this event is wrapped in mediaobject
                LOGIC_EVENT_ERROR                   = 0x7f000000,
            };

            enum LogicErrorType
            {
                LOGIC_ERROR_TYPE_UNKNOWN = 0,
                LOGIC_ERROR_TYPE_HTTP = (1 << 16),//match the "LOGIC_ERROR_TYPE_MASK"
                LOGIC_ERROR_TYPE_STREAM_NOTAVAILABLE = (2 << 16),//match the "LOGIC_ERROR_TYPE_MASK"
            };

            enum LogicState
            {
                LOGIC_STATE_RUN  = 0,//normal state
                LOGIC_STATE_EOS
            };

            class IAdaptationLogic
            {
                public:
                    virtual ~IAdaptationLogic () {}

                    virtual input::MediaObject*     GetSegment          (int type)                                              = 0;
                    virtual uint32_t                GetPosition         ()                                              = 0;
                    virtual void                    SetPosition         (uint32_t segmentNumber)                        = 0;
                    virtual void                    SetRepresentation   (dash::mpd::IRepresentation *representation,  int index, bool invokeInigSeg)    = 0;
                    virtual int                    GetCurrentRepresentationIndex   ()    = 0;
                    virtual void                    InvokeInitSegment   (bool invoke)                                   = 0;
                    virtual LogicType               GetType             ()                                              = 0;
                    virtual void*                  Pause()                                                                      =0;
                    virtual bool                    Resume(void *breakpoints)                                         =0;
                    virtual bool                    isLive()                                                                       =0;
                    virtual int                      SetSAPs      (dash::mpd::IRepresentation *representation, std::vector<uint64_t> &saps)  = 0;
            };
        }
    }
}
#endif /* LIBDASH_FRAMEWORK_ADAPTATION_IADAPTATIONLOGIC_H_ */
