#ifndef _CLIENT_LOG_
#define _CLIENT_LOG_

#include <stdlib.h>
#include <stdio.h>

#define RetrDebug 0
class ClientLog
    {
    public:
        static void logOut(char *fmt,...);
        static void open();
        static void close();
    private:
        static FILE* log;
        static bool isInitialized;
    };

#endif
