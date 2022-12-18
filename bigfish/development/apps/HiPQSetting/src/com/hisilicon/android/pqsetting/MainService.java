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

public class MainService extends Service {

    private static String TAG = "PQSetting";
    private IBinder binder = new MyBinder();

    public static MainDialog cMainDialog;

    public static DisplayDialog cDisplayDialog;

    public static EngineDialog cEngineDialog;

    public static ColorDialog cColorDialog;

    public static AlertDialog mMainDialog;

    public static AlertDialog mDisplayDialog;

    public static AlertDialog mEngineDialog;

    public static AlertDialog mColorDialog;

    private static Handler dHandler = null;

    private static DismissThread dismissThread = null;

    private static boolean isDShow = false;

    public static long startTime = 0;

    public enum PQType {
		DISPLAY, SPDIF,  COLOR, CONTRAST, SUPER, COLOR_ENHANCE
	}

    public static PQType mType = PQType.DISPLAY;

    private static final int FRESH_BUTTON_RIGHT = 1;
    private static final int FRESH_BUTTON_LEFT = 2;
    private static final int mDelayTime = 300;

    private static Handler mhandler = new Handler() {
        public void handleMessage(Message msg) {
			switch (msg.what) {
			case FRESH_BUTTON_LEFT:
				switch (mType) {
				case DISPLAY:
					Common.display_left.setImageResource(R.drawable.left_normal);
					break;
				case SPDIF:
					Common.engine_left.setImageResource(R.drawable.left_normal);
					break;
				case COLOR:
					Common.smart_left.setImageResource(R.drawable.left_normal);
					break;
				case CONTRAST:
					Common.contrast_left.setImageResource(R.drawable.left_normal);
					break;
				case SUPER:
					Common.super_left.setImageResource(R.drawable.left_normal);
					break;
				case COLOR_ENHANCE:
					Common.color_left.setImageResource(R.drawable.left_normal);
					break;
				default:
					break;
				}

			case FRESH_BUTTON_RIGHT:
				switch (mType) {
				case DISPLAY:
					Common.display_right.setImageResource(R.drawable.right_normal);
					break;
				case SPDIF:
					Common.engine_right.setImageResource(R.drawable.right_normal);
					break;
				case COLOR:
					Common.smart_right.setImageResource(R.drawable.right_normal);
					break;
				case CONTRAST:
					Common.contrast_right.setImageResource(R.drawable.right_normal);
					break;
				case SUPER:
					Common.super_right.setImageResource(R.drawable.right_normal);
					break;
				case COLOR_ENHANCE:
					Common.color_right.setImageResource(R.drawable.right_normal);
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
    public void onCreate()
    {
        super.onCreate();
    }

    @Override
    public IBinder onBind(Intent arg0)
    {
        return binder;
    }

    public class MyBinder extends Binder
    {
        public MainService getService()
        {
            return MainService.this;
        }
    }

    @Override
    public void onStart(Intent intent, int startId)
    {
	 super.onStart(intent, startId);
        if (Common.mPQManager == null) {
	    Common.mPQManager = new PQManager();
        }
        if (cMainDialog == null) {
	    cMainDialog = new MainDialog(MainService.this);
        }
        if (cDisplayDialog == null) {
	    cDisplayDialog = new DisplayDialog(MainService.this);
        }
        if (cEngineDialog == null) {
	    cEngineDialog = new EngineDialog(MainService.this);
        }
        if (cColorDialog == null) {
	    cColorDialog = new ColorDialog(MainService.this);
        }
        Common.display_array = getResources().getStringArray(R.array.display_mode_array);
	 Common.onoff_array = getResources().getStringArray(R.array.onoff_array);
        Common.onoff_split_array = getResources().getStringArray(R.array.onoff_split_array);
	 Common.smart_color_array = getResources().getStringArray(R.array.smart_color_array);
	 Common.dynamic_contrast_array = getResources().getStringArray(R.array.dynamic_contrast_array);
        if(mMainDialog != null)
            mMainDialog.dismiss();
        if(mDisplayDialog != null)
            mDisplayDialog.dismiss();
        if(mEngineDialog != null)
            mEngineDialog.dismiss();
        if(mColorDialog != null)
            mColorDialog.dismiss();
        mMainDialog = cMainDialog.showMainDialog();
        dialogAutoDismiss(mMainDialog);
    }

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
				int id = v.getId();
				switch (keyCode) {
				case KeyEvent.KEYCODE_DPAD_LEFT:
					progress--;
					progress = progress < 0 ? 0 : progress;
					break;
				case KeyEvent.KEYCODE_DPAD_RIGHT:
					progress++;
					progress = progress > 100 ? 100 : progress;
					break;
				default:
					break;
				}
				seekBar.setProgress(progress);
				textView.setText(progress + "");
				switch (id) {
				case R.id.brightness_layout:
					Common.mPQManager.setBrightness(progress);
					break;
				case R.id.contrast_layout:
					Common.mPQManager.setContrast(progress);
					break;
				case R.id.chroma_layout:
					Common.mPQManager.setHue(progress);
					break;
				case R.id.saturation_layout:
					Common.mPQManager.setSaturation(progress);
					break;
				case R.id.sharpness_layout:
                                 Log.i(TAG,"setSharpness:"+progress);
					Common.mPQManager.setSharpness(progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_SHARPNESS);
					break;
				case R.id.red_enhance_layout:
					Common.mPQManager.setCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_RED, progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
					break;
				case R.id.blue_enhance_layout:
					Common.mPQManager.setCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_BLUE, progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
					break;
				case R.id.green_enhance_layout:
					Common.mPQManager.setCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_GREEN, progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
					break;
				case R.id.cyan_enhance_layout:
					Common.mPQManager.setCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_CYAN, progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
					break;
				case R.id.violet_enhance_layout:
					Common.mPQManager.setCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_MAGENTA, progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
					break;
				case R.id.yellow_enhance_layout:
					Common.mPQManager.setCustomizeColor(PQManager.HI_PQ_BASE_COLOR_TYPE_YELLOW, progress);
					Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
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
				case R.id.display_layout:
					mType = PQType.DISPLAY;
					break;
				case R.id.engine_layout:
					mType = PQType.SPDIF;
					break;
				case R.id.smart_color_layout:
					mType = PQType.COLOR;
					break;
				case R.id.dynamic_contrast_layout:
					mType = PQType.CONTRAST;
					break;
				case R.id.super_resolution_layout:
					mType = PQType.SUPER;
					break;
				case R.id.color_layout:
					mType = PQType.COLOR_ENHANCE;
					break;
				}
				RefreshText(mType, keyCode);
			}
			if (keyCode == KeyEvent.KEYCODE_DPAD_DOWN) {
				switch (id) {
				case R.id.display_layout:
					if (Common.mPQManager.getImageMode() != 4)
						return true;
					break;
                           case R.id.color_layout:
					if (Common.mPQManager.getColorEnhanceMode() != 5)
						return true;
					break;
				}
			}
			return false;
		}
	}

	private static void RefreshText(PQType type, int keycode) {
		int mCurMode = -1;
		switch (keycode) {
		case KeyEvent.KEYCODE_DPAD_LEFT: {
			switch (type) {
			case DISPLAY:
				Common.display_left.setImageResource(R.drawable.left_focused);
				mCurMode = Common.mPQManager.getImageMode();
				mCurMode--;
				mCurMode = mCurMode < 0 ? 4 : mCurMode;
				Common.mPQManager.setImageMode(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_IMAGE);
				cDisplayDialog.RefreshDisplay();
				break;
			case SPDIF:
				Common.engine_left.setImageResource(R.drawable.left_focused);
				mCurMode = Common.mPQManager.getShopMode();
				mCurMode--;
				mCurMode = mCurMode < 0 ? 2 : mCurMode;
				Common.engine_text.setText(Common.onoff_split_array[mCurMode]);
				Common.mPQManager.setShopMode(mCurMode);
                Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_SHOPMODE);
				break;
			case COLOR:
				Common.smart_left.setImageResource(R.drawable.left_focused);
				mCurMode = Common.mPQManager.getColorEnhanceMode();
				mCurMode--;
				mCurMode = mCurMode < 0 ? 5 : mCurMode;
				Common.smart_color_text.setText(Common.smart_color_array[mCurMode]);
				Common.mPQManager.setColorEnhanceMode(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
				break;
			case CONTRAST:
				Common.contrast_left.setImageResource(R.drawable.left_focused);
				mCurMode = Common.mPQManager.getDynamicContrast();
				mCurMode--;
				mCurMode = mCurMode < 0 ? 3 : mCurMode;
				Common.dynamic_contrast_text.setText(Common.dynamic_contrast_array[mCurMode]);
				Common.mPQManager.setDynamicContrast(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_DYNCCONTRAST);
				break;
			case SUPER:
				Common.super_left.setImageResource(R.drawable.left_focused);
				mCurMode = Common.mPQManager.getSuperResolution();
				mCurMode--;
				mCurMode = mCurMode < 0 ? 1 : mCurMode;
				Common.super_resolution_text.setText(Common.onoff_array[mCurMode]);
				Common.mPQManager.setSuperResolution(mCurMode);
                Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_SUPERRESOLUTION);
				break;
			case COLOR_ENHANCE:
				Common.color_left.setImageResource(R.drawable.left_focused);
				mCurMode = Common.mPQManager.getColorEnhanceMode();
				mCurMode--;
				mCurMode = mCurMode < 0 ? 5 : mCurMode;
				Common.color_text.setText(Common.smart_color_array[mCurMode]);
				Common.mPQManager.setColorEnhanceMode(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
				cColorDialog.RefreshColor();
				break;
			}
			mhandler.removeMessages(FRESH_BUTTON_LEFT);
			mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_LEFT, mDelayTime);
			break;
		}
		case KeyEvent.KEYCODE_DPAD_RIGHT:
			switch (type) {
			case DISPLAY:
				Common.display_right.setImageResource(R.drawable.right_focused);
				mCurMode = Common.mPQManager.getImageMode();
				mCurMode++;
				mCurMode = mCurMode > 4 ? 0 : mCurMode;
				Common.display_text.setText(Common.display_array[mCurMode]);
				Common.mPQManager.setImageMode(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_IMAGE);
				cDisplayDialog.RefreshDisplay();
				break;
			case SPDIF:
				Common.engine_right.setImageResource(R.drawable.right_focused);
				mCurMode = Common.mPQManager.getShopMode();
				mCurMode++;
				mCurMode = mCurMode > 2 ? 0 : mCurMode;
				Common.engine_text.setText(Common.onoff_split_array[mCurMode]);
				Common.mPQManager.setShopMode(mCurMode);
                Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_SHOPMODE);
				break;
			case COLOR:
				Common.smart_right.setImageResource(R.drawable.right_focused);
				mCurMode = Common.mPQManager.getColorEnhanceMode();
				mCurMode++;
				mCurMode = mCurMode > 5 ? 0 : mCurMode;
				Common.smart_color_text.setText(Common.smart_color_array[mCurMode]);
				Common.mPQManager.setColorEnhanceMode(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
				break;
			case CONTRAST:
				Common.contrast_right.setImageResource(R.drawable.right_focused);
				mCurMode = Common.mPQManager.getDynamicContrast();
				mCurMode++;
				mCurMode = mCurMode > 3 ? 0 : mCurMode;
				Common.dynamic_contrast_text.setText(Common.dynamic_contrast_array[mCurMode]);
				Common.mPQManager.setDynamicContrast(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_DYNCCONTRAST);
				break;
			case SUPER:
				Common.super_right.setImageResource(R.drawable.right_focused);
				mCurMode = Common.mPQManager.getSuperResolution();
				mCurMode++;
				mCurMode = mCurMode > 1 ? 0 : mCurMode;
				Common.super_resolution_text.setText(Common.onoff_array[mCurMode]);
				Common.mPQManager.setSuperResolution(mCurMode);
                Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_SUPERRESOLUTION);
				break;
			case COLOR_ENHANCE:
				Common.color_right.setImageResource(R.drawable.right_focused);
				mCurMode = Common.mPQManager.getColorEnhanceMode();
				mCurMode++;
				mCurMode = mCurMode > 5 ? 0 : mCurMode;
				Common.color_text.setText(Common.smart_color_array[mCurMode]);
				Common.mPQManager.setColorEnhanceMode(mCurMode);
				Common.mPQManager.saveParam(PQManager.HI_PQ_SAVE_TYPE_COLOR);
				cColorDialog.RefreshColor();
				break;
			}
			mhandler.removeMessages(FRESH_BUTTON_RIGHT);
			mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_RIGHT, mDelayTime);
			break;
		}
	}

       public static void dialogAutoDismiss(Dialog dialog)
       {
            if(!isDShow)
            {
                dHandler = new Handler();
                dismissThread = new DismissThread(dialog);
                startTime = System.currentTimeMillis();
                dHandler.post(dismissThread);
                isDShow = true;
            }
            else
            {
                if(dismissThread != null)
                    dismissThread.SetDialog(dialog);
                startTime = System.currentTimeMillis();
            }
       }
       private static class DismissThread  implements Runnable
       {
            Dialog dialog = null;

            public DismissThread(Dialog dialog)
            {
                this.dialog = dialog;
            }

            public void SetDialog(Dialog dialog)
            {
                this.dialog = dialog;
            }
            public void run()
            {
                long endTime  = System.currentTimeMillis();
                long distance = endTime - startTime;

                if (distance >= 10 * 1000)
                {
                    if(dialog != null)
                        dialog.dismiss();

                    dHandler.removeCallbacks(dismissThread);
                    isDShow = false;
                }
                else
                {
                    dHandler.postDelayed(this, 1000);
                }
            }
        }
}
