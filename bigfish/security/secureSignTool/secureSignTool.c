#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <dirent.h>
#include <unistd.h>
#include "src/adapter.h"
#include "priv_signTool.h"
#include "signprocess.h"
#include "sparse.h"
#include "version.h"

//boot
#define KeyArea                 "KeyArea.bin"
#define KeyAreaSign             "KeyAreaSign.bin"
#define ParamArea               "ParamArea.bin"
#define ParamAreaSign           "ParamAreaSign.bin"
#define BootArea                "BootArea.bin"
#define BootAreaSign            "BootAreaSign.bin"
#define FinalBoot               "FinalBoot.bin"
#define UncheckedArea           "UncheckedArea.bin"

//kernel fs
#define KernelSign              "./SignOutput/kernel.sig"
#define RootfsSign              "./SignOutput/rootfs.sig"


//for non-boot
#define PAGE_SIZE   0x2000
#define IMG_MAX_BLOCK_NUM   5
#define SIGNATURE_LEN 256

#define CAIMGHEAD_MAGICNUMBER   "Hisilicon_ADVCA_ImgHead_MagicNum"
#define CAIMGHEAD_VERSION       "v1.0.0.3"


#define ROWCNT          2
#define BLKCNT          2

#define SIZE_K        1024
#define BLOCKNUM      15
#define SIGNATURESIZE 16
#define SIGNBLOCKSIZE (1024*1024)
#define PARTNUM_MAX   256
#define SIGN_SIZE 0x100000  //1M



typedef struct hi_CAImgHead_S
{
    unsigned char  u8MagicNumber[32];
    unsigned char  u8Version[8];
    unsigned int u32TotalLen;
    unsigned int u32CodeOffset;
    unsigned int u32SignedImageLen;
    unsigned int u32SignatureOffset;
    unsigned int u32SignatureLen;
    unsigned int u32BlockNum;
    unsigned int u32BlockOffset[IMG_MAX_BLOCK_NUM];
    unsigned int u32BlockLength[IMG_MAX_BLOCK_NUM];
    unsigned int Reserverd[32];
    unsigned int u32CRC32;
} HI_CAImgHead_S;

typedef struct
{
    unsigned char u8MagicNumber[32];             //Magic Number: "Hisilicon_ADVCA_ImgTail_MagicNum"
    unsigned char u8Version[8];                  //version: "V000 0003" , former version "V000 0002"
    unsigned int  u32CreateDay;                  //yyyymmdd
    unsigned int  u32CreateTime;                 //hhmmss
    unsigned int  u32HeadLength;                 //The following data size
    unsigned int  u32SignedDataLength;           //signed data length
    unsigned int  u32IsYaffsImage;               //Yaffsr image need to specail read-out, No use
    unsigned int  u32IsConfigNandBlock;          //Yaffsr image need to specail read-out, No use
    unsigned int  u32NandBlockType;              //Yaffsr image need to specail read-out, No use
    unsigned int  u32IsNeedEncrypt;              //if "1", code need to be encrypted.
    unsigned int  u32IsEncrypted;                //if "1", code has encrypted.
    unsigned int  u32HashType;                   //if "0", u8Sha save sha1 of code, if "1",  u8Sha save sha256 of code
    unsigned char u8Sha[32];                     //SHA value
    unsigned int  u32SignatureLen;               //Actural Signature length
    unsigned char u8Signature[256];              //Max length:0x100
    unsigned char OrignalImagePath[256];         //Max length:
    unsigned char RSAPrivateKeyPath[256];        //Max length:0x100
    unsigned int  u32CurrentsectionID;            //begin with 0
    unsigned int  u32SectionSize;                 //section size
    unsigned int  u32TotalsectionID;              //Max section ID > 1
    unsigned int  CRC32;                         //CRC32 of upper data
} HI_CASignImageTail_S;


typedef enum hi_Algorithm_E
{
    Hash1,
    Hash2
}HI_Algorithm_EN;

#define     POLYNOMIAL 0x04c11db7L
static short _First = 1;                       /*Init _CrcTable[256] Flag, Only init once time*/
static unsigned long  _CrcTable[256];                  /*Calculate CRC32*/

#define SRC_FILE_NUM 32
#define SRC_FILE_LEN 4096


HI_CHIPSET_TYPE_EN g_enChipsetType_android = Hi3716CV200;

static void GenCrcTable()
{
    int i, j;
    unsigned long crc_accum;
    for( i = 0;  i < 256;  i++ )
    {
        crc_accum =  ( i << 24 );
        for( j = 0;  j < 8;  j++ )
        {
            if( crc_accum & 0x80000000L )
                crc_accum = ( crc_accum << 1 ) ^ POLYNOMIAL;
            else
                crc_accum = ( crc_accum << 1 );
        }
        _CrcTable[i] = crc_accum;
    }
    return;
}


unsigned long DVB_CRC32(unsigned char *buf, int length)
{
    unsigned long crc = 0xffffffff;

    if(_First)
    {
        GenCrcTable();
        _First = 0;
    }
    while( length-- )
    {
        crc = (crc << 8) ^ _CrcTable[((crc >> 24) ^ *buf++) & 0xff];
    }

    return crc;
}

void StrTrim(char*pStr)
{
    char *pTmp = pStr;

    while(*pStr != '\0')
    {
        if(*pStr != ' ')
        {
            *pTmp++ = *pStr;
        }

        ++pStr;
    }

    *pTmp = '\0';
}

int ParseFile(char *tmp,const char *str, char *srcFile)
{
    char *ptr = NULL;
    int length = 0, offset = 0;
    if (tmp[0] == '#') return 0;

    length = strlen(tmp);
    if (tmp[length - 1] == 0x0a && tmp[length - 2] == 0x0d)
    {
         offset = 2;
    }
    else if (tmp[length -1] == 0x0a && tmp[length -2] != 0x0d)
    {
         offset = 1;
    }

    if(!strncmp(tmp, str,strlen(str)) && *(tmp + strlen(str)) == '=')
    {
        ptr = (strrchr(tmp,'='));
        if(ptr)
        {
            ptr++;
            StrTrim(ptr);
            if(!isalnum(*ptr))
            {
                printf("input file %s is null or space before!\n",str);
                return -1;
            }
            strncpy(srcFile,ptr, strlen(ptr) - offset);
        }
        else
        {
            ptr = (strchr(tmp,':'));
            StrTrim(ptr);
            if(ptr)
            {
                ptr++;
                if(!isalnum(*ptr))
                {
                    printf("input file %s is null or space before!\n",str);
                    return -1;
                }
                strncpy(srcFile,ptr, strlen(ptr) - offset);
            }
        }
    }
    return 0;
}

int GetDirName(char *tmp, char *dir)
{
    char *ptr = strchr(tmp,'=');
    int length, offset = 0;
    if(ptr)
    {
       ptr++;
       if('.' == *ptr)   // delete . or /
       {
            ptr += 2;
       }
       else if('/' == *ptr)
       {
            ptr++;
       }

       length = strlen(ptr);
       if (ptr[length - 1] == 0x0a && ptr[length - 2] == 0x0d)
       {
            offset = 2;
       }
       else if (ptr[length -1] == 0x0a && ptr[length -2] != 0x0d)
       {
            offset = 1;
       }

       if (strrchr(ptr, '/'))   //if last input name chr is '/'
       {
            strncpy(dir,ptr, strlen(ptr) - offset - 1);
       }
       else
       {
            strncpy(dir,ptr, strlen(ptr) - offset);
       }

    }
    else
    {
        printf("no output path!\n");
        return -1;
    }
    return 0;
}

int main(int argc, char **argv)
{
    struct stat buf;

    int ret;
    unsigned int msid = 0, versionid = 0;
    unsigned int sectionSize = 0;
    FILE *fp = NULL;
    char tmp[SRC_FILE_LEN];


    //for boot sign final
    unsigned int strSrcParamList[11];
    char strSrcFileList[SRC_FILE_NUM][SRC_FILE_LEN] = {0};
    char strDestPaths[SRC_FILE_NUM][SRC_FILE_LEN] = {0};

    char srcFile[SRC_FILE_NUM][SRC_FILE_LEN] = {0};
    char tmp2[SRC_FILE_NUM][SRC_FILE_LEN] = {0};
    char dirname[32] = "mkdir ";
    char rmdir[32] = "rm -rf ";
    char chmod[32] = "chmod 777 -R ";
    char *ptr = NULL;
    int i,oc;
    int type = -1;
    char config_filename[SRC_FILE_LEN]={0};
    char bootcfg_filename[SRC_FILE_LEN]={0};
    char rsakey_dirname[SRC_FILE_LEN]={0};
    char inputdir[SRC_FILE_LEN]={0};
    char outputdir[SRC_FILE_LEN]={0};
    char outputfile[SRC_FILE_LEN]={0};

    if(argc < 2)
    {
        printf("version: %s\n", GetVersion());
        printf("Usage:%s\n" \
                "-t  set Signed type:\n" \
                "      0    Signboot_config\n" \
                "      1    merge_config\n" \
                "      2    common_config\n" \
                "      3    special_config\n" \
                "      4    crypto_config\n" \
                "-c  input configure file name\n" \
                "-b  input Boot cfg file\n" \
                "-k  input rsa key directory name\n" \
                "-r  input unsigned file directory name\n" \
                "-o  output signed file directory name\n", argv[0]);
        return -1;
    }

    while((oc = getopt(argc, argv, "r:o:k:b:c:t:")) != -1)
    {
        switch(oc)
        {
        case 't':{
            type = atoi(optarg);
            printf("type:%s\n",optarg);
            break;
            }
        case 'c':{
            sprintf(config_filename,"%s",optarg);
            printf("configure filename:%s\n", config_filename);
            break;
            }
        case 'b':{
            sprintf(bootcfg_filename,"%s",optarg);
            printf("boot cfg filename:%s\n", bootcfg_filename);
            break;
            }
        case 'k':{
            sprintf(rsakey_dirname,"%s",optarg);
            ptr = strrchr(rsakey_dirname, '/');
            rsakey_dirname[ptr - rsakey_dirname + 1] = '\0';
            printf("rsa key directory name:%s\n", rsakey_dirname);
            break;
            }
        case 'r':{
#if 0
            i = optind-1;
            while(i < argc)
            {
                sprintf(config_filename,"%s",argv[i]);
                i++;
                if(config_filename[0] != '-')/* check if optarg is next switch */
                {
                    printf("configure filename:%s\n", config_filename);
                }
                else
                    break;
            }
#endif
            sprintf(inputdir,"%s",optarg);
            ptr = strrchr(inputdir, '/');
            inputdir[ptr - inputdir + 1] = '\0';
            printf("unsigned image directory name:%s\n", inputdir);
            break;
            }
        case 'o':{
            sprintf(outputdir,"%s",optarg);
            ptr = strrchr(outputdir, '/');
            outputdir[ptr - outputdir + 1] = '\0';
            printf("output signed image directory name:%s\n", outputdir);
            break;
            }
        default:{
            printf("unknow args\n");
            break;
            }
        }
    }

    if (outputdir[0] == 0 || inputdir[0] ==0)
    {
        printf("Input or Output directory is null, Please input!\n");
        return -1;
    }
    if (type == -1)
    {
        printf("Please input signed type!!!\n");
        return -1;
    }
    if ((fp = fopen(config_filename, "r")) == NULL)
    {
        printf("Open configure file name failed\n");
        return -1;
    }

    memset(strSrcFileList, 0, sizeof(strSrcFileList));
    memset(strSrcParamList, 0, sizeof(strSrcParamList));
    memset(strDestPaths, 0, sizeof(strDestPaths));

    if(0 == type)
    {
        do
        {
            memset(tmp, 0, sizeof(tmp));
            fgets(tmp, SRC_FILE_LEN, fp);
            StrTrim(tmp);

            ret = ParseFile(tmp, "Root_private_key_file", srcFile[0]);
            ret |= ParseFile(tmp, "External_private_key_file", srcFile[1]);
            ret |= ParseFile(tmp, "External_public_key_file", srcFile[2]);
            ret |= ParseFile(tmp, "CFG", srcFile[3]);
            ret |= ParseFile(tmp, "BootFile", srcFile[4]);
            ret |= ParseFile(tmp, "Chip_Type", srcFile[5]);
            ret |= ParseFile(tmp, "MSID", srcFile[6]);
            ret |= ParseFile(tmp, "Version", srcFile[7]);
            ret |= ParseFile(tmp, "OutputSignedFile", outputfile);
            if(0 != ret)
            {
                printf("parse file failed!\n");
                return -1;
            }
#if 0
            if(!strncasecmp(tmp, "InputFileDir",strlen("InputFileDir")))
            {
                ret = GetDirName(tmp,inputdir);
                if(0 != ret)
                {
                    printf("get input dir fail!\n");
                    return -1;
                }
            }
            if(!strncasecmp(tmp, "OutputFileDir",strlen("OutputFileDir")))
            {
                ret = GetDirName(tmp,outputdir);
                if(0 != ret)
                {
                    printf("get output dir fail!\n");
                    return -1;
                }
            }
#endif
        }while(!feof(fp));

        if(!strcasecmp("Hi3716CV200", srcFile[5]))
        {
            SetChipsetType(Hi3716CV200);
        }
        else if(!strcasecmp("Hi3716MV300", srcFile[5]))
        {
            SetChipsetType(Hi3716MV300);
        }
        else if(!strcasecmp("Hi3719MV100", srcFile[5]))
        {
            SetChipsetType(Hi3719MV100);
        }
        else if(!strcasecmp("Hi3719CV100", srcFile[5]))
        {
            SetChipsetType(Hi3719CV100);
        }
        else
        {
            SetChipsetType(Hi3716CV200);
        }

        if (rsakey_dirname[0] != 0)
        {//key dir file
            for( i=0; i < 3; i++)
            {
                strcpy(strSrcFileList[i],rsakey_dirname);
                strcat(strSrcFileList[i],srcFile[i]);
                strSrcFileList[i][strlen(strSrcFileList[i])] = '\0';
                printf("strSrcFileList[%d]=%s\n",i,strSrcFileList[i]);
            }
        }

        if (bootcfg_filename[0] != 0)
        {//boot cfg file
            sprintf(strSrcFileList[3],"%s",bootcfg_filename);
            printf("strSrcFileList[%d]=%s\n",3,strSrcFileList[3]);
        }
        if (inputdir[0] != 0)
        {//input boot file
            strcpy(strSrcFileList[4],inputdir);
            strcat(strSrcFileList[4],srcFile[4]);
            strSrcFileList[4][strlen(strSrcFileList[4])] = '\0';
            printf("strSrcFileList[%d]=%s\n",4,strSrcFileList[4]);
        }

        for(i = 5; i < sizeof(strSrcFileList)/sizeof(strSrcFileList[0]); i++)
        {
            strcpy(tmp2[i], inputdir);
            if(!('/' == inputdir[strlen(inputdir) -1]))
            {
                strcat(tmp2[i], "/");
            }

            strcat(tmp2[i],srcFile[i]);
            strcpy(strSrcFileList[i], tmp2[i]);
            strSrcFileList[i][strlen(strSrcFileList[i])] = '\0';
        }

        if(lstat(strSrcFileList[4],&buf))   // boot file
        {
            printf("not found boot file!\n");
            return -1;
        }

        sscanf(srcFile[6], "%x", &msid);
        sscanf(srcFile[7], "%x", &versionid);

        mkdir(outputdir, 0755);
        //strcat(chmod, outputdir);
        //system(chmod);

        for(i= 0; i < sizeof(strDestPaths)/sizeof(strDestPaths[0]); i++)
        {
            strcpy(strDestPaths[i],outputdir);
            strcat(strDestPaths[i],"/");
        }
        strcat(strDestPaths[0],KeyArea);
        strcat(strDestPaths[1],KeyAreaSign);
        strcat(strDestPaths[2],ParamArea);
        strcat(strDestPaths[3],ParamAreaSign);
        strcat(strDestPaths[4],BootArea);
        strcat(strDestPaths[5],BootAreaSign);
        if (outputfile[0] != 0)
        {
            strcat(strDestPaths[6],outputfile);
        }
        else
        {
            strcat(strDestPaths[6],FinalBoot);
        }
        strcat(strDestPaths[7],UncheckedArea); //UncheckedArea

        strSrcParamList[0] = msid;  // msid
        strSrcParamList[1] = 0;
        strSrcParamList[2] = 0;
        strSrcParamList[3] = 0;
        strSrcParamList[4] = 0;
        strSrcParamList[5] = 0;
        strSrcParamList[6] = 0;
        strSrcParamList[7] = 0;
        strSrcParamList[8] = buf.st_size;
        strSrcParamList[9] = msid;
        strSrcParamList[10] = versionid;

        BOOL bRet = MakeKeyAreaFile(strSrcFileList[2], strSrcParamList[0], strDestPaths[0]);
        if(bRet) bRet = MakeSignFile(strDestPaths[0], strSrcFileList[0], strDestPaths[1]);
        if(bRet) bRet = MakeParamAreaFile((strSrcParamList+1), strSrcFileList[3], strDestPaths[2]);
        if(bRet) bRet = MakeSignFile(strDestPaths[2], strSrcFileList[1], strDestPaths[3]);
        if(bRet) bRet = MakeBootAreaFile(strSrcFileList[4], (strSrcParamList+1), strDestPaths[4], strDestPaths[7]);
        if(bRet) bRet = MakeSignFile(strDestPaths[4], strSrcFileList[1], strDestPaths[5]);
        if(bRet)
        {
            if(MakeFinalBootFile(strDestPaths[0], strDestPaths[1],
                                                                    strDestPaths[2], strDestPaths[3],
                                                                    strDestPaths[4], strDestPaths[5],
                                                                    strDestPaths[7],
                                                                    strDestPaths[6]))
            {
                printf("The signed img has been created success in %s!\n",outputdir);
            }
        }
    }
    else if(1 == type)
    {
        do
        {
            memset(tmp, 0, sizeof(tmp));
            fgets(tmp, SRC_FILE_LEN, fp);
            ret = ParseFile(tmp, "Key_Area_File", srcFile[0]);
            ret |= ParseFile(tmp, "Key_Area_Sign_File", srcFile[1]);
            ret |= ParseFile(tmp, "Param_Area_File", srcFile[2]);
            ret |= ParseFile(tmp, "Param_Area_Sign_File", srcFile[3]);
            ret |= ParseFile(tmp, "Fastboot_Area_File", srcFile[4]);
            ret |= ParseFile(tmp, "Fastboot_Area_Sign_File", srcFile[5]);
            ret |= ParseFile(tmp, "Ucheked_Area_File", srcFile[6]);
            ret |= ParseFile(tmp, "Chip_Type", srcFile[7]);
            ret |= ParseFile(tmp, "OutputSignedFile", outputfile);
            if(0 != ret)
            {
                printf("parse file %s failed!\n", argv[2]);
                return -1;
            }
#if 0
            if(!strncasecmp(tmp, "InputFileDir",strlen("InputFileDir")))
            {
                ret = GetDirName(tmp,inputdir);
                if(0 != ret)
                {
                    printf("The parameter InputFileDir is not correct!, please check it.\n");
                    return -1;
                }
            }
            if(!strncasecmp(tmp, "OutputFileDir",strlen("OutputFileDir")))
            {
                ret = GetDirName(tmp,outputdir);
                if(0 != ret)
                {
                    printf("The parameter OutputFileDir is not correct!, please check it.\n");
                    return -1;
                }
            }
#endif
        }while(!feof(fp));

        if(!strcasecmp("Hi3716CV200", srcFile[7]))
        {
            SetChipsetType(Hi3716CV200);
        }
        else if(!strcasecmp("Hi3716MV300", srcFile[7]))
        {
            SetChipsetType(Hi3716MV300);
        }
        else if(!strcasecmp("Hi3719MV100", srcFile[7]))
        {
            SetChipsetType(Hi3719MV100);
        }
        else if(!strcasecmp("Hi3719CV100", srcFile[7]))
        {
            SetChipsetType(Hi3719CV100);
        }
        else
        {
            SetChipsetType(Hi3716CV200);
        }

        //add srcfile path
        for(i = 0; i < sizeof(strSrcFileList)/sizeof(strSrcFileList[0]); i++)
        {
            strcpy(tmp2[i], inputdir);
            if(!('/' == inputdir[strlen(inputdir) -1]))
            {
                strcat(tmp2[i], "/");
            }

            strcat(tmp2[i],srcFile[i]);
            strcpy(strSrcFileList[i], tmp2[i]);
            strSrcFileList[i][strlen(strSrcFileList[i])] = '\0';
        }

        mkdir(outputdir, 0755);
//        strcat(chmod, outputdir);
//        system(chmod);

        // dest file final boot path
        strcpy(strDestPaths[7],outputdir);
        if (outputfile[0] != 0)
        {
            strcat(strDestPaths[7],outputfile);
        }
        else
        {
            strcat(strDestPaths[7],"/FinalBoot.bin");
        }

        if(MakeFinalBootFile(strSrcFileList[0], strSrcFileList[1],
                                                                    strSrcFileList[2], strSrcFileList[3],
                                                                    strSrcFileList[4], strSrcFileList[5],
                                                                    strSrcFileList[6],
                                                                    strDestPaths[7]))
        {
            printf("The signed boot has been created success in %s\n", strDestPaths[7]);
        }

    }
    else if (2 == type)
    {
        do
        {
            memset(tmp, 0, sizeof(tmp));
            fgets(tmp, SRC_FILE_LEN, fp);
            StrTrim(tmp);

            ret = ParseFile(tmp, "External_private_key_file", srcFile[1]);
            ret |= ParseFile(tmp, "SectionSize", srcFile[2]);
            ret |= ParseFile(tmp, "InputFile", srcFile[3]);
            ret |= ParseFile(tmp, "OutputSignedFile", outputfile);
            if (0 != ret)
            {
                printf("parse file %s failed!\n", argv[2]);
                return -1;
            }
#if 0
            if (!strncasecmp(tmp, "InputFileDir",strlen("InputFileDir")))
            {
                ret = GetDirName(tmp, inputdir);
                if (0 != ret)
                {
                    printf("The parameter InputFileDir is not correct!, please check it.\n");
                    return -1;
                }
            }
            if (!strncasecmp(tmp, "OutputFileDir",strlen("OutputFileDir")))
            {
                ret = GetDirName(tmp, outputdir);
                if(0 != ret)
                {
                    printf("The parameter OutputFileDir is not correct!, please check it.\n");
                    return -1;
                }
            }
#endif
        }while(!feof(fp));

        if (outputfile[0] == 0)
        {
            sprintf(outputfile,"%s",srcFile[3]);
            printf("OutputSignedFile is null, set OutputSignedFile=%s . Warnning!!!\n",outputfile);
        }
        sprintf(srcFile[4],"%s",outputfile);

        //add srcfile path
        for (i = 0; i < sizeof(strSrcFileList) / sizeof(strSrcFileList[0]); i++)
        {
            strcpy(tmp2[i], inputdir);
            if(!('/' == inputdir[strlen(inputdir) -1]))
            {
                strcat(tmp2[i], "/");
            }

            strcat(tmp2[i],srcFile[i]);
            strcpy(strSrcFileList[i], tmp2[i]);
            strSrcFileList[i][strlen(strSrcFileList[i])] = '\0';
        }

        if (rsakey_dirname[0] != 0)
        {
            strcpy(strSrcFileList[1],rsakey_dirname);
            strcat(strSrcFileList[1],srcFile[1]);
            strSrcFileList[1][strlen(strSrcFileList[1])] = '\0';
            printf("strSrcFileList[%d]=%s\n",1,strSrcFileList[1]);
        }

        mkdir(outputdir, 0755);
//        strcat(chmod, outputdir);
//        system(chmod);

        // dest file final boot path
        strcpy(strDestPaths[0],outputdir);
        strcat(strDestPaths[0], "/");
        strcat(strDestPaths[0], srcFile[4]);

        sectionSize =  strtoul(srcFile[2], 0, 16);

        if (TRUE == Sign_NonBOOTImage_Common(strDestPaths[0], strSrcFileList[1], strSrcFileList[3], sectionSize))
        {
            printf("sign %s sucessful!\n", strSrcFileList[3]);
        }
        else
        {
            printf("sign %s sucessful!\n", strSrcFileList[3]);
        }
    }
    else if (3 == type)
    {
        mkdir(outputdir, 0755);
//        strcat(chmod, outputdir);
//        system(chmod);

        ret = Sign_NonBOOTImage_Special(config_filename, inputdir, outputdir, rsakey_dirname);
        if (TRUE == ret)
        {
            printf("success!\n");
        }
        else
        {
            printf("failed!\n");
        }
    }
    else if (4 == type)
    {
        mkdir(outputdir, 0755);

        ret = Sign_NonBOOTImage_Crypto(config_filename, inputdir,outputdir,rsakey_dirname);
        if (0 == ret)
        {
            printf("success!\n");
        }
        else
        {
            printf("failed!\n");
        }
    }
    return 0;
}
