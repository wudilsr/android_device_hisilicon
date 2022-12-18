/******************************************************************************

  Copyright (C), 2012-2050, Hisilicon Tech. Co., Ltd.

******************************************************************************
  File Name     : pq_mng_pfmd.h
  Version       : Initial Draft
  Author        : l00191147
  Created       : 2013/10/11
  Description   : 

******************************************************************************/
#ifndef __PQ_MNG_PFMD_H__
#define __PQ_MNG_PFMD_H__

#include "hi_type.h"
#include "pq_hal_comm.h"
#include "pq_hal_fmd.h"

#ifdef __cplusplus
 #if __cplusplus
extern "C" {
 #endif
#endif /* __cplusplus */

//软件层的定义
#define pfmd_round(a, rup, rdn) ((a)>(rup)?(rup):((a)<(rdn)?(rdn):(a)))

typedef struct  
{
	HI_S32 iDelay;
	//每种模式下每种相位的计数器;
	HI_S32 iModeCounter32[5+1];
	HI_S32 iModeCounter2332[10+1];
	HI_S32 iModeCounter2224[10+1];
	HI_S32 iModeCounter64[10+1];
	HI_S32 iModeCounter55[10+1];
	HI_S32 iModeCounter32322[12+1];
	HI_S32 iModeCounter87[15+1];
	HI_S32 iModeCounter11_2_3[25+1];
	HI_S32 iModeCounter22[2+1];

	//7种模式相关的计数器
	HI_S32 *iModeCounters[9];   //9种模式不同相位的计数器;
	HI_S32 iModeLocked[9];       //锁定;
	HI_S32 iUnlockCounter[9];    //未锁定;
	HI_S32 iLastTend[9];  //??
	HI_S32 iMaxPCCPhase[9];
//	HI_S32 iFrameCount[9];
	HI_S32 iMaxPCCPerMode[9];
	HI_S32 iModeTotalPhase[9];

	HI_S32 iSubtitle[9];
	int aHalfSecondModeReport[30];//增加一个数组来记录半秒内PCC为1000的模式信息。//如果出现多个模式有PCC达到1000的情况，以短周期者为主。
	int iHalfSecondNewest;
	int iHalfSecondNewestReport;
	int bHalfSecondModeTrans;
	int iHalfSecondModeTransCounter;
	//如果发现出现了多个模式/相位计数器大于入锁阈值的情况，说明发生了类似MPC（media player classic）播放器的各种模式交替使用的插帧方法。
	//目前默认这种插帧方法是在60Hz播放时出现的，且模式的切换以半秒为周期。如果出现其他情况可以按此思路扩展。
	HI_S32 iFinalUnlockCounter;

} PfmdPulldownDetectorStatus;



typedef struct
{
	HI_S32 BUFFERSIZE;
	HI_S32 MAX_PIXEL_VALUE;
	HI_S32 WINWIDTH;
	HI_S32 TSS;
	HI_S32 SIGMA_CHANGE_MULTIPLE_THRED;

	HI_S32 PMAX_UINT;
	HI_S32 PMIN_UINT;
	HI_S32 PMIN_INT;
	HI_S32 PMODE_UP_BOUND;
	HI_S32 PMODE_DOWN_BOUND;
	HI_S32 PMODE_COUNTER_THRD;
	HI_S32 PMODE_NONE;
	HI_S32 SUBTITLE_THRESGOLD;
	HI_S32 PMODE22_COUNTER_THRD;//8
	HI_S32 PMODE32_COUNTER_THRD;//8    //should be large enough to avoid the 32322 be detected as MODE32
	HI_S32 PMODE2224_COUNTER_THRD; //8,22
	HI_S32 PMODE2332_COUNTER_THRD;  //8
	HI_S32 PMODE55_COUNTER_THRD;      //8
	HI_S32 PMODE64_COUNTER_THRD;      //8
	HI_S32 PMODE32322_COUNTER_THRD;  //8
	HI_S32 PMODE87_COUNTER_THRD;      //8
	HI_S32 PMODE11_2_3_COUNTER_THRD;  
    HI_S32 PMODE22_UNLOCKCOUNTER_THRD;//8
	HI_S32 PMODE32_UNLOCKCOUNTER_THRD;//8    //should be large enough to avoid the 32322 be detected as MODE32
	HI_S32 PMODE2224_UNLOCKCOUNTER_THRD; //8,22
	HI_S32 PMODE2332_UNLOCKCOUNTER_THRD;  //8
	HI_S32 PMODE55_UNLOCKCOUNTER_THRD;      //8
	HI_S32 PMODE64_UNLOCKCOUNTER_THRD;      //8
	HI_S32 PMODE32322_UNLOCKCOUNTER_THRD;  //8
	HI_S32 PMODE87_UNLOCKCOUNTER_THRD;      //8
	HI_S32 PMODE11_2_3_UNLOCKCOUNTER_THRD;  
	HI_S32 PMODE_HALF_SECOND_MODE_TRANS_COUNTER_THRD;//25

	HI_S32 PSCD_THRE;
	HI_S32 *iComb;   
	HI_S32 *iCombDiff;//
	HI_S32 *iCombVary;//comb跳转值，用于计算PCC
	HI_S32 *iNonMonotony;
    HI_S32 *iSumNonmonotony;
    //单调性窗口
	HI_S32 iThresholdTitle;  //单调性阈值
	//HI_S32 iThredCoring;   //空域comb阈值
	//HI_S32 iThredMov;      //时域运动阈值
	HI_S32 iCalcVaryWindow[9];
    HI_S32 PreCHD[128];
	HI_S32 iCurrSCD;
	HI_S32 iCurrPos;
	HI_S32 *iCHD_window;
    HI_S32 iThresh[9];

	HI_S32 SceneChangeCounter;
	HI_S32 iSubtitle;
	HI_S32 *PSS;
	HI_S32 *stillFrame;
	PfmdPulldownDetectorStatus *spPfmdPdDetectorStatus;

}PfmdSoftwareAPIParas;

typedef struct{
	char *sInputFileName;  //输入文件
	char *sOutputFileLock;  //输出锁定结果，所有模式
	char *sOutputFileComb; //输出comb，及直方图
	char *sResultFileName;   //最终统计结果
	HI_S32 iHeight;
	HI_S32 iWidth;
	HI_S32 iFrameBegin;
	HI_S32 iFrameEnd;
	HI_S32 YuvForm; // =0 :420, =1 :422,  =2: 444
	HI_S32 OSDDetectionEnable;
	int TestDeinterlaceSrc;
}PfmdInputParameters;

typedef struct
{
	HI_S32 iMaxPCCSigmaCadence;
	HI_S32 iMaxPCCCombCadence;
	HI_S32 iMaxPCC;// =iMaxPCCSigmaCadence+iMaxPCCCombCadence;
	HI_S32 iMaxPCCMode;//最大PCC的模式以及相位
} PfmdMaxPCCAndMode;


typedef enum
{
	pMODE_32        =  0, 
	pMODE_2332      =  1, 
	pMODE_2224      =  2, 
	pMODE_64        =  3, 
	pMODE_55        =  4,
	pMODE_32322     =  5, 
	pMODE_87        =  6,
	pMODE_11_2_3    =  7,
	pMODE_22        =8
} PfmdPulldownMode;

typedef struct
{
    PfmdSoftwareAPIParas      spPfmdSoftwareAPIParas;
    PfmdMaxPCCAndMode         spPfmdMaxPCCAndMode;
    PfmdInputParameters       spPfmdInputParas;
    PfmdPulldownMode          spPfmdPulldownMode; 
    
}PFMD_TotalSoftPara;  

typedef struct
{
     HI_S32 iFinalModeLocked ;//多实例y00220178
     HI_S32 iFrameNum ;//多实例y00220178
}PFMD_TotalStaticPara;



typedef struct 
{	
    //HI_U32	u32Stt_w_addr;//统计信息回写起始地址
    HI_U32  u32HandleNo;
	HI_U32  u32WidthY;
	HI_U32  u32HeightY;
	S_VPSSWB_REGS_TYPE *pstIfmdHardOutReg;//读取pfmd的状态寄存器
}PQ_PFMD_CALC_S;

/******************************************
 \brief 初始化PFMD参数
 \attention \n

 \param[in] PFMD初始化参数配置

 \retval ::HI_SUCCESS

 */

HI_S32 PQ_MNG_InitPfmd(HI_VOID);


HI_S32 PQ_MNG_PFMD_SoftwareParaInitByHandleNo(HI_U32 u32HandleNo);
HI_S32  PQ_MNG_PFMD_SoftwareParaInit(HI_VOID);

/**
 \brief 初始化IFMD模块的硬件相关参数
 \attention \n

 \param[in] pstIFmdParameter, IFMD硬件初始化参数

 \retval ::HI_SUCCESS

 */
HI_S32 PQ_MNG_PFMD_HardwareParaInit(HI_VOID);

HI_VOID SoftwareInit(PfmdSoftwareAPIParas *spPfmdSoftwareAPIParas);

HI_VOID InitPfmdPulldownDetectorStatus(PfmdPulldownDetectorStatus* spPfmdPdDetectorStatus);
/*****************************************************************************
 函 数 名  : Optm_PFMDAlg_GetPlayBackConfig
 功能描述  : API的总入口，用于根据检测和回放延时来获取新的回放配置参数
 输入参数  :            
 返 回 值  : 
 输出参数  : 无
 返 回 值  : 
 调用函数  :
 被调函数  :

*****************************************************************************/
//HI_VOID Optm_PFMDAlg_GetPlayBackConfig
//(PFMD_TotalSoftPara* pPfmdTotalSoftPara, HardwareAPIParas* pPfmdTotalHardPara)
HI_VOID Optm_PFMDAlg_GetPlayBackConfig(PfmdHardwareAPIParas* pPfmdTotalHardPara,PQ_PFMD_CALC_S *pstPfmdCalc,PFMD_PLAYBACK_S *pstPfmdResult);
HI_VOID CalcuCombVary(HI_S32 iFrameNum,PfmdHardwareAPIParas  *HardwareParas,PfmdSoftwareAPIParas *SoftwareParas);
HI_VOID CombParas(PfmdHardwareAPIParas *HardwareParas,PfmdSoftwareAPIParas *SoftwareParas,HI_S32 iFrameNum, PfmdInputParameters *sInput);
HI_VOID CalcuMonotony(HI_S32 iFrameNum,PfmdHardwareAPIParas *HardwareParas,PfmdSoftwareAPIParas *SoftwareParas);
HI_S32 CheckVary(HI_S32 *pSigma, HI_S32 sigmaBuffIdx, HI_S32 buffSize,HI_S32 SIGMA_CHANGE_MULTIPLE_THRED);
HI_S32 GetThrend(HI_S32 * iCombDiff,HI_S32 Mode, PfmdSoftwareAPIParas  *SoftwareParas,HI_S32 iFrameNum);
HI_S32 DetectPfmdPdModePhase(HI_S32 iFrameNum, PfmdHardwareAPIParas * HardwareParas, HI_S32 iModeLocked,  PfmdSoftwareAPIParas * sSoftwareAPIParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_VOID StillSceneDetection(HI_S32 iFrameNum, PfmdHardwareAPIParas * HardwareParas, PfmdSoftwareAPIParas *SoftwareParas);
HI_S32 PulldownDetection32(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection2332(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection2224(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection64(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection55(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection32322(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection87(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection11_2_3(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);
HI_S32 PulldownDetection22(HI_S32 iFrameNum, PfmdHardwareAPIParas *HardwareParas, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, PfmdSoftwareAPIParas *SoftwareParas,PfmdMaxPCCAndMode* spMaxPCCAndMode);

HI_S32 CheckSigmaAndCombCadence(HI_S32 iCurrCadenceMode, HI_S32 iFrameNum, PfmdHardwareAPIParas * HardwareParas,
	PfmdPulldownDetectorStatus *sPulldownDetectorStatus,PfmdSoftwareAPIParas *sSoftwareAPIParas,HI_S32 iTotalPhase,const HI_S32 *iCadence,PfmdMaxPCCAndMode* spMaxPCCAndMode);

HI_S32 PfmdCalcPCCLinearComp(HI_S32 iCurrCadenceMode,const HI_S32* pRef, HI_S32 *pToBeCompare, HI_S32 iRefStartPos, HI_S32 iToBeComStartPos, HI_S32 iLengthRef, HI_S32 iLengthToBeComp);

HI_VOID PfmdAdjustModeCounters(HI_S32 *pModeCounters, HI_S32 numTotalModes, HI_S32 lockedMode, HI_S32 lastTrend,HI_S32 currTrend, HI_S32 MaxPCCLargeEnough, HI_S32 * pUnlockCounter, HI_S32 iSubtitle,HI_S32 PMODE_UP_BOUND,HI_S32 PMODE_DOWN_BOUND);

HI_S32 CheckSubtitle(HI_S32 iFrameNum, PfmdHardwareAPIParas  *HardwareParas,PfmdSoftwareAPIParas  *SoftwareParas, HI_S32 iPeriod);

HI_S32 PfmdLockerScheme(PfmdPulldownDetectorStatus *sPulldownDetectorStatus, HI_S32 iLockThresh,HI_S32 iUnLockThresh, HI_S32 iCurrCadenceMode, HI_S32 numTotalModes,PfmdHardwareAPIParas *HardwareParas, PfmdSoftwareAPIParas * SoftwareParas);

HI_S32 GetFinalLockMode(HI_S32 iFrameNum,HI_S32 iModeLocked, PfmdPulldownDetectorStatus *sPulldownDetectorStatus, HI_S32 *iModeDecisionFrame,PfmdSoftwareAPIParas *SoftwareParas);
HI_S32 PfmdCheckSCD(HI_S32 FrameNum,PfmdHardwareAPIParas *HardwareParas,PfmdSoftwareAPIParas *pSoftwareAPIParas,HI_S32 LockedMode);
HI_S32 GetKeyFrameState(HI_S32 iFinal_mode, HI_S32 iDelay, HI_S32 iFrameNum);
HI_VOID SoftwareDeInit(PfmdSoftwareAPIParas *spPfmdSoftwareAPIParas);

/******************************************
 \brief 去初始化PFMD参数
 \attention \n


 \param[in] none

 \retval ::HI_SUCCESS

 *****************************************/
HI_S32 PQ_MNG_DeInitPFmd(HI_VOID);


/**
 \brief 开关PFMD模块
 \attention \n


 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
//HI_S32 PQ_MNG_EnablePFmd(HI_U8 u8HandleNo, HI_BOOL bOnOff);

/**
 \brief 开关FMD 的debug模块
 \attention \n


 \param[in] bOnOff

 \retval ::HI_SUCCESS

 */
//HI_S32 PQ_MNG_EnablePFMDDebug(HI_U8 u8HandleNo, HI_BOOL bOnOff);

/**
 \brief 输出检测到电影模式的类型
 \attention \n


 \param[in] none

 \retval ::filmtype

 */
//HI_S32 PQ_MNG_GetPFMDType();


/**
 \brief 输出当前帧是否为关键帧
 \attention \n


 \param[in] none

 \retval :: HI_TRUE

 */
//HI_BOOL PQ_MNG_IsKeyPFMDFrame();




 

#ifdef __cplusplus
 #if __cplusplus
}
 #endif
#endif /* __cplusplus */

#endif


