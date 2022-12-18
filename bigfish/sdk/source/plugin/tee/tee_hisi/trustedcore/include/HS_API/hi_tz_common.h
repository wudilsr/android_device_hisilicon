/**
 * @file Hi_Tz_Common.h
 */

#ifndef	__HI_TZ_COMMON_H__
#define	__HI_TZ_COMMON_H__

typedef enum
{
	CMD_TZ_HDCP_SETHDMISTATUS = 1,
	CMD_TZ_CIPHER_INIT,
	CMD_TZ_CIPHER_DEINIT,
	CMD_TZ_CIPHER_ENCRYPT,
	CMD_TZ_CIPHER_ENCRYPTMULTI,
	CMD_TZ_CIPHER_DECRYPT,
	CMD_TZ_CIPHER_DECRYPTMULTI,
	CMD_TZ_CIPHER_CONFIGHANDLE,
	CMD_TZ_CIPHER_CREATEHANDLE,
	CMD_TZ_CIPHER_DESTROYHANDLE,
	CMD_TZ_CIPHER_GETHANDLECONFIG,
	CMD_TZ_CIPHER_GETRANDOMNUMBER,
	CMD_TZ_CIPHER_ENCRYPTHDCPKEY,
	CMD_TZ_CIPHER_LOADHDCPKEY,
	CMD_TZ_CIPHER_HASHINIT,  //15
	CMD_TZ_CIPHER_HASHUPDATE,
	CMD_TZ_CIPHER_HASHFINAL,
	CMD_TZ_OTP_TEST,
	CMD_TZ_CIPHER_TEST,
	CMD_TZ_ADVCA_GDRMENCRYPT,
	CMD_TZ_TEST  = 0x100,
	CMD_TZ_BUTT
}HiTzCommandId_E;

#endif

