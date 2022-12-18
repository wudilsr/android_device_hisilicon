package com.hisilicon.multiscreen.vime;

import android.app.Service;
import android.content.Intent;
import android.content.SharedPreferences;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.view.Gravity;
import android.widget.Toast;

import com.hisilicon.multiscreen.mybox.MultiScreenControlService;
import com.hisilicon.multiscreen.mybox.MultiSettingActivity;
import com.hisilicon.multiscreen.mybox.R;
import com.hisilicon.multiscreen.protocol.HiDeviceInfo;
import com.hisilicon.multiscreen.protocol.message.Action;
import com.hisilicon.multiscreen.protocol.message.VImeTextInfo;
import com.hisilicon.multiscreen.protocol.remote.IVImeActivityHandler;
import com.hisilicon.multiscreen.protocol.remote.VImeClientController;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;

/**
 * VIME control service.<br>
 * CN:虚拟输入法控制服务类。
 * @since MultiScreen V2.0.1.1 2013/01/11: first create
 */
public class VImeClientControlService extends Service
{
    /**
     * Index of first argument in message. <br>
     * CN:消息中第一个参数的索引。
     */
    private static final int FIRST_ARGUMENT_INDEX = 0;

    /**
     * Index of second argument in message. <br>
     * CN:消息中第二个参数的索引。
     */
    private static final int SECOND_ARGUMENT_INDEX = 1;

    /**
     * Index of third argument in message. <br>
     * CN:消息中第三个参数的索引。
     */
    private static final int THIRD_ARGUMENT_INDEX = 2;

    /**
     * Index of fourth argument in message.<br>
     * CN:消息中的第四个参数的索引。
     */
    private static final int FOURTH_ARGUMENT_INDEX = 3;

    /**
     * Index of fifth argument in message.<br>
     * CN:消息中的第五个参数的索引。
     */
    private static final int FIFTH_ARGUMENT_INDEX = 4;

    /**
     * Instance of VIME client control service.
     */
    private static VImeClientControlService mVImeControlServiceInstance = null;

    /**
     * VIME client control class.
     */
    private VImeClientController mVImeCenter = null;

    /**
     * True if input activity is on top.<br>
     * CN:显示输入页面是否在顶层。
     */
    private boolean mIsActivityOnTop = false;

    /**
     * Handler for adding show toast runnable to the message queue.<br>
     * CN:将显示toast的runnable加入消息队列。
     */
    private Handler mHandler = null;

    /**
     * Client APK handler.<br>
     * CN:活动处理回调。
     */
    private IVImeActivityHandler mActivityHandler = new IVImeActivityHandler()
    {
        @Override
        public void openVimeSwitch()
        {
            // Update switch of VIME in setting of MultiScreen APP.
            // writeVIMEStatusPreference(true);
            // Intent intent = new
            // Intent(MultiScreenIntentAction.SWITCH_VIME_SETTING);
            // sendBroadcast(intent);
        }

        @Override
        public void closeVimeSwitch()
        {
            // Update switch of VIME in setting of MultiScreen APP.
            // writeVIMEStatusPreference(false);
            // Intent intent = new
            // Intent(MultiScreenIntentAction.SWITCH_VIME_SETTING);
            // sendBroadcast(intent);
            showVImeDisableToast();
        }

        @Override
        public void callInput(Action action)
        {
            Intent intent =
                new Intent(VImeClientControlService.getInstance(), ContentInputActivity.class);
            intent.setFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
            Bundle bundle = new Bundle();
            bundle.putInt(VImeTextInfo.INPUT_TYPE, (Integer) action.getArgument(0)
                .getArgumentValue(FIRST_ARGUMENT_INDEX).getVaule());
            bundle.putInt(VImeTextInfo.INPUT_OPTION, (Integer) action.getArgument(0)
                .getArgumentValue(SECOND_ARGUMENT_INDEX).getVaule());
            bundle.putString(VImeTextInfo.INPUT_TEXT, (String) action.getArgument(0)
                .getArgumentValue(THIRD_ARGUMENT_INDEX).getVaule());
            bundle.putInt(VImeTextInfo.SRC_START_SELECTION, (Integer) action.getArgument(0)
                .getArgumentValue(FOURTH_ARGUMENT_INDEX).getVaule());
            bundle.putInt(VImeTextInfo.SRC_END_SELECTION, (Integer) action.getArgument(0)
                .getArgumentValue(FIFTH_ARGUMENT_INDEX).getVaule());
            intent.putExtras(bundle);
            startActivity(intent);
        }

        /**
         * End input by self.<br>
         */
        @Override
        public void endInputBySelf()
        {
            Intent intent = new Intent();
            intent.setAction(MultiScreenIntentAction.END_INPUT_BY_PHONE);
            sendBroadcast(intent);
        }

        /**
         * End input by STB.<br>
         */
        @Override
        public void endInputByServer()
        {
            /* 如果是STB发起的关闭，就不用再发ENDINPUT消息 */
            Intent intent = new Intent(MultiScreenIntentAction.END_INPUT_BY_STB);
            sendBroadcast(intent);
            LogTool.d("end input by STB.");
        }

        /**
         * Get status of input activity on top.
         */
        @Override
        public boolean isInputActivityOnTop()
        {
            // CN:输入页面置顶数量.
            return mIsActivityOnTop;
        }

    };

    /**
     * Get the single instance of VImeClientControlService.<br>
     * CN:获得VImeClientControlService的单实例。
     * @return instance of VImeClientControlService
     */
    public static VImeClientControlService getInstance()
    {
        if (mVImeControlServiceInstance == null)
        {
            LogTool.e("VImeControlServiceInstance is null");
        }
        return mVImeControlServiceInstance;
    }

    @Override
    public void onCreate()
    {
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent intent)
    {
        return null;
    }

    @Override
    public int onStartCommand(Intent intent, int flg, int startid)
    {
        LogTool.v("VImeClientControl service onStartCommand.");
        super.onStartCommand(intent, flg, startid);

        mVImeControlServiceInstance = this;
        mHandler = new Handler();
        // CN:服务可能重启，关闭输入框（不发消息）。
        mActivityHandler.endInputByServer();
        mIsActivityOnTop = false;
        reset();
        // CN:非粘性 START_NOT_STICKY，重传Intent START_REDELIVER_INTENT。
        return START_NOT_STICKY;
    }

    @Override
    public void onDestroy()
    {
        super.onDestroy();

        LogTool.v("VImeClientControl service onDestroy.");

        if (mVImeCenter.isVImeEnable())
        {
            // CN:VIme打开了才向STB发送关闭消息。
            LogTool.v("VIme will be disable.");
            disableVIme();
        }

        mVImeCenter.destroy();
    }

    /**
     * Reset VIME server.<br>
     * CN:重置VIME服务。
     */
    public boolean reset()
    {
        boolean isOK;
        boolean isSwitchOpen = readVIMEStatusPreference();
        isOK = initVimeServer(MultiScreenControlService.getInstance().getHiDevice(), isSwitchOpen);
        return isOK;
    }

    /**
     * Enable the virtual IME.<br>
     * CN:使能虚拟输入法。
     * @return - true if success
     */
    public boolean enableVIme()
    {
        return mVImeCenter.enableVIme();
    }

    /**
     * Disable virtual IME.<br>
     * CN:禁用虚拟输入法。
     * @return - true if success
     */
    public boolean disableVIme()
    {
        return mVImeCenter.disableVIme();
    }

    /**
     * Return true if status of VIme is input on client.<br>
     * CN:检查VIme状态机是否为输入状态。
     * @return - true if status is input.
     */
    public boolean isInputStatusOnClient()
    {
        return mVImeCenter.isInputStatusOnClient();
    }

    /**
     * Set input activity top status.<br>
     * CN:设置输入页面顶层状态。
     * @param isNewOnTop - true if a new activity is on top.
     */
    public void setInputActivityTopStatus(boolean isNewOnTop)
    {
        mIsActivityOnTop = isNewOnTop;
    }

    /**
     * Read record of VIME switch status.<br>
     * CN:读取虚拟输入法开关状态记录。
     * @return - true if switch opened
     */
    public boolean readVIMEStatusPreference()
    {
        boolean isOpened = true;
        SharedPreferences prefrence =
            getSharedPreferences(MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE);
        isOpened = prefrence.getBoolean(MultiSettingActivity.VIME_STATUS_KEY, true);

        // boolean isFirstTime = true;
        //
        // SharedPreferences prefrence =
        // getSharedPreferences(SettingActivity.VIME_STATUS_FILE_NAME,
        // MODE_PRIVATE);
        // isFirstTime =
        // prefrence.getBoolean(SettingActivity.VIME_FIRST_USED_KEY, true);
        //
        // if (isFirstTime)
        // {
        // isOpened = true;
        // SharedPreferences.Editor editor =
        // getSharedPreferences(SettingActivity.VIME_STATUS_FILE_NAME,
        // MODE_PRIVATE).edit();
        // editor.putBoolean(SettingActivity.VIME_FIRST_USED_KEY, false);
        // editor.putBoolean(SettingActivity.VIME_STATUS_KEY, true);
        // editor.commit();
        // }
        // else
        // {
        // isOpened = prefrence.getBoolean(SettingActivity.VIME_STATUS_KEY,
        // true);
        // }

        return isOpened;
    }

    /**
     * Write enable/disable record of virtual IME.<br>
     * CN:虚拟输入法开启/关闭记录写入。
     * @param isOpened - true if switch opened
     */
    private void writeVIMEStatusPreference(boolean isOpened)
    {
        SharedPreferences.Editor editor =
            getSharedPreferences(MultiSettingActivity.SETTING_STATUS_FILE_NAME, MODE_PRIVATE)
                .edit();
        editor.putBoolean(MultiSettingActivity.VIME_STATUS_KEY, isOpened);
        editor.commit();
    }

    /**
     * Initialize VIME on client while server on start.<br>
     * CN:服务启动时初始化客户端VIME。
     * @param device - device info.
     * @param isSwitchOpened - VIME switch status.
     * @return success if VIME is opened
     */
    private boolean initVimeServer(HiDeviceInfo device, boolean isSwitchOpened)
    {
        boolean isEnableSuccess = false;
        mVImeCenter = VImeClientController.getInstance(device);
        mVImeCenter.setVimeActivityHandler(mActivityHandler);

        if (isSwitchOpened)
        {
            LogTool.d("Send enable VIME");

            isEnableSuccess = enableVIme();
            if (isEnableSuccess)
            {
                LogTool.d("Enable VIME successful.");
            }
            else
            {
                LogTool.e("Enable VIME failed.");
                // CN:开始VIME失败，不自动更新开关。
                // writeVIMEStatusPreference(false);
                Intent intentSwitchVime = new Intent(MultiScreenIntentAction.SWITCH_VIME_SETTING);
                sendBroadcast(intentSwitchVime);
            }
        }
        else
        {
            LogTool.d("Switch closed");
            isEnableSuccess = false;
        }

        return isEnableSuccess;
    }

    /**
     * Show toast when VIme close on Phone.<br>
     * CN:手机自动关闭VIme时显示提示信息。
     */
    private void showVImeDisableToast()
    {
        mHandler.post(new ToastRunnable());
    }

    /**
     * Runnable for showing toast.<br>
     * CN:用于在服务中显示toast的runnable。
     */
    private class ToastRunnable implements Runnable
    {
        @Override
        public void run()
        {
            Toast toast =
                Toast.makeText(getApplicationContext(), R.string.toast_VIME_close,
                    Toast.LENGTH_SHORT);
            toast.setGravity(Gravity.TOP, 0, 0);
            toast.show();
        }
    }
}
