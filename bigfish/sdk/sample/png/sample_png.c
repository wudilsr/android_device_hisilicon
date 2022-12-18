#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/mman.h>
#include <linux/fb.h>
#include <assert.h>
#include <dirent.h>
#include <sys/stat.h>
#include <pthread.h>
#include <sys/time.h>
#include <sys/wait.h>
#include <sys/types.h>

#include "hi_type.h"
#include "png.h"
#include "pngpriv.h"
#include "hi_png_api.h"
#include "hi_png_errcode.h"
#include "hi_png_config.h"
#include "hi_tde_type.h"
#include "zlib.h"

#include "hifb.h"
#include "hi_tde_api.h"
#include "hi_type.h"
#include "hi_unf_disp.h"
#include "hi_adp_mpi.h"
#include "hi_math.h"

#define PNG_DIR                         "./res/"    
#define HI_MMB_New      HI_MMZ_New
#define HI_MMB_Map      HI_MMZ_Map
#define HI_MMB_Unmap    HI_MMZ_Unmap
#define HI_MMB_Delete   HI_MMZ_Delete


typedef struct tagPNG_DECPARAM_S
{
    HI_BOOL           bSoftDec; /* �Ƿ��������*/
    HI_BOOL           bSync; /* �Ƿ�ͬ������*/
    HI_U32            u32Transform; /* ת��*/
    HI_PNG_COLORFMT_E eOutFmt;
    HI_U32            u32XPos;
    HI_U32            u32YPos;
} PNG_DECPARAM_S;


typedef struct tagPNG_RESULT_S
{
    HI_U32 u32PhyAddr;      /* �����ַ*/
    HI_U32 u32Stride;       /* �п�*/
    HI_U32 u32RowBytes;     /* ����Ч�ֽ���*/
    HI_U32 u32Height;       /* �߶�*/
} PNG_RESULT_S;

typedef struct tag_HI_PNG_ARGB_S
{
    HI_U8 bit_alpha;
    HI_U8 bit_red;
    HI_U8 bit_green;
    HI_U8 bit_blue;
    HI_U8 offset_alpha;
    HI_U8 offset_red;
    HI_U8 offset_green;
    HI_U8 offset_blue;
} HI_PNG_ARGB_S;


HI_PNG_ARGB_S sArgbInfo[] =
{
    /* ARGB4444 */
    {4, 4, 4, 4, 12,  8, 4, 0},
    /* ARGB1555 */
    {1, 5, 5, 5, 15, 10, 5, 0},
    /* RGB565 */
    {0, 5, 6, 5, 16, 11, 5, 0},
    /* RGB555 */
    {0, 5, 5, 5, 15, 10, 5, 0},
    /* RGB444 */
    {0, 4, 4, 4, 12,  8, 4, 0}
};

HI_S32 PNG_ShowSurface(TDE2_SURFACE_S *pstSurface, HI_U32 u32PosX, HI_U32 u32PosY)
{
    int fd;
    struct fb_fix_screeninfo fix;
    struct fb_var_screeninfo var;
    struct fb_bitfield r32 = {16, 8, 0};
    struct fb_bitfield g32 = {8, 8, 0};
    struct fb_bitfield b32 = {0, 8, 0};    
    struct fb_bitfield a32 = {24, 8, 0};

    HIFB_POINT_S stPoint = {u32PosX, u32PosY};

    TDE2_SURFACE_S stFbSurface;
    TDE_HANDLE tdeHandle;
    TDE2_RECT_S copyRect = {0, 0, pstSurface->u32Width, pstSurface->u32Height};
    TDE2_OPT_S stOpt = {0};
    HI_BOOL bShow = HI_TRUE;
    HI_S32 ret ;
    HI_SYS_Init();
    HIADP_MCE_Exit();
    ret = HIADP_Disp_Init(HI_UNF_ENC_FMT_720P_50);
    if (ret != HI_SUCCESS)
    {
        return 0;
    }

    fd = open("/dev/fb0", O_RDWR);
    if(fd < 0)
    {
        printf("open fb0 failed!\n");
        return -1;
    }
    if (ioctl(fd, FBIOPUT_SCREEN_ORIGIN_HIFB, &stPoint) < 0)
    {
        printf("set screen original show position failed!\n");
        close(fd);
        return -1;
    }

    if (ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0)
    {
   	printf("Get variable screen info failed!\n");
        close(fd);
        return -1;
    }

    var.xres = var.xres_virtual = pstSurface->u32Width;
    var.yres = pstSurface->u32Height;
    var.yres_virtual = pstSurface->u32Height;
    
    var.transp= a32;
    var.red = r32;
    var.green = g32;
    var.blue = b32;
    var.bits_per_pixel = 32;

    if (ioctl(fd, FBIOPUT_VSCREENINFO, &var) < 0)
    {
   	printf("Put variable screen info failed!\n");
        close(fd);
        return -1;
    }

        if (ioctl(fd, FBIOGET_VSCREENINFO, &var) < 0)
    {
   	printf("Put variable screen info failed!\n");
        close(fd);
        return -1;
    }

    
    if (ioctl(fd, FBIOGET_FSCREENINFO, &fix) < 0)
    {
   	printf("Get fix screen info failed!\n");
        close(fd);
        return -1;
    }

    stFbSurface.u32PhyAddr = fix.smem_start;
    stFbSurface.bAlphaMax255 = HI_TRUE;
    stFbSurface.bYCbCrClut = 0;
    stFbSurface.enColorFmt = TDE2_COLOR_FMT_ARGB8888;
    stFbSurface.pu8ClutPhyAddr = HI_NULL;
    stFbSurface.u32Height = pstSurface->u32Height;
    stFbSurface.u32Width = pstSurface->u32Width;
    stFbSurface.u32Stride = fix.line_length;

    if (ioctl(fd, FBIOPUT_SHOW_HIFB, &bShow) < 0)
    {
        printf("show failed!\n");
        close(fd);
        return -1;
    }

    ret = HI_TDE2_Open();
    if(ret < 0)
    {
        printf("TDE open failed!!!\n");
        return -1;
    }

    tdeHandle = HI_TDE2_BeginJob();
    if(tdeHandle == HI_ERR_TDE_INVALID_HANDLE)
    {
        printf("TDE BeginJob  failed!!!\n");
        return -1;
    }

    stOpt.bClutReload = HI_TRUE;
    ret = HI_TDE2_Bitblit(tdeHandle, NULL, NULL, pstSurface, &copyRect, &stFbSurface, &copyRect, &stOpt);
    if(ret < 0)
    {
     printf("ret=0x%x\n",ret);
        printf("TDE Blit  failed!!!\n");
        return -1;
    }
    
    ret = HI_TDE2_EndJob(tdeHandle, HI_FALSE, HI_TRUE, 100);
	
    if(ret < 0)
    {
        printf("TDE end job  failed!!!\n");
	close(fd);

        return -1;
    }
    printf("Please press Enter to show next picture!\n");
    getchar();
    close(fd);
    return 0;
}




static HI_S32 PNG_Decode(HI_CHAR *pszFilepath, PNG_DECPARAM_S *pstDecConfig, PNG_RESULT_S *pstDecResult)
{
    FILE *fp = HI_NULL;
    png_structp png_ptr;
    png_infop info_ptr;
    HI_U32 u32Phyaddr = 0;
    png_uint_32 width, height;
    int bit_depth, color_type, interlace_type;
    HI_U32 i;
    int number_passes;
    HI_U32 u32RowBytes = 0;
    HI_VOID *pVir = HI_NULL;
    HI_PNG_STATE_E enState = HI_PNG_STATE_BUTT;
    HI_U32 u32ChannelNum = 0;

    fp = fopen(pszFilepath, "rb");

    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, HI_NULL, HI_NULL, HI_NULL);

    info_ptr = png_create_info_struct(png_ptr);

    if (setjmp(png_jmpbuf(png_ptr)))
    {
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        if (pstDecResult->u32PhyAddr)
        {
            HI_MMB_Unmap(pstDecResult->u32PhyAddr);
            HI_MMB_Delete(pstDecResult->u32PhyAddr);
        }

        fclose(fp);
        return -1;
    }

    png_init_io(png_ptr, fp);

    png_read_info(png_ptr, info_ptr);

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,&interlace_type, NULL, NULL);

    number_passes = png_set_interlace_handling(png_ptr);

    if (number_passes == 7)
    {
        pstDecResult->u32PhyAddr = 0;
        png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
        fclose(fp);
        return -1;
    }

    if (color_type == PNG_COLOR_TYPE_PALETTE)
    {
        png_set_expand(png_ptr);
    }

    if ((color_type == PNG_COLOR_TYPE_GRAY) && (bit_depth < 8))
    {
        png_set_expand(png_ptr);
    }

    if (png_get_valid(png_ptr, info_ptr, PNG_INFO_tRNS))
    {
        png_set_tRNS_to_alpha(png_ptr);
    }
    else
    {
        png_set_add_alpha(png_ptr, 0xff, PNG_FILLER_AFTER);
    }

    if (bit_depth == 16)
    {
        png_set_strip_16(png_ptr);
    }

    /** GRAY->RGB */
    if ((color_type == PNG_COLOR_TYPE_GRAY)
        || (color_type == PNG_COLOR_TYPE_GRAY_ALPHA))
    {
        png_set_gray_to_rgb(png_ptr);
    }

    /** RGBA->BGRA */
    png_set_bgr(png_ptr);

    if ((pstDecConfig->u32Transform & HI_PNG_TRANSFORM_8TO4) && !pstDecConfig->bSoftDec)
    {
        switch (pstDecConfig->eOutFmt)
        {
	        case HI_PNG_COLORFMT_ARGB1555:
	            png_set_outfmt(png_ptr, HIPNG_FMT_ARGB1555);
	            break;
	        case HI_PNG_COLORFMT_ARGB4444:
	            png_set_outfmt(png_ptr, HIPNG_FMT_ARGB4444);
	            break;
	        case HI_PNG_COLORFMT_RGB565:
	            png_set_outfmt(png_ptr, HIPNG_FMT_RGB565);
	            break;
	        case HI_PNG_COLORFMT_RGB555:
	            png_set_outfmt(png_ptr, HIPNG_FMT_RGB555);
	            break;
	        case HI_PNG_COLORFMT_RGB444:
	        default:
	            png_set_outfmt(png_ptr, HIPNG_FMT_RGB444);
	            break;
        }
    }

    png_read_update_info(png_ptr, info_ptr);

    png_bytep row_pointers[height];

    png_get_IHDR(png_ptr, info_ptr, &width, &height, &bit_depth, &color_type,
                 &interlace_type, NULL, NULL);

    u32ChannelNum = png_get_channels(png_ptr, info_ptr);
    u32RowBytes = u32ChannelNum * bit_depth * width >> 3;
    if (u32RowBytes == 0)
    {
        u32RowBytes = 1;
    }
    pstDecResult->u32RowBytes = u32RowBytes;
    //u32RowBytes = (u32RowBytes + 0xf) & ~0xf;
u32RowBytes=HI_SYS_GET_STRIDE(u32RowBytes);
    u32Phyaddr = (HI_U32)HI_MMB_New(u32RowBytes * height, 16, HI_NULL, "PNG_IMAGE_BUF");
	if(0 == u32Phyaddr)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		if(NULL != fp)
		{
		   fclose(fp);
		}
		return -1;
	}
    pVir = HI_MMB_Map(u32Phyaddr,0);
	if(NULL == pVir)
	{
		png_destroy_read_struct(&png_ptr, &info_ptr, NULL);
		if(NULL != fp)
		{
		   fclose(fp);
		}
		return -1;
	}


    pstDecResult->u32PhyAddr = u32Phyaddr;

    for (i = 0; i < height; i++)
    {
        row_pointers[i] = (HI_UCHAR *)pVir + i * u32RowBytes;
    }

    if (pstDecConfig->bSoftDec)
    {
        png_set_swdec(png_ptr);
    }

    if (pstDecConfig->bSync)
    {
        png_read_image(png_ptr, row_pointers);
    }
    else
    {
        png_read_image_async(png_ptr, row_pointers);
    }

    png_get_state(png_ptr, HI_TRUE, (PNG_STATE_E *)(&enState));

    /* ���ת����Ŀ���ʽ*/
    if (pstDecConfig->bSoftDec && (pstDecConfig->u32Transform & HI_PNG_TRANSFORM_8TO4))
    {
        HI_U32 *pSrc;
        HI_U16 *pDst;
        HI_U32 j;
        for (i = 0; i < height; i++)
        {
            pSrc = (HI_U32 *)row_pointers[i];
            pDst = (HI_U16 *)row_pointers[i];
            for (j = 0; j < width; j++)
            {
                *pDst = ((((*pSrc
                            & 0xff000000)
                           >> (32
                               - sArgbInfo[pstDecConfig->eOutFmt].bit_alpha))
                          & 0xff) << sArgbInfo[pstDecConfig->eOutFmt].offset_alpha)
                        | ((((*pSrc
                              & 0xff0000)
                             >> (24
                                 - sArgbInfo[pstDecConfig->eOutFmt].bit_red))
                            & 0xff) << sArgbInfo[pstDecConfig->eOutFmt].offset_red)
                        | ((((*pSrc
                              & 0xff00)
                             >> (16
                                 - sArgbInfo[pstDecConfig->eOutFmt].bit_green))
                            & 0xff) << sArgbInfo[pstDecConfig->eOutFmt].offset_green)
                        | ((((*pSrc
                              & 0xff)
                             >> (8
                                 - sArgbInfo[pstDecConfig->eOutFmt].bit_blue))
                            & 0xff) << sArgbInfo[pstDecConfig->eOutFmt].offset_blue);
                pSrc++;
                pDst++;
            }
        }
    }

    if (pstDecConfig->u32Transform & HI_PNG_TRANSFORM_8TO4)
    {
        pstDecResult->u32RowBytes /= 2;
    }

    png_read_end(png_ptr, info_ptr);

    HI_MMB_Unmap(u32Phyaddr);

    pstDecResult->u32Stride  = u32RowBytes;
    pstDecResult->u32Height  = height;
    pstDecResult->u32PhyAddr = u32Phyaddr;
    /* ��ʾ*/
    {
        TDE2_SURFACE_S stSur = {0};

        if (pstDecConfig->u32Transform & HI_PNG_TRANSFORM_8TO4)
        {
            switch (pstDecConfig->eOutFmt)
            {
            case HI_PNG_COLORFMT_ARGB4444:
                stSur.enColorFmt = TDE2_COLOR_FMT_ARGB4444;
                break;
            case HI_PNG_COLORFMT_ARGB1555:
                stSur.enColorFmt = TDE2_COLOR_FMT_ARGB1555;
                break;
            case HI_PNG_COLORFMT_RGB565:
                stSur.enColorFmt = TDE2_COLOR_FMT_RGB565;
                break;
            case HI_PNG_COLORFMT_RGB555:
                stSur.enColorFmt = TDE2_COLOR_FMT_RGB555;
                break;
            case HI_PNG_COLORFMT_RGB444:
                stSur.enColorFmt = TDE2_COLOR_FMT_RGB444;
                break;
            default:
                break;
            }
        }
        else
        {
            stSur.enColorFmt = TDE2_COLOR_FMT_ARGB8888;
        }

        stSur.u32Stride = u32RowBytes;
        stSur.u32Width   = width;
        stSur.u32Height  = height;
        stSur.u32PhyAddr = u32Phyaddr;
        PNG_ShowSurface(&stSur, pstDecConfig->u32XPos, pstDecConfig->u32YPos);
    }

    png_destroy_read_struct(&png_ptr, &info_ptr, NULL);

    fclose(fp);

    return 0;
}

static HI_S32 PNG_SearchPng(const struct dirent *dir)
{

    HI_CHAR *p;
    p = strrchr(dir->d_name, '.');
    if (p == HI_NULL)
    {
        return 0;
    }
    if (strcasecmp(p, ".png") == 0)
    {
        return 1;
    }
    return 0;
}

HI_S32 main(void)
{
    HI_U32 u32ImageNum;
    struct dirent **namelist = HI_NULL;
    HI_U32 i;
    HI_CHAR filepath[128];
    PNG_DECPARAM_S DecConfig = {0};
    PNG_RESULT_S HwDecResult = {0};

    DecConfig.bSync   = HI_TRUE;
    DecConfig.u32XPos = 70;
    DecConfig.u32YPos = 20;

    u32ImageNum = scandir(PNG_DIR, &namelist, PNG_SearchPng, alphasort);


    for (i = 0; i < u32ImageNum; i++)
    {		
        memset(filepath, 0, 128);
        strcpy(filepath, PNG_DIR);
        strcat(filepath, namelist[i]->d_name);
        printf("%s\n", namelist[i]->d_name);
        DecConfig.bSoftDec = HI_FALSE;

        PNG_Decode(filepath, &DecConfig, &HwDecResult);

    }

    return 0;
}
