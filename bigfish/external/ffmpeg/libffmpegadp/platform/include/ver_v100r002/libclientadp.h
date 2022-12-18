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
\brief Create a client object. CNcomment:����һ��client ʵ��CNend
\attention \n
none

\param[out] pHdl Client handle. CNcomment:client ���CNend

\retval ::CLIENT_SUCCESS Handle create success. CNcomment:��������ɹ�CNend
\retval ::CLIENT_FAILURE Handle create fail CNcomment:�������ʧ��CNend

\see \n
None.
*/
int CLIENT_Init(unsigned int *pHdl);

/**
\brief Obtain the aes key. CNcomment:��ȡaes ������ԿCNend
\attention \n
none

\param[in] handle Client handle. CNcomment:client ���CNend
\param[in] purl Url of obtain the key. CNcomment:��Կ��ַCNend
\param[in] keybufferlen Length of the key buffer. CNcomment:��Կbuffer����CNend
\param[out] key Key storage buffer. CNcomment:�洢��Կ��buffer CNend
\param[out] key_len The actual length of the key. CNcomment:��Կʵ�ʳ���CNend

\retval ::CLIENT_SUCCESS Obtain the key success. CNcomment:��ȡ��Կ�ɹ�CNend
\retval ::CLIENT_FAILURE Obtain the key fail. CNcomment:��ȡ��Կʧ��CNend

\see \n
None.
*/
int CLIENT_GetKey(unsigned int handle, const char *purl, char *key, unsigned int keybufferlen, unsigned int *key_len);

/**
\brief Delete the client handle. CNcomment:ɾ��Clent���CNend
\attention \n
none

\param[in] handle Client handle. CNcomment:client ���CNend

\retval ::CLIENT_SUCCESS Delete client handle success. CNcomment:ɾ��client ����ɹ�CNend

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

