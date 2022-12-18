package com.hisilicon.android.videoplayer.model;

import java.io.Serializable;
import java.util.List;

public class ModelDVDInfo implements Serializable
{
    private static final long serialVersionUID = -578884547250348258L;

    private String mPath;

    private String mDVDISOPath;

    private boolean mIsNetworkFile;

    private String mMovieName;

    private int mTitleNumber;

    private int mChapterNumber;

    private int mSubtitleNumber;

    private int mAudioTrackNumber;

    private int mChapterPosition;

    private int mSelectTitleId;

    private int mSelectChapterId = 0;

    private int mSelectPlaylist;

    private int mSelectSubtitleId = 0;

    private int mSelectAudioTrackId = 0;

    private List<String> mSubtitleLanguageList;

    private List<String> mExtraSubtitleList;

    private List<String> mAudioTrackLanguageList;

    private List<String> mAudioFormatList;

    private List<String> mAudioSampleRateList;

    private List<String> mAudioChannelList;

    private String mVideoFormat;

    private String mVideoFps;

    private boolean mUsePosterCache;

    private List<Integer> mChapterPositionList;

    public String getPath()
    {
        return mPath;
    }

    public void setPath(String pPath)
    {
        mPath = pPath;
    }

    public String getDVDISOPath()
    {
        return mDVDISOPath;
    }

    public void setDVDISOPath(String pDVDISOPath)
    {
        mDVDISOPath = pDVDISOPath;
    }

    public boolean isNetworkFile()
    {
        return mIsNetworkFile;
    }

    public void setNetworkFile(boolean pIsNetworkFile)
    {
        mIsNetworkFile = pIsNetworkFile;
    }

    public String getMovieName()
    {
        return mMovieName;
    }

    public void setPosterCache(boolean pUsePosterCache)
    {
        mUsePosterCache = pUsePosterCache;
    }

    public boolean getPosterCache()
    {
        return mUsePosterCache;
    }

    public void setMovieName(String pMovieName)
    {
        mMovieName = pMovieName;
    }

    public int getTitleNumber()
    {
        return mTitleNumber;
    }

    public void setTitleNumber(int pTitleNumber)
    {
        mTitleNumber = pTitleNumber;
    }

    public int getChapterNumber()
    {
        return mChapterNumber;
    }

    public void setChapterNumber(int pChapterNumber)
    {
        mChapterNumber = pChapterNumber;
    }

    public int getSubtitleNumber()
    {
        return mSubtitleNumber;
    }

    public void setSubtitleNumber(int pSubtitleNumber)
    {
        mSubtitleNumber = pSubtitleNumber;
    }

    public int getAudioTrackNumber()
    {
        return mAudioTrackNumber;
    }

    public void setAudioTrackNumber(int pAudioTrackNumber)
    {
        mAudioTrackNumber = pAudioTrackNumber;
    }

    public int getChapterPosition()
    {
        return mChapterPosition;
    }

    public void setChapterPosition(int pChapterPosition)
    {
        mChapterPosition = pChapterPosition;
    }

    public int getSelectTitleId()
    {
        return mSelectTitleId;
    }

    public void setSelectTitleId(int pSelectTitleId)
    {
        mSelectTitleId = pSelectTitleId;
    }

    public int getSelectChapterId()
    {
        return mSelectChapterId;
    }

    public void setSelectChapterId(int pSelectChapterId)
    {
        mSelectChapterId = pSelectChapterId;
    }

    public int getSelectPlaylist()
    {
        return mSelectPlaylist;
    }

    public void setSelectPlaylist(int pSelectPlaylist)
    {
        mSelectPlaylist = pSelectPlaylist;
    }

    public int getSelectSubtitleId()
    {
        return mSelectSubtitleId;
    }

    public void setSelectSubtitleId(int pSelectSubtitleId)
    {
        mSelectSubtitleId = pSelectSubtitleId;
    }

    public int getSelectAudioTrackId()
    {
        return mSelectAudioTrackId;
    }

    public void setSelectAudioTrackId(int pSelectAudioTrackId)
    {
        mSelectAudioTrackId = pSelectAudioTrackId;
    }

    public List<String> getSubtitleLanguageList()
    {
        return mSubtitleLanguageList;
    }

    public void setSubtitleLanguageList(List<String> pSubtitleLanguageList)
    {
        mSubtitleLanguageList = pSubtitleLanguageList;
    }

    public List<String> getExtraSubtitleList()
    {
        return mExtraSubtitleList;
    }

    public void setExtraSubtitleList(List<String> pExtraSubtitleList)
    {
        mExtraSubtitleList = pExtraSubtitleList;
    }

    public List<String> getAudioTrackLanguageList()
    {
        return mAudioTrackLanguageList;
    }

    public void setAudioTrackLanguageList(List<String> pAudioTrackLanguageList)
    {
        mAudioTrackLanguageList = pAudioTrackLanguageList;
    }

    public List<String> getAudioFormatList()
    {
        return mAudioFormatList;
    }

    public void setAudioFormatList(List<String> pAudioFormatList)
    {
        mAudioFormatList = pAudioFormatList;
    }

    public List<String> getAudioSampleRateList()
    {
        return mAudioSampleRateList;
    }

    public void setAudioSampleRateList(List<String> pAudioSampleRateList)
    {
        mAudioSampleRateList = pAudioSampleRateList;
    }

    public List<String> getAudioChannelList()
    {
        return mAudioChannelList;
    }

    public void setAudioChannelList(List<String> pAudioChannelList)
    {
        mAudioChannelList = pAudioChannelList;
    }

    public String getVideoFormat()
    {
        return mVideoFormat;
    }

    public void setVideoFormat(String pVideoFormat)
    {
        mVideoFormat = pVideoFormat;
    }

    public String getVideoFps()
    {
        return mVideoFps;
    }

    public void setVideoFps(String pVideoFps)
    {
        mVideoFps = pVideoFps;
    }

    public void setChapterPositionList(List<Integer> pChapterPositionList)
    {
        mChapterPositionList = pChapterPositionList;
    }

    public List<Integer> getChapterPositionList()
    {
        return mChapterPositionList;
    }
}
