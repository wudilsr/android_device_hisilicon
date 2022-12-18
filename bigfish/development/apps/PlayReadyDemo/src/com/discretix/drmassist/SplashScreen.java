package com.discretix.drmassist;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.widget.Button;
import android.view.View;
import android.view.View.OnClickListener;

public class SplashScreen extends Activity implements OnClickListener {
	private Handler mHandler = new Handler();
	private final int mDelay = 3500; //msec
	private final Runnable mLauncher = new DrmAssistLauncher();
	private volatile Boolean isCannseled = false;

    private Button localPlay;
    private Button urlPlay;

	private class DrmAssistLauncher implements Runnable{
		public void run() {
			if (isCannseled) {
				return;
			}
			Intent intent = new Intent(SplashScreen.this, FileNavigatorActivity.class);
			SplashScreen.this.startActivity(intent);
			SplashScreen.this.finish();

		}
	}

	@Override
	public void onBackPressed() {
		isCannseled = true;
		mHandler.removeCallbacks(mLauncher);
		Intent intent = new Intent(SplashScreen.this, FileNavigatorActivity.class);
		SplashScreen.this.startActivity(intent);
		SplashScreen.this.finish();

	}

    public void onClick(View pView)
    {
        switch (pView.getId())
        {
            case R.id.localPlay:
                {
                    Intent intent = new Intent(SplashScreen.this, FileNavigatorActivity.class);
			        SplashScreen.this.startActivity(intent);
			        SplashScreen.this.finish();
                }
                break;

            case R.id.urlPlay:
                {
                    Intent intent = new Intent(SplashScreen.this, WebActivity.class);
			        SplashScreen.this.startActivity(intent);
			        SplashScreen.this.finish();
                }
                break;

            default:
                break;
        }
    }

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		setContentView(R.layout.splashscreen);
		super.onCreate(savedInstanceState);
        localPlay = (Button) findViewById(R.id.localPlay);
        urlPlay = (Button) findViewById(R.id.urlPlay);
        localPlay.setOnClickListener(this);
        urlPlay.setOnClickListener(this);
		//mHandler.postDelayed(mLauncher, mDelay);
	}

}
