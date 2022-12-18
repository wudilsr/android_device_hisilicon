/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.hisilicon.android.music.util;

import java.io.Serializable;

/**
 * One used to represent the content of each word class encapsulates the lyrics
 * and the lyrics start time and end time, and some practical method
 * @author
 */
public class Sentence implements Serializable {

    private static final long serialVersionUID = 20071125L;
    private long fromTime;// The starting time, time is in milliseconds.
    private long toTime;// The end time
    private String content;// content
    private final static long DISAPPEAR_TIME = 1000L;// The lyrics from the
                                                     // display end to disappear
                                                     // time

    public Sentence(String content, long fromTime, long toTime) {
        this.content = content;
        this.fromTime = fromTime;
        this.toTime = toTime;
    }

    public Sentence(String content, long fromTime) {
        this(content, fromTime, 0);
    }

    public Sentence(String content) {
        this(content, 0, 0);
    }

    public long getFromTime() {
        return fromTime;
    }

    public void setFromTime(long fromTime) {
        this.fromTime = fromTime;
    }

    public long getToTime() {
        return toTime;
    }

    public void setToTime(long toTime) {
        this.toTime = toTime;
    }

    /**
     * Check one time are included in the middle of a sentence
     * @param time
     * @return is included
     */
    public boolean isInTime(long time) {
        return time >= fromTime && time <= toTime;
    }

    /**
     * get content
     * @return content
     */
    public String getContent() {
        return content;
    }

    /**
     * This sentence is the length of time, in milliseconds
     * @return length
     */
    public long getDuring() {
        return toTime - fromTime;
    }

    public String toString() {
        return "{" + fromTime + "(" + content + ")" + toTime + "}";
    }
}
