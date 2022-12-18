package com.hisilicon.android.hidvdinfo;

import java.util.ArrayList;
import java.util.List;

import android.os.Parcel;

/**
 * HiDVDInfo: get DVD info, Usage: openDVD->playback->closeDVD
 */
public class HiDVDInfo
{
    public static class DVDCommand
    {
        public static int DVD_CMD_OPEN_DVD = 1051;

        public static int DVD_CMD_CLOSE_DVD = 1052;

        public static int DVD_CMD_CHECK_DVD_DISC_INFO = 1053;

        public static int DVD_CMD_GET_DVD_TITLE_NUMBER = 1061;

        public static int DVD_CMD_GET_DVD_CHAPTER_NUMBER = 1062;

        public static int DVD_CMD_GET_DVD_DEFAULT_TITLE = 1064;

        public static int DVD_CMD_GET_DVD_SUBPICTURE_LANGUAGE = 1066;

        public static int DVD_CMD_GET_DVD_AUDIO_TRACK_LANGUAGE = 1067;

        public static int DVD_CMD_GET_CUR_DVD_CHAPTER = 1068;

        public static int DVD_CMD_GET_DVD_DURATION = 1069;

        public static int DVD_CMD_GET_DVD_CHAPTER_DURATION = 1070;
    }

    static
    {
        System.loadLibrary("dvdinfo_jni");
    }

    private native final int native_invoke(Parcel pRequest, Parcel pReply);

    /**
     * do invoke command
     * @param pRequest request
     * @param pReply reply
     * @return 0 - success other - failure
     */
    public synchronized int invoke(Parcel pRequest, Parcel pReply)
    {
        pRequest.setDataPosition(0);

        int _Ret = native_invoke(pRequest, pReply);
        pReply.setDataPosition(0);
        return _Ret;
    }

    /**
     * open dvd
     * @param pPath dvd path
     * @return 0 - success other - failure
     */
    public int openDVD(String pPath)
    {
        return excuteCommand(DVDCommand.DVD_CMD_OPEN_DVD, pPath);
    }

    /**
     * close dvd
     * @return 0 - success other - failure
     */
    public int closeDVD()
    {
        return excuteCommand(DVDCommand.DVD_CMD_CLOSE_DVD);
    }

    /**
     * check disc info
     * @return 0 - is DVD Video, other - not DVD Video
     */
    public int checkDiscInfo()
    {
        return excuteCommand(DVDCommand.DVD_CMD_CHECK_DVD_DISC_INFO, true);
    }

    /**
     * get title number
     * @return title number
     */
    public int getTitleNumber()
    {
        return excuteCommand(DVDCommand.DVD_CMD_GET_DVD_TITLE_NUMBER, true);
    }

    /**
     * get chapter number by title id
     * @param pTitleId title id
     * @return chapter number
     */
    public int getChapterNumberByTitleId(int pTitleId)
    {
        return excuteCommand(DVDCommand.DVD_CMD_GET_DVD_CHAPTER_NUMBER, pTitleId, true);
    }

    /**
     * get default title id
     * @return title id
     */
    public int getDefaultTitleId()
    {
        return excuteCommand(DVDCommand.DVD_CMD_GET_DVD_DEFAULT_TITLE, true);
    }

    /**
     * get current chapter id by title id and position
     * @param pTitleId title id
     * @param pPosition chapter position
     * @return chapter id
     */
    public int getCurChapterId(int pTitleId, int pPosition)
    {
        return excuteCommand(DVDCommand.DVD_CMD_GET_CUR_DVD_CHAPTER, pTitleId, pPosition, true);
    }

    /**
     * get duration by title id
     * @param pTitleId title id
     * @return duration
     */
    public int getDurationByTitleId(int pTitleId)
    {
        return excuteCommand(DVDCommand.DVD_CMD_GET_DVD_DURATION, pTitleId, true);
    }

    /**
     * get chapter position
     * @param pTitleId title id
     * @param pChapterId chapter id
     * @return chapter position
     */
    public int getChapterPosition(int pTitleId, int pChapterId)
    {
        return excuteCommand(DVDCommand.DVD_CMD_GET_DVD_CHAPTER_DURATION, pTitleId, pChapterId, true);
    }



    /**
     * get subtitle language list
     * @deprecated
     * @return language list
     */
    public List<String> getSubtitleLanguageList()
    {
        Parcel _Request = Parcel.obtain();
        Parcel _Reply = Parcel.obtain();
        List<String> _LanguageList = new ArrayList<String>();

        _Request.writeInt(DVDCommand.DVD_CMD_GET_DVD_SUBPICTURE_LANGUAGE);

        if (invoke(_Request, _Reply) != 0)
        {
            _Request.recycle();
            _Reply.recycle();
            return null;
        }

        // for get
        _Reply.readInt();
        int _SubtitleNum = _Reply.readInt();
        String _Language = "";

        for (int i = 0; i < _SubtitleNum; i++)
        {
            _Language = _Reply.readString();
            if (_Language.equals(""))
            {
                _Language = "und";
            }
            _LanguageList.add(_Language);
        }

        _Request.recycle();
        _Reply.recycle();

        return _LanguageList;
    }

    /**
     * get audio language list
     * @deprecated
     * @return language list
     */
    public List<String> getAudioTrackLanguageList()
    {
        Parcel _Request = Parcel.obtain();
        Parcel _Reply = Parcel.obtain();
        List<String> _LanguageList = new ArrayList<String>();

        _Request.writeInt(DVDCommand.DVD_CMD_GET_DVD_AUDIO_TRACK_LANGUAGE);

        if (invoke(_Request, _Reply) != 0)
        {
            _Request.recycle();
            _Reply.recycle();
            return null;
        }

        // for get
        _Reply.readInt();
        int _AudioTrackNum = _Reply.readInt();
        String _Language = "";

        for (int i = 0; i < _AudioTrackNum; i++)
        {
            _Language = _Reply.readString();
            if (_Language.equals(""))
            {
                _Language = "und";
            }
            _LanguageList.add(_Language);
        }

        _Request.recycle();
        _Reply.recycle();

        return _LanguageList;
    }

    private int excuteCommand(int pCmdId, boolean pIsGet)
    {
        Parcel _Request = Parcel.obtain();
        Parcel _Reply = Parcel.obtain();
        _Request.setDataPosition(0);
        _Request.writeInt(pCmdId);

        if (invoke(_Request, _Reply) != 0)
        {
            _Request.recycle();
            _Reply.recycle();
            return -1;
        }

        if (pIsGet)
        {
            _Reply.readInt();
        }

        int _Result = _Reply.readInt();

        _Request.recycle();
        _Reply.recycle();

        return _Result;
    }

    private int excuteCommand(int pCmdId, int pArg1, boolean pIsGet)
    {
        Parcel _Request = Parcel.obtain();
        Parcel _Reply = Parcel.obtain();
        _Request.setDataPosition(0);
        _Request.writeInt(pCmdId);
        _Request.writeInt(pArg1);

        if (invoke(_Request, _Reply) != 0)
        {
            _Request.recycle();
            _Reply.recycle();
            return -1;
        }

        if (pIsGet)
        {
            _Reply.readInt();
        }

        int _Result = _Reply.readInt();

        _Request.recycle();
        _Reply.recycle();

        return _Result;
    }

    private int excuteCommand(int pCmdId, String pArg1, boolean pIsGet)
    {
        Parcel _Request = Parcel.obtain();
        Parcel _Reply = Parcel.obtain();
        _Request.setDataPosition(0);
        _Request.writeInt(pCmdId);
        _Request.writeString(pArg1);

        if (invoke(_Request, _Reply) != 0)
        {
            _Request.recycle();
            _Reply.recycle();
            return -1;
        }

        if (pIsGet)
        {
            _Reply.readInt();
        }

        int _Result = _Reply.readInt();

        _Request.recycle();
        _Reply.recycle();

        return _Result;
    }

    private int excuteCommand(int pCmdId, int pArg1, int pArg2, boolean pIsGet)
    {
        Parcel _Request = Parcel.obtain();
        Parcel _Reply = Parcel.obtain();
        _Request.setDataPosition(0);
        _Request.writeInt(pCmdId);
        _Request.writeInt(pArg1);
        _Request.writeInt(pArg2);

        if (invoke(_Request, _Reply) != 0)
        {
            _Request.recycle();
            _Reply.recycle();
            return -1;
        }

        if (pIsGet)
        {
            _Reply.readInt();
        }

        int _Result = _Reply.readInt();

        _Request.recycle();
        _Reply.recycle();

        return _Result;
    }

    private int excuteCommand(int pCmdId)
    {
        return excuteCommand(pCmdId, false);
    }

    private int excuteCommand(int pCmdId, int pArg1)
    {
        return excuteCommand(pCmdId, pArg1, false);
    }

    private int excuteCommand(int pCmdId, String pArg1)
    {
        return excuteCommand(pCmdId, pArg1, false);
    }

    private int excuteCommand(int pCmdId, int pArg1, int pArg2)
    {
        return excuteCommand(pCmdId, pArg1, pArg2, false);
    }
}
