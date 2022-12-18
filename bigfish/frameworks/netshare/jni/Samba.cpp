/*********************************************************************************************************************
*  @file     Samba.cpp
*  @brief    define samba server interface file
*  @version  1.0
*  @date     20110601
**********************************************************************************************************************/


#include "Samba.h"
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <net/if.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include "HiNSClient.h"
#include "IHiNSService.h"
using namespace android;
Samba::Samba()
{
	SMBD_PID = "/data/app/samba/var/locks/smbd.pid";
	NMBD_PID = "/data/app/samba/var/locks/nmbd.pid";
	SMBUSERS_PATH = "/data/app/samba/lib/smbusers";
	SMBCONF_PATH = "/data/app/samba/lib/smb.conf";
	SMB_PATH = "/data/app/samba";
	SMB_LOCKS = "/data/app/samba/var/locks";
	if(create_smbConf())
		LOGE("Create smb.conf fail!!");
	std::string codepages_path = SMB_PATH + "/lib";
	std::string str = codepages_path + "/lowcase.dat";
	std::string charset_path = SMB_PATH + "/lib/charset";
	std::string cp850 = charset_path + "/CP850.so";
	if(access(str.c_str(), F_OK) != 0)
	{
		LOGW("line : %d, codepages doesnot existed! Need copy!", __LINE__);
		str = "/system/samba/codepages/lowcase.dat " + codepages_path + ";";
		str += "cp /system/samba/codepages/upcase.dat " + codepages_path + ";";
		str += "cp /system/samba/codepages/valid.dat " + codepages_path;
		HiNSClient::NSSh(HI_NS_CMD_TYPE_CPM,(char *)str.c_str());
	}
	LOGE("Create SAMBA 4");
	if(access(cp850.c_str(), F_OK) != 0)
	{
		LOGW("line : %d, codepages doesnot existed! Need copy!", __LINE__);
		cp850 = "/system/samba/codepages/CP850.so " + charset_path + ";";
		cp850 += "cp /system/samba/codepages/CP437.so " + charset_path;
		HiNSClient::NSSh(HI_NS_CMD_TYPE_CPM,(char *)cp850.c_str());
	}
}

Samba::~Samba()
{

}
/**
 *	Create Samba Directory
 *	@param[in]			void
 *	@param[in|out]
 *	@return		    int
 *	@note
 */
int Samba::create_smbDir()
{
	DIR *pDir;
	char buf[MAX_SIZE] = {0};
	if((pDir = opendir(SMB_PATH.c_str())) == NULL)
	{
		LOGI("DIR does not existed!");
		sprintf(buf, "mkdir %s", SMB_PATH.c_str());
		if((system(buf)) != 0)
		{
		LOGE("mkdir '/data/app/samba' fail!!");
		return ERROR;
		}
		LOGI("mkdir success! mkdir = %s", buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/var").c_str());
		system(buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/var/tmp").c_str());
		system(buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/var/locks").c_str());
		system(buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/private").c_str());
		system(buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/lib").c_str());
		system(buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/lib/codepages").c_str());
		system(buf);
		sprintf(buf, "mkdir %s", (SMB_PATH + "/lib/charset").c_str());
		system(buf);
		LOGI("SMB Directory Create Success!");
	}
	else {
		closedir(pDir);
		LOGI("SMB Directory has Existed!");
	}
	return NOMAL_RETURN;
}

/**
 *	Create Samba's smb.conf in /data/data/samba/lib/smb.conf
 *	@param[in]			void
 *	@param[in|out]
 *	@return		    int
 *	@note
 */
int Samba::create_smbConf()
{
	LOGI("Create smb.conf");
	if(create_smbDir())
	{
		LOGE("Create smb directory!");
		return ERROR;
	}
	if(access(SMBCONF_PATH.c_str(), R_OK) != 0)
	{
		int fd;
		fd = open(SMBCONF_PATH.c_str(), O_RDWR | O_CREAT, S_IRWXU | S_IRWXG | S_IRWXO);
		if(fd < 0)
		{
		LOGE("Create SMBCONF fail!");
		return ERROR;
		}
		const char *str[] = {
		"#------------smb.conf-----------#\n",
		"[global]\n",
		"\tworkgroup = WORKGROUP\n",
		"\tserver string = Hi3716C\n",
		"\tsecurity = user\n",
		"\tencrypt passwords = yes\n",
		"\tusername map = /data/app/samba/lib/smbusers\n",
		"\twins support = yes\n",
		"\tunix extensions = no\n",
		"\tenable core files = no\n",
		"\t# lanman auth = yes\n",
		"\tcase sensitive = yes\n",
		"\tdisplay charset = UTF-8\n",
		"\tunix charset = UTF-8\n",
		"\tdos charset = UTF-8\n",
		"\tmax log size	= 100\n",
		"\tprintcap name = /dev/null\n",
		"\tload printers = no\n",
		//"\tsocket options = TCP_NODELAY IPTOS_LOWDELAY SO_SNDBUF=12288 SO_RCVBUF=12288\n",
		"\tsocket options = TCP_NODELAY IPTOS_LOWDELAY SO_SNDBUF=16384 SO_RCVBUF=32768\n",
		"\tread raw = yes\n",
		"\twrite raw = yes\n",
		"\toplocks = yes\n",
		"\tmax xmit = 65535\n",
		"\tdead time = 15\n",
		"\tgetwd cache = yes\n",
		"\tdns proxy = no\n",
		"\tuse sendfile = yes\n",
		"\tlpq cache time = 30\n",
		"\tclient NTLMv2 auth = yes",
		"\t# guest account = root\n",
		"\t# passdb backend = smbpasswd\n",
		"\t# domain logons = no\n",
		"\t;netbios name = hisi\n",
		"\t#  Networking configuration options  #\n",
		"\t; hosts allow = 192.168.*\n",
		"\t; hosts deny = 192.168.*\n",
		"\t; interfaces = 192.168.*/255.255.255.0\n",
		"\t; bind interfaces only = yes\n",
		"\tmax connections = 15\n",
		"\twide links = yes",
		NULL
		};
		int i = 0;
		for( ; i < SMBCONF; i++)
		{
		if(str[i] == NULL) break;
		write(fd, str[i], strlen(str[i]));
		}
		close(fd);
	}
	else LOGI("No need to create smb.conf,it has existed!");
	return NOMAL_RETURN;
}

void Samba::cleanup(int whichfile)
{
	std::string str;
	const std::string ip_path = "/data/app/samba/var/ip";
	FILE *stream, *stream_ip;
	if(access(ip_path.c_str(), R_OK) != 0)
	{
		str = "touch " + ip_path;
		system(str.c_str());
	}
	std::string ip;
	int sock;
	struct sockaddr_in sin;
	struct ifreq ifr;
	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock == -1)
	{
		ip = "";
	}
	strncpy(ifr.ifr_name, "eth0", sizeof(ifr.ifr_name));
	if (ioctl(sock, SIOCGIFADDR, &ifr) < 0)
	{
		ip = "";
	}
	memcpy(&sin, &ifr.ifr_addr, sizeof(sin));
	close(sock);
	ip=inet_ntoa(sin.sin_addr);

	std::string echo_ip;
	if(ip.empty())
	{
		ip = str;
		echo_ip = "echo \"" + ip + "\" >" + ip_path;
		LOGI("line : %d, echo_ip = %s",__LINE__, echo_ip.c_str());
		system(echo_ip.c_str());
	}
	LOGI("line : %d, ip = %s, str = %s", __LINE__, ip.c_str(), str.c_str());
	if((whichfile == SMBTREE || whichfile == SMBSERVER))
	{
		str = "rm -r ";
		str += SMB_LOCKS + "/*";
		system(str.c_str());
		system("rm /data/app/samba/var/workgroup");
		echo_ip = "echo \"" + ip + "\" >" + ip_path;
		LOGI("line : %d, echo_ip = %s",__LINE__, echo_ip.c_str());
		system(echo_ip.c_str());
	}
}
