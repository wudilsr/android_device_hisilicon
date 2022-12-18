/**
 *  @class      dash::network::IDownloadObserver
 *  @brief      This interface is needed for informing the application of the state of the download process.
 *  @details    Informs the application about the download rate and the state of the download.
 *
 *  @author     bitmovin Softwareentwicklung OG \n
 *              Email: libdash-dev@vicky.bitmovin.net
 *  @version    2.1
 *  @date       2013
 *  @copyright  bitmovin Softwareentwicklung OG, All Rights Reserved \n\n
 *              This source code and its use and distribution, is subject to the terms
 *              and conditions of the applicable license agreement.
 */

#ifndef IDOWNLOADOBSERVER_H_
#define IDOWNLOADOBSERVER_H_

#include "config.h"

namespace dash
{
    namespace network
    {
        enum DownloadState
        {
            NOT_STARTED     = 0,
            IN_PROGRESS     = 1,
            REQUEST_ABORT   = 2,
            ABORTED         = 3,
            COMPLETED       = 4,
            REQUEST_PAUSE   = 5,
            PAUSED         = 6,
        };
        class DownloadInfo
        {
            public:
                uint32_t downloadBytes;
                uint32_t consumedUS;
        };

        class IDownloadObserver
        {
            public:
                virtual ~IDownloadObserver(){}
#if 0
                /**
                 *  Informs the dash::network::IDownloadObserver object that the download rate has changed.
                 *  @param      bytesDownloaded     the number of downloaded bytes
                 *  @param      bandWidth           the current bandwidth bit/s
                 */
                virtual void OnDownloadRateChanged  (uint32_t bandWidth, uint64_t bytesDownloaded)        = 0;
#endif
                virtual void OnBytesDownloaded(DownloadInfo &info)   = 0;

                virtual void OnErrorHappened        (bool errorHappened)        = 0;
                /**
                 *  Informs the dash::network::IDownloadObserver object that the download state has changed.
                 *  @param      state               the download state
                 */
                virtual void OnDownloadStateChanged (DownloadState state)       = 0;
        };
    }
}

#endif /* IDOWNLOADOBSERVER_H_ */