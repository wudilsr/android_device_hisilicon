package com.hisilicon.android.pqsetting;

import java.util.HashMap;
import java.util.Map;
import java.util.ArrayList;

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

import com.hisilicon.android.PQManager;

public class DisplayDialog {

    private Context mContext;

    public DisplayDialog(Context m)
    {
        mContext = m;
    }

    public AlertDialog showDisplayDialog() {
        //create ui

        //use custom UI.
        View v = View.inflate(mContext, R.layout.display_set, null);
        initDisplayView(v);

        AlertDialog.Builder builder = new AlertDialog.Builder(mContext,R.style.MyTranslucent);
        builder.setTitle(mContext.getString(R.string.display_mode));
        builder.setView(v,0,0,0,0);
        AlertDialog dialog = builder.create();
        dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_ALERT);
        //dialog.getWindow().setType(WindowManager.LayoutParams.TYPE_SYSTEM_OVERLAY);
        dialog.show();

        //set dialog size and position.
        WindowManager.LayoutParams lp=dialog.getWindow().getAttributes();
        WindowManager wm=(WindowManager) mContext.getSystemService(mContext.WINDOW_SERVICE);
        Display display = wm.getDefaultDisplay();
        if (Common.isPortrait()) {
            lp.width=(int) (display.getHeight()*0.35);
            lp.height=(int) (display.getWidth()*0.55);
            lp.x=(int) (600 * display.getWidth() / display.getHeight());
            lp.y=(int) (-400 * display.getHeight() / display.getWidth());
        } else {
            lp.width=(int) (display.getWidth()*0.35);
            lp.height=(int) (display.getHeight()*0.55);
            lp.x=600;
            lp.y=-400;
        }
        lp.alpha = 0.7f;
        dialog.getWindow().setAttributes(lp);
        return dialog;
    }

    private void initDisplayView(View v) {
        Common.display_layout = (RelativeLayout) v.findViewById(R.id.display_layout);
        Common.display_text = (TextView) v.findViewById(R.id.display_info);
        Common.display_layout.setOnKeyListener(new MainService.LayoutListener());
        Common.display_layout.requestFocus();

        Common.brightness_layout = (RelativeLayout) v.findViewById(R.id.brightness_layout);
        Common.brightness_seekbar = (SeekBar) v.findViewById(R.id.brightness_seekbar);
        Common.brightness_text = (TextView) v.findViewById(R.id.brightness_text);
        Common.brightness_info= (TextView) v.findViewById(R.id.brightness_info);
        Common.brightness_layout.setOnKeyListener(new MainService.SeekBarListener(Common.brightness_seekbar, Common.brightness_info));

        Common.contrast_layout = (RelativeLayout) v.findViewById(R.id.contrast_layout);
        Common.contrast_seekbar = (SeekBar) v.findViewById(R.id.contrast_seekbar);
        Common.contrast_text = (TextView) v.findViewById(R.id.contrast_text);
        Common.contrast_info = (TextView) v.findViewById(R.id.contrast_info);
        Common.contrast_layout.setOnKeyListener(new MainService.SeekBarListener(Common.contrast_seekbar,Common.contrast_info));

        Common.hue_layout = (RelativeLayout) v.findViewById(R.id.chroma_layout);
        Common.hue_seekbar = (SeekBar) v.findViewById(R.id.chroma_seekbar);
        Common.hue_text = (TextView) v.findViewById(R.id.chroma_text);
        Common.hue_info = (TextView) v.findViewById(R.id.chroma_info);
        Common.hue_layout.setOnKeyListener(new MainService.SeekBarListener(Common.hue_seekbar, Common.hue_info));

        Common.saturation_layout = (RelativeLayout) v.findViewById(R.id.saturation_layout);
        Common.saturation_seekbar = (SeekBar) v.findViewById(R.id.saturation_seekbar);
        Common.saturation_text = (TextView) v.findViewById(R.id.saturation_text);
        Common.saturation_info = (TextView) v.findViewById(R.id.saturation_info);
        Common.saturation_layout.setOnKeyListener(new MainService.SeekBarListener(Common.saturation_seekbar, Common.saturation_info));
        Common.display_left = (ImageView) v.findViewById(R.id.display_left);
        Common.display_right = (ImageView) v.findViewById(R.id.display_right);
        RefreshDisplay();
    }

    public void RefreshDisplay() {
        int init_image_mode = Common.mPQManager.getImageMode();
        init_image_mode = init_image_mode == -1 ? 0 : init_image_mode;
        Common.display_text.setText(Common.display_array[init_image_mode]);

        int init_brightness = Common.mPQManager.getBrightness();
        if (init_brightness < 0 || init_brightness > 100) {
			init_brightness = 50;
        }
        Common.brightness_seekbar.setProgress(init_brightness);
        Common.brightness_info.setText(init_brightness + "");

        int init_hue = Common.mPQManager.getHue();
        if (init_hue < 0 || init_hue > 100) {
			init_hue = 50;
        }
        Common.hue_seekbar.setProgress(init_hue);
        Common.hue_info.setText(init_hue + "");

        int init_contrast = Common.mPQManager.getContrast();
        if (init_contrast < 0 || init_contrast > 100) {
			init_contrast = 50;
        }
        Common.contrast_seekbar.setProgress(init_contrast);
        Common.contrast_info.setText(init_contrast + "");

        int init_saturation = Common.mPQManager.getSaturation();
        if (init_saturation < 0 || init_saturation > 100) {
			init_saturation = 50;
        }
        Common.saturation_seekbar.setProgress(init_saturation);
        Common.saturation_info.setText(init_saturation + "");

         if(init_image_mode !=4)
         {
            Common.brightness_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.brightness_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.hue_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.hue_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.contrast_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.contrast_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.saturation_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.saturation_layout.setBackgroundResource(R.drawable.input_disable_wide);
         }
         else
         {
            Common.brightness_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.brightness_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.hue_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.hue_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.contrast_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.contrast_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.saturation_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.saturation_layout.setBackgroundResource(R.drawable.input_wide_selector);
         }
    }
}
