/******************************************************************************

  Copyright (C), 2011-2021, Hisilicon Tech. Co., Ltd.

 ******************************************************************************
  File Name     : hi_playreadyhttp.h
  Version       : Initial Draft
  Author        : Hisilicon multimedia software group
  Created       : 2011.12.17
  Description   :
  History       :

*******************************************************************************/

#ifndef __HI_PLAYREADYHTTP_H__
#define __HI_PLAYREADYHTTP_H__

#ifdef __cplusplus
#if __cplusplus
extern "C"{
#endif
#endif /* __cplusplus */

#include "hi_type.h"
#include "hi_common.h"
#include "hi_playready.h"


/* http status, sent in sync with the license states
*/
typedef enum hiPLAYREADY_HTTP_STATE_E
{
    HI_PLAYREADY_HTTP_STATUS_OK            = 0,
     HI_PLAYREADY_HTTP_STATUS_FAILED_REPSONSE_CODE,
    HI_PLAYREADY_HTTP_STATUS_FAILED_RESPONSE_READ,
    HI_PLAYREADY_HTTP_STATUS_FAILED_CONNECT,
    HI_PLAYREADY_HTTP_STATUS_FAILED_GETPOST,
    HI_PLAYREADY_DRM_E_SERVER_DEVICE_LIMIT_REACHED,
    HI_PLAYREADY_DRM_E_DEVCERT_REVOKED,
    HI_PLAYREADY_DRM_E_SERVER_INTERNAL_ERROR,
    HI_PLAYREADY_DRM_E_SERVER_INVALID_MESSAGE,
    HI_PLAYREADY_DRM_E_SERVER_SERVICE_SPECIFIC,
    HI_PLAYREADY_HTTP_STATUS_REQUIRE_DOMAIN,
    HI_PLAYREADY_DRM_E_SERVER_RENEW_DOMAIN,
    HI_PLAYREADY_HTTP_INTERNAL_SERVER_UNKNOWN,
    HI_PLAYREADY_DRM_E_SERVER_NOT_A_MEMBER,
    HI_PLAYREADY_DRM_E_SERVER_PROTOCOL_VERSION_MISMATCH,
    HI_PLAYREADY_DRM_E_SERVER_UNKNOWN_ACCOUNTID,
    HI_PLAYREADY_DRM_E_SERVER_PROTOCOL_REDIRECT,
    
    HI_PLAYREADY_HTTP_STATUS_MAX
}HI_PLAYREADY_HTTP_STATE_E;

/* http header structure */
typedef struct PLAYREADY_HTTP_HEADER_s
{
    HI_PLAYREADY_ASCII_STRING name;
    HI_PLAYREADY_ASCII_STRING value;
    
    struct PLAYREADY_HTTP_HEADER_s *next;
}PLAYREADY_HTTP_HEADER_S;

typedef struct
{
    HI_U8   *url;                  // url ptr
    HI_U32   port;                 // port value
    HI_U8   *query;                // ptr into query
    HI_U8    host[0x40];           // server host
    HI_U8    protocol[8];          // protocol
} HI_PLAYREADY_URL;

/**
\brief 	 Send the Challenge to the Server(URL contain in the pChallenge), And store the Response returned by the Server.
		IsWhatEncryp is the Challenge Type 
\attention \n
*/
HI_U32 HI_PLAYREADY_HTTP_FetchLicense(HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_ASCII_STRING *pResponse, HI_IS_WHAT_ENCRYPT IsWhatEncryp);

/**
\brief 	 Send the Challenge to the Server(URL contain in the pChallenge), And store the Response returned by the Server.
		IsWhatEncryp is the Challenge Type 
		This function does not include socket opening and connecting. The socket's opening and connecting should be implemented outside.
\attention \n
*/
HI_U32 HI_PLAYREADY_HTTP_FetchLicenseEx(HI_S32 *ps32SocketFd, HI_PLAYREADY_URL *pstUrl, HI_PLAYREADY_CHALLENGE_S *pChallenge, HI_PLAYREADY_ASCII_STRING *pResponse, HI_IS_WHAT_ENCRYPT IsWhatEncryp);
/**
\brief Release the Response Resource after Called HI_PLAYREADY_HTTP_FetchLicenseEx.
	
\attention MUST be called after HI_PLAYREADY_HTTP_FetchLicense(Ex) when don't need the Response.\n
*/
HI_VOID HI_PLAYREADY_HTTP_Release_Response(HI_PLAYREADY_ASCII_STRING *pResponse);


#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */


#endif /* __HI_PLAYREADYHTTP_H__ */


