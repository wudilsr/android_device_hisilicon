/*********************************************************************************************************************
*  @file     smbtree.cpp
*  @brief    smbtree is here, for getting server pc and pc's directory
*  @version  1.0
*  @date     20110616
**********************************************************************************************************************/


/*	    C		*/
#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <string.h>

/*	    C++		*/
#include <iostream>
#include <vector>
#include <string>

#include <sys/select.h>
/* 		According to earlier standards 		*/
#include <sys/time.h>
#include <sys/types.h>

#include "Samba.h"

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "smbtree"

#ifdef ANDROID_SAMBA
/*		ANDROID		*/
#define NON_GLOBAL_SEARCH
#include "jni.h"
#include "JNIHelp.h"
#include <android_runtime/AndroidRuntime.h>

#ifdef NONUSE_SMBCLIENT
#undef NONUSE_SMBCLIENT
#endif

#else
/*		UBUNTU		*/
#define LOGI(str) printf("%s:\t%s\n", LOG_TAG, str)
#define LOGE(str) printf("%s:\t%s\n", LOG_TAG, str)
#define LOGW(str) printf("%s:\t%s\n", LOG_TAG, str)
#endif

/*	 	class smbtree		*/
class smbtree : public Samba
{
    public:
        /*		for jni , no para get server PC		*/
        static const char * getPara();
        /*		for jni , one para get server PC's share path		*/
        static const char * getPara(const char *pc, const char *user = NULL, const char *passwd = NULL);
    private:
        /*		NOTICE : You can not create class smbtree's object!		*/
        smbtree();
        virtual ~smbtree();
        static std::string getIp(const char *pc);
        static int getWorkgroups();
        /**
         *	for time up
         *	@param[in]			int args
         *	@param[in|out]
         *	@return		   int 0 or -1
         *	@note		    	inline static function
         */
        inline static void handler(int args)
        {
            alarmNum = true;
            LOGI("%d : TIME is up!", __LINE__);
        }

        /**
         *	for find char
         *	@param[in]			const char *buf, const char argv
         *	@param[in|out]
         *	@return		    int 0 or -1
         *	@note 				inline static function
         */
        inline static int findChar(const char *buf, const char argv)
        {
            int num = 0;
            if (!buf) return ERROR;
            for(unsigned int i = 0; i < strlen(buf) + 1; i++)
            {
                if(buf[i] == argv)
                    num ++;
            }
            return num;
        }
        inline static void findChar(char *buf)
        {
            int num = 0;
            if(!buf) return;
            for(unsigned int i = 0; i < strlen(buf) + 1; i++)
            {
                if(buf[i] == '.')
                    num ++;
                if(num == 2)
                {
                    buf[i] = '\0';
                    break;
                }
            }
        }

        inline static const char * substr(const char *buf)
        {
            pcName.clear();
            for(unsigned int i = 0, j = 0; i < strlen(buf) + 1; i++)
            {
                if (buf[i] == '\t' && i == 0)
                    continue;
                if(buf[i] == ' ' || (i != 0 && buf[i] == '\t'))
                    break;
                pcName += buf[i];
                j ++;
            }
            return pcName.empty() ? "ERROR" : pcName.c_str();
        }

        inline static int strNum(const char *str)
        {
            int count = 0;
            for(std::vector<std::string>::iterator iter = allInfo.begin(); iter != allInfo.end(); iter ++)
            {
                if((*iter).find(str, 0) != std::string::npos)
                    count ++;
            }
            return count;
        }

        inline static std::string strtrim(std::string &str)
        {
            std::string r=str.erase(str.find_last_not_of(' ')+1);
            return r.erase(0,r.find_first_not_of(' '));
        }


        /**
         *	for replace char
         *	@param[in]			std::string &str, const char tab = '\t', const char lineFeed = '\n'
         *	@param[in|out]	std::string &str
         *	@return		    int 0 or -1
         *	@note 				inline static function
         */
        inline static int replaceChar(std::string &str, bool flag = false, const char tab = '\t', const char lineFeed = '\n')
        {
            int i = 0, j = 0;
            if(str.empty()) return ERROR;
            if(findChar(str.c_str(), '\\') == 3)
                for(std::string::iterator the_iterator = str.begin(); the_iterator != str.end(); the_iterator++)
                {
                    if(*the_iterator == lineFeed)
                        *the_iterator = '|';
                    if(*the_iterator == tab)
                    {
                        i ++;
                        if(i == 3)
                            retSharePath += ':|';
                        continue;
                    }
                    if(i == 2)
                        retSharePath += *the_iterator;
                }
            else
#ifdef NON_GLOBAL_SEARCH
                if (flag)
#endif
                {
                    for(std::string::iterator the_iterator = str.begin(); the_iterator != str.end(); the_iterator++)
                    {
                        if(*the_iterator == lineFeed)
                            *the_iterator = '|';
                        if(*the_iterator == tab)
                        {
                            j ++;
                            if(j == 2)
                                retServerPc += ':|';
                            continue;
                        }
                        if(j == 1)
                            retServerPc += *the_iterator;

                    }
                }
            return NORMAL_RETURN;
        }

        inline static char *find_last_of(char *str, const char *name = "Disk")
        {
            int len_name = strlen(name), end = strlen(str) - len_name;
            char *last_index = NULL;
            for(int i = 0; i <= end; ++i)
                if(!strncmp(name, str + i, len_name))
                    last_index = str +i;
            return last_index;
        }

    private:
        enum
        {
            ERROR = -1,
            NORMAL_RETURN = 0,
            ERROR_TIME = 15,
            SELECT_TIMEOUT = ERROR_TIME,
            WORK_GROUPS = 30,
            RESPOND_SERVER_OVERTIME = 90,
            MAX_SIZE =255,
        };
        static int errNum;
        static bool alarmNum;
        static std::vector<std::string> serverPc;
        static std::vector<std::string> allInfo;
        static std::vector<std::string> sharePath;
        static std::string retServerPc,retSharePath,ip,pcName;

    private:
        static smbtree *pTree;

};		/*		smbtree		*/

smbtree::smbtree()
{

}
smbtree::~smbtree()
{

}

/*		initialization		*/
bool smbtree::alarmNum = false;
int smbtree::errNum = smbtree::NORMAL_RETURN;
std::vector<std::string> smbtree::serverPc;
std::vector<std::string> smbtree::allInfo;
std::vector<std::string> smbtree::sharePath;
std::string smbtree::retServerPc;
std::string smbtree::retSharePath;
std::string smbtree::ip;
std::string smbtree::pcName;
smbtree *smbtree::pTree = NULL;

/**
 *	for get ip of server's pc
 *	@param[in]			const char *pc
 *	@param[in|out]
 *	@return		    std::string
 *	@note
 */
std::string smbtree::getIp(const char *pc)
{
    if(!pc)
    {
        LOGE("Argument is NULL!");
        return "NULL";
    }
    if(!ip.empty())
        ip.clear();
    FILE *fd;
    LOGI("%d : start getting IP", __LINE__);
    char buf[MAX_SIZE] = {0};
    sprintf(buf, "nmblookup %s", pc);
    fd = popen(buf, "r");
    if(fd == NULL)
    {
        LOGE("%d : popen fail", __LINE__);
        return "NULL";
    }
    char ip_prefix[MAX_SIZE] = {0};
    while(fgets(buf, sizeof(buf), fd) != NULL)
    {
        if(strstr(buf, "name_query failed to find name")){
            pclose(fd);
            return "ERROR";
        }
        if(strstr(buf, "querying"))
        {
            strcpy(ip_prefix, strstr(buf, "on") != NULL ? (strstr(buf, "on") + 3) : NULL);
            findChar(ip_prefix);
            continue;
        }
        if(strlen(ip_prefix) == 0)
            continue;
        if(strstr(buf, ip_prefix))
        {
            for(unsigned int i = 0; i < sizeof(buf); i++)
            {
                if(buf[i] == ' '){
                    pclose(fd);
                    return ip;
                }
                ip += buf[i];
            }
        }
    }
    pclose(fd);
    return ip;
}

int smbtree::getWorkgroups()
{
    FILE *stream, *stream_path;
    std::string workgroup[WORK_GROUPS], workgroup_in_file[WORK_GROUPS];
    char buf[MAX_SIZE] = {0};
    if( (stream = popen("smbtree -D -N", "r")) == NULL)
    {
        LOGE("line : %d, popen fail", __LINE__);
        return ERROR;
    }
    int i = 0;
    while((fgets(buf, sizeof(buf), stream)) != NULL)
    {
        if(strstr(buf, "init_iconv:") || strstr(buf, "session request")
                || strstr(buf, "failed ") || strstr(buf, "Receiving SMB")
                || strstr(buf, "timeout connecting") || strstr(buf, "Error connecting "))
            continue;

        if(strstr(buf, " ") == NULL)
        {
            workgroup[i ++] = buf;
        }
    }
    pclose(stream);
    std::string workgroup_path = "/data/app/samba/var/workgroup";
    if(access(workgroup_path.c_str(), R_OK) != 0)
    {
        std::string str = "touch " + workgroup_path;
        system(str.c_str());
    }
    workgroup_path = "cat /data/app/samba/var/workgroup";
    stream_path = popen(workgroup_path.c_str(), "r");
    i = 0;
    while((fgets(buf, sizeof(buf), stream_path)) != NULL)
    {
        if(strlen(buf) > 0)
        {
            workgroup_in_file[i ++] = buf;
        }
    }
    pclose(stream_path);
    i = 0;
    if(workgroup_in_file[0].empty())
    {
        while(i != WORK_GROUPS && !workgroup[i].empty())
        {
            std::string str = "echo ";
            std::size_t found = workgroup[i].find('\n',0);
            if (found!=std::string::npos)
                workgroup[i].erase(found, 1);
            found = workgroup[i].find('\t',0);
            if (found!=std::string::npos)
                workgroup[i].erase(found, 1);
            //workgroup[i].erase(workgroup[i].find('\n', 0), 1);
            //workgroup[i].erase(workgroup[i].find('\t', 0), 1);
            std::string workname = strtrim(workgroup[i]);

            if (!workname.empty())
            {
                str += "\"" + workgroup[i] + "\"";
                str += " >> ";
                str += "/data/app/samba/var/workgroup";
                LOGI("line :%d, write to file's workgroup = %s", __LINE__, str.c_str());
                system(str.c_str());
            }
            else
            {
                LOGV("line : %d, the group is null so not write workgroup = %s", __LINE__, str.c_str());
            }
            i ++;
        }
    }
    /*!	compare workgroups by smbtree searching and workgroups by file geting!	*/
    else
    {
        i = 0;
        for( ; i < WORK_GROUPS && !workgroup[i].empty(); i ++)
        {
            int j = 0;
            for( ; j < WORK_GROUPS && !workgroup_in_file[j].empty(); j ++)
            {
                if(workgroup_in_file[j] == workgroup[i])
                    break;
            }
            if(workgroup_in_file[j].empty() || j == WORK_GROUPS)
            {
                std::string str = "echo ";
                workgroup[i].erase(workgroup[i].find('\n', 0), 1);
                workgroup[i].erase(workgroup[i].find('\t', 0), 1);
                std::string workname = strtrim(workgroup[i]);

                if (!workname.empty())
                {
                    str += "\"" + workgroup[i] + "\"";
                    str += " >> ";
                    str += "/data/app/samba/var/workgroup";
                    LOGI("line : %d, write to file's workgroup = %s", __LINE__, str.c_str());
                    system(str.c_str());
                }
            }
        }
    }
    return NORMAL_RETURN;
}

/**
 *	for get Server PC
 *	@param[in]			void
 *	@param[in|out]
 *	@return		    const char *
 *	@note 				function reload
 */
const char *smbtree::getPara()
{
    LOGI("Beginning get Server's PC! We will need 1 min to get server's PC.");
    if(!pTree)
    {
        pTree = new smbtree();
        pTree -> cleanup(0x02);
        delete pTree;
        pTree = NULL;
    }
    signal(SIGALRM, handler);
    alarm(RESPOND_SERVER_OVERTIME);
    /********************************************************************************************************
Usage: [OPTION...]
-b, --broadcast                    Use broadcast instead of using the master browser
-D, --domains                      List only domains (workgroups) of tree
-S, --servers                      List domains(workgroups) and servers of tree

Help options:
-?, --help                         Show this help message
--usage                        Display brief usage message

Common samba options:
-d, --debuglevel=DEBUGLEVEL        Set debug level
-s, --configfile=CONFIGFILE        Use alternate configuration file
-l, --log-basename=LOGFILEBASE     Base name for log files
-V, --version                      Print version

Authentication options:
-U, --user=USERNAME                Set the network username
-N, --no-pass                      Don't ask for a password
-k, --kerberos                     Use kerberos (active directory) authentication
-A, --authentication-file=FILE     Get the credentials from a file
-S, --signing=on|off|required      Set the client signing state
-P, --machine-pass                 Use stored machine account password
-e, --encrypt                      Encrypt SMB transport (UNIX extended servers only)
-C, --use-ccache                   Use the winbind ccache for authentication
     *********************************************************************************************************/
    FILE *stream;
    LOGI("%d : start smbtree command", __LINE__);
    getWorkgroups();
    stream = popen("smbtree -S -N", "r");
    if(stream == NULL)
    {
        LOGE("%d : popen fail", __LINE__);
        return "ERROR";
    }

    if(!allInfo.empty()) allInfo.clear();
    if(!serverPc.empty()) serverPc.clear();
    if(!retServerPc.empty()) retServerPc.clear();
    alarmNum = false;
    errNum = 0;

    char buf[MAX_SIZE] = {0};
    /**
     *	@brief : prevent blocking, by adding "select" function.
     */
    int fd = fileno(stream);
    fd_set readfd;
    struct timeval timeout;
    int ret;
    while(true)
    {
        FD_ZERO(&readfd);
        FD_SET(fd, &readfd);
        timeout.tv_sec = SELECT_TIMEOUT;
        timeout.tv_usec = 0;
        ret = select(fd + 1, &readfd, NULL, NULL, &timeout);
        if(ret < 0)
        {
            LOGE("line : %d, Select < 0. While loop, select error.\n", __LINE__);
            return "ERROR";
        }
        else if(ret == 0 || errNum == ERROR_TIME || alarmNum)
        {
            LOGW("%d : alarmNum = %d. Time is up or ERROR is over count!", __LINE__, alarmNum);
            break;
        }
        else
        {
            if(fgets(buf, sizeof(buf), stream) != NULL)
            {
                LOGI("%d : Data begin getting server. Data = %s", __LINE__, buf);
                if(!strstr(buf, "\\"))
                    continue;

                /*		if PDF or IPC or ERROR or PRINT or OFFICE, filter them		*/
                if(strstr(buf, "Error") || strstr(buf, "failed to connect"))
                {
                    errNum += 1;
                    continue;
                }

                if(strstr(buf, "Printer Drivers") || strstr(buf, "PDF Printer") || strstr(buf, "Fax")
                        || strstr(buf, "IPC Service") || strstr(buf, "Microsoft XPS Document Writer"))
                    continue;

                allInfo.push_back(buf);
                if(findChar(buf, '\\') == 3)
                    continue;
                serverPc.push_back(buf);
            }
            else
            {
                LOGI("%d : data is geted. OK!", __LINE__);
                pclose(stream);
                break;
            }
        }
    }

    for(unsigned int i = 0; i < serverPc.size(); i ++)
    {
        bool flag = false;
#ifdef NON_GLOBAL_SEARCH
        /* 	According to finding 3 '\' i can find the path.	 */
        std::string pcNameforUI;
        pcNameforUI += substr(serverPc[i].c_str());
        if( strNum(pcNameforUI.c_str()) >= 1 )
            flag = true;
        LOGI("%d : PC name = %s", __LINE__, pcNameforUI.c_str());
#endif
        if(replaceChar(serverPc[i], flag))
        {
            LOGE("%d : Replace Char fail!", __LINE__);
            return "ERROR";
        }
    }
    alarm(0);
    if(!retServerPc.empty())
    {
        LOGI("%d : return success", __LINE__);
        return retServerPc.c_str();
    }
    else
    {
        LOGE("%d : return error", __LINE__);
        return "ERROR";
    }
}

const char *smbtree::getPara(const char *pc, const char *user, const char *passwd)
{
    if(!pTree)
    {
        pTree = new smbtree();
        delete pTree;
        pTree = NULL;
    }
    if(!retSharePath.empty()) retSharePath.clear();
#ifdef NONUSE_SMBCLIENT
    if(!sharePath.empty()) sharePath.clear();
    retSharePath = "ip:" + getIp(pc) + "|";
#endif

    char buf[MAX_SIZE] = {0};
    if(serverPc.empty() || allInfo.empty())
    {
        LOGW("Get Server's PC is empty!! Next we will need 1 min to reget server's PC.");
        getPara();
    }
#ifdef NONUSE_SMBCLIENT
    if(!findChar(pc, '\\'))
    {
        sprintf(buf, "\\\\%s\\", pc);
        LOGI("%d : buf = %s", __LINE__, buf);
    }
    else sprintf(buf, "%s", pc);
    bool temp = false;
    for(int i = 0; i < allInfo.size(); i++)
    {
        if(!temp)
            if(strstr((allInfo[i]).c_str(), buf))
            {
                temp = true;
            }
        if(temp && findChar((allInfo[i]).c_str(), '\\') == 3)
        {
            sharePath.push_back(allInfo[i]);
            LOGI("%d : share path = %s", __LINE__, allInfo[i].c_str());
        }
        if(temp && findChar(allInfo[i].c_str(), '\\') != 3)
            break;
    }
    for(int i = 0; i < sharePath.size(); i++)
    {
        if(replaceChar(sharePath[i]))
        {
            LOGE("Replace Char fail!");
            return "ERROR";
        }
    }
#else
    /**
     *	@brief : change and optimize searching mechanism.
     */
    std::string ip_address = getIp(pc);
    if(ip_address == "ERROR" || ip_address == "NULL")
    {
        LOGE("Get IP fail, Maybe Network Error.");
        return "ERROR";
    }
    std::string smbclient_no_pass, smbclient_use_pass;
    std::vector<std::string> disk_info;
    bool is_use_pass = true;
    if(strlen(user) == 0 || strlen(passwd) == 0)
        smbclient_no_pass += "smbclient -L " + ip_address + " -N";
    else
    {
        smbclient_use_pass += "smbclient -L " + ip_address + " -U";
        smbclient_use_pass += user;
        smbclient_use_pass += "%";
        smbclient_use_pass += passwd;
    }
    LOGI("line : %d, smbclient str = %s", __LINE__ ,
            !smbclient_no_pass.empty() ? smbclient_no_pass.c_str() : smbclient_use_pass.c_str());
    FILE *stream;
    if( (stream = popen(!smbclient_no_pass.empty() ? smbclient_no_pass.c_str() : smbclient_use_pass.c_str(), "r")) == NULL )
    {
        LOGE("line : %d, popen fail.", __LINE__);
        return "ERROR";
    }
    while(fgets(buf, sizeof(buf), stream) != NULL)
    {
        LOGI("line : %d, smbclient get string = %s", __LINE__, buf);
        if(strstr(buf, "NT_STATUS_UNSUCCESSFUL") != NULL)
        {
            LOGE("line : %d, smbclient connection fail!", __LINE__);
            pclose(stream);
            return "NT_STATUS_UNSUCCESSFUL";
        }
        if(strstr(buf, "Error connecting") || strstr(buf, "Error NT_STATUS_HOST_UNREACHABLE"))
        {
            pclose(stream);
            return "ERROR";
        }
        if((is_use_pass && strstr(buf, "NT_STATUS_ACCESS_DENIED") != NULL) || (is_use_pass && strstr(buf, "NT_STATUS_ACCOUNT_DISABLED") != NULL))
        {
            LOGW("line : %d, Access Server denied! If starting use! Please enter user and password!", __LINE__);
            pclose(stream);
            return "NT_STATUS_ACCESS_DENIED";
        }
        if(is_use_pass && (strstr(buf, "NT_STATUS_LOGON_FAILURE")) != NULL)
        {
            LOGE("line : %d, smbclient logon failure!", __LINE__);
            pclose(stream);
            return "NT_STATUS_LOGON_FAILURE";
        }
        if(strstr(buf, "$") != NULL)
            continue;
        if(strstr(buf, "Disk") != NULL)
        {
            LOGI("line : %d, Disk = %s", __LINE__, buf);
            disk_info.push_back(buf);
        }
    }
    pclose(stream);
    retSharePath = "ip:" + ip_address + "|";
    for(std::vector<std::string>::iterator it = disk_info.begin(); it != disk_info.end(); it ++ )
    {
        *find_last_of(const_cast<char *>((*it).c_str()), "Disk") = '\0';
        char *q = const_cast<char *>((*it).c_str()) + 1;
        char *p = q;
        for(p = q + strlen(q) - 1; p != NULL; --p)
        {
            if(*p != ' ')
                break;
            if(*p == ' ')
                *p = '\0';
        }
        retSharePath += q;
        retSharePath += '|';
    }
#endif
    if(!retSharePath.empty())
    {
        LOGI("%d : return success, PC's share path = %s", __LINE__, retSharePath.c_str());
        return retSharePath.c_str();
    }
    else {
        LOGE("%d : return error!", __LINE__);
        return "ERROR";
    }
}


/*
 * Class:     com_explorer_jni_SambaTreeNative
 * Method:    getWorkgroups
 * Signature: ()Ljava/lang/String;
 */
    JNIEXPORT jstring JNICALL Java_com_hisilicon_android_SambaTreeNative_getWorkgroups
(JNIEnv *env, jobject jobj)
{
    const char *workgroups = smbtree::getPara();
    jstring jWorkgroups = env->NewStringUTF(workgroups);
    LOGI("%s", workgroups);
    return jWorkgroups;
}


/*
 * Class:     com_explorer_jni_SambaTreeNative
 * Method:    getDetailsBy
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
    JNIEXPORT jstring JNICALL Java_com_hisilicon_android_SambaTreeNative_getDetailsBy
(JNIEnv *env, jobject jobj, jstring pc_server, jstring server_user, jstring server_passwd)
{
    const char *pc = env->GetStringUTFChars(pc_server, NULL);
    const char *user = env->GetStringUTFChars(server_user, NULL);
    const char *passwd = env->GetStringUTFChars(server_passwd, NULL);
    const char *details = smbtree::getPara(pc, user, passwd);
    jstring jDetails = env->NewStringUTF(details);
    return jDetails;
}

static const JNINativeMethod g_methods[] =
{
    {"getWorkgroups", "()Ljava/lang/String;", (void*)Java_com_hisilicon_android_SambaTreeNative_getWorkgroups},
    {"getDetailsBy", "(Ljava/lang/String;Ljava/lang/String;Ljava/lang/String;)Ljava/lang/String;", (void*)Java_com_hisilicon_android_SambaTreeNative_getDetailsBy},
};

int register_com_explorer_jni_SambaTreeNative(JNIEnv* env) {

    jclass clazz;
    clazz = env->FindClass("com/hisilicon/android/netshare/SambaTreeNative");
    if (clazz == NULL)
        return JNI_FALSE;
    if (env->RegisterNatives(clazz, g_methods, NELEM(g_methods)) < 0)
        return JNI_FALSE;
    return JNI_TRUE;
}
