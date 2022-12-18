package com.hisilicon.android.music.util;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStreamWriter;

import com.hisilicon.android.music.MediaPlaybackActivity;

/**
 * To search the results of object representation
 * @author
 */
public class SearchResult {
    private String id;
    private String lrcId;
    private String lrcCode;
    private String artist;
    private String title;
    private Task task;
    private String content;

    public static interface Task {

        public String getLyricContent();
    }

    public SearchResult(String id, String lrcId, String lrcCode, String artist,
            String title, Task task) {
        this.id = id;
        this.lrcId = lrcId;
        this.lrcCode = lrcCode;
        this.artist = artist;
        this.title = title;
        this.task = task;
    }

    public String getArtist() {
        return artist;
    }

    public String getTitle() {
        return title;
    }

    public String getId() {
        return id;
    }

    public String getLrcCode() {
        return lrcCode;
    }

    public String getLrcId() {
        return lrcId;
    }

    public String getContent() {
        if (content == null) {
            content = task.getLyricContent();
        }
        return content;
    }

    public void save(String name) throws IOException {
        BufferedWriter bw = new BufferedWriter(new OutputStreamWriter(
                new FileOutputStream(new File(MediaPlaybackActivity.HOME,
                        "Lyrics/" + name)), "GBK"));
        bw.write(String.valueOf(getContent()));
        bw.close();
    }

    public String toString() {
        return artist + ":" + title;
    }
}
