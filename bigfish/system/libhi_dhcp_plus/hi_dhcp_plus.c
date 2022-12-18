#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "hi_dhcp_plus.h"

#ifdef ANDROID
#define LOG_TAG "HiDhcpPlus"
#include <cutils/log.h>
#endif

#define DEBUG 1

/*****************************************************************************/
/*
 * STB 生成密文C = EnCry(R+TS+64Bit, Login)， 例如 C 的长度为128bit,
 * Login 为120bit(15 字符)，EnCry 为3DES 对称
 * 加密算法，密钥为R+TS 后用64 位0 补足192bit。
 */
int EnCry(char r[R_SIZE], char ts[TS_SIZE],
          unsigned char login[MAX_LOGIN_LEN],
          unsigned char selogin[MAX_LOGIN_LEN], unsigned int *sz_selogin)
{
    unsigned int i;
    unsigned char key[DES_KEY_SIZE * 3];
    unsigned char val;
    des3_context ctx;

    if(login == NULL) return EMPTY_STRING;

    unsigned int ilen = strlen((char *)login);
    if (ilen > MAX_LOGIN_LEN)
        return LOGIN_LEN_ERR;

    memcpy(key, r, R_SIZE);
    memcpy(key + R_SIZE, ts, TS_SIZE);
    memset(key + R_SIZE + TS_SIZE, 0, DES_KEY_SIZE);

    des3_set3key_enc(&ctx, key);

    /* PKCS7 填充 */
    val = DES_KEY_SIZE - (ilen % DES_KEY_SIZE);
    memset(login + ilen, val, val);
    ilen += val;
    *sz_selogin = ilen;

    if(DEBUG) {
        ALOGD("EnCry: username:%s sz_selogin:%d", login, *sz_selogin);
        ALOGD("login:");
        for(i = 0; i < ilen; i++)
            ALOGD("%02x",login[i]);
    }

    for (i = 0; i < ilen; i += DES_KEY_SIZE)
        des3_crypt_ecb(&ctx, login + i, selogin + i);

    return SUCCESS;
}
/*****************************************************************************/
/*
 * STB 生成密钥 Key = Hash(R+Password+TS)，其中 Key 为 128bit, Hash()
 * 为哈希算法，这里定义为 MD5；R+Password+TS 就是 Byte 的直接拼接
 */
int Hash(char r[R_SIZE], char ts[TS_SIZE], const char *pwd, unsigned int sz_pwd,
         unsigned char key[HASH_KEY_SIZE])
{
    unsigned char *ptr;
    unsigned char buf[MAX_PASSWORD_LEN + R_SIZE + TS_SIZE];

    if (sz_pwd > MAX_PASSWORD_LEN)
        return PASSWORD_LEN_ERR;

    if(DEBUG)
        ALOGD("Hash: password:%s sz_pwd:%d", pwd, sz_pwd);

    ptr = buf;

    memcpy(ptr, r, R_SIZE);
    ptr += R_SIZE;

    memcpy(ptr, pwd, sz_pwd);
    ptr += sz_pwd;

    memcpy(ptr, ts, TS_SIZE);
    ptr += TS_SIZE;

    md5(buf, ptr - buf, key);

    return SUCCESS;
}
/*****************************************************************************/
/*
 * STB 生成发送消息Message = O+R+TS+Key+C，其中O 描述使用
 * 的对称加密算法8bit，O=1：表示为上述描述的加密算法，O=
 * 其他数字：保留。
 */
int Message(const char *login, const char *pwd, unsigned char msg[MESSAGE_LEN], unsigned int *sz_msg)
{
    int ret;
    unsigned int sz_login, sz_pwd, sz_3DESKey, i;
    unsigned char *ptr = msg;
    unsigned char buf[MAX_LOGIN_LEN];
    char r[R_SIZE] = {0x00};
    char ts[TS_SIZE] = {0x00};
    time_t timer;
    long rn[2] = {0};


    if(login == NULL) {
        ALOGE("Login name ERROR! Emtpy String!");
        return EMPTY_STRING;
    }

    if(pwd == NULL) {
        ALOGE("Password ERROR! Emtpy String!");
        return EMPTY_STRING;
    }

    sz_login = strlen(login);
    if (sz_login > MAX_LOGIN_LEN) {
        ALOGE("Login name lenth ERROR! Too long!");
        return LOGIN_LEN_ERR;
    }

    sz_pwd = strlen(pwd);
    if (sz_pwd > MAX_PASSWORD_LEN) {
        ALOGE("Password lenth ERROR! Too long!");
        return LOGIN_LEN_ERR;
    }

    timer = time(NULL);
    memcpy(ts + TS_SIZE - sizeof(time_t), &timer, sizeof(time_t));

    srand((unsigned)time(NULL));
    rn[0] = rand();
    rn[1] = rand();
    memcpy(r, &rn, R_SIZE);

    *ptr = DEFAULT_ENCRPYTION_ALG;
    ptr++;
    memcpy(ptr, r, R_SIZE);
    ptr += R_SIZE;
    memcpy(ptr, ts, TS_SIZE);
    ptr += TS_SIZE;

    if(DEBUG) {
        ALOGD("Message: username:%s password:%s\n", login, pwd);
        ALOGD("R:");
        for(i = 0; i < R_SIZE; i++)
            ALOGD("%02x", r[i]);
        ALOGD("TS:");
        for(i = 0; i < TS_SIZE; i++)
            ALOGD("%02x", ts[i]);
    }

    ret = Hash(r, ts, pwd, sz_pwd, ptr);
    if (ret != SUCCESS) {
        ALOGD("Hash Encrypt Error!! ret = %d", ret);
        return ret;
    }
    ptr += HASH_KEY_SIZE;

    if(DEBUG) {
        ALOGD("HashKey:");
        for(i = 0; i < HASH_KEY_SIZE; i++)
            ALOGD("%02x",*(ptr - HASH_KEY_SIZE + i));
    }

    memcpy(buf, login, sz_login);
    ret = EnCry(r, ts, buf, ptr, &sz_3DESKey);
    if(ret != SUCCESS) {
        ALOGD("3DES Encrypt Error!! ret = %d", ret);
        return ret;
    }

    *sz_msg = 1 + R_SIZE + TS_SIZE + HASH_KEY_SIZE + sz_3DESKey;

    if(DEBUG) {
        ALOGD("3DESKey length = %d!!", sz_3DESKey);
        for(i = 0; i < sz_3DESKey; i++)
            ALOGD("%02x",*(ptr+i));
    }

    if(DEBUG) {
        ALOGD("Message length = %d!!", *sz_msg);
        for(i = 0; i < *sz_msg; i++)
            ALOGD("%02x",msg[i]);
    }

    ALOGD("Encrypt SUCCESS!!");
    return SUCCESS;
}
