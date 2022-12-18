#include <stdio.h>
#include <stdlib.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <pthread.h>
#include <malloc.h>
#include <string.h>
#include <semaphore.h>
#include "hi_drv_vinput.h"
#include "android_vinput_inter.h"

#define  Vinput_FILE "/dev/vinput"
#define  VINPUT_LOG(fmt ...) printf(fmt)

static int s_fdVinput = -1;

int Hi_Vinput_Init()
{

	s_fdVinput = open(Vinput_FILE,O_RDONLY);
	if(s_fdVinput < 0)
	{
			VINPUT_LOG("can't open Vinput,%s\n", Vinput_FILE);
			return -1;
	}

	return s_fdVinput;
}

int Hi_Vinput_DeInit(void)
{

	if(s_fdVinput > 0)
	{
		VINPUT_LOG("close vinput device\n");
		close(s_fdVinput);
		s_fdVinput=-1;
	}
	return 0;
}

int ReportKeyEvent(int iKeyValue,int iStatus)
{
	int mousedata[4];

	if( s_fdVinput < 0)
	{
		VINPUT_LOG("Vinput not init\n");
		return -1;
	}

	mousedata[0]=iKeyValue;
	mousedata[1]=iStatus;
	mousedata[2]=0;
	mousedata[3]=0;

	ioctl(s_fdVinput,IOCTK_KBD_STATUS,(void *)mousedata);

	return 0;
}

int ReportMouseState(int key,int dx,int dy)
{
	int mousedata[4];

	if( s_fdVinput < 0)
	{
		VINPUT_LOG("key Vinput not init\n");
		return -1;
	}

	mousedata[0]=key;
	mousedata[1]=dx;
	mousedata[2]=dy;
	mousedata[3]=0;

	ioctl(s_fdVinput,IOCTL_MOUSE_STATUS,(void *)mousedata);

	return 0;
}
