package com.hisilicon.android.videoplayer.listmanager;

import java.io.File;
import java.util.List;

import android.os.Parcel;
import android.os.Parcelable;
import android.util.Log;

import com.hisilicon.android.videoplayer.activity.MediaFileListService;
import com.hisilicon.android.videoplayer.activity.VideoActivity;
import com.hisilicon.android.videoplayer.activity.VideoModel;
import com.hisilicon.android.videoplayer.util.Constants;

public class FMMediaFileList extends MediaFileList
{
    private String currPath = null;
    private String currName = null;
    private MediaFileListService mediaFileListService = null;

    /*public FMMediaFileList(String currPath)
    {
        this.currPath = currPath;
        setId(Constants.FROMFILEM);
    }*/
    public FMMediaFileList(String path,String name)
    {
        this.currPath = path;
        this.currName = name;
        setId(Constants.FROMFILEM);
    }

    @Override
    public VideoModel getCurrVideoInfo()
    {
        File file = new File(this.currPath);
        VideoModel model = new VideoModel();

        model.setPath(currPath);
        model.setTitle(currName);
        model.setSize(file.length());
        return model;
    }

    @Override
    public VideoModel getNextVideoInfo(List < VideoModel > list)
    {
        checkService();
        return mediaFileListService.getVideoInfo(1);
    }

    @Override
    public VideoModel getNextVideoInfo_NoCycle(List < VideoModel > list)
    {
        checkService();
        return mediaFileListService.getVideoInfo(4);
    }

    @Override
    public VideoModel getPreVideoInfo(List < VideoModel > list)
    {
        checkService();
        return mediaFileListService.getVideoInfo(2);
    }

    @Override
    public VideoModel getRandomVideoInfo(List < VideoModel > list)
    {
        checkService();
        return mediaFileListService.getVideoInfo(3);
    }

    private void checkService()
    {
        if (mediaFileListService == null)
        {
            mediaFileListService = VideoActivity.mediaFileListService;
        }
    }

    public int describeContents()
    {
        return 0;
    }

    public void writeToParcel(Parcel arg0, int arg1)
    {
        arg0.writeString(currPath);
        arg0.writeString(currName);
    }

    public static final Parcelable.Creator <FMMediaFileList> CREATOR = new Creator <FMMediaFileList>()
    {
        public FMMediaFileList createFromParcel(Parcel arg0)
        {
            String path = arg0.readString();
            String name = arg0.readString();
            FMMediaFileList r = new FMMediaFileList(path,name);

            return r;
        }

        public FMMediaFileList[] newArray(int arg0)
        {
            return new FMMediaFileList[arg0];
        }
    };
}
