/*
 **************************************************************************************
 *       Filename:  CameraDriverTest.h
 *    Description:  Camera Driver Test  header file
 *
 *        Version:  1.0
 *        Created:  2012-05-24 14:59:20
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERADRIVERTEST_H_INCLUDED
#define CAMERADRIVERTEST_H_INCLUDED

#include <errno.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/videodev2.h>

#define CAMERA_DEV_NAME  "/dev/video0"

#define MAX_PREVIEW_BUFFERS     6
#define MAX_SNAPSHOT_BUFFERS    1 //must be 1

struct cameraBuffer
{
    size_t  offset;
    void*   start;
    size_t  length;
};

struct cameraBuffer     mBufferPreview[MAX_PREVIEW_BUFFERS];
int mCameraFd;

#endif /*CAMERADRIVERTEST_H_INCLUDED*/

/********************************* END ***********************************************/

