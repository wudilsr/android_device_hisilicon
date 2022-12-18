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
import android.view.WindowManager;
import android.view.View;
import android.view.Display;
import android.view.KeyEvent;
import android.view.LayoutInflater;
import android.view.View.OnKeyListener;
import android.view.View.OnClickListener;
import android.telephony.TelephonyManager;
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
import com.hisilicon.android.karaokesetting.MainService.SoundType;
import com.hisilicon.android.karaokesetting.R;
import com.cmcc.media.Micphone;
import com.cmcc.media.RTSoundEffects;
import android.os.SystemProperties;

public class EngineDialog {

    private Context mContext;

    public EngineDialog(Context m) {
        mContext = m;
    }

    public AlertDialog showEngineDialog() {
        // create ui

        // use custom UI.
        View v = View.inflate(mContext, R.layout.karaoke_set, null);
        initEngineView(v);

        AlertDialog.Builder builder = new AlertDialog.Builder(mContext, R.style.MyTranslucent);
        builder.setTitle(mContext.getString(R.string.engine_mode));
        builder.setView(v, 0, 0, 0, 0);
        AlertDialog dialog = builder.create();
        dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        // dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY);
        dialog.show();

        // set dialog size and position.
        WindowManager.LayoutParams lp = dialog.getWindow().getAttributes();
        WindowManager wm = (WindowManager) mContext.getSystemService(mContext.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        /*
         * if (Common.isPortrait()) { lp.width=(int) (display.getHeight()*0.35);
         * lp.height=(int) (display.getWidth()*0.55); lp.x=(int) (600 *
         * display.getWidth() / display.getHeight()); lp.y=(int) (-400 *
         * display.getHeight() / display.getWidth()); } else {
         *
         * }
         */
        lp.width = (int) (display.getWidth() * 0.35);
        lp.height = (int) (display.getHeight() * 0.55);
        lp.x = 600;
        lp.y = -400;
        lp.alpha = 0.7f;
        dialog.getWindow().setAttributes(lp);
        return dialog;
    }

    private void initEngineView(View v) {
        Common.karaoke_mode_layout = (RelativeLayout) v.findViewById(R.id.karaoke_mode_layout);
        Common.karaoke_mode_text = (TextView) v.findViewById(R.id.karaoke_mode_info);
        Common.karaoke_mode_layout.setOnKeyListener(new MainService.LayoutListener());
        Common.karaoke_mode_layout.requestFocus();
        if (Common.KaraokOnOff) {
            Common.karaoke_mode_text.setText(Common.onoff_array[1]);
        } else {
            Common.karaoke_mode_text.setText(Common.onoff_array[0]);
        }

        Common.soundEffects_layout = (RelativeLayout) v.findViewById(R.id.soundEffects_layout);
        Common.soundEffects_text = (TextView) v.findViewById(R.id.soundEffects_info);
        Common.soundEffects_layout.setOnKeyListener(new MainService.LayoutListener());

        Common.micphone_layout = (RelativeLayout) v.findViewById(R.id.micphone_layout);
        Common.micphone_seekbar = (SeekBar) v.findViewById(R.id.micphone_seekbar);
        Common.micphone_text = (TextView) v.findViewById(R.id.micphone_info);
        Common.micphone_layout.setOnKeyListener(new MainService.SeekBarListener(Common.micphone_seekbar, Common.micphone_text));

        Common.karaoke_mode_left = (ImageView) v.findViewById(R.id.karaoke_mode_left);
        Common.karaoke_mode_right = (ImageView) v.findViewById(R.id.karaoke_mode_right);
        Common.soundEffects_left = (ImageView) v.findViewById(R.id.soundEffects_left);
        Common.soundEffects_right = (ImageView) v.findViewById(R.id.soundEffects_right);
        if (!Common.KaraokOnOff) {
            Common.micphone_text.setTypeface(Typeface.MONOSPACE, Typeface.ITALIC);
            Common.micphone_layout.setFocusableInTouchMode(false);
            Common.micphone_layout.setFocusable(false);
            Common.micphone_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.soundEffects_text.setTypeface(Typeface.MONOSPACE, Typeface.ITALIC);
            Common.soundEffects_layout.setFocusableInTouchMode(false);
            Common.soundEffects_layout.setFocusable(false);
            Common.micphone_seekbar.setFocusable(false);
            Common.soundEffects_layout.setBackgroundResource(R.drawable.input_disable_wide);

        } else {
            Common.micphone_text.setTypeface(Typeface.DEFAULT, Typeface.NORMAL);
            Common.micphone_layout.setFocusableInTouchMode(true);
            Common.micphone_layout.setFocusable(true);
            Common.micphone_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.soundEffects_text.setTypeface(Typeface.DEFAULT, Typeface.NORMAL);
            Common.soundEffects_layout.setFocusableInTouchMode(true);
            Common.soundEffects_layout.setFocusable(true);
            Common.micphone_seekbar.setFocusable(true);
            Common.soundEffects_layout.setBackgroundResource(R.drawable.input_wide_selector);

        }

        RefreshEngineView();
    }

    public void RefreshEngineView() {
        Common.micphone = (Micphone) mContext.getSystemService("Micphone");

        Common.rtSoundEffects = (RTSoundEffects) mContext.getSystemService("RTSoundEffects");


        int init_engine = 0;
        if (Common.soundEffects_type.equals("Mode_Studio")) {
            init_engine = 1;
        }
        if (Common.soundEffects_type.equals("Mode_KTV")) {
            init_engine = 2;
        }
        if (Common.soundEffects_type.equals("Mode_Concert")) {
            init_engine = 3;
        }
        Common.soundEffects_text.setText(Common.soundEffects_array[init_engine - 1]);



        int init_sharpness = Integer.parseInt(Common.volume);
        // int init_sharpness = Common.micphone.getVolume();
        if (init_sharpness < 0 || init_sharpness > 100) {
            init_sharpness = 56;
        }
        Common.micphone_seekbar.setProgress(init_sharpness);
        Common.micphone_text.setText(init_sharpness + "");

    }
}
