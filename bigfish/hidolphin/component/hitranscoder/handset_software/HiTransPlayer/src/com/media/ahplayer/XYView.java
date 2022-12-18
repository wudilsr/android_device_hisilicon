/*
 * Copyright (C) 2011 xuyangpo/x54178 huawei
 */
package com.media.ahplayer;

import com.media.libahplayer.libahplayer;
import com.media.libahplayer.AHSMonitorInfo;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.os.Message;
import android.util.AttributeSet;
import android.util.Log;
import android.view.View;

public class XYView extends View {
    private static final String     TAG = "XYView";
    private long mTimeOfGetData = -1000;//ms
    private static final long GETDATAINTERVAL = 100;//ms
    private static final int MAXPOINTS = 30;//ms
    private Paint   mPaint = new Paint();
    private XYViewListener mListener = null;
    private AHSMonitorInfo[] mInfoArray;
    private int mStartIndex = 0;//要显示的第一个点所在的index
    private int mEndIndex = 0;//要现实的最后一个点所在的index
    private int mInfoNum = 0;//总的要显示的点个数。
    private int mWindowWidth = 800;//pixels
    private int mWindowHeight = 480;//pixels
    private static int mXStart = 100;
    private static int mYStart = 450;
    private static int mXPixels = 600;
    private static int mYPixels = 400;
    private static float mYRange = 2000;//(0~2000)kbps;
    private static float mXRange = 30;//(0~2000)kbps;
    private static float mYPixelRange = mYRange/mYPixels;
    private static float mXPixelRange = mXRange/mXPixels;
    private int mDrawState;//0 prepare 1 Drawing;2 Stopping; 3 Stoped;
    private void Init()
    {
        mInfoArray = new AHSMonitorInfo[MAXPOINTS];
        for(int i = 0;i<MAXPOINTS;i++)
        {
            mInfoArray[i] = null;
        }
        mStartIndex = -1;
        mEndIndex = -1;
        mInfoNum = 0;
        mDrawState = 0;
    }
    public XYView(Context context) {
        super(context);
        Init();
        //buildPoints();
    }
    public XYView(Context context, AttributeSet attrs) {
        this(context, attrs, 0);
        Init();
        //buildPoints();
    }
    public XYView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        Init();
        //buildPoints();
    }
    public void SetViewSize(int width,int height)
    {
        mWindowWidth = width;
        mWindowHeight = height;
        mXStart = 70;
        mYStart = (mWindowHeight + mYPixels)/2;
    }
    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        if((this.getVisibility()==View.VISIBLE))
        {
            canvas.drawColor(Color.TRANSPARENT);
            canvas.translate(mXStart, mYStart);
            DrawAHSMonitorInfo(canvas);
            if(mDrawState==0)
            {
                Log.e(TAG, "new DrawThread");
                new Thread(new DrawThread()).start();
            }
        }

    }
    public void StopDraw()
    {
        if((mDrawState == 3)||(this.getVisibility()!=View.VISIBLE))
        {
            return;
        }
        if(mDrawState == 1)
        {
            mDrawState = 2;
            while(mDrawState != 3)
            {
                try {
                    Thread.sleep(200);
                } catch (InterruptedException e) {
                    // TODO Auto-generated catch block
                    Log.e(TAG, "Thread.sleep" + e.getMessage());
                }
            }
        }
    }
    /**
     *
     * @author x54178
     *
     */
    public static interface XYViewListener {
        public AHSMonitorInfo onGetAHSData(int lastTimeSec);
    }
    public void setXYViewListener(XYViewListener listener)
    {
        mListener = listener;
    }
    private void DrawAHSMonitorInfo(Canvas canvas)
    {
        if(mInfoNum == MAXPOINTS)
        {
            DrawXY(canvas,mInfoArray[mEndIndex].time);
        }
        else
        {
            DrawXY(canvas,30);
        }
        Paint paint = mPaint;
        int i = 1;
        int tmpIndex = mStartIndex;
        {//画线
            paint.setStrokeWidth(0);
            while(i<mInfoNum)
            {
                float X1 = 0 + (i-1)/mXPixelRange;
                float X2 = 0 + i/mXPixelRange;
                float VBRY1 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].PLVideoBitRate)/mYPixelRange;
                float VBRY2 = 0 -(float)(mInfoArray[(tmpIndex+1)%MAXPOINTS].PLVideoBitRate)/mYPixelRange;
                float DBRY1 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].DLVideoBitRate)/mYPixelRange;
                float DBRY2 = 0 -(float)(mInfoArray[(tmpIndex+1)%MAXPOINTS].DLVideoBitRate)/mYPixelRange;
                float SBWY1 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].SMBandwidth)/mYPixelRange;
                float SBWY2 = 0 -(float)(mInfoArray[(tmpIndex+1)%MAXPOINTS].SMBandwidth)/mYPixelRange;
                float RBWY1 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].RTBandwidth)/mYPixelRange;
                float RBWY2 = 0 -(float)(mInfoArray[(tmpIndex+1)%MAXPOINTS].RTBandwidth)/mYPixelRange;
//                Log.e(TAG, "SBWY1 "+Float.toString(SBWY1));
                SBWY1= (SBWY1<(-mYPixels))?(-mYPixels):(SBWY1);
                SBWY2= (SBWY2<(-mYPixels))?(-mYPixels):(SBWY2);
                RBWY1= (RBWY1<(-mYPixels))?(-mYPixels):(RBWY1);
                RBWY2= (RBWY2<(-mYPixels))?(-mYPixels):(RBWY2);
                //Log.e(TAG, "SBWY1 "+Float.toString(SBWY1));
                paint.setColor(Color.RED);
                canvas.drawLine(X1,VBRY1,X2,VBRY2,paint);
                paint.setColor(Color.rgb(0, 255, 255));
                canvas.drawLine(X1,SBWY1,X2,SBWY2,paint);
                paint.setColor(Color.YELLOW);
                canvas.drawLine(X1,RBWY1,X2,RBWY2,paint);
                paint.setColor(Color.rgb(255, 128, 64));
                canvas.drawLine(X1,DBRY1,X2,DBRY2,paint);
                i++;
                tmpIndex++;
            }
        }
        {//画点
            i=0;
            tmpIndex = mStartIndex;
            paint.setStrokeWidth(3);
            while(i<mInfoNum)
            {
                float X2 = 0 + i/mXPixelRange;
                float SBRY2 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].PLVideoBitRate)/mYPixelRange;
                float DBRY2 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].DLVideoBitRate)/mYPixelRange;
                float SBWY2 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].SMBandwidth)/mYPixelRange;
                float RBWY2 = 0 -(float)(mInfoArray[tmpIndex%MAXPOINTS].RTBandwidth)/mYPixelRange;
                SBWY2= (SBWY2<(-mYPixels))?(-mYPixels):(SBWY2);
                RBWY2= (RBWY2<(-mYPixels))?(-mYPixels):(RBWY2);
                paint.setColor(Color.RED);
                canvas.drawPoint(X2,SBRY2,paint);
                paint.setColor(Color.rgb(0, 255, 255));
                canvas.drawPoint(X2,SBWY2,paint);
                paint.setColor(Color.YELLOW);
                canvas.drawPoint(X2,RBWY2,paint);
                paint.setColor(Color.rgb(255, 128, 64));
                canvas.drawPoint(X2,DBRY2,paint);
                i++;
                tmpIndex++;
            }
            if(mInfoNum > 0)
            {
                paint.setColor(Color.YELLOW);
                canvas.drawText("  RTBandwidth(kbps): " + mInfoArray[mEndIndex].RTBandwidth, mXPixels-60,-mYPixels - 20, paint);
                paint.setColor(Color.rgb(0, 255, 255));
                canvas.drawText("  SMBandwidth(kbps): " + mInfoArray[mEndIndex].SMBandwidth, mXPixels-60,-mYPixels, paint);
                paint.setColor(Color.RED);
                canvas.drawText("PLVideoBitRate(kbps): " + mInfoArray[mEndIndex].PLVideoBitRate, mXPixels-60,-mYPixels+20, paint);
                paint.setColor(Color.rgb(255, 128, 64));
                canvas.drawText("DLVideoBitRate(kbps): " + mInfoArray[mEndIndex].DLVideoBitRate, mXPixels-60,-mYPixels+40, paint);
                paint.setColor(Color.GREEN);
                canvas.drawText("     BufferedTime(ms): " + mInfoArray[mEndIndex].BufferedTime, mXPixels-60,-mYPixels + 60, paint);
            }
        }
    }
    //Xmax = 600;Ymax = 400;
    private void DrawXY(Canvas canvas,int maxTimeSec)
    {
        Paint paint = mPaint;
        paint.setColor(Color.RED);
        paint.setStrokeWidth(0);
        canvas.drawLine(0,0,0,0-mYPixels,paint);
        canvas.drawLine(0,0,0+mXPixels,0,paint);
        paint.setTextSize(18);
        paint.setTextAlign(Paint.Align.CENTER);
        for(int i = 0;i<30;i++)
        {
            //画X轴刻度
            if(i%10 == 9)
            {
                canvas.drawLine(0 + 20*(i+1),0-20,0 + 20*(i+1),0,paint);
                canvas.drawText(Integer.toString(maxTimeSec - MAXPOINTS+i+1), 20*(i+1),20, paint);
            }
            else
            {
                canvas.drawLine(0 + 20*(i+1),0-10,0 + 20*(i+1),0,paint);
            }
        }
        canvas.drawText("(s)", mXPixels+20,0, paint);
        for(int i = 0;i<20;i++)
        {
            //画Y轴刻度
            if(i%10 == 9)
            {
                canvas.drawLine(20,-20*(i+1),0,-20*(i+1),paint);
                canvas.drawText(Integer.toString((int)((i+1)*mYRange/20)), -30,-20*(i+1), paint);
            }
            else
            {
                canvas.drawLine(0 + 10,0-20*(i+1),0,0-20*(i+1),paint);
            }
        }
        canvas.drawText("kbps", 0,-(mYPixels+20), paint);
    }
    class DrawThread implements Runnable {

        public void run() {
            try
            {
                mDrawState = 1;
                while(mDrawState == 1)
                {
                    long timeNow = System.currentTimeMillis();
                    if((timeNow - mTimeOfGetData)>=GETDATAINTERVAL)
                    {//达到数据刷新时间
                        mTimeOfGetData = timeNow;
                        if(mListener != null)
                        {//可以请求数据
                            AHSMonitorInfo info = null;
                            if(mInfoNum == 0)
                            {//获取第一组数据
                                info = mListener.onGetAHSData(-1);
                            }
                            else
                            {//获取最后一组之后的一组数据
                                info = mListener.onGetAHSData(mInfoArray[mEndIndex].time);
                            }
                            if(info != null)
                            {//成功获取到数据
                                if(mInfoNum != MAXPOINTS)//还没有充满AHSMonitorInfo数组
                                {
                                    mStartIndex = 0;
                                    mInfoNum++;
                                    mEndIndex++;
                                    mInfoArray[mEndIndex] = info;
                                }
                                else//已经充满AHSMonitorInfo数组,endIndex更新为startIndex,startIndex++，
                                {
                                    mEndIndex = mStartIndex;
                                    mStartIndex++;
                                    if(mStartIndex == MAXPOINTS)
                                    {
                                        mStartIndex = 0;
                                    }
                                    mInfoArray[mEndIndex] = info;
                                }
                                //刷新数据
                                postInvalidate();
                            }
                            else
                            {
                                //不需要刷新
                            }
                        }
                        else
                        {
                            //不需要刷新
                        }
                    }
                    else
                    {
                        //不需要刷新
                    }
                    Thread.sleep(50);
                }
                mDrawState = 3;
            }catch(Exception e)
            {
                Log.e(TAG, "DrawThread" + e.getMessage());
                mDrawState = 3;
            }
        }
   }
}
