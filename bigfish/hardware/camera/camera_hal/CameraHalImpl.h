/*
 **************************************************************************************
 *       Filename:  CameraHalImpl.h
 *    Description:  Camera Hal Impl header file
 *
 *        Version:  1.0
 *        Created:  2012-05-21 13:49:03
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include <errno.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <linux/videodev2.h>

#include "CameraTypes.h"
#include "CameraExtendedEnv.h"

#define CAMERA_DEV_NAME  "/dev/video0"

#define MAX_PREVIEW_BUFFERS     4
#define MAX_SNAPSHOT_BUFFERS    2
#define MAX_ERROR_COUNT         1000
#define CONNECT_ERROR_COUNT     100

namespace android {

class CameraHalImpl
{
public:
        CameraHalImpl(void *env);
        ~CameraHalImpl();

    int openCamera();
    int closeCamera();
    int startPreview();
    int stopPreview();
    int getPreview(struct previewBuffer * buffer);
    int getPreview(int *index);
    int queueFrame(int index);

    int getPicture(previewBuffer* buffer);
    int stopSnapshot();

private:
    int mPreviewWidth;
    int mPreviewHeight;
    int mPreviewFormat;

    int mSnapshotWidth;
    int mSnapshotHeight;
    int mSnapshotFormat;

    CameraExtendedEnv*      mEnv;
    struct cameraBuffer     mBufferPreview[MAX_PREVIEW_BUFFERS];      //preview buffer
    struct cameraBuffer     mBufferSnapshot[MAX_SNAPSHOT_BUFFERS];    //capture buffer

public:
    struct previewBuffer*   mPreviewBuffer;

private:
    int initCameraBuffers(struct cameraBuffer *buffer, int num);
    int deinitCameraBuffers(struct cameraBuffer *buffer,int num);
    int cameraSetFormat(int width, int height, int fmt);
    int cameraRequestBuffer(int fp, enum v4l2_buf_type type, int num);
    int cameraQueryBuffer(int fp, struct cameraBuffer *buffer, enum v4l2_buf_type type, int num);
    int cameraStreamOn(int fp,enum v4l2_buf_type buf_type);
    int cameraStreamOff(int fp,enum v4l2_buf_type buf_type);
    int cameraQueueBuffer(int fp, struct cameraBuffer *buffer, enum v4l2_buf_type type, int index);
    int cameraDequeueBuffer(int fp,enum v4l2_buf_type type);
    int cameraSetCtrl(int fp, unsigned int id, unsigned int value);
    int cameraSetParameter(int fp, int fps);
};

}; // namespace android

#endif /*CAMERA_H_INCLUDED*/

/********************************* END ***********************************************/

