#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include "tee_client_api.h"
#include "tee_client_id.h"
#include "tee_client_time_api.h"
#include <unistd.h>

#define DEFAULT_TIMES   5

int main(int argc, char* argv[])
{
    struct timeval tv;
    int i, times;

    if(argc == 1)
        times = DEFAULT_TIMES;
    else{
        times = atoi(argv[1]);
        if(times == 0)
            times = DEFAULT_TIMES;
    }

    printf("start get tee time every second in %d seconds:\n", times);
    for(i=0; i<times; i++){
        TEEC_GetTEETime(&tv);
        printf("tee time is second:%d, usec:%d\n", tv.tv_sec, tv.tv_usec);
        sleep(1);
    }

    return 0;
}
