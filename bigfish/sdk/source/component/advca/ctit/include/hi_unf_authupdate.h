#ifndef __HI_UNF_CA_H__
#define __HI_UNF_CA_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

/**
\brief the api of the security update.zip.  CNcomment: 安全升级包校验接口
\param[in] inputfilepath  the path of security update.zip 		CNcomment:安全升级包路径
\param[out] outputfilepath	the path of security update.zip after auth.    		CNcomment:安全升级包检验后存放路径
\retval ::0  Success  CNcomment:0 成功
\retval ::-1 This API fails to be called CNcomment:-1  API系统调用失败
 */
int CA_Android_authUpdateFile(const char *inputfilepath,  char *outputfilepath)

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */
#endif /* __HI_UNF_CA_H__ */
