package com.zzg.himediarecorder;

import java.io.File;
import java.io.FilenameFilter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.List;

import android.app.Activity;
import android.content.Intent;
import android.media.MediaRecorder;
import android.net.Uri;
import android.os.Bundle;
import android.os.Environment;
import android.util.Log;
import android.view.View;
import android.widget.AdapterView;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ListView;
import android.widget.Toast;
import android.widget.AdapterView.OnItemClickListener;

import android.widget.VideoView;
import android.widget.MediaController;
import android.view.SurfaceHolder;
import android.view.SurfaceView;


public class HiMediaRecorderTest extends Activity {
    /** Called when the activity is first created. */
    private ListView mListView = null;
    private ListView mListView2 = null;
    private Button btn_start = null;
    private Button btn_stop = null;
    private MediaRecorder mMediaRecorder = null;
    private List<String> rec = new ArrayList<String>(); //source file
    private List<String> rec2 = new ArrayList<String>();//recorded file
    private File home = null;
    private File home2 = null;
    private File path = null;
    private String temp = "HiMediaRecorder_";

    private VideoView mVideoView;
    private SurfaceView mPreview;
    private SurfaceHolder holder;
    private boolean started = false;

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.main);
        mListView = (ListView) this.findViewById(R.id.ListView01);
        mListView2 = (ListView) this.findViewById(R.id.ListView02);
        btn_start = (Button) this.findViewById(R.id.Button01);
        btn_stop = (Button) this.findViewById(R.id.Button02);



        mVideoView = (VideoView) findViewById(R.id.surface_view);
        mVideoView.setMediaController(new MediaController(this));
        mPreview = (SurfaceView) findViewById(R.id.surface_view);
        holder = mPreview.getHolder();
        Toast.makeText(this, "click source video file! in list view", Toast.LENGTH_LONG).show();

        //check sdcard
        if (Environment.getExternalStorageState().equals(
                Environment.MEDIA_MOUNTED)) {
            home2 = Environment.getExternalStorageDirectory();
            home = new File("/mnt");
            MusicList(home);
            MusicList2(home2);
        } else {
            Toast.makeText(this, "No sdcard!", Toast.LENGTH_LONG).show();
            return;
        }
        btn_start.setOnClickListener(new Button.OnClickListener() {

            public void onClick(View v) {
                // TODO Auto-generated method stub
                try {
                    started = true;
                    //create file
                    path = File.createTempFile(temp, ".ts", home2);
                    setTitle("=="+path.getAbsolutePath());
                    mMediaRecorder = new MediaRecorder();

                    mMediaRecorder.setVideoSource(MediaRecorder.VideoSource.MEDIAPLAYER);
                    mMediaRecorder.setOutputFormat(MediaRecorder.OutputFormat.DEFAULT);
                    mMediaRecorder.setVideoEncoder(MediaRecorder.VideoEncoder.DEFAULT);
                    //mMediaRecorder.setParameters(String.format("URL=%s","/sdcard/nobody.mp4"));
                    mMediaRecorder.setVideoSize(480, 320);
                    mMediaRecorder.setVideoFrameRate(25);
                    mMediaRecorder.setPreviewDisplay(holder.getSurface());

                    mMediaRecorder.setOutputFile(path.getAbsolutePath());
                    mMediaRecorder.prepare();
                    mMediaRecorder.start();
                    Toast.makeText(getApplicationContext(), "Recording...", Toast.LENGTH_LONG).show();
                } catch (IOException e) {
                    // TODO Auto-generated catch block
                    e.printStackTrace();
                }
            }

        });
        btn_stop.setOnClickListener(new Button.OnClickListener() {

            public void onClick(View v) {
                // TODO Auto-generated method stub
                if (started == true)
                {
                    Toast.makeText(getApplicationContext(), "Recording Stopped, Click recorded TS file for playback", Toast.LENGTH_LONG).show();
                    mMediaRecorder.stop();
                    mMediaRecorder.release();
                    mMediaRecorder = null;
                    mVideoView.stopPlayback();
                    started = false;
                }
                MusicList(home);
                MusicList2(home2);

            }

        });
        mListView.setOnItemClickListener(new OnItemClickListener(){

            public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                    long arg3) {
                // TODO Auto-generated method stub
                String path = home+File.separator+rec.get(arg2);
                File f = new File(path);
                PlayVideo(f);
                Toast.makeText(getApplicationContext(), "Click start to record", Toast.LENGTH_LONG).show();
            }

        });
        mListView2.setOnItemClickListener(new OnItemClickListener(){

            public void onItemClick(AdapterView<?> arg0, View arg1, int arg2,
                    long arg3) {
                // TODO Auto-generated method stub
                String path = home2+File.separator+rec2.get(arg2);
                File f = new File(path);
                //PlayMusic(f);
                PlayVideo(f);
            }

        });
    }

    /**
     * list file
     */
    public void MusicList(File file2) {
        //File[] f = home.listFiles();//(new MusicFilter());
        File[] f = file2.listFiles();//(new MusicFilter());
        rec.clear();
        rec.add("..");
        for (int i = 0; i < f.length; i++) {
            File file = f[i];
            rec.add(file.getName());
        }
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, rec);
        mListView.setAdapter(adapter);
    }

    public void MusicList2(File file2) {
        File[] f = file2.listFiles(new MusicFilter2());
        rec2.clear();
        for (int i = 0; i < f.length; i++) {
            File file = f[i];
            rec2.add(file.getName());
        }
        ArrayAdapter<String> adapter = new ArrayAdapter<String>(this,
                android.R.layout.simple_list_item_1, rec2);
        mListView2.setAdapter(adapter);
    }
    /**
     * playback recorded file
     * @param file
     */
    public void PlayMusic(File file){
        Intent intent = new Intent();
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        intent.setAction(Intent.ACTION_VIEW);
        intent.setDataAndType(Uri.fromFile(file), "audio");
        this.startActivity(intent);
    }
    public void PlayVideo(File file){
        Log.i("HiMediaRecorderTest","(" + file.getPath() +")");
        if(file.isDirectory())
        {
            MusicList(file);
            home = null;
            home = new File (file.getPath());
        }else{
            mVideoView.setVideoPath(file.getPath());
            //mVideoView.setVideoPath(file.getCanonicalPath());
            mVideoView.requestFocus();
            mVideoView.start();
        }
    }
    class MusicFilter implements FilenameFilter {

        public boolean accept(File dir, String filename) {
            // TODO Auto-generated method stub
            return (filename.endsWith(".mp4"));
        }
    }
    class MusicFilter2 implements FilenameFilter {

        public boolean accept(File dir, String filename) {
            // TODO Auto-generated method stub
            return (filename.endsWith(".ts"));
        }
    }
}
