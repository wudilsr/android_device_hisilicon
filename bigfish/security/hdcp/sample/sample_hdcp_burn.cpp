#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include "hi_type.h"


extern "C" HI_S32  HI_HDCP2_SetHDCPKey(HI_U8 *pKey, HI_U32 u32Length);

int main(int argc, char **argv)
{
    unsigned char buf[902];
    FILE *fp = NULL; 

    if (argc != 2)
    {
        printf("Usage: hdcp_burn_v3 [key_file]\n");
        return -1;
    }

    fp = fopen(argv[1], "rb");
    if (fp)
    {
        fread((char *)buf, 1, sizeof(buf), fp);
        fclose(fp);
        return HI_HDCP2_SetHDCPKey(buf, sizeof(buf));
    }

    return -1;
}
