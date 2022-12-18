package com.hisilicon.android.videoplayer.control;

import java.util.List;

import com.hisilicon.android.hibdinfo.HiBDInfo;
import com.hisilicon.android.videoplayer.utility.LogTool;

/**
 * BDInfo: get bluray info
 */
public class BDInfo
{
    private HiBDInfo mHiBDInfo;

    public BDInfo()
    {
        initVariable();
    }

    private void initVariable()
    {
        mHiBDInfo = new HiBDInfo();
    }

    /**
     * open bluray
     * @param pPath bluray path
     * @return 0 - success other - failure
     */
    public int openBluray(String pPath)
    {
        LogTool.d(pPath);
        return mHiBDInfo.openBluray(pPath);
    }

    /**
     * close bluray
     * @return 0 - success other - failure
     */
    public int closeBluray()
    {
        LogTool.d("");
        return mHiBDInfo.closeBluray();
    }

    /**
     * check disc info
     * @return 0 - is bluray other - is not bluray
     */
    public int checkDiscInfo()
    {
        LogTool.d("");
        return mHiBDInfo.checkDiscInfo();
    }

    /**
     * get title number
     * @return title number
     */
    public int getTitleNumber()
    {
        int _Number = mHiBDInfo.getTitleNumber();
        LogTool.d(String.valueOf(_Number));
        return _Number;
    }

    /**
     * get chapter number by title id
     * @param pTitleId title id
     * @return chapter number
     */
    public int getChapterNumberByTitleId(int pTitleId)
    {
        int _Number = mHiBDInfo.getChapterNumberByTitleId(pTitleId);
        LogTool.d(String.valueOf(_Number));
        return _Number;
    }

    /**
     * get playlist by title id
     * @param pTitleId title id
     * @return playlist
     */
    public int getPlaylistByTitleId(int pTitleId)
    {
        int _Playlist = mHiBDInfo.getPlaylistByTitleId(pTitleId);
        LogTool.d(String.valueOf(_Playlist));
        return _Playlist;
    }

    /**
     * get default playlist
     * @return playlist
     */
    public int getDefaultPlaylist()
    {
        int _Playlist = mHiBDInfo.getDefaultPlaylist();
        LogTool.d(String.valueOf(_Playlist));
        return _Playlist;
    }

    /**
     * get default title id
     * @return title id
     */
    public int getDefaultTitleId()
    {
        int _Id = mHiBDInfo.getDefaultTitleId();
        LogTool.d(String.valueOf(_Id));
        return _Id;
    }

    /**
     * get title id by playlist
     * @param pPlaylist playlist
     * @return title id
     */
    public int getTitleIdByPlaylist(int pPlaylist)
    {
        int _Id = mHiBDInfo.getTitleIdByPlaylist(pPlaylist);
        LogTool.d(String.valueOf(_Id));
        return _Id;
    }

    /**
     * get chapter position
     * @param pTitleId title id
     * @param pChapterId chapter id
     * @return chapter position
     */
    public int getChapterPosition(int pTitleId, int pChapterId)
    {
        int _Position = mHiBDInfo.getChapterPosition(pTitleId, pChapterId);
        LogTool.d(String.valueOf(_Position));
        return _Position;
    }

    /**
     * get current chapter id by title id and position
     * @param pTitleId title id
     * @param pPosition chapter position
     * @return chapter id
     */
    public int getCurChapterId(int pTitleId, int pPosition)
    {
        int _Id = mHiBDInfo.getCurChapterId(pTitleId, pPosition);
        LogTool.d(String.valueOf(pTitleId));
        return _Id;
    }

    /**
     * get duration by title id
     * @param pTitleId title id
     * @return duration
     */
    public int getDurationByTitleId(int pTitleId)
    {
        int _Duration = mHiBDInfo.getDurationByTitleId(pTitleId);
        LogTool.d(String.valueOf(_Duration));
        return _Duration;
    }

    /**
     * get subtitle language list
     * @deprecated
     * @return language list
     */
    public List<String> getSubtitleLanguageList()
    {
        LogTool.d("");
        return mHiBDInfo.getSubtitleLanguageList();
    }

    /**
     * get audio language list
     * @deprecated
     * @return language list
     */
    public List<String> getAudioTrackLanguageList()
    {
        LogTool.d("");
        return mHiBDInfo.getAudioTrackLanguageList();
    }

	public byte[] getPoster()
	{
		LogTool.d("");
		return mHiBDInfo.getPoster();
	}
}
