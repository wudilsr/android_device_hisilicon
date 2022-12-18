/******************************************************************************

  Copyright (C), 2001-2011, Hisilicon Tech. Co., Ltd.
 ******************************************************************************
 File Name      : unf_tuner.c
Version         : Initial Draft
Author          : Hisilicon multimedia Software group
Created         : 2009/01/23
Last Modified   :
Description     :
Function List   :
History         :
 ******************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <string.h>
#include <math.h>
#include <pthread.h>

#include "hi_type.h"
#include "hi_common.h"
#include "hi_mpi_mem.h"
#include "hi_unf_frontend.h"
#include "drv_tuner_ioctl.h"
#include "hi_drv_struct.h"

#define QAM_RF_MIN 45000  /*kHz*/
#define QAM_RF_MAX 870000 /*kHz*/
#define TER_RF_MIN 48000  //kHz
#define TER_RF_MAX 870000 //kHz
#define TER_BW_MIN 1700  //KHz
#define TER_BW_MAX 10000 //KHz
#define     PI     3.14159265
#define UNF_TUNER_NUM 5

#define MAX_BLINDSCAN_TIMES (4)

#define SAT_C_MIN (3000)
#define SAT_C_MAX (4200)
#define SAT_KU_MIN (10600)
#define SAT_KU_MAX (12750)
#define SAT_IF_MIN_KHZ (950000)
#define SAT_IF_MAX_KHZ (2150000)
#define SAT_C_MIN_KHZ (3000000)
#define SAT_C_MAX_KHZ (4200000)
#define SAT_KU_MIN_KHZ (10600000)
#define SAT_KU_MAX_KHZ (12750000)

#define SAT_SYMBOLRATE_MAX (60000000)//(45000000)

#define SAT_IF_MIN (950)
#define SAT_IF_MAX (2150)
#define SAT_IF_C_H_MIN (1550)
#define SAT_IF_C_H_MAX (2150)
#define SAT_IF_C_L_MIN (950)
#define SAT_IF_C_L_MAX (1550)
//#define SAT_IF_KU_H_MIN_1 (1100)
//#define SAT_IF_KU_H_MAX_1 (2150)
//#define SAT_IF_KU_H_MIN_2 (950)
//#define SAT_IF_KU_H_MAX_2 (2000)
//#define SAT_IF_KU_L_MIN (950)
//#define SAT_IF_KU_L_MAX (1950)

#define SAT_LO_C_L (5150)
#define SAT_LO_C_H (5750)
//#define SAT_LO_KU_L_1 (9750)
//#define SAT_LO_KU_H_1 (10600)
//#define SAT_LO_KU_L_2 (9750)
//#define SAT_LO_KU_H_2 (10750)


#define SPEC_RF_START_KHZ (1000) /*Hz,1kHz*/
#define SPEC_RF_END_KHZ (1300000000) /*Hz,1.3GHz*/
#define SPEC_RF_STEP_MIN_KHZ (10000) /*Hz,10kHz*/


#define SAT_DOWNLINK_FREQ_KU_MID (11700)

#define DISEQC_DELAY_TIME_MS (15)

#define T2_GROUP_SUM			(16)

#define GET_REFER_SNR(ref, array, FECRate) \
    { \
        HI_U32 i = 0; \
        for (i = 0; i < sizeof(array) / sizeof(TUNER_REFER_SNR_S); i++) \
        { \
            if (array[i].enFECRate == FECRate) \
            { \
                ref = array[i].u8ReferSNR; \
            } \
        } \
    }

typedef struct
{
    HI_U32                        u32Port;
    HI_UNF_TUNER_BLINDSCAN_PARA_S stPara;
} BLINDSCAN_PARA_S;

typedef struct
{
	HI_U32						  u32Port;
	HI_UNF_TUNER_TER_SCAN_PARA_S  stPara;
}TERSCAN_PARA_S;

typedef struct
{
    HI_UNF_TUNER_FE_LNB_22K_E      enLNB22K;
    HI_UNF_TUNER_FE_POLARIZATION_E enPolar;
    HI_U16                         u16StartFreq; /* MHz */
    HI_U16                         u16StopFreq; /* MHz */
} BLINDSCAN_CONDITION_T;

typedef struct
{
    HI_U32                u32ScanTimes;
    BLINDSCAN_CONDITION_T astScanCond[MAX_BLINDSCAN_TIMES];
} BLINDSCAN_CTRL_T;

typedef struct
{
    HI_UNF_TUNER_FE_LNB_CONFIG_S     stLNBConfig;/* LNB configuration */
    HI_UNF_TUNER_FE_LNB_POWER_E     enLNBPower; /* LNB power */
    HI_UNF_TUNER_FE_POLARIZATION_E  enPolar;    /* LNB polarization */
    HI_UNF_TUNER_FE_LNB_22K_E       enLNB22K;   /* LNB 22K on or off */
    pthread_t*                      pBlindScanMonitor; /* Blind scan thread */
    //pthread_t*                      pConnectMonitor; /* connect thread using while the symbol rate is low*/
    HI_BOOL                         bBlindScanStop; /* Blind scan stop flag */
    HI_BOOL                         bBlindScanBusy; /* Blind scan stop flag */
    //HI_BOOL                         bConnectStop; /* Blind scan stop flag */
    //HI_UNF_TUNER_SWITCH_22K_E       enSavedSwitch22K;
    HI_UNF_TUNER_SWITCH_22K_E       enSwitch22K;
    HI_UNF_TUNER_SWITCH_TONEBURST_E enToneBurst;
} TUNER_STATUS_SAT_S;

typedef struct
{
    HI_U16 u16SignalLevel;
    HI_S16 s16SignalDBUV;
} TUNER_SIGNAL_LEVEL_SAT_S;

typedef struct
{
	pthread_t*                      pScanMonitor; /* Blind scan thread */
	HI_BOOL                         bScanBusy; /* Blind scan stop flag */
	HI_BOOL                         bScanStop; /* Blind scan stop flag */
	HI_UNF_TUNER_TER_ANTENNA_POWER_E enAntennaPower;
}TUNER_STATUS_TERR_S;

static HI_S32  s_s32TunerFd = 0;
static HI_U32  g_u32PLPMode = 0;
static TUNER_ACC_QAM_PARAMS_S s_stCurrentSignal[TUNER_NUM];
//static TUNER_ACC_QAM_PARAMS_S s_stCurrentLockSignal[TUNER_NUM];
static HI_BOOL s_bTunerInited = HI_FALSE;
static HI_BOOL s_bTunerOpened = HI_FALSE;
static HI_UNF_TUNER_ATTR_S s_strDeftTunerAttr[UNF_TUNER_NUM];
static HI_UNF_TUNER_ATTR_S s_strCurTunerAttr[UNF_TUNER_NUM];
static HI_UNF_TUNER_CONNECT_PARA_S s_strCurTunerConnectPara[UNF_TUNER_NUM];
static TUNER_STATUS_SAT_S s_stSatPara[UNF_TUNER_NUM];
static TUNER_STATUS_TERR_S s_stTerPara[UNF_TUNER_NUM];

static pthread_mutex_t g_stTunerMutex = PTHREAD_MUTEX_INITIALIZER;

#define HI_TUNER_LOCK()        (void)pthread_mutex_lock(&g_stTunerMutex);
#define HI_TUNER_UNLOCK()      (void)pthread_mutex_unlock(&g_stTunerMutex);

#define CHECK_TUNER_OPEN()\
do{\
    HI_TUNER_LOCK();\
    if ( !s_bTunerOpened )\
    {\
        HI_ERR_TUNER("tuner not opened\n");\
        HI_TUNER_UNLOCK();\
        return HI_ERR_TUNER_NOT_OPEN;\
    }\
    HI_TUNER_UNLOCK();\
}while(0)

HI_VOID SET_BLINDSCAN_CTRL_COND(HI_U32 u32TunerId, BLINDSCAN_CTRL_T *pstBlindScanCtrl, HI_S32 i, HI_UNF_TUNER_FE_LNB_22K_E LNB22K, HI_UNF_TUNER_FE_POLARIZATION_E polar, HI_S32 startFreqMHz, HI_S32 stopFreqMHz)
{
	if(i >= MAX_BLINDSCAN_TIMES)
	{
		return;
	}
	
    pstBlindScanCtrl->astScanCond[i].enLNB22K = (LNB22K);
    pstBlindScanCtrl->astScanCond[i].enPolar = (polar);

    /* Check whether the LNB is unicable */
    if(HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
    {
        if ((startFreqMHz) < SAT_IF_MIN)
        {
            pstBlindScanCtrl->astScanCond[i].u16StartFreq = SAT_IF_MIN;
        }
        else
        {
            pstBlindScanCtrl->astScanCond[i].u16StartFreq = (HI_U16)(startFreqMHz);
        }
        if ((stopFreqMHz) > SAT_IF_MAX)
        {
            pstBlindScanCtrl->astScanCond[i].u16StopFreq = SAT_IF_MAX;
        }
        else
        {
            pstBlindScanCtrl->astScanCond[i].u16StopFreq = (HI_U16)(stopFreqMHz);
        }
        if ((pstBlindScanCtrl->astScanCond[i].u16StopFreq) < (pstBlindScanCtrl->astScanCond[i].u16StartFreq))
        {
            pstBlindScanCtrl->astScanCond[i].u16StopFreq = pstBlindScanCtrl->astScanCond[i].u16StartFreq;
        }
    }
    else
    {
        if ((startFreqMHz) < SAT_KU_MIN)
        {
            pstBlindScanCtrl->astScanCond[i].u16StartFreq = SAT_KU_MIN;
        }
        else
        {
            pstBlindScanCtrl->astScanCond[i].u16StartFreq = (HI_U16)(startFreqMHz);
        }
        if ((stopFreqMHz) > SAT_KU_MAX)
        {
            pstBlindScanCtrl->astScanCond[i].u16StopFreq = SAT_KU_MAX;
        }
        else
        {
            pstBlindScanCtrl->astScanCond[i].u16StopFreq = (HI_U16)(stopFreqMHz);
        }
        if ((pstBlindScanCtrl->astScanCond[i].u16StopFreq) < (pstBlindScanCtrl->astScanCond[i].u16StartFreq))
        {
            pstBlindScanCtrl->astScanCond[i].u16StopFreq = pstBlindScanCtrl->astScanCond[i].u16StartFreq;
        }
    }
}

static TUNER_SIGNAL_LEVEL_SAT_S s_astSignalLevelAV2011[100] =
    {
        {0, 18},      {0, 19},      {0, 20},      {1906,21},    {4959, 22},   {6712, 23},   {8254, 24},   {9419, 25},   {10508, 26},  {11450, 27},
        {12360, 28},  {13151, 29},  {13940, 30},  {14744, 31},  {15396, 32},  {16027, 33},  {16529, 34},  {16997, 35},  {17425, 36},  {17900, 37},
        {18248, 38},  {18658, 39},  {19012, 40},  {19324, 41},  {19707, 42},  {19937, 43},  {20246, 44},  {20478, 48},  {20789, 49},  {21018, 50},
        {21380, 51},  {21658, 52},  {21967, 53},  {22338, 54},  {22646, 55},  {23056, 56},  {23400, 57},  {23932, 58},  {24469, 59},  {25119, 60},
        {25844, 61},  {26485, 66},  {27486, 67},  {28610, 68},  {29767, 69},  {30935, 70},  {31449, 74},  {32603, 75},  {33750, 76},  {34700, 77},
        {35526, 78},  {36280, 79},  {37022, 80},  {37677, 81},  {38217, 82},  {38724, 83},  {39135, 84},  {39584, 85},  {40063, 86},  {40486, 87},
        {40863, 88},  {41399, 89},  {41931, 90},  {42498, 91},  {43132, 92},  {43701, 93},  {44282, 94},  {44761, 95},  {45353, 96},  {45795, 97},
        {46258, 98},  {46792, 99},  {47346, 100}, {47771, 101}, {48144, 102}, {48611, 103}, {49030, 104}, {49344, 105}, {49663, 106}, {50020, 107},
        {50195, 108}, {50440, 109}, {50652, 110}, {50911, 111}, {51170, 112}, {51287, 113}, {51480, 114}, {51617, 115}, {51868, 116}, {51858, 117},
        {51890, 118}, {51873, 119}, {51893, 120}, {51906, 121}, {51808, 122}, {51843, 123}, {51857, 124}, {51831, 125}, {51823, 126}, {51823, 127}
    };

static TUNER_SIGNAL_LEVEL_SAT_S s_astSignalLevelSHARP7903[100] =
    {
        {5463, 18},   {5962, 19},   {6488, 20},   {7011, 21},   {7611, 22},   {8206, 23},   {8811, 24},   {9482, 25},   {10174, 26},  {16635, 37},
        {11382, 28},  {12050, 29},  {12664, 30},  {13179, 31},  {13860, 32},  {14447, 33},  {14967, 34},  {15490, 35},  {16096, 36},  {17900, 37},
        {17168, 38},  {17645, 39},  {18122, 40},  {18610, 41},  {19053, 42},  {19657, 43},  {20523, 44},  {21279, 45},  {22003, 46},  {22683, 47},
        {23345, 48},  {23943, 49},  {24440, 50},  {24994, 51},  {25409, 52},  {25804, 53},  {26186, 54},  {26469, 55},  {26906, 56},  {27343, 57},
        {27828, 58},  {28254, 59},  {28725, 60},  {29231, 61},  {29715, 62},  {30227, 63},  {30730, 64},  {31233, 65},  {31713, 66},  {32291, 67},
        {32860, 68},  {33391, 69},  {33901, 70},  {34514, 71},  {35076, 72},  {35802, 73},  {37001, 74},  {37667, 75},  {38242, 76},  {38775, 77},
        {39240, 78},  {39642, 79},  {39996, 80},  {40356, 81},  {40684, 82},  {41033, 83},  {41339, 84},  {41568, 85},  {41950, 86},  {42288, 87},
        {42609, 88},  {42983, 89},  {43368, 90},  {43847, 91},  {44335, 92},  {44923, 93},  {45543, 94},  {46188, 95},  {46897, 96},  {47591, 97},
        {48245, 98},  {48902, 99},  {49535, 100}, {50093, 101}, {50611, 102}, {51103, 103}, {51525, 104}, {51963, 105}, {52479, 106}, {52825, 107},
        {53257, 108}, {53601, 109}, {53985, 110}, {54323, 111}, {54642, 112}, {54947, 113}, {55242, 114}, {55477, 116}, {55465, 118}, {55451, 120}
    };

static HI_S32  s_s32TunerFreq = 0;
typedef struct
{
    HI_S32 s32SignalFreq;
    HI_S32 s32SignalLevel;
} TUNER_SIGNAL_LEVEL_S;

static TUNER_SIGNAL_LEVEL_S s_SignalLevelTda18250[] =
    {
        {52, 5},    {60, 5},    {68, 5},    {76, 5},   {84, 5},    {92, 5},   {100, 5},
        {108, 5},  {115, 5},  {123, 5},  {131, 4},  {139, 5},  {147, 5},  {155, 5},  {163, 5},  {171, 5},
        {179, 5},  {187, 5},  {195, 4},  {203, 4},  {211, 4},  {219, 5},  {227, 4},  {235, 4},  {243, 4},  {251, 4},
        {259, 4},  {267, 4},  {275, 4},  {283, 4},  {291, 4},  {299, 4},  {307, 4},  {315, 4},  {323, 4},  {331, 5},
        {339, 5},  {347, 5},  {355, 4},  {363, 5},  {371, 5},  {379, 5},  {387, 5},  {395, 4},  {411, 5},  {419, 5},
        {427, 5},  {435, 4},  {443, 5},  {451, 5},  {459, 5},  {467, 5},  {474, 5},  {482, 5},  {490, 5},  {498, 5},
        {506, 5},  {514, 4},  {522, 5},  {530, 4},  {538, 5},  {546, 4},  {554, 4},  {562, 4},  {570, 4},  {578, 4},
        {586, 4},  {594, 4},  {602, 4},  {610, 4},  {618, 4},  {626, 4},  {634, 4},  {642, 4},  {650, 5},  {658, 4},
        {666, 4},  {674, 4},  {682, 4},  {690, 5},  {698, 4},  {706, 4},  {714, 4},  {722, 5},  {730, 4},  {738, 4},
        {746, 4},  {754, 5},  {762, 5},  {770, 5},  {778, 5},  {786, 5},  {794, 5},  {802, 5},  {810, 5},  {818, 5},
        {826, 5},  {834, 5},  {842, 5},  {850, 6},  {858, 7}
    };
/*    //tda18250 soft filter open
static TUNER_SIGNAL_LEVEL_S s_SignalLevelTda18250[] =
    {
        {52, 5},    {60, 5},    {68, 5},    {76, 5},   {84, 5},    {92, 5},   {100, 5},
        {108, 3},  {115, 2},  {123, 3},  {131, 3},  {139, 3},  {147, 3},  {155,3},  {163, 3},  {171, 2},
        {179, 2},  {187, 2},  {195, 3},  {203, 3},  {211, 3},  {219, 4},  {227, 4},  {235, 4},  {243, 4},  {251, 4},
        {259, 4},  {267, 5},  {275, 5},  {283, 4},  {291, 5},  {299, 5},  {307, 5},  {315, 5},  {323, 5},  {331, 5},
        {339, 5},  {347, 5},  {355, 4},  {363, 7},  {371, 6},  {379, 6},  {387, 6},  {395, 6},  {411, 6},  {419, 6},
        {427, 6},  {435, 6},  {443, 6},  {451, 6},  {459, 6},  {467, 6},  {474, 5},  {482, 5},  {490, 6},  {498, 5},
        {506, 7},  {514, 7},  {522, 7},  {530, 8},  {538, 8},  {546, 8},  {554, -1},  {562, -1},  {570, -1},  {578, 0},
        {586, -1},  {594, -1},  {602, -1},  {610, -1},  {618, -1},  {626, -1},  {634, -1},  {642, -1},  {650, -1},  {658, -1},
        {666, -1},  {674, -1},  {682, -1},  {690, -1},  {698, -1},  {706, -1},  {714, -1},  {722, -1},  {730, -2},  {738, -3},
        {746, -2},  {754, -3},  {762, -2},  {770, -2},  {778, -2},  {786, -3},  {794, -2},  {802, -2},  {810, -2},  {818, -2},
        {826, -2},  {834, -2},  {842, -1},  {850, -1},  {858, 0}
    }; */
static HI_VOID  TUNER_DownlinkFreqToIF(HI_UNF_TUNER_FE_LNB_CONFIG_S* pstLNBConfig,
                                       HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_U32 u32DownlinkFreq,
                                       HI_U32* pu32IF, HI_UNF_TUNER_FE_LNB_22K_E *penLNB22K);
static HI_VOID  TUNER_IFToDownlinkFreq(const HI_UNF_TUNER_FE_LNB_CONFIG_S* pstLNBConfig,
                                       HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_UNF_TUNER_FE_LNB_22K_E enLNB22K,
                                       HI_U32 u32IF, HI_U32* pu32DownlinkFreq);
static HI_S32   TUNER_SetLNBOutAnd22K(HI_U32 u32TunerId,
                                      HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_UNF_TUNER_FE_LNB_22K_E enLNB22K);
static HI_VOID* TUNER_BlindScanThread(HI_VOID * pstBlindScan);
static HI_S32 UNIC_ChanChange(HI_U32 u32TunerId, HI_U32 u32Freq_MHz, HI_UNF_TUNER_FE_POLARIZATION_E enPolar);
//static HI_VOID* TUNER_ConnectThread(HI_VOID * pstConnect);


/* Convert downlink frequency to IF, calculate LNB 22K status synchronously, for connect */
/*Downlink freq dominates the course, i.e, the freq band is decided by the downlink freq*/
static HI_VOID TUNER_DownlinkFreqToIF(HI_UNF_TUNER_FE_LNB_CONFIG_S* pstLNBConfig,
                                      HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_U32 u32DownlinkFreq,
                                      HI_U32* pu32IF, HI_UNF_TUNER_FE_LNB_22K_E *penLNB22K)
{
    /* Default */
    if (HI_NULL != penLNB22K)
    {
        *penLNB22K = HI_UNF_TUNER_FE_LNB_22K_OFF;
    }

    if ((SAT_C_MIN_KHZ <= u32DownlinkFreq)
            && (SAT_C_MAX_KHZ >= u32DownlinkFreq))
    {
        pstLNBConfig->enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_C;
    }
    else if ((SAT_KU_MIN_KHZ <= u32DownlinkFreq)
            && (SAT_KU_MAX_KHZ >= u32DownlinkFreq))
    {
        pstLNBConfig->enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_KU;
    }
    else
    {
        HI_ERR_TUNER("Error freq!\n");
        return;
    }

    switch (pstLNBConfig->enLNBBand)
    {
        /* C band, IF = LO - downlink frequency */
    case HI_UNF_TUNER_FE_LNB_BAND_C:
        /* Single LO */
        if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNBConfig->enLNBType)
           || (pstLNBConfig->u32HighLO == pstLNBConfig->u32LowLO))
        {
            *pu32IF = pstLNBConfig->u32LowLO * 1000 - u32DownlinkFreq;
        }
        /* Dual LO */
        else
        {
            /* V/R polarization, use high LO */
            if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
            {
                *pu32IF = pstLNBConfig->u32HighLO * 1000 - u32DownlinkFreq;
            }
            /* H/L polarization, use low LO */
            else
            {
                *pu32IF = pstLNBConfig->u32LowLO * 1000 - u32DownlinkFreq;
            }
        }

        break;

    /* Ku band, IF = downlink frequency - LO */
    case HI_UNF_TUNER_FE_LNB_BAND_KU:

        /* Single LO */
        if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNBConfig->enLNBType)
           || (pstLNBConfig->u32HighLO == pstLNBConfig->u32LowLO))
        {
            *pu32IF = u32DownlinkFreq - pstLNBConfig->u32LowLO * 1000;
        }
        /* Dual LO */
        else if(HI_UNF_TUNER_FE_LNB_DUAL_FREQUENCY == pstLNBConfig->enLNBType)
        {
            /* downlink frequency >= 11700MHz, use high LO */
            if ((u32DownlinkFreq >= SAT_DOWNLINK_FREQ_KU_MID * 1000))
            {
                *pu32IF = u32DownlinkFreq - pstLNBConfig->u32HighLO * 1000;

                /* Ku dual LO LNB use 22K select high LO */
                if (HI_NULL != penLNB22K)
                {
                    *penLNB22K = HI_UNF_TUNER_FE_LNB_22K_ON;
                }
            }
            /* downlink frequency < 11700MHz, use low LO */
            else
            {
                *pu32IF = u32DownlinkFreq - pstLNBConfig->u32LowLO * 1000;
            }
        }
        /*unicable LNB*/
        else if(HI_UNF_TUNER_FE_LNB_UNICABLE == pstLNBConfig->enLNBType)
        {
            *pu32IF = pstLNBConfig->u32UNICIFFreqMHz * 1000;
        }

        break;

    default:
        break;
    }
}


/* Convert IF to downlink frequency, the units of IF and Dlink freq are both kHz */
static HI_VOID TUNER_IFToDownlinkFreq(const HI_UNF_TUNER_FE_LNB_CONFIG_S* pstLNBConfig,
                                      HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_UNF_TUNER_FE_LNB_22K_E enLNB22K,
                                      HI_U32 u32IF_kHz, HI_U32* pu32DownlinkFreq_kHz)
{
    switch (pstLNBConfig->enLNBBand)
    {
    /* C band, downlink frequency = LO - IF */
    case HI_UNF_TUNER_FE_LNB_BAND_C:
        /* Single LO */
        if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNBConfig->enLNBType)
           || (pstLNBConfig->u32HighLO == pstLNBConfig->u32LowLO))
        {
            *pu32DownlinkFreq_kHz = pstLNBConfig->u32LowLO * 1000 - u32IF_kHz;
        }
        /* Dual LO */
        else
        {
            /* V/R polarization, use high LO */
            if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
            {
                *pu32DownlinkFreq_kHz = pstLNBConfig->u32HighLO * 1000 - u32IF_kHz;
            }
            /* H/L polarization, use low LO */
            else
            {
                *pu32DownlinkFreq_kHz = pstLNBConfig->u32LowLO * 1000 - u32IF_kHz;
            }
        }

        break;

    /* Ku band, downlink frequency = IF + LO */
    case HI_UNF_TUNER_FE_LNB_BAND_KU:

        /* Single LO */
        if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNBConfig->enLNBType)
           || (pstLNBConfig->u32HighLO == pstLNBConfig->u32LowLO))
        {
            *pu32DownlinkFreq_kHz = pstLNBConfig->u32LowLO * 1000 + u32IF_kHz;
        }
        /* Dual LO */
        else
        {
            /* 22K on, use high LO */
            if (HI_UNF_TUNER_FE_LNB_22K_ON == enLNB22K)
            {
                *pu32DownlinkFreq_kHz = pstLNBConfig->u32HighLO * 1000 + u32IF_kHz;
            }
            /* 22K off, use low LO */
            else
            {
                *pu32DownlinkFreq_kHz = pstLNBConfig->u32LowLO * 1000 + u32IF_kHz;
            }
        }

        break;

    default:
        return;
    }
}

static HI_S32 TUNER_SetLNBOutAnd22K(HI_U32 u32TunerId,
                                    HI_UNF_TUNER_FE_POLARIZATION_E enPolar, HI_UNF_TUNER_FE_LNB_22K_E enLNB22K)
{
    TUNER_LNB_OUT_S stLNBOut;
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret;

    if(HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
    {
        switch (s_stSatPara[u32TunerId].enLNBPower)
        {
        /* 0V */
        case HI_UNF_TUNER_FE_LNB_POWER_OFF:
            stLNBOut.enOut = TUNER_LNB_OUT_0V;
            break;

    /* 13V/18V */
    case HI_UNF_TUNER_FE_LNB_POWER_ON:
        if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
        {
            stLNBOut.enOut = TUNER_LNB_OUT_13V;
        }
        else
        {
            stLNBOut.enOut = TUNER_LNB_OUT_18V;
        }

        break;

            /* 14V/19V */
        case HI_UNF_TUNER_FE_LNB_POWER_ENHANCED:
            if ((HI_UNF_TUNER_FE_POLARIZATION_V == enPolar) || (HI_UNF_TUNER_FE_POLARIZATION_R == enPolar))
            {
                stLNBOut.enOut = TUNER_LNB_OUT_14V;
            }
            else
            {
                stLNBOut.enOut = TUNER_LNB_OUT_19V;
            }
            break;

        default:
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }
    else
    {
        switch (s_stSatPara[u32TunerId].enLNBPower)
        {
        /* 0V */
        case HI_UNF_TUNER_FE_LNB_POWER_OFF:
            stLNBOut.enOut = TUNER_LNB_OUT_0V;
            break;

        /* 18V */
        case HI_UNF_TUNER_FE_LNB_POWER_ON:
            stLNBOut.enOut = TUNER_LNB_OUT_18V;
            break;

            /* 19V */
        case HI_UNF_TUNER_FE_LNB_POWER_ENHANCED:
            stLNBOut.enOut = TUNER_LNB_OUT_19V;
            break;

        default:
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }

    stLNBOut.u32Port = u32TunerId;
    s32Ret = ioctl(s_s32TunerFd, TUNER_SET_LNBOUT_CMD, &stLNBOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set LNB out fail.\n");
        return HI_ERR_TUNER_FAILED_LNBCTRL;
    }

    /* Save polarization status */
    s_stSatPara[u32TunerId].enPolar = enPolar;

    /* 22K signal control. If LNB power off, can't send 22K signal. */
    if ((HI_UNF_TUNER_FE_LNB_POWER_OFF != s_stSatPara[u32TunerId].enLNBPower) && \
        (HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32TunerId].stLNBConfig.enLNBType))
    {
        /* If has 22K switch, 22K controlled by switch.
           If hasn't 22K switch, 22K controlled by tuner lock or blind scan.
         */
        if (HI_UNF_TUNER_SWITCH_22K_NONE == s_stSatPara[u32TunerId].enSwitch22K)
        {
            stTunerData.u32Port = u32TunerId;
            stTunerData.u32Data = enLNB22K;
            s32Ret = ioctl(s_s32TunerFd, TUNER_SEND_CONTINUOUS_22K_CMD, &stTunerData);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Set continuous 22K fail.\n");
                return HI_ERR_TUNER_FAILED_LNBCTRL;
            }
        }
    }

    /* Save polarization status */
    s_stSatPara[u32TunerId].enLNB22K = enLNB22K;
    return HI_SUCCESS;
}

HI_VOID sort_tp_and_deredun(HI_S32 *psts32TPNum, HI_UNF_TUNER_SAT_TPINFO_S *pstTPInfo)
{
    HI_S32 i = 0, j = 0, n = 0, i_sub_1=0;
    HI_UNF_TUNER_SAT_TPINFO_S temp_tp = {0};
    HI_U32 deta_fc_KHZ = 0, deta_fs_HZ = 0;

    if (*psts32TPNum > 0)
    {
        for(i = 0; i < *psts32TPNum - 1; i++)
        {
            for(j = i + 1; j < *psts32TPNum; j++)
            {
                if(pstTPInfo[i].cbs_reliablity < pstTPInfo[j].cbs_reliablity)   //����CBS�ɿ��Ƚ��������ɴ���С
                {
                    temp_tp = pstTPInfo[i];
                    pstTPInfo[i] = pstTPInfo[j];
                    pstTPInfo[j] = temp_tp;
                }
            }
        }
        //printf("TP NUM is %daaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa\n", *psts32TPNum);
        for(i = 0; i < *psts32TPNum - 1; i++)   //freq & symbol   unit: KHZ
        {
            if(i_sub_1)
            {
                i--;
                i_sub_1 = 0;
            }
            for(j = i + 1; j < *psts32TPNum; j++)
            {
                /* Use abs value directly?*/
                deta_fc_KHZ = (pstTPInfo[j].u32Freq > pstTPInfo[i].u32Freq) ?
                                (pstTPInfo[j].u32Freq - pstTPInfo[i].u32Freq) :
                                (pstTPInfo[i].u32Freq - pstTPInfo[j].u32Freq);
                deta_fs_HZ = (pstTPInfo[j].u32SymbolRate > pstTPInfo[i].u32SymbolRate) ?
                                (pstTPInfo[j].u32SymbolRate - pstTPInfo[i].u32SymbolRate) :
                                (pstTPInfo[i].u32SymbolRate - pstTPInfo[j].u32SymbolRate);
                /*if(deta_fc_KHZ < 0)
                {
                    deta_fc_KHZ = pstTPInfo[i].u32Frequency - pstTPInfo[j].u32Frequency;
                }
                if(deta_fs_KHZ < 0)
                {
                    deta_fs_KHZ = pstTPInfo[i].u32SymbolRate - pstTPInfo[j].u32SymbolRate;
                }*/

                if((deta_fc_KHZ < pstTPInfo[i].u32SymbolRate / 3000) && (deta_fs_HZ < pstTPInfo[i].u32SymbolRate / 200))
                {
                    temp_tp = pstTPInfo[j];

                    for(n = j; n < (*psts32TPNum) - 1; n++)
                    {
                        pstTPInfo[n] = pstTPInfo[n+1];
                    }

                    *psts32TPNum = *psts32TPNum - 1;
                    j -= 1;
                    if(pstTPInfo[i].cbs_reliablity < temp_tp.cbs_reliablity)    //select the big one
                    {
                        pstTPInfo[i] = temp_tp;

                        if(i>0)
                            i--;
                        else
                            i_sub_1 = 1;

                        break;      //???????
                     }
                }
            }
        }
    }
}

#define BUF_TP_NUM 625
//#define CBS_TH_BASE 0x18

static HI_S32 hi_tuner_tpverify(HI_U32  u32tunerId , const TUNER_TP_VERIFY_PARAMS_S  *pstTPInfo)
{
    HI_S32       s32Ret = HI_SUCCESS;
    //TUNER_DATA_S stTunerData;
    HI_U32 u32Freq = 0, u32OrigFreq = 0;
    HI_U32 u32Symb = 0;
    TUNER_TP_VERIFY_PARAMS_S stTPVerifyPrm = {0};
    //TUNER_ACC_QAM_PARAMS_S stTunerPara = {0};
    //TUNER_SIGNAL_S stTunerSignal;
    TUNER_TP_VERIFY_INFO_S stTPVerifyInfo;
    HI_UNF_TUNER_FE_LNB_22K_E enLNB22K;

    CHECK_TUNER_OPEN();
    //stTunerData.u32Data = 0;
    //stTunerData.u32Port = u32tunerId;

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTPInfo)
    {
        HI_ERR_TUNER("Input parameter(pstTPInfo) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    /* only for Satellite */
    if (SAT_SYMBOLRATE_MAX  < *(pstTPInfo->pu32SymbolRate))     //jiangzhb 20121221
    {
        HI_ERR_TUNER("Input parameter(u32SymbolRate) invalid: %d\n",
                            *(pstTPInfo->pu32SymbolRate));
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= pstTPInfo->enPolar)
    {
        HI_ERR_TUNER("Input parameter(enPolar) invalid: %d\n",
                            pstTPInfo->enPolar);
        return HI_ERR_TUNER_INVALID_PARA;

    }

    stTPVerifyPrm = *pstTPInfo;

    /* Convert downlink frequency to IF */
    TUNER_DownlinkFreqToIF(&(s_stSatPara[u32tunerId].stLNBConfig), pstTPInfo->enPolar,
                           *(pstTPInfo->pu32Frequency), /*&(stTPVerifyPrm.u32Frequency)*/&u32Freq, &enLNB22K);

    if(HI_UNF_TUNER_FE_LNB_UNICABLE == s_stSatPara[u32tunerId].stLNBConfig.enLNBType)
    {
        s32Ret = UNIC_ChanChange(u32tunerId, *(pstTPInfo->pu32Frequency) / 1000, pstTPInfo->enPolar);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }
    }

    //stTPVerifyPrm.u32SymbolRate = pstTPInfo->u32SymbolRate;
    //stTPVerifyPrm.enPolar = pstTPInfo->enPolar;

    stTPVerifyInfo.u32Port = u32tunerId;
    stTPVerifyPrm.pu32Frequency = &u32Freq;
    u32OrigFreq = u32Freq;
    u32Symb = *(pstTPInfo->pu32SymbolRate);
    stTPVerifyPrm.pu32SymbolRate = &u32Symb;
    stTPVerifyInfo.stTPVerifyPrm = stTPVerifyPrm;

    s32Ret = ioctl(s_s32TunerFd, TUNER_TPVERIFY_CMD, (unsigned long)&stTPVerifyInfo);
    if (HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    *(pstTPInfo->pu32SymbolRate) = u32Symb;

    if(HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32tunerId].stLNBConfig.enLNBType)
    {
        TUNER_IFToDownlinkFreq(&(s_stSatPara[u32tunerId].stLNBConfig), pstTPInfo->enPolar, enLNB22K,
                               u32Freq, pstTPInfo->pu32Frequency);
    }
    else
    {
        *(pstTPInfo->pu32Frequency) = *(pstTPInfo->pu32Frequency) - (u32Freq - u32OrigFreq);
    }

    //printf("real tp freq is %d, symb is %d\n", *(pstTPInfo->pu32Frequency), *(pstTPInfo->pu32SymbolRate));
    return HI_SUCCESS;
}

/*The freq used is downlink freq while using unicable LNB, else is IF freq.*/
static HI_VOID* TUNER_BlindScanThread(HI_VOID* pstBlindScan)
{
    HI_UNF_TUNER_BLINDSCAN_PARA_S stPara;
    TUNER_BLINDSCAN_S stBlindScan;
    TUNER_BLINDSCAN_INFO_S stBlindScanInfo;
    TUNER_BLINDSCAN_PARA_S stActionPara;
    BLINDSCAN_CTRL_T stBlindScanCtrl = {0};
    HI_UNF_TUNER_SAT_TPINFO_S stResult;
    HI_UNF_TUNER_SAT_TPINFO_S stTP[BUF_TP_NUM];
    HI_UNF_TUNER_BLINDSCAN_NOTIFY_U unNotify;
    TUNER_DATA_S stTunerData;
    //TUNER_LNB_OUT_S stLNBOut;
    //TUNER_FUNC_MODE_E enFuncMode = FunctMode_Demod;
    HI_U32 u32AllFreq  = 0;
    HI_U32 u32OverFreq = 0;
    HI_U32 u32StepFreq;
    HI_U32 u32StepNum;
    HI_U32 u32TunerId;
    HI_S32 s32Result = HI_FAILURE;
    HI_S32 i, j, k;
    HI_S32 s32IFStart = 0;
    HI_S32 s32IFStop = 0;
    HI_U32 u32DlinkStart = 0;
    HI_U32 u32DlinkStop = 0;
    HI_U32 u32WindowMHz = 0;
    HI_U16 u16LastProgressPercent = 0;
    HI_U16 u16ProgressPercent = 0, u16OverPercent = 0;
    HI_U16 u16LastNum = 0, same_tp, kk;
    HI_U32 fs_dlt, if_dlt;
    HI_S32 s32TPNum = 0, s32ReliTPNum = 0;
    HI_UNF_TUNER_BLINDSCAN_STATUS_E enStatus = HI_UNF_TUNER_BLINDSCAN_STATUS_IDLE;
    //HI_UNF_TUNER_SAT_TPINFO_S *pstVerifyStart = HI_NULL;


    HI_U32 fec_ok_cnt = 0, last_fec_ok_cnt = 0, fec_no_ok_cnt = 0, fs_cur;/*fs_first = 0;*/
    //HI_FLOAT  fs_bias=0;
    //HI_U8 fs_equal;
    /*HI_U8 fec_ok, fs_grade, CBS_TH, cbs_th_temp, fec_ok_flag, signal_type = 0;*/
    //HI_U8 fs_grade0_down, fs_grade1_up;
    HI_U8 /*may_no_sig = 0, may_sfu = 0,*/ stop_quit=0;
    TUNER_TP_VERIFY_PARAMS_S stTPParm = {0};


    if (HI_NULL == pstBlindScan)
    {
        HI_ERR_TUNER("Input parameter(pstBlindScan) invalid\n");
        return HI_NULL;
    }

    u32TunerId = ((BLINDSCAN_PARA_S*)pstBlindScan)->u32Port;
    stPara = ((BLINDSCAN_PARA_S*)pstBlindScan)->stPara;

    if (HI_NULL == (stPara.unScanPara.stSat.pfnEVTNotify))
    {
        HI_ERR_TUNER("Input parameter(pfnEVTNotify) invalid\n");
        /*if (s_stSatPara[u32TunerId].pBlindScanMonitor)
        {
            free(s_stSatPara[u32TunerId].pBlindScanMonitor);
            s_stSatPara[u32TunerId].pBlindScanMonitor = HI_NULL;
        }*/

        s_stSatPara[u32TunerId].bBlindScanStop = HI_FALSE;
        return HI_NULL;
    }

    s_stSatPara[u32TunerId].bBlindScanBusy = HI_TRUE;

    memset(&stActionPara, 0, sizeof(stActionPara));
    stBlindScanInfo.u32Port = u32TunerId;
    stBlindScanInfo.pstPara = &stActionPara;

    /* Manual scan mode */
    if (HI_UNF_TUNER_BLINDSCAN_MODE_MANUAL == stPara.enMode)
    {
        /*unicable, convert IF to downlink freq first */
        if(HI_UNF_TUNER_FE_LNB_UNICABLE == s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
        {
            TUNER_IFToDownlinkFreq(&(s_stSatPara[u32TunerId].stLNBConfig), stPara.unScanPara.stSat.enPolar, stPara.unScanPara.stSat.enLNB22K,
                                   stPara.unScanPara.stSat.u32StartFreq, &u32DlinkStart);
            TUNER_IFToDownlinkFreq(&(s_stSatPara[u32TunerId].stLNBConfig), stPara.unScanPara.stSat.enPolar, stPara.unScanPara.stSat.enLNB22K,
                                   stPara.unScanPara.stSat.u32StopFreq, &u32DlinkStop);

            stBlindScanCtrl.u32ScanTimes = 1;
            SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, stPara.unScanPara.stSat.enLNB22K, stPara.unScanPara.stSat.enPolar,
                            (HI_S32)(u32DlinkStart/1000), (HI_S32)(u32DlinkStop/1000));
        }
        else /*not unicable */
        {
            stBlindScanCtrl.u32ScanTimes = 1;
            SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, stPara.unScanPara.stSat.enLNB22K, stPara.unScanPara.stSat.enPolar,
                            (HI_S32)(stPara.unScanPara.stSat.u32StartFreq/1000), (HI_S32)(stPara.unScanPara.stSat.u32StopFreq/1000));
        }
    }
    /* Auto scan mode */
    else
    {
        if(HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
        {
            /* Single LO */
            if ((HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
                 || (s_stSatPara[u32TunerId].stLNBConfig.u32LowLO == s_stSatPara[u32TunerId].stLNBConfig.u32HighLO))
            {
                /* C band */
                if (HI_UNF_TUNER_FE_LNB_BAND_C == s_stSatPara[u32TunerId].stLNBConfig.enLNBBand)
                {
                    s32IFStart = (HI_S32)(s_stSatPara[u32TunerId].stLNBConfig.u32LowLO - SAT_C_MAX);
                    s32IFStop = (HI_S32)(s_stSatPara[u32TunerId].stLNBConfig.u32LowLO - SAT_C_MIN);
                    stBlindScanCtrl.u32ScanTimes = 2;
                    SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                    SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                }
                /* Ku band */
                else
                {
                    s32IFStart = (HI_S32)(SAT_KU_MIN - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                    s32IFStop = (HI_S32)(SAT_KU_MAX - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                    stBlindScanCtrl.u32ScanTimes = 2;
                    SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                    SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                }
            }
            /* Dual LO */
            else
            {
                /* C band */
                if (HI_UNF_TUNER_FE_LNB_BAND_C == s_stSatPara[u32TunerId].stLNBConfig.enLNBBand)
                {
                    if ((s_stSatPara[u32TunerId].stLNBConfig.u32LowLO == SAT_LO_C_L)
                                     && (s_stSatPara[u32TunerId].stLNBConfig.u32HighLO == SAT_LO_C_H))
                    {
                        /* 13V/18V select High/Low LO here */
                        stBlindScanCtrl.u32ScanTimes = 2;
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, SAT_IF_C_L_MIN, SAT_IF_C_L_MAX);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, SAT_IF_C_H_MIN, SAT_IF_C_H_MAX);
                    }
                    /* Special C band LNB */
                    else
                    {
                        stBlindScanCtrl.u32ScanTimes = 2;
                        s32IFStart = (HI_S32)(s_stSatPara[u32TunerId].stLNBConfig.u32LowLO - SAT_C_MAX);
                        s32IFStop = (HI_S32)(s_stSatPara[u32TunerId].stLNBConfig.u32LowLO - SAT_C_MIN);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                        s32IFStart = (HI_S32)(s_stSatPara[u32TunerId].stLNBConfig.u32HighLO - SAT_C_MAX);
                        s32IFStop = (HI_S32)(s_stSatPara[u32TunerId].stLNBConfig.u32HighLO - SAT_C_MIN);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, /*HI_FALSE*/HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                    }
                }
                /* Ku band */
                else
                {
                    /*no 22k switch*/
                    if (HI_UNF_TUNER_SWITCH_22K_NONE == s_stSatPara[u32TunerId].enSwitch22K)
                    {
                        stBlindScanCtrl.u32ScanTimes = 4;
                        s32IFStart = (HI_S32)(/*SAT_KU_MIN*/SAT_DOWNLINK_FREQ_KU_MID - s_stSatPara[u32TunerId].stLNBConfig.u32HighLO);
                        s32IFStop = (HI_S32)(SAT_KU_MAX - s_stSatPara[u32TunerId].stLNBConfig.u32HighLO);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, HI_UNF_TUNER_FE_LNB_22K_ON, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 2, HI_UNF_TUNER_FE_LNB_22K_ON, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                        s32IFStart = (HI_S32)(SAT_KU_MIN - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                        s32IFStop = (HI_S32)(/*SAT_KU_MAX*/SAT_DOWNLINK_FREQ_KU_MID - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 3, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                    }
                    /*22k switch 0Hz port*/
                    else if (HI_UNF_TUNER_SWITCH_22K_0 == s_stSatPara[u32TunerId].enSwitch22K)
                    {
                        stBlindScanCtrl.u32ScanTimes = 2;
                        s32IFStart = (HI_S32)(SAT_KU_MIN - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                        s32IFStop = (HI_S32)(/*SAT_KU_MAX*/SAT_DOWNLINK_FREQ_KU_MID - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                    }
                    /*22k switch 22kHz port*/
                    else if (HI_UNF_TUNER_SWITCH_22K_22 == s_stSatPara[u32TunerId].enSwitch22K)
                    {
                        stBlindScanCtrl.u32ScanTimes = 2;
                        s32IFStart = (HI_S32)(/*SAT_KU_MIN*/SAT_DOWNLINK_FREQ_KU_MID - s_stSatPara[u32TunerId].stLNBConfig.u32HighLO);
                        s32IFStop = (HI_S32)(SAT_KU_MAX - s_stSatPara[u32TunerId].stLNBConfig.u32HighLO);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, HI_UNF_TUNER_FE_LNB_22K_ON, HI_UNF_TUNER_FE_POLARIZATION_H, s32IFStart, s32IFStop);
                        SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, HI_UNF_TUNER_FE_LNB_22K_ON, HI_UNF_TUNER_FE_POLARIZATION_V, s32IFStart, s32IFStop);
                    }
                }
            }
        }
        else /*unicable LNB */
        {
            /*Single LO, bs 2 times, start downlink freq, stop downlink freq */
            if(s_stSatPara[u32TunerId].stLNBConfig.u32LowLO == s_stSatPara[u32TunerId].stLNBConfig.u32HighLO)
            {
                stBlindScanCtrl.u32ScanTimes = 2;
                u32DlinkStart = (SAT_IF_MIN + s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                u32DlinkStop = (SAT_IF_MAX + s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, (HI_S32)u32DlinkStart, (HI_S32)u32DlinkStop);
                SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, (HI_S32)u32DlinkStart, (HI_S32)u32DlinkStop);
            }
            /*Dual LO, bs 4 times, start downlink freq, stop downlink freq */
            else
            {
                stBlindScanCtrl.u32ScanTimes = 4;
                u32DlinkStart = SAT_DOWNLINK_FREQ_KU_MID;
                u32DlinkStop = (SAT_IF_MAX + s_stSatPara[u32TunerId].stLNBConfig.u32HighLO);
                SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 0, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, (HI_S32)u32DlinkStart, (HI_S32)u32DlinkStop);
                SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 2, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, (HI_S32)u32DlinkStart, (HI_S32)u32DlinkStop);
                u32DlinkStart = (SAT_IF_MIN + s_stSatPara[u32TunerId].stLNBConfig.u32LowLO);
                u32DlinkStop = SAT_DOWNLINK_FREQ_KU_MID;
                SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 1, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_H, (HI_S32)u32DlinkStart, (HI_S32)u32DlinkStop);
                SET_BLINDSCAN_CTRL_COND(u32TunerId, &stBlindScanCtrl, 3, HI_UNF_TUNER_FE_LNB_22K_OFF, HI_UNF_TUNER_FE_POLARIZATION_V, (HI_S32)u32DlinkStart, (HI_S32)u32DlinkStop);
            }
        }
    }

    /* Calculate scan frequency */
    for (i = 0; i < (HI_S32)(stBlindScanCtrl.u32ScanTimes); i++)
    {
        u32AllFreq += stBlindScanCtrl.astScanCond[i].u16StopFreq - stBlindScanCtrl.astScanCond[i].u16StartFreq;
    }

    /* Init the stBlindScan */
    stBlindScan.u32Port = u32TunerId;

    /* Start a scan */
    s32Result = ioctl(s_s32TunerFd, TUNER_BLINDSCAN_INIT_CMD, &stBlindScan);
    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("TUNER_BLINDSCAN_INIT_CMD error %d\n", s32Result);
    }

    stTunerData.u32Port = u32TunerId;
    //stLNBOut.u32Port = u32TunerId;

    /* Wait to over this scan and call back when new status or new TP */
    switch (s_strCurTunerAttr[u32TunerId].enDemodDevType)
    {
    case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
        u32StepFreq = 10;
        break;
    case HI_UNF_DEMOD_DEV_TYPE_3136:
    case HI_UNF_DEMOD_DEV_TYPE_3136I:
        u32StepFreq = 12;
        break;

    default:
        HI_ERR_TUNER("Demod type wrong!\n");
        s_stSatPara[u32TunerId].bBlindScanBusy = HI_FALSE;
        s_stSatPara[u32TunerId].bBlindScanStop = HI_FALSE;
        return HI_NULL;
    }

    for (i = 0; i < (HI_S32)(stBlindScanCtrl.u32ScanTimes); i++)
    {
        s32TPNum = 0;
        s32ReliTPNum = 0;
        fec_ok_cnt = 0;
        fec_no_ok_cnt = 0;
        last_fec_ok_cnt = 0;

        /* If register pfnDISEQCSet, set DiSEqC */
        if (stPara.unScanPara.stSat.pfnDISEQCSet)
        {
            stPara.unScanPara.stSat.pfnDISEQCSet(u32TunerId,
                                                 stBlindScanCtrl.astScanCond[i].enPolar,
                                                 stBlindScanCtrl.astScanCond[i].enLNB22K);
        }

        (HI_VOID)TUNER_SetLNBOutAnd22K(u32TunerId, stBlindScanCtrl.astScanCond[i].enPolar,
                              stBlindScanCtrl.astScanCond[i].enLNB22K);
		usleep(100*1000);

        u32StepNum = (HI_U32)(((stBlindScanCtrl.astScanCond[i].u16StopFreq
                      - stBlindScanCtrl.astScanCond[i].u16StartFreq) + u32StepFreq - 1) / u32StepFreq) + 1;

        for (j = 0; j < (HI_S32)u32StepNum; j++)
        {
            /*unicable freq is downlink freq, else is if freq. */
            stBlindScanInfo.pstPara->u32CentreFreq = stBlindScanCtrl.astScanCond[i].u16StartFreq
                                                     + ((HI_U32)j) * u32StepFreq;
            u32WindowMHz = stBlindScanInfo.pstPara->u32CentreFreq;
            stBlindScanInfo.pstPara->u16Count = 0;
            u16LastNum = 0;

            /*unicable should send ODU_ChannelChange cmd first, then calculate the if freq. */
            if(HI_UNF_TUNER_FE_LNB_UNICABLE == s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
            {
                (HI_VOID)UNIC_ChanChange(u32TunerId, u32WindowMHz, stBlindScanCtrl.astScanCond[i].enPolar);
                stBlindScanInfo.pstPara->u32CentreFreq = s_stSatPara[u32TunerId].stLNBConfig.u32UNICIFFreqMHz;
            }
            s32Result = ioctl(s_s32TunerFd, TUNER_BLINDSCAN_ACTION_CMD, &stBlindScanInfo);
            if (HI_SUCCESS != s32Result)
            {
                HI_ERR_TUNER("TUNER_BLINDSCAN_ACTION_CMD error %d\n", s32Result);
                enStatus = HI_UNF_TUNER_BLINDSCAN_STATUS_FAIL;
            }
            else
            {
                enStatus = HI_UNF_TUNER_BLINDSCAN_STATUS_SCANNING;
            }

            /* New TP callback */
            while (stBlindScanInfo.pstPara->u16Count > u16LastNum)
            {
                /* Convert IF(950-2150) to downlink frequency (C:3400-4200, Ku: 10600-12750 ) */
                /* unicable do not need. The freq offset of downlink is the same as the if freq.
                   SO we can substract the offset to the downlink freq directly. */
                if(HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
                {
                    TUNER_IFToDownlinkFreq(&(s_stSatPara[u32TunerId].stLNBConfig),
                                               stBlindScanCtrl.astScanCond[i].enPolar,
                                               stBlindScanCtrl.astScanCond[i].enLNB22K,
                                               stBlindScanInfo.pstPara->unResult.astSat[u16LastNum].u32Freq,
                                               &(stResult.u32Freq));
                }
                else
                {
                    stResult.u32Freq = u32WindowMHz * 1000 - (stBlindScanInfo.pstPara->unResult.astSat[u16LastNum].u32Freq -
                                           s_stSatPara[u32TunerId].stLNBConfig.u32UNICIFFreqMHz * 1000);
                }

                /* Symbol rate */
                stResult.u32SymbolRate = stBlindScanInfo.pstPara->unResult.astSat[u16LastNum].u32SymbolRate;

                /* Polarization */
                stResult.enPolar = stBlindScanCtrl.astScanCond[i].enPolar;

                stResult.cbs_reliablity = stBlindScanInfo.pstPara->unResult.astSat[u16LastNum].cbs_reliablity;
                //stResult.agc_h8 = stBlindScanInfo.pstPara->unResult.astSat[u16LastNum].agc_h8;

                u16LastNum++;

				if(stResult.u32SymbolRate > SAT_SYMBOLRATE_MAX)
				{
					continue;
				}

				if((s_stSatPara[u32TunerId].stLNBConfig.enLNBBand == HI_UNF_TUNER_FE_LNB_BAND_C)&&((stResult.u32Freq < SAT_C_MIN_KHZ)||(stResult.u32Freq > SAT_C_MAX_KHZ)))
				{
					continue;
				}

				if((s_stSatPara[u32TunerId].stLNBConfig.enLNBBand == HI_UNF_TUNER_FE_LNB_BAND_KU)&&((stResult.u32Freq < SAT_KU_MIN_KHZ)||(stResult.u32Freq > SAT_KU_MAX_KHZ)))
				{
					continue;
				}

                if ((HI_UNF_DEMOD_DEV_TYPE_3136 == s_strCurTunerAttr[u32TunerId].enDemodDevType) || \
                    (HI_UNF_DEMOD_DEV_TYPE_3136I == s_strCurTunerAttr[u32TunerId].enDemodDevType))
                {
                    if (s32TPNum < BUF_TP_NUM)
                    {
                        stTP[s32TPNum] = stResult;
                        s32TPNum ++;
                    }
                    else
                    {
                        HI_ERR_TUNER("Memory overflow!\n");
                        break;
                    }
                }

                if (HI_UNF_DEMOD_DEV_TYPE_AVL6211 == s_strCurTunerAttr[u32TunerId].enDemodDevType)
                {
                    unNotify.pstResult = &stResult;

                    /* Notify new TP */
                    stPara.unScanPara.stSat.pfnEVTNotify(u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_NEWRESULT, &unNotify);
                }
            }

            if (HI_UNF_DEMOD_DEV_TYPE_3136 == s_strCurTunerAttr[u32TunerId].enDemodDevType ||
                HI_UNF_DEMOD_DEV_TYPE_3136I == s_strCurTunerAttr[u32TunerId].enDemodDevType)
            {
                if (stBlindScanCtrl.astScanCond[i].u16StopFreq > stBlindScanCtrl.astScanCond[i].u16StartFreq)
                    u16ProgressPercent =
                        (HI_U16)(u16OverPercent + ((HI_U16)(/*stBlindScanInfo.pstPara->u32CentreFreq*/u32WindowMHz - stBlindScanCtrl.astScanCond[i].u16StartFreq)
                          * 20 / (HI_U16)(stBlindScanCtrl.astScanCond[i].u16StopFreq - stBlindScanCtrl.astScanCond[i].u16StartFreq)) / stBlindScanCtrl.u32ScanTimes);
            }
            else
            {
                if (u32AllFreq)
                    u16ProgressPercent =
                        (HI_U16)(((/*stBlindScanInfo.pstPara->u32CentreFreq*/u32WindowMHz - stBlindScanCtrl.astScanCond[i].u16StartFreq)
                         + u32OverFreq) * 100 / u32AllFreq);
            }

            if ((u16ProgressPercent != u16LastProgressPercent) && (u16ProgressPercent < 100))
            {
                /* Notify new status and percent */
                unNotify.pu16ProgressPercent = &u16ProgressPercent;
                stPara.unScanPara.stSat.pfnEVTNotify(u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_PROGRESS, &unNotify);

                /* Record new percent */
                u16LastProgressPercent = u16ProgressPercent;
            }

            /* Finish status */
            if ((u32StepNum - 1 == (HI_U32)j) && ((HI_U32)i == stBlindScanCtrl.u32ScanTimes - 1))
            {
                enStatus = HI_UNF_TUNER_BLINDSCAN_STATUS_FINISH;
            }

            /* Quit status */
            if (s_stSatPara[u32TunerId].bBlindScanStop)
            {
                enStatus = HI_UNF_TUNER_BLINDSCAN_STATUS_QUIT;
            }

            /* If over, break */
            if (enStatus > HI_UNF_TUNER_BLINDSCAN_STATUS_SCANNING)
            {
                stop_quit = 1;
                break;
            }
        }

        /* Over one time, add the over frequency */
        u32OverFreq += stBlindScanCtrl.astScanCond[i].u16StopFreq - stBlindScanCtrl.astScanCond[i].u16StartFreq;

        if (HI_UNF_DEMOD_DEV_TYPE_3136 == s_strCurTunerAttr[u32TunerId].enDemodDevType ||
            HI_UNF_DEMOD_DEV_TYPE_3136I == s_strCurTunerAttr[u32TunerId].enDemodDevType)
        {
            sort_tp_and_deredun(&s32TPNum, stTP);

            for (k = 0; k < s32TPNum; k++)
            {
                if(stTP[k].cbs_reliablity < 60)
                {
                    break;
                }
                else
                {
                    s32ReliTPNum++;
                }
            }

            for (k = 0; k < s32TPNum; k++)
            {
                fs_cur = stTP[k].u32SymbolRate;


                if(stTP[k].cbs_reliablity > 10)
                {
                    //unicable need to convert downklink freq to if freq.
                    stTPParm.pu32Frequency = &(stTP[k].u32Freq);
                    stTPParm.pu32SymbolRate = &fs_cur;
                    stTPParm.enPolar = stTP[k].enPolar;
                    stTPParm.cbs_reliablity = stTP[k].cbs_reliablity;
                    stTPParm.CBS_TH = s32TPNum;     //not match, changed by zouzhiyong
                    stTPParm.fec_ok_cnt = &fec_ok_cnt;
                    stTPParm.fec_no_ok_cnt = &fec_no_ok_cnt;
                    (HI_VOID)hi_tuner_tpverify(u32TunerId, &stTPParm);
                }
                stTP[k].u32SymbolRate = fs_cur; //Hz

                //remove same tp
                if (fec_ok_cnt > last_fec_ok_cnt)
                {
                    same_tp = 0;
                    if(fec_ok_cnt > 1)
                    {
                        for(kk = 0; kk < fec_ok_cnt - 1; kk++)
                        {
                            fs_dlt = (stTP[kk].u32SymbolRate > fs_cur) ? (stTP[kk].u32SymbolRate - fs_cur)/(fs_cur/1000) : \
                                                                         (fs_cur - stTP[kk].u32SymbolRate)/(fs_cur/1000);
                            if_dlt = (stTP[kk].u32Freq > stTP[k].u32Freq) ? (stTP[kk].u32Freq - stTP[k].u32Freq) : \
                                                                            (stTP[k].u32Freq - stTP[kk].u32Freq);

                            if((fs_dlt < 5) && (if_dlt < (fs_cur * 15/100000)))
                            {
                                //API_DEBUG("same_tp:  if freq=%d,  symbol rate=%d"\n", stTP[k].u32Freq, fs_cur/1000);
                                same_tp = 1;
                                fec_ok_cnt -= 1;
                            }
                        }
                    }

                    if(!same_tp)
                    {
                        last_fec_ok_cnt = fec_ok_cnt;
                        stTP[fec_ok_cnt - 1] = stTP[k];      //stTP array reinit from 0
                        unNotify.pstResult = &stTP[fec_ok_cnt-1];   //notice ?  origin is "&stTP[k]", changed by zouzhiyong
                        /* Notify new TP */
                        stPara.unScanPara.stSat.pfnEVTNotify(u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_NEWRESULT, &unNotify);
                    }
                }
                if ((k < s32ReliTPNum) && (0 != s32ReliTPNum))
                {
                    u16ProgressPercent =
                        (HI_U16)(u16OverPercent + (HI_U16)(20 + 75 * (k + 1) / s32ReliTPNum) / stBlindScanCtrl.u32ScanTimes);
                }
                else if (s32ReliTPNum < s32TPNum)
                {
                    u16ProgressPercent =
                        (HI_U16)(u16OverPercent + (HI_U16)(95 + 5 * (k + 1 - s32ReliTPNum) / (s32TPNum - s32ReliTPNum)) / stBlindScanCtrl.u32ScanTimes);
                }

                if ((u16ProgressPercent != u16LastProgressPercent) && (u16ProgressPercent < 100))
                {
                    /* Notify new status and percent */
                    unNotify.pu16ProgressPercent = &u16ProgressPercent;
                    stPara.unScanPara.stSat.pfnEVTNotify(u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_PROGRESS, &unNotify);

                    /* Record new percent */
                    u16LastProgressPercent = u16ProgressPercent;
                }

                /* Quit status */
                if (s_stSatPara[u32TunerId].bBlindScanStop)
                {
                    enStatus = HI_UNF_TUNER_BLINDSCAN_STATUS_QUIT;
                    stop_quit = 1;
                    break;
                }
            }

            u16OverPercent = (HI_U16)(100 * (HI_U16)(i + 1) / stBlindScanCtrl.u32ScanTimes);
        }

        if(stop_quit)
        {
            /* Notify new status and percent */
            unNotify.penStatus = &enStatus;
            stPara.unScanPara.stSat.pfnEVTNotify(u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_STATUS, &unNotify);
            break;
        }
        /*unNotify.ppstVerifyStart = &pstVerifyStart;
        stPara.unScanPara.stSat.pfnEVTNotify(u32TunerId, HI_UNF_TUNER_BLINDSCAN_EVT_VERIFY, &unNotify);
        pstVerifyStart = *(unNotify.ppstVerifyStart);*/
    }

#if 1
    for (i = 0; i < 4; i++)
    {
        stTunerData.u32Port = u32TunerId;
        stTunerData.u32Data = FunctMode_Demod;
        s32Result = ioctl(s_s32TunerFd, TUNER_SETFUNCMODE_CMD, &stTunerData);
        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("TUNER_SETFUNCMODE_CMD error %d\n", s32Result);
        }
        else
        {
            break;
        }
    }
#endif

    /*if (s_stSatPara[u32TunerId].pBlindScanMonitor)
    {
        free(s_stSatPara[u32TunerId].pBlindScanMonitor);
        s_stSatPara[u32TunerId].pBlindScanMonitor = HI_NULL;
    }*/

    s_stSatPara[u32TunerId].bBlindScanBusy = HI_FALSE;
    s_stSatPara[u32TunerId].bBlindScanStop = HI_FALSE;
    return HI_NULL;
}

HI_VOID* TUNER_DVBT2ScanThread(HI_VOID* pstTerScan)
{
	HI_S32 s32Result;
	HI_U32 u32TunerId = 0;
	//HI_UNF_TUNER_TER_SCAN_PARA_S stPara;
	TUNER_TERSCAN_INFO_S stTerScanInfo;
	//static HI_UNF_TUNER_TER_TPINFO_S stTerTP = {0};
	HI_UNF_TUNER_TER_CHANNEL_ATTR_S stTpArray[TER_MAX_TP];
	HI_UNF_TUNER_TER_PLP_ATTR_S stPlpAttr;
	HI_UNF_TUNER_TER_SCAN_STATUS_E stScanStatus = HI_UNF_TUNER_TER_SCAN_STATUS_IDLE;
	HI_UNF_TUNER_TER_SCAN_NOTIFY_U stScanNofify;
	HI_U32 u32Num,i,j,k,u32GrpNum = 0,u32Cnt = 0;
	HI_U8  u8CommExist = 0;
	typedef struct stT2MultiGroup
	{
		HI_U8 u8GrpId;
		HI_U8 u8CommId;
		HI_U8 u8Combination;
	}T2MultiGroup;
	T2MultiGroup T2PLPArray[T2_GROUP_SUM];

	if (HI_NULL == pstTerScan)
    {
        HI_ERR_TUNER("Input parameter(pstTerScan) invalid\n");
		//s_stTerPara[u32TunerId].bBlindScanBusy = HI_FALSE;
        return HI_NULL;
    }

	s_stTerPara[u32TunerId].bScanBusy = HI_TRUE;
	stTerScanInfo.u32Port = ((TERSCAN_PARA_S *)pstTerScan)->u32Port;
	memcpy(&(stTerScanInfo.stScanPara.stTer) , &(((TERSCAN_PARA_S *)pstTerScan)->stPara.stTer) ,sizeof(HI_UNF_TUNER_TER_SCAN_ATTR_S));

	s32Result = ioctl(s_s32TunerFd, TUNER_TERSCAN_ACTION_CMD, &stTerScanInfo);
	if(s32Result != HI_SUCCESS)
	{
		HI_ERR_TUNER("TUNER_TERSCAN_ACTION_CMD failed.\n");
		s_stTerPara[u32TunerId].bScanBusy = HI_FALSE;
		return HI_NULL;
	}

	memset(stTpArray,0,sizeof(stTpArray));
 	if(stTerScanInfo.stScanPara.enTpInfo.u8DVBTMode)   //dvb-t
	{
		stTpArray[0].u32Frequency = stTerScanInfo.stScanPara.stTer.u32Frequency;
		stTpArray[0].u32BandWidth = stTerScanInfo.stScanPara.stTer.u32BandWidth;
		stTpArray[0].u8DVBTMode = 1;
		stTpArray[0].enTSPri = HI_UNF_TUNER_TS_PRIORITY_HP;
		((TERSCAN_PARA_S *)pstTerScan)->stPara.u32ChanNum = 1;
		
		if(stTerScanInfo.stScanPara.enTpInfo.u8DVBTHier)
		{
			stTpArray[1].u32Frequency = stTerScanInfo.stScanPara.stTer.u32Frequency;
			stTpArray[1].u32BandWidth = stTerScanInfo.stScanPara.stTer.u32BandWidth;
			stTpArray[1].u8DVBTMode = 1;
			stTpArray[1].enTSPri = HI_UNF_TUNER_TS_PRIORITY_LP;
			((TERSCAN_PARA_S *)pstTerScan)->stPara.u32ChanNum = 2;
		}
	}
	else   //dvb-t2
	{
		u32Num = stTerScanInfo.stScanPara.enTpInfo.u8ProgNum;    //�Ȱ�group id����
		for(i=0;i<u32Num-1;i++)
		{
			for(j=0;j<u32Num - 1-i;j++)
			{
				if(stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[j].u8PlpGrpId 
					> stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[j+1].u8PlpGrpId)
				{
					memcpy(&stPlpAttr,&stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[j],sizeof(HI_UNF_TUNER_TER_PLP_ATTR_S));
					memcpy(&stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[j],&stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[j+1],sizeof(HI_UNF_TUNER_TER_PLP_ATTR_S));
					memcpy(&stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[j+1],&stPlpAttr,sizeof(HI_UNF_TUNER_TER_PLP_ATTR_S));
				}
			}
		}

		memset(T2PLPArray,0,sizeof(T2PLPArray));
		T2PLPArray[0].u8GrpId = stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[0].u8PlpGrpId;
		for(i = 0,u32GrpNum = 0;i < u32Num;i++)
		{
			if(T2PLPArray[u32GrpNum].u8GrpId != stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].u8PlpGrpId)
			{
				u32GrpNum++;
				if(u32GrpNum >= T2_GROUP_SUM)
				{
					s_stTerPara[u32TunerId].bScanBusy = HI_FALSE;
					return HI_NULL;
				}
				T2PLPArray[u32GrpNum].u8GrpId = stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].u8PlpGrpId;
				u32Cnt = 0;
				u8CommExist = 0;
			}

			if(HI_UNF_TUNER_T2_PLP_TYPE_COM == stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].enPlpType)
			{
				T2PLPArray[u32GrpNum].u8CommId = stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].u8PlpId;
				u8CommExist = 1;
			}
			
			u32Cnt++;
			if((u32Cnt >= 2) && u8CommExist)
			{
				T2PLPArray[u32GrpNum].u8Combination = 1;
			}
		}
		
		u32GrpNum = u32GrpNum + 1;

		for(i=0,j=i,k=0;i<u32Num;i++)
		{
			for(j=0;j < u32GrpNum;j++)
			{
				if(stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].u8PlpGrpId == T2PLPArray[j].u8GrpId)
					break;
			}

			if(j >= T2_GROUP_SUM)
			{
				HI_ERR_TUNER("plp group number is more than 16.\n");
				s_stTerPara[u32TunerId].bScanBusy = HI_FALSE;
				return HI_NULL;
			}
			
			if(HI_UNF_TUNER_T2_PLP_TYPE_COM == stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].enPlpType)
			{
				continue;
			}

			stTpArray[k].u32Frequency = stTerScanInfo.stScanPara.stTer.u32Frequency;
			stTpArray[k].u32BandWidth = stTerScanInfo.stScanPara.stTer.u32BandWidth;
			stTpArray[k].u8DVBTMode = 0;
			stTpArray[k].enChannelMode = stTerScanInfo.stScanPara.enTpInfo.enChannelAttr;
			stTpArray[k].u8PlpIndex = stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].u8PlpIndex;
			stTpArray[k].u8PlpId = stTerScanInfo.stScanPara.enTpInfo.enPlpAttr[i].u8PlpId;
			stTpArray[k].u8CommId = T2PLPArray[j].u8CommId;
			stTpArray[k].u8Combination = T2PLPArray[j].u8Combination;
			k++;
			if(k >= TER_MAX_TP)
				k = 0;
		}

		((TERSCAN_PARA_S *)pstTerScan)->stPara.u32ChanNum = k;
	}

	if(HI_NULL != stTerScanInfo.stScanPara.stTer.pfnEVTNotify)
	{
		*(stScanNofify.pu16ProgressPercent) =100;
		if((HI_NULL != stScanNofify.pstResult) && (sizeof(stScanNofify.pstResult) >= 16*sizeof(HI_UNF_TUNER_TER_CHANNEL_ATTR_S)))
		{
			memcpy(stScanNofify.pstResult,stTpArray,16*sizeof(HI_UNF_TUNER_TER_CHANNEL_ATTR_S));
		}
		stTerScanInfo.stScanPara.stTer.pfnEVTNotify(stTerScanInfo.u32Port,stScanStatus, &stScanNofify);
	}

	memcpy(((TERSCAN_PARA_S *)pstTerScan)->stPara.enChanArray,stTpArray,sizeof(stTpArray));

	/*printf("\n-----------------------scan result-------------------------\n");
	if(stTerScanInfo.stScanPara.enTpInfo.u8DVBTMode)   //dvb-t
	{
		printf("signal:DVB-T\n");
		printf("program number:%d\n",stTerScanInfo.stScanPara.enTpInfo.u8ProgNum);
	}
	else
	{
		printf("signal:DVB-T2\n");
		if(HI_UNF_TUNER_TER_MIXED_CHANNEL == stTerScanInfo.stScanPara.enTpInfo.enChannelMode)
		{
			printf("mixed channel,there are base and lite signals\n");
		}
		else
		{
			if(HI_UNF_TUNER_TER_MODE_BASE== stTerScanInfo.stScanPara.enTpInfo.enChannelAttr)
				printf("pure channel,there is only base signal\n");
			else
				printf("pure channel,there is only lite signal\n");
		}

		printf("program number:%d\n",stTerScanInfo.stScanPara.enTpInfo.u8ProgNum);
		
		printf("plp index		plp id		common plp id		combination\n");
		for(i=0;i < k;i++)
		{
			printf("%d			%d			%d			%d\n",stTpArray[i].u8PlpIndex,stTpArray[i].u8PlpId,stTpArray[i].u8CommId,stTpArray[i].u8Combination);
		}
	}*/

	s_stTerPara[u32TunerId].bScanBusy = HI_FALSE;
	
	return HI_NULL;
}

#if 0
static HI_VOID* TUNER_ConnectThread(HI_VOID * pstConnect)
{
    HI_S32 s32Ret;
    HI_U32 u32tunerId;
    TUNER_DATA_S stTunerData;
    HI_UNF_TUNER_FE_POLARIZATION_E  enPolar;
    HI_U32 u32Freq = 0;
    HI_U32 u32dLinkFreq = 0;
    HI_U32 u32SR = 0;
    HI_S32 s32NO;

    u32tunerId = ((TUNER_SIGNAL_S *)pstConnect)->u32Port;
    enPolar      = ((TUNER_SIGNAL_S *)pstConnect)->stSignal.enPolar;
    u32Freq = ((TUNER_SIGNAL_S *)pstConnect)->stSignal.u32Frequency;
    u32SR = ((TUNER_SIGNAL_S *)pstConnect)->stSignal.unSRBW.u32SymbolRate;

    if (u32SR < 5000000)
        s32NO = 1000;
    else if (u32SR < 10000000)
        s32NO = 120;
    else
        s32NO = 50;

    /*calculate the down link freq*/
    TUNER_IFToDownlinkFreq(&(s_stSatPara[u32tunerId].stLNBConfig),
                           enPolar,
                           s_stSatPara[u32tunerId].enLNB22K,
                           u32Freq,
                           &(u32dLinkFreq));

    stTunerData.u32Data = 0;
    stTunerData.u32Port = u32tunerId;


    s32Ret = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (HI_U32)pstConnect);

    do
    {
        usleep(10000);
        s32Ret = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
        if (HI_SUCCESS != s32Ret)
        {
            continue;
        }

        if (HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
        {
                HI_ERR_TUNER("Tuner   Lock freq %d symb %d  Success!\n",
                       u32dLinkFreq/1000, u32SR);

                /*automatically play the first program after locked successfully*/
                HI_ERR_TUNER("SUCCESS end\n");
            break;
        }
    } while((--s32NO) && (HI_TRUE != s_stSatPara[u32tunerId].bConnectStop));

    if (0 == s32NO)
    {
        HI_ERR_TUNER("Tuner Lock freq %d symb %d Fail timeout!\n",
               u32dLinkFreq, u32SR);
    }

    /*if (s_stSatPara[u32tunerId].pConnectMonitor)
    {
        free(s_stSatPara[u32tunerId].pConnectMonitor);
        s_stSatPara[u32tunerId].pConnectMonitor = HI_NULL;
        s_stSatPara[u32tunerId].bConnectStop     = HI_FALSE;
    }*/
    //((TUNER_SIGNAL_S *)pstConnect)->bstopFlag = HI_TRUE;

    s_stCurrentLockSignal[u32tunerId].u32Frequency = u32dLinkFreq;
    s_stCurrentLockSignal[u32tunerId].unSRBW.u32SymbolRate = u32SR;
    s_stCurrentLockSignal[u32tunerId].enPolar = enPolar;

    return HI_NULL;
}
#endif

static HI_S32 TUNER_DISEQC_Send22K(HI_U32 u32TunerId, HI_BOOL bStatus)
{
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = bStatus ? 1 : 0;
    s32Ret = ioctl(s_s32TunerFd, TUNER_SEND_CONTINUOUS_22K_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set continuous 22K fail.\n");
        return HI_ERR_TUNER_FAILED_DISEQC;
    }

    return HI_SUCCESS;
}

static HI_S32 TUNER_DISEQC_Stop22K(HI_U32 u32TunerId)
{
    HI_S32 s32Ret = HI_FAILURE;

    s32Ret = TUNER_DISEQC_Send22K(u32TunerId, HI_FALSE);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Stop 22K fail.\n");
        return HI_ERR_TUNER_FAILED_SWITCH;
    }

    /* Save status */
    //s_stSatPara[u32TunerId].enSavedSwitch22K = s_stSatPara[u32TunerId].enSwitch22K;
    return HI_SUCCESS;
}

static HI_S32 TUNER_DISEQC_Resume22K(HI_U32 u32TunerId)
{
    /* Resume */
    if (HI_UNF_TUNER_SWITCH_22K_22 == s_stSatPara[u32TunerId].enSwitch22K/*enSavedSwitch22K*/)
    {
        return TUNER_DISEQC_Send22K(u32TunerId, HI_TRUE);
    }
    else
    {
        return HI_SUCCESS;
    }
}

HI_UNF_TUNER_SWITCH_TONEBURST_E TUNER_DISEQC_GetToneBurstStatus(HI_U32 u32TunerId)
{
    return s_stSatPara[u32TunerId].enToneBurst;
}

HI_S32 TUNER_DISEQC_SendRecvMessage(HI_U32 u32TunerId,
                                           const HI_UNF_TUNER_DISEQC_SENDMSG_S * pstSendMsg,
                                           HI_UNF_TUNER_DISEQC_RECVMSG_S * pstRecvMsg)
{
    TUNER_DISEQC_SENDMSG_S stSend;
    TUNER_DISEQC_RECVMSG_S stRecv;
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RepeatTimes;
    HI_U32 u32RepeatTime = 0;
    HI_BOOL bSendTone = HI_FALSE;


    CHECK_TUNER_OPEN();
    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstSendMsg)
    {
        HI_ERR_TUNER("Input parameter(pstSendMsg) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstSendMsg->enLevel)
    {
        HI_ERR_TUNER("Input parameter(enLevel) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_SWITCH_TONEBURST_BUTT <= pstSendMsg->enToneBurst)
    {
        HI_ERR_TUNER("Input parameter(enToneBurst) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_DISEQC_MSG_MAX_LENGTH < pstSendMsg->u8Length)
    {
        HI_ERR_TUNER("Input parameter(u8Length) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_DISEQC_MAX_REPEAT_TIMES < pstSendMsg->u8RepeatTimes)
    {
        HI_ERR_TUNER("Input parameter(u8RepeatTimes) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* pstRecvMsg can be NULL */

    /* Handle tone burst */
    stTunerData.u32Port = u32TunerId;
    switch (pstSendMsg->enToneBurst)
    {
    case HI_UNF_TUNER_SWITCH_TONEBURST_NONE:
        bSendTone = HI_FALSE;
        break;

    case HI_UNF_TUNER_SWITCH_TONEBURST_0:
        bSendTone = HI_TRUE;
        stTunerData.u32Data = 0;
        break;

    case HI_UNF_TUNER_SWITCH_TONEBURST_1:
        bSendTone = HI_TRUE;
        stTunerData.u32Data = 1;
        break;
    default:
        HI_ERR_TUNER("Input parameter invalid!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Stop continuous 22K */
    (HI_VOID)TUNER_DISEQC_Stop22K(u32TunerId);
    usleep(DISEQC_DELAY_TIME_MS * 1000);

    /* Send command */
    stSend.u32Port = u32TunerId;
    stSend.stSendMsg = *pstSendMsg;
    u32RepeatTimes = pstSendMsg->u8RepeatTimes;
    //while (/*u32RepeatTimes >= 0*/1)
    for(;;)
    {
        /* Handle repeat */
        if (u32RepeatTime == 1)
        {
            stSend.stSendMsg.au8Msg[0] += 1;
        }

        /* Send command */
        s32Ret = ioctl(s_s32TunerFd, TUNER_DISEQC_SEND_MSG_CMD, &stSend);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Send DiSEqC message fail.\n");
            return HI_ERR_TUNER_FAILED_DISEQC;
        }

        /* After send command, delay 15ms */
        usleep(DISEQC_DELAY_TIME_MS * 1000);

        /* Send tone */
        if (bSendTone)
        {
            s32Ret = ioctl(s_s32TunerFd, TUNER_SEND_TONE_CMD, &stTunerData);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Send tone fail.\n");
                return HI_ERR_TUNER_FAILED_DISEQC;
            }

            /* After send tone, delay 15ms */
            usleep(DISEQC_DELAY_TIME_MS * 1000);
        }

        if (u32RepeatTimes == 0)
        {
            break;
        }

        u32RepeatTimes--;
        u32RepeatTime++;
    }

    /* Recv msessage */
    stRecv.u32Port = u32TunerId;
    stRecv.pstRecvMsg = pstRecvMsg;
    if (HI_NULL != pstRecvMsg)
    {
        if (HI_UNF_TUNER_DISEQC_LEVEL_2_X == pstSendMsg->enLevel)
        {
            s32Ret = ioctl(s_s32TunerFd, TUNER_DISEQC_RECV_MSG_CMD, &stRecv);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Recv DiSEqC message fail.\n");
                return HI_ERR_TUNER_FAILED_DISEQC;
            }

            usleep(DISEQC_DELAY_TIME_MS * 1000);
        }
        else
        {
            stRecv.pstRecvMsg->enStatus = HI_UNF_TUNER_DISEQC_RECV_UNSUPPORT;
            stRecv.pstRecvMsg->u8Length = 0;
        }
    }

    (HI_VOID)TUNER_DISEQC_Resume22K(u32TunerId);

    return HI_SUCCESS;
}

HI_S32 UNICABLE_DISEQC_SendRecvMessage(HI_U32 u32TunerId,
                                           const HI_UNF_TUNER_DISEQC_SENDMSG_S * pstSendMsg,
                                           HI_UNF_TUNER_DISEQC_RECVMSG_S * pstRecvMsg)
{
    TUNER_DISEQC_SENDMSG_S stSend;
    TUNER_DISEQC_RECVMSG_S stRecv;
    TUNER_DATA_S stTunerData;
	TUNER_LNB_OUT_S stLNBOut;
    HI_S32 s32Ret = HI_FAILURE;
    HI_U32 u32RepeatTimes;
    HI_U32 u32RepeatTime = 0;
    HI_BOOL bSendTone = HI_FALSE;

    if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstSendMsg)
    {
        HI_ERR_TUNER("Input parameter(pstSendMsg) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_DISEQC_LEVEL_BUTT <= pstSendMsg->enLevel)
    {
        HI_ERR_TUNER("Input parameter(enLevel) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_SWITCH_TONEBURST_BUTT <= pstSendMsg->enToneBurst)
    {
        HI_ERR_TUNER("Input parameter(enToneBurst) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_DISEQC_MSG_MAX_LENGTH < pstSendMsg->u8Length)
    {
        HI_ERR_TUNER("Input parameter(u8Length) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_DISEQC_MAX_REPEAT_TIMES < pstSendMsg->u8RepeatTimes)
    {
        HI_ERR_TUNER("Input parameter(u8RepeatTimes) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* pstRecvMsg can be NULL */

    /* Handle tone burst */
    stTunerData.u32Port = u32TunerId;
    switch (pstSendMsg->enToneBurst)
    {
    case HI_UNF_TUNER_SWITCH_TONEBURST_NONE:
        bSendTone = HI_FALSE;
        break;

    case HI_UNF_TUNER_SWITCH_TONEBURST_0:
        bSendTone = HI_TRUE;
        stTunerData.u32Data = 0;
        break;

    case HI_UNF_TUNER_SWITCH_TONEBURST_1:
        bSendTone = HI_TRUE;
        stTunerData.u32Data = 1;
        break;
    default:
        HI_ERR_TUNER("Input parameter invalid!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Stop continuous 22K */
    (HI_VOID)TUNER_DISEQC_Stop22K(u32TunerId);
	usleep(DISEQC_DELAY_TIME_MS * 1000);

	stLNBOut.u32Port = u32TunerId;
	stLNBOut.enOut = TUNER_LNB_OUT_13V;
	s32Ret = ioctl(s_s32TunerFd, TUNER_SET_LNBOUT_CMD, &stLNBOut);
	if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set LNB out 13V fail.\n");
        return HI_ERR_TUNER_FAILED_LNBCTRL;
    }

	stLNBOut.u32Port = u32TunerId;
	stLNBOut.enOut = TUNER_LNB_OUT_18V;
	s32Ret = ioctl(s_s32TunerFd, TUNER_SET_LNBOUT_CMD, &stLNBOut);
	if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set LNB out 18V fail.\n");
        return HI_ERR_TUNER_FAILED_LNBCTRL;
    }

    /* Send command */
    stSend.u32Port = u32TunerId;
    stSend.stSendMsg = *pstSendMsg;
    u32RepeatTimes = pstSendMsg->u8RepeatTimes;
    //while (/*u32RepeatTimes >= 0*/1)
    for(;;)
    {
        /* Handle repeat */
        if (u32RepeatTime == 1)
        {
            stSend.stSendMsg.au8Msg[0] += 1;
        }

        /* Send command */
        s32Ret = ioctl(s_s32TunerFd, TUNER_DISEQC_SEND_MSG_CMD, &stSend);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Send DiSEqC message fail.\n");
            return HI_ERR_TUNER_FAILED_DISEQC;
        }

		(HI_VOID)TUNER_DISEQC_Stop22K(u32TunerId);
        /* After send command, delay 15ms */
        usleep(DISEQC_DELAY_TIME_MS * 1000);

        /* Send tone */
        if (bSendTone)
        {
            s32Ret = ioctl(s_s32TunerFd, TUNER_SEND_TONE_CMD, &stTunerData);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Send tone fail.\n");
                return HI_ERR_TUNER_FAILED_DISEQC;
            }

            /* After send tone, delay 15ms */
            usleep(DISEQC_DELAY_TIME_MS * 1000);
        }

        if (u32RepeatTimes == 0)
        {
            break;
        }

        u32RepeatTimes--;
        u32RepeatTime++;
    }

    /* Recv msessage */
    stRecv.u32Port = u32TunerId;
    stRecv.pstRecvMsg = pstRecvMsg;
    if (HI_NULL != pstRecvMsg)
    {
        if (HI_UNF_TUNER_DISEQC_LEVEL_2_X == pstSendMsg->enLevel)
        {
            s32Ret = ioctl(s_s32TunerFd, TUNER_DISEQC_RECV_MSG_CMD, &stRecv);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Recv DiSEqC message fail.\n");
                return HI_ERR_TUNER_FAILED_DISEQC;
            }

            usleep(DISEQC_DELAY_TIME_MS * 1000);
        }
        else
        {
            stRecv.pstRecvMsg->enStatus = HI_UNF_TUNER_DISEQC_RECV_UNSUPPORT;
            stRecv.pstRecvMsg->u8Length = 0;
        }
    }

	stLNBOut.u32Port = u32TunerId;
	stLNBOut.enOut = TUNER_LNB_OUT_13V;
	s32Ret = ioctl(s_s32TunerFd, TUNER_SET_LNBOUT_CMD, &stLNBOut);
	if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set LNB out 13V fail.\n");
        return HI_ERR_TUNER_FAILED_LNBCTRL;
    }

    (HI_VOID)TUNER_DISEQC_Resume22K(u32TunerId);

    return HI_SUCCESS;
}

/*FFT Function*/
static HI_U8 rot_tbl[512] =
{
    255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,  255,
    255,  255,  255,  255,  254,  254,  254,  254,  254,  254,  254,  254,  254,  254,  253,  253,  253,  253,  253,  253,  253,  253,  252,  252,  252,  252,  252,  252,  252,  252,  251,  251,
    251,  251,  251,  251,  250,  250,  250,  250,  250,  250,  249,  249,  249,  249,  249,  249,  248,  248,  248,  248,  248,  247,  247,  247,  247,  247,  246,  246,  246,  246,  245,  245,
    245,  245,  245,  244,  244,  244,  244,  243,  243,  243,  243,  242,  242,  242,  242,  241,  241,  241,  241,  240,  240,  240,  239,  239,  239,  239,  238,  238,  238,  237,  237,  237,
    237,  236,  236,  236,  235,  235,  235,  234,  234,  234,  233,  233,  233,  232,  232,  232,  231,  231,  231,  230,  230,  230,  229,  229,  229,  228,  228,  228,  227,  227,  227,  226,
    226,  225,  225,  225,  224,  224,  224,  223,  223,  222,  222,  222,  221,  221,  220,  220,  220,  219,  219,  218,  218,  218,  217,  217,  216,  216,  215,  215,  215,  214,  214,  213,
    213,  212,  212,  212,  211,  211,  210,  210,  209,  209,  208,  208,  207,  207,  207,  206,  206,  205,  205,  204,  204,  203,  203,  202,  202,  201,  201,  200,  200,  199,  199,  198,
    198,  197,  197,  196,  196,  195,  195,  194,  194,  193,  193,  192,  192,  191,  191,  190,  190,  189,  189,  188,  188,  187,  186,  186,  185,  185,  184,  184,  183,  183,  182,  182,
    181,  180,  180,  179,  179,  178,  178,  177,  177,  176,  175,  175,  174,  174,  173,  173,  172,  171,  171,  170,  170,  169,  168,  168,  167,  167,  166,  165,  165,  164,  164,  163,
    162,  162,  161,  161,  160,  159,  159,  158,  157,  157,  156,  156,  155,  154,  154,  153,  152,  152,  151,  151,  150,  149,  149,  148,  147,  147,  146,  145,  145,  144,  144,  143,
    142,  142,  141,  140,  140,  139,  138,  138,  137,  136,  136,  135,  134,  134,  133,  132,  132,  131,  130,  130,  129,  128,  128,  127,  126,  125,  125,  124,  123,  123,  122,  121,
    121,  120,  119,  119,  118,  117,  117,  116,  115,  114,  114,  113,  112,  112,  111,  110,  109,  109,  108,  107,  107,  106,  105,  104,  104,  103,  102,  102,  101,  100,  99 ,  99 ,
    98 ,  97 ,  97 ,  96 ,  95 ,  94 ,  94 ,  93 ,  92 ,  91 ,  91 ,  90 ,  89 ,  88 ,  88 ,  87 ,  86 ,  86 ,  85 ,  84 ,  83 ,  83 ,  82 ,  81 ,  80 ,  80 ,  79 ,  78 ,  77 ,  77 ,  76 ,  75 ,
    74 ,  74 ,  73 ,  72 ,  71 ,  71 ,  70 ,  69 ,  68 ,  68 ,  67 ,  66 ,  65 ,  64 ,  64 ,  63 ,  62 ,  61 ,  61 ,  60 ,  59 ,  58 ,  58 ,  57 ,  56 ,  55 ,  55 ,  54 ,  53 ,  52 ,  51 ,  51 ,
    50 ,  49 ,  48 ,  48 ,  47 ,  46 ,  45 ,  45 ,  44 ,  43 ,  42 ,  41 ,  41 ,  40 ,  39 ,  38 ,  38 ,  37 ,  36 ,  35 ,  34 ,  34 ,  33 ,  32 ,  31 ,  31 ,  30 ,  29 ,  28 ,  27 ,  27 ,  26 ,
    25 ,  24 ,  24 ,  23 ,  22 ,  21 ,  20 ,  20 ,  19 ,  18 ,  17 ,  16 ,  16 ,  15 ,  14 ,  13 ,  13 ,  12 ,  11 ,  10 ,  9  ,  9  ,  8  ,  7  ,  6  ,  5  ,  5  ,  4  ,  3  ,  2  ,  2  ,  1
};

//fix point fft, input data length = 2^l, l should be less than 12
HI_S32 fft_fxpt(HI_UNF_TUNER_SAMPLE_DATA_S *pstData, HI_U8 u8LenPow, HI_U32 *pu32SignalSpecturm)
{
    HI_U32 n, nv2, i, j, k, m, le, lei, ip, idx;
    HI_S32 u_re, u_im;
    HI_S32 re_t, im_t;
    HI_U32 re_abs, im_abs, bigger, smaller;
    HI_U32 len = 0;

    if((11 < u8LenPow) || (9 > u8LenPow))
    {
        HI_INFO_TUNER("u8LenPow error!\n");
        return HI_FAILURE;
    }

    //reverse order
    len = (1 << u8LenPow);
    n   = (1 << u8LenPow); //u8LenPow=10  1024
    nv2 = (n >> 1); //512
    i   = 0;
    j   = 0;
    k   = 0;

    for (i = 0; i < (n - 1); i++)
    {
        if(i < j)  //j=512
        {
            re_t  = pstData[j].s32DataIP;
            pstData[j].s32DataIP = pstData[i].s32DataIP;
            pstData[i].s32DataIP = re_t;

            im_t  = /*im[j]*/pstData[j].s32DataQP;
            pstData[j].s32DataQP = pstData[i].s32DataQP;
            pstData[i].s32DataQP = im_t;
        }

        k = nv2; //512
        while(k <= j)
        {
            j  -= k;
            k   = (k >> 1);
        }
        j += k;
    }

    //fft core
    for (m = 1; m <= u8LenPow; m++)  //loop over stage  u8LenPow=10
    {
        le  = (1 << m); // 2-1024
        lei = (le >> 1); // 1-512

        for (j = 0; j < lei; j++) //loop over coef
        {
            idx     = j * (1 << (11-m));
            if((idx < 512))
            {
                u_re = (HI_S32)rot_tbl[idx];
                u_im = (HI_S32)rot_tbl[511-idx];
            }
            else
            {
                u_re = (HI_S32)rot_tbl[1023-idx];
                u_re = - u_re;
                u_im = (HI_S32)rot_tbl[idx-512];
            }

            for (i = j; i < n; i += le)
            {
                ip = i + lei;

                re_t = /*re[ip]*/pstData[ip].s32DataIP * u_re - pstData[ip].s32DataQP * u_im;
                im_t = /*re[ip]*/pstData[ip].s32DataIP * u_im + pstData[ip].s32DataQP * u_re;
                re_t = (re_t / 256);
                im_t = (im_t / 256);

                pstData[ip].s32DataIP = pstData[i].s32DataIP - re_t;
                pstData[ip].s32DataQP = pstData[i].s32DataQP - im_t;
                pstData[i].s32DataIP  += re_t;
                pstData[i].s32DataQP  += im_t;

                if((m % 2) && (m == u8LenPow)) //last odd stage, *0.707
                {
                    re_t = pstData[ip].s32DataIP * 181;
                    im_t = pstData[ip].s32DataQP * 181;
                    pstData[ip].s32DataIP  = (re_t / 256);
                    pstData[ip].s32DataQP  = (im_t / 256);

                    re_t  = pstData[i].s32DataIP * 181;
                    im_t  = pstData[i].s32DataQP * 181;
                    pstData[i].s32DataIP = (re_t / 256);
                    pstData[i].s32DataQP = (im_t / 256);
                }

                if ((m % 2) == 0) //even stage, *0.5
                {
                    pstData[ip].s32DataIP  = (pstData[ip].s32DataIP / 2);
                    pstData[ip].s32DataQP  = (pstData[ip].s32DataQP / 2);

                    pstData[i].s32DataIP   = (pstData[i].s32DataIP  / 2);
                    pstData[i].s32DataQP   = (pstData[i].s32DataQP  / 2);
                }
            }
        }
    }

    for (i = 0; i < len; i++)
    {
        re_abs  = (HI_U32)((pstData[i].s32DataIP >= 0) ? pstData[i].s32DataIP : -pstData[i].s32DataIP);
        im_abs  = (HI_U32)((pstData[i].s32DataQP >= 0) ? pstData[i].s32DataQP : -pstData[i].s32DataQP);

        bigger  = (re_abs >= im_abs) ? re_abs : im_abs;
        smaller = (re_abs >= im_abs) ? im_abs : re_abs;

        pu32SignalSpecturm[i]  = bigger + (smaller >> 1) - (smaller >> 8);
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_Init(HI_VOID)
{
    HI_U8 u8Port;

    if( s_bTunerInited )
    {
        return HI_SUCCESS;
    }

    s_strDeftTunerAttr[0].enDemodDevType = HI_UNF_DEMOD_DEV_TYPE_3130I;
    s_strDeftTunerAttr[0].enI2cChannel = 5;
    s_strDeftTunerAttr[0].enOutputMode = HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A;
    s_strDeftTunerAttr[0].enSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
    s_strDeftTunerAttr[0].enTunerDevType = HI_UNF_TUNER_DEV_TYPE_TDA18250B;

    s_strDeftTunerAttr[0].u32DemodAddr = QAM_PORT0_ADDR;
    s_strDeftTunerAttr[0].u32TunerAddr = TUNER_PORT0_ADDR;

    s_strDeftTunerAttr[1].enDemodDevType = HI_UNF_DEMOD_DEV_TYPE_3130E;
    s_strDeftTunerAttr[1].enI2cChannel = 3;
    s_strDeftTunerAttr[1].enOutputMode = HI_UNF_TUNER_OUTPUT_MODE_PARALLEL_MODE_A;
    s_strDeftTunerAttr[1].enSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
    s_strDeftTunerAttr[1].enTunerDevType = HI_UNF_TUNER_DEV_TYPE_CD1616;

    s_strDeftTunerAttr[1].u32DemodAddr = QAM_PORT1_ADDR;
    s_strDeftTunerAttr[1].u32TunerAddr = TUNER_PORT1_ADDR;

    s_strDeftTunerAttr[2].enDemodDevType = HI_UNF_DEMOD_DEV_TYPE_3130I;
    s_strDeftTunerAttr[2].enI2cChannel = 0;
    s_strDeftTunerAttr[2].enOutputMode = HI_UNF_TUNER_OUTPUT_MODE_SERIAL;
    s_strDeftTunerAttr[2].enSigType = HI_UNF_TUNER_SIG_TYPE_CAB;
    s_strDeftTunerAttr[2].enTunerDevType = HI_UNF_TUNER_DEV_TYPE_CD1616;

    s_strDeftTunerAttr[2].u32DemodAddr = QAM_PORT2_ADDR;
    s_strDeftTunerAttr[2].u32TunerAddr = TUNER_PORT2_ADDR;

    for(u8Port = 0; u8Port < UNF_TUNER_NUM; u8Port++)
    {
        s_strCurTunerAttr[u8Port].enDemodDevType = HI_UNF_DEMOD_DEV_TYPE_BUTT;
        s_strCurTunerAttr[u8Port].enI2cChannel = 16;
        s_strCurTunerAttr[u8Port].enOutputMode = HI_UNF_TUNER_OUTPUT_MODE_BUTT;
        s_strCurTunerAttr[u8Port].enSigType = HI_UNF_TUNER_SIG_TYPE_BUTT;
        s_strCurTunerAttr[u8Port].enTunerDevType = HI_UNF_TUNER_DEV_TYPE_BUTT;
    }

    /* Default single frequency, C band SAT_LO_C_L */
    s_stSatPara[0].pBlindScanMonitor = HI_NULL;
    //s_stSatPara[0].pConnectMonitor   = HI_NULL;
    s_stSatPara[0].bBlindScanStop  = HI_FALSE;
    s_stSatPara[0].bBlindScanBusy  = HI_FALSE;
    //s_stSatPara[0].bConnectStop       = HI_FALSE;
    s_stSatPara[0].stLNBConfig.enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_C;
    s_stSatPara[0].stLNBConfig.enLNBType = HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY;
    s_stSatPara[0].stLNBConfig.u32LowLO  = SAT_LO_C_L;
    s_stSatPara[0].stLNBConfig.u32HighLO = SAT_LO_C_L;
    s_stSatPara[0].enLNBPower  = HI_UNF_TUNER_FE_LNB_POWER_ON;
    s_stSatPara[0].enSwitch22K = HI_UNF_TUNER_SWITCH_22K_NONE;
    //s_stSatPara[0].enSavedSwitch22K = HI_UNF_TUNER_SWITCH_22K_NONE;
    s_stSatPara[0].enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    s_stSatPara[1].pBlindScanMonitor = HI_NULL;
    //s_stSatPara[1].pConnectMonitor   = HI_NULL;
    s_stSatPara[1].bBlindScanStop  = HI_FALSE;
    //s_stSatPara[1].bConnectStop       = HI_FALSE;
    s_stSatPara[1].bBlindScanBusy  = HI_FALSE;
    s_stSatPara[1].stLNBConfig.enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_C;
    s_stSatPara[1].stLNBConfig.enLNBType = HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY;
    s_stSatPara[1].stLNBConfig.u32LowLO  = SAT_LO_C_L;
    s_stSatPara[1].stLNBConfig.u32HighLO = SAT_LO_C_L;
    s_stSatPara[1].enLNBPower  = HI_UNF_TUNER_FE_LNB_POWER_ON;
    s_stSatPara[1].enSwitch22K = HI_UNF_TUNER_SWITCH_22K_NONE;
    //s_stSatPara[1].enSavedSwitch22K = HI_UNF_TUNER_SWITCH_22K_NONE;
    s_stSatPara[1].enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;
    s_stSatPara[2].pBlindScanMonitor = HI_NULL;
    //s_stSatPara[2].pConnectMonitor   = HI_NULL;
    s_stSatPara[2].bBlindScanStop = HI_FALSE;
    //s_stSatPara[2].bConnectStop      = HI_FALSE;
    s_stSatPara[2].bBlindScanBusy  = HI_FALSE;
    s_stSatPara[2].stLNBConfig.enLNBBand = HI_UNF_TUNER_FE_LNB_BAND_C;
    s_stSatPara[2].stLNBConfig.enLNBType = HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY;
    s_stSatPara[2].stLNBConfig.u32LowLO  = SAT_LO_C_L;
    s_stSatPara[2].stLNBConfig.u32HighLO = SAT_LO_C_L;
    s_stSatPara[2].enLNBPower  = HI_UNF_TUNER_FE_LNB_POWER_ON;
    s_stSatPara[2].enSwitch22K = HI_UNF_TUNER_SWITCH_22K_NONE;
    //s_stSatPara[2].enSavedSwitch22K = HI_UNF_TUNER_SWITCH_22K_NONE;
    s_stSatPara[2].enToneBurst = HI_UNF_TUNER_SWITCH_TONEBURST_NONE;

	s_stTerPara[0].pScanMonitor = HI_NULL;
	s_stTerPara[0].bScanStop = HI_FALSE;
	s_stTerPara[0].bScanBusy = HI_FALSE;
	s_stTerPara[0].enAntennaPower = HI_UNF_TUNER_TER_ANTENNA_POWER_OFF;
	s_stTerPara[1].pScanMonitor = HI_NULL;
	s_stTerPara[1].bScanStop = HI_FALSE;
	s_stTerPara[1].bScanBusy = HI_FALSE;
	s_stTerPara[1].enAntennaPower = HI_UNF_TUNER_TER_ANTENNA_POWER_OFF;
	s_stTerPara[2].pScanMonitor = HI_NULL;
	s_stTerPara[2].bScanStop = HI_FALSE;
	s_stTerPara[2].bScanBusy = HI_FALSE;
	s_stTerPara[2].enAntennaPower = HI_UNF_TUNER_TER_ANTENNA_POWER_OFF;
    s_bTunerInited = HI_TRUE;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_DeInit(HI_VOID)
{
    s_bTunerInited = HI_FALSE;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetDeftAttr(HI_U32 u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr)
{
    if( !s_bTunerInited )
    {
        HI_ERR_TUNER("TUNER UNF hasn't been Inited\n");
        return HI_ERR_TUNER_NOT_INIT;
    }

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    memcpy(pstTunerAttr, &s_strDeftTunerAttr[u32tunerId], sizeof(HI_UNF_TUNER_ATTR_S));

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetAttr(HI_U32  u32tunerId , const HI_UNF_TUNER_ATTR_S *pstTunerAttr)
{
    HI_S32 s32Result;
    TUNER_DATA_S stTunerData;
    TUNER_DATABUF_S stDataBuf = {0};
    HI_TunerAttr_S stTuner = {HI_UNF_TUNER_DEV_TYPE_BUTT, 0};
    HI_DemodAttr_S stDemod = {HI_UNF_DEMOD_DEV_TYPE_BUTT, 0};

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId)invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr)invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    /* Modified begin: l00185424 2011-11-26 Support satellite */
    if (HI_UNF_TUNER_SIG_TYPE_BUTT <= pstTunerAttr->enSigType)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr)invalid, sigType unsupported:%d\n",pstTunerAttr->enSigType);
        return HI_ERR_TUNER_INVALID_PARA;
    }
#if 0
    /* Check satellite tuner attribute */
    if (HI_UNF_TUNER_SIG_TYPE_SAT == pstTunerAttr->enSigType)
    {
        if (HI_UNF_TUNER_RFAGC_BUTT <= pstTunerAttr->unTunerAttr.stSat.enRFAGC)
        {
            HI_ERR_TUNER("Input parameter(enRFAGC)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
        if (HI_UNF_TUNER_IQSPECTRUM_BUTT <= pstTunerAttr->unTunerAttr.stSat.enIQSpectrum)
        {
            HI_ERR_TUNER("Input parameter(enIQSpectrum)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
        if (HI_UNF_TUNER_TSCLK_POLAR_BUTT <= pstTunerAttr->unTunerAttr.stSat.enTSClkPolar)
        {
            HI_ERR_TUNER("Input parameter(enTSClkPolar)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
        if (HI_UNF_TUNER_TS_FORMAT_BUTT <= pstTunerAttr->unTunerAttr.stSat.enTSFormat)
        {
            HI_ERR_TUNER("Input parameter(enTSFormat)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
        if (HI_UNF_TUNER_TS_SERIAL_PIN_BUTT <= pstTunerAttr->unTunerAttr.stSat.enTSSerialPIN)
        {
            HI_ERR_TUNER("Input parameter(enTSSerialPIN)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
        if (HI_UNF_TUNER_DISEQCWAVE_BUTT <= pstTunerAttr->unTunerAttr.stSat.enDiSEqCWave)
        {
            HI_ERR_TUNER("Input parameter(enDiSEqCWave)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
        if (HI_UNF_LNBCTRL_DEV_TYPE_BUTT <= pstTunerAttr->unTunerAttr.stSat.enLNBCtrlDev)
        {
            HI_ERR_TUNER("Input parameter(enLNBCtrlDev)invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }
#endif
    /* Modified end: l00185424 2011-11-26 Support satellite */
    if(16 <= pstTunerAttr->enI2cChannel)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr->enI2cChannell) invalid:%d\n", pstTunerAttr->enI2cChannel);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if(HI_UNF_TUNER_OUTPUT_MODE_BUTT <= pstTunerAttr->enOutputMode)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr->enOutputMode) invalid:%d\n", pstTunerAttr->enOutputMode);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stTunerData.u32Data = (HI_U32)(pstTunerAttr->enI2cChannel);
    stTunerData.u32Port = u32tunerId;
    s32Result = ioctl(s_s32TunerFd, TUNER_SELECT_I2C_CMD, (HI_U32)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner TUNER_SELECT_I2C_CMD error\n");
        return HI_ERR_TUNER_FAILED_SELECTI2CCHANNEL;
    }

    stDataBuf.u32Port = u32tunerId;	
	stTuner.enSigType = pstTunerAttr->enSigType;
    stTuner.enTunerDevType = pstTunerAttr->enTunerDevType;
    stTuner.u32TunerAddr= pstTunerAttr->u32TunerAddr;
    stDemod.enDemodDevType = pstTunerAttr->enDemodDevType;
    stDemod.u32DemodAddr = pstTunerAttr->u32DemodAddr;

    if(HI_UNF_TUNER_DEV_TYPE_BUTT <= stTuner.enTunerDevType)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr->enTunerDevType) invalid:%d\n", stTuner.enTunerDevType);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if(HI_UNF_DEMOD_DEV_TYPE_BUTT <= stDemod.enDemodDevType)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr->enDemodDevType) invalid:%d\n", stDemod.enDemodDevType);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stDataBuf.u32DataBuf[0] = (HI_U32)&stDemod;
    stDataBuf.u32DataBuf[1] = (HI_U32)&stTuner;

    /* Added begin: l00185424, for outer demod configure, 2012-01-19 */
    stDataBuf.u32DataBuf[2] = pstTunerAttr->u32ResetGpioNo;
    /* Added end: l00185424, for outer demod configure, 2012-01-19 */
    s32Result = ioctl(s_s32TunerFd, TUNER_SELECT_TYPE_CMD, (HI_U32)&stDataBuf);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner HI_TUNER_SelectTuner error\n");
        return s32Result;
    }

    stTunerData.u32Data = pstTunerAttr->enOutputMode ;
    stTunerData.u32Port = u32tunerId;

    s32Result = ioctl(s_s32TunerFd, TUNER_SET_TSTYPE_CMD, (HI_U32)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner HI_UNF_TUNER_SetTsType error\n");
        return HI_FAILURE;
    }

    memcpy(&s_strCurTunerAttr[u32tunerId], pstTunerAttr, sizeof(HI_UNF_TUNER_ATTR_S));

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetSatAttr(HI_U32   u32tunerId , const HI_UNF_TUNER_SAT_ATTR_S *pstSatTunerAttr)
{
    HI_S32 s32Ret;
    TUNER_DATA_S stTunerData;

    CHECK_TUNER_OPEN();
    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId)invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstSatTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr)invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_SIG_TYPE_SAT != s_strCurTunerAttr[u32tunerId].enSigType)
    {
        HI_ERR_TUNER("Current sig type is not satellite!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_RFAGC_BUTT <= pstSatTunerAttr->enRFAGC)
    {
        HI_ERR_TUNER("Input parameter(enRFAGC)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_IQSPECTRUM_BUTT <= pstSatTunerAttr->enIQSpectrum)
    {
        HI_ERR_TUNER("Input parameter(enIQSpectrum)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TSCLK_POLAR_BUTT <= pstSatTunerAttr->enTSClkPolar)
    {
        HI_ERR_TUNER("Input parameter(enTSClkPolar)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TS_FORMAT_BUTT <= pstSatTunerAttr->enTSFormat)
    {
        HI_ERR_TUNER("Input parameter(enTSFormat)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TS_SERIAL_PIN_BUTT <= pstSatTunerAttr->enTSSerialPIN)
    {
        HI_ERR_TUNER("Input parameter(enTSSerialPIN)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_DISEQCWAVE_BUTT <= pstSatTunerAttr->enDiSEqCWave)
    {
        HI_ERR_TUNER("Input parameter(enDiSEqCWave)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_LNBCTRL_DEV_TYPE_BUTT <= pstSatTunerAttr->enLNBCtrlDev)
    {
        HI_ERR_TUNER("Input parameter(enLNBCtrlDev)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stTunerData.u32Port = u32tunerId;
    stTunerData.u32Data = (HI_U32)pstSatTunerAttr;
    s32Ret = ioctl(s_s32TunerFd, TUNER_SETDEMODATTR_CMD, (HI_U32)&stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner TUNER_SETDEMODATTR_CMD error\n");
        return HI_ERR_TUNER_FAILED_SETSATATTR;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetTerAttr(HI_U32   u32tunerId , const HI_UNF_TUNER_TER_ATTR_S *pstTerTunerAttr)
{
    HI_S32 s32Ret;
    TUNER_DATA_S stTunerData;

    CHECK_TUNER_OPEN();
    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId)invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTerTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr)invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if ((HI_UNF_TUNER_SIG_TYPE_DVB_T != s_strCurTunerAttr[u32tunerId].enSigType)
        && (HI_UNF_TUNER_SIG_TYPE_DVB_T2 != s_strCurTunerAttr[u32tunerId].enSigType))
    {
        HI_ERR_TUNER("Current sig type is not DVB-T or DVB-T2!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /*if (HI_UNF_TUNER_RFAGC_BUTT <= pstTerTunerAttr->enRFAGC)
    {
        HI_ERR_TUNER("Input parameter(enRFAGC)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_IQSPECTRUM_BUTT <= pstTerTunerAttr->enIQSpectrum)
    {
        HI_ERR_TUNER("Input parameter(enIQSpectrum)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TSCLK_POLAR_BUTT <= pstTerTunerAttr->enTSClkPolar)
    {
        HI_ERR_TUNER("Input parameter(enTSClkPolar)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TS_FORMAT_BUTT <= pstTerTunerAttr->enTSFormat)
    {
        HI_ERR_TUNER("Input parameter(enTSFormat)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }
    if (HI_UNF_TUNER_TS_SERIAL_PIN_BUTT <= pstTerTunerAttr->enTSSerialPIN)
    {
        HI_ERR_TUNER("Input parameter(enTSSerialPIN)invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }*/

    stTunerData.u32Port = u32tunerId;
    stTunerData.u32Data = (HI_U32)pstTerTunerAttr;
    s32Ret = ioctl(s_s32TunerFd, TUNER_SETDEMODATTR_CMD, (HI_U32)&stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner TUNER_SETDEMODATTR_CMD error\n");
        return HI_ERR_TUNER_FAILED_SETTERATTR;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetAttr(HI_U32  u32tunerId , HI_UNF_TUNER_ATTR_S *pstTunerAttr )
{
    if( !s_bTunerInited )
    {
        HI_ERR_TUNER("TUNER UNF hasn't been Inited\n");
        return HI_ERR_TUNER_NOT_INIT;
    }

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId)invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTunerAttr)
    {
        HI_ERR_TUNER("Input parameter(pstTunerAttr)invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    memcpy(pstTunerAttr, &s_strCurTunerAttr[u32tunerId], sizeof(HI_UNF_TUNER_ATTR_S));

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_Open (HI_U32  u32tunerId)
{
    HI_S32  s32TunerFd = 0;

     if( !s_bTunerInited )
    {
        HI_ERR_TUNER("TUNER UNF hasn't been Inited\n");
        return HI_ERR_TUNER_NOT_INIT;
    }

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if( s_bTunerOpened )
    {
        return HI_SUCCESS;
    }

    HI_TUNER_LOCK();
    s32TunerFd = open("/dev/"UMAP_DEVNAME_TUNER, O_RDWR, 0);
    if (s32TunerFd < 0)
    {
        HI_ERR_TUNER("open %s tuner failed\n", "/dev/"UMAP_DEVNAME_TUNER);
        HI_TUNER_UNLOCK();

        return HI_ERR_TUNER_FAILED_INIT;
    }
    s_s32TunerFd = s32TunerFd;
    s_bTunerOpened = HI_TRUE;
    HI_TUNER_UNLOCK();
    return HI_SUCCESS;

}

HI_S32 HI_UNF_TUNER_Close(HI_U32    u32tunerId)
{
     if( !s_bTunerInited )
    {
        HI_ERR_TUNER("TUNER UNF hasn't been Inited\n");
        return HI_ERR_TUNER_NOT_INIT;
    }

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if( !s_bTunerOpened )
    {
        return HI_SUCCESS;
    }
    HI_TUNER_LOCK();
    close (s_s32TunerFd);
    HI_TUNER_UNLOCK();
    s_s32TunerFd = 0;
    s_bTunerOpened = HI_FALSE;

    return HI_SUCCESS;
}

#define FRAMING_BYTE (0)
#define ADDRESS_BYTE (1)
#define COMMAND_BYTE (2)
#define DATA_BYTE_0 (3)

#define FORMAT_DISEQC_CMD_VALUE(a, F, A, C, aD, L) \
    { \
        int i; \
        a[FRAMING_BYTE] = F; \
        a[ADDRESS_BYTE] = A; \
        a[COMMAND_BYTE] = C; \
        for (i = 0; i < L; i++){  a[DATA_BYTE_0 + i] = ((HI_U8*)aD)[i]; } \
    }

static HI_S32 UNIC_ChanChange(HI_U32 u32TunerId, HI_U32 u32Freq_MHz, HI_UNF_TUNER_FE_POLARIZATION_E enPolar)
{
    HI_U8 u8SCRNO = 0;
    HI_U8 u8LNBNO = 0;
    HI_U16 u16Tune = 0;
    HI_U8 u8ChanByte[2] = {0};
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_S32 s32Ret = 0;

    stSendMsg.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 5;
    stSendMsg.u8RepeatTimes = 0;
    u8SCRNO = s_stSatPara[u32TunerId].stLNBConfig.u8UNIC_SCRNO;
    /*low LO*/
    if(u32Freq_MHz < SAT_DOWNLINK_FREQ_KU_MID)
    {
        u16Tune = (HI_U16)((u32Freq_MHz - s_stSatPara[u32TunerId].stLNBConfig.u32LowLO) + s_stSatPara[u32TunerId].stLNBConfig.u32UNICIFFreqMHz)/4 - 350;
        if(HI_UNF_TUNER_SATPOSN_A == s_stSatPara[u32TunerId].stLNBConfig.enSatPosn)
        {
            if(HI_UNF_TUNER_FE_POLARIZATION_V == enPolar)
            {
                u8LNBNO = 0;
            }
            else
            {
                u8LNBNO = 2;
            }
        }
        else
        {
            if(HI_UNF_TUNER_FE_POLARIZATION_V == enPolar)
            {
                u8LNBNO = 4;
            }
            else
            {
                u8LNBNO = 6;
            }
        }
    }
    else /*high LO*/
    {
        u16Tune = (HI_U16)((u32Freq_MHz - s_stSatPara[u32TunerId].stLNBConfig.u32HighLO) + s_stSatPara[u32TunerId].stLNBConfig.u32UNICIFFreqMHz)/4 - 350;
        if(HI_UNF_TUNER_SATPOSN_A == s_stSatPara[u32TunerId].stLNBConfig.enSatPosn)
        {
            if(HI_UNF_TUNER_FE_POLARIZATION_V == enPolar)
            {
                u8LNBNO = 1;
            }
            else
            {
                u8LNBNO = 3;
            }
        }
        else
        {
            if(HI_UNF_TUNER_FE_POLARIZATION_V == enPolar)
            {
                u8LNBNO = 5;
            }
            else
            {
                u8LNBNO = 7;
            }
        }
    }

    u8ChanByte[0] = ((u8SCRNO & 7) << 5) | ((u8LNBNO & 7) << 2) | ((u16Tune >> 8) & 3);
    u8ChanByte[1] = u16Tune & 0xFF;

    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, 0xE0, 0x10, 0x5A, u8ChanByte, 2);

    s32Ret = UNICABLE_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send WRITE N0 fail.\n");
        return s32Ret;
    }

    /* If support level 2.x, handle received message here. */

    return HI_SUCCESS;
}

HI_S32 UNIC_PowerOFF(HI_U32 u32TunerId,HI_U8 u8SCRNO)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_S32 s32Ret = 0;
    HI_U8 u8ChanByte[2] = {0,0};

    if(u8SCRNO>=4)
    {
        HI_ERR_TUNER("SCR NO error.\n");
            return HI_FALSE;
    }

    stSendMsg.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 5;
    stSendMsg.u8RepeatTimes = 0;

    u8ChanByte[0] = ((u8SCRNO & 7) << 5) ;

    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, 0xE0, 0x10, 0x5A, u8ChanByte, 2);

    s32Ret = UNICABLE_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send WRITE N0 fail.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 UNIC_SCRxSignal_ON(HI_U32 u32TunerId)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_S32 s32Ret = 0;
    HI_U8 u8ChanByte[2] = {0,0};
    HI_U8 u8SubFunc=0;
    HI_U8 u8SCRNO = 0;

    stSendMsg.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 5;
    stSendMsg.u8RepeatTimes = 0;

    u8ChanByte[0] = ((u8SCRNO & 7) << 5) || ((u8SubFunc & 0x1f) << 0);

    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, 0xE0, 0x10, 0x5B, u8ChanByte, 2);

    s32Ret = UNICABLE_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send SCRxSignal ON fail.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 UNIC_Config(HI_U32 u32TunerId,HI_U8 u8SCRNO,HI_U8 u8AppNo)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_S32 s32Ret = 0;
    HI_U8 u8ChanByte[2] = {0,0};
    HI_U8 u8SubFunc=1;

    if(u8SCRNO>=4)
    {
        HI_ERR_TUNER("SCR NO error.\n");
        return HI_FALSE;
    }

    stSendMsg.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 5;
    stSendMsg.u8RepeatTimes = 0;

    u8ChanByte[0] = ((u8SCRNO & 7) << 5) || ((u8SubFunc & 0x1f) << 0);
    u8ChanByte[1] = u8AppNo;

    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, 0xE0, 0x10, 0x5B, u8ChanByte, 2);

    s32Ret = UNICABLE_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send unicable config fail.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

HI_S32 UNIC_LOFREQ(HI_U32 u32TunerId,HI_U8 u8SCRNO,HI_U8 u8LoFreqNo)
{
    HI_UNF_TUNER_DISEQC_SENDMSG_S stSendMsg;
    HI_S32 s32Ret = 0;
    HI_U8 u8ChanByte[2] = {0,0};
    HI_U8 u8SubFunc=2;

    if(u8SCRNO>=4)
    {
        HI_ERR_TUNER("SCR NO error.\n");
        return HI_FALSE;
    }

    stSendMsg.enLevel = HI_UNF_TUNER_DISEQC_LEVEL_1_X;
    stSendMsg.enToneBurst = TUNER_DISEQC_GetToneBurstStatus(u32TunerId);
    stSendMsg.u8Length = 5;
    stSendMsg.u8RepeatTimes = 0;

    u8ChanByte[0] = ((u8SCRNO & 7) << 5) || ((u8SubFunc & 0x1f) << 0);
    u8ChanByte[1] = u8LoFreqNo;

    FORMAT_DISEQC_CMD_VALUE(stSendMsg.au8Msg, 0xE0, 0x10, 0x5B, u8ChanByte, 2);

    s32Ret = UNICABLE_DISEQC_SendRecvMessage(u32TunerId, &stSendMsg, NULL/*&stRecvMsg*/);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Send unicable local oscillator number fail.\n");
        return s32Ret;
    }

    return HI_SUCCESS;
}

#define IS_SIGNAL_SAT(enSigType) (HI_UNF_TUNER_SIG_TYPE_SAT == enSigType)

HI_S32 HI_UNF_TUNER_GetDefaultTimeout(HI_U32  u32tunerId, const HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara, HI_U32 *pu32TimeOutMs)
{
    HI_U32 u32SymbRate_kHz = 0;

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstConnectPara)
    {
        HI_ERR_TUNER("Input parameter(pstConnectPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if(HI_NULL == pu32TimeOutMs)
    {
        HI_ERR_TUNER("Input parameter(pstConnectPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if ((HI_S32)IS_SIGNAL_SAT(s_strCurTunerAttr[u32tunerId].enSigType) != (HI_S32)IS_SIGNAL_SAT(pstConnectPara->enSigType))
    {
        HI_ERR_TUNER("Current sigtype and connect type not match!\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_SIG_TYPE_CAB == pstConnectPara->enSigType)
    {
        *pu32TimeOutMs = 1000;
    }
    /* Satellite */
    else if (HI_UNF_TUNER_SIG_TYPE_SAT == pstConnectPara->enSigType)
    {
        if (HI_UNF_TUNER_FE_LNB_BAND_C == s_stSatPara[u32tunerId].stLNBConfig.enLNBBand)
        {
            if ((SAT_C_MIN_KHZ > pstConnectPara->unConnectPara.stSat.u32Freq) ||
                (SAT_C_MAX_KHZ < pstConnectPara->unConnectPara.stSat.u32Freq))
            {
                HI_ERR_TUNER("Input parameter(u32Freq) invalid: %d\n",
                                    pstConnectPara->unConnectPara.stSat.u32Freq);
                return HI_ERR_TUNER_INVALID_PARA;
            }
        }

        if (HI_UNF_TUNER_FE_LNB_BAND_KU == s_stSatPara[u32tunerId].stLNBConfig.enLNBBand)
        {
            if ((SAT_KU_MIN_KHZ > pstConnectPara->unConnectPara.stSat.u32Freq) ||
                (SAT_KU_MAX_KHZ < pstConnectPara->unConnectPara.stSat.u32Freq))
            {
                HI_ERR_TUNER("Input parameter(u32Freq) invalid: %d\n",
                                    pstConnectPara->unConnectPara.stSat.u32Freq);
                return HI_ERR_TUNER_INVALID_PARA;
            }
        }

        if (SAT_SYMBOLRATE_MAX < pstConnectPara->unConnectPara.stSat.u32SymbolRate)
        {
            HI_ERR_TUNER("Input parameter(u32SymbolRate) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.u32SymbolRate);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= pstConnectPara->unConnectPara.stSat.enPolar)
        {
            HI_ERR_TUNER("Input parameter(enPolar) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.enPolar);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        u32SymbRate_kHz = pstConnectPara->unConnectPara.stSat.u32SymbolRate / 1000;

        switch (s_strCurTunerAttr[u32tunerId].enDemodDevType)
        {
        case HI_UNF_DEMOD_DEV_TYPE_3136:
        case HI_UNF_DEMOD_DEV_TYPE_3136I:
            if (2000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 2000;
            }
            else if (3000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 1500;
            }
            else if (4900 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 1400;
            }
            else if (8000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 1200;
            }
            else if (15000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 1150;
            }
            else if (20000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 1900;
            }
            else
            {
                *pu32TimeOutMs = 600;
            }
            break;

        case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
            if (5000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 10000;
            }
            else if (10000 > u32SymbRate_kHz)
            {
                *pu32TimeOutMs = 1200;
            }
            else
            {
                *pu32TimeOutMs = 1000;
            }
            break;

        default:
            HI_ERR_TUNER("Error demod type!\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }
    /* Terrestrial, Other */
    else if (HI_UNF_TUNER_SIG_TYPE_BUTT > pstConnectPara->enSigType)
    {
        *pu32TimeOutMs = 1000;
    }
    else
    {
        HI_ERR_TUNER("Error signal type!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

HI_S32 TUNER_Get_Agc(HI_U32 u32TunerId,HI_S32 s32CenterFreq, HI_S32 *ps32Agc)
{
	TUNER_DATABUF_S stTunerDataBuf = {0};
    HI_S32 s32Ret;
	HI_U32 CenterFreq;
	HI_U32 u32Percent = 0,u32Tmp = 0;
	
	if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

	stTunerDataBuf.u32Port = u32TunerId;
	stTunerDataBuf.u32DataBuf[0] = (HI_U32)s32CenterFreq;

	s32Ret = ioctl(s_s32TunerFd, TUNER_GET_AGC, &stTunerDataBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("get tone fail.\n");
        return HI_ERR_TUNER_FAILED_GETTONE;
    }

	*ps32Agc = (HI_S32)stTunerDataBuf.u32DataBuf[1];

    return HI_SUCCESS;
}

static HI_VOID* TUNER_TerSignalDetect(HI_VOID *pstSignal)
{
	TUNER_DATA_S stTunerData;
	static TUNER_SIGNAL_S stTunerSignal;
	HI_S32 s32Result = HI_SUCCESS ,s32TimeOut = 4000;
	HI_U32 u32TimeSpan = 0;

	if (HI_NULL == pstSignal)
    {
        HI_ERR_TUNER("Input parameter(pstSignal) invalid\n");
        return HI_NULL;
    }

	memcpy(&stTunerSignal,pstSignal,sizeof(TUNER_SIGNAL_S));

	printf("+++++++++++++freq:%d\n",stTunerSignal.stSignal.u32Frequency);
	printf("+++++++++++++bandwidth:%d\n",stTunerSignal.stSignal.unSRBW.u32SymbolRate);
	
	while(s32TimeOut > 0)
	{
		stTunerSignal.stSignal.u8DVBTMode = 1;
		stTunerSignal.enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;

	    s32Result = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
		if(HI_SUCCESS != s32Result)
	    {
	        HI_ERR_TUNER("dvb-t connect failed.\n");
	    }
		else
		{
			stTunerData.u32Data = 0;
		    stTunerData.u32Port = stTunerSignal.u32Port;
			u32TimeSpan = 0;
			s32TimeOut -= 500;
		    while (u32TimeSpan < 500)
		    {
		        s32Result = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
		        if(HI_SUCCESS != s32Result)
		        {
		        	HI_ERR_TUNER("dvb-t get lock failed.\n");
		        }

		        if(HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
		        {
		        	s_strCurTunerConnectPara[stTunerSignal.u32Port].enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;
		            return HI_NULL;
		        }
		        else
		        {
		            usleep(10 * 1000);
		            u32TimeSpan += 10;
		        }
		    }
		}

		stTunerSignal.stSignal.u8DVBTMode = 0;
		stTunerSignal.enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;

	    s32Result = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
		if(HI_SUCCESS != s32Result)
	    {
	        return HI_NULL;
	    }
		else
		{
			stTunerData.u32Data = 0;
		    stTunerData.u32Port = stTunerSignal.u32Port;
			u32TimeSpan = 0;
			s32TimeOut -= 1000;
		    while (u32TimeSpan < 1000)
		    {
		        s32Result = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
		        if(HI_SUCCESS != s32Result)
		        {
		            return HI_NULL;
		        }

		        if(HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
		        {
		        	s_strCurTunerConnectPara[stTunerSignal.u32Port].enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;
		            return HI_NULL;
		        }
		        else
		        {
		            usleep(10 * 1000);
		            u32TimeSpan += 10;
		        }
			}
		}
	}

	return HI_NULL;
}

HI_S32 HI_UNF_TUNER_Connect(HI_U32  u32tunerId, const HI_UNF_TUNER_CONNECT_PARA_S  *pstConnectPara, HI_U32 u32TimeOut)
{
    HI_S32       s32Ret = HI_SUCCESS;
    TUNER_DATA_S stTunerData;
    TUNER_ACC_QAM_PARAMS_S stTunerPara = {0};
    TUNER_SIGNAL_S stTunerSignal;
	static pthread_t*     pTerSignalDetect = HI_NULL; /* terr signal detect thread */
    HI_U32 u32TimeSpan = 0;
	HI_U32 i,u32Value = 1,u32New,u32N;
	HI_U32 u32Bit0Value,u32Bit7Value;
    TUNER_DATABUF_S stConnectTimeout;
    HI_UNF_TUNER_FE_LNB_22K_E enLNB22K;
    HI_S32 s32Result = HI_SUCCESS,s32TimeLeft;
    TUNER_DATA_S stTmpTunerData;
    HI_U8 u8ParamNOK = 0;

    CHECK_TUNER_OPEN();

    stTunerData.u32Data = 0;
    stTunerData.u32Port = u32tunerId;

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstConnectPara)
    {
        HI_ERR_TUNER("Input parameter(pstConnectPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if ((HI_S32)IS_SIGNAL_SAT(s_strCurTunerAttr[u32tunerId].enSigType) != (HI_S32)IS_SIGNAL_SAT(pstConnectPara->enSigType))
    {
        HI_ERR_TUNER("Current sigtype and connect type not match!\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    stTunerSignal.enSigType = pstConnectPara->enSigType;
    /* Modified begin: l00185424 2011-11-26 Support satellite */
    /* Cable */
    if ((HI_UNF_TUNER_SIG_TYPE_CAB == pstConnectPara->enSigType) || (HI_UNF_TUNER_SIG_TYPE_J83B == pstConnectPara->enSigType))
    {
        s_s32TunerFreq = pstConnectPara->unConnectPara.stCab.u32Freq;
        stTunerPara.u32Frequency = pstConnectPara->unConnectPara.stCab.u32Freq;
        stTunerPara.unSRBW.u32SymbolRate = pstConnectPara->unConnectPara.stCab.u32SymbolRate;
        stTunerPara.bSI = pstConnectPara->unConnectPara.stCab.bReverse;


        if(( stTunerPara.u32Frequency < QAM_RF_MIN ) || ( stTunerPara.u32Frequency > QAM_RF_MAX ))
        {
            HI_ERR_TUNER("Input parameter(pSignal.u32frequency) invalid freq = %d\n", stTunerPara.u32Frequency);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if ((stTunerPara.unSRBW.u32SymbolRate < 900000) || (stTunerPara.unSRBW.u32SymbolRate > 7200000))
        {
            HI_ERR_TUNER("Input parameter(pSignal.u32SymbolRate = %d) invalid, \n", stTunerPara.unSRBW.u32SymbolRate);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        switch(pstConnectPara->unConnectPara.stCab.enModType)
        {
            case HI_UNF_MOD_TYPE_QAM_16:
                stTunerPara.enQamType = QAM_TYPE_16;
                break;

            case HI_UNF_MOD_TYPE_QAM_32:
                stTunerPara.enQamType = QAM_TYPE_32;
                break;

            case HI_UNF_MOD_TYPE_QAM_64:
            case HI_UNF_MOD_TYPE_DEFAULT:
                stTunerPara.enQamType = QAM_TYPE_64;
                break;

            case HI_UNF_MOD_TYPE_QAM_128:
                stTunerPara.enQamType = QAM_TYPE_128;
                break;

            case HI_UNF_MOD_TYPE_QAM_256:
                stTunerPara.enQamType = QAM_TYPE_256;
                break;
            default:
                HI_ERR_TUNER("Tuner HI_UNF_SET_eqamType error:%d\n",pstConnectPara->unConnectPara.stCab.enModType);
                return HI_ERR_TUNER_INVALID_PARA;

        }


        s_stCurrentSignal[u32tunerId] =  stTunerPara;
        stTunerSignal.u32Port = u32tunerId;
        stTunerSignal.stSignal = stTunerPara;
        memcpy(&s_strCurTunerConnectPara[u32tunerId], pstConnectPara, sizeof(HI_UNF_TUNER_CONNECT_PARA_S));

        stConnectTimeout.u32DataBuf[0] = u32TimeOut;
        stConnectTimeout.u32Port = u32tunerId;
        s32Ret = ioctl(s_s32TunerFd, TUNER_CONNECT_TIMEOUT_CMD, (unsigned long)&stConnectTimeout);
        if(HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("HI_UNF TUNER_CONNECT_TIMEOUT_CMD");
            return s32Ret;
        }

        s32Ret = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
        if(HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }

        if(0 == u32TimeOut)
        {
            return HI_SUCCESS;
        }

        while (u32TimeSpan < u32TimeOut)
        {
            stTunerData.u32Port = u32tunerId;
            s32Ret = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
            if(HI_SUCCESS != s32Ret)
            {
                return s32Ret;
            }

            if(HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
            {
                return HI_SUCCESS;
            }
            else
            {
                usleep(10 * 1000);
                u32TimeSpan += 10;
            }
        }
    }
    /* Satellite */
    else if (HI_UNF_TUNER_SIG_TYPE_SAT == pstConnectPara->enSigType)
    {
        if (HI_UNF_TUNER_FE_LNB_BAND_C == s_stSatPara[u32tunerId].stLNBConfig.enLNBBand)
        {
            if ((SAT_C_MIN_KHZ > pstConnectPara->unConnectPara.stSat.u32Freq) ||
                (SAT_C_MAX_KHZ < pstConnectPara->unConnectPara.stSat.u32Freq))
            {
                HI_ERR_TUNER("Input parameter(u32Freq) invalid: %d\n",
                                    pstConnectPara->unConnectPara.stSat.u32Freq);
                u8ParamNOK = 1;
                //return HI_ERR_TUNER_INVALID_PARA;
            }
        }

        if (HI_UNF_TUNER_FE_LNB_BAND_KU == s_stSatPara[u32tunerId].stLNBConfig.enLNBBand)
        {
            if ((SAT_KU_MIN_KHZ > pstConnectPara->unConnectPara.stSat.u32Freq) ||
                (SAT_KU_MAX_KHZ < pstConnectPara->unConnectPara.stSat.u32Freq))
            {
                HI_ERR_TUNER("Input parameter(u32Freq) invalid: %d\n",
                                    pstConnectPara->unConnectPara.stSat.u32Freq);
                u8ParamNOK = 1;
                //return HI_ERR_TUNER_INVALID_PARA;
            }
        }

        if (SAT_SYMBOLRATE_MAX < pstConnectPara->unConnectPara.stSat.u32SymbolRate)
        {
            HI_ERR_TUNER("Input parameter(u32SymbolRate) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.u32SymbolRate);
            u8ParamNOK = 1;
            //return HI_ERR_TUNER_INVALID_PARA;
        }

        if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= pstConnectPara->unConnectPara.stSat.enPolar)
        {
            HI_ERR_TUNER("Input parameter(enPolar) invalid: %d\n",
                                pstConnectPara->unConnectPara.stSat.enPolar);
            u8ParamNOK = 1;
            //return HI_ERR_TUNER_INVALID_PARA;

        }

        for (i = 0; i < 4; i++)
        {
            stTmpTunerData.u32Port = u32tunerId;
            stTmpTunerData.u32Data = FunctMode_Demod;
            s32Result = ioctl(s_s32TunerFd, TUNER_SETFUNCMODE_CMD, &stTmpTunerData);
            if (HI_SUCCESS != s32Result)
            {
                HI_ERR_TUNER("TUNER_SETFUNCMODE_CMD error %d\n", s32Result);
            }
            else
            {
                break;
            }
        }

        if (u8ParamNOK)
        {
            stTunerSignal.u32Port  = u32tunerId;
            stTunerSignal.stSignal.u32Frequency = 900000;
            stTunerSignal.stSignal.unSRBW.u32SymbolRate = 30000000;
            stTunerSignal.stSignal.enPolar = HI_UNF_TUNER_FE_POLARIZATION_H;
            (HI_VOID)ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
            return HI_ERR_TUNER_INVALID_PARA;

        }

#if 0
        if (s_stSatPara[u32tunerId].pConnectMonitor)
        {
            //set the stop flag
            s_stSatPara[u32tunerId].bConnectStop = HI_TRUE;
            (HI_VOID)pthread_join(*s_stSatPara[u32tunerId].pConnectMonitor, HI_NULL);
            HI_FREE(HI_ID_TUNER, s_stSatPara[u32tunerId].pConnectMonitor);
            s_stSatPara[u32tunerId].pConnectMonitor = HI_NULL;
            s_stSatPara[u32tunerId].bConnectStop     = HI_FALSE;
        }
#endif

        /* Convert downlink frequency to IF */
        TUNER_DownlinkFreqToIF(&(s_stSatPara[u32tunerId].stLNBConfig), pstConnectPara->unConnectPara.stSat.enPolar,
                               pstConnectPara->unConnectPara.stSat.u32Freq, &(stTunerPara.u32Frequency), &enLNB22K);

        stTunerPara.unSRBW.u32SymbolRate = pstConnectPara->unConnectPara.stSat.u32SymbolRate;
        stTunerPara.enPolar = pstConnectPara->unConnectPara.stSat.enPolar;

        /* LNB power and 22K signal switch */
        s32Ret = TUNER_SetLNBOutAnd22K(u32tunerId, pstConnectPara->unConnectPara.stSat.enPolar, enLNB22K);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("TUNER_SetLNBOutAnd22K fail.\n");
        }

        if(HI_UNF_TUNER_FE_LNB_UNICABLE == s_stSatPara[u32tunerId].stLNBConfig.enLNBType)
        {
            s32Ret = UNIC_ChanChange(u32tunerId, pstConnectPara->unConnectPara.stSat.u32Freq / 1000, pstConnectPara->unConnectPara.stSat.enPolar);
            if (HI_SUCCESS != s32Ret)
            {
                HI_ERR_TUNER("Send ODU_ChannelChange cmd fail.\n");
            }
        }

#if 0
        s_stSatPara[u32tunerId].pConnectMonitor = (pthread_t*)HI_MALLOC(HI_ID_TUNER, sizeof(pthread_t));
        if (HI_NULL == s_stSatPara[u32tunerId].pConnectMonitor)
        {
            HI_ERR_TUNER("No memory.\n");
            return HI_ERR_TUNER_FAILED_CONNECT;
        }

        //stTunerSignal.bstopFlag = HI_FALSE;
        s32Ret = pthread_create(s_stSatPara[u32tunerId].pConnectMonitor, 0, TUNER_ConnectThread, &stTunerSignal);

        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Create pthread fail.\n");
            if (s_stSatPara[u32tunerId].pConnectMonitor)
            {
                HI_FREE(HI_ID_TUNER, s_stSatPara[u32tunerId].pConnectMonitor);
                s_stSatPara[u32tunerId].pConnectMonitor = HI_NULL;
                s_stSatPara[u32tunerId].bConnectStop = HI_FALSE;
            }

            return HI_ERR_TUNER_FAILED_CONNECT;
        }
#endif
		/**add begin by wangjunqi 20140825:calculate initial scrambling code***/
		u32N = pstConnectPara->unConnectPara.stSat.u32ScrambleValue;
		for(i = 0;i < u32N;i++)
		{
			u32Bit0Value = u32Value & 0x1;
			u32Bit7Value = (u32Value >> 7) & 0x1;
			u32New = (u32Bit0Value + u32Bit7Value) % 2;
			u32Value = (u32Value >> 1) | (u32New << 17);
		}
		stTunerPara.u23ScrambleCode = u32Value;
		/**add end***/

		s_stCurrentSignal[u32tunerId] = stTunerPara;
        stTunerSignal.u32Port  = u32tunerId;
        stTunerSignal.stSignal = stTunerPara;
		memcpy(&s_strCurTunerConnectPara[u32tunerId], pstConnectPara, sizeof(HI_UNF_TUNER_CONNECT_PARA_S));

        s32Ret = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }

        if (0 == u32TimeOut)
        {
            return HI_SUCCESS;
        }

		

        while (u32TimeSpan < u32TimeOut)
        {
            stTunerData.u32Port = u32tunerId;
            s32Ret = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
            if (HI_SUCCESS != s32Ret)
            {
                return s32Ret;
            }

            if (HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
            {
                return HI_SUCCESS;
            }
            else
            {
                usleep(10 * 1000);
                u32TimeSpan += 10;
            }
        }

        return HI_SUCCESS;
    }
    /* Terrestrial, Other */
	else if((HI_UNF_TUNER_SIG_TYPE_DVB_T | HI_UNF_TUNER_SIG_TYPE_DVB_T2) == pstConnectPara->enSigType)
	{
		s32TimeLeft = u32TimeOut;
		stTunerPara.u32Frequency  = pstConnectPara->unConnectPara.stTer.u32Freq;
        stTunerPara.unSRBW.u32BandWidth = pstConnectPara->unConnectPara.stTer.u32BandWidth;
        stTunerPara.bSI = pstConnectPara->unConnectPara.stTer.bReverse;
        stTunerPara.unTer.enDVBT2.enChannelAttr = pstConnectPara->unConnectPara.stTer.enChannelMode;
        stTunerPara.unTer.enDVBT = pstConnectPara->unConnectPara.stTer.enDVBTPrio;
		memcpy(&s_strCurTunerConnectPara[u32tunerId], pstConnectPara, sizeof(HI_UNF_TUNER_CONNECT_PARA_S));
		s_strCurTunerConnectPara[u32tunerId].enSigType = (HI_UNF_TUNER_SIG_TYPE_DVB_T | HI_UNF_TUNER_SIG_TYPE_DVB_T2);
		if(u32TimeOut == 0)
		{
			stTunerSignal.u32Port = u32tunerId;
			stTunerSignal.stSignal = stTunerPara;

			if (HI_NULL != pTerSignalDetect)
	        {
                (HI_VOID)pthread_join(*pTerSignalDetect, HI_NULL);
                HI_FREE(HI_ID_TUNER, pTerSignalDetect);
                pTerSignalDetect = HI_NULL;
	        }

			pTerSignalDetect = (pthread_t*)HI_MALLOC(HI_ID_TUNER, sizeof(pthread_t));
	        if (HI_NULL == pTerSignalDetect)
	        {
	            HI_ERR_TUNER("No memory.\n");
	            return HI_FAILURE;
	        }
		
			s32Result = pthread_create(pTerSignalDetect, 0, TUNER_TerSignalDetect, &stTunerSignal);
			if (HI_SUCCESS != s32Result)
	        {
	            HI_ERR_TUNER("Create pthread fail.\n");
	            if (pTerSignalDetect)
	            {
	                HI_FREE(HI_ID_TUNER, pTerSignalDetect);
	                pTerSignalDetect = HI_NULL;
	            }
				
	            return HI_FAILURE;
	        }
			return HI_SUCCESS;
		}
		else
		{
			while(s32TimeLeft > 0)
			{
			    stTunerSignal.u32Port = u32tunerId;
				stTunerPara.u8DVBTMode = 1;
			    stTunerSignal.stSignal = stTunerPara;
				stTunerSignal.enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;

			    s32Result = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
				if(HI_SUCCESS != s32Result)
			    {
			        HI_ERR_TUNER("dvb-t connect failed.\n");
			    }
				else
				{
					stTunerData.u32Data = 0;
				    stTunerData.u32Port = u32tunerId;
					if(s32TimeLeft >= 500)
					{
						s32TimeLeft = s32TimeLeft - 500;
						u32TimeSpan = 0;
					    while (u32TimeSpan < 500)
					    {
					        stTunerData.u32Port = u32tunerId;
					        s32Result = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
					        if(HI_SUCCESS != s32Result)
					        {
					        	HI_ERR_TUNER("dvb-t get lock failed.\n");
					        }

					        if(HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
					        {
					        	s_strCurTunerConnectPara[u32tunerId].enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T;
					            return HI_SUCCESS;
					        }
							/*else if(HI_UNF_TUNER_SIGNAL_DROPPED == stTunerData.u32Data)
							{
								break;
							}*/
					        else
					        {
					            usleep(10 * 1000);
					            u32TimeSpan += 10;
					        }
					    }
					}
					else
					{
						return HI_ERR_TUNER_FAILED_TERSCANTIMEOUT;
					}
				}

				stTunerSignal.u32Port = u32tunerId;
				stTunerPara.u8DVBTMode = 0;
			    stTunerSignal.stSignal = stTunerPara;
				stTunerSignal.enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;

			    s32Result = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
				if(HI_SUCCESS != s32Result)
			    {
			        return s32Result;
			    }
				else
				{
					stTunerData.u32Data = 0;
				    stTunerData.u32Port = u32tunerId;
					if(s32TimeLeft >= 1000)
					{
						s32TimeLeft = s32TimeLeft - 1000;
						u32TimeSpan = 0;
					    while (u32TimeSpan < 1000)
					    {
					        stTunerData.u32Port = u32tunerId;
					        s32Result = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
					        if(HI_SUCCESS != s32Result)
					        {
					            return s32Result;
					        }

					        if(HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
					        {
					        	s_strCurTunerConnectPara[u32tunerId].enSigType = HI_UNF_TUNER_SIG_TYPE_DVB_T2;
					            return HI_SUCCESS;
					        }
							/*else if(HI_UNF_TUNER_SIGNAL_DROPPED == stTunerData.u32Data)
							{
								break;
							}*/
					        else
					        {
					            usleep(10 * 1000);
					            u32TimeSpan += 10;
					        }
					   }
					}
					else
					{
						return HI_ERR_TUNER_FAILED_TERSCANTIMEOUT;
					}
				}
			}
		}
	}
    else if (HI_UNF_TUNER_SIG_TYPE_BUTT > pstConnectPara->enSigType)
    {
        if(HI_UNF_TUNER_SIG_TYPE_DVB_T == pstConnectPara->enSigType)
        {
            stTunerPara.u8DVBTMode = 1;
        }
        else
        {
            stTunerPara.u8DVBTMode = 0;
        }

        stTunerPara.u32Frequency  = pstConnectPara->unConnectPara.stTer.u32Freq;
        stTunerPara.unSRBW.u32BandWidth = pstConnectPara->unConnectPara.stTer.u32BandWidth;
        stTunerPara.bSI = pstConnectPara->unConnectPara.stTer.bReverse;
        stTunerPara.unTer.enDVBT2.enChannelAttr = pstConnectPara->unConnectPara.stTer.enChannelMode;
        stTunerPara.unTer.enDVBT = pstConnectPara->unConnectPara.stTer.enDVBTPrio;

        switch(pstConnectPara->unConnectPara.stTer.enModType)
        {
            case HI_UNF_MOD_TYPE_QAM_16:
                stTunerPara.enQamType=QAM_TYPE_16;
                break;
            case  HI_UNF_MOD_TYPE_QAM_64:
                stTunerPara.enQamType=QAM_TYPE_64;
                break;
            default:
                stTunerPara.enQamType=QAM_TYPE_16;
                break;
        }

        if ((stTunerPara.u32Frequency < TER_RF_MIN) || (stTunerPara.u32Frequency > TER_RF_MAX))
        {
            HI_ERR_TUNER("Input parameter(pSignal.u32frequency) invalid freq = %d\n", stTunerPara.u32Frequency);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if ((stTunerPara.unSRBW.u32BandWidth < TER_BW_MIN) || (stTunerPara.unSRBW.u32BandWidth > TER_BW_MAX))
        {
            HI_ERR_TUNER("Input parameter(pSignal.u32BandWidth = %d) invalid, \n", stTunerPara.unSRBW.u32BandWidth);
            return HI_ERR_TUNER_INVALID_PARA;
        }

        s_stCurrentSignal[u32tunerId] =  stTunerPara;
        stTunerSignal.u32Port = u32tunerId;
        stTunerSignal.stSignal = stTunerPara;
        memcpy(&s_strCurTunerConnectPara[u32tunerId], pstConnectPara, sizeof(HI_UNF_TUNER_CONNECT_PARA_S));

        s32Ret = ioctl(s_s32TunerFd, TUNER_CONNECT_CMD, (unsigned long)&stTunerSignal);
        if (HI_SUCCESS != s32Ret)
        {
            return s32Ret;
        }

        if (0 == u32TimeOut)
        {
            return HI_SUCCESS;
        }

        while (u32TimeSpan < u32TimeOut)
        {
            stTunerData.u32Port = u32tunerId;
            s32Ret = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);
            if (HI_SUCCESS != s32Ret)
            {
                return s32Ret;
            }

            if (HI_UNF_TUNER_SIGNAL_LOCKED == stTunerData.u32Data)
            {
                return HI_SUCCESS;
            }
            else
            {
                usleep(10 * 1000);
                u32TimeSpan += 10;
            }
        }

        return HI_SUCCESS;
    }
    else
    {
        HI_ERR_TUNER("Error signal type!\n");
    }
    /* Modified end: l00185424 2011-11-26 Support satellite */

    return HI_ERR_TUNER_FAILED_CONNECT;
}

HI_S32 HI_UNF_TUNER_GetStatus(HI_U32    u32tunerId , HI_UNF_TUNER_STATUS_S  *pstTunerStatus)
{
    HI_S32 s32Ret = 0;
    TUNER_DATA_S stTunerData;

    stTunerData.u32Data = 0;
    stTunerData.u32Port = u32tunerId;

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pstTunerStatus)
    {
        HI_ERR_TUNER("Input parameter(pstTunerStatus) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Ret = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (HI_U32)&stTunerData);

    if(HI_SUCCESS != s32Ret)
    {
        return s32Ret;
    }

    pstTunerStatus->enLockStatus = (HI_UNF_TUNER_LOCK_STATUS_E)stTunerData.u32Data;

    pstTunerStatus->stConnectPara.enSigType = s_strCurTunerConnectPara[u32tunerId].enSigType;
    switch (pstTunerStatus->stConnectPara.enSigType)
    {
    case HI_UNF_TUNER_SIG_TYPE_CAB:
	case HI_UNF_TUNER_SIG_TYPE_J83B:
    default:
        pstTunerStatus->stConnectPara.unConnectPara.stCab.bReverse =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stCab.bReverse;
        pstTunerStatus->stConnectPara.unConnectPara.stCab.enModType =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stCab.enModType;
        pstTunerStatus->stConnectPara.unConnectPara.stCab.u32Freq =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stCab.u32Freq;
        pstTunerStatus->stConnectPara.unConnectPara.stCab.u32SymbolRate =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stCab.u32SymbolRate;
        break;

    case HI_UNF_TUNER_SIG_TYPE_DVB_T:
    case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
	case (HI_UNF_TUNER_SIG_TYPE_DVB_T|HI_UNF_TUNER_SIG_TYPE_DVB_T2):
    case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
    case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
    case HI_UNF_TUNER_SIG_TYPE_DTMB:
		pstTunerStatus->stConnectPara.enSigType = s_strCurTunerConnectPara[u32tunerId].enSigType;
        pstTunerStatus->stConnectPara.unConnectPara.stTer.u32Freq =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stTer.u32Freq;
        pstTunerStatus->stConnectPara.unConnectPara.stTer.u32BandWidth =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stTer.u32BandWidth;
        break;

    case HI_UNF_TUNER_SIG_TYPE_SAT:
        pstTunerStatus->stConnectPara.unConnectPara.stSat.u32Freq =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stSat.u32Freq;
        pstTunerStatus->stConnectPara.unConnectPara.stSat.u32SymbolRate =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stSat.u32SymbolRate;
        pstTunerStatus->stConnectPara.unConnectPara.stSat.enPolar =
            s_strCurTunerConnectPara[u32tunerId].unConnectPara.stSat.enPolar;
        break;
    }
    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetBER(HI_U32   u32tunerId , HI_U32 *pu32BER)
{
    HI_S32 s32Result;
    HI_DOUBLE dBer = 0;
    HI_S32 i = 0;
    TUNER_DATABUF_S stTunerDataBuf;
    TUNER_DATA_S stTunerData;

    stTunerData.u32Port= u32tunerId;
    stTunerData.u32Data = 0;

    stTunerDataBuf.u32Port= u32tunerId;
    memset(stTunerDataBuf.u32DataBuf, 0, sizeof(stTunerDataBuf.u32DataBuf));

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pu32BER)
    {
        HI_ERR_TUNER("Input parameter(pu32BER) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    /*pu32BER points to the first address of three unsigned numbers which have BER*/
    /*CNcomment:pu32BER ָ���������ʵ������޷������׵�ַ*/
    s32Result= ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (unsigned long)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("GET_STATUS_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSTATUS;
    }

    if(HI_UNF_TUNER_SIGNAL_LOCKED != stTunerData.u32Data)
    {
        HI_ERR_TUNER("SIGNAL DROP\n");
        return HI_ERR_TUNER_NOT_CONNECT;
    }

    s32Result= ioctl(s_s32TunerFd, TUNER_GET_BER_CMD, (int)&stTunerDataBuf);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner HI_TUNER_GetBER error\n");
        return s32Result;
    }

    /* Modified begin: l00185424 2011-11-26 Support satellite */
    /* If the signal type is cable, convert the data here. */
    if ((HI_UNF_TUNER_SIG_TYPE_CAB == s_strCurTunerConnectPara[u32tunerId].enSigType)||(HI_UNF_TUNER_SIG_TYPE_J83B == s_strCurTunerConnectPara[u32tunerId].enSigType))
    {
        switch (s_strCurTunerAttr[u32tunerId].enDemodDevType)
        {

         case HI_UNF_DEMOD_DEV_TYPE_NONE:
            break;
         case HI_UNF_DEMOD_DEV_TYPE_3130I:
         case HI_UNF_DEMOD_DEV_TYPE_3130E:
         case HI_UNF_DEMOD_DEV_TYPE_J83B:
         {
            /* conver to value */
            dBer = ((HI_DOUBLE)(((stTunerDataBuf.u32DataBuf[0] & 0xFF) << 16) + ((stTunerDataBuf.u32DataBuf[1] & 0xFF) << 8)
                    + (stTunerDataBuf.u32DataBuf[2] & 0xFF)) / 8388608.0);

            i = 0;
            if (dBer != 0)
            {
                while (dBer < 1)
                {
                    dBer *= 10;
                    i++;
                }
            }

            /*get the integer and exponent part by Scientific notation, keep three effective digits*/
            /*CNcomment:��ѧ�������õ�����λ��ָ����������λ��Ч����*/
            pu32BER[0] = (HI_U32)dBer;
            pu32BER[1] = ((HI_U32)(dBer * 1000)) % 1000;
            pu32BER[2] = (HI_U32)i;
            break;
        }
         case HI_UNF_DEMOD_DEV_TYPE_MXL254:
		 case HI_UNF_DEMOD_DEV_TYPE_MXL214:  

        {

	    	pu32BER[0] = (HI_U32)(stTunerDataBuf.u32DataBuf[0]);
         	pu32BER[1] = (HI_U32)(stTunerDataBuf.u32DataBuf[1]);
         	pu32BER[2] = (HI_U32)(stTunerDataBuf.u32DataBuf[2]);

         break;
        }
		 case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
	    { 
	        pu32BER[0] = (HI_U32)stTunerDataBuf.u32DataBuf[0];
	        pu32BER[1] = (HI_U32)stTunerDataBuf.u32DataBuf[1];
	        pu32BER[2] = (HI_U32)stTunerDataBuf.u32DataBuf[2];
		
		 break;
	    }
        /*add HiFhone demod for DVB-C*/
        case HI_UNF_DEMOD_DEV_TYPE_HIFDVBC100:
        /* now jump into case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100*/
        case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100:
        {
            dBer = (HI_DOUBLE)((HI_DOUBLE)stTunerDataBuf.u32DataBuf[0]/16384.0) ;
	    
	        i = 0;
	        if (dBer != 0)
	        {
	            while (dBer < 1)
	            {
	                dBer *= 10;
	                i++;
	            }
	        }
	        
	        /*get the integer and exponent part by Scientific notation, keep three effective digits*/
	        /*CNcomment:��ѧ�������õ�����λ��ָ����������λ��Ч����*/
	        pu32BER[0] = (HI_U32)dBer;
	        pu32BER[1] = ((HI_U32)(dBer * 1000)) % 1000;
	        pu32BER[2] = (HI_U32)i;
		    break;
        }
	    default:
			
		break;
          	}
    }
    /* For satellite, convert it at lower driver. */
    else if (HI_UNF_TUNER_SIG_TYPE_SAT == s_strCurTunerConnectPara[u32tunerId].enSigType)
    {
        memcpy(pu32BER, stTunerDataBuf.u32DataBuf, sizeof(stTunerDataBuf.u32DataBuf));
        dBer = pu32BER[0]/pow(10.0, 9.0);
        if (dBer > 1 || dBer < 0)
        {
            HI_ERR_TUNER("Error BER !\n");
            return HI_FAILURE;
        }

        if (dBer == 0)
        {
            pu32BER[0] = 0;
            pu32BER[1] = 0;
            pu32BER[2] = 0;
        }
        else
        {
            i = 0;

            while (dBer < 1.0)
            {
                dBer *= 10;
                i++;
            }

            pu32BER[0] = (HI_U32)dBer;
            pu32BER[1] = (HI_U32)((dBer - pu32BER[0])*1000.0);
            pu32BER[2] = (HI_U32)i;
        }
    }
    else
    {
        switch (s_strCurTunerAttr[u32tunerId].enDemodDevType)
        {
            case HI_UNF_DEMOD_DEV_TYPE_MN88472:
			case HI_UNF_DEMOD_DEV_TYPE_3137:
                pu32BER[0] = (HI_U32)stTunerDataBuf.u32DataBuf[0];
    	        pu32BER[1] = (HI_U32)stTunerDataBuf.u32DataBuf[1];
    	        pu32BER[2] = (HI_U32)stTunerDataBuf.u32DataBuf[2];
                break;
            default:
                pu32BER[0] = (HI_U32)stTunerDataBuf.u32DataBuf[0];
    	        pu32BER[1] = (HI_U32)stTunerDataBuf.u32DataBuf[1];
    	        pu32BER[2] = (HI_U32)stTunerDataBuf.u32DataBuf[2];
                break;
        }

    }
    /* Modified end: l00185424 2011-11-26 Support satellite */
    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetSNR(HI_U32   u32tunerId , HI_U32 *pu32SNR)               /* range : 0-255  */
{
    HI_DOUBLE u32Snr = 0;
    HI_DOUBLE dTmp = 0.0;
    HI_DOUBLE dTmp_HiDVBC = 0.0;	
    HI_DOUBLE dSnrEva = 0;
    HI_S32 s32Result;
    TUNER_DATA_S stTunerData;

    stTunerData.u32Data = 0;
    stTunerData.u32Port = u32tunerId;

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pu32SNR)
    {
        HI_ERR_TUNER("Input parameter(pu32SNR) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Result= ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (unsigned long)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("GET_STATUS_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSTATUS;
    }

    if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerData.u32Data)
    {
        HI_ERR_TUNER("SIGNAL DROP\n");
        return HI_ERR_TUNER_NOT_CONNECT;
    }

    s32Result= ioctl(s_s32TunerFd, TUNER_GET_SNR_CMD, (int)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner GET_SNR_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSNR;
    }
    /* calculate the SNR regarding to the modulation */

    if (HI_UNF_TUNER_SIG_TYPE_DVB_T == s_strCurTunerConnectPara[u32tunerId].enSigType
        || HI_UNF_TUNER_SIG_TYPE_DVB_T2 == s_strCurTunerConnectPara[u32tunerId].enSigType)
    {
    	switch(s_strCurTunerAttr[u32tunerId].enDemodDevType)
    	{
			case HI_UNF_DEMOD_DEV_TYPE_MN88472:
				break;
			case HI_UNF_DEMOD_DEV_TYPE_3137:
				dTmp = ( HI_DOUBLE )stTunerData.u32Data;
        		*pu32SNR = (HI_U32)(10*log10(dTmp) - 11.7);
				break;
			default:
				*pu32SNR = 0;
				break;
		}
    }
    else
    {
        dTmp = ( HI_DOUBLE )stTunerData.u32Data;
        dTmp_HiDVBC = dTmp / ( pow(2.0, 11.0) );
        dTmp  =  dTmp / ( pow(2.0, 20.0) );
        switch (s_strCurTunerAttr[u32tunerId].enDemodDevType)
        {
            case HI_UNF_DEMOD_DEV_TYPE_NONE:
                break;

            case HI_UNF_DEMOD_DEV_TYPE_3130I:
            case HI_UNF_DEMOD_DEV_TYPE_3130E:
            case HI_UNF_DEMOD_DEV_TYPE_J83B:
            switch (s_stCurrentSignal[u32tunerId].enQamType)
            {
                case QAM_TYPE_16:
                    dSnrEva = 10.0 * log10((5.0 / 18.0) / dTmp);
                    u32Snr = dSnrEva;
                    break;

                case QAM_TYPE_32:
                    dSnrEva = 10.0 * log10(0.2 / dTmp);
                    u32Snr = dSnrEva;
                    break;

                case QAM_TYPE_64:
                    dSnrEva = 10.0 * log10(((42.0 / 14.0) / 14.0) / dTmp);
                    u32Snr = dSnrEva;
                    break;

                case QAM_TYPE_128:
                    dSnrEva = 10.0 * log10(((82.0 / 22.0) / 22.0) / dTmp);
                    u32Snr = dSnrEva;
                    break;

                case QAM_TYPE_256:
                    dSnrEva = 10.0 * log10(((170.0 / 32.0) / 32.0) / dTmp);
                    u32Snr = dSnrEva;
                    break;

                default:
                    return HI_FAILURE;
            }
                break;

            case HI_UNF_DEMOD_DEV_TYPE_3136:
            case HI_UNF_DEMOD_DEV_TYPE_3136I:
                if (stTunerData.u32Data)
                {
                    u32Snr = 10.0 * log10(8192.0 / (HI_DOUBLE)(stTunerData.u32Data));
                }
                else
                {
                    u32Snr = 50.0;
                }
                break;

            case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
                u32Snr = (HI_U32)(stTunerData.u32Data / 100.0);
                break;

            case HI_UNF_DEMOD_DEV_TYPE_MXL101:
                u32Snr = stTunerData.u32Data;
                break;

            case HI_UNF_DEMOD_DEV_TYPE_MN88472:
                u32Snr = stTunerData.u32Data;
                break;

            case HI_UNF_DEMOD_DEV_TYPE_IT9170:
                u32Snr = stTunerData.u32Data;
                break;

            case HI_UNF_DEMOD_DEV_TYPE_IT9133:
                u32Snr = stTunerData.u32Data;
                break;
            case HI_UNF_DEMOD_DEV_TYPE_MXL254:
            case HI_UNF_DEMOD_DEV_TYPE_MXL214:
                u32Snr = (HI_DOUBLE) (stTunerData.u32Data /10);
                break;
            case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
                u32Snr = (HI_DOUBLE) (stTunerData.u32Data);
                break; 

            case HI_UNF_DEMOD_DEV_TYPE_HIFDVBC100:
            /* now jump into case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100*/
            case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100:
        	 	switch (s_strCurTunerConnectPara[u32tunerId].enSigType)
         		{
         			case HI_UNF_TUNER_SIG_TYPE_CAB:
        				switch (s_stCurrentSignal[u32tunerId].enQamType)
        			        {
                                    case QAM_TYPE_16:           
                                        dSnrEva = 10.0 * log10(161 / dTmp_HiDVBC);
                                        u32Snr = dSnrEva;
                                        break;

                                    case QAM_TYPE_32:
                                        dSnrEva = 10.0 * log10(180 / dTmp_HiDVBC);
                                        u32Snr = dSnrEva;
                                        break;

                                    case QAM_TYPE_64:
                                        dSnrEva = 10.0 * log10(168 / dTmp_HiDVBC);
                                        u32Snr = dSnrEva;
                                        break;

                                    case QAM_TYPE_128:
                                        dSnrEva = 10.0 * log10(184 / dTmp_HiDVBC);
                                        u32Snr = dSnrEva;
                                        break;

                                    case QAM_TYPE_256:
                                        dSnrEva = 10.0 * log10(170 / dTmp_HiDVBC);
                                        u32Snr = dSnrEva;
                                        break;

                                    default:
                                        return HI_FAILURE;
                                }
        				break;
                        case HI_UNF_TUNER_SIG_TYPE_DTMB:    /*Ϊ�����Ժ���չ��������switch���*/
                        /* now jump into default*/
                        default:
                            HI_ERR_TUNER("s_strCurTunerConnectPara[u32TunerId].enSigType:%d\n",s_strCurTunerConnectPara[u32tunerId].enSigType);
                            return HI_FAILURE;
                }
                break;
            default:
                return HI_ERR_TUNER_INVALID_PARA;
            }
        *pu32SNR = (HI_U32)u32Snr;
    }
    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetSignalStrength(HI_U32   u32tunerId , HI_U32 *pu32SignalStrength)
{
    HI_S32 s32Result;
    TUNER_DATA_S stTunerData;
    TUNER_DATABUF_S stTunerDataBuf;
    HI_S32 s32Agc = 0;
    HI_U32 i = 0;
    HI_S32 s32levelcorrect = 0;
    TUNER_SIGNAL_LEVEL_SAT_S* pstSignalLevel = HI_NULL;

    stTunerData.u32Port = u32tunerId;
    stTunerData.u32Data = 0;
    stTunerDataBuf.u32Port= u32tunerId;
    memset(stTunerDataBuf.u32DataBuf,0,sizeof(stTunerDataBuf.u32DataBuf));

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32tunerId)
    {
        HI_ERR_TUNER("Input parameter(u32tunerId) invalid,invalid tunerId is: %d\n",u32tunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if(HI_NULL == pu32SignalStrength)
    {
        HI_ERR_TUNER("Input parameter(pu32SignalStrength) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Result= ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (unsigned long)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {

        HI_ERR_TUNER("GET_STATUS_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSTATUS;
    }

    if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerData.u32Data)
    {
        HI_ERR_TUNER("SIGNAL DROP\n");
        return HI_ERR_TUNER_NOT_CONNECT;
    }

    /* Modefied begin: l00185424 2011-11-26 Support satellite*/
    if ((HI_UNF_TUNER_SIG_TYPE_CAB == s_strCurTunerConnectPara[u32tunerId].enSigType)||(HI_UNF_TUNER_SIG_TYPE_J83B == s_strCurTunerConnectPara[u32tunerId].enSigType))
    {  
        stTunerData.u32Port = u32tunerId;
        stTunerData.u32Data = 0;
        s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGNALSTRENGTH_CMD, (HI_U32)&stTunerDataBuf);

        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("Tuner TUNER_GET_SIGNALSTRENGTH_CMD error\n");
            *pu32SignalStrength  = 0;
            return HI_ERR_TUNER_FAILED_GETSIGNALSTRENGTH;
        }

        s32Agc = (HI_S32)stTunerDataBuf.u32DataBuf[1];

        switch (s_strCurTunerAttr[u32tunerId].enTunerDevType)
        {
             case HI_UNF_TUNER_DEV_TYPE_CD1616:
            {
                if(s32Agc >= 2263)
                {
                    *pu32SignalStrength = 30;
                }
                else if(s32Agc >= 2019)
                {
                    *pu32SignalStrength = (HI_U32)((-1.0 / 61) * s32Agc + 67.10);
                }
                else if(s32Agc >= 1531)
                {
                    *pu32SignalStrength = (HI_U32)((-5.0 / 218) * s32Agc + 80.11);
                }
                else if(s32Agc >= 1122)
                {
                    *pu32SignalStrength = (HI_U32)((-12.0 / 409) * s32Agc + 89.92);
                }
                else if(s32Agc >= 1088)
                {
                    *pu32SignalStrength = (HI_U32)(-0.5 * s32Agc + 614);
                }
                else if(s32Agc >= 1032)
                {
                    *pu32SignalStrength = (HI_U32)((-5.0 / 7) * s32Agc + 847);
                }
                else
                {
                    *pu32SignalStrength = 110;
                }
                break;
            }

            case HI_UNF_TUNER_DEV_TYPE_ALPS_TDAE:
            {
                if (s32Agc >= 2134)
                {
                    *pu32SignalStrength  = 30;
                }
                else if(s32Agc >= 1763)
                {
                    *pu32SignalStrength = (HI_U32)((-9.0 / 371) * s32Agc + 81.77);
                }
                else if(s32Agc >= 1366)
                {
                    *pu32SignalStrength = (HI_U32)((-11.0 / 405) * s32Agc + 86.88);
                }
                else if(s32Agc >= 1285)
                {
                    *pu32SignalStrength = 70;
                }
                else
                {
                    *pu32SignalStrength = 100;
                }
                break;
            }

            case HI_UNF_TUNER_DEV_TYPE_TMX7070X:
            {
                if (s32Agc >= 2747)
                {
                    *pu32SignalStrength = 30;
                }
                else if (s32Agc >= 2255)
                {
                    *pu32SignalStrength = (HI_U32)((-9.0 / 160) * s32Agc + 184.5);
                }
                else
                {
                    *pu32SignalStrength = 75;
                }
                break;
            }

            case HI_UNF_TUNER_DEV_TYPE_TDA18250:
            {
                if(1 == stTunerDataBuf.u32DataBuf[2])
                {
                    s32Agc = 0- s32Agc;
                }
                 for(i = 0;i<(sizeof(s_SignalLevelTda18250)/sizeof(TUNER_SIGNAL_LEVEL_S));i++)
                 {
                    if(s_s32TunerFreq < (s_SignalLevelTda18250[i].s32SignalFreq *1000))
                    {
                        if(0 == i)
                        {
                            s32levelcorrect = s_SignalLevelTda18250[i].s32SignalLevel;
                            break;
                        }
                        s32levelcorrect = (s_SignalLevelTda18250[i].s32SignalLevel+ s_SignalLevelTda18250[i-1].s32SignalLevel)/2;
                        break;
                    }
                    else if(( s_SignalLevelTda18250[i].s32SignalFreq *1000) == s_s32TunerFreq)
                    {
                        s32levelcorrect = s_SignalLevelTda18250[i].s32SignalLevel;
                        break;
                    }
                    else
                    {

                        if(((sizeof(s_SignalLevelTda18250)/sizeof(TUNER_SIGNAL_LEVEL_S)) -1) == i )
                        {
                            s32levelcorrect = s_SignalLevelTda18250[i].s32SignalLevel;
                            break;
                        }

                    }
                 }

                 *pu32SignalStrength = (HI_U32)(s32Agc / 100.00 + 60 + s32levelcorrect);
                 break;
            }
            case HI_UNF_TUNER_DEV_TYPE_TDA18250B:
            {
                    //*pu32SignalStrength = (HI_U32)(s32Agc / 101.76 - 1.0);
                    *pu32SignalStrength = (HI_U32)(s32Agc / 101.76);
                    break;
        }

            case HI_UNF_TUNER_DEV_TYPE_MT2081:
            {
                *pu32SignalStrength = (HI_U32)((((109.0 - 30.0) * (s32Agc - 3102.0) / (10514.0 - 3102.0))) + 30);
                break;
            }

            /*TDCC-G131F*/
            case HI_UNF_TUNER_DEV_TYPE_TDCC:
            {
                if (s32Agc >= 1166)
                {
                    *pu32SignalStrength = (HI_U32)((-22.0 / 634) * s32Agc + 92.46);
                }
                else
                {
                    *pu32SignalStrength = 81;
                }
                break;
            }
			
			case HI_UNF_TUNER_DEV_TYPE_SI2147:
            {
                    *pu32SignalStrength = s32Agc;

                break;
            }
			
            case HI_UNF_TUNER_DEV_TYPE_R820C:
            {
                if(HI_UNF_DEMOD_DEV_TYPE_3130E == s_strCurTunerAttr[u32tunerId].enDemodDevType)
                {
                    if(45 == stTunerDataBuf.u32DataBuf[2])
                    {
                        *pu32SignalStrength = (HI_U32)(60.0 - ((s32Agc * 26.0) / 613.0));
                    }
                    else
                    {
                        if(stTunerDataBuf.u32DataBuf[2] > 27)
                        {
                            *pu32SignalStrength = (HI_U32)((109 - ((50.0 / 39.0) * stTunerDataBuf.u32DataBuf[2])) + (50.0 / 39.0));
                        }
                        else
                        {
                            *pu32SignalStrength = (HI_U32)((107 - ((27.0 / 21.0) * stTunerDataBuf.u32DataBuf[2] ))+ (9.0 / 21.0));
                        }
                    }
                }
                else
                {
                    if(HI_UNF_DEMOD_DEV_TYPE_J83B == s_strCurTunerAttr[u32tunerId].enDemodDevType)
                    {
                        if(45 == stTunerDataBuf.u32DataBuf[2])
                        {
                            *pu32SignalStrength = (HI_U32)((s32Agc * (-21.0 / 1011.0 )) + 37.0 + (21.0 / 1011.0) * 2616.0);
                        }
                        else
                        {
                            if(stTunerDataBuf.u32DataBuf[2] > 27)
                            {
                                *pu32SignalStrength = (HI_U32)((109.0 - ((50.00 / 39.00) * stTunerDataBuf.u32DataBuf[2])) + (50.00 / 39.00));
                            }
                            else
                            {
                                *pu32SignalStrength = (HI_U32)((107.0 - ((27.00 / 21.00) * stTunerDataBuf.u32DataBuf[2])) + (9.00 / 21.00));
                            }
                        }
                    }
                    else
                    {
                        if(45 == stTunerDataBuf.u32DataBuf[2])
                        {
                            *pu32SignalStrength = (HI_U32)((s32Agc - 4116.5) / (-50.85) + 2.0);
                        }
                        else
                        {
                            if(stTunerDataBuf.u32DataBuf[2] > 27)
                            {
                                *pu32SignalStrength = (HI_U32)((109.0 - ((50.00 / 39.00) * stTunerDataBuf.u32DataBuf[2])) + (50.00 / 39.00));
                            }
                            else
                            {
                                *pu32SignalStrength = (HI_U32)((107.0 - ((27.00 / 21.00) * stTunerDataBuf.u32DataBuf[2])) + (9.00 / 21.00));
                            }
                        }
                    }
                }
                break;
            }

            case HI_UNF_TUNER_DEV_TYPE_MXL203:
            {
                *pu32SignalStrength = (HI_U32)(110.0 - (((s32Agc - 691.0) * 80.0) / (2503.0 - 691.0)));
                break;
            }
          case HI_UNF_TUNER_DEV_TYPE_MXL603:
            {
              if(1 == stTunerDataBuf.u32DataBuf[2])
                    {
                         s32Agc = 0- s32Agc;
                }

                *pu32SignalStrength = (HI_U32)((s32Agc/100.0) + 107);
                 break;
            }
		  
		  case HI_UNF_TUNER_DEV_TYPE_MXL608:
		  {  
			  *pu32SignalStrength = (HI_U32)(s32Agc );
			  break;
		  }

          case HI_UNF_TUNER_DEV_TYPE_MXL254:
		  case HI_UNF_TUNER_DEV_TYPE_MXL214:	
	        {
	            *pu32SignalStrength = (HI_U32)(s32Agc);			
	             break;
	        }
		         	
          case HI_UNF_TUNER_DEV_TYPE_TDA18280:  
		    { 
				 *pu32SignalStrength = (HI_U32)(s32Agc);
				 break;
		  	}
            default:
            {
                return HI_FAILURE; 
            }                
        }
	}
    else if (HI_UNF_TUNER_SIG_TYPE_SAT == s_strCurTunerConnectPara[u32tunerId].enSigType)
    {
        stTunerData.u32Port = u32tunerId;
        stTunerData.u32Data = 0;
        s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGNALSTRENGTH_CMD, (HI_U32)&stTunerDataBuf);

        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("Tuner TUNER_GET_SIGNALSTRENGTH_CMD error\n");
            *pu32SignalStrength = 0;
            return HI_ERR_TUNER_FAILED_GETSIGNALSTRENGTH;
        }

        if(HI_UNF_DEMOD_DEV_TYPE_AVL6211 == s_strCurTunerAttr[u32tunerId].enDemodDevType)
        {
            switch (s_strCurTunerAttr[u32tunerId].enTunerDevType)
            {
            case HI_UNF_TUNER_DEV_TYPE_AV2011:
            case HI_UNF_TUNER_DEV_TYPE_AV2018:
                pstSignalLevel = s_astSignalLevelAV2011;
                break;

            case HI_UNF_TUNER_DEV_TYPE_SHARP7903:
                pstSignalLevel = s_astSignalLevelSHARP7903;
                break;

            default:
                {
                    return HI_FAILURE;
                }
            }

            //if (HI_NULL != pstSignalLevel)
            {
                for (i = 0; i < 100; i++)
                {
                    if (stTunerDataBuf.u32DataBuf[1] <= pstSignalLevel[i].u16SignalLevel)
                    {
                        if ((0 == i) && (stTunerDataBuf.u32DataBuf[1] < pstSignalLevel[i].u16SignalLevel))
                        {
                            HI_ERR_TUNER("RFSignalLevel is too weak !");
                            *pu32SignalStrength = 18;
                        }
                        else
                        {
                            *pu32SignalStrength = (HI_U16)(pstSignalLevel[i].s16SignalDBUV);
                        }

                        break;
                    }
                }
            }
            /*else
            {
                *pu32SignalStrength = 18;
            }*/
        }
        else if (HI_UNF_DEMOD_DEV_TYPE_3136 == s_strCurTunerAttr[u32tunerId].enDemodDevType ||
                    HI_UNF_DEMOD_DEV_TYPE_3136I == s_strCurTunerAttr[u32tunerId].enDemodDevType)
        {
            s32Agc = (HI_S32)stTunerDataBuf.u32DataBuf[1];
            switch (s_strCurTunerAttr[u32tunerId].enTunerDevType)
            {
            case HI_UNF_TUNER_DEV_TYPE_AV2011:
            case HI_UNF_TUNER_DEV_TYPE_AV2018:
            default:
                {
                    if(s32Agc < 1000)  //>-10dbm
                    {
                        *pu32SignalStrength = 97;
                    }
                    else if(s32Agc < 1600)  //-40dbm ~ -10dbm
                    {
                        *pu32SignalStrength = (HI_U32)(67 - 0.05 * (s32Agc - 1600));
                    }
                    else if(s32Agc < 2200)
                    {
                        *pu32SignalStrength = (HI_U32)(47 - 0.033 * (s32Agc - 2200));
                    }
                    else if(s32Agc < 3000)
                    {
                        *pu32SignalStrength = (HI_U32)(27 - 0.025 * (s32Agc - 3000));
                    }
                    else
                    {
                        *pu32SignalStrength = (HI_U32)(17 - 0.01 * (s32Agc - 4095));    //<-80dbm
                    }
                    break;
                }

            case HI_UNF_TUNER_DEV_TYPE_SHARP7903:
                {
                    if(s32Agc < 600)
                    {
                        *pu32SignalStrength = 107;      //<-80dbm
                    }
                    else if (s32Agc < 1150) //-18dbm ~ 0dbm
                    {
                        *pu32SignalStrength = (HI_U32)(89 - (18.0/500)*(s32Agc - 1150));
                    }
                    else if (s32Agc < 1300) //-30dbm ~ -18dbm
                    {
                        *pu32SignalStrength = (HI_U32)(77 - (12.0/150)*(s32Agc - 1300));
                    }
                    else if (s32Agc < 1700) //-40dbm ~ -30dbm
                    {
                        *pu32SignalStrength = (HI_U32)(47 - (10.0/400)*(s32Agc - 1700));
                    }
                    else if (s32Agc < 2340) //-60dbm ~ -40dbm
                    {
                        *pu32SignalStrength = (HI_U32)(47 - (20.0/640)*(s32Agc - 2340));
                    }
                    else if (s32Agc < 2480) //-63dbm ~ -60dbm
                    {
                        *pu32SignalStrength = (HI_U32)(44-(3.0/140)*(s32Agc - 2480));
                    }
                    else if (s32Agc < 2650) //-66dbm ~ -63dbm
                    {
                        *pu32SignalStrength = (HI_U32)(41-(3.0/170)*(s32Agc - 2650));
                    }
                    else if (s32Agc < 3500) //-85dbm ~ -66dbm
                    {
                        *pu32SignalStrength = (HI_U32)(22-(19.0/850)*(s32Agc - 3500));
                    }
                    else        //<-85dbm
                    {
                        *pu32SignalStrength = 22;
                    }
                    break;
                }

            case HI_UNF_TUNER_DEV_TYPE_RDA5815:
                {
                    if(s32Agc < 350)  //>-10dbm
                    {
                        *pu32SignalStrength = 97;   //(dbuv)
                    }
                    else if(s32Agc < 800)       //-25dbm ~ -10dbm
                    {
                        *pu32SignalStrength = (HI_U32)(82 - 0.033 * (s32Agc - 800));
                    }
                    else if(s32Agc < 1725)     //-50dbm ~ -25dbm
                    {
                        *pu32SignalStrength = (HI_U32)(57 - 0.027 * (s32Agc - 1725));
                    }
                    else if(s32Agc < 2207)  //-60dbm ~ -50dbm
                    {
                        *pu32SignalStrength = (HI_U32)(47 - 0.021 * (s32Agc - 2207));
                    }
                    else if(s32Agc < 2507)  //-63dbm ~ -60dbm
                    {
                        *pu32SignalStrength = (HI_U32)(44 - 0.01 * (s32Agc - 2507));
                    }
                    else if(s32Agc < 2661)  //-66dbm ~ -63dbm
                    {
                        *pu32SignalStrength = (HI_U32)(41 - 0.0195 * (s32Agc - 2661));
                    }
                    else if(s32Agc < 2884)  //-69dbm ~ -66dbm
                    {
                        *pu32SignalStrength = (HI_U32)(38 - 0.0135 * (s32Agc - 2884));
                    }
                    else if(s32Agc < 3178)  //-72dbm ~ -69dbm
                    {
                        *pu32SignalStrength = (HI_U32)(35 - 0.0102 * (s32Agc - 3178));
                    }
                    else if(s32Agc < 3910)  //-81dbm ~ -72dbm
                    {
                        *pu32SignalStrength = (HI_U32)(26 - 0.0123 * (s32Agc - 3910));
                    }
                    else if(s32Agc < 4085)  //-84dbm ~ -81dbm
                    {
                        *pu32SignalStrength = (HI_U32)(23 - 0.0171 * (s32Agc - 4085));
                    }
                    else
                    {
                        *pu32SignalStrength = 22;   //<-85dbm
                    }
                    break;
                }

            case HI_UNF_TUNER_DEV_TYPE_M88TS2022:
                {
                    HI_U32 u32BBGainBase = 0, u32BBGain = 0, u32RFGain = 0;

                    if(s32Agc < 3920)
                    {
                        u32BBGainBase = 0;
                    }
                    else if(s32Agc < 3952)
                    {
                        u32BBGainBase = (HI_U32)((2.0 / 32) * (s32Agc - 3920));
                    }
                    else if(s32Agc < 4000)
                    {
                        u32BBGainBase = (HI_U32)(2 + (4.5 / 48) * (s32Agc - 3952));
                    }
                    else if(s32Agc < 4016)
                    {
                        u32BBGainBase = (HI_U32)(6.5 + (0.5 / 16) * (s32Agc - 4000));
                    }
                    else if(s32Agc < 4032)
                    {
                        u32BBGainBase = (HI_U32)(7 + (4.0 / 16) * (s32Agc - 4016));
                    }
                    else if (s32Agc < 4040)
                    {
                        u32BBGainBase = (HI_U32)(11 + (1.0 / 8) * (s32Agc - 4032));
                    }
                    else if (s32Agc < 4080)
                    {
                        u32BBGainBase = (HI_U32)(12 + (0.3 / 8) * (s32Agc - 4040));
                    }
                    else
                    {
                        u32BBGainBase = 13;
                    }

                    u32BBGain = (HI_U32)((pu32SignalStrength[0] & 0x1f) * 36.0 / 10);
                    u32RFGain = (HI_U32)(2 + (pu32SignalStrength[2] & 0x1f) * 24.0 / 10);
                    *pu32SignalStrength =(HI_U32)(107 - (u32BBGainBase + u32BBGain + u32RFGain));
                    break;
                }
            }
        }
    }
    else
    {
        s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGNALSTRENGTH_CMD, (HI_U32)&stTunerDataBuf);

        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("Tuner TUNER_GET_SIGNALSTRENGTH_CMD error\n");
            *pu32SignalStrength = 0;
            return HI_ERR_TUNER_FAILED_GETSIGNALSTRENGTH;
        }
        *pu32SignalStrength = stTunerDataBuf.u32DataBuf[1];
    }
    /* Modefied end: l00185424 2011-11-26 Support satellite*/

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetSignalQuality(HI_U32 u32TunerId, HI_U32 *pu32SignalQuality)
{
    HI_S32 s32Result,s32Delta;
    TUNER_DATA_S stTunerData;
    TUNER_SIGNALINFO_S stTunerSignalInfo;
    TUNER_DATABUF_S stTunerDataBuf;
    HI_U32 u32SNR = 0;
    HI_U32 i=0;
    HI_DOUBLE dTmp = 0;
    HI_DOUBLE dSnrEva = 0;
    HI_DOUBLE dCNnordig = 0;
    HI_DOUBLE dSnrSQI = 0;
    HI_DOUBLE dBerSQI = 0;
    HI_DOUBLE dBer = 0;
    
    HI_DOUBLE dSQI = 0;
    HI_DOUBLE dTmp_HiDVBC = 0.0;	

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;

    stTunerSignalInfo.u32Port = u32TunerId;
	
    stTunerDataBuf.u32Port= u32TunerId;
    memset(stTunerDataBuf.u32DataBuf, 0, sizeof(stTunerDataBuf.u32DataBuf));
	
    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pu32SignalQuality)
    {
        HI_ERR_TUNER("Input parameter(pu32SignalQuality) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Result = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (unsigned long)&stTunerData);
    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("GET_STATUS_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSTATUS;
    }

    if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerData.u32Data)
    {
        HI_ERR_TUNER("SIGNAL DROP\n");
        *pu32SignalQuality = 0;
        return HI_ERR_TUNER_NOT_CONNECT;
    }

    s32Result = ioctl(s_s32TunerFd, TUNER_GET_SNR_CMD, (int)&stTunerData);
    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner get SNR error\n");
        return HI_ERR_TUNER_FAILED_GETSIGNALQUALITY;
    }

    switch (s_strCurTunerAttr[u32TunerId].enDemodDevType)
    {
        case HI_UNF_DEMOD_DEV_TYPE_3136:
        case HI_UNF_DEMOD_DEV_TYPE_3136I:
            u32SNR = (HI_U32)(1000*(3.913 - log10((HI_DOUBLE)stTunerData.u32Data)));
            break;
        case HI_UNF_DEMOD_DEV_TYPE_3137:
            dTmp = (HI_DOUBLE)(10*log10((HI_DOUBLE)stTunerData.u32Data) - 11.7);
            break;
		case HI_UNF_DEMOD_DEV_TYPE_3130I:
        case HI_UNF_DEMOD_DEV_TYPE_3130E:
        case HI_UNF_DEMOD_DEV_TYPE_J83B:
			
			dTmp = ( HI_DOUBLE )stTunerData.u32Data;
	        dTmp  =  dTmp / ( pow(2.0, 20.0) );
	        switch (s_stCurrentSignal[u32TunerId].enQamType)
	        {
	            case QAM_TYPE_16:
	                dSnrEva = 10.0 * log10((5.0 / 18.0) / dTmp);
	              //  u32Snr = dSnrEva;
	                break;

	            case QAM_TYPE_32:
	                dSnrEva = 10.0 * log10(0.2 / dTmp);
	               // u32Snr = dSnrEva;
	                break;

	            case QAM_TYPE_64:
	                dSnrEva = 10.0 * log10(((42.0 / 14.0) / 14.0) / dTmp);
	               // u32Snr = dSnrEva;
	                break;

	            case QAM_TYPE_128:
	                dSnrEva = 10.0 * log10(((82.0 / 22.0) / 22.0) / dTmp);
	                //u32Snr = dSnrEva;
	                break;

	            case QAM_TYPE_256:
	                dSnrEva = 10.0 * log10(((170.0 / 32.0) / 32.0) / dTmp);
	                //u32Snr = dSnrEva;
	                break;
             
	            default:
	                return HI_FAILURE;
	        }
            break;
		 case HI_UNF_DEMOD_DEV_TYPE_MXL254:
	     case HI_UNF_DEMOD_DEV_TYPE_MXL214:
		 	
            dSnrEva = (HI_DOUBLE) (stTunerData.u32Data /10);
			
            break;
	    case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
			
            dSnrEva = (HI_DOUBLE) (stTunerData.u32Data);
            break; 

        case HI_UNF_DEMOD_DEV_TYPE_HIFDVBC100:
        /* now jump into case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100*/
        case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100:
            dTmp = ( HI_DOUBLE )stTunerData.u32Data;
            dTmp_HiDVBC = dTmp / ( pow(2.0, 11.0) );
            dTmp  =  dTmp / ( pow(2.0, 20.0) );
            switch (s_strCurTunerConnectPara[u32TunerId].enSigType)
            {
                case HI_UNF_TUNER_SIG_TYPE_CAB:
                    switch (s_stCurrentSignal[u32TunerId].enQamType)
                    {
                        case QAM_TYPE_16:           
                            dSnrEva = 10.0 * log10(161 / dTmp_HiDVBC);
                            break;
                     
                        case QAM_TYPE_32:
                            dSnrEva = 10.0 * log10(180 / dTmp_HiDVBC);
                            break;
                     
                        case QAM_TYPE_64:
                            dSnrEva = 10.0 * log10(168 / dTmp_HiDVBC);
                            break;
                     
                        case QAM_TYPE_128:
                            dSnrEva = 10.0 * log10(184 / dTmp_HiDVBC);
                            break;

                        case QAM_TYPE_256:
                            dSnrEva = 10.0 * log10(170 / dTmp_HiDVBC);
                            break;

                        default:
                            HI_ERR_TUNER("s_stCurrentSignal[u32TunerId].unMODPOL.enQamType:%d\n",s_stCurrentSignal[u32TunerId].enQamType);
                            return HI_FAILURE;
                    }
                    break;
                case HI_UNF_TUNER_SIG_TYPE_DTMB:    /*Ϊ�����Ժ���չ��������switch���*/
                /* now jump into default*/
                default:
                    HI_ERR_TUNER("s_strCurTunerConnectPara[u32TunerId].enSigType:%d\n",s_strCurTunerConnectPara[u32TunerId].enSigType);
                    return HI_FAILURE;
            }
            break;
        default:
            u32SNR = stTunerData.u32Data;
    }

    /* For SAT */
    if (HI_UNF_TUNER_SIG_TYPE_SAT == s_strCurTunerConnectPara[u32TunerId].enSigType)
    {
        HI_U8 u8SNRrefer = 0;
        typedef struct
        {
            HI_UNF_TUNER_FE_FECRATE_E enFECRate;
            HI_U8                     u8ReferSNR;
        } TUNER_REFER_SNR_S;

        TUNER_REFER_SNR_S astDVBS2QpskRefSNR[8] =
        {
            {HI_UNF_TUNER_FE_FEC_1_2, 10}, {HI_UNF_TUNER_FE_FEC_3_5,  24}, {HI_UNF_TUNER_FE_FEC_2_3, 32},
            {HI_UNF_TUNER_FE_FEC_3_4, 41}, {HI_UNF_TUNER_FE_FEC_4_5,  47}, {HI_UNF_TUNER_FE_FEC_5_6, 52},
            {HI_UNF_TUNER_FE_FEC_8_9, 63}, {HI_UNF_TUNER_FE_FEC_9_10, 65}
        };

        TUNER_REFER_SNR_S astDVBSRefSNR[6];
        TUNER_REFER_SNR_S astDVBS28pskRefSNR[6];

        TUNER_REFER_SNR_S astDVBSRefSNR_Avl6211[6] =
        {
            {HI_UNF_TUNER_FE_FEC_1_2, 12}, {HI_UNF_TUNER_FE_FEC_2_3, 32}, {HI_UNF_TUNER_FE_FEC_3_4, 41},
            {HI_UNF_TUNER_FE_FEC_5_6, 52}, {HI_UNF_TUNER_FE_FEC_6_7, 58}, {HI_UNF_TUNER_FE_FEC_7_8, 62}
        };
        TUNER_REFER_SNR_S astDVBS28pskRefSNR_Avl6211[6] =
        {
            {HI_UNF_TUNER_FE_FEC_3_5, 57}, {HI_UNF_TUNER_FE_FEC_2_3, 67}, {HI_UNF_TUNER_FE_FEC_3_4, 80},
            {HI_UNF_TUNER_FE_FEC_4_5, 95}, {HI_UNF_TUNER_FE_FEC_5_6, 10}, {HI_UNF_TUNER_FE_FEC_8_9, 11}
        };

        TUNER_REFER_SNR_S astDVBSRefSNR_Hi3136[6] =
        {
            {HI_UNF_TUNER_FE_FEC_1_2, 23}, {HI_UNF_TUNER_FE_FEC_2_3, 42}, {HI_UNF_TUNER_FE_FEC_3_4, 52},
            {HI_UNF_TUNER_FE_FEC_5_6, 63}, {HI_UNF_TUNER_FE_FEC_6_7, 70}, {HI_UNF_TUNER_FE_FEC_7_8, 70}
        };
        TUNER_REFER_SNR_S astDVBS28pskRefSNR_Hi3136[6] =
        {
            {HI_UNF_TUNER_FE_FEC_3_5, 57}, {HI_UNF_TUNER_FE_FEC_2_3, 67}, {HI_UNF_TUNER_FE_FEC_3_4, 80},
            {HI_UNF_TUNER_FE_FEC_4_5, 95}, {HI_UNF_TUNER_FE_FEC_5_6, 108}, {HI_UNF_TUNER_FE_FEC_8_9, 111}
        };

        switch (s_strCurTunerAttr[u32TunerId].enDemodDevType)
        {
            case HI_UNF_DEMOD_DEV_TYPE_3136:
            case HI_UNF_DEMOD_DEV_TYPE_3136I:
                memcpy(astDVBSRefSNR, astDVBSRefSNR_Hi3136, sizeof(astDVBSRefSNR_Hi3136));
                memcpy(astDVBS28pskRefSNR, astDVBS28pskRefSNR_Hi3136, sizeof(astDVBS28pskRefSNR_Hi3136));
                break;

            case HI_UNF_DEMOD_DEV_TYPE_AVL6211:
            default:
                memcpy(astDVBSRefSNR, astDVBSRefSNR_Avl6211, sizeof(astDVBSRefSNR_Avl6211));
                memcpy(astDVBS28pskRefSNR, astDVBS28pskRefSNR_Avl6211, sizeof(astDVBS28pskRefSNR_Avl6211));
        }


        s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGANLINFO_CMD, (int)&stTunerSignalInfo);
        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("Tuner get signal info error\n");
            return HI_ERR_TUNER_FAILED_GETSIGNALQUALITY;
        }

        /* For DVBS */
        if (HI_UNF_TUNER_FE_DVBS == stTunerSignalInfo.stInfo.unSignalInfo.stSat.enSATType)
        {
            GET_REFER_SNR(u8SNRrefer, astDVBSRefSNR, stTunerSignalInfo.stInfo.unSignalInfo.stSat.enFECRate);
        }
        /* For DVBS2 */
        else
        {
            if (HI_UNF_MOD_TYPE_8PSK == stTunerSignalInfo.stInfo.unSignalInfo.stSat.enModType)
            {
                GET_REFER_SNR(u8SNRrefer, astDVBS28pskRefSNR, stTunerSignalInfo.stInfo.unSignalInfo.stSat.enFECRate);
            }
            else if (HI_UNF_MOD_TYPE_QPSK == stTunerSignalInfo.stInfo.unSignalInfo.stSat.enModType)
            {
                GET_REFER_SNR(u8SNRrefer, astDVBS2QpskRefSNR, stTunerSignalInfo.stInfo.unSignalInfo.stSat.enFECRate);
            }
        }

        if ((u32SNR / 10) > u8SNRrefer)
        {
            u32SNR = u32SNR / 10 - u8SNRrefer;
            if (u32SNR >= 100)
            {
                *pu32SignalQuality = 99;
            }
            else if (u32SNR >= 50)  /* >5.0dB */
            {
                *pu32SignalQuality = 80 + (u32SNR - 50) * 20 / 50;
            }
            else if (u32SNR >= 25)  /* > 2.5dB */
            {
                *pu32SignalQuality = 50 + (u32SNR - 25) * 30 / 25;
            }
            else if (u32SNR >= 10)  /* > 1dB */
            {
                *pu32SignalQuality = 25 + (u32SNR - 10) * 25 / 15;
            }
            else
            {
                *pu32SignalQuality = 5 + (u32SNR) * 20 / 10;
            }
        }
        else
        {
            *pu32SignalQuality = 5;
        }
    }
    /* For other, unsupport now */
    else if (HI_UNF_TUNER_SIG_TYPE_DVB_T <= s_strCurTunerConnectPara[u32TunerId].enSigType && HI_UNF_TUNER_SIG_TYPE_DTMB >= s_strCurTunerConnectPara[u32TunerId].enSigType)
    {
         typedef struct
        {
            HI_UNF_MODULATION_TYPE_E  enModulation;
            HI_UNF_TUNER_FE_FECRATE_E enFECRate;
            HI_FLOAT   f16NordigP1;
        } TUNER_NORDIG_P1_S;

        TUNER_NORDIG_P1_S  stCNNordigP1[4][6] =
        {
            {{HI_UNF_MOD_TYPE_QPSK,HI_UNF_TUNER_FE_FEC_1_2,3.5},{HI_UNF_MOD_TYPE_QPSK,HI_UNF_TUNER_FE_FEC_3_5,4.7},{HI_UNF_MOD_TYPE_QPSK,HI_UNF_TUNER_FE_FEC_2_3,5.6},{HI_UNF_MOD_TYPE_QPSK,HI_UNF_TUNER_FE_FEC_3_4,6.6},{HI_UNF_MOD_TYPE_QPSK,HI_UNF_TUNER_FE_FEC_4_5,7.2},{HI_UNF_MOD_TYPE_QPSK,HI_UNF_TUNER_FE_FEC_5_6,7.7}},
            {{HI_UNF_MOD_TYPE_QAM_16,HI_UNF_TUNER_FE_FEC_1_2,8.7},{HI_UNF_MOD_TYPE_QAM_16,HI_UNF_TUNER_FE_FEC_3_5,10.1},{HI_UNF_MOD_TYPE_QAM_16,HI_UNF_TUNER_FE_FEC_2_3,11.4},{HI_UNF_MOD_TYPE_QAM_16,HI_UNF_TUNER_FE_FEC_3_4,12.5},{HI_UNF_MOD_TYPE_QAM_16,HI_UNF_TUNER_FE_FEC_4_5,13.3},{HI_UNF_MOD_TYPE_QAM_16,HI_UNF_TUNER_FE_FEC_5_6,13.8}},
            {{HI_UNF_MOD_TYPE_QAM_64,HI_UNF_TUNER_FE_FEC_1_2,13.0},{HI_UNF_MOD_TYPE_QAM_64,HI_UNF_TUNER_FE_FEC_3_5,14.8},{HI_UNF_MOD_TYPE_QAM_64,HI_UNF_TUNER_FE_FEC_2_3,16.2},{HI_UNF_MOD_TYPE_QAM_64,HI_UNF_TUNER_FE_FEC_3_4,17.7},{HI_UNF_MOD_TYPE_QAM_64,HI_UNF_TUNER_FE_FEC_4_5,18.7},{HI_UNF_MOD_TYPE_QAM_64,HI_UNF_TUNER_FE_FEC_5_6,19.4}},
            {{HI_UNF_MOD_TYPE_QAM_256,HI_UNF_TUNER_FE_FEC_1_2,17.0},{HI_UNF_MOD_TYPE_QAM_256,HI_UNF_TUNER_FE_FEC_3_5,19.4},{HI_UNF_MOD_TYPE_QAM_256,HI_UNF_TUNER_FE_FEC_2_3,20.8},{HI_UNF_MOD_TYPE_QAM_256,HI_UNF_TUNER_FE_FEC_3_4,22.9},{HI_UNF_MOD_TYPE_QAM_256,HI_UNF_TUNER_FE_FEC_4_5,24.3},{HI_UNF_MOD_TYPE_QAM_256,HI_UNF_TUNER_FE_FEC_5_6,25.1}},
        };

        HI_U8 i,j;
        double dCNReceive = 0,dNordigReference = 0,dCNRelative = 0,dSNRReceive = 0;

        switch (s_strCurTunerAttr[u32TunerId].enDemodDevType)
        {
        case HI_UNF_DEMOD_DEV_TYPE_MXL101:
            dSNRReceive = ((HI_DOUBLE)stTunerData.u32Data)/10000;

            s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGANLINFO_CMD, (int)&stTunerSignalInfo);
            if (HI_SUCCESS == s32Result)
            {
                for(i=0;i<4;i++)
                {
                    if(stCNNordigP1[i][0].enModulation == stTunerSignalInfo.stInfo.unSignalInfo.stTer.enModType)
                    {
                        for(j=0;j<6;j++)
                        {
                            if(stCNNordigP1[i][j].enFECRate == stTunerSignalInfo.stInfo.unSignalInfo.stTer.enFECRate)
                            {
                                dNordigReference = stCNNordigP1[i][j].f16NordigP1;
                            }
                        }
                    }
                }
            }
            else
            {
                HI_ERR_TUNER("tuner get signalinfo fail.\n");
                return HI_ERR_TUNER_FAILED_GETSIGNALQUALITY;
            }

            dCNReceive = dSNRReceive - 1;
            dCNRelative = dCNReceive - dNordigReference;
            if(dCNRelative >= 0)
            {
                if(dCNRelative >= 10)
                {
                    *pu32SignalQuality = 99;
                }
                else if(dCNRelative >= 6)
                {
                    *pu32SignalQuality = 75 + (dCNRelative - 6) * 24 / 4.0;
                }
                else if (dCNRelative >= 3.5)  /* > 3.5dB */
                {
                    *pu32SignalQuality = 45 + (dCNRelative - 3.5) * 30 / 2.5;
                }
                else if (dCNRelative >= 2)  /* > 2dB */
                {
                    *pu32SignalQuality = 30 + (dCNRelative - 2) * 15 / 1.5;
                }
                else if(dCNRelative >= 1)  /* > 1dB */
                {
                    *pu32SignalQuality = 15 + (dCNRelative-1) * 15 / 1.0;
                }
                else
                {
                    *pu32SignalQuality = 5 + (dCNRelative ) *10 ;
                }
            }
            else
            {
                *pu32SignalQuality = 5;
            }
            break;
        case HI_UNF_DEMOD_DEV_TYPE_3137:
            s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGANLINFO_CMD, (int)&stTunerSignalInfo);
            if (HI_SUCCESS != s32Result)
            {
                HI_ERR_TUNER("Tuner HI_UNF_TUNER_GetSignalInfo error\n");
                return HI_ERR_TUNER_FAILED_GETSIGNALINFO;
            }

            if(HI_UNF_MOD_TYPE_QPSK == stTunerSignalInfo.stInfo.unSignalInfo.stTer.enModType)
            {
                s32Delta = 25;
            }
            else if(HI_UNF_MOD_TYPE_QAM_16 == stTunerSignalInfo.stInfo.unSignalInfo.stTer.enModType)
            {
                s32Delta = 15;
            }
            else if(HI_UNF_MOD_TYPE_QAM_64 == stTunerSignalInfo.stInfo.unSignalInfo.stTer.enModType)
            {
                s32Delta = 10;
            }
            else
            {
                s32Delta = -5;
            }

            dTmp = 3 * dTmp + s32Delta;

            if(dTmp > 95)
                dTmp = 95;
            else if(dTmp < 10)
                dTmp = 10;
            else
                dTmp = dTmp;

            *pu32SignalQuality = (HI_U32)dTmp;
            break;
        default:
            *pu32SignalQuality = 0;
            return HI_ERR_TUNER_FAILED_GETSIGNALQUALITY;
        }
    }
	else if((HI_UNF_TUNER_SIG_TYPE_CAB == s_strCurTunerConnectPara[u32TunerId].enSigType )|| (HI_UNF_TUNER_SIG_TYPE_J83B == s_strCurTunerConnectPara[u32TunerId].enSigType))
	{
	    //snr
		switch (s_strCurTunerConnectPara[u32TunerId].enSigType)
	    {
	        case HI_UNF_TUNER_SIG_TYPE_CAB:
				if(s_strCurTunerAttr[u32TunerId].enDemodDevType == HI_UNF_DEMOD_DEV_TYPE_J83B )
				{
				    switch (s_stCurrentSignal[u32TunerId].enQamType)
			        {
						case QAM_TYPE_64:
							dCNnordig = 24;
							break;
						case QAM_TYPE_256:
							dCNnordig = 30;
							break;
						default:
							dCNnordig = 24;
							break;
				    }
				}
				else
				{
					switch (s_stCurrentSignal[u32TunerId].enQamType)
			        {
			            case QAM_TYPE_16:
						    dCNnordig = 17.5;
							break;
						case QAM_TYPE_32:
							dCNnordig = 20.5;
							break;
						case QAM_TYPE_64:
							dCNnordig = 23.5;
							break;
						case QAM_TYPE_128:
							dCNnordig = 26.5;
							break;
						case QAM_TYPE_256:
							dCNnordig = 29.5;
							break;
						default:
							dCNnordig = 23.5;
							break;
							
				    }
				}
				 
				break;
			case HI_UNF_TUNER_SIG_TYPE_J83B:
				switch (s_stCurrentSignal[u32TunerId].enQamType)
		        {
					case QAM_TYPE_64:
						dCNnordig = 24;
						break;
					case QAM_TYPE_256:
						dCNnordig = 30;
						break;
					default:
						dCNnordig = 24;
						break;
			    }
				break;
			default:
				dCNnordig = 23.5;
				break;
				
		}
	   
            dSnrSQI = dSnrEva - dCNnordig;
            
		//ber
	    s32Result= ioctl(s_s32TunerFd, TUNER_GET_BER_CMD, (int)&stTunerDataBuf);
	    if (HI_SUCCESS != s32Result)
	    {
	        HI_ERR_TUNER("Tuner HI_TUNER_GetBER error\n");
	        return s32Result;
	    }

	    /* Modified begin: l00185424 2011-11-26 Support satellite */
	    /* If the signal type is cable, convert the data here. */
        switch (s_strCurTunerAttr[u32TunerId].enDemodDevType)
        {
                case HI_UNF_DEMOD_DEV_TYPE_NONE:
                break;
                case HI_UNF_DEMOD_DEV_TYPE_3130I:
                case HI_UNF_DEMOD_DEV_TYPE_3130E:
                case HI_UNF_DEMOD_DEV_TYPE_J83B:
                {
                /* conver to value */
                dBer = ((HI_DOUBLE)(((stTunerDataBuf.u32DataBuf[0] & 0xFF) << 16) + ((stTunerDataBuf.u32DataBuf[1] & 0xFF) << 8)
                        + (stTunerDataBuf.u32DataBuf[2] & 0xFF)) / 8388608.0);
                break;
                }
                case HI_UNF_DEMOD_DEV_TYPE_MXL254:
                case HI_UNF_DEMOD_DEV_TYPE_MXL214:  
                 //{
                  // dBer = (HI_DOUBLE)(stTunerDataBuf.u32DataBuf[0]) ;
                   //break;
                 //}
                case HI_UNF_DEMOD_DEV_TYPE_TDA18280:
                { 
                    
                    dBer = 1;
                    for(i=0;i<stTunerDataBuf.u32DataBuf[2];i++)
                    {
                       dBer = 10 * dBer;
                    }
                    dBer = ((stTunerDataBuf.u32DataBuf[0] + (HI_DOUBLE)stTunerDataBuf.u32DataBuf[1] / 1000)) / dBer ; 

                    break;
                }
                case HI_UNF_DEMOD_DEV_TYPE_HIFDVBC100:
                /* now jump into case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100*/
                case HI_UNF_DEMOD_DEV_TYPE_HIFJ83B100:
                {
                    dBer = (HI_DOUBLE)((HI_DOUBLE)stTunerDataBuf.u32DataBuf[0]/16384.0) ;
                    dBer = dBer*10*10*4/204/8;  /*�˹�ʽ��PERת����BER*/
                    
                    break;
                }
                default:
                break;
	     }

            if(dBer != 0.000000)
            {
                dBerSQI = 20*log10(1/dBer)- 40;
                
                //SQI
                dSQI = ((dSnrSQI - 3)/10 + 1) *dBerSQI + 30;
             
                if(dSQI >= 100)
                {
                   dSQI = 100;
                }
            }
            else
            {
                 dSQI = 100;
            }

            *pu32SignalQuality = (HI_U32)dSQI;
	}
	else
    {
        *pu32SignalQuality = 0;
        return HI_ERR_TUNER_FAILED_GETSIGNALQUALITY;
    }

    return HI_SUCCESS;
}


HI_S32 HI_UNF_TUNER_GetRealFreqSymb( HI_U32 u32TunerId, HI_U32 *pu32Freq, HI_U32 *pu32Symb )
{
    HI_DOUBLE dSampleRate = 28.8;
    HI_S32 i = 1;
    HI_S16 s16Fs,s16Err = 0,s16ErrOneShot;
    TUNER_DATABUF_S stTunerDataBuf = { 0 };
    HI_DOUBLE dTmpFreqOffset = 0.0;
    HI_DOUBLE dTmpFreq = 0.0,c;
    HI_DOUBLE dTmpSymb = 0.0;
    HI_S32 s32Result = HI_FAILURE;
    TUNER_DATA_S stTunerData = { 0 };

    stTunerData.u32Port= u32TunerId;
    stTunerData.u32Data = 0;

    CHECK_TUNER_OPEN();

    if(UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n",u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pu32Freq)
    {
        HI_ERR_TUNER("Input parameter(pu32Freq) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_NULL == pu32Symb)
    {
        HI_ERR_TUNER("Input parameter(pu32Symb) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Result= ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (unsigned long)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {

        HI_ERR_TUNER("GET_STATUS_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSTATUS;
    }

    if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerData.u32Data)
    {
        HI_ERR_TUNER("SIGNAL DROP\n");
        return HI_ERR_TUNER_NOT_CONNECT;
    }

    stTunerDataBuf.u32Port= u32TunerId;
    memset(stTunerDataBuf.u32DataBuf, 0, sizeof(stTunerDataBuf.u32DataBuf));
    s32Result = ioctl(s_s32TunerFd, TUNER_GET_FREQ_SYMB_OFFSET, (HI_U32)&stTunerDataBuf);
    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner TUNER_GET_FREQ_SYMB_OFFSET error\n");
        return HI_ERR_TUNER_FAILED_GETSIGNALSTRENGTH;
    }

    /* Modefied begin: l00185424 2011-11-26 Support satellite*/
    if ((HI_UNF_TUNER_SIG_TYPE_CAB == s_strCurTunerConnectPara[u32TunerId].enSigType)||(HI_UNF_TUNER_SIG_TYPE_J83B == s_strCurTunerConnectPara[u32TunerId].enSigType))
    {
        if( ( stTunerDataBuf.u32DataBuf[0] & 0x08000000 ) > 0 )
        {
            dTmpFreqOffset = (~(stTunerDataBuf.u32DataBuf[0] - 1)) & 0x07FFFFFF;
        }
        else
        {
            dTmpFreqOffset = stTunerDataBuf.u32DataBuf[0];
        }

        i = (HI_S32)pow(2.0, 27.0);

        dTmpFreqOffset = dTmpFreqOffset / i;
        dTmpFreqOffset = (s_stCurrentSignal[u32TunerId].unSRBW.u32SymbolRate / (2 * PI)) * dTmpFreqOffset;
        if( ( stTunerDataBuf.u32DataBuf[0] & 0x08000000 ) > 0 )
        {
            dTmpFreqOffset = -dTmpFreqOffset;
        }

        /* convert Hz to KHz */
        dTmpFreqOffset = dTmpFreqOffset / 1000;

        if(HI_UNF_DEMOD_DEV_TYPE_J83B == s_strCurTunerAttr[u32TunerId].enDemodDevType)
        {
            if(0 == (stTunerDataBuf.u32DataBuf[2] & 0x01))
            {
                dTmpFreqOffset = -dTmpFreqOffset;
            }
        }
        else
        {
            if(stTunerDataBuf.u32DataBuf[2] & 0x01)
            {
                dTmpFreqOffset = -dTmpFreqOffset;
            }
        }


        dTmpFreq = s_stCurrentSignal[u32TunerId].u32Frequency;
        *pu32Freq = ( HI_U32 )( dTmpFreq + dTmpFreqOffset );

		if(HI_UNF_TUNER_DEV_TYPE_TDA18280== s_strCurTunerAttr[u32TunerId].enTunerDevType)
		{
			*pu32Symb = stTunerDataBuf.u32DataBuf[1];
		}
		else
		{

	        /* calculate symbolrate */
	        i = (HI_S32)pow(2.0, 12.0);

	        if(HI_UNF_DEMOD_DEV_TYPE_J83B == s_strCurTunerAttr[u32TunerId].enDemodDevType)
	        {
	            dTmpSymb = i * 25.0;
	        }
	        else
	        {
	            dTmpSymb = i * dSampleRate;
	        }
	        if ( 0 == stTunerDataBuf.u32DataBuf[1] )
	        {
	            HI_ERR_TUNER("get symbolrate error\n");
	            return HI_FAILURE;
	        }
	        else
	        {
	            dTmpSymb = dTmpSymb / stTunerDataBuf.u32DataBuf[1];
	        }
	        *pu32Symb = (HI_U32)(dTmpSymb * 1000000);
		}
    }
    /* Satellite */
    else if (HI_UNF_TUNER_SIG_TYPE_SAT == s_strCurTunerConnectPara[u32TunerId].enSigType)
    {
        if(HI_UNF_TUNER_FE_LNB_UNICABLE != s_stSatPara[u32TunerId].stLNBConfig.enLNBType)
        {
            *pu32Freq = (HI_U32)((HI_S32)s_stCurrentSignal[u32TunerId].u32Frequency - (HI_S32)stTunerDataBuf.u32DataBuf[0]);
            TUNER_IFToDownlinkFreq(&(s_stSatPara[u32TunerId].stLNBConfig),
                s_stSatPara[u32TunerId].enPolar, s_stSatPara[u32TunerId].enLNB22K, *pu32Freq, pu32Freq);
        }
        else
        {
            *pu32Freq = s_strCurTunerConnectPara[u32TunerId].unConnectPara.stSat.u32Freq - stTunerDataBuf.u32DataBuf[0];
        }
        *pu32Symb = s_stCurrentSignal[u32TunerId].unSRBW.u32SymbolRate;
    }
    else if (HI_UNF_TUNER_SIG_TYPE_DVB_T <= s_strCurTunerConnectPara[u32TunerId].enSigType
                 && HI_UNF_TUNER_SIG_TYPE_DTMB >= s_strCurTunerConnectPara[u32TunerId].enSigType)
    {
        if(HI_UNF_DEMOD_DEV_TYPE_3137 == s_strCurTunerAttr[u32TunerId].enDemodDevType)
        {
            s16Fs = stTunerDataBuf.u32DataBuf[0] & 0xffff;
            s16Err = (stTunerDataBuf.u32DataBuf[0] >> 16) & 0xffff;

            //ת�����з�����
            if((s16Err & 0x8000) != 0)
            {
                s16Err = s16Err - 65536;
            }

            c = s16Err * s16Fs / 256.0 / 1000;
            *pu32Freq = (HI_U32)((HI_DOUBLE)s_stCurrentSignal[u32TunerId].u32Frequency + c);

            s16Err = (stTunerDataBuf.u32DataBuf[1] >> 16) & 0xffff;
            s16ErrOneShot = stTunerDataBuf.u32DataBuf[1] & 0xff;
            //ת�����з�����
            if(s16Err > 8191)
            {
                s16Err = s16Err - 16384;
            }

            if((s16ErrOneShot & 0x80) != 0)
            {
                s16ErrOneShot = s16ErrOneShot -256;
            }

            c = (s16ErrOneShot*4 - s16Err/16) * s16Fs / 1024.0 / 1000;
            *pu32Symb = (HI_U32)((HI_DOUBLE)s_stCurrentSignal[u32TunerId].unSRBW.u32SymbolRate + c);
        }
        else
        {
            *pu32Freq = (HI_U32)((HI_S32)s_stCurrentSignal[u32TunerId].u32Frequency - (HI_S32)stTunerDataBuf.u32DataBuf[0]);
            *pu32Symb = s_stCurrentSignal[u32TunerId].unSRBW.u32SymbolRate;
        }
    }
    /* Modefied end: l00185424 2011-11-26 Support satellite*/

    return HI_SUCCESS;
}

/*Obtains current signal information of the TUNER, used in satellite and terrestrial, not necessary for cable.*/
HI_S32 HI_UNF_TUNER_GetSignalInfo(HI_U32 u32TunerId, HI_UNF_TUNER_SIGNALINFO_S *pstSignalInfo)
{
    HI_S32 s32Result;
    TUNER_DATA_S stTunerData;
    TUNER_SIGNALINFO_S stTunerSignalInfo;

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;

    stTunerSignalInfo.u32Port = u32TunerId;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstSignalInfo)
    {
        HI_ERR_TUNER("Input parameter(pstSignalInfo) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    s32Result = ioctl(s_s32TunerFd, TUNER_GET_STATUS_CMD, (unsigned long)&stTunerData);

    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("GET_STATUS_CMD error\n");
        return HI_ERR_TUNER_FAILED_GETSTATUS;
    }

    if (HI_UNF_TUNER_SIGNAL_LOCKED != stTunerData.u32Data)
    {
        HI_ERR_TUNER("SIGNAL DROP\n");
        return HI_ERR_TUNER_NOT_CONNECT;
    }

    s32Result = ioctl(s_s32TunerFd, TUNER_GET_SIGANLINFO_CMD, (int)&stTunerSignalInfo);
    if (HI_SUCCESS != s32Result)
    {
        HI_ERR_TUNER("Tuner HI_UNF_TUNER_GetSignalInfo error\n");
        return HI_ERR_TUNER_FAILED_GETSIGNALINFO;
    }

    memcpy(pstSignalInfo, &stTunerSignalInfo.stInfo, sizeof(HI_UNF_TUNER_SIGNALINFO_S));
    switch (pstSignalInfo->enSigType)
    {
        /* Unsupport now */
    case HI_UNF_TUNER_SIG_TYPE_CAB:
	case HI_UNF_TUNER_SIG_TYPE_J83B:
    default:
        return HI_ERR_TUNER_FAILED_GETSIGNALINFO;

    case HI_UNF_TUNER_SIG_TYPE_DVB_T:
    case HI_UNF_TUNER_SIG_TYPE_DVB_T2:
    case HI_UNF_TUNER_SIG_TYPE_ISDB_T:
    case HI_UNF_TUNER_SIG_TYPE_ATSC_T:
    case HI_UNF_TUNER_SIG_TYPE_DTMB:
        pstSignalInfo->unSignalInfo.stTer.u32Freq =
            s_strCurTunerConnectPara[u32TunerId].unConnectPara.stTer.u32Freq;
        pstSignalInfo->unSignalInfo.stTer.u32BandWidth =
            s_strCurTunerConnectPara[u32TunerId].unConnectPara.stTer.u32BandWidth;
        break;
    case HI_UNF_TUNER_SIG_TYPE_SAT:
        pstSignalInfo->unSignalInfo.stSat.u32Freq =
            s_strCurTunerConnectPara[u32TunerId].unConnectPara.stSat.u32Freq;
        pstSignalInfo->unSignalInfo.stSat.u32SymbolRate =
            s_strCurTunerConnectPara[u32TunerId].unConnectPara.stSat.u32SymbolRate;
        pstSignalInfo->unSignalInfo.stSat.enPolar =
            s_strCurTunerConnectPara[u32TunerId].unConnectPara.stSat.enPolar;
        break;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetLNBConfig( HI_U32 u32TunerId,  HI_UNF_TUNER_FE_LNB_CONFIG_S *pstLNB)
{
    HI_U32 u32LocalFreq;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstLNB)
    {
        HI_ERR_TUNER("Input parameter(pstLNB) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    if (HI_UNF_TUNER_FE_LNB_TYPE_BUTT <= pstLNB->enLNBType)
    {
        HI_ERR_TUNER("Input parameter(pstLNB->enLNBType) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_LNB_BAND_BUTT <= pstLNB->enLNBBand)
    {
        HI_ERR_TUNER("Input parameter(pstLNB->enLNBBand) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_FE_LNB_SINGLE_FREQUENCY == pstLNB->enLNBType)
    {
        if (pstLNB->u32LowLO != pstLNB->u32HighLO)
        {
            HI_ERR_TUNER("Input parameter invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }

    if (pstLNB->u32LowLO > pstLNB->u32HighLO)
    {
        u32LocalFreq = pstLNB->u32LowLO;
        pstLNB->u32LowLO = pstLNB->u32HighLO;
        pstLNB->u32HighLO = u32LocalFreq;
    }

    if (HI_UNF_TUNER_FE_LNB_BAND_C == pstLNB->enLNBBand)
    {
        if ((pstLNB->u32LowLO > 7500) || (pstLNB->u32HighLO > 7500))
        {
            HI_ERR_TUNER("Invalid LO freq\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }
    else
    {
        if ((pstLNB->u32LowLO <= 7500) || (pstLNB->u32HighLO <= 7500))
        {
            HI_ERR_TUNER("Invalid LO freq\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }

    if (HI_UNF_TUNER_FE_LNB_UNICABLE == pstLNB->enLNBType)
    {
        if ((HI_UNF_TUNER_FE_LNB_BAND_KU != pstLNB->enLNBBand) || \
            (7500 >= pstLNB->u32LowLO) || \
            (7500 >= pstLNB->u32HighLO))
        {
            HI_ERR_TUNER("Unicable only support Ku band!\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (7 < pstLNB->u8UNIC_SCRNO)
        {
            HI_ERR_TUNER("Unicable support 8 SCR max!\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if ((SAT_IF_MAX < pstLNB->u32UNICIFFreqMHz) || \
            (SAT_IF_MIN > pstLNB->u32UNICIFFreqMHz))
        {
            HI_ERR_TUNER("Unicable IF error!\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (HI_UNF_TUNER_SATPOSN_BUT <= pstLNB->enSatPosn)
        {
            HI_ERR_TUNER("Unicable position error!\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }
    }

    s_stSatPara[u32TunerId].stLNBConfig = *pstLNB;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetLNBPower(HI_U32 u32TunerId, HI_UNF_TUNER_FE_LNB_POWER_E enLNBPower)
{
    TUNER_LNB_OUT_S stLNBOut;
    HI_S32 s32Ret;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_FE_LNB_POWER_BUTT <= enLNBPower)
    {
        HI_ERR_TUNER("Input parameter(pstLNB) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stLNBOut.u32Port = u32TunerId;

    switch (enLNBPower)
    {
    case HI_UNF_TUNER_FE_LNB_POWER_ON:
        stLNBOut.enOut = TUNER_LNB_OUT_18V;
        break;

    case HI_UNF_TUNER_FE_LNB_POWER_ENHANCED:
        stLNBOut.enOut = TUNER_LNB_OUT_19V;
        break;

    case HI_UNF_TUNER_FE_LNB_POWER_OFF:
        stLNBOut.enOut = TUNER_LNB_OUT_0V;
        break;

    default:
        return HI_ERR_TUNER_INVALID_PARA;
    }

    s32Ret = ioctl(s_s32TunerFd, TUNER_SET_LNBOUT_CMD, &stLNBOut);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set LNB power fail.\n");
        return HI_ERR_TUNER_FAILED_LNBCTRL;
    }

    s_stSatPara[u32TunerId].enLNBPower = enLNBPower;
    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetPLPID(HI_U32 u32TunerId, HI_U8 u8PLPID)
{
    TUNER_DATABUF_S stTunerDataBuf = {0};
    HI_S32 s32Ret;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    stTunerDataBuf.u32Port = u32TunerId;
    stTunerDataBuf.u32DataBuf[0] = u8PLPID;
    stTunerDataBuf.u32DataBuf[1] = g_u32PLPMode;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SETPLPNO_CMD, &stTunerDataBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set PLP ID fail.\n");
        return HI_ERR_TUNER_FAILED_SETPLPID;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetPLPMode(HI_U32 u32TunerId, HI_U8 u8Mode)
{
    g_u32PLPMode = u8Mode;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetCommonPLPID(HI_U32 u32TunerId, HI_U8 u8PLPID)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;

    if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = u8PLPID;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SET_COMMONPLP_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set Common PLP ID fail.\n");
        return HI_ERR_TUNER_FAILED_SETPLPID;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetCommonPLPCombination(HI_U32 u32TunerId, HI_U8 u8PLPID)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;

    if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = u8PLPID;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SET_COMMONPLP_COMBINATION_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set Common PLP Combination fail.\n");
        return HI_ERR_TUNER_FAILED_SETPLPID;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetPLPNum(HI_U32 u32TunerId, HI_U8 *pu8PLPNum)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pu8PLPNum)
    {
        HI_ERR_TUNER("Input parameter(pu8PLPNum) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;

    s32Ret = ioctl(s_s32TunerFd, TUNER_GETPLPNUM_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Get PLP NUM fail.\n");
        return HI_ERR_TUNER_FAILED_GETPLPNUM;
    }

    *pu8PLPNum = (HI_U8)stTunerData.u32Data;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetCurrentPLPType(HI_U32 u32TunerId,  HI_UNF_TUNER_T2_PLP_TYPE_E *penPLPType)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == penPLPType)
    {
        HI_ERR_TUNER("Input parameter(penPLPType) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;
    
    s32Ret = ioctl(s_s32TunerFd, TUNER_GETCURPLPTYPE_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Get PLP Type fail.\n");
        return HI_ERR_TUNER_FAILED_GETPLPTYPE;
    }

    *penPLPType = (HI_UNF_TUNER_T2_PLP_TYPE_E)stTunerData.u32Data;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetPLPId(HI_U32 u32TunerId, HI_U8 *pu8PLPId)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pu8PLPId)
    {
        HI_ERR_TUNER("Input parameter(pu8PLPId) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    stTunerData.u32Port = u32TunerId;

    s32Ret = ioctl(s_s32TunerFd, TUNER_GET_PLP_ID_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Get PLP id fail.\n");
        return HI_ERR_TUNER_FAILED_GETPLPTYPE;
    }

    *pu8PLPId = (HI_U8)stTunerData.u32Data;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetPLPGrpId(HI_U32 u32TunerId, HI_U8 *pu8PLPGrpId)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pu8PLPGrpId)
    {
        HI_ERR_TUNER("Input parameter(pu8PLPGrpId) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    stTunerData.u32Port = u32TunerId;

    s32Ret = ioctl(s_s32TunerFd, TUNER_GET_GROUP_PLP_ID_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Get PLP group id fail.\n");
        return HI_ERR_TUNER_FAILED_GETPLPTYPE;
    }

    *pu8PLPGrpId = (HI_U8)stTunerData.u32Data;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetAntennaPower(HI_U32 u32TunerId, HI_UNF_TUNER_TER_ANTENNA_POWER_E enPower)
{
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Result = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

	stTunerData.u32Port = u32TunerId;
	stTunerData.u32Data = (HI_U32)enPower;
	s_stTerPara[u32TunerId].enAntennaPower = enPower;

    s32Result = ioctl(s_s32TunerFd, TUNER_SET_ANTENNA_POWER_CMD, &stTunerData);

    return s32Result;
}

HI_S32 HI_UNF_TUNER_GetAntennaPower(HI_U32 u32TunerId, HI_UNF_TUNER_TER_ANTENNA_POWER_E *penPower)
{
    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    *penPower = s_stTerPara[u32TunerId].enAntennaPower;

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_BlindScanStart(HI_U32 u32TunerId,const HI_UNF_TUNER_BLINDSCAN_PARA_S *pstPara)
{
    static BLINDSCAN_PARA_S stBlindScan;

    HI_S32 s32Result = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstPara)
    {
        HI_ERR_TUNER("Input parameter(pstPara) invalid\n");
        return HI_ERR_TUNER_INVALID_POINT;
    }

    /* DVB-S/S2 Blindscan */
    if (HI_UNF_TUNER_SIG_TYPE_SAT == s_strCurTunerAttr[u32TunerId].enSigType)
    {
        if (HI_UNF_TUNER_BLINDSCAN_MODE_BUTT <= pstPara->enMode)
        {
            HI_ERR_TUNER("Input parameter(enMode) invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (HI_NULL == pstPara->unScanPara.stSat.pfnEVTNotify)
        {
            HI_ERR_TUNER("Input parameter(pfnEVTNotify) invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
        }

        if (HI_UNF_TUNER_BLINDSCAN_MODE_MANUAL == pstPara->enMode)
        {
            if (HI_UNF_TUNER_FE_POLARIZATION_BUTT <= pstPara->unScanPara.stSat.enPolar)
            {
                HI_ERR_TUNER("Input parameter(enPolar) invalid\n");
                return HI_ERR_TUNER_INVALID_PARA;
            }
            if (HI_UNF_TUNER_FE_LNB_22K_BUTT <= pstPara->unScanPara.stSat.enLNB22K)
            {
                HI_ERR_TUNER("Input parameter(enLNB22K) invalid\n");
                return HI_ERR_TUNER_INVALID_PARA;
            }
            if ((SAT_IF_MIN_KHZ > pstPara->unScanPara.stSat.u32StartFreq)
                    || (SAT_IF_MAX_KHZ < pstPara->unScanPara.stSat.u32StartFreq))
            {
                HI_ERR_TUNER("Input parameter(u32StartFreq) invalid\n");
                return HI_ERR_TUNER_INVALID_PARA;
            }
            if ((SAT_IF_MIN_KHZ > pstPara->unScanPara.stSat.u32StopFreq)
                    || (SAT_IF_MAX_KHZ < pstPara->unScanPara.stSat.u32StopFreq))
            {
                HI_ERR_TUNER("Input parameter(u32StopFreq) invalid\n");
                return HI_ERR_TUNER_INVALID_PARA;
            }
            if (pstPara->unScanPara.stSat.u32StopFreq <= pstPara->unScanPara.stSat.u32StartFreq)
            {
                HI_ERR_TUNER("Input parameter(u32StopFreq) invalid\n");
                return HI_ERR_TUNER_INVALID_PARA;
            }
        }

        if (HI_NULL != s_stSatPara[u32TunerId].pBlindScanMonitor)
        {
            if (s_stSatPara[u32TunerId].bBlindScanBusy)
            {
                HI_ERR_TUNER("Blind scan busy.\n");
                return HI_ERR_TUNER_FAILED_BLINDSCAN;
            }
            else
            {
                (HI_VOID)pthread_join(*s_stSatPara[u32TunerId].pBlindScanMonitor, HI_NULL);
                //free(s_stSatPara[u32TunerId].pBlindScanMonitor);
                HI_FREE(HI_ID_TUNER, s_stSatPara[u32TunerId].pBlindScanMonitor);
                s_stSatPara[u32TunerId].pBlindScanMonitor = HI_NULL;
            }
        }

        s_stSatPara[u32TunerId].pBlindScanMonitor = (pthread_t*)HI_MALLOC(HI_ID_TUNER, sizeof(pthread_t));
        if (HI_NULL == s_stSatPara[u32TunerId].pBlindScanMonitor)
        {
            HI_ERR_TUNER("No memory.\n");
            return HI_ERR_TUNER_FAILED_BLINDSCAN;
        }

        stBlindScan.u32Port = u32TunerId;
        stBlindScan.stPara = *pstPara;

        s32Result = pthread_create(s_stSatPara[u32TunerId].pBlindScanMonitor, 0, TUNER_BlindScanThread, &stBlindScan);
        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("Create pthread fail.\n");
            if (s_stSatPara[u32TunerId].pBlindScanMonitor)
            {
                HI_FREE(HI_ID_TUNER, s_stSatPara[u32TunerId].pBlindScanMonitor);
                s_stSatPara[u32TunerId].pBlindScanMonitor = HI_NULL;
            }

            s_stSatPara[u32TunerId].bBlindScanStop = HI_FALSE;
            return HI_ERR_TUNER_FAILED_BLINDSCAN;
        }
        s_stSatPara[u32TunerId].bBlindScanStop = HI_FALSE;
    }
    else
    {
        HI_ERR_TUNER("Error signal type!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_BlindScanStop( HI_U32 u32TunerId)
{
    /*TUNER_DATA_S stTunerData = { 0 };

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;*/    /* Reserve */

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL != s_stSatPara[u32TunerId].pBlindScanMonitor)
    {
        s_stSatPara[u32TunerId].bBlindScanStop = HI_TRUE;
        (HI_VOID)pthread_join(*s_stSatPara[u32TunerId].pBlindScanMonitor, HI_NULL);
        //free(s_stSatPara[u32TunerId].pBlindScanMonitor);
        HI_FREE(HI_ID_TUNER, s_stSatPara[u32TunerId].pBlindScanMonitor);
        s_stSatPara[u32TunerId].pBlindScanMonitor = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_TerScanStart( HI_U32 u32TunerId, HI_UNF_TUNER_TER_SCAN_PARA_S *pstPara)
{
	HI_S32 s32Result = HI_FAILURE;
	static TERSCAN_PARA_S stTerScan;
	
	if(HI_UNF_TUNER_SIG_TYPE_DVB_T == s_strCurTunerAttr[u32TunerId].enSigType
		|| HI_UNF_TUNER_SIG_TYPE_DVB_T2 == s_strCurTunerAttr[u32TunerId].enSigType)
	{
		if((pstPara->stTer.u32Frequency < TER_RF_MIN)  || (pstPara->stTer.u32Frequency > TER_RF_MAX))
		{
			HI_ERR_TUNER("Input parameter(u32Frequency) invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
		}

		if((pstPara->stTer.u32BandWidth < TER_BW_MIN)  || (pstPara->stTer.u32BandWidth > TER_BW_MAX))
		{
			HI_ERR_TUNER("Input parameter(u32BandWidth) invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
		}

		if(pstPara->stTer.enScanMode >= HI_UNF_TUNER_TER_SCAN_DVB_T_T2_BUTT)
		{
			HI_ERR_TUNER("Input parameter(enScanMode) invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
		}

		if(pstPara->stTer.bScanLite > 1)
		{
			HI_ERR_TUNER("Input parameter(u8ScanLite) invalid\n");
            return HI_ERR_TUNER_INVALID_PARA;
		}

		if (HI_NULL != s_stTerPara[u32TunerId].pScanMonitor)
        {
            if (s_stTerPara[u32TunerId].bScanBusy)
            {
                HI_ERR_TUNER("Blind scan busy.\n");
                return HI_ERR_TUNER_FAILED_BLINDSCAN;
            }
            else
            {
                (HI_VOID)pthread_join(*s_stTerPara[u32TunerId].pScanMonitor, HI_NULL);
                free(s_stTerPara[u32TunerId].pScanMonitor);
                s_stTerPara[u32TunerId].pScanMonitor = HI_NULL;
            }
        }

        s_stTerPara[u32TunerId].pScanMonitor = (pthread_t*)malloc(sizeof(pthread_t));
        if (HI_NULL == s_stTerPara[u32TunerId].pScanMonitor)
        {
            HI_ERR_TUNER("No memory.\n");
            return HI_ERR_TUNER_FAILED_BLINDSCAN;
        }

		memset(pstPara->enChanArray,0,sizeof(pstPara->enChanArray));
        stTerScan.u32Port = u32TunerId;
        stTerScan.stPara = *pstPara;

        s32Result = pthread_create(s_stTerPara[u32TunerId].pScanMonitor, 0, TUNER_DVBT2ScanThread, &stTerScan);
        if (HI_SUCCESS != s32Result)
        {
            HI_ERR_TUNER("Create pthread fail.\n");
            if (s_stTerPara[u32TunerId].pScanMonitor)
            {
                free(s_stTerPara[u32TunerId].pScanMonitor);
                s_stTerPara[u32TunerId].pScanMonitor = HI_NULL;
            }

            s_stTerPara[u32TunerId].bScanStop = HI_FALSE;
            return HI_ERR_TUNER_FAILED_BLINDSCAN;
        }

		(HI_VOID)pthread_join(*s_stTerPara[u32TunerId].pScanMonitor, HI_NULL);
        free(s_stTerPara[u32TunerId].pScanMonitor);
        s_stTerPara[u32TunerId].pScanMonitor = HI_NULL;
				
        s_stTerPara[u32TunerId].bScanStop = HI_FALSE;
	}
	else
    {
        HI_ERR_TUNER("Error signal type!\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

	return s32Result;
}

HI_S32 HI_UNF_TUNER_TerScanStop( HI_U32 u32TunerId)
{
    /*TUNER_DATA_S stTunerData = { 0 };

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;*/    /* Reserve */


    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL != s_stTerPara[u32TunerId].pScanMonitor)
    {
        s_stTerPara[u32TunerId].bScanStop = HI_TRUE;
        (HI_VOID)pthread_join(*s_stTerPara[u32TunerId].pScanMonitor, HI_NULL);
        HI_FREE(HI_ID_TUNER, s_stTerPara[u32TunerId].pScanMonitor);
        s_stTerPara[u32TunerId].pScanMonitor = HI_NULL;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_Switch22K(HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_22K_E enPort)
{
    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_SWITCH_22K_BUTT <= enPort)
    {
        HI_ERR_TUNER("Input parameter(enPort) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Save */
    s_stSatPara[u32TunerId].enSwitch22K = enPort;

    if (HI_UNF_TUNER_SWITCH_22K_0 == enPort)
    {
        return TUNER_DISEQC_Send22K(u32TunerId, HI_FALSE);
    }
    else if (HI_UNF_TUNER_SWITCH_22K_22 == enPort)
    {
        return TUNER_DISEQC_Send22K(u32TunerId, HI_TRUE);
    }
    else
    {
        return HI_SUCCESS;
    }
}

HI_S32 HI_UNF_TUNER_Switch012V( HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_0_12V_E enPort)
{
    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_SWITCH_0_12V_BUTT <= enPort)
    {
        HI_ERR_TUNER("Input parameter(enPort) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SwitchToneBurst(HI_U32 u32TunerId, HI_UNF_TUNER_SWITCH_TONEBURST_E enStatus)
{
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_UNF_TUNER_SWITCH_TONEBURST_BUTT <= enStatus)
    {
        HI_ERR_TUNER("Input parameter(enStatus) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /* Save */
    s_stSatPara[u32TunerId].enToneBurst = enStatus;

    /* Send tone */
    stTunerData.u32Port = u32TunerId;
    if ((HI_UNF_TUNER_SWITCH_TONEBURST_0 == enStatus) || (HI_UNF_TUNER_SWITCH_TONEBURST_1 == enStatus))
    {
        stTunerData.u32Data = enStatus - 1;

        (HI_VOID)TUNER_DISEQC_Stop22K(u32TunerId);
        usleep(DISEQC_DELAY_TIME_MS * 1000);

        s32Ret = ioctl(s_s32TunerFd, TUNER_SEND_TONE_CMD, &stTunerData);
        if (HI_SUCCESS != s32Ret)
        {
            HI_ERR_TUNER("Set tone burst fail.\n");
            return HI_ERR_TUNER_FAILED_DISEQC;
        }

        usleep(DISEQC_DELAY_TIME_MS * 1000);
        (HI_VOID)TUNER_DISEQC_Resume22K(u32TunerId);
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_DISEQC_SendRecvMessage(HI_U32 u32TunerId,
                                           const HI_UNF_TUNER_DISEQC_SENDMSG_S * pstSendMsg,
                                           HI_UNF_TUNER_DISEQC_RECVMSG_S * pstRecvMsg)
{
    HI_S32 s32Ret = HI_FAILURE;
    s32Ret = TUNER_DISEQC_SendRecvMessage(u32TunerId, pstSendMsg, pstRecvMsg);
    return s32Ret;
}

HI_S32 HI_UNF_TUNER_Standby(HI_U32 u32TunerId)
{
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 1;

    s32Ret = ioctl(s_s32TunerFd, TUNER_STANDBY_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner standby fail.\n");
        return HI_ERR_TUNER_FAILED_STANDBY;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_WakeUp( HI_U32 u32TunerId)
{
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = 0;

    s32Ret = ioctl(s_s32TunerFd, TUNER_STANDBY_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner wake up fail.\n");
        return HI_ERR_TUNER_FAILED_WAKEUP;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetTSOUT(HI_U32 u32TunerId, HI_UNF_TUNER_TSOUT_SET_S *pstTSOUT)
{
    TUNER_DATA_S stTunerData;
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstTSOUT)
    {
        HI_ERR_TUNER("penTSOUT is NULL\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = (HI_U32)pstTSOUT;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SETTSOUT_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner set ts out fail.\n");
        return HI_ERR_TUNER_FAILED_SETTSOUT;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetConstellationData(HI_U32 u32TunerId, HI_UNF_TUNER_SAMPLE_DATALEN_E enDataLen, HI_UNF_TUNER_SAMPLE_DATA_S *pstData)
{
    HI_U32 u32DataLen = 0;
    TUNER_DATA_SRC_E enDataSrc = TUNER_DATA_SRC_EQU;
    TUNER_SAMPLE_DATA_PARAM_S stSampleParam;
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret = HI_FAILURE;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pstData)
    {
        HI_ERR_TUNER("ps32Data is NULL\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if (HI_UNF_TUNER_SAMPLE_DATALEN_BUTT <= enDataLen)
    {
        HI_ERR_TUNER("Input parameter(enDataLen) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    switch (enDataLen)
    {
    case HI_UNF_TUNER_SAMPLE_DATALEN_32:
        u32DataLen = 32;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_64:
        u32DataLen = 64;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_128:
        u32DataLen = 128;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_256:
        u32DataLen = 256;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_512:
        u32DataLen = 512;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_1024:
        u32DataLen = 1024;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_2048:
        u32DataLen = 2048;
        break;
    default:
        HI_ERR_TUNER("Input parameter(enDataLen) invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /*sample data of equ, return*/
    stSampleParam.enDataSrc = enDataSrc;
    stSampleParam.u32DataLen = u32DataLen;
    stSampleParam.pstData = pstData;

    if (TUNER_DATA_SRC_BUTT <= stSampleParam.enDataSrc)
    {
        HI_ERR_TUNER("Data source invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = (HI_U32)&stSampleParam;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SAMPLE_DATA_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner sample data fail.\n");
        return HI_ERR_TUNER_FAILED_SAMPLEDATA;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetSpectrumData(HI_U32 u32TunerId, HI_UNF_TUNER_SAMPLE_DATALEN_E enDataLen, HI_U32 *pu32Data)
{
    HI_UNF_TUNER_SAMPLE_DATA_S *pstADData = 0;
    HI_U32 u32DataLen = 0;
    TUNER_DATA_SRC_E enDataSrc = TUNER_DATA_SRC_ADC;
    TUNER_SAMPLE_DATA_PARAM_S stSampleParam;
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret = HI_FAILURE;
    HI_U8 u8LenPow = 0;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == pu32Data)
    {
        HI_ERR_TUNER("pu32Data is NULL\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    switch (enDataLen)
    {
    case HI_UNF_TUNER_SAMPLE_DATALEN_512:
        u32DataLen = 512;
        u8LenPow = 9;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_1024:
        u32DataLen = 1024;
        u8LenPow = 10;
        break;
    case HI_UNF_TUNER_SAMPLE_DATALEN_2048:
        u32DataLen = 2048;
        u8LenPow = 11;
        break;
    default:
        HI_ERR_TUNER("invalid parameter DataLen = 0x%x\n",enDataLen);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /*malloc mem*/
    pstADData = (HI_UNF_TUNER_SAMPLE_DATA_S *)HI_MALLOC(HI_ID_TUNER, u32DataLen * sizeof(HI_UNF_TUNER_SAMPLE_DATA_S));
    if (HI_NULL == pstADData)
    {
        HI_ERR_TUNER("Malloc fail!\n");
        return HI_FAILURE;
    }

    /*sample data of ADC*/
    stSampleParam.enDataSrc = enDataSrc;
    stSampleParam.u32DataLen = u32DataLen;
    stSampleParam.pstData = pstADData;

    if (TUNER_DATA_SRC_BUTT <= stSampleParam.enDataSrc)
    {
        HI_ERR_TUNER("Data source invalid\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = (HI_U32)&stSampleParam;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SAMPLE_DATA_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner sample data fail.\n");
        HI_FREE(HI_ID_TUNER, pstADData);
        return HI_ERR_TUNER_FAILED_SAMPLEDATA;
    }

    /*fft of ADC data*/
    s32Ret = fft_fxpt(pstADData, u8LenPow, pu32Data);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("FFT fail.\n");
        HI_FREE(HI_ID_TUNER, pstADData);
        return HI_FAILURE;
    }

    /*free buffer and return*/
    HI_FREE(HI_ID_TUNER, pstADData);
    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetSatIsiID(HI_U32 u32TunerId, HI_U8 u8IsiID)
{
	TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;
	
	if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

	stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = (HI_U32)u8IsiID;

    s32Ret = ioctl(s_s32TunerFd, TUNER_SET_ISI_ID_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Set isi id fail.\n");
        return HI_ERR_TUNER_FAILED_SETISIID;
    }

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetSatTotalStream(HI_U32 u32TunerId, HI_U8 *pu8TotalStream)
{
	TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;
	
	if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

	stTunerData.u32Port = u32TunerId;

	s32Ret = ioctl(s_s32TunerFd, TUNER_GET_TOTAL_STREAM_CMD, &stTunerData);  
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Get total isi number fail.\n");
        return HI_ERR_TUNER_FAILED_GETTOTALISI;
    }

	*pu8TotalStream = (HI_U8)(stTunerData.u32Data);

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_GetSatIsiID(HI_U32 u32TunerId, HI_U8 u8StreamIndex, HI_U8 *pu8IsiID)
{
	TUNER_DATABUF_S stTunerDataBuf = {0};
    HI_S32 s32Ret;
	
	if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

	stTunerDataBuf.u32Port = u32TunerId;
	stTunerDataBuf.u32DataBuf[0] = (HI_U32)u8StreamIndex;

	s32Ret = ioctl(s_s32TunerFd, TUNER_GET_ISI_ID_CMD, &stTunerDataBuf);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("get isi id fail.\n");
        return HI_ERR_TUNER_FAILED_GETISIID;
    }

	*pu8IsiID = (HI_U8)stTunerDataBuf.u32DataBuf[1];

    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_SetScramble(HI_U32 u32TunerId,HI_U32 u32N)
{
	TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret;
	HI_U32 i,u32Value = 1,u32New;
	HI_U32 u32Bit0Value,u32Bit7Value;
	
	if (!s_bTunerOpened)
    {
        HI_ERR_TUNER("tuner not opened, tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_NOT_OPEN;
    }

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

	for(i = 0;i < u32N;i++)
	{
		u32Bit0Value = u32Value & 0x1;
		u32Bit7Value = (u32Value >> 7) & 0x1;
		u32New = (u32Bit0Value + u32Bit7Value) % 2;
		u32Value = (u32Value >> 1) | (u32New << 17);
	}

	stTunerData.u32Port = u32TunerId;
	stTunerData.u32Data = u32Value;

	s32Ret = ioctl(s_s32TunerFd, TUNER_SET_SCRAMBLE_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("set scramble fail.\n");
        return HI_FAILURE;
    }
	
    return HI_SUCCESS;
}

HI_S32 HI_UNF_TUNER_UnicPowerOff(HI_U32 u32TunerId,HI_U8 u8SCRNO)
{
    HI_S32 s32Ret = 0;
    s32Ret =  UNIC_PowerOFF(u32TunerId,u8SCRNO);
    return s32Ret;
}

HI_S32 HI_UNF_TUNER_UnicSCRxOn(HI_U32 u32TunerId)
{
    HI_S32 s32Ret = 0;
    s32Ret =  UNIC_SCRxSignal_ON(u32TunerId);
    return s32Ret;
}

HI_S32 HI_UNF_TUNER_UnicConfig(HI_U32 u32TunerId,HI_U8 u8SCRNO,HI_U8 u8AppNo)
{
    HI_S32 s32Ret = 0;
    s32Ret =  UNIC_Config(u32TunerId,u8SCRNO,u8AppNo);
    return s32Ret;
}

HI_S32 HI_UNF_TUNER_UnicLOFREQ(HI_U32 u32TunerId,HI_U8 u8SCRNO,HI_U8 u8LoFreqNo)
{
    HI_S32 s32Ret = 0;
    s32Ret =  UNIC_LOFREQ(u32TunerId,u8SCRNO,u8LoFreqNo);
    return s32Ret;
}

HI_S32 HI_UNF_TUNER_GetTunerPowerSpectrumData(HI_U32 u32TunerId, HI_U32 u32freqStartInHz,HI_U32 u32freqStepInHz,HI_U32 u32numOfFreqSteps,HI_S16 *ps16powerData)
{
    HI_S16 *ps16ADData = 0;
	TUNER_POWER_SPECTRUM_DATA_PARAM_S stSpectrumParam;
    HI_U32 u32DataLen = 0;
    TUNER_DATA_S stTunerData = {0};
    HI_S32 s32Ret = HI_FAILURE;
    HI_S32 i= 0;

    CHECK_TUNER_OPEN();

    if (UNF_TUNER_NUM <= u32TunerId)
    {
        HI_ERR_TUNER("Input parameter(u32TunerId) invalid,invalid tunerId is: %d\n", u32TunerId);
        return HI_ERR_TUNER_INVALID_PORT;
    }

    if (HI_NULL == ps16powerData)
    {
        HI_ERR_TUNER("pu32Data is NULL\n");
        return HI_ERR_TUNER_INVALID_PARA;
    }

    if((u32freqStartInHz < SPEC_RF_START_KHZ) || (u32freqStartInHz > SPEC_RF_END_KHZ))
	{
	    HI_ERR_TUNER("invalid parameter u32freqStartInHz = %d\n",u32freqStartInHz);
        return HI_ERR_TUNER_INVALID_PARA;
	}
	if(u32freqStepInHz < SPEC_RF_STEP_MIN_KHZ)
	{
	    HI_ERR_TUNER("invalid parameter u32freqStepInHz = %d\n",u32freqStepInHz);
        return HI_ERR_TUNER_INVALID_PARA;
	}

    if((0 == u32numOfFreqSteps) ||(( u32freqStartInHz + u32freqStepInHz * u32numOfFreqSteps) > SPEC_RF_END_KHZ ))
    {
        HI_ERR_TUNER("invalid parameter u32numOfFreqSteps = %d\n",u32numOfFreqSteps);
        return HI_ERR_TUNER_INVALID_PARA;
    }

    /*malloc mem*/
    ps16ADData = (HI_S16 *)HI_MALLOC(HI_ID_TUNER, u32numOfFreqSteps * sizeof(HI_S16));
    if (HI_NULL == ps16ADData)
    {
        HI_ERR_TUNER("Malloc fail!\n");
        return HI_FAILURE;
    }

    /*sample data of ADC*/

	stSpectrumParam.u32freqStartInHz = u32freqStartInHz;	
	stSpectrumParam.u32freqStepInHz = u32freqStepInHz;
	stSpectrumParam.u32numOfFreqSteps = u32numOfFreqSteps;
	stSpectrumParam.ps16powerData = ps16ADData;

    stTunerData.u32Port = u32TunerId;
    stTunerData.u32Data = (HI_U32)&stSpectrumParam;

    s32Ret = ioctl(s_s32TunerFd, TUNER_TUENR_POWER_SPECTRUM_DATA_CMD, &stTunerData);
    if (HI_SUCCESS != s32Ret)
    {
        HI_ERR_TUNER("Tuner sample data fail.\n");
        HI_FREE(HI_ID_TUNER, ps16ADData);
        return HI_ERR_TUNER_FAILED_SAMPLEDATA;
    }
    for(i=0;i<u32numOfFreqSteps;i++)
    {
        ps16powerData[i] = ps16ADData[i];
		
    }

	
    /*free buffer and return*/
    HI_FREE(HI_ID_TUNER, ps16ADData);
    return HI_SUCCESS;
}

