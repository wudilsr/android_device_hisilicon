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

#include "android_vinput_inter.h"
#include "key_pars.h"
#include "keyled.h"

#define KEY_ARRY_NUM 1
struct _key_arry keyarry[KEY_ARRY_NUM];
KEY_STU val;

void *front_thread(void *arg)
{
    int ret;
    unsigned int i,j;
    while (1) {
        ret = key_get(&val);
        if(ret == HI_SUCCESS){
//          printf("keyid=%x,status=%x\n",val.keyid,val.status);
            for (i = 0 ; i< KEY_ARRY_NUM ; i++ ) {
                for(j=0; j<keyarry[i].keynum; j++) {
                    if(keyarry[i].hi_keycode[j].bottom_keycode == val.keyid)
                    {
                        if(val.status == KEY_STATUS_DOWN) {
                            ReportKeyEvent(keyarry[i].hi_keycode[j].linux_keycode,KPC_EV_KEY_PRESS);
                        }
                        else if(val.status == KEY_STATUS_UP) {
                            ReportKeyEvent(keyarry[i].hi_keycode[j].linux_keycode,KPC_EV_KEY_RELEASE);
                        }
                        break;
                    }
                }
            }
        }else{
            usleep(50000);
        }
    }
    return (void *)0;
}

int main(int argc, char *argv[])
{
    int ret;
    pthread_t thread;
    ret = Hi_Vinput_Init();
    if (ret == -1){
        printf("can't open hi_vinput\n");
        exit(-1);
    }
    ret = key_init();
    if (ret != HI_SUCCESS){
        Hi_Vinput_DeInit();
        printf("can't key_init\n");
        exit(-1);
    }
    get_keycode(keyarry,KEY_ARRY_NUM);
    ret = pthread_create(&thread, NULL, front_thread, NULL);
    if (ret < 0) {
        Hi_Vinput_DeInit();
        key_deinit();
        perror("Failt to create thread!");
        exit(-1);
    }
    pthread_join(thread, NULL);
    return 0;
}
