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

public class EngineDialog {

    private Context mContext;

    public EngineDialog(Context m)
    {
        mContext = m;
    }

    public AlertDialog showEngineDialog() {
        //create ui

        //use custom UI.
        View v = View.inflate(mContext, R.layout.engine_set, null);
        initEngineView(v);

        AlertDialog.Builder builder = new AlertDialog.Builder(mContext,R.style.MyTranslucent);
        builder.setTitle(mContext.getString(R.string.engine_mode));
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

    private void initEngineView(View v) {
        Common.engine_layout = (RelativeLayout) v.findViewById(R.id.engine_layout);
        Common.engine_text = (TextView) v.findViewById(R.id.engine_info);
        Common.engine_layout.setOnKeyListener(new MainService.LayoutListener());
        Common.engine_layout.requestFocus();

        Common.smart_color_layout = (RelativeLayout) v.findViewById(R.id.smart_color_layout);
        Common.smart_color_text = (TextView) v.findViewById(R.id.smart_color_info);
        Common.smart_color_layout.setOnKeyListener(new MainService.LayoutListener());
        Common.smart_color_layout.setOnClickListener(new OnClickListener()
			{
			@Override
			public void onClick(View v) {
				MainService.mEngineDialog.dismiss();
				MainService.mColorDialog = MainService.cColorDialog.showColorDialog();
                           MainService.dialogAutoDismiss(MainService.mColorDialog);
				MainService.mColorDialog.setOnCancelListener(new OnCancelListener()
				{
					public void onCancel(DialogInterface dialog)
					{
						MainService.mEngineDialog = showEngineDialog();
						MainService.mEngineDialog.setOnCancelListener(new OnCancelListener()
						{
							public void onCancel(DialogInterface dialog)
							{
								MainService.mMainDialog = MainService.cMainDialog.showMainDialog();
                                                     MainService.dialogAutoDismiss(MainService.mMainDialog);
							}
						});
					}
				});
			}
		});

        Common.dynamic_contrast_layout = (RelativeLayout) v.findViewById(R.id.dynamic_contrast_layout);
        Common.dynamic_contrast_text = (TextView) v.findViewById(R.id.dynamic_contrast_info);
        Common.dynamic_contrast_layout.setOnKeyListener(new MainService.LayoutListener());

        Common.sharpness_layout = (RelativeLayout) v.findViewById(R.id.sharpness_layout);
        Common.sharpness_seekbar = (SeekBar) v.findViewById(R.id.sharpness_seekbar);
        Common.sharpness_text = (TextView) v.findViewById(R.id.sharpness_info);
        Common.sharpness_layout.setOnKeyListener(new MainService.SeekBarListener(Common.sharpness_seekbar, Common.sharpness_text));

        Common.super_resolution_layout = (RelativeLayout) v.findViewById(R.id.super_resolution_layout);
        Common.super_resolution_text = (TextView) v.findViewById(R.id.super_resolution_info);
        Common.super_resolution_layout.setOnKeyListener(new MainService.LayoutListener());

        Common.engine_left = (ImageView) v.findViewById(R.id.engine_left);
        Common.engine_right = (ImageView) v.findViewById(R.id.engine_right);
        Common.smart_left = (ImageView) v.findViewById(R.id.smart_color_left);
        Common.smart_right = (ImageView) v.findViewById(R.id.smart_color_right);
        Common.contrast_left = (ImageView) v.findViewById(R.id.dynamic_contrast_left);
        Common.contrast_right = (ImageView) v.findViewById(R.id.dynamic_contrast_right);
        Common.super_left = (ImageView) v.findViewById(R.id.super_resolution_left);
        Common.super_right = (ImageView) v.findViewById(R.id.super_resolution_right);
        RefreshEngineView();
    }

    public void RefreshEngineView() {
	int init_engine = Common.mPQManager.getShopMode();
	init_engine = init_engine == -1 ? 0 : init_engine;
	Common.engine_text.setText(Common.onoff_split_array[init_engine]);

	int init_smart_color = Common.mPQManager.getColorEnhanceMode();
	init_smart_color = init_smart_color == -1 ? 0 : init_smart_color;
	Common.smart_color_text.setText(Common.smart_color_array[init_smart_color]);

	int init_contrast = Common.mPQManager.getDynamicContrast();
	init_contrast = init_contrast == -1 ? 0 : init_contrast;
	Common.dynamic_contrast_text.setText(Common.dynamic_contrast_array[init_contrast]);

	int init_sharpness = Common.mPQManager.getSharpness();
	if (init_sharpness < 0 || init_sharpness > 100) {
		init_sharpness = 50;
	}
	Common.sharpness_seekbar.setProgress(init_sharpness);
	Common.sharpness_text.setText(init_sharpness + "");

	int init_super = Common.mPQManager.getSuperResolution();
	init_super = init_super == -1 ? 0 : init_super;
	Common.super_resolution_text.setText(Common.onoff_array[init_super]);
    }
}
