#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <string.h>
#include <pthread.h>

#include <assert.h>
#include <linux/fb.h>
#include <linux/input.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <cutils/properties.h>

#define LOGTAG "ir_user"
#include <utils/Log.h>

#include "InfraredService.h"
#include "android_ir_inter.h"

#include "android_vinput_inter.h"
#include "key_pars.h"

#include <binder/IPCThreadState.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>

#define  POWER_RESUME_SET 1

#ifdef  POWER_RESUME_SET
#include "hi_unf_pmoc.h"
#endif

#define MOUSE_MODE_EN             1
#define MOUSE_MAX_STEP            200
#define MOUSE_MIN_STEP            15
#define MOUSE_STEP                10

#define BROWSER_MOUSE_STEP        30
#define BROWSER_MOUSE_MIN_STEP    15
#define BROWSER_MOUSE_MAX_STEP    250


#define KPC_EV_KEY_PRESS          (0x1)
#define KPC_EV_KEY_RELEASE        (0x0)

#pragma GCC diagnostic ignored "-Wwrite-strings"
#pragma GCC diagnostic ignored "-fpermissive"

static int  g_mouse_move_step = MOUSE_MIN_STEP;
static int  debug_enable = 0;

#define KEY_ARRY_NUM 2
struct _key_arry keyarry[KEY_ARRY_NUM];

static char *prot_names[] =
{
    "nec full 2headers",
    "nec simple 2headers changshu",
    "nec simple uPD6121G like",
    "nec simple LC7461MCL13 like",
    "nec full dezhou like",
    "nec full huizhou like",
    "nec simple 2headers gd",
    "credit",
    "sony d7c5",
    "sony d7c8",
    "tc9012",
    "rc6 32bit data",
    "rc6 20bit data",
    "rc6 16bit data",
    "rc5 14bit data",
    "extended rc5 14bit"
};

void usage(char *base)
{
    printf("usage: %s [-m 0|1] [-u 0|1] [-U num] [-r 0|1] [-R num] [-T readtimeout] [-E 0|1]"\
            " [-g protocolname] [-l] [-s protocolname -e 0|1] [-h]\n"\
            "\t-m : key fetch mode, 0 to read key parsed by driver, 1 to read symbols received.\n"\
            "\t-u : set keyup event, 0 to disable keyup event, 1 to enable keyup event.\n"\
            "\t-U : set keyup timeout, e.g. -U 300, driver will send a keyup event of last key parsed.\n"\
            "\t     after 300ms if no follow key recevied. Not supported yet.\n"\
            "\t-r : set repeat key event report or not. 0 to disable repeat event, 1 to enable.\n"\
            "\t-R : set repeat key event interval time. Default 200ms.\n"\
            "\t     e.g. -R 100 was set, then driver will report a key repeat event each 100ms.\n"\
            "\t-T : set read timeout value. e.g. -T 1000 was set, then read syscall will return after 1000 ms if no key recevied.\n"\
            "\t-E : enable or disable ir module. 0 to disable, 1 to enable. If 1 is set, ir module will do nothing.\n"
            "\t-g : get the enable/disable status of protocol which is specified by protocolname and then exit.\n"\
            "\t-l : list all default protocol name and exit. Only constains IR module, no customer's included!\n"\
            "\t-s : set the enable/disable status of protocol which is specified by protocolname, 0 to enable, 1 to disable.\n"\
            "\t     while set disable state, the respect protocol will not be considerd as a protocol parser,\n"\
            "\t     and if some corresponding infrared symbol received, they are not parsed and may be discarded.\n"\
            "\t-e : 0 to enable, 1 to disable, must be used with -s\n"\
            "\t-h : display this message and exit.\n"\
            "\tNOTES: Only [-s -e] option can be set more than once!\n",
            base);
}

extern char *optarg;
extern int optind, opterr, optopt;

/*lint -save -e729 */
int mode, mode_set;
int keyup_event, keyup_event_set;
unsigned int keyup_timeout, keyup_timeout_set;
int repeat_event, repeat_event_set;
unsigned int repeat_interval, repeat_interval_set;
unsigned int read_timeout = 200;
int ir_enable, ir_enable_set;
int prot_status;
char *prot_name;
int prot_name_set;
int prot_enable, prot_enable_set;

int g_thread_should_stop = 0;

static int check_params(void)
{
    if (mode_set >  1 || ( mode != 0 && mode != 1)) {
        printf("fetch mode error!\n");
        return -1;
    }

    if (keyup_event_set > 1 || (keyup_event != 0 && keyup_event != 1)) {
        printf("keyup event error!\n");
        return -1;
    }
    if (repeat_event_set > 1 || repeat_interval_set > 1) {
        printf("Only -g [-s -e] option can be set more than once!\n");
        return -1;
    }
    return 0;
}
static int ir_get_prot_status(char *prot)
{
    int ret;
    BOOL enabled;

    ret = IR_Open();
    if (ret) {
        perror("Fail to open ir device!\n");
        return -1;
    }

    ret = IR_GetProtocolEnabled(prot, &enabled);
    if (ret) {
        IR_Close();
        printf("Fail to get protocol status!\n");
        return -1;
    }

    IR_Close();
    return enabled;

}
static int ir_sample_set_prot_enable(char *prot, int enable)
{
    int ret;

    ret = IR_Open();
    if (ret) {
        perror("Fail to open ir device!\n");
        return -1;
    }

    printf("Try set enable status %d to protocol %s.\n", enable, prot);
    if (enable)
        ret = IR_EnableProtocol(prot);
    else
        ret = IR_DisableProtocol(prot);
    if (ret) {
        printf("Fail to set enable status of %s\n",prot);
        IR_Close();
        return -1;
    }

    printf("Check it out if we do have set succussfully!\n");
    if (enable == ir_get_prot_status(prot))
        printf("Check pass!\n");
    else
        printf("Check fail!\n");

    IR_Close();
    return 0;
}
static void process_options(int argc, char *argv[])
{
    int op, ret;
    opterr = 0;
    while ((op = getopt(argc, argv, "m:u:U:r:R:T:E:g:ls:e:hD")) != -1) {
        switch (op) {
            case 'm' :
                mode = atoi(optarg);
                mode_set ++;
                printf("key fetch mode set to :%d\n", mode);
                break;
            case 'u' :
                keyup_event = atoi(optarg);
                keyup_event_set ++;
                printf("keyup event set to %d\n",keyup_event);
                break;
            case 'U' :
                keyup_timeout = strtoul(optarg, 0, 10);
                keyup_timeout_set ++;
                printf("keyup timeout set to %d\n",keyup_timeout);
                break;
            case 'r' :
                repeat_event = atoi(optarg);
                repeat_event_set ++;
                printf("repeat event set to %d\n",repeat_event);
                break;
            case 'R' :
                repeat_interval = strtoul(optarg, 0, 10);
                repeat_interval_set ++;
                printf("repeat interval set to %d\n",repeat_interval);
                break;
            case 'T' :
                read_timeout = strtoul(optarg, 0, 10);
                printf("read syscall timeout set to %d\n",read_timeout);
                break;
            case 'E':
                ir_enable = atoi(optarg);
                if (ir_enable != 0 && ir_enable != 1) {
                    printf("-E parameter not correct, only 0 or 1 allowed!\n");
                    break;
                }
                ir_enable_set = 1;
                printf("Set ir mode to %s state!\n", ir_enable ? "enable": "disable");
                break;
            case 'g' :
                printf("try to get the enable status of %s\n",optarg);

                prot_status = ir_get_prot_status(optarg);
                if (prot_status >= 0)
                    printf("The status of %s is :%s\n",
                            optarg,
                            prot_status == 0 ? "disabled" : "enabled");
                else
                    printf("Fail to get protocol status!\n");

                exit(0);
            case 'l' :
                {
                    int i;
                    printf("Available default protocols list:\n");
                    for (i = 0; i < (signed int)(sizeof(prot_names) / sizeof(prot_names[0])); i++)
                        printf("%s\n",prot_names[i]);
                }
                exit(0);
            case 's' :
                prot_name = optarg;
                prot_name_set = 1;

                printf("prot_name :%s.\n", prot_name);

                if (prot_enable_set && prot_name_set) {
                    prot_enable_set = 0;
                    prot_name_set = 0;
                    ret = ir_sample_set_prot_enable(prot_name, prot_enable);
                    if (ret) {
                        perror("Fail to set prot_enable!\n");
                        exit(-1);
                    }
                }

                break;
            case 'e' :
                prot_enable = atoi(optarg);
                prot_enable_set = 1;

                printf("protocol enable status will set to :%d\n",prot_enable);

                if (prot_enable_set && prot_name_set) {
                    prot_enable_set = 0;
                    prot_name_set = 0;
                    ret = ir_sample_set_prot_enable(prot_name, prot_enable);
                    if (ret) {
                        perror("Fail to set prot_enable!\n");
                        exit(-1);
                    }
                }
                break;
            case 'D' :
                debug_enable = 1;
                break;
            case 'h' :
            default :
                usage(argv[0]);
                exit(0);
        }
    }
}



/*lint -save -e715 */
void *ir_sample_thread(void *arg) {
    int ret;
    unsigned int i,j;
    unsigned long long key, lower, upper;
    unsigned int linux_keycode = 0;

    int keycode_flag = 0;

    int mouse_flag = 0;

    char name[64];
    KEY_STATUS_E status;

    static unsigned int u32MouseMode = 0;

    while (!g_thread_should_stop) {
        if (mode) {
            ret = IR_GetSymbol(&lower, &upper, read_timeout);
            if (!ret) {
                printf("Received symbols [%d, %d].\n",(unsigned int)lower, (unsigned int)upper);
            }
        } else {
            ret = IR_GetValueWithProtocol(&status, &key, name, sizeof(name), read_timeout);
            if (!ret) {

                mouse_flag = 0;
                keycode_flag = 0;
                linux_keycode = 0;

                for (i = 0 ; i< KEY_ARRY_NUM ; i++ ) {
                    for(j=0; j<keyarry[i].keynum; j++) {
                        if(keyarry[i].hi_keycode[j].ir_keycode == key)
                        {
                            keycode_flag = 1;
                            linux_keycode = keyarry[i].hi_keycode[j].linux_keycode;
                            break;
                        }
                    }

                }

#if MOUSE_MODE_EN == 1        //this code is only for mouse mode

                if (KEY_FN_S == linux_keycode) {
                    if(KEY_STATUS_UP == status) {
                        u32MouseMode = !u32MouseMode;
                        //ReportKeyEvent(KEY_PVR,u32MouseMode);
                    }
                }

                printf( "IR got value linux_key:%d; status:%d; infraredState:%d;...",
                        linux_keycode, status, android::InfraredService::infraredState());
                //using namespace android;
                if (android::InfraredService::infraredState() || (u32MouseMode && keycode_flag) ) {
                    printf( "We are entering into MOUSE MODE!");
                    // Browser mode or not -- checking
                    if (!android::InfraredService::infraredState()) {
                        printf( "We are currently in non-browser mode!");
                        if (status < KEY_STATUS_HOLD) {
                            g_mouse_move_step = MOUSE_MIN_STEP;
                        } else {
                            g_mouse_move_step = ((g_mouse_move_step+MOUSE_STEP)>MOUSE_MAX_STEP ? MOUSE_MAX_STEP : (g_mouse_move_step+MOUSE_STEP));
                        }
                    } else {
                        XLOGD(LOGTAG, "We are currently in browser mode!");
                        if (status < KEY_STATUS_HOLD) {
                            // Normal
                            g_mouse_move_step = BROWSER_MOUSE_MIN_STEP;
                        } else {
                            // Holding
                            g_mouse_move_step += BROWSER_MOUSE_STEP;
                        }
                    }

                    printf( "Current g_mouse_move_step - %d!", g_mouse_move_step);
                    if(KEY_UP == linux_keycode && status != KEY_STATUS_UP) {
                        mouse_flag = 1;
                        ReportMouseState(0,0,-g_mouse_move_step);
                    }
                    else if(KEY_DOWN == linux_keycode  && status != KEY_STATUS_UP) {
                        mouse_flag = 1;
                        ReportMouseState(0,0,g_mouse_move_step);
                    }
                    else if(KEY_LEFT == linux_keycode  && status != KEY_STATUS_UP){
                        mouse_flag = 1;
                        ReportMouseState(0,-g_mouse_move_step,0);
                    }
                    else if(KEY_RIGHT == linux_keycode  && status != KEY_STATUS_UP){
                        mouse_flag = 1;
                        ReportMouseState(0,g_mouse_move_step,0);
                    }
                    else if(KEY_ENTER == linux_keycode){
                        mouse_flag = 1;
                        if(KEY_STATUS_DOWN == status ) {
                            ReportMouseState(0x01,0,0);
                        }else if(KEY_STATUS_UP == status ) {
                            ReportMouseState(0x00,0,0);
                        }
                    }
                }
#endif
                if (!mouse_flag && keycode_flag){

                    if(status == KEY_STATUS_DOWN) {
                        ReportKeyEvent(linux_keycode,KPC_EV_KEY_PRESS);
                    }
                    else if(status == KEY_STATUS_UP) {
                        ReportKeyEvent(linux_keycode,KPC_EV_KEY_RELEASE);
                    }
                }

                if (debug_enable)
                    printf("Received key: 0x%.08llx,linux_keycode =0x%x,%d,%d, %s,\tprotocol: %s.\n",
                            key, linux_keycode,linux_keycode, keycode_flag , status == KEY_STATUS_DOWN ? "DOWN" :
                            (status == KEY_STATUS_UP ? "UP" : "HOLD"),
                            name);
            }
        }
    }

    return (void *)0;
}


#ifdef  POWER_RESUME_SET
static int PowerResumSet()
{
    unsigned int i,j;
    unsigned int power_num;
    signed int ret;
    char tmp[PROP_VALUE_MAX];

    HI_UNF_PMOC_MODE_E mode;
    HI_UNF_PMOC_WKUP_S wakeup;
    HI_UNF_PMOC_DEV_TYPE_S devType;

    ret = HI_UNF_PMOC_Init();
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_Init err, 0x%08x !\n", ret);
        return ret;
    }

    memset(&wakeup, 0, sizeof(HI_UNF_PMOC_WKUP_S));
    memset(&devType, 0, sizeof(HI_UNF_PMOC_DEV_TYPE_S));
    property_get("persist.suspend.mode", tmp, "deep_restart");
    if(!strcmp(tmp, "deep_restart"))
    {
        wakeup.bResumeResetEnable = HI_TRUE;
    } else {
        wakeup.bResumeResetEnable = HI_FALSE;
    }
    devType.irtype = HI_UNF_IR_CODE_RAW;
    devType.kltype = 2 ; //HI_UNF_KEYLED_TYPE_CT1642;

    ret = HI_UNF_PMOC_SetDevType(&devType);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_SetDevType err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }

    //wakeup.u32IrPmocNum = PMOC_WKUP_IRKEY_MAXNUM;

    //get the power value from the key.xml
    power_num = 0;
    for (i =0 ;i < KEY_ARRY_NUM ;i++) {

        for(j=0; j<keyarry[i].keynum; j++) {
            if(keyarry[i].hi_keycode[j].linux_keycode == KEY_POWER)
            {
                if (power_num < PMOC_WKUP_IRKEY_MAXNUM) {
                    wakeup.u32IrPowerKey0[power_num] = keyarry[i].hi_keycode[j].ir_keycode & 0x00000000ffffffff;
                    wakeup.u32IrPowerKey1[power_num] = (keyarry[i].hi_keycode[j].ir_keycode & 0xffffffff00000000) >> 32;
                    printf("power %d resume value =0x%x%x \n",power_num+1, wakeup.u32IrPowerKey1[power_num],wakeup.u32IrPowerKey0[power_num]);
                    power_num = power_num + 1;
                }
            }
        }
    }
    wakeup.u32IrPmocNum = power_num;
    wakeup.u32WakeUpTime = 0xffffffff;
#ifdef MCU
    wakeup.bGpioWakeUpEnable = 0x1;
#ifdef Hi3798CV100
    wakeup.u32GpioNo = 0x2d;
#endif
#ifdef Hi3798MV100
    wakeup.u32GpioNo = 0x2a;
#endif
#endif

    ret = HI_UNF_PMOC_SetWakeUpAttr(&wakeup);
    if (HI_SUCCESS != ret)
    {
        printf("HI_UNF_PMOC_SetWakeUpAttr err, 0x%08x !\n", ret);
        HI_UNF_PMOC_DeInit();
        return ret;
    }

    printf("PowerResumSet  ok.\n");

    return HI_SUCCESS ;

}
#endif

// Start InfraredService
void* StartInfraredService(void*) {
    // add service
    XLOGD(LOGTAG, "StartInfraredService - InfraredService::start()...\n");
    android::InfraredService::start();
    android::ProcessState::self()->startThreadPool();
    android::IPCThreadState::self()->joinThreadPool();
    XLOGD(LOGTAG, "StartInfraredService - After start InfraredService...");
    return (void*)0;
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread;
    /*lint -save -e550 */
    char c;
    process_options(argc, argv);

    ret = Hi_Vinput_Init();
    if (ret == -1){
        printf("can't open hi_vinput,so we can't use ir ,please check vinput driver\n");
        exit(-1);
    }

    get_keycode(keyarry,KEY_ARRY_NUM);

    #ifdef  POWER_RESUME_SET
    PowerResumSet();
    #endif

    if(check_params() < 0) {
        usage(argv[0]);
        exit(-1);
    }

    // open
    printf( "IR_Open-ing...");
    ret = IR_Open();
    if (ret) {
        perror("Fail to open ir dev!");
        exit(-1);
    }

    if (!mode) {
       IR_SetCodeType(0);
        if (keyup_event_set) {
            ret = IR_EnableKeyUp(keyup_event);
            if (ret) {
                perror("Fail to set keyup event!");
                exit(-1);
            }
        }

        if (keyup_timeout_set) {
            printf("This version cannot support dynamicly change keyup timeout!\n");
        }

        if (repeat_event_set) {
            ret = IR_EnableRepKey(repeat_event);
            if (ret) {
                perror("Fail to set repeat key event!");
                exit(-1);
            }
        }

        if (repeat_interval_set) {
            ret = IR_SetRepKeyTimeoutAttr(repeat_interval);
            if (ret) {
                perror("Fail to set repeat interval!");
                exit(-1);
            }
        }
    }

    ret = IR_SetFetchMode(mode);
    if (ret) {
        perror("Fail to set key fetch mode!");

        exit(-1);

    }

    if (ir_enable_set) {
        ret = IR_Enable(ir_enable);
        if (ret) {
            perror("Fail to set enable state of ir module!");
            exit(-1);
        }
    }

    /////////////////////////////////////////////////////////////
    // Start InfraredService...
    XLOGD(LOGTAG, "Creating infrared service thread...\n");
    pthread_t infrared_thread_id;
    pthread_attr_t attr;
    pthread_attr_init(&attr);
    pthread_attr_setdetachstate(&attr, PTHREAD_CREATE_DETACHED);
    pthread_create(&infrared_thread_id, &attr, StartInfraredService, NULL);
    pthread_attr_destroy(&attr);
    XLOGD(LOGTAG, "Created infrared service!\n");
    /////////////////////////////////////////////////////////////

    /////////////////////////////////////////////////////////////
    printf( "Creating ir  thread\n");
    // IR processing thread
    ret = pthread_create(&thread, NULL, ir_sample_thread, NULL);
    if (ret < 0) {
        perror("Failt to create thread!");
        exit(-1);
    }
    pthread_join(thread, NULL);
    printf( "Ir sample thread exit! Bye!\n");
    /////////////////////////////////////////////////////////////

    // cancel infrared service thread!
    // pthread_cancel(infrared_thread_id);
    int status = 0;
    if ( (status = pthread_kill(infrared_thread_id, SIGUSR1)) != 0 ) {
        XLOGD(LOGTAG, "Error cancelling thread %ld, error = %d;", infrared_thread_id, status);
    }

    IR_Close();
    return 0;
}

#pragma GCC diagnostic pop
#pragma GCC diagnostic pop
