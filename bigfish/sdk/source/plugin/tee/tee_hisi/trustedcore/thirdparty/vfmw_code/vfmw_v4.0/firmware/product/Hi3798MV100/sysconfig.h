/*--------------------------------------------------------------------------------------------------------------------------*/
/*!!Warning: This is a key information asset of Huawei Tech Co.,Ltd                                                         */
/*CODEMARK:kOyQZYzjDpyGdBAEC2GaWinjiDDUykL9e8pckESWBbMVmSWkBuyJO01cTiy3TdzKxGk0oBQa
mSMf7J4FkTpfvzHyMxSEsfcbL/G0fFswaAZ8tsS4we+PBWC6a/UNlzCWIaw+Ujkv9NAY+as0
fg7WZIRvw27AjvRqJbkRJvqFUORSa6KPQaSBMxCxJTGTTf//sQbjPOyYldN0OVR9ut4HFO4U
ZguGQVqcOAJQbE96v6175DqhuprKgQB8R+2fu7VD3qtX+ZJh/t0512oqv+e8YA==*/
/*--------------------------------------------------------------------------------------------------------------------------*/
#ifndef __VFMW_SYSCONFIG_HEADER__
#define __VFMW_SYSCONFIG_HEADER__

//#define TWO_VDH

/* ����֧�ֵ�ͨ����Ŀ */
#ifdef CFG_MAX_CHAN_NUM
#define MAX_CHAN_NUM CFG_MAX_CHAN_NUM
#else
#define MAX_CHAN_NUM 32
#endif

/*��֧�ֵ�VDH����*/
#if defined(TWO_VDH)
#define MAX_VDH_NUM 2
#else
#define MAX_VDH_NUM 1
#endif

/* ϵͳ���ƼĴ�����ַ��λ�� */
#define SCD_RESET_REG_PHY_ADDR   0x0   //scd
/* Ӳ������IP�ӿڼĴ�����ַ */
#define VDM_REG_PHY_ADDR       0xf8c30000    // VDM0 �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define VDM_REG_PHY_ADDR_1     0xf8c30000    // VDM1�Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define DNR_REG_PHY_ADDR       0x10450000    //DNR
#define SCD_REG_PHY_ADDR       0xf8c3c000    // scd �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define SCD_REG_PHY_ADDR_1     SCD_REG_PHY_ADDR    // scd �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define FOD_REG_PHY_ADDR       0x10150000    // fod �Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ
#define BPD_REG_PHY_ADDR       0xf8c60000
#define BTL_REG_PHY_ADDR       0xf8d00000   //0x10450000 // 0x101b0000   //BTL�Ĵ���ӳ�䵽ARM�ռ�ĵ�ַ����ʼ��ַ����
#define SYSTEM_REG_RANGE       (1024*1024)
/* �жϺ� */
#define VDM_INT_NUM            (95+32)
#define VDM_INT_NUM_1          (95+32)
#define SCD_INT_NUM            (104+32)

#ifdef ENV_SOS_KERNEL
/*sec interrupt*/
#define SEC_VDM_INT_NUM        (105+32)
#define SEC_VDM_INT_NUM_1      (105+32)
#define SEC_SCD_INT_NUM        (106+32)
#endif

#define BPD_INT_NUM            (99+32)  
#define DNR_INT_NUM            (61+32)
#define BTL_INT_NUM            (103+32)

#ifdef ENV_SOS_KERNEL
#define SYSTEM_REG_PHY_ADDR        0xf8a22000
#define BOARD_MEM_BASE_ADDR        0x3E200000
#define BOARD_MEM_TOTAL_SIZE       (10*1024*1024) //�ǰ���Ҫɾ������ʱ����10M����ʼ����
#define BOARD_MEM_BASE_ADDR_Sec    0x3B000000     //��ȫ�ڴ����ַ
#define BOARD_MEM_TOTAL_SIZE_Sec   (50*1024*1024) //��ȫ�ڴ��ܴ�С
#else
/* ���Ե����Ͽɱ���Ƶ����ʹ�õ�memoryԤ�� */
//#define BOARD_MEM_BASE_ADDR    0x98000000
#define BOARD_MEM_BASE_ADDR    0x08000000
#define BOARD_MEM_TOTAL_SIZE   (72*1024*1024)
#endif

#endif