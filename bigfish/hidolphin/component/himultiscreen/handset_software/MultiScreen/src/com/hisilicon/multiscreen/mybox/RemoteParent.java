package com.hisilicon.multiscreen.mybox;

import android.app.Activity;
import android.graphics.drawable.BitmapDrawable;
import android.view.LayoutInflater;
import android.view.MotionEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.ViewGroup.LayoutParams;
import android.widget.Button;
import android.widget.LinearLayout;
import android.widget.PopupWindow;
import android.widget.TextView;

import com.hisilicon.multiscreen.protocol.message.MessageDef;

/**
 * CN：菜单按钮的子布局。
 */
public class RemoteParent extends PopupWindow
{
    /**
     * CN：滑动模式按钮。
     */
    public Button mRemote_parent_touchs;

    /**
     * CN：按键模式按钮。
     */
    public Button mRemote_parent_keyboards;

    /**
     * CN：游戏模式按钮。
     */
    public Button mRemote_parent_games;

    /**
     * CN：滑动模式的显示信息。
     */
    private TextView mRemote_parent_touch_name;

    /**
     * CN：键盘模式的显示信息。
     */
    private TextView mRemote_parent_keyboard_name;

    /**
     * CN：游戏模式的显示信息。
     */
    private TextView mRemote_parent_game_name;

    private LinearLayout mRemote_parent_touch_layout;

    int[] location = new int[2];

    int x1, y1;

    private View parent;

    private Activity activity;

    /**
     * init view.
     */
    public RemoteParent(Activity context, OnClickListener click)
    {
        super(context);
        this.activity = context;
        parent = LayoutInflater.from(context).inflate(R.layout.mybox_remote_parent, null);

        mRemote_parent_touch_layout =
            (LinearLayout) parent.findViewById(R.id.remote_parent_touch_layout);
        mRemote_parent_touchs = (Button) parent.findViewById(R.id.remote_parent_touchs);
        mRemote_parent_touchs.setOnClickListener(click);

        mRemote_parent_keyboards = (Button) parent.findViewById(R.id.remote_parent_keyboards);
        mRemote_parent_keyboards.setOnClickListener(click);

        mRemote_parent_games = (Button) parent.findViewById(R.id.remote_parent_games);
        mRemote_parent_games.setOnClickListener(click);

        mRemote_parent_touch_name = (TextView) parent.findViewById(R.id.remote_parent_touch_name);
        mRemote_parent_keyboard_name =
            (TextView) parent.findViewById(R.id.remote_parent_keyboard_name);
        mRemote_parent_game_name = (TextView) parent.findViewById(R.id.remote_parent_game_name);

        this.setContentView(parent);
        this.setWidth(LayoutParams.FILL_PARENT);
        this.setHeight(LayoutParams.FILL_PARENT);
        this.setFocusable(true);
        this.setTouchable(true);
        this.setOutsideTouchable(true);
        this.update();
        //this.setBackgroundDrawable(new BitmapDrawable());

        parent.setOnTouchListener(new View.OnTouchListener()
        {
            public boolean onTouch(View v, MotionEvent event)
            {

                mRemote_parent_touch_layout.getLocationInWindow(location);
                x1 = location[0];
                y1 = location[1];

                int y = (int) event.getY();
                if (event.getAction() == MotionEvent.ACTION_UP)
                {
                    if (y < y1 || y > y1 + mRemote_parent_touch_layout.getHeight())
                    {
                        dismiss();
                    }
                }
                return true;
            }
        });
    }

    /**
     * CN：模式切换及相应的界面更新。
     */
    public void updateBackground(int value)
    {

        if (value == MessageDef.REMOTE_TOUCH)
        {
            mRemote_parent_touchs.setBackgroundResource(R.drawable.remote_parent_touch_on);
            mRemote_parent_keyboards.setBackgroundResource(R.drawable.remote_keyboard_select);
            mRemote_parent_games.setBackgroundResource(R.drawable.remote_game_select);

            mRemote_parent_touch_name.setTextColor(activity.getResources().getColor(R.color.blue));
            mRemote_parent_keyboard_name.setTextColor(activity.getResources().getColor(
                R.color.white));
            mRemote_parent_game_name.setTextColor(activity.getResources().getColor(R.color.white));

        }
        else if (value == MessageDef.REMOTE_KEY)
        {
            mRemote_parent_touchs.setBackgroundResource(R.drawable.remote_touch_select);
            mRemote_parent_keyboards.setBackgroundResource(R.drawable.remote_parent_keyboard_on);
            mRemote_parent_games.setBackgroundResource(R.drawable.remote_game_select);

            mRemote_parent_touch_name.setTextColor(activity.getResources().getColor(R.color.white));
            mRemote_parent_keyboard_name.setTextColor(activity.getResources()
                .getColor(R.color.blue));
            mRemote_parent_game_name.setTextColor(activity.getResources().getColor(R.color.white));

        }
        else if (value == MessageDef.REMOTE_GAME)
        {
            mRemote_parent_touchs.setBackgroundResource(R.drawable.remote_touch_select);
            mRemote_parent_keyboards.setBackgroundResource(R.drawable.remote_keyboard_select);
            mRemote_parent_games.setBackgroundResource(R.drawable.remote_parent_game_on);

            mRemote_parent_touch_name.setTextColor(activity.getResources().getColor(R.color.white));
            mRemote_parent_keyboard_name.setTextColor(activity.getResources().getColor(
                R.color.white));
            mRemote_parent_game_name.setTextColor(activity.getResources().getColor(R.color.blue));

        }
    }
}
