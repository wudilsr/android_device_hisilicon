#include "ClientLog.h"
#include <stdarg.h>
#include <android/log.h>
#define NOCLIENTLOGOUT 0
#define  NOLOG 1
bool ClientLog::isInitialized = false;
FILE* ClientLog::log;
#if NOCLIENTLOGOUT
#define TAG "CLIENTLOG"
void ClientLog::open()
{
    if(!isInitialized)
    {
        isInitialized = true;
    }
}
void ClientLog::logOut(char *fmt,...)
{
#if  NOLOG
    return;
#endif
    char tmpBuffer[1024];
    va_list vl;
    va_start(vl, fmt);
    vsnprintf(tmpBuffer,1024,fmt,vl);
    va_end(vl);
    __android_log_print(ANDROID_LOG_ERROR, TAG, "AV_LOG_WARNING: %s",tmpBuffer);
}

void ClientLog::close()
{
//    fclose(log);
    isInitialized = false;
}

#else
void ClientLog::open()
{
    if(!isInitialized)
    {
        log = fopen("/sdcard/clientlog.txt","a+");
        isInitialized = true;
    }
}
void ClientLog::logOut(char *fmt,...)
{
#if  NOLOG
    return;
#endif
    va_list args;
    if(!isInitialized)
    {
        open();
    }
    if (log)
    {
        va_start(args, fmt);
        vfprintf(log,fmt,args);
        va_end(args);
        fprintf(log,"\n");
        fflush(log);
    }
}

void ClientLog::close()
{
    fclose(log);
    isInitialized = false;
}
#endif
