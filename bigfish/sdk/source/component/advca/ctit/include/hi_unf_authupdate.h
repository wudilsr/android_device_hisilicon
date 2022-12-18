#ifndef __HI_UNF_CA_H__
#define __HI_UNF_CA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
\brief the api of the security update.zip.  CNcomment: ��ȫ������У��ӿ�
\param[in] inputfilepath  the path of security update.zip 		CNcomment:��ȫ������·��
\param[out] outputfilepath	the path of security update.zip after auth.    		CNcomment:��ȫ�������������·��
\retval ::0  Success  CNcomment:0 �ɹ�
\retval ::-1 This API fails to be called CNcomment:-1  APIϵͳ����ʧ��
 */
int CA_Android_authUpdateFile(const char *inputfilepath,  char *outputfilepath)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __HI_UNF_CA_H__ */
