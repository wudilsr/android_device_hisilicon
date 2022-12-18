#ifndef __TEE_CONFIG_H_
#define __TEE_CONFIG_H_
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * HELLO_WORLD TA
 * 79b77788-9789-4a7a-a2be-b60155eef5f3
 */
#define TEE_SERVICE_HELLOWORLD \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf3 \
    } \
}

/**
 * @ingroup  TEE_CONFIG_DATA
 *
 *  KERNEL_MEM_USAGE TA
 * 04040404-9789-4a7a-a2be-b60155eef5f3
 */
#define TEE_SERVICE_KERNELMEMUSAGE \
{ \
    0x04040404, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf3 \
    } \
}


/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * TUI_DEMO TA
 * 8a613138-5288-e6ac-3f3f-fb4790f7b1fa
 */
#define TEE_SERVICE_TUI_DEMO \
{ \
    0x8a613138, \
    0x5288, \
    0xe6ac, \
    { \
        0x3f, 0x3f, 0xfb, 0x47, 0x90, 0xf7, 0xb1, 0xfa \
    } \
}

/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * TIMER_UT TA
    19B39980-2487-7B84-F41A-BC892262BB3D
 */
#define TEE_SERVICE_TIMER_UT \
{ \
    0x19B39980, \
    0x2487, \
    0x7B84, \
    { \
        0xf4, 0x1a, 0xbc, 0x89, 0x22, 0x62, 0xbb, 0x3d \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * PERMISSIONCONTROL_UT TA
 * F1AE5991-F36A-84A4-EE9F-234B37FBBE69
 */
#define TEE_SERVICE_PERMCTRL_UT \
{ \
    0xF1AE5991, \
    0xF36A, \
    0x84A4, \
    { \
        0xee, 0x9f, 0x23, 0x4b, 0x37, 0xfb, 0xbe, 0x69 \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * FingerPrint TA
 * a32b3d00-cb57-11e3-9c1a-0800200c9a66.sec
 */
#define TEE_SERVICE_FINGERPRINT \
{ \
    0xa32b3d00, \
    0xcb57, \
    0x11e3, \
    { \
        0x9c, 0x1a, 0x08, 0x00, 0x20, 0x0c, 0x9a, 0x66 \
    } \
}

/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * FingerPrint Coating check TA
 * e5c6a727-c219-aa13-3e14-444d853a200a.sec
 */

#define TEE_FINGERPRINT_COATING_CHECK  \
{ \
    0xe5c6a727, \
    0xc219, \
    0xaa13, \
    { \
        0x3e, 0x14, 0x44, 0x4d, 0x85, 0x3a, 0x20, 0x0a   \
    } \
}


/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * SignTool TA:used to store huawei VIP key
 * 9b17660b-8968-4eed-917e-dd32379bd548
 */
#define TEE_SERVICE_SIGNTOOL \
{ \
    0x9b17660b, \
    0x8968, \
    0x4eed, \
    { \
        0x91, 0x7e, 0xdd, 0x32, 0x37, 0x9b, 0xd5, 0x48 \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * product line RPMB key write TA
 * 6c8cf255-ca98-439e-a98e-ade64022ecb6
 */
#define TEE_SERVICE_RPMBKEY \
{ \
    0x6c8cf255, \
    0xca98, \
    0x439e, \
    { \
        0xa9, 0x8e, 0xad, 0xe6, 0x40, 0x22, 0xec, 0xb6 \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * Huawei wallet TA:used to check spi in product line
 * 4ae7ba51-2810-4cee-abbe-a42307b4ace3
 */
#define TEE_SERVICE_HUAWEIWALLET \
{ \
    0x4ae7ba51, \
    0x2810, \
    0x4cee, \
    { \
        0xab, 0xbe, 0xa4, 0x23, 0x07, 0xb4, 0xac, 0xe3 \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * SKYTONE TA
 * abe89147-cd61-f43f-71c4-1a317e405312.sec
 */
#define TEE_SERVICE_SKYTONE \
{ \
    0xabe89147, \
    0xcd61, \
    0xf43f, \
    { \
        0x71, 0xc4, 0x1a, 0x31, 0x7e, 0x40, 0x53, 0x12 \
    } \
}

/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * crypto sms TA:used to encrypt sms in carrara
 * 79b77788-9789-4a7a-a2be-b60155eef5f4
 */
#define TEE_SERVICE_CRYPTOSMS \
{ \
    0x79b77788, \
    0x9789, \
    0x4a7a, \
    { \
        0xa2, 0xbe, 0xb6, 0x01, 0x55, 0xee, 0xf5, 0xf4 \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * alipay TA from zhifubao:used for zhifubao
 * 66302DF4-31F2-1782-042F-A55C7466DA21
 */
#define TEE_SERVICE_ALIPAY \
{ \
    0x66302DF4, \
    0x31F2, \
    0x1782, \
    { \
        0x04, 0x2F, 0xA5, 0x5C, 0x74, 0x66, 0xDA, 0x21 \
    } \
}
/**
 * @ingroup  TEE_CONFIG_DATA
 *
 * wechat TA from tencent:used for wechar pay
 * B7C9A7FD-851E-7761-07DF-8AB7C0B02787
 */
#define TEE_SERVICE_WECHAT \
{ \
    0xB7C9A7FD, \
    0x851E, \
    0x7761, \
    { \
        0x07, 0xdf, 0x8a, 0xb7, 0xc0, 0xb0, 0x27, 0x87 \
    } \
}
#define TEE_SERVICE_Antitheft \
{ \
    0xB4B71581, \
    0xADD2, \
    0xE89F, \
    { \
        0xD5, 0x36, 0xF3, 0x54, 0x36, 0xDC, 0x79, 0x73   \
    } \
}
#endif
