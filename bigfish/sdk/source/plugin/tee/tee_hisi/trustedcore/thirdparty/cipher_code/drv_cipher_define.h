/******************************************************************************
 *
 * Copyright (C), 2004-2020, Hisilicon Tech. Co., Ltd.
 * ******************************************************************************
 * File Name     : drv_cipher_define.h
 * Version       : Initial
 * Author        : Hisilicon hisecurity team
 * Created       : 2013-12-28
 * Last Modified :
 * Description   : 
 * Function List :
 * History       :
 * ******************************************************************************/
#ifndef __DRV_CIPHER_DEFINE_H__
#define __DRV_CIPHER_DEFINE_H__

#include "hi_type.h"
#include "hi_unf_cipher.h"
#include "hi_error_mpi.h"
#include "hi_unf_hdcp.h"
#include "hi_drv_cipher.h"
#include "tee_log.h"
#include "sre_ticktimer_functions.h"

#define __CIPHER_DEBUG_VERSION__ /* when release cipher SW, mask it */

#define HASH_BLOCK_SIZE		(64)
#define HASH_PAD_MAX_LEN	(64)
#define SECURE_MEM_CIPHER_MAX_SIZE           (0x100000-16)

//#define CIPHER_INTERRUPT_ENABLE     1

#define  CIPHER_IRQ_NUMBER          		(126 + 32)       /*Hi3798m*/

#define CIPHER_WAIT_IDLE_TIMES 1000
//#define HASH_MAX_DURATION      1000
/*change by y00201671 for trustedcore:begin*/
/*when hash data buffer is larger than 16K the hash eng copy time will be larger than 1000*/
/*change by y00201671 for trustedcore:end*/


/*Porting to TrustedCore STB begin*/
//no use
#if 0
#define  SA_INTERRUPT     IRQF_DISABLED
#define  SA_SHIRQ         IRQF_SHARED
#endif
/*Porting to TrustedCore STB end*/


#define TASK_QUEUE_IDLE 			(0)
#define TASK_QUEUE_BUSY 			(1)

#define MEM_LENGTH_ERROR    		(1)
#define AHB_BUS_ERROR       		(2)

#define CIPHER_MAX_LIST_NUM  		(128)

#define CI_IV_SIZE       			(16)  /* max 128bit */
#define CI_KEY_SIZE      			(32)  /* max 256bit */


#define CI_BUF_LIST_FLAG_IVSET_BIT  (21)
#define CI_BUF_LIST_FLAG_EOL_BIT    (22)

typedef struct hiCI_BUF_LIST_ENTRY_S
{
    HI_U32  u32DataAddr;    /* Phy Addr */
    HI_U32  u32Flags;       /* bit21: iv_set_flag, bit22: end_of_list_flag */
    HI_U32  U32DataLen;     /* bit0~bit19, total 20 bit */
    HI_U32  u32IVStartAddr; /* if iv_set_flag == 1, this is the IV addr */
} CI_BUF_LIST_ENTRY_S;

/*************************** Structure Definition ****************************/
/** \addtogroup      CIPHER */
/** @{ */  /** <!-- [CIPHER] */

/*media memory map structure*/
typedef struct hiMMZ_BUFFER_S
{
    unsigned int u32StartVirAddr;
    unsigned int u32StartPhyAddr;
    unsigned int u32Size;
}MMZ_BUFFER_S;

#define HI_PRINT uart_printf_func
#define HI_ERR_CIPHER(format, arg...)  uart_printf_func("<<<CIPHER ERR>>> %s %d: " format, __FUNCTION__, __LINE__, ## arg)
#define HI_INFO_CIPHER(format, arg...) 

#define HI_PRINT_HEX(name, str, len) \
{\
    HI_U32 _i = 0;\
    HI_U32 _val; \
    HI_U8 *_str = (HI_U8*)str;\
    HI_PRINT("[%s]:\n", name);\
    for ( _i = 0 ; _i < (len); _i+=4 )\
    {\
        _val  = *((_str)+_i+3);\
        _val |= *((_str)+_i+2) << 8;\
        _val |= *((_str)+_i+1) << 16;\
        _val |= *((_str)+_i+0) << 24;\
        if( (_i % 16 == 0) && (_i != 0)) HI_PRINT("\n");\
        HI_PRINT("%x ", _val);\
    }\
    HI_PRINT("\n");\
}

#ifndef CIPHER_READ_REG
#define CIPHER_READ_REG(reg, result) ((result) = *(volatile unsigned int *)(reg))
#endif

#ifndef CIPHER_WRITE_REG
#define CIPHER_WRITE_REG(reg, data) (*((volatile unsigned int *)(reg)) = (data))
#endif

#define CIPHER_MSLEEP(msec) SRE_SwMsleep(msec)


#endif


