#include <stdio.h>
#include "hi_log.h"
#include "svr_debug.h"
SVR_MODULE_DECLARE("COMMONMOD");
int main()
{
// HI_SYS_SetLogLevel((HI_MOD_ID_E)MODULE_ID,HI_LOG_LEVEL_DBG);
#if HI_OS_TYPE == HI_OS_LINUX
  printf("os type is linux \n");
#endif

#ifndef HI_ADVCA_FUNCTION_RELEASE
   printf("make hi_log_outputf effect\n");
#else
   printf("make hi_log_outputf  not effect\n");
#endif


#ifndef DISCARD_DEBUG_INFO
  printf("using debug info \n");
#else
  printf("not using debug info \n");
#endif

    printf("log level %d \n",SVR_LOG_LEVEL);

//    HI_LOG_Init();
    printf("hello world \n");
 //   sleep(1000);
    HI_LOG_INFO("info level yzp ");
    HI_LOG_DEBUG("debug level yzp ");
    HI_LOG_ERROR("error level yzp ");
    HI_LOG_ERROR_NO(666,"error level with number ,yzp");
    HI_LOG_FATAL(888,"fatal level yzp");

  //  HI_LOG_DeInit();
    return 0;
}
