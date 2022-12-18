package com.explorer.activity;

import android.R.integer;
import android.app.Activity;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.res.Resources;
import android.net.ConnectivityManager;
import android.net.NetworkInfo;
import android.net.wifi.WifiManager;
import android.os.Bundle;
import android.os.SystemProperties;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.Toast;

import com.explorer.R;
import com.explorer.common.CommonActivity;
import com.explorer.common.AnimationButton;
import com.explorer.common.ImageReflect;

public class TabBarExample extends Activity implements OnClickListener, OnKeyListener {
//  private RelativeLayout hsScrollView;
  private AnimationButton tabButton;
  private AnimationButton samBaButton;
  private AnimationButton UPnPButton;
  private AnimationButton nfsButton;
  private AnimationButton baiduPcs;
    private int focusViewId;
  private ImageView refImageView[] = new ImageView[3];

    private IntentFilter mIntenFilter = null;
    private BroadcastReceiver mReceiver = null;
    private boolean isOTTMode;
  // private AnimationButton tabButton_bg;
  // private AnimationButton samBaButton_bg;
  // private AnimationButton nfsButton_bg;
  // private AnimationButton UPnPButton_bg;
  // private AnimationButton baiduPcs_bg;

  public void onCreate(Bundle savedInstanceState) {
    super.onCreate(savedInstanceState);
    isOTTMode = "demo".equals(SystemProperties.get("ro.product.target"));
    if (isOTTMode)
        setContentView(R.layout.main_home_view_ott);
    else
        setContentView(R.layout.main_home_view);

    init();

    tabButton.requestFocus();
    }
    @Override
    protected void onResume() {
        if ("true".equals(SystemProperties.get("ro.samba.quick.search"))) {
            Intent sambaService = new Intent(TabBarExample.this,
                    SambaService.class);
            startService(sambaService);
        }
        super.onResume();
  }

  private void init() {
    tabButton = (AnimationButton) findViewById(R.id.button_1);
    samBaButton = (AnimationButton) findViewById(R.id.button_5);
    nfsButton = (AnimationButton) findViewById(R.id.button_2);
    UPnPButton = (AnimationButton) findViewById(R.id.button_4);
    baiduPcs = (AnimationButton) findViewById(R.id.button_3);

    tabButton.setText(getResources().getString(R.string.local_tab_title));
    samBaButton.setText(getResources().getString(R.string.lan_tab_title));
    nfsButton.setText(getResources().getString(R.string.nfs_tab_title));
    UPnPButton.setText(getResources().getString(R.string.upnp_tab_title));
    baiduPcs.setText(getResources().getString(R.string.baidu_pcs));

    tabButton.setImage(R.drawable.tv_play);
    samBaButton.setImage(R.drawable.music_but);
    nfsButton.setImage(R.drawable.dongman);
    UPnPButton.setImage(R.drawable.zongyi);
    baiduPcs.setImage(R.drawable.live);

    tabButton.setImageBg(R.drawable.shadow_transverse);
    nfsButton.setImageBg(R.drawable.shadow_transverse);
    baiduPcs.setImageBg(R.drawable.shadow_transverse);
        if (isOTTMode) {
            samBaButton.setImageBg(R.drawable.shadow_transverse);
            UPnPButton.setImageBg(R.drawable.shadow_transverse);
        } else {
            samBaButton.setImageBg(R.drawable.shadow_square);
            UPnPButton.setImageBg(R.drawable.shadow_square);
        }

    tabButton.setOnClickListener(this);
    samBaButton.setOnClickListener(this);
    nfsButton.setOnClickListener(this);
    UPnPButton.setOnClickListener(this);
    baiduPcs.setOnClickListener(this);

    tabButton.setOnKeyListener(this);
    samBaButton.setOnKeyListener(this);
    nfsButton.setOnKeyListener(this);
    UPnPButton.setOnKeyListener(this);
    baiduPcs.setOnKeyListener(this);

    // 倒影图片
    refImageView[0] = (ImageView) findViewById(R.id.hot_reflected_img_0);
    refImageView[1] = (ImageView) findViewById(R.id.hot_reflected_img_1);
    refImageView[2] = (ImageView) findViewById(R.id.hot_reflected_img_2);



    ReflectedImage();
		mIntenFilter = new IntentFilter();
	    mIntenFilter.addAction(WifiManager.RSSI_CHANGED_ACTION);
	    mIntenFilter.addAction(WifiManager.WIFI_STATE_CHANGED_ACTION);
	    mIntenFilter.addAction(WifiManager.NETWORK_STATE_CHANGED_ACTION);

	    mIntenFilter.addAction(ConnectivityManager.CONNECTIVITY_ACTION);
	    mIntenFilter.addAction(ConnectivityManager.INET_CONDITION_ACTION);

	    mReceiver = new BroadcastReceiver() {
	        public void onReceive(Context context, Intent intent) {
//	            if (0 != tabHost.getCurrentTab()) {
	                boolean bIsConnect = true;
	                final String action = intent.getAction();
	                if (action.equals(WifiManager.NETWORK_STATE_CHANGED_ACTION)) {
	                    final NetworkInfo networkInfo = (NetworkInfo) intent
	                            .getParcelableExtra(WifiManager.EXTRA_NETWORK_INFO);
	                    bIsConnect = networkInfo != null
	                            && networkInfo.isConnected();
	                } else if (action
	                        .equals(ConnectivityManager.CONNECTIVITY_ACTION)
	                        || action
	                                .equals(ConnectivityManager.INET_CONDITION_ACTION)) {
	                    NetworkInfo info = (NetworkInfo) (intent
	                            .getParcelableExtra(ConnectivityManager.EXTRA_NETWORK_INFO));
	                    bIsConnect = info.isConnected();
	                }
	                ;
	                if (false == bIsConnect) {
	                    Toast.makeText(
	                            TabBarExample.this,
	                            getString(R.string.network_error_exitnetbrowse),
	                            Toast.LENGTH_LONG).show();
//	                    tabHost.setCurrentTab(0);
	                }
//	            }
	        };
	    };
	    registerReceiver(mReceiver, mIntenFilter);
	    
		
  }

  private void ReflectedImage() {
        if (isOTTMode) {
            refImageView[0].setImageBitmap(ImageReflect
                    .createCutReflectedImage(ImageReflect.convertViewToBitmap(
                            TabBarExample.this, R.drawable.live), 0, 662));
            refImageView[1].setImageBitmap(ImageReflect
                    .createCutReflectedImage(ImageReflect.convertViewToBitmap(
                            TabBarExample.this, R.drawable.zongyi), 0, 317));
            refImageView[2].setImageBitmap(ImageReflect
                    .createCutReflectedImage(ImageReflect.convertViewToBitmap(
                            TabBarExample.this, R.drawable.music_but), 0, 300));
        } else {
            refImageView[0].setImageBitmap(ImageReflect
                    .createCutReflectedImage(ImageReflect.convertViewToBitmap(
                            TabBarExample.this, R.drawable.dongman), 0, 662));
            refImageView[1].setImageBitmap(ImageReflect
                    .createCutReflectedImage(ImageReflect.convertViewToBitmap(
                            TabBarExample.this, R.drawable.music_but), 0, 317));
        }
    }

  @Override
  public boolean onKey(View v, int keyCode, KeyEvent event) {
    // TODO Auto-generated method stub

    return false;
  }

  @Override
  public void onClick(View v) {
    // TODO Auto-generated method stub
    focusViewId = v.getId();
    switch (focusViewId) {
    case R.id.button_1:
            Intent tabIntent=new Intent(TabBarExample.this, MainExplorerActivity.class);
            startActivity(tabIntent);
      break;

    case R.id.button_5:
            Intent sambaIntent=new Intent(TabBarExample.this, SambaActivity.class);
            startActivity(sambaIntent);
      break;

    case R.id.button_2:
            Intent nfsIntent=new Intent(TabBarExample.this, NFSActivity.class);
            startActivity(nfsIntent);
      break;

    case R.id.button_4:
      try {
            Intent intent = new Intent();
            ComponentName componentName = new ComponentName("com.hisilicon.dlna.mediacenter", "com.hisilicon.dlna.mediacenter.MediaCenterActivity");
            intent.setComponent(componentName);
            startActivity(intent);
          } catch (Exception e) {
            Toast.makeText(TabBarExample.this, getString(R.string.no_activity_info), Toast.LENGTH_SHORT).show();
          }
      break;

    case R.id.button_3:
      try {
            Intent intent = new Intent();
            ComponentName componentName = new ComponentName("com.hisilicon.baidu.pcs", "com.hisilicon.baidu.pcs.MainActivity");
            intent.setComponent(componentName);
            startActivity(intent);
          } catch (Exception e) {
            Toast.makeText(TabBarExample.this, getString(R.string.no_activity_info), Toast.LENGTH_SHORT).show();
          }
      break;

    default:
      break;
    }
  }

	/**
	 * cancle Toast
	 * CNcomment:取消提示
	 */
	protected void onStop() {
		super.onStop();
		CommonActivity.cancleToast();
	}

	protected void onDestroy() {
		super.onDestroy();
		unregisterReceiver(mReceiver);
        Intent sambaService = new Intent(TabBarExample.this, SambaService.class);
        stopService(sambaService);
	}
}
