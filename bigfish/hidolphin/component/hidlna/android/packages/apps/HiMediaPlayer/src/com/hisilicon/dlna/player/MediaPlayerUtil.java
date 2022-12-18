package com.hisilicon.dlna.player;

import android.util.Log;

public class MediaPlayerUtil
{
    private static final String TAG = "MediaPlayerUtil";

    /**
     * Function of MediaPlayer
     */
    public static enum Action
    {
        reset,
        setDataSource,
        prepareAsync,
        prepare,
        start,
        pause,
        stop,
        seekTo,
        release
    }

    public static enum Status
    {
        Idle,
        Initialized,
        Preparing,
        Prepared,
        Started,
        Paused,
        Stopped,
        PlaybackCompleted,
        End,
        Error;
        public boolean validAction(Action action)
        {
            if (action == Action.release || action == Action.reset)
            {
                return true;
            }
            switch (this)
            {
                case Idle:
                    if (action == Action.setDataSource)
                        return true;
                    else
                        return false;
                case Initialized:
                    if (action == Action.prepareAsync || action == Action.prepare)
                        return true;
                    else
                        return false;
                case Preparing:
                    return false;
                case Prepared:
                    if (action == Action.seekTo || action == Action.start || action == Action.stop)
                        return true;
                    else
                        return false;
                case Started:
                    if (action == Action.stop || action == Action.pause || action == Action.start
                            || action == Action.seekTo)
                        return true;
                    else
                        return false;
                case Stopped:
                    if (action == Action.prepareAsync || action == Action.prepare)
                        return true;
                    else
                        return false;
                case Paused:
                    if (action == Action.stop || action == Action.start || action == Action.pause
                            || action == Action.seekTo)
                        return true;
                    else
                        return false;
                case PlaybackCompleted:
                    return true;
                default:
                    break;

            }
            Log.d(TAG, new StringBuffer("Action: ").append(action).append(" Status: ").append(this)
                    .append(" not set").toString());
            return true;
        }
    }
}
