#include <stdio.h>
#include<time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "adapter.h"
#include "sign_non_boot_image.h"

#define FILE_NUMBER 32
#define FILE_PATH_LENGTH 4096

typedef struct image_attribute_st
{
    unsigned char ImageName[FILE_PATH_LENGTH];
    unsigned char SignImage[FILE_PATH_LENGTH];
    unsigned char strlength[FILE_NUMBER/4];
}IMG_ATTRIBUTE_ST;

static IMG_ATTRIBUTE_ST g_ImageList[FILE_NUMBER] = {0};
//char strDestPaths[FILE_NUMBER][FILE_PATH_LENGTH] = {0};


typedef struct sign_config_parameter_st
{
    unsigned char External_private_key_file[FILE_PATH_LENGTH];
    unsigned char HashMode[FILE_NUMBER / 4];
    unsigned char RSALength[FILE_NUMBER / 4];
    unsigned char HeaderSize[FILE_NUMBER / 4];
    unsigned char Support_block_signature[4];
    unsigned char SectionSize[FILE_NUMBER / 4];
    unsigned char CustomerData[FILE_PATH_LENGTH / 2];
    unsigned char ImageNumber[FILE_NUMBER / 4];
    unsigned char OutputFile[FILE_PATH_LENGTH];
    unsigned char InputFileDir[FILE_PATH_LENGTH/2];
    unsigned char OutputFileDir[FILE_PATH_LENGTH/2];
}SIGN_CONFIG_PARAMETER_ST;

unsigned int Char2Hex(char *pDataBuf)
{
    unsigned char u8TmpBuf[16];
    unsigned int u32Value;
    memset(u8TmpBuf, 0, sizeof(u8TmpBuf));
    u8TmpBuf[0] = pDataBuf[0];
    u8TmpBuf[1] = pDataBuf[1];
    u32Value = strtoul((const char *)u8TmpBuf, 0, 16);
    return u32Value;
}

unsigned long ToHex(char *strValue)
{
    unsigned long uValue = 0;
    char tmp[32] = {0};
    char *p = NULL;

    strcpy(tmp, strValue);

    if ((p = strstr(tmp, "k")) != NULL)
    {
        *p = 0;
        uValue = strtoul(tmp, NULL, 10);
        uValue <<= 10;
    }
    else if ((p = strstr(tmp, "K")) != NULL)
    {
        *p = 0;
        uValue = strtoul(tmp, NULL, 10);
        uValue <<= 10;
    }
    else if ((p = strstr(tmp, "m")) != NULL)
    {
        *p = 0;
        uValue = strtoul(tmp, NULL, 10);
        uValue <<= 20;
    }
    else if ((p = strstr(tmp, "M")) != NULL)
      {
        *p = 0;
        uValue = strtoul(tmp, NULL, 10);
        uValue <<= 20;
    }

    return uValue;
}

int PaserSignConfigParameter(const char *strConfigFile,
    SIGN_CONFIG_PARAMETER_ST *pConfigPara,
    const char* inputdir,
    const char* outputdir,
    const char* keydir)
{
    int ret;
    int i = 0;
    int length = 0;
    int imageNumber = -1;
    FILE *fp = NULL;
    char tmp[FILE_PATH_LENGTH];
    char buf[32];

    fp = fopen(strConfigFile, "r");
    if (fp == NULL)
    {
        printf("Open the config file %s failed\n", strConfigFile);
        return -1;
    }

    do
    {
        memset(buf, 0, sizeof(buf));
        memset(tmp, 0, sizeof(tmp));
        fgets(tmp, FILE_PATH_LENGTH, fp);
        StrTrim(tmp);

        ret  = ParseFile(tmp, "External_private_key_file", pConfigPara->External_private_key_file);
        ret |= ParseFile(tmp, "HashMode", pConfigPara->HashMode);
        ret |= ParseFile(tmp, "RSALength", pConfigPara->RSALength);
        ret |= ParseFile(tmp, "HeaderSize", pConfigPara->HeaderSize);
        ret |= ParseFile(tmp, "Support_block_signature", pConfigPara->Support_block_signature);
        ret |= ParseFile(tmp, "SectionSize", pConfigPara->SectionSize);
        ret |= ParseFile(tmp, "CustomerData", pConfigPara->CustomerData);
        ret |= ParseFile(tmp, "ImageNumber", pConfigPara->ImageNumber);
        ret |= ParseFile(tmp, "OutputSignedFile", pConfigPara->OutputFile);
        ret |= ParseFile(tmp, "InputFileDir", pConfigPara->InputFileDir);
        ret |= ParseFile(tmp, "OutputFileDir", pConfigPara->OutputFileDir);
        if (0 != ret)
        {
            fclose(fp);
            return -1;
        }

        memcpy(buf, "Image", 5);
        sprintf(buf + 5, "%d", i + 1);
        ParseFile(tmp, buf, g_ImageList[i].ImageName);

        memcpy(buf, "PartitionSize", 13);
        sprintf(buf + 13, "%d", i + 1);
        ParseFile(tmp, buf, g_ImageList[i].strlength);

        memset(buf, 0, sizeof(buf));
        memcpy(buf, "SignImage", 9);
        sprintf(buf + 9, "%d", i + 1);
        ParseFile(tmp, buf, g_ImageList[i].SignImage);
        if (0 == strncmp(tmp, buf, strlen(buf)))
        {
            i++;
        }
    }while(!feof(fp));
    fclose(fp);

    //add dir
    if (inputdir != NULL && inputdir[0] != 0)
    {
        sprintf(pConfigPara->InputFileDir,"%s",inputdir);
    }
    if (outputdir != NULL && outputdir[0] != 0)
    {
        sprintf(pConfigPara->OutputFileDir,"%s",outputdir);
    }

    //printf("i =  %d\n", i);
    //printf("pConfigPara->ImageNumber =  %s\n", pConfigPara->ImageNumber);
    //printf("atoi(pConfigPara->ImageNumber) =  %d\n", atoi(pConfigPara->ImageNumber));
    if (i != atoi(pConfigPara->ImageNumber))
    {
        printf("The parameter ImageNumber is not correct, please check it!\n");
        return -1;
    }

    // update sign image path
    for (i = 0; i < atoi(pConfigPara->ImageNumber); i++)
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, pConfigPara->InputFileDir);
        if(!('/' == tmp[strlen(tmp) -1]))
        {
            strcat(tmp, "/");
        }

        strcat(tmp, g_ImageList[i].ImageName);
        strcpy(g_ImageList[i].ImageName, tmp);
        g_ImageList[i].ImageName[strlen(g_ImageList[i].ImageName)] = '\0';
    }

    //
    for (i = 0; i < atoi(pConfigPara->ImageNumber); i++)
    {
        memset(tmp, 0, sizeof(tmp));
        strcpy(tmp, pConfigPara->OutputFileDir);
        if(!('/' == tmp[strlen(tmp) -1]))
        {
            strcat(tmp, "/");
        }

        strcat(tmp, g_ImageList[i].SignImage);
        strcpy(g_ImageList[i].SignImage, tmp);
        g_ImageList[i].SignImage[strlen(g_ImageList[i].SignImage)] = '\0';
    }

    memset(tmp, 0, sizeof(tmp));
    if (keydir != NULL && keydir[0] != 0)
    {
        strcpy(tmp, keydir);
    }
    else
    {
        strcpy(tmp, pConfigPara->InputFileDir);
    }
    if(!('/' == tmp[strlen(tmp) -1]))
    {
        strcat(tmp, "/");
    }
    strcat(tmp, pConfigPara->External_private_key_file);
    strcpy(pConfigPara->External_private_key_file, tmp);

    memset(tmp, 0, sizeof(tmp));
    strcpy(tmp, pConfigPara->OutputFileDir);
    if(!('/' == tmp[strlen(tmp) -1]))
    {
        strcat(tmp, "/");
    }
    strcat(tmp, pConfigPara->OutputFile);
    strcpy(pConfigPara->OutputFile, tmp);

    return 0;
}

void printConfigFile(void *pConfigFile)
{
    int i;
    SIGN_CONFIG_PARAMETER_ST *p = NULL;
    p = pConfigFile;

    printf("External_private_key_file=%s\n", p->External_private_key_file);
    printf("HashMode=%s\n", p->HashMode);
    printf("RSALength=%s\n", p->RSALength);
    printf("HeaderSize=%s\n", p->HeaderSize);
    printf("Support_block_signature=%s\n", p->Support_block_signature);
    printf("SectionSize=%s\n", p->SectionSize);
    printf("CustomerData=%s\n", p->CustomerData);
    printf("ImageNumber=%s\n", p->ImageNumber);
    printf("OutputSignedFile=%s\n", p->OutputFile);

    for (i = 0; i < atoi(p->ImageNumber); i++)
    {
        printf("Image%d=%s\n", i + 1, g_ImageList[i].ImageName);
        printf("PartitionSize%d=%s\n", i + 1, g_ImageList[i].strlength);
        printf("SignImage%d=%s\n", i + 1, g_ImageList[i].SignImage);
    }
}

//生成comon方式签名的镜像
BOOL Sign_NonBOOTImage_Common(char* strDestFile, const char *rsaKeyFile, const char* strSrcFile, unsigned int sectionSize)
{
    int fpInputFile;
    int nRet, index;
    char sMergetFile[256] = {0};
    char sSignatureDataFile[256] = {0};
    FILE *fileRsaKey, *fpOutFile, *fpSigntureDatefile;
    unsigned char hash[32], rsaBuf[256];
    unsigned int FilePathlen, InputFileLength;
    unsigned int SectionCount, LastSectionSize, SignedDataLength;
    char *ptr = NULL;

    //struct tm *ptr;
    //time_t it;
    rsa_context rsa;
    struct stat buf;
    HI_CASignImageTail_S stCAImageTail;

    if (!(fpInputFile = open(strSrcFile, O_RDONLY)))
    {
        printf("Open file %s failed!", strSrcFile);
        return FALSE;
    }

    //获取输入文件长度
    stat(strSrcFile, &buf);
    InputFileLength = buf.st_size;
    lseek(fpInputFile, 0, SEEK_SET);
    //分配内存：文件长度+32K
    unsigned char *filebuffer = (unsigned char *)malloc(InputFileLength + 0x8000);
    if (NULL == filebuffer)
    {
        printf("Malloc Filebuffer failed!!!\n");
        return FALSE;
    }
    memset(filebuffer, 0, InputFileLength + 0x8000);
    //读取输入签名文件的数据到buffer中
    read(fpInputFile, filebuffer, InputFileLength);
    close(fpInputFile);

    //分配页大小内存：8K
    unsigned char *Pagebuffer = (unsigned char *)malloc(PAGE_SIZE);
    if (NULL == Pagebuffer)
    {
        printf("Malloc Signbuffer failed!!!\n");
        free(filebuffer);
        return FALSE;
    }
    memset(Pagebuffer, 0, PAGE_SIZE);

    //打开最终输出文件
    memcpy(sMergetFile, strDestFile, strlen(strDestFile));
    memcpy(sSignatureDataFile, strDestFile, strlen(strDestFile));
    ptr = strrchr(sSignatureDataFile, '.');
    if (ptr != NULL) *ptr = '\0';
    //strcat(sMergetFile, "_Sign.img");
    strcat(sSignatureDataFile, ".sig");
    fpOutFile = fopen(sMergetFile, "wb");
    if (NULL == fpOutFile)
    {
        return FALSE;
    }
    fseek(fpOutFile, 0, SEEK_SET);
    //向输出文件输出数据
    fwrite(filebuffer, 1, InputFileLength, fpOutFile);
    fclose(fpOutFile);

    //解析rsa key
    if ((fileRsaKey = fopen(rsaKeyFile, "r")) == NULL)
    {
        printf("Open RSA key file %s failed!", rsaKeyFile);
        free(filebuffer);
        free(Pagebuffer);
        return FALSE;
    }

    rsa_init(&rsa, RSA_PKCS_V15, 0, NULL, NULL);
    if((nRet = mpi_read_file(&rsa->n, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&(rsa->e) , 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->d , 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->p , 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->q, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->dmp1, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->dmq1, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->iqmp, 16, fileRsaKey)) != 0)
    {
        printf("Failed to read rsa file!");
        fclose(fileRsaKey);
        nRet =  FALSE;
        goto FAIL;
    }
    fclose(fileRsaKey);

    if (0 == sectionSize)
    {
        //设置CA头部，保存在文件的尾部某个位置
        memset(&stCAImageTail, 0, sizeof(stCAImageTail));
        memcpy(stCAImageTail.u8MagicNumber, CAIMGHEAD_MAGICNUMBER, sizeof(stCAImageTail.u8MagicNumber));
        memcpy(stCAImageTail.u8Version, CAIMGHEAD_VERSION, sizeof(stCAImageTail.u8Version));

        //it = time(NULL);
        //ptr = localtime(&it);

        //stCAImageTail.u32CreateDay = (((ptr->tm_year + 1900)  << 12) & 0XFFFFF000) + ((ptr->tm_mon << 7) & 0XF80) + ptr->tm_mday;
        //stCAImageTail.u32CreateTime = ptr->tm_hour * 60 *60 + ptr->tm_min * 60 + ptr->tm_sec;
        stCAImageTail.u32HeadLength = sizeof(stCAImageTail);
        stCAImageTail.u32SignedDataLength = InputFileLength;
        stCAImageTail.u32CurrentsectionID = 0;
        stCAImageTail.u32TotalsectionID = 1;
        stCAImageTail.u32SectionSize = 0;
        stCAImageTail.u32IsYaffsImage = 0;

        //计算HASH256值
        sha2(filebuffer, stCAImageTail.u32SignedDataLength, hash, 0);
        //对HASH256值用RSA2048算法签名
        if ((nRet = rsa_pkcs1_sign(&rsa, RSA_PRIVATE, SIG_RSA_SHA256, 32, hash, rsaBuf)) != 0)
        {
            printf("Failed to make the sign!");
            nRet = FALSE;
            goto FAIL;
        }

        stCAImageTail.u32IsConfigNandBlock = 1;
        stCAImageTail.u32NandBlockType = 0;
        stCAImageTail.u32IsNeedEncrypt = 0;
        stCAImageTail.u32IsEncrypted   = 0;

        stCAImageTail.u32HashType = Hash2;
        memcpy(stCAImageTail.u8Sha, hash, 32);

        stCAImageTail.u32SignatureLen = 256;
        memcpy(stCAImageTail.u8Signature, rsaBuf, stCAImageTail.u32SignatureLen);

        //保存输入文件的路径
        FilePathlen = strlen(strSrcFile);
        if (FilePathlen > 255)
        {
            FilePathlen = 255;
        }
        memcpy(stCAImageTail.OrignalImagePath, strSrcFile, FilePathlen);

        //保存签名RSA key 文件的路径
        FilePathlen = strlen(rsaKeyFile);
        if (FilePathlen > 255)
        {
            FilePathlen = 255;
        }
        memcpy(stCAImageTail.RSAPrivateKeyPath, rsaKeyFile, FilePathlen);

        //填充签名尾部
        memcpy(Pagebuffer, &stCAImageTail, sizeof(stCAImageTail));
        stCAImageTail.CRC32 = DVB_CRC32(Pagebuffer, (sizeof(stCAImageTail) - 4));
        memcpy(Pagebuffer, &stCAImageTail, sizeof(stCAImageTail));

        //打开最终输出文件
        fpOutFile = fopen(sMergetFile, "a+");
        if(NULL == fpOutFile)
        {
            nRet = FALSE;
            goto FAIL;
        }
        fseek(fpOutFile, 0, SEEK_END);

        fpSigntureDatefile= fopen(sSignatureDataFile, "wb");
        if (NULL == fpSigntureDatefile)
        {
            nRet = FALSE;
            fclose(fpOutFile);
            goto FAIL;
        }

        //8K对齐
        if (InputFileLength % PAGE_SIZE != 0)
        {
            unsigned char Tempbuffer[] = {0xff, 0xff, 0xff, 0xff};
            for (index = 0; index < (PAGE_SIZE - InputFileLength % PAGE_SIZE); index++)
            {
                fwrite(Tempbuffer, 1, 1, fpOutFile);
            }
        }
        fwrite(Pagebuffer, PAGE_SIZE, 1, fpOutFile);
        fclose(fpOutFile);
        fwrite(Pagebuffer, PAGE_SIZE, 1, fpSigntureDatefile);
        fclose(fpSigntureDatefile);
    }
    else
    {
        //获取分块数目和最后分块大小
        if (sectionSize > InputFileLength /2)
        {
            printf("Section size > File length/2!\n");
            nRet = FALSE;
            goto FAIL;
        }

        SectionCount = InputFileLength / sectionSize;
        LastSectionSize = InputFileLength % sectionSize;
        //签名数据处理
        if (!(fpInputFile = open(strSrcFile, O_RDONLY)))
        {
            printf("Open file %s failed!", strSrcFile);
            nRet = FALSE;
            goto FAIL;
        }
        if (LastSectionSize)
        {
            SectionCount += 1;
        }

        //分配内存
        unsigned char *signbuffer = (unsigned char *)malloc(sectionSize);
        if(NULL == signbuffer)
        {
            printf("Malloc Filebuffer failed!!!");
            nRet = FALSE;
            goto FAIL;
        }

        //块数处理
        for (index = 1; index <= SectionCount; index++)
        {
            if (index == SectionCount && (LastSectionSize != 0))    //the last section
            {
                SignedDataLength = LastSectionSize;
            }
            else
            {
                SignedDataLength = sectionSize;
            }

            memset(Pagebuffer, 0, PAGE_SIZE);
            memset(signbuffer, 0, sectionSize);

            memset(&stCAImageTail, 0, sizeof(stCAImageTail));
            memcpy(stCAImageTail.u8MagicNumber, CAIMGHEAD_MAGICNUMBER, sizeof(stCAImageTail.u8MagicNumber));
            memcpy(stCAImageTail.u8Version, CAIMGHEAD_VERSION, sizeof(stCAImageTail.u8Version));

            //stCAImageTail.u32CreateDay = time.GetHour() * 0x10000+ time.GetMinute()* 0x100+ time.GetDay();
            //stCAImageTail.u32CreateTime = time.GetHour() * 0x10000+ time.GetMinute()* 0x100+ time.GetSecond();
            stCAImageTail.u32HeadLength = sizeof(stCAImageTail);
            stCAImageTail.u32IsYaffsImage = 0;
            stCAImageTail.u32SignedDataLength = SignedDataLength;
            stCAImageTail.u32CurrentsectionID = index - 1;
            stCAImageTail.u32TotalsectionID = SectionCount;
            stCAImageTail.u32SectionSize = sectionSize;

            read(fpInputFile, signbuffer, SignedDataLength);

            ////Hash2模式签名
            sha2(signbuffer, stCAImageTail.u32SignedDataLength, hash, 0);
            memset(rsaBuf, 0, 256);
            if ((nRet = rsa_pkcs1_sign(&rsa, RSA_PRIVATE, SIG_RSA_SHA256, 32, hash, rsaBuf)) != 0)
            {
                free(signbuffer);
                close(fpInputFile);
                printf("Failed to make the sign!");
                nRet = FALSE;
                goto FAIL;
            }
            stCAImageTail.u32IsConfigNandBlock = 1;
            stCAImageTail.u32NandBlockType = 0;
            stCAImageTail.u32IsNeedEncrypt = 0;
            stCAImageTail.u32IsEncrypted  = 0;

            //Hash2模式签名
            stCAImageTail.u32HashType = Hash2;
            memcpy(stCAImageTail.u8Sha, hash, 32);
            stCAImageTail.u32SignatureLen = 256;
            memcpy((unsigned char *)stCAImageTail.u8Signature, rsaBuf, stCAImageTail.u32SignatureLen);

            FilePathlen = strlen(strDestFile);
            if (FilePathlen > 255)  FilePathlen = 255;
            memcpy(stCAImageTail.OrignalImagePath, strDestFile, FilePathlen);

            FilePathlen = strlen(rsaKeyFile);
            if (FilePathlen > 255)  FilePathlen = 255;
            memcpy(stCAImageTail.RSAPrivateKeyPath, rsaKeyFile, FilePathlen);
            //算法效验
            memcpy(Pagebuffer, &stCAImageTail, sizeof(stCAImageTail));
            stCAImageTail.CRC32 = DVB_CRC32(Pagebuffer, (sizeof(stCAImageTail) - 4));
            memcpy(Pagebuffer, &stCAImageTail, sizeof(stCAImageTail));

            // 第一次签名时打开输出文件
            if (1 == index)
            {
                fpOutFile = fopen(sMergetFile, "a+");
                if (NULL == fpOutFile)
                {
                    printf("Open %s file failed!", sMergetFile);
                    free(signbuffer);
                    close(fpInputFile);
                    nRet = FALSE;
                    goto FAIL;
                }
                fseek(fpOutFile, 0, SEEK_END);

                //8K对齐
                if (InputFileLength % PAGE_SIZE != 0)
                {
                    int loop;
                    unsigned char Tempbuffer[] = {0xff, 0xff, 0xff, 0xff};
                    for(loop = 0; loop < (PAGE_SIZE - InputFileLength % PAGE_SIZE); loop++)
                    {
                        fwrite(Tempbuffer, 1, 1, fpOutFile);
                    }
                }

                fpSigntureDatefile= fopen(sSignatureDataFile, "wb");
                if (NULL == fpSigntureDatefile)
                {
                    nRet = FALSE;
                    free(signbuffer);
                    close(fpInputFile);
                    fclose(fpOutFile);
                    goto FAIL;
                }

            }

            fwrite(Pagebuffer, PAGE_SIZE, 1, fpOutFile);
            fwrite(Pagebuffer, PAGE_SIZE, 1, fpSigntureDatefile);
        }
        free(signbuffer);
        fclose(fpOutFile);
        fclose(fpSigntureDatefile);
        close(fpInputFile);
    }

    nRet = TRUE;

FAIL:
    free(filebuffer);
    free(Pagebuffer);
    rsa_free(&rsa);

    return nRet;
}



BOOL Sign_NonBOOTImage_Special(const char* strConfigFile,
    const char* inputdir,
    const char* outputdir,
    const char* keydir)
{
    int fpInputFile;
    int nRet, index, i, fileNubmer = 0, uLengthCusData = 0;
    FILE *fileRsaKey, *fpOutFile;
    unsigned char hash[32], rsaBuf[256];
    unsigned char headBuf[PAGE_SIZE];
    unsigned int tmpBuf[4];
    unsigned int offset, InputFileLength;
    unsigned long uAddrStart = 0; 
    unsigned long uLength = 0;
    unsigned long ulFinalImageLength = 0;
    unsigned long uLengthTmp = 0;
    rsa_context rsa;
    struct stat buf;
    HI_CAImgHead_S stCaImageHead;
    SIGN_CONFIG_PARAMETER_ST stConfigPara;

    //解析配置文件
    memset(&stConfigPara, '\0', sizeof(SIGN_CONFIG_PARAMETER_ST));

    nRet = PaserSignConfigParameter(strConfigFile, &stConfigPara, inputdir, outputdir, keydir);
    if (nRet != 0)
    {
        printf("parse %s failed!\n", strConfigFile);
        return FALSE;
    }

    printConfigFile(&stConfigPara);

    fileNubmer = atoi(stConfigPara.ImageNumber);

    memset(&stCaImageHead, 0x0, sizeof(HI_CAImgHead_S));
    memcpy(stCaImageHead.u8MagicNumber, CAIMGHEAD_MAGICNUMBER, sizeof(stCaImageHead.u8MagicNumber));
    memcpy(stCaImageHead.u8Version, CAIMGHEAD_VERSION, sizeof(stCaImageHead.u8Version));
    stCaImageHead.u32TotalLen = 0;
    stCaImageHead.u32CodeOffset = PAGE_SIZE;
    stCaImageHead.u32SignedImageLen = 0;
    stCaImageHead.u32SignatureOffset = 0;
    //stCaImageHead.u32ImageLen = 0;
    //stCaImageHead.u32ImageOffset = PAGE_SIZE; //the length of the iamge head is 8K, page size
    stCaImageHead.u32BlockNum = fileNubmer;
    stCaImageHead.u32SignatureLen = SIGNATURE_LEN;

    //printf("strlen(stConfigPara.CustomerData) = %d\n", strlen(stConfigPara.CustomerData));

    if ((strncmp(stConfigPara.CustomerData, "0x", 2) == 0) || (strncmp(stConfigPara.CustomerData, "0X", 2) == 0))
        offset = 2;
    else
        offset = 0;

    uLengthCusData = ((strlen(stConfigPara.CustomerData)) - 1 - offset) / 8 + 1;

    for (i = 0; i < uLengthCusData; i++)
    {
        memset(tmpBuf, 0, sizeof(tmpBuf));
        tmpBuf[0] = Char2Hex(&(stConfigPara.CustomerData[i * 8 + offset]));
        tmpBuf[1] = Char2Hex(&(stConfigPara.CustomerData[i * 8 + offset + 2]));
        tmpBuf[2] = Char2Hex(&(stConfigPara.CustomerData[i * 8 + offset + 4]));
        tmpBuf[3] = Char2Hex(&(stConfigPara.CustomerData[i * 8 + offset + 6]));
        stCaImageHead.Reserverd[i] = ((tmpBuf[0]) + (tmpBuf[1] << 8) + (tmpBuf[2] << 16) + (tmpBuf[3] << 24));
    }

    for (i = 0; i < fileNubmer; i++)
    {
        if ((i == (fileNubmer - 1) && i != 0) || fileNubmer == 1)
        {
            if (-1 == stat(g_ImageList[i].ImageName, &buf))
            {
                printf("Cannot get the information of the file %s\n", g_ImageList[i].ImageName);
                return FALSE;
            }
            uLengthTmp = ((buf.st_size + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;
            if (uLengthTmp > ToHex(g_ImageList[i].strlength))
            {
                printf("The size of %s is bigger than the size %lx you have set\n", g_ImageList[i].ImageName, ToHex(g_ImageList[i].strlength));
                return FALSE;
            }
            ulFinalImageLength += uLengthTmp;
        }
        else
        {
            ulFinalImageLength += ToHex(g_ImageList[i].strlength);
        }
    }
    //printf("ulFinalImageLength = 0x%x\n", ulFinalImageLength);
    if (fileNubmer == 1)
    {
        ulFinalImageLength += PAGE_SIZE;
    }

    char *pucTmpBuf = (unsigned char*)malloc(ulFinalImageLength);
    if(NULL == pucTmpBuf)
    {
        printf("Malloc memory failed!");
        return -1;
    }
    memset(pucTmpBuf, 0x0, ulFinalImageLength);

    //解析rsa key
    if ((fileRsaKey = fopen(stConfigPara.External_private_key_file, "r")) == NULL)
    {
        printf("Open RSA key file %s failed!", stConfigPara.External_private_key_file);
        return FALSE;
    }

    rsa_init(&rsa, RSA_PKCS_V15, 0, NULL, NULL);
    if((nRet = mpi_read_file(&rsa->n, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&(rsa->e) , 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->d , 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->p , 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->q, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->dmp1, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->dmq1, 16, fileRsaKey)) != 0 ||
        (nRet = mpi_read_file(&rsa->iqmp, 16, fileRsaKey)) != 0)
    {
        printf("Failed to read rsa file!");
        free(pucTmpBuf);
        fclose(fileRsaKey);
        return FALSE;
    }
    fclose(fileRsaKey);

    // buffer
    for (i = 0; i < fileNubmer; i++)
    {
        if ((i == (fileNubmer - 1)  && i != 0) || fileNubmer == 1)
        {
            if (-1 == stat(g_ImageList[i].ImageName, &buf))
            {
                printf("Cannot get the information of the file %s\n", g_ImageList[i].ImageName);
                return FALSE;
            }
            uLength = ((buf.st_size + PAGE_SIZE - 1) / PAGE_SIZE) * PAGE_SIZE;
        }
        else
        {
            uLength = ToHex(g_ImageList[i].strlength);
        }

        if (i == 0)
        {
            uAddrStart = PAGE_SIZE;
            if (fileNubmer == 1)
            {
                stCaImageHead.u32BlockOffset[i] = uAddrStart;
                stCaImageHead.u32BlockLength[i] = uLength;
            }
            else
            {
                stCaImageHead.u32BlockOffset[i] = uAddrStart;
                stCaImageHead.u32BlockLength[i] = uLength - PAGE_SIZE;
            }
        }
        else
        {
            stCaImageHead.u32BlockLength[i] = uLength;
            stCaImageHead.u32BlockOffset[i] = uAddrStart;
        }

        if (i == (fileNubmer - 1))
        {
            if (fileNubmer == 1)
            {
                stCaImageHead.u32TotalLen = uAddrStart + uLength + PAGE_SIZE;
                stCaImageHead.u32SignedImageLen = uAddrStart + uLength; //ImageHead也被签名
                stCaImageHead.u32SignatureOffset = stCaImageHead.u32SignedImageLen;     //签名偏移
            }
            else
            {
                stCaImageHead.u32TotalLen = uAddrStart + uLength;
                stCaImageHead.u32SignedImageLen = uAddrStart + uLength - PAGE_SIZE; //ImageHead也被签名
                stCaImageHead.u32SignatureOffset = stCaImageHead.u32SignedImageLen;     //签名偏移
            }
        }

        if (!(fpInputFile = open(g_ImageList[i].ImageName, O_RDONLY)))
        {
            printf("Open file %s failed!", g_ImageList[i].ImageName);
            return FALSE;
        }
        //获取输入文件长度
        stat(g_ImageList[i].ImageName, &buf);
        InputFileLength = buf.st_size;
        lseek(fpInputFile, 0, SEEK_SET);
        read(fpInputFile, pucTmpBuf + uAddrStart, InputFileLength);
        uAddrStart += stCaImageHead.u32BlockLength[i];

        close(fpInputFile);
    }

    memset(headBuf, 0xFF, PAGE_SIZE);
    memcpy(headBuf, &stCaImageHead, sizeof(stCaImageHead));
    stCaImageHead.u32CRC32 = DVB_CRC32(headBuf, sizeof(stCaImageHead) - 4);

    memset(pucTmpBuf, 0, PAGE_SIZE);
    memcpy(pucTmpBuf, &stCaImageHead, sizeof(stCaImageHead));

    sha2(pucTmpBuf, ulFinalImageLength, hash, 0);
    if((nRet = rsa_pkcs1_sign(&rsa, RSA_PRIVATE, SIG_RSA_SHA256, 32, hash, rsaBuf)) != 0)
    {
        rsa_free(&rsa);
        free(pucTmpBuf);
        printf("Error! %s:%d\n", __FILE__, __LINE__);
        return FALSE;
    }
    rsa_free(&rsa);

    //打开最终输出文件
    fpOutFile = fopen(stConfigPara.OutputFile, "wb");
    if (NULL == fpOutFile)
    {
            free(pucTmpBuf);
        printf("Error! %s:%d\n", __FILE__, __LINE__);
        return FALSE;
    }
    fseek(fpOutFile, 0, SEEK_SET);
    //向输出文件输出数据
    fwrite(pucTmpBuf, 1, ulFinalImageLength, fpOutFile);

    memset(headBuf, 0, PAGE_SIZE);
    memcpy(headBuf, rsaBuf, 256);
    fwrite(headBuf, 1, PAGE_SIZE, fpOutFile);
    fflush(fpOutFile);
    fclose(fpOutFile);

    free(pucTmpBuf);

    return TRUE;
}
