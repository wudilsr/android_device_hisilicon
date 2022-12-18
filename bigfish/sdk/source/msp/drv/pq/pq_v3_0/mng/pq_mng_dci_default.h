#ifndef __PQ_MNG_DCI_DEFAULT_H__
#define __PQ_MNG_DCI_DEFAULT_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/*PQ Source Mode*/
typedef enum hiPQ_SOURCE_MODE_E
{
    SOURCE_MODE_NO = 0,
    SOURCE_MODE_SD,
    SOURCE_MODE_HD,
    SOURCE_MODE_UHD,
    SOURCE_MODE_ALL,
} PQ_SOURCE_MODE_E;

/*PQ Source Mode*/
typedef enum hiPQ_DCI_GLOBAL_GAIN_E
{
    DCI_GLOBAL_GAIN_0 = 0,
    DCI_GLOBAL_GAIN_1,
    DCI_GLOBAL_GAIN_2,
    DCI_GLOBAL_GAIN_BUTT,
} PQ_DCI_GLOBAL_GAIN_E;


static HI_S32 sg_s32DCILevelGain[SOURCE_MODE_ALL][DCI_GLOBAL_GAIN_BUTT] =
{
    {38, 38, 38}, //SOURCE_MODE_NO
    {32, 32, 32}, //SOURCE_MODE_SD
    {38, 38, 38}, //SOURCE_MODE_HD
    {42, 42, 42}, //SOURCE_MODE_UHD
};

HI_S16 HistCoef0[32] = { 17, 16, 15, 14,   13, 11, 9, 7,     4, 2, 0, 0,     0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0 };
HI_S16 HistCoef1[32] = { 0, 0, 0, 0,    1, 2, 3, 4,   6, 8, 9, 10,   11, 12, 13, 14,  15, 16, 16, 15,    14, 13, 12, 11,   10, 9, 8, 7,     6, 5, 4, 3};
HI_S16 HistCoef2[32] = { 0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    0, 0, 0, 0,    1, 1, 2, 3,    4, 6, 8, 9,   10, 12, 13, 14,   14, 15, 15, 15 };

HI_S16 WgtCoef0[33] = {0, 0, 3, 7, 12, 19, 30, 45, 61, 81, 100, 112, 118, 122, 123, 123, 121, 119, 115, 110, 103, 94, 82, 66, 49, 35, 23, 12, 8, 5, 3, 2, 0};
HI_S16 WgtCoef1[33] = {0, -6, -13, -23, -32, -38, -41, -41, -39, -36, -30, -20, 0, 13, 28, 39, 46, 51, 52, 54, 54, 52, 49, 43, 39, 33, 25, 14, 2, 0, 0, 0, 0};
HI_S16 WgtCoef2[33] = {0, 0, 0, 0, 0, -6, -15, -21, -25, -32, -38, -42, -42, -43, -43, -47, -48, -51, -50, -49, -46, -42, -39, -36, -30, -24, -18, -10, -4, 0, 0, 0, 0};

HI_S16 YdivCoef[64] = {1, 4096, 2048, 1365, 1024, 819, 682, 585, 512, 455, 409, 372, 341, 315, 292, 273, 256, 240, 227, 215, 204, 195, 186, 178, 170, 163, 157, 151, 146, 141, 136, 132, 128, 124, 120, 117, 113, 110, 107, 105, 102, 99, 97, 95, 93, 91, 89, 87, 85, 83, 81, 80, 78, 77, 75, 74, 73, 71, 70, 69, 68, 67, 66, 65};


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif

