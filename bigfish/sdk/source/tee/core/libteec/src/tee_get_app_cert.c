#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stddef.h>
#include <fcntl.h>

//#include <libxml/tree.h>
//#include <libxml/parser.h>
//#include <libxml/xpath.h>
//#include <libxml/xpathInternals.h>

//#include "../test_utils.h"
//#include <openssl/x509.h>
//#include <openssl/x509v3.h>
//#include <openssl/bio.h>


#include "tee_client_storage_api.h"
#include "tee_client_type.h"

#define LOG_TAG "tee_get_app_cert"

#ifdef _ANDROID_PLATFORM_HISI /* for hisi */
//#include "cutils/log.h"
#define LOG_NDEBUG 0
#include <cutils/log.h>
#include <cutils/properties.h>

#ifdef K3V3_FPGA
#define LOGE ALOGE
#define LOGV
#else /* for hisi compile */
#define LOGE
#define LOGV
#endif

#else
#define LOGE(fmt, args...) printf("[error]%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#define LOGV(fmt, args...) printf("[debug]%s %s: " fmt "", LOG_TAG, __FUNCTION__, ## args)
#endif

#define SHELL_UID (2000)


//static const xmlChar ** appCerts = NULL;
static int appCertsSize = 0;
#define MAX_PATH_LENGTH      256
#if 0
static unsigned int convert_str2dex(char byte)
{
    if(byte >= '0' && byte <= '9')
        return (unsigned int)(byte-'0');
    if(byte >= 'A' && byte <= 'F')
        return (unsigned int)(byte-'A'+10);
    if(byte >= 'a' && byte <= 'f')
        return (unsigned int)(byte-'a'+10);
    return 0;
}

void dump_data(char *info, unsigned char * data, unsigned int len)
{
    char  buf[100] = {0};
    int i, j, k;
    char *pbuf = buf;
    char *pdata = (char *)data;

    if (len > 1024)
    {
        len = 1024;
    };

    k = len / 32;

    for (j = 0; j < k; j++)
    {
        for (i = 0; i < 32; i++)
        {
            snprintf(pbuf, sizeof(buf),"%02X", *pdata++);
            pbuf += 2;
        }

        buf[64] = 0;
        LOGV("%s : %s", info, buf);
        pbuf = buf;
    }

    k = len % 32;

    if (k == 0)
    {
        return;
    }

    for (i = 0; i < k; i++)
    {
        snprintf(pbuf, sizeof(buf), "%02X", *pdata++);
        pbuf += 2;
    }

    *pbuf = 0;
    LOGV("%s : %s", info, buf);
}

char hexToByte(char c)
{
    if ((c >= '0') && (c <= '9'))
        return c - '0';
    else if ((c >= 'A') && (c <= 'F'))
        return c - 'A' + 10;
    else if ((c >= 'a') && (c <= 'f'))
        return c - 'a' + 10;
    else
        return 0;
}


int strToByte(char *result, char* str)
{
    int i;
    char n1, n2;
    int len = strlen(str);

    for (i = 0; i < len / 2; i++)
    {
        n1 = hexToByte(str[2*i]);
        n2 = hexToByte(str[2*i+1]);
        result[i] = n1 << 4 | n2;
    }
    return len /2;
}

int getInstalledAppCerts(xmlDocPtr doc)
{
    xmlXPathContextPtr xpathCtx;
    xmlXPathObjectPtr xpathObj;
    xmlNodeSetPtr nodes;
    xmlNodePtr cur;
    const xmlChar *tmp;

    int size = 0;
    int i, index;

    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        LOGE("Error: unable to create new XPath context\n");
        xmlXPathFreeContext(xpathCtx);
        return(-1);
    }

    xpathObj = xmlXPathEvalExpression((const xmlChar *)"//package/sigs/cert[@key]", xpathCtx);
    if(xpathObj == NULL) {
        LOGE("Error: unable to evaluate xpath expression \n");
        xmlXPathFreeContext(xpathCtx);
        return(-1);
    }

    nodes = xpathObj->nodesetval;
    size = (nodes) ? nodes->nodeNr : 0;
    if (size <= 0)
    {
        LOGE("size = %d", size);
        xmlXPathFreeContext(xpathCtx);
        return -1;
    }

    if (appCerts != NULL && appCertsSize > 0)
    {
        for (i = 0; i < appCertsSize; i++)
            xmlFree((xmlChar *)appCerts[i]);
        free(appCerts);
    }

    appCertsSize = size;
    appCerts = malloc(sizeof(char *) * size);
    if (appCerts== NULL)
    {
        xmlXPathFreeContext(xpathCtx);
        return -1;
    }

    for (i = 0; i < size; i++)
    {
        cur = nodes->nodeTab[i];
        tmp = xmlGetProp(cur, (const xmlChar*)"index");
        index = atoi((char const *)tmp);
        xmlFree((void *)tmp);

        tmp = xmlGetProp(cur, (const xmlChar*)"key");
        if (index < appCertsSize)
        {
            appCerts[index] = tmp;
        }
    }

    xmlXPathFreeContext(xpathCtx);
    return 0;
}

int getCertsForPackage(xmlDocPtr doc,const char * pkgName, unsigned int uid, const xmlChar ** certs)
{
    xmlXPathContextPtr xpathCtx, xpathCtxUid;
    xmlXPathObjectPtr xpathObj, xpathObjUid;
    xmlNodeSetPtr nodes, nodesUid;
    xmlNodePtr cur, curUid;
    const xmlChar *tmp;
    const xmlChar *tmpForUid;
    char eval[1024] = {0};

    int size = 0;
    int sizeOfCertForUid = 0;
    int index, i, indexForUid;

    /* com.android.shell has the same cert with framework
    *  So when malicious c program fake is cmdline to com.huawei.hidisk pacage name
    *  it also can get the system cert. Then the malicious can use storage_task in trustedcore.
    *  To stop the attack, when UID is SHELL, just return -1, then pass the uid to the TrustedCore.
    */
    if (uid == SHELL_UID) {
        LOGE("Error: uid is shell UID, just return -1\n");
        return -1;
    }

    /*1. use package name to find cert index*/
    xpathCtx = xmlXPathNewContext(doc);
    if(xpathCtx == NULL) {
        LOGE("Error: unable to create new XPath context\n");
        xmlFreeDoc(doc);
        return(-1);
    }

    snprintf(eval, sizeof(eval) - 1, "//package[@name='%s']/sigs/cert", pkgName);
	eval[sizeof(eval) - 1] = '\0';
    xpathObj = xmlXPathEvalExpression((xmlChar const *)eval, xpathCtx);
    if(xpathObj == NULL) {
        /*cannot find package name*/
        LOGE("Error: unable to evaluate xpath expression \n");
        xmlXPathFreeContext(xpathCtx);
        return(-1);
    }

    nodes = xpathObj->nodesetval;
    size = (nodes) ? nodes->nodeNr : 0;
    if (size <= 0)
    {
        LOGE("cannot find package:%s\n", pkgName);
        xmlXPathFreeContext(xpathCtx);
        xmlXPathFreeObject(xpathObj);
        return -1;
    }
    /*2. use userId to find cert index*/
    xpathCtxUid = xmlXPathNewContext(doc);
    if(xpathCtxUid == NULL) {
        LOGE("Error: unable to create new xpathCtxUid context\n");
        xmlFreeDoc(doc);
        xmlXPathFreeContext(xpathCtx);
        xmlXPathFreeObject(xpathObj);
        return(-1);
    }

    if (uid > 100000)
        uid = uid % 100000;
    snprintf(eval, 1024, "//package[@userId='%d' or @sharedUserId='%d']/sigs/cert", uid, uid);
    xpathObjUid = xmlXPathEvalExpression((xmlChar const *)eval, xpathCtxUid);
    if(xpathObjUid == NULL) {
        /*cannot find uid or shareUid*/
        LOGE("Error: unable to evaluate xpathObjUid expression \n");
        xmlXPathFreeContext(xpathCtxUid);
        xmlXPathFreeContext(xpathCtx);
        xmlXPathFreeObject(xpathObj);
        return(-1);
    }

    nodesUid = xpathObjUid->nodesetval;
    sizeOfCertForUid = (nodesUid) ? nodesUid->nodeNr : 0;
    if (sizeOfCertForUid <= 0)
    {
        LOGE("cannot find sizeOfCertForUid uid:%d\n", sizeOfCertForUid);
        xmlXPathFreeContext(xpathCtx);
        xmlXPathFreeObject(xpathObj);
        xmlXPathFreeContext(xpathCtxUid);
        xmlXPathFreeObject(xpathObjUid);
        return -1;
    }

    LOGV("package %s has %d certs %d certsOfUid\n",pkgName, size, sizeOfCertForUid);

    getInstalledAppCerts(doc);

    for (i = 0; i < size; i++)
    {
        cur = nodes->nodeTab[i];
        tmp = xmlGetProp(cur, (const xmlChar*)"index");
        LOGV("index:%s \n",tmp);
        index = atoi((char const *)tmp);
        xmlFree((void *)tmp);

        curUid = nodesUid->nodeTab[i];
        tmpForUid = xmlGetProp(curUid, (const xmlChar*)"index");
        LOGV("index for uid:%s \n",tmpForUid);
        indexForUid = atoi((char const *)tmpForUid);
        xmlFree((void *)tmpForUid);
        /*3. check if uid and package name get the same cert index*/
        if (indexForUid != index) {
            LOGE("indexForUid %d, index %d not the same\n", indexForUid, index);
            certs[i] = NULL;
            xmlXPathFreeContext(xpathCtx);
            xmlXPathFreeObject(xpathObj);
            xmlXPathFreeContext(xpathCtxUid);
            xmlXPathFreeObject(xpathObjUid);
            return -1;
        }

        if (index < appCertsSize)
        {
            certs[i] = appCerts[index];
        }
        else
        {
            certs[i] = NULL;
        }
    }

    // indicate  the end of data;
    certs[i] = NULL;

    xmlXPathFreeContext(xpathCtx);
    xmlXPathFreeObject(xpathObj);
    xmlXPathFreeContext(xpathCtxUid);
    xmlXPathFreeObject(xpathObjUid);
    return size;

}

static int tee_encode_app_cert(X509 *cert, uint32_t* len, char *buf) {
    char *modulus = NULL;
    unsigned char *modulus_temp = NULL;
    int modulus_size = 0;
    char *exponent = NULL;
    unsigned char *exponent_temp = NULL;
    int exponent_size = 0;
    unsigned char *publickeys_temp = NULL;
    int cer_size = 1;
    int *cer_num = &cer_size;
    int i;
    int ret = -1;
    int public_key_len;

    *len = 0;
    if (X509_get_pubkey(cert) == NULL) {
        LOGE("get pubkey is null");
        return -1;
    }
    modulus = BN_bn2hex(X509_get_pubkey(cert)->pkey.rsa->n);
    exponent = BN_bn2hex(X509_get_pubkey(cert)->pkey.rsa->e);
    if (modulus == NULL || exponent == NULL) {
        LOGE("mod or exp is null");
        goto clean_up;
    }
    LOGV("------exponent %s, modulus %s\n", exponent, modulus);
    LOGV("------exponent size %d, modulus size %d\n", strlen(exponent), strlen(modulus));
    modulus_size = strlen(modulus)/2;
    exponent_size = strlen(exponent)/2;
    publickeys_temp = (unsigned char *)malloc((modulus_size + exponent_size + 8)*(*cer_num));
    if(!publickeys_temp){
        LOGE("*publickeys malloc failed\n");
        goto clean_up;
    }
    memset(publickeys_temp, 0, (modulus_size + exponent_size + 8)*(*cer_num));
    modulus_temp = (unsigned char *)malloc(modulus_size);
    if(!modulus_temp){
        LOGE("modulus_temp malloc failed\n");
        goto clean_up;
    }
    memset(modulus_temp, 0, modulus_size);
    exponent_temp = (unsigned char *)malloc(exponent_size);
    if(!exponent_temp){
        LOGE("exponent_temp malloc failed\n");
        goto clean_up;
    }
    memset(exponent_temp, 0, exponent_size);
    for(i=0; i<modulus_size;i++){
        *(modulus_temp+i) = convert_str2dex(*(modulus+i*2)) << 4 | convert_str2dex(*(modulus+i*2+1));
    }
    for(i=0; i<exponent_size;i++){
        *(exponent_temp+i) = convert_str2dex(*(exponent+i*2)) << 4 | convert_str2dex(*(exponent+i*2+1));
    }
    //dump_data("n:", modulus_temp, modulus_size);
    //dump_data("e:", exponent_temp, exponent_size);

    /* The apk certificate format is as follows:
     * modulus_size(4bytes) ||modulus buffer || exponent size || exponent buffer
     */

    //modulus
    *(unsigned int *)publickeys_temp = modulus_size;
    memcpy(publickeys_temp+sizeof(modulus_size), modulus_temp, modulus_size);

    //exponent
    *(unsigned int *)(publickeys_temp+sizeof(modulus_size)+modulus_size) = exponent_size;
    memcpy(publickeys_temp+sizeof(modulus_size)+sizeof(exponent_size)+modulus_size, exponent_temp, exponent_size);

    public_key_len = modulus_size + exponent_size + sizeof(modulus_size)+sizeof(exponent_size);
    memcpy(buf, &public_key_len, sizeof(public_key_len));
    buf += sizeof(public_key_len);
    *len += sizeof(public_key_len);
    LOGV("public_key_len = %d\n", public_key_len);

    memcpy(buf, publickeys_temp, modulus_size + exponent_size + sizeof(modulus_size) + sizeof(exponent_size));
    *len += modulus_size + exponent_size + sizeof(modulus_size) + sizeof(exponent_size);
    //dump_data("publickey", buf, public_key_len);
    LOGV("total_size = %d ", *len);

    ret = 0;
clean_up:
    if(publickeys_temp)
        free(publickeys_temp);
    if(modulus_temp)
        free(modulus_temp);
    if(exponent_temp)
        free(exponent_temp);
    return ret;
}
#endif

// 测试
int tee_get_app_cert(int ca_pid, int ca_uid, uint32_t* len,
        uint8_t *buffer, uint32_t* type) {
    char * pkgName;
    //xmlDocPtr doc;
    //const xmlChar * certs[16] = {0};
    char buf[2048] = {0};
    int ret;
    //X509 *cert = NULL;
    const unsigned char *temp = NULL;
    char path[MAX_PATH_LENGTH] = {0};
    FILE *fd;
    //uid_t exe_uid;
    int pubkey_len, path_len;
    uint32_t num = 0;

    *type = CA_CERT_NATIVE;

    (void)snprintf(path,MAX_PATH_LENGTH,"/proc/%d/cmdline", ca_pid);
    fd = fopen(path,"r");
    if(fd == NULL) {
        LOGE("fopen is error\n");
        return -1;
    }
    memset(path, 0x00, MAX_PATH_LENGTH);
    num = fread(path,1,MAX_PATH_LENGTH-1,fd);
    fclose(fd);
    if(num == 0 || num > MAX_PATH_LENGTH - 1) {
        LOGE("Bad pacakge name:num is %d\n", num);
        return -1;
    }

    pkgName = path;
    *len = 0;
    //LOGV("num is %d", num);
    //LOGV("len is %d, packagename is %s\n", *len, pkgName);
    path_len = num;
    memcpy(buffer, &path_len, sizeof(path_len));
    buffer += sizeof(path_len);
    *len += 4;
    memcpy(buffer, path, num);
    buffer += num;
    *len += num;


    //doc = xmlParseFile("/data/system/packages.xml");
    //if (doc == NULL)
    {
        pubkey_len = 0;
        memcpy(buffer, &pubkey_len, sizeof(pubkey_len));
        buffer += sizeof(pubkey_len);
        *len += sizeof(pubkey_len);
        //LOGE( "Error: unable to parse xml file\n");
        /* We return success because we still have valid uid data */
        return(0);
    }
#if 0
    if (getCertsForPackage(doc, pkgName, ca_uid, certs) < 0)
    {
        /*If get public key failed,pass 0, then in kernel get uid for ca*/
        pubkey_len = 0;
        memcpy(buffer, &pubkey_len, sizeof(pubkey_len));
        buffer += sizeof(pubkey_len);
        *len += sizeof(pubkey_len);
        LOGE("get certs for app failed\n");
        xmlFreeDoc(doc);
        /* We return success because we still have valid uid data */
        return 0;
    }

    int i = 0;
    uint32_t cert_len=0;
    *type = CA_CERT_APK;
    LOGE("get certs :\n");
    while(certs[i])
    {
        ret = strToByte(buf, (char *)certs[i]);
        temp = buf;

        cert = d2i_X509(NULL, &temp, ret);
        if (!cert)
        {
            LOGE("unable to parse certificate in memory\n");
            return -1;
        }

        tee_encode_app_cert(cert, &cert_len, buffer);
        X509_free(cert);
        i++;
    }
    *len += cert_len;

    xmlFreeDoc(doc);
    return 0;
#endif
}
