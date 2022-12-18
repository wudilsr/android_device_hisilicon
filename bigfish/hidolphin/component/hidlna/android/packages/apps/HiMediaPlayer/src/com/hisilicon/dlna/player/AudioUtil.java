package com.hisilicon.dlna.player;

import android.media.AudioManager;
import android.util.Log;

import java.util.Timer;
import java.util.TimerTask;

/**
 * volume control
 */
/**
 * 音量控制
 */
public class AudioUtil
{
    private static final String TAG = "AudioUtil";
    private static final long VOLUME_SET_DELAY = 1;//500; // ms
    private static Timer setVolumeTimer = new Timer("SetVolume");
    private static int DMCSetVolumeNum = -1;

    public static void setVolume(AudioManager audioManager, int num)
    {
        setVolumeTimer.cancel();
        setVolumeTimer = new Timer("SetVolume");
        try
        {
            setVolumeTimer.schedule(new SetVolumeTask(audioManager, num), VOLUME_SET_DELAY);
            DMCSetVolumeNum = num;
        }
        catch (IllegalStateException e)
        {
            Log.e(TAG, "another volume set is comming: " + num);
        }
    }

    public static int getVolume(AudioManager audioManager)
    {
        Log.e(TAG, "DMCSetVolumeNum: " + DMCSetVolumeNum);
        int maxVolume = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
        int curVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
        Log.d(TAG, "DMCSetVolumeNum: " + convPerc2StreamVolume(DMCSetVolumeNum, maxVolume) + "curVolume" +curVolume );
        if(DMCSetVolumeNum != -1 && curVolume == convPerc2StreamVolume(DMCSetVolumeNum, maxVolume))
        {//sumsung S5 need getVolume when setVolume
            return DMCSetVolumeNum;
        }
        int volume = convStreamVolume2Perc(curVolume, maxVolume);
        return volume;
    }

    public static void setMute(AudioManager audioManager, boolean isMute)
    {
        if (isMute)
        {
            if (!audioManager.isStreamMute(AudioManager.STREAM_MUSIC))
            {
                audioManager.setStreamMute(AudioManager.STREAM_MUSIC, true);
            }
        }
        else
        {
            if (audioManager.isStreamMute(AudioManager.STREAM_MUSIC))
            {
                audioManager.setStreamMute(AudioManager.STREAM_MUSIC, false);
            }
        }
        audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC, AudioManager.ADJUST_SAME,
                AudioManager.FLAG_PLAY_SOUND | AudioManager.FLAG_SHOW_UI);
    }

    static class SetVolumeTask extends TimerTask
    {
        private AudioManager audioManager;
        private int num;

        public SetVolumeTask(AudioManager audioManager, int num)
        {
            this.audioManager = audioManager;
            this.num = num;
        }

        public void run()
        {
            int maxVolume = audioManager.getStreamMaxVolume(AudioManager.STREAM_MUSIC);
            int curVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);

            int volume = convPerc2StreamVolume(num, maxVolume);
            Log.d(TAG, "num:" + num + ", volume:" + volume);
            if (audioManager.isStreamMute(AudioManager.STREAM_MUSIC))
            {
                audioManager.setStreamMute(AudioManager.STREAM_MUSIC, false);
            }
            if (volume < curVolume)
            {
                while (volume < curVolume)
                {
                    audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,
                            AudioManager.ADJUST_LOWER, AudioManager.FLAG_PLAY_SOUND
                                    | AudioManager.FLAG_SHOW_UI);
                    curVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
                }
                if (curVolume == 0 && num > 0)
                {
                    audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,
                            AudioManager.ADJUST_RAISE, AudioManager.FLAG_PLAY_SOUND
                                    | AudioManager.FLAG_SHOW_UI);
                }
            }
            else if (volume > curVolume)
            {
                while (volume > curVolume)
                {
                    audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,
                            AudioManager.ADJUST_RAISE, AudioManager.FLAG_PLAY_SOUND
                                    | AudioManager.FLAG_SHOW_UI);
                    curVolume = audioManager.getStreamVolume(AudioManager.STREAM_MUSIC);
                }
                if (curVolume == maxVolume && num < 100)
                {
                    audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,
                            AudioManager.ADJUST_LOWER, AudioManager.FLAG_PLAY_SOUND
                                    | AudioManager.FLAG_SHOW_UI);
                }
            }
            else
            {
                audioManager.adjustStreamVolume(AudioManager.STREAM_MUSIC,
                        AudioManager.ADJUST_SAME, AudioManager.FLAG_PLAY_SOUND
                                | AudioManager.FLAG_SHOW_UI);
            }
        }
    }

    static int convPerc2StreamVolume(int perc, int max)
    {
        int streamVolume;
        switch (perc)
        {
            case 0:
                streamVolume = 0;
                break;
            case 100:
                streamVolume = max;
                break;
            default:
                // streamVolume = (perc-1) / (98 / (max-1)) + 1;
                int tmp = perc * max / 100;
                streamVolume = (tmp == 0 ? 1 : tmp);
                break;
        }
        Log.d(TAG, "convPerc2StreamVolume(" + perc + ", " + max + ") return " + streamVolume);

        return streamVolume;
    }

    static int convStreamVolume2Perc(int streamVolume, int max)
    {
        int perc;
        if (streamVolume == 0)
        {
            perc = 0;
        }
        else if (streamVolume == max)
        {
            perc = 100;
        }
        else
        {
            int tmp = (streamVolume * 99) / (max - 1);
            perc = (tmp >= 100 ? 100 : tmp);
        }
        return perc;
    }
}
