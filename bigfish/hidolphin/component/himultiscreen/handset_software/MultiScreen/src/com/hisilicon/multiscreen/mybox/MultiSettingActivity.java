package com.hisilicon.multiscreen.mybox;

import android.app.Activity;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * CN：设置界面。
 */
public class MultiSettingActivity extends Activity implements OnClickListener
{
    /**
     * Setting status name in preference.
     */
    public static final String SETTING_STATUS_FILE_NAME = "Setting_Status";

    /**
     * Preference key records VIME switch status.
     */
    public static final String VIME_STATUS_KEY = "vime";

    /**
     * Preference key records SENSOR switch status.
     */
    public static final String SENSOR_STATUS_KEY = "sensor";

    /**
     * Preference key records VIDEO switch status.
     */
    public static final String VIDEO_STATUS_KEY = "video";

    /**
     * Preference key records AUDIO switch status.
     */
    public static final String AUDIO_STATUS_KEY = "audio";

    /**
     * Preference key records VIBRATOR switch status.
     */
    public static final String VIBRATOR_STATUS_KEY = "vibrator";

    /**
     * Preference key records HomePage Remote status.<br>
     */
    public static final String HOMEPAGE_REMOTE_KEY = "homepage_remote";

    /**
     * Preference key records iScene status.<br>
     */
    //public static final String SCENE_KEY = "iscene";

    /**
     * CN：返回按钮。
     */
    private Button mTitle_logo_img;

    /**
     * CN：设备显示信息。
     */
    private TextView mTitle_user_txt;

    /**
     * CN：帮助的布局。
     */
    private RelativeLayout mHelp_layout;

    /**
     * CN：关于的布局。
     */
    private RelativeLayout mIdea_layout;

    /**
     * CN：虚拟输入法按钮。
     */
    private Button mSet_Vime;

    /**
     * CN：体感按钮。
     */
    private Button mSet_Sensor;

    /**
     * CN：视频按钮。
     */
    private Button mSet_Video;

    /**
     * CN：音频按钮。
     */
    private Button mSet_Audio;

    /**
     * CN：震动按钮。
     */
    private Button mSet_Vibrator;

    /**
     * Button of setting remote as home page.<br>
     * CN:设置首页为遥控器。
     */
    private Button mBtnSetHomePage;

    /**
     * Button of setting iScene.<br>
     * CN:智能切换开关按钮。
     */
    //private Button mBtnSetScene;

    /**
     * CN：虚拟输入法开启或者关闭状态。
     */
    private boolean vime_status = false;

    /**
     * CN：体感开启或者关闭状态。
     */
    private boolean sensor_status = false;

    /**
     * CN：视频开启或者关闭状态。
     */
    private boolean video_status = false;

    /**
     * CN：音频开启或者关闭状态。
     */
    private boolean audio_status = false;

    /**
     * CN：震动开启或者关闭状态。
     */
    private boolean vibrator_status = false;

    /**
     * CN:首页是否设为遥控器。
     */
    private boolean mHomePage_remote_status = false;

    /**
     * CN:智能切换开启或关闭状态。
     */
    //private boolean mScene_status = false;

    private MultiScreenControlService mMultiScreenControlService = null;

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        LogTool.d("onCreate.");
        super.onCreate(savedInstanceState);
        initData();
        initView();
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();
    }

    @Override
    public void onBackPressed()
    {
        LogTool.v("onBackPressed.");
        super.onBackPressed();
        finish();
    }

    @Override
    public void onClick(View v)
    {
        handleClick(v);
    }

    private void initData()
    {
        mMultiScreenControlService = MultiScreenControlService.getInstance();
    }

    private void initView()
    {
        LogTool.d("initView");

        setContentView(R.layout.mybox_setting);
        mTitle_logo_img = (Button) findViewById(R.id.title_logo_img);
        mTitle_logo_img.setOnClickListener(this);

        mTitle_user_txt = (TextView) findViewById(R.id.title_user_txt);
        mTitle_user_txt.setText(getResources().getString(R.string.setting_title));

        mHelp_layout = (RelativeLayout) findViewById(R.id.help_layout);
        mHelp_layout.setOnClickListener(this);

        mIdea_layout = (RelativeLayout) findViewById(R.id.idea_layout);
        mIdea_layout.setOnClickListener(this);

        mSet_Vime = (Button) findViewById(R.id.set_vime);
        mSet_Vime.setOnClickListener(this);

        mSet_Sensor = (Button) findViewById(R.id.set_sensor);
        mSet_Sensor.setOnClickListener(this);

        mSet_Video = (Button) findViewById(R.id.set_video);
        mSet_Video.setOnClickListener(this);

        mSet_Audio = (Button) findViewById(R.id.set_audio);
        mSet_Audio.setOnClickListener(this);

        mSet_Vibrator = (Button) findViewById(R.id.set_vibrator);
        mSet_Vibrator.setOnClickListener(this);

        mBtnSetHomePage = (Button) findViewById(R.id.set_homepage_remote);
        mBtnSetHomePage.setOnClickListener(this);

        // hide iScene
        //mBtnSetScene = (Button) findViewById(R.id.set_iScene);
        //mBtnSetScene.setOnClickListener(this);

        initStatusPreference();
    }

    private void initStatusPreference()
    {
        vime_status = readStatusPreference(VIME_STATUS_KEY, true);
        updateStatus(vime_status, mSet_Vime);

        sensor_status = readStatusPreference(SENSOR_STATUS_KEY, false);
        updateStatus(sensor_status, mSet_Sensor);

        video_status = readStatusPreference(VIDEO_STATUS_KEY, true);
        updateStatus(video_status, mSet_Video);

        audio_status = readStatusPreference(AUDIO_STATUS_KEY, true);
        updateStatus(audio_status, mSet_Audio);

        vibrator_status = readStatusPreference(VIBRATOR_STATUS_KEY, true);
        updateStatus(vibrator_status, mSet_Vibrator);

        mHomePage_remote_status = readStatusPreference(HOMEPAGE_REMOTE_KEY, false);
        updateStatus(mHomePage_remote_status, mBtnSetHomePage);

        //mScene_status = readStatusPreference(SCENE_KEY, false);
        //updateStatus(mScene_status, mBtnSetScene);
    }

    private void handleClick(View v)
    {
        switch (v.getId())
        {
            case R.id.title_logo_img:
            {
                finish();
            }
                break;
            case R.id.help_layout:
            {
                startActivity(new Intent(this, GuideActivity.class));
            }
                break;
            case R.id.idea_layout:
            {
                startActivity(new Intent(this, AboutActivity.class));
            }
                break;
            case R.id.set_vime:
            {
                vime_status = !vime_status;
                updateStatus(vime_status, mSet_Vime);
            }
                break;
            case R.id.set_sensor:
            {
                sensor_status = !sensor_status;
                updateStatus(sensor_status, mSet_Sensor);
            }
                break;
            case R.id.set_video:
            {
                video_status = !video_status;
                updateStatus(video_status, mSet_Video);
            }
                break;
            case R.id.set_audio:
            {
                audio_status = !audio_status;
                updateStatus(audio_status, mSet_Audio);
            }
                break;
            case R.id.set_vibrator:
            {
                vibrator_status = !vibrator_status;
                updateStatus(vibrator_status, mSet_Vibrator);
            }
                break;
            case R.id.set_homepage_remote:
            {
                mHomePage_remote_status = !mHomePage_remote_status;
                updateStatus(mHomePage_remote_status, mBtnSetHomePage);
            }
                break;
            //case R.id.set_iScene:
            //{
            //    mScene_status = !mScene_status;
            //    updateStatus(mScene_status, mBtnSetScene);
            //}
            //    break;
            default:
                break;
        }
    }

    /**
     * CN：更新开关状态。
     */
    private void updateStatus(boolean status, Button btn)
    {
        if (status == true)
        {
            btn.setBackgroundResource(R.drawable.mybox_setting_on);
        }
        else
        {
            btn.setBackgroundResource(R.drawable.mybox_setting_off);
        }

        if (btn == mSet_Vime)
        {
            writeStatusPreference(VIME_STATUS_KEY, status);
        }
        else if (btn == mSet_Sensor)
        {
            writeStatusPreference(SENSOR_STATUS_KEY, status);
        }
        else if (btn == mSet_Video)
        {
            writeStatusPreference(VIDEO_STATUS_KEY, status);
            switchVideoStatus(status);
        }
        else if (btn == mSet_Audio)
        {
            writeStatusPreference(AUDIO_STATUS_KEY, status);
            switchAudioStatus(status);
        }
        else if (btn == mSet_Vibrator)
        {
            writeStatusPreference(VIBRATOR_STATUS_KEY, status);
        }
        else if (btn == mBtnSetHomePage)
        {
            writeStatusPreference(HOMEPAGE_REMOTE_KEY, status);
        }
        //else if (btn == mBtnSetScene)
        //{
        //    writeStatusPreference(SCENE_KEY, status);
        //    switchScene(status);
        //}
        else
        {
            LogTool.d("Unkown button.");
        }
    }

    /**
     * CN:开关音频。
     * @param status
     */
    private void switchAudioStatus(boolean status)
    {
        if (mMultiScreenControlService != null)
        {
            mMultiScreenControlService.setAudioPlay(status);
        }
    }

    /**
     * CN:开关视频。
     * @param status 打开还是关闭的状态
     */
    private void switchVideoStatus(boolean status)
    {
        if (mMultiScreenControlService != null)
        {
            mMultiScreenControlService.setVideoPlay(status);
        }
    }

    /**
     * Switch iScene status.<br>
     * CN:设置智能切换状态。
     * @param isOpen
     */
    private void switchScene(boolean isOpen)
    {
        MultiScreenControlService.switchScene(isOpen);
    }

    /**
     * Read enable/disable record.<br>
     * @param statusKey
     * @param defValue
     */
    private boolean readStatusPreference(String statusKey, boolean defValue)
    {
        SharedPreferences prefrence = getSharedPreferences(SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        return prefrence.getBoolean(statusKey, defValue);
    }

    /**
     * Write enable/disable record.<br>
     * @param statusKey
     * @param isOpened
     */
    private void writeStatusPreference(String statusKey, boolean isOpened)
    {
        SharedPreferences.Editor editor =
            getSharedPreferences(SETTING_STATUS_FILE_NAME, MODE_PRIVATE).edit();
        editor.putBoolean(statusKey, isOpened);
        editor.commit();
    }

    private float readStatusPreference(String statusKey, float defValue)
    {
        SharedPreferences prefrence =
            getSharedPreferences(MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        return prefrence.getFloat(statusKey, defValue);
    }

    private void writeStatusPreference(String statusKey, float value)
    {
        SharedPreferences.Editor editor =
            getSharedPreferences(SETTING_STATUS_FILE_NAME, MODE_PRIVATE).edit();
        editor.putFloat(statusKey, value);
        editor.commit();
    }
}
