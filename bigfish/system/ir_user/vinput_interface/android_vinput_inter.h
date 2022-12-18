
#ifndef _ANDROID_VINPUT_INTER_HEADER_
#define _ANDROID_VINPUT_INTER_HEADER_


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

int Hi_Vinput_Init();
int Hi_Vinput_DeInit(void);
int ReportKeyEvent(int iKeyValue,int iStatus);
int ReportMouseState(int key,int dx,int dy);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
