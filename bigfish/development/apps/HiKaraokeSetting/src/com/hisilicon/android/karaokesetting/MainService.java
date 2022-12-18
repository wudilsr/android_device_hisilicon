package com.hisilicon.android.karaokesetting;

import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;

import android.R.integer;
import android.app.Dialog;
import android.app.Service;
import android.app.AlertDialog;
import android.os.Binder;
import android.os.IBinder;
import android.os.Handler;
import android.os.Message;
import android.content.Intent;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.IntentFilter;
import android.view.WindowManager;
import android.view.View;
import android.view.Display;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View.OnKeyListener;
import android.view.View.OnClickListener;
import android.util.Log;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.SeekBar;
import android.widget.TextView;
import android.widget.SimpleAdapter;
import android.widget.RelativeLayout;
import android.widget.AdapterView;
import android.widget.AdapterView.OnItemClickListener;
import android.widget.AdapterView.OnItemSelectedListener;
import android.graphics.Typeface;

//import com.hisilicon.android.PQManager;
import com.hisilicon.android.karaokesetting.R;
import com.cmcc.media.Micphone;
import com.cmcc.media.RTSoundEffects;
import android.os.SystemProperties;

import android.os.PowerManager;
import android.os.PowerManager.WakeLock;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.os.ServiceManager;

public class MainService extends Service {

    private static String TAG = "PQSetting";
    private IBinder binder = new MyBinder();

    // public static DisplayDialog cDisplayDialog;

    public static EngineDialog cEngineDialog;

    // public static ColorDialog cColorDialog;

    public static AlertDialog mDisplayDialog;

    public static AlertDialog mEngineDialog;

    public static AlertDialog mColorDialog;
    //public HiKaraokeReceiver hiKaraokeReceiver;

    private static Handler dHandler = null;

    private static DismissThread dismissThread = null;

    private static boolean isDShow = false;
    private static int mSoundMode;
    public static long startTime = 0;
    private static Context mmContext;

    public enum SoundType {
        KARAOKE_MODE, SOUNDEFFS_MODE
    }

    public static SoundType mType = SoundType.KARAOKE_MODE;

    private static final int FRESH_BUTTON_RIGHT = 1;
    private static final int FRESH_BUTTON_LEFT = 2;
    private static final int mDelayTime = 300;

    private static Handler mhandler = new Handler() {
        public void handleMessage(Message msg) {
            switch (msg.what) {
            case FRESH_BUTTON_LEFT:
                switch (mType) {
                case KARAOKE_MODE:
                    Common.karaoke_mode_left.setImageResource(R.drawable.left_normal);
                    break;
                case SOUNDEFFS_MODE:
                    Common.soundEffects_left.setImageResource(R.drawable.left_normal);
                    break;

                default:
                    break;
                }

            case FRESH_BUTTON_RIGHT:
                switch (mType) {
                case KARAOKE_MODE:
                    Common.karaoke_mode_right.setImageResource(R.drawable.right_normal);
                    break;
                case SOUNDEFFS_MODE:
                    Common.soundEffects_right.setImageResource(R.drawable.right_normal);
                    break;

                default:
                    break;
                }

            default:
                break;
            }
        }
    };

    @Override
    public void onCreate() {
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent arg0) {
        return binder;
    }

    public class MyBinder extends Binder {
        public MainService getService() {
            return MainService.this;
        }
    }

    @Override
    public void onStart(Intent intent, int startId) {
        super.onStart(intent, startId);
        mmContext = MainService.this;
        initMICDate();
        if (cEngineDialog == null) {
            cEngineDialog = new EngineDialog(MainService.this);
        }
        Common.soundEffects_array = getResources().getStringArray(R.array.soundEffects_array);
        Common.onoff_array = getResources().getStringArray(R.array.onoff_array);

        if (mEngineDialog != null)
            mEngineDialog.dismiss();

        mEngineDialog = cEngineDialog.showEngineDialog();
        dialogAutoDismiss(mEngineDialog);

        //IntentFilter filter = new IntentFilter();
        //filter.addAction(Intent.ACTION_SCREEN_OFF);
        //registerReceiver(hiKaraokeReceiver, filter);

    }

//    public class PowerReceiver extends BroadcastReceiver {
//        private WakeLock wakeLock = null;
//
//        @Override
//        public void onReceive(Context context, Intent intent) {
//            // TODO Auto-generated method stub
//            if (intent.getAction().equals("com.hisilicon.sendPowerService")) {
//
//                PowerManager pm = (PowerManager) mmContext.getSystemService(Context.POWER_SERVICE);
//                wakeLock = pm.newWakeLock(PowerManager.SUSPEND_WAKE_LOCK, this.getClass().getCanonicalName());
//                acquireWakeLock();
//                String status = SystemProperties.get("persist.sys.karaoke.onoff");
//                if (status.equals("ON")) {
//                    Common.micphone.stop();
//                    Common.micphone.release();
//                    SystemProperties.set("persist.sys.karaoke.onoff", "OFF");
//                }
//                Log.i("liangguofu", "*************PowerReceiver*******接收到广播********");
//                wakeLock.release();
//            }
//        }
//
//        private void acquireWakeLock() {
//            synchronized (wakeLock) {
//                try {
//                    wakeLock.acquire();
//                } catch (Exception e) {
//
//                }
//            }
//        }
//    }
    /*
    public class HiKaraokeReceiver extends BroadcastReceiver {

        private static final String ACTION = Intent.ACTION_SCREEN_OFF;
            private WakeLock wakeLock = null;
        @Override
        public void onReceive(Context context, Intent intent) {

            if (intent.getAction().equals(ACTION)) {
//                Intent intent2 = new Intent();
//                intent2.setAction("com.hisilicon.sendPowerService");
//                context.sendBroadcast(intent2);
                Log.i("liangguofu", "*************HiKaraokeReceiver*******接收到广播********");

                  PowerManager pm = (PowerManager) mmContext.getSystemService(Context.POWER_SERVICE);
                  wakeLock = pm.newWakeLock(PowerManager.SUSPEND_WAKE_LOCK, this
                    .getClass().getCanonicalName());
                acquireWakeLock();
                String status = SystemProperties.get("persist.sys.karaoke.onoff");
                if(status.equals("ON"))
                {
                        Common.micphone.stop();
                      Common.micphone.release();
                      SystemProperties.set("persist.sys.karaoke.onoff","OFF");
                }

                wakeLock.release();
            }
        }

        private void acquireWakeLock() {
            synchronized (wakeLock) {
                try {
                    wakeLock.acquire();
                } catch (Exception e) {
                    //Log.e(TAG, "exception in acquireWakeLock()", e);
                }
            }
        }

    }*/

    public static class SeekBarListener implements OnKeyListener {
        private SeekBar seekBar;
        private TextView textView;

        public SeekBarListener(SeekBar seekBar, TextView textView) {
            this.seekBar = seekBar;
            this.textView = textView;
        }

        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
            if (event.getAction() == KeyEvent.ACTION_UP)
                return false;
            else {
                startTime = System.currentTimeMillis();
                int progress = seekBar.getProgress();
                int pg_count;
                pg_count = progress / 7;
                int id = v.getId();
                switch (keyCode) {
                case KeyEvent.KEYCODE_DPAD_LEFT:
                    pg_count--;
                    pg_count = pg_count < 0 ? 0 : pg_count;
                    if (progress == 100) {
                        progress = 98;
                    } else {
                        progress = pg_count * 7;
                    }
                    break;
                case KeyEvent.KEYCODE_DPAD_RIGHT:
                    pg_count++;
                    pg_count = pg_count > 14 ? 15 : pg_count;
                    if (pg_count == 15) {
                        progress = 100;
                    } else {
                        progress = pg_count * 7;
                    }
                    break;
                default:
                    break;
                }
                seekBar.setProgress(progress);
                textView.setText(progress + "");

                switch (id) {
                case R.id.micphone_layout:
                    // Common.mPQManager.setBrightness(progress);
                    Common.micphone = (Micphone) mmContext.getSystemService("Micphone");
                    Common.micphone.setVolume(progress == 100 ? 99 : progress);
                    Common.volume = String.valueOf(progress);
                    SystemProperties.set("persist.sys.karaoke.volume", Common.volume);
                    break;
                }
                return false;
            }
        }
    }

    public static class LayoutListener implements OnKeyListener {
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
            if (event.getAction() == KeyEvent.ACTION_UP)
                return false;
            startTime = System.currentTimeMillis();
            int id = v.getId();
            if (keyCode == KeyEvent.KEYCODE_DPAD_LEFT || keyCode == KeyEvent.KEYCODE_DPAD_RIGHT) {
                switch (id) {
                case R.id.karaoke_mode_layout:
                    mType = SoundType.KARAOKE_MODE;
                    break;
                case R.id.soundEffects_layout:
                    mType = SoundType.SOUNDEFFS_MODE;
                    break;

                }
                RefreshText(mType, keyCode);
            }
            return false;

        }
    }

    private static void saveSoundEffects() {

        if (mSoundMode == 1) {
            SystemProperties.set("persist.sys.karaoke.type", "Mode_Studio");
        } else if (mSoundMode == 2) {
            SystemProperties.set("persist.sys.karaoke.type", "Mode_KTV");
        } else if (mSoundMode == 3) {
            SystemProperties.set("persist.sys.karaoke.type", "Mode_Concert");
        }
    }

    private static void saveKaraokOnOff() {
        if (Common.KaraokOnOff == true) {
            SystemProperties.set("persist.sys.karaoke.onoff", "ON");
        } else if (Common.KaraokOnOff == false) {
            SystemProperties.set("persist.sys.karaoke.onoff", "OFF");
        }
    }
    public static void initMICDate()
    {

        Common.soundEffects_type = SystemProperties.get("persist.sys.karaoke.type");
        if(Common.soundEffects_type==null || Common.soundEffects_type.equals(""))
        {
            Common.soundEffects_type = "Mode_Studio";
            SystemProperties.set("persist.sys.karaoke.type", Common.soundEffects_type);
        }

        int init_engine = 0;
        if (Common.soundEffects_type.equals("Mode_Studio")) {
            init_engine = 1;
        }
        else if (Common.soundEffects_type.equals("Mode_KTV")) {
            init_engine = 2;
        }
        else if (Common.soundEffects_type.equals("Mode_Concert")) {
            init_engine = 3;
        }
        mSoundMode = init_engine;


        Common.volume = SystemProperties.get("persist.sys.karaoke.volume");
        if(Common.volume==null || Common.volume.equals(""))
        {
            Common.volume = "49";
            SystemProperties.set("persist.sys.karaoke.volume", Common.volume);
        }

        Common.MIC_ONOFF = SystemProperties.get("persist.sys.karaoke.onoff");
        if(Common.MIC_ONOFF==null || Common.MIC_ONOFF.equals(""))
        {
            Common.MIC_ONOFF = "OFF";
            SystemProperties.set("persist.sys.karaoke.onoff", Common.MIC_ONOFF);
        }
        /*if (Common.MIC_ONOFF.equals("ON")) {
            Common.KaraokOnOff = true;
        }
        else if (Common.MIC_ONOFF.equals("OFF")) {
            Common.KaraokOnOff = false;
        }*/

    }
    public static void startMIC()
    {
        if (!Common.KaraokOnOff) {
            Common.micphone.initial();
            Common.micphone.start();
            Common.rtSoundEffects.setReverbMode(mSoundMode);
            int mVolume = Integer.parseInt(Common.volume);
            Common.micphone.setVolume(mVolume == 100 ? 99 : mVolume);
        }
        Common.KaraokOnOff = true;
        saveKaraokOnOff();
    }
    public static void stopMIC()
    {
        if (Common.KaraokOnOff) {
            Common.micphone.stop();
            Common.micphone.release();
        }
        Common.KaraokOnOff = false;
        saveKaraokOnOff();
    }
    private static void RefreshText(SoundType type, int keycode) {
        Common.rtSoundEffects = (RTSoundEffects) mmContext.getSystemService("RTSoundEffects");
        switch (keycode) {
        case KeyEvent.KEYCODE_DPAD_LEFT: {
            switch (type) {
            case KARAOKE_MODE:
                Common.karaoke_mode_left.setImageResource(R.drawable.left_focused);
                Common.karaoke_mode_text.setText(Common.onoff_array[0]);

                Common.micphone_text.setTypeface(Typeface.MONOSPACE, Typeface.ITALIC);
                Common.micphone_layout.setFocusableInTouchMode(false);
                Common.micphone_layout.setFocusable(false);
                Common.micphone_layout.setBackgroundResource(R.drawable.input_disable_wide);
                Common.micphone_seekbar.setFocusable(false);
                Common.soundEffects_text.setTypeface(Typeface.MONOSPACE, Typeface.ITALIC);
                Common.soundEffects_layout.setFocusableInTouchMode(false);
                Common.soundEffects_layout.setFocusable(false);
                Common.soundEffects_layout.setBackgroundResource(R.drawable.input_disable_wide);
                stopMIC();
                break;
            case SOUNDEFFS_MODE:
                Common.soundEffects_left.setImageResource(R.drawable.left_focused);
                mSoundMode--;
                mSoundMode = mSoundMode < 1 ? 1 : mSoundMode;
                Common.rtSoundEffects.setReverbMode(mSoundMode);
                Common.soundEffects_text.setText(Common.soundEffects_array[mSoundMode - 1]);
                saveSoundEffects();
                break;

            }
            mhandler.removeMessages(FRESH_BUTTON_LEFT);
            mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_LEFT, mDelayTime);
            break;
        }
        case KeyEvent.KEYCODE_DPAD_RIGHT:
            switch (type) {
            case KARAOKE_MODE:
                Common.karaoke_mode_right.setImageResource(R.drawable.right_focused);
                Common.karaoke_mode_text.setText(Common.onoff_array[1]);

                Common.micphone_seekbar.setFocusable(true);
                Common.micphone_text.setTypeface(Typeface.DEFAULT, Typeface.NORMAL);
                Common.micphone_layout.setFocusableInTouchMode(true);
                Common.micphone_layout.setFocusable(true);
                Common.micphone_layout.setBackgroundResource(R.drawable.input_wide_selector);
                Common.soundEffects_text.setTypeface(Typeface.DEFAULT, Typeface.NORMAL);
                Common.soundEffects_layout.setFocusableInTouchMode(true);
                Common.soundEffects_layout.setFocusable(true);
                Common.soundEffects_layout.setBackgroundResource(R.drawable.input_wide_selector);
                startMIC();
                break;
            case SOUNDEFFS_MODE:
                Common.soundEffects_right.setImageResource(R.drawable.right_focused);
                mSoundMode++;
                mSoundMode = mSoundMode > 3 ? 3 : mSoundMode;
                Common.rtSoundEffects.setReverbMode(mSoundMode);

                Common.soundEffects_text.setText(Common.soundEffects_array[mSoundMode - 1]);
                saveSoundEffects();

                break;
            }
            mhandler.removeMessages(FRESH_BUTTON_RIGHT);
            mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_RIGHT, mDelayTime);
            break;
        }
    }

    public static void dialogAutoDismiss(Dialog dialog) {
        if (!isDShow) {
            dHandler = new Handler();
            dismissThread = new DismissThread(dialog);
            startTime = System.currentTimeMillis();
            dHandler.post(dismissThread);
            isDShow = true;
        } else {
            if (dismissThread != null)
                dismissThread.SetDialog(dialog);
            startTime = System.currentTimeMillis();
        }
    }

    private static class DismissThread implements Runnable {
        Dialog dialog = null;

        public DismissThread(Dialog dialog) {
            this.dialog = dialog;
        }

        public void SetDialog(Dialog dialog) {
            this.dialog = dialog;
        }

        public void run() {
            long endTime = System.currentTimeMillis();
            long distance = endTime - startTime;

            if (distance >= 10 * 1000) {
                if (dialog != null)
                    dialog.dismiss();

                dHandler.removeCallbacks(dismissThread);
                isDShow = false;
            } else {
                dHandler.postDelayed(this, 1000);
            }
        }
    }



}
