package com.hisilicon.multiscreen.mybox;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.view.WindowManager;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.multiscreen.protocol.utils.ServiceUtil;

public class WelcomeActivity extends Activity
{
    /**
     * CN:1秒后跳转
     */
    private final long SPLASH_LENGTH = 1000;

    private Handler myHandler = new Handler();

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        initView();
        initData();
    }

    @Override
    protected void onResume()
    {
        super.onResume();
        myHandler.postDelayed(splash, SPLASH_LENGTH);
    };

    @Override
    protected void onPause()
    {
        super.onPause();
        myHandler.removeCallbacks(splash);
    };

    private void initView()
    {
        // CN:允许布局被状态栏遮盖，防止退出全屏后重新布局。
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN);
        getWindow().addFlags(WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS);
        setContentView(R.layout.mybox_welcome);
    }

    private void initData()
    {
        ServiceUtil.startMultiScreenControlService(this);
    }

    private Runnable splash = new Runnable()
    {
        public void run()
        {
            showStatusBar();
            startTheActivity();
        }
    };

    /**
     * Show status bar of system.<br>
     * CN:在欢迎页面提前显示系统状态栏，防止设备发现页面UI抖动。
     */
    private void showStatusBar()
    {
        getWindow().setFlags(~WindowManager.LayoutParams.FLAG_FULLSCREEN,
            WindowManager.LayoutParams.FLAG_FULLSCREEN);
    }

    /**
     * Show guide activity if this application runs at first time, otherwise
     * start home activity.<br>
     * CN:判断程序是第几次运行，如果是第一次运行则显示引导页面，否则启动首页。
     */
    private void startTheActivity()
    {
        if (AppPreference.isAppFirstUse())
        {
            Intent intent = new Intent(WelcomeActivity.this, GuideActivity.class);
            startActivity(intent);
            finish();
        }
        else
        {
            Intent intent;
            boolean isHomePageRemote =
                readStatusPreference(MultiSettingActivity.HOMEPAGE_REMOTE_KEY);
            if (isHomePageRemote == true)
            {
                intent = new Intent(WelcomeActivity.this, RemoteActivity.class);
            }
            else
            {
                intent = new Intent(WelcomeActivity.this, DeviceDiscoveryActivity.class);
            }
            startActivity(intent);
            finish();
        }
    }

    /**
     * Read enable/disable record.<br>
     * CN:开启/关闭记录读取。
     * @param statusKey
     */
    private boolean readStatusPreference(String statusKey)
    {
        SharedPreferences prefrence =
            getSharedPreferences(MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        return prefrence.getBoolean(statusKey, false);
    }
}
