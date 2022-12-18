#include <binder/IPCThreadState.h>
#include <pthread.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/BinderService.h>
#include <fcntl.h>
#include <HiAoService.h>
#include <hardware_legacy/uevent.h>
#include <utils/Log.h>
#include <hi_unf_hdmi.h>
using namespace android;
#define LOG_TAG "AOService"
#define HDMI_SWITCH_PATH "/sys/class/switch/hdmi/state"
char* hdmi_event = "change@/devices/virtual/switch/hdmi";
HI_UNF_EDID_BASE_INFO_S  st_edid;
static void SetAudCapByHDMI()
{
	HI_U32 TureHDMaxChan = 2;
	HI_S32 ret;
	ret = HI_UNF_HDMI_GetSinkCapability(HI_UNF_HDMI_ID_0,&st_edid);
	if(ret != HI_SUCCESS)
	{
		TureHDMaxChan = 2;
	}
	else
	{
		for(int i=0;i<st_edid.u32AudioInfoNum;i++)
		{
			if(st_edid.stAudioInfo[i].enAudFmtCode == HI_UNF_EDID_AUDIO_FORMAT_CODE_MAT)
			{
				if(TureHDMaxChan < st_edid.stAudioInfo[i].u8AudChannel)
					TureHDMaxChan = st_edid.stAudioInfo[i].u8AudChannel;
			}
		}
	}
	HiAoService::setAudEdidCap(TureHDMaxChan);
}
static void read_path(const char* path, char* buf, size_t size)
{
	int fd = open(path, O_RDONLY, 0);
	int count;

	if (fd < 0) {
		ALOGE("Could not open %s", path);
		return;
	}
	count = read(fd, buf, size);

	close(fd);
}


static void handle_uevent(const char* udata)
{
	const char *str = udata;
	char hdmi[2];
	memset(hdmi, 0, 2);
	ALOGI("hdmi_observer  %s",str);
	if (!strncmp(str, hdmi_event, strlen(hdmi_event))){
	    read_path(HDMI_SWITCH_PATH, hdmi, 1);
        if ( (!strncmp(hdmi, "1", 1)) )
        {
            ALOGI("strncmp(hdmi,1)");
            SetAudCapByHDMI();
        }
        if((!strncmp(hdmi, "0", 1)))
        {
            ALOGI("strncmp(hdmi,0)");
            HiAoService::setAudEdidCap(0);// hdmi plug off ,edid is 0
        }
    }
}

void *thread_loop(void* arg)
{
	ALOGI("aoservice thead_loop start");
	int len = 0;
	static char udata[4096];
	memset(udata, 0, sizeof(udata));
	uevent_init();
	while (1) {
		len = uevent_next_event(udata, sizeof(udata) - 2);
		handle_uevent(udata);
	}
	return 0;
}

int main(int argc, char** argv)
{
	int ret;
	HI_UNF_HDMI_OPEN_PARA_S st_default;
	pthread_t observer_thread;
	HI_UNF_HDMI_Init();
	st_default.enDefaultMode = HI_UNF_HDMI_DEFAULT_ACTION_HDMI;
	HI_UNF_HDMI_Open(HI_UNF_HDMI_ID_0,&st_default);
	ret = pthread_create(&observer_thread, NULL, thread_loop, NULL);//service
	if(ret!=0)
		ALOGI("HDMI Observer thread create fail");
	else
		ALOGI("HDMI observer thread create success");
    sp<ProcessState> proc(ProcessState::self());
    HiAoService::instantiate();
    SetAudCapByHDMI();
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
