package com.hisilicon.android.gallery3d.list;

import java.io.Serializable;

/**
 * MusicModel
 */
public class MusicModel implements Serializable {

    /**
     * serialVersionUID
     */
    private static final long serialVersionUID = 1L;

    private int id;
    private String path;
    private String title;
    private long size;
    private long AddedTime;

    public int getId() {
        return id;
    }

    public void setId(int id) {
        this.id = id;
    }

    public String getPath() {
        return path;
    }

    public void setPath(String path) {
        this.path = path;
    }

    public String getTitle() {
        return title;
    }

    public void setTitle(String title) {
        this.title = title;
    }

    public long getSize() {
        return size;
    }

    public void setSize(long size) {
        this.size = size;
    }

    public long getAddedTime() {
        return AddedTime;
    }

    public void setAddedTime(long addedTime) {
        AddedTime = addedTime;
    }
}
