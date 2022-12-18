
#include <stdio.h>
#include <stdlib.h>
#include "libclientadp.h"

#define LOG_TAG "CLIENT"
#include <utils/Log.h>
#define CLIENT_PRINTF ALOGE

typedef struct tagCLIENT_MEMBER_S
{
    unsigned int client;
} CLIENT_MEMBER_S;

class ViewRightWebClient;

static void VRClientHTTPCallback(void * pUserParam, const char * url, unsigned int reason)
{
    CLIENT_PRINTF("CLIENT: URL: %s - Retrieve Code = %d\n", url, reason);
}

int CLIENT_Init(unsigned int *pHdl)
{
    CLIENT_MEMBER_S *pstMember = NULL;

    if (NULL == pHdl)
        return CLIENT_FAILURE;

    pstMember = (CLIENT_MEMBER_S*)malloc(sizeof(CLIENT_MEMBER_S));

    if (NULL == pstMember)
        return CLIENT_FAILURE;

    *pHdl = (unsigned int)pstMember;

    return CLIENT_SUCCESS;
}

int CLIENT_GetKey(unsigned int handle, const char *purl, char *key, unsigned int keybufferlen, unsigned int *key_len)
{
    if (0 == handle)
        return CLIENT_FAILURE;

    CLIENT_PRINTF("CLIENT: Client is empty, use default path obtain key \n");

    return CLIENT_FAILURE;
}

int CLIENT_Deinit(unsigned int handle)
{
    CLIENT_MEMBER_S *pstMember = (CLIENT_MEMBER_S*)handle;

    if (NULL != pstMember)
    {
        free(pstMember);
    }
    else
    {
        return CLIENT_FAILURE;
    }

    return CLIENT_SUCCESS;
}

