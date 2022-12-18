/*
 **************************************************************************************
 *       Filename:  CapabilityManager.h
 *    Description:  Camera Capability Manager header file
 *
 *        Version:  1.0
 *        Created:  2012-05-11 18:05:57
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAPABILITYMANAGER_H_INCLUDED
#define CAPABILITYMANAGER_H_INCLUDED

#include <utils/Vector.h>
#include <linux/videodev2.h>
#include <camera/CameraParameters.h>

#include "CameraObject.h"
#include "CapabilityInterface.h"
#include "CameraExtendedEnv.h"

namespace android
{

#define DEFAULT_CAMERA_THUMBNAIL_WIDTH                  200
#define DEFAULT_CAMERA_THUMBNAIL_HEIGHT                 200
#define DEFAULT_CAMERA_JPEG_QUALITY                     100
#define DEFAULT_CAMERA_THUMBNAIL_QUALITY                100
#define DEFAULT_CAMERA_MAX_PREVIEW_FPS                  30
#define DEFAULT_CAMERA_PREVIEW_FORMAT                   CameraParameters::PIXEL_FORMAT_YUV420SP
#define DEFAULT_CAMERA_VIDEO_FORMAT                     "yuv420sp"
#define DEFAULT_CAMERA_PREVIEW_V4L2_FORMAT              V4L2_PIX_FMT_YUYV
#define DEFAULT_CAMERA_SNAPSHOT_V4L2_FORMAT             V4L2_PIX_FMT_YUYV

typedef struct
{
    unsigned int width;
    unsigned int height;
}resolution;

//preview size list
static resolution previewSizes[] =
{
    { 1920, 1080 },
    { 1280, 960  },
    { 1280, 720  },
    { 960,  540  },
    { 800,  480  },
    { 720,  480  },
    { 704,  576  },
    { 640,  480  },
    { 352,  288  },
    { 320,  240  },
    { 176,  144  },
};
#define PREVIEW_SIZE_COUNT (sizeof(previewSizes)/sizeof(resolution))

//picture size list
static resolution pictureSizes[] =
{
    { 2592, 1936 },
    { 2048, 1536 },
    { 1920, 1080 },
    { 1280, 960  },
    { 1280, 720  },
    { 960,  540  },
    { 800,  480  },
    { 720,  480  },
    { 704,  576  },
    { 640,  480  },
    { 352,  288  },
    { 320,  240  },
    { 176,  144  },
};
#define PICTURE_SIZE_COUNT (sizeof(pictureSizes)/sizeof(resolution))


class CapabilityManager : public CameraObject
{
public:
    /* constructor */
    CapabilityManager(void *env);
    ~CapabilityManager();

    /* return all capablities of current camera device */
    int     queryCap(CameraParameters& p);

    /* set parameters to the CameraParameterManager, but not really be set to device */
    int     setParam(CameraParameters& p);

    /* Set all changed parameters to device */
    int     commitParam( void );

private:
    int     registerAllCapInterface(void);

private:
    Vector<CapabilityInterface*> mParametersObjs;
};

};  /* namespace android */

#endif /*CAPABILITYMANAGER_H_INCLUDED*/

/********************************* END ***********************************************/
