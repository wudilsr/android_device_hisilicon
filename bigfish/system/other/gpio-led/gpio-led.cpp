/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <dirent.h>
#include "cutils/properties.h"
#include "cutils/log.h"
#include "cutils/klog.h"
#include <cutils/properties.h>
#include <sys/reboot.h>

#include "hi_common.h"
#include "hi_unf_gpio.h"


#ifdef Hi3798MV100
#define GPIO5_5_6_3798MV100_DIR   "himm 0xF8004400 0x60"
#define GPIO5_5_6_3798MV100_CLOSE "himm 0xF8004180 0x60"
#define GPIO5_5_3798MV100_GREEN   "himm 0xF8004180 0x40"
#define GPIO5_6_3798MV100_RED     "himm 0xF8004180 0x20"
#endif

#define FLASH_LED



int main() {
    HI_CHIP_PACKAGE_TYPE_E penPackageType;
    HI_SYS_Init();
    HI_SYS_GetChipPackageType(&penPackageType);

    int fp;
    int ret;
    char value[PROPERTY_VALUE_MAX] = {0};
    char value_2[PROPERTY_VALUE_MAX] = {0};
    char value_3[PROPERTY_VALUE_MAX] = {0};
    char value_4[PROPERTY_VALUE_MAX] = {0};

    #ifdef Hi3798MV100

    ALOGE("HI_UNF_GPIO_QFP %d",penPackageType);
    if(penPackageType==HI_CHIP_PACKAGE_TYPE_QFP_216)
    {
        ret = HI_UNF_GPIO_Init();
        if (HI_SUCCESS != ret)
        {
           ALOGE("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, ret);
        }
        HI_UNF_GPIO_SetDirBit(0x2a, HI_FALSE);
        // addr :0x2a
        // hi-level
        //HI_UNF_GPIO_WriteBit(0x2a, HI_TRUE);

        while (1) {
             property_get("sys.boot_completed", value, "0");
             property_get("persist.sys.qb.enable", value_2, "false");
             property_get("persist.sys.qb.flag", value_3, "true");
             property_get("persist.sys.firstboot.flag", value_4, "true");

            if ( !strcmp(value_2,"false")) {
                #ifdef FLASH_LED
                //green  hi-level
                HI_UNF_GPIO_WriteBit(0x2a, HI_TRUE);
                sleep(1);
                //red   low-level
                HI_UNF_GPIO_WriteBit(0x2a, HI_FALSE);
                #endif
                sleep(1);
                ALOGE("value_2 is false");
                if ( 0 == strcmp(value, "1") ) {
                    ALOGE("value is 1");
                    HI_UNF_GPIO_WriteBit(0x2a, HI_TRUE);
                    break;
                }
             }

            else if ( !strcmp(value_2,"true") && !strcmp(value_4,"true")){

                #ifdef FLASH_LED
                //green
                HI_UNF_GPIO_WriteBit(0x2a, HI_TRUE);
                sleep(1);
                //red
                HI_UNF_GPIO_WriteBit(0x2a, HI_FALSE);
                #endif
                sleep(1);
                if ( 0 == strcmp(value, "1") ) {
                    HI_UNF_GPIO_WriteBit(0x2a, HI_FALSE);
                    break;
                }
            }else if ( !strcmp(value_2,"true") && !strcmp(value_4,"false")){
                   HI_UNF_GPIO_WriteBit(0x2a, HI_FALSE);
                break;
            }
        }
        ret = HI_UNF_GPIO_DeInit();
            if (HI_SUCCESS != ret)
            {
             printf("%s: %d ErrorCode=0x%x\n", __FILE__, __LINE__, ret);
            }
    }
    else{

         while (1) {
             property_get("sys.boot_completed", value, "0");
             property_get("persist.sys.qb.enable", value_2, "false");
             property_get("persist.sys.qb.flag", value_3, "true");
             property_get("persist.sys.firstboot.flag", value_4, "true");

            if ( !strcmp(value_2,"false")) {
                #ifdef FLASH_LED
                system(GPIO5_5_6_3798MV100_DIR);
                //green
                system(GPIO5_5_6_3798MV100_CLOSE);
                system(GPIO5_5_3798MV100_GREEN);
                sleep(1);
                //red
                system(GPIO5_5_6_3798MV100_CLOSE);
                system(GPIO5_6_3798MV100_RED);
                #endif
                sleep(1);

                if ( 0 == strcmp(value, "1") ) {
                    system(GPIO5_5_6_3798MV100_DIR);
                    system(GPIO5_5_6_3798MV100_CLOSE);
                    system(GPIO5_5_3798MV100_GREEN);
                    break;
                }
             }

            else if ( !strcmp(value_2,"true") && !strcmp(value_4,"true")){

                #ifdef FLASH_LED
                system(GPIO5_5_6_3798MV100_DIR);
                //green
                system(GPIO5_5_6_3798MV100_CLOSE);
                system(GPIO5_5_3798MV100_GREEN);
                sleep(1);
                //red
                system(GPIO5_5_6_3798MV100_CLOSE);
                system(GPIO5_6_3798MV100_RED);
                #endif
                sleep(1);
                if ( 0 == strcmp(value, "1") ) {
                    system(GPIO5_5_6_3798MV100_DIR);
                    system(GPIO5_5_6_3798MV100_CLOSE);
                    system(GPIO5_6_3798MV100_RED);
                    break;
                }
            }else if ( !strcmp(value_2,"true") && !strcmp(value_4,"false")){
                   system(GPIO5_5_6_3798MV100_DIR);
                   system(GPIO5_5_6_3798MV100_CLOSE);
                   system(GPIO5_6_3798MV100_RED);
                break;
            }
        }
    }
  #endif
}
