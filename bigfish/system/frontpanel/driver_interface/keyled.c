#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "keyled.h"
#include "panel.h"

int key_get(KEY_STU *val)
{
    unsigned status = 0;
    unsigned keyid = 0;
    int ret = HI_UNF_KEY_GetValue(&status, &keyid);
    val->status = status;
    val->keyid  = keyid;
    return ret;
}

int key_init(void)
{
    HI_S32 s32Ret;
    pthread_t keyTaskid;
    HI_SYS_Init();
    HI_UNF_KEYLED_Init();

    s32Ret = HI_UNF_KEYLED_SelectType(KEYLED_TYPE_DEF);
    if (HI_SUCCESS != s32Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        return s32Ret;
    }

    /*open KEY device*/
    s32Ret = HI_UNF_KEY_Open();
    if (HI_SUCCESS != s32Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        goto ERR1;
    }

    s32Ret = HI_UNF_KEY_IsKeyUp(1);
    if (HI_SUCCESS != s32Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        goto ERR2;
    }

    s32Ret = HI_UNF_KEY_IsRepKey(1);
    if (HI_SUCCESS != s32Ret)
    {
        printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, s32Ret);
        goto ERR2;
    }

    return HI_SUCCESS;

ERR2:
    HI_UNF_KEY_Close();
ERR1:

    HI_UNF_KEYLED_DeInit();
    HI_SYS_DeInit();

    return s32Ret;
}

void key_deinit(void)
{
    HI_UNF_KEY_Close();
    HI_UNF_KEYLED_DeInit();
    HI_SYS_DeInit();
}
