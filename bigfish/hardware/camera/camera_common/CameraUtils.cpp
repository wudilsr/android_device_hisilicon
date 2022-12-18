/*
 **************************************************************************************
 *       Filename:  CameraUtils.cpp
 *    Description:  CameraUtils source file
 *
 *        Version:  1.0
 *        Created:  2012-05-16 09:33:28
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "CameraUtils"
#include <utils/Log.h>

#include <linux/videodev2.h>
#include <hardware/hardware.h>
#include <camera/CameraParameters.h>

#include "CameraUtils.h"
#include <fcntl.h>

namespace android {

/*
 **************************************************************************
 * FunctionName: convertFormat2V4L2Format;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int convertFormat2V4L2Format(const char *string)
{
    int format = V4L2_PIX_FMT_YUV420;

    if(string != NULL)
    {
        if (strcmp(string, CameraParameters::PIXEL_FORMAT_YUV422SP) == 0)
        {
            format = V4L2_PIX_FMT_YYUV;
        }
        else if (strcmp(string, CameraParameters::PIXEL_FORMAT_YUV422I) == 0)
        {
            format = V4L2_PIX_FMT_YUYV;
        }
        else if (strcmp(string, CameraParameters::PIXEL_FORMAT_YUV420P) == 0)
        {
            format = V4L2_PIX_FMT_YUV420;
        }
        else if (strcmp(string, CameraParameters::PIXEL_FORMAT_YUV420SP) == 0)
        {
            format = V4L2_PIX_FMT_NV12;
        }
        else if (strcmp(string, CameraParameters::PIXEL_FORMAT_RGB565) == 0)
        {
            format = V4L2_PIX_FMT_RGB565;
        }
        else if (strcmp(string, CameraParameters::PIXEL_FORMAT_JPEG) == 0)
        {
            format = V4L2_PIX_FMT_JPEG;
        }
        else
        {
            CAMERA_HAL_LOGW("invalid format, set it to default(V4L2_PIX_FMT_NV12)");
            format = V4L2_PIX_FMT_NV12;
        }
    }

    return format;
}

/*
 **************************************************************************
 * FunctionName: getPixelDepth;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
int getPixelDepth(int format)
{
    int depth = 0;

    switch (format)
    {
        case V4L2_PIX_FMT_RGB565:
            depth = 16;
            break;

        case V4L2_PIX_FMT_RGB24:
            depth = 24;
            break;

        case V4L2_PIX_FMT_NV12:
            depth = 12;
            break;

        case V4L2_PIX_FMT_NV21:
            depth = 12;
            break;

        case V4L2_PIX_FMT_YUV420:
            depth = 12;
            break;

        case V4L2_PIX_FMT_YUYV:
            depth = 16;
            break;

        case V4L2_PIX_FMT_YVYU:
            depth = 16;
            break;

        case V4L2_PIX_FMT_UYVY:
            depth = 16;
            break;

        case V4L2_PIX_FMT_VYUY:
            depth = 16;
            break;

        case V4L2_PIX_FMT_NV16:
            depth = 16;
            break;

        case V4L2_PIX_FMT_NV61:
            depth = 16;
            break;

        case V4L2_PIX_FMT_YUV422P:
            depth = 16;
            break;
        default:
            depth = 16;
            break;
    }

    return depth;
}

/*
 **************************************************************************
 * FunctionName: currentThreadId;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
pid_t getCurrentThreadId ( void )
{
    return syscall(__NR_gettid);
}

/*
 **************************************************************************
 * FunctionName: measureTime;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
unsigned long measureTime(nsecs_t start, nsecs_t stop)
{
    return (stop - start)/1000000;
}

}; // namespace android

/********************************** END **********************************************/
