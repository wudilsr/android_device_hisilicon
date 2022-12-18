package com.hisilicon.multiscreen.gsensor;

import java.util.List;

import android.content.Context;
import android.hardware.Sensor;
import android.hardware.SensorEvent;
import android.hardware.SensorEventListener;
import android.hardware.SensorManager;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.remote.RemoteKeyboard;
import com.hisilicon.multiscreen.protocol.remote.RemoteMouse;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Air mouse.<br>
 * CN:空鼠。
 */
public class AirMouse
{
    /**
     * Default minimum distance of move step.<br>
     * CN:最小位移量，用于防抖。
     */
    private static final float MIN_MOVE_STEP = 2;

    /**
     * If mouse click down, set minimum distance of move step with the value.<br>
     */
    private static final float ANTI_SHAKE_MOVE_STEP = 8;

    /**
     * CN:最大X位移，用于隐藏鼠标。
     */
    private static final float MAX_MOVE_X = 3840;

    private static final float MAX_MOVE_Y = 2160;

    /**
     * Message of set anti-shake delay.<br>
     */
    private static final int MSG_ANTI_SHAKE = 1;

    private static final int MSG_HIDE_MOUSE = MSG_ANTI_SHAKE + 1;

    private static final long DELAY_MILLIS_ANTI_SHAKE = 500;

    private static final long DELAY_MILLIS_HIDE_MOUSE = 100;

    /**
     * True if air mouse library is loaded.<br>
     */
    private static boolean sLoaded = false;

    /**
     * True if air mouse is enable.<br>
     */
    private boolean mIsEnable = false;

    private SensorManager mSensormanager = null;

    private SensorEventListener mSensorEventListener = null;

    private Sensor gyroSensor = null;

    private Sensor accSensor = null;

    private Sensor mgcSensor = null;

    private Sensor gravSensor = null;

    /**
     * 0-2 GYRO 3-5 GRAV.<br>
     */
    private float[] newInputArray =
    { 0, 0, 0, 0, 0, 0, 0, 0, 0 };

    /**
     * Mouse move values.<br>
     */
    private float[] sendCoord =
    { 0, 0 };

    /**
     * Remote mouse.<br>
     */
    private RemoteMouse mMouse = null;

    /**
     * Remote keyboard.<br>
     * CN:虚拟键盘对象，用于发送键值F12隐藏鼠标。
     */
    private RemoteKeyboard mRemoteKeyboard = null;

    /**
     * State of mouse.<br>
     * CN:鼠标状态。
     */
    private int mMouseState = RemoteMouse.MOUSE_ACTION_MOVE;

    /**
     * Time stamp of sensor.<br>
     * CN:时间戳，用于测试体感平滑度。
     */
    private long timestamp = 0;

    /**
     * Minimum step of mouse move.<br>
     */
    private float mMinStep = MIN_MOVE_STEP;

    private HandlerThread mHandlerThread = null;

    private AntiShakeHandler AntiShakeHandler = null;

    private HandlerThread mHideHandlerThread = null;

    private HideMouseHandler mHideMouseHandler = null;

    /**
     * Construction of air mouse.<br>
     * @param context
     * @param mouse
     */
    public AirMouse(Context context)
    {
        reset(context);
    }

    public void reset(Context context)
    {
        initRemote();
        initSensor(context);
        initHideHandler();
    }

    public void deinit()
    {
        unregisterSensor();
        deinitAntiShakeHandler();
        deinitHideHandler();
        mIsEnable = false;
    }

    public boolean isSupported()
    {
        boolean isSupported;
        List<Sensor> sensorList = mSensormanager.getSensorList(Sensor.TYPE_GYROSCOPE);
        if (sensorList.isEmpty())
        {
            LogTool.e("Airmouse is not supported without GYR sensor.");
            isSupported = false;
        }
        else
        {
            isSupported = true;
        }
        return isSupported;
    }

    /**
     * Enable air mouse.<br>
     * @return True if the GYR sensor is supported and successfully enabled.
     */
    public boolean enable()
    {
        cancelHide();
        mIsEnable = registerSensor(gyroSensor);
        if (mIsEnable)
        {
            // registerSensor(accSensor);
            mIsEnable = registerSensor(gravSensor);
            // registerSensor(mgcSensor);
            initAntiShakeHandler();
        }
        return mIsEnable;
    }

    /**
     * Disable air mouse.<br>
     */
    public void disable()
    {
        unregisterSensor();
        deinitAntiShakeHandler();
        hideMouse();
        mIsEnable = false;
    }

    /**
     * Mouse down.<br>
     */
    public void down()
    {
        if (mMouseState != RemoteMouse.MOUSE_LEFT_DOWN_MOVE)
        {
            increaseAntiShake();
            mMouse.sendMouseClickEvent(RemoteMouse.MOUSE_LEFT_DOWN);
            mMouseState = RemoteMouse.MOUSE_LEFT_DOWN_MOVE;
        }
    }

    /**
     * Mouse up.<br>
     */
    public void up()
    {
        reduceAntiShake();
        mMouse.sendMouseClickEvent(RemoteMouse.MOUSE_LEFT_UP);
        mMouseState = RemoteMouse.MOUSE_ACTION_MOVE;
    }

    /**
     * Calculate air mouse move with GYR GRV.<br>
     */
    private void move()
    {
        native_getAirCoord(mMinStep, newInputArray, sendCoord);
        // LogTool.d("ztest sendCoordX=" + mAirData.sendCoord[0] +
        // ",sendCoordY="
        // + mAirData.sendCoord[1]);
        mMouse.sendMouseMoveEvent(mMouseState, sendCoord[0], sendCoord[1]);
    }

    private void initRemote()
    {
        loadAirMouseLibs();
        MultiScreenControlService controlService = MultiScreenControlService.getInstance();
        if (controlService != null)
        {
            mMouse = controlService.getRemoteControlCenter().getRemoteMouse();
            mRemoteKeyboard = controlService.getRemoteControlCenter().getRemoteKeyboard();
        }
        else
        {
            LogTool.e("Fail to init remote, MultiScreenControlService is null.");
        }
    }

    private void setSensorManager(Context context)
    {
        if (context == null)
        {
            LogTool.e("context is null");
            return;
        }
        mSensormanager = (SensorManager) context.getSystemService(Context.SENSOR_SERVICE);

        gyroSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_GYROSCOPE);
        accSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_ACCELEROMETER);
        mgcSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_MAGNETIC_FIELD);
        gravSensor = mSensormanager.getDefaultSensor(Sensor.TYPE_GRAVITY);
    }

    private void initSensor(Context context)
    {
        setSensorManager(context);

        if (mSensorEventListener == null)
        {
            mSensorEventListener = new SensorEventListener()
            {
                @Override
                public void onSensorChanged(SensorEvent event)
                {
                    switch (event.sensor.getType())
                    {
                        case Sensor.TYPE_GYROSCOPE:
                        {
                            newInputArray[0] = event.values[0];
                            newInputArray[1] = event.values[1];
                            newInputArray[2] = event.values[2];
                            // LogTool.d("ztest newGyrX=" + mAirData.newGyr[0] +
                            // ",newGyrY="
                            // + mAirData.newGyr[1] + ",newGyrZ=" +
                            // mAirData.newGyr[2]);

                            // LogTool.d("ztest event.timestamp:" +
                            // ((event.timestamp -
                            // timestamp)/1000000));
                            // timestamp = event.timestamp;

                            move();
                        }
                            break;
                        case Sensor.TYPE_GRAVITY:
                        {
                            newInputArray[3] = event.values[0];
                            newInputArray[4] = event.values[1];
                            newInputArray[5] = event.values[2];

                            // LogTool.d("[grvSensor]newX=" + mAirData.newGrvX +
                            // ",newY="
                            // + mAirData.newGrvY + ",newZ=" +
                            // mAirData.newGrvZ);
                        }
                            break;
                        case Sensor.TYPE_ACCELEROMETER:
                        {
                            newAcc[0] = event.values[0];
                            newAcc[1] = event.values[1];
                            newAcc[2] = event.values[2];

                            // mAirData.calculateOrientation();
                            // LogTool.d("[accSensor]newX=" + newAccX + ",newY="
                            // +
                            // newAccY + ",newZ="
                            // + newAccZ);
                        }
                            break;
                        case Sensor.TYPE_MAGNETIC_FIELD:
                        {
                            newMgc[0] = event.values[0];
                            newMgc[1] = event.values[1];
                            newMgc[2] = event.values[2];

                            calculateOrientation();
                            // LogTool.d("[accSensor]newMgcX=" +
                            // mAirData.newMgc[0]
                            // +
                            // ",newMgcY="
                            // + mAirData.newMgc[1] + ",newMgcZ=" +
                            // mAirData.newMgc[2]);
                        }
                            break;
                        default:
                            break;
                    }
                }

                @Override
                public void onAccuracyChanged(Sensor s, int accuracy)
                {
                }
            };
        }
    }

    /**
     * True if the sensor is supported and successfully enabled.<br>
     * @param sensor
     * @return
     */
    private boolean registerSensor(Sensor sensor)
    {
        return mSensormanager.registerListener(mSensorEventListener, sensor,
            SensorManager.SENSOR_DELAY_GAME);
    }

    /**
     * Unregister sensors of air mouse.<br>
     */
    private void unregisterSensor()
    {
        if (mSensormanager != null)
        {
            mSensormanager.unregisterListener(mSensorEventListener);
        }
    }

    /**
     * Set MIN step of move for anti-shake.<br>
     * CN:设置最小位移，用于防抖。
     * @param step
     */
    private void setMinStep(float step)
    {
        final float DEFAULT_MIN_STEP = 10;
        if (step > DEFAULT_MIN_STEP)
        {
            step = DEFAULT_MIN_STEP;
            LogTool.e("ERROR: minStep is large than " + DEFAULT_MIN_STEP);
        }
        mMinStep = step;
    }

    /**
     * Increase anti-shake for a while.<br>
     * CN:鼠标点击时，短暂提高防抖。
     */
    private void increaseAntiShake()
    {
        setMinStep(ANTI_SHAKE_MOVE_STEP);
        reduceAntiShakeDelay();
    }

    private void reduceAntiShake()
    {
        setMinStep(MIN_MOVE_STEP);
    }

    private void initAntiShakeHandler()
    {
        if (mHandlerThread == null)
        {
            mHandlerThread = new HandlerThread("AirMouseHandlerThread");
            mHandlerThread.start();
            AntiShakeHandler = new AntiShakeHandler(mHandlerThread.getLooper());
        }
    }

    private void deinitAntiShakeHandler()
    {
        if (mHandlerThread != null)
        {
            clearAntiShakeMessage();
            Looper looper = mHandlerThread.getLooper();
            if (looper != null)
            {
                looper.quit();
            }
            mHandlerThread = null;
        }
    }

    private void clearAntiShakeMessage()
    {
        if (AntiShakeHandler.hasMessages(MSG_ANTI_SHAKE))
        {
            AntiShakeHandler.removeMessages(MSG_ANTI_SHAKE);
        }
    }

    private void reduceAntiShakeDelay()
    {
        clearAntiShakeMessage();

        Message msg = AntiShakeHandler.obtainMessage(MSG_ANTI_SHAKE);
        AntiShakeHandler.sendMessageDelayed(msg, DELAY_MILLIS_ANTI_SHAKE);
    }

    private class AntiShakeHandler extends Handler
    {
        AntiShakeHandler(Looper looper)
        {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MSG_ANTI_SHAKE:
                {
                    setMinStep(MIN_MOVE_STEP);
                }
                    break;
                default:
                    break;
            }
        }
    }

    private boolean isEnable()
    {
        return mIsEnable;
    }

    private void initHideHandler()
    {
        mHideHandlerThread = new HandlerThread("AirMouseHideHandlerThread");
        mHideHandlerThread.start();
        mHideMouseHandler = new HideMouseHandler(mHideHandlerThread.getLooper());
    }

    private void deinitHideHandler()
    {
        if (mHideHandlerThread != null)
        {
            clearHideMessage();
            Looper looper = mHideHandlerThread.getLooper();
            if (looper != null)
            {
                looper.quit();
            }
            mHideHandlerThread = null;
        }
    }

    /**
     * Hide mouse.<br>
     */
    private void hideMouse()
    {
        if (mMouse != null && isEnable())
        {
            up();
            startHideMouse();
        }
    }

    /**
     * Cancel hide mouse.<br>
     */
    private void cancelHide()
    {
        clearHideMessage();
    }

    private void startHideMouse()
    {
        clearHideMessage();

        Message msg = mHideMouseHandler.obtainMessage(MSG_HIDE_MOUSE);
        mHideMouseHandler.sendMessageDelayed(msg, DELAY_MILLIS_HIDE_MOUSE);
    }

    private void clearHideMessage()
    {
        if (mHideMouseHandler.hasMessages(MSG_HIDE_MOUSE))
        {
            mHideMouseHandler.removeMessages(MSG_HIDE_MOUSE);
        }
    }

    private class HideMouseHandler extends Handler
    {
        HideMouseHandler(Looper looper)
        {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg)
        {
            switch (msg.what)
            {
                case MSG_HIDE_MOUSE:
                {
                    handleHideMouse();
                }
                    break;

                default:
                    break;
            }
        }
    }

    private void handleHideMouse()
    {
        final int TIME_AFTER_MOUSE = 50;
        final int TIME_AFTER_KEY = 500;

        // CN:将鼠标移到右下角，再发送无效键值，隐藏鼠标。
        if (mMouse != null)
        {
            mMouse.sendMouseMoveEvent(RemoteMouse.MOUSE_ACTION_MOVE, MAX_MOVE_X, MAX_MOVE_Y);
            threadSleep(TIME_AFTER_MOUSE);
            mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_F12);
            threadSleep(TIME_AFTER_KEY);
            mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_F12);
        }
    }

    private void threadSleep(int time)
    {
        try
        {
            Thread.sleep(time);
        }
        catch (InterruptedException e)
        {
            LogTool.w(e.getMessage());
        }
    }

    // New and Previous ACC sensor values.<br>
    public float[] newAcc = new float[3];

    // New and Previous MGC sensor values.<br>
    public float[] newMgc = new float[3];

    // Rotation
    public float[] newRotation = new float[3];

    private float[] rotationMatrix = new float[9];

    /**
     * Calculate orientation with ACC and MGC.<br>
     */
    private void calculateOrientation()
    {
        SensorManager.getRotationMatrix(rotationMatrix, null, newAcc, newMgc);
        SensorManager.getOrientation(rotationMatrix, newRotation);
        // CN:地磁方向 0 90 180 -180 -90
        newRotation[0] = (float) Math.toDegrees(newRotation[0]);
        // CN:Y轴与水平夹角 -90 0 90
        newRotation[1] = (float) Math.toDegrees(newRotation[1]);
        newRotation[2] = (float) Math.toDegrees(newRotation[2]);
    }

    /**
     * Load libairmouse_jni.so
     * @return
     */
    private static boolean loadAirMouseLibs()
    {
        if (sLoaded)
        {
            return true;
        }
        boolean err = false;

        try
        {
            LogTool.d("load libairmouse_jni.so");
            System.loadLibrary("airmouse_jni");
        }
        catch (UnsatisfiedLinkError e)
        {
            err = true;
            LogTool.e("Error when Loading our lib: " + e.getMessage());
        }
        if (!err)
        {
            sLoaded = true;
        }
        return sLoaded;
    }

    /**
     * JNI function, get air mouse coordinates.<br>
     * @param min step.
     * @param Input array.
     * @param output mouse coordinates.
     * @return
     */
    private native int native_getAirCoord(float minStep, float[] inputArray, float[] outputMouse);
}
