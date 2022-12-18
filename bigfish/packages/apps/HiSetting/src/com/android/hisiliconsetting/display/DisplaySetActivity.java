package com.android.hisiliconsetting.display;
import java.util.HashMap;
import java.util.Timer;
import java.util.TimerTask;

import com.android.hisiliconsetting.CommonDialog;
import com.android.hisiliconsetting.CommonDialog.OnCallback;
import com.android.hisiliconsetting.R;
import com.hisilicon.android.HiDisplayManager;
import android.app.Activity;
import android.app.ActivityManager;
import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.content.IntentFilter;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnFocusChangeListener;
import android.view.View.OnKeyListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;
import android.os.SystemProperties;

public class DisplaySetActivity extends Activity implements OnClickListener {
    private String TAG ="DisplaySetActivity";
    private RelativeLayout mScalLayout = null,mTvLayout = null;
    private ImageView mTv_Up = null,mTv_Down = null;
    private TextView mTvInfo = null;
    private int mTvFmt = 0;
    private int mTvCount = 0;
    private int mTvOldFmt = 0;
    private int mTvNewFmt = 0;
    private String[] mList_Tv = null;
    private int[] mtv_value = null;
    private final int FRESH_BUTTON_UP = 1;
    private final int FRESH_BUTTON_DOWN = 2;
    private final int FRESH_FMT = 3;
    private final int mDelayTime = 300;
    private Timer mtimer = null;
    private HiDisplayManager mDisplay = null;
    private CommonDialog dialog = null;
    private HashMap<String, Integer> map_value = new HashMap<String, Integer>();
    private HashMap<Integer, String> map_key = new HashMap<Integer, String>();
    private String mProduc_name = null;
    private Boolean m_bHires = true;
    private final String DISPLAY_ACTION = "com.hisilicon.intent.action.ACTION_FORMAT_CHANGED"; 
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.display_set_main);
        mDisplay = new HiDisplayManager();
        InitUi();
        IntentFilter mintenfilter = new IntentFilter(DISPLAY_ACTION);
        registerReceiver(FmtChangReceiver, mintenfilter);

    }
    @Override
    protected void onResume() {
        super.onResume();
        if(mDisplay.getDisplayDeviceType()<=1){
            mList_Tv = getResources().getStringArray(R.array.set_video_tv_list);
            mtv_value = getResources().getIntArray(R.array.set_video_tv_value);
            mProduc_name = SystemProperties.get("ro.product.device");
            if(!mProduc_name.substring(0, 5).equals("Hi379")){
            m_bHires = false;
            }
        }else{
            mList_Tv = getResources().getStringArray(R.array.set_video_pc_list);
            mtv_value = getResources().getIntArray(R.array.set_video_pc_list_value);
            mTvInfo.setTextSize(24);
        }
        mTvCount = mtv_value.length;
        Log.i(TAG, "mTvCount="+mTvCount);
        AddMap();
        mTvOldFmt = mDisplay.getFmt();
        mTvFmt = getIndex(mTvOldFmt);
        mTvInfo.setText(mList_Tv[mTvFmt]);
    }
    private void AddMap(){
        for(int i = 0; i < mTvCount; i++) {
        map_value.put(mList_Tv[i], mtv_value[i]);
        map_key.put(mtv_value[i], mList_Tv[i]);
        }
    }
    private int getIndex(int fmt){
        int ret = 0;
        Log.i(TAG, "oldfmt="+fmt);
        Log.i(TAG, "map_key="+map_key.toString());
        String info = map_key.get(fmt);
        if(info==null)
           return ret;
        for (int i = 0; i < mTvCount; i++) {
        if(info.equals(mList_Tv[i])){
        ret = i;
        break;
        }
        }
        return ret;
    }
    private Handler mhandler = new Handler(){
        public void handleMessage(Message msg) {
        switch (msg.what) {
        case FRESH_BUTTON_DOWN:
        mTv_Down.setBackgroundResource(R.drawable.arrow_normal_down);
        break;
        case FRESH_BUTTON_UP:
        mTv_Up.setBackgroundResource(R.drawable.arrow_normal_up);
        break;
        case FRESH_FMT:
        if(mTvNewFmt!=mTvOldFmt){
        dialog.dismiss();
        mDisplay.setFmt(mTvOldFmt);
        mDisplay.SaveParam();
        }
        break;
        default:
        break;
        }
        }
    };
    private void InitUi(){
        mScalLayout = (RelativeLayout)findViewById(R.id.display_scale);
        mScalLayout.setOnKeyListener(new LayoutListener());
        mScalLayout.setOnClickListener(new OnClickListener() {
            @Override
            public void onClick(View v) {
                Intent intent = new Intent();
                intent.setClass(DisplaySetActivity.this, ScaleAndMoveActivity.class);
                startActivity(intent);
           }
        });
        mTvLayout = (RelativeLayout)findViewById(R.id.display_set_tv);
        mTvLayout.setOnKeyListener(new LayoutListener());
        mTv_Down = (ImageView)findViewById(R.id.display_set_down);
        mTv_Up = (ImageView)findViewById(R.id.display_set_up);
        mTvInfo = (TextView)findViewById(R.id.display_set_tv_info);
        mTv_Up.setOnClickListener(this);
        mTv_Down.setOnClickListener(this);
        mTvLayout.setOnClickListener(this);
    }
    private class LayoutListener implements OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        int id = v.getId();
        if(id==R.id.display_set_tv){
        if(keyCode==KeyEvent.KEYCODE_DPAD_UP&&event.getAction()==KeyEvent.ACTION_DOWN){
        setUp();
        }
        if(keyCode==KeyEvent.KEYCODE_DPAD_DOWN&&event.getAction()==KeyEvent.ACTION_DOWN){
        setDown();
        }
        }
        if(keyCode==KeyEvent.KEYCODE_DPAD_CENTER&&event.getAction()==KeyEvent.ACTION_DOWN||
           keyCode == KeyEvent.KEYCODE_ENTER&&event.getAction()==KeyEvent.ACTION_DOWN ){
        switch (id) {

        case R.id.display_scale:
        Intent intent = new Intent();
        intent.setClass(DisplaySetActivity.this, ScaleAndMoveActivity.class);
        startActivity(intent);
        break;
        default:
        break;
        }
        }
//        if(keyCode==KeyEvent.KEYCODE_BACK&&event.getAction()==KeyEvent.ACTION_DOWN){
//        mTvNewFmt = map_value.get(mList_Tv[mTvFmt]);
//        if(mTvNewFmt!=mTvOldFmt){
//        ShowDialog(false);
//        return true;
//        }
//        }
        return false;
        }
    }
    private void RefreshText(int count,int keycode){
        mTvInfo.setText(mList_Tv[count]);
        if(keycode==KeyEvent.KEYCODE_DPAD_UP){
        mTv_Up.setBackgroundResource(R.drawable.arrow_focus_up);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_UP, mDelayTime);
        }else if(keycode==KeyEvent.KEYCODE_DPAD_DOWN){
        mTv_Down.setBackgroundResource(R.drawable.arrow_focus_down);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_DOWN, mDelayTime);
        }
    }
    private void ShowDialog(final boolean reset){
         dialog = new CommonDialog(this, android.R.style.Theme_Translucent_NoTitleBar_Fullscreen, new OnCallback() {
        @Override
        public void OkcallBack() {
        cancelTimer();
        mTvOldFmt = mTvNewFmt;
        mDisplay.SaveParam();
        }
        @Override
        public void CancelcallBack() {
        cancelTimer();
        mDisplay.setFmt(mTvOldFmt);
        mDisplay.SaveParam();
        }
		@Override
		public void MidcallBack() {
			// TODO Auto-generated method stub
		}
        });
        dialog.show();
        dialog.setCancelable(false);
        dialog.SetText(getResources().getString(R.string.display_set_hint));
        startTimer();
    }
     private void startTimer(){
        if(mtimer==null){
        mtimer = new Timer();
        mtimer.schedule(new TimerTask() {
        @Override
        public void run() {
        mhandler.sendEmptyMessage(FRESH_FMT);
        }
        }, 10000);
        }
        }
        private void cancelTimer(){
        if(mtimer!=null){
        mtimer.cancel();
        mtimer = null;
        }
        }
    private void setUp() {
        if (mTvFmt < mTvCount - 1) {
            mTvFmt++;
        } else {
            if (!m_bHires) {
                mTvFmt = 2;
            } else {
                mTvFmt = 0;
            }
        }
        mTvInfo.setText(mList_Tv[mTvFmt]);
        mTv_Up.setBackgroundResource(R.drawable.arrow_focus_up);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_UP, mDelayTime);
    }
    private void setDown() {
        if (mTvFmt > 0) {
            mTvFmt--;
            if (!m_bHires && mTvFmt == 1) {
                mTvFmt = mTvCount - 1;
            }
        } else {
            mTvFmt = mTvCount - 1;
        }
        mTvInfo.setText(mList_Tv[mTvFmt]);
        mTv_Down.setBackgroundResource(R.drawable.arrow_focus_down);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_DOWN, mDelayTime);
    }
    private void setAttributes() {
        mTvNewFmt = map_value.get(mList_Tv[mTvFmt]);
        if (mTvOldFmt != mTvNewFmt) {
            int ret = mDisplay.setFmt(mTvNewFmt);
            if (ret == 0) {
                ShowDialog(true);
            }
        }
    }
    @Override
    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.display_set_down:
            setDown();
            break;
        case R.id.display_set_up:
            setUp();
            break;
        case R.id.display_set_tv:
            setAttributes();
            break;
        default:
            break;
        }
    }
    @Override
    protected void onDestroy() {
        super.onDestroy();
        unregisterReceiver(FmtChangReceiver);
    }
    private BroadcastReceiver FmtChangReceiver = new BroadcastReceiver(){
        @Override
        public void onReceive(Context arg0, Intent intent) {
            if(intent.getAction().equals(DISPLAY_ACTION)){
                mTvOldFmt = mDisplay.getFmt();
                mTvFmt = getIndex(mTvOldFmt);
                mTvInfo.setText(mList_Tv[mTvFmt]);
            }
        }
    };
}
