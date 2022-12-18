package com.hisilicon.android.videoplayer.utility;

public class ShooterSubinfo
{
    private String Desc;
    private int Delay;
    private String Ext;
    private String Link;
    private String FileHash;

    public void setDesctribe(String mDesc)
    {
        Desc = mDesc;
    }

    public String getDesctribe()
    {
        return Desc;
    }

    public void setDelay(int mDelay)
    {
        Delay = mDelay;
    }

    public int getDelay()
    {
        return Delay;
    }

    public void setExt(String mExt)
    {
        Ext = mExt;
    }

    public String getExt()
    {
        return Ext;
    }

    public void setLink(String mLink)
    {
        Link = mLink;
    }

    public String getLink()
    {
        return Link;
    }

    public void setFileHash(String mFileHash)
    {
        FileHash = mFileHash;
    }

    public String getFileHash()
    {
        return FileHash;
    }

    public void addFile(String mExt,String mLink)
    {
        Ext = mExt;
        Link = mLink;
    }
}