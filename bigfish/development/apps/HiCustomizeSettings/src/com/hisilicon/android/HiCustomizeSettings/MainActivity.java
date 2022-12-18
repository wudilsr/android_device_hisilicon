package com.hisilicon.android.HiCustomizeSettings;

import com.hisilicon.android.HiSettingsDemo.R;

import android.app.Activity;
import android.content.Intent;
import android.os.Bundle;
import android.view.Menu;
import android.view.View;
import android.view.View.OnClickListener;
import android.widget.Button;

public class MainActivity extends Activity implements OnClickListener {
	private Button button1;
	private Button button2;
	private Button button3;

	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		setContentView(R.layout.activity_main);
		init();
	}

	private void init() {
		button1 = (Button) findViewById(R.id.button1);
		button2 = (Button) findViewById(R.id.button2);
		button3 = (Button) findViewById(R.id.button3);

		button1.setOnClickListener(this);
		button2.setOnClickListener(this);
		button3.setOnClickListener(this);
	}

	@Override
	public boolean onCreateOptionsMenu(Menu menu) {
		// Inflate the menu; this adds items to the action bar if it is present.
		getMenuInflater().inflate(R.menu.main, menu);
		return true;
	}

	@Override
	public void onClick(View v) {
		Intent intent;
		switch (v.getId()) {
		case R.id.button1:
			intent = new Intent(MainActivity.this, HiDualNetActivity.class);
			startActivity(intent);
			break;

		case R.id.button2:
			intent = new Intent(MainActivity.this, HiSuspendMode.class);
			startActivity(intent);
			break;

		case R.id.button3:
			intent = new Intent(MainActivity.this, HiStartMode.class);
			startActivity(intent);
			break;
		default:
			break;
		}
	}

}
