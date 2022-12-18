package com.hisilicon.dlna.mediacenter;

import java.util.List;

import com.hisilicon.dlna.file.AbstractFile;
import com.hisilicon.dlna.file.TopLevel;

public interface AbstractExplore
{
    void updateTopList();

    void gotoTop(TopLevel device);

    void gotoSubDir();

    void gotoParent();

    void gotoNextPage();

    void gotoPageIncludeIndex(int index);

    AbstractFile getParent();

    List<AbstractFile> getFileList();

    Location getLocation();

    String getPath(AbstractFile file);

    void setFocusFile(AbstractFile focusFile);

    AbstractFile getFocusFile();

    void breakBrowse();
}
