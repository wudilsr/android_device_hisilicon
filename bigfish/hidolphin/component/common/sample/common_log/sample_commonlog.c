#include <stdio.h>
#include "svr_debug.h"
SVR_MODULE_DECLARE("sample_log");


int main()
{
#if defined(HI_LOG_SUPPORT) && (0 == HI_LOG_SUPPORT)
printf("not define svr_debug\n");
#else
printf("define svr_debug\n");
#endif

    char* msg = "hisilicon";
    printf("%s\n",msg);
    printf("log level is %d\n",SVR_LOG_LEVEL);
    SVR_LOG_INFO("info level, %s \n", msg);
    SVR_LOG_WARN("warn level,%s\n", msg);
    SVR_LOG_ERROR("error level,%s\n",msg);
    SVR_LOG_FATAL("fatal level,%s\n",msg);

    char c;
    while(1)
    {
        scanf("%c",&c);
        if(c == 'q')
        {
            break;
        }
    }
    return 0;
}
