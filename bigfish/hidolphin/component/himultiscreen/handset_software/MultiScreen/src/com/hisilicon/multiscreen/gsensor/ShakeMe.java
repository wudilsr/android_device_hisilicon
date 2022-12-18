package com.hisilicon.multiscreen.gsensor;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Vibrator;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Shake detector.<br>
 * CN:摇一摇监控。
 */
public class ShakeMe
{
    /**
     * CN:判定摇动手机的线性加速度的阈值。
     */
    private static final float SHAKE_SENSOR_VALUE = 10;

    private static final int MAX_RECORDING_TIMES = 20;

    private static final int MAX_LINE_ACC_TIMES = 6;

    private SensorManager mSensormanager = null;

    private Sensor mLineSensor = null;

    private SensorEventListener mSensorEventListener = null;

    private IShakeListener mShakeListener = null;

    /**
     * An instance of the system vibrator.<br>
     * CN:系统振动控制实例。
     */
    private Vibrator mVibrator = null;

    private boolean isEnable = false;

    /**
     * CN:摇一摇次数。
     */
    private int mShakeTimes = 0;

    /**
     * True if recording begin.<br>
     */
    private boolean mIsRecording = false;

    /**
     * Total times of recording sensor.<br>
     */
    private int mRecordingTimes = 0;

    /**
     * Total times of line ACC.<br>
     */
    private float mTotalLineAccTimes = 0;

    /**
     * Construction.
     * @param context
     * @param shakeListener
     */
    public ShakeMe(Context context, IShakeListener shakeListener)
    {
        initSensor(context);
        setListener(shakeListener);
        initVibrator(context);
    }

    public void setListener(IShakeListener shakeListener)
    {
        mShakeListener = shakeListener;
    }

    public void enable()
    {
        reset();
        isEnable = registerSensor();
    }

    public void disable()
    {
        reset();
        unregisterSensor();
        isEnable = false;
    }

    public void doVibrate()
    {
        long[] pattern =
        { 0, 300, 200, 300 };
        // It is shaken.
        mVibrator.vibrate(pattern, -1);
    }

    private void initSensor(Context context)
    {
        mSensormanager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);
        // CN:采用线性加速度，屏蔽重力。
        mLineSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_LINEAR_ACCELERATION);

        mSensorEventListener = new SensorEventListener()
        {
            @Override
            public void onSensorChanged(SensorEvent event)
            {
                if (event.sensor.getType() == Sensor.TYPE_LINEAR_ACCELERATION)
                {
                    handleSensorEvent(event.values[0], event.values[1]);
                }
            }

            @Override
            public void onAccuracyChanged(Sensor s, int accuracy)
            {
            }
        };
    }

    private void initVibrator(Context context)
    {
        mVibrator = (Vibrator) context.getSystemService(Context.VIBRATOR_SERVICE);
    }

    private void reset()
    {
        mShakeTimes = 0;
        resetRecord();
    }

    private void resetRecord()
    {
        mIsRecording = false;
        mRecordingTimes = 0;
        mTotalLineAccTimes = 0;
    }

    /**
     * Handle sensor event.<br>
     * CN:处理体感事件，屏幕正向(Z轴)晃动不处理。
     * @param x
     * @param y
     */
    private void handleSensorEvent(float x, float y)
    {
        // LogTool.d("test x=" + x + ",y=" + y);

        if (mIsRecording == false && isLineAcc(x, y))
        {
            // LogTool.d("Begin to recording.");
            mIsRecording = true;
            mRecordingTimes = MAX_RECORDING_TIMES;
            mTotalLineAccTimes = 1;
        }
        else if (mIsRecording && mRecordingTimes > 0)
        {
            mRecordingTimes--;

            if (isLineAcc(x, y))
            {
                mTotalLineAccTimes++;
            }

            if (mTotalLineAccTimes >= MAX_LINE_ACC_TIMES)
            {
                // LogTool.d("End recording:" + mTotalPositiveTimes + ", " +
                // mTotalNegativeTimes);
                shake();
                resetRecord();
            }

            if (mRecordingTimes == 0)
            {
                resetRecord();
            }
        }
    }

    /**
     * True if line ACC value more than SHAKE_SENSOR_VALUE.<br>
     * CN:当线性加速度超过阈值则返回真。
     * @param x
     * @param y
     * @return
     */
    private boolean isLineAcc(float x, float y)
    {
        if (Math.abs(x) > SHAKE_SENSOR_VALUE || Math.abs(y) > SHAKE_SENSOR_VALUE)
        {
            return true;
        }
        return false;
    }

    /**
     * Notify listener shake happened.<br>
     * CN:通知监听者手机摇一摇触发。
     */
    private void shake()
    {
        mShakeTimes++;
        mShakeListener.shake(mShakeTimes, 0);
        // LogTool.d("shake end:" + System.currentTimeMillis());
    }

    /**
     * Register sensors.<br>
     * CN:注册感应器，注意不要重复注册，影响性能。
     * @return true if success
     */
    private boolean registerSensor()
    {
        boolean isOK = false;

        if (mSensormanager == null)
        {
            LogTool.e("Fail to enable shakeMe, sensormanger is null.");
            isOK = false;
        }
        else if (isEnable)
        {
            // ShakeMe has been enable, do not register it again.
            isOK = true;
        }
        else
        {
            isOK = registerSensor(mLineSensor);
        }

        return isOK;
    }

    /**
     * Register sensor.<br>
     * SENSOR_DELAY_GAME:20ms SENSOR_DELAY_UI:60ms SENSOR_DELAY_NORMAL:200ms
     * @param sensor
     * @return
     */
    private boolean registerSensor(Sensor sensor)
    {
        return mSensormanager.registerListener(mSensorEventListener, sensor,
            SensorManager.SENSOR_DELAY_UI);
    }

    private void unregisterSensor()
    {
        if (mSensormanager != null)
        {
            mSensormanager.unregisterListener(mSensorEventListener);
        }
    }
}
