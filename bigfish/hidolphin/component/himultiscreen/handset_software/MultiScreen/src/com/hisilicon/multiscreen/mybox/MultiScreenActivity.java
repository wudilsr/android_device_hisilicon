package com.hisilicon.multiscreen.mybox;

import java.lang.ref.SoftReference;

import android.annotation.SuppressLint;
import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.SharedPreferences;
import android.content.res.Configuration;
import android.graphics.drawable.BitmapDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.util.DisplayMetrics;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.OrientationEventListener;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.view.ViewGroup;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.hisilicon.multiscreen.controller.IAccessListener;
import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.gsensor.SensorService;
import com.hisilicon.multiscreen.mirror.MirrorView;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService.ClientState;
import com.hisilicon.multiscreen.mybox.MultiScreenControlService.TopActivity;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.message.TouchRequest;
import com.hisilicon.multiscreen.protocol.remote.RemoteControlCenter;
import com.hisilicon.multiscreen.protocol.remote.RemoteKeyboard;
import com.hisilicon.multiscreen.protocol.remote.RemoteTouch;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.protocol.utils.ServiceUtil;
import com.hisilicon.multiscreen.scene.ISceneListener;
import com.hisilicon.multiscreen.scene.SceneType;
import com.hisilicon.multiscreen.vime.VImeClientControlService;

/**
 * MultiScreen main activity.<br>
 * CN:????????????????????????
 */
public class MultiScreenActivity extends Activity implements OnClickListener
{
    /**
     * MultiScreen control service.<br>
     * CN:?????????????????????
     */
    private MultiScreenControlService mMultiScreenControlService = null;

    /**
     * Instance of remote control center.<br>
     * CN:???????????????
     */
    public static RemoteControlCenter mRemoteControlCenter = null;

    /**
     * Mirror view for transmiting function.<br>
     * CN:???????????????MirrorView???
     */
    public MirrorView mMirrorView = null;

    public LinearLayout mLayout = null;

    /**
     * Handle message for showing packet loss toast.<br>
     * CN:?????????????????????
     */
    public static final int KEEP_ALIVE_PACKET_LOSS = 10;

    /**
     * Handle message for showing failed dialog.<br>
     * CN:???????????????
     */
    public static final int KEEP_ALIVE_FAILED = 20;

    /**
     * Access reaved.<br>
     * CN:???????????????
     */
    public static final int ACCESS_REAVED = 30;

    /**
     * STB leave.<br>
     * CN:STB???????????????
     */
    public static final int STB_LEAVE = 40;

    /**
	 *
	 */
    public static final int START_SYNC_STB_INFO = 50;

    /**
	 *
	 */
    public static final int STOP_SYNC_STB_INFO = 60;

    /**
     * STB suspend.<br>
     * CN:STB???????????????
     */
    public static final int STB_SUSPEND = 80;

    /**
     * Max width of touch device in STB.<br>
     * 1280*720 1920*1080 3840*2160.
     */
    private static final int MAX_STB_TOUCH_WIDTH = 1279;

    /**
     * Max height of touch device in STB.<br>
     */
    private static final int MAX_STB_TOUCH_HEIGHT = 719;

    /**
     * CN:???????????????
     */
    private Button mControl_close;

    /**
     * CN:????????????????????????????????????
     */
    private RelativeLayout mControl_layout;

    /**
     * CN:???????????????
     */
    private Button mControl_back;

    /**
     * CN:???????????????
     */
    private Button mControl_more;

    private int currentX;

    private int currentY;

    private int mLayoutWidth = 0;

    private int mCloseWidth = 0;

    /**
     * CN:?????????????????????????????????
     */
    private MultiScreenMorePop mMorePop;

    /**
     * CN:home?????????
     */
    private Button mControl_pop_home;

    /**
     * CN:menu?????????
     */
    private Button mControl_pop_menu;

    /**
     * CN:vol?????????
     */
    private Button mControl_pop_vol;

    /**
     * CN:game?????????
     */
    private Button mControl_pop_game;

    /**
     * CN:?????????????????????
     */
    // private RelativeLayout mControl_error;

    /**
     * CN:????????????????????????
     */
    private boolean remote_game_flag = false;

    private View parent;

    private DisplayMetrics dm = null;

    /**
     * Width of screen: size of screen will change when virtual key hides.<br>
     * CN:????????????????????????????????????????????????????????????
     */
    private int screenWidth = 0;

    /**
     * Height of screen: size of screen will change when virtual key hides.<br>
     * CN:????????????????????????????????????????????????????????????
     */
    private int screenHeight = 0;

    // private MirrorfpsControl mMirrorfpsControl = null;

    private static boolean sLoaded;

    /**
     * Remote Touch event response <br>
     * CN:???????????????????????????
     */
    private RemoteTouch mRemoteTouch = null;

    private TouchRequest mTouchInfo = new TouchRequest();

    /**
     * Remote keyboard event response <br>
     * CN:???????????????????????????
     * @see RemoteControlCenter
     */
    public static RemoteKeyboard mRemoteKeyboard = null;

    private int countMove = 0;

    /**
     * Access ping listener.<br>
     * CN:???????????????????????????
     */
    private IAccessListener mAccessListener = null;

    /**
     * Recognize scene listener.<br>
     * CN:?????????????????????
     */
    private ISceneListener mSceneListener = null;

    /**
     * Detector of orientation.<br>
     * CN:??????????????????
     */
    private OrientationDetector mOrientationDetector = null;

    /**
     * Touch value: finger is pressed.
     */
    private static final boolean FINGER_PRESSED = true;

    /**
     * TOuch value: finger is up.
     */
    private static final boolean FINGER_UP = false;

    /**
     * Handler of access event.
     */
    private AccessEventHandler mAccessEventHandler = null;

    /**
     * Context of this.
     */
    private Context mContext = null;

    private boolean vime_status;

    /**
     * Detector of phone orientation.<br>
     */
    public class OrientationDetector extends OrientationEventListener
    {
        public OrientationDetector(Context context)
        {
            super(context);
        }

        @Override
        public void onOrientationChanged(int orientation)
        {
            if (orientation == OrientationEventListener.ORIENTATION_UNKNOWN)
            {
                // CN:????????????????????????????????????????????????
                return;
            }
            else if (orientation > 350 || orientation < 10)
            { // 0???????????????????????????
              // Toast.makeText(mContext, "start remote",
              // Toast.LENGTH_SHORT).show();
                LogTool.d("To finish mirror activity");
                int select = checkRemoteIntent();

                if (MessageDef.REMOTE_AIRMOUSE == select)
                {
                    gotoAirMouse();
                }
                else if (MessageDef.REMOTE_TOUCH == select)
                {
                    gotoRemoteTouch();
                }
                else
                {
                    gotoRemoteTouch();
                }
            }
        }
    }

    /**
     * Called when the activity is starting.<br>
     * Initial control and start transmit screen.<br>
     * CN:?????????????????????????????????????????????????????????
     */
    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        LogTool.d("onCreate.");
        super.onCreate(savedInstanceState);

        loadMirrorLibs();
        setStrictMode();
        initData();
        initView();
        syncInfo();
    }

    @Override
    public void onNewIntent(Intent intent)
    {
        LogTool.d("onNewIntent");
        super.onNewIntent(intent);
        handleIntent();
    }

    @Override
    public void onConfigurationChanged(Configuration newConfig)
    {
        LogTool.d("onConfigurationChanged");
        super.onConfigurationChanged(newConfig);
    }

    @Override
    public void onResume()
    {
        LogTool.d("on resume.");
        super.onResume();
        resumeActivity();
    }

    @Override
    public void onPause()
    {
        LogTool.d("onPause");
        super.onPause();
        clearSceneListener();
        disableOrientationDetector();
        stopMirror();
        stopGsensor();
    }

    /**
     * OnStop activity.<br>
     * CN:??????????????????
     */
    @Override
    public void onStop()
    {
        LogTool.d("onStop");
        super.onStop();
    }

    @Override
    public void onDestroy()
    {
        LogTool.d("onDestroy");
        super.onDestroy();
        doFinishWork();
    }

    /**
     * Do handling key down even.<br>
     * CN:?????????????????????
     */
    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        if (keyCode == KeyEvent.KEYCODE_BACK)
        {
            exitImageControl();
            return true;
        }
        return super.onKeyDown(keyCode, event);
    }

    /**
     * Callback of click listener.<br>
     * CN????????????????????????????????????
     */
    @Override
    public void onClick(View view)
    {
        if (mMorePop != null)
        {
            mMorePop.dismiss();
        }

        switch (view.getId())
        {
            case R.id.control_back:
                mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_BACK);
                break;

            case R.id.control_more:
            {
                mMorePop.showAtLocation(this.findViewById(R.id.control_more),
                        Gravity.CENTER_HORIZONTAL, 0, 0);
                if (remote_game_flag == true)
                {
                    mControl_pop_game.setBackgroundResource(R.drawable.image_control_game_focus);
                }
                else
                {
                    mControl_pop_game.setBackgroundResource(R.drawable.image_control_game);
                }
            }
                break;

            case R.id.control_close:
                exitImageControl();
                break;

            case R.id.control_pop_home:
                mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_HOME);
                break;

            case R.id.control_pop_menu:
                mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_MENU);
                break;

            case R.id.control_pop_vol:
                mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_VOLUME_UP);
                mRemoteKeyboard.sendDownAndUpKeyCode(KeyInfo.KEYCODE_VOLUME_DOWN);
                break;

            case R.id.control_pop_game:
                remote_game_flag = !remote_game_flag;
                if (remote_game_flag == true)
                {
                    mControl_pop_game.setBackgroundResource(R.drawable.image_control_game_focus);
                    startGsensor();
                }
                else
                {
                    mControl_pop_game.setBackgroundResource(R.drawable.image_control_game);
                    stopGsensor();
                }
                break;

            default:
                break;
        }
    }

    /**
     * Finish activity on destroy.<br>
     * CN:????????????????????????
     */
    private void doFinishWork()
    {
        unbindDrawables(findViewById(R.layout.mybox_image_control));
        mMirrorView = null;
        mContext = null;
        stopGsensor();
        deInitVIMEService();
    }

    /**
     * Release view object.<br>
     * CN:??????View?????????
     * @param view - View object to be released.<br>
     *        CN:???????????????View?????????
     */
    private void unbindDrawables(View view)
    {
        if (view != null)
        {
            if (view.getBackground() != null)
            {
                view.getBackground().setCallback(null);
            }
            if (view instanceof ViewGroup)
            {
                for (int i = 0; i < ((ViewGroup) view).getChildCount(); i++)
                {
                    unbindDrawables(((ViewGroup) view).getChildAt(i));
                }
                ((ViewGroup) view).removeAllViews();
            }
        }
        view = null;
    }

    /**
     * CN:???????????????
     */
    private void exitImageControl()
    {
        DialogUtils.showCancelDialog(mContext, R.string.quitDialogTitle,
                R.string.quitDialogContent, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        gotoDeviceDiscovery();
                    }
                }, null);
    }

    private void resumeActivity()
    {
        mMultiScreenControlService.setTopActivity(TopActivity.mirror);
        enableOrientationDetector();
        resetAccessListener();
        resetSceneListener();
        checkState();
    }

    /**
     * CN:?????????????????????<br>
     * CN:????????????????????????????????????????????????
     */
    private void initOrientationDetector()
    {
        int remoteStatus = checkRemoteIntent();
        // CN:???intent???remoteStatus???????????????0????????????????????????????????????
        if (remoteStatus != 0)
        {
            // FIXME ???????????????
            // mOrientationDetector = new MyOrientationDetector(this);
        }
    }

    private void enableOrientationDetector()
    {
        if (mOrientationDetector != null)
        {
            mOrientationDetector.enable();
        }
    }

    private void disableOrientationDetector()
    {
        if (mOrientationDetector != null)
        {
            mOrientationDetector.disable();
        }
    }

    /**
     * Reset access listener.
     */
    private void resetAccessListener()
    {
        if (mAccessEventHandler == null)
        {
            mAccessEventHandler = new AccessEventHandler(this);
        }

        if (mAccessListener == null)
        {
            mAccessListener = new IAccessListener()
            {
                @Override
                public void dealNetWorkNotWellEvent()
                {
                    // keep alive packet loss.
                    mAccessEventHandler.sendEmptyMessage(KEEP_ALIVE_PACKET_LOSS);
                }

                @Override
                public void dealNetWorkLostEvent(Caller caller)
                {
                    // Keep alive fail.
                    LogTool.d("keep alive fail.");
                    sendAccessStatusMessage(caller, KEEP_ALIVE_FAILED);
                }

                @Override
                public void dealReaveEvent(Caller caller)
                {
                    // Be reaved.
                    LogTool.d("be reaved.");
                    sendAccessStatusMessage(caller, ACCESS_REAVED);
                }

                @Override
                public void dealSTBLeaveEvent(Caller caller)
                {
                    // STB leave.
                    LogTool.d("STB leave.");
                    sendAccessStatusMessage(caller, STB_LEAVE);
                }

                @Override
                public void dealSTBSuspendEvent(Caller caller)
                {
                    // STB suspend
                    LogTool.d("STB suspend.");
                    sendAccessStatusMessage(caller, STB_SUSPEND);
                }
            };
        }

        mMultiScreenControlService.setAllAccessListener(mAccessListener);
    }

    /**
     * Clear access listener.<br>
     * CN:???????????????
     */
    private void clearAccessListener()
    {
        mMultiScreenControlService.setAllAccessListener(null);
    }

    private void resetSceneListener()
    {
        if (mSceneListener == null)
        {
            mSceneListener = new ISceneListener()
            {
                @Override
                public void sceneChanged(SceneType sceneType)
                {
                    dealSceneChanged(sceneType);
                }
            };
        }
        mMultiScreenControlService.setSceneListener(mSceneListener);
    }

    private void clearSceneListener()
    {
        mMultiScreenControlService.setSceneListener(null);
    }

    private void dealSceneChanged(SceneType sceneType)
    {
        switch (sceneType)
        {
            case REMOTE_TOUCH:
            {
                gotoRemoteTouch();
            }
                break;
            case REMOTE_AIRMOUSE:
            {
                gotoAirMouse();
            }
                break;
            case MIRROR_SENSOR:
            {
                gotoMirrorSensor();
            }
                break;
            default:
            {
                gotoRemoteTouch();
            }
                break;
        }
    }

    /**
     * Close current activity.<br>
     * CN:???????????????
     * @param clientState state of client now.
     */
    private void finishCurActivity(ClientState clientState)
    {
        finishCurActivity(Caller.Others, clientState);
    }

    private void finishCurActivity(Caller caller, ClientState clientState)
    {
        clearAccessListener();
        deInitNetworkChecker(caller, clientState);
        sendByeToSTB(clientState);
        stopGsensor();
        deInitVIMEService();
        deInitRemoteCenter();
    }

    /**
     * Start mirror.<br>
     * @return result of start mirror.
     */
    private boolean startMirror()
    {
        LogTool.d("Start mirror.");
        boolean isOK = mMultiScreenControlService.startMirror(2);

        // if (mMirrorfpsControl != null)
        // {
        // mMirrorfpsControl.start(mMirrorView);
        // }

        if (isOK == false)
        {
            LogTool.e("Start mirror failed.");
            mAccessEventHandler.sendEmptyMessage(KEEP_ALIVE_FAILED);
        }
        return isOK;
    }

    /**
     * Stop mirror.<br>
     * @return result of stop mirror.
     */
    private boolean stopMirror()
    {
        LogTool.d("Stop mirror.");
        boolean isOK = false;

        if (mMultiScreenControlService.isRunning()
                || (mMultiScreenControlService.getState() == ClientState.NETWORK_LOST))
        {
            isOK = mMultiScreenControlService.stopMirror(1);
            if (isOK == false)
            {
                LogTool.w("Fail to stop mirror.");
            }
        }
        else
        {
            // CN:????????????stopMirror?????????????????????????????????????????????STB????????????????????????
        }

        return isOK;
    }

    /**
     * Deal packet loss.<br>
     * CN:?????????????????????
     */
    private void dealPacketLoss()
    {
        Toast.makeText(this, getResources().getString(R.string.toast_KeepAlive_packet_loss),
                Toast.LENGTH_SHORT).show();
    }

    /**
     * Deal keeping alive failed.<br>
     * CN:?????????????????????
     */
    private void dealNetfailedStatus(Caller caller)
    {
        finishCurActivity(caller, ClientState.NETWORK_LOST);
        // CN:??????????????????????????????????????????
        removeInvalidDevice();
        DialogUtils.showDialogNoCancelable(mContext, R.string.network_title,
                R.string.network_status, new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        gotoDeviceDiscovery();
                    }
                });
    }

    /**
     * Deal Access bye for reave.<br>
     * CN:?????????????????????
     */
    private void dealAccessByeForReave(Caller caller)
    {
        finishCurActivity(caller, ClientState.REAVED);
        clearCurrentDevice();
        DialogUtils.showDialogNoCancelable(mContext, R.string.Access_Quit__Title,
                R.string.AccessControlService_toast_remove_tip,
                new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        gotoDeviceDiscovery();
                    }
                });
    }

    /**
     * Deal STB leave.<br>
     * CN:??????STB???????????????
     */
    private void dealSTBLeave(Caller caller)
    {
        finishCurActivity(ClientState.STB_LEAVE);
        // CN:??????????????????????????????????????????
        removeInvalidDevice();

        DialogUtils.showDialogNoCancelable(mContext,
                getResources().getString(R.string.Access_Quit__Title),
                getResources().getString(R.string.AccessControlService_toast_STBLeave_tip),
                new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        gotoDeviceDiscovery();
                    }
                });
    }

    /**
     * Deal Access bye for reave.<br>
     * CN:???????????? ?????????
     * @param caller
     */
    private void dealSTBSuspend(Caller caller)
    {
        finishCurActivity(caller, ClientState.STB_SUSPEND);
        clearCurrentDevice();
        DialogUtils.showDialogNoCancelable(mContext, R.string.Access_Quit__Title,
                R.string.AccessControlService_toast_STBSuspend_tip,
                new DialogInterface.OnClickListener()
                {
                    @Override
                    public void onClick(DialogInterface dialog, int which)
                    {
                        gotoDeviceDiscovery();
                    }
                });
    }

    /**
     * Remove invalid device in original list.<br>
     * CN:???????????????????????????????????????
     */
    private void removeInvalidDevice()
    {
        mMultiScreenControlService.getControlPoint().removeCannotAccessDevice(
                mMultiScreenControlService.getControlPoint().getCurrentDevice());
        clearCurrentDevice();
    }

    private void clearCurrentDevice()
    {
        mMultiScreenControlService.getControlPoint().setCurrentDevice(null);
    }

    /**
     * Load library of mirror, and support mirror.<br>
     * CN:??????LIBS???????????????????????????
     * @return true means load successful.
     */
    private static boolean loadMirrorLibs()
    {
        if (sLoaded)
        {
            return true;
        }
        boolean err = false;

        try
        {
            // LogTool.d("load libmirror_jni.so");
            // System.loadLibrary("mirror23_jni");
            // System.loadLibrary("mirror_jni");
            String osVersion = android.os.Build.VERSION.SDK;
            if (Integer.valueOf(osVersion) < 14)
            {
                LogTool.d("load libmirror23_jni.so");
                System.loadLibrary("mirror23_jni");
            }
            else if (Integer.valueOf(osVersion) < 19)
            {
                LogTool.d("load libmirror40_jni.so");
                System.loadLibrary("mirror40_jni");
            }
            else if (Integer.valueOf(osVersion) < 21)
            {
                LogTool.d("load libmirror44_jni.so");
                System.loadLibrary("mirror44_jni");
            }
            else
            {
                LogTool.d("load libmirror50_jni.so");
                System.loadLibrary("mirror50_jni");
            }
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
     * Touch listener.<br>
     * CN:?????????????????????
     */
    private OnTouchListener mTouchListener = new OnTouchListener()
    {
        @Override
        public boolean onTouch(View v, MotionEvent event)
        {
            switch (v.getId())
            {

                case R.id.MirrorView:
                    handleMotionEvent(event);
                    break;

                case R.id.control_layout:

                    switch (event.getAction())
                    {

                        case MotionEvent.ACTION_DOWN:
                        {
                            currentX = (int) event.getRawX();
                            currentY = (int) event.getRawY();
                            int right = mControl_layout.getRight();
                            int left = right - mControl_close.getWidth();
                            if (currentX < left || currentX > right)
                                return false;
                            return true;
                        }
                        case MotionEvent.ACTION_MOVE:
                        {
                            int x2 = (int) event.getRawX();
                            int y2 = currentY;

                            moveViewBy(mControl_layout, x2 - currentX, y2 - currentY);
                            currentX = x2;
                            currentY = y2;
                            return true;
                        }
                        case MotionEvent.ACTION_UP:
                        {
                            return true;
                        }
                    }

                default:
                    break;
            }
            return true;

        }
    };

    /**
     * CN????????????????????????
     */
    private void moveViewBy(View view, int x, int y)
    {
        int left = view.getLeft() + x;
        int right = view.getRight() + x;
        int top = view.getTop() + y;
        int bottom = view.getBottom() + y;

        mLayoutWidth = mControl_layout.getWidth();
        mCloseWidth = mControl_close.getWidth();
        int width = mLayoutWidth - mCloseWidth;

        if (left >= -width && right <= screenWidth)
        {
            view.layout(left, top, right, bottom);
        }
    }

    /**
     * Map X-coordinate on STB.<br>
     * The range is [0, MAX_STB_TOUCH_WIDTH].<br>
     * @param x original X.
     * @return mapping X .
     */
    private int getMappingX(int x)
    {
        int ret_value = 0;
        int localWidth;

        if ((mMirrorView == null) || (mMirrorView.mSurfaceHolder == null))
        {
            // Use default width as touch range.
            localWidth = screenWidth - 1;
        }
        else
        {
            // Use width of Surface as touch range.
            localWidth = mMirrorView.mSurfaceHolder.getSurfaceFrame().width() - 1;
        }

        if (x > localWidth)
        {
            ret_value = MAX_STB_TOUCH_WIDTH;
        }
        else
        {
            ret_value = (x * MAX_STB_TOUCH_WIDTH) / localWidth;
        }

        return ret_value;
    }

    /**
     * Map Y-coordinate on STB.<br>
     * The range is [0, MAX_STB_TOUCH_HEIGHT].<br>
     * @param y original Y.
     * @return mapping Y.
     */
    private int getMappingY(int y)
    {
        int ret_value = 0;
        int localHeight;

        if ((mMirrorView == null) || (mMirrorView.mSurfaceHolder == null))
        {
            // Use default height as touch range.
            localHeight = screenHeight - 1;
        }
        else
        {
            // Use height of Surface as touch range.
            localHeight = mMirrorView.mSurfaceHolder.getSurfaceFrame().height() - 1;
        }

        if (y > localHeight)
        {
            ret_value = MAX_STB_TOUCH_HEIGHT;
        }
        else
        {
            ret_value = (y * MAX_STB_TOUCH_HEIGHT) / localHeight;
        }

        return ret_value;
    }

    /**
     * Handle MotionEvent of touch.
     * @param event MotionEvent
     */
    private void handleMotionEvent(MotionEvent event)
    {
        int index = event.getActionIndex();
        if (index > 1)
        {
            LogTool.d("Action index is not 0 or 1, so we will not handle it.");
            return;
        }

        int pointCount = (event.getPointerCount() == 1) ? 1 : 2;
        int x0 = getMappingX((int) event.getX(0));
        int y0 = getMappingY((int) event.getY(0));
        int x1 = (pointCount == 1) ? 0 : getMappingX((int) event.getX(1));
        int y1 = (pointCount == 1) ? 0 : getMappingY((int) event.getY(1));
        int id0 = (event.getPointerId(0) == 0) ? 0 : 1;
        if (pointCount > 1)
        {
            id0 = (event.getPointerId(0) <= event.getPointerId(1)) ? 0 : 1;
        }
        int id1 = (id0 == 0) ? 1 : 0;

        switch (event.getActionMasked())
        {
            case MotionEvent.ACTION_DOWN:
            case MotionEvent.ACTION_POINTER_DOWN:
            {
                // LogTool.d("Fingers down.");
                if (pointCount == 1)
                {
                    mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_PRESSED);
                    mTouchInfo.getFingerInfo(id1).setPress(FINGER_UP);
                }
                else
                {
                    mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_PRESSED);
                    mTouchInfo.setFingerInfo(id1, x1, y1, FINGER_PRESSED);
                }
                mRemoteTouch.sendMultiTouchEvent(mTouchInfo);
            }
                break;

            case MotionEvent.ACTION_MOVE:
            {
                // LogTool.d("Fingers move.");
                if (countMove != 1)
                {
                    countMove++;
                    break;
                }
                countMove = 0;
                if (pointCount == 1)
                {
                    mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_PRESSED);
                }
                else
                {
                    mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_PRESSED);
                    mTouchInfo.setFingerInfo(id1, x1, y1, FINGER_PRESSED);
                }
                mRemoteTouch.sendMultiTouchEvent(mTouchInfo);
            }
                break;

            case MotionEvent.ACTION_UP:
            case MotionEvent.ACTION_POINTER_UP:
            case MotionEvent.ACTION_CANCEL:
            {
                // LogTool.d("Fingers up.");
                // LogTool.d("test up x0:" + x0 + " y0:" + y0);
                if (pointCount == 1)
                {
                    mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_UP);
                    mTouchInfo.setFingerInfo(id1, x1, y1, FINGER_UP);
                }
                else
                {
                    if (index == 0)
                    {
                        mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_UP);
                        mTouchInfo.setFingerInfo(id1, x1, y1, FINGER_PRESSED);
                    }
                    else
                    {
                        mTouchInfo.setFingerInfo(id0, x0, y0, FINGER_PRESSED);
                        mTouchInfo.setFingerInfo(id1, x1, y1, FINGER_UP);
                    }
                }
                mRemoteTouch.sendMultiTouchEvent(mTouchInfo);
                // Send up again.
                mRemoteTouch.sendMultiTouchEvent(mTouchInfo);
            }
                break;

            default:
            {
                LogTool.e("Unkown Motion Action:" + event.getAction());
            }
                break;
        }
    }

    /**
     * Send byebye to STB.<br>
     * CN:???STB??????byebye?????????
     * @param clientState
     */
    private void sendByeToSTB(ClientState clientState)
    {
        // CN:??????????????????????????????????????????byebye?????????
        if (clientState != ClientState.REAVED)
        {
            new Thread()
            {
                public void run()
                {
                    boolean isByebye = MultiScreenControlService.getInstance().accessByebye();
                    if (!isByebye)
                    {
                        LogTool.d("AccessByebye failed and try again!");
                        MultiScreenControlService.getInstance().accessByebye();
                    }
                }
            }.start();
        }
    }

    /**
     * Show dialog if access event notify.<br>
     * CN:??????????????????????????????
     */
    private static class AccessEventHandler extends Handler
    {
        SoftReference<MultiScreenActivity> mActivityReference = null;

        AccessEventHandler(MultiScreenActivity activity)
        {
            mActivityReference = new SoftReference<MultiScreenActivity>(activity);
        }

        public void handleMessage(Message msg)
        {
            MultiScreenActivity activity = mActivityReference.get();

            super.handleMessage(msg);

            if (activity == null)
            {
                return;
            }

            switch (msg.what)
            {
                case KEEP_ALIVE_PACKET_LOSS:
                {
                    // CN:?????????????????????
                    LogTool.e("keep alive packet loss!");
                    activity.dealPacketLoss();
                    break;
                }

                case KEEP_ALIVE_FAILED:
                {
                    // CN:???????????????
                    Caller caller = (Caller) msg.obj;
                    activity.dealNetfailedStatus(caller);
                    break;
                }

                case ACCESS_REAVED:
                {
                    // CN:?????????
                    Caller caller = (Caller) msg.obj;
                    activity.dealAccessByeForReave(caller);
                    break;
                }

                case STB_LEAVE:
                {
                    // CN:STB?????????
                    Caller caller = (Caller) msg.obj;
                    activity.dealSTBLeave(caller);
                    break;
                }

                case STB_SUSPEND:
                {
                    // CN:STB?????????
                    Caller caller = (Caller) msg.obj;
                    activity.dealSTBSuspend(caller);
                    break;
                }

                default:
                    break;
            }

        }
    }

    /**
     * Set strict mode.
     */
    @SuppressLint("NewApi")
    private void setStrictMode()
    {
        LogTool.d("setStrictMode");
        // CN:??????StrictMode??????
        // or .detectAll() for all detectable problems
        StrictMode.setThreadPolicy(new StrictMode.ThreadPolicy.Builder().detectDiskReads()
                .detectDiskWrites().detectNetwork().penaltyLog().build());
        StrictMode.setVmPolicy(new StrictMode.VmPolicy.Builder().detectLeakedSqlLiteObjects()
                .penaltyLog().penaltyDeath().build());
        // FIXME delete detectLeakedClosableObjects() for 4.2
    }

    /**
     * Init service and controller.<br>
     * CN:??????????????????????????????
     */
    private void initData()
    {
        LogTool.d("initData");
        ServiceUtil.checkMultiScreenControlService(this);
        mMultiScreenControlService = MultiScreenControlService.getInstance();
        initOrientationDetector();
    }

    /**
     * Initialize view of activity.<br>
     * CN:????????????????????????
     */
    private void initView()
    {
        LogTool.d("initView");
        // Hide title(full screen).
        // CN:???????????????????????????????????????
        setContentView(R.layout.mybox_image_control);
        mContext = this;

        vime_status = readStatusPreference(MultiSettingActivity.VIME_STATUS_KEY, true);

        dm = getResources().getDisplayMetrics();
        screenWidth = dm.widthPixels;
        screenHeight = dm.heightPixels;

        mControl_close = (Button) findViewById(R.id.control_close);
        mControl_close.setOnClickListener(this);

        mControl_layout = (RelativeLayout) findViewById(R.id.control_layout);
        mControl_layout.setOnTouchListener(mTouchListener);

        mControl_back = (Button) findViewById(R.id.control_back);
        mControl_back.setOnClickListener(this);

        mControl_more = (Button) findViewById(R.id.control_more);
        mControl_more.setOnClickListener(this);

        mMorePop = new MultiScreenMorePop(this, this);
        // mControl_error = (RelativeLayout) findViewById(R.id.control_error);
    }

    /**
     * Check intent on create.<br>
     * @return
     */
    private int checkRemoteIntent()
    {
        int retVal = 0;
        Intent intent = getIntent();
        Bundle bundle = intent.getExtras();
        if (bundle != null)
        {
            retVal = bundle.getInt(MessageDef.INTENT_REMOTE_STATUS);
        }
        return retVal;
    }

    /**
     * Sync info of STB.<br>
     * CN:??????STB?????????
     */
    private void syncInfo()
    {
        ClientState state = mMultiScreenControlService.getState();
        switch (state)
        {
            case INIT:
            {
                // CN:????????????????????????
                if (mMultiScreenControlService.canSyncInfo())
                {
                    // CN:???????????????????????????????????????????????????RUNNING???
                    mMultiScreenControlService.startPing();
                    initModules();
                }
                else
                {
                    // CN:????????????STB?????????????????????????????????
                    LogTool.e("sync STB info failed!");
                    mMultiScreenControlService.setState(ClientState.NETWORK_LOST);
                }
            }
                break;
            case RUNNING:
            {
                // CN:???HOME??????????????????
                LogTool.d("Resume MultiScreenActivity from HOME.");
                initModules();
            }
                break;
            default:
            {
                LogTool.e("The client state is " + state.toString() + " when activity on create.");
            }
                break;
        }
    }

    /**
     * Init modules.<br>
     * CN:?????????????????????
     */
    private void initModules()
    {
        LogTool.d("initModules");
        // We have start checking network on DeviceDiscoveryActivity.
        // CN:?????????????????????????????????????????????
        initRemoteCenter();
        initMirror();
        initTouch();
        initVIME();
    }

    /**
     * Stop network check.<br>
     * CN:???????????????????????????
     * @param caller CN:????????????
     * @param clientState CN:??????????????????
     */
    private void deInitNetworkChecker(Caller caller, ClientState clientState)
    {
        // CN:???????????????????????????
        mMultiScreenControlService.stopPing(caller, clientState);
    }

    /**
     * Init remote center.<br>
     * CN:??????????????????????????????
     */
    private void initRemoteCenter()
    {
        LogTool.d("initRemoteCenter");
        mRemoteControlCenter = MultiScreenControlService.getInstance().getRemoteControlCenter();
        // Virtual keyboard object.
        // CN:?????????????????????
        mRemoteKeyboard = mRemoteControlCenter.getRemoteKeyboard();
    }

    /**
     * Destroy remote center.<br>
     * CN:???????????????????????????
     */
    private void deInitRemoteCenter()
    {
        LogTool.d("destroy remote control center.");
        if (mRemoteControlCenter != null)
        {
            mRemoteControlCenter.destroy();
            mRemoteControlCenter = null;
        }
    }

    /**
     * Init remote touch after MirrorView has been initialized.<br>
     * CN:??????????????????????????????MirrorView???????????????????????????
     */
    private void initTouch()
    {
        LogTool.d("initTouch");
        // Initial remote touch.
        // CN:??????????????????????????????
        mRemoteTouch = mRemoteControlCenter.getRemoteTouch();

        if (mMirrorView != null)
        {
            mMirrorView.setOnTouchListener(mTouchListener);
        }
    }

    /**
     * Start mirror.<br>
     * CN:???????????????
     */
    private void initMirror()
    {
        LogTool.d("initMirror");
        // Init mirror on STB.
        if (initMirrorServer() == false)
        {
            LogTool.e("Fail to set mirror parameter.");
        }

        // Init mirror on client.
        // TODO load when init.
        loadMirrorLibs();
        mMirrorView = (MirrorView) findViewById(R.id.MirrorView);
        // y00273148 modify for hme begin
        mLayout = (LinearLayout) findViewById(R.id.VideoView);
        mMirrorView.setViewLayout(mLayout);
        // y00273148 end

        // mMirrorfpsControl = new MirrorfpsControl();
    }

    /**
     * Initialize Mirror on server.<br>
     * CN:??????????????????Mirror?????????
     * @return result of initialize mirror server.
     */
    private boolean initMirrorServer()
    {
        return mMultiScreenControlService.setDefaultMirrorParameter(2);
    }

    /**
     * Start vime control service.<br>
     * CN:????????????????????????????????????
     */
    private void initVIME()
    {
        LogTool.d("initVIME");
        // Start VIME client control service.
        if (vime_status == true)
            startService(new Intent(this, VImeClientControlService.class));
        else
            stopService(new Intent(this, VImeClientControlService.class));
    }

    /**
     * Read enable/disable record.<br>
     * CN:?????????????????????
     * @param statusKey
     * @param defValue
     */
    private boolean readStatusPreference(String statusKey, boolean defValue)
    {
        SharedPreferences prefrence = getSharedPreferences(
                MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        return prefrence.getBoolean(statusKey, defValue);
    }

    /**
     * Write enable/disable record.<br>
     * CN:?????????????????????
     * @param statusKey
     * @param isOpened
     */
    private void writeStatusPreference(String statusKey, boolean isOpened)
    {
        SharedPreferences.Editor editor = getSharedPreferences(
                MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE).edit();
        editor.putBoolean(statusKey, isOpened);
        editor.commit();
    }

    /**
     * Stop vime control service.<br>
     * CN:????????????????????????????????????
     */
    private void deInitVIMEService()
    {
        LogTool.v("stopService VImeClientControlService.");
        sendBroadcast(new Intent(MultiScreenIntentAction.END_INPUT_BY_STB));
        stopService(new Intent(this, VImeClientControlService.class));
    }

    private void startGsensor()
    {
        LogTool.d("Start gsensor service.");
        startService(new Intent(this, SensorService.class));
    }

    private void stopGsensor()
    {
        LogTool.v("Stop gsensor service.");
        stopService(new Intent(this, SensorService.class));
    }

    /**
     * Initialize gsensor.<br>
     * CN:????????????????????????
     * @deprecated CN:????????????????????????????????????
     */
    private void initGsensor()
    {
        // CN:??????????????????????????????
        boolean isOpened = readStatusPreference(MultiSettingActivity.SENSOR_STATUS_KEY, false);
        if (isOpened)
        {
            startGsensor();
            writeStatusPreference(MultiSettingActivity.SENSOR_STATUS_KEY, true);
        }
    }

    /**
     * DeInit gsensor service.<br>
     * CN:?????????????????????
     * @deprecated CN:????????????????????????????????????
     */
    private void deInitSensorService()
    {
        stopGsensor();
        writeStatusPreference(MultiSettingActivity.SENSOR_STATUS_KEY, false);
    }

    /**
     * Check state of client control service on resume.<br>
     * CN:????????????????????????????????????????????????
     */
    private void checkState()
    {
        switch (mMultiScreenControlService.getState())
        {
            case RUNNING:
            {
                LogTool.d("check state RUNNING.");
                startMirror();
                handleIntent();
                break;
            }
            case REAVED:
            {
                LogTool.d("check state REAVED.");
                sendAccessStatusMessage(Caller.AccessPing, ACCESS_REAVED);
                break;
            }
            case STB_LEAVE:
            {
                LogTool.d("check state STB_LEAVE.");
                sendAccessStatusMessage(Caller.AccessPing, STB_LEAVE);
                break;
            }
            case NETWORK_LOST:
            {
                LogTool.d("check state NETWORK_LOST.");
                sendAccessStatusMessage(Caller.KeepAlive, KEEP_ALIVE_FAILED);
                break;
            }
            case STB_SUSPEND:
            {
                LogTool.d("check state STB_SUSPEND.");
                sendAccessStatusMessage(Caller.AccessPing, STB_SUSPEND);
                break;
            }
            default:
            {
                LogTool.e("check state error: " + mMultiScreenControlService.getState().toString());
                // CN:??????????????????????????????
                sendAccessStatusMessage(Caller.Others, KEEP_ALIVE_FAILED);
                break;
            }
        }
    }

    /**
     * Handle intent on resume.<br>
     * CN:??????????????????????????????????????????<br>
     * Call this function in onNewIntent and onResume.<br>
     * CN:???onNewIntent???onResume???????????????
     */
    private void handleIntent()
    {
        LogTool.d("");
        int mirrorStatus = getIntent().getIntExtra(MessageDef.INTENT_MIRROR_STATUS,
                MessageDef.MIRROR_STATUS_DEFAULT);
        if (mirrorStatus == MessageDef.MIRROR_STATUS_SENSOR)
        {
            // LogTool.d("MIRROR_STATUS_SENSOR");
            remote_game_flag = true;
            mControl_pop_game.setBackgroundResource(R.drawable.image_control_game_focus);
            startGsensor();
        }
        else
        {
            // LogTool.d("MIRROR_STATUS_DEFAULT");
            remote_game_flag = false;
            mControl_pop_game.setBackgroundResource(R.drawable.image_control_game);
            stopGsensor();
        }
    }

    /**
     * Send access status message to handler.<br>
     * @param caller
     * @param what
     */
    private void sendAccessStatusMessage(Caller caller, int what)
    {
        Message msg = mAccessEventHandler.obtainMessage();
        msg.obj = caller;
        msg.what = what;
        msg.sendToTarget();
    }

    /**
     * CN??????????????????????????????
     */
    class MultiScreenMorePop extends PopupWindow
    {
        public MultiScreenMorePop(Activity context, OnClickListener click)
        {
            super(context);

            parent = LayoutInflater.from(context).inflate(R.layout.mybox_image_pop, null);

            mControl_pop_home = (Button) parent.findViewById(R.id.control_pop_home);
            mControl_pop_home.setOnClickListener(click);

            mControl_pop_menu = (Button) parent.findViewById(R.id.control_pop_menu);
            mControl_pop_menu.setOnClickListener(click);

            mControl_pop_vol = (Button) parent.findViewById(R.id.control_pop_vol);
            mControl_pop_vol.setOnClickListener(click);

            mControl_pop_game = (Button) parent.findViewById(R.id.control_pop_game);
            mControl_pop_game.setOnClickListener(click);

            this.setContentView(parent);
            this.setWidth(LayoutParams.WRAP_CONTENT);
            this.setHeight(LayoutParams.WRAP_CONTENT);
            this.setFocusable(true);
            this.setTouchable(true);
            this.setOutsideTouchable(false);
            this.setBackgroundDrawable(new BitmapDrawable());
            this.update();
        }
    }

    private void gotoRemoteTouch()
    {
        Intent intent = new Intent(this, RemoteActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_TOUCH);
        startActivity(intent);
        finish();
    }

    private void gotoAirMouse()
    {
        Intent intent = new Intent(this, RemoteActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_AIRMOUSE);
        startActivity(intent);
        finish();
    }

    private void gotoMirrorSensor()
    {
        Intent intent = getIntent();
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_SENSOR);
        startActivity(intent);
    }

    /**
     * Go back to device discovery if exceptions happened.<br>
     * CN:????????????????????????????????????
     */
    private void gotoDeviceDiscovery()
    {
        Intent intent = new Intent(this, DeviceDiscoveryActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
        finish();
    }
}
