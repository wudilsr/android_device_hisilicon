#ifndef __TVP_ADAPTER_H__
#define __TVP_ADAPTER_H__

#define SEC_VFMW_VERSION      "2015060900s" 

#define DEBUG_SAVE_SUPPORT    (0)

#define MAX_RAW_NUM           (1024) 
#define MAX_EVENT_NUM         (128) 
#define MAX_PARA_SIZE         (1024)

#define MAX_PROC_SIZE         (100*1024)

/* stream list address */
typedef struct hiSTREAM_LIST_S
{
    HI_S32  stream_list_phy_addr;
} STREAM_LIST_S;

typedef struct 
{
    HI_S32      Head_NS;
    HI_S32      Head_S;
    HI_S32      Tail_S; 
    HI_S32      Tail_NS;
    STREAM_DATA_S RawPacket[MAX_RAW_NUM];   
} RAW_ARRAY_NS;

typedef struct 
{
    HI_S32      IsValid;
    HI_S32      ChanID;
    HI_S32      Type;
    HI_U8       para[MAX_PARA_SIZE];
} MSG_DATA_S;

typedef struct 
{   
    HI_S32      Head;
    HI_S32      Tail;
    MSG_DATA_S  Message[MAX_EVENT_NUM];
} CALLBACK_ARRAY_NS;


#if defined(ENV_ARMLINUX_KERNEL)

// Definition for Linux Kernel VFMW
typedef HI_S32 (*VDEC_CALLBACK)( HI_S32 ChanID, HI_S32 eEventID, HI_VOID *pArgs );

HI_VOID TVP_VDEC_OpenModule(HI_VOID);
HI_VOID TVP_VDEC_ExitModule(HI_VOID);
HI_S32  TVP_VDEC_Init(HI_S32 (*VdecCallback)(HI_S32, HI_S32, HI_VOID*));
HI_S32  TVP_VDEC_InitWithOperation(VDEC_OPERATION_S *pArgs);
HI_S32  TVP_VDEC_Exit(HI_VOID);
HI_S32  TVP_VDEC_Control(HI_S32 ChanID, VDEC_CID_E eCmdID, HI_VOID *pArgs);
HI_S32  TVP_VDEC_Suspend(HI_VOID);
HI_S32  TVP_VDEC_Resume(HI_VOID);
HI_S32  TVP_VDEC_SetDbgOption (HI_U32 opt, HI_U8* p_args);
HI_S32  TVP_VDEC_TrustDecoderInit(VDEC_OPERATION_S *pArgs);
HI_S32  TVP_VDEC_TrustDecoderExit(HI_VOID);

#endif

#endif

