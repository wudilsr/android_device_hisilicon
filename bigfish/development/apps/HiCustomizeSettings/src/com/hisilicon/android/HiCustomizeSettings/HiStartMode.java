package com.hisilicon.android.HiCustomizeSettings;

import com.hisilicon.android.HiSettingsDemo.R;

import android.os.Bundle;
import android.os.SystemProperties;
import android.app.Activity;
import android.util.Log;
import android.view.Menu;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;

public class HiStartMode extends Activity {

	RadioGroup start_mode;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_hi_start_mode);

		start_mode = (RadioGroup) findViewById(R.id.start_mode);
		String supendType = FlashInfo.getFlashInfo(0x100000, 4);
		Log.i("current start mode is :", supendType);
		if (supendType.equals("161")) {
			start_mode.check(R.id.quick_start);
		} else {
			start_mode.check(R.id.normal_start);
		}
		start_mode.setOnCheckedChangeListener(listener);
	}

	OnCheckedChangeListener listener = new OnCheckedChangeListener() {

		@Override
		public void onCheckedChanged(RadioGroup group, int checkedId) {
			// TODO Auto-generated method stub
			if (checkedId == R.id.normal_start) {
				FlashInfo.setFlashInfo(0x100000, 4, 0xa0);
			} else {
				FlashInfo.setFlashInfo(0x100000, 4, 0xa1);
			}
		}
	};

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.hi_suspend_mode, menu);
		return true;
	}

}
