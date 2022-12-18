#ifndef _VINPUT_SELF
#define _VINPUT_SELF

int Hi_Vinput_Init();
int Hi_Vinput_DeInit(void);
int ReportKeyEvent(int iKeyValue,int iStatus);
int ReportMouseState(int key,int dx,int dy);
#endif
