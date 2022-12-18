/******************************* Include Files *******************************/

/* Sys headers */
#include <linux/version.h>
#include <linux/proc_fs.h>
#include <linux/ioport.h>
#include <linux/string.h>
#include <linux/ioctl.h>
#include <linux/fs.h>
#include <linux/delay.h>
#include <linux/sched.h>
#include <linux/vmalloc.h>
#include <linux/interrupt.h>
#include <linux/seq_file.h>
#include <asm/uaccess.h>
#include <asm/io.h>
#include <mach/hardware.h>

/* Unf headers */
#include "hi_error_mpi.h"
#include "hi_board.h"

/* Drv headers */
#include "drv_amp_private.h"
#include "drv_amp_ioctl.h"

#include "amp_i2s.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/***************************** Static Definition *****************************/

DECLARE_MUTEX(g_AmpMutex);

static AMP_GLOBAL_PARAM_S s_stAmpDrv =
{
	.atmOpenCnt			= ATOMIC_INIT(0),
};

static AMP_DRV_FUNC_S* pfnAMPFunc;

//static AMP_STORING_S g_stRusumeStoreAttr;

/****************************** Static Function *********************************/
static HI_S32 AMP_RegChanProc(HI_VOID)
{
	DRV_PROC_ITEM_S* pstItem;

	/* Check parameters */
	if (HI_NULL == s_stAmpDrv.pstProcParam)
	{
		return HI_FAILURE;
	}

	/* Create proc */
	pstItem = HI_DRV_PROC_AddModule("amp", HI_NULL, HI_NULL);

	if (!pstItem)
	{
		HI_FATAL_AMP("Create audio AMP proc fail!\n");
		return HI_FAILURE;
	}

	/* Set functions */
	pstItem->read  = s_stAmpDrv.pstProcParam->pfnReadProc;
	pstItem->write = s_stAmpDrv.pstProcParam->pfnWriteProc;

	HI_INFO_AMP("Create proc for audio AMP OK!\n");

	return HI_SUCCESS;
}

static HI_VOID AMP_UnRegChanProc(HI_VOID)
{
	HI_DRV_PROC_RemoveModule("amp");

	return;
}

static HI_S32 AMP_OpenDev(HI_VOID)
{
	return HI_SUCCESS;
}

static HI_S32 AMP_CloseDev(HI_VOID)
{
	return HI_SUCCESS;
}

static HI_S32 AMP_Ioctl(struct inode* inode, struct file* file, HI_U32 cmd, HI_VOID* arg)
{
	HI_S32 s32Ret = HI_SUCCESS;

	switch (cmd)
	{
		case CMD_AMP_SETMUTE:
		{
			HI_BOOL bMute = *(HI_BOOL*)arg;
			s32Ret = pfnAMPFunc->pfnAmpSetMute(bMute);
			break;
		}

		case CMD_AMP_GETMUTE:
		{
			HI_BOOL* pbMute = (HI_BOOL*)arg;
			s32Ret = pfnAMPFunc->pfnAmpGetMute(pbMute);
			break;
		}

		case CMD_AMP_SETSUBWOOFERVOL:
		{
			HI_U32 u32Volume = *(HI_U32*)arg;
			s32Ret = pfnAMPFunc->pfnAmpSetSubWooferVol(u32Volume);
			break;
		}

		case CMD_AMP_GETSUBWOOFERVOL:
		{
			HI_U32* pu32Volume = (HI_U32*)arg;
			s32Ret = pfnAMPFunc->pfnAmpGetSubWooferVol(pu32Volume);
			break;
		}

		case CMD_AMP_WRITEREG:
		{
			AMP_REG_OPERATE_PARAM_S_PTR pstRegParam = (AMP_REG_OPERATE_PARAM_S_PTR)arg;
			s32Ret = pfnAMPFunc->pfnAmpWriteReg(pstRegParam->u32RegAddr, pstRegParam->u32ByteSize, pstRegParam->pu8Value);
			break;
		}

		case CMD_AMP_READREG:
		{
			AMP_REG_OPERATE_PARAM_S_PTR pstRegParam = (AMP_REG_OPERATE_PARAM_S_PTR)arg;
			s32Ret = pfnAMPFunc->pfnAmpReadReg(pstRegParam->u32RegAddr, pstRegParam->u32ByteSize, pstRegParam->pu8Value);
			break;
		}

		default:
		{
			s32Ret = HI_FAILURE;
			HI_ERR_AMP("unknown custom audio AMP cmd: 0x%x\n", cmd);
			break;
		}
	}

	return s32Ret;
}

HI_S32 AMP_ReadProc(struct seq_file* p)
{
	PROC_PRINT(p, "\n-----------------------------  Amp  ------------------------------------------------\n");
	pfnAMPFunc->pfnAmpProc(p);
	PROC_PRINT(p, "\n");

	return HI_SUCCESS;
}

/******************************Extern Function *********************************/
long AMP_DRV_Ioctl(struct file* file, HI_U32 cmd, unsigned long arg)
{
	long s32Ret = HI_SUCCESS;

	s32Ret = down_interruptible(&g_AmpMutex);

	//cmd process
	s32Ret = (long)HI_DRV_UserCopy(file->f_dentry->d_inode, file, cmd, arg, AMP_Ioctl);

	up(&g_AmpMutex);

	return s32Ret;
}

HI_S32 AMP_DRV_Open(struct inode* inode, struct file*  filp)
{
	HI_S32 Ret;

	Ret = down_interruptible(&g_AmpMutex);

	if (atomic_inc_return(&s_stAmpDrv.atmOpenCnt) == 1)
	{
		/* Init device */
		if (HI_SUCCESS != AMP_OpenDev())
		{
			HI_FATAL_AMP("AMP_OpenDev err!\n");
			goto err;
		}
	}

	up(&g_AmpMutex);
	return HI_SUCCESS;

err:
	atomic_dec(&s_stAmpDrv.atmOpenCnt);
	up(&g_AmpMutex);
	return HI_FAILURE;
}

HI_S32 AMP_DRV_Release(struct inode* inode, struct file*  filp)
{
	long Ret = HI_SUCCESS;

	Ret = down_interruptible(&g_AmpMutex);

	/* Not the last close, only close the channel match with the 'filp' */
	if (atomic_dec_return(&s_stAmpDrv.atmOpenCnt) != 0)
	{}
	/* Last close */
	else
	{
		AMP_CloseDev();
	}

	up(&g_AmpMutex);
	return HI_SUCCESS;
}

HI_S32 AMP_DRV_ReadProc(struct seq_file* p, HI_VOID* v)
{
	return AMP_ReadProc(p);
}

HI_S32 AMP_DRV_WriteProc(struct file* file, const char __user* buf, size_t count, loff_t* ppos)
{
	HI_S32 s32Ret;

	s32Ret = down_interruptible(&g_AmpMutex);

	up(&g_AmpMutex);
	return count;
}

HI_S32 AMP_DRV_RegisterProc(AMP_REGISTER_PARAM_S* pstParam)
{
	/* Check parameters */
	if (HI_NULL == pstParam)
	{
		return HI_FAILURE;
	}

	s_stAmpDrv.pstProcParam = pstParam;

	return AMP_RegChanProc();
}

HI_VOID AMP_DRV_UnRegisterProc(HI_VOID)
{
	/* Unregister */
	AMP_UnRegChanProc();

	/* Clear param */
	s_stAmpDrv.pstProcParam = HI_NULL;

	return;
}

HI_S32 AMP_DRV_Suspend(PM_BASEDEV_S* pdev, pm_message_t state)
{
#if 0
	long s32Ret = HI_SUCCESS;
	s32Ret = down_interruptible(&g_AmpMutex);

	if (HI_TRUE == s_stAmpDrv.bReady)
	{
		/* Destory all amp */
		/* Store amp settings */
		AMP_GetSettings(&g_stRusumeStoreAttr);

		/* Destroy amp */
		s32Ret = AMPDestroy();

		if (HI_SUCCESS != s32Ret)
		{
			HI_FATAL_AMP("Suspend destroy audio AMP fail\n");
			up(&g_AmpMutex);
			return HI_FAILURE;
		}
	}

	up(&g_AmpMutex);
#endif
	AMP_DRV_Exit();
	HI_PRINT("AMP suspend OK\n");

	return HI_SUCCESS;
}

HI_S32 AMP_DRV_Resume(PM_BASEDEV_S* pdev)
{
#if 0
	HI_S32 s32Ret = HI_SUCCESS;

	s32Ret = down_interruptible(&g_AmpMutex);

	if (HI_TRUE == s_stAmpDrv.bReady)
	{
		/* Restore all ade */
		if (HI_SUCCESS != AMPCreate(g_stRusumeStoreAttr.bMute))
		{
			HI_FATAL_AMP("AMP_RestoreSettings fail\n");
			up(&g_AmpMutex);
			return HI_FAILURE;
		}
	}

	up(&g_AmpMutex);
#endif
	AMP_DRV_Init();
	HI_PRINT("AMP resume OK\n");

	return HI_SUCCESS;
}

HI_S32 AMP_DRV_Init(HI_VOID)
{
	HI_S32 Ret;

	Ret = down_interruptible(&g_AmpMutex);

	Ret = HI_DRV_MODULE_Register(HI_ID_AMP, AMP_NAME, HI_NULL);

	if (HI_SUCCESS != Ret)
	{
		HI_FATAL_AMP("Register amp module fail:%#x!\n", Ret);
		goto err0;
	}

	/* Get I2C functions */
	Ret = HI_DRV_MODULE_GetFunction(HI_ID_I2C, (HI_VOID**)&s_stAmpDrv.pI2CFunc);

	if (HI_SUCCESS != Ret)
	{
		HI_FATAL_AMP("Get i2c function err:%#x!\n", Ret);
		goto err1;
	}

	if (HI_SUCCESS != HI_DRV_MODULE_GetFunction(HI_ID_GPIO, (HI_VOID**)&s_stAmpDrv.pGpioFunc))
	{
		HI_ERR_AMP("Get gpio function err\n");
		goto err1;
	}

	s_stAmpDrv.u32ResetGPIONum 		= HI_BOARD_AMP_RST_GPIONUM;
	s_stAmpDrv.u32ResetPolarity 	= HI_BOARD_AMP_RST_ON;
	s_stAmpDrv.u32HWMuteGPIONum 	= HI_BOARD_AMP_MUTE_GPIONUM;
	s_stAmpDrv.u32HWMutePolarity 	= HI_BOARD_AMP_MUTE_ON;
	s_stAmpDrv.u32I2CNum 			= HI_BOARD_AMP_I2C_CHAN;
	s_stAmpDrv.u8DeviceAddr 		= HI_BOARD_AMP_I2C_ADDR;
	s_stAmpDrv.u32GPIOOutputPolarity = HI_BOARD_GPIO_OUT; //0:Output, 1:Input
	s_stAmpDrv.u8DeviceType		= HI_BOARD_AMP_TYPE;

	switch (HI_BOARD_AMP_TYPE)
	{
		case 0:
		{
			extern AMP_DRV_FUNC_S stTas5707Func;
			pfnAMPFunc = &stTas5707Func;
			break;
		}

		case 1:
		{
			extern AMP_DRV_FUNC_S stTas5711Func;
			pfnAMPFunc = &stTas5711Func;
			break;
		}

		case 2:
		{
			extern AMP_DRV_FUNC_S stNTP8214Func;
			pfnAMPFunc = &stNTP8214Func;
			break;
		}

		default:
		{
			HI_FATAL_AMP("Amp init err: HI_BOARD_AMP_TYPE not define\n");
			goto err1;
			break;
		}
	}

	Ret = pfnAMPFunc->pfnAmpInit(&s_stAmpDrv);

	if (HI_SUCCESS != Ret)
	{
		HI_FATAL_AMP("Amp init err:%#x!\n", Ret);
		goto err1;
	}

	up(&g_AmpMutex);
	return HI_SUCCESS;

err1:
	HI_DRV_MODULE_UnRegister(HI_ID_AMP);
err0:
	up(&g_AmpMutex);
	return Ret;
}

HI_VOID AMP_DRV_Exit(HI_VOID)
{
	HI_S32 Ret;

	Ret = down_interruptible(&g_AmpMutex);
	pfnAMPFunc->pfnAmpDeinit();
	s_stAmpDrv.pGpioFunc = HI_NULL;
	s_stAmpDrv.pI2CFunc = HI_NULL;

	HI_DRV_MODULE_UnRegister(HI_ID_AMP);
	up(&g_AmpMutex);

	return;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
