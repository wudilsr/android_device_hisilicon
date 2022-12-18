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

public class ColorDialog {

    private Context mContext;

    private AlertDialog mMainDialog;

    public ColorDialog(Context m)
    {
        mContext = m;
    }

    public AlertDialog showColorDialog() {
        //create ui

        //use custom UI.
        View v = View.inflate(mContext, R.layout.color_set, null);
        initColorView(v);

        AlertDialog.Builder builder = new AlertDialog.Builder(mContext,R.style.MyTranslucent);
        builder.setTitle(mContext.getString(R.string.intelligent_color));
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
            lp.height=(int) (display.getWidth()*0.85);
            lp.x=(int) (600 * display.getWidth() / display.getHeight());
            lp.y=(int) (-400 * display.getHeight() / display.getWidth());
        } else {
            lp.width=(int) (display.getWidth()*0.35);
            lp.height=(int) (display.getHeight()*0.85);
            lp.x=600;
            lp.y=-400;
        }
        lp.alpha = 0.7f;
        dialog.getWindow().setAttributes(lp);
        return dialog;
    }

    private void initColorView(View v) {
		Common.color_layout = (RelativeLayout) v.findViewById(R.id.color_layout);
		Common.color_text = (TextView) v.findViewById(R.id.color_info);
		Common.color_layout.setOnKeyListener(new MainService.LayoutListener());
		Common.color_layout.requestFocus();

        Common.red_layout = (RelativeLayout) v.findViewById(R.id.red_enhance_layout);
        Common.red_seekbar = (SeekBar) v.findViewById(R.id.red_enhance_seekbar);
        Common.red_text = (TextView) v.findViewById(R.id.red_enhance_text);
        Common.red_info = (TextView) v.findViewById(R.id.red_enhance_info);
        Common.red_layout.setOnKeyListener(new MainService.SeekBarListener(Common.red_seekbar, Common.red_info));

        Common.green_layout = (RelativeLayout) v.findViewById(R.id.green_enhance_layout);
        Common.green_seekbar = (SeekBar) v.findViewById(R.id.green_enhance_seekbar);
        Common.green_text = (TextView) v.findViewById(R.id.green_enhance_text);
        Common.green_info = (TextView) v.findViewById(R.id.green_enhance_info);
        Common.green_layout.setOnKeyListener(new MainService.SeekBarListener(Common.green_seekbar,Common.green_info));

        Common.blue_layout = (RelativeLayout) v.findViewById(R.id.blue_enhance_layout);
        Common.blue_seekbar = (SeekBar) v.findViewById(R.id.blue_enhance_seekbar);
        Common.blue_text = (TextView) v.findViewById(R.id.blue_enhance_text);
        Common.blue_info = (TextView) v.findViewById(R.id.blue_enhance_info);
        Common.blue_layout.setOnKeyListener(new MainService.SeekBarListener(Common.blue_seekbar,Common.blue_info));

        Common.cyan_layout = (RelativeLayout) v.findViewById(R.id.cyan_enhance_layout);
        Common.cyan_seekbar = (SeekBar) v.findViewById(R.id.cyan_enhance_seekbar);
        Common.cyan_text = (TextView) v.findViewById(R.id.cyan_enhance_text);
        Common.cyan_info = (TextView) v.findViewById(R.id.cyan_enhance_info);
        Common.cyan_layout.setOnKeyListener(new MainService.SeekBarListener(Common.cyan_seekbar,Common.cyan_info));

        Common.violet_layout = (RelativeLayout) v.findViewById(R.id.violet_enhance_layout);
        Common.violet_seekbar = (SeekBar) v.findViewById(R.id.violet_enhance_seekbar);
        Common.violet_text = (TextView) v.findViewById(R.id.violet_enhance_text);
        Common.violet_info = (TextView) v.findViewById(R.id.violet_enhance_info);
        Common.violet_layout.setOnKeyListener(new MainService.SeekBarListener(Common.violet_seekbar,Common.violet_info));

        Common.yellow_layout = (RelativeLayout) v.findViewById(R.id.yellow_enhance_layout);
        Common.yellow_seekbar = (SeekBar) v.findViewById(R.id.yellow_enhance_seekbar);
        Common.yellow_text = (TextView) v.findViewById(R.id.yellow_enhance_text);
        Common.yellow_info = (TextView) v.findViewById(R.id.yellow_enhance_info);
        Common.yellow_layout.setOnKeyListener(new MainService.SeekBarListener(Common.yellow_seekbar,Common.yellow_info));
        Common.color_left = (ImageView) v.findViewById(R.id.color_left);
        Common.color_right = (ImageView) v.findViewById(R.id.color_right);
        RefreshColor();
    }

    public void RefreshColor() {
        int init_color = Common.mPQManager.getColorEnhanceMode();
        init_color = init_color == -1 ? 0 : init_color;
        Common.color_text.setText(Common.smart_color_array[init_color]);

        int init_red = Common.mPQManager.getCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_RED);
        if (init_red < 0 || init_red > 100) {
			init_red = 50;
		}
        Common.red_seekbar.setProgress(init_red);
        Common.red_info.setText(init_red + "");

        int init_blue = Common.mPQManager.getCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_BLUE);
        if (init_blue < 0 || init_blue > 100) {
			init_blue = 50;
        }
        Common.blue_seekbar.setProgress(init_blue);
        Common.blue_info.setText(init_blue + "");

        int init_green = Common.mPQManager.getCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_GREEN);
        if (init_green < 0 || init_green > 100) {
			init_green = 50;
        }
        Common.green_seekbar.setProgress(init_green);
        Common.green_info.setText(init_green + "");

        int init_cyan = Common.mPQManager.getCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_CYAN);
        if (init_cyan < 0 || init_cyan > 100) {
			init_cyan = 50;
        }
        Common.cyan_seekbar.setProgress(init_cyan);
        Common.cyan_info.setText(init_cyan + "");

        int init_violet = Common.mPQManager.getCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_MAGENTA);
        if (init_violet < 0 || init_violet > 100) {
			init_violet = 50;
        }
        Common.violet_seekbar.setProgress(init_violet);
        Common.violet_info.setText(init_violet + "");

        int init_yellow = Common.mPQManager.getCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_YELLOW);
        if (init_yellow < 0 || init_yellow > 100) {
			init_yellow = 50;
        }
        Common.yellow_seekbar.setProgress(init_yellow);
        Common.yellow_info.setText(init_yellow + "");

         if(init_color !=5)
         {
            Common.red_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.red_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.blue_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.blue_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.green_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.green_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.cyan_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.cyan_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.violet_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.violet_layout.setBackgroundResource(R.drawable.input_disable_wide);
            Common.yellow_text.setTypeface(Typeface.MONOSPACE,Typeface.ITALIC);
            Common.yellow_layout.setBackgroundResource(R.drawable.input_disable_wide);
         }
         else
         {
            Common.red_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.red_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.blue_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.blue_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.green_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.green_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.cyan_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.cyan_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.violet_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.violet_layout.setBackgroundResource(R.drawable.input_wide_selector);
            Common.yellow_text.setTypeface(Typeface.DEFAULT,Typeface.NORMAL);
            Common.yellow_layout.setBackgroundResource(R.drawable.input_wide_selector);
         }
    }
}
