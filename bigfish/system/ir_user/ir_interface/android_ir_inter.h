#ifndef __IR_H__
#define __IR_H__


#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#pragma GCC diagnostic ignored "-fpermissive"
typedef enum {
	FALSE    = 0,
	TRUE     = 1,
} BOOL;
typedef enum  _KEY_STATUS_E
{
	KEY_STATUS_DOWN = 0 ,   /**<Pressed*/
	KEY_STATUS_HOLD ,       /**<Hold*/
	KEY_STATUS_UP ,         /**<Released*/
	KEY_STATUS_BUTT
}KEY_STATUS_E ;

#define IR_Open(void)  IR_Init(void)
signed int IR_Init(void);

#define IR_Close(void) IR_DeInit(void)
signed int IR_DeInit(void);

signed int IR_Enable(BOOL bEnable);

#define IR_GetValue(penPressStatus, pu64KeyId, u32TimeoutMs) IR_GetValueWithProtocol(penPressStatus, pu64KeyId, NULL, 0, u32TimeoutMs)

unsigned int  IR_GetValueWithProtocol (KEY_STATUS_E *penPressStatus, unsigned long long *pu64KeyId,
        char *pszProtocolName, signed int  s32NameSize, unsigned int u32TimeoutMs);

signed int IR_SetFetchMode(signed int s32Mode);

signed int IR_GetSymbol(unsigned long long *pu64First, unsigned long long* pu64Second, unsigned int u32TimeoutMs);

signed int IR_EnableKeyUp(BOOL bEnable);

signed int IR_EnableRepKey(BOOL bEnable);

signed int IR_SetRepKeyTimeoutAttr(unsigned int u32TimeoutMs);

signed int IR_Reset(void);

signed int IR_EnableProtocol(char* pszProtocolName);

signed int IR_DisableProtocol(char * pszProtocolName);

signed int  IR_GetProtocolEnabled(char* pszProtocolName, BOOL *pbEnabled);

signed int IR_SetCodeType(signed int enIRCode);

#pragma GCC diagnostic pop
#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif
