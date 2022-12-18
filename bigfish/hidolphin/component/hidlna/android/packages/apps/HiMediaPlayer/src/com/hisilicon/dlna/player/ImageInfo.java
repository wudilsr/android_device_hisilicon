package com.hisilicon.dlna.player;

public class ImageInfo
{
    private String name;
    private String resolution;
    private String mimeType;
    private String dateToken;

    public void setName(String name)
    {
        this.name = name;
    }

    public String getName()
    {
        return name;
    }

    public void setResolution(String resolution)
    {
        this.resolution = resolution;
    }

    public String getResolution()
    {
        return resolution;
    }

    public void setMimeType(String mimeType)
    {
        this.mimeType = mimeType;
    }

    public String getMimeType()
    {
        return mimeType;
    }

    public void setDateToken(String dateToken)
    {
        this.dateToken = dateToken;
    }

    public String getDateToken()
    {
        return dateToken;
    }
}
