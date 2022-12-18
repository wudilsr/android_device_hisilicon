// HiBDInfo.h: interface for the HiBDInfo class.
//
//////////////////////////////////////////////////////////////////////
#ifndef _ANDROID_HIBDINFO_H_
#define _ANDROID_HIBDINFO_H_

#include "bluray.h"
#include "clpi_data.h"
#include <binder/Parcel.h>
#include <utils/threads.h>

#define ANDROID_VERSION_4_0
// #define ANDROID_VERSION_2_2

using namespace android;

class HiBDInfo
{
public:
    HiBDInfo();
    virtual ~HiBDInfo();

    int invoke(const Parcel & p_request, Parcel * p_reply);

    int openBluray(const char * p_bdPath);
    int closeBluray();
    int checkDiscInfo();
    int getTitleNumber();
    int getChapterNumberByTitleId(int p_titleId);
    int getPlaylistByTitleId(int p_titleId);
    int getDefaultPlaylist();
    int getDefaultTitleId();
    int getTitleIdByPlaylist(int p_playlist);
    int getChapterPosition(int p_titleId, int p_chapterId);
    int getCurChapterId(int p_titleId, int p_position);
    int getDurationByTitleId(int p_titleId);
    int checkBluray3D();
    int getPoster(char** pBuffer, int* pSize);
    int freePoster();

    static int checkDiscInfo(const char * p_bdPath);

private:
    BLURAY *    m_bd;
    int         titleNumber;
    Mutex       mLock;
};


#endif // !defined(_ANDROID_HIBDINFO_H_)
