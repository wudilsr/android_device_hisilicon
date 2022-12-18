package com.hisilicon.android.HiSuspendMode;

import android.os.Bundle;
import android.os.SystemProperties;
import android.app.Activity;
import android.view.Menu;
import android.widget.RadioButton;
import android.widget.RadioGroup;
import android.widget.RadioGroup.OnCheckedChangeListener;

public class HiSuspendMode extends Activity {

	RadioGroup suspend_mode;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_hi_suspend_mode);

		suspend_mode = (RadioGroup)findViewById(R.id.suspend_mode);
        String supendType = SystemProperties.get("service.suspend.type", "0");
        if (supendType.equals("0")) {
            suspend_mode.check(R.id.deep_suspend);
        } else {
            suspend_mode.check(R.id.smart_suspend);
        }
		suspend_mode.setOnCheckedChangeListener(listener);
	}

	OnCheckedChangeListener listener = new OnCheckedChangeListener() {

		@Override
		public void onCheckedChanged(RadioGroup group, int checkedId) {
			// TODO Auto-generated method stub
			if (checkedId == R.id.deep_suspend) {
				SystemProperties.set("service.suspend.type", "0");
			} else {
				SystemProperties.set("service.suspend.type", "1");
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
