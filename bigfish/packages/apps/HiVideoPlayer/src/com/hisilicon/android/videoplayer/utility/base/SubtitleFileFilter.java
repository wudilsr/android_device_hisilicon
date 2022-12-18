package com.hisilicon.android.videoplayer.utility.base;

import java.io.File;

import com.hisilicon.android.videoplayer.utility.FileTool;

public class SubtitleFileFilter implements java.io.FileFilter
{
    private static final String MIME_SUBTITLE = "srt,ssa,sub,ass,idx";

    public boolean accept(File pFile)
    {
        if (MIME_SUBTITLE.contains(FileTool.getExtension(pFile)))
        {
            return true;
        }
        return false;
    }
}
