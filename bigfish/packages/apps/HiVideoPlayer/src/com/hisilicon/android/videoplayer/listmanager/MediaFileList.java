package com.hisilicon.android.videoplayer.listmanager;

import java.util.List;

import android.os.Parcelable;

import com.hisilicon.android.videoplayer.activity.VideoModel;

public abstract class MediaFileList implements Parcelable
{
    private int id;

    public int getId()
    {
        return id;
    }

    public void setId(int id)
    {
        this.id = id;
    }

    public abstract VideoModel getPreVideoInfo(List < VideoModel > list);

    public abstract VideoModel getNextVideoInfo(List < VideoModel > list);

    public abstract VideoModel getNextVideoInfo_NoCycle(List < VideoModel > list);

    public abstract VideoModel getRandomVideoInfo(List < VideoModel > list);

    public abstract VideoModel getCurrVideoInfo();
}
