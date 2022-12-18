
/*
 * Copyright (c) (2014 - ...) Device Chipset Source Algorithm and Chipset Platform Development Dept
 * Hisilicon. All rights reserved.
 *
 * File:    drv_omxvdec.h
 *
 * Purpose: omxvdec export header file
 *
 * Author:  yangyichang 00226912
 *
 * Date:    26, 11, 2014
 *
 * NOTICE !!
 * 该文件同时被component 和driver 引用
 * 如修改，两边均需重新编译!!!
 */

#ifndef __DRV_OMXVDEC_H__
#define __DRV_OMXVDEC_H__

#include <linux/ioctl.h>

#include "vfmw.h"
#include "hi_drv_video.h"  //主要是输出颜色空间枚举


#define OMXVDEC_VERSION	 		        (2015032400)

#define OMXVDEC_NAME                    "hi_omxvdec"
#define DRIVER_PATH                     "/dev/hi_omxvdec"

#define PATH_LEN                        (64)
#define NAME_LEN                        (64)

#define MAX(a, b)                       (((a) > (b)) ?  (a) : (b))
#define MIN(a, b)                       (((a) > (b)) ?  (b) : (a))

#define UHD_FRAME_WIDTH	                (4096) 
#define UHD_FRAME_HEIGHT                (2304)
#define HD_FRAME_WIDTH                  (1920) 
#define HD_FRAME_HEIGHT                 (1088)
#define SD_FRAME_WIDTH                  (1280) 
#define SD_FRAME_HEIGHT                 (736)

#define SD_HEVC_FRAME_HEIGHT            (768)

#define MAX_SUPPORT_WIDTH               (UHD_FRAME_WIDTH)
#define MAX_SUPPORT_HEIGHT              (UHD_FRAME_HEIGHT)

#define DEFAULT_FRAME_WIDTH             (HD_FRAME_WIDTH)
#define DEFAULT_FRAME_HEIGHT            (HD_FRAME_HEIGHT)

#define FRAME_SIZE(w, h)                (((w)*(h)*3)/2)

enum {
	VDEC_S_SUCCESS = 0,
	VDEC_S_FAILED  = 1,
};

/* omxvdec msg response types */ 
#define VDEC_MSG_RESP_BASE              (0x10000)
#define VDEC_MSG_RESP_OPEN              (VDEC_MSG_RESP_BASE + 0x1)
#define VDEC_MSG_RESP_START_DONE        (VDEC_MSG_RESP_BASE + 0x2)
#define VDEC_MSG_RESP_STOP_DONE         (VDEC_MSG_RESP_BASE + 0x3)
#define VDEC_MSG_RESP_PAUSE_DONE        (VDEC_MSG_RESP_BASE + 0x4)
#define VDEC_MSG_RESP_RESUME_DONE       (VDEC_MSG_RESP_BASE + 0x5)
#define VDEC_MSG_RESP_FLUSH_INPUT_DONE  (VDEC_MSG_RESP_BASE + 0x6)
#define VDEC_MSG_RESP_FLUSH_OUTPUT_DONE (VDEC_MSG_RESP_BASE + 0x7)
#define VDEC_MSG_RESP_INPUT_DONE        (VDEC_MSG_RESP_BASE + 0x8)
#define VDEC_MSG_RESP_OUTPUT_DONE       (VDEC_MSG_RESP_BASE + 0x9)
#define VDEC_MSG_RESP_MSG_STOP_DONE     (VDEC_MSG_RESP_BASE + 0xa)

/* omxvdec error code types */
#define VDEC_S_ERR_BASE                 (0x20000)
#define VDEC_ERR_FAIL                   (VDEC_S_ERR_BASE + 0x01)
#define VDEC_ERR_DYNAMIC_ALLOC_FAIL     (VDEC_S_ERR_BASE + 0x02)
#define VDEC_ERR_ILLEGAL_OP             (VDEC_S_ERR_BASE + 0x03)
#define VDEC_ERR_ILLEGAL_PARM           (VDEC_S_ERR_BASE + 0x04)
#define VDEC_ERR_BAD_POINTER            (VDEC_S_ERR_BASE + 0x05)
#define VDEC_ERR_BAD_HANDLE             (VDEC_S_ERR_BASE + 0x06)
#define VDEC_ERR_NOT_SUPPORTED          (VDEC_S_ERR_BASE + 0x07)
#define VDEC_ERR_BAD_STATE              (VDEC_S_ERR_BASE + 0x08)
#define VDEC_ERR_BUSY                   (VDEC_S_ERR_BASE + 0x09)
#define VDEC_ERR_HW_FATAL               (VDEC_S_ERR_BASE + 0x0a)
#define VDEC_ERR_BITSTREAM_ERR          (VDEC_S_ERR_BASE + 0x0b)
#define VDEC_ERR_QEMPTY                 (VDEC_S_ERR_BASE + 0x0c)
#define VDEC_ERR_QFULL                  (VDEC_S_ERR_BASE + 0x0d)
#define VDEC_ERR_INPUT_NOT_PROCESSED    (VDEC_S_ERR_BASE + 0x0e)
#define VDEC_ERR_INDEX_NOMORE           (VDEC_S_ERR_BASE + 0x0f)

#define VDEC_EVT_REPORT_BASE            (0x30000)
#define VDEC_EVT_REPORT_IMG_SIZE_CHG	(VDEC_EVT_REPORT_BASE + 0x1)
#define VDEC_EVT_REPORT_FRAME_RATE_CHG	(VDEC_EVT_REPORT_BASE + 0x2)
#define VDEC_EVT_REPORT_SCAN_TYPE_CHG	(VDEC_EVT_REPORT_BASE + 0x3)
#define VDEC_EVT_REPORT_HW_ERROR        (VDEC_EVT_REPORT_BASE + 0x4)
#define VDEC_EVT_REPORT_CROP_RECT_CHG	(VDEC_EVT_REPORT_BASE + 0x5)

/* ========================================================
 * IOCTL for interaction with omx components
 * ========================================================*/
typedef struct {
	HI_S32 chan_num;
	void  *in;
	void  *out;
}OMXVDEC_IOCTL_MSG;

#define VDEC_IOCTL_MAGIC 'v'

#define VDEC_IOCTL_CHAN_CREATE   \
	_IOWR(VDEC_IOCTL_MAGIC, 1, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_RELEASE  \
	_IOW(VDEC_IOCTL_MAGIC, 2, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_SET_EXTRADATA \
	_IOW(VDEC_IOCTL_MAGIC, 3, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_GET_EXTRADATA \
	_IOR(VDEC_IOCTL_MAGIC, 4, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_GET_PORT_PRO \
	_IOR(VDEC_IOCTL_MAGIC, 5, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_SET_PORT_PRO \
	_IOW(VDEC_IOCTL_MAGIC, 6, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_FLUSH_PORT \
	_IOW(VDEC_IOCTL_MAGIC, 7, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_BIND_BUFFER \
	_IOWR(VDEC_IOCTL_MAGIC, 8, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_UNBIND_BUFFER \
	_IOWR(VDEC_IOCTL_MAGIC, 9, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_FILL_OUTPUT_FRAME \
	_IOWR(VDEC_IOCTL_MAGIC, 10, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_EMPTY_INPUT_STREAM \
	_IOWR(VDEC_IOCTL_MAGIC, 11, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_START \
	_IOW(VDEC_IOCTL_MAGIC, 12, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_STOP  \
	_IOW(VDEC_IOCTL_MAGIC, 13, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_PAUSE \
	_IOW(VDEC_IOCTL_MAGIC, 14, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_RESUME \
	_IOW(VDEC_IOCTL_MAGIC, 15, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_GET_MSG \
	_IOR(VDEC_IOCTL_MAGIC, 16, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_STOP_MSG \
	_IOW(VDEC_IOCTL_MAGIC, 17, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_GET_NUMBER_INSTANCES \
	_IOR(VDEC_IOCTL_MAGIC, 18, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_SET_PICTURE_ORDER \
	_IOW(VDEC_IOCTL_MAGIC, 19, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_SET_FRAME_RATE \
	_IOW(VDEC_IOCTL_MAGIC, 20, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_SET_DECODE_MODE \
	_IOW(VDEC_IOCTL_MAGIC, 21, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_SET_PIC_SIZE	\
	_IOW(VDEC_IOCTL_MAGIC, 22, OMXVDEC_IOCTL_MSG)

#define VDEC_IOCTL_CHAN_GET_PIC_SIZE	\
	_IOW(VDEC_IOCTL_MAGIC, 23, OMXVDEC_IOCTL_MSG)

/* ========================================================
 * internal struct enum definition
 * ========================================================*/ 
typedef enum {
    PORT_DIR_INPUT,
    PORT_DIR_OUTPUT,
    PORT_DIR_BOTH = 0xFFFFFFFF
}ePORT_DIR;

typedef enum {
    OMX_ALLOCATE_TYPE,
    OMX_USE_TYPE,
    OMX_USE_NATIVE_TYPE,
    OMX_ALLOCATE_SECURE_TYPE,
    OMX_BUTT_TYPE,
}eBUFFER_TYPE;

typedef VID_STD_E  VDEC_CODEC_TYPE;

/* CodecType Relative */
typedef enum {
    STD_WMV = STD_END_RESERVED + 1,
    STD_MJPEG,
    STD_EXT_RESERVED,
}OMXVDEC_CODEC_EXT;

typedef struct {
    HI_U32           cfg_width;
    HI_U32           cfg_height;
    HI_U32           cfg_stride;
    HI_U32           cfg_inbuf_num;
    HI_U32           cfg_outbuf_num;
    HI_U32           cfg_color_format;
    VDEC_CHAN_CFG_S  chan_cfg;
}OMXVDEC_DRV_CFG;

typedef struct {
    HI_S32           video_driver_fd;
    HI_S32           chan_handle;
    OMXVDEC_DRV_CFG  drv_cfg;
    HI_VOID*         yuv_fp;
    HI_U8*           chrom_l;
    HI_U32           chrom_l_size;
}OMXVDEC_DRV_CONTEXT;

/* video frame buffer description */
typedef struct {
    HI_U32   phyaddr_Y;
    HI_U32   phyaddr_C;
    HI_U32   stride;
    HI_U32   width;
    HI_U32   height;
    HI_BOOL  save_yuv;
    HI_CHAR  save_path[PATH_LEN];
}OMXVDEC_FRAME_S;

typedef struct {
	HI_U32           phyaddr;
	HI_U32           buffer_len;
	HI_U32           data_offset;
	HI_U32           data_len;
	HI_U32           flags;
	HI_S64           timestamp;
	eBUFFER_TYPE     buffer_type;
	ePORT_DIR        dir;
	HI_VOID         *bufferaddr;
	HI_VOID         *client_data;
    OMXVDEC_FRAME_S  out_frame;
}OMXVDEC_BUF_DESC;

typedef struct {
	HI_U32 frame_width;
	HI_U32 frame_height;
	HI_U32 frame_stride;
}OMXVDEC_IMG_SIZE;

typedef union {
	OMXVDEC_BUF_DESC buf;
	OMXVDEC_IMG_SIZE img_size;
}OMXVDEC_MSG_DATA;

typedef struct {
	HI_U32           status_code;
	HI_U32           msgcode;
	OMXVDEC_MSG_DATA msgdata;
	HI_U32           msgdatasize;
}OMXVDEC_MSG_INFO;

#endif

