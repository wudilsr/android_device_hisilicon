/*********************************************************************************************************************
*  @file     Samba.h
*  @brief    define samba server interface file
*  @version  1.0
*  @date     20110601
**********************************************************************************************************************/


#ifndef SAMBA_H_
#define SAMBA_H_

/*		C		*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <fcntl.h>

/*		C++		*/
#include <string>
#include <vector>
#include <iostream>

#define ANDROID_SAMBA

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "------Samba_Interface--------"
/*		ANDROID		*/
#ifdef ANDROID_SAMBA
#include <android/log.h>
#define LOGV(...) __android_log_print(ANDROID_LOG_VERBOSE, LOG_TAG, __VA_ARGS__)
#define LOGD(...) __android_log_print(ANDROID_LOG_DEBUG , LOG_TAG, __VA_ARGS__)
#define LOGI(...) __android_log_print(ANDROID_LOG_INFO  , LOG_TAG, __VA_ARGS__)
#define LOGW(...) __android_log_print(ANDROID_LOG_WARN  , LOG_TAG, __VA_ARGS__)
#define LOGE(...) __android_log_print(ANDROID_LOG_ERROR  , LOG_TAG, __VA_ARGS__)
#else
/*		UBUNTU		*/
#define LOGI(str) printf("%s:\t%s\n", LOG_TAG, str)
#define LOGE(str) printf("%s:\t%s\n", LOG_TAG, str)
#define LOGW(str) printf("%s:\t%s\n", LOG_TAG, str)
#endif


/*	Base	Class	*/
class Samba
{

	protected:
		Samba();
		virtual ~Samba();
		virtual int create_smbDir();
		virtual int create_smbConf();
		virtual void cleanup(int whichfile);
	protected:
		std::string SMBD_PID;
		std::string NMBD_PID;
		std::string SMBUSERS_PATH;
		std::string SMBCONF_PATH;
		std::string SMB_PATH;
		std::string SMB_LOCKS;

	private:
		enum
		{
			HEAD_DOESNOT_EXIST = -11,
			HEAD_HAS_EXISTED = -10,
			ERROR = -1,
			NOMAL_RETURN = 0,
			SMBTREE = 0x02,
			SMBSERVER = 0x04,
			SMBCONF = 128,
			MAX_SIZE = 255,
		};

};

#endif /* SAMBA_H_ */
