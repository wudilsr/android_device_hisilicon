package com.hisilicon.android.fastboot;

import android.annotation.TargetApi;
import android.app.Activity;
import android.app.ProgressDialog;
import android.os.Build;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.StrictMode;
import android.os.SystemProperties;
import android.view.MotionEvent;
import android.view.View;
import android.widget.Button;
import android.widget.Toast;
import android.widget.EditText;
import android.widget.TextView;
import android.util.Log;
import android.content.Context;

import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileWriter;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.ByteArrayInputStream;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.text.SimpleDateFormat;
import java.util.Date;

import android.app.QbAndroidManager;

/**
 * An example full-screen activity that shows and hides the system UI (i.e.
 * status bar and navigation/system bar) with user interaction.
 *
 * @see SystemUiHider
 */
public class FullscreenActivity extends Activity {
	/**
	 * Whether or not the system UI should be auto-hidden after
	 * {@link #AUTO_HIDE_DELAY_MILLIS} milliseconds.
	 */
	private static final boolean AUTO_HIDE = true;

	/**
	 * If {@link #AUTO_HIDE} is set, the number of milliseconds to wait after
	 * user interaction before hiding the system UI.
	 */
	private static final int AUTO_HIDE_DELAY_MILLIS = 1000;

	/**
	 * If set, will toggle the system UI visibility upon interaction. Otherwise,
	 * will show the system UI visibility upon interaction.
	 */
	private static final boolean TOGGLE_ON_CLICK = true;

	/**
	 * The flags to pass to {@link SystemUiHider#getInstance}.
	 */
	/**
	 * The instance of the {@link SystemUiHider} for this activity.
	 */

	public static final String TAG = "HiFastboot";

	private Button openQb = null;

	private Button closeQb = null;

       private TextView mTextView = null;

	private EditText editTitleView = null;

	private EditText editContentView = null;

	private static ProgressDialog progressBar = null;

	private qbThread mThread = null;

	private String LogFile = null;

	private String ProcInfoFile = null;

	private String registerInfoFile = null;

	private String CacheDir = null;

	private File tmp = null;

	private String curDateStr;

	private QbAndroidManager mQbAndroidManager;

       private boolean mQbFlag;

	final Handler mHandler = new Handler() {
		public void handleMessage(Message msg) {
			switch (msg.what) {
				case 0:
					{
						String path = (String)msg.obj;
						Context mContext = FullscreenActivity.this;
						progressBar = new ProgressDialog(mContext);
						progressBar.setTitle(mContext.getString(R.string.app_name));
						progressBar.setMessage(mContext.getString(R.string.collect));
						progressBar.setCancelable(true);
						progressBar.show();
						mThread = new qbThread(true);
						mThread.start();
						break;
					}
				case 1:
					{
						progressBar.dismiss();
						break;
					}
				case 2:
					{
						String path = (String)msg.obj;
						Context mContext = FullscreenActivity.this;
						progressBar = new ProgressDialog(mContext);
						progressBar.setTitle(mContext.getString(R.string.app_name));
						progressBar.setMessage(mContext.getString(R.string.collect));
						progressBar.setCancelable(true);
						progressBar.show();
						mThread = new qbThread(false);
						mThread.start();
						break;
					}
			}
		}
	};
	@Override
		protected void onCreate(Bundle savedInstanceState) {
			super.onCreate(savedInstanceState);

			setContentView(R.layout.activity_fullscreen);

			//final View controlsView = findViewById(R.id.fullscreen_content_controls);
			final View contentView = findViewById(R.id.fullscreen_content);

			openQb = (Button) findViewById(R.id.openButton);

			closeQb = (Button) findViewById(R.id.closeButton);

                    mTextView = (TextView) findViewById(R.id.textView);
			// Set up the user interaction to manually show or hide the system UI.
			contentView.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View view) {
					}
					});

			openQb.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View view) {
					Log.i(TAG,"openQb");
					Message msg = mHandler.obtainMessage(0);
					mHandler.sendMessage(msg);
					}
					});
			openQb.setEnabled(true);
			openQb.requestFocus();

			closeQb.setOnClickListener(new View.OnClickListener() {
					@Override
					public void onClick(View view) {
					Log.i(TAG,"closeQb");
					Message msg = mHandler.obtainMessage(2);
					mHandler.sendMessage(msg);
					}
					});

			CacheDir = getCacheDir().getPath() + "/";

                    mQbFlag  = SystemProperties.get("persist.sys.qb.enable","false").equals("true");
                    if(mQbFlag)
                    {
                        mTextView.setText(getResources().getString(R.string.current)+" "+getResources().getString(R.string.open));
                    }
                    else
                    {
                        mTextView.setText(getResources().getString(R.string.current)+" "+getResources().getString(R.string.close));
                    }
		}

	@Override
		protected void onPostCreate(Bundle savedInstanceState) {
			super.onPostCreate(savedInstanceState);

			// Trigger the initial hide() shortly after the activity has been
			// created, to briefly hint to the user that UI controls
			// are available.
			delayedHide(100);
		}

	//final View controlsView = findViewById(R.id.fullscreen_content_controls);
	/**
	 * Touch listener to use for in-layout UI controls to delay hiding the
	 * system UI. This is to prevent the jarring behavior of controls going away
	 * while interacting with activity UI.
	 */
	View.OnTouchListener mDelayHideTouchListener = new View.OnTouchListener() {
		@Override
			public boolean onTouch(View view, MotionEvent motionEvent) {
				if (AUTO_HIDE) {
					delayedHide(AUTO_HIDE_DELAY_MILLIS);
				}
				return false;
			}
	};

	Handler mHideHandler = new Handler();
	Runnable mHideRunnable = new Runnable() {
		@Override
			public void run() {
				//mSystemUiHider.hide();
			}
	};

	/**
	 * Schedules a call to hide() in [delay] milliseconds, canceling any
	 * previously scheduled calls.
	 */
	private void delayedHide(int delayMillis) {
		mHideHandler.removeCallbacks(mHideRunnable);
		mHideHandler.postDelayed(mHideRunnable, delayMillis);
	}

	private class qbThread extends Thread
	{
		private boolean flag = false;

		qbThread(boolean mFlag)
		{
			flag = mFlag;
		}
		public void run()
		{
		      getQbAndroidManager();
			if(flag)
			{
			       mQbAndroidManager.setQbEnable (true);
			}
			else
			{
				mQbAndroidManager.setQbEnable (false);
			}
			Message msg = mHandler.obtainMessage(1);
			mHandler.sendMessage(msg);
		}
	}

	private QbAndroidManager getQbAndroidManager()
	{
		if (mQbAndroidManager == null)
		{
			mQbAndroidManager=(QbAndroidManager)FullscreenActivity.this.getSystemService(Context.QB_ANDROID_MANAGER_SERVICE);
			if (mQbAndroidManager == null)
			{
				Log.e("Qb", "mQbAndroidManager is Null.");
			}
		}
		return mQbAndroidManager;
	}

}
