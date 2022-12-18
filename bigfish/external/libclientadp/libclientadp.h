#ifndef __CLIENT_APD_H__
#define __CLIENT_APD_H__

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

/* error code */
#define CLIENT_SUCCESS    (0)
#define CLIENT_FAILURE    (-1)

/**
\brief Create a client object. CNcomment:创建一个client 实例CNend
\attention \n
none

\param[out] pHdl Client handle. CNcomment:client 句柄CNend

\retval ::CLIENT_SUCCESS Handle create success. CNcomment:句柄创建成功CNend
\retval ::CLIENT_FAILURE Handle create fail CNcomment:句柄创建失败CNend

\see \n
None.
*/
int CLIENT_Init(unsigned int *pHdl);

/**
\brief Obtain the aes key. CNcomment:获取aes 解密密钥CNend
\attention \n
none

\param[in] handle Client handle. CNcomment:client 句柄CNend
\param[in] purl Url of obtain the key. CNcomment:密钥地址CNend
\param[in] keybufferlen Length of the key buffer. CNcomment:密钥buffer长度CNend
\param[out] key Key storage buffer. CNcomment:存储密钥的buffer CNend
\param[out] key_len The actual length of the key. CNcomment:密钥实际长度CNend

\retval ::CLIENT_SUCCESS Obtain the key success. CNcomment:获取密钥成功CNend
\retval ::CLIENT_FAILURE Obtain the key fail. CNcomment:获取密钥失败CNend

\see \n
None.
*/
int CLIENT_GetKey(unsigned int handle, const char *purl, char *key, unsigned int keybufferlen, unsigned int *key_len);

/**
\brief Delete the client handle. CNcomment:删除Clent句柄CNend
\attention \n
none

\param[in] handle Client handle. CNcomment:client 句柄CNend

\retval ::CLIENT_SUCCESS Delete client handle success. CNcomment:删除client 句柄成功CNend

\see \n
None.
*/
int CLIENT_Deinit(unsigned int handle);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __CLIENT_APD_H__ */

