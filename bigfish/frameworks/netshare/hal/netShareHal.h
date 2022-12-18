#ifndef NETSHAEW_HAL_H_
#define NETSHAEW_HAL_H_
#include "IHiNSService.h"

int netShareChangePassword(const char *buff);
int netShareSambaStop();
int netShareSambaStart();
int netShareUnMount(const char *buf);
int netShareMount(const char *buf);
int netShareNssh(HI_NS_CMD_TYPE_E cmd ,const char *buf);

#endif
