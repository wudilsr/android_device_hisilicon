  /**
  * @file:
  *
  * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
  *
  * @description��
  */

 #ifdef __cplusplus
 #if __cplusplus
 extern "C" {
 #endif /* __cpluscplus */
 #endif /* __cpluscplus */

 #include "iCunit.h"
 #include "app_data_common.h"
 #include "Set_Peg.h"
 #include "sre_config.h"
  #include "sre_sys.h"
 #include "sre_mem.h"
 #include "sre_mem.ph"
 #include "osTest.h"

 extern UINT8 m_aucUtStmemRegion[UT_STATMEM_SIZE];
 extern UINT8 m_aucUtDymemRegion[0x00001500];
 extern UINT8 m_aucUtDynplmemRegion[0x00001500];
 extern UINT8 m_aucUtMcmemRegion[0x00005000];

 EXTERN_FAR MEM_PT_INFO_S  *m_astMemPtInfo;
 EXTERN_FAR MEM_PT_CHECK_S *g_astMemPtCheck;
 EXTERN_FAR UINT8  m_ucMaxPtNum;

 extern UINT32 osMemRegMemPtInfo(UINT8 scPtNo, UINT32 uwSize, VOID *pAddr,  OS_MEM_ARITH_E enArith);
 extern VOID Ut_MemPtDelete(UINT8 ucPtNo);

 /**
 *-@test  UT_SRE_MemUsageGet_001
 *-@tspec  ��ȡָ���ڴ�������ڴ�ռ���ʺ���SRE_MemUsageGet���ܲ��ԡ�
 *-@ttitle ��������ŷǷ���������ӦС����������
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemUsageGet_001(void)
 {
     UINT32 uwRet;
     UINT8  ucPtNo = 30;
     OS_MEM_PT_STATE stMemPtState;

     uwRet = __SRE_MemUsageGet(ucPtNo);
     ICUNIT_ASSERT_EQUAL(uwRet, 0, uwRet);

     return SRE_OK;
 }

 /**
 *-@test  UT_SRE_MemUsageGet_002
 *-@tspec  ��ȡָ���ڴ�������ڴ�ռ���ʺ���SRE_MemUsageGet���ܲ��ԡ�
 *-@ttitle ��ȡ˽��pool��̬�ڴ���Ϣ
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemUsageGet_002(void)
 {
     UINT32 uwRet;
     UINT8  ucPtNo = UT_MEM_PTNO;
     UINT32 uwUsage;
     UINT16 usSliceSize;

     OS_MEM_PT_STATE stMemPtStateNoAlloc;
     OS_MEM_PT_STATE stMemPtStateAlloced;
     MEM_CREATEPT_PARA stamemSt;

     UINT32 uwMemSize = 0x100;
     stamemSt.enArith = MEM_ARITH_POOL;
     stamemSt.pPtAddr = &m_aucUtDynplmemRegion[0];
     stamemSt.uwPtSize = 0x00001500;

     stamemSt.ausSliceSize[0] = 16;
     stamemSt.ausSliceSize[1] = 32;
     stamemSt.ausSliceSize[2] = 48;
     stamemSt.ausSliceSize[3] = 64;
     stamemSt.ausSliceSize[4] = 128;
     stamemSt.ausSliceSize[5] = 256;
     stamemSt.ausSliceSize[6] = 512;
     stamemSt.ausSliceSize[7] = 1024;

    //SRE_WaitForAllCores();

    if (m_astMemPtInfo[ucPtNo].bInstalled)
    {
        Ut_MemPtDelete(UT_MEM_PTNO);
    }

    //SRE_WaitForAllCores();

    /*����˽�ж�̬Pool�㷨�ڴ����*/
    uwRet= SRE_MemPtCreate(&stamemSt, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);

    /*��ȡ��ǰ˽�й���pool��̬�ڴ���Ϣ�������ڴ����ռ����*/
    uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateNoAlloc);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwUsage = 10000 * (stMemPtStateNoAlloc.uwPtSize - stMemPtStateNoAlloc.uwFreeSize) / stMemPtStateNoAlloc.uwPtSize;

    /*��ȡ�ڴ�ռ����*/
    uwRet = __SRE_MemUsageGet(ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet, uwUsage, uwRet);

    /*��˽�ж�̬pool��̬�ڴ������ڴ�*/
    SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

    /*��ȡ˽�ж�̬pool��̬�ڴ�����֮�����Ϣ�������ڴ�ռ����*/
    uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwUsage = 10000 * (stMemPtStateAlloced.uwPtSize - stMemPtStateAlloced.uwFreeSize) / stMemPtStateAlloced.uwPtSize;

    /*��ȡ�ڴ����ռ����*/
    uwRet = __SRE_MemUsageGet(ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet, uwUsage, uwRet);

    /* ʵ���ڴ���С=������ڴ���С+�ڴ�ͷ�Ĵ�С*/
    usSliceSize = m_ausSliceTypeToSize[ucPtNo][5];

    ICUNIT_ASSERT_EQUAL(usSliceSize, (stMemPtStateAlloced.uwPeakUsed - stMemPtStateNoAlloc.uwPeakUsed), usSliceSize);
    ICUNIT_ASSERT_EQUAL(usSliceSize, (stMemPtStateNoAlloc.uwFreeSize - stMemPtStateAlloced.uwFreeSize), usSliceSize);

    //SRE_WaitForAllCores();

    Ut_MemPtDelete(UT_MEM_PTNO);

    //SRE_WaitForAllCores();

    return SRE_OK;
 }

 /**
 *-@test  UT_SRE_MemUsageGet_003
 *-@tspec  ��ȡָ���ڴ�������ڴ�ռ���ʺ���SRE_MemUsageGet���ܲ��ԡ�
 *-@ttitle ��ȡ����pool��̬�ڴ���Ϣ
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemUsageGet_003(void)
 {
     //SRE_WaitForAllCores();

     UINT32 uwRet;
     UINT8  ucPtNo = UT_MEM_PTNO;
     UINT32 uwUsage1 = 0;
     UINT32 uwUsage2 = 0;
     UINT32 uwUsage3 = 0;
     UINT16 usSliceSize;

     OS_MEM_PT_STATE stMemPtStateNoAlloc;
     OS_MEM_PT_STATE stMemPtStateAlloced;

     UINT32 uwMemSize = 0x100;

     MEM_CREATEPT_PARA  stPara;

     stPara.enArith         = MEM_ARITH_MCPOOL;
     stPara.pPtAddr         = &m_aucUtMcmemRegion[0];
     stPara.uwPtSize        = 0x00005000;
     stPara.ausSliceSize[0] = 32;
     stPara.ausSliceSize[1] = 48;
     stPara.ausSliceSize[2] = 64;
     stPara.ausSliceSize[3] = 128;
     stPara.ausSliceSize[4] = 256;
     stPara.ausSliceSize[5] = 512;
     stPara.ausSliceSize[6] = 1024;
     stPara.ausSliceSize[7] = 2048;

    //SRE_WaitForAllCores();

    if (m_astMemPtInfo[ucPtNo].bInstalled)
    {
        Ut_MemPtDelete(UT_MEM_PTNO);
    }

    //SRE_WaitForAllCores();

    uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

    /*��ȡ��ǰ����Pool��̬�ڴ���Ϣ*/
    uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateNoAlloc);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwUsage1 = 10000 * (stMemPtStateNoAlloc.uwPtSize - stMemPtStateNoAlloc.uwFreeSize) / stMemPtStateNoAlloc.uwPtSize;

    /*��ȡ�ڴ����ռ����*/
    uwRet = __SRE_MemUsageGet(ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet, uwUsage1, uwRet);

    //SRE_WaitForAllCores();

    if ( OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        /*����Pool��̬�ڴ������ڴ�*/
        SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

        /*��ȡ����Pool��̬�ڴ�����֮�����Ϣ*/
        uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        uwUsage2 = 10000 * (stMemPtStateAlloced.uwPtSize - stMemPtStateAlloced.uwFreeSize) / stMemPtStateAlloced.uwPtSize;

        /*��ȡ�ڴ����ռ����*/
        uwRet = __SRE_MemUsageGet(ucPtNo);
        ICUNIT_ASSERT_EQUAL(uwRet, uwUsage2, uwRet);

        /* ʵ���ڴ���С����������ڴ���С���������ڴ�ͷ�Ĵ�С*/
        usSliceSize = m_ausSliceTypeToSize[ucPtNo][4];

        ICUNIT_ASSERT_EQUAL(usSliceSize, (stMemPtStateAlloced.uwPeakUsed - stMemPtStateNoAlloc.uwPeakUsed), usSliceSize);
        ICUNIT_ASSERT_EQUAL(usSliceSize, (stMemPtStateNoAlloc.uwFreeSize - stMemPtStateAlloced.uwFreeSize), usSliceSize);
    }

    //SRE_WaitForAllCores();

    if ( OS_SYS_CORE_MASTER != SRE_GetCoreID())
    {
        /*����Pool��̬�ڴ������ڴ�*/
        SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

        /*��ȡ����Pool��̬�ڴ�����֮�����Ϣ*/
        uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
        ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
        uwUsage3 = 10000 * (stMemPtStateAlloced.uwPtSize - stMemPtStateAlloced.uwFreeSize) / stMemPtStateAlloced.uwPtSize;

        /*��ȡ�ڴ����ռ����*/
        uwRet = __SRE_MemUsageGet(ucPtNo);
        ICUNIT_ASSERT_EQUAL(uwUsage1 < uwUsage3, 1, uwRet);
    }

    //SRE_WaitForAllCores();

    Ut_MemPtDelete(UT_MEM_PTNO);

    //SRE_WaitForAllCores();

    return SRE_OK;
 }

 /**
  *-@test  UT_SRE_MemUsageGet_004
  *-@tspec  ��ȡָ���ڴ�������ڴ�ռ���ʺ���SRE_MemUsageGet���ܲ��ԡ�
  *-@ttitle ��ȡ˽�ж�̬FSC�ڴ���Ϣ
  *-@tprecon
  *-@tbrief
  *-@texpect
  *-@tprior
  *-@tremark
  */
  OS_SEC_TEXT2_UT UINT32 UT_SRE_MemUsageGet_004(void)
  {
    UINT32 uwRet;
    UINT8  ucPtNo = UT_MEM_PTNO;
    UINT32 uwUsage;
    OS_MEM_PT_STATE stMemPtStateNoAlloc;
    OS_MEM_PT_STATE stMemPtStateAlloced;
    MEM_CREATEPT_PARA stamemSt;

    UINT32 uwMemSize = 0x100;
    stamemSt.enArith = MEM_ARITH_FSC;
    stamemSt.pPtAddr = &m_aucUtDynplmemRegion[0];
    stamemSt.uwPtSize = 0x00001500;

    //SRE_WaitForAllCores();

    if (m_astMemPtInfo[ucPtNo].bInstalled)
    {
      Ut_MemPtDelete(UT_MEM_PTNO);
    }

    //SRE_WaitForAllCores();

    /*����˽�ж�̬FSC�㷨�ڴ����*/
    uwRet= SRE_MemPtCreate(&stamemSt, ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);

    /*��ȡ��ǰ˽�ж�̬FSC�ڴ���Ϣ�������ڴ����ռ����*/
    uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateNoAlloc);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwUsage = 10000 * (stMemPtStateNoAlloc.uwPtSize - stMemPtStateNoAlloc.uwFreeSize) / stMemPtStateNoAlloc.uwPtSize;

    /*��ȡ�ڴ�ռ����*/
    uwRet = __SRE_MemUsageGet(ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet, uwUsage, uwRet);

    /*��˽�ж�̬FSC�ڴ������ڴ�*/
    SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

    /*��ȡ˽�ж�̬FSC�ڴ�����֮�����Ϣ�������ڴ�ռ����*/
    uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
    ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
    uwUsage = 10000 * (stMemPtStateAlloced.uwPtSize - stMemPtStateAlloced.uwFreeSize) / stMemPtStateAlloced.uwPtSize;

    /*��ȡ�ڴ����ռ����*/
    uwRet = __SRE_MemUsageGet(ucPtNo);
    ICUNIT_ASSERT_EQUAL(uwRet, uwUsage, uwRet);

    uwMemSize = uwMemSize + 0x10;

    /* ʵ���ڴ���С=������ڴ���С+�ڴ�ͷ�Ĵ�С*/
    ICUNIT_ASSERT_EQUAL(uwMemSize, (stMemPtStateAlloced.uwPeakUsed - stMemPtStateNoAlloc.uwPeakUsed), uwMemSize);
    ICUNIT_ASSERT_EQUAL(uwMemSize, (stMemPtStateNoAlloc.uwFreeSize - stMemPtStateAlloced.uwFreeSize), uwMemSize);

    //SRE_WaitForAllCores();

    Ut_MemPtDelete(UT_MEM_PTNO);

    //SRE_WaitForAllCores();

    return SRE_OK;
  }

 /**
  *-@test  UT_SRE_MemUsageGet_005
  *-@tspec  ��ȡָ���ڴ�������ڴ�ռ���ʺ���SRE_MemUsageGet���ܲ��ԡ�
  *-@ttitle ��ȡ����̬FSC�ڴ���Ϣ
  *-@tprecon
  *-@tbrief
  *-@texpect
  *-@tprior
  *-@tremark
  */
  OS_SEC_TEXT2_UT UINT32 UT_SRE_MemUsageGet_005(void)
  {
      UINT32 uwRet;
      UINT8  ucPtNo = UT_SRE_MCDYN_FSC_MEM_PTN0;
      UINT32 uwUsage1;
      UINT32 uwUsage2;
      UINT32 uwUsage3;

      OS_MEM_PT_STATE stMemPtStateNoAlloc;
      OS_MEM_PT_STATE stMemPtStateAlloced;

      UINT32 uwMemSize = 0x100;

      MEM_CREATEPT_PARA  stPara;

      stPara.enArith         = MEM_ARITH_MCDYNFSC;
      stPara.pPtAddr         = &m_aucUtMcmemRegion[0];
      stPara.uwPtSize        = 0x00005000;

      //SRE_WaitForAllCores();

      Ut_MemPtDelete(UT_MEM_PTNO);

      //SRE_WaitForAllCores();

      uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
      ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

      /*��ȡ��ǰ����̬FSC�ڴ���Ϣ*/
      uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateNoAlloc);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
      uwUsage1 = 10000 * (stMemPtStateNoAlloc.uwPtSize - stMemPtStateNoAlloc.uwFreeSize) / stMemPtStateNoAlloc.uwPtSize;

      /*��ȡ�ڴ����ռ����*/
      uwRet = __SRE_MemUsageGet(ucPtNo);
      ICUNIT_ASSERT_EQUAL(uwRet, uwUsage1, uwRet);

      //SRE_WaitForAllCores();

      if ( OS_SYS_CORE_MASTER == SRE_GetCoreID())
      {
          /*����̬FSC�ڴ������ڴ�*/
          SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

          /*��ȡ����̬FSC�ڴ�����֮�����Ϣ*/
          uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
          ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
          uwUsage2 = 10000 * (stMemPtStateAlloced.uwPtSize - stMemPtStateAlloced.uwFreeSize) / stMemPtStateAlloced.uwPtSize;

          /*��ȡ�ڴ����ռ����*/
          uwRet = __SRE_MemUsageGet(ucPtNo);
          ICUNIT_ASSERT_EQUAL(uwRet, uwUsage2, uwRet);

          /* ʵ���ڴ���С����������ڴ���С���������ڴ�ͷ�Ĵ�С*/
          ICUNIT_ASSERT_EQUAL(uwMemSize + 16, (stMemPtStateAlloced.uwPeakUsed - stMemPtStateNoAlloc.uwPeakUsed), uwMemSize);
          ICUNIT_ASSERT_EQUAL(uwMemSize + 16, (stMemPtStateNoAlloc.uwFreeSize - stMemPtStateAlloced.uwFreeSize), uwMemSize);
      }

      //SRE_WaitForAllCores();

      if ( OS_SYS_CORE_MASTER != SRE_GetCoreID())
      {
          /*����̬FSC�ڴ������ڴ�*/
          SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

          /*��ȡ����̬FSC�ڴ�����֮�����Ϣ*/
          uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
          ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
          uwUsage3 = 10000 * (stMemPtStateAlloced.uwPtSize - stMemPtStateAlloced.uwFreeSize) / stMemPtStateAlloced.uwPtSize;

          /*��ȡ�ڴ����ռ����*/
          uwRet = __SRE_MemUsageGet(ucPtNo);
          ICUNIT_ASSERT_EQUAL(uwUsage1 < uwUsage3, 1, uwRet);
      }

      //SRE_WaitForAllCores();

      Ut_MemPtDelete(UT_SRE_MCDYN_FSC_MEM_PTN0);

      //SRE_WaitForAllCores();

      return SRE_OK;
  }

 /**
  *-@test  UT_SRE_MemUsageGet_006
  *-@tspec  ��ȡָ���ڴ�������ڴ�ռ���ʺ���SRE_MemUsageGet���ܲ��ԡ�
  *-@ttitle ��ȡ����̬FSC�ڴ���Ϣ
  *-@tprecon
  *-@tbrief
  *-@texpect
  *-@tprior
  *-@tremark
  */
  OS_SEC_TEXT2_UT UINT32 UT_SRE_MemUsageGet_006(void)
  {
      UINT32 uwRet;
      UINT32 uwUsage;
      OS_MEM_PT_STATE stMemPtStateAlloc;

      //SRE_WaitForAllCores();

      /*��ȡ����̬FSC�ڴ���Ϣ*/
      uwRet = SRE_MemPtStateGet(1, &stMemPtStateAlloc);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
      uwUsage = 10000 * (stMemPtStateAlloc.uwPtSize - stMemPtStateAlloc.uwFreeSize) / stMemPtStateAlloc.uwPtSize;

      /*��ȡ�ڴ����ռ����*/
      uwRet = __SRE_MemUsageGet(1);
      ICUNIT_ASSERT_EQUAL(uwRet, uwUsage, uwRet);

      //SRE_WaitForAllCores();

      return SRE_OK;
  }

 /**
 *-@test  UT_SRE_MemPtStateGet_001
 *-@tspec  ��ѯָ���ڴ������ʷʹ�÷�ֵ��ʣ���ڴ����ʼ��ַ�ʹ�С����SRE_MemPtStateGet���ܲ��ԡ�
 *-@ttitle �������ָ��Ϊ��
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemPtStateGet_001(void)
 {
     UINT32 uwRet;
     UINT8  ucPtNo = UT_MEM_PTNO;

     OS_MEM_PT_STATE *pstMemPtState = NULL; //ָ��Ϊ��

     uwRet = SRE_MemPtStateGet(ucPtNo, pstMemPtState);

     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_INPUT_INVAILD, uwRet);

     return SRE_OK;
 }

 /**
 *-@test  UT_SRE_MemPtStateGet_002
 *-@tspec  ��ѯָ���ڴ������ʷʹ�÷�ֵ��ʣ���ڴ����ʼ��ַ�ʹ�С����SRE_MemPtStateGet���ܲ��ԡ�
 *-@ttitle ��������ŷǷ���������ӦС����������
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemPtStateGet_002(void)
 {
     UINT32 uwRet;
     UINT8  ucPtNo = 30;

     OS_MEM_PT_STATE stMemPtState;

     uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtState);

     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_MEM_NO_USE, uwRet);

     return SRE_OK;
 }

 /**
 *-@test  UT_SRE_MemPtStateGet_003
 *-@tspec  ��ѯָ���ڴ������ʷʹ�÷�ֵ��ʣ���ڴ����ʼ��ַ�ʹ�С����SRE_MemPtStateGet���ܲ��ԡ�
 *-@ttitle ��ȡ˽��pool��̬�ڴ���Ϣ
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemPtStateGet_003(void)
 {
     UINT32 uwRet;
     UINT8  ucPtNo = UT_MEM_PTNO;
     OS_MEM_PT_STATE stMemPtStateNoAlloc;
     OS_MEM_PT_STATE stMemPtStateAlloced;
     MEM_CREATEPT_PARA stamemSt;

     UINT32 uwMemSize = 0x100;
     stamemSt.enArith = MEM_ARITH_POOL;
     stamemSt.pPtAddr = &m_aucUtDynplmemRegion[0];
     stamemSt.uwPtSize = 0x00001500;

     stamemSt.ausSliceSize[0] = 16;
     stamemSt.ausSliceSize[1] = 32;
     stamemSt.ausSliceSize[2] = 48;
     stamemSt.ausSliceSize[3] = 64;
     stamemSt.ausSliceSize[4] = 128;
     stamemSt.ausSliceSize[5] = 256;
     stamemSt.ausSliceSize[6] = 512;
     stamemSt.ausSliceSize[7] = 1024;

     //SRE_WaitForAllCores();

     Ut_MemPtDelete(UT_MEM_PTNO);

     //SRE_WaitForAllCores();

     /*����˽�ж�̬Pool�㷨�ڴ����*/
     uwRet= SRE_MemPtCreate(&stamemSt, ucPtNo);
     ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);

     //SRE_WaitForAllCores();

     /*��ȡ��ǰ˽�й���pool��̬�ڴ���Ϣ*/
     uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateNoAlloc);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     /*��˽�ж�̬pool��̬�ڴ������ڴ�*/
     SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

     /*��ȡ˽�ж�̬pool��̬�ڴ�����֮�����Ϣ���鿴��Ϣ�Ƿ���ȷ*/
     uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     ICUNIT_ASSERT_EQUAL((uwMemSize + sizeof(OS_MEM_SLICE_CTRL_HEAD_S)), (stMemPtStateNoAlloc.uwFreeSize - stMemPtStateAlloced.uwFreeSize), uwMemSize);
     ICUNIT_ASSERT_EQUAL((uwMemSize + sizeof(OS_MEM_SLICE_CTRL_HEAD_S)), (stMemPtStateAlloced.uwPeakUsed - stMemPtStateNoAlloc.uwPeakUsed), uwMemSize);

     //SRE_WaitForAllCores();

     Ut_MemPtDelete(UT_MEM_PTNO);

     //SRE_WaitForAllCores();

     return SRE_OK;
 }

 /**
 *-@test  UT_SRE_MemPtStateGet_004
 *-@tspec  ��ѯָ���ڴ������ʷʹ�÷�ֵ��ʣ���ڴ����ʼ��ַ�ʹ�С����SRE_MemPtStateGet���ܲ��ԡ�
 *-@ttitle ��ȡ����pool��̬�ڴ���Ϣ
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior
 *-@tremark
 */
 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemPtStateGet_004(void)
 {
     UINT32 uwRet;
     UINT8  ucPtNo = UT_MEM_PTNO;
     UINT16 usSliceSize;

     OS_MEM_PT_STATE stMemPtStateNoAlloc;
     OS_MEM_PT_STATE stMemPtStateAlloced;

     UINT32 uwMemSize = 0x100;//����256��С���ڴ棬������Ҫ���Ͽ���ͷ��stPara.ausSliceSize[4]������������ڴ��С����stPara.ausSliceSize[5]

     MEM_CREATEPT_PARA  stPara;

     stPara.enArith         = MEM_ARITH_MCPOOL;
     stPara.pPtAddr         = &m_aucUtMcmemRegion[0];
     stPara.uwPtSize        = 0x00005000;
     stPara.ausSliceSize[0] = 32;
     stPara.ausSliceSize[1] = 48;
     stPara.ausSliceSize[2] = 64;
     stPara.ausSliceSize[3] = 128;
     stPara.ausSliceSize[4] = 256;
     stPara.ausSliceSize[5] = 512;
     stPara.ausSliceSize[6] = 1024;
     stPara.ausSliceSize[7] = 2048;

     //SRE_WaitForAllCores();

     Ut_MemPtDelete(UT_MEM_PTNO);

     //SRE_WaitForAllCores();

     /*����˽�ж�̬Pool�㷨�ڴ����*/
     uwRet = SRE_MemPtCreate(&stPara, ucPtNo);
     ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

     //SRE_WaitForAllCores();

     /*��ȡ��ǰ����Pool��̬�ڴ���Ϣ*/
     uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateNoAlloc);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     /*����Pool��̬�ڴ������ڴ�*/
     SRE_MemAlloc(OS_MID_SYS, ucPtNo, uwMemSize);

     /*��ȡ����Pool��̬�ڴ�����֮�����Ϣ���鿴��Ϣ�Ƿ���ȷ*/
     uwRet = SRE_MemPtStateGet(ucPtNo, &stMemPtStateAlloced);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     /* ʵ���ڴ���С����������ڴ���С���������ڴ�ͷ�Ĵ�С*/
     usSliceSize = m_ausSliceTypeToSize[ucPtNo][4];

     ICUNIT_ASSERT_EQUAL(usSliceSize, usSliceSize, (stMemPtStateAlloced.uwPeakUsed - stMemPtStateNoAlloc.uwPeakUsed));
     ICUNIT_ASSERT_EQUAL(usSliceSize, usSliceSize, (stMemPtStateNoAlloc.uwFreeSize - stMemPtStateAlloced.uwFreeSize));

     //SRE_WaitForAllCores();

     Ut_MemPtDelete(UT_MEM_PTNO);

     //SRE_WaitForAllCores();

     return SRE_OK;
 }

 /**
  *-@test  UT_SRE_MemMinor_001
  *-@tspec  ��ѯָ���ڴ������ʷʹ�÷�ֵ��ʣ���ڴ����ʼ��ַ�ʹ�С����SRE_MemPtStateGet���ܲ��ԡ�
  *-@ttitle ��ȡ����pool��̬�ڴ���Ϣ
  *-@tprecon
  *-@tbrief
  *-@texpect
  *-@tprior
  *-@tremark
  */

 OS_SEC_TEXT2_UT UINT32 UT_SRE_MemMinor_001(VOID)
 {
     UINT32 uwRet;
     MEM_CREATEPT_PARA StaTestSt;
     OS_MEM_PT_STATE pstMemPtState;

     StaTestSt.enArith = MEM_ARITH_FSC;
     StaTestSt.pPtAddr = m_aucUtStmemRegion;
     StaTestSt.uwPtSize = sizeof(m_aucUtStmemRegion);
     StaTestSt.bCachable = FALSE;

     //SRE_WaitForAllCores();

     uwRet = SRE_MemPtCreate(&StaTestSt,UT_MEM_PTNO);
     ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK,uwRet);

     uwRet = __SRE_MemUsageGet(UT_MEM_PTNO);
     ICUNIT_ASSERT_EQUAL(uwRet,39,uwRet);


     uwRet = SRE_MemPtStateGet(UT_MEM_PTNO,&pstMemPtState);
     ICUNIT_ASSERT_EQUAL(uwRet,SRE_OK, uwRet);

     ICUNIT_GOTO_EQUAL(pstMemPtState.uwPtSize, 4096, pstMemPtState.uwPtSize, ErrorHandle);
     ICUNIT_GOTO_EQUAL(pstMemPtState.uwPeakUsed, 16, pstMemPtState.uwPeakUsed, ErrorHandle);
     ICUNIT_GOTO_EQUAL(pstMemPtState.uwFreeSize, 4080, pstMemPtState.uwFreeSize, ErrorHandle);

     //SRE_WaitForAllCores();

     Ut_MemPtDelete(UT_MEM_PTNO);

     //SRE_WaitForAllCores();

     return SRE_OK;
 ErrorHandle:
     Ut_MemPtDelete(UT_MEM_PTNO);
     return SRE_OK;
 }

 OS_SEC_TEXT2_UT void UT_SRE_Mem_Minor(void)
 {
    iUINT32 uiSuiteId;

    TEST_ADD_SUITE(uiSuiteId, "UT_SRE_Mem_Minor");

    //SRE_WaitForAllCores();

    TEST_ADD_CASE(UT_SRE_MemUsageGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemUsageGet_002, uiSuiteId, Label_RUN);
   // TEST_ADD_CASE(UT_SRE_MemUsageGet_003, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemUsageGet_004, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MemUsageGet_005, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MemUsageGet_006, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_MemPtStateGet_001, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemPtStateGet_002, uiSuiteId, Label_RUN);
    TEST_ADD_CASE(UT_SRE_MemPtStateGet_003, uiSuiteId, Label_RUN);
    //TEST_ADD_CASE(UT_SRE_MemPtStateGet_004, uiSuiteId, Label_RUN);

    TEST_ADD_CASE(UT_SRE_MemMinor_001, uiSuiteId, Label_RUN);

    //SRE_WaitForAllCores();
    Ut_MemPtDelete(UT_MEM_PTNO);
    //SRE_WaitForAllCores();
 Label_RUN:
    TEST_RUN_SUITE(uiSuiteId);
    Ut_MemPtDelete(UT_MEM_PTNO);
 }

 #ifdef __cplusplus
 #if __cplusplus
 }
 #endif /* __cpluscplus */
 #endif /* __cpluscplus */


                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                 