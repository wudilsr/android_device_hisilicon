/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.libahplayer;

public class libahplayerException extends Exception {

    /**
     *
     */
    private static final long serialVersionUID = 1L;
    public static final int LEVEL_FATAL = -1;
    public static final int LEVEL_ERROR = -2;
    public static final int LEVEL_WARNING = -3;

    private int mLevel;

    public libahplayerException(int level, String msg) {
        super(msg);
        mLevel = level;
    }

    public int getLevel() {
        return mLevel;
    }

}
