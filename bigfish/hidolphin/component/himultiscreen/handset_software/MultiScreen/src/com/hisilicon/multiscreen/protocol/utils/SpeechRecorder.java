package com.hisilicon.multiscreen.protocol.utils;

import java.io.File;
import java.io.FileOutputStream;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.LinkedBlockingQueue;
import java.util.concurrent.TimeUnit;

import android.content.Context;
import android.media.AudioFormat;
import android.media.AudioManager;
import android.media.AudioRecord;
import android.media.MediaRecorder;
import android.media.SoundPool;

import com.hisilicon.multiscreen.mybox.R;

/**
 * Speech recorder class. <br>
 * CN:语音录制类。
 */
public class SpeechRecorder
{
    private ISpeechMsgDealer mISpeechMsgDealer = null;

    private AudioRecord mRecord;

    private static final String AudioName = "/sdcard/audioData.raw";

    FileOutputStream fos = null;

    private LinkedBlockingQueue<byte[]> mAudioDataQueue = null;

    // Audio source
    private int audioSource = MediaRecorder.AudioSource.MIC;

    // Audio sample rate
    private static int sampleRateInHz = 16000;// 44100;

    // Auido channel config.
    private static int channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;// AudioFormat.CHANNEL_IN_STEREO;

    // Audio format.
    private static int audioFormat = AudioFormat.ENCODING_PCM_16BIT;

    // Audio buffer size.
    private int minBufSize;

    // Auido data seq.
    private int mAudioSeq = 0;

    // Audio record flag
    private boolean isRecording = false;

    // record thread.
    private Thread recordThread = null;

    // sound pool.
    private SoundPool mSp = null;

    // sound id.
    private int mMusic;

    private Context mContext;

    // Thread sound pool.
    ExecutorService mSendThreadPool = null;

    // Send runnable.
    private Runnable sendRunnable = new Runnable()
    {

        @Override
        public void run()
        {
                byte[] audioData;
                try
                {
                if ((mAudioDataQueue != null) && (!mAudioDataQueue.isEmpty()))
                {
                    mAudioSeq++;
                    audioData = mAudioDataQueue.take();
                    mISpeechMsgDealer.pushAudioData(audioData, mAudioSeq);
                }
                }
                catch (InterruptedException e)
                {
                    LogTool.e(e.getMessage());
                }
        }
    };

    // record runnable.
    private Runnable recordRunnable = new Runnable()
    {

        @Override
        public void run()
        {
            LogTool.d("");
            openFile();
            mISpeechMsgDealer.startSpeaking();
            try
            {
                Thread.sleep(200);
            }
            catch (InterruptedException e1)
            {
                LogTool.e(e1.getMessage());
            }
            mAudioSeq = 0;
            mRecord.startRecording();
            while (isRecording == true)
            {
                // new一个byte数组用来存一些字节数据，大小为缓冲区大小
                byte[] audiodata = new byte[minBufSize];
                int readsize = 0;
                readsize = mRecord.read(audiodata, 0, minBufSize);
                LogTool.i(" record size" + String.valueOf(readsize));
                if ((AudioRecord.ERROR_INVALID_OPERATION != readsize)
                    && (AudioRecord.ERROR_BAD_VALUE != readsize))
                {
                    writeFile(audiodata);
                    try
                    {
                        mAudioDataQueue.put(audiodata);
                    }
                    catch (InterruptedException e)
                    {
                        LogTool.e(e.getMessage());
                    }
                    mSendThreadPool.execute(sendRunnable);
                }
            }

            try
            {
                mSendThreadPool.shutdown();
                mSendThreadPool.awaitTermination(1000, TimeUnit.MILLISECONDS);
            }
            catch (InterruptedException ignored)
            {
                LogTool.e(ignored.getMessage());
            }
            mISpeechMsgDealer.stopSpeaking();

            closeFile();
        }
    };

    /**
     * Init recorder.
     * @param dealer
     * @param context
     */
    public void initRecorder(ISpeechMsgDealer dealer, Context context)
    {
        audioSource = MediaRecorder.AudioSource.MIC;

        sampleRateInHz = 16000;

        channelConfig = AudioFormat.CHANNEL_CONFIGURATION_MONO;

        audioFormat = AudioFormat.ENCODING_PCM_16BIT;

        minBufSize = 0;

        isRecording = false;

        minBufSize = AudioRecord.getMinBufferSize(sampleRateInHz, channelConfig, audioFormat);

        mISpeechMsgDealer = dealer;

        mContext = context;
        initSoundPool();
        // mRecordDialog = new SpeechRecordDialog(mContext);
    }

    /**
     * Start audio record.
     */
    public void startRecord()
    {
        playTouchSound();
        mRecord =
            new AudioRecord(audioSource, sampleRateInHz, channelConfig, audioFormat, minBufSize);
        LogTool.d("");
        mSendThreadPool = Executors.newFixedThreadPool(3);
        mAudioDataQueue = new LinkedBlockingQueue<byte[]>(20);
        isRecording = true;
        recordThread = new Thread(recordRunnable);
        recordThread.start();
    }

    /**
     * Stop record.
     */
    public void stopRecord()
    {
        LogTool.d("");
        mRecord.stop();

        playTouchSound();

        isRecording = false;
        try
        {
            recordThread.join();
        }
        catch (InterruptedException e)
        {
            LogTool.e(e.getMessage());
        }
        mRecord.release();
        mRecord = null;
        recordThread = null;
        mAudioDataQueue.clear();
        mAudioDataQueue = null;
    }

    /**
     * Init tip sound pool.
     */
    private void initSoundPool()
    {
        // TODO Auto-generated method stub
        mSp = new SoundPool(10, AudioManager.STREAM_SYSTEM, 5);
        mMusic = mSp.load(mContext, R.raw.speech, 1);
    }

    /**
     * Play record tip sound.
     */
    private void playTouchSound()
    {
        if (mSp != null)
        {
            mSp.play(mMusic, 1, 1, 0, 0, 2);
        }
    }

    /**
     * Open audio files.
     */
    private void openFile()
    {
        try
        {
            File file = new File(AudioName);
            if (file.exists())
            {
                file.delete();
            }
            fos = new FileOutputStream(file);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Close audio record files.
     */
    private void closeFile()
    {
        try
        {
            fos.close();

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    /**
     * Write record audio files.
     * @param audioDate
     */
    private void writeFile(byte[] audioDate)
    {
        try
        {
            fos.write(audioDate, 0, audioDate.length);
        }
        catch (Exception e)
        {
            LogTool.e(e.getMessage());
        }
    }
}
