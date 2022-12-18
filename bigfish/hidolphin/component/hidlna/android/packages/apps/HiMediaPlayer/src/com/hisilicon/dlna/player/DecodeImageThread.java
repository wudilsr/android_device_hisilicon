package com.hisilicon.dlna.player;

import java.io.IOException;
import java.net.HttpURLConnection;
import java.net.URL;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import android.graphics.Bitmap;
import android.util.Log;

import com.hisilicon.dlna.util.imagedecode.*;

public class DecodeImageThread extends Thread
{
    private static final String TAG = "DecodeImageThread";
    private Bitmap bitmap;
    private DecodeFinishListener finishListener;
    private URL url;
    private int targetWidth;
    private int targetHeight;
    private int imageLength;
    private boolean startFlag = false;
    private boolean quitFlag = false;
    private boolean isRunning = false;
    private DecodeMethod decodeMethod = null;

    public DecodeImageThread()
    {
    }

    public static enum DecodeError
    {
        NOERROR, OUTOFMEMORY, FAILEDTOGETFILE, OTHER
    }

    public boolean registerFinishListener(DecodeFinishListener listener)
    {
        if (finishListener != null)
        {
            Log.e(TAG, "alread has a listener");
            return false;
        }
        finishListener = listener;
        return true;
    }

    public boolean unregisterFinishListener(DecodeFinishListener listener)
    {
        if (finishListener == null)
        {
            Log.e(TAG, "no listener exist");
            return false;
        }
        finishListener = null;
        return true;
    }

    private void notify(Bitmap bitmap, ImageInfo info, DecodeError error)
    {
        if (finishListener != null)
        {
            finishListener.onDecodeFinish(bitmap, info, error);
        }
    }

    public boolean isRunning()
    {
        return isRunning;
    }

    public void cancelQuit()
    {
        quitFlag = false;
    }

    public void quit()
    {
        int mCount = 300;
        quitFlag = true;
        if(decodeMethod != null)
        {
            if(decodeMethod instanceof DecodeStreamMethod)
            ((DecodeStreamMethod) decodeMethod).interrupt();
        }
        Log.d(TAG, "set flag and waite DecodeThread quit");
        while(isRunning == true)
        {
            mCount ++;
            if(mCount > 500)
                break;
            try
            {
                Thread.sleep(10);
            }
            catch (InterruptedException e)
            {
                Log.e(TAG, "DecodeThread", e);
            }
        }
        Log.d(TAG, "DecodeThread quit success");
    }

    public void decode(URL url, int targetWidth, int targetHeight,int imageLength)
    {
        if (startFlag == true)
        {
            Log.e(TAG, "Alread has a decode job");
            return;
        }
        startFlag = true;
        this.url = url;
        this.targetWidth = targetWidth;
        this.targetHeight = targetHeight;
        this.imageLength= imageLength;
    }

    public void run()
    {
        isRunning = true;
        while (!quitFlag)
        {
            if (startFlag)
            {
                ImageInfo info = new ImageInfo();
                if (targetWidth < 1 || targetHeight < 1)
                {
                    Log.e(TAG, "targetWidth: " + targetWidth + " targetHeight: " + targetHeight);
                    startFlag = false;
                    notify(null, null, DecodeError.OTHER);
                    continue;
                }

                Log.d(TAG, "use decodeStream");
                decodeMethod = new DecodeStreamMethod(url, imageLength, targetWidth, targetHeight);

                try
                {
                    decodeMethod.prepare();
                }
                catch (DecodeException e)
                {
                    Log.e(TAG, "prepare", e);
                    Log.e(TAG, "DecodeException:" + e.toString());
                    if (e instanceof DecodeOutOfMemoryException)
                    {
                        startFlag = false;
                        notify(null, info, DecodeError.OUTOFMEMORY);
                        continue;
                    }
                    else if (e.getMessage() != null && e.getMessage().equals("inputStream is null"))
                    {
                        startFlag = false;
                        notify(null, info, DecodeError.FAILEDTOGETFILE);
                        continue;
                    }
                    startFlag = false;
                    notify(null, info, DecodeError.OTHER);
                    continue;
                }
                String strPhotoRect = decodeMethod.getImageWidth() + "x"
                        + decodeMethod.getImageHeight();
                info.setResolution(strPhotoRect);
                try
                {
                    bitmap = decodeMethod.decode();
                }
                catch (DecodeException e)
                {
                    Log.e(TAG, "decode", e);
                    if (e instanceof DecodeOutOfMemoryException)
                    {
                        startFlag = false;
                        notify(null, info, DecodeError.OUTOFMEMORY);
                        continue;
                    }
                    startFlag = false;
                    notify(null, info, DecodeError.OTHER);
                    continue;
                }
                notify(bitmap, info, DecodeError.NOERROR);
                startFlag = false;
                continue;
            }
            try
            {
                Thread.sleep(10);
            }
            catch (InterruptedException e)
            {
                Log.e(TAG, "DecodeThread", e);
            }
        }
        isRunning = false;
    }
}
