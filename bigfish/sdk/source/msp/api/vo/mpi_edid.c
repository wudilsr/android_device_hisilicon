/******************************************************************************

   Copyright (C), 2001-2012, Hisilicon Tech. Co., Ltd.

******************************************************************************
	File Name     : mpi_edid.c
	Version       : Initial Draft
	Author        : Hisilicon TC group
	Created       : 2012/05/26
	Description   :
	History       :
	1.1Date       : 2012/07/16
	Author	      : l214567
	Modification  : Created file

*******************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>

#include "list.h"
//#include "priv_i2c.h"
#include "hi_unf_common.h"
#include "mpi_priv_edid.h"
#include "hi_unf_hdmi.h"
#include "hi_mpi_edid.h"

#define EDID_EST_TIMINGS1   17
#define EDID_EST_TIMINGS3   44
#define EDID_DMT_TIMINGS    30
#define EDID_STD_TIMINGS1   8
#define EDID_STD_TIMINGS2   6
#define EDID_DETAILED_TIMINGS 4

#define EDID_BLOCK_LENG 128


#define EDID_COLOR_TMP_BASE 0x3F800000

static struct MPI_SIMPLE_TIMING_S g_stVideoTimingCEA[] =
{
    /*{Identification Code, u32Hact, v_pixels, Frame Rate,Scan Type,                   Aspect Ratio, Pixel Repetition} */
    {HI_UNF_EDID_TIMING_TYPE_861,       0,    0,   0,  HI_TRUE,   0, 0, 0},
    {HI_UNF_EDID_TIMING_TYPE_861,     640,  480,  60,  HI_TRUE,   4, 3, 0},  /* 1:  640x480p   @ 59.94Hz/60Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480,  60,  HI_TRUE,   4, 3, 0},  /* 2:  720x480p   @ 59.94Hz/60Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480,  60,  HI_TRUE,  16, 9, 0},  /* 3:  720x480p   @ 59.94Hz/60Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280,  720,  60,  HI_TRUE,  16, 9, 0},  /* 4:  1280x720p  @ 59.94Hz/60Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  60,  HI_FALSE,  16, 9, 0},  /* 5:  1920x1080i @ 59.94Hz/60Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480,  60,  HI_FALSE,   4, 3, 1},  /* 6:  720(1440)x480i @ 59.94Hz/60Hz pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480,  60,  HI_FALSE,  16, 9, 1},  /* 7:  720(1440)x480i @ 59.94Hz/60Hz pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  240,  60,  HI_TRUE,   4, 3, 1},  /* 8:  720(1440)x240p @ 59.94Hz/60Hz pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  240,  60,  HI_TRUE,  16, 9, 1},  /* 9:  720(1440)x240p @ 59.94Hz/60Hz pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  480,  60,  HI_FALSE,   4, 3, 1},  /* 10: 2880x480i  @ 59.94Hz/60Hz     pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  480,  60,  HI_FALSE,  16, 9, 1},  /* 11: 2880x480i  @ 59.94Hz/60Hz     pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  240,  60,  HI_TRUE,   4, 3, 1},  /* 12: 2880x240p  @ 59.94Hz/60Hz     pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  240,  60,  HI_TRUE,  16, 9, 1},  /* 13: 2880x240p  @ 59.94Hz/60Hz     pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1440,  480,  60,  HI_TRUE,   4, 3, 1},  /* 14: 1440x480p  @ 59.94Hz/60Hz     pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1440,  480,  60,  HI_TRUE,  16, 9, 1},  /* 15: 1440x480p  @ 59.94Hz/60Hz     pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  60,  HI_TRUE,  16, 9, 0},  /* 16: 1920x1080p @ 59.94Hz/60Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  576,  50,  HI_TRUE,   4, 3, 0},  /* 17: 720x576p   @ 50Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  576,  50,  HI_TRUE,  16, 9, 0},  /* 18: 720x576p   @ 50Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280,  720,  50,  HI_TRUE,  16, 9, 0},  /* 19: 1280x720p  @ 50Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  50,  HI_FALSE,  16, 9, 0},  /* 20: 1920x1080i @ 50Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  576,  50,  HI_FALSE,   4, 3, 1},  /* 21: 720(1440)x576i @ 50Hz         pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  576,  50,  HI_FALSE,  16, 9, 1},  /* 22: 720(1440)x576i @ 50Hz         pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  288,  50,  HI_TRUE,   4, 3, 1},  /* 23: 720(1440)x288p @ 50Hz         pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  288,  50,  HI_TRUE,  16, 9, 1},  /* 24: 720(1440)x288p @ 50Hz         pixel sent 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2880,  576,  50,  HI_FALSE,   4, 3, 1},  /* 25: 2880x576i  @ 50Hz             pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2880,  576,  50,  HI_FALSE,  16, 9, 1},  /* 26: 2880x576i  @ 50Hz             pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2880,  288,  50,  HI_TRUE,   4, 3, 1},  /* 27: 2880x288p  @ 50Hz             pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2880,  288,  50,  HI_TRUE,  16, 9, 1},  /* 28: 2880x288p  @ 50Hz             pixel sent 1 to 10 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1440,  576,  50,  HI_TRUE,   4, 3, 1},  /* 29: 1440x576p  @ 50Hz             pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1440,  576,  50,  HI_TRUE,  16, 9, 1},  /* 30: 1440x576p  @ 50Hz             pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  50,  HI_TRUE,  16, 9, 0},  /* 31: 1920x1080p @ 50Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  24,  HI_TRUE,  16, 9, 0},  /* 32: 1920x1080p @ 23.98Hz/24Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  25,  HI_TRUE,  16, 9, 0},  /* 33: 1920x1080p @ 25Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  30,  HI_TRUE,  16, 9, 0},  /* 34: 1920x1080p @ 29.98Hz/30Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  480,  60,  HI_TRUE,   4, 3, 1},  /* 35: 2880x480p  @ 59.94Hz/60Hz     pixel sent 1, 2 or 4 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  480,  60,  HI_TRUE,  16, 9, 1},  /* 36: 2880x480p  @ 59.94Hz/60Hz     pixel sent 1, 2 or 4 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  576,  50,  HI_TRUE,   4, 3, 1},  /* 37: 2880x576p  @ 50Hz             pixel sent 1, 2 or 4 times*/
    {HI_UNF_EDID_TIMING_TYPE_861,    2280,  576,  50,  HI_TRUE,  16, 9, 1},  /* 38: 2880x576p  @ 50Hz             pixel sent 1, 2 or 4 times*/
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  50,  HI_FALSE,  16, 9, 0},  /* 39: 1920x1080i(1250) @ 50Hz       No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080, 100,  HI_FALSE,  16, 9, 0},  /* 40: 1920x1080i @ 100Hz            No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280, 720,  100,  HI_TRUE,  16, 9, 0},  /* 41: 1280x720p  @ 100Hz            No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  576, 100,  HI_TRUE,   4, 3, 0},  /* 42: 720x576p   @100Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  576, 100,  HI_TRUE,  16, 9, 0},  /* 43: 720x576p   @100Hz             No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  567, 100,  HI_FALSE,   4, 3, 1},  /* 44: 720(1440)x567i @ 100Hz        pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  567, 100,  HI_FALSE,  16, 9, 1},  /* 45: 720(1440)x567i @ 100Hz        pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080, 120,  HI_FALSE,  16, 9, 0},  /* 46: 1920x1080i @ 119.88/120Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280, 720,  120,  HI_TRUE,  16, 9, 0},  /* 47: 1280x720p  @  119.88/120Hz    No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 120,  HI_TRUE,   4, 3, 0},  /* 48: 720x480p   @  119.88/120Hz    No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 120,  HI_TRUE,  16, 9, 0},  /* 49: 720x480p   @  119.88/120Hz    No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 120,  HI_FALSE,   4, 3, 1},  /* 50: 720(1440)x480i @ 119.88/120Hz pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 120,  HI_FALSE,  16, 9, 1},  /* 51: 720(1440)x480i @ 119.88/120Hz pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  567, 200,  HI_TRUE,   4, 3, 0},  /* 52: 720x567p   @ 200Hz            No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  567, 200,  HI_TRUE,  16, 9, 0},  /* 53: 720x567p   @ 200Hz            No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  567, 200,  HI_FALSE,   4, 3, 1},  /* 54: 720(1440)x567i @ 200Hz        pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  567, 200,  HI_FALSE,  16, 9, 1},  /* 55: 720(1440)x567i @ 200Hz        pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 240,  HI_TRUE,   4, 3, 0},  /* 56: 720x480p   @ 239.76/240Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 240,  HI_TRUE,  16, 9, 0},  /* 57: 720x480p   @ 239.76/240Hz     No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 120,  HI_FALSE,   4, 3, 1},  /* 58: 720(1440)x480i @ 119.88/120Hz pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,     720,  480, 120,  HI_FALSE,  16, 9, 1},  /* 59: 720(1440)x480i @ 119.88/120Hz pixel sent 1 to 2 times */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280,  720,  24,  HI_TRUE,  16, 9, 1},  /* 60: 1280x720p  @ 23.97Hz/24Hz 16:9 No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280,  720,  25,  HI_TRUE,  16, 9, 0},  /* 61: 1280x720p  @ 25Hz 16:9  	   No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1280,  720,  30,  HI_TRUE,  16, 9, 0},  /* 62: 1280x720p  @ 29.97Hz/30Hz 16:9 No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080, 120,  HI_TRUE,  16, 9, 1},  /* 63: 1920x1080p @ 119.88/120Hz 16:9 No Repetition */
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080, 100,  HI_TRUE,  16, 9, 1},  /* 64: 1920x1080p @ 100Hz 16:9  	   No Repetition */
};

static struct MPI_SYSTEM_TIMING_S g_stVESATiming[] =
{
    /*  enTimingType,u32Hact, u32Vact, u32Freq, u32PixClkKHz, enTimingAttr   */
    /*EDID Established 1 Timings->  (0~16)*/
    {HI_UNF_EDID_TIMING_TYPE_DMT,     720,  400,  70,      0, 0},  //720 x 400 @ 70Hz IBM, VGA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     720,  400,  88,      0, 0},  //720 x 400 @ 88Hz IBM, XGA2
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  60,  25175, 0},  //640 x 480 @ 60Hz IBM, VGA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  67,      0, 0},  //640 x 480 @ 67Hz Apple, Mac II
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  72,  31500, 0},  //640 x 480 @ 72Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  75,  31500, 0},  //640 x 480 @ 75Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  56,  36000, 0},  //800 x 600 @ 56Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  60,  40000, 0},  //800 x 600 @ 60Hz VESA

    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  72,  50000, 0},  //800 x 600 @ 72Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  75,  49500, 0},  //800 x 600 @ 75Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,     832,  642,  75,      0, 0},  //832 x 624 @ 75Hz Apple, Mac II
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  87,      0, 0}, //1024 x 768 @ 87Hz(I) IBM
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  60,  68000, 0}, //1024 x 768 @ 60Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  70,  75000, 0}, //1024 x 768 @ 70Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  75,  78750, 0}, //1024 x 768 @ 75Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280, 1024,  75, 135000, 0},//1280 x 1024 @ 75Hz VESA
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1152,  870,  75,      0, 0}, //1152 x 870 @ 75Hz Apple, Mac II

    /*<-EDID Established 2 Timings   17~60)*/
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  350,  85,      0, 0},  //   640 x 350 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  400,  85,      0, 0},  //   640 x 400 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,     720,  400,  85,      0, 0},  //   720 x 400 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  85,  36000, 0},  //   640 x 480 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,     848,  480,  60,  33750, 0},  //   848 x 480 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  85,  56250, 0},  //   800 x 600 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  85,  94500, 0},  //   1024 x 768 @ 85 Hz

    {HI_UNF_EDID_TIMING_TYPE_DMT,    1152,  864,  75, 108000, 0},  //   1152 x 864 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1280,  768,  60,  68250, 1},  //   1280 x 768 @ 60 Hz (RB) Note: (RB) means reduced blanking
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1280,  768,  60,  79500, 0},  //   1280 x 768 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1280,  768,  75, 102250, 0},  //   1280 x 768 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1280,  768,  85, 117500, 0},  //   1280 x 768 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280,  960,  60, 108000, 0},  //   1280 x 960 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280,  960,  85, 148500, 0},  //   1280 x 960 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280, 1024,  60, 108000, 0},  //   1280 x 1024 @ 60 Hz

    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280, 1024,  85, 157500, 0},  //   1280 x 1024 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1360,  768,  60,  85500, 0},  //   1360 x 768 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1440,  900,  60,  88750, 1},  //   1440 x 900 @ 60 Hz (RB)
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1440,  900,  60, 106500, 0},  //   1440 x 900 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1440,  900,  75, 136750, 0},  //   1440 x 900 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1440,  900,  85, 157000, 0},  //   1440 x 900 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1400, 1050,  60,  88750, 1},  //   1400 x 1050 @ 60 Hz (RB)
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1400, 1050,  60, 106500, 0},  //   1400 x 1050 @ 60 Hz

    {HI_UNF_EDID_TIMING_TYPE_DMT,    1400, 1050,  75, 136750, 0},  //   1400 x 1050 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1440, 1050,  85,      0, 0},  //   1400 x 1050 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1680, 1050,  60, 119000, 1},  //   1680 x 1050 @ 60 Hz (RB)
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1680, 1050,  60, 146250, 0},  //   1680 x 1050 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1680, 1050,  75,      0, 0},  //   1680 x 1050 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT,    1680, 1050,  85,      0, 0},  //   1680 x 1050 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  60, 162000, 0},  //   1600 x 1200 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  65,      0, 0},  //   1600 x 1200 @ 65 Hz

    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  70,      0, 0},  //   1600 x 1200 @ 70 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  75,      0, 0},  //   1600 x 1200 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  85,      0, 0},  //   1600 x 1200 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1792, 1344,  60,      0, 0},  //   1792 x 1344 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1792, 1344,  75,      0, 0},  //   1792 x 1344 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1856, 1392,  60,      0, 0},  //   1856 x 1392 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1856, 1392,  75,      0, 0},  //   1856 x 1392 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1920, 1200,  60,      0, 1},  //   1920 x 1200 @ 60 Hz (RB)

    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1920, 1200,  60, 154000, 1},  //   1920 x 1200 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1920, 1200,  75,      0, 1},  //   1920 x 1200 @ 75 Hz
    {HI_UNF_EDID_TIMING_TYPE_CVT_RB, 1920, 1200,  80,      0, 1},  //   1920 x 1200 @ 85 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1920, 1440,  60,      0, 0},  //   1920 x 1440 @ 60 Hz
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1920, 1440,  75,      0, 0},  //   1920 x 1440 @ 75 Hz
    /*<-EDID DMT Standard Timings  (61~90)*/
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  400,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     640,  480,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  72,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     800,  600,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,     848,  480,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  70,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1024,  768,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1152,  864,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_861,    1280,  720,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280,  960,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280,  960,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280, 1024,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280, 1024,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1280, 1024,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  65,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  70,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1600, 1200,  85,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1792, 1344,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1792, 1344,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1856, 1392,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1856, 1392,  75,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_861,    1920, 1080,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1920, 1440,  60,      0, 0},
    {HI_UNF_EDID_TIMING_TYPE_DMT,    1920, 1440,  75,      0, 0},

};

static EDID_SIMPLE_TIMING_S* HI_MPI_Search_Timing(EDID_SIMPLE_TIMING_S* pstSimpleTimingList, EDID_SIMPLE_TIMING_S* hand_display_timing)
{
    struct list_head* pos;
    EDID_SIMPLE_TIMING_S* p_Search_Timing;

    if (HI_NULL == pstSimpleTimingList)
    {
        return HI_NULL;
    }

    pos = &hand_display_timing->head;

    do
    {
        p_Search_Timing = list_entry(pos, EDID_SIMPLE_TIMING_S, head);

        if (p_Search_Timing->stSimpleTiming.u32Hact == pstSimpleTimingList->stSimpleTiming.u32Hact)
        {
            if (p_Search_Timing->stSimpleTiming.u32Vact == pstSimpleTimingList->stSimpleTiming.u32Vact)
            {
                if ((p_Search_Timing->stSimpleTiming.u32VerFreq == pstSimpleTimingList->stSimpleTiming.u32VerFreq) || \
                    (p_Search_Timing->stSimpleTiming.u32VerFreq == (pstSimpleTimingList->stSimpleTiming.u32VerFreq + 1)) || \
                    (p_Search_Timing->stSimpleTiming.u32VerFreq == (pstSimpleTimingList->stSimpleTiming.u32VerFreq - 1)))
                {
                    pstSimpleTimingList->stSimpleTiming.enTimingType = p_Search_Timing->stSimpleTiming.enTimingType;
                    return  p_Search_Timing;
                }
            }
        }
        pos = pos->next;

    }
    while (pos != &(hand_display_timing->head));

    return HI_NULL;
}


static HI_S32 HI_MPI_Search_enTimingType(EDID_SIMPLE_TIMING_S* pstSimpleTimingList, HI_U32 u32PixClkKHz, HI_U8 u8RB)
{
    HI_S16 number, len;

    if (HI_NULL == pstSimpleTimingList)
    {
        HI_ERR_EDID("[%s]ERROR LINE:%d,\n", __FUNCTION__, __LINE__);
        return HI_FAILURE;
    }
    HI_DBG_EDID("%dX%d@%dHz,[%d]\n", pstSimpleTimingList->stSimpleTiming.u32Hact, pstSimpleTimingList->stSimpleTiming.u32Vact, \
                pstSimpleTimingList->stSimpleTiming.u32VerFreq, pstSimpleTimingList->stSimpleTiming.enTimingAttr)  ;

    len = sizeof(g_stVESATiming) / sizeof(struct MPI_SYSTEM_TIMING_S);

    for (number = len - 1; (len - EDID_DMT_TIMINGS) <= number ; number--)
    {
        if (g_stVESATiming[number].u32Hact == pstSimpleTimingList->stSimpleTiming.u32Hact)
        {
            if (g_stVESATiming[number].u32Vact == pstSimpleTimingList->stSimpleTiming.u32Vact)
            {
                if (0 != u32PixClkKHz)
                {
                    if (((g_stVESATiming[number].u32PixClkKHz - 50) <= u32PixClkKHz) && \
                        (u32PixClkKHz <= (g_stVESATiming[number].u32PixClkKHz + 50)))
                    {
                        pstSimpleTimingList->stSimpleTiming.enTimingType = g_stVESATiming[number].enTimingType;
                        return  g_stVESATiming[number].enTimingType;
                    }
                }
                else if ((g_stVESATiming[number].u32VerFreq >= (pstSimpleTimingList->stSimpleTiming.u32VerFreq - 1))\
                         && (g_stVESATiming[number].u32VerFreq <= (pstSimpleTimingList->stSimpleTiming.u32VerFreq + 1))
                         && (g_stVESATiming[number].u16RB == u8RB))
                {
                    pstSimpleTimingList->stSimpleTiming.u32VerFreq = g_stVESATiming[number].u32VerFreq;
                    pstSimpleTimingList->stSimpleTiming.enTimingType = g_stVESATiming[number].enTimingType;
                    return  g_stVESATiming[number].enTimingType;
                }
            }
        }
    }
    pstSimpleTimingList->stSimpleTiming.enTimingType = HI_UNF_EDID_TIMING_TYPE_CVT;

    return HI_UNF_EDID_TIMING_TYPE_CVT;
}

/*** DDC fetch and block validation ***/

static const HI_U8 u8EDIDHeader[] =
{
    0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x00
};
/*
 * Sanity check the EDID block (base or extension).  Return 0 if the block
 * doesn't check out, or 1 if it's valid.
 */
static HI_S32  HI_MPI_EDID_Block_Valid(HI_U8* raw_edid)
{
    HI_U32  i;
    HI_U8 u8Csum = 0;
    struct edid* edid = (struct edid*)raw_edid;

    if (raw_edid[0] == 0x00)
    {
        int score = 0;

        for (i = 0; i < sizeof(u8EDIDHeader); i++)
        {
            if (raw_edid[i] == u8EDIDHeader[i])
            {
                score++;
            }
        }

        if (score == 8) ;
        else if (score >= 6)
        {
            HI_DBG_EDID("Fixing EDID header, your hardware may be failing\n");
            memcpy(raw_edid, u8EDIDHeader, sizeof(u8EDIDHeader));
        }
        else
        {
            goto EXIT1;
        }
    }

    if (3 < edid->u8Extensions ) /* check extensions*/
    {
        HI_DBG_EDID("EDID extensions is invalid, extensions is %d\n", edid->u8Extensions);
        goto EXIT1;
    }

    for (i = 0; i < EDID_LENGTH; i++)
    {
        u8Csum += raw_edid[i];
    }

    if (u8Csum)
    {
        HI_DBG_EDID("EDID checksum is invalid, remainder is %d\n", u8Csum);

        /* allow CEA to slide through, switches mangle this */


        if (raw_edid[0] != 0x02)
        {
            goto EXIT1;
        }

    }

    /* per-block-type checks */
    switch (raw_edid[0])
    {
        case 0: /* base */
            if (edid->u8Version != 1)
            {
                HI_DBG_EDID("EDID has major u8Version %d, instead of 1\n", edid->u8Version);
                goto EXIT1;
            }

            if (edid->u8Revision > 4)
            {
                HI_DBG_EDID("EDID minor > 4, assuming backward compatibility\n");
            }
            break;

        default:
            break;
    }

    return HI_SUCCESS;

EXIT1:
    HI_ERR_EDID("EDID Check Error\n");
    return HI_FAILURE;
}



static HI_S32 HI_MPI_EDID_Parse_Vendor(HI_U8* u8Edid, EDID_VENDOR_S* EDID_u8Vendor)
{
    HI_U16 i, data16;
    struct edid* edid = (struct edid*)u8Edid;

    if (u8Edid == HI_NULL)
    {
        HI_ERR_EDID("para u8Edid  is null\n");
        return HI_FAILURE;
    }

    data16 = (edid->u8MfgID[0] << 8) | (edid->u8MfgID[1]);

    for (i = 0; i < 3; i++)
    {
        EDID_u8Vendor->cMfName[2 - i] = ((data16 & (0x1F << (5 * i))) >> (5 * i));
        if ((0 < EDID_u8Vendor->cMfName[2 - i]) && \
            (27 > EDID_u8Vendor->cMfName[2 - i]))
        {
            EDID_u8Vendor->cMfName[2 - i] += 'A' - 1;
        }
        else
        {
            HI_ERR_EDID("cMfName parse err\n");
            return HI_FAILURE;
        }
    }

    EDID_u8Vendor->u16ProductCode = (edid->u8ProductCode[1] << 8) | edid->u8ProductCode[0];
    EDID_u8Vendor->u32SerialNum = edid->u32SerialNum;
    EDID_u8Vendor->u32MfWeek = edid->u8MfWeek;
    EDID_u8Vendor->u32MfYear = edid->u8MfYear + 1990;

    HI_DBG_EDID("cMfName[%s]\n", EDID_u8Vendor->cMfName);
    HI_DBG_EDID("u16ProductCode:%d\n", EDID_u8Vendor->u16ProductCode);
    HI_DBG_EDID("u32SerialNum:%d\n", EDID_u8Vendor->u32SerialNum);
    HI_DBG_EDID("year:%d,week:%d\n", EDID_u8Vendor->u32MfYear, EDID_u8Vendor->u32MfWeek);

    return HI_SUCCESS;
}

#if 0
HI_UNF_DISP_EDID_CHOCK_E HD0_Edid_Check_State = HI_UNF_DISP_EDID_READ_ERROR;
HI_UNF_DISP_EDID_CHOCK_E HD1_Edid_Check_State = HI_UNF_DISP_EDID_READ_ERROR;
#endif
static EDID_SIMPLE_TIMING_S* HI_MPI_EDID_Parse_Stantard_Timing(EDID_STD_TIMING_S* p_Stantard_Timing, HI_U8 edid_u8Revision)
{
    EDID_SIMPLE_TIMING_S* psSimpleTiming;

    if (HI_NULL == p_Stantard_Timing)
    {
        return HI_NULL;
    }

    if ( (p_Stantard_Timing->u8HSize == 0x00 && p_Stantard_Timing->u8VfreqAspect == 0x00) || \
         (p_Stantard_Timing->u8HSize == 0x01 && p_Stantard_Timing->u8VfreqAspect == 0x01) || \
         (p_Stantard_Timing->u8HSize == 0x20 && p_Stantard_Timing->u8VfreqAspect == 0x20) )
    {
        return HI_NULL;
    }

    psSimpleTiming = malloc(sizeof(EDID_SIMPLE_TIMING_S));

    if (HI_NULL == psSimpleTiming)
    {
        return HI_NULL;
    }

    memset(psSimpleTiming, 0, sizeof(EDID_SIMPLE_TIMING_S));

    psSimpleTiming->stSimpleTiming.u32Hact = (p_Stantard_Timing->u8HSize + 31) * 8;

    switch (p_Stantard_Timing->u8VfreqAspect & EDID_TIMING_ASPECT_MASK)
    {
        case 0x00:
            if (edid_u8Revision < 3)
            {
                psSimpleTiming->stSimpleTiming.u32Hact = psSimpleTiming->stSimpleTiming.u32Hact;
            }
            else
            {
                psSimpleTiming->stSimpleTiming.u32Vact = psSimpleTiming->stSimpleTiming.u32Hact * 5 / 8;    /*16:10*/
            }
            break;

        case 0x40:
            psSimpleTiming->stSimpleTiming.u32Vact = psSimpleTiming->stSimpleTiming.u32Hact * 3 / 4;
            break;

        case 0x80:
            psSimpleTiming->stSimpleTiming.u32Vact = psSimpleTiming->stSimpleTiming.u32Hact * 4 / 5;
            break;

        case 0xC0:
            psSimpleTiming->stSimpleTiming.u32Vact = psSimpleTiming->stSimpleTiming.u32Hact * 9 / 16;
            break;

        default:
            break;
    }

    psSimpleTiming->stSimpleTiming.u32VerFreq = (p_Stantard_Timing->u8VfreqAspect & EDID_TIMING_VFREQ_MASK) + 60;

    return psSimpleTiming;
}



static HI_S32 HI_MPI_EDID_Detailed_Descriptor_18Byte_Data_Parse(struct DETAILED_TIMING_DATA* pstDetailedData, EDID_INFO_S* pstEdidInfo)
{
    EDID_CUSTOMER_OTHER_S* pstNewCustomerOther  = HI_NULL;
    EDID_DETAIL_TIMING_S* psDetailTiming = HI_NULL;              /* Header prev */
    EDID_SIMPLE_TIMING_S*   psSimpleTiming = HI_NULL, *psSimpleTiming1 = HI_NULL, *psSimpleTiming2 = HI_NULL ;
    struct DETAILED_PIXEL_TMING_S* pt = HI_NULL;
    HI_FLOAT  floatColorTmp = 0;
    HI_U8 u8RB = 0;
    HI_U8 i, k;

    /*Detailed timing Parse*/
    if ((100 <= pstDetailedData->u16PixClk) && \
        (65500 >= pstDetailedData->u16PixClk))
    {
        psDetailTiming = malloc(sizeof(EDID_DETAIL_TIMING_S));
        if (HI_NULL == psDetailTiming)
        {
            HI_ERR_EDID("[%s]ERROR LINE:%d,\n", __FUNCTION__, __LINE__);
            return HI_FAILURE;
        }
        memset(psDetailTiming, 0, sizeof(EDID_DETAIL_TIMING_S));

        if (HI_NULL != pstEdidInfo->pstDetailTimingList)
        {
            HI_DBG_EDID("ADD Datil Timing-----\n");
            list_add(&psDetailTiming->head, &pstEdidInfo->pstDetailTimingList->head);
            pstEdidInfo->u32DetailTimingNum++;
        }
        else
        {
            HI_DBG_EDID("ADD first  Datil Timing-----\n");
            INIT_LIST_HEAD(&psDetailTiming->head);
            pstEdidInfo->pstDetailTimingList = psDetailTiming;
            pstEdidInfo->u32DetailTimingNum = 1;
        }

        pt = &pstDetailedData->data.stDetailTimingData;


        psDetailTiming->stDetailTiming.stTiming.u32VFB = pt->u8Vborder + ((pt->u8VsyncOffsetPulseWidthL >> 4) | \
                ((pt->u8HsyncVsyncOffsetPulseWidthH & 0x0C) << 4));            
        psDetailTiming->stDetailTiming.stTiming.u32VBB = (((pt->u8VactiveVblankH & 0x0f) << 8) | pt->u8VblankL); 
        psDetailTiming->stDetailTiming.stTiming.u32VACT = ((pt->u8VactiveVblankH & 0xf0) << 4) | pt->u8VactiveL;  
        psDetailTiming->stDetailTiming.stTiming.u32HFB = pt->u8Hborder + (pt->u8HsyncOffsetL | \
                ((pt->u8HsyncVsyncOffsetPulseWidthH & 0xC0) << 2));                
        psDetailTiming->stDetailTiming.stTiming.u32HBB = (((pt->u8HactiveHblankH & 0x0f) << 8) | pt->u8HblankL); 
        psDetailTiming->stDetailTiming.stTiming.u32HACT = ((pt->u8HactiveHblankH & 0xf0) << 4) | pt->u8HactiveL; 
        psDetailTiming->stDetailTiming.stTiming.u32VPW = ((pt->u8HsyncVsyncOffsetPulseWidthH & 0x03) << 4) | \
                (pt->u8VsyncOffsetPulseWidthL & 0x0f);                                              
        psDetailTiming->stDetailTiming.stTiming.u32HPW = ((pt->u8HsyncVsyncOffsetPulseWidthH & 0x30) << 4) | \
                pt->u8HsyncPulseWidthL;                                                          
        psDetailTiming->stDetailTiming.stTiming.u32AspectRatioW = pt->u8WidthMmL | ((pt->u8WidthHeightHmH & 0x0F) << 8);                        /**< display rect width  */
        psDetailTiming->stDetailTiming.stTiming.u32AspectRatioH = pt->u8HeightMmL | ((pt->u8WidthHeightHmH & 0xF0) << 4);                      /**< display rect height  */
        psDetailTiming->stDetailTiming.stTiming.u32PixelClk = (pstDetailedData->u16PixClk) * 10;


        if (pt->u8Misc & 0x80)        /*Interlaced flag*/
        {
            psDetailTiming->stDetailTiming.stTiming.bInterlace = HI_TRUE;
        }
        else
        {
            psDetailTiming->stDetailTiming.stTiming.bInterlace = HI_FALSE;
        }

        /*Sync Signal Definitions Type*/
        if (0 == (pt->u8Misc & 0x10))    /*Analog Sync Signal Definitions*/
        {
            switch ((pt->u8Misc & 0x0E) >> 1)
            {
                case 0x00:                  /*Analog Composite Sync - Without Serrations - Sync On Green Signal only*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_ACS_WS_GREEN;
                    break;

                case 0x01:                  /*Analog Composite Sync - Without Serrations - Sync On all three (RGB) video signals*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_ACS_WS_ALL;
                    break;

                case 0x02:                  /*Analog Composite Sync - With Serrations (H-sync during V-sync); - Sync On Green Signal only*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_ACS_DS_GREEN;
                    break;

                case 0x03:                  /*Analog Composite Sync - With Serrations (H-sync during V-sync); - Sync On all three (RGB) video signals*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_ACS_DS_ALL;
                    break;

                case 0x04:                  /*Bipolar Analog Composite Sync - Without Serrations; - Sync On Green Signal only*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_BACS_WS_GREEN;
                    break;

                case 0x05:                  /*Bipolar Analog Composite Sync - Without Serrations; - Sync On all three (RGB) video signals*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_BACS_WS_ALL;
                    break;

                case 0x06:                  /*Bipolar Analog Composite Sync - With Serrations (H-sync during V-sync); - Sync On Green Signal only*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_BACS_DS_GREEN;
                    break;

                case 0x07:                  /*Bipolar Analog Composite Sync - With Serrations (H-sync during V-sync); - Sync On all three (RGB) video signals*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_BACS_DS_ALL;
                    break;
                default:
                    break;

            }
        }
        else                /*Digital Sync Signal Definitions*/
        {
            switch ((pt->u8Misc & 0x0E) >> 1)
            {
                case 0x01:
                case 0x00:                  /*Digital Composite Sync - Without Serrations*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_DCS_WS;
                    psDetailTiming->stDetailTiming.stTiming.bIHS = HI_FALSE;
                    psDetailTiming->stDetailTiming.stTiming.bIVS = HI_FALSE;
                    break;

                case 0x02:                   /*Digital Composite Sync - With Serrations (H-sync during V-sync)*/
                case 0x03:
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_DCS_DS;
                    break;

                case 0x04:                  /*Digital Separate Sync Vsync(-) Hsync(-)*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_DSS_VN_HN;
                    psDetailTiming->stDetailTiming.stTiming.bIHS = HI_FALSE;
                    psDetailTiming->stDetailTiming.stTiming.bIVS = HI_FALSE;
                    break;

                case 0x05:                  /*Digital Separate Sync Vsync(-) Hsync(+)*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_DSS_VN_HP;
                    psDetailTiming->stDetailTiming.stTiming.bIHS = HI_TRUE;
                    psDetailTiming->stDetailTiming.stTiming.bIVS = HI_FALSE;
                    break;

                case 0x06:                  /*Digital Separate Sync Vsync(+) Hsync(-)*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_DSS_VP_HN;
                    psDetailTiming->stDetailTiming.stTiming.bIHS = HI_FALSE;
                    psDetailTiming->stDetailTiming.stTiming.bIVS = HI_TRUE;
                    break;

                case 0x07:                  /*Digital Separate Sync Vsync(+) Hsync(+)*/
                    psDetailTiming->stDetailTiming.enSyncType = HI_UNF_EDID_SYNC_DSS_VP_HP;
                    psDetailTiming->stDetailTiming.stTiming.bIHS = HI_TRUE;
                    psDetailTiming->stDetailTiming.stTiming.bIVS = HI_TRUE;
                    break;

                default:
                    break;

            }
        }

        /*Stereo Viewing Support*/
        switch (((pt->u8Misc & 0x60) >> 4) | (pt->u8Misc & 0x01))
        {
            case 0x02:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_SEQUENTIAL_R;
                break;

            case 0x04:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_SEQUENTIAL_L;
                break;

            case 0x03:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_INTERLEAVED_2R;
                break;

            case 0x05:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_INTERLEAVED_2L;
                break;

            case 0x06:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_INTERLEAVED_4;
                break;

            case 0x07:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_INTERLEAVED_SBS;
                break;

            default:
                psDetailTiming->enStereoType = EDID_STEREO_VIEWING_NO;
                break;

        }
 
        psDetailTiming->stDetailTiming.stTiming.bIDV = HI_FALSE;                                              /**<¨®DD¡ì¨ºy?YD?o?¨º?¡¤?¡¤-¡Áa*/
        psDetailTiming->stDetailTiming.stTiming.u32VBB -= psDetailTiming->stDetailTiming.stTiming.u32VFB;
        psDetailTiming->stDetailTiming.stTiming.u32HBB -= psDetailTiming->stDetailTiming.stTiming.u32HFB;
        psDetailTiming->stDetailTiming.stTiming.bIHS = (HI_BOOL) (psDetailTiming->stDetailTiming.stTiming.bIHS ^ 0x1);
        psDetailTiming->stDetailTiming.stTiming.bIVS = (HI_BOOL)(psDetailTiming->stDetailTiming.stTiming.bIVS ^ 0x1);

        return HI_SUCCESS;
    }
    else if (0 == pstDetailedData->u16PixClk )
    {
        if ((0x11 <= pstDetailedData->data.stOtherData.u8Type) && \
            (0xF6 >= pstDetailedData->data.stOtherData.u8Type))
        {
            /*Currently undefined*/
            return HI_SUCCESS;
        }
        else
        {
            pstNewCustomerOther = HI_NULL;
            HI_DBG_EDID("Descriptor type: 0x%x\n", pstDetailedData->data.stOtherData.u8Type);
            switch (pstDetailedData->data.stOtherData.u8Type)
            {
                case EDID_CUSTOMER_STANDARD_TIMING:                 /*Descriptor contains additional Standard Timing Identifications*/
                    //Stantard Timing
                    HI_DBG_EDID("Descriptor contains additiona Stantard Timing:\n");

                    for (k = 0; k < EDID_STD_TIMINGS2; k++)
                    {

                        psSimpleTiming = HI_MPI_EDID_Parse_Stantard_Timing(&pstDetailedData->data.stOtherData.data.stSTDTiming[k], pstEdidInfo->stVersion.u8Revision);

                        if (HI_NULL == psSimpleTiming)
                        {
                            continue;
                        }

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
                        //pixclock=84750 is CVT_1360x768@60;
                        if ((1360 == psSimpleTiming->u32Hact) && (768 == psSimpleTiming->u32Vact) && (60 == psSimpleTiming->u32Freq ))
                        {
                            u32PixClkKHz = 84750;
                        }
                        //pixclock=118250 is CVT_1600x900@60,ceterm no support DMT_1600x900@60_RB,so add this;
                        else if ((1600 == psSimpleTiming->u32Hact) && (900 == psSimpleTiming->u32Vact) && (60 == psSimpleTiming->u32Freq ))
                        {
                            u32PixClkKHz = 118250;
                        }
                        else
                        {
                            u32PixClkKHz = 0;
                        }
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

                        HI_MPI_Search_enTimingType(psSimpleTiming, 0, 0);

                        if (HI_NULL != pstEdidInfo->pstSimpleTimingList)
                        {
                            if (HI_NULL == HI_MPI_Search_Timing(psSimpleTiming, pstEdidInfo->pstSimpleTimingList))
                            {

                                list_add(&psSimpleTiming->head, &pstEdidInfo->pstSimpleTimingList->head);
                            }
                            else
                            {
                                free(psSimpleTiming);
                            }
                        }
                        else
                        {
                            INIT_LIST_HEAD(&psSimpleTiming->head);
                            pstEdidInfo->pstSimpleTimingList = psSimpleTiming;
                        }
                    }

                    break;

                case EDID_CUSTOMER_COLOR_POINT:                 /*Descriptor contains additional color point data*/

                    pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S));
                    if (HI_NULL == pstNewCustomerOther)
                    {
                        HI_ERR_EDID("malloc  err\n");
                        return HI_FAILURE;
                    }
                    memset(pstNewCustomerOther, 0, sizeof(EDID_CUSTOMER_OTHER_S));

                    pstNewCustomerOther->enCustomType = EDID_CUSTOMER_COLOR_POINT;
                    
                    if (0x01 == pstDetailedData->data.stOtherData.data.stColor.u8WIndex1)
                    {
                         floatColorTmp =  (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex1[0]  & (BIT3 | BIT2)) 
                         | (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex1[1] << 2);
                        pstNewCustomerOther->data.stColor[0].floatWhiteX = floatColorTmp/1024;
                        
                        floatColorTmp =  (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex1[0]  & (BIT1 | BIT0)) 
                         | (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex1[2] << 2);
                        pstNewCustomerOther->data.stColor[0].floatWhiteY = floatColorTmp/1024;

                        if (0xFF != pstDetailedData->data.stOtherData.data.stColor.u8Gamma1)
                        {
                            pstNewCustomerOther->data.stColor[0].floatGamma = ((HI_FLOAT)(pstDetailedData->data.stOtherData.data.stColor.u8Gamma1 + 100)) / 100;
                        }
                    }

                    if (0x02 == pstDetailedData->data.stOtherData.data.stColor.u8WIndex1)
                    {

                       floatColorTmp =  (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex2[0]  & (BIT3 | BIT2)) 
                        | (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex1[1] << 2);
                       pstNewCustomerOther->data.stColor[1].floatWhiteX = floatColorTmp/1024;
                       
                       floatColorTmp =  (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex2[0]  & (BIT1 | BIT0)) 
                        | (pstDetailedData->data.stOtherData.data.stColor.u8WpIndex1[2] << 2);
                       pstNewCustomerOther->data.stColor[1].floatWhiteY = floatColorTmp/1024;

                        if (0xFF != pstDetailedData->data.stOtherData.data.stColor.u8Gamma2)
                        {
                            pstNewCustomerOther->data.stColor[1].floatGamma = ((HI_FLOAT)(pstDetailedData->data.stOtherData.data.stColor.u8Gamma2 + 100)) / 100;
                        }
                    }
                    break;

                case EDID_CUSTOMER_MONITOR_RANGE:                 /*Monitor range limits, binary coded*/
                    pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S));
                    if (HI_NULL == pstNewCustomerOther)
                    {
                        HI_ERR_EDID("malloc  err\n");
                        return HI_FAILURE;
                    }
                    memset(pstNewCustomerOther, 0, sizeof(EDID_CUSTOMER_OTHER_S));

                    pstNewCustomerOther->enCustomType = EDID_CUSTOMER_MONITOR_RANGE;

                    /*Vertical Binary coded rate in kHz Min/Max */
                    pstNewCustomerOther->data.stDetailFreqRange.u32VFreqMin_KHz = pstDetailedData->data.stOtherData.data.stDetailFreqRange.u8VFreqMin;
                    pstNewCustomerOther->data.stDetailFreqRange.u32VFreqMax_KHz = pstDetailedData->data.stOtherData.data.stDetailFreqRange.u8VFreqMax;

                    if (0x02 == (pstDetailedData->data.stOtherData.u8Pad2 & 0x03))
                    {
                        pstNewCustomerOther->data.stDetailFreqRange.u32VFreqMax_KHz += 256;
                    }
                    else if (0x03 == (pstDetailedData->data.stOtherData.u8Pad2 & 0x03))
                    {
                        pstNewCustomerOther->data.stDetailFreqRange.u32VFreqMin_KHz += 256;
                        pstNewCustomerOther->data.stDetailFreqRange.u32VFreqMax_KHz += 256;
                    }

                    /*Horizontal Binary coded rate in kHz  Min/Max */
                    pstNewCustomerOther->data.stDetailFreqRange.u32HFreqMin_KHz = pstDetailedData->data.stOtherData.data.stDetailFreqRange.u8HFreqMin;
                    pstNewCustomerOther->data.stDetailFreqRange.u32HFreqMax_KHz = pstDetailedData->data.stOtherData.data.stDetailFreqRange.u8HFreqMax;

                    if (0x02 == (pstDetailedData->data.stOtherData.u8Pad2 & 0x0C) >> 2)
                    {
                        pstNewCustomerOther->data.stDetailFreqRange.u32HFreqMax_KHz += 256;
                    }
                    else if (0x03 == (pstDetailedData->data.stOtherData.u8Pad2 & 0x0C) >> 2)
                    {
                        pstNewCustomerOther->data.stDetailFreqRange.u32HFreqMin_KHz += 256;
                        pstNewCustomerOther->data.stDetailFreqRange.u32HFreqMax_KHz += 256;
                    }

                    /*Maximum Pixel Clock*/
                    pstNewCustomerOther->data.stDetailFreqRange.u32PixClkMax_KHz = pstDetailedData->data.stOtherData.data.stDetailFreqRange.u8PixClk_MHz * 10000;

                    pstNewCustomerOther->data.stDetailFreqRange.u8Indicate = pstDetailedData->data.stOtherData.data.stDetailFreqRange.u8Indicate;


                    /*GTF Secondary Curve Definitions*/
                    if (DETAILED_RANGE_INDICATE_SECONDARY_GTF == pstNewCustomerOther->data.stDetailFreqRange.u8Indicate)
                    {
                        pstNewCustomerOther->data.stDetailFreqRange.data.stGTFInfo.u8HFreqStart_KHz = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stGTFInfo.u8HFreqStart_KHz;
                        pstNewCustomerOther->data.stDetailFreqRange.data.stGTFInfo.u8C = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stGTFInfo.u8C;
                        pstNewCustomerOther->data.stDetailFreqRange.data.stGTFInfo.u16M = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stGTFInfo.u16M;
                        pstNewCustomerOther->data.stDetailFreqRange.data.stGTFInfo.u8K = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stGTFInfo.u8K;
                        pstNewCustomerOther->data.stDetailFreqRange.data.stGTFInfo.u8J = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stGTFInfo.u8J;
                    }

                    /*CVT Support Definition*/
                    else if (DETAILED_RANGE_INDICATE_CVT == pstNewCustomerOther->data.stDetailFreqRange.u8Indicate)
                    {
                        /*CVT Standard Version*/
                        pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.u8Version = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.u8Version;

                        /*extra pixel clock resolution for 0.25 MHz accuracy*/
                        pstNewCustomerOther->data.stDetailFreqRange.u32PixClkMax_KHz -= pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.PixClkPrecision * 250;

                        /*Maximum Active Pixels per Line*/
                        pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.u16PixelsPerLine = ((pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.PixPerLineMaxH << 8)\
                                | pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.PixPerLineMaxL ) << 3;
                        /*Supported Aspect Ratios*/
                        pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.u8ARSupport = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.ARSupport ;

                        /*Type of Display Scaling Supported*/
                        pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.u8ScalingSupport = pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.ScalSupport ;

                        /*CVT Blanking Support*/
                        switch (pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.BlankSupport)
                        {
                            case 0x00:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enBlankingType = EDID_BLANKING_NO_SUPPORT ;
                                break;

                            case 0x01:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enBlankingType = EDID_BLANKING_SUPPORT_STANDARD;
                                break;

                            case 0x02:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enBlankingType = EDID_BLANKING_SUPPORT_REDUCED;
                                break;

                            case 0x03:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enBlankingType = EDID_BLANKING_SUPPORT_ALL;
                                break;
                            default:
                                break;
                        }

                        /*Preferred Aspect Ratio*/
                        switch (pstDetailedData->data.stOtherData.data.stDetailFreqRange.data.stCVTInfo.PreferredAR)
                        {
                            case 0x00:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enAspRatioPref = EDID_ASPECT_RATIOS_43 ;
                                break;

                            case 0x01:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enAspRatioPref = EDID_ASPECT_RATIOS_169 ;
                                break;

                            case 0x02:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enAspRatioPref = EDID_ASPECT_RATIOS_1610 ;
                                break;

                            case 0x03:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enAspRatioPref = EDID_ASPECT_RATIOS_54 ;
                                break;

                            case 0x04:
                                pstNewCustomerOther->data.stDetailFreqRange.data.stCVTInfo.enAspRatioPref = EDID_ASPECT_RATIOS_159 ;
                                break;

                            default:
                                break;
                        }
                    }

                    break;

                case EDID_CUSTOMER_MONITOR_NAME:                 /*ASCII String - Stored as ASCII*/
                    pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S));
                    if (HI_NULL == pstNewCustomerOther)
                    {
                        HI_ERR_EDID("malloc  err\n");
                        return HI_FAILURE;
                    }

                    memset(pstNewCustomerOther, 0, sizeof(EDID_CUSTOMER_OTHER_S));
                    pstNewCustomerOther->enCustomType = EDID_CUSTOMER_MONITOR_NAME;
                    memcpy(&pstNewCustomerOther->data.stString.string[0], &pstDetailedData->data.stOtherData.data.stString.string[0], DETAILED_STRING_LEN);

                    pstEdidInfo->stVendor.pMonitorName = &pstNewCustomerOther->data.stString.string[0];

                    break;

                case EDID_CUSTOMER_SERIAL_INFO:                 /*Monitor Serial Number - Stored as ASCII,*/

                    pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S) );
                    if (HI_NULL == pstNewCustomerOther)
                    {
                        HI_ERR_EDID("malloc  err\n");
                        return HI_FAILURE;
                    }

                    memset(pstNewCustomerOther, 0, sizeof(EDID_CUSTOMER_OTHER_S) );
                    pstNewCustomerOther->enCustomType = EDID_CUSTOMER_SERIAL_INFO;
                    memcpy(&pstNewCustomerOther->data.stString.string[0], &pstDetailedData->data.stOtherData.data.stString.string[0], DETAILED_STRING_LEN);

                    pstEdidInfo->stVendor.pMonitorSerialNum = &pstNewCustomerOther->data.stString.string[0];

                    break;

                case EDID_CUSTOMER_ALPANUMERIC_DATA :            /*Alphanumeric Data String (ASCII),*/
                    pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S));
                    if (HI_NULL == pstNewCustomerOther)
                    {
                        HI_ERR_EDID("malloc  err\n");
                        return HI_FAILURE;
                    }

                    memset(pstNewCustomerOther, 0, sizeof(EDID_CUSTOMER_OTHER_S));
                    pstNewCustomerOther->enCustomType = EDID_CUSTOMER_ALPANUMERIC_DATA;
                    memcpy(&pstNewCustomerOther->data.stString.string[0], &pstDetailedData->data.stOtherData.data.stString.string[0], DETAILED_STRING_LEN);

                    pstEdidInfo->stVendor.pMonitorSerialNum = &pstNewCustomerOther->data.stString.string[0];

                    break;

                default:                  /*<0x00...0x10> (<0xF6...0xF9> EDID 1.4 Add) Descriptor defined by manufacturer.*/

                    HI_DBG_EDID("[%s]ERROR LINE:%d,\n", __FUNCTION__, __LINE__);
                    if ((0x0F < pstDetailedData->data.stOtherData.u8Type)\
                        && (1 == pstEdidInfo->stVersion.u8Version)\
                        && (4 == pstEdidInfo->stVersion.u8Revision))
                    {
                        switch (pstDetailedData->data.stOtherData.u8Type)
                        {
                            case EDID_CUSTOMER_DUMMY_INFO:   /*Dummy Descriptor EDID 1.4 Add*/
                                pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S));
                                if (HI_NULL == pstNewCustomerOther)
                                {
                                    HI_ERR_EDID("malloc  err\n");
                                    return HI_FAILURE;
                                }

                                memset(pstNewCustomerOther, 0, sizeof(EDID_CUSTOMER_OTHER_S));

                                pstNewCustomerOther->enCustomType = EDID_CUSTOMER_DUMMY_INFO;
                                memcpy(&pstNewCustomerOther->data.stString.string[0], &pstDetailedData->data.stOtherData.data.stString.string[0], DETAILED_STRING_LEN);
                                break;

                            case EDID_CUSTOMER_EST_TIMING:   /*Established Timings III EDID 1.4 Add*/
                                //Established Timing3
                                HI_DBG_EDID("Established Timings III EDID 1.4 Add:\n");

                                for (k = 0; k < EDID_EST_TIMINGS3; k++)
                                {
                                    if ((pstDetailedData->data.stOtherData.data.stEstTiming.u8Timing[k / 8] & (0x80 >> (k % 8))) && \
                                        (HI_UNF_EDID_TIMING_TYPE_GTF != g_stVESATiming[k + EDID_EST_TIMINGS1].enTimingType))
                                    {
                                        psSimpleTiming = malloc(sizeof(EDID_SIMPLE_TIMING_S));
                                        if (HI_NULL == psSimpleTiming)
                                        {
                                            HI_ERR_EDID("malloc  err\n");
                                            return HI_FAILURE;
                                        }
                                        memset(psSimpleTiming, 0, sizeof(EDID_SIMPLE_TIMING_S));

                                        psSimpleTiming->stSimpleTiming.enTimingType = g_stVESATiming[k].enTimingType;
                                        psSimpleTiming->stSimpleTiming.u32Hact = g_stVESATiming[k].u32Hact;
                                        psSimpleTiming->stSimpleTiming.u32Vact = g_stVESATiming[k].u32Vact;
                                        psSimpleTiming->stSimpleTiming.u32VerFreq = g_stVESATiming[k].u32VerFreq;

                                        HI_DBG_EDID("%dX%d@%dHz,enTimingType:%d\n", psSimpleTiming->stSimpleTiming.u32Hact, psSimpleTiming->stSimpleTiming.u32Vact, \
                                                    psSimpleTiming->stSimpleTiming.u32VerFreq, psSimpleTiming->stSimpleTiming.enTimingType)  ;

                                        if (HI_NULL != pstEdidInfo->pstSimpleTimingList)
                                        {
                                            if (HI_NULL == HI_MPI_Search_Timing(psSimpleTiming, pstEdidInfo->pstSimpleTimingList))
                                            {
                                                list_add(&psSimpleTiming->head, &pstEdidInfo->pstSimpleTimingList->head);
                                            }
                                            else
                                            {
                                                free(psSimpleTiming);
                                            }
                                        }
                                        else
                                        {
                                            INIT_LIST_HEAD(&psSimpleTiming->head);
                                            pstEdidInfo->pstSimpleTimingList = psSimpleTiming;
                                        }
                                    }
                                }

                                break;

                            case EDID_CUSTOMER_CVT_TIMING:   /*CVT 3 Byte Timing Codes EDID 1.4 Add*/

                                /*CVT Standard Version*/
                                //pstDetailedData->data.stOtherData.data.stCVTTiming.u8Version;
                                for (k = 0; k < 4; k++)
                                {
                                    psSimpleTiming = malloc(sizeof(EDID_SIMPLE_TIMING_S));
                                    if (HI_NULL == psSimpleTiming)
                                    {
                                        HI_ERR_EDID("malloc err\n");
                                        return HI_FAILURE;
                                    }
                                    memset(psSimpleTiming, 0, sizeof(EDID_SIMPLE_TIMING_S));

                                    psSimpleTiming->stSimpleTiming.u32Vact = (( pstDetailedData->data.stOtherData.data.stCVTTiming.stTimingDataCVT[k].Value_L\
                                            | (pstDetailedData->data.stOtherData.data.stCVTTiming.stTimingDataCVT[k].Value_H << 8))\
                                            + 1) << 1;

                                    /*not defined*/
                                    if (300 > psSimpleTiming->stSimpleTiming.u32Vact)
                                    {
                                        free(psSimpleTiming);
                                        continue;
                                    }

                                    switch (pstDetailedData->data.stOtherData.data.stCVTTiming.stTimingDataCVT[k].AR)
                                    {
                                        case 0x00:  /*4:3*/
                                            psSimpleTiming->stSimpleTiming.u32Hact = (HI_U16)(((HI_U32)psSimpleTiming->stSimpleTiming.u32Vact) * 4 / 3);
                                            break;

                                        case 0x01:  /*16:9*/
                                            psSimpleTiming->stSimpleTiming.u32Hact = (HI_U16)(((HI_U32)psSimpleTiming->stSimpleTiming.u32Vact) * 16 / 9);
                                            break;

                                        case 0x02:  /*16:10*/
                                            psSimpleTiming->stSimpleTiming.u32Hact = (HI_U16)(((HI_U32)psSimpleTiming->stSimpleTiming.u32Vact) * 8 / 5);
                                            break;

                                        case 0x03:  /*15:9*/
                                            psSimpleTiming->stSimpleTiming.u32Hact = (HI_U16)(((HI_U32)psSimpleTiming->stSimpleTiming.u32Vact) * 15 / 9);
                                            break;

                                        default:
                                            break;
                                    }
                                    HI_DBG_EDID("[%d]%d,\n", k, pstDetailedData->data.stOtherData.data.stCVTTiming.stTimingDataCVT[k].AR);
                                    HI_DBG_EDID("%dx%d,\n", psSimpleTiming->stSimpleTiming.u32Hact, psSimpleTiming->stSimpleTiming.u32Vact);

                                    /*Preferred Vertical Rate*/
                                    switch (pstDetailedData->data.stOtherData.data.stCVTTiming.stTimingDataCVT[k].PrefVerticalRate )
                                    {
                                        case 0x03:  /*85 Hz */
                                            psSimpleTiming->stSimpleTiming.u32VerFreq = 85;
                                            break;

                                        case 0x02:  /*75 Hz*/
                                            psSimpleTiming->stSimpleTiming.u32VerFreq = 75;
                                            break;

                                        case 0x01:  /*60 Hz */
                                            psSimpleTiming->stSimpleTiming.u32VerFreq = 60;
                                            break;

                                        case 0x00:  /*50 Hz */
                                            psSimpleTiming->stSimpleTiming.u32VerFreq = 50;
                                            break;

                                        default:
                                            psSimpleTiming->stSimpleTiming.u32VerFreq  = 0;
                                            break;
                                    }

                                    /*start parse simple timing*/
                                    psSimpleTiming1 = malloc(sizeof(EDID_SIMPLE_TIMING_S));
                                    if (HI_NULL == psSimpleTiming1)
                                    {
                                        HI_ERR_EDID("malloc err\n");
                                        free(psSimpleTiming);
                                        return HI_FAILURE;
                                    }
                                    memcpy(psSimpleTiming1, psSimpleTiming, sizeof(EDID_SIMPLE_TIMING_S));

                                    for (i = 0; i < 5; i++)
                                    {
                                        u8RB = 0;
                                        psSimpleTiming1->stSimpleTiming.enTimingAttr = HI_UNF_EDID_TIMING_ATTR_NONE;

                                        /*Vertical Rate*/
                                        switch (pstDetailedData->data.stOtherData.data.stCVTTiming.stTimingDataCVT[k].VerticalBlackSupport & (0x01 << i))
                                        {
                                            case 0x01:  /*60 Hz with reduced blanking (as per CVT Standard) is supported*/
                                                psSimpleTiming1->stSimpleTiming.u32VerFreq = 60;
                                                u8RB = 1;
                                                break;

                                            case 0x02:  /*85 Hz with standard blanking (CRT style) is supported*/
                                                psSimpleTiming1->stSimpleTiming.u32VerFreq = 85;
                                                break;

                                            case 0x04:  /*75 Hz with standard blanking (CRT style) is supported*/
                                                psSimpleTiming1->stSimpleTiming.u32VerFreq = 75;
                                                break;

                                            case 0x08:  /*60 Hz with standard blanking (CRT style) is supported*/
                                                psSimpleTiming1->stSimpleTiming.u32VerFreq = 60;
                                                break;

                                            case 0x10:  /*50 Hz with standard blanking (CRT style) is supported*/
                                                psSimpleTiming1->stSimpleTiming.u32VerFreq = 50;
                                                break;

                                            default:
                                                continue;

                                                // break;
                                        }

                                        if (psSimpleTiming->stSimpleTiming.u32VerFreq == psSimpleTiming1->stSimpleTiming.u32VerFreq)
                                        {
                                            psSimpleTiming1->stSimpleTiming.enTimingAttr = HI_UNF_EDID_TIMING_ATTR_PREFERRED_VERTICAL_FREQ;
                                        }

                                        HI_DBG_EDID("%dX%d@%dHz,enTimingType:%d\n", psSimpleTiming1->stSimpleTiming.u32Hact, psSimpleTiming1->stSimpleTiming.u32Vact, \
                                                    psSimpleTiming1->stSimpleTiming.u32VerFreq, psSimpleTiming1->stSimpleTiming.enTimingType)  ;

                                        if (u8RB)
                                        {
                                            HI_MPI_Search_enTimingType(psSimpleTiming1, 0, 0);
                                        }
                                        else
                                        {
                                            psSimpleTiming1->stSimpleTiming.enTimingType = HI_UNF_EDID_TIMING_TYPE_CVT_RB;
                                        }

                                        if (HI_NULL != pstEdidInfo->pstSimpleTimingList)
                                        {
                                            if (HI_NULL == HI_MPI_Search_Timing(psSimpleTiming1, pstEdidInfo->pstSimpleTimingList))
                                            { 
                                                psSimpleTiming2 = malloc(sizeof(EDID_SIMPLE_TIMING_S));
                                                if (HI_NULL == psSimpleTiming2)
                                                {
                                                    HI_ERR_EDID("malloc err\n" );
                                                    free(psSimpleTiming);
                                                    free(psSimpleTiming1);
                                                    return HI_FAILURE;
                                                }
                                                memcpy(psSimpleTiming2, psSimpleTiming1, sizeof(EDID_SIMPLE_TIMING_S));
                                                list_add(&psSimpleTiming2->head, &pstEdidInfo->pstSimpleTimingList->head);
                                            }
                                            else
                                            { 
                                                continue;
                                            }
                                        }
                                        else
                                        {
                                            /*first simple timing add */
                                            psSimpleTiming2 = malloc(sizeof(EDID_SIMPLE_TIMING_S));
                                            if (HI_NULL == psSimpleTiming2)
                                            {
                                                HI_ERR_EDID("malloc err\n");
                                                free(psSimpleTiming);
                                                free(psSimpleTiming1);
                                                return HI_FAILURE;
                                            }
                                            memcpy(psSimpleTiming2, psSimpleTiming1, sizeof(EDID_SIMPLE_TIMING_S));
                                            INIT_LIST_HEAD(&psSimpleTiming2->head);
                                            pstEdidInfo->pstSimpleTimingList = psSimpleTiming2;
                                        }
                                    }
                                    free(psSimpleTiming1);
                                    free(psSimpleTiming);
                                }

                                break;

                            case EDID_CUSTOMER_DCM:          /*Display Color Management (DCM) Data EDID 1.4 Add*/
                                pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S) + 1);
                                if (HI_NULL == pstNewCustomerOther)
                                {
                                    HI_ERR_EDID("malloc err\n");
                                    return HI_FAILURE;
                                }
                                pstNewCustomerOther->enCustomType = EDID_CUSTOMER_DCM;

                                memcpy(&pstNewCustomerOther->data.stColorManage, &pstDetailedData->data.stOtherData.data.stColorManage, sizeof(EDID_DETAILED_COLOR_MANAGEMENT_S));

                                break;

                            default:
                                break;
                        }

                    }

                    else if (0x0F >= pstDetailedData->data.stOtherData.u8Type)
                    {
                        for (k = 0 ; (k < 13) && (0x00 == pstDetailedData->data.stOtherData.data.stString.string[k]) ; k++);

                        HI_DBG_EDID("[k=%d]ERROR LINE:%d,\n", k, __LINE__);
                        if (k < 13)
                        {
                            pstNewCustomerOther = malloc(sizeof(EDID_CUSTOMER_OTHER_S) + 1);
                            if (HI_NULL == pstNewCustomerOther)
                            {
                                HI_ERR_EDID("malloc err\n");
                                return HI_FAILURE;
                            }
                            pstNewCustomerOther->enCustomType = EDID_CUSTOMER_MANUFACTURER_INFO;
                            memcpy(&pstNewCustomerOther->data.stString.string[0], &pstDetailedData->data.stOtherData.data.stString.string[0], DETAILED_STRING_LEN);

                            break;
                        }
                        else
                        {
                            HI_DBG_EDID("[HI_UNF_EDID_CUSTOMER_MANUFACTURER_INFO]data = 0");
                        }
                    }

                    break;
            }

            HI_DBG_EDID("[%s]LINE:%d,\n", __FUNCTION__, __LINE__);
            if (HI_NULL != pstNewCustomerOther)
            {
                if (HI_NULL != pstEdidInfo->pstCustomerOther)
                {

                    list_add(&pstNewCustomerOther->head, &pstEdidInfo->pstCustomerOther->head);
                }
                else
                {
                    INIT_LIST_HEAD(&pstNewCustomerOther->head);
                    pstEdidInfo->pstCustomerOther = pstNewCustomerOther;
                }

            }
            return HI_SUCCESS;
        }
    }
    else    //EDID Error
    {
        HI_ERR_EDID("pix clk err\n");
        return HI_FAILURE;
    }
}

static HI_S32 HI_MPI_EDID_Parse_Extensions(HI_U8* u8Edid, EDID_INFO_S* pstEdidInfo)
{

    EDID_EXTENSION_INFO* pstExtenInfo;
    HI_U8 u8OffsetDesc, length, u8StartBlock, u8StartBlock1, len, j, k;
    EDID_VIDEO_TIMING_S* pstVideoTiming;
    EDID_AUDIO_S* pstAudioInfoDesc;
    EDID_EXTENSION_OTHER_S* pstNewExtenOther;
    struct HDMI_DEFINE_DATA_S* pstHDMI_Data;
    struct DETAILED_TIMING_DATA* pstDetailedData;
    HI_U8 u8Csum = 0, *block1 = u8Edid;

    pstNewExtenOther = HI_NULL;
    pstAudioInfoDesc = HI_NULL;
    pstVideoTiming = HI_NULL;
    pstExtenInfo = HI_NULL;
    pstHDMI_Data = HI_NULL;


    HI_DBG_EDID("[%s]LINE:%d,\n", __FUNCTION__, __LINE__);

    if ((HI_NULL == u8Edid) ||  (HI_NULL == pstEdidInfo))
    {
        HI_ERR_EDID("EDID DATA or pstEdidInfo = HI_NULL\n");
        return HI_FAILURE;
    }

    block1 = u8Edid;

    if (3 < block1[126]) /* check extensions*/
    {
        HI_ERR_EDID("EDID extensions is invalid, extensions is %d\n", block1[126]);
        return HI_FAILURE;
    }

    for (j = 0; j < EDID_LENGTH; j++)
    {
        u8Csum += block1[j];
    }
    if (u8Csum)
    {
        HI_ERR_EDID("EDID checksum is invalid, remainder is %d\n", u8Csum);
        return HI_FAILURE;
    }

    /*
    block [0]:
    01h  LCD Timings
    02h  CEA Extension, previously reserved for VESA additional timing data, which now uses a different tag.
    20h  EDID 2.0 Extension
    30h  Color information Type 0
    40h  DVI feature data
    50h  Touch Screen Map
    F0h  Block Map
    FFh  Extension Defined by monitor manufacturer

    block [2]:  d   Byte number offset d where 18-byte descriptors begin (typically Detailed Timing Descriptors)
    block [4]: Start reserved data block
    block [d]:Start of 18-byte descriptors (typically Detailed Timing Descriptors)
    block [d-1]: End of reserved data block.


    block [126]: End of Padding .
    block [127]: Checksum
    */
    if ((block1[0] != 0x02) && (block1[1] != 0x03))
    {
        HI_ERR_EDID("EDID Extensions is not CEA 861.\n");
        return HI_FAILURE;
    }

    if (HI_NULL == pstEdidInfo->pstExitenInfo)
    {
        pstExtenInfo = malloc(sizeof(EDID_EXTENSION_INFO));
        if (HI_NULL == pstExtenInfo)
        {
            HI_ERR_EDID("malloc err\n");
            return HI_FAILURE;
        }
        memset(pstExtenInfo, 0, sizeof(EDID_EXTENSION_INFO));
        pstEdidInfo->pstExitenInfo = pstExtenInfo;
    }
    else
    {
        pstExtenInfo = pstEdidInfo->pstExitenInfo;
    }

    pstExtenInfo->block = block1[0];
    pstExtenInfo->u8Version = block1[1];

    u8OffsetDesc = block1[2];/* Detailed Timing data start posion offset */

    pstExtenInfo->stNativeFormats.bSupportUnderScan	= (HI_BOOL)((block1[3] & BIT7) >> 7);
    pstExtenInfo->stNativeFormats.bSupportAudiob		= (HI_BOOL)((block1[3] & BIT6) >> 6);
    pstExtenInfo->stNativeFormats.bSupportYPbPr444	= (HI_BOOL)((block1[3] & BIT5) >> 5);
    pstExtenInfo->stNativeFormats.bSupportYPbPr422	= (HI_BOOL)((block1[3] & BIT4) >> 4);
    pstExtenInfo->u8DetailedTimingNum = (HI_U16)(block1[3] & 0x0f);
    HI_DBG_EDID("DetailedTimingNum---(%d),\n", pstExtenInfo->u8DetailedTimingNum);

    u8StartBlock = 4;

    HI_DBG_EDID("[%s]LINE:%d,\n", __FUNCTION__, __LINE__);
    if (0 == u8OffsetDesc)
    {
        HI_DBG_EDID("EDID Extensions no data!\n");
        return HI_SUCCESS;
    }
    else if (u8OffsetDesc >= 1 && u8OffsetDesc < 4)
    {
        HI_ERR_EDID("EDID Extensions data error!\n");
        return HI_FAILURE;
    }
    else if (4 < u8OffsetDesc)
    {
        length = 0;
        while (u8OffsetDesc != u8StartBlock)
        {
            length = block1[u8StartBlock] & (BIT0 | BIT1 | BIT2 | BIT3 | BIT4);
            HI_DBG_EDID("Type:%d,leng:%d\n", ((block1[u8StartBlock] & (BIT7 | BIT6 | BIT5)) >> 5), length);

            switch ((block1[u8StartBlock] & (BIT7 | BIT6 | BIT5)) >> 5)
            {
                case EDID_EXTENSION_AUDIO:
                    for (j = 0; j < length / 3; j++)
                    {
                        pstAudioInfoDesc = malloc(sizeof(EDID_AUDIO_S));
                        if (HI_NULL == pstAudioInfoDesc)
                        {
                            HI_ERR_EDID("malloc err\n");
                            return HI_FAILURE;
                        }
                        memset(pstAudioInfoDesc, 0, sizeof(EDID_AUDIO_S));

                        pstAudioInfoDesc->enAudioCompressType = (EDID_AUDIO_COMPRESSED_TYPE_E)((block1[u8StartBlock + 3 * j + 1] & (BIT3 | BIT4 | BIT5 | BIT6)) >> 3);
                        pstAudioInfoDesc->u8AudioChannel = (block1[u8StartBlock + 3 * j + 1] & (BIT2 | BIT1 | BIT0)) + 1;
                        pstAudioInfoDesc->u8SampleRate = block1[u8StartBlock + 3 * j + 2] & (~BIT7);
                        if (j == 0)
                        {
                            pstAudioInfoDesc->u8SampleDepth = block1[u8StartBlock + 3 * j + 3] & (BIT2 | BIT1 | BIT0);
                        }
                        else if (j < 8)
                        {
                            pstAudioInfoDesc->u16BitRateMax = block1[u8StartBlock + 3 * j + 3] * 8;
                        }

                        if (HI_NULL != pstExtenInfo->pstAudioInfo)
                        {
                            list_add(&pstAudioInfoDesc->head, &pstExtenInfo->pstAudioInfo->head);
                        }
                        else
                        {
                            INIT_LIST_HEAD(&pstAudioInfoDesc->head);
                            pstExtenInfo->pstAudioInfo = pstAudioInfoDesc;
                        }
                    }
                    break;

                case EDID_EXTENSION_VIDEO:
                    len = sizeof(g_stVideoTimingCEA) / sizeof(struct MPI_SIMPLE_TIMING_S);

                    for (j = 1; j <= length; j++)
                    {
                        k = block1[u8StartBlock + j] & (~BIT7);
                        if (k < len)
                        {
                            pstVideoTiming = malloc(sizeof(EDID_VIDEO_TIMING_S));
                            if (HI_NULL == pstVideoTiming)
                            {
                                HI_ERR_EDID("malloc err\n");
                                return HI_FAILURE;
                            }
                            memset(pstVideoTiming, 0, sizeof(EDID_VIDEO_TIMING_S));


                            pstVideoTiming->enTimingType	= g_stVideoTimingCEA[k].enTimingType;
                            pstVideoTiming->u32Hact	= g_stVideoTimingCEA[k].u32Hact;
                            pstVideoTiming->u32Vact	= g_stVideoTimingCEA[k].u32Vact;
                            pstVideoTiming->u32VerFreq	= g_stVideoTimingCEA[k].u32VerFreq;
                            pstVideoTiming->bProgressive	= g_stVideoTimingCEA[k].bProgressive;
                            //pstVideoTiming->aspectRatio = g_stVideoTimingCEA[k].AspectRatio;
                            pstVideoTiming->u32AspectWidth = g_stVideoTimingCEA[k].u32AspectWidth;
                            pstVideoTiming->u32AspectHeight = g_stVideoTimingCEA[k].u32AspectHeight;

                            pstVideoTiming->enTimingAttr	= (HI_UNF_EDID_TIMING_ATTR_E) ((block1[u8StartBlock + j] & BIT7) >> 7);
                            HI_DBG_EDID ("add CEA  Vide Timing ---(%d)\n", k)   ;
                            if (HI_NULL != pstExtenInfo->pstVideoTiming)
                            {
                                list_add(&pstVideoTiming->head, &pstExtenInfo->pstVideoTiming->head);
                            }
                            else
                            {
                                INIT_LIST_HEAD(&pstVideoTiming->head);
                                pstExtenInfo->pstVideoTiming = pstVideoTiming;
                            }
                        }
                    }
                    break;

                case EDID_EXTENSION_VENDOR:
                    if (0x00 == block1[u8StartBlock + 3] && 0x0C == block1[u8StartBlock + 2] && 0x03 == block1[u8StartBlock + 1])
                    {
                        pstEdidInfo->enVideoPort = HI_UNF_EDID_VIDEO_PORT_HDMI;
                    }

                    pstExtenInfo->u16CEC_ID = ((block1[u8StartBlock + 4] & 0xF0) >> 4) | ((block1[u8StartBlock + 4] & 0x0F) << 4)
                                              | ((block1[u8StartBlock + 5] & 0xF0) << 4) | ((block1[u8StartBlock + 5] & 0x0F) << 12);


                    if (5 < length)
                    {
                        u8StartBlock1 = u8StartBlock + 6;
                        pstHDMI_Data = (struct HDMI_DEFINE_DATA_S*)&block1[u8StartBlock];

                        if (HI_NULL == pstExtenInfo->pstVideoFormat)
                        {
                            pstExtenInfo->pstVideoFormat = malloc(sizeof(EDID_VIDEO_FORMATS_S));
                            if (HI_NULL == pstExtenInfo->pstVideoFormat)
                            {
                                HI_ERR_EDID("malloc err\n");
                                return HI_FAILURE;
                            }
                            memset(pstExtenInfo->pstVideoFormat, 0, sizeof(EDID_VIDEO_FORMATS_S));

                            pstExtenInfo->pstVideoFormat->bDVI_Dual = (HI_BOOL) pstHDMI_Data->DVI_Dual;
                            pstExtenInfo->pstVideoFormat->bDC_Y444 = (HI_BOOL)pstHDMI_Data->bDC_Y444;
                            pstExtenInfo->pstVideoFormat->bDC_30bit = (HI_BOOL)pstHDMI_Data->bDC_30Bit;
                            pstExtenInfo->pstVideoFormat->bDC_36bit = (HI_BOOL)pstHDMI_Data->bDC_36Bit;
                            pstExtenInfo->pstVideoFormat->bDC_48bit = (HI_BOOL)pstHDMI_Data->bDC_48Bit;
                            pstExtenInfo->pstVideoFormat->bSupportsAI = (HI_BOOL)pstHDMI_Data->bAI;

                            if (6 < length)
                            {
                                u8StartBlock1 += 1;

                                pstExtenInfo->pstVideoFormat->u16TMDS_ClkMax = pstHDMI_Data->u8TMD_ClkMax * 5;

                                if (7 < length)
                                {
                                    u8StartBlock1 += 1;

                                    pstExtenInfo->pstVideoFormat->bCNC[0] = (HI_BOOL)(pstHDMI_Data->CNC & 0x01);
                                    pstExtenInfo->pstVideoFormat->bCNC[1] = (HI_BOOL)(pstHDMI_Data->CNC & 0x02);
                                    pstExtenInfo->pstVideoFormat->bCNC[2] = (HI_BOOL)(pstHDMI_Data->CNC & 0x04);
                                    pstExtenInfo->pstVideoFormat->bCNC[3] = (HI_BOOL)(pstHDMI_Data->CNC & 0x08);

                                    if ((1 == pstHDMI_Data->bLe) && ((u8StartBlock1 + 2 - u8StartBlock) <= length))
                                    {
                                        u8StartBlock1 += 2;

                                        if ((0 != block1[u8StartBlock1 - 1]) && (0 != block1[u8StartBlock1]))
                                        {
                                            pstExtenInfo->pstVideoFormat->pstFieldsLatencyPresent = malloc(sizeof(EDID_LATENCY_PRESENT_S));
                                            if (HI_NULL == pstExtenInfo->pstVideoFormat->pstFieldsLatencyPresent)
                                            {
                                                HI_ERR_EDID("malloc err\n");
                                                return HI_FAILURE;
                                            }
                                            memset(pstExtenInfo->pstVideoFormat->pstFieldsLatencyPresent, 0, sizeof(EDID_LATENCY_PRESENT_S));

                                            pstExtenInfo->pstVideoFormat->pstFieldsLatencyPresent->u16VideoLatency = block1[u8StartBlock1 - 1] * 2;
                                            pstExtenInfo->pstVideoFormat->pstFieldsLatencyPresent->u16AudioLatency = block1[u8StartBlock1] * 2;
                                        }

                                        if ((u8StartBlock1 - u8StartBlock) == length)
                                        {
                                            break;
                                        }
                                    }

                                    if ((1 == pstHDMI_Data->bIle) && ((u8StartBlock1 + 2 - u8StartBlock) <= length))
                                    {
                                        u8StartBlock1 += 2;

                                        if ((0 != block1[u8StartBlock1 - 1]) && (0 != block1[u8StartBlock1]))
                                        {
                                            pstExtenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent = malloc(sizeof(EDID_LATENCY_PRESENT_S));
                                            if (HI_NULL == pstExtenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent)
                                            {
                                                HI_ERR_EDID("malloc err\n");
                                                return HI_FAILURE;
                                            }
                                            memset(pstExtenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent, 0, sizeof(EDID_LATENCY_PRESENT_S));

                                            pstExtenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent->u16VideoLatency = block1[u8StartBlock1 - 1] * 2;
                                            pstExtenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent->u16AudioLatency = block1[u8StartBlock1] * 2;
                                        }

                                        if ((u8StartBlock1 - u8StartBlock) == length)
                                        {
                                            break;
                                        }
                                    }

                                    if ((1 == pstHDMI_Data->bHvp) && ((u8StartBlock1 + 2 - u8StartBlock) <= length))
                                    {
                                        u8StartBlock1 += 2;

                                        if ((0 != block1[u8StartBlock1 - 1]) && (0 != block1[u8StartBlock1]))
                                        {
                                            pstExtenInfo->pstVideoFormat->stHDMIVideoPresent = malloc(sizeof(EDID_HDMI_PRESENT_S));
                                            if (HI_NULL == pstExtenInfo->pstVideoFormat->stHDMIVideoPresent)
                                            {
                                                HI_ERR_EDID("malloc err\n");
                                                return HI_FAILURE;
                                            }
                                            memset(pstExtenInfo->pstVideoFormat->stHDMIVideoPresent, 0, sizeof(EDID_HDMI_PRESENT_S));

                                            pstExtenInfo->pstVideoFormat->stHDMIVideoPresent->b3DPresent = (HI_BOOL)((block1[u8StartBlock1 - 1] & 0x80) >> 7);
                                            pstExtenInfo->pstVideoFormat->stHDMIVideoPresent->u8HDMI_3DLen = (HI_U8)(block1[u8StartBlock1] & 0x1F);
                                            pstExtenInfo->pstVideoFormat->stHDMIVideoPresent->u8HDMI_VICLen = (HI_U8)((block1[u8StartBlock1] & 0xE0) >> 5);
                                        }

                                        if ((u8StartBlock1 - u8StartBlock) == length)
                                        {
                                            break;
                                        }
                                    }
                                }
                                else
                                {
                                    break;
                                }
                            }
                            else
                            {
                                break;
                            }
                        }

                        pstNewExtenOther = malloc(sizeof(EDID_EXTENSION_OTHER_S));
                        if (HI_NULL == pstNewExtenOther)
                        {
                            HI_ERR_EDID("malloc err\n");
                            return HI_FAILURE;
                        }
                        memset(pstNewExtenOther, 0, sizeof(EDID_EXTENSION_OTHER_S));

                        pstNewExtenOther->enExtenType = EDID_EXTENSION_VENDOR;
                        pstNewExtenOther->u8Length = length;

                        pstNewExtenOther->pu8Data = malloc(length);
                        if (HI_NULL == pstNewExtenOther->pu8Data)
                        {
                            HI_ERR_EDID("malloc err\n");
                            free(pstNewExtenOther);
                            return HI_FAILURE;
                        }
                        memset(pstNewExtenOther->pu8Data, 0, length);
                        memcpy(pstNewExtenOther->pu8Data, &block1[u8StartBlock], length);

                        if (HI_NULL != pstExtenInfo->pstVideoFormat->stHDMIVideoPresent)
                        {
                            pstExtenInfo->pstVideoFormat->stHDMIVideoPresent->pu8Data = pstNewExtenOther->pu8Data + u8StartBlock1;
                        }

                        if (HI_NULL != pstExtenInfo->pstExitensionOther)
                        {
                            list_add(&pstNewExtenOther->head, &pstExtenInfo->pstExitensionOther->head);
                        }
                        else
                        {
                            INIT_LIST_HEAD(&pstNewExtenOther->head);
                            pstExtenInfo->pstExitensionOther = pstNewExtenOther;
                        }
                    }
                    break;

                case EDID_EXTENSION_SPEAKER:
                    pstExtenInfo->u32Speaker = block1[u8StartBlock + 1];
                    pstExtenInfo->u32Speaker |= block1[u8StartBlock + 2] << 8;
                    pstExtenInfo->u32Speaker |= block1[u8StartBlock + 3] << 16;
                    break;

                case EDID_EXTENSION_VESA_DTC:
                case EDID_EXTENSION_UET:
                    /*save  data */
                    pstNewExtenOther = malloc(sizeof(EDID_EXTENSION_OTHER_S));
                    if (HI_NULL == pstNewExtenOther)
                    {
                        HI_ERR_EDID("malloc err\n");
                        return HI_FAILURE;
                    }
                    memset(pstNewExtenOther, 0, sizeof(EDID_EXTENSION_OTHER_S));

                    pstNewExtenOther->enExtenType = (EDID_EXTENSION_TYPE_E) ((block1[u8StartBlock] & (BIT7 | BIT6 | BIT5)) >> 5);
                    pstNewExtenOther->u8Length = length;

                    pstNewExtenOther->pu8Data = malloc(length);
                    if (HI_NULL == pstNewExtenOther->pu8Data)
                    {
                        HI_ERR_EDID("malloc err\n");
                        free(pstNewExtenOther);
                        return HI_FAILURE;
                    }
                    memset(pstNewExtenOther->pu8Data, 0, length);
                    memcpy(pstNewExtenOther->pu8Data, &block1[u8StartBlock], length);

                    if (HI_NULL != pstExtenInfo->pstExitensionOther)
                    {
                        list_add(&pstNewExtenOther->head, &pstExtenInfo->pstExitensionOther->head);
                    }
                    else
                    {
                        INIT_LIST_HEAD(&pstNewExtenOther->head);
                        pstExtenInfo->pstExitensionOther = pstNewExtenOther;
                    }

                    break;

                default:
                    break;
            }
            u8StartBlock = u8StartBlock + length + 1;
        }
    }

    if (u8OffsetDesc != u8StartBlock)
    {
        HI_ERR_EDID("exten block  info err\n");
        return HI_FAILURE;
    }

    HI_DBG_EDID("Parse hdmi timing.\n");
    while (u8StartBlock + 18 < 125)
    {
        pstDetailedData = (struct DETAILED_TIMING_DATA*)(&block1[u8StartBlock]);
        HI_MPI_EDID_Detailed_Descriptor_18Byte_Data_Parse(pstDetailedData, pstEdidInfo);
        u8StartBlock += 18;
    }

    return HI_SUCCESS;
}
HI_VOID HI_MPI_EDID_EdidRelease(EDID_INFO_S* pstEdidInfo)
{
    struct list_head* pos, *pos1;
    pos = HI_NULL;
    pos1 = HI_NULL;

    if (HI_NULL == pstEdidInfo)
    {
        HI_ERR_EDID("pstEdidInfo para is null \n");
        return;
    }

    /* edid info init  start*/
    if (HI_NULL != pstEdidInfo->pstSimpleTimingList)
    {
        for (pos = pstEdidInfo->pstSimpleTimingList->head.next; pos != &(pstEdidInfo->pstSimpleTimingList->head); pos = pos1)
        {
            pos1 = pos->next;
            list_del(pos);
            free(list_entry(pos, EDID_SIMPLE_TIMING_S, head));
        }
        free(pstEdidInfo->pstSimpleTimingList);
        pstEdidInfo->pstSimpleTimingList = HI_NULL;
    }

    if (HI_NULL != pstEdidInfo->pstDetailTimingList)
    {
        for (pos = pstEdidInfo->pstDetailTimingList->head.next; pos != &(pstEdidInfo->pstDetailTimingList->head); pos = pos1)
        {
            list_del(pos);
            pos1 = pos->next;
            free(list_entry(pos, EDID_DETAIL_TIMING_S, head));
        }
        free(pstEdidInfo->pstDetailTimingList);
        pstEdidInfo->pstDetailTimingList = HI_NULL;
    }

    if (HI_NULL != pstEdidInfo->pstCustomerOther)
    {
        for (pos = pstEdidInfo->pstCustomerOther->head.next; pos != &(pstEdidInfo->pstCustomerOther->head); pos = pos1)
        {
            pos1 = pos->next;
            list_del(pos);
            free(list_entry(pos, EDID_CUSTOMER_OTHER_S, head));
        }
        free(pstEdidInfo->pstCustomerOther);
        pstEdidInfo->pstCustomerOther = HI_NULL;
    }

    if (HI_NULL != pstEdidInfo->pstExitenInfo)
    {
        if (HI_NULL != pstEdidInfo->pstExitenInfo->pstAudioInfo)
        {
            for (pos = pstEdidInfo->pstExitenInfo->pstAudioInfo->head.next; pos != &(pstEdidInfo->pstExitenInfo->pstAudioInfo->head); pos = pos1)
            {
                pos1 = pos->next;
                list_del(pos);
                free(list_entry(pos, EDID_AUDIO_S, head));
            }
            free(pstEdidInfo->pstExitenInfo->pstAudioInfo);
            pstEdidInfo->pstExitenInfo->pstAudioInfo = HI_NULL;
        }


        if (HI_NULL != pstEdidInfo->pstExitenInfo->pstVideoTiming)
        {
            for (pos = pstEdidInfo->pstExitenInfo->pstVideoTiming->head.next; pos != &(pstEdidInfo->pstExitenInfo->pstVideoTiming->head); pos = pos1)
            {
                pos1 = pos->next;
                list_del(pos);
                free(list_entry(pos, EDID_VIDEO_TIMING_S, head));
            }
            free(pstEdidInfo->pstExitenInfo->pstVideoTiming);
            pstEdidInfo->pstExitenInfo->pstVideoTiming = HI_NULL;
        }


        if (HI_NULL != pstEdidInfo->pstExitenInfo->pstVideoFormat)
        {
            if (HI_NULL != pstEdidInfo->pstExitenInfo->pstVideoFormat->stHDMIVideoPresent)
            {
                free(pstEdidInfo->pstExitenInfo->pstVideoFormat->stHDMIVideoPresent);
                pstEdidInfo->pstExitenInfo->pstVideoFormat->stHDMIVideoPresent = HI_NULL;
            }
            if (HI_NULL != pstEdidInfo->pstExitenInfo->pstVideoFormat->pstFieldsLatencyPresent)
            {
                free(pstEdidInfo->pstExitenInfo->pstVideoFormat->pstFieldsLatencyPresent);
                pstEdidInfo->pstExitenInfo->pstVideoFormat->pstFieldsLatencyPresent = HI_NULL;
            }
            if (HI_NULL != pstEdidInfo->pstExitenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent)
            {
                free(pstEdidInfo->pstExitenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent);
                pstEdidInfo->pstExitenInfo->pstVideoFormat->pstIntelaceFieldsLatencyPresent = HI_NULL;
            }
            free(pstEdidInfo->pstExitenInfo->pstVideoFormat);
            pstEdidInfo->pstExitenInfo->pstVideoFormat = HI_NULL;
        }

        if (HI_NULL != pstEdidInfo->pstExitenInfo->pstExitensionOther)
        {
            for (pos = pstEdidInfo->pstExitenInfo->pstExitensionOther->head.next; pos != &(pstEdidInfo->pstExitenInfo->pstExitensionOther->head); pos = pos1)
            {
                pos1 = pos->next;
                list_del(pos);
                free(list_entry(pos, EDID_EXTENSION_OTHER_S, head));
            }
            free(pstEdidInfo->pstExitenInfo->pstExitensionOther);
            pstEdidInfo->pstExitenInfo->pstExitensionOther = HI_NULL;
        }

        free(pstEdidInfo->pstExitenInfo);
        pstEdidInfo->pstExitenInfo = HI_NULL;
    }

    memset(pstEdidInfo, 0, sizeof(EDID_INFO_S));
    return ;
}

HI_S32 HI_MPI_EDID_EdidParse(HI_U8* u8Edid, HI_U32 u32EdidLength, EDID_INFO_S* pstEdidInfo)
{
    HI_U8 k;
    struct edid* edid = (struct edid*)u8Edid;
    EDID_SIMPLE_TIMING_S* psSimpleTiming;
    struct list_head* pos;
    HI_FLOAT  floatColorTmp;

    pos = HI_NULL;
    psSimpleTiming = HI_NULL;

    if ((u8Edid == HI_NULL) || (HI_FAILURE == HI_MPI_EDID_Block_Valid(u8Edid)))
    {
        HI_ERR_EDID("check block valid\n");
        return HI_FAILURE;
    }
    HI_DBG_EDID("Para  Data Num is %d\n",u32EdidLength);

    /* edid info init  start*/
    memset(pstEdidInfo, 0, sizeof(EDID_INFO_S));
    /*edid info init end */

    /* Vendor & product info */
    if (HI_SUCCESS != HI_MPI_EDID_Parse_Vendor(u8Edid, &pstEdidInfo->stVendor))
    {
        HI_ERR_EDID("Vendor valid\n");
        return HI_FAILURE;
    }

    /* EDID u8Version */
    pstEdidInfo->stVersion.u8Version = edid->u8Version;
    pstEdidInfo->stVersion.u8Revision = edid->u8Revision;

    /* Display info: */
    //struct stDevDispInfo_parameters stDevDispInfo;
    if (edid->u8Input & BIT7)
    {
        pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_NUDEFIND_DIGITAL;
        pstEdidInfo->enVideoPort = HI_UNF_EDID_VIDEO_PORT_DVI;
        if ((1 == pstEdidInfo->stVersion.u8Version) && (4 == pstEdidInfo->stVersion.u8Revision))
        {
            /*Digital Video Interface Standard Supported*/
            switch (edid->u8Input & 0x0F)
            {
                case 1:
                    pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_DVI;
                    break;

                case 2:
                    pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_HDMI_A;
                    pstEdidInfo->enVideoPort =  HI_UNF_EDID_VIDEO_PORT_HDMI;
                    break;

                case 3:
                    pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_HDMI_B;
                    pstEdidInfo->enVideoPort =  HI_UNF_EDID_VIDEO_PORT_HDMI;
                    break;

                case 4:
                    pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_MDDI;
                    break;

                case 5:
                    pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_DISPLAYPORT;
                    break;

                default:
                    pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_NUDEFIND_DIGITAL;
                    break;
            }

            /*Color Bit Depth*/
            switch ((edid->u8Input & 0x70) >> 4)
            {
                case 1:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_6BIT;
                    break;

                case 2:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_8BIT;
                    break;

                case 3:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_10BIT;
                    break;

                case 4:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_12BIT;
                    break;

                case 5:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_14BIT;
                    break;

                case 6:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_16BIT;
                    break;

                default:
                    pstEdidInfo->stDevDispInfo.enColorDepth = EDID_COLO_DEPTH_NUDEFIND;
                    break;
            }

            /*Supported Color Encoding Format*/
            switch ((edid->u8Features & (BIT4 | BIT3)) >> 3)
            {
                case 0:
                    pstEdidInfo->stDevDispInfo.enColorEncoding = EDID_COLO_ENCODING_RGB444;
                    break;

                case 1:
                    pstEdidInfo->stDevDispInfo.enColorEncoding = EDID_COLO_ENCODING_RGB444YUV444;
                    break;

                case 2:
                    pstEdidInfo->stDevDispInfo.enColorEncoding = EDID_COLO_ENCODING_RGB444YUV422;
                    break;

                case 3:
                    pstEdidInfo->stDevDispInfo.enColorEncoding = EDID_COLO_ENCODING_RGB444YUV444YUV422;
                    break;

                default:
                    break;
            }

        }
        else
        {
            /*Display Color Type*/
            switch ((edid->u8Features & (BIT4 | BIT3)) >> 3)
            {
                case 0:
                    pstEdidInfo->stDevDispInfo.enDisplayType = EDID_MONOCHROME_DISPLAY;
                    break;
                case 1:
                    pstEdidInfo->stDevDispInfo.enDisplayType = EDID_RGB_COLOR_DISPLAY;
                    break;
                case 2:
                    pstEdidInfo->stDevDispInfo.enDisplayType = EDID_NON_RGB_DISPLAY;
                    break;
                case 3:
                    pstEdidInfo->stDevDispInfo.enDisplayType = EDID_UNDEFINED_DISPLAY;
                    break;
                default:
                    break;
            }
        }
    }
    else
    {
        pstEdidInfo->stDevDispInfo.enInputSignalType = EDID_SIGNAL_ANALOG;
        pstEdidInfo->enVideoPort = HI_UNF_EDID_VIDEO_PORT_VGA;

        /*Signal Level Standard*/
        switch ((edid->u8Input & (BIT6 | BIT5)) >> 5)
        {
            case 0:
                pstEdidInfo->stDevDispInfo.enSignalLevel = EDID_SIGNAL_LEVE07_03;
                break;

            case 1:
                pstEdidInfo->stDevDispInfo.enSignalLevel = EDID_SIGNAL_LEVE07_02;
                break;

            case 2:
                pstEdidInfo->stDevDispInfo.enSignalLevel = EDID_SIGNAL_LEVE10_04;
                break;

            case 3:
                pstEdidInfo->stDevDispInfo.enSignalLevel = EDID_SIGNAL_LEVE07_00;
                break;
            default:
                break;
        }

        /*Synchronization Types*/
        pstEdidInfo->stDevDispInfo.stFeatureSupport.bBlank2Black	= (HI_BOOL)(edid->u8Input & BIT4);
        pstEdidInfo->stDevDispInfo.stFeatureSupport.bSeparateSyncs = (HI_BOOL)(edid->u8Input & BIT3);
        pstEdidInfo->stDevDispInfo.stFeatureSupport.bCompositeSync = (HI_BOOL)(edid->u8Input & BIT2);
        pstEdidInfo->stDevDispInfo.stFeatureSupport.bGreenSync = (HI_BOOL)(edid->u8Input & BIT1);

        /*Serrations Synchronization supported*/
        pstEdidInfo->stDevDispInfo.stFeatureSupport.bSerrationVsyncs = (HI_BOOL)(edid->u8Input & BIT0);

        /*Display Color Type*/
        switch ((edid->u8Features & (BIT4 | BIT3)) >> 3)
        {
            case 0:
                pstEdidInfo->stDevDispInfo.enDisplayType = EDID_MONOCHROME_DISPLAY;
                break;
            case 1:
                pstEdidInfo->stDevDispInfo.enDisplayType = EDID_RGB_COLOR_DISPLAY;
                break;
            case 2:
                pstEdidInfo->stDevDispInfo.enDisplayType = EDID_NON_RGB_DISPLAY;
                break;
            case 3:
                pstEdidInfo->stDevDispInfo.enDisplayType = EDID_UNDEFINED_DISPLAY;
                break;
            default:
                break;
        }

    }

    /*Horizontal and Vertical Screen Size or Aspect Ratio*/
    pstEdidInfo->stDevDispInfo.u32ImgeWMax = edid->u8ImgeW_CM;
    pstEdidInfo->stDevDispInfo.u32ImgeHMax = edid->u8ImgeH_CM;

    /*Display Transfer Characteristics (GAMMA)*/
    if (0 == edid->u8Gamma || 0xFF == edid->u8Gamma)
    {
        pstEdidInfo->stDevDispInfo.u32Gamma = 0;
    }
    else
    {
        pstEdidInfo->stDevDispInfo.u32Gamma = ((HI_U32)(edid->u8Gamma) + 100);
    }

    /*Display Power Management*/
    pstEdidInfo->stDevDispInfo.stFeatureSupport.bStandby = (HI_BOOL)(edid->u8Features & BIT7);
    pstEdidInfo->stDevDispInfo.stFeatureSupport.bSuspend = (HI_BOOL)(edid->u8Features & BIT6);
    pstEdidInfo->stDevDispInfo.stFeatureSupport.bActiveOff = (HI_BOOL)(edid->u8Features & BIT5);

    /*Other Feature Support Flags*/
    pstEdidInfo->stDevDispInfo.stFeatureSupport.bsRGB = (HI_BOOL)(edid->u8Features & BIT2);
    pstEdidInfo->stDevDispInfo.stFeatureSupport.bPreferredTiming = (HI_BOOL)(edid->u8Features & BIT1);
    pstEdidInfo->stDevDispInfo.stFeatureSupport.bDefaultGTF = (HI_BOOL)(edid->u8Features & BIT0);


    /* Color characteristics */

    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT7 | BIT6))  | (edid->u8RedX << 2);
    pstEdidInfo->stColorPara.floatRedX = floatColorTmp/1024;
    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT5 | BIT4))  | (edid->u8RedY << 2);
    pstEdidInfo->stColorPara.floatRedY = floatColorTmp/1024;
    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT3 | BIT2))  | (edid->u8GreenX << 2);
    pstEdidInfo->stColorPara.floatGreenX = floatColorTmp/1024;
    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT1 | BIT0))  | (edid->u8GreenY << 2);
    pstEdidInfo->stColorPara.floatGreenY = floatColorTmp/1024;

    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT7 | BIT6))  | (edid->u8BlueX << 2);
    pstEdidInfo->stColorPara.floatBlueX = floatColorTmp/1024;
    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT5 | BIT4))  | (edid->u8BlueY << 2);
    pstEdidInfo->stColorPara.floatBlueY = floatColorTmp/1024;
    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT3 | BIT2))  | (edid->u8WhiteX << 2);
    pstEdidInfo->stColorPara.floatWhiteX = floatColorTmp/1024;
    floatColorTmp =  (edid->u8RedGreenLowBits & (BIT1 | BIT0))  | (edid->u8WhiteY << 2);
    pstEdidInfo->stColorPara.floatWhiteY = floatColorTmp/1024;

    //struct stColorParacteristics stColorPara;
    /* Est. timings and mfg rsvd timings*/


    //Detailed Timing
    for (k = 0; k < EDID_DETAILED_TIMINGS; k++)
    {
        if (HI_FAILURE == HI_MPI_EDID_Detailed_Descriptor_18Byte_Data_Parse(&edid->stDetailTimingData[k], pstEdidInfo))
        {
            HI_ERR_EDID("HI_MPI_EDID_Detailed_Descriptor_18Byte_Data_Parse[%d] ERROR:%d\n", k, __LINE__);
            continue;
        }

        /*Preferred Timing*/
        if ((0 == k) && (HI_NULL != pstEdidInfo->pstDetailTimingList))
        {
            pstEdidInfo->pstDetailTimingList->stDetailTiming.enTimingAttr = HI_UNF_EDID_TIMING_ATTR_PREFERRED_TIMING;
        }
    }

    //Stantard Timing
    HI_DBG_EDID("Stantard Timing:\n");

    for (k = 0; k < EDID_STD_TIMINGS1; k++)
    {
        psSimpleTiming = HI_MPI_EDID_Parse_Stantard_Timing(&edid->stSTDTimingData[k], pstEdidInfo->stVersion.u8Revision);

        if (HI_NULL == psSimpleTiming)
        {
            continue;
        }

#if 0 /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/
        //pixclock=84750 is CVT_1360x768@60;
        if ((1360 == psSimpleTiming->u32Hact) && (768 == psSimpleTiming->u32Vact) && (60 == psSimpleTiming->u32Freq ))
        {
            u32PixClkKHz = 84750;
        }
        //pixclock=118250 is CVT_1600x900@60,ceterm no support DMT_1600x900@60_RB,so add this;
        else if ((1600 == psSimpleTiming->u32Hact) && (900 == psSimpleTiming->u32Vact) && (60 == psSimpleTiming->u32Freq ))
        {
            u32PixClkKHz = 118250;
        }
        else
        {
            u32PixClkKHz = 0;
        }
#endif /*--NO MODIFY : COMMENT BY CODINGPARTNER--*/

        HI_MPI_Search_enTimingType(psSimpleTiming, 0, 0);

        if (HI_NULL != pstEdidInfo->pstSimpleTimingList)
        {
            if (HI_NULL == HI_MPI_Search_Timing(psSimpleTiming, pstEdidInfo->pstSimpleTimingList))
            {
                list_add(&psSimpleTiming->head, &pstEdidInfo->pstSimpleTimingList->head);
            }
            else
            {
                free(psSimpleTiming);
            }
        }
        else
        {
            INIT_LIST_HEAD(&psSimpleTiming->head);
            pstEdidInfo->pstSimpleTimingList = psSimpleTiming;
        }
    }
    //Established Timing1
    HI_DBG_EDID("Established Timing1:\n");
    unsigned long est_bits = (edid->stEstTimingData.u8T1 << 16) | \
                             (edid->stEstTimingData.u8T2 << 8) | \
                             (edid->stEstTimingData.u8MfgRsvd & 0x80);

    for (k = 0; k < EDID_EST_TIMINGS1; k++)
    {
        if ((est_bits & (1 << (23 - k))) && (HI_UNF_EDID_TIMING_TYPE_GTF != g_stVESATiming[k].enTimingType))
        {
            psSimpleTiming = malloc(sizeof(EDID_SIMPLE_TIMING_S));
            if (HI_NULL == psSimpleTiming)
            {
                HI_ERR_EDID("malloc err\n");
                return HI_FAILURE;
            }
            memset(psSimpleTiming, 0, sizeof(EDID_SIMPLE_TIMING_S));

            psSimpleTiming->stSimpleTiming.enTimingType = g_stVESATiming[k].enTimingType;
            psSimpleTiming->stSimpleTiming.u32Hact = g_stVESATiming[k].u32Hact;
            psSimpleTiming->stSimpleTiming.u32Vact = g_stVESATiming[k].u32Vact;
            psSimpleTiming->stSimpleTiming.u32VerFreq = g_stVESATiming[k].u32VerFreq;


            HI_DBG_EDID("%dX%d@%dHz,enTimingType:%d\n", psSimpleTiming->stSimpleTiming.u32Hact, psSimpleTiming->stSimpleTiming.u32Vact, \
                        psSimpleTiming->stSimpleTiming.u32VerFreq, psSimpleTiming->stSimpleTiming.enTimingType)  ;


            if (HI_NULL != pstEdidInfo->pstSimpleTimingList)
            {

                if (HI_NULL == HI_MPI_Search_Timing(psSimpleTiming, pstEdidInfo->pstSimpleTimingList))
                {
                    list_add(&psSimpleTiming->head, &pstEdidInfo->pstSimpleTimingList->head);
                }
                else
                {
                    free(psSimpleTiming);
                }
            }
            else
            {
                INIT_LIST_HEAD(&psSimpleTiming->head);
                pstEdidInfo->pstSimpleTimingList = psSimpleTiming;
            }
        }
    }

    HI_DBG_EDID ("extensions ---------%d\n", edid->u8Extensions);

    for (k = 1; (k <= edid->u8Extensions) && (EDID_BLOCK_LENG * k + EDID_BLOCK_LENG <= u32EdidLength); k++ )
    {
        HI_DBG_EDID("-----------Parse_Extensions  block -------------%d----------\n",k);
        HI_MPI_EDID_Parse_Extensions(u8Edid + EDID_BLOCK_LENG * k, pstEdidInfo);
    }
	
    pstEdidInfo->u32SimpleTimingNum = 0;

    HI_DBG_EDID("Display Timing:\n");
    if (pstEdidInfo->pstSimpleTimingList)
    {
        pos = &pstEdidInfo->pstSimpleTimingList->head;
        do
        {
            psSimpleTiming = list_entry(pos, EDID_SIMPLE_TIMING_S, head);
            HI_DBG_EDID("%dX%d@%dHz,enTimingType:%d,[%d]\n", psSimpleTiming->stSimpleTiming.u32Hact, psSimpleTiming->stSimpleTiming.u32Vact, \
                        psSimpleTiming->stSimpleTiming.u32VerFreq, psSimpleTiming->stSimpleTiming.enTimingType, psSimpleTiming->stSimpleTiming.enTimingAttr)  ;
            pos = pos->next;

            pstEdidInfo->u32SimpleTimingNum++;
        }
        while (pos != &(pstEdidInfo->pstSimpleTimingList->head));
    }
    HI_DBG_EDID("----EDID Para end----\n");
    return HI_SUCCESS;
}
//TC MODIFY END

