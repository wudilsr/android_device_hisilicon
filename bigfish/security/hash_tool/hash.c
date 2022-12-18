#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
//#include "version.h"
#include "hash.h"
#include "openssl/sha.h"

#define MAX_PATH_LEN 512
#define FILENAME_LENGTH 32

char outputFile[MAX_PATH_LEN+FILENAME_LENGTH] = {0};
int inputDirLen = 0;
FILE* fp = NULL;
int count = 0;

int CalHash(char* path, HASH_ALGORITHM stALGTHM, unsigned char* hash)
{
    int fileLength = 0;
    char *pBuf = NULL;
    FILE* fpInFile = NULL;
    struct stat buf;
    int hashLength = 0;

    if (stALGTHM == SHA1_ALG)
    {
        if ((fpInFile = fopen(path, "rb")) == NULL)
        {
            printf("Open file %s failed!\n", path);
            return -2;
        }

        stat(path, &buf);
        fileLength = buf.st_size;
        pBuf = (char *)malloc(fileLength);
        if (pBuf == NULL)
        {
            printf("Faile to malloc memory!!\n");
            fclose(fpInFile);
            return -1;
        }
        fread(pBuf, 1, fileLength, fpInFile);
        fclose(fpInFile);

        SHA1(pBuf, fileLength, hash);

        hashLength = 20;
        WriteHashToFile(path, hash, hashLength);

        free(pBuf);
        return 0;
    }
    else if (stALGTHM == SHA256_ALG)
    {
        if ((fpInFile = fopen(path, "rb")) == NULL)
        {
            printf("Open file %s failed!\n", path);
            return -2;
        }

        stat(path, &buf);
        fileLength = buf.st_size;
        pBuf = (char *)malloc(fileLength);
        if (pBuf == NULL)
        {
            printf("Faile to malloc memory!!\n");
            fclose(fpInFile);
            return -1;
        }
        fread(pBuf, 1, fileLength, fpInFile);
        fclose(fpInFile);

        SHA256(pBuf, fileLength, hash);

        hashLength = 32;
        WriteHashToFile(path, hash, hashLength);

        free(pBuf);
        return 0;
    }
    return 0;
}

void WriteHashToFile(char* path, unsigned char* hash, int hashLength)
{
    int i = 0;
    char systemPath[MAX_PATH_LEN] = {0};
    char hashGap = ' ';

    strcat(systemPath, "/system/");
    while(path[i] != '\0')
    {
        systemPath[i+8] = path[i+inputDirLen+1];
        i++;
    }

    fprintf(fp, "%s\t", systemPath);

    //fwrite(hash, hashLength, 1, fp);
    for (i = 0; i < hashLength; i++)
    {
        if (((i + 1) % hashLength) == 0)
        {
            hashGap = '\n';
        }
        else
        {
            hashGap = ' ';
        }
        fprintf(fp, "%02x%c", hash[i], hashGap);
    }

    //fprintf(fp, "\n");
}

int CalAllFilesHash(char *dirname, HASH_ALGORITHM hashAlgorithm)
{
    char path[MAX_PATH_LEN] = {0};
    unsigned char hash[32] = {0};
    struct dirent *filename = NULL;//readdir return type
    DIR *dir = NULL;
    struct stat s;
    int ret = 0;
    if(dirname == NULL)
    {
         printf("dirname %s is NULL!\n",dirname);
         return -1;
    }

    dir = opendir(dirname);
    if(dir == NULL)
    {
         printf("open dir %s error!\n",dirname);
         return -1;
    }

    while((filename = readdir(dir)) != NULL)
    {
        if(!strcmp(filename->d_name,".")||!strcmp(filename->d_name,".."))
            continue;
        if(!strcmp(filename->d_name,"system_list"))
            continue;
        sprintf(path,"%s/%s", dirname, filename->d_name);

        lstat(path, &s);
        if(S_ISDIR(s.st_mode))
        {
             if (CalAllFilesHash(path, hashAlgorithm) == -1)
             {
                 closedir(dir);
                 return -1;
             }
        }
        else
        {
            printf("%s\n", path);
            count++;
            ret = CalHash(path, hashAlgorithm, hash);
            if (ret == -1)
            {
                printf("CalHash failed!\n");
                closedir(dir);
                return -1;
            }
            else if (ret == -2)
            {
                printf("This is a link file!\n");
            }
        }
    }
    closedir(dir);
    return 0;
}

int main(int argc, char **argv)
{
    char inputDir[MAX_PATH_LEN] = {0};
    char outputDir[MAX_PATH_LEN] = {0};
    HASH_ALGORITHM hashAlgorithm = SHA1_ALG;
    if(argc != 4)
    {
        printf("The argc is wrong!\n");
        printf("Usage: ./hash hashAlgorithm(1:SHA1; 2:SHA256) /home/myFolder/system /home/outputDir/\n");
        return -1;
    }

    if (!strcmp(argv[1], "1"))
    {
        hashAlgorithm = SHA1_ALG;
    }
    else if (!strcmp(argv[1], "2"))
    {
        hashAlgorithm = SHA256_ALG;
    }
    else
    {
        printf("Hash algorithm is wrong!\n");
        printf("Usage: ./hash hashAlgorithm(1:SHA1; 2:SHA256) /home/myFolder/system /home/outputDir/\n");
        return -1;
    }

    strncpy(inputDir, argv[2], MAX_PATH_LEN-1);
    strncpy(outputDir, argv[3], MAX_PATH_LEN-1);

    if (inputDir[strlen(inputDir)-1] == '/')
    {
        //printf("Remove inputDir '/'\n");
        inputDir[strlen(inputDir)-1] = '\0';
    }

    if (outputDir[strlen(outputDir)-1] == '/')
    {
        //printf("Remove outputDir '/'\n");
        outputDir[strlen(outputDir)-1] = '\0';
    }
    inputDirLen = strlen(inputDir);
    sprintf(outputFile, "%s/%s",outputDir, "system_list.txt");

    if ((fp = fopen(outputFile, "w+")) == NULL)
    {
        printf("Open file %s failed!\n", outputFile);
        return -1;
    }

    if (CalAllFilesHash(inputDir, hashAlgorithm) == -1)
    {
        printf("CalAllFilesHash failed!\n");
        fclose(fp);
        fp = NULL;
        return -1;
    }
    fwrite(&count, sizeof(int), 1, fp);
    printf("Total files:%d\n", count);
    fclose(fp);
    fp = NULL;
    return 0;
}
