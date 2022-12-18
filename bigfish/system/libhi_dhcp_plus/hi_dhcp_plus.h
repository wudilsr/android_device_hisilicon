#ifndef _HI_DHCP_PLUS_H_
#define _HI_DHCP_PLUS_H_

#include <polarssl/md5.h>
#include <polarssl/des.h>

#define R_SIZE DES_KEY_SIZE
#define TS_SIZE DES_KEY_SIZE
#define MAX_LOGIN_LEN 128
#define MAX_PASSWORD_LEN 128
#define HASH_KEY_SIZE 16
#define DEFAULT_ENCRPYTION_ALG 1
#define SUCCESS 0
#define LOGIN_LEN_ERR 1
#define PASSWORD_LEN_ERR 2
#define EMPTY_STRING 3
#define MESSAGE_LEN (1+R_SIZE+TS_SIZE+HASH_KEY_SIZE+MAX_LOGIN_LEN)

/*****************************************************************************/
/*
 * STB 生成密文C = EnCry(R+TS+64Bit, Login)， 例如 C 的长度为128bit,
 * Login 为120bit(15 字符)，EnCry 为3DES 对称
 * 加密算法，密钥为R+TS 后用64 位0 补足192bit。
 */
int EnCry(char r[R_SIZE], char ts[TS_SIZE],
          unsigned char login[MAX_LOGIN_LEN],
          unsigned char selogin[MAX_LOGIN_LEN], unsigned int *sz_selogin);

/*****************************************************************************/
/*
 * STB 生成密钥 Key = Hash(R+Password+TS)，其中 Key 为 128bit, Hash()
 * 为哈希算法，这里定义为 MD5；R+Password+TS 就是 Byte 的直接拼接
 */
int Hash(char r[R_SIZE], char ts[TS_SIZE], const char *pwd, unsigned int sz_pwd,
         unsigned char key[HASH_KEY_SIZE]);

/*****************************************************************************/
/*
 * STB 生成发送消息Message = O+R+TS+Key+C，其中O 描述使用
 * 的对称加密算法8bit，O=1：表示为上述描述的加密算法，O=
 * 其他数字：保留。
 */
int Message(const char *login, const char *pwd, unsigned char msg[MESSAGE_LEN], unsigned int *sz_msg);

#endif /* _HI_DHCP_PLUS_H_ */
