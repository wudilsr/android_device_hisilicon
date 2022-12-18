package com.hisilicon.multiscreen.mybox;

import android.app.Activity;
import android.content.Context;
import android.content.pm.PackageInfo;
import android.content.pm.PackageManager;
import android.content.pm.PackageManager.NameNotFoundException;
import android.os.Bundle;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;
import android.widget.TextView;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

public class AboutActivity extends Activity implements OnClickListener {
	
	/**
	 * Context of this.
	 */
	private Context mContext = null;

	/**
	 * CN:返回按钮。
	 */
	private Button mTitle_logo_img;

	/**
	 * CN:关于。
	 */
	private TextView mTitle_user_txt;

	/**
	 * CN:版本号。
	 */
	private TextView mMybox_about_version;

	@Override
	public void onCreate(Bundle savedInstanceState) {
		LogTool.v("onCreate.");
		super.onCreate(savedInstanceState);

		initView();
	}

	public void onBackPressed() {
		LogTool.v("onBackPressed.");
		super.onBackPressed();
	}

	/**
	 * Init view of activity.
	 */
	private void initView() {
		LogTool.d("initView");

		setContentView(R.layout.mybox_about);
		mContext = this;
		mTitle_logo_img = (Button) findViewById(R.id.title_logo_img);
		mTitle_logo_img.setOnClickListener(this);

		mTitle_user_txt = (TextView) findViewById(R.id.title_user_txt);
		mTitle_user_txt.setText(mContext.getResources().getString(R.string.about_info));

		mMybox_about_version = (TextView) findViewById(R.id.mybox_about_version);
		mMybox_about_version.setText(getVersionName());

	}

	public void onDestory() {
		super.onDestroy();
	}

	/**
	 * CN:控件监听者。
	 */
	@Override
	public void onClick(View v) {
		// TODO Auto-generated method stub

		switch (v.getId()) {
		case R.id.title_logo_img:
			finish();
			break;

		default:
			break;
		}

	}
	
	/**
	 * CN:处理按键事件。
	 */
	@Override
	public boolean onKeyDown(int keyCode, KeyEvent event) {
		// TODO Auto-generated method stub

		if (keyCode == KeyEvent.KEYCODE_BACK|| keyCode == KeyEvent.KEYCODE_HOME) {
			finish();
		}
		return super.onKeyDown(keyCode, event);
	}
	
	/**
	 * 
	 * CN:获取应用的 version name。
	 */
	private String getVersionName() {

		String appVersion = null;
		PackageManager manager = this.getPackageManager();
		try {
			PackageInfo info = manager.getPackageInfo(this.getPackageName(), 0);
			appVersion = info.versionName;
		} catch (NameNotFoundException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		return appVersion;
	}

}
