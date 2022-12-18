package com.hisilicon.multiscreen.gsensor;

import android.app.Service;
import android.content.Intent;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.IBinder;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.remote.RemoteSensor;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Sensor service, for passing sensor events to the server.<br>
 * CN:传感器服务，用于发送体感数据给客户端。
 */
public class SensorService extends Service
{
    /**
     * Max value of gravity.<br>
     */
    public static final float GRAVITY_EARTH = 9.80665f;

    /**
     * Max value of accelerometer.<br>
     */
    public static final float MAX_ACC = 2 * GRAVITY_EARTH;

    private RemoteSensor mSensor = null;

    private SensorManager mSensormanager = null;

    private Sensor mAccSensor = null;

    private Sensor mGyrSensor = null;

    // private Sensor mMgcSensor = null;
    //
    // private Sensor mOrnSensor = null;
    //
    // private Sensor mTemSensor = null;

    /**
     * Sensor event listener.<br>
     * CN:体感事件监听者。
     */
    private SensorEventListener mSensorEventListener = new SensorEventListener()
    {
        // private int sensorType = 0;
        private float x = 0, y = 0, z = 0;

        @Override
        public void onSensorChanged(SensorEvent event)
        {
            // Send event of changes to the server if the sensor changed.<br>
            if (mSensor != null)
            {
                // switch (event.sensor.getType())
                // {
                // case Sensor.TYPE_ACCELEROMETER:
                // {
                // x = event.values[0];
                // y = event.values[1];
                // z = event.values[2];
                // sensorType = RemoteSensor.SENSOR_TYPE_ACCELEROMETER;
                // // LogTool.d("[accSensor]x=" + x + ",y=" + y + ",z=" +
                // // z);
                // }
                // break;
                // case Sensor.TYPE_GYROSCOPE:
                // {
                // x = event.values[0];
                // y = event.values[1];
                // z = event.values[2];
                // sensorType = RemoteSensor.SENSOR_TYPE_GYROSCOPE;
                // // LogTool.d("[mGyrSensor]x=" + x + ",y=" + y + ",z=" +
                // // z);
                // }
                // break;
                // default:
                // break;
                // }

                x = event.values[0];
                y = event.values[1];
                z = event.values[2];
                mSensor.sendSensorEvent(event.sensor.getType(), x, y, z);
            }
        }

        @Override
        public void onAccuracyChanged(Sensor s, int accuracy)
        {
            // Called when the accuracy of a sensor has changed. <br>
        }
    };

    @Override
    public IBinder onBind(Intent intent)
    {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId)
    {
        super.onStartCommand(intent, flags, startId);
        LogTool.d("onStart.");

        setSensorManager();
        mSensor =
            MultiScreenControlService.getInstance().getRemoteControlCenter().getRemoteSensor();

        return START_NOT_STICKY;
    }

    /**
     * Close sensor service.<br>
     * 关闭体感服务。
     */
    @Override
    public void onDestroy()
    {
        LogTool.d("onDestroy");
        super.onDestroy();

        mSensormanager.unregisterListener(mSensorEventListener);
        // CN:不要调用RemoteSensor的destroy方法，会关闭socket，不能再次开启。
        // CN:RemoteSensor的socket关闭，在RemoteControlCenter中完成。
    }

    private void setSensorManager()
    {
        mSensormanager = (SensorManager) getSystemService(SENSOR_SERVICE);

        mAccSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mGyrSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);

        // mMgcSensor =
        // sensormanager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        // mOrnSensor = sensormanager.getDefaultSensor(Sensor.TYPE_ORIENTATION);
        // mTemSensor = sensormanager.getDefaultSensor(Sensor.TYPE_TEMPERATURE);

        registerSensor(mAccSensor);
        registerSensor(mGyrSensor);

        // registerSensor(mMgcSensor);
        // registerSensor(mOrnSensor);
        // registerSensor(mTemSensor);
    }

    private void registerSensor(Sensor sensor)
    {
        mSensormanager.registerListener(mSensorEventListener, sensor,
            SensorManager.SENSOR_DELAY_GAME);
    }
}
