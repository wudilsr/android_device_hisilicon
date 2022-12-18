#ifndef __DRV_DISP_ALG_VZME_H__
#define __DRV_DISP_ALG_VZME_H__

#include <linux/string.h>

#include "hi_type.h"
//#include "pq_hal_zme.h"


#define ALG_V_HZME_PRECISION 1048576
#define ALG_V_VZME_PRECISION 4096
#define VouBitValue(a)  (a)

typedef struct hiALG_MMZ_BUF_S
{
    HI_U32 u32StartVirAddr;
    HI_U32 u32StartPhyAddr;
    HI_U32 u32Size;
} ALG_MMZ_BUF_S;

typedef struct hiALG_RECT_S
{
    HI_S32 s32X;
    HI_S32 s32Y;
    HI_S32 s32Width;
    HI_S32 s32Height;
} ALG_RECT_S;

/*缩放YUV数据结构体444 422 420*/
typedef enum hiPQ_ALG_ZME_FORMAT_E
{
    PQ_ALG_ZME_PIX_FORMAT_SP420 = 0,
    PQ_ALG_ZME_PIX_FORMAT_SP422,
    PQ_ALG_ZME_PIX_FORMAT_SP444,

    PQ_ALG_ZME_PIX_FORMAT_BUTT,
} PQ_ALG_ZME_FORMAT_E;


typedef struct
{
    //Luma-Hor-8T32P
    HI_U32 u32ZmeCoefAddrHL8_1;
    HI_U32 u32ZmeCoefAddrHL8_E1;
    HI_U32 u32ZmeCoefAddrHL8_075;
    HI_U32 u32ZmeCoefAddrHL8_05;
    HI_U32 u32ZmeCoefAddrHL8_033;
    HI_U32 u32ZmeCoefAddrHL8_025;
    HI_U32 u32ZmeCoefAddrHL8_0;

    //Chroma-Hor-4T32P
    HI_U32 u32ZmeCoefAddrHC4_1;
    HI_U32 u32ZmeCoefAddrHC4_E1;
    HI_U32 u32ZmeCoefAddrHC4_075;
    HI_U32 u32ZmeCoefAddrHC4_05;
    HI_U32 u32ZmeCoefAddrHC4_033;
    HI_U32 u32ZmeCoefAddrHC4_025;
    HI_U32 u32ZmeCoefAddrHC4_0;

    //Luma-Vert-6T32P
    HI_U32 u32ZmeCoefAddrVL6_1;
    HI_U32 u32ZmeCoefAddrVL6_E1;
    HI_U32 u32ZmeCoefAddrVL6_075;
    HI_U32 u32ZmeCoefAddrVL6_05;
    HI_U32 u32ZmeCoefAddrVL6_033;
    HI_U32 u32ZmeCoefAddrVL6_025;
    HI_U32 u32ZmeCoefAddrVL6_0;

    //Chroma-Vert-4T32P
    HI_U32 u32ZmeCoefAddrVC4_1;
    HI_U32 u32ZmeCoefAddrVC4_E1;
    HI_U32 u32ZmeCoefAddrVC4_075;
    HI_U32 u32ZmeCoefAddrVC4_05;
    HI_U32 u32ZmeCoefAddrVC4_033;
    HI_U32 u32ZmeCoefAddrVC4_025;
    HI_U32 u32ZmeCoefAddrVC4_0;

    //H_L8C4:Luma-Hor-8T32P Chroma-Hor-4T32P
    HI_U32 u32ZmeCoefAddrHL8C4_1;
    HI_U32 u32ZmeCoefAddrHL8C4_E1;
    HI_U32 u32ZmeCoefAddrHL8C4_075;
    HI_U32 u32ZmeCoefAddrHL8C4_05;
    HI_U32 u32ZmeCoefAddrHL8C4_033;
    HI_U32 u32ZmeCoefAddrHL8C4_025;
    HI_U32 u32ZmeCoefAddrHL8C4_0;

    //V_L6C4:Luma-Vert-6T32P Chroma-Vert-4T32P
    HI_U32 u32ZmeCoefAddrVL6C4_1;
    HI_U32 u32ZmeCoefAddrVL6C4_E1;
    HI_U32 u32ZmeCoefAddrVL6C4_075;
    HI_U32 u32ZmeCoefAddrVL6C4_05;
    HI_U32 u32ZmeCoefAddrVL6C4_033;
    HI_U32 u32ZmeCoefAddrVL6C4_025;
    HI_U32 u32ZmeCoefAddrVL6C4_0;

    //V_L4C4:Luma-Vert-4T32P Chroma-Vert-4T32P
    HI_U32 u32ZmeCoefAddrVL4C4_1;
    HI_U32 u32ZmeCoefAddrVL4C4_E1;
    HI_U32 u32ZmeCoefAddrVL4C4_075;
    HI_U32 u32ZmeCoefAddrVL4C4_05;
    HI_U32 u32ZmeCoefAddrVL4C4_033;
    HI_U32 u32ZmeCoefAddrVL4C4_025;
    HI_U32 u32ZmeCoefAddrVL4C4_0;

    //Luma-Vert-4T32P
    HI_U32 u32ZmeCoefAddrVL4_1;
    HI_U32 u32ZmeCoefAddrVL4_E1;
    HI_U32 u32ZmeCoefAddrVL4_075;
    HI_U32 u32ZmeCoefAddrVL4_05;
    HI_U32 u32ZmeCoefAddrVL4_033;
    HI_U32 u32ZmeCoefAddrVL4_025;
    HI_U32 u32ZmeCoefAddrVL4_0;

    //add from 3798 and HiFoneB2
    //Chroma-Hor-8T32P
    HI_U32 u32ZmeCoefAddrHC8_1;
    HI_U32 u32ZmeCoefAddrHC8_E1;
    HI_U32 u32ZmeCoefAddrHC8_075;
    HI_U32 u32ZmeCoefAddrHC8_05;
    HI_U32 u32ZmeCoefAddrHC8_033;
    HI_U32 u32ZmeCoefAddrHC8_025;
    HI_U32 u32ZmeCoefAddrHC8_0;

    //Chroma-Vert-6T32P
    HI_U32 u32ZmeCoefAddrVC6_1;
    HI_U32 u32ZmeCoefAddrVC6_E1;
    HI_U32 u32ZmeCoefAddrVC6_075;
    HI_U32 u32ZmeCoefAddrVC6_05;
    HI_U32 u32ZmeCoefAddrVC6_033;
    HI_U32 u32ZmeCoefAddrVC6_025;
    HI_U32 u32ZmeCoefAddrVC6_0;

} ALG_VZME_COEF_ADDR_S;

typedef struct
{
    ALG_MMZ_BUF_S stMBuf;
    ALG_VZME_COEF_ADDR_S stZmeCoefAddr;
} ALG_VZME_MEM_S;

typedef struct
{
    HI_U32 u32Ratio;
    HI_U32 u32TapL;
    HI_U32 u32TapC;
} VZME_PICKCOEF_PARA_S;

typedef struct
{
    HI_U32 u32ZmeFrmWIn;      /* zme input frame width*/
    HI_U32 u32ZmeFrmHIn;      /* zme input frame height*/
    HI_U32 u32ZmeFrmWOut;     /* zme output frame width*/
    HI_U32 u32ZmeFrmHOut;     /* zme output frame height*/

    HI_U8 u8ZmeYCFmtIn;       /* video format for zme input: 0-422; 1-420; 2-444*/
    HI_U8 u8ZmeYCFmtOut;      /* video format for zme Output: 0-422; 1-420; 2-444*/

    HI_BOOL bZmeFrmFmtIn;     /* Frame format for zme input: 0-field; 1-frame*/
    HI_BOOL bZmeFrmFmtOut;    /* Frame format for zme Output: 0-field; 1-frame*/
    HI_BOOL bZmeBFIn;         /* Input field polar when input is field format: 0-top field; 1-bottom field*/
    HI_BOOL bZmeBFOut;        /* Output field polar when Output is field format: 0-top field; 1-bottom field*/

    ALG_RECT_S stOriRect;
    HI_U32  u32InRate;        /* Vpss out Rate  RealRate*1000*/
    HI_U32  u32OutRate;       /* Disp Rate      RealRate*1000*/
    HI_BOOL bDispProgressive; /* 1:Progressive  0:Interlace*/
    HI_U32  u32Fidelity;      /* rwzb info >0:is rwzb*/
    /*
     1.OriRect
     2.InFrameRate
     3.OutRate
     4.Out I/P
     */
} ALG_VZME_DRV_PARA_S;

typedef struct Hi_VDP_SR_ZME_COEF_S
{
    HI_S16 s16HLCoef0[8];
    HI_S16 s16HLCoef1[8];
    HI_S16 s16HCCoef0[8];
    HI_S16 s16HCCoef1[8];
    
    HI_S16 s16VLCoef0[6];
    HI_S16 s16VLCoef1[6];
    HI_S16 s16VCCoef0[6];
    HI_S16 s16VCCoef1[6];
    
} VDP_SR_ZME_COEF_S;

typedef struct
{
    HI_BOOL bZmeEnHL;  /* zme enable of horizontal luma: 0-off; 1-on*/
    HI_BOOL bZmeEnHC;
    HI_BOOL bZmeEnVL;
    HI_BOOL bZmeEnVC;

    HI_BOOL bZmeMdHL;  /* zme mode of horizontal luma: 0-copy mode; 1-FIR filter mode*/
    HI_BOOL bZmeMdHC;
    HI_BOOL bZmeMdVL;
    HI_BOOL bZmeMdVC;

    HI_BOOL bZmeMedHL; /* zme Median filter enable of horizontal luma: 0-off; 1-on*/
    HI_BOOL bZmeMedHC;
    HI_BOOL bZmeMedVL;
    HI_BOOL bZmeMedVC;

    HI_S32 s32ZmeOffsetHL;
    HI_S32 s32ZmeOffsetHC;
    HI_S32 s32ZmeOffsetVL;
    HI_S32 s32ZmeOffsetVC;
    HI_S32 s32ZmeOffsetVLBtm;
    HI_S32 s32ZmeOffsetVCBtm;

    HI_U32 u32ZmeWIn;      /* HIFoneB2 does not exist WIn */
    HI_U32 u32ZmeHIn;      /* HIFoneB2 does not exist HIn */
    HI_U32 u32ZmeWOut;
    HI_U32 u32ZmeHOut;

    HI_U32 u32ZmeRatioHL;
    HI_U32 u32ZmeRatioVL;
    HI_U32 u32ZmeRatioHC;
    HI_U32 u32ZmeRatioVC;

    HI_BOOL bZmeOrder;     /* zme order of hzme and vzme: 0-hzme first; 1-vzme first*/
    HI_BOOL bZmeTapVC;     /* zme tap of vertical chroma: 0-4tap; 1-2tap*/

    HI_U8  u8ZmeYCFmtIn;   /* video format for zme input vdp: 0-422; 1-420; 2-444  vpss: 0-420; 1-422; 2-444*/
    HI_U8  u8ZmeYCFmtOut;  /* video format for zme input vdp: 0-422; 1-420; 2-444  vpss: 0-420; 1-422; 2-444*/

    HI_U32 u32ZmeCoefAddrHL;
    HI_U32 u32ZmeCoefAddrHC;
    HI_U32 u32ZmeCoefAddrVL;
    HI_U32 u32ZmeCoefAddrVC;

    VDP_SR_ZME_COEF_S stVdpSrZmeCoef; 
} ALG_VZME_RTL_PARA_S;


typedef enum
{
    VZME_COEF_1         = 0,
    VZME_COEF_E1           ,
    VZME_COEF_075          ,
    VZME_COEF_05           ,
    VZME_COEF_033          ,
    VZME_COEF_025          ,
    VZME_COEF_0            ,
    VZME_COEF_RATIO_BUTT

} VZME_COEF_RATIO_E;

typedef enum
{
    VZME_COEF_8T32P_LH = 0,
    VZME_COEF_6T32P_LV    ,
    VZME_COEF_4T32P_LV    ,
    VZME_COEF_4T32P_CH    ,
    VZME_COEF_4T32P_CV    ,
    VZME_COEF_8T32P_CH    ,
    VZME_COEF_6T32P_CV    ,
    VZME_COEF_TYPE_BUTT
} VZME_COEF_TYPE_E;

typedef enum
{
    VZME_VPSS_COEF_8T32P_LH   = 0,
    VZME_VPSS_COEF_6T32P_LV      ,
    VZME_VPSS_COEF_4T32P_LV      ,
    VZME_VPSS_COEF_4T32P_CH      ,
    VZME_VPSS_COEF_4T32P_CV      ,
    VZME_VPSS_COEF_8T32P_CH      , //add
    VZME_VPSS_COEF_6T32P_CV      , //add
    VZME_VPSS_COEF_TYPE_BUTT
} VZME_VPSS_COEF_TYPE_E;

typedef enum
{
    VDTI_COEF_8T32P_LH  = 0,
    VDTI_COEF_2T32P_LV     ,
    VDTI_COEF_4T32P_CH     ,
    VDTI_COEF_2T32P_CV     ,
    VDTI_COEF_TYPE_BUTT
} VDTI_COEF_TYPE_E;

typedef enum
{
    VZME_TAP_8T32P = 0,
    VZME_TAP_6T32P    ,
    VZME_TAP_4T32P    ,
    VZME_TAP_2T32P    ,
    VZME_TAP_BUTT
} VZME_TAP_E;


typedef struct
{
    HI_S32 bits_0   : 10  ;
    HI_S32 bits_1   : 10  ;
    HI_S32 bits_2   : 10  ;
    HI_S32 bits_32  : 2   ;
    HI_S32 bits_38  : 8   ;
    HI_S32 bits_4   : 10  ;
    HI_S32 bits_5   : 10  ;
    HI_S32 bits_64  : 4   ;
    HI_S32 bits_66  : 6   ;
    HI_S32 bits_7   : 10  ;
    HI_S32 bits_8   : 10  ;
    HI_S32 bits_96  : 6   ;
    HI_S32 bits_94  : 4   ;
    HI_S32 bits_10  : 10  ;
    HI_S32 bits_11  : 10  ;
    HI_S32 bits_12  : 8   ;
} ZME_COEF_BIT_S;

typedef struct
{
    HI_U32          u32Size;
    ZME_COEF_BIT_S  stBit[12];
    HI_S32          s32CoefAttr[51];
} ZME_COEF_BITARRAY_S;


HI_S32  ALG_VZmeVdpComnInit(ALG_VZME_MEM_S* pstVZmeCoefMem);
HI_VOID ALG_VZmeVdpComnDeInit(ALG_VZME_MEM_S* pstVZmeCoefMem);
HI_S32  ALG_VZmeVpssComnInit(ALG_VZME_MEM_S* pstVZmeCoefMem);
HI_VOID ALG_VZmeVpssComnDeInit(ALG_VZME_MEM_S* pstVZmeCoefMem);


HI_VOID ALG_VZmeVdpHQSet(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_VOID ALG_VZmeVdpSQSet(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_VOID ALG_VZmeVdpSQSetSptAddr(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_VOID ALG_VZmeVdpHQSetSptAddr(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_VOID ALG_VZmeComnSet(ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_VOID ALG_VZmeVpssHQSetSptAddr(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);
HI_VOID ALG_VZmeVpssSetSptAddr(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);

//HI_VOID ALG_VZmeVdpSRCoef(VDP_SR_ZME_COEF_S* pstVdpSrZmeCoef);
HI_VOID ALG_VZmeSRSetAddr(ALG_VZME_MEM_S* pstMem, ALG_VZME_DRV_PARA_S* pstZmeDrvPara, ALG_VZME_RTL_PARA_S* pstZmeRtlPara);



#endif  /* endif of '__DRV_DISP_ALG_ZME_H__' */

