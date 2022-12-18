package com.hisilicon.multiscreen.mybox;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.multiscreen.gsensor.AirMouse;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.widget.RemoteTouchShowView;

/**
 * CN：滑动模式界面。
 */
public class RemoteTouchView extends RelativeLayout
{
    public static final int GESTURE_UP = 0;

    public static final int GESTURE_DOWN = 1;

    public static final int GESTURE_LEFT = 2;

    public static final int GESTURE_RIGHT = 3;

    public static final int GESTURE_ENTER = 4;

    public static final int GESTURE_IDLE = 5;

    /**
     * CN：提示信息。
     */
    public TextView mRemote_touch_info;

    /**
     * CN:空鼠整体布局。
     */
    public RelativeLayout mRemote_touch_layout;

    /**
     * CN：滑动模式显示的布局区域。
     */
    private RemoteTouchShowView mRemote_touch_show;

    /**
     * CN:空鼠按键提示。
     */
    private ImageView mRemote_touch_airmouse;

    /**
     * CN:触摸监听。
     */
    private OnTouchListener mOnTouchListener;

    /**
     * Air mouse controller.<br>
     */
    private AirMouse mAirMouse = null;

    private boolean mIsAirMouseOpen = false;

    private boolean mIsCloseBtnShown = false;

    private int downX = 0;

    private int downY = 0;

    private Context mContext;

    public RemoteTouchView(Context context)
    {
        super(context);
        mContext = context;
    }

    public RemoteTouchView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        this.mContext = context;
        initViews(context);
        initDetector();
    }

    public void initViews(Context context)
    {
        View view = LayoutInflater.from(mContext).inflate(R.layout.mybox_remote_touch, this);
        mRemote_touch_info = (TextView) view.findViewById(R.id.remote_touch_info);
        mRemote_touch_layout = (RelativeLayout) view.findViewById(R.id.remote_touch_layout);
        mRemote_touch_show = (RemoteTouchShowView) view.findViewById(R.id.remote_touch_show);
        mRemote_touch_airmouse = (ImageView) view.findViewById(R.id.remote_touch_airmouse);
        mRemote_touch_airmouse.setVisibility(INVISIBLE);
    }

    /**
     * Initialize AirMouse.<br>
     * CN:初始化空鼠。
     */
    public void initAirMouse()
    {
        if (mAirMouse == null)
        {
            mAirMouse = MultiScreenControlService.getInstance().getAirMouse();
        }

        if (mAirMouse.isSupported() == false)
        {
            mRemote_touch_info.setText(R.string.remote_mouse_not_supported);
            mRemote_touch_airmouse.setVisibility(INVISIBLE);
            mIsAirMouseOpen = false;
        }
    }

    public boolean enableAirMouse()
    {
        if (mAirMouse != null)
        {
            if (mIsAirMouseOpen == false)
            {
                mIsAirMouseOpen = mAirMouse.enable();
            }
        }
        else
        {
            mIsAirMouseOpen = false;
            LogTool.i("Enable failed, air mouse hasn't initialized.");
        }

        if (mIsAirMouseOpen)
        {
            mRemote_touch_airmouse.setVisibility(VISIBLE);
            hideBtnClose();
        }
        else
        {
            mRemote_touch_airmouse.setVisibility(INVISIBLE);
        }

        return mIsAirMouseOpen;
    }

    public void disableAirMouse()
    {
        mIsAirMouseOpen = false;
        mRemote_touch_airmouse.setVisibility(INVISIBLE);
        if (mAirMouse != null)
        {
            mAirMouse.disable();
        }
    }

    public boolean isAirMouseOpen()
    {
        return mIsAirMouseOpen;
    }

    private void initDetector()
    {
        initTouchListener();
        initSwipeDetector();
    }

    /**
     * Initialize touch listener for mouse.<br>
     * CN:初始化触摸监听，用于鼠标操作。
     */
    private void initTouchListener()
    {
        mOnTouchListener = new OnTouchListener()
        {
            private float x1, y1, x2, y2;

            private float dX1, dY1, dX2;

            private int keyboard_width, keyboard_height;

            @Override
            public boolean onTouch(View view, MotionEvent event)
            {
                switch (event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                    {
                        x1 = event.getX();
                        y1 = event.getY();
                        // downX = (int) x1;
                        // downY = (int) y1;

                        if (isCloseDown())
                        {
                            // Is close button down, don't send mouse down.
                        }
                        else if (mIsAirMouseOpen)
                        {
                            mAirMouse.down();
                        }

                        // setInfoVisible(View.INVISIBLE);
                        // LogTool.d("ztest x1:" + x1 + ",y1:" + y1);
                    }
                        break;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                    {
                        if (mIsAirMouseOpen)
                        {
                            mAirMouse.up();
                        }

                        x2 = event.getX();
                        y2 = event.getY();
                        // LogTool.d("ztest x2:" + x2 + ",y2:" + y2);

                        // matchGesture();
                        matchCloseGesture();
                    }
                        break;
                    case MotionEvent.ACTION_MOVE:
                    {
                        x2 = event.getX();
                        y2 = event.getY();
                        // LogTool.d("ztest x2:" + x2 + ",y2:" + y2);
                        // getGesture();
                        matchCloseGesture();
                    }
                        break;
                }
                return true;
            }

            /**
             * CN:匹配关闭空鼠手势。
             */
            private void matchCloseGesture()
            {
                dX2 = x2 - x1;
                if (dX2 < -150)
                {
                    showBtnClose();
                }
                else if (dX2 > 150)
                {
                    hideBtnClose();
                }
            }

            /**
             * CN:检测关闭按钮是否按下。
             */
            private boolean isCloseDown()
            {
                if (isBtnCloseShown())
                {
                    getKeyboardXY();
                    float closeX = 2 * keyboard_width / 3;
                    float closeY = 3 * keyboard_height / 7;
                    LogTool.d("keyboard_width:" + keyboard_width + ",keyboard_height"
                        + keyboard_height);
                    LogTool.d("closeX:" + closeX + ", closeY:" + closeY + ",x1:" + x1 + ",y1" + y1);
                    if ((closeX < x1) && (x1 < keyboard_width) && (0 < y1) && (y1 < closeY))
                    {
                        disableAirMouse();
                        return true;
                    }
                }
                return false;
            }

            private void getKeyboardXY()
            {
                keyboard_width = mRemote_touch_airmouse.getWidth();
                keyboard_height = mRemote_touch_airmouse.getHeight();
            }
        };

        mRemote_touch_airmouse.setOnTouchListener(mOnTouchListener);
    }

    private boolean isBtnCloseShown()
    {
        return mIsCloseBtnShown;
    }

    private void showBtnClose()
    {
        mIsCloseBtnShown = true;
        mRemote_touch_airmouse.setBackgroundResource(R.drawable.remote_touch_airmouse_close);
    }

    private void hideBtnClose()
    {
        mIsCloseBtnShown = false;
        mRemote_touch_airmouse.setBackgroundResource(R.drawable.remote_touch_airmouse_open);
    }

    /**
     * Initialize swipe detector.<br>
     * CN:初始化滑动方向监听。
     */
    private void initSwipeDetector()
    {
        OnTouchListener remoteTouchListener = new OnTouchListener()
        {
            private float x1, y1, x2, y2;

            private float dX1, dY1;

            private boolean isDownReset = false;

            @Override
            public boolean onTouch(View view, MotionEvent event)
            {
                switch (event.getAction())
                {
                    case MotionEvent.ACTION_DOWN:
                    {
                        x1 = event.getX();
                        y1 = event.getY();
                        downX = (int) x1;
                        downY = (int) y1;
                        isDownReset = false;
                        setInfoVisible(View.INVISIBLE);
                        hideBtnClose();
                        // LogTool.d("ztest x1:" + x1 + ",y1:" + y1);
                    }
                        break;
                    case MotionEvent.ACTION_UP:
                    case MotionEvent.ACTION_CANCEL:
                    {
                        x2 = event.getX();
                        y2 = event.getY();
                        // LogTool.d("ztest x2:" + x2 + ",y2:" + y2);
                        matchDown();
                    }
                        break;
                    case MotionEvent.ACTION_MOVE:
                    {
                        x2 = event.getX();
                        y2 = event.getY();
                        // LogTool.d("ztest x2:" + x2 + ",y2:" + y2);
                        matchGesture();
                    }
                        break;
                }
                return true;
            }

            private void matchDown()
            {
                if (isDownReset)
                {
                    return;
                }

                dX1 = x2 - downX;
                dY1 = y2 - downY;
                if (Math.abs(dX1) < 5 && Math.abs(dY1) < 5)
                {
                    // ENTER
                    doResult(GESTURE_ENTER);
                }

                // Clear bitmap of touch.
                getHandler().removeCallbacks(clearTouchRunnable);
                getHandler().postDelayed(clearTouchRunnable, 1000);
            }

            /**
             * Match direction gestures.<br>
             * CN:匹配方向手势。
             */
            private void matchGesture()
            {
                dX1 = x2 - downX;
                dY1 = y2 - downY;
                if (Math.abs(dX1) < Math.abs(dY1) && dY1 < -120)
                {
                    // UP
                    doResult(GESTURE_UP);
                    resetDownXY();
                }
                else if (Math.abs(dX1) < Math.abs(dY1) && dY1 > 120)
                {
                    // DOWN
                    doResult(GESTURE_DOWN);
                    resetDownXY();
                }
                else if (Math.abs(dX1) > Math.abs(dY1) && dX1 < -150)
                {
                    // LEFT
                    doResult(GESTURE_LEFT);
                    resetDownXY();
                }
                else if (Math.abs(dX1) > Math.abs(dY1) && dX1 > 150)
                {
                    // RIGHT
                    doResult(GESTURE_RIGHT);
                    resetDownXY();
                }

                // Clear bitmap of touch.
                getHandler().removeCallbacks(clearTouchRunnable);
                getHandler().postDelayed(clearTouchRunnable, 1000);
            }

            private void resetDownXY()
            {
                isDownReset = true;
                downX = (int) x2;
                downY = (int) y2;
            }
        };

        mRemote_touch_layout.setOnTouchListener(remoteTouchListener);
    }

    /**
     * Clean bitmap.<br>
     */
    private Runnable clearTouchRunnable = new Runnable()
    {
        @Override
        public void run()
        {
            setInfoVisible(View.VISIBLE);
        }
    };

    private void setInfoVisible(int visibility)
    {
        mRemote_touch_show.touchClearShow();
        mRemote_touch_info.setVisibility(visibility);
    }

    /**
     * CN：滑向的方向相应的按键监听
     */
    private void doResult(final int result)
    {
        switch (result)
        {
            case GESTURE_RIGHT:
                mRemote_touch_show.touchShowRight(downX, downY);
                RemoteActivity.doKeyboard(RemoteActivity.REMOTE_RIGHT);
                break;

            case GESTURE_LEFT:
                mRemote_touch_show.touchShowLeft(downX, downY);
                RemoteActivity.doKeyboard(RemoteActivity.REMOTE_LEFT);
                break;
            case GESTURE_DOWN:
                mRemote_touch_show.touchShowDown(downX, downY);
                RemoteActivity.doKeyboard(RemoteActivity.REMOTE_DOWN);
                break;
            case GESTURE_UP:
                mRemote_touch_show.touchShowUp(downX, downY);
                RemoteActivity.doKeyboard(RemoteActivity.REMOTE_UP);
                break;

            case GESTURE_ENTER:
                mRemote_touch_show.touchShowOk(downX, downY);
                RemoteActivity.doKeyboard(RemoteActivity.REMOTE_OK);
                break;

            default:
                break;
        }
    }
}
