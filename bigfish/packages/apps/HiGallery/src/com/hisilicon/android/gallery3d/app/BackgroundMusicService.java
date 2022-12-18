package com.hisilicon.android.gallery3d.app;

import java.io.IOException;
import java.util.List;

import com.hisilicon.android.gallery3d.list.MusicModel;

import android.app.Service;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.media.AudioManager;

import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;

import android.os.IBinder;
import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.os.SystemProperties;

public class BackgroundMusicService extends Service implements
        OnCompletionListener, MediaPlayer.OnPreparedListener {
    private final String TAG = "BackgroundMusicService";
    private static final boolean DEBUG = true;
    private MediaPlayer mediaPlayer;
    private String musicUrl = "";
    private static int playMusicIndex = 0;
    private List<MusicModel> musicLists = null;
    private WakeLock mWakeLock;

    @Override
    public IBinder onBind(Intent intent) {
        return null;
    }

    @Override
    public void onStart(Intent intent, int startId) {
        Log.d(DEBUG, TAG, "onStart BackgroundMusicService");
        mediaPlayer = new MediaPlayer();
        //mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
        mediaPlayer.setOnPreparedListener(this);
        mediaPlayer.setOnCompletionListener(this);
        GalleryApp galleryApp = (GalleryApp) getApplication();
        if(galleryApp!=null && galleryApp.getMediaFileListService()!=null)
        {
        musicLists = galleryApp.getMediaFileListService().getMusicList();
        if (musicLists != null && musicLists.size() > 0) {
        Log.d(DEBUG, TAG, "musicLists.size()" + musicLists.size());
        playMusicIndex = intent.getIntExtra("music_index", 0);
        playUrl(playMusicIndex);
        }
        }
        PowerManager pm = (PowerManager) getSystemService(Context.POWER_SERVICE);
        mWakeLock = pm.newWakeLock(PowerManager.PARTIAL_WAKE_LOCK, this
                .getClass().getName());
        mWakeLock.setReferenceCounted(false);
        registerPower();
        super.onStart(intent, startId);
    }

    public void playUrl(int playIndex) {
        Log.d(DEBUG, TAG, "playUrl playIndex=" + playIndex);
        if (musicLists.size() > 0) {
            musicUrl = musicLists.get(playIndex).getPath();
            try {
                mediaPlayer.reset();
                mediaPlayer.setDataSource(musicUrl);
                mediaPlayer.prepare();
            } catch (IllegalArgumentException e) {
                e.printStackTrace();
            } catch (IllegalStateException e) {
                e.printStackTrace();
            } catch (IOException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    public void onDestroy() {
        super.onDestroy();
        stop();
    }

    public void stop() {
        if (mediaPlayer != null) {
            mediaPlayer.stop();
            mediaPlayer.release();
            mediaPlayer = null;
        }
        unregisterReceiver();
    }

    public void onPrepared(MediaPlayer mediaPlayer) {
        mediaPlayer.start();
        Log.d(DEBUG, TAG, "onPrepared");
    }

    @Override
    public void onCompletion(MediaPlayer arg0) {
        Log.d(DEBUG, TAG, "onCompletion playMusicIndex = " + playMusicIndex);
        playMusicIndex++;
        if (playMusicIndex >= musicLists.size()) {
            playMusicIndex = 0;
        }
        playUrl(playMusicIndex);
    }
    private BroadcastReceiver PowerReceiver = new BroadcastReceiver() {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();
            if (action.equals(Intent.ACTION_SCREEN_OFF)) {
            Log.d(DEBUG, TAG, "onStart ACTION_SCREEN_OFF");
               if(SystemProperties.get("persist.suspend.mode").equals("deep_resume")) {
                   mWakeLock.acquire();
                   mediaPlayer.pause();
                   mWakeLock.release();
                }
            } else if (action.equals(Intent.ACTION_SCREEN_ON)) {
             Log.d(DEBUG, TAG, "onStart ACTION_SCREEN_ON");
             if(SystemProperties.get("persist.suspend.mode").equals("deep_resume")) {
                 mediaPlayer.start();
             }
            }
        }
    };
    private void registerPower(){
	 Log.d(DEBUG, TAG, "onStart registerPower");
	IntentFilter powerIntentFilter = new IntentFilter();
        powerIntentFilter.addAction(Intent.ACTION_SCREEN_ON);
        powerIntentFilter.addAction(Intent.ACTION_SCREEN_OFF);
        this.registerReceiver(PowerReceiver, powerIntentFilter);
    }
    private void unregisterReceiver(){
	Log.d(DEBUG, TAG, "onStart unregisterReceiver");
	mWakeLock.release();
	this.unregisterReceiver(PowerReceiver);
    }
}
