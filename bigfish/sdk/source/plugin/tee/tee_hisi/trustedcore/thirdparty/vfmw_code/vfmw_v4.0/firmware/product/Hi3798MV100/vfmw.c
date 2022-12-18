/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:64z4jYnYa5t1KtRL8a/vnMxg4uGttU/wzF06xcyNtiEfsIe4UpyXkUSy93j7U7XZDdqx2rNx
p+25Dla32ZW7opllls6N4+3ndAUojS6eCHJa9l6FKEwvAJc6HyzW+LkPf+EbPkekD0NWfuag
+pY0jNPRIPsm2poAF0GeTZLqExAttPYe9cP8XwsHyRw+lxld1gMbceAQeQQmtCSeiyqN0GQY
2+N2c3F616u78Hg1EmgZPyvfHx9b/uuHkSoeUprTEiXUhJwpuAwuwPdp/nHBIw==*/
/*--------------------------------------------------------------------------------------------------------------------------*/

/******************************************************************************

  ��Ȩ���� (C), 2001-2011, ��Ϊ�������޹�˾

******************************************************************************
    �� �� ��   : vdec_firmware.c
    �� �� ��   : ����
    ��    ��   :
    ��������   :
    ����޸�   :
    ��������   : firmware�Ķ���ӿ�ʵ��


 �޸���ʷ   :
    1.��    �� : 2009-01-08
    ��    ��   : z56361
    �޸�����   :

******************************************************************************/
#include "vfmw_trust_intf.h"
#include "vfmw.h"
#ifdef VFMW_VC1_SUPPORT
#include "vc1.h"
#endif
#include "vdm_hal.h"
#ifdef VFMW_VDH_V100_SUPPORT
#include "vdm_hal_v100_api.h"
#endif
#ifdef VFMW_VDH_V300R001_SUPPORT
#include "vdm_hal_v300r001_api.h"
#endif
#ifdef VFMW_VC1_SUPPORT
#include "bitplane.h"
#endif
#include "mem_manage.h"
#include "public.h"
#ifdef VFMW_FOD_SUPPORT
#include "fod_drv.h"
#endif
#include "vfmw_ctrl.h"
#include "syntax.h"
#include "vfmw_osal.h"

#ifdef VFMW_DNR_SUPPORT
#include "dnr_hal.h"
#include "dnr_offline.h"
#endif
#ifdef VFMW_BTL_SUPPORT
#include "btl_hal_v100.h"
#include "btl_drv.h"
#endif

#include <sre_debug.h>


#include "hi_reg_common.h"

#define  IO_ADDRESS(x)         (x)
volatile HI_REG_CRG_S       *g_pstRegCrg        = (HI_REG_CRG_S*)IO_ADDRESS(HI_CRG_BASE_ADDR);

/*======================================================================*/
/*   ��                                                                 */
/*======================================================================*/
#define  VDEC_ASSERT_RET( cond, else_print )                    \
do {                                                            \
    if( !(cond) )                                               \
    {                                                           \
        dprint(PRN_FATAL,"vfmw.c,L%d: %s\n", __LINE__, else_print ); \
        return VDEC_ERR;                                        \
    }                                                           \
}while(0)

#define  VDEC_ASSERT( cond, else_print )                        \
do {                                                            \
    if( !(cond) )                                               \
    {                                                           \
        dprint(PRN_FATAL,"vfmw.c,L%d: %s\n", __LINE__, else_print ); \
        return;                                                 \
    }                                                           \
}while(0)

/*======================================================================*/
/*   ȫ�ֹ�������                                                       */
/*======================================================================*/
extern OSAL_IRQ_SPIN_LOCK g_TaskLock;
extern OSAL_IRQ_SPIN_LOCK g_SpinLock;
extern OSAL_IRQ_SPIN_LOCK g_SpinLock_fsp;
extern OSAL_IRQ_SPIN_LOCK g_SpinLockIrq_Destroy;
extern OSAL_IRQ_SPIN_LOCK g_ActivateLock;
#if defined(VFMW_DNR_SUPPORT) || defined(VFMW_BTL_SUPPORT)
extern OSAL_IRQ_SPIN_LOCK g_SpinLockIsr_Image2D;
#endif

//extern SINT32  g_SleepTime;

#ifdef ENV_SOS_KERNEL
/* SECURE MARK */
extern RAW_ARRAY_NS *g_pStreamList;
extern CALLBACK_ARRAY_NS *g_pCallBackList;
#endif

SINT32 g_VfmwEnableFlag = 0;
SINT32 g_VfmwInitCount = 0;
SINT32 g_chipID = VFMW_CHIP_TYPE_Hi3716L;
SINT32 g_ChipMaxWidth = 8192;   // chip support max width   //y00226912
SINT32 g_ChipMaxHeight = 8192;  // chip support max height
VDMHAL_FUN_PTR_S g_vdm_hal_fun_ptr = {0}; 
#ifdef VFMW_DNR_SUPPORT    
DNRHAL_FUN_PTR_S g_dnr_hal_fun_ptr = {0};
#endif
#ifdef VFMW_BTL_SUPPORT
BTLHAL_FUN_PTR_S g_btl_hal_fun_ptr = {0};
#endif
SINT32 g_FrameRate[MAX_CHAN_NUM]={30}; 
SINT32 g_LastFrameRate[MAX_CHAN_NUM]={30}; 

#ifdef VFMW_MODULE_LOWDLY_SUPPORT
UINT8 g_LowDelayCalcStat[MAX_CHAN_NUM]={0}; 
SINT32 g_LowDelayCalcHandle[MAX_CHAN_NUM]={0}; 
UINT32 g_LowDelaySeqIndex[MAX_CHAN_NUM]={0};
#endif


/*======================================================================*/
/*   ���ú�������                                                       */
/*======================================================================*/
VOID  GetVdecCapability( VDEC_CAP_S *pCap );
//SINT32 GetVdecChipType(UINT32 *ChipType);


/*======================================================================*/
/*   ����ʵ��                                                           */
/*======================================================================*/
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
/************************************************************************
    ��/�˳�VDEC���: ��insmod/rmmodʱ�������º�����
    ��Ҫְ���Ǵ���/����proc�ļ�ϵͳ
 ************************************************************************/
VOID VDEC_Lowdelay_Event_Time(SINT32 ChanId,HI_LD_Event_ID_E eventId, HI_U32 u32FrameId)
{
    HI_LD_Event_S evt;
    HI_U32 TmpTime = 0;    
	HI_DRV_SYS_GetTimeStampMs(&TmpTime);
    
    evt.evt_id = eventId;
    evt.frame = u32FrameId;
    evt.handle = g_LowDelayCalcHandle[ChanId];
    evt.time = TmpTime; 
    if(1==g_LowDelayCalcStat[ChanId])
    {    
        HI_DRV_LD_Notify_Event(&evt);
    }
}
#endif

VOID VDEC_OpenModule(VOID)
{
    OSAL_SEMA_INTIT();

#ifdef ENV_ARMLINUX_KERNEL
    vfmw_proc_init();
#endif
}

VOID VDEC_ExitModule(VOID)
{
#ifdef ENV_ARMLINUX_KERNEL
    vfmw_proc_exit();
#endif
}

VOID VDM_ResetClock(VOID)
{
	U_PERI_CRG30 u32TmpValue;
	u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
    u32TmpValue.bits.vdhclk_skipcfg = 0;
    
    /*ʹ�ܿ�����Ĳ�����Ҫ�������ʱ���λҪ����0����1*/
    u32TmpValue.bits.vdhclk_loaden = 0x0;
    g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;
    u32TmpValue.bits.vdhclk_loaden = 0x1;
    g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32; 

	return;
}

VOID VDM_OpenHardware(SINT32 VdhId)
{
	U_PERI_CRG30 u32TmpValue;
	u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
    u32TmpValue.bits.vdh_cken = 0x1;
	u32TmpValue.bits.vdhdsp_cken = 0x1;
	u32TmpValue.bits.vdh_all_srst_req = 0x0;
	u32TmpValue.bits.vdh_mfd_srst_req = 0x0;
	u32TmpValue.bits.vdh_clk_sel = 0x0;
	g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

    VDM_ResetClock();

	return;
}

VOID VDM_CloseHardware(SINT32 VdhId)
{
    U_PERI_CRG30 u32TmpValue;
	u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
    u32TmpValue.bits.vdh_all_srst_req = 0x1;
	u32TmpValue.bits.vdh_mfd_srst_req = 0x1;
	u32TmpValue.bits.vdh_cken = 0x0;
	u32TmpValue.bits.vdhdsp_cken = 0x0; 
	g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

	return;  
}

VOID SCD_OpenHardware(VOID)
{
	U_PERI_CRG30 u32TmpValue;
	u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
    u32TmpValue.bits.vdh_scd_srst_req = 0x0;
	g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;

    return;
}

VOID SCD_CloseHardware(VOID)
{
   	U_PERI_CRG30 u32TmpValue;
	u32TmpValue.u32 = g_pstRegCrg->PERI_CRG30.u32;
    u32TmpValue.bits.vdh_scd_srst_req = 0x1;
	g_pstRegCrg->PERI_CRG30.u32 = u32TmpValue.u32;
    return;
}

#ifdef VFMW_DNR_SUPPORT    
VOID DNR_OpenHardware(VOID)
{
    /*X6V300������DNRģ��*/
    return;
}
#endif

#ifdef VFMW_BTL_SUPPORT
VOID BTL_OpenHardware(VOID)
{
    UINT32  *p32 = (UINT32 *)MEM_Phy2Vir(BTL_RESET_REG_PHY_ADDR);
    if( NULL != p32)
    {
    #if 0
        /* ��ʱ��ʼ�� */
        p32[0] |= 0x100;   // PERI_CRG8[8:8] = btl_clken
        /* ������λ�ź� */
        p32[0] &= (~1);    // PERI_CRG8[0:0] = btl_srst_req
	#endif
	   p32[0] |= 0x1;   
        /* ������λ�ź� */
        p32[0] &= (~0x10);
    }
    return;
}

VOID BTL_CloseHardware(VOID)
{
    UINT32  *p32 = (UINT32 *)MEM_Phy2Vir(BTL_RESET_REG_PHY_ADDR);
    if( NULL != p32)
    {
       /* ������λ�ź� */
       p32[0] |= 0x10;
	   /*�ر�ʼ��*/
	   p32[0] &= (~0x1);   

    }
    return;
}
#endif

SINT32 BPD_OpenHardware(VOID)
{
	U_PERI_CRG34 u32TmpValue;
	u32TmpValue.u32 = g_pstRegCrg->PERI_CRG34.u32;
    u32TmpValue.bits.bpd_cken = 0x1;
	u32TmpValue.bits.bpd_srst_req = 0x0;
	g_pstRegCrg->PERI_CRG34.u32 = u32TmpValue.u32;

    return VCTRL_OK;
}

/************************************************************************
    VDEC ��VFMW���е������г�ʼ��
 ************************************************************************/
VOID VDEC_SpinLockInit(VOID)
{

    OSAL_SpinLockIRQInit(&g_TaskLock);
    OSAL_SpinLockIRQInit(&g_RecordLock);
    OSAL_SpinLockIRQInit(&g_SpinLock);
    OSAL_SpinLockIRQInit(&g_SpinLock_fsp);
    OSAL_SpinLockIRQInit(&g_SpinLockIrq_Destroy);
    OSAL_SpinLockIRQInit(&g_ActivateLock);
#if defined(VFMW_DNR_SUPPORT) || defined(VFMW_BTL_SUPPORT)
    OSAL_SpinLockIRQInit(&g_SpinLockIsr_Image2D);
#endif

    return;
}


/************************************************************************
    VDECȫ�ֳ�ʼ�����ϲ���ô˺���ʹVDEC�ص���ʼ״̬��ͬʱע��ص�����.
    VdecCallback: ���������Ӵ˴��ݻص�������VDEC
 ************************************************************************/
SINT32 VDEC_Init( SINT32 (*VdecCallback)( SINT32 ChanID, SINT32 eEventID, VOID *pArgs ) )
{
    SINT32 ret;
	VDEC_OPERATION_S Args;

	memset(&Args,0,sizeof(VDEC_OPERATION_S));

	/* ��׼���� */
	Args.VdecCallback = VdecCallback;
	Args.mem_malloc = NULL;
	Args.mem_free = NULL;

	ret = VDEC_InitWithOperation(&Args);
                
    return  (ret == VCTRL_OK)? VDEC_OK : VDEC_ERR;
}

SINT32 VDEC_InitWithOperation(VDEC_OPERATION_S *pArgs)
{
    SINT32 ret;
//  UINT32 *pChipIDReg;

    uart_printf("==  VDEC_InitWithOperation INTER == !!!\n");

    OSAL_DOWN_INTERRUPTIBLE();

    if (NULL == pArgs)
    {
        OSAL_UP();
        dprint(PRN_ERROR, "VDEC_InitWithOperation has NULL parameter, error!\n");
        return VDEC_ERR;
    }

    /* ����: mem_malloc & mem_free���������ÿ�����Ч*/
    /* ��ΪOMX ��VDEC ����ͬʱ���棬����һ����ʼ������һ��ֱ�ӷ���OK������ᱨ��ʼ��ʧ�� y00226912 */
    if (1 == g_VfmwEnableFlag)
    {
        g_VfmwInitCount++;
        ret = VCTRL_OK;
        goto Exit;
    }
	
#ifdef ENV_SOS_KERNEL
    g_pstRegCrg = (HI_REG_CRG_S *)OSAL_IO_ADDRESS(SYSTEM_REG_PHY_ADDR);//add sec mode z00241305

    /* SECURE MARK */  
    //dprint(PRN_ERROR, "CallBack: Phy=0x%x, Size=0x%x\n", (UINT32)pArgs->VdecCallback, sizeof(CALLBACK_ARRAY_NS));  
    dprint(PRN_ERROR, "SOS: eAdapterType=%d, VdecCallback=%p\n", pArgs->eAdapterType, pArgs->VdecCallback);
    g_pCallBackList = (CALLBACK_ARRAY_NS *)OSAL_Map_To_Ns((UINT32)pArgs->VdecCallback, sizeof(CALLBACK_ARRAY_NS), 1);
    if (VDEC_ERR == g_pCallBackList)
    {
        dprint(PRN_ERROR, "Map g_pCallBackList Failed!\n");
        return VDEC_ERR;
    }
#endif	

    memset(&g_TaskLock, 0, sizeof(OSAL_IRQ_SPIN_LOCK));
    memset(&g_RecordLock, 0, sizeof(OSAL_IRQ_SPIN_LOCK));
    memset(&g_SpinLock, 0, sizeof(OSAL_IRQ_SPIN_LOCK));
    memset(&g_SpinLock_fsp, 0, sizeof(OSAL_IRQ_SPIN_LOCK)); 
    memset(&g_SpinLockIrq_Destroy, 0, sizeof(OSAL_IRQ_SPIN_LOCK));
    memset(&g_ActivateLock, 0, sizeof(OSAL_IRQ_SPIN_LOCK));
#if defined(VFMW_DNR_SUPPORT) || defined(VFMW_BTL_SUPPORT)
    memset(&g_SpinLockIsr_Image2D, 0, sizeof(OSAL_IRQ_SPIN_LOCK));  
#endif

	AcceleratorCharacter = NULL;

    g_chipID = VFMW_CHIP_TYPE_Hi3798MV100;

    switch(g_chipID)
	{
        case VFMW_CHIP_TYPE_Hi3798MV100:	        
            g_vdm_hal_fun_ptr.pfun_VDMDRV_OpenHardware           = VDM_OpenHardware;
            g_vdm_hal_fun_ptr.pfun_VDMDRV_CloseHardware          = VDM_CloseHardware;
            g_vdm_hal_fun_ptr.pfun_SCDDRV_OpenHardware           = SCD_OpenHardware;
            g_vdm_hal_fun_ptr.pfun_SCDDRV_CloseHardware          = SCD_CloseHardware;
            g_vdm_hal_fun_ptr.pfun_BPDDRV_OpenHardware           = BPD_OpenHardware;
        
        #ifdef VFMW_VDH_V300R001_SUPPORT
            g_vdm_hal_fun_ptr.pfun_VDMHAL_GetHalMemSize          = VDMHAL_V300R001_GetHalMemSize;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_OpenHAL                = VDMHAL_V300R001_OpenHAL;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_CloseHAL               = VDMHAL_V300R001_CloseHAL;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem             = VDMHAL_V300R001_ArrangeMem;
			g_vdm_hal_fun_ptr.pfun_VDMHAL_ArrangeMem_BTL         = VDMHAL_V300R001_ArrangeMem_BTL;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_ResetVdm               = VDMHAL_V300R001_ResetVdm;
		  #ifdef VFMW_BVT_SUPPORT
			g_vdm_hal_fun_ptr.pfun_VDMHAL_GlbReset               = VDMHAL_V300R001_ResetGlb;
		  #else
            g_vdm_hal_fun_ptr.pfun_VDMHAL_GlbReset               = VDMHAL_V300R001_GlbReset;
		  #endif
            g_vdm_hal_fun_ptr.pfun_VDMHAL_ClearIntState          = VDMHAL_V300R001_ClearIntState;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_MaskInt                = VDMHAL_V300R001_MaskInt;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_EnableInt              = VDMHAL_V300R001_EnableInt;	
            g_vdm_hal_fun_ptr.pfun_VDMHAL_CheckReg               = VDMHAL_V300R001_CheckReg;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwRepair          = VDMHAL_V300R001_StartHwRepair;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_StartHwDecode          = VDMHAL_V300R001_StartHwDecode;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareDec             = VDMHAL_V300R001_PrepareDec;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmReady             = VDMHAL_V300R001_IsVdmReady;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_IsVdmRun               = VDMHAL_V300R001_IsVdmRun;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_PrepareRepair          = VDMHAL_V300R001_PrepareRepair;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_MakeDecReport          = VDMHAL_V300R001_MakeDecReport;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_BackupInfo             = VDMHAL_V300R001_BackupInfo;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_GetCharacter           = VDMHAL_V300R001_GetCharacter;
            g_vdm_hal_fun_ptr.pfun_VDMHAL_Write1DYuv             = VDMHAL_V300R001_WriteBigTitle1DYuv;
		#endif
            break;
            
        default:
            OSAL_UP();
            dprint(PRN_ALWS,"g_chipID = %d is not support!\n",g_chipID);
            return VDEC_ERR;
            break;
    }

    // �������г�ʼ��
    VDEC_SpinLockInit();

    VDMHAL_GetCharacter();
	MEM_ManagerWithOperation(pArgs);
	ret = VCTRL_OpenVfmw();
	dprint(PRN_CTRL, "VCTRL_OpenVfmw() return %d\n", ret);
    if (ret == VCTRL_OK)
    {
        g_VfmwEnableFlag = 1;
        g_VfmwInitCount = 1;
    }
    else
    {
        g_VfmwEnableFlag = 0;
        g_VfmwInitCount = 0;
    }
	    /* ȫ�ָ�λ */
    VDMHAL_GlbReset();

Exit:
    VCTRL_SetCallBack(pArgs->eAdapterType, pArgs->VdecCallback);
    OSAL_UP();
    return  (ret == VCTRL_OK)? VDEC_OK : VDEC_ERR;
}
/************************************************************************
    VDECȫ��ȥ��ʼ�����ϲ���ô˺���ʹVDEC�ر�����Ӳ�����٣��ͷ�������Դ
 ************************************************************************/
SINT32 VDEC_Exit( VOID )
{
    SINT32 ret;
    ret = OSAL_DOWN_INTERRUPTIBLE();

    /* ��ΪOMX ��VDEC ����ͬʱ���棬������һ���������ȫ��ȥ��ʼ�� y00226912 */
    g_VfmwInitCount--;        
    if (g_VfmwInitCount > 0)
    {
        OSAL_UP();
        return VCTRL_OK;
    }
    
    ret = VCTRL_CloseVfmw();
    MEM_ManagerClearOperation();

    g_VfmwEnableFlag = 0;
	
    OSAL_UP();
    return  (ret == VCTRL_OK)? VDEC_OK : VDEC_ERR;
}

/************************************************************************
    VDEC��������
    ChanID:  ��Ҫ������ͨ����(����ͨ���޹ز������˲�����Ϊ����ֵ)
    eCmdID:  ������룬ָ����ҪVDECִ�к��ֶ���
    pArgs:   ������������ʽ��eCmdID���
 ************************************************************************/
SINT32 VDEC_Control( SINT32 ChanID, VDEC_CID_E eCmdID, VOID *pArgs )
{
    SINT32 ret=VDEC_OK;
    IMAGE_INTF_S *pImgIntf;
    SINT32 VdmMem[3], ScdMem[3];
	SINT32 *p32 = NULL;
	UINT64 *p64 = NULL;
    DETAIL_MEM_SIZE DetailMemSize;
    SINT32 TaskLockFlag = 0;
    SINT32 s32Loop = 500;
    UINT32 MapPhy;

//    UINT32 *pu32 = NULL;
    //OSAL_SpinLock(&g_TaskLock);

    if (g_VfmwEnableFlag != 1)
    {
        dprint(PRN_FATAL, "VFMW has been destroyed, so any operation is unuseful!\n");
        return VDEC_ERR;
    }
    switch(eCmdID)
    {
    case VDEC_CID_GET_GLOBAL_STATE: /* ��ȡȫ��״̬��Ϣ */
        break;

    case VDEC_CID_GET_CAPABILITY:   /* ��ȡ���������� */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;

    case VDEC_CID_GET_GLOBAL_CFG:   /* ��ȡȫ��������Ϣ */
        break;

    case VDEC_CID_CFG_DECODER:      /* ����ȫ�ֽ����� */
        break;

    case VDEC_CID_CFG_EXTRA:      /* ���ý����� extra_ref & extra_disp */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL, "vfmw.c, L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;
		
    case VDEC_CID_CREATE_CHAN:      /* ����ͨ�� */
        
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		else
		{
            p32 = (SINT32*)pArgs;
			if (p32[0] > CAP_LEVEL_BUTT)
			{
			    dprint(PRN_FATAL,"vfmw.c,L%d: capability level out of range\n", __LINE__);
				TaskLockFlag = 1;
			}
		}
        break;
    case VDEC_CID_CREATE_CHAN_WITH_OPTION:  /* �����ض���С�Ľ���ͨ�� */        
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
            TaskLockFlag = 1;
        }
        else
        {
            p32 = (SINT32*)pArgs;
            if (p32[0] > CAP_LEVEL_BUTT)
            {
                dprint(PRN_FATAL,"vfmw.c,L%d: capability level out of range\n", __LINE__);
                TaskLockFlag = 1;
            }
        }
        break;
        
    case VDEC_CID_DESTROY_CHAN:     /* ����ͨ�� */
        break;

    case VDEC_CID_DESTROY_CHAN_WITH_OPTION:     /* ����ͨ������Դ�ⲿ�ͷ� */
        break;
        
    case VDEC_CID_GET_CHAN_CFG:     /* ��ȡͨ������ */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;

    case VDEC_CID_CFG_CHAN:         /* ����ͨ�� */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;

    case VDEC_CID_GET_CHAN_STATE:   /* ��ȡͨ��״̬��Ϣ */
        break;
#if 0
	case VDEC_CID_GET_CHAN_FRMSTATE:/*��ȡ֡��״̬*/
        break;
#endif
    case VDEC_CID_START_CHAN:       /* ����ͨ�� */
        break;
    case VDEC_CID_START_CHAN_WITH_OPTION:       /* ����ͨ�� */
        break;
    case VDEC_CID_STOP_CHAN:        /* ֹͣͨ�� */
        break;

    case VDEC_CID_RESET_CHAN:       /* ��λͨ�� */
        break;

    case VDEC_CID_RELEASE_STREAM:        /* �ͷ�raw buffer */
        break;

    case VDEC_CID_SET_STREAM_INTF:  /* ����ͨ���������ӿ� */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;

    case VDEC_CID_GET_IMAGE_INTF:   /* ��ȡͨ����ͼ��ӿ� */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;
    case VDEC_CID_GET_STREAM_SIZE:     /* ��ȡͨ����VDH����������(byte) */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;
		
    case VDEC_CID_GET_CHAN_MEMSIZE:    /* ��ȡͨ�����ض�������������Ҫռ�õ��ڴ����� */
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;
    case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
            TaskLockFlag = 1;
        }
        break;
           
    case VDEC_CID_GET_CHAN_MEMADDR:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;		

    case VDEC_CID_GET_CHAN_ID_BY_MEM:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
		break;
		
    //add by z00222166, 2012.11.20
    case VDEC_CID_SET_DISCARDPICS_PARAM:   /*��ȡ��֡����ز���*/
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }

	break;
	
    case VDEC_CID_SET_DBG_OPTION:   /* ���õ���ѡ�� */
        break;

    case VDEC_CID_GET_DGB_OPTION:   /* ��ȡ����ѡ�� */
        break;
    /* ���������������STD_USERͨ���²ſ���ʹ�� */
    case VDEC_CID_GET_USRDEC_FRAME:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;

    case VDEC_CID_PUT_USRDEC_FRAME:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;
    case VDEC_CID_SET_PTS_TO_SEEK:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;
    case VDEC_CID_SET_TRICK_MODE:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;
    case VDEC_CID_SET_CTRL_INFO:
        if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;
    case VDEC_CID_RESET_CHAN_WITH_OPTION:       /* ��λͨ����ѡ��ر���ĳЩͨ������ */
        break;
	case VDEC_CID_FRAME_BTL:
		if ( NULL == pArgs )
        {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
        }
        break;
    case VDEC_CID_SET_FRAME_RATE:
       if ( NULL == pArgs )
       {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
       }
       break;
   case VDEC_CID_START_LOWDLAY_CALC:
       if ( NULL == pArgs )
       {
            dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
			TaskLockFlag = 1;
       }
       break;
   case VDEC_CID_STOP_LOWDLAY_CALC:
       if ( NULL == pArgs )
       {
           dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
		   TaskLockFlag = 1;
       }
       break;
   case VDEC_CID_ALLOC_MEM_TO_CHANNEL: //l00273086
    {
        if ( NULL == pArgs )
        {
           dprint(PRN_FATAL,"vfmw.c,L%d: pArgs is NULL!\n", __LINE__); 
           TaskLockFlag = 1;
        }
        break;
    }
#if 0        
    case VDEC_CID_OPEN_RAWBUF:
    case VDEC_CID_OPEN_MOUNT_RAWBUF:
    case VDEC_CID_CLOSE_RAWBUF:
    case VDEC_CID_MOUNT_RAWBUF:
    case VDEC_CID_UNMOUNT_RAWBUF:
    case VDEC_CID_RESET_RAWBUF:
    case VDEC_CID_GET_STREAM_BUF:
    case VDEC_CID_PUT_STREAM_BUF:

    case VDEC_CID_GET_CHIP_TYPE:
    case VDEC_CID_SLEEP_TIME:        
        
        break;
#endif                
       default:
           TaskLockFlag = 1;
    }
   
	if (1 == TaskLockFlag)
    {
        return VDEC_ERR; 
    }
	
    switch(eCmdID)
    {
    case VDEC_CID_GET_GLOBAL_STATE: /* ��ȡȫ��״̬��Ϣ */
        break;

    case VDEC_CID_GET_CAPABILITY:   /* ��ȡ���������� */
        OSAL_SpinLockIRQ(&g_TaskLock);
        GetVdecCapability((VDEC_CAP_S*)pArgs);
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;

    case VDEC_CID_GET_GLOBAL_CFG:   /* ��ȡȫ��������Ϣ */
        break;

    case VDEC_CID_CFG_DECODER:      /* ����ȫ�ֽ����� */
        break;
		
    case VDEC_CID_CFG_EXTRA:      /* ���ý����� extra_ref & extra_disp */
        OSAL_SpinLockIRQ(&g_TaskLock);
        p32 = (SINT32*)pArgs;
        VCTRL_SetVdecExtra(p32[0], p32[1]);
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
		
    case VDEC_CID_CREATE_CHAN:      /* ����ͨ�� */
        p32 = (SINT32*)pArgs;
        ret = VCTRL_CreateChan(p32[0], (MEM_DESC_S*)(&p32[1]));
        dprint(PRN_CTRL, "VCTRL_CreateChan() return %d\n", ret);
        p32[0] = ret;  /* ע�⣬��������pArgs�ȴ����������(������),�ִ����������(ͨ����) */
        ret = (ret>=0)? VDEC_OK: VDEC_ERR;
        break;
        
    case VDEC_CID_CREATE_CHAN_WITH_OPTION:  /* �����ض���С�Ľ���ͨ�� */  
	#ifdef ENV_SOS_KERNEL            
	    p32 = (SINT32*)pArgs;
        MapPhy = (UINT32)(p32[1]);
        //dprint(PRN_ERROR, "Option: Phy=0x%x, Size=0x%x\n", MapPhy, sizeof(VDEC_CHAN_OPTION_S));
        if (VDEC_ERR != OSAL_Map_To_Ns(MapPhy, sizeof(VDEC_CHAN_OPTION_S), 1))
        {
            ret = VCTRL_CreateChanWithOption(p32[0], (VDEC_CHAN_OPTION_S*)(p32[1]), VCTRL_IGNOR_EXTRA, 0);
            p32[0] = ret;  /* ע�⣬��������pArgs�ȴ����������(������),�ִ����������(ͨ����) */   
            OSAL_UnMap_To_Ns(MapPhy, sizeof(VDEC_CHAN_OPTION_S), 1);
            ret = (ret>=0)? VDEC_OK: VDEC_ERR;
        }
        else
        {
            dprint(PRN_FATAL, "VDEC_CID_CREATE_CHAN_WITH_OPTION OSAL_Map_To_Ns Failed!\n");
            ret = VDEC_ERR;
        } 
	#else
        p32 = (SINT32*)pArgs;
        ret = VCTRL_CreateChanWithOption(p32[0], (VDEC_CHAN_OPTION_S*)(p32[1]), VCTRL_IGNOR_EXTRA, 0);
        p32[0] = ret;  /* ע�⣬��������pArgs�ȴ����������(������),�ִ����������(ͨ����) */
        ret = (ret>=0)? VDEC_OK: VDEC_ERR;
	#endif
        break;
    case VDEC_CID_DESTROY_CHAN:     /* ����ͨ�� */
	  #ifndef ENV_SOS_KERNEL
        while((VDEC_ERR == (VCTRT_SetChanCtrlState(ChanID, CHAN_DESTORY))) && (s32Loop != 0))
        {
            msleep(1);
            s32Loop--;
        }
        if(s32Loop <=0)
        {
            ret = VDEC_ERR;
            break;
        }
	  #endif
        ret = VCTRL_DestroyChan(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        break;

    case VDEC_CID_DESTROY_CHAN_WITH_OPTION:     /* ����ͨ������Դ�ⲿ�ͷ� */
      #ifndef ENV_SOS_KERNEL   //��ȫ��������������
        while((VDEC_ERR == (VCTRT_SetChanCtrlState(ChanID, CHAN_DESTORY))) && (s32Loop != 0))
        {
            msleep(1);
            s32Loop--;
        }
        if(s32Loop <= 0)
        {
            ret = VDEC_ERR;
            break;
        }
	  #endif
        ret = VCTRL_DestroyChanWithOption(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        break;
    case VDEC_CID_GET_CHAN_CFG:     /* ��ȡͨ������ */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_GetChanCfg(ChanID, (VDEC_CHAN_CFG_S*)pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);		
        break;

    case VDEC_CID_CFG_CHAN:         /* ����ͨ�� */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_ConfigChan(ChanID, (VDEC_CHAN_CFG_S*)pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        #if defined(VFMW_SCD_LOWDLY_SUPPORT) || defined(VFMW_AVSPLUS_SUPPORT)
        VCTRL_LoadDspCode(ChanID);
        #endif
				
        break;

    case VDEC_CID_GET_CHAN_STATE:   /* ��ȡͨ��״̬��Ϣ */
        OSAL_SpinLockIRQ(&g_TaskLock);
		VCTRL_GetChanState(ChanID, (VDEC_CHAN_STATE_S *)pArgs);
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
#if 0
	case VDEC_CID_GET_CHAN_FRMSTATE:/*��ȡ֡��״̬*/
		OSAL_SpinLockIRQ(&g_TaskLock);
		VCTRL_GetChanFrmState(ChanID, (VDEC_CHAN_FRMSTATUSINFO_S *)pArgs);
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
#endif
    case VDEC_CID_START_CHAN:       /* ����ͨ�� */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_StartChan(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);				
        break;
    case VDEC_CID_START_CHAN_WITH_OPTION:
		OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_StartChanWithOption(ChanID, (MEM_DESC_S*)pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
    case VDEC_CID_STOP_CHAN:        /* ֹͣͨ�� */
      #ifdef ENV_SOS_KERNEL   //��ȫ��������������
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_StopChan(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
	  #else
        ret = VCTRL_StopChanWithCheck(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
      #endif			
        break;

    case VDEC_CID_RESET_CHAN:       /* ��λͨ�� */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_ResetChan(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;

    case VDEC_CID_RELEASE_STREAM:       /* �ͷ�raw buffer */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_ReleaseStream(ChanID);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
        
    case VDEC_CID_SET_STREAM_INTF:  /* ����ͨ���������ӿ� */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_SetStreamInterface(ChanID, pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);		
		break;

    case VDEC_CID_GET_IMAGE_INTF:   /* ��ȡͨ����ͼ��ӿ� */
        OSAL_SpinLockIRQ(&g_TaskLock);
        pImgIntf = (IMAGE_INTF_S*)pArgs;
		pImgIntf->image_provider_inst_id = ChanID;

#if defined(OFF_LINE_DNR_ENABLE)
        pImgIntf->read_image = DNR_ReceiveImage;
        pImgIntf->release_image = DNR_ReleaseImage;
#elif defined(BTL_ENABLE)
        pImgIntf->read_image = BTL_ReceiveImage;
        pImgIntf->release_image = BTL_ReleaseImage; 
#else
        pImgIntf->read_image = VCTRL_GetChanImage;
        pImgIntf->release_image = VCTRL_ReleaseChanImage;
#endif	
        ret = VDEC_OK;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
    case VDEC_CID_GET_STREAM_SIZE:     /* ��ȡͨ����VDH����������(byte) */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_GetStreamSize(ChanID, (SINT32 *)pArgs);
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
		break;
    case VDEC_CID_GET_CHAN_MEMSIZE:    /* ��ȡͨ�����ض�������������Ҫռ�õ��ڴ����� */
        p32 = (SINT32*)pArgs;
        OSAL_SpinLockIRQ(&g_TaskLock);
        if ( VCTRL_OK == VCTRL_GetChanMemSize( p32[0], VdmMem, ScdMem) )
        {
            CHAN_MEM_BUDGET_S *pMem = (CHAN_MEM_BUDGET_S*)pArgs;
            pMem->MinMemSize    = VdmMem[0] + ScdMem[0];
            pMem->NormalMemSize = VdmMem[1] + ScdMem[1];
            pMem->FluentMemSize = VdmMem[2] + ScdMem[2];
            ret = VDEC_OK;
        }
        else
        {
            ret = VDEC_ERR;
        }
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
    case VDEC_CID_GET_CHAN_DETAIL_MEMSIZE_WITH_OPTION:
        p32 = (SINT32*)pArgs;
        OSAL_SpinLockIRQ(&g_TaskLock);
        MapPhy = (UINT32)(p32[1]);
        if (VDEC_ERR != OSAL_Map_To_Ns(MapPhy, sizeof(VDEC_CHAN_OPTION_S), 1))
        {
            if ( VCTRL_OK == VCTRL_GetChanMemSizeWithOption( p32[0], (VDEC_CHAN_OPTION_S *)p32[1], &DetailMemSize,VCTRL_ADD_EXTRA) )
            {
                p32[0] = DetailMemSize.VdhDetailMem;
                p32[1] = DetailMemSize.ScdDetailMem;
                p32[2] = DetailMemSize.ChanCtxDetailMem;            
                ret = VDEC_OK;
            }
            else
            {
                ret = VDEC_ERR;
            }
            VCTRL_EnableAllInt();
            OSAL_UnMap_To_Ns(MapPhy, sizeof(VDEC_CHAN_OPTION_S), 1);
        }
        else
        {
            ret = VDEC_ERR;
        }
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
        
    case VDEC_CID_GET_CHAN_MEMADDR:
        OSAL_SpinLockIRQ(&g_TaskLock);
        {
            MEM_RECORD_S MemRec;
            MEM_RECORD_S *pstMemRec = &MemRec;
            MEM_DESC_S *pMem;

            pMem = (MEM_DESC_S *)pArgs;

            ret = VCTRL_GetChanMemInfo(ChanID, pstMemRec);
            if (VCTRL_OK != ret)
            {
                ret = VDEC_ERR;
                VCTRL_EnableAllInt();
                OSAL_SpinUnLockIRQ(&g_TaskLock);				
                break;
            }

            pMem->PhyAddr = pstMemRec->PhyAddr;
            pMem->VirAddr = pstMemRec->VirAddr;
            pMem->Length = pstMemRec->Length;
            if ( (NULL==pMem->VirAddr) || (0==pMem->PhyAddr) )
            {
                ret = VDEC_ERR;
            }
            else
            {
                ret = VDEC_OK;
            }
        }
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);				
        break;
    case VDEC_CID_GET_CHAN_ID_BY_MEM:
        OSAL_SpinLockIRQ(&g_TaskLock);
        p32 = (SINT32*)pArgs;
		p32[0] = VCTRL_GetChanIDByMemAddr(p32[0]);
		ret = (-1 != p32[0])? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
		break;
#if 0
    case VDEC_CID_OPEN_RAWBUF:           /* ��ָ��ͨ���ϴ�raw buf */
        OSAL_SpinLock(&g_TaskLock);
        p32 = (SINT32*)pArgs;
        ret = VCTRL_OpenRawBuf(ChanID, p32[0]);
		ret = (VCTRL_OK == ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;

    case VDEC_CID_OPEN_MOUNT_RAWBUF:    /* ��ָ��ͨ���ϴ�raw buf, ������raw buf��װ��ͨ��(ʹ��"��"ģʽ������) */
        OSAL_SpinLock(&g_TaskLock);
        p32 = (SINT32*)pArgs;
        ret = VCTRL_OpenRawBuf(ChanID, p32[0]);
        if(VCTRL_OK != ret)
        {
            ret = VDEC_ERR;
        }
        else
        {
            ret = VCTRL_MountRawBuf(ChanID);
            ret = (VCTRL_OK == ret)? VDEC_OK: VDEC_ERR;
        }
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;

    case VDEC_CID_CLOSE_RAWBUF:          /* ��ָ��ͨ���Ϲر�raw buf */
        OSAL_SpinLock(&g_TaskLock);
        ret = VCTRL_CloseRawBuf(ChanID);
        ret = (VCTRL_OK == ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;

    case VDEC_CID_MOUNT_RAWBUF:          /* Ϊָ��ͨ����װraw buf */
        OSAL_SpinLock(&g_TaskLock);
        ret = VCTRL_MountRawBuf(ChanID);
        ret = (VCTRL_OK == ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;

    case VDEC_CID_UNMOUNT_RAWBUF:        /* Ϊָ��ͨ��ж��raw buf */
        OSAL_SpinLock(&g_TaskLock);
        ret = VCTRL_UnMountRawBuf(ChanID);
        ret = (VCTRL_OK == ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;
        
    case VDEC_CID_RESET_RAWBUF:          /* Ϊָ��ͨ����λraw buf */
        OSAL_SpinLock(&g_TaskLock);
        ret = VCTRL_ResetRawBuf(ChanID);
        ret = (VCTRL_OK == ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;
        
    case VDEC_CID_GET_STREAM_BUF:        /* ��ȡ��������Ŀռ� */
        OSAL_SpinLock(&g_TaskLock);
        {
            SINT32 D32;
            
            p32 = (SINT32*)pArgs;
            ret = RAW_GetFree(ChanID, p32[0], &D32);
            if (RAW_OK == ret)
            {
                p32[0] = D32;
                ret = VDEC_OK;
            }
            else
            {
                ret = VDEC_ERR;
            }
        }
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;

    case VDEC_CID_PUT_STREAM_BUF:        /* �������� */
        OSAL_SpinLock(&g_TaskLock);
        {
            MEM_DESC_S *pMem;
            UINT64 *p32_1;
			p32_1 = (UINT64*)(pArgs + sizeof(MEM_DESC_S));  //PTS
            pMem = (MEM_DESC_S*)pArgs;
            ret = RAW_PutBusy(ChanID, pMem->PhyAddr, pMem->Length, p32_1[0]);
            ret = (RAW_OK == ret)? VDEC_OK: VDEC_ERR;
        }
        VCTRL_EnableAllInt();
        OSAL_SpinUnLock(&g_TaskLock);
		break;
#endif

    //add by z00222166, 2012.11.20
    case VDEC_CID_SET_DISCARDPICS_PARAM:     /*��ȡ��֡����ز���*/
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_SetDiscardPicParam(ChanID, (VDEC_DISPIC_PARAM_S*)pArgs);
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
    case VDEC_CID_SET_DBG_OPTION:   /* ���õ���ѡ�� */
        break;

    case VDEC_CID_GET_DGB_OPTION:   /* ��ȡ����ѡ�� */
        break;

    /* ���������������STD_USERͨ���²ſ���ʹ�� */
#ifdef VFMW_USER_SUPPORT
    case VDEC_CID_GET_USRDEC_FRAME:
        OSAL_SpinLockIRQ(&g_TaskLock);
        {
            MEM_DESC_S  stMem;  /* phy_addr, length */
            p32 = (SINT32*)pArgs;
            ret = VCTRL_GetUsrdecFrame(ChanID, &stMem);
            p32[0] = stMem.PhyAddr;
            p32[1] = stMem.Length;
            ret = (ret == VCTRL_OK)? VDEC_OK: VDEC_ERR;
        }
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;

    case VDEC_CID_PUT_USRDEC_FRAME:
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_PutUsrdecFrame(ChanID, (USRDEC_FRAME_DESC_S*)pArgs);
        ret = (ret == VCTRL_OK)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
#endif        
    case VDEC_CID_SET_PTS_TO_SEEK:
        OSAL_SpinLockIRQ(&g_TaskLock);
        {
            VDEC_CHAN_RESET_OPTION_S option;
            option.s32KeepBS = 1;
            option.s32KeepSPSPPS = 0;
            ret = VCTRL_ResetChanWithOption(ChanID, &option);
            ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
            if (ret == VDEC_OK)
            {
                p64 = (UINT64*)pArgs;
                ret = VCTRL_SeekPts(ChanID, p64);
                ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
            }
		}
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock); 
        break;

    case VDEC_CID_SET_TRICK_MODE:
        OSAL_SpinLockIRQ(&g_TaskLock);
    #if defined(OFF_LINE_DNR_ENABLE)
        ret = DNR_ConfigFFFBSpeed(ChanID, (SINT32 *)pArgs);
        ret = (DNR_OK==ret)? VDEC_OK: VDEC_ERR;
        if (VDEC_OK == ret)
        {
            ret = VCTRL_ConfigFFFBSpeed(ChanID, (SINT32 *)pArgs);
            ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        }
    #endif
    #if defined(BTL_ENABLE)
        ret = BTL_ConfigFFFBSpeed(ChanID, (SINT32 *)pArgs);
        ret = (BTL_OK==ret)? VDEC_OK: VDEC_ERR;
        if (VDEC_OK == ret)
		{
            ret = VCTRL_ConfigFFFBSpeed(ChanID, (SINT32 *)pArgs);
            ret = (BTL_OK==ret)? VDEC_OK: VDEC_ERR;
		}
    #else
        ret = VCTRL_ConfigFFFBSpeed(ChanID, (SINT32 *)pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
    #endif

        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock); 
        break;

    case VDEC_CID_SET_CTRL_INFO:
        OSAL_SpinLockIRQ(&g_TaskLock);
		ret = VCTRL_ConfigPVRInfo(ChanID, (VFMW_CONTROLINFO_S *)pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock); 
        break;

    case VDEC_CID_RESET_CHAN_WITH_OPTION:       /* ��λͨ����ѡ��ر���ĳЩͨ������ */
        OSAL_SpinLockIRQ(&g_TaskLock);
        ret = VCTRL_ResetChanWithOption(ChanID, (VDEC_CHAN_RESET_OPTION_S *)pArgs);
        ret = (VCTRL_OK==ret)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);        
        break;
#if 0
    case VDEC_CID_GET_CHIP_TYPE:
	    pu32 = (UINT32*)pArgs;
		ret = GetVdecChipType(&(pu32[0]));   /* ��ȡоƬ���� */
        break;
    case VDEC_CID_SLEEP_TIME:
        p32 = (SINT32*)pArgs;
        g_SleepTime = p32[0];
        ret = VDEC_OK;
        break;
#endif
	//add by l00225186
#ifdef VFMW_BTL_SUPPORT
    case VDEC_CID_FRAME_BTL:
		OSAL_SpinLockIRQ(&g_TaskLock);
        ret = BTL_SetDataSource(ChanID,1,(IMAGE*)pArgs);
        ret = (ret == BTL_OK)? VDEC_OK: VDEC_ERR;
        VCTRL_EnableAllInt();
        OSAL_SpinUnLockIRQ(&g_TaskLock);
        break;
#endif
   case VDEC_CID_SET_FRAME_RATE:
        g_FrameRate[ChanID] = *(SINT32 *)pArgs;
        break;
#ifdef VFMW_MODULE_LOWDLY_SUPPORT
   case VDEC_CID_START_LOWDLAY_CALC:
        g_LowDelayCalcStat[ChanID] = 1;
        g_LowDelayCalcHandle[ChanID] = *(SINT32 *)pArgs;
		break;
   case VDEC_CID_STOP_LOWDLAY_CALC:
        g_LowDelayCalcStat[ChanID] = 0;
        g_LowDelayCalcHandle[ChanID] = 0;
	    break;
#endif
   case VDEC_CID_ALLOC_MEM_TO_CHANNEL:        //l00273086
        ret = VCTRT_SetChanCtrlState(ChanID, CHAN_FRAME_STORE_ALLOC);
        if(VDEC_OK != ret)
        {
            ret = VDEC_ERR;
            break;
        }       
        ret = VCTRL_RlsAllFrameNode(ChanID); //�ͷ�֮ǰ�Ѿ���̬�����֡��
        if(VDEC_OK != ret)
        {
            dprint(PRN_FS,"DFS, rls chan %d frame store fail!\n", ChanID);
            break;
        }
        dprint(PRN_FS,"DFS, rls chan %d frame store success!\n", ChanID);
        VCTRL_SetFsParamToChan(ChanID, (VDEC_CHAN_FRAME_STORE_PARAM_S*)pArgs);
        ret = VCTRL_RequestChanMem(ChanID);
        if(VDEC_OK == ret)
        {
            OSAL_SpinLockIRQ(&g_TaskLock);
            VCTRL_SetChanFsPartitionState(ChanID, FSP_PARTITION_STATE_SUCCESS);
            dprint(PRN_FS, "DFS, set decoding thread state to success!\n ");
            OSAL_SpinUnLockIRQ(&g_TaskLock);
        }
        else if(0 != VCTRL_GetCurChanFsSize(ChanID))
        {
            dprint(PRN_FS,"DFS, request frame store fail!, chanid: %d\n", ChanID);
            OSAL_SpinLockIRQ(&g_TaskLock);
            VCTRL_SetChanFsPartitionState(ChanID, FSP_PARTITION_STATE_FAIL);
            dprint(PRN_FS,"DFS, set decoding thread state to fail\n");
            OSAL_SpinUnLockIRQ(&g_TaskLock);
        }
        ret = VCTRT_SetChanCtrlState(ChanID, CHAN_NORMAL);
        if(VDEC_OK != ret)
        {
            ret = VDEC_ERR;
        }       
        break;
    default:
        ret = VDEC_ERR;
    }
    return ret;
}


VOID GetVdecCapability( VDEC_CAP_S *pCap )
{
    SINT32  StdCnt = 0; 

    memset( pCap, 0, sizeof(VDEC_CAP_S) );
	
    pCap->s32MaxChanNum = MAX_CHAN_NUM;
    pCap->s32MaxBitRate = 50;
    pCap->s32MaxFrameWidth  = 4096;// 1920;
    pCap->s32MaxFrameHeight = 2304;// 1088;
    pCap->s32MaxPixelPerSec = pCap->s32MaxFrameWidth*pCap->s32MaxFrameHeight*30*3/2; //8192*8192*30*3/2;// 1920*1088*30*3/2;   /* FHD*1.5 */

    pCap->SupportedStd[StdCnt++] = VFMW_H264;
    pCap->SupportedStd[StdCnt++] = VFMW_MPEG2;
    pCap->SupportedStd[StdCnt++] = VFMW_MPEG4;
    pCap->SupportedStd[StdCnt++] = VFMW_AVS;
	#ifdef    VFMW_REAL8_SUPPORT
	pCap->SupportedStd[StdCnt++] = VFMW_REAL8;
	#endif
	#ifdef    VFMW_REAL9_SUPPORT
	pCap->SupportedStd[StdCnt++] = VFMW_REAL9;
	#endif
    pCap->SupportedStd[StdCnt++] = VFMW_VC1;
    pCap->SupportedStd[StdCnt++] = VFMW_DIVX3;
    pCap->SupportedStd[StdCnt++] = VFMW_H263;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6;
    pCap->SupportedStd[StdCnt++] = VFMW_SORENSON;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6F;
    pCap->SupportedStd[StdCnt++] = VFMW_VP6A;
    pCap->SupportedStd[StdCnt++] = VFMW_VP8;
    pCap->SupportedStd[StdCnt++] = VFMW_MVC;
#ifdef VFMW_HEVC_SUPPORT  //l00214825
	pCap->SupportedStd[StdCnt++] = VFMW_HEVC;
#endif		
    pCap->SupportedStd[StdCnt++] = VFMW_RAW;
    pCap->SupportedStd[StdCnt++] = VFMW_USER;    
    pCap->SupportedStd[StdCnt++] = VFMW_END_RESERVED;


    return;
}
#if 0
SINT32 GetVdecChipType(UINT32 *ChipType)
{
    SINT32 ret = VDEC_OK;

   *ChipType = g_chipID;
   return ret;

}
#endif
SINT32 VDEC_Suspend(VOID)
{
    VCTRL_Suspend();
    dprint(PRN_FATAL,"VDEC_Suspend ok !\n");

    return VDEC_OK;
}

SINT32 VDEC_Resume(VOID)
{

    VCTRL_Resume();

    dprint(PRN_FATAL,"VDEC_Resume ok !\n");
	return VDEC_OK;
}


/* testframe use vfmw functions */
EXPORT_SYMBOL(VDEC_Init);
EXPORT_SYMBOL(VDEC_Exit);
EXPORT_SYMBOL(VDEC_Control);
EXPORT_SYMBOL(VDEC_InitWithOperation);
EXPORT_SYMBOL(VDEC_Suspend);
EXPORT_SYMBOL(VDEC_Resume);

