package com.hisilicon.android.gallery3d.app;

import java.io.IOException;
import java.util.List;

import com.hisilicon.android.gallery3d.list.MusicModel;

import android.app.Service;
import android.content.Intent;
import android.media.AudioManager;

import android.media.MediaPlayer;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;

import android.os.IBinder;

public class BackgroundMusicService extends Service implements
        OnCompletionListener, MediaPlayer.OnPreparedListener {
    private final String TAG = "BackgroundMusicService";
    private static final boolean DEBUG = false;
    private MediaPlayer mediaPlayer;
    private String musicUrl = "";
    private static int playMusicIndex = 0;
    private List<MusicModel> musicLists = null;

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

}
