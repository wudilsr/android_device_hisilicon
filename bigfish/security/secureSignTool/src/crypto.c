#include <stdio.h>
#include<time.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

#include "adapter.h"
#include "crypto.h"

static CRYPTO_IMG_ATTRIBUTE_ST g_CryptoImageList[BUFFER_SIZE] = {0};

int PaserCryptoConfigParameter(const char *strConfigFile,
    CRYPTO_CONFIG_PARAMETER_ST *pConfigPara,
    const char* inputdir,
    const char* outputdir,
    const char* keydir)
{
    int ret;
    int i = 0;
    int length = 0;
    int imageNumber = -1;
    FILE *fp = NULL;
    char tmp[PATH_LENGTH];
    char buf[BUFFER_SIZE];

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
        fgets(tmp, PATH_LENGTH, fp);
        StrTrim(tmp);

        ret = ParseFile(tmp, "External_private_key_file", pConfigPara->External_private_key_file);
        ret |= ParseFile(tmp, "Algorithm", pConfigPara->Algorithm);
        ret |= ParseFile(tmp, "Mode", pConfigPara->Mode);
        ret |= ParseFile(tmp, "OperationType", pConfigPara->OperationType);
        ret |= ParseFile(tmp, "Key", pConfigPara->Key);
        ret |= ParseFile(tmp, "IV", pConfigPara->IV);
        ret |= ParseFile(tmp, "ImageNumber", pConfigPara->ImageNumber);
        ret |= ParseFile(tmp, "InputFileDir", pConfigPara->InputFileDir);
        ret |= ParseFile(tmp, "OutputFileDir", pConfigPara->OutputFileDir);
        if (0 != ret)
        {
            fclose(fp);
            return -1;
        }

        memcpy(buf, "Input", 5);
        sprintf(buf + 5, "%d", i + 1);
        ParseFile(tmp, buf, g_CryptoImageList[i].Input);

        memset(buf, 0, sizeof(buf));
        memcpy(buf, "Output", 6);
        sprintf(buf + 6, "%d", i + 1);
        ParseFile(tmp, buf, g_CryptoImageList[i].Output);
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

    memset(tmp, 0, sizeof(tmp));
    if (keydir != NULL && keydir[0] != 0)
    {
        sprintf(tmp,"%s",keydir);
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

    //printf("i =  %d\n", i);
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
        if (!('/' == tmp[strlen(tmp) -1]))
        {
            strcat(tmp, "/");
        }

        strcat(tmp, g_CryptoImageList[i].Input);
        strcpy(g_CryptoImageList[i].Input, tmp);
        g_CryptoImageList[i].Input[strlen(g_CryptoImageList[i].Input)] = '\0';
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

        strcat(tmp, g_CryptoImageList[i].Output);
        strcpy(g_CryptoImageList[i].Output, tmp);
        g_CryptoImageList[i].Output[strlen(g_CryptoImageList[i].Output)] = '\0';
    }

    return 0;
}

static void printCryptoConfigFile(void *pConfigFile)
{
    int i;
    CRYPTO_CONFIG_PARAMETER_ST *p = NULL;
    p = pConfigFile;

    printf("External_private_key_file=%s\n", p->External_private_key_file);
    printf("Algorithm=%s\n", p->Algorithm);
    printf("Mode=%s\n", p->Mode);
    printf("OperationType=%s\n", p->OperationType);
    printf("Key=%s\n", p->Key);
    printf("IV=%s\n", p->IV);
    printf("ImageNumber=%s\n", p->ImageNumber);

    for (i = 0; i < atoi(p->ImageNumber); i++)
    {
        printf("Input%d=%s\n", i + 1, g_CryptoImageList[i].Input);
        printf("Output%d=%s\n", i + 1, g_CryptoImageList[i].Output);
    }
}

static int GetAlgtheMode(char *strAlgMode, MODE_EN *p)
{
    int ret = 0;
    if (!strncmp(strAlgMode, "CBC", 3))
    {
        *p = CBC;
    }
    else if (!strncmp(strAlgMode, "ECB", 3))
    {
        *p = ECB;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

static int GetCryptoOperation(char *strCryptMode, CRYPT_EN *p)
{
    int ret = 0;
    if (!strncmp(strCryptMode, "Decrypt", 7))
    {
        *p = DECRYPT_OP;
    }
    else if (!strncmp(strCryptMode, "Encrypt", 7))
    {
        *p = ENCRYPT_OP;
    }
    else
    {
        ret = -1;
    }

    return ret;
}

static int GetAlgthem(char *strAlg, ALGORITHM_EN *p)
{
    int ret = 0;
    if (!strncmp(strAlg, "AES", 3))
    {
        *p = AES;
    }
    else if (!strncmp(strAlg, "TDES", 4))
    {
        *p = TDES;
    }
    else if (!strncmp(strAlg, "SHA1", 4))
    {
        *p = SHA1_ALG;
    }
    else if (!strncmp(strAlg, "SHA256", 6))
    {
        *p = SHA256_ALG;
    }
    else if (!strncmp(strAlg, "HiCRC16", 7))
    {
        *p = CRC16;
    }
    else if (!strncmp(strAlg, "RSA", 3))
    {
        *p = RSA_ALG;
    }
    else
    {
        ret = -1;
    }

    return ret;
}


unsigned short CalculateCRC16 (const unsigned char* data_array_ptr,
                    unsigned long data_array_length)
{
    unsigned short crc_value = 0xff;
    unsigned short polynomial = 0x8005;
    unsigned short data_index = 0;
    int l = 0;
    bool flag = false;
    unsigned char byte0 = 0;
    unsigned char au8CrcInput[17] = {0};

    if (data_array_ptr == NULL) {
        return crc_value;
    }
    if (data_array_length == 0) {
        return crc_value;
    }

    memset(au8CrcInput, 0, sizeof(au8CrcInput));
    au8CrcInput[0] = 0x55;
    memcpy(au8CrcInput + 1, data_array_ptr, data_array_length);
    data_array_length += 1;

    for (data_index = 0; data_index < data_array_length; data_index++){
        byte0 = au8CrcInput [data_index];
        crc_value ^= byte0 * 256;
        for (l=0;l<8;l++) {
            flag = ((crc_value & 0x8000)==32768);
            crc_value = (crc_value & 0x7FFF)*2;
            if (flag == true) {
                crc_value ^= polynomial;
            }
        }
    }
    return crc_value;
}

unsigned short cal_crc_perbyte(unsigned char byte, unsigned short crc)
{
    unsigned char  da = 0;
    const unsigned short crc_ta[16]={ 0x0000, 0x1021, 0x2042, 0x3063, 0x4084, 0x50a5, 0x60c6, 0x70e7,
                              0x8108, 0x9129, 0xa14a, 0xb16b, 0xc18c, 0xd1ad, 0xe1ce, 0xf1ef};

    da = ((unsigned char) (crc/256)) / 16;
    crc <<= 4;
    crc ^= (unsigned short)crc_ta[da^(byte/16)];
    da = ((unsigned char) (crc/256)) / 16;
    crc <<= 4;
    crc ^= (unsigned short)crc_ta[da^(byte&0x0f)];

    return(crc);
}


int Sign_NonBOOTImage_Crypto(const char* strConfigFile,
    const char* inputdir,
    const char* outputdir,
    const char* keydir)
{
    int ret, offset, i, index, fileNubmer = 0;
    FILE *fileRsaKey, *fpOutFile, *fpInFile;
    unsigned char *pBuf = NULL;
    unsigned char *pOutputBuf = NULL;
    unsigned char hash[32], rsaBuf[256];
    unsigned char ucKey[16]; //for AES, it is 16; for TDES, 8
    unsigned char ucIV[16];
    unsigned char ucTmpIV[16];
    unsigned short uCrc16 = 0;
    unsigned int uwKeylength;
    unsigned int ucBlockLength;
    unsigned long uwFileLength;
    unsigned long uwDataLength;
    rsa_context rsa;
    aes_context ctx;
    des3_context des3ctx;
    struct stat buf;
    CRYPTO_CONFIG_PARAMETER_ST stConfigPara;
    ALGORITHM_EN stALGTHM;
    MODE_EN stMode;
    CRYPT_EN stOPeration;

    //½âÎöÅäÖÃÎÄ¼þ
    memset(&stConfigPara, '\0', sizeof(CRYPTO_CONFIG_PARAMETER_ST));
    ret = PaserCryptoConfigParameter(strConfigFile,&stConfigPara,inputdir,outputdir,keydir);
    if (ret != 0)
    {
        printf("parse %s failed!\n", strConfigFile);
        return -1;
    }

    //printCryptoConfigFile(&stConfigPara);

    ret = GetAlgthem(stConfigPara.Algorithm, &stALGTHM);
    if (ret !=  0)
    {
        printf("The parameter Algorithm is not correct. Please check it.\n");
        return -1;
    }

    fileNubmer = atoi(stConfigPara.ImageNumber);

    if (stALGTHM == CRC16)
    {
        for (i = 0; i < fileNubmer; i++)
        {
            stat(g_CryptoImageList[i].Input, &buf);
            uwFileLength = buf.st_size;

            if (uwFileLength != 16)
            {
                printf("File length invalid! Length must be 16!");
                return -1;
            }

            fpInFile = fopen(g_CryptoImageList[i].Input, "r");
            if (NULL == fpInFile)
            {
                printf("Open file %s failed!\n", g_CryptoImageList[i].Input);
                return -1;
            }

            pBuf = (char *)malloc(uwFileLength);
            if (pBuf == NULL)
            {
                printf("Faile to malloc memory!!\n");
                fclose(fpInFile);
                return -1;
            }
            fread(pBuf, 1, uwFileLength, fpInFile);
            fclose(fpInFile);

            uCrc16 = CalculateCRC16(pBuf, uwFileLength);
            printf("CRC16: 0x%04x\n", uCrc16);
            free(pBuf);
            pBuf = NULL;

            fpOutFile = fopen(g_CryptoImageList[i].Output, "wb");
            if (NULL == fpOutFile)
            {
                printf("Create file %s failed!\n", g_CryptoImageList[i].Output);
                return -1;
            }
            memset(ucTmpIV, 0, sizeof(ucTmpIV));
            sprintf((char*)ucTmpIV, "0x%04x", uCrc16);
            fwrite(ucTmpIV, 1, 6, fpOutFile);
            fclose(fpOutFile);
        }
    }
    else if (stALGTHM == SHA1_ALG)
    {
        for (i = 0; i < fileNubmer; i++)
        {
            fpInFile = fopen(g_CryptoImageList[i].Input, "r");
            if (NULL == fpInFile)
            {
                printf("Open file %s failed!\n", g_CryptoImageList[i].Input);
                return -1;
            }

            stat(g_CryptoImageList[i].Input, &buf);
            uwFileLength = buf.st_size;
            pBuf = (char *)malloc(uwFileLength);
            if (pBuf == NULL)
            {
                printf("Faile to malloc memory!!\n");
                fclose(fpInFile);
                return -1;
            }
            fread(pBuf, 1, uwFileLength, fpInFile);
            fclose(fpInFile);

            sha1(pBuf, uwFileLength, hash);

            fpOutFile = fopen(g_CryptoImageList[i].Output, "wb");
            if (NULL == fpOutFile)
            {
                printf("Create file %s failed!\n", g_CryptoImageList[i].Output);
                free(pBuf);
                pBuf = NULL;
                return -1;
            }

            for (i = 0; i < 20; i++)
            {
                sprintf((char*)ucTmpIV, "0x%02x,", hash[i]);
                fwrite(ucTmpIV, 1, 5, fpOutFile);
            }
            fclose(fpOutFile);
            free(pBuf);
            pBuf = NULL;
        }
    }
    else if (stALGTHM == SHA256_ALG)
    {
        for (i = 0; i < fileNubmer; i++)
        {
            fpInFile = fopen(g_CryptoImageList[i].Input, "r");
            if (NULL == fpInFile)
            {
                printf("Open file %s failed!\n", g_CryptoImageList[i].Input);
                return -1;
            }

            stat(g_CryptoImageList[i].Input, &buf);
            uwFileLength = buf.st_size;
            pBuf = (char *)malloc(uwFileLength);
            if (pBuf == NULL)
            {
                printf("Faile to malloc memory!!\n");
                fclose(fpInFile);
                return -1;
            }
            fread(pBuf, 1, uwFileLength, fpInFile);
            fclose(fpInFile);

            sha2(pBuf, uwFileLength, hash, 0);

            fpOutFile = fopen(g_CryptoImageList[i].Output, "wb");
            if (NULL == fpOutFile)
            {
                printf("Create file %s failed!\n", g_CryptoImageList[i].Output);
                free(pBuf);
                pBuf = NULL;
                return -1;
            }

            for (i = 0; i < 32; i++)
            {
                sprintf((char*)ucTmpIV, "0x%02x%s", hash[i], ((i + 1) % 16) ? "," : "\n");
                fwrite(ucTmpIV, 1, 5, fpOutFile);
            }
            //fwrite(hash, 1, 32, fpOutFile);
            fclose(fpOutFile);
            free(pBuf);
            pBuf = NULL;
        }
    }
    else if (stALGTHM == RSA_ALG)
    {
        if ((fileRsaKey = fopen(stConfigPara.External_private_key_file, "r")) == NULL)
        {
            printf("Open RSA key file %s failed, please check the parameter External_private_key_file!\n", stConfigPara.External_private_key_file);
            return -1;
        }

        rsa_init(&rsa, RSA_PKCS_V15, 0, NULL, NULL);
        if((ret = mpi_read_file(&rsa->n, 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&(rsa->e) , 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&rsa->d , 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&rsa->p , 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&rsa->q, 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&rsa->dmp1, 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&rsa->dmq1, 16, fileRsaKey)) != 0 ||
            (ret = mpi_read_file(&rsa->iqmp, 16, fileRsaKey)) != 0)
        {
            printf("Failed to read rsa file!");
            fclose(fileRsaKey);
            return -1;
        }
        fclose(fileRsaKey);

        for (i = 0; i < fileNubmer; i++)
        {
            fpInFile = fopen(g_CryptoImageList[i].Input, "r");
            if (NULL == fpInFile)
            {
                printf("Open file %s failed!\n", g_CryptoImageList[i].Input);
                fclose(fileRsaKey);
                return -1;
            }

            stat(g_CryptoImageList[i].Input, &buf);
            uwFileLength = buf.st_size;
            pBuf = (char *)malloc(uwFileLength);
            if (pBuf == NULL)
            {
                printf("Faile to malloc memory!!\n");
                fclose(fileRsaKey);
                fclose(fpInFile);
                return -1;
            }
            fread(pBuf, 1, uwFileLength, fpInFile);
            fclose(fpInFile);
            fpInFile = NULL;

            sha2(pBuf, uwFileLength, hash, 0);
            free(pBuf);
            pBuf = NULL;

            if((ret = rsa_pkcs1_sign(&rsa, RSA_PRIVATE, SIG_RSA_SHA256, 32, hash, rsaBuf)) != 0)
            {
                printf("Failed to sign the file %s!\n", g_CryptoImageList[i].Input);
                rsa_free(&rsa);
                fclose(fileRsaKey);
                fclose(fpInFile);
                return -1;
            }

            fpOutFile = fopen(g_CryptoImageList[i].Output, "wb");
            if (NULL == fpOutFile)
            {
                printf("Open file %s failed!\n", g_CryptoImageList[i].Output);
                fclose(fileRsaKey);
                fclose(fpInFile);
                rsa_free(&rsa);
                return -1;
            }
            fwrite(rsaBuf, 1, 256, fpOutFile);
            fclose(fpOutFile);
            fpOutFile = NULL;
        }
        rsa_free(&rsa);
    }
    else if (stALGTHM == AES || stALGTHM == TDES)
    {
        uwKeylength = 16;
        if (stALGTHM == AES)
        {
            ucBlockLength = 16;
        }
        else if (stALGTHM == TDES)
        {
            ucBlockLength = 8;
        }

        ret = GetAlgtheMode(stConfigPara.Mode, &stMode);
        if (ret !=  0)
        {
            printf("The parameter Mode is not correct. Please check it.\n");
            return -1;
        }

        ret = GetCryptoOperation(stConfigPara.OperationType, &stOPeration);
        if (ret !=  0)
        {
            printf("The parameter OperationType is not correct. Please check it.\n");
            return -1;
        }

        // key
        if ((strncmp(stConfigPara.Key, "0x", 2) == 0) || (strncmp(stConfigPara.Key, "0X", 2) == 0))
            offset = 2;
        else
            offset = 0;

        if (strlen(stConfigPara.Key + offset) != 32 )
        {
            printf("The length of Key must be 32, please check it!\n");
            return -1;
        }

        for (i = 0; i < uwKeylength; i++)
        {
            ucKey[i] = Char2Hex(&(stConfigPara.Key[i * 2 + offset]));
        }

        // IV
        if ((strncmp(stConfigPara.IV, "0x", 2) == 0) || (strncmp(stConfigPara.IV, "0X", 2) == 0))
            offset = 2;
        else
            offset = 0;

        if (strlen(stConfigPara.IV + offset) != 32)
        {
            printf("The length of Key must be 32, please check it!\n");
            return -1;
        }

        for (i = 0; i < uwKeylength; i++)
        {
            ucIV[i] = Char2Hex(&(stConfigPara.IV[i * 2 + offset]));
        }

        // Encrypt or Decrypt
        for (i = 0; i < fileNubmer; i++)
        {
            fpInFile = fopen(g_CryptoImageList[i].Input, "r");
            if (NULL == fpInFile)
            {
                printf("Open file %s failed!\n", g_CryptoImageList[i].Input);
                fclose(fileRsaKey);
                return -1;
            }

            stat(g_CryptoImageList[i].Input, &buf);
            uwFileLength = buf.st_size;
            pBuf = (unsigned char *)malloc(uwFileLength);
            if (pBuf == NULL)
            {
                printf("Failed to malloc memory!!\n");
                fclose(fpInFile);
                return -1;
            }
            fread(pBuf, 1, uwFileLength, fpInFile);
            fclose(fpInFile);
            fpInFile = NULL;

            fpOutFile = fopen(g_CryptoImageList[i].Output, "wb");
            if (NULL == fpOutFile)
            {
                printf("Create file %s failed!\n", g_CryptoImageList[i].Output);
                return FALSE;
            }

            uwDataLength = (uwFileLength / ucBlockLength) * ucBlockLength;
            pOutputBuf = (unsigned char *)malloc(uwFileLength);
            if (pOutputBuf == NULL)
            {
                printf("Failed to malloc memory!!\n");
                return -1;
            }
            memcpy(pOutputBuf, pBuf, uwFileLength);

            memset(ucTmpIV, 0, 16);
            memcpy(ucTmpIV, ucIV, 16);

            switch(stALGTHM)
            {
                case AES:
                if (stOPeration == ENCRYPT_OP)
                {
                    aes_setkey_enc(&ctx, ucKey, 128);

                    if (stMode == CBC)
                    {
                        aes_crypt_cbc(&ctx, AES_ENCRYPT, uwDataLength, ucTmpIV, pBuf, pOutputBuf);
                    }
                    else if (stMode == ECB)
                    {
                        for (i = 0; i < uwDataLength / 16; i++)
                        {
                            aes_crypt_ecb(&ctx, AES_ENCRYPT, pBuf + 16 * i, pOutputBuf + 16 * i);
                            //printf("LOG: %d \n", i);
                        }
                    }
                }
                else if (stOPeration == DECRYPT_OP)
                {
                    aes_setkey_dec(&ctx, ucKey, 128);

        if (stMode == CBC)
        {
        aes_crypt_cbc(&ctx, AES_DECRYPT, uwDataLength, ucTmpIV, pBuf, pOutputBuf);
        }
        else if (stMode == ECB)
        {
        for (i = 0; i < uwDataLength / 16; i++)
        {
        aes_crypt_ecb(&ctx, AES_DECRYPT, pBuf + 16 * i, pOutputBuf + 16 *  i);
        }
        }
                }
                break;

                case TDES:
                if (stOPeration == ENCRYPT_OP)
        {
        des3_set2key_enc(&des3ctx, ucKey);

        if(stMode == CBC)
        {
        des3_crypt_cbc(&des3ctx, DES_ENCRYPT, uwDataLength, ucTmpIV, pBuf, pOutputBuf);
        }
        else if(stMode == ECB)
        {
        for(i = 0; i < uwDataLength / 8; i++)
        {
        des3_crypt_ecb(&des3ctx, pBuf + 8 * i, pOutputBuf + 8 * i);
        }
        }
        }
            else if (stOPeration == DECRYPT_OP)
        {
        des3_set2key_dec(&des3ctx, ucKey);

        if(stMode == CBC)
        {
        des3_crypt_cbc(&des3ctx, DES_DECRYPT, uwDataLength, ucTmpIV, pBuf, pOutputBuf);
        }
        else if(stMode == ECB)
        {
        for(i = 0; i < uwDataLength / 8; i++)
        {
        des3_crypt_ecb(&des3ctx, pBuf+ 8 * i, pOutputBuf + 8 * i);
        }
        }
        }
                break;

                default:
                    break;
            }

            fwrite(pOutputBuf, 1, uwFileLength, fpOutFile);
            free(pOutputBuf);
            free(pBuf);

            fclose(fpOutFile);
            fpOutFile = NULL;
        }
    }

    return ret;
}
