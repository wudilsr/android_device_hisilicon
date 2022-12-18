package com.hisilicon.multiscreen.mybox;

import android.content.Intent;
import android.os.Bundle;
import android.os.SystemClock;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnTouchListener;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.multiscreen.controller.IAccessListener.Caller;
import com.hisilicon.multiscreen.gsensor.SensorService;
import com.hisilicon.multiscreen.protocol.message.KeyInfo;
import com.hisilicon.multiscreen.protocol.message.MessageDef;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * CN：游戏模式界面。
 */
public class RemoteGameActivity extends BaseActivity implements OnClickListener, OnTouchListener
{
    /**
     * CN：手柄按键的显示信息。
     */
    private TextView mTextViewGameHandle;

    /**
     * CN：体感按键的显示信息。
     */
    private TextView mTextViewGameSensor;

    /**
     * CN：手柄界面的布局。
     */
    private RelativeLayout mRemote_game_control;

    /**
     * CN：体感界面的布局。
     */
    private RelativeLayout mRemote_game_sensor;

    /**
     * CN：返回按钮。
     */
    private Button mBtnRemote_game_back;

    /**
     * CN：菜单按钮。
     */
    private Button mBtnRemote_game_menu;

    /**
     * CN：手柄界面上下左右方向按钮。
     */
    private Button mBtnRemote_game_key;

    /**
     * CN：手柄界面的返回按钮。
     */
    private Button mBtnRemote_game_key_back;

    /**
     * CN：手柄界面的选择按钮。
     */
    private Button mBtnRemote_game_key_select;

    /**
     * CN：手柄界面的开始按钮。
     */
    private Button mBtnRemote_game_key_start;

    /**
     * CN：手柄界面的x按钮。
     */
    private Button mBtnRemote_game_key_x;

    /**
     * CN：手柄界面的y按钮。
     */
    private Button mBtnRemote_game_key_y;

    /**
     * CN：手柄界面的a按钮。
     */
    private Button mBtnRemote_game_key_a;

    /**
     * CN：手柄界面的b按钮。
     */
    private Button mBtnRemote_game_key_b;

    /**
     * CN：体感界面的返回按钮。
     */
    private Button mBtnRemote_game_sensor_back;

    /**
     * CN：菜单按钮的子布局。
     */
    private RemoteParent mPopwin;

    /**
     * Pop click listener of remote status select.
     */
    private OnClickListener mPopClickListener = null;

    private int width = 0;

    private int x = 0;

    private int y = 0;

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        initView();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        resumeActivity();
    }

    @Override
    protected void onPause()
    {
        super.onPause();
        stopGsensor();
    }

    @Override
    public void onBackPressed()
    {
        super.onBackPressed();
        gotoDeviceDiscovery();
    }

    @Override
    protected void onDestroy()
    {

        super.onDestroy();
        unbindDrawables(findViewById(R.layout.mybox_remote_game));
    }

    /**
     * CN:控件监听者。
     */
    @Override
    public void onClick(View view)
    {
        switch (view.getId())
        {
            case R.id.remote_game_handle_select:
            {
                updateHandsUI();
            }
                break;

            case R.id.remote_game_body_select:
            {
                updateSensotUI();
            }
                break;

            case R.id.remote_game_back:
            {
                gotoDeviceDiscovery();
            }
                break;

            case R.id.remote_game_menu:

                if (mPopwin != null)
                {
                    mPopwin.dismiss();
                }
                mPopwin.updateBackground(mRemoteUiStatus);
                mPopwin.showAtLocation(this.findViewById(R.id.remote_game_menu),
                    Gravity.CLIP_VERTICAL, 0, 0);
                break;

            default:
                break;
        }
    }

    private void resumeActivity()
    {
        resetAccessListener();
        initModules();
    }

    /**
     * Init modules.<br>
     * CN:初始化各模块。
     */
    private void initModules()
    {
        LogTool.d("initModules");
        // We have start checking network on DeviceDiscoveryActivity.
        // CN:首页已启动保活，不要重复开启。
        initRemoteCenter();
        if (mRemote_game_sensor.getVisibility() == View.VISIBLE)
        {
            startGsensor();
        }
    }

    /**
     * Start gsensor.<br>
     * CN:开启体感服务。
     */
    private void startGsensor()
    {
        LogTool.d("startGsensor");
        Intent intent = new Intent(RemoteGameActivity.this, SensorService.class);
        startService(intent);
    }

    /**
     * Stop gsensor. CN:关闭体感服务。
     */
    private void stopGsensor()
    {
        LogTool.d("stopGsensor");
        Intent mIntent = new Intent(RemoteGameActivity.this, SensorService.class);
        stopService(mIntent);
    }

    /**
     * Init remote center.<br>
     * CN:初始化远程控制中心。
     */
    private void initRemoteCenter()
    {
        LogTool.d("initRemoteCenter");
        mRemoteControlCenter = MultiScreenControlService.getInstance().getRemoteControlCenter();
        // Virtual keyboard object.
        // CN:虚拟键盘对象。
        mKeyboard = mRemoteControlCenter.getRemoteKeyboard();
        mRemoteTouch = mRemoteControlCenter.getRemoteTouch();
    }

    @Override
    protected void initData()
    {
        super.initData();
        mPopClickListener = new PopwinClickEvent();
        mPopwin = new RemoteParent(this, mPopClickListener);
    }

    /**
     * Init view.<br>
     */
    private void initView()
    {
        LogTool.d("initView");

        setContentView(R.layout.mybox_remote_game);

        mRemoteUiStatus = MessageDef.REMOTE_GAME;

        mTextViewGameHandle = (TextView) findViewById(R.id.remote_game_handle_select);
        mTextViewGameHandle.setOnClickListener(this);

        mTextViewGameSensor = (TextView) findViewById(R.id.remote_game_body_select);
        mTextViewGameSensor.setOnClickListener(this);

        mRemote_game_control = (RelativeLayout) findViewById(R.id.remote_game_control);
        mRemote_game_sensor = (RelativeLayout) findViewById(R.id.remote_game_sensor);

        mBtnRemote_game_back = (Button) findViewById(R.id.remote_game_back);
        mBtnRemote_game_back.setOnClickListener(this);

        mBtnRemote_game_menu = (Button) findViewById(R.id.remote_game_menu);
        mBtnRemote_game_menu.setOnClickListener(this);

        mBtnRemote_game_key = (Button) findViewById(R.id.remote_game_key);
        mBtnRemote_game_key.setOnTouchListener(this);

        mBtnRemote_game_key_back = (Button) findViewById(R.id.remote_game_key_back);
        mBtnRemote_game_key_back.setOnTouchListener(this);

        mBtnRemote_game_key_select = (Button) findViewById(R.id.remote_game_key_select);
        mBtnRemote_game_key_select.setOnTouchListener(this);

        mBtnRemote_game_key_start = (Button) findViewById(R.id.remote_game_key_start);
        mBtnRemote_game_key_start.setOnTouchListener(this);

        mBtnRemote_game_key_x = (Button) findViewById(R.id.remote_game_key_x);
        mBtnRemote_game_key_x.setOnTouchListener(this);

        mBtnRemote_game_key_y = (Button) findViewById(R.id.remote_game_key_y);
        mBtnRemote_game_key_y.setOnTouchListener(this);

        mBtnRemote_game_key_a = (Button) findViewById(R.id.remote_game_key_a);
        mBtnRemote_game_key_a.setOnTouchListener(this);

        mBtnRemote_game_key_b = (Button) findViewById(R.id.remote_game_key_b);
        mBtnRemote_game_key_b.setOnTouchListener(this);

        mBtnRemote_game_sensor_back = (Button) findViewById(R.id.remote_game_sensor_back);
        mBtnRemote_game_sensor_back.setOnTouchListener(this);
    }

    /**
     * CN:菜单按钮子布局的控件监听者。
     */
    private class PopwinClickEvent implements OnClickListener
    {
        @Override
        public void onClick(View v)
        {

            if (mPopwin != null)
            {
                mPopwin.dismiss();
            }

            switch (v.getId())
            {
                case R.id.remote_parent_touchs:
                {
                    gotoRemoteTouch();
                }
                    break;

                case R.id.remote_parent_keyboards:
                {
                    gotoRemoteKey();
                }
                    break;

                case R.id.remote_parent_games:
                {
                    updateHandsUI();
                }
                    break;

                default:
                    break;
            }

            mPopwin.updateBackground(mRemoteUiStatus);
        }
    }

    /**
     * CN:显示手柄界面。
     */
    public void updateHandsUI()
    {
        mRemoteUiStatus = MessageDef.REMOTE_GAME;

        mTextViewGameSensor.setBackgroundDrawable(null);
        mTextViewGameHandle.setBackgroundResource(R.drawable.remote_game_mode_change_foucs);
        mBtnRemote_game_menu.setBackgroundResource(R.drawable.remote_head_switch_game);
        mRemote_game_control.setVisibility(View.VISIBLE);
        mRemote_game_sensor.setVisibility(View.INVISIBLE);

        stopGsensor();
    }

    /**
     * CN:显示体感界面。
     */
    private void updateSensotUI()
    {
        mRemoteUiStatus = MessageDef.REMOTE_GAME;

        mTextViewGameSensor.setBackgroundResource(R.drawable.remote_game_mode_change_foucs);
        mTextViewGameHandle.setBackgroundDrawable(null);
        mBtnRemote_game_menu.setBackgroundResource(R.drawable.remote_head_switch_game);
        mRemote_game_control.setVisibility(View.INVISIBLE);
        mRemote_game_sensor.setVisibility(View.VISIBLE);

        startGsensor();
    }

    @Override
    protected void dealNetfailedStatus(Caller caller)
    {
        super.dealNetfailedStatus(caller);
        gotoRemoteTouch();
    }

    private void getKeyboardXY(MotionEvent event)
    {
        width = mBtnRemote_game_key.getHeight();
    }

    /**
     * CN:OnTouch() 事件控件监听者。
     */
    @Override
    public boolean onTouch(View v, MotionEvent event)
    {

        x = (int) event.getX();
        y = (int) event.getY();

        switch (v.getId())
        {

            case R.id.remote_game_key:
                getKeyboardXY(event);

                if (y > 0 && y < width / 3 && x > width / 3 && x < 2 * width / 3)
                {// REMOTE_UP
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mBtnRemote_game_key.setBackgroundResource(R.drawable.remote_game_handle_up);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_normal);
                        // doKeyboard(REMOTE_UP);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (x > 0 && x < width / 3 && y > width / 3 && y < 2 * width / 3)
                {// REMOTE_LEFT
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_left);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_normal);
                        // doKeyboard(REMOTE_LEFT);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (x > 2 * width / 3 && x < width && y > width / 3 && y < 2 * width / 3)
                {// REMOTE_RIGHT

                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_right);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_normal);
                        // doKeyboard(REMOTE_RIGHT);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (y > 2 * width / 3 && y < width && x > width / 3 && x < 2 * width / 3)
                {// REMOTE_DOWN

                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        toVibrate();
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_down);
                        mLoopCount = 0;
                        mPressTime = SystemClock.elapsedRealtime();
                        if (mPressTime != 0)
                        {
                            sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_DOWN);
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_MOVE)
                    {
                        if (mPressTime != 0)
                        {
                            if (mLoopCount < MAX_LOOP_COUNT)
                            {
                                mLoopCount++;
                            }
                            else
                            {
                                sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_DOWN);
                                mLoopCount = 0;
                            }
                        }
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_normal);
                        // doKeyboard(REMOTE_DOWN);
                        sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_UP);
                    }
                }
                else if (y > width / 3 && y < 2 * width / 3 && x > width / 3 && x < 2 * width / 3)
                {
                    if (event.getAction() == MotionEvent.ACTION_DOWN)
                    {
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_mid);
                    }
                    else if (event.getAction() == MotionEvent.ACTION_UP
                        || event.getAction() == MotionEvent.ACTION_CANCEL)
                    {
                        mBtnRemote_game_key
                            .setBackgroundResource(R.drawable.remote_game_handle_normal);
                        doKeyboard(REMOTE_OK);
                    }
                }
                else
                {
                    // Out of range.
                    mBtnRemote_game_key.setBackgroundResource(R.drawable.remote_game_handle_normal);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_UP, KeyInfo.KEY_EVENT_UP);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_LEFT, KeyInfo.KEY_EVENT_UP);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_RIGHT, KeyInfo.KEY_EVENT_UP);
                    sendLongPress(KeyInfo.KEYCODE_DPAD_DOWN, KeyInfo.KEY_EVENT_UP);
                }
                break;

            case R.id.remote_game_key_back:

                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mBtnRemote_game_key_back
                        .setBackgroundResource(R.drawable.remote_game_btn_back_pressed);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP)
                {
                    mBtnRemote_game_key_back.setBackgroundResource(R.drawable.remote_game_btn_back);
                    doKeyboard(REMOTE_BACK);
                }

                break;

            case R.id.remote_game_key_select:

                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mBtnRemote_game_key_select
                        .setBackgroundResource(R.drawable.remote_game_btn_select_pressed);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP)
                {
                    mBtnRemote_game_key_select
                        .setBackgroundResource(R.drawable.remote_game_btn_select);
                    // TODO CN:投币键
                    // sendLongPress(292, KeyInfo.KEY_EVENT_DOWN);
                    // sendLongPress(292, KeyInfo.KEY_EVENT_UP);
                    // sendLongPress(138, KeyInfo.KEY_EVENT_DOWN);
                    // sendLongPress(138, KeyInfo.KEY_EVENT_UP);
                    // L1：投币 292, R1：确认投币 138
                    // /dev/input/event4: 0004 0004 00090005
                    // /dev/input/event4: 0001 0124 00000001
                    // /dev/input/event4: 0000 0000 00000000
                    // /dev/input/event4: 0004 0004 00090005
                    // /dev/input/event4: 0001 0124 00000000
                    // /dev/input/event4: 0000 0000 00000000
                    // /dev/input/event4: 0003 0002 00000089
                    // /dev/input/event4: 0000 0000 00000000
                    // /dev/input/event4: 0003 0002 0000008a
                }
                break;

            case R.id.remote_game_key_start:

                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mBtnRemote_game_key_start
                        .setBackgroundResource(R.drawable.remote_game_start_pressed);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP)
                {
                    mBtnRemote_game_key_start.setBackgroundResource(R.drawable.remote_game_start);
                    doKeyboard(REMOTE_PARENT_MENU);
                }
                break;

            case R.id.remote_game_key_x:
                // FIXME CN:游戏按键，仿PlayStation。
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    toVibrate();
                    mBtnRemote_game_key_x.setBackgroundResource(R.drawable.remote_game_x_foucs);
                    mLoopCount2 = 0;
                    mPressTime2 = SystemClock.elapsedRealtime();
                    if (mPressTime2 != 0)
                    {
                        sendLongPress(KeyInfo.KEYCODE_3, KeyInfo.KEY_EVENT_DOWN);
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_MOVE)
                {
                    if (mPressTime2 != 0)
                    {
                        if (mLoopCount2 < MAX_LOOP_COUNT)
                        {
                            mLoopCount2++;
                        }
                        else
                        {
                            sendLongPress(KeyInfo.KEYCODE_3, KeyInfo.KEY_EVENT_DOWN);
                            mLoopCount2 = 0;
                        }
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mBtnRemote_game_key_x.setBackgroundResource(R.drawable.remote_game_x);
                    sendLongPress(KeyInfo.KEYCODE_3, KeyInfo.KEY_EVENT_UP);
                }
                break;

            case R.id.remote_game_key_y:
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    toVibrate();
                    mBtnRemote_game_key_y.setBackgroundResource(R.drawable.remote_game_y_foucs);
                    mLoopCount2 = 0;
                    mPressTime2 = SystemClock.elapsedRealtime();
                    if (mPressTime2 != 0)
                    {
                        sendLongPress(KeyInfo.KEYCODE_2, KeyInfo.KEY_EVENT_DOWN);
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_MOVE)
                {
                    if (mPressTime2 != 0)
                    {
                        if (mLoopCount2 < MAX_LOOP_COUNT)
                        {
                            mLoopCount2++;
                        }
                        else
                        {
                            sendLongPress(KeyInfo.KEYCODE_2, KeyInfo.KEY_EVENT_DOWN);
                            mLoopCount2 = 0;
                        }
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mBtnRemote_game_key_y.setBackgroundResource(R.drawable.remote_game_y);
                    sendLongPress(KeyInfo.KEYCODE_2, KeyInfo.KEY_EVENT_UP);
                }
                break;

            case R.id.remote_game_key_a:
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    toVibrate();
                    mBtnRemote_game_key_a.setBackgroundResource(R.drawable.remote_game_a_foucs);
                    mLoopCount2 = 0;
                    mPressTime2 = SystemClock.elapsedRealtime();
                    if (mPressTime2 != 0)
                    {
                        sendLongPress(KeyInfo.KEYCODE_4, KeyInfo.KEY_EVENT_DOWN);
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_MOVE)
                {
                    if (mPressTime2 != 0)
                    {
                        if (mLoopCount2 < MAX_LOOP_COUNT)
                        {
                            mLoopCount2++;
                        }
                        else
                        {
                            sendLongPress(KeyInfo.KEYCODE_4, KeyInfo.KEY_EVENT_DOWN);
                            mLoopCount2 = 0;
                        }
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mBtnRemote_game_key_a.setBackgroundResource(R.drawable.remote_game_a);
                    sendLongPress(KeyInfo.KEYCODE_4, KeyInfo.KEY_EVENT_UP);
                }
                break;

            case R.id.remote_game_key_b:
                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    toVibrate();
                    mBtnRemote_game_key_b.setBackgroundResource(R.drawable.remote_game_b_foucs);
                    mLoopCount2 = 0;
                    mPressTime2 = SystemClock.elapsedRealtime();
                    if (mPressTime2 != 0)
                    {
                        sendLongPress(KeyInfo.KEYCODE_1, KeyInfo.KEY_EVENT_DOWN);
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_MOVE)
                {
                    if (mPressTime2 != 0)
                    {
                        if (mLoopCount2 < MAX_LOOP_COUNT)
                        {
                            mLoopCount2++;
                        }
                        else
                        {
                            sendLongPress(KeyInfo.KEYCODE_1, KeyInfo.KEY_EVENT_DOWN);
                            mLoopCount2 = 0;
                        }
                    }
                }
                else if (event.getAction() == MotionEvent.ACTION_UP
                    || event.getAction() == MotionEvent.ACTION_CANCEL)
                {
                    mBtnRemote_game_key_b.setBackgroundResource(R.drawable.remote_game_b);
                    sendLongPress(KeyInfo.KEYCODE_1, KeyInfo.KEY_EVENT_UP);
                }
                break;

            case R.id.remote_game_sensor_back:

                if (event.getAction() == MotionEvent.ACTION_DOWN)
                {
                    mBtnRemote_game_sensor_back
                        .setBackgroundResource(R.drawable.remote_sensor_back_on);
                }
                else if (event.getAction() == MotionEvent.ACTION_UP)
                {
                    mBtnRemote_game_sensor_back
                        .setBackgroundResource(R.drawable.remote_sensor_back);
                    doKeyboard(REMOTE_BACK);
                }
                break;

            default:
                break;
        }
        return true;
    }

    @Override
    protected void gotoRemoteTouch()
    {
        super.gotoRemoteTouch();
        Intent intent = new Intent(RemoteGameActivity.this, RemoteActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_TOUCH);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoAirMouse()
    {
        super.gotoAirMouse();
        Intent intent = new Intent(RemoteGameActivity.this, RemoteActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_AIRMOUSE);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoRemoteKey()
    {
        super.gotoRemoteKey();
        Intent intent = new Intent(this, RemoteActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, MessageDef.REMOTE_KEY);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoMirror()
    {
        super.gotoMirror();
        Intent intent = new Intent(this, MultiScreenActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_REMOTE_STATUS, mRemoteUiStatus);
        intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_DEFAULT);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoMirrorSensor()
    {
        super.gotoMirrorSensor();
        Intent intent = new Intent(this, MultiScreenActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_REORDER_TO_FRONT);
        intent.putExtra(MessageDef.INTENT_MIRROR_STATUS, MessageDef.MIRROR_STATUS_SENSOR);
        startActivity(intent);
        finish();
    }

    @Override
    protected void gotoDeviceDiscovery()
    {
        super.gotoDeviceDiscovery();
        Intent intent = new Intent(this, DeviceDiscoveryActivity.class);
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        startActivity(intent);
        finish();
    }
}
