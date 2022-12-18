/*!
 ********************************************************************************
 *  Copyright (C), 2012-2014, Hisilicon Tech. Co., Ltd.
 *  \file  pq_hal_csc.c
 *  \brief
 ********************************************************************************
 */

/*-----------------------------------------------------------------------------*/
/* Include Header Files                                                        */
/*-----------------------------------------------------------------------------*/
#ifndef  __PQ_PLATFORM_BOOT__
#include <linux/slab.h>      /* kmalloc() */
#include <linux/string.h>    /* memcpy()  */
#endif
#include "hi_type.h"
#include "hi_debug.h"
#include "pq_hal_csc.h"
#include "pq_hal_comm.h"

static HI_U32 PQ_TRACE_RANGE = HI_LOG_LEVEL_ERROR;

const HI_S32 SIN_TABLE[61] =
{
    -500, -485, -469, -454, -438, -422, -407, -391,
    -374, -358, -342, -325, -309, -292, -276, -259,
    -242, -225, -208, -191, -174, -156, -139, -122,
    -104,  -87,  -70,  -52,  -35,  -17,    0,   17,
    35,    52,   70,    87,  104,  122,  139,  156,
    174,   191,  208,  225,  242,  259,  276,  292,
    309,   325,  342,  358,  374,  391,  407,  422,
    438,   454,  469,  485, 500
};
const HI_U32 COS_TABLE[61] =
{
    866, 875, 883, 891, 899,  906,	914,  921,
    927, 934, 940, 946, 951,  956,	961,  966,
    970, 974, 978, 982, 985,  988,	990,  993,
    995, 996, 998, 999, 999, 1000, 1000, 1000,
    999, 999, 998, 996, 995,  993,	990,  988,
    985, 982, 978, 974, 970,  966,	961,  956,
    951, 946, 940, 934, 927,  921,	914,  906,
    899, 891, 883, 875, 866
};


/**************************************************
CSC Matrix for [YCbCr]->[YCbCr]
**************************************************/

/* SMPTE 170M (i.e. modern SD NTSC) -> BT.709 (i.e. HD) */
CSC_COEF_S CSCTable_NtscSDYCbCr_to_HDYCbCr =
{
    1024,   -88, -204,
    0, 1032,  114,
    0,	60, 964
};

/* BT.470-2 System B, G (i.e. SD Pal) -> BT.709 (i.e. HD) */
CSC_COEF_S CSCTable_PalSDYCbCr_to_HDYCbCr =
{
    1024,  -116, -192,
    0, 1028,  104,
    0,	88, 1100
};

/* SMPTE 240M (i.e. 1987 ATSC HD) -> BT.709 (i.e. HD) */
CSC_COEF_S CSCTable_240MHDYCbCr_to_HDYCbCr =
{
    1024,     0, 0,
    0, 1016, 0,
    0,    1, 948
};

/* FCC (i.e. 1953 NTSC) -> BT.709 (i.e. HD) */
CSC_COEF_S CSCTable_FccSDYCbCr_to_HDYCbCr =
{
    1024,      0,  0,
    56, 1148, -4,
    36,  -12, 1148
};

/* xvYCC BT.601 (i.e. SD) -> to BT.709 (i.e. HD) */
CSC_COEF_S CSCTable_XvYCCSDYCbCr_to_HDYCbCr =
{
    1024, -118, -213,
    0,  1043,  117,
    0,	77, 1050
};

/* BT.709 (i.e. HD) -> to xvYCC BT.601 (i.e. SD) */
CSC_COEF_S CSCTable_HDYCbCr_to_XvYCCSDYCbCr =
{
    1024,   102,  196,
    0, 1014, -113,
    0,  -74, 1007
};

/* FCC (i.e. 1953 NTSC) -> to xvYCC BT.601 (i.e. SD) */
CSC_COEF_S CSCTable_FccSDYCbCr_to_XvYCCSDYCbCr =
{
    1036,	112,  292,
    52, 1140, -176,
    28,	-96, 1444
};

/* BT.470-2 System B, G (i.e. SD Pal) -> xvYCC BT.601 (i.e. SD) */
CSC_COEF_S CSCTable_PalSDYCbCr_to_XvYCCSDYCbCr =
{
    1024,     0,  28,
    0, 1004, -20,
    0,    4, 1072
};

/* SMPTE 170M (i.e. modern SD NTSC)) -> xvYCC BT.601 (i.e. SD) */
CSC_COEF_S CSCTable_NtscSDYCbCr_to_XvYCCSDYCbCr =
{
    1024,	24, -8,
    0, 1016,  4,
    0,  -20, 940
};

/* SMPTE 240M (i.e. 1987 ATSC HD) -> xvYCC BT.601 (i.e. SD) */
CSC_COEF_S CSCTable_240MHDYCbCr_to_XvYCCSDYCbCr =
{
    1024,   104,	180,
    0, 1004, -104,
    0,  -68, 932
};

/* identity matrix */
CSC_COEF_S CSCTable_Identity_YCbCr_to_YCbCr =
{
    1024,     0, 0,
    0, 1024, 0,
    0,    0, 1024
};

/**************************************************
CSC Matrix for [RGB]->[YCbCr]
**************************************************/
/* RGB -> YUV709 (i.e. SD) */
CSC_COEF_S CSCTable_RGB_to_HDYCbCr =
{
    188,   629,  63,
    -103, -347, 450,
    450, -409, -41
};      //range[0,255]->range[16,235]
/*{218, 732, 74,
-118, -394, 512,
512, -465, -47};*/  //range[0,255]->range[0,255]



/* RGB -> YUV601 (i.e. SD) */
CSC_COEF_S CSCTable_RGB_to_XvYCCSDYCbCr =
{
    264,  516, 100,
    -152, -298, 450,
    450, -377, -73
};    //range[0,255]->range[16,235]
/*{306, 601, 117,
   -173, -339, 512,
   512, -429, -83};*/   //range[0,255]->range[0,255]

/* RGB -> YUV709 full (i.e. SD) */
CSC_COEF_S CSCTable_RGB_to_HDYCbCr_Full =
{
    218, 732, 74,
    -118, -394, 512,
    512, -465, -47
};  //range[0,255]->range[0,255]



/* RGB -> YUV601 full(i.e. SD) */
CSC_COEF_S CSCTable_RGB_to_XvYCCSDYCbCr_Full =
{
    306, 601, 117,
    -173, -339, 512,
    512, -429, -83
};   //range[0,255]->range[0,255]


/**************************************************
CSC Matrix for [YCbCr]->[RGB]
**************************************************/

/* BT.709 (i.e. HD) -> RGB */
CSC_COEF_S CSCTable_HDYCbCr_to_RGB =
{
    1192,    0,  1836,
    1192, -218,  -547,
    1192, 2166,     0
};    //range[0,255]->range[16,235]
/*{1024,  0,     1613,
1024, -191, -479,
1024, 1901, 0};*/       //range[0,255]->range[0,255]

/* xvYCC BT.601 (i.e. SD) -> RGB */
CSC_COEF_S CSCTable_XvYCCSDYCbCr_to_RGB =
{
    1192,    0, 1634,
    1192, -400, -833,
    1192, 2066,    0
};     //range[0,255]->range[16,235]
/*{1024,  0,  1436,
1024,  -352,  -731,
1024,  1815,  0};*/     //range[0,255]->range[0,255]

/* BT.709 full(i.e. HD) -> RGB */
CSC_COEF_S CSCTable_HDYCbCr_to_RGB_Full =
{
    1024,  0,     1613,
    1024, -191, -479,
    1024, 1901, 0
};       //range[0,255]->range[0,255]

/* xvYCC BT.601 full(i.e. SD) -> RGB */
CSC_COEF_S CSCTable_XvYCCSDYCbCr_to_RGB_Full =
{
    1024,  0,  1436,
    1024,  -352,  -731,
    1024,  1815,  0
};     //range[0,255]->range[0,255]


/*    {298,	0,	459,
    298, -55, -136,
    298,  541, 0};*/

/**************************************************
CSC Matrix for [RGB]->[RGB]
**************************************************/

/* identity matrix */
CSC_COEF_S CSCTable_Identity_RGB_to_RGB =
{
    1024,     0, 0,
    0, 1024, 0,
    0,    0, 1024
};

/*
    {   256,   0, 0,
        0,   256, 0,
        0,     0, 256 };
 */

/* the compositor color matrices table WITH Color Primaries Matching */
static CSC_COEF_S* CSC_YCbCr_MatrixTbl[][2] =
{
    /* BVDC_P_MatrixCoefficients_eHdmi_RGB = 0 */
    {
        NULL,
    },

    /* BVDC_P_MatrixCoefficients_eItu_R_BT_709, */
    /* BVDC_P_MatrixCoefficients_eXvYCC_709 = 1 */
    {
        &CSCTable_Identity_YCbCr_to_YCbCr,    /* HD -> HD, XvYCC_HD */
        &CSCTable_HDYCbCr_to_XvYCCSDYCbCr     /* HD -> XvYCC_SD */
    },

    /* BVDC_P_MatrixCoefficients_eUnknown = 2 */
    {
        &CSCTable_Identity_YCbCr_to_YCbCr,    /* Identity */
        &CSCTable_Identity_YCbCr_to_YCbCr     /* Identity */
    },

    /* forbidden 3 */
    {
        NULL,
    },

    /* BVDC_P_MatrixCoefficients_eFCC = 4 */
    {
        &CSCTable_FccSDYCbCr_to_HDYCbCr,       /* FCC -> HD, XvYCC_HD */
        &CSCTable_FccSDYCbCr_to_XvYCCSDYCbCr   /* FCC -> XvYCC_SD */
    },

    /* BVDC_P_MatrixCoefficients_eItu_R_BT_470_2_BG = 5 */
    {
        &CSCTable_PalSDYCbCr_to_HDYCbCr,       /* PAL -> HD, XvYCC_HD */
        &CSCTable_PalSDYCbCr_to_XvYCCSDYCbCr   /* PAL -> XvYCC_SD */
    },

    /* BVDC_P_MatrixCoefficients_eSmpte_170M = 6 */
    {
        &CSCTable_NtscSDYCbCr_to_HDYCbCr,      /* NTSC -> HD, XvYCC_HD */
        &CSCTable_NtscSDYCbCr_to_XvYCCSDYCbCr  /* NTSC -> XvYCC_SD */
    },

    /* BVDC_P_MatrixCoefficients_eSmpte_240M = 7 */
    {
        &CSCTable_240MHDYCbCr_to_HDYCbCr,      /* 240M -> HD, XvYCC_HD */
        &CSCTable_240MHDYCbCr_to_XvYCCSDYCbCr  /* 240M -> XvYCC_SD */
    },

    /* BVDC_P_MatrixCoefficients_eXvYCC_601 = 8 */
    {
        &CSCTable_XvYCCSDYCbCr_to_HDYCbCr,     /* XvYCC_SD -> HD, XvYCC_HD */
        &CSCTable_Identity_YCbCr_to_YCbCr      /* XvYCC_SD -> XvYCC_SD */
    }
};

/* the compositor YCbCr to RGB color matrices table */
static CSC_COEF_S* CSC_YCbCr_to_RGBPrim_MatrixTbl[][9] =
{
    /*LIMIT*/
    {
        NULL,                             /* BVDC_P_MatrixCoefficients_eHdmi_RGB = 0 */
        &CSCTable_HDYCbCr_to_RGB,        /* BVDC_P_MatrixCoefficients_eItu_R_BT_709, */
        /* BVDC_P_MatrixCoefficients_eXvYCC_709 = 1 */
        NULL,        /* BVDC_P_MatrixCoefficients_eUnknown = 2 */
        NULL,                             /* forbidden 3 */
        NULL,    /* BVDC_P_MatrixCoefficients_eFCC = 4 */
        NULL,    /* BVDC_P_MatrixCoefficients_eItu_R_BT_470_2_BG = 5 */
        NULL,    /* BVDC_P_MatrixCoefficients_eSmpte_170M = 6 */
        NULL,    /* BVDC_P_MatrixCoefficients_eSmpte_240M = 7 */
        &CSCTable_XvYCCSDYCbCr_to_RGB,     /* BVDC_P_MatrixCoefficients_eXvYCC_601 = 8 */
    },
    /*FULL*/
    {
        NULL,                             /* BVDC_P_MatrixCoefficients_eHdmi_RGB = 0 */
        &CSCTable_HDYCbCr_to_RGB_Full,        /* BVDC_P_MatrixCoefficients_eItu_R_BT_709, */
        /* BVDC_P_MatrixCoefficients_eXvYCC_709 = 1 */
        NULL,        /* BVDC_P_MatrixCoefficients_eUnknown = 2 */
        NULL,                             /* forbidden 3 */
        NULL,    /* BVDC_P_MatrixCoefficients_eFCC = 4 */
        NULL,    /* BVDC_P_MatrixCoefficients_eItu_R_BT_470_2_BG = 5 */
        NULL,    /* BVDC_P_MatrixCoefficients_eSmpte_170M = 6 */
        NULL,    /* BVDC_P_MatrixCoefficients_eSmpte_240M = 7 */
        &CSCTable_XvYCCSDYCbCr_to_RGB_Full,     /* BVDC_P_MatrixCoefficients_eXvYCC_601 = 8 */
    },
};

/* the compositor RGB to YCbCr color matrices table */
static CSC_COEF_S* CSC_RGBPrim_to_YCbCr_MatrixTbl[][2] =
{
    /*LIMIT*/
    {
        &CSCTable_RGB_to_HDYCbCr,        /* HD,Limit*/
        &CSCTable_RGB_to_XvYCCSDYCbCr,     /* SD,Limit */
    },
    /*FULL*/
    {
        &CSCTable_RGB_to_HDYCbCr_Full,        /* HD, Full */
        &CSCTable_RGB_to_XvYCCSDYCbCr_Full,     /* SD,Full */
    }
};

static CSC_MODE_S sg_stCscMode[HAL_DISP_LAYER_BUTT] =
{
    {HI_FALSE, HAL_CSC_BUTT},
    {HI_FALSE, HAL_CSC_BUTT},
    {HI_FALSE, HAL_CSC_BUTT},
    {HI_FALSE, HAL_CSC_BUTT},
    {HI_FALSE, HAL_CSC_BUTT},
  //{HI_FALSE, HAL_CSC_BUTT},
};

/*-----------------------------------------------------------------------------*/
/* Extern Global Variables                                                     */
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/* Extern Function Prototype                                                   */
/*-----------------------------------------------------------------------------*/

/*-----------------------------------------------------------------------------*/
/* Local Function Protype                                                      */
/*-----------------------------------------------------------------------------*/
static HI_S32  PQ_HAL_SetCscCoef(HAL_DISP_LAYER_E enChan, CSC_COEF_S* pstCscCoef);
static HI_S32  PQ_HAL_SetCscDcCoef(HAL_DISP_LAYER_E enLayer, CSC_DCCOEF_S* pstCscCoef);
static HI_VOID PQ_HAL_CalcCSCCoef(CSC_PARA_S* pstCSCParameter, CSC_COEF_S* pstCSCCoef);
static HI_VOID PQ_HAL_CalCSCCoefTprtYCbCrtoRGB(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue, HI_U32 Kr, HI_U32 Kg,
        HI_U32 Kb, CSC_COEF_S* pCSCTable,
        CSC_COEF_S* pDstCSCTable);
static HI_VOID PQ_HAL_CalCTemperatureMat(HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, CSC_COEF_S* pCSCTable,
        CSC_COEF_S* pDstCSCTable);
static HI_VOID PQ_HAL_CalCSCCoefTprtYCbCrtoYCbCr(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue, HI_U32 Kr, HI_U32 Kg,
        HI_U32 Kb, CSC_COEF_S* pCSCTable,
        CSC_COEF_S* pDstCSCTable);
static HI_VOID PQ_HAL_CalCSCCoefTprtRGBtoYCbCr(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue, HI_U32 Kr, HI_U32 Kg,
        HI_U32 Kb, CSC_COEF_S* pCSCTable,
        CSC_COEF_S* pDstCSCTable);
static HI_VOID PQ_HAL_CalCSCCoefTprtRGBtoRGB(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue, HI_U32 Kr, HI_U32 Kg,
        HI_U32 Kb, CSC_COEF_S* pCSCTable,
        CSC_COEF_S* pDstCSCTable);
static HI_VOID PQ_HAL_CalcCscDcCoef(CSC_PARA_S* pstCSCParameter, CSC_DCCOEF_S* pstCscDcCoef);

/*-----------------------------------------------------------------------------*/
/* Interface Functions                                                         */
/*-----------------------------------------------------------------------------*/

/**
 \brief 设置CSC参数;
 \attention \n
无

 \param[in] enDisplayId
 \param[in] pstCSCParameter

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetCSCPictureParam(HAL_DISP_LAYER_E enDisplayId, CSC_PARA_S* pstCSCParameter)
{
    CSC_COEF_S st_csc_coef;
    CSC_DCCOEF_S stDcCoef;

    if (pstCSCParameter == NULL || enDisplayId >= HAL_DISP_LAYER_BUTT)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstCSCParameter is invalid!\n");
        return HI_FAILURE;
    }

    if (pstCSCParameter->u16InputColorSpace == OPTM_CS_eUnknown || pstCSCParameter->u16OutputColorSpace == OPTM_CS_eUnknown)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "unknow color space!\n");
        return HI_FAILURE;
    }

    PQ_HAL_CalcCSCCoef(pstCSCParameter, &st_csc_coef);
    PQ_HAL_CalcCscDcCoef(pstCSCParameter, &stDcCoef);

    PQ_HAL_SetCscDcCoef(enDisplayId, &stDcCoef);
    PQ_HAL_SetCscCoef(enDisplayId, &st_csc_coef);

    //PQ_HAL_EnableCSC(enDisplayId, HI_TRUE);

    return HI_SUCCESS;
}

/**
 \brief 获取CSC转换模式;
 \attention \n
无

 \param[in] enDisplayId
 \param[out] pstCscMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_GetCSCMode(HAL_DISP_LAYER_E enDisplayId, CSC_MODE_S* pstCscMode)
{
    if (pstCscMode == NULL)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstCscMode is NULL!\n");
        return HI_FAILURE;
    }

    pstCscMode->bCSCEn = sg_stCscMode[enDisplayId].bCSCEn;
    pstCscMode->enCSC = sg_stCscMode[enDisplayId].enCSC;
    return HI_SUCCESS;
}

/**
 \brief 设置CSC转换模式;
 \attention \n
无

 \param[in] eLayer
 \param[in] eCSCMode

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_SetCSCMode(HAL_DISP_LAYER_E enLayer, CSC_MODE_E enCscMode)
{
    CSC_COEF_S st_csc_coef;
    CSC_DCCOEF_S stDcCoef;

    if (enLayer >= HAL_DISP_LAYER_BUTT)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "Error, Select Wrong VP Layer ID\n");
        return HI_FAILURE;
    }

    sg_stCscMode[enLayer].enCSC = enCscMode;

    if (enCscMode == HAL_CSC_RGB2YUV_601)//RGB->YUV601 LIMIT
    {
        st_csc_coef.csc_coef00 = (HI_S32)(264);
        st_csc_coef.csc_coef01 = (HI_S32)(516);
        st_csc_coef.csc_coef02 = (HI_S32)(100);

        st_csc_coef.csc_coef10 = (HI_S32)(-152);
        st_csc_coef.csc_coef11 = (HI_S32)(-298);
        st_csc_coef.csc_coef12 = (HI_S32)(450);

        st_csc_coef.csc_coef20 = (HI_S32)(450);
        st_csc_coef.csc_coef21 = (HI_S32)(-377);
        st_csc_coef.csc_coef22 = (HI_S32)(-73);

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = 0;
        stDcCoef.csc_in_dc0 = 0;

        stDcCoef.csc_out_dc2 = 16 * 4;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_601)//YUV601->RGB LIMIT
    {
        st_csc_coef.csc_coef00 = (HI_S32)(1192);
        st_csc_coef.csc_coef01 = (HI_S32)(0);
        st_csc_coef.csc_coef02 = (HI_S32)(1634);

        st_csc_coef.csc_coef10 = (HI_S32)(1192);
        st_csc_coef.csc_coef11 = (HI_S32)(-400);
        st_csc_coef.csc_coef12 = (HI_S32)(-833);

        st_csc_coef.csc_coef20 = (HI_S32)(1192);
        st_csc_coef.csc_coef21 = (HI_S32)(2066);
        st_csc_coef.csc_coef22 = (HI_S32)(0);

        stDcCoef.csc_in_dc2 = -16 * 4;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 0;
        stDcCoef.csc_out_dc1 = 0;
        stDcCoef.csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_709)//RGB->YUV709 LIMIT
    {
        st_csc_coef.csc_coef00 = (HI_S32)(188);
        st_csc_coef.csc_coef01 = (HI_S32)(629);
        st_csc_coef.csc_coef02 = (HI_S32)(63);

        st_csc_coef.csc_coef10 = (HI_S32)(-103);
        st_csc_coef.csc_coef11 = (HI_S32)(-347);
        st_csc_coef.csc_coef12 = (HI_S32)(450);

        st_csc_coef.csc_coef20 = (HI_S32)(450);
        st_csc_coef.csc_coef21 = (HI_S32)(-409);
        st_csc_coef.csc_coef22 = (HI_S32)(-41);

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = 0;
        stDcCoef.csc_in_dc0 = 0;

        stDcCoef.csc_out_dc2 = 16 * 4;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_709)//YUV709->RGB LIMIT
    {
        st_csc_coef.csc_coef00 = (HI_S32)(1192);
        st_csc_coef.csc_coef01 = (HI_S32)(0);
        st_csc_coef.csc_coef02 = (HI_S32)(1836);

        st_csc_coef.csc_coef10 = (HI_S32)(1192);
        st_csc_coef.csc_coef11 = (HI_S32)(-218);
        st_csc_coef.csc_coef12 = (HI_S32)(-547);

        st_csc_coef.csc_coef20 = (HI_S32)(1192);
        st_csc_coef.csc_coef21 = (HI_S32)(2166);
        st_csc_coef.csc_coef22 = (HI_S32)(0);

        stDcCoef.csc_in_dc2 = -16 * 4;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 0;
        stDcCoef.csc_out_dc1 = 0;
        stDcCoef.csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV_709_601)
    {
        st_csc_coef.csc_coef00 = (HI_S32)(1024);
        st_csc_coef.csc_coef01 = (HI_S32)(102);
        st_csc_coef.csc_coef02 = (HI_S32)(196);

        st_csc_coef.csc_coef10 = (HI_S32)(0);
        st_csc_coef.csc_coef11 = (HI_S32)(1014);
        st_csc_coef.csc_coef12 = (HI_S32)(-113);

        st_csc_coef.csc_coef20 = (HI_S32)(0);
        st_csc_coef.csc_coef21 = (HI_S32)(-74);
        st_csc_coef.csc_coef22 = (HI_S32)(1007);

        stDcCoef.csc_in_dc2 = -16 * 4;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 16 * 4;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV_601_709)
    {
        st_csc_coef.csc_coef00 = (HI_S32)(1024);
        st_csc_coef.csc_coef01 = (HI_S32)(-118);
        st_csc_coef.csc_coef02 = (HI_S32)(-213);

        st_csc_coef.csc_coef10 = (HI_S32)(0);
        st_csc_coef.csc_coef11 = (HI_S32)(1043);
        st_csc_coef.csc_coef12 = (HI_S32)(117);

        st_csc_coef.csc_coef20 = (HI_S32)(0);
        st_csc_coef.csc_coef21 = (HI_S32)(77);
        st_csc_coef.csc_coef22 = (HI_S32)(1050);

        stDcCoef.csc_in_dc2 = -16 * 4;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 16 * 4;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV)
    {
        st_csc_coef.csc_coef00 = 1024;
        st_csc_coef.csc_coef01 = 0;
        st_csc_coef.csc_coef02 = 0;

        st_csc_coef.csc_coef10 = 0;
        st_csc_coef.csc_coef11 = 1024;
        st_csc_coef.csc_coef12 = 0;

        st_csc_coef.csc_coef20 = 0;
        st_csc_coef.csc_coef21 = 0;
        st_csc_coef.csc_coef22 = 1024;

        stDcCoef.csc_in_dc2 = -16 * 4;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 16 * 4;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_601_FULL)//YUV601->RGB FULL
    {
        st_csc_coef.csc_coef00 = (HI_S32)(1024);
        st_csc_coef.csc_coef01 = (HI_S32)(0);
        st_csc_coef.csc_coef02 = (HI_S32)(1436);

        st_csc_coef.csc_coef10 = (HI_S32)(1024);
        st_csc_coef.csc_coef11 = (HI_S32)(-352);
        st_csc_coef.csc_coef12 = (HI_S32)(-731);

        st_csc_coef.csc_coef20 = (HI_S32)(1024);
        st_csc_coef.csc_coef21 = (HI_S32)(1815);
        st_csc_coef.csc_coef22 = (HI_S32)(0);

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 0;
        stDcCoef.csc_out_dc1 = 0;
        stDcCoef.csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_709_FULL)//YUV709->RGB FULL
    {
        st_csc_coef.csc_coef00 = (HI_S32)(1024);
        st_csc_coef.csc_coef01 = (HI_S32)(0);
        st_csc_coef.csc_coef02 = (HI_S32)(1613);

        st_csc_coef.csc_coef10 = (HI_S32)(1024);
        st_csc_coef.csc_coef11 = (HI_S32)(-191);
        st_csc_coef.csc_coef12 = (HI_S32)(-479);

        st_csc_coef.csc_coef20 = (HI_S32)(1024);
        st_csc_coef.csc_coef21 = (HI_S32)(1901);
        st_csc_coef.csc_coef22 = (HI_S32)(0);

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 0;
        stDcCoef.csc_out_dc1 = 0;
        stDcCoef.csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_601_FULL)//RGB->YUV601 FULL
    {
        st_csc_coef.csc_coef00 = (HI_S32)(306);
        st_csc_coef.csc_coef01 = (HI_S32)(601);
        st_csc_coef.csc_coef02 = (HI_S32)(117);

        st_csc_coef.csc_coef10 = (HI_S32)(-173);
        st_csc_coef.csc_coef11 = (HI_S32)(-339);
        st_csc_coef.csc_coef12 = (HI_S32)(512);

        st_csc_coef.csc_coef20 = (HI_S32)(512);
        st_csc_coef.csc_coef21 = (HI_S32)(-429);
        st_csc_coef.csc_coef22 = (HI_S32)(-83);

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = 0;
        stDcCoef.csc_in_dc0 = 0;

        stDcCoef.csc_out_dc2 = 0;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_709_FULL)//RGB->YUV709 FULL
    {
        st_csc_coef.csc_coef00 = (HI_S32)(218);
        st_csc_coef.csc_coef01 = (HI_S32)(732);
        st_csc_coef.csc_coef02 = (HI_S32)(74);

        st_csc_coef.csc_coef10 = (HI_S32)(-118);
        st_csc_coef.csc_coef11 = (HI_S32)(-394);
        st_csc_coef.csc_coef12 = (HI_S32)(512);

        st_csc_coef.csc_coef20 = (HI_S32)(512);
        st_csc_coef.csc_coef21 = (HI_S32)(-465);
        st_csc_coef.csc_coef22 = (HI_S32)(-47);

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = 0;
        stDcCoef.csc_in_dc0 = 0;

        stDcCoef.csc_out_dc2 = 0;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_RGB2RGB)
    {
        st_csc_coef.csc_coef00 = 1024;
        st_csc_coef.csc_coef01 = 0;
        st_csc_coef.csc_coef02 = 0;

        st_csc_coef.csc_coef10 = 0;
        st_csc_coef.csc_coef11 = 1024;
        st_csc_coef.csc_coef12 = 0;

        st_csc_coef.csc_coef20 = 0;
        st_csc_coef.csc_coef21 = 0;
        st_csc_coef.csc_coef22 = 1024;

        stDcCoef.csc_in_dc2 = 0;
        stDcCoef.csc_in_dc1 = 0;
        stDcCoef.csc_in_dc0 = 0;

        stDcCoef.csc_out_dc2 = 2;
        stDcCoef.csc_out_dc1 = 2;
        stDcCoef.csc_out_dc0 = 2;
    }
    else
    {
        st_csc_coef.csc_coef00 = 1 * 1024;
        st_csc_coef.csc_coef01 = 0 * 1024;
        st_csc_coef.csc_coef02 = 0 * 1024;

        st_csc_coef.csc_coef10 = 0 * 1024;
        st_csc_coef.csc_coef11 = 1 * 1024;
        st_csc_coef.csc_coef12 = 0 * 1024;

        st_csc_coef.csc_coef20 = 0 * 1024;
        st_csc_coef.csc_coef21 = 0 * 1024;
        st_csc_coef.csc_coef22 = 1 * 1024;

        stDcCoef.csc_in_dc2 = -16 * 4;
        stDcCoef.csc_in_dc1 = -128 * 4;
        stDcCoef.csc_in_dc0 = -128 * 4;

        stDcCoef.csc_out_dc2 = 16 * 4;
        stDcCoef.csc_out_dc1 = 128 * 4;
        stDcCoef.csc_out_dc0 = 128 * 4;
    }

    PQ_HAL_SetCscCoef(enLayer, &st_csc_coef);

    PQ_HAL_SetCscDcCoef(enLayer, &stDcCoef);

    return HI_SUCCESS;
}

/**
 \brief 打开CSC模块
 \attention \n
无

 \param[in] enLayer
 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_HAL_EnableCSC(HAL_DISP_LAYER_E enLayer, HI_BOOL bCscEn)
{
    S_VDP_REGS_TYPE* pstVDPReg = NULL;
    U_VP0_CSC0_IDC VP0_CSC0_IDC;
    U_VP0_CSC1_IDC VP0_CSC1_IDC;
    U_V0_CSC_IDC V0_CSC_IDC;

    if (enLayer >= HAL_DISP_LAYER_BUTT)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "Error, Select Wrong VP Layer ID\n");
        return HI_FAILURE;
    }

    sg_stCscMode[enLayer].bCSCEn = bCscEn;
    pstVDPReg = PQ_HAL_GetVdpReg();

    if (enLayer == HAL_DISP_LAYER_V0)
    {
        VP0_CSC0_IDC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_IDC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_IDC.bits.csc_en = bCscEn;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_IDC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_IDC.u32);
    }
    else if (enLayer == HAL_DISP_LAYER_V1)
    {
        VP0_CSC1_IDC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_IDC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_IDC.bits.csc_en = bCscEn;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_IDC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_IDC.u32);
    }
    else if ((enLayer >= HAL_DISP_LAYER_V2)&& (enLayer < HAL_DISP_LAYER_BUTT))
    {
        V0_CSC_IDC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_IDC.u32) + enLayer * VDP_VID_OFFSET);
        V0_CSC_IDC.bits.csc_en = bCscEn;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_IDC.u32) + enLayer * VDP_VID_OFFSET), V0_CSC_IDC.u32);
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_GetCscCoef(CSC_MODE_E enCscMode, CSC_COEF_S* pstCscCoef, CSC_DCCOEF_S* pstCscDCCoef)
{
    if (pstCscCoef == NULL || pstCscDCCoef == NULL)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstCscCoef is NULL!\n");
        return HI_FAILURE;
    }

    if (enCscMode == HAL_CSC_RGB2YUV_601)//RGB->YUV601 LIMIT
    {
        pstCscCoef->csc_coef00 = (HI_S32)(264);
        pstCscCoef->csc_coef01 = (HI_S32)(516);
        pstCscCoef->csc_coef02 = (HI_S32)(100);

        pstCscCoef->csc_coef10 = (HI_S32)(-152);
        pstCscCoef->csc_coef11 = (HI_S32)(-298);
        pstCscCoef->csc_coef12 = (HI_S32)(450);

        pstCscCoef->csc_coef20 = (HI_S32)(450);
        pstCscCoef->csc_coef21 = (HI_S32)(-377);
        pstCscCoef->csc_coef22 = (HI_S32)(-73);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 16 * 4;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_601)//YUV601->RGB LIMIT
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1192);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1634);

        pstCscCoef->csc_coef10 = (HI_S32)(1192);
        pstCscCoef->csc_coef11 = (HI_S32)(-400);
        pstCscCoef->csc_coef12 = (HI_S32)(-833);

        pstCscCoef->csc_coef20 = (HI_S32)(1192);
        pstCscCoef->csc_coef21 = (HI_S32)(2066);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = -16 * 4;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_709)//RGB->YUV709 LIMIT
    {
        pstCscCoef->csc_coef00 = (HI_S32)(188);
        pstCscCoef->csc_coef01 = (HI_S32)(629);
        pstCscCoef->csc_coef02 = (HI_S32)(63);

        pstCscCoef->csc_coef10 = (HI_S32)(-103);
        pstCscCoef->csc_coef11 = (HI_S32)(-347);
        pstCscCoef->csc_coef12 = (HI_S32)(450);

        pstCscCoef->csc_coef20 = (HI_S32)(450);
        pstCscCoef->csc_coef21 = (HI_S32)(-409);
        pstCscCoef->csc_coef22 = (HI_S32)(-41);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 16 * 4;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_709)//YUV709->RGB LIMIT
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1192);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1836);

        pstCscCoef->csc_coef10 = (HI_S32)(1192);
        pstCscCoef->csc_coef11 = (HI_S32)(-218);
        pstCscCoef->csc_coef12 = (HI_S32)(-547);

        pstCscCoef->csc_coef20 = (HI_S32)(1192);
        pstCscCoef->csc_coef21 = (HI_S32)(2166);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = -16 * 4;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV_709_601)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(102);
        pstCscCoef->csc_coef02 = (HI_S32)(196);

        pstCscCoef->csc_coef10 = (HI_S32)(0);
        pstCscCoef->csc_coef11 = (HI_S32)(1014);
        pstCscCoef->csc_coef12 = (HI_S32)(-113);

        pstCscCoef->csc_coef20 = (HI_S32)(0);
        pstCscCoef->csc_coef21 = (HI_S32)(-74);
        pstCscCoef->csc_coef22 = (HI_S32)(1007);

        pstCscDCCoef->csc_in_dc2 = -16 * 4;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 16 * 4;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV_601_709)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(-118);
        pstCscCoef->csc_coef02 = (HI_S32)(-213);

        pstCscCoef->csc_coef10 = (HI_S32)(0);
        pstCscCoef->csc_coef11 = (HI_S32)(1043);
        pstCscCoef->csc_coef12 = (HI_S32)(117);

        pstCscCoef->csc_coef20 = (HI_S32)(0);
        pstCscCoef->csc_coef21 = (HI_S32)(77);
        pstCscCoef->csc_coef22 = (HI_S32)(1050);

        pstCscDCCoef->csc_in_dc2 = -16 * 4;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 16 * 4;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV)
    {
        pstCscCoef->csc_coef00 = 1024;
        pstCscCoef->csc_coef01 = 0;
        pstCscCoef->csc_coef02 = 0;

        pstCscCoef->csc_coef10 = 0;
        pstCscCoef->csc_coef11 = 1024;
        pstCscCoef->csc_coef12 = 0;

        pstCscCoef->csc_coef20 = 0;
        pstCscCoef->csc_coef21 = 0;
        pstCscCoef->csc_coef22 = 1024;

        pstCscDCCoef->csc_in_dc2 = -16 * 4;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 16 * 4;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_601_FULL)//YUV601->RGB FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1436);

        pstCscCoef->csc_coef10 = (HI_S32)(1024);
        pstCscCoef->csc_coef11 = (HI_S32)(-352);
        pstCscCoef->csc_coef12 = (HI_S32)(-731);

        pstCscCoef->csc_coef20 = (HI_S32)(1024);
        pstCscCoef->csc_coef21 = (HI_S32)(1815);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_709_FULL)//YUV709->RGB FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1613);

        pstCscCoef->csc_coef10 = (HI_S32)(1024);
        pstCscCoef->csc_coef11 = (HI_S32)(-191);
        pstCscCoef->csc_coef12 = (HI_S32)(-479);

        pstCscCoef->csc_coef20 = (HI_S32)(1024);
        pstCscCoef->csc_coef21 = (HI_S32)(1901);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_601_FULL)//RGB->YUV601 FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(306);
        pstCscCoef->csc_coef01 = (HI_S32)(601);
        pstCscCoef->csc_coef02 = (HI_S32)(117);

        pstCscCoef->csc_coef10 = (HI_S32)(-173);
        pstCscCoef->csc_coef11 = (HI_S32)(-339);
        pstCscCoef->csc_coef12 = (HI_S32)(512);

        pstCscCoef->csc_coef20 = (HI_S32)(512);
        pstCscCoef->csc_coef21 = (HI_S32)(-429);
        pstCscCoef->csc_coef22 = (HI_S32)(-83);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_709_FULL)//RGB->YUV709 FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(218);
        pstCscCoef->csc_coef01 = (HI_S32)(732);
        pstCscCoef->csc_coef02 = (HI_S32)(74);

        pstCscCoef->csc_coef10 = (HI_S32)(-118);
        pstCscCoef->csc_coef11 = (HI_S32)(-394);
        pstCscCoef->csc_coef12 = (HI_S32)(512);

        pstCscCoef->csc_coef20 = (HI_S32)(512);
        pstCscCoef->csc_coef21 = (HI_S32)(-465);
        pstCscCoef->csc_coef22 = (HI_S32)(-47);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    else if (enCscMode == HAL_CSC_RGB2RGB)
    {
        pstCscCoef->csc_coef00 = 1024;
        pstCscCoef->csc_coef01 = 0;
        pstCscCoef->csc_coef02 = 0;

        pstCscCoef->csc_coef10 = 0;
        pstCscCoef->csc_coef11 = 1024;
        pstCscCoef->csc_coef12 = 0;

        pstCscCoef->csc_coef20 = 0;
        pstCscCoef->csc_coef21 = 0;
        pstCscCoef->csc_coef22 = 1024;

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 2;
        pstCscDCCoef->csc_out_dc1 = 2;
        pstCscDCCoef->csc_out_dc0 = 2;
    }
    else
    {
        pstCscCoef->csc_coef00 = 1 * 1024;
        pstCscCoef->csc_coef01 = 0 * 1024;
        pstCscCoef->csc_coef02 = 0 * 1024;

        pstCscCoef->csc_coef10 = 0 * 1024;
        pstCscCoef->csc_coef11 = 1 * 1024;
        pstCscCoef->csc_coef12 = 0 * 1024;

        pstCscCoef->csc_coef20 = 0 * 1024;
        pstCscCoef->csc_coef21 = 0 * 1024;
        pstCscCoef->csc_coef22 = 1 * 1024;

        pstCscDCCoef->csc_in_dc2 = -16 * 4;
        pstCscDCCoef->csc_in_dc1 = -128 * 4;
        pstCscDCCoef->csc_in_dc0 = -128 * 4;

        pstCscDCCoef->csc_out_dc2 = 16 * 4;
        pstCscDCCoef->csc_out_dc1 = 128 * 4;
        pstCscDCCoef->csc_out_dc0 = 128 * 4;
    }
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_Get8BitCscCoef(CSC_MODE_E enCscMode, CSC_COEF_S* pstCscCoef, CSC_DCCOEF_S* pstCscDCCoef)
{
    if (pstCscCoef == NULL || pstCscDCCoef == NULL)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "pstCscCoef is NULL!\n");
        return HI_FAILURE;
    }

    if (enCscMode == HAL_CSC_RGB2YUV_601)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(264);
        pstCscCoef->csc_coef01 = (HI_S32)(516);
        pstCscCoef->csc_coef02 = (HI_S32)(100);

        pstCscCoef->csc_coef10 = (HI_S32)(-152);
        pstCscCoef->csc_coef11 = (HI_S32)(-298);
        pstCscCoef->csc_coef12 = (HI_S32)(450);

        pstCscCoef->csc_coef20 = (HI_S32)(450);
        pstCscCoef->csc_coef21 = (HI_S32)(-377);
        pstCscCoef->csc_coef22 = (HI_S32)(-73);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 16;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_601)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1192);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1634);

        pstCscCoef->csc_coef10 = (HI_S32)(1192);
        pstCscCoef->csc_coef11 = (HI_S32)(-400);
        pstCscCoef->csc_coef12 = (HI_S32)(-833);

        pstCscCoef->csc_coef20 = (HI_S32)(1192);
        pstCscCoef->csc_coef21 = (HI_S32)(2066);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = -16;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_709)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(188);
        pstCscCoef->csc_coef01 = (HI_S32)(629);
        pstCscCoef->csc_coef02 = (HI_S32)(63);

        pstCscCoef->csc_coef10 = (HI_S32)(-103);
        pstCscCoef->csc_coef11 = (HI_S32)(-347);
        pstCscCoef->csc_coef12 = (HI_S32)(450);

        pstCscCoef->csc_coef20 = (HI_S32)(450);
        pstCscCoef->csc_coef21 = (HI_S32)(-409);
        pstCscCoef->csc_coef22 = (HI_S32)(-41);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 16;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_709)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1192);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1836);

        pstCscCoef->csc_coef10 = (HI_S32)(1192);
        pstCscCoef->csc_coef11 = (HI_S32)(-218);
        pstCscCoef->csc_coef12 = (HI_S32)(-547);

        pstCscCoef->csc_coef20 = (HI_S32)(1192);
        pstCscCoef->csc_coef21 = (HI_S32)(2166);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = -16;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV_709_601)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(102);
        pstCscCoef->csc_coef02 = (HI_S32)(196);

        pstCscCoef->csc_coef10 = (HI_S32)(0);
        pstCscCoef->csc_coef11 = (HI_S32)(1014);
        pstCscCoef->csc_coef12 = (HI_S32)(-113);

        pstCscCoef->csc_coef20 = (HI_S32)(0);
        pstCscCoef->csc_coef21 = (HI_S32)(-74);
        pstCscCoef->csc_coef22 = (HI_S32)(1007);

        pstCscDCCoef->csc_in_dc2 = -16;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 16;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV_601_709)
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(-118);
        pstCscCoef->csc_coef02 = (HI_S32)(-213);

        pstCscCoef->csc_coef10 = (HI_S32)(0);
        pstCscCoef->csc_coef11 = (HI_S32)(1043);
        pstCscCoef->csc_coef12 = (HI_S32)(117);

        pstCscCoef->csc_coef20 = (HI_S32)(0);
        pstCscCoef->csc_coef21 = (HI_S32)(77);
        pstCscCoef->csc_coef22 = (HI_S32)(1050);

        pstCscDCCoef->csc_in_dc2 = -16;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 16;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_YUV2YUV)
    {
        pstCscCoef->csc_coef00 = 1024;
        pstCscCoef->csc_coef01 = 0;
        pstCscCoef->csc_coef02 = 0;

        pstCscCoef->csc_coef10 = 0;
        pstCscCoef->csc_coef11 = 1024;
        pstCscCoef->csc_coef12 = 0;

        pstCscCoef->csc_coef20 = 0;
        pstCscCoef->csc_coef21 = 0;
        pstCscCoef->csc_coef22 = 1024;

        pstCscDCCoef->csc_in_dc2 = -16;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 16;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_601_FULL)//YUV601->RGB FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1436);

        pstCscCoef->csc_coef10 = (HI_S32)(1024);
        pstCscCoef->csc_coef11 = (HI_S32)(-352);
        pstCscCoef->csc_coef12 = (HI_S32)(-731);

        pstCscCoef->csc_coef20 = (HI_S32)(1024);
        pstCscCoef->csc_coef21 = (HI_S32)(1815);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_YUV2RGB_709_FULL)//YUV709->RGB FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(1024);
        pstCscCoef->csc_coef01 = (HI_S32)(0);
        pstCscCoef->csc_coef02 = (HI_S32)(1613);

        pstCscCoef->csc_coef10 = (HI_S32)(1024);
        pstCscCoef->csc_coef11 = (HI_S32)(-191);
        pstCscCoef->csc_coef12 = (HI_S32)(-479);

        pstCscCoef->csc_coef20 = (HI_S32)(1024);
        pstCscCoef->csc_coef21 = (HI_S32)(1901);
        pstCscCoef->csc_coef22 = (HI_S32)(0);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 0;
        pstCscDCCoef->csc_out_dc0 = 0;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_601_FULL)//RGB->YUV601 FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(306);
        pstCscCoef->csc_coef01 = (HI_S32)(601);
        pstCscCoef->csc_coef02 = (HI_S32)(117);

        pstCscCoef->csc_coef10 = (HI_S32)(-173);
        pstCscCoef->csc_coef11 = (HI_S32)(-339);
        pstCscCoef->csc_coef12 = (HI_S32)(512);

        pstCscCoef->csc_coef20 = (HI_S32)(512);
        pstCscCoef->csc_coef21 = (HI_S32)(-429);
        pstCscCoef->csc_coef22 = (HI_S32)(-83);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_RGB2YUV_709_FULL)//RGB->YUV709 FULL
    {
        pstCscCoef->csc_coef00 = (HI_S32)(218);
        pstCscCoef->csc_coef01 = (HI_S32)(732);
        pstCscCoef->csc_coef02 = (HI_S32)(74);

        pstCscCoef->csc_coef10 = (HI_S32)(-118);
        pstCscCoef->csc_coef11 = (HI_S32)(-394);
        pstCscCoef->csc_coef12 = (HI_S32)(512);

        pstCscCoef->csc_coef20 = (HI_S32)(512);
        pstCscCoef->csc_coef21 = (HI_S32)(-465);
        pstCscCoef->csc_coef22 = (HI_S32)(-47);

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 0;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    else if (enCscMode == HAL_CSC_RGB2RGB)
    {
        pstCscCoef->csc_coef00 = 1024;
        pstCscCoef->csc_coef01 = 0;
        pstCscCoef->csc_coef02 = 0;

        pstCscCoef->csc_coef10 = 0;
        pstCscCoef->csc_coef11 = 1024;
        pstCscCoef->csc_coef12 = 0;

        pstCscCoef->csc_coef20 = 0;
        pstCscCoef->csc_coef21 = 0;
        pstCscCoef->csc_coef22 = 1024;

        pstCscDCCoef->csc_in_dc2 = 0;
        pstCscDCCoef->csc_in_dc1 = 0;
        pstCscDCCoef->csc_in_dc0 = 0;

        pstCscDCCoef->csc_out_dc2 = 2;
        pstCscDCCoef->csc_out_dc1 = 2;
        pstCscDCCoef->csc_out_dc0 = 2;
    }
    else
    {
        pstCscCoef->csc_coef00 = 1 * 1024;
        pstCscCoef->csc_coef01 = 0 * 1024;
        pstCscCoef->csc_coef02 = 0 * 1024;

        pstCscCoef->csc_coef10 = 0 * 1024;
        pstCscCoef->csc_coef11 = 1 * 1024;
        pstCscCoef->csc_coef12 = 0 * 1024;

        pstCscCoef->csc_coef20 = 0 * 1024;
        pstCscCoef->csc_coef21 = 0 * 1024;
        pstCscCoef->csc_coef22 = 1 * 1024;

        pstCscDCCoef->csc_in_dc2 = -16;
        pstCscDCCoef->csc_in_dc1 = -128;
        pstCscDCCoef->csc_in_dc0 = -128;

        pstCscDCCoef->csc_out_dc2 = 16;
        pstCscDCCoef->csc_out_dc1 = 128;
        pstCscDCCoef->csc_out_dc0 = 128;
    }
    
    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetCscCoef(HAL_DISP_LAYER_E enChan, CSC_COEF_S* pstCscCoef)
{
    S_VDP_REGS_TYPE* pstVDPReg = NULL;
    U_VP0_CSC0_P0 VP0_CSC0_P0;
    U_VP0_CSC0_P1 VP0_CSC0_P1;
    U_VP0_CSC0_P2 VP0_CSC0_P2;
    U_VP0_CSC0_P3 VP0_CSC0_P3;
    U_VP0_CSC0_P4 VP0_CSC0_P4;
    U_VP0_CSC1_P0 VP0_CSC1_P0;
    U_VP0_CSC1_P1 VP0_CSC1_P1;
    U_VP0_CSC1_P2 VP0_CSC1_P2;
    U_VP0_CSC1_P3 VP0_CSC1_P3;
    U_VP0_CSC1_P4 VP0_CSC1_P4;
    U_V0_CSC_P0 V0_CSC_P0;
    U_V0_CSC_P1 V0_CSC_P1;
    U_V0_CSC_P2 V0_CSC_P2;
    U_V0_CSC_P3 V0_CSC_P3;
    U_V0_CSC_P4 V0_CSC_P4;

    if (enChan >= HAL_DISP_LAYER_BUTT)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "Error,Select Wrong VP layer!\n");
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    if (enChan == HAL_DISP_LAYER_V0)
    {
        VP0_CSC0_P0.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_P0.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_P0.bits.cscp00 = pstCscCoef->csc_coef00;
        VP0_CSC0_P0.bits.cscp01 = pstCscCoef->csc_coef01;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_P0.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_P0.u32);

        VP0_CSC0_P1.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_P1.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_P1.bits.cscp02 = pstCscCoef->csc_coef02;
        VP0_CSC0_P1.bits.cscp10 = pstCscCoef->csc_coef10;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_P1.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_P1.u32);

        VP0_CSC0_P2.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_P2.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_P2.bits.cscp11 = pstCscCoef->csc_coef11;
        VP0_CSC0_P2.bits.cscp12 = pstCscCoef->csc_coef12;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_P2.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_P2.u32);

        VP0_CSC0_P3.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_P3.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_P3.bits.cscp20 = pstCscCoef->csc_coef20;
        VP0_CSC0_P3.bits.cscp21 = pstCscCoef->csc_coef21;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_P3.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_P3.u32);

        VP0_CSC0_P4.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_P4.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_P4.bits.cscp22 = pstCscCoef->csc_coef22;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_P4.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_P4.u32);
    }
    else if (enChan == HAL_DISP_LAYER_V1)
    {
        VP0_CSC1_P0.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_P0.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_P0.bits.cscp00 = pstCscCoef->csc_coef00;
        VP0_CSC1_P0.bits.cscp01 = pstCscCoef->csc_coef01;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_P0.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_P0.u32);
        VP0_CSC1_P1.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_P1.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_P1.bits.cscp02 = pstCscCoef->csc_coef02;
        VP0_CSC1_P1.bits.cscp10 = pstCscCoef->csc_coef10;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_P1.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_P1.u32);
        VP0_CSC1_P2.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_P2.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_P2.bits.cscp11 = pstCscCoef->csc_coef11;
        VP0_CSC1_P2.bits.cscp12 = pstCscCoef->csc_coef12;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_P2.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_P2.u32);
        VP0_CSC1_P3.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_P3.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_P3.bits.cscp20 = pstCscCoef->csc_coef20;
        VP0_CSC1_P3.bits.cscp21 = pstCscCoef->csc_coef21;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_P3.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_P3.u32);
        VP0_CSC1_P4.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_P4.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_P4.bits.cscp22 = pstCscCoef->csc_coef22;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_P4.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_P4.u32);
    }
    else if ((enChan >= HAL_DISP_LAYER_V2) && (enChan < HAL_DISP_LAYER_BUTT))
    {
        V0_CSC_P0.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_P0.u32) + enChan * VDP_VID_OFFSET);
        V0_CSC_P0.bits.cscp00 = pstCscCoef->csc_coef00;
        V0_CSC_P0.bits.cscp01 = pstCscCoef->csc_coef01;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_P0.u32) + enChan *VDP_VID_OFFSET), V0_CSC_P0.u32);

        V0_CSC_P1.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_P1.u32) + enChan  * VDP_VID_OFFSET);
        V0_CSC_P1.bits.cscp02 = pstCscCoef->csc_coef02;
        V0_CSC_P1.bits.cscp10 = pstCscCoef->csc_coef10;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_P1.u32) + enChan *VDP_VID_OFFSET), V0_CSC_P1.u32);

        V0_CSC_P2.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_P2.u32) + enChan  * VDP_VID_OFFSET);
        V0_CSC_P2.bits.cscp11 = pstCscCoef->csc_coef11;
        V0_CSC_P2.bits.cscp12 = pstCscCoef->csc_coef12;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_P2.u32) + enChan *VDP_VID_OFFSET), V0_CSC_P2.u32);

        V0_CSC_P3.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_P3.u32) + enChan  * VDP_VID_OFFSET);
        V0_CSC_P3.bits.cscp20 = pstCscCoef->csc_coef20;
        V0_CSC_P3.bits.cscp21 = pstCscCoef->csc_coef21;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_P3.u32) + enChan *VDP_VID_OFFSET), V0_CSC_P3.u32);

        V0_CSC_P4.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_P4.u32) + enChan * VDP_VID_OFFSET);
        V0_CSC_P4.bits.cscp22 = pstCscCoef->csc_coef22;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_P4.u32) + enChan *VDP_VID_OFFSET), V0_CSC_P4.u32);
    }

    return HI_SUCCESS;
}

HI_S32 PQ_HAL_SetCscDcCoef(HAL_DISP_LAYER_E enChan, CSC_DCCOEF_S* pstCscCoef)
{
    S_VDP_REGS_TYPE* pstVDPReg = NULL;
    U_VP0_CSC0_IDC  VP0_CSC0_IDC;
    U_VP0_CSC0_ODC  VP0_CSC0_ODC;
    U_VP0_CSC0_IODC VP0_CSC0_IODC;

    U_VP0_CSC1_IDC  VP0_CSC1_IDC;
    U_VP0_CSC1_ODC  VP0_CSC1_ODC;
    U_VP0_CSC1_IODC VP0_CSC1_IODC;

    U_V0_CSC_IDC  V0_CSC_IDC;
    U_V0_CSC_ODC  V0_CSC_ODC;
    U_V0_CSC_IODC V0_CSC_IODC;

    if (enChan >= HAL_DISP_LAYER_BUTT)
    {
        PQ_TRACE(HI_LOG_LEVEL_ERROR, PQ_TRACE_RANGE, "Error,Select Wrong VP layer!\n");
        return HI_FAILURE;
    }

    pstVDPReg = PQ_HAL_GetVdpReg();
    if (enChan == HAL_DISP_LAYER_V0)
    {
        VP0_CSC0_IDC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_IDC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_IDC.bits.cscidc1  = pstCscCoef->csc_in_dc1;
        VP0_CSC0_IDC.bits.cscidc0  = pstCscCoef->csc_in_dc0;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_IDC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_IDC.u32);

        VP0_CSC0_ODC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_ODC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_ODC.bits.cscodc1 = pstCscCoef->csc_out_dc1;
        VP0_CSC0_ODC.bits.cscodc0 = pstCscCoef->csc_out_dc0;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_ODC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_ODC.u32);

        VP0_CSC0_IODC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC0_IODC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC0_IODC.bits.cscodc2 = pstCscCoef->csc_out_dc2;
        VP0_CSC0_IODC.bits.cscidc2 = pstCscCoef->csc_in_dc2;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC0_IODC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC0_IODC.u32);
    }
    else if (enChan == HAL_DISP_LAYER_V1)
    {
        VP0_CSC1_IDC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_IDC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_IDC.bits.cscidc1  = pstCscCoef->csc_in_dc1;
        VP0_CSC1_IDC.bits.cscidc0  = pstCscCoef->csc_in_dc0;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_IDC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_IDC.u32);

        VP0_CSC1_ODC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_ODC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_ODC.bits.cscodc1 = pstCscCoef->csc_out_dc1;
        VP0_CSC1_ODC.bits.cscodc0 = pstCscCoef->csc_out_dc0;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_ODC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_ODC.u32);

        VP0_CSC1_IODC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->VP0_CSC1_IODC.u32) + 0 * VDP_VID_OFFSET);
        VP0_CSC1_IODC.bits.cscodc2 = pstCscCoef->csc_out_dc2;
        VP0_CSC1_IODC.bits.cscidc2 = pstCscCoef->csc_in_dc2;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->VP0_CSC1_IODC.u32) + 0 * VDP_VID_OFFSET), VP0_CSC1_IODC.u32);
    }
    else if ((enChan >= HAL_DISP_LAYER_V2) && (enChan < HAL_DISP_LAYER_BUTT))
    {
        V0_CSC_IDC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_IDC.u32) + enChan  * VDP_VID_OFFSET);
        V0_CSC_IDC.bits.cscidc1  = pstCscCoef->csc_in_dc1;
        V0_CSC_IDC.bits.cscidc0  = pstCscCoef->csc_in_dc0;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_IDC.u32) + enChan * VDP_VID_OFFSET), V0_CSC_IDC.u32);

        V0_CSC_ODC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_ODC.u32) + enChan * VDP_VID_OFFSET);
        V0_CSC_ODC.bits.cscodc1 = pstCscCoef->csc_out_dc1;
        V0_CSC_ODC.bits.cscodc0 = pstCscCoef->csc_out_dc0;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_ODC.u32) + enChan * VDP_VID_OFFSET), V0_CSC_ODC.u32);

        V0_CSC_IODC.u32 = PQ_HAL_RegRead((HI_U32) & (pstVDPReg->V0_CSC_IODC.u32) + enChan * VDP_VID_OFFSET);
        V0_CSC_IODC.bits.cscodc2 = pstCscCoef->csc_out_dc2;
        V0_CSC_IODC.bits.cscidc2 = pstCscCoef->csc_in_dc2;
        PQ_HAL_RegWrite(((HI_U32) & (pstVDPReg->V0_CSC_IODC.u32) + enChan * VDP_VID_OFFSET), V0_CSC_IODC.u32);
    }

    return HI_SUCCESS;
}

HI_VOID PQ_HAL_CalcCSCCoef(CSC_PARA_S* pstCSCParameter, CSC_COEF_S* pstCSCCoef)
{
    CSC_COEF_S* pCSCMatrix;
    CSC_COEF_S stCSCMatrix;

    if (pstCSCParameter->u16InputColorSpace == OPTM_CS_eRGB)  //input RGB color space
    {
        if (pstCSCParameter->u16OutputColorSpace == OPTM_CS_eRGB) //RGB -> RGB
        {
            pCSCMatrix = &CSCTable_Identity_RGB_to_RGB;
            PQ_HAL_CalCSCCoefTprtRGBtoRGB(pstCSCParameter->u16Contrast, pstCSCParameter->u16Saturation,
                                          pstCSCParameter->u16Hue,
                                          pstCSCParameter->as16ColorTempGain[COLORTEMP_R],
                                          pstCSCParameter->as16ColorTempGain[COLORTEMP_G],
                                          pstCSCParameter->as16ColorTempGain[COLORTEMP_B], pCSCMatrix,
                                          &stCSCMatrix);
        }
        else //RGB -> YCbCr
        {
            if (OPTM_CS_eXvYCC_709 == pstCSCParameter->u16OutputColorSpace)
            {
                pCSCMatrix = CSC_RGBPrim_to_YCbCr_MatrixTbl[pstCSCParameter->bFullRange][0];
            }
            else
            {
                pCSCMatrix = CSC_RGBPrim_to_YCbCr_MatrixTbl[pstCSCParameter->bFullRange][1];
            }

            PQ_HAL_CalCSCCoefTprtRGBtoYCbCr(pstCSCParameter->u16Contrast, pstCSCParameter->u16Saturation,
                                            pstCSCParameter->u16Hue,
                                            pstCSCParameter->as16ColorTempGain[COLORTEMP_R],
                                            pstCSCParameter->as16ColorTempGain[COLORTEMP_G],
                                            pstCSCParameter->as16ColorTempGain[COLORTEMP_B], pCSCMatrix,
                                            &stCSCMatrix);
        }
    }
    else //input YCbCr color space
    {
        if (pstCSCParameter->u16OutputColorSpace == OPTM_CS_eRGB) //YCbCr -> RGB
        {
            if (OPTM_CS_eXvYCC_709 == pstCSCParameter->u16InputColorSpace)
            {
                pCSCMatrix = CSC_YCbCr_to_RGBPrim_MatrixTbl[pstCSCParameter->bFullRange][1];
            }
            else
            {
                pCSCMatrix = CSC_YCbCr_to_RGBPrim_MatrixTbl[pstCSCParameter->bFullRange][8];
            }

            //pCSCMatrix = CSC_YCbCr_to_RGBPrim_MatrixTbl[eInputColorSpace];
            PQ_HAL_CalCSCCoefTprtYCbCrtoRGB(pstCSCParameter->u16Contrast, pstCSCParameter->u16Saturation,
                                            pstCSCParameter->u16Hue,
                                            pstCSCParameter->as16ColorTempGain[COLORTEMP_R],
                                            pstCSCParameter->as16ColorTempGain[COLORTEMP_G],
                                            pstCSCParameter->as16ColorTempGain[COLORTEMP_B], pCSCMatrix,
                                            &stCSCMatrix);
        }
        else //YCbCr -> YCbCr
        {
            //pCSCMatrix = CSC_YCbCr_MatrixTbl[eInputColorSpace][eOutputColorSpace];
            if (OPTM_CS_eXvYCC_709 == pstCSCParameter->u16OutputColorSpace)
            {
                pCSCMatrix = CSC_YCbCr_MatrixTbl[pstCSCParameter->u16InputColorSpace][0];
            }
            else
            {
                pCSCMatrix = CSC_YCbCr_MatrixTbl[pstCSCParameter->u16InputColorSpace][1];
            }

            PQ_HAL_CalCSCCoefTprtYCbCrtoYCbCr(pstCSCParameter->u16Contrast, pstCSCParameter->u16Saturation,
                                              pstCSCParameter->u16Hue,
                                              pstCSCParameter->as16ColorTempGain[COLORTEMP_R],
                                              pstCSCParameter->as16ColorTempGain[COLORTEMP_G],
                                              pstCSCParameter->as16ColorTempGain[COLORTEMP_B], pCSCMatrix,
                                              &stCSCMatrix);
        }
    }

    pstCSCCoef->csc_coef00 = stCSCMatrix.csc_coef00;
    pstCSCCoef->csc_coef01 = stCSCMatrix.csc_coef01;
    pstCSCCoef->csc_coef02 = stCSCMatrix.csc_coef02;

    pstCSCCoef->csc_coef10 = stCSCMatrix.csc_coef10;
    pstCSCCoef->csc_coef11 = stCSCMatrix.csc_coef11;
    pstCSCCoef->csc_coef12 = stCSCMatrix.csc_coef12;

    pstCSCCoef->csc_coef20 = stCSCMatrix.csc_coef20;
    pstCSCCoef->csc_coef21 = stCSCMatrix.csc_coef21;
    pstCSCCoef->csc_coef22 = stCSCMatrix.csc_coef22;

    return;
}

HI_VOID PQ_HAL_CalCSCCoefTprtYCbCrtoRGB(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue,
                                        HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, CSC_COEF_S* pCSCTable, CSC_COEF_S* pDstCSCTable)
{
    HI_S32 ContrastAdjust;
    HI_S32 SaturationAdjust;
    HI_S32 rGain, gGain, bGain;

#if 0//0-100
    ContrastAdjust = Contrast - 50;
    ContrastAdjust = 2 * ContrastAdjust + 100;

    SaturationAdjust = Saturation - 50;
    SaturationAdjust = 2 * SaturationAdjust + 100;

    Hue = Hue * 60 / 100;

    rGain = Kr - 50;
    rGain = 2 * rGain + 100;
    gGain = Kg - 50;
    gGain = 2 * gGain + 100;
    bGain = Kb - 50;
    bGain = 2 * bGain + 100;
#else//0-255
    ContrastAdjust = Contrast * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue = Hue * 60 / 255;
    rGain = Kr * 40 / 51;
    gGain = Kg * 40 / 51;
    bGain = Kb * 40 / 51;
#endif

    pDstCSCTable->csc_coef00 = pCSCTable->csc_coef00 * ContrastAdjust * rGain / 10000;

    pDstCSCTable->csc_coef01 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef01 * COS_TABLE[Hue]) / 1000
                                         - ((HI_S32)(pCSCTable->csc_coef02
                                                 * SIN_TABLE[Hue])) * SaturationAdjust / 100000)
                                        * ContrastAdjust * rGain) / 10000;

    pDstCSCTable->csc_coef02 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef01 * SIN_TABLE[Hue]) / 1000
                                         + ((HI_S32)(pCSCTable->csc_coef02
                                                 * COS_TABLE[Hue])) * SaturationAdjust / 100000)
                                        * ContrastAdjust * rGain) / 10000;

    pDstCSCTable->csc_coef10 = pCSCTable->csc_coef10 * ContrastAdjust * gGain / 10000;

    pDstCSCTable->csc_coef11 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef11 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef12 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * gGain) / 1000000;

    pDstCSCTable->csc_coef12 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef11 * SIN_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef12 * COS_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * gGain) / 1000000;

    pDstCSCTable->csc_coef20 = pCSCTable->csc_coef20 * ContrastAdjust * bGain / 10000;

    pDstCSCTable->csc_coef21 = (HI_S32)((((HI_S32)(pCSCTable->csc_coef21 * COS_TABLE[Hue])) * SaturationAdjust / 100000
                                         - (HI_S32)(pCSCTable->csc_coef22 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * bGain) / 10000;

    pDstCSCTable->csc_coef22 = (HI_S32)((((HI_S32)(pCSCTable->csc_coef21 * SIN_TABLE[Hue])) * SaturationAdjust / 100000
                                         - (HI_S32)(pCSCTable->csc_coef22 * COS_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * bGain) / 10000;

    return;
}

//计算色彩空间转换系数
//计算色温变换矩阵(for YCbCr->YCbCr 调节色温)
HI_VOID PQ_HAL_CalCTemperatureMat(HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, CSC_COEF_S* pCSCTable, CSC_COEF_S* pDstCSCTable)
{
    HI_S32 rGain;
    HI_S32 gGain;
    HI_S32 bGain;

    CSC_COEF_S yuv_color_temp;

#if 0//0-100
    rGain = Kr - 50;
    rGain = 2 * rGain + 100;
    gGain = Kg - 50;
    gGain = 2 * gGain + 100;
    bGain = Kb - 50;
    bGain = 2 * bGain + 100;
#else//0-255
    rGain = Kr * 40 / 51;
    gGain = Kg * 40 / 51;
    bGain = Kb * 40 / 51;
#endif

    //Kr系列精度100, 色温矩阵系数精度1000
    yuv_color_temp.csc_coef00 = (114 * bGain + 587 * gGain + 299 * rGain) / 100;
    yuv_color_temp.csc_coef01 = (232 * bGain - 232 * gGain) / 100;
    yuv_color_temp.csc_coef02 = -(341 * gGain - 341 * rGain) / 100;

    yuv_color_temp.csc_coef10 = -(289 * gGain - 436 * bGain + 147 * rGain) / 100;
    yuv_color_temp.csc_coef11 = (886 * bGain + 114 * gGain) / 100;
    yuv_color_temp.csc_coef12 = (168 * gGain - 168 * rGain) / 100;

    yuv_color_temp.csc_coef20 = -(100 * bGain + 515 * gGain - 615 * rGain) / 100;
    yuv_color_temp.csc_coef21 = -(203 * bGain - 203 * gGain) / 100;
    yuv_color_temp.csc_coef22 = (299 * gGain + 701 * rGain) / 100;

    pDstCSCTable->csc_coef00 = (pCSCTable->csc_coef00 * yuv_color_temp.csc_coef00 +
                                pCSCTable->csc_coef01 * yuv_color_temp.csc_coef10 +
                                pCSCTable->csc_coef02 * yuv_color_temp.csc_coef20) / 1000;

    pDstCSCTable->csc_coef01 = (pCSCTable->csc_coef00 * yuv_color_temp.csc_coef01 +
                                pCSCTable->csc_coef01 * yuv_color_temp.csc_coef11 +
                                pCSCTable->csc_coef02 * yuv_color_temp.csc_coef21) / 1000;

    pDstCSCTable->csc_coef02 = (pCSCTable->csc_coef00 * yuv_color_temp.csc_coef02 +
                                pCSCTable->csc_coef01 * yuv_color_temp.csc_coef12 +
                                pCSCTable->csc_coef02 * yuv_color_temp.csc_coef22) / 1000;

    pDstCSCTable->csc_coef10 = (pCSCTable->csc_coef10 * yuv_color_temp.csc_coef00 +
                                pCSCTable->csc_coef11 * yuv_color_temp.csc_coef10 +
                                pCSCTable->csc_coef12 * yuv_color_temp.csc_coef20) / 1000;

    pDstCSCTable->csc_coef11 = (pCSCTable->csc_coef10 * yuv_color_temp.csc_coef01 +
                                pCSCTable->csc_coef11 * yuv_color_temp.csc_coef11 +
                                pCSCTable->csc_coef12 * yuv_color_temp.csc_coef21) / 1000;

    pDstCSCTable->csc_coef12 = (pCSCTable->csc_coef10 * yuv_color_temp.csc_coef02 +
                                pCSCTable->csc_coef11 * yuv_color_temp.csc_coef12 +
                                pCSCTable->csc_coef12 * yuv_color_temp.csc_coef22) / 1000;

    pDstCSCTable->csc_coef20 = (pCSCTable->csc_coef20 * yuv_color_temp.csc_coef00 +
                                pCSCTable->csc_coef21 * yuv_color_temp.csc_coef10 +
                                pCSCTable->csc_coef22 * yuv_color_temp.csc_coef20) / 1000;

    pDstCSCTable->csc_coef21 = (pCSCTable->csc_coef20 * yuv_color_temp.csc_coef01 +
                                pCSCTable->csc_coef21 * yuv_color_temp.csc_coef11 +
                                pCSCTable->csc_coef22 * yuv_color_temp.csc_coef21) / 1000;

    pDstCSCTable->csc_coef22 = (pCSCTable->csc_coef20 * yuv_color_temp.csc_coef02 +
                                pCSCTable->csc_coef21 * yuv_color_temp.csc_coef12 +
                                pCSCTable->csc_coef22 * yuv_color_temp.csc_coef22) / 1000;

    return;
}

//计算色彩空间转换系数
//for YCbCr->YCbCr
HI_VOID PQ_HAL_CalCSCCoefTprtYCbCrtoYCbCr(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue,
        HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, CSC_COEF_S* pCSCTable,
        CSC_COEF_S* pDstCSCTable)
{
    HI_S32 ChromaAdjust;
    HI_S32 SaturationAdjust;
    CSC_COEF_S DstCSCTable2;

#if 0//0-100
    ChromaAdjust = Contrast - 50;
    ChromaAdjust = 2 * ChromaAdjust + 100;

    SaturationAdjust = Saturation - 50;
    SaturationAdjust = 2 * SaturationAdjust + 100;

    Hue = Hue * 60 / 100;
#else//0-255
    ChromaAdjust = Contrast * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue = Hue * 60 / 255;
#endif

    pDstCSCTable->csc_coef00 = pCSCTable->csc_coef00 * ChromaAdjust / 100;
    pDstCSCTable->csc_coef01 = pCSCTable->csc_coef01 * ChromaAdjust / 100;
    pDstCSCTable->csc_coef02 = pCSCTable->csc_coef02 * ChromaAdjust / 100;

    pDstCSCTable->csc_coef10 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef10 * COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef20
                                                 * SIN_TABLE[Hue])
                                         / 1000) * ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef11 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef11 * COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef21
                                                 * SIN_TABLE[Hue])
                                         / 1000) * ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef12 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef12 * COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef22
                                                 * SIN_TABLE[Hue])
                                         / 1000) * ChromaAdjust * SaturationAdjust) / 10000;

    pDstCSCTable->csc_coef20 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef20 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef10
                                                 * SIN_TABLE[Hue])
                                         / 1000) * ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef21 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef21 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef11
                                                 * SIN_TABLE[Hue])
                                         / 1000) * ChromaAdjust * SaturationAdjust) / 10000;
    pDstCSCTable->csc_coef22 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef22 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef12
                                                 * SIN_TABLE[Hue])
                                         / 1000) * ChromaAdjust * SaturationAdjust) / 10000;

    PQ_HAL_CalCTemperatureMat(Kr, Kg, Kb, pDstCSCTable, &DstCSCTable2);

    pDstCSCTable->csc_coef00 = DstCSCTable2.csc_coef00;
    pDstCSCTable->csc_coef01 = DstCSCTable2.csc_coef01;
    pDstCSCTable->csc_coef02 = DstCSCTable2.csc_coef02;
    pDstCSCTable->csc_coef10 = DstCSCTable2.csc_coef10;
    pDstCSCTable->csc_coef11 = DstCSCTable2.csc_coef11;
    pDstCSCTable->csc_coef12 = DstCSCTable2.csc_coef12;
    pDstCSCTable->csc_coef20 = DstCSCTable2.csc_coef20;
    pDstCSCTable->csc_coef21 = DstCSCTable2.csc_coef21;
    pDstCSCTable->csc_coef22 = DstCSCTable2.csc_coef22;

    return;
}

//计算色彩空间转换系数
//for RGB->YCbCr
HI_VOID PQ_HAL_CalCSCCoefTprtRGBtoYCbCr(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue,
                                        HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, CSC_COEF_S* pCSCTable, CSC_COEF_S* pDstCSCTable)
{
    HI_S32 ContrastAdjust;
    HI_S32 SaturationAdjust;
    HI_S32 rGain, gGain, bGain;
#if 0//0-100
    ContrastAdjust = Contrast - 50;
    ContrastAdjust = 2 * ContrastAdjust + 100;

    SaturationAdjust = Saturation - 50;
    SaturationAdjust = 2 * SaturationAdjust + 100;

    Hue = Hue * 60 / 100;

    rGain = Kr - 50;
    rGain = 2 * rGain + 100;
    gGain = Kg - 50;
    gGain = 2 * gGain + 100;
    bGain = Kb - 50;
    bGain = 2 * bGain + 100;
#else//0-255
    ContrastAdjust = Contrast * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue = Hue * 60 / 255;
    rGain = Kr * 40 / 51;
    gGain = Kg * 40 / 51;
    bGain = Kb * 40 / 51;
#endif

    pDstCSCTable->csc_coef00 = pCSCTable->csc_coef00 * ContrastAdjust * rGain / 10000;
    pDstCSCTable->csc_coef01 = pCSCTable->csc_coef01 * ContrastAdjust * gGain / 10000;
    pDstCSCTable->csc_coef02 = pCSCTable->csc_coef02 * ContrastAdjust * bGain / 10000;

    pDstCSCTable->csc_coef10 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef10 * COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef20 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * rGain) / 1000000;

    pDstCSCTable->csc_coef11 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef11 * COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef21 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * gGain) / 1000000;

    pDstCSCTable->csc_coef12 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef12 * COS_TABLE[Hue]) / 1000
                                         + (HI_S32)(pCSCTable->csc_coef22 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * bGain) / 1000000;

    pDstCSCTable->csc_coef20 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef20 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef10 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * rGain) / 1000000;

    pDstCSCTable->csc_coef21 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef21 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef11 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * gGain) / 1000000;

    pDstCSCTable->csc_coef22 = (HI_S32)(((HI_S32)(pCSCTable->csc_coef22 * COS_TABLE[Hue]) / 1000
                                         - (HI_S32)(pCSCTable->csc_coef12 * SIN_TABLE[Hue]) / 1000)
                                        * ContrastAdjust * SaturationAdjust * bGain) / 1000000;

    return;
}

//计算色彩空间转换系数
//for RGB->RGB
HI_VOID PQ_HAL_CalCSCCoefTprtRGBtoRGB(HI_U32 Contrast, HI_U32 Saturation, HI_U32 Hue,
                                      HI_U32 Kr, HI_U32 Kg, HI_U32 Kb, CSC_COEF_S* pCSCTable, CSC_COEF_S* pDstCSCTable)
{
    HI_S32 ContrastAdjust;
    HI_S32 SaturationAdjust;
    HI_S32 rGain, gGain, bGain;

#if 0//0-100
    ContrastAdjust = Contrast - 50;
    ContrastAdjust = 2 * ContrastAdjust + 100;

    SaturationAdjust = Saturation - 50;
    SaturationAdjust = 2 * SaturationAdjust + 100;

    Hue = Hue * 60 / 100;

    rGain = Kr - 50;
    rGain = 2 * rGain + 100;
    gGain = Kg - 50;
    gGain = 2 * gGain + 100;
    bGain = Kb - 50;
    bGain = 2 * bGain + 100;
#else//0-255
    ContrastAdjust   = Contrast * 40 / 51;
    SaturationAdjust = Saturation * 40 / 51;
    Hue   = Hue * 60 / 255;
    rGain = Kr * 40 / 51;
    gGain = Kg * 40 / 51;
    bGain = Kb * 40 / 51;
#endif

    pDstCSCTable->csc_coef00 = (HI_S32)(77 + (HI_S32)(60 * SIN_TABLE[Hue] * SaturationAdjust) / 100000
                                        + (HI_S32)(179 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * rGain / 10000;
    pDstCSCTable->csc_coef01 = (HI_S32)(150 + (HI_S32)(119 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        - (HI_S32)(150 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * gGain / 10000;
    pDstCSCTable->csc_coef02 = (HI_S32)(29 - (HI_S32)(179 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        - (HI_S32)(29 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * bGain / 10000;

    pDstCSCTable->csc_coef10 = (HI_S32)(77 - (HI_S32)(75 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        - (HI_S32)(77 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * rGain / 10000;
    pDstCSCTable->csc_coef11 = (HI_S32)(150 - (HI_S32)(24 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        + (HI_S32)(106 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * gGain / 10000;
    pDstCSCTable->csc_coef12 = (HI_S32)(29 + (HI_S32)(99 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        - (HI_S32)(29 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * bGain / 10000;

    pDstCSCTable->csc_coef20 = (HI_S32)(77 + (HI_S32)(227 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        - (HI_S32)(77 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * rGain / 10000;
    pDstCSCTable->csc_coef21 = (HI_S32)(150 - (HI_S32)(190 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        - (HI_S32)(150 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * gGain / 10000;
    pDstCSCTable->csc_coef22 = (HI_S32)(29 - (HI_S32)(37 * SIN_TABLE[Hue] * SaturationAdjust) / 100000 * 4
                                        + (HI_S32)(227 * COS_TABLE[Hue]
                                                * SaturationAdjust) / 100000) * 4 * ContrastAdjust * bGain / 10000;

    return;
}

/*计算直流分量*/
HI_VOID PQ_HAL_CalcCscDcCoef(CSC_PARA_S* pstCSCParameter, CSC_DCCOEF_S* pstCscDcCoef)
{
    HI_S32 s32Brightness = (HI_S32)pstCSCParameter->u16Brightness * 100 / 255 - 50;

    if (pstCSCParameter->u16InputColorSpace == OPTM_CS_eRGB)  //input RGB color space
    {
        if (pstCSCParameter->u16OutputColorSpace == OPTM_CS_eRGB) //RGB -> RGB
        {
            //pstCSCParameter->u16Brightness = pstCSCParameter->u16Brightness * 5 / 4 - 160; //+-160

            pstCscDcCoef->csc_in_dc2  = 0;
            pstCscDcCoef->csc_in_dc1  = 0;
            pstCscDcCoef->csc_in_dc0  = 0;
            pstCscDcCoef->csc_out_dc2 = (s32Brightness * 4 * 298 + 128) * 4 / 256 + (pstCSCParameter->as16ColorTempOffset[COLORTEMP_R]) - 128;
            pstCscDcCoef->csc_out_dc1 = (s32Brightness * 4 * 298 + 128) * 4 / 256 + (pstCSCParameter->as16ColorTempOffset[COLORTEMP_G]) - 128;
            pstCscDcCoef->csc_out_dc0 = (s32Brightness * 4 * 298 + 128) * 4 / 256 + (pstCSCParameter->as16ColorTempOffset[COLORTEMP_B]) - 128;
        }
        else  //RGB -> YCbCr
        {
            //pstCSCParameter->u16Brightness = pstCSCParameter->u16Brightness - 128;//+-128
            //pstCSCParameter->u16Brightness = pstCSCParameter->u16Brightness * 5 / 4 - 160; //+-160

            pstCscDcCoef->csc_in_dc2 = 0;
            pstCscDcCoef->csc_in_dc1 = 0;
            pstCscDcCoef->csc_in_dc0 = 0;

            //pstCscDcCoef->csc_out_dc2 = Bright + 16;
            pstCscDcCoef->csc_out_dc2 = s32Brightness * 4 + 64;
            pstCscDcCoef->csc_out_dc1 = 512;
            pstCscDcCoef->csc_out_dc0 = 512;
        }
    }
    else //input YCbCr color space
    {
        if (pstCSCParameter->u16OutputColorSpace == OPTM_CS_eRGB) //YCbCr -> RGB
        {
            //pstCSCParameter->u16Brightness = pstCSCParameter->u16Brightness*25/8 - 400;//+-400
            //pstCSCParameter->u16Brightness = (pstCSCParameter->u16Brightness * 5 / 4 - 160) * 4; //+-640

            //pstCscDcCoef->csc_in_dc2  = -64 + (Bright / Contrast);
            pstCscDcCoef->csc_in_dc2  = -64 + s32Brightness * 4;
            pstCscDcCoef->csc_in_dc1  = -512;
            pstCscDcCoef->csc_in_dc0  = -512;
            pstCscDcCoef->csc_out_dc2 = -128 + (pstCSCParameter->as16ColorTempOffset[COLORTEMP_R]);//0;
            pstCscDcCoef->csc_out_dc1 = -128 + (pstCSCParameter->as16ColorTempOffset[COLORTEMP_G]);//0;
            pstCscDcCoef->csc_out_dc0 = -128 + (pstCSCParameter->as16ColorTempOffset[COLORTEMP_B]);//0;
        }
        else //YCbCr -> YCbCr
        {
            //pstCSCParameter->u16Brightness = pstCSCParameter->u16Brightness - 128;//+-128
            //pstCSCParameter->u16Brightness = (pstCSCParameter->u16Brightness * 5 / 4 - 160) * 4; //+-640

            pstCscDcCoef->csc_in_dc2  = -64;
            pstCscDcCoef->csc_in_dc1  = -512;
            pstCscDcCoef->csc_in_dc0  = -512;
            pstCscDcCoef->csc_out_dc2 = s32Brightness * 4 + 64;
            pstCscDcCoef->csc_out_dc1 = 512;
            pstCscDcCoef->csc_out_dc0 = 512;
        }
    }
    //PQ_TRACE(HI_LOG_LEVEL_DBG, PQ_TRACE_RANGE, "pstCSCParameter->u16Brightness=%d\n",pstCSCParameter->u16Brightness);
    return;
}
