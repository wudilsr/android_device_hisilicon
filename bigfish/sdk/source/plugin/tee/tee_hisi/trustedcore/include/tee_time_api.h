#ifndef __TEE_TIME_API_H
#define __TEE_TIME_API_H

#include "tee_internal_api.h"

#define TEE_TIMEOUT_INFINITE (0xFFFFFFFF)

typedef struct{
    uint32_t seconds;
    uint32_t millis;
}TEE_Time;

void get_sys_rtc_time(TEE_Time *time);

void TEE_GetSystemTime(TEE_Time* time);

TEE_Result TEE_Wait(uint32_t timeout);

TEE_Result TEE_GetTAPersistentTime(TEE_Time* time);

TEE_Result TEE_SetTAPersistentTime(TEE_Time* time);

void TEE_GetREETime(TEE_Time* time);

#endif
