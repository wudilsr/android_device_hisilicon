 /**
  * @file:
  *
  * Copyright(C), 2010-2050, Huawei Tech. Co., Ltd. ALL RIGHTS RESERVED. \n
  *
  * @description£º
  */

#ifdef __cplusplus
#if __cplusplus
 extern "C" {
#endif /* __cpluscplus */
#endif /* __cpluscplus */


#include "sre_config.h"
#include "sre_sem.ph"
#include "sre_task.h"
#include "sre_swi.h"
#include "sre_hwi.h"
#include "sre_mem.h"
#include "sre_sys.h"
#include "sre_sys.ph"
//#include "sre_sync.ph"
#include "sre_task.ph"
#include "sre_list.ph"
#include "sre_hunt.h"
#include "osTest.h"
#include "app_data_common.h"
#include "Set_Peg.h"

 //extern UINT32 osMcComEnQ(UINT32 uwDstPid, UINT8  ucOprtType, UINT32 uwOprtNum);
 static SEM_HANDLE_T   gs_uwSemHandle;
 static UINT32   uwSemCount = 0;
 EXTERN_FAR UINT16        g_usMaxSem;
 EXTERN_FAR LIST_OBJECT_S g_stUnusedSemList;
 extern UINT32 osSemRegister(const SEM_MOD_INFO_S *pstModInfo);

 OS_SEC_TEXT_UT VOID *  UTest_MemAlloc_Sem_Stub()
 {
     return NULL;
 }
 /**
 *@test UT_SRE_Sem_001
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ´´½¨ÐÅºÅÁ¿£¬ÊäÈëÐÅºÅÁ¿¼ÆÊýÖµºÏ·¨£¨0 ¡« 0xFFFFFFFE)£¬ÐÅºÅÁ¿²Ù×÷¾ä±úºÏ·¨(²»ÎªNULL)£¬´´½¨ÐÅºÅÁ¿³É¹¦¡£
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ´´½¨ÐÅºÅÁ¿£¬ÊäÈëÐÅºÅÁ¿¼ÆÊýÖµºÏ·¨£¨0 ¡« 0xFFFFFFFE)£¬ÐÅºÅÁ¿²Ù×÷¾ä±úºÏ·¨(²»ÎªNULL)£¬
 *-@texpect
 *-# ´´½¨ÐÅºÅÁ¿³É¹¦
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_001()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemCreate(0XFFFFFFFE, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_002
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ´´½¨ÐÅºÅÁ¿£¬ÊäÈëÐÅºÅÁ¿¼ÆÊýÖµ0XFFFFFFFF£¬ÐÅºÅÁ¿²Ù×÷¾ä±úºÏ·¨(²»ÎªNULL)£¬´´½¨ÐÅºÅÁ¿Ê§°Ü¡£
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ´´½¨ÐÅºÅÁ¿£¬ÊäÈëÐÅºÅÁ¿¼ÆÊýÖµ0XFFFFFFFF£¬ÐÅºÅÁ¿²Ù×÷¾ä±úºÏ·¨(²»ÎªNULL)£¬
 *-@texpect
 *-# ´´½¨ÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_002()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0XFFFFFFFF, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_003
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ´´½¨ÐÅºÅÁ¿£¬ÊäÈëÐÅºÅÁ¿¼ÆÊýÖµºÏ·¨£¨0 ¡« 0xFFFFFFFE)£¬ÐÅºÅÁ¿²Ù×÷¾ä±úÎªNULL£¬´´½¨ÐÅºÅÁ¿Ê§°Ü¡£
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ´´½¨ÐÅºÅÁ¿£¬ÊäÈëÐÅºÅÁ¿¼ÆÊýÖµ0£¬ÐÅºÅÁ¿²Ù×÷¾ä±úÎªNULL
 *-@texpect
 *-# ´´½¨ÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_003()
 {
     UINT32 uwRet;
     SEM_HANDLE_T *uwSemHandle = NULL;

     uwRet = __SRE_SemCreate(0, uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_PTR_NULL, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_004
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ´´½¨ÐÅºÅÁ¿£¬Á¬Ðø´´½¨ÅäÖÃ×î´óÖ§³ÖµÄÐÅºÅÁ¿Êý£¬ÔÙ´´½¨ÐÅºÅÁ¿Ê±£¬´´½¨Ê§°Ü£¬·µ»Ø´íÎóÂëOS_ERRNO_SEM_ALL_BUSY£»
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ´´½¨ÐÅºÅÁ¿£¬Á¬Ðø´´½¨ÅäÖÃ×î´óÖ§³ÖµÄÐÅºÅÁ¿Êý£¬ÔÙ´´½¨ÐÅºÅÁ¿
 *-@texpect
 *-# ´´½¨ÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_004()
 {
     UINT32 uwRet;
     UINT32 uwLoop;
     SEM_HANDLE_T uwSemHandle[11] ;

     for(uwLoop = 0; uwLoop < g_usMaxSem ; uwLoop++)
     {
         uwRet = __SRE_SemCreate(0, &uwSemHandle[uwLoop]);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }
     uwRet = __SRE_SemCreate(0, &uwSemHandle[uwLoop]);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_ALL_BUSY, uwRet);

     for(uwLoop = 0; uwLoop < g_usMaxSem ; uwLoop++)
     {
         uwRet = __SRE_SemDelete(uwSemHandle[uwLoop]);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_005
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ´´½¨Ò»¸öÐÅºÅÁ¿£¬¸ù¾ÝÊäÈëµÄÐÅºÅÁ¿¾ä±ú£¬É¾³ý¸ÃÐÅºÅÁ¿£¬ÐÅºÅÁ¿¾ä±úºÏ·¨£¬É¾³ý³É¹¦
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ´´½¨Ò»¸öÐÅºÅÁ¿£¬¸ù¾ÝÊäÈëµÄÐÅºÅÁ¿¾ä±ú£¬É¾³ý¸ÃÐÅºÅÁ¿£¬ÐÅºÅÁ¿¾ä±úºÏ·¨£¬É¾³ý³É¹¦
 *-@texpect
 *-# É¾³ýÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_005()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_006
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle É¾³ýÐÅºÅÁ¿£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬É¾³ýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# É¾³ýÐÅºÅÁ¿£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬É¾³ýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# É¾³ýÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_006()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_007
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle É¾³ýÐÅºÅÁ¿£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬É¾³ýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# É¾³ýÐÅºÅÁ¿£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬É¾³ýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# É¾³ýÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_007()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_008
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle É¾³ýÐÅºÅÁ¿£¬´«ÈëµÄÐÅºÅÁ¿¾ä±úºÏ·¨£¬µ«ÐÅºÅÁ¿ÉÏÓÐ×èÈûµÄÈÎÎñ£¬É¾³ýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_PendED
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# É¾³ýÐÅºÅÁ¿£¬´«ÈëµÄÐÅºÅÁ¿¾ä±úºÏ·¨£¬µ«ÐÅºÅÁ¿ÉÏÓÐ×èÈûµÄÈÎÎñ£¬É¾³ýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_PendED
 *-@texpect
 *-# É¾³ýÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_008_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet;
    UINT32 uwTaskPID;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_008()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_008_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_PENDED, uwRet, EXIT2);



 EXIT2:
     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     __SRE_SemDelete(uwSemHandle);
     __SRE_TaskDelete(uwTaskPid1);
     return ICUNIT_SUCCESS;
 EXIT1:
     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_009
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# PENDÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_009()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_010
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# PENDÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_010()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }



 /**
 *@test UT_SRE_Sem_011
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼äÎª0£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_UNAVAILABLE
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼äÎª0£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_UNAVAILABLE
 *-@texpect
 *-# PENDÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_011()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPend(uwSemHandle, 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_UNAVAILABLE, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_012
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬Èç¹ûÊÇÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿ö£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_Pend_INTERR
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬Èç¹ûÊÇÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿ö£¬PendÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_Pend_INTERR
 *-@texpect
 *-# PENDÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_012_swi(UINT32 uwValue)
 {

     UINT32 uwRet;

     uwRet = __SRE_SemPend(gs_uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_PEND_INTERR, uwRet);

     return;

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_012()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     SWI_INIT_PARA_S pstInitPara;
     SWI_PRIOR_T usPrior = 4;
     UINT32  uwInitValue = 0x01;
     UINT32  uwSwiHandle = 0;

     uwRet = __SRE_SemCreate(0,  &gs_uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstInitPara.pfnHandler =  UT__SRE_SemPend_012_swi;
     pstInitPara.pcSwiName = "Sem_UT";
     pstInitPara.usPriority = usPrior;
     pstInitPara.uwInitValue = uwInitValue;

     uwRet = __SRE_SwiCreate(&uwSwiHandle,&pstInitPara);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SwiActivate(uwSwiHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     uwRet = __SRE_SwiDelete(uwSwiHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(gs_uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

 }



 /**
 *@test UT_SRE_Sem_013
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬Èç¹ûÈÎÎñ±»Ëø£¬Pend
 ÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_Pend_IN_LOCK
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬Èç¹ûÈÎÎñ±»Ëø£¬Pend
 ÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_Pend_IN_LOCK
 *-@texpect
 *-# PENDÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_013_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     UINT32 uwTaskPID;

     __SRE_TaskLock();
     uwRet = __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_PEND_IN_LOCK, uwRet);
     __SRE_TaskUnlock();

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_013()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_013_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};


     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet , EXIT1);

     EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }




 /**
 *@test UT_SRE_Sem_014
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬ÈÎÎñÎ´±»Ëø£¬µÈ´ýÊ±¼äÎª
 0xFFFFFFFF
 £¬ÈÎÎñ×èÈûÓÚÐÅºÅÁ¿Pend,·¢ÉúÈÎÎñÇÐ»»£¬Ö±ÖÁÐÅºÅÁ¿ÓÐ¿ÕÏÐ
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬ÈÎÎñÎ´±»Ëø£¬µÈ´ýÊ±¼äÎª0xFFFFFFFF
 £¬ÈÎÎñ×èÈûÓÚÐÅºÅÁ¿Pend,·¢ÉúÈÎÎñÇÐ»»£¬Ö±ÖÁÐÅºÅÁ¿ÓÐ¿ÕÏÐ
 *-@texpect
 *-# pendÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_014_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_014()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_014_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     __SRE_TaskDelay(10);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_015
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬ÈÎÎñÎ´±»Ëø£¬µÈ´ýÊ±¼äÎª1¡«
 0xFFFFFFFE
 £¬ÈÎÎñ×èÈûÓÚÐÅºÅÁ¿Pend,·¢ÉúÈÎÎñÇÐ»»£¬ÈçÔÚµÈ´ýÊ±¼äÄÚÐÅºÅÁ¿Î´»ñÈ¡µ½£¬ÔòPendÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_TIMEOUT
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬ÈÎÎñÎ´±»Ëø£¬µÈ´ýÊ±¼äÎª1¡«
 0xFFFFFFFE
 £¬ÈÎÎñ×èÈûÓÚÐÅºÅÁ¿Pend,·¢ÉúÈÎÎñÇÐ»»£¬ÈçÔÚµÈ´ýÊ±¼äÄÚÐÅºÅÁ¿Î´»ñÈ¡µ½£¬ÔòPendÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_TIMEOUT
 *-@texpect
 *-# PENDÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_015_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
    UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x10);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_TIMEOUT, uwRet);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_015()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_015_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
     __SRE_TaskDelay(20);

 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_016
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬ÈÎÎñÎ´±»Ëø£¬µÈ´ýÊ±¼äÎª1¡«
 0xFFFFFFFE
 £¬ÈÎÎñ×èÈûÓÚÐÅºÅÁ¿Pend,·¢ÉúÈÎÎñÇÐ»»£¬ÈçÔÚµÈ´ýÊ±¼äÄÚÓÐÐÅºÅÁ¿¿ÕÏÐ£¬Pend³É¹¦¡£
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PendÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µÈ´ýÊ±¼ä·Ç0£¬ÇÒ²»ÔÚÖÐ¶Ï£¨ÈíÖÐ¶Ï,Ó²ÖÐ¶Ï£©Çé¿öÏÂ£¬ÈÎÎñÎ´±»Ëø£¬µÈ´ýÊ±¼äÎª1¡«
 0xFFFFFFFE
 £¬ÈÎÎñ×èÈûÓÚÐÅºÅÁ¿Pend,·¢ÉúÈÎÎñÇÐ»»£¬ÈçÔÚµÈ´ýÊ±¼äÄÚÓÐÐÅºÅÁ¿¿ÕÏÐ£¬Pend³É¹¦¡£
 *-@texpect
 *-# PENDÐÅºÅÁ¿³É¹¦
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_016_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x20);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_016()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_016_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     __SRE_TaskDelay(10);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }



 /**
 *@test UT_SRE_Sem_017
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PostÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬PostÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PostÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬PostÐÅºÅÁ¿Ê§°Ü£¬·µ»Ø·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# POSTÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_017()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_018
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PostÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬PostÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PostÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬PostÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# POSTÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_018()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_019
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PostÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨ÐÅºÅÁ¿¼ÆÊýÖµÎª0XFFFFFFFE£©£¬PostÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_OVERFLOW
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PostÐÅºÅÁ¿Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨ÐÅºÅÁ¿¼ÆÊýÖµÎª0XFFFFFFFE£©£¬PostÐÅºÅÁ¿Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_OVERFLOW
 *-@texpect
 *-# POSTÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_019()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0XFFFFFFFE, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_020
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PostÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬ÈçÓÐÈÎÎñ×èÈûÓÚ¸ÃÐÅºÅÁ¿£¬»Ö¸´×èÈûµÄµÚÒ»¸öÈÎÎñ£¬·¢ÉúÈÎÎñÇÐ»»¡£
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PostÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬ÈçÓÐÈÎÎñ×èÈûÓÚ¸ÃÐÅºÅÁ¿£¬»Ö¸´×èÈûµÄµÚÒ»¸öÈÎÎñ£¬·¢ÉúÈÎÎñÇÐ»»¡£
 *-@texpect
 *-# POSTÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_020_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
    UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x100);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
     if(uwRet == SRE_OK)
     {

         uart_printf("task1 pend sem success!");
     }

         uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_020_tsk2(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
    UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(uwParam1, 0x100);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);
     if(uwRet == SRE_OK)
     {

         uart_printf("task2 pend sem success!");
     }

        uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_020()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_020_tsk1, 20, 0, {0}, 0x600, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam2 = {UT__SRE_SemPend_020_tsk2, 21, 0, {0}, 0x600, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     __SRE_TaskDelay(10);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }
     if (uwTaskPid2  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid2);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_021
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle PostÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬Ã»ÓÐÈÎÎñ×èÈûÓÚ¸ÃÐÅºÅÁ¿£¬ÐÅºÅÁ¿¼ÆÊýÖµ+1¡£
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# PostÐÅºÅÁ¿Ê±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬Ã»ÓÐÈÎÎñ×èÈûÓÚ¸ÃÐÅºÅÁ¿£¬ÐÅºÅÁ¿¼ÆÊýÖµ+1¡£
 *-@texpect
 *-# POSTÐÅºÅÁ¿³É¹¦
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_021()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);


     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     ICUNIT_GOTO_EQUAL(uwSemCount, 1, uwSemCount, EXIT);

 EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_022
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»Ø·µ»Ø
 OS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»Ø·µ»Ø
 OS_ERRNO_SEM_INVALID
 *-@texpect
 *-# RESETÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_022()
 {
     UINT32 uwRet;
     UINT32 uwCount;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemReset(uwSemHandle , 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_023
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# RESETÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_023()
 {
     UINT32 uwRet;
     UINT32 uwCount;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemReset(uwSemHandle , 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_024
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨ÐÅºÅÁ¿¼ÆÊýÖµÎª0XFFFFFFFF£©£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_OVERFLOW
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨ÐÅºÅÁ¿¼ÆÊýÖµÎª0XFFFFFFFF£©£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_OVERFLOW
 *-@texpect
 *-# RESETÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_024()
 {
     UINT32 uwRet;
     UINT32 uwCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemReset(uwSemHandle, 0XFFFFFFFF);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet, EXIT);

     EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_025
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µ«ÓÐÈÎÎñ¹Ò½ÓÔÚ´ýÖØÉèµÄÐÅºÅÁ¿Á´±íÖÐ£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_PENDED
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬µ«ÓÐÈÎÎñ¹Ò½ÓÔÚ´ýÖØÉèµÄÐÅºÅÁ¿Á´±íÖÐ£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_PENDED
 *-@texpect
 *-# resetÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPend_025_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     UINT32 uwRet;
     uwRet = __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

 }
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_025()
 {

     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPend_016_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     uwRet = __SRE_SemReset(uwSemHandle, 1);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_PENDED, uwRet, EXIT1);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

 EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }

     return ICUNIT_SUCCESS;
 }



 /**
 *@test UT_SRE_Sem_026
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle
 ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬ÎÞÈÎÎñ¹Ò½ÓÔÚ´ýÖØÉèµÄÐÅºÅÁ¿Á´±íÖÐ£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµ³É¹¦£¬ÐÅºÅÁ¿ÖµÐÞ¸ÄÎªÉè¶¨¼ÆÊýÖ
 µ
 *-@tbrief
 *-#
 ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµÊ±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬ÎÞÈÎÎñ¹Ò½ÓÔÚ´ýÖØÉèµÄÐÅºÅÁ¿Á´±íÖÐ£¬ÖØÉèÐÅºÅÁ¿¼ÆÊýÖµ³É¹¦£¬ÐÅºÅÁ¿ÖµÐÞ¸ÄÎªÉè¶¨¼ÆÊýÖ
 µ
 *-@texpect
 *-# RESETÐÅºÅÁ¿³É¹¦
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_026()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemReset(uwSemHandle, 1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(uwSemCount, 1, uwSemCount, EXIT);

     EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_027
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle »ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬»ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ§°Ü£¬·µ»Ø·µ»Ø
 OS_ERRNO_SEM_GET_COUNT_ERR
 *-@tbrief
 *-# »ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬»ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ§°Ü£¬·µ»Ø·µ»Ø
 OS_ERRNO_SEM_GET_COUNT_ERR
 *-@texpect
 *-# »ñÈ¡ÐÅºÅÁ¿¼ÆÊýÊ§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_027()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = 11;

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_GET_COUNT_ERR, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *@test UT_SRE_Sem_028
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle »ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬»ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_GET_COUNT_ERR
 *-@tbrief
 *-# »ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬»ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ§°Ü£¬·µ»ØOS_ERRNO_SEM_GET_COUNT_ERR
 *-@texpect
 *-# »ñÈ¡ÐÅºÅÁ¿¼ÆÊýÊ§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_028()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = 2;

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_GET_COUNT_ERR, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *@test UT_SRE_Sem_029
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle »ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬»ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊý³É¹¦£¬·µ»Ø¸ÃÐÅºÅÁ¿¼ÆÊýÖµ
 *-@tbrief
 *-# »ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊýÊ±£¬´«ÈëºÏ·¨ÐÅºÅÁ¿¾ä±ú£¬»ñÈ¡Ö¸¶¨ÐÅºÅÁ¿¼ÆÊý³É¹¦£¬·µ»Ø¸ÃÐÅºÅÁ¿¼ÆÊýÖµ
 *-@texpect
 *-# »ñÈ¡ÐÅºÅÁ¿¼ÆÊý³É¹¦
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_029()
 {
     UINT32 uwRet;
     UINT32 uwSemCount;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     ICUNIT_GOTO_EQUAL(uwSemCount, 0, uwSemCount, EXIT);

     EXIT:
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);


     return ICUNIT_SUCCESS;
 }



 /**
 *-@test UT_SRE_Sem_030
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨´óÓÚÅäÖÃÐÅºÅÁ¿×î´ó¸öÊý£©£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 *-@texpect
 *-# »ñÈ¡Ê§°Ü
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_030()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];


     uwRet = __SRE_SemPendListGet(11, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_031
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INVALID
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«Èë·Ç·¨ÐÅºÅÁ¿¾ä±ú£¨¸ÃÐÅºÅÁ¿Î´±»´´½¨£©£¬»ñÈ¡Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INVALID
 *-@texpect
 *-# »ñÈ¡Ê§°Ü
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_031()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];


     uwRet = __SRE_SemPendListGet(2, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_032
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬Ö¸¶¨³¤¶ÈÎª0£¬»ñÈ¡Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬Ö¸¶¨³¤¶ÈÎª0£¬»ñÈ¡Ê§°Ü£¬·µ»ØOS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# »ñÈ¡Ê§°Ü
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_032()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];

     uwRet = __SRE_SemPendListGet(2, &uwTskCnt, auwPidBuf, 0);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_ERROR, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_033
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬PENDÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñ¸öÊýÖ¸ÕëÎªNULL£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬PENDÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñ¸öÊýÖ¸ÕëÎªNULL£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# »ñÈ¡Ê§°Ü
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_033()
 {
     UINT32 uwRet;
     UINT32 auwPidBuf[10];

     uwRet = __SRE_SemPendListGet(2, NULL, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_ERROR, uwRet);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_034
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«ÈëµÄ´æ´¢ÈÎÎñPIDµÄÄÚ´æÇøÓòÊ×µØÖ··Ç·¨£¨ÎªNULL)£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INPUT_ERROR
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«ÈëµÄ´æ´¢ÈÎÎñPIDµÄÄÚ´æÇøÓòÊ×µØÖ··Ç·¨£¨ÎªNULL)£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INPUT_ERROR
 *-@texpect
 *-# »ñÈ¡Ê§°Ü
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_034()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[10];

     uwRet = __SRE_SemPendListGet(2, &uwTskCnt, NULL, sizeof(auwPidBuf));
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_ERROR, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *-@test UT_SRE_Sem_035
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬»ñÈ¡µÄÈÎÎñ¸öÊýÖµ·Ç·¨£¨ÄÚ´æ²»×ã£©£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬»ñÈ¡µÄÈÎÎñ¸öÊýÖµ·Ç·¨£¨ÄÚ´æ²»×ã£©£¬»ñÈ¡Ê§°Ü£¬·µ»Ø
 OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH
 *-@texpect
 *-# »ñÈ¡Ê§°Ü
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPendListGet_035_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

         uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_035()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2];
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPendListGet_035_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam2 = {UT__SRE_SemPendListGet_035_tsk, 21, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);


     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf[1]));
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH, uwRet, EXIT1);

     EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }
     if (uwTaskPid2  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid2);
     }

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_036
 *-@tspec  ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle  »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«Èë²ÎÊýºÏ·¨£¬ÇÒÄÚ´æÄÜ´æ´¢ËùÓÐPIDÇåµ¥£¬»ñÈ¡³É¹¦
 *-@tbrief
 *-# »ñÈ¡×èÈûÔÚÖ¸¶¨ºËÄÚÐÅºÅÁ¿µÄÈÎÎñPIDÇåµ¥Ê±£¬´«Èë²ÎÊýºÏ·¨£¬ÇÒÄÚ´æÄÜ´æ´¢ËùÓÐPIDÇåµ¥£¬»ñÈ¡³É¹¦
 *-@texpect
 *-# »ñÈ¡³É¹¦
 *-@tprior  1
 *-@tauto TRUE
 *-@tremark ALL
 */
 OS_SEC_TEXT_UT VOID UT__SRE_SemPendListGet_036_tsk(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_036()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2];
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;

     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT__SRE_SemPendListGet_036_tsk, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam2 = {UT__SRE_SemPendListGet_036_tsk, 21, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);


     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, sizeof(auwPidBuf));
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT1);
     ICUNIT_GOTO_EQUAL(uwTskCnt, 2, uwTskCnt, EXIT1);

     EXIT1:

     if (uwSemHandle  != (UINT32)-1)
     {
         __SRE_SemDelete(uwSemHandle);
     }
     if (uwTaskPid1  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid1);
     }
     if (uwTaskPid2  != (UINT32)-1)
     {
         __SRE_TaskDelete(uwTaskPid2);
     }

     return ICUNIT_SUCCESS;
 }


 /**
 *-@test UT_SRE_Sem_037
 *-@tspec
 *-@ttitle
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_037()
 {
     UINT32 uwRet;
     SEM_MOD_INFO_S stModInfo;

     stModInfo.usMaxNum = 0;

     uwRet = osSemRegister(&stModInfo);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_REG_ERROR, uwRet);

     stModInfo.usMaxNum = 10;

     uwRet = osSemRegister(&stModInfo);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return ICUNIT_SUCCESS;
 }


 /**
 *-@test UT_SRE_Sem_038
 *-@tspec
 *-@ttitle
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_038()
 {
     UINT32  uwRet;
     UINT16  usMaxNumBak = 0;

     usMaxNumBak = g_usMaxSem;

     g_usMaxSem = 0;

     uwRet = osSemInit();
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      g_usMaxSem = 10;

     uwRet = osSemInit();
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     g_usMaxSem = usMaxNumBak;

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE__sem_init_039
 *-@tspec  »ñÈ¡×èÈûÓÚºËÄÚÐÅºÅÁ¿ÉÏµÄÈÎÎñÇåµ¥
 *-@ttitle  ¿ÕÖ¸Õë
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_039()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;
     UINT32 uwCount;
     UINT32 *pstSemLisg;

     uwRet = __SRE_SemCreate(0xffffffff, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet);

     pstSemLisg  = (UINT32 *)g_stUnusedSemList.pstNext;

     g_stUnusedSemList.pstNext = &g_stUnusedSemList;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_ALL_BUSY, uwRet);

     g_stUnusedSemList.pstNext = (struct tagListObject *)pstSemLisg;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }

 /**
 *-@test UT_SRE_Sem_038
 *-@tspec  »ñÈ¡×èÈûÓÚºËÄÚÐÅºÅÁ¿ÉÏµÄÈÎÎñÇåµ¥
 *-@ttitle  ¿ÕÖ¸Õë
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_040()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;
     UINT32 uwCount;
     SEM_CB_S *pstSemDeleted;
     UINT16 usCpySemStat;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstSemDeleted = GET_SEM(uwSemHandle);
     usCpySemStat = pstSemDeleted->usSemStat;

     pstSemDeleted->usSemStat = 0;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet);

     pstSemDeleted->usSemStat = usCpySemStat;

     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }


 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_041()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     SEM_CB_S  *pstSemPended;
     UINT32 uwCpyCnt = 0;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     uwRet = __SRE_SemPend(0xffff, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INVALID, uwRet, EXIT);

     pstSemPended = GET_SEM(uwSemHandle);

     uwCpyCnt = pstSemPended->uwSemCount;

     pstSemPended->uwSemCount = 1;

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     pstSemPended->uwSemCount = 0;

     uwRet = __SRE_SemPend(uwSemHandle, 0);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_UNAVAILABLE, uwRet, EXIT);

     pstSemPended->uwSemCount = uwCpyCnt;

 EXIT:
     pstSemPended->uwSemCount = uwCpyCnt;
     if (uwSemHandle != (UINT32)-1) __SRE_SemDelete(uwSemHandle);

     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_042()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     SEM_CB_S  *pstSemPosted;
     UINT32 uwCpyCnt = 0;
  //   LIST_OBJECT_S    *pstSemList;

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstSemPosted = GET_SEM(uwSemHandle);

     uwCpyCnt = pstSemPosted->uwSemCount;

     pstSemPosted->uwSemCount = OS_SEM_COUNT_MAX;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet, EXIT);

     pstSemPosted->uwSemCount = uwCpyCnt;

     __SRE_TaskLock();

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_PEND_IN_LOCK, uwRet, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:

     pstSemPosted->uwSemCount = uwCpyCnt;
     __SRE_TaskUnlock();
     if (uwSemHandle != (UINT32)-1) __SRE_SemDelete(uwSemHandle);

     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_043()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;
     UINT32 uwSemCount;

     uwRet = __SRE_SemCreate(1,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     __SRE_TaskLock();

     uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(uwSemCount, 0, uwSemCount, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemCountGet(uwSemHandle, &uwSemCount);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(uwSemCount, 1, uwSemCount, EXIT);

 EXIT:
     __SRE_TaskUnlock();
     uwRet = __SRE_SemDelete(uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_044()
 {
     UINT32 uwRet;

     uwRet = __SRE_SemCreate(2,   NULL);
     ICUNIT_ASSERT_NOT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_045()
 {
     UINT32 i;
     UINT32 j;
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle[OS_SEM_MAX_SUPPORT_NUM+1];

     for (i = 0; i < OS_SEM_MAX_SUPPORT_NUM; i++)
     {
         uwRet = __SRE_SemCreate(2,  &uwSemHandle[i]);
         j = i;
         ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, CLEAN_UP);
     }
     j = OS_SEM_MAX_SUPPORT_NUM;
     uwRet = __SRE_SemCreate(2,  &uwSemHandle[OS_SEM_MAX_SUPPORT_NUM]);
     ICUNIT_GOTO_EQUAL( uwRet, OS_ERRNO_SEM_ALL_BUSY, uwRet, CLEAN_UP);

 CLEAN_UP:
     for (i = 0; i < j; i++)
     {
       uwRet = __SRE_SemDelete(uwSemHandle[i]);
       ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }

     return SRE_OK;
 }

 /**
 *@test UT_SRE_Sem_046
 *-@tspec ÐÅºÅÁ¿Ä£¿é²âÊÔ
 *-@ttitle ´´½¨ÐÅºÅÁ¿£¬´«ÈëuwCountÎª0xffffffff
 *-@tprecon ºËÄÚÐÅºÅÁ¿Ä£¿é¿ª¹Ø´ò¿ª
 *-@tbrief
 *-# ´´½¨ÐÅºÅÁ¿
 *-@texpect
 *-# ´´½¨ÐÅºÅÁ¿Ê§°Ü
 *-@tprior 1
 *-@tauto TRUE
 *-@tremark ALL
  */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_046()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle;

     uwRet = __SRE_SemCreate(0xffffffff,  &uwSemHandle);
     ICUNIT_ASSERT_NOT_EQUAL(uwRet, SRE_OK, uwRet);

     return SRE_OK;
 }


 /**
 *-@test UT_SRE_Sem_007
 *-@tspec  »ñÈ¡×èÈûÓÚºËÄÚÐÅºÅÁ¿ÉÏµÄÈÎÎñÇåµ¥
 *-@ttitle  ÓÐÈÎÎñ×èÈûÓÚºËÄÚÐÅºÅÁ¿
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_047()
 {
     UINT32 uwRet;
     SEM_HANDLE_T uwSemHandle = (UINT32)-1;
     SEM_CB_S  *pstSemPosted;
     UINT32 uwCpyCnt = 0;
 ///  LIST_OBJECT_S    *pstSemList;
 //    TSK_CB_S  *pstRunTsk;

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     pstSemPosted = GET_SEM(uwSemHandle);

     uwCpyCnt = pstSemPosted->uwSemCount;

     pstSemPosted->uwSemCount = OS_SEM_COUNT_MAX;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_OVERFLOW, uwRet, EXIT);

     pstSemPosted->uwSemCount = uwCpyCnt;

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:
     pstSemPosted->uwSemCount = uwCpyCnt;
     if (uwSemHandle != (UINT32)-1) __SRE_SemDelete(uwSemHandle);

     return ICUNIT_SUCCESS;
 }

 /**
 *-@test UT_SRE_Sem_048
 *-@tspec  »ñÈ¡×èÈûÓÚºËÄÚÐÅºÅÁ¿ÉÏµÄÈÎÎñÇåµ¥
 *-@ttitle  ÓÐÈÎÎñ×èÈûÓÚºËÄÚÐÅºÅÁ¿£¬µ«buf³¤¶È²»×ã
 *-@tprecon
 *-@tbrief
 *-@texpect
 *-@tprior  1
 *-@tremark
 */
 OS_SEC_TEXT_UT VOID UT_SRE_Sem_048_tsk2(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID = 0;

     __SRE_SemPend(uwParam1, OS_WAIT_FOREVER);

         uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT VOID UT_SRE_Sem_048_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
    UINT32 uwRet = 0;
    UINT32 uwTaskPID = 0;

     __SRE_SemPend(uwParam1, 10000);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_048()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2] = {(UINT32)-1, (UINT32)-1};
     SEM_HANDLE_T   uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT_SRE_Sem_048_tsk2, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_INIT_PARAM_S stInitParam2 = {UT_SRE_Sem_048_tsk1, 18, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     //SRE_WaitForAllCores();

     uwRet = __SRE_SemCreate(0,  &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, 4);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[0], uwTaskPid1, auwPidBuf[0], EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[1], (UINT32)-1, auwPidBuf[1], EXIT);
     ICUNIT_GOTO_EQUAL(uwTskCnt, 2, uwTskCnt, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:
     if (uwSemHandle  != (UINT32)-1) __SRE_SemDelete(uwSemHandle);
     if (uwTaskPid1   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid1);
     if (uwTaskPid2   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid2);
     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT VOID UT_SRE_Sem_049_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {

     UINT32 uwRet;
     UINT32 uwTaskPID;

     uwRet = __SRE_SemPend(gs_uwSemHandle, OS_WAIT_FOREVER);
     ICUNIT_ASSERT_EQUAL_VOID(uwRet, OS_ERRNO_SEM_PEND_INTERR, uwRet);

     if (gs_uwSemHandle != (UINT32)-1)
     {
         __SRE_SemDelete(gs_uwSemHandle);
     }

    uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);

     return;

 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_049()
 {
     UINT32 uwRet;
 //    UINT32 uwTskCnt;
 //    UINT32 auwPidBuf[2] = {(UINT32)-1, (UINT32)-1};
     SWI_INIT_PARA_S pstInitPara;
     SWI_PRIOR_T usPrior = 4;
     UINT32          uwInitValue = 0x01;
     UINT32          uwSwiHandle = 0;

     //SRE_WaitForAllCores();

     if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
     {
         uwRet = __SRE_SemCreate(0,  &gs_uwSemHandle);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

         pstInitPara.pfnHandler =  UT_SRE_Sem_049_tsk1;
         pstInitPara.pcSwiName = "Sem_UT";
         pstInitPara.usPriority = usPrior;
         pstInitPara.uwInitValue = uwInitValue;

         uwRet = __SRE_SwiCreate(&uwSwiHandle,&pstInitPara);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

         uwRet = __SRE_SwiActivate(uwSwiHandle);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
         uwRet = __SRE_SwiDelete(uwSwiHandle);
         ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);
     }
     else
     {
         __SRE_TaskDelay(10);
     }
     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT VOID UT_SRE_Sem_050_tsk1(UINT32 uwParam1, UINT32 uwParam2, UINT32 uwParam3, UINT32 uwParam4)
 {
     TSK_CB_S  *pstRunTsk;
     UINT32 uwRet = 0;
     UINT32 uwTaskPID;

     pstRunTsk = (TSK_CB_S *)g_pRunningTask;

     pstRunTsk->usTaskStatus |= 0x10;

     __SRE_SemPend(uwParam1, OS_ERRNO_SEM_TIMEOUT);

     uwRet = __SRE_TaskSelf(&uwTaskPID);
    ICUNIT_ASSERT_EQUAL_VOID(uwRet, SRE_OK, uwRet);

    __osTskExit(uwTaskPID);
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_050()
 {
     UINT32 uwRet;
     UINT32 uwTskCnt;
     UINT32 auwPidBuf[2] = {(UINT32)-1, (UINT32)-1};
     SEM_HANDLE_T   uwSemHandle = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid1   = (UINT32)-1;
     TSK_HANDLE_T   uwTaskPid2   = (UINT32)-1;
     TSK_INIT_PARAM_S stInitParam1 = {UT_SRE_Sem_050_tsk1, 20, 0, {0}, 0x400, "0", 0, 0, OS_MEM_DEFAULT_FSC_PT};
     TSK_INIT_PARAM_S stInitParam2 = {UT_SRE_Sem_050_tsk1, 18, 0, {0}, 0x400, "1", 0, 0, OS_MEM_DEFAULT_FSC_PT};

     //SRE_WaitForAllCores();

     uwRet = __SRE_SemCreate(0, &uwSemHandle);
     ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

     stInitParam1.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid1, &stInitParam1);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     stInitParam2.auwArgs[0] = uwSemHandle;
     uwRet = __SRE_TaskCreate(&uwTaskPid2, &stInitParam2);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

     uwRet = __SRE_SemPendListGet(uwSemHandle, &uwTskCnt, auwPidBuf, 4);
     ICUNIT_GOTO_EQUAL(uwRet, OS_ERRNO_SEM_INPUT_BUF_NOT_ENOUGH, uwRet, EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[0], uwTaskPid1, auwPidBuf[0], EXIT);
     ICUNIT_GOTO_EQUAL(auwPidBuf[1], (UINT32)-1, auwPidBuf[1], EXIT);
     ICUNIT_GOTO_EQUAL(uwTskCnt, 2, uwTskCnt, EXIT);

     uwRet = __SRE_SemPost(uwSemHandle);
     ICUNIT_GOTO_EQUAL(uwRet, SRE_OK, uwRet, EXIT);

 EXIT:
     if (uwSemHandle  != (UINT32)-1) __SRE_SemDelete(uwSemHandle);
     if (uwTaskPid1   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid1);
     if (uwTaskPid2   != (UINT32)-1) __SRE_TaskDelete(uwTaskPid2);
     return ICUNIT_SUCCESS;
 }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_051()
  {
      UINT32 uwRet;
      SEM_HANDLE_T uwSemHandle = (UINT32)-1;

      uwRet = __SRE_SemCreate(1, &uwSemHandle);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      uwRet = __SRE_SemPend(uwSemHandle, OS_WAIT_FOREVER);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      uwRet = __SRE_SemDelete(uwSemHandle);
      ICUNIT_ASSERT_EQUAL(uwRet, SRE_OK, uwRet);

      return ICUNIT_SUCCESS;
  }

 OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_052()
  {
      UINT32 uwRet;
      SEM_MOD_INFO_S stModInfo;
      stModInfo.usMaxNum = 0;
      uwRet = osSemRegister(&stModInfo);
      ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_REG_ERROR, uwRet);
      return ICUNIT_SUCCESS;
  }
#if 0
OS_SEC_TEXT_UT UINT32 UT_SRE_Sem_053()
{
    UINT32 uwRet;
    SETPEG_JMP_ST stRebootStub;
    UINT32 uvIntSave;
    SEM_CB_S *pstAllSem;

    uvIntSave = __SRE_IntLock();
    if(OS_SYS_CORE_MASTER == SRE_GetCoreID())
    {
        pstAllSem = g_pstAllSem;
        SET_PEG(SRE_MemAllocAlign, UTest_MemAlloc_Sem_Stub, (SETPEG_JMP_ST *)&stRebootStub);

        uwRet = osSemInit();
        ICUNIT_ASSERT_EQUAL(uwRet, OS_ERRNO_SEM_NO_MEMORY, uwRet);
        g_pstAllSem = pstAllSem;
        CLEAN_PEG(SRE_MemAllocAlign, stRebootStub);
    }
    (VOID)__SRE_IntRestore(uvIntSave);
    return ICUNIT_SUCCESS;
}
#endif
OS_SEC_TEXT_UT VOID UT_SRE_sem(void)
 {

     iUINT32 uiSuiteId;
     TEST_ADD_SUITE(uiSuiteId, "UT_SRE__sem");

     TEST_ADD_CASE(UT_SRE_Sem_001, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_002, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_003, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_004, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_005, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_006, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_007, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_008, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_009, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_010, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_011, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_012, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_013, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_014, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_015, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_016, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_017, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_018, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_019, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_020, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_021, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_022, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_023, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_024, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_025, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_026, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_027, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_028, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_029, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_030, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_031, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_032, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_033, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_034, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_035, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_036, uiSuiteId, Label_RUN);
     /* ------------ ¼Ì³ÐÓÃÀý -----------------------*/
     #if 0
     TEST_ADD_CASE(UT_SRE_Sem_037, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_038, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_039, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_040, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_041, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_042, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_043, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_044, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_045, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_046, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_047, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_048, uiSuiteId, Label_RUN);

     TEST_ADD_CASE(UT_SRE_Sem_049, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_050, uiSuiteId, Label_RUN);

     #endif

     TEST_ADD_CASE(UT_SRE_Sem_051, uiSuiteId, Label_RUN);
     TEST_ADD_CASE(UT_SRE_Sem_052, uiSuiteId, Label_RUN);
     //TEST_ADD_CASE(UT_SRE_Sem_053, uiSuiteId, Label_RUN);
     Label_RUN:
          TEST_RUN_SUITE(uiSuiteId);
 }

#ifdef __cplusplus
#if __cplusplus
 }
#endif /* __cpluscplus */
#endif /* __cpluscplus */

                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                            





                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                              