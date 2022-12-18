/*********************************************************************************************************************
*  @file     samba_server.cpp
*  @brief    samba server is here
*  @version  1.0
*  @date     20110610
**********************************************************************************************************************/


#include "Samba.h"
#include <ctype.h>
#include <time.h>
#include <signal.h>
#include <setjmp.h>
#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
static sigjmp_buf jmpbuf;
static volatile sig_atomic_t canjump;

#include "HiNSClient.h"
#include "IHiNSService.h"

#include <cutils/properties.h>
#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "------SambaServer--------"

#ifdef ANDROID_SAMBA
/*      ANDROID     */
#include "jni.h"
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>

#define USE_NETBIOS_NAME

#else
/*      UBUNTU      */
#define LOGI(str) printf("%s:\t%s\n", LOG_TAG, str)
#define LOGE(str) printf("%s:\t%s\n", LOG_TAG, str)
#define LOGW(str) printf("%s:\t%s\n", LOG_TAG, str)
#endif
using namespace android;
class SambaServer : public Samba
{
public:
    class Share_Parameter;
    /*  Constructor and distructor function     */
    static SambaServer * getInstance();
    static void releaseInstance();
public:
    /*      for jni     */
    /*  start or stop samba and set user passwd */
    int start_sambaServer(void);
    int stop_sambaServer(void);
    int set_user(const char *user);
    int set_passwd(const char *passwd);

    /*  Set often use parameter */
    int set_global(const char *workgroup, const char *server_string, const char *security, int maxLogSize, const char *netbios, ...);
    int get_share_head();                               // Get share head
    int get_share_parameter(const char *head);      // Get share parameter
    int get_config_model(const char *head);         // Reserve      Get config model
    int add_share_path(Share_Parameter *para);      // Create new share path
    int edit_share_path(Share_Parameter *para);     // Edit existed share path
    int delete_share_path(const char *head);            // Delete existed share path
    int get_sambaStatus();                              // Get Samba status


public:
    std::vector<std::string> share_head;    //  get share head
    std::vector<std::string> listStr;       //  get property in here.
    std::string str;                            //  for jni get share parameter
    Share_Parameter *para;

public:
    struct Share_Parameter                  //  embedded class
    {
    public:
        Share_Parameter();
//      ~Share_Parameter();
    public:
        const char *isHideDotFiles;
        const char *hideFiles;
        const char *head;
        const char *path;
        const char *createMask;
        const char *directoryMask;
        const char *available;
        const char *browseable;
        const char *writable;
//  #ifdef VALIDUSERS
        const char *validUsers;
//  #endif
    };
        enum
    {
        HEAD_DOESNOT_EXIST = -11,
        HEAD_HAS_EXISTED = -10,
        ERROR = -1,
        NOMAL_RETURN = 0,
        SHARE = 0x01,
        USER = 0x02,
        DOMAIN = 0x04,
        GET_PARA = 0x0a,
        HAVE_EXECUTE = 16,
        SMBCONF = 128,
        MAX_SIZE = 255,
    };

private:
/*      Set share property  */
    int set_share_property(Share_Parameter *para);
	int changeConf(const char *filepath,const char *title,const char *valume);
/***********************************************************************
    The next two function is implyed in Base Class : class Samba
if you wanna rewrite, you can redefine!
    virtual int create_smbDir();
    virtual int create_smbConf();
************************************************************************/
    char*	getMac();
/*  get security degree */
        int getSecurity();

private:
/*
The five string is in Base Class : class Samba
        std::string SMBD_PID;
        std::string NMBD_PID;
        std::string SMBUSERS_PATH;
        std::string SMBCONF_PATH;
        std::string SMB_PATH;
*/
    static int SECURITY;
    static SambaServer *pSamba;
    SambaServer();
    virtual ~SambaServer();

};

/*      Constructor         */
SambaServer::SambaServer()
{
    LOGI("SambaServer constructor");
    SMBD_PID = "/data/app/samba/var/locks/smbd.pid";
    NMBD_PID = "/data/app/samba/var/locks/nmbd.pid";
    SMBUSERS_PATH = "/data/app/samba/lib/smbusers";
    SMBCONF_PATH = "/data/app/samba/lib/smb.conf";
    SMB_PATH = "/data/app/samba";
    para = new Share_Parameter();
    if(create_smbConf())
        LOGE("Create smb.conf fail!!");
}

/*      disstructor     */
SambaServer::~SambaServer()
{
    delete para;
    para = NULL;
}

/*      embedded class  Share_Parameter Construct   */
SambaServer::Share_Parameter::Share_Parameter() : isHideDotFiles("yes"),
        hideFiles("/.*/lost+found/"), path(NULL), createMask(NULL), directoryMask(NULL),
        available(NULL), browseable(NULL), writable(NULL), validUsers(NULL)
{

}



int SambaServer::changeConf(const char *filepath,const char *title,const char *valume)
{
    FILE *stream;
	char buf[255] = {0};
	char writebuf[2048]= {0};
    stream = fopen(filepath, "r");
    if(stream == NULL)
    {
        LOGE("Open SMBCONF fail!");
        return -1;
    }

    fseek(stream, 0, SEEK_SET);

    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
		if( strstr(buf, title))
		{
		sprintf(buf,"\t%s = %s\n",title,valume);
		}
		strcat(writebuf,buf);
	}
	fclose(stream);

	stream = fopen(filepath, "w");
	fputs(writebuf, stream);
	fclose(stream);
	return 0;
}


/*      Just One Instance       */
SambaServer * SambaServer::getInstance()    //  static need remove
{
    if(!pSamba)
        pSamba = new SambaServer();
    return pSamba;
}

/*      Release the only one Instance       */
void SambaServer::releaseInstance()     //  static need remove
{
    delete pSamba;
    pSamba = NULL;
}

/*      Security        */
int SambaServer::SECURITY = 0;
SambaServer* SambaServer::pSamba = NULL;

static void alarm_func(int sig)
{
    if(canjump == 0)
        return;
    canjump = 0;
    siglongjmp(jmpbuf, 1);
}
static int GetMac( const char *ifname, unsigned char *mac )
{
    int sock, ret ,i;
    struct ifreq ifr;
    sock = socket( AF_INET, SOCK_STREAM, 0 );
    if ( sock < 0 ) {
        perror( "socket" );
        return -1;
    }
    memset( &ifr, 0, sizeof(ifr) );
    strcpy( ifr.ifr_name, ifname );
    ret = ioctl( sock, SIOCGIFHWADDR, &ifr, sizeof(ifr) );
    if ( ret == 0 ) {
        memcpy( mac , ifr.ifr_hwaddr.sa_data ,6);
    } else {
        SLOGE("no mac");
    }
    close( sock );
    return ret;
}
/*      Start Samba Server      */
int SambaServer::start_sambaServer()
{
    if(get_sambaStatus())
    {
        LOGW("Samba have started! No need to restart samba!");
        return NOMAL_RETURN;
    }
    cleanup(0x04);
#ifdef USE_NETBIOS_NAME
    char netbios_name[MAX_SIZE / 2] = {0};
    unsigned char mac[6]={0};
    if( GetMac("eth0",mac) == 0 ){
        sprintf(netbios_name,"Android_%x%x%x",mac[5],mac[4],mac[3]);
    }else
        strcpy(netbios_name,"Android_STB");


	changeConf("/data/app/samba/lib/smb.conf","netbios name",netbios_name);
	changeConf("/data/app/samba/lib/smb.conf","server string",netbios_name);
    LOGI("line : %d, netbios and server string = %s", __LINE__, netbios_name);
    sleep(1);
#endif
	if(HiNSClient::sambaStart() != 0)
		return ERROR;

    return NOMAL_RETURN;
}

/*      Stop Samba Server       */
int SambaServer::stop_sambaServer()
{
    if(!get_sambaStatus())
    {
        LOGW("Samba have stoped! No need to restop samba!");
        return NOMAL_RETURN;
	}
	if(HiNSClient::sambaStop() != 0)
		return ERROR;
    remove("/data/app/samba/var/log.smbd");
    remove("/data/app/samba/var/log.nmbd");
    return NOMAL_RETURN;
}


/**
 *  Create user for samba
 *  @param[in]          const char *user
 *  @param[in|out]
 *  @return         int
 *  @note
 */
int SambaServer::set_user(const char *user)
{
    if(access(SMBUSERS_PATH.c_str(), R_OK) != 0)
    {
        int fd;
//      Create file when file does not exist!
        fd = open(SMBUSERS_PATH.c_str(), O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
        const char *str = "radio = ";
        if((write(fd, str, strlen(str) + 1)) < 0)
        LOGE("Write fail!");
        close(fd);
    }
    FILE *stream;
    char buf[MAX_SIZE] = {0};
    char write_buf[MAX_SIZE] = {0};
    if((stream = fopen(SMBUSERS_PATH.c_str(), "w+")) == NULL)
    {
        LOGE("fopen fail!");
        return ERROR;
    }
	/*
    fseek(stream, 0, SEEK_SET);
    if(fgets(buf, MAX_SIZE, stream) == NULL)
    {
        LOGE("fgets file fail!");
        return ERROR;
    }
    char *pStr = strchr(buf, '\n');
    if(pStr)
        *pStr = 0;
	*/
LOGI("info buf:\t%s", buf);
LOGI("info user:\t%s",user);

    sprintf(write_buf, "radio = %s",  user);
    LOGI("info:\t%s", write_buf);
    fseek(stream, 0, SEEK_SET);
    if( fputs(write_buf, stream) >= 0)
        LOGI("Write smbusers success!");
    else LOGE("Write smbusers fail!");
    fclose(stream);
    return NOMAL_RETURN;
}


/**
 *  Create user's passwd for samba
 *  @param[in]          const char *passwd
 *  @param[in|out]
 *  @return         int
 *  @note
 */
int SambaServer::set_passwd(const char *passwd)
{
/*
 *  options:
 *    -L                   local mode (must be first option)
 *    -h                   print this usage message
 *    -s                   use stdin for password prompt
 *    -c smb.conf file     Use the given path to the smb.conf file
 *    -D LEVEL             debug level
 *    -r MACHINE           remote machine
 *    -U USER              remote username
 *  extra options when run by root or in local mode:
 *    -a                   add user
 *    -d                   disable user
 *    -e                   enable user
 *    -i                   interdomain trust account
 *    -m                   machine trust account
 *    -n                   set no password
 *    -W                   use stdin ldap admin password
 *    -w PASSWORD          ldap admin password
 *    -x                   delete user
 *    -R ORDER             name resolve order
 */
    if(!passwd)
		return ERROR;
	if(HiNSClient::sambaChangePassword(passwd) != 0)
		return ERROR;
    return NOMAL_RETURN;
}


/**
 *  Set Global parameter
 *  @param[in]          const char *workgroup, const char *server_string, const char *security, int maxLogSize
 *  @param[in|out]
 *  @return         int
 *  @note
 */
int SambaServer::set_global(const char *workgroup, const char *server_string, const char *security, int maxLogSize, const char *netbios, ...)
{
    LOGI("Set global parameter!");
    char buf[MAX_SIZE] = {0};
    if(workgroup)
    {
        LOGI("WORKGROUP = %s", workgroup);
		changeConf(SMBCONF_PATH.c_str(),"workgroup",workgroup);
    }
    if(server_string && strlen(server_string) > 0)
    {
        LOGI("server_string = %s", server_string);
		changeConf(SMBCONF_PATH.c_str(),"server string",server_string);
    }
    if(security)
    {
        if(!strcmp(security,"share"))
        {
		SECURITY = 0x01;
		changeConf(SMBCONF_PATH.c_str(),"valid users","");
		changeConf(SMBCONF_PATH.c_str(),"guest ok","yes");
                changeConf(SMBCONF_PATH.c_str(),"force user","root");
        }
        else if(!strcmp(security,"user"))
        {
        SECURITY = 0x02;
        /**
         *  @brief : Same as above
         */
		changeConf(SMBCONF_PATH.c_str(),"valid users","radio");
		changeConf(SMBCONF_PATH.c_str(),"guest ok","");
        }
        else
		{
		SECURITY = 0x04;
		}
        LOGI("security = %s", security);
		changeConf(SMBCONF_PATH.c_str(),"security",security);
    }
    if(maxLogSize > 0)
    {
        LOGI("maxLogSize = %d", maxLogSize);
		char logsize[64];
		sprintf(logsize,"%d",maxLogSize);
		changeConf(SMBCONF_PATH.c_str(),"max log size",logsize);
    }
#ifdef USE_NETBIOS_NAME
    if(0)
    {
        char netbios_short[MAX_SIZE / 2] = {0};
        char netbios_name[MAX_SIZE / 2] = {0};
        strncpy(netbios_short, netbios, 10);
        sprintf(netbios_name, "%s-%s", netbios_short, getMac());
        LOGI("Netbois name = %s", netbios);
		changeConf(SMBCONF_PATH.c_str(),"netbios name",netbios_name);
    }
#endif
    return NOMAL_RETURN;
}



/**
 *  Set Share parameter
 *  @param[in]          Share_Parameter *para
 *  @param[in|out]
 *  @return         int
 *  @note
 */

int SambaServer::set_share_property(Share_Parameter *para)
{
    LOGI("Set global parameter!");
    char buf[MAX_SIZE] = {0};
	char writebuf[2048]= {0};
//  first set out of function 'set_share_property';
    if(para == NULL)
    {
        para = new Share_Parameter();
        para->head = "sdcard";      // Reserve
        para->available = "yes";
        para->browseable = "yes";
        para->createMask = "0777";
        para->directoryMask = "0777";
        para->path = "/sdcard";
        para->writable = "yes";
        if(getSecurity() == USER || SECURITY == USER)
        para->validUsers = "radio";
        else if(SECURITY == SHARE)
        ;
    }

    FILE *stream;
    stream = fopen(SMBCONF_PATH.c_str(), "r");
    if(stream == NULL)
    {
        LOGE("Open SMBCONF fail!");
        return NULL;
    }

    fseek(stream, 0, SEEK_SET);

    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
		if( strstr(buf, "writable") && para->writable)
		{
		sprintf(buf,"\twritable = %s\n",para->writable);
		}
		else if( strstr(buf, "available") && para->available )
		{
		sprintf(buf,"\tavailable = %s\n",para->available);
		}
		else if( strstr(buf, "browseable") && para->browseable )
		{
		sprintf(buf,"\tbrowseable = %s\n",para->browseable);
		}
		else if( strstr(buf, "create mask") && para->createMask )
		{
		sprintf(buf,"\tcreate mask = %s\n",para->createMask);
		}
		else if( strstr(buf, "directory mask") && para->directoryMask )
		{
		sprintf(buf,"\tdirectory mask = %s\n",para->directoryMask);
		}
		else if( strstr(buf, "path") && para->path )
		{
		char tmp[MAX_SIZE] = {0};
		LOGI("path = %s", para->path);
		if(*(para->path) == '/')
		sprintf(tmp, "%s", para->path);
		else
		sprintf(tmp, "/%s", para->path);

		sprintf(buf,"\tpath = %s\n",tmp);
		}

		if(SECURITY == USER || getSecurity() == USER)
		{
		if( strstr(buf, "guest ok") )
		{
		sprintf(buf,"\tguest ok = \n");
		}
		else if( strstr(buf, "valid users") && para->validUsers )
		{
		para->validUsers = "radio";
		sprintf(buf,"\tvalid users = %s\n",para->validUsers);
		}
		}
		if(SECURITY == SHARE || getSecurity() == SHARE)
		{
		if( strstr(buf, "guest ok") )
		{
		sprintf(buf,"\tguest ok = yes\n");
		}
		else if( strstr(buf, "valid users") )
		{
		sprintf(buf,"\tvalid users = \n");
		}
                else if(strstr(buf,"force user"))
                {
                sprintf(buf,"\tforce user = root \n");
                }
		}

		strcat(writebuf,buf);
	}
	fclose(stream);

	stream = fopen(SMBCONF_PATH.c_str(), "w");
	fputs(writebuf, stream);
	fclose(stream);
    return NOMAL_RETURN;
}


/**
 *  Get Security
 *  @param[in]          void
 *  @param[in|out]
 *  @return         int
 *  @note
 */
int SambaServer::getSecurity()
{
    FILE *stream;
    char buf[MAX_SIZE] = {0};
    if( (stream = fopen(SMBCONF_PATH.c_str(), "r")) == NULL )
        LOGE("Open SMBCONF fail!");
    fseek(stream, 0, SEEK_SET);
    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
        if(strstr(buf, "security"))
        {
        if(strstr(buf, "share"))
        return SHARE;
        else if(strstr(buf, "user"))
        return USER;
        else return DOMAIN;
        }
    }
    return ERROR;
}


/**
 *  Get Samba smb.conf share head
 *  @param[in]          void
 *  @param[in|out]
 *  @return         int
 *  @note
 */
int SambaServer::get_share_head()
{
    FILE *stream;
    char buf[MAX_SIZE] = {0};
    stream = fopen(SMBCONF_PATH.c_str(), "r");
    if(stream == NULL)
    {
        LOGE("Open SMBCONF fail!");
        return ERROR;
    }
    fseek(stream, 0, SEEK_SET);
    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
        if(strstr(buf, "[global]"))
        continue;
        if(strstr(buf, "\n"))
        *strstr(buf, "\n") = 0;
        if(strstr(buf, "]"))
        *strstr(buf, "]") = 0;
        if(strstr(buf, "["))
        share_head.push_back(buf + 1);
    }
    return NOMAL_RETURN;
}


/**
 *  get ont of share parameter
 *  @param[in]          const char *head
 *  @param[in|out]
 *  @return         int
 *  @note
 */
int SambaServer::get_share_parameter(const char *head)
{
    if(!head)
    {
        LOGE("Please enter parameter for share!");
        return NULL;
    }
    FILE *stream;
    char head_buf[MAX_SIZE] = {0};
    sprintf(head_buf, "[%s]", head);
    char buf[MAX_SIZE] = {0};
    stream = fopen(SMBCONF_PATH.c_str(), "r");
    if(stream == NULL)
    {
        LOGE("Open SMBCONF fail!");
        return NULL;
    }
    fseek(stream, 0, SEEK_SET);
    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
        if( strstr(buf, head_buf) )
        break;
    }
    fseek(stream, 0, SEEK_CUR);
    int i = 0;
    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
        if( strstr(buf, "[") || strstr(buf, "]") )
        break;
        if(strstr(buf, "available"))
        {
        *strstr(buf, "\n") = 0;
        para->available = buf;
        listStr.push_back(para->available);
        }
        if(strstr(buf, "browseable"))
        {
        *strstr(buf, "\n") = 0;
        para->browseable = buf;
        listStr.push_back(para->browseable);
        }
        if(strstr(buf, "create mask"))
        {
        *strstr(buf, "\n") = 0;
        para->createMask = buf;
        listStr.push_back(para->createMask);
        }
        if(strstr(buf, "directory mask"))
        {
        *strstr(buf, "\n") = 0;
        para->directoryMask = buf;
        listStr.push_back(para->directoryMask);
        }
        if(strstr(buf, "path"))
        {
        *strstr(buf, "\n") = 0;
        para->path = buf;
        listStr.push_back(para->path);
        }
        if(strstr(buf, "valid users") && getSecurity() == USER)
        {
        *strstr(buf, "\n") = 0;
        para->validUsers = buf;
        listStr.push_back(para->validUsers);
        }
        if(strstr(buf, "writable"))
        {
        *strstr(buf, "\n") = 0;
        para->writable = buf;
        listStr.push_back(para->writable);
        }
    }
    return NOMAL_RETURN;
}


/**
 *  reserve : get config model
 *  @param[in]          const char *head
 *  @param[in|out]
 *  @return         int
 *              return HEAD_HAS_EXISTED         head has existed
 *              return HEAD_DOESNOT_EXIST       head does not exist
 *              return ERROR                        normal error
 *  @note       reserve
 */
int SambaServer::get_config_model(const char *head)
{
    return NOMAL_RETURN;
}


/**
 *  Create new share path
 *  @param[in]          Share_Parameter *para
 *  @param[in|out]
 *  @return         int
 *              return HEAD_HAS_EXISTED         head has existed
 *              return HEAD_DOESNOT_EXIST       head does not exist
 *              return ERROR                        normal error
 *  @note       reserve
 */
int SambaServer::add_share_path(Share_Parameter *para)
{
    if(!para->head)
    {
        LOGE("Please enter parameter for share!");
        return ERROR;
    }
    FILE *stream;
    char buf[MAX_SIZE] = {0};
    stream = fopen(SMBCONF_PATH.c_str(), "a+");
    if(stream == NULL)
    {
        LOGE("Open SMBCONF fail!");
        return ERROR;
    }
    char tmp[SMBCONF] = {0};
    sprintf(tmp, "[%s]", para->head);
    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
        if( strstr(buf, tmp) )
        goto error;
    }
    sprintf(buf, "\n[%s]\n", para->head);
    fputs(buf, stream);
    sprintf(buf, "\thide dot files = %s\n", para->isHideDotFiles);
    fputs(buf, stream);
    sprintf(buf, "\thide files = %s\n", para->hideFiles);
    fputs(buf, stream);
    sprintf(buf, "\tavailable = %s\n", para->available);
    fputs(buf, stream);
    sprintf(buf, "\tbrowseable = %s\n", para->browseable);
    fputs(buf, stream);
    sprintf(buf, "\tcreate mask = %s\n", para->createMask);
    fputs(buf, stream);
    sprintf(buf, "\tdirectory mask = %s\n", para->directoryMask);
    fputs(buf, stream);
    if(para->path)
    {
        if(*(para->path) != '/')
        {
        sprintf(tmp, "/%s", para->path);
        }
        else sprintf(tmp, "%s", para->path);
    }
    sprintf(buf, "\tpath = %s\n", tmp);
    fputs(buf, stream);
    sprintf(buf, "\twritable = %s\n", para->writable);
    fputs(buf, stream);
    if(getSecurity() == USER)
    {
        para->validUsers = "radio";
        sprintf(buf, "\tvalid users = %s\n", para->validUsers);
        fputs(buf, stream);
        sprintf(buf, "\tguest ok = \n");
        fputs(buf, stream);
    }
    else if(getSecurity() == SHARE)
    {
        sprintf(buf, "\tvalid users = \n");
        fputs(buf, stream);
        sprintf(buf, "\tguest ok = yes\n");
        fputs(buf, stream);
        sprintf(buf, "\tforce user = root \n");
        fputs(buf, stream);
    }
    fclose(stream);
    return NOMAL_RETURN;
error:
    LOGE("add_share_path :\t Head has existed");
    return HEAD_HAS_EXISTED;
}


/**
 *  Edit existed share path
 *  @param[in]          Share_Parameter *para
 *  @param[in|out]
 *  @return         int
 *              return HEAD_HAS_EXISTED         head has existed
 *              return HEAD_DOESNOT_EXIST       head does not exist
 *              return ERROR                        normal error
 *  @note       reserve
 */
int SambaServer::edit_share_path(Share_Parameter *para)
{
    if(!para->head)
    {
        LOGE("Please enter parameter for share!");
        return ERROR;
    }
    set_share_property(para);
    return NOMAL_RETURN;
}


/**
 *  Delete existed share path
 *  @param[in]          const char *head
 *  @param[in|out]
 *  @return         int
 *              return HEAD_HAS_EXISTED         head has existed
 *              return HEAD_DOESNOT_EXIST       head does not exist
 *              return ERROR                        normal error
 *  @note       reserve
 */
int SambaServer::delete_share_path(const char *head)
{
    if(!head)
    {
        LOGE("Please enter parameter for share!");
        return ERROR;
    }
    FILE *stream;
    char buf[MAX_SIZE] = {0};
	char writebuf[2048] = {0};
    stream = fopen(SMBCONF_PATH.c_str(), "r");
    if(stream == NULL)
    {
        LOGE("Open SMBCONF fail!");
        return ERROR;
    }
    char tmp[SMBCONF] = {0};
    sprintf(tmp, "[%s]", head);
    while( (fgets(buf, sizeof(buf), stream)) != NULL )
    {
        if( strstr(buf, tmp) )
		break;
		strcat(writebuf,buf);
    }
    fclose(stream);

	stream = fopen(SMBCONF_PATH.c_str(), "w");
	fputs(writebuf, stream);
	fclose(stream);
    return NOMAL_RETURN;
}




int find_pid_by_name( char* ProcName)
{
	int retpid=0;
	HiNSClient::NSSh(HI_NS_CMD_TYPE_PSM,"/mnt/ps") ;
	FILE *fp = fopen("/mnt/ps", "r");
	if (fp)
	{
		char line[4096] = {0};
		int row = 0;
		while (line == fgets(line, 4096, fp))
		{
		row++;
		if (row > 1)
		{
		char user[50];
		char pid[10];
		char cpu[10];
		char vsz[10];
		char rss[10];
		char wchan[20];
		char pc[20];
		char status[20];
		char name[20];
		sscanf(line, "%s %s %s %s %s %s %s %s %s",
		   user, pid, cpu, vsz, rss, wchan, pc,status,name);
		if(strstr(name,ProcName))
		{
		retpid=atoi(pid);
		break;
		}
		}
		}

		fclose(fp);
		remove("/mnt/ps");
	}
	return retpid;
}


/**
 *  get ont of share parameter
 *  @param[in]          void
 *  @param[in|out]
 *  @return         int 1, starting status;     0, Stopping status;
 *  @note
 */
int SambaServer::get_sambaStatus()
{
    int rev , smbdID, nmbdID, pid_t[128];
    smbdID = find_pid_by_name("smbd");
    nmbdID = find_pid_by_name("nmbd");
	if(smbdID!=0 && nmbdID!=0)
	{
		return 1;
	}
    return 0;
}



char* SambaServer::getMac()
{
	int nSocket;
	char mac[18];
	struct ifreq struReq;

	nSocket = socket(PF_INET,SOCK_STREAM,0);
	memset(&struReq,0,sizeof(struReq));
	strncpy(struReq.ifr_name, "eth0", sizeof(struReq.ifr_name));
	ioctl(nSocket,SIOCGIFHWADDR,&struReq);
	close(nSocket);
	sprintf(mac,"%02x:%02x:%02x:%02x:%02x:%02x",
		(unsigned char)struReq.ifr_hwaddr.sa_data[0],
		(unsigned char)struReq.ifr_hwaddr.sa_data[1],
		(unsigned char)struReq.ifr_hwaddr.sa_data[2],
		(unsigned char)struReq.ifr_hwaddr.sa_data[3],
		(unsigned char)struReq.ifr_hwaddr.sa_data[4],
		(unsigned char)struReq.ifr_hwaddr.sa_data[5]);

	return 0;
}

/*      JNI     */
JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_startSambaServer
  (JNIEnv *env, jobject obj)
{
    LOGI("Start");
    int ret = SambaServer::getInstance()->start_sambaServer();
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_stopSambaServer
  (JNIEnv *env, jobject obj)
{
    int ret = SambaServer::getInstance()->stop_sambaServer();
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_setUser
  (JNIEnv *env, jobject obj, jstring account)
{
        const char *user;
    user = env->GetStringUTFChars(account,NULL);
    int ret = SambaServer::getInstance()->set_user(user);
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_setPasswd
  (JNIEnv *env, jobject obj, jstring pw)
{
    const char *pass;
    pass = env->GetStringUTFChars(pw,NULL);
    int ret = SambaServer::getInstance()->set_passwd(pass);
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_setGlobal
  (JNIEnv *env, jobject obj, jstring workgroup, jstring server_string, jstring security, jint maxLogSize, jstring netbios)
{
    const char *group,*info,*safe,*bios;
    group = env->GetStringUTFChars(workgroup,NULL);
    info = env->GetStringUTFChars(server_string,NULL);
    safe = env->GetStringUTFChars(security,NULL);
    bios = env->GetStringUTFChars(netbios,NULL);
    int ret = SambaServer::getInstance()->set_global(group,info,safe,maxLogSize,bios);
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_addProperty
  (JNIEnv *env, jobject obj, jstring hd, jstring ph, jstring cMask, jstring dMask,
    jstring avail, jstring browse, jstring write, jstring Users)
{
    const char *head,*path,*createMask,*directoryMask,*available,*browseable,*writable,*validUsers;
    head = env->GetStringUTFChars(hd,NULL);
    path = env->GetStringUTFChars(ph,NULL);
    createMask = env->GetStringUTFChars(cMask,NULL);
    directoryMask = env->GetStringUTFChars(dMask,NULL);
    available = env->GetStringUTFChars(avail,NULL);
    browseable = env->GetStringUTFChars(browse,NULL);
    writable = env->GetStringUTFChars(write,NULL);
    validUsers = env->GetStringUTFChars(Users,NULL);

    SambaServer::getInstance()->para->available = available;
    SambaServer::getInstance()->para->browseable = browseable;
    SambaServer::getInstance()->para->createMask = createMask;
    SambaServer::getInstance()->para->directoryMask = directoryMask;
    SambaServer::getInstance()->para->head = head;
    SambaServer::getInstance()->para->path = path;
    SambaServer::getInstance()->para->writable = writable;
    SambaServer::getInstance()->para->validUsers = validUsers;
    int ret = SambaServer::getInstance()->add_share_path(SambaServer::getInstance()->para);
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_editShare
  (JNIEnv *env, jobject obj, jstring hd, jstring ph, jstring cMask, jstring dMask,
    jstring avail, jstring browse, jstring write, jstring Users)
{

    const char *head,*path,*createMask,*directoryMask,*available,*browseable,*writable,*validUsers;
    head = env->GetStringUTFChars(hd,NULL);
    path = env->GetStringUTFChars(ph,NULL);
    createMask = env->GetStringUTFChars(cMask,NULL);
    directoryMask = env->GetStringUTFChars(dMask,NULL);
    available = env->GetStringUTFChars(avail,NULL);
    browseable = env->GetStringUTFChars(browse,NULL);
    writable = env->GetStringUTFChars(write,NULL);
    validUsers = env->GetStringUTFChars(Users,NULL);

    SambaServer::getInstance()->para->available = available;
    SambaServer::getInstance()->para->browseable = browseable;
    SambaServer::getInstance()->para->createMask = createMask;
    SambaServer::getInstance()->para->directoryMask = directoryMask;
    SambaServer::getInstance()->para->head = head;
    SambaServer::getInstance()->para->path = path;
    SambaServer::getInstance()->para->writable = writable;
    SambaServer::getInstance()->para->validUsers = validUsers;
    int ret = SambaServer::getInstance()->edit_share_path(SambaServer::getInstance()->para);
    SambaServer::releaseInstance();
    return ret;
}

JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_deleteShare
  (JNIEnv *env, jobject obl, jstring hd)
{
    const char *head;
    head = env->GetStringUTFChars(hd,NULL);
    int ret = SambaServer::getInstance()->delete_share_path(head);
    SambaServer::releaseInstance();
    return ret;
}


JNIEXPORT jstring JNICALL Java_com_hisilicon_android_NativeSamba_getProperty
  (JNIEnv *env, jobject obj)
{
    jstring myshared;
    if(!SambaServer::getInstance()->get_share_head())
    {
        for(int i = 0; i < SambaServer::getInstance()->share_head.size(); i++)
        {
        SambaServer::getInstance()->str += SambaServer::getInstance()->share_head[i];
        SambaServer::getInstance()->str += "|";
        //  std::cout<<SambaServer::getInstance()->share_head[i]<<std::endl;
        }
    }
    if(SambaServer::getInstance()->str.empty())
    {
        SambaServer::releaseInstance();
        return NULL;
    }
    myshared = env->NewStringUTF(SambaServer::getInstance()->str.c_str());
    SambaServer::releaseInstance();
    return myshared;
}

JNIEXPORT jstring JNICALL Java_com_hisilicon_android_NativeSamba_getParameter
  (JNIEnv *env, jobject obj, jstring hd)
{

    jstring myshared;
    const char *head;
    head = env->GetStringUTFChars(hd,NULL);
    if(!SambaServer::getInstance()->get_share_parameter(head))
    {
        for(int i = 0; i < SambaServer::getInstance()->listStr.size(); i++)
        {
        SambaServer::getInstance()->str += SambaServer::getInstance()->listStr[i].substr(1);

        SambaServer::getInstance()->str += "|";
        }
    }
        if(SambaServer::getInstance()->str.empty())
        {
                SambaServer::releaseInstance();
                return NULL;
        }
    myshared = env->NewStringUTF(SambaServer::getInstance()->SambaServer::getInstance()->str.c_str());
    SambaServer::releaseInstance();
    return myshared;
}

/*
 * Class:     com_explorer_jni_NativeSamba
 * Method:    getSambaProcessState
 * Signature: ()I
 */
JNIEXPORT jint JNICALL Java_com_hisilicon_android_NativeSamba_getSambaProcessState
  (JNIEnv *env, jobject jobj)
{
    jint i = SambaServer::getInstance()->get_sambaStatus();
    SambaServer::releaseInstance();
    return i;
}



static const JNINativeMethod g_methods[] =
{
    { "startSambaServer", "()I", (void*)Java_com_hisilicon_android_NativeSamba_startSambaServer},
    { "stopSambaServer", "()I", (void*)Java_com_hisilicon_android_NativeSamba_stopSambaServer},
    { "setUser", "(Ljava/lang/String;)I", (void*)Java_com_hisilicon_android_NativeSamba_setUser},
    { "setPasswd", "(Ljava/lang/String;)I", (void*)Java_com_hisilicon_android_NativeSamba_setPasswd},
    { "setGlobal", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;ILjava/lang/String;)I", (void*)Java_com_hisilicon_android_NativeSamba_setGlobal},
    { "addProperty", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I" \
, (void*)Java_com_hisilicon_android_NativeSamba_addProperty},
    { "editShare", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)I" \
, (void*)Java_com_hisilicon_android_NativeSamba_editShare},
    { "deleteShare", "(Ljava/lang/String;)I", (void*)Java_com_hisilicon_android_NativeSamba_deleteShare},
    { "getProperty", "()Ljava/lang/String;", (void*)Java_com_hisilicon_android_NativeSamba_getProperty},
    { "getParameter", "(Ljava/lang/String;)Ljava/lang/String;", (void*)Java_com_hisilicon_android_NativeSamba_getParameter},
    { "getSambaProcessState", "()I", (void*)Java_com_hisilicon_android_NativeSamba_getSambaProcessState},

};

static int register_com_odc_setting_NativeSamba(JNIEnv* env) {

    jclass clazz;
    clazz = env->FindClass("com/hisilicon/android/netshare/NativeSamba");
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, g_methods, NELEM(g_methods)) < 0)
        return JNI_FALSE;
    return JNI_TRUE;
}

extern int register_com_explorer_jni_SambaTreeNative(JNIEnv* env);
extern int register_com_FileExplorer_jni_Jni(JNIEnv* env);
extern int register_com_hisilicon_android_nfsClient(JNIEnv* env);
jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    JNIEnv* env = NULL;
    jint result = -1;

    if (vm->GetEnv((void**) &env, JNI_VERSION_1_4) != JNI_OK)
        goto bail;
    if (!register_com_odc_setting_NativeSamba(env))
        goto bail;

	if (!register_com_explorer_jni_SambaTreeNative(env))
		goto bail;

	if (!register_com_FileExplorer_jni_Jni(env))
		goto bail;

	if (!register_com_hisilicon_android_nfsClient(env))
		goto bail;
    result = JNI_VERSION_1_4;
bail:
    return result;
}
