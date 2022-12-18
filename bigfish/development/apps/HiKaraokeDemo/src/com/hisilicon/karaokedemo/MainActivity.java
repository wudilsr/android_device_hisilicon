package com.hisilicon.karaokedemo;

import android.app.Activity;
import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.MediaPlayer;
import android.media.MediaPlayer.OnBufferingUpdateListener;
import android.media.MediaPlayer.OnCompletionListener;
import android.media.MediaPlayer.OnErrorListener;
import android.media.MediaPlayer.OnInfoListener;
import android.media.MediaPlayer.OnPreparedListener;
import android.media.MediaPlayer.TrackInfo;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.SurfaceHolder;
import android.view.SurfaceView;
import android.view.View;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemSelectedListener;
import android.widget.ArrayAdapter;
import android.widget.Spinner;
import android.widget.TextView;
import android.widget.Toast;

import com.cmcc.media.*;
import com.cmcc.media.MediaPlayerEx.CHANNEL;
import com.iflytek.mediaplayertester.R;

public class MainActivity extends Activity implements OnErrorListener,
        OnPreparedListener, OnCompletionListener, OnBufferingUpdateListener, OnInfoListener {
    private static final boolean FULL_SUPPORT = true;

    private static final String[] Mp3Url = {
        "/mnt/sdcard/qgw.mp3",
        "/mnt/sdcard/test.mp4" };

    private static final String[] ReverbMode = { "STUDIO", "KTV", "CONCERT" };
    private MediaPlayer mediaPlayer;
    private Micphone micphone;
    private RTSoundEffects rtSoundEffects;
    private AudioRecord audioRecord;
    private MediaRecorder mediaRecorder;
    private RecordThread recordThread;

    private int micVol = 100;
    private double volume;

    private boolean isPaused = false;
    private boolean isPrepared = false;
    private int bs;
    private int channel = 1;
    private SurfaceView surfaceView;

    AudioManager mAudioManager;
    private Handler handler = new Handler(new Handler.Callback() {

        @Override
        public boolean handleMessage(Message msg) {
        switch (msg.what) {
        case 0:
        if (mediaPlayer != null) {
        ((TextView) findViewById(R.id.textView3))
        .setText("进度: "
        + mediaPlayer.getCurrentPosition() + "ms");
        ((TextView) findViewById(R.id.textView5))
        .setText("mic电平：" + String.format("%.2f", volume));
        handler.removeMessages(0);
        handler.sendEmptyMessageDelayed(0, 100);
        }
        return true;
        default:
        return false;
        }
        }
    });

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        surfaceView = (SurfaceView) findViewById(R.id.videoView1);
        surfaceView.getHolder().addCallback(new SurfaceCallback());
        ((Spinner) findViewById(R.id.spinner1))
        .setAdapter(new ArrayAdapter<String>(this,
        android.R.layout.simple_spinner_item, Mp3Url));
        ((Spinner) findViewById(R.id.spinner2))
        .setAdapter(new ArrayAdapter<String>(this,
        android.R.layout.simple_spinner_item, ReverbMode));
        ((Spinner) findViewById(R.id.spinner2))
        .setOnItemSelectedListener(new OnItemSelectedListener() {

        @Override
        public void onItemSelected(AdapterView<?> parent,
        View view, int position, long id) {
        if (mediaPlayer != null && mediaPlayer.isPlaying()
        && rtSoundEffects != null) {
        String s = (String) parent
        .getItemAtPosition(position);
        if (FULL_SUPPORT) {
        rtSoundEffects.setReverbMode(convModeId(s));
        } else {
        rtSoundEffects.setParam(
        RTSoundEffects.MODE_REVERB,
        convModeId(s));
        }
        }
        }

        @Override
        public void onNothingSelected(AdapterView<?> parent) {

        }
        });
        mAudioManager = (AudioManager) getSystemService(Context.AUDIO_SERVICE);
        int max =  mAudioManager.getStreamMaxVolume( AudioManager.STREAM_MUSIC);
        Log.d("karaoke","max volume = "+max);
    }

    @Override
    protected void onDestroy() {
        super.onDestroy();
        release();
    }

    @Override
    protected void onResume() {
        super.onResume();
        surfaceView.setFocusable(false);
        surfaceView.setFocusableInTouchMode(false);
        findViewById(R.id.button1).requestFocus();
    }

    public void onClickMp3(View v) {
        String url = (String) ((Spinner) findViewById(R.id.spinner1))
        .getSelectedItem();
        String mode = (String) ((Spinner) findViewById(R.id.spinner2))
        .getSelectedItem();
        startAudio(url, convModeId(mode));
    }

    public void onVolPlusClick(View v) {
        if (micphone == null) {
        return;
        }
        micVol += 10;
        if (micVol >= 100)
        micVol = 100;
        micphone.setVolume(micVol);
        if (FULL_SUPPORT) {
        ((TextView) findViewById(R.id.textView6)).setText("mic vol："
        + String.valueOf(micphone.getVolume()));
        } else {
        ((TextView) findViewById(R.id.textView6)).setText("mic vol："
        + micVol);
        }
    }

    public void onVolSubClick(View v) {
        if (micphone == null) {
        return;
        }
        micVol -= 10;
        if (micVol <= 0)
        micVol = 0;
        micphone.setVolume(micVol);
        if (FULL_SUPPORT) {
        ((TextView) findViewById(R.id.textView6)).setText("mic vol："
        + String.valueOf(micphone.getVolume()));
        } else {
        ((TextView) findViewById(R.id.textView6)).setText("mic vol："
        + micVol);
        }
    }

    public void onClickPauseOrResume(View v) {
        if (mediaPlayer == null) {
        return;
        }
        if (isPaused) {
        mediaPlayer.start();
        if (FULL_SUPPORT) {
        //    ((MediaRecorderEx) mediaRecorder).resume();
        }
        } else {
        mediaPlayer.pause();
        if (FULL_SUPPORT) {
        //    ((MediaRecorderEx) mediaRecorder).pause();
        }
        }
        isPaused = !isPaused;
    }

    public void onSwitchChannelClick(View v) {
        if (mediaPlayer != null) {
        if (mediaPlayer instanceof MediaPlayerEx) {
        MediaPlayerEx mpe = (MediaPlayerEx) mediaPlayer;
        channel = ++channel > 3 ? 1 : channel;
        mpe.switchChannel(convChannelId(channel));
        ((TextView) findViewById(R.id.textView4)).setText("声道"
        + convChannelStr(channel));
        } else {
        ((TextView) findViewById(R.id.textView4))
        .setText("切换声道失败，未获取到MediaPlayerEx对象");
        }
        } else {
        Toast.makeText(this, "错误，播放未�?��", Toast.LENGTH_LONG).show();
        }
    }

    private MediaPlayerEx.CHANNEL convChannelId(int chid) {
        switch (chid) {
        case 1:
        return CHANNEL.CENTER;
        case 2:
        return CHANNEL.LEFT;
        case 3:
        return CHANNEL.RIGHT;
        default:
        return CHANNEL.CENTER;
        }
    }

    private int convModeId(String mode) {
        if (mode.equals("STUDIO"))
        return 1;
        if (mode.equals("KTV"))
        return 2;
        if (mode.equals("CONCERT"))
        return 3;
        return 1;
    }

    private String convChannelStr(int chid) {
        switch (chid) {
        case 1:
        return "中";
        case 2:
        return "左";
        case 3:
        return "右";
        default:
        return "中";
        }
    }

    public void onClickStop(View v) {
        release();
    }

    private void startAudio(String url, int mode) {
        release();
        try {
        isPaused = false;
        isPrepared = false;
        micphone = (Micphone) getSystemService("Micphone");
        micphone.initial();

        rtSoundEffects = (RTSoundEffects) getSystemService("RTSoundEffects");
        if (FULL_SUPPORT) {
        rtSoundEffects.setReverbMode(mode);
        } else {
        rtSoundEffects.setParam(RTSoundEffects.MODE_REVERB, mode);
        }
        micphone.start();
        int bst = AudioRecord
        .getMinBufferSize(44100, AudioFormat.CHANNEL_IN_MONO,
        AudioFormat.ENCODING_PCM_16BIT);
        bs = bst;
        if (FULL_SUPPORT) {
        audioRecord = new AudioRecord(AudioSource.CMCC_KARAOK_MIC,
        44100, AudioFormat.CHANNEL_IN_MONO,
        AudioFormat.ENCODING_PCM_16BIT, bs);
        } else {
        audioRecord = new AudioRecord(
        android.media.MediaRecorder.AudioSource.MIC, 44100,
        AudioFormat.CHANNEL_IN_MONO,
        AudioFormat.ENCODING_PCM_16BIT, bs);
        }
        recordThread = new RecordThread();

        mediaRecorder = new MediaRecorder();
        if (FULL_SUPPORT) {
        mediaRecorder.setAudioSource(AudioSource.CMCC_KARAOK_SPEAKER);
        } else {
        mediaRecorder
        .setAudioSource(android.media.MediaRecorder.AudioSource.MIC);
        }
        mediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.AAC_ADTS);
        mediaRecorder.setAudioEncoder(MediaRecorder.AudioEncoder.AAC);
        mediaRecorder.setAudioSamplingRate(44100);
        mediaRecorder.setAudioEncodingBitRate(64000);
        mediaRecorder.setAudioChannels(1);
        mediaRecorder.setOutputFile(Environment
        .getExternalStorageDirectory() + "/out.adts");
        mediaRecorder.prepare();

        mediaPlayer = new MediaPlayer();
        mediaPlayer.setAudioStreamType(AudioManager.STREAM_MUSIC);
        if (url.endsWith("mp3") || url.endsWith("aac")) {
        surfaceView.setVisibility(View.INVISIBLE);
        } else if (url.endsWith("mp4")) {
        surfaceView.setVisibility(View.VISIBLE);
        mediaPlayer.setDisplay(surfaceView.getHolder());
        }

        mediaPlayer.setDataSource(this, Uri.parse(url));
        mediaPlayer.setOnErrorListener(this);
        mediaPlayer.setOnBufferingUpdateListener(this);
        mediaPlayer.setOnPreparedListener(this);
        mediaPlayer.setOnInfoListener(this);
        mediaPlayer.setOnCompletionListener(this);
        mediaPlayer.prepareAsync();
        ((TextView) findViewById(R.id.textView1)).setText("载入中");
        } catch (Exception e) {
        Toast.makeText(this, "MediaPlayer异常，" + e.getMessage(),
        Toast.LENGTH_LONG).show();
        release();
        }
    }

    @Override
    public void onPrepared(MediaPlayer mp) {
        mediaPlayer.start();
        mediaRecorder.start();
        recordThread.start();
        isPrepared = true;
        onVolPlusClick(null);
        if (FULL_SUPPORT) {
        ((TextView) findViewById(R.id.textView7)).setText("mic数："
        + String.valueOf(micphone.getMicNumber()));
        } else {
        ((TextView) findViewById(R.id.textView7)).setText("mic数：?");
        }
        ((TextView) findViewById(R.id.textView1)).setText("播放中");
        ((TextView) findViewById(R.id.textView2)).setText("总时 长"
        + mediaPlayer.getDuration() + "ms");
        ((TextView) findViewById(R.id.textView4)).setText("声道:"
        + convChannelStr(channel));
        handler.sendEmptyMessage(0);
    }

    @Override
    public boolean onError(MediaPlayer mp, int what, int extra) {
        Toast.makeText(this, "MediaPlayer出错，what=" + what + ", extra=" + extra,
        Toast.LENGTH_LONG).show();
        release();
        return true;
    }

    @Override
    public void onCompletion(MediaPlayer mp) {
        release();
    }

    private void release() {
        if (mediaPlayer != null) {
        ((TextView) findViewById(R.id.textView1)).setText("已停止");
        if (isPrepared)
        mediaPlayer.stop();
        mediaPlayer.release();
        mediaPlayer = null;
        }
        if (recordThread != null) {
        recordThread.shutdown();
        recordThread = null;
        }
        if (mediaRecorder != null) {
        if (isPrepared)
        mediaRecorder.stop();
        mediaRecorder.release();
        mediaRecorder = null;
        }
        if (micphone != null) {
        if (isPrepared)
        micphone.stop();
        micphone.release();
        micphone = null;
        }
        if (rtSoundEffects != null) {
        rtSoundEffects = null;
        }
    }

    private class SurfaceCallback implements SurfaceHolder.Callback {
        public void surfaceChanged(SurfaceHolder holder, int format, int width,
        int height) {
        }

        public void surfaceCreated(SurfaceHolder holder) {

        }

        public void surfaceDestroyed(SurfaceHolder holder) {
        release();
        }

    }

    private class RecordThread extends Thread {
        boolean isRun = true;

        @Override
        public void run() {
        audioRecord.startRecording();
        // 用于读取�?buffer
        short[] buffer = new short[bs];
        Log.i("yyp", "bs = "+bs);
        while (isRun) {
        int r = audioRecord.read(buffer, 0, bs);
        //micphone.setVolume(90);
        if(r <= 0){
        try {
        Thread.sleep(5);
        } catch (InterruptedException e) {
        // TODO Auto-generated catch block
        e.printStackTrace();
        }
        continue;
        }
        double v = 0;
        // 将 buffer 内容取出，进行平方和运算
        for (int i = 0; i < buffer.length; i++) {
        // 这里没有做运算的优化，为了更加清晰的展示代码
        v += buffer[i] * buffer[i];
        }
        // 平方和除以数据总长度，得到音量大小。可以获取白噪声值，然后对实际采样进行标准化。
        // 如果想利用这个数值进行操作，建议用 sendMessage 将其抛出，在 Handler 里进行处理。
        volume = Math.sqrt(v) / r;
        }
        audioRecord.stop();
        audioRecord.release();
        audioRecord = null;
        }

        public void shutdown() {
        isRun = false;
        }
    }

    @Override
    public void onBufferingUpdate(MediaPlayer mp, int percent) {
        Log.v("MediaPlayerTester", "onBufferingUpdate: " + percent + "%");

    }

    @Override
    public boolean onInfo(MediaPlayer mp, int what, int extra) {
        switch (what) {
        case MediaPlayer.MEDIA_INFO_BUFFERING_START:
        Log.v("MediaPlayerTester", "MEDIA_INFO_BUFFERING_START");
        break;
        case MediaPlayer.MEDIA_INFO_BUFFERING_END:
        Log.v("MediaPlayerTester", "MEDIA_INFO_BUFFERING_END");
        break;
        default:
        break;
        }

        return false;
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event){
        Log.d("test", "keycode = "+keyCode);
        switch (keyCode) {
        case KeyEvent.KEYCODE_VOLUME_DOWN:
        Log.d("karaoke", "cuurent volume = "+mAudioManager.getStreamVolume( AudioManager.STREAM_MUSIC));
        break;
        case KeyEvent.KEYCODE_VOLUME_UP:
        Log.d("karaoke", "cuurent volume = "+mAudioManager.getStreamVolume( AudioManager.STREAM_MUSIC));
        break;
        case KeyEvent.KEYCODE_1:
        mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC, 0, 0);
        break;
        case KeyEvent.KEYCODE_2:
        mAudioManager.setStreamVolume(AudioManager.STREAM_MUSIC, 10, 0);
        break;
        case KeyEvent.KEYCODE_3:
        mAudioManager.setStreamMute(AudioManager.STREAM_MUSIC, false);
        break;
        case KeyEvent.KEYCODE_4:
        mAudioManager.setStreamMute(AudioManager.STREAM_MUSIC, true);
        break;
        case KeyEvent.KEYCODE_5:
        TrackInfo[] info = mediaPlayer.getTrackInfo();
        Log.i("YYP", "info SIZE = "+info.length);
        for(int i = 0; i < info.length; i++){
        Log.i("YYP", "info type = "+info[i].getTrackType());
        }
        break;
        case KeyEvent.KEYCODE_6:
        TrackInfo[] info_1 = mediaPlayer.getTrackInfo();
        mediaPlayer.selectTrack(1);
        break;
        case KeyEvent.KEYCODE_7:
        TrackInfo[] info_2 = mediaPlayer.getTrackInfo();
        mediaPlayer.selectTrack(2);
        break;
        default:
        break;
        }
        return super.onKeyDown(keyCode, event);
    }
}
