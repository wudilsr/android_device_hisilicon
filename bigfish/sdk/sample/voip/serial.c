#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <linux/types.h>
#include <string.h>

#include "hi_usbphone.h"
#include "hi_adp.h"

HI_S32 usb_phone_event_proc(HI_USB_PHONE_EVENT_E enEvent, HI_S32 s32EventValue, HI_U32 u32Args)
{
    switch(enEvent)
    {
        case HI_USB_PHONE_EVENT_BS_REG:
            printf("\nusb phone event: BS REG , state %d, args 0x%x\n",s32EventValue,u32Args);
            break;
        case HI_USB_PHONE_EVENT_OFF_HOOK:
            printf("\nusb phone event: OFF HOOK, args 0x%x\n",u32Args);
            break;
        case HI_USB_PHONE_EVENT_ON_HOOK:
            printf("\nusb phone event: ON HOOK, args 0x%x\n",u32Args);
            break;
        case HI_USB_PHONE_EVENT_KEY:
            printf("\nusb phone event: KEY %c , args 0x%x\n",(HI_CHAR)s32EventValue,u32Args);
            break;
        case HI_USB_PHONE_EVENT_HOLD:
            printf("\nusb phone event: HOLD , state %d, args 0x%x\n",s32EventValue,u32Args);
            break;
        case HI_USB_PHONE_EVENT_DISCON:
            printf("\nusb phone event: DISCON , args 0x%x\n",u32Args);
            break;
        default:
            printf("\nusb phone event: UNKNOWN , value %d, args 0x%x\n",s32EventValue,u32Args);
            break;
    }
    return HI_SUCCESS;
}

#define HELP_INFO  \
" ------------- help info ----------------------------------  \n\n " \
"  h           : help info                                    \n " \
"  q           : quite                                        \n " \
"  ringon      : ring on                                      \n " \
"  ringoff     : ring off                                     \n " \
"  busytone    : play busy tone                               \n " \
"  howlertone  : play howler tone                             \n " \
"  stoptone    : stop tone and on hook / stop tone only       \n " \
"  display     : display call in id                           \n " \
"  cfgcontone  : enable/disable connect tone                  \n " \
"  getver      : display usb phone version                    \n " \
"  state       : get usb phone state                          \n " \
" ----------------------------------------------------------- \n\n " \

HI_S32 main(HI_S32 argc, HI_CHAR *argv[])
{
    HI_S32 ret = 0;
    HI_CHAR InputCmd[32];

    HI_SYS_Init();
    HI_SYS_SetLogLevel(HI_ID_VOIP_HME, HI_LOG_LEVEL_INFO);
    
    ret = HI_USB_PHONE_Init();
    if(HI_SUCCESS != ret)
    {
        goto _system_deinit;
    }

    ret = HI_USB_PHONE_Open("/dev/ttyUSB0");
    if(HI_SUCCESS != ret)
    {
        goto _usbphone_deinit;
    }

    ret = HI_USB_PHONE_RegisterEvent(usb_phone_event_proc, 0xa5a5);

    usleep(100*1000);
    printf("%s",HELP_INFO);  
    
    while(1)
    {
        SAMPLE_GET_INPUTCMD(InputCmd);
        
        if (0 == strncmp("ringon", InputCmd, 6))        
        {
            ret = HI_USB_PHONE_Ring(HI_TRUE);
        }
        else if (0 == strncmp("ringoff", InputCmd, 7))        
        {
            ret = HI_USB_PHONE_Ring(HI_FALSE);
        }
        else if (0 == strncmp("busytone", InputCmd, 8))        
        {
            ret = HI_USB_PHONE_PlayTone(HI_USB_PHONE_BUSY_TONE);
        }
        else if (0 == strncmp("howlertone", InputCmd, 10))        
        {
            ret = HI_USB_PHONE_PlayTone(HI_USB_PHONE_HOWLER_TONE);
        }
        else if (0 == strncmp("stoptone", InputCmd, 8))        
        {
            HI_CHAR c;
            c = InputCmd[8];
            if(c == '0')
                ret = HI_USB_PHONE_StopTone(HI_FALSE);
            else
                ret = HI_USB_PHONE_StopTone(HI_TRUE);
        }
        else if (0 == strncmp("display", InputCmd, 7))        
        {
            ret = HI_USB_PHONE_DisplayCallID(&InputCmd[7]);
        }
        else if (0 == strncmp("cfgcontone", InputCmd, 10))        
        {
            HI_CHAR c;
            c = InputCmd[10];
            if((c == '0')||(c == '1'))
                ret = HI_USB_PHONE_Config_ConTone(c - '0');
            else
                printf("invalid input\n");
        }
        else if (0 == strncmp("getver", InputCmd, 6))        
        {
            HI_CHAR *pszVer = HI_NULL;
            ret = HI_USB_PHONE_GetBSVersion(&pszVer);
            printf("\nusb phone version:   %s\n",pszVer);
        }
        else if (0 == strncmp("state", InputCmd, 5))        
        {
            HI_USB_PHONE_STATE_E State = HI_USB_PHONE_STATE_BUTT;
            const HI_CHAR * str_state[]={
                    "IDLE",
                    "TALK",
                    "REG",
                    "RING",
                    "BUTT",
                    };
            ret = HI_USB_PHONE_GetState(&State);
            printf("\nusb phone state: %s\n",str_state[State]);
        }
        else if ('h' == InputCmd[0])
        {
            printf("%s",HELP_INFO);
        }
        else if ('q' == InputCmd[0])
        {
            printf("prepare to quit!\n");
            break;
        }
    }        

    HI_USB_PHONE_Close();
_usbphone_deinit:
    HI_USB_PHONE_DeInit();
_system_deinit: 
    HI_SYS_DeInit();
	return 0;
}
