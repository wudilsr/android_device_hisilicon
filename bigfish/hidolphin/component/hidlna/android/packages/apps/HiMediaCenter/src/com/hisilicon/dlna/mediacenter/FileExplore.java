package com.hisilicon.dlna.mediacenter;

import java.util.ArrayList;
import java.util.List;

import com.hisilicon.dlna.file.AbstractFile;
import com.hisilicon.dlna.file.TopLevel;

public class FileExplore
{
    private static final String TAG = "FileExplore";
    private AbstractExplore explore;
    private List<RootItem> rootList;

    public void initExplore(AbstractExplore explore)
    {
        this.explore = explore;
    }

    public void unInitExplore()
    {
        this.explore = null;
    }

    public AbstractExplore getExplore()
    {
        return explore;
    }

    public Location getLocation()
    {
        if (explore == null)
        {
            return Location.ROOT;
        }
        return explore.getLocation();
    }

    public FileExplore()
    {
        rootList = new ArrayList<RootItem>();
    }

    public List<RootItem> getRootList()
    {
        if (rootList.size() == 0)
        {
            rootList.add(RootItem.UPNP);
        }
        return rootList;
    }

    public void updateTopList()
    {
        if (explore != null)
        {
            explore.updateTopList();
        }
    }

    public void gotoTop(TopLevel device)
    {
        if (explore != null)
        {
            explore.gotoTop(device);
        }
    }

    public void gotoSubDir()
    {
        if (explore != null)
        {
            explore.gotoSubDir();
        }
    }

    public void gotoParent()
    {
        if (explore != null)
        {
            explore.gotoParent();
        }
    }

    public void gotoNextPage()
    {
        if (explore != null)
        {
            explore.gotoNextPage();
        }
    }

    public void gotoPageIncludeIndex(int index)
    {
        if (explore != null)
        {
            explore.gotoPageIncludeIndex(index);
        }
    }

    public AbstractFile getParent()
    {
        if (explore != null)
        {
            return explore.getParent();
        }
        return null;
    }

    public List<AbstractFile> getFileList()
    {
        if (explore != null)
        {
            return explore.getFileList();
        }
        return null;
    }

    public String getPath(AbstractFile file)
    {
        if (explore != null)
        {
            return explore.getPath(file);
        }
        return null;
    }

    public void setFocusFile(AbstractFile focusFile)
    {
        if (explore != null)
        {
            explore.setFocusFile(focusFile);
        }
    }

    public AbstractFile getFocusFile()
    {
        if (explore != null)
        {
            return explore.getFocusFile();
        }
        return null;
    }

    public void breakBrowse()
    {
        if (explore != null)
        {
            explore.breakBrowse();
        }
    }
}
