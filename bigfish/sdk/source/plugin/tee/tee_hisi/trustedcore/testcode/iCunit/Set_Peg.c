#include "Set_Peg.h"
#include "sre_sys.h"
#include "iCunit.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */
extern VOID iCunitPrintCurrentCase(VOID);

extern TST_CDA_INFO_S  *g_stCdaInfoAddr;
extern UINT32       g_uwCurNestCount;
extern UINT32       g_vuwIntCount;
extern UINT32       g_vuwUniFlag;
extern UINT32       g_uwHwResetFlag;
extern UINT32       g_uwNMIErrFlag;
extern BOOL         g_bExcSaveFlag;

extern TST_EXC_INFO_S  *g_pstExcInfo;                  /* 异常信息 */
UINT32 g_uwExcPC = 0;

REBOOT_HOOK  g_pfnRebootHook = NULL;
UINT32       g_uwPara[4] = {0};

#if(OS_HARDWARE_PLATFORM == OS_SC3850)
#define ADDR_IN_RANGE(addr, start, end) \
    (((UINT32)(addr) >= (UINT32)(start)) && ((UINT32)(addr) <= (UINT32)(end)))
#define M2_MEMORY_BASE          0x30000000
#define M2_MEMORY_END           0x3FFFFFFF
#define CACHE_INVALIDATE 0x00000003
#define CACHE_FLUSH 0x00000001

extern UINT32  SRE_ProgVA2PA(VOID const * pVirtAddr, VOID ** ppPhysAddr, UINT32 * pSegNum);
extern UINT32 osCacheL1L2DataSweep(VOID const* virt_addr_start, VOID const * virt_addr_end,
                                                     VOID const* phys_addr_start, UINT32 command, BOOL bWait);
extern UINT32 osL1CacheDataSweep(VOID const* virt_addr_start, VOID const * virt_addr_end, UINT32 command, BOOL bWait);



OS_SEC_TEXT_INIT VOID TEST_DCacheWbInv(VOID *pStartAddr, UINT32 uwSize, BOOL bWait)
{
   UINT8 * pEndAddr = NULL;
   VOID    * phys_start = NULL;
   UINT32  uwSegNum = 0;

   if((0 == uwSize)||(SRE_OK != SRE_ProgVA2PA(pStartAddr, &phys_start, &uwSegNum)))
   {
      return;
   }

   pEndAddr = (UINT8 *)pStartAddr + uwSize - 1;

   if (!ADDR_IN_RANGE(phys_start, M2_MEMORY_BASE, M2_MEMORY_END))
   {
       (VOID)osCacheL1L2DataSweep(pStartAddr, pEndAddr, phys_start, CACHE_FLUSH, bWait);
   }
   else
   {
       (VOID)osL1CacheDataSweep(pStartAddr, pEndAddr, CACHE_FLUSH, bWait);
   }

}


OS_SEC_TEXT_INIT UINT32 SET_PEG(VOID *pOldFunc, VOID *pNewFunc, SETPEG_JMP_ST *pstIncSave)
{
    SETPEG_JMP_ST *pstRepIns;
    SETPEG_JMP_OFFSET_ST *pstFuncAddr;
    UINT32 uvIntSave;

    uvIntSave = SRE_IntLock();

    /* len of JMP instruction */
    memcpy((VOID *)pstIncSave, pOldFunc, 6);

    pstFuncAddr = (SETPEG_JMP_OFFSET_ST *)&pNewFunc;
    pstRepIns = (SETPEG_JMP_ST *)pOldFunc;

    /* 对照JMP jump指令 */
    pstRepIns->pat1 = 4;
    pstRepIns->pat2 = 49;
    pstRepIns->pat3 = 1;
    pstRepIns->pat4 = 2;
    pstRepIns->A1 = pstFuncAddr->A1;
    pstRepIns->A2 = pstFuncAddr->A2;
    pstRepIns->a1 = pstFuncAddr->a1;
    pstRepIns->a2 = pstFuncAddr->a2;
    asm(" syncio");

    TEST_DCacheWbInv( pOldFunc, 6, 1);
    SRE_ICacheInv(pOldFunc, 6, 1);

    (VOID)SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

OS_SEC_TEXT_INIT UINT32 CLEAN_PEG(VOID *pOldFunc, SETPEG_JMP_ST stIncSave)
{
    UINT32 uvIntSave;
    UINT32 uwMcrSave;

    uvIntSave = SRE_IntLock();

    uwMcrSave = (*(volatile UINT32*) 0xFFF06000);
    (*(volatile UINT32*) 0xFFF06000) &= 0xFFFFFF77;
    asm(" syncio");

    memcpy((VOID *)pOldFunc, (VOID *)&stIncSave, 6);
    asm(" syncio");

    (*(volatile UINT32*) 0xFFF06000) = uwMcrSave;
    asm(" syncio");

    TEST_DCacheWbInv( pOldFunc, 6, 1);
    SRE_ICacheInv(pOldFunc, 6, 1);

    (VOID)SRE_IntRestore(uvIntSave);
    return SRE_OK;
}
#elif(OS_HARDWARE_PLATFORM == OS_SC3400)
UINT32 SET_PEG(VOID *pOldFunc, VOID *pNewFunc, SETPEG_JMP_ST *pstIncSave)
{
    UINT32 uwOldAddr;
    UINT32 uwNewAddr;
    SETPEG_JMP_ST   *pstRepIns;
    SETPEG_JMP_OFFSET_ST *pstIncAddr;
    CHAR    acStoredInc[12];
    UINT16  acJmp[12];
    UINT32 uvIntSave;
    UINT32 uwIndex;

    uvIntSave = SRE_IntLock();

    uwOldAddr = (UINT32)((UINT32 *)pOldFunc);
    uwNewAddr = (UINT32)((UINT32 *)pNewFunc);

    pstIncAddr = (SETPEG_JMP_OFFSET_ST *)&uwNewAddr;
    pstRepIns = (SETPEG_JMP_ST *)acJmp;


    for (uwIndex = 0; uwIndex < 6 ; uwIndex++)
    {
        acStoredInc[uwIndex] = ((CHAR *)uwOldAddr)[uwIndex];
    }

    pstRepIns->pat1 = 4;
    pstRepIns->pat2 = 49;
    pstRepIns->pat3 = 1;
    pstRepIns->pat4 = 2;
    pstRepIns->A1 = pstIncAddr->A1;
    pstRepIns->A2 = pstIncAddr->A2;
    pstRepIns->a1 = pstIncAddr->a1;
    pstRepIns->a2 = pstIncAddr->a2;

    memcpy((VOID *)uwOldAddr, (VOID *)pstRepIns, 6);
    SRE_DCacheFlush((VOID *) uwOldAddr, 6, 1);
    SRE_ICacheInv((VOID *)uwOldAddr, 6, 1);

    memcpy((VOID *)pstIncSave, (VOID *)acStoredInc, 6);

    (VOID)SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

UINT32 CLEAN_PEG(VOID *pOldFunc, SETPEG_JMP_ST stIncSave)
{
    UINT32 uvIntSave;

    uvIntSave = SRE_IntLock();

    memcpy((VOID *)pOldFunc, (VOID *)&stIncSave, 6);
    SRE_DCacheFlush((VOID *)pOldFunc, 6, 1);
    SRE_ICacheInv((VOID *)pOldFunc, 6, 1);

    (VOID)SRE_IntRestore(uvIntSave);
    return SRE_OK;
}
#elif (OS_HARDWARE_PLATFORM == OS_C64XPLUS)
#define VOS_UINT32 UINT32
UINT32 SET_PEG(VOID *pOldFunc, VOID *pNewFunc, SETPEG_JMP_ST *pstIncSave)
{
    UINT32 uwOldAddr;
    UINT32 uwNewAddr;
    UINT32 uvIntSave;
    INT32  slOffset;
    UINT32 uwFunPos;
    UINT8  ucCount;
    UINT32 ulRepIns[10];
    UINT32 ulFlag1,ulFlag2;
    UINT32  *pulRepInsAddr;
    UINT32  ulTmp;


    uwOldAddr = (UINT32)((UINT32 *)pOldFunc);
    uwNewAddr = (UINT32)((UINT32 *)pNewFunc);

    slOffset = uwNewAddr - (INT32)(uwOldAddr & 0xffffffe0);

   /* The value is too big. */
    if(slOffset > (1 << 22) - 1)
    {
        uart_printf("overflow.\n");
        return 1;
    }
    /* The value is too small. */
    else if (slOffset < -(1 << 22))
    {
        uart_printf("overflow.\n");
        return 1;
    }

    uvIntSave = SRE_IntLock();

    slOffset = (INT32)((UINT32)slOffset >> 2);
    uwFunPos = (uwOldAddr - (INT32)(uwOldAddr & 0xffffffe0))/4 + 1;

    for (ucCount = 0; ucCount <40; ucCount++)
    {
        ((UINT8 *)pstIncSave)[ucCount] = ((UINT8 *)uwOldAddr)[ucCount];
    }
    ulFlag1 = 0;
    ulFlag2 = 0;
    ulRepIns[0] = (0x00000012 & ~0x0fffff80) | (((UINT32)slOffset << 7) & 0x0fffff80);
    pulRepInsAddr = (VOS_UINT32 *)uwOldAddr;
    pulRepInsAddr++;

    for(ucCount = 1; ucCount < 10; ucCount++)
    {
        /*.fphead判断*/
        if (0xE0000000 == (*pulRepInsAddr & 0xE0000000)
        && (0 == ((VOS_UINT32)pulRepInsAddr + 4) % 32))
        {
            /* 第一次遇到.fphead */
            if( 0 == ulFlag1)
            {
                if(uwFunPos == 8)
                {
                    ulTmp = (1 << 21) | 0x3;
                    ulTmp = ~ulTmp;
                    ulRepIns[ucCount] = *pulRepInsAddr & ulTmp;
                }
                else
                {
                    /*修改fphead，使该指令不按照压缩指令执行*/
                    ulTmp = (1 << (20 + uwFunPos)) | (1 << (uwFunPos * 2 - 1)) | (1 << (uwFunPos * 2 - 2));
                    ulTmp = ~ulTmp;
                    ulRepIns[ucCount] = *pulRepInsAddr & ulTmp;

                    /* NOP 5 跟 B 指令在同一个指令包，清除并行运行位*/
                    if( 1 == ulFlag2)
                    {
                        ulTmp = (1 << (21 + uwFunPos)) | (1 << (uwFunPos * 2 + 1)) | (1 << (uwFunPos * 2));
                        ulTmp = ~ulTmp;
                        ulRepIns[ucCount] &= ulTmp;
                    }
                }

                ulFlag1 = 1;
            }
            else
            {
                /* 0x3 : 指令包的第一条指令为NOP 5 指令，设置为不能并行执行 */
                ulTmp = (1 << 21) | 0x3;
                ulTmp = ~ulTmp;
                ulRepIns[ucCount] = *pulRepInsAddr & ulTmp;
            }
        }
        else if ((0 == ulFlag2))
        {
            /*NOP 5 = 0x0000A000*/
            ulRepIns[ucCount] = 0x0000A000;
            ulFlag2 = 1;
        }
        else
        {
            ulRepIns[ucCount] = *pulRepInsAddr;
        }

        pulRepInsAddr++;
    }

    memcpy((CHAR *)uwOldAddr, (CHAR *)ulRepIns, 40);

    SRE_DCacheFlush((VOID *)uwOldAddr, 40, 1);
    SRE_ICacheInv((VOID *)uwOldAddr, 40, 1);

    (VOID)SRE_IntRestore(uvIntSave);

    return SRE_OK;
}

UINT32 CLEAN_PEG(VOID *pOldFunc, SETPEG_JMP_ST stIncSave)
{
    UINT32 uvIntSave;

    uvIntSave = SRE_IntLock();

    memcpy((VOID *)pOldFunc, (VOID *)&stIncSave, 40);
    SRE_DCacheFlush((VOID *)pOldFunc, 40, 1);
    SRE_ICacheInv((VOID *)pOldFunc, 40, 1);

    (VOID)SRE_IntRestore(uvIntSave);
    return SRE_OK;
}

#elif ((OS_HARDWARE_PLATFORM == OS_XTENSA2)||(OS_HARDWARE_PLATFORM == OS_DSP170)\
    ||(OS_HARDWARE_PLATFORM == OS_RISC170)|| (OS_HARDWARE_PLATFORM == OS_DSP220)\
    || (OS_HARDWARE_PLATFORM == OS_RISC220)||(OS_HARDWARE_PLATFORM == OS_HACCC))
UINT32 SET_PEG(VOID *pOldFunc, VOID *pNewFunc, SETPEG_JMP_ST *pstIncSave)
{
    UINT32 uwOldAddr;
    UINT32 uwNewAddr;
    UINT32 uvIntSave;
    SETPEG_JMP_ST stRspIncInfo = {0x06, 0x01, 0x00,    //j lable
                                   0x00,                //resverd
                                   0x00,                //newaddr
                                   0x91, 0xff, 0xff,    //l32r a9 -4
                                   0xa0,0x09, 0x00,     //jx a9
                                   0x3D,                //nop.n
                                   0xF0};               //nop.n

    uvIntSave = SRE_IntLock();

    uwOldAddr = (UINT32)((UINT32 *)pOldFunc);
    uwNewAddr = (UINT32)((UINT32 *)pNewFunc);

    stRspIncInfo.ulNewAddr = uwNewAddr;

    memcpy((void *)pstIncSave, (VOID *)uwOldAddr, sizeof(SETPEG_JMP_ST));
    memcpy((void *)uwOldAddr, (void *)&stRspIncInfo, sizeof(SETPEG_JMP_ST));

    //SRE_DCacheFlush((VOID *)uwOldAddr, sizeof(SETPEG_JMP_ST), 1);
    //SRE_ICacheInv((VOID *)uwOldAddr, sizeof(SETPEG_JMP_ST), 1);
    SRE_CacheUpdate((VOID *)uwOldAddr, sizeof(SETPEG_JMP_ST), 1);

    (VOID)SRE_IntRestore(uvIntSave);
    return SRE_OK;

}

UINT32 CLEAN_PEG(VOID *pOldFunc, SETPEG_JMP_ST stIncSave)
{
    UINT32 uvIntSave;

    uvIntSave = SRE_IntLock();

    memcpy((VOID *)pOldFunc, (VOID *)&stIncSave, sizeof(SETPEG_JMP_ST));
    SRE_DCacheFlush((VOID *)pOldFunc, sizeof(SETPEG_JMP_ST), 1);
    SRE_ICacheInv((VOID *)pOldFunc, sizeof(SETPEG_JMP_ST), 1);

    (VOID)SRE_IntRestore(uvIntSave);
    return SRE_OK;
}

#elif (OS_HARDWARE_PLATFORM == OS_CORTEX_A9)
UINT32 SET_PEG(VOID *pOldFunc, VOID *pNewFunc, SETPEG_JMP_ST *pstIncSave)
{
	return SRE_OK;
}

UINT32 CLEAN_PEG(VOID *pOldFunc, SETPEG_JMP_ST stIncSave)
{
	return SRE_OK;
}

#endif

UINT32 SRE_ErrHandle_Stub( CHAR *pcFileName,
                     UINT32 uwLineNo,
                     UINT32 uwErrorNo,
                     UINT32 uwParaLen,
                     VOID  *pPara )
{
    return uwErrorNo;
}

VOID osSpinOnHwSemInt_Stub(UINT16 usHwSemId)
{
    return;
}

VOID SRE_HwSemPend_Stub(UINT16 usHwSemId)
{
    return;
}

VOID SRE_HwSemPost_Stub(UINT16 usHwSemId)
{
    return;
}

UINT32 SRE_HwSemIrqPend_Stub(UINT16 usHwSemId)
{
    return 0;
}

VOID SRE_HwSemIrqPost_Stub(UINT16 usHwSemId, UINT32 uwIntSave)
{
    return;
}
#ifndef CI_SIM_PAT_TEST
#define CI_SIM_PAT_TEST_1 1
#else
#define CI_SIM_PAT_TEST_1 0
#endif
#if (((OS_HARDWARE_PLATFORM == OS_DSP220) || (OS_HARDWARE_PLATFORM == OS_RISC220) || (OS_HARDWARE_PLATFORM == OS_HACCC)) && (CI_SIM_PAT_TEST_1 == 1))

extern UINT32 osGetCoreID();
extern VOID   _PostResetVector();

extern UINT32 _data_table_start;
extern UINT32 _data_table_end;
extern UINT32 _data_bak_start;
extern UINT32 _data_bak_end;
extern UINT32 _reboot_flag;
extern UINT32 _reboot_suit_idx;
extern UINT32 _reboot_case_idx;
extern UINT32 iCunit_Case_Idx;
extern UINT32 iCunit_Suit_Idx;
extern UINT32 iCunit_bak_buff;

VOID osRestoreFromExc(UINT32 uwRet, EXC_REGS_S *pstRegs)
{
    /*
        a1 = pstRegs->auwA[1];
        a0 = pstRegs->auwA[0];
        PS = pstRegs->uwPS & (~PS.EXCM)
        return uwRet;
    */
    g_bExcSaveFlag = FALSE;
    OS_EMBED_ASM("mov    a2, %0                          \n\
                  mov    a3, %1                          \n\
                                                         \n\
                  mov    a12, a12                         \n\
                  rotw   3                               \n\
                  mov    a12, a12                         \n\
                  rotw   3                               \n\
                  mov    a12, a12                         \n\
                  rotw   3                               \n\
                  mov    a12, a12                         \n\
                  rotw   3                               \n\
                  mov    a12, a12                          \n\
                  rotw   4                               \n\
                                                         \n\
                  movi   a0, 0                           \n\
                  l32i   a1, a3, 36                      \n\
                  l32i   a0, a3, 32                      \n\
                  l32i   a3, a3, 4                       \n\
                  movi   a4, 0xFFFFFFEF                  \n\
                  and    a3, a3, a4                      \n\
                  wsr    a3, ps                          \n\
                  rsync                                  \n\
                 " : : "a"(uwRet), "a"(pstRegs));
}


#if 0
OS_SEC_TEXT_INIT UINT32 ExcInfoCheckHook(UINT32 uwA0, UINT32 uwA1, UINT32 uwThreadType, UINT32 uwExcType)
{
    if((g_pstExcInfo->stRegInfo.uwPC >= g_uwExcPC) && (g_pstExcInfo->stRegInfo.uwPC <= (g_uwExcPC + 0x50))) //PC指针在合理范围内
    {
        //OK
    }
    else
    {
        //NOK
        fprintf(stderr, "ExcPc:%x, SavePc:%x\r\n", g_uwExcPC, g_pstExcInfo->stRegInfo.uwPC);
        ICUNIT_ASSERT_EQUAL(g_uwExcPC, g_pstExcInfo->stRegInfo.uwPC, g_uwExcPC);
    }

    ICUNIT_ASSERT_EQUAL(g_pstExcInfo->uwThread, uwThreadType, g_pstExcInfo->uwThread);//线程类型
    ICUNIT_ASSERT_EQUAL(g_pstExcInfo->stRegInfo.uwEXCCAUSE, uwExcType, g_pstExcInfo->stRegInfo.uwEXCCAUSE);//异常类型
    ICUNIT_ASSERT_EQUAL(g_pstExcInfo->stRegInfo.auwA[1], uwA1, g_pstExcInfo->stRegInfo.auwA[1]); //a1寄存器,保存了当前栈指针

    return SRE_OK;
}

OS_SEC_TEXT_INIT UINT32 TEST_RebootHookAdd(REBOOT_HOOK pfnHook, UINT32 uwPara1, UINT32 uwPara2, UINT32 uwPara3, UINT32 uwPara4)
{
    UINT32 uwA0 = 0;

    /*确保寄存器压栈*/
    OS_EMBED_ASM("  xor     a12, a12, a12        \n\
                    rotw    3                    \n\
                    mov     a12, a0              \n\
                    rotw    3                    \n\
                    mov     a7, a7               \n\
                    rotw    2                    \n\
                 " : : : "a7", "a12");

    g_pfnRebootHook = ExcInfoCheckHook;

    g_uwPara[0] = uwPara1;
    g_uwPara[1] = uwPara2;
    g_uwPara[2] = uwPara3;
    g_uwPara[3] = uwPara4;

    OS_EMBED_ASM("  mov    %0, a0" : "=a" (uwA0));
    uwA0 &= 0x3FFFFFFF;

    return uwA0;
}

OS_SEC_TEXT_INIT VOID TEST_Reboot()
{
    UINT32  *pResetVectorAddr;

    pResetVectorAddr = _PostResetVector;

    _reboot_flag = 1;
    _reboot_case_idx = iCunit_Case_Idx;
    _reboot_suit_idx = iCunit_Suit_Idx;

    OS_EMBED_ASM("mov    a2, %0              \n\
                            jx a2                          \n\
                 " : : "a"(pResetVectorAddr));
}


OS_SEC_TEXT_INIT VOID SRE_Reboot_Stub(VOID)
{
    volatile UINT32 vuwLoop;
    UINT32  uwRet = 0;

    g_uwHwResetFlag = 1;

    TEST_Reboot();

    #if 0

    if ((g_stCdaInfoAddr->uwExcFlag != 0xff) && (NULL != g_pfnRebootHook))
    {
        /*调用结果比较钩子函数*/
        uwRet = g_pfnRebootHook(g_uwPara[0], g_uwPara[1], g_uwPara[2], g_uwPara[3]);

        /*复位*/
        TEST_Reboot();
    }
    else
    {
        /*提示复位*/
        SRE_IntUnLock();
        iCunitPrintCurrentCase();
        for (vuwLoop = 0; vuwLoop < 50000000; vuwLoop++)
        {
            /* Wait for HWWDG to reboot board. */
        }
    }

    #endif

    return;
}


/*****************************************************************************
Function    : _save_restore_data_section
Description : 第一次运行时,保存DATA段,后续再运行时,恢复第一次保存的DATA段
Input       : None
Output      : None
Return      : None
Other       : None
*****************************************************************************/
OS_SEC_TEXT_INIT UINT32 _save_restore_data_section()
{
    UINT32 *puwDataTabStart;
    UINT32 *puwDataTabEnd;
    UINT8  *pucBakBuffStart;
    UINT8  *pucBakBuffEnd;
    UINT32 uwBakBufLen;      /*每个核实际可用的备份区长度*/
    UINT32 uwIndex;
    UINT32 uwLength;
    UINT32 uwDataTotLen = 0;
    volatile UINT32 uwStart;
    volatile UINT32 uwEnd;
    volatile char *p;

    puwDataTabStart = (UINT32*)(&_data_table_start);
    puwDataTabEnd   = (UINT32*)(&_data_table_end);

    if (0 == _reboot_flag)
    {
        /*第一次启动*/
        if ((NULL == puwDataTabStart) || (NULL == puwDataTabEnd) || (puwDataTabStart >= puwDataTabEnd))
        {
            return (UINT32)-1;
        }

        pucBakBuffStart = (UINT8*)(&_data_bak_start);
        pucBakBuffEnd   = (UINT8*)(&_data_bak_end);
        if ((NULL == pucBakBuffStart) || (NULL == pucBakBuffEnd) || (pucBakBuffStart >= pucBakBuffEnd))
        {
            return (UINT32)-2;
        }

        if (osGetCoreID() >= 20)
        {
            return (UINT32)-3; /*按照6181的规格，目前最多支持20个核*/
        }

        /*计算数据备份区的起始地址和大小*/
        uwBakBufLen = ((UINT32)pucBakBuffEnd - (UINT32)pucBakBuffStart) / 20;
        pucBakBuffStart += (uwBakBufLen * osGetCoreID()); /*备份区的cache line对齐，由LSP配置保证*/
        iCunit_bak_buff = (UINT32)pucBakBuffStart;

        /*检查备份区是否足够大*/
        while (puwDataTabStart < puwDataTabEnd)
        {
            uwStart = puwDataTabStart[0];
            uwEnd   = puwDataTabStart[1];

            if ((uwStart < uwEnd) && (uwStart < 0x10000000))
            {
                uwDataTotLen += (uwEnd - uwStart);
            }
            puwDataTabStart += 2;
        }
        if (uwDataTotLen > uwBakBufLen)
        {
            return (UINT32)-4;
        }

        /*以下申请释放操作操作主要是保证后续fopen等函数可用*/
        p = (UINT8 *)malloc(1000);
        free(p);

        /*保存数据至备份区*/
        puwDataTabStart = (UINT32*)(&_data_table_start);
        while (puwDataTabStart < puwDataTabEnd)
        {
            uwStart = puwDataTabStart[0];
            uwEnd   = puwDataTabStart[1];

            if ((uwStart < uwEnd) && (uwStart < 0x10000000))
            {
                uwLength = (UINT32)(uwEnd - uwStart);
                memcpy((VOID*)pucBakBuffStart, (VOID*)uwStart, uwLength);
                pucBakBuffStart += uwLength;
            }

            puwDataTabStart += 2;
        }
        SRE_DCacheFlush((VOID*)iCunit_bak_buff, uwDataTotLen, 1);
    }
    else
    {
        /*发生过复位*/
        pucBakBuffStart = (UINT8 *)iCunit_bak_buff;

        /*从备份区恢复数据*/
        while (puwDataTabStart < puwDataTabEnd)
        {
            uwStart = puwDataTabStart[0];
            uwEnd   = puwDataTabStart[1];

            if ((uwStart < uwEnd) && (uwStart < 0x10000000))
            {
                uwLength = (UINT32)(uwEnd - uwStart);
                SRE_DCacheInv((VOID*)pucBakBuffStart, uwLength, 1);
                memcpy((VOID*)uwStart, (VOID*)pucBakBuffStart, uwLength);
                pucBakBuffStart += uwLength;
            }

            puwDataTabStart += 2;
        }

    }

    return SRE_OK;
}

#endif


#if 1 /*异常复位自动化用单核复位自动化代替，以下代码可以注掉*/
VOID SRE_Reboot_Stub(VOID)
{
    volatile UINT32 vuwLoop;
    UINT32  uwRet = 0;

    //if ((g_stCdaInfoAddr->uwExcFlag != 0xff) && (NULL != g_pfnRebootHook))
    //{
        /*调用结果比较钩子函数*/
    //uwRet = g_pfnRebootHook(g_uwPara[0], g_uwPara[1], g_uwPara[2], g_uwPara[3]);

    /*恢复异常前的状态*/
    //g_stCdaInfoAddr->uwExcFlag = 0xff;
    g_uwCurNestCount--;
    g_vuwIntCount--;
    if (0 == g_vuwIntCount)
    {
        g_vuwUniFlag &= (~OS_FLG_HWI_ACTIVE);
    }
    g_pfnRebootHook = NULL;
    g_uwNMIErrFlag  = 0;

    /*恢复异常现场*/
    osRestoreFromExc(uwRet, &(g_pstExcInfo->stRegInfo));
    return;
}
#endif

#elif((OS_HARDWARE_PLATFORM == OS_DSP170) || (OS_HARDWARE_PLATFORM == OS_RISC170))
VOID osRestoreFromExc(UINT32 uwRet, EXC_REGS_S *pstRegs)
{
    /*
        a1 = pstRegs->auwA[1];
        a0 = pstRegs->auwA[0];
        PS = pstRegs->uwPS & (~PS.EXCM)
        return uwRet;
    */
    g_bExcSaveFlag = FALSE;
    OS_EMBED_ASM("mov    a2, %0                          \n\
                  mov    a3, %1                          \n\
                                                         \n\
                  mov    a12, a12                         \n\
                  rotw   3                               \n\
                  mov    a12, a12                         \n\
                  rotw   3                               \n\
                  mov    a7, a7                         \n\
                  rotw   2                               \n\
                                                         \n\
                  movi   a0, 0                           \n\
                  l32i   a1, a3, 36                      \n\
                  l32i   a0, a3, 32                      \n\
                  l32i   a3, a3, 4                       \n\
                  movi   a4, 0xFFFFFFEF                  \n\
                  and    a3, a3, a4                      \n\
                  wsr    a3, ps                          \n\
                  rsync                                  \n\
                 " : : "a"(uwRet), "a"(pstRegs));
}

#if 1 /*异常复位自动化用单核复位自动化代替，以下代码可以注掉*/
VOID SRE_Reboot_Stub(VOID)
{
    volatile UINT32 vuwLoop;
    UINT32  uwRet = 0;

    //if ((g_stCdaInfoAddr->uwExcFlag != 0xff) && (NULL != g_pfnRebootHook))
    //{
        /*调用结果比较钩子函数*/
    //uwRet = g_pfnRebootHook(g_uwPara[0], g_uwPara[1], g_uwPara[2], g_uwPara[3]);

    /*恢复异常前的状态*/
    //g_stCdaInfoAddr->uwExcFlag = 0xff;
    g_uwCurNestCount--;
    g_vuwIntCount--;
    if (0 == g_vuwIntCount)
    {
        g_vuwUniFlag &= (~OS_FLG_HWI_ACTIVE);
    }
    g_pfnRebootHook = NULL;
    g_uwNMIErrFlag  = 0;

    /*恢复异常现场*/
    osRestoreFromExc(uwRet, &(g_pstExcInfo->stRegInfo));

    return;
}
#endif

#else
VOID SRE_Reboot_Stub(VOID)
{
    volatile UINT32 vuwLoop;

    /*????*/
    SRE_IntUnLock();
    iCunitPrintCurrentCase();
    for (vuwLoop = 0; vuwLoop < 50000000; vuwLoop++)
    {
        /* Wait for HWWDG to reboot board. */
    }
    return;
}

#endif

#ifdef __cplusplus
#if __cplusplus
}
#endif /* __cpluscplus */
#endif /* __cpluscplus */

