/*
 **************************************************************************************
 *       Filename:  PipeMessage.cpp
 *    Description:  Pipe Message  source file
 *
 *        Version:  1.0
 *        Created:  2012-05-24 20:13:23
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "PipeMessage"
#include <utils/Log.h>

#include <errno.h>

#include "PipeMessage.h"
#include "CameraUtils.h"

namespace android {

/*
 **************************************************************************
 * FunctionName: PipeMessage::PipeMessage;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
PipeMessage::PipeMessage()
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    int fds[2];

    pipe(fds);
    mFdRead     = fds[0];
    mFdWrite    = fds[1];
}

/*
 **************************************************************************
 * FunctionName: PipeMessage::~PipeMessage;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
PipeMessage::~PipeMessage()
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    close(mFdRead);
    close(mFdWrite);
}

/*
 **************************************************************************
 * FunctionName: PipeMessage::get;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
/* will block */
int PipeMessage::get(int* msg)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    char *p         = (char *)msg;
    int read_bytes  = 0;
    int left_bytes  = sizeof(*msg);

    while(left_bytes)
    {
        read_bytes = read(mFdRead, p, left_bytes);
        if(read_bytes < 0)
        {
            CAMERA_HAL_LOGE("read() error: %s", strerror(errno));
            return -1;
        }
        else
        {
            left_bytes -= read_bytes;
            p += read_bytes;
        }
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: PipeMessage::put;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int PipeMessage::put(int* msg)
{
    CAMERA_HAL_LOGV("enter %s()", __FUNCTION__);

    char *p         = (char *)msg;
    int write_bytes = 0;
    int left_bytes  = sizeof(*msg);

    while(left_bytes)
    {
        write_bytes = write(mFdWrite, p, left_bytes);
        if(write_bytes < 0)
        {
            CAMERA_HAL_LOGE("write() error: %s", strerror(errno));
            return -1;
        }
        else
        {
            left_bytes -= write_bytes;
            p += write_bytes;
        }
    }

    return 0;
}

}; // namespace android

/********************************** END **********************************************/
