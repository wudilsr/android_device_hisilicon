/*
 **************************************************************************************
 *       Filename:  CameraDriverTest.cpp
 *    Description:  Camera Driver Test  source file
 *
 *        Version:  1.0
 *        Created:  2012-05-24 14:50:22
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

//#define LOG_NDEBUG 0
#define LOG_TAG "CameraDriverTest"
#include <utils/Log.h>

#include "CameraDriverTest.h"

#define TEST_FRAMES     100
#define PREVIEW_WIDTH   352
#define PREVIEW_HEIGHT  288

/*
 **************************************************************************
 * FunctionName: initYuvBuffers;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int initYuvBuffers(struct cameraBuffer *buffer, int num)
{
    ALOGV("enter %s()", __FUNCTION__);

    for (int i = 0; i < num; i++)
    {
        buffer[i].start = NULL;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: closeBuffers;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int closeBuffers(struct cameraBuffer *buffer,int num)
{
    ALOGV("enter %s()", __FUNCTION__);

    for (int i = 0; i < num; i++)
    {
        if (buffer[i].start)
        {
            munmap(buffer[i].start, buffer[i].length);
            buffer[i].start = NULL;
        }
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: cameraSetFormat;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraSetFormat(int width, int height, int fmt)
{
    ALOGV("%s", __FUNCTION__);

    int ret = 0;
    struct v4l2_format format;

	format.type                 = V4L2_BUF_TYPE_VIDEO_CAPTURE;
	format.fmt.pix.width        = width;
	format.fmt.pix.height       = height;
	format.fmt.pix.pixelformat  = fmt;

	ret = ioctl(mCameraFd, VIDIOC_S_FMT, &format);
	if(ret < 0)
	{
	    ALOGE("camera VIDIOC_S_FMT err! %s", strerror(errno));
        return -1;
	}

    return 0;
 
}

/*
 **************************************************************************
 * FunctionName: cameraRequestBuffer;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraRequestBuffer(int fp, enum v4l2_buf_type type, int num)
{
    ALOGV("%s", __FUNCTION__);

    int ret = 0;
    struct v4l2_requestbuffers req;

    memset(&req, 0, sizeof (req));
    req.count   = num;
    req.type    = type;
    req.memory  = V4L2_MEMORY_MMAP;

    if ((ret = ioctl(fp, VIDIOC_REQBUFS, &req)) < 0)
    {
        ALOGE("ERR(%s):VIDIOC_REQBUFS failed(error : %s)", __FUNCTION__, strerror(errno));
        return ret;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: cameraQueryBuffer;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraQueryBuffer(int fp, struct cameraBuffer *buffers, enum v4l2_buf_type type, int num)
{
    ALOGV("enter %s()", __FUNCTION__);

    int i   = 0;
    int ret = 0;
    struct v4l2_buffer v4l2_buf;

    for(i = 0; i < num; i++)
    {
        memset(&v4l2_buf, 0, sizeof(v4l2_buf));
        v4l2_buf.type = type;
        v4l2_buf.index = i;

        ret = ioctl(fp , VIDIOC_QUERYBUF, &v4l2_buf);
        if(ret < 0)
        {
            ALOGE("ERR(%s):VIDIOC_QUERYBUF failed", __FUNCTION__);
            return ret;
        }

        if(NULL == buffers[i].start)
        {
            buffers[i].length = (size_t) v4l2_buf.length;
            buffers[i].offset = (size_t) v4l2_buf.m.offset;
            if ((buffers[i].start = (char *) mmap(NULL, buffers[i].length, \
                    PROT_READ | PROT_WRITE, MAP_SHARED, \
                    fp, v4l2_buf.m.offset)) < 0)
            {
                ALOGE("ERR(%s):mmap() failed",__FUNCTION__);
                return -1;
            }
        }

        ALOGV("virt. addr[%d]: 0x%x", i, (unsigned int) buffers[i].start);
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: cameraStreamOn;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraStreamOn(int fp, enum v4l2_buf_type buf_type)
{
    ALOGV("enter %s()", __FUNCTION__);

    int ret = 0;
    enum v4l2_buf_type type = buf_type;

    ret = ioctl(fp, VIDIOC_STREAMON, &type);
    if (ret < 0)
    {
        ALOGE("ERR(%s):VIDIOC_STREAMON failed(error : %s)", __FUNCTION__, strerror(errno));
        return ret;
    }

    return ret;
}

/*
 **************************************************************************
 * FunctionName: cameraStreamOff;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraStreamOff(int fp, enum v4l2_buf_type buf_type)
{
    ALOGV("enter %s()", __FUNCTION__);

    int ret = 0;
    enum v4l2_buf_type type = buf_type;

    ret = ioctl(fp, VIDIOC_STREAMOFF, &type);
    if (ret < 0)
    {
        ALOGE("ERR(%s):VIDIOC_STREAMOFF failed(error:%s)", __FUNCTION__, strerror(errno));

        return ret;
    }

    return ret;
}

/*
 **************************************************************************
 * FunctionName: cameraQueueBuffer;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraQueueBuffer(int fp, struct cameraBuffer *buffer, enum v4l2_buf_type type, int index)
{
    ALOGV("%s", __FUNCTION__);

    struct v4l2_buffer buf;
    memset(&buf, 0, sizeof (buf));

    buf.type        = type;
    buf.memory      = V4L2_MEMORY_MMAP;
    buf.index       = index;

    if (ioctl(fp, VIDIOC_QBUF, &buf) < 0)
    {
        ALOGE("ERR(%s):VIDIOC_QBUF failed(error : %s)", __FUNCTION__, strerror(errno));
        return -1;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: cameraDequeueBuffer;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraDequeueBuffer(int fp, enum v4l2_buf_type type)
{
    ALOGV("enter %s()", __FUNCTION__);

    int ret = 0;
    struct v4l2_buffer v4l2_buf;

    memset(&v4l2_buf, 0, sizeof(v4l2_buf));
    v4l2_buf.type   = type;
    v4l2_buf.memory = V4L2_MEMORY_MMAP;

    ret = ioctl(fp, VIDIOC_DQBUF, &v4l2_buf);
    if (ret < 0)
    {
        ALOGE("ERR(%s):VIDIOC_DQBUF failed(error : %s)", __FUNCTION__, strerror(errno));
        return ret;
    }

    return v4l2_buf.index;
}

/*
 **************************************************************************
 * FunctionName: cameraSetCtrl;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int cameraSetCtrl(int fp, unsigned int id, unsigned int value)
{
    ALOGV("enter %s()", __FUNCTION__);

    int ret = 0;
    struct v4l2_control ctrl;

    ctrl.id     = id;
    ctrl.value  = value;

    ret = ioctl(fp, VIDIOC_S_CTRL, &ctrl);
    if (ret < 0)
    {
        ALOGE("ERR(%s):VIDIOC_S_CTRL failed", __FUNCTION__);
        return ret;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: startPreview;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int startPreview(int width, int height)
{
    ALOGV("enter %s()", __FUNCTION__);
    ALOGI("preview size %d x %d", width, height);
    printf("preview size %d x %d\n", width, height);

    int i   = 0;
    int ret = 0;

    initYuvBuffers(mBufferPreview, MAX_PREVIEW_BUFFERS);

    ret = cameraSetFormat(width, height, V4L2_PIX_FMT_YUYV);
    if(ret < 0)
    {
        ALOGE("fail to set preview format to camera driver");
        return ret;
    }

    ret = cameraRequestBuffer(mCameraFd, V4L2_BUF_TYPE_VIDEO_CAPTURE, MAX_PREVIEW_BUFFERS);
    if(ret < 0)
    {
        ALOGE("fail to request buffers from camera driver");
        return ret;
    }

    ret = cameraQueryBuffer(mCameraFd, mBufferPreview, V4L2_BUF_TYPE_VIDEO_CAPTURE, MAX_PREVIEW_BUFFERS);
    if(ret < 0)
    {
        ALOGE("fail to query buffer from driver");
        return ret;
    }
    
    for(i = 0; i < MAX_PREVIEW_BUFFERS; i++)
    {
        ret = cameraQueueBuffer(mCameraFd, mBufferPreview, V4L2_BUF_TYPE_VIDEO_CAPTURE, i);
        if(ret < 0)
        {
            ALOGE("fail to queue buffer[%d] to driver", i);
            return ret;
        }
    }

    ret = cameraStreamOn(mCameraFd, V4L2_BUF_TYPE_VIDEO_CAPTURE);
    if(ret < 0)
    {
        ALOGE("fail to start preview");
        return ret;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: stopPreview;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int stopPreview(void)
{
    ALOGV("enter %s()", __FUNCTION__);

    int ret = 0;

    ret = cameraStreamOff(mCameraFd, V4L2_BUF_TYPE_VIDEO_CAPTURE);
    if(ret < 0)
    {
        ALOGE("fail to stop preview");
    }

    closeBuffers(mBufferPreview, MAX_PREVIEW_BUFFERS);

    return 0;
}

/*
 **************************************************************************
 * FunctionName: getPreview;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int getPreview(int *index)
{
    ALOGV("enter %s()", __FUNCTION__);

    int ret = 0;
    struct v4l2_buffer v4l2_buf;

    memset(&v4l2_buf, 0, sizeof(v4l2_buf));
    v4l2_buf.type   = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    v4l2_buf.memory = V4L2_MEMORY_MMAP;

    ret = ioctl(mCameraFd, VIDIOC_DQBUF, &v4l2_buf);
    if (ret < 0)
    {
        ALOGE("fail to dequeue buffer from driver:%s",strerror(errno));
        return ret;
    }

    *index = v4l2_buf.index;

    return 0;
}

/*
 **************************************************************************
 * FunctionName: queueFrame;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int queueFrame(int index)
{
    ALOGV("enter %s()", __FUNCTION__);

    struct v4l2_buffer buf;

    memset(&buf, 0, sizeof (buf));
    buf.type     = V4L2_BUF_TYPE_VIDEO_CAPTURE;
    buf.memory   = V4L2_MEMORY_MMAP;
    buf.index    = index;

    if (ioctl (mCameraFd, VIDIOC_QBUF, &buf) < 0)
    {
        ALOGE("fail to queue buffer to driver");
        return -1;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: openCameraDevice;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int openCameraDevice()
{
    ALOGV("enter %s()", __FUNCTION__);

    mCameraFd = open(CAMERA_DEV_NAME, O_RDWR);
    if (mCameraFd < 0)
    {
        ALOGE("open(%s) failed[%s]", CAMERA_DEV_NAME, strerror(errno));
        return mCameraFd;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: closeCameraDevice;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int closeCameraDevice()
{
    ALOGV("enter %s()", __FUNCTION__);

    if(mCameraFd >= 0)
    {
        close(mCameraFd);
        mCameraFd = -1;
    }

    return 0;
}

/*
 **************************************************************************
 * FunctionName: previewTest;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int previewTest()
{
    ALOGV("enter %s()", __FUNCTION__);
    
    ALOGI("================================");
    printf("================================\n");
    ALOGI("start preview test");
    printf("start preview test\n");

    int i       = 0;
    int ret     = 0;
    int index   = 0;

    ret = openCameraDevice();
    if(ret < 0)
    {
        goto ON_ERROR;
    }

    ret = startPreview(PREVIEW_WIDTH, PREVIEW_HEIGHT);
    if(ret < 0)
    {
        goto ON_ERROR;
    }

    while(i < TEST_FRAMES)
    {
        ret = getPreview(&index);
        if(ret < 0)
        {
            goto ON_ERROR;
        }

        ret = queueFrame(index);
        if(ret < 0)
        {
            goto ON_ERROR;
        }

        i++;
    }

    stopPreview();

    closeCameraDevice();

    ALOGI("preview test OK");
    printf("preview test OK\n");

    return 0;

ON_ERROR:

    ALOGI("preview test FAIL");
    printf("preview test FAIL\n");

    return ret;
}

/*
 **************************************************************************
 * FunctionName: previewSizeSwitchTest;
 * Description : NA;
 * Input       : NA;
 * Output      : NA;
 * ReturnValue : NA;
 * Other       : NA;
 **************************************************************************
 */
static int previewSizeSwitchTest()
{
    ALOGV("enter %s()", __FUNCTION__);

    ALOGI("================================");
    printf("================================\n");
    ALOGI("start preview size switch test");
    printf("start preview size switch test\n");

    int i       = 0;
    int ret     = 0;
    int index   = 0;

    ret = openCameraDevice();
    if(ret < 0)
    {
        goto ON_ERROR;
    }

    ret = startPreview(PREVIEW_WIDTH, PREVIEW_HEIGHT);
    if(ret < 0)
    {
        goto ON_ERROR;
    }

    while(i < TEST_FRAMES)
    {
        ret = getPreview(&index);
        if(ret < 0)
        {
            goto ON_ERROR;
        }

        ret = queueFrame(index);
        if(ret < 0)
        {
            goto ON_ERROR;
        }

        i++;
    }

    stopPreview();

    closeCameraDevice();

    ret = openCameraDevice();
    if(ret < 0)
    {
        goto ON_ERROR;
    }

    ret = startPreview(640, 480);
    if(ret < 0)
    {
        goto ON_ERROR;
    }

    i = 0;
    while(i < TEST_FRAMES)
    {
        ret = getPreview(&index);
        if(ret < 0)
        {
            goto ON_ERROR;
        }

        ret = queueFrame(index);
        if(ret < 0)
        {
            goto ON_ERROR;
        }

        i++;
    }

    stopPreview();

    closeCameraDevice();

    ALOGI("preview size switch test OK");
    printf("preview size switch test OK\n");
    ALOGI("================================");
    printf("================================\n");

    return 0;

ON_ERROR:

    ALOGI("preview size switch test FAIL");
    printf("preview size switch test FAIL\n");
    ALOGI("================================");
    printf("================================\n");

    return ret;
}

int main()
{
    previewTest();
    
    previewSizeSwitchTest();

    return 0;
}

/********************************** END **********************************************/
