#include "sre_ticktimer.h"

extern void uart_printf_func(const char *fmt, ...);

struct snprintf_ctxt
{
    char *next;
    int avail;
};

#define UART_PRINTF_TIME(fmt, args...) \
    ({\
        TEE_Date_Time_kernel date_time;\
        get_sys_date_time(&date_time);\
        uart_printf_func("%s%d/%d/%d %d:%d:%d.%d %s: " fmt "", "[TIME]",\
        date_time.month,date_time.day,date_time.year,date_time.hour,date_time.min,date_time.seconds,date_time.millis,\
        __FUNCTION__, ## args);\
    })
