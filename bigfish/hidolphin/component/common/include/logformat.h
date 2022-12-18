#ifndef __LOGFORMAT_H__
#define __LOGFORMAT_H__


#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* End of #ifdef __cplusplus */

#define SVR_MOD_NAME_MAXNUM  16
typedef struct HISVR_LOG_MOD_INFO_S
{
    HI_U32  u32ModuleId;
    HI_CHAR acModuleName[SVR_MOD_NAME_MAXNUM];
}SVR_LOG_MOD_INFO_S;


HI_U32 Module_Init(HI_U32* g_moduleid,const HI_CHAR * moduleNname);
HI_U32 Module_Uninit(HI_U32 g_moduleid);

HI_VOID  SVR_LogOut(HI_U32 u32Level, HI_MOD_ID_E enModId, HI_U8 *pFuncName, HI_U32 u32LineNum, const char *format, ...);

HI_VOID  SVR_HiLogOut(HI_U32 u32ModID,HI_MOD_ID_E enModId,HI_U32 u32Level,HI_ERRNO enoErrno, const HI_CHAR* pszFileName,const HI_CHAR* pszFunctionName, HI_S32 s32LineNo,const char *format, ...);

HI_U32  SVR_Set_LogLevel_ById(HI_U32 u32ModID, HI_LOG_LEVEL_E loglevel);
HI_U32  SVR_Set_LogLevel_ByName(const HI_CHAR* modname, HI_LOG_LEVEL_E loglevel);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* End of #ifdef __cplusplus */


#endif /* End of #ifndef __UTIL_H__ */
