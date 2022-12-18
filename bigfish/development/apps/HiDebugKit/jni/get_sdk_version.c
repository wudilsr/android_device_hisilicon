#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <utils/Log.h>

#include "get_sdk_version.h"

HI_S32 HisiGetSDKVersion(HI_CHAR* Version)
{
	HI_SYS_VERSION_S stVersion;
	HI_S32 Ret = HI_SUCCESS;

	memset(&stVersion, 0, sizeof(stVersion));

	Ret = HI_SYS_GetVersion(&stVersion);
	if (HI_SUCCESS == Ret)
	{
	    strcpy(Version,stVersion.aVersion);
	}
	return Ret;
}

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */
