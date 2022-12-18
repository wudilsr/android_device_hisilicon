package com.android.hisiliconsetting.play;
import com.android.hisiliconsetting.R;
import com.hisilicon.android.HiAoService;
import com.hisilicon.android.HiDisplayManager;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.util.Log;
import android.view.KeyEvent;
import android.view.View;
import android.view.View.OnClickListener;
import android.view.View.OnKeyListener;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class PlaySetActivity extends Activity{
    private String TAG = "PlaySetActivity";
    private int AUDIO_HDMI = 0;
    private int AUDIO_SPDIF = 0;
    private int AUDIO_HBR = 0;

    private TextView mHdmiTx = null,mSpdifTx = null,mHbrTx = null,mV_ratioTx=null,mV_tranTx=null;
    private ImageView mHdmi_Bn_r = null,mHdmi_Bn_l = null;
    private ImageView mSpdif_Bn_r = null,mSpdif_Bn_l = null;
    private ImageView mHbr_Bn_r = null,mHbr_Bn_l = null;
    private ImageView mTran_Bn_r = null,mTran_Bn_l = null;
    private ImageView mRatio_Bn_r = null,mRatio_Bn_l = null;

    private String[] mHdmi_array = null;
    private String[] mSpdif_array = null;
    private String[] mHbr_array = null;
    private String[] mRatio_array = null;
    private String[] mTran_array = null;

    private int mHdim_index = 0;
    private int mSpdif_index = 0;
    private int mHbr_index = 0;
    private int mRatio_index = 0;
    private int mTran_index = 0;


    private RelativeLayout mHdmi_layout = null,mSpdif_layout = null,mHbr_layout = null,mRatio_layout = null,mTran_layout = null;
    private HiAoService mAudioManager = null;
    private HiDisplayManager mDisplayManager = null;
    private final int FRESH_BUTTON_RIGHT = 1;
    private final int FRESH_BUTTON_LEFT = 2;
    private final int mDelayTime = 300;
    private enum PlayType{
        HDMI,
        SPDIF,
        HBR,
        VIDEO_RATIO,
        VIDEO_TRAN,
    }
    private PlayType mType = PlayType.HDMI;
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.play_set_main);
        mAudioManager = new HiAoService();
        mDisplayManager = new HiDisplayManager();
        InitUI();
    }
    @Override
    protected void onResume() {
        super.onResume();
        InitData();
    }

    private void InitData(){
        AUDIO_HDMI = HiAoService.AUDIO_OUTPUT_PORT_HDMI;
        AUDIO_SPDIF = HiAoService.AUDIO_OUTPUT_PORT_SPDIF;
        AUDIO_HBR = 3;

        mHdmi_array = getResources().getStringArray(R.array.hdmi_output_show);
        mSpdif_array = getResources().getStringArray(R.array.sdpif_output_show);
        mHbr_array = getResources().getStringArray(R.array.bluelight_output_show);
        mRatio_array = getResources().getStringArray(R.array.set_video_ratio);
        mTran_array = getResources().getStringArray(R.array.set_video_cvrs);

        mHdim_index = mAudioManager.getAudioOutput(AUDIO_HDMI);
        mSpdif_index = mAudioManager.getAudioOutput(AUDIO_SPDIF);
        mHbr_index = mAudioManager.getAudioOutput(AUDIO_HBR);
        mRatio_index = mDisplayManager.getAspectRatio();
        mTran_index = mDisplayManager.getAspectCvrs();
        Log.i(TAG, "mHdim_index = "+mHdim_index);
        Log.i(TAG, "mSpdif_index = "+mSpdif_index);
        Log.i(TAG, "mHbr_index = "+mHbr_index);
        if(mSpdif_index!=0)
        mSpdif_index = mSpdif_index-1;
        mHdmiTx.setText(mHdmi_array[mHdim_index]);
        mSpdifTx.setText(mSpdif_array[mSpdif_index]);
        mHbrTx.setText(mHbr_array[mHbr_index]);
        mV_ratioTx.setText(mRatio_array[mRatio_index]);
        mV_tranTx.setText(mTran_array[mTran_index]);
        if(mHdim_index==2){
        HideHbrLayout(true);
        }
    }
    private void InitUI(){
        mHdmi_layout = (RelativeLayout)findViewById(R.id.play_audio_hdmi);
        mHdmi_layout.setOnKeyListener(new LayoutListener());
        mHdmi_layout.setOnClickListener(new LayoutOnClick());

        mSpdif_layout = (RelativeLayout)findViewById(R.id.play_audio_spdif);
        mSpdif_layout.setOnKeyListener(new LayoutListener());
        mSpdif_layout.setOnClickListener(new LayoutOnClick());

        mHbr_layout = (RelativeLayout)findViewById(R.id.play_audio_hbr);
        mHbr_layout.setOnKeyListener(new LayoutListener());
        mHbr_layout.setOnClickListener(new LayoutOnClick());

        mRatio_layout = (RelativeLayout)findViewById(R.id.play_video_ratio);
        mRatio_layout.setOnKeyListener(new LayoutListener());
        mRatio_layout.setOnClickListener(new LayoutOnClick());

        mTran_layout = (RelativeLayout)findViewById(R.id.play_video_transform);
        mTran_layout.setOnKeyListener(new LayoutListener());
        mTran_layout.setOnClickListener(new LayoutOnClick());

        mHdmi_Bn_r = (ImageView)findViewById(R.id.play_hdmi_right);
        mHdmi_Bn_l = (ImageView)findViewById(R.id.play_hdmi_left);
        mSpdif_Bn_r = (ImageView)findViewById(R.id.play_spdif_right);
        mSpdif_Bn_l = (ImageView)findViewById(R.id.play_spdif_left);
        mHbr_Bn_r = (ImageView)findViewById(R.id.play_hbr_right);
        mHbr_Bn_l = (ImageView)findViewById(R.id.play_hbr_left);
        mRatio_Bn_r = (ImageView)findViewById(R.id.play_ratio_right);
        mRatio_Bn_l = (ImageView)findViewById(R.id.play_ratio_left);
        mTran_Bn_r = (ImageView)findViewById(R.id.play_transform_right);
        mTran_Bn_l = (ImageView)findViewById(R.id.play_transform_left);

        mHdmiTx = (TextView)findViewById(R.id.play_hdmi_info);
        mSpdifTx = (TextView)findViewById(R.id.play_spdif_info);
        mHbrTx = (TextView)findViewById(R.id.play_hbr_info);
        mV_ratioTx = (TextView)findViewById(R.id.play_ratio_info);
        mV_tranTx = (TextView)findViewById(R.id.play_transform_info);
    }
    private Handler mhandler = new Handler(){
        public void handleMessage(Message msg) {
        switch (msg.what) {
        case FRESH_BUTTON_RIGHT:
        if(mType==PlayType.HDMI){
        mHdmi_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==PlayType.SPDIF){
        mSpdif_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==PlayType.HBR){
        mHbr_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==PlayType.VIDEO_RATIO){
        mRatio_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }else if(mType==PlayType.VIDEO_TRAN){
        mTran_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_normal);
        }
        break;
        case FRESH_BUTTON_LEFT:
        if(mType==PlayType.HDMI){
        mHdmi_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==PlayType.SPDIF){
        mSpdif_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==PlayType.HBR){
        mHbr_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==PlayType.VIDEO_RATIO){
        mRatio_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }else if(mType==PlayType.VIDEO_TRAN){
        mTran_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_normal);
        }
        break;
        default:
        break;
        }
        saveVideSet();
        setAudioHdmi(AUDIO_HDMI, mHdim_index);
        setAudioSpdif(AUDIO_SPDIF, mSpdif_index);
        setAudioHbr(mHbr_index);
        }
    };
    private class LayoutOnClick implements OnClickListener{
		@Override
		public void onClick(View v) {
			int id = v.getId();
			switch (id) {
	        case R.id.play_audio_hdmi:
	        mType = PlayType.HDMI;
	        OnClickRefreshText(mType);
	        break;
	        case R.id.play_audio_spdif:
	        mType = PlayType.SPDIF;
	        OnClickRefreshText(mType);
	        break;
	        case R.id.play_audio_hbr:
	        mType = PlayType.HBR;
	        OnClickRefreshText(mType);
	        break;
	        case R.id.play_video_ratio:
	        mType = PlayType.VIDEO_RATIO;
	        OnClickRefreshText(mType);
	        break;
	        case R.id.play_video_transform:
	        mType = PlayType.VIDEO_TRAN;
	        OnClickRefreshText(mType);
	        break;
	        default:
	        break;
	        }
		}
    }
    private class LayoutListener implements OnKeyListener{
        @Override
        public boolean onKey(View v, int keyCode, KeyEvent event) {
        if(event.getAction()==KeyEvent.ACTION_UP)
        return false;
        int id = v.getId();
        if(keyCode==KeyEvent.KEYCODE_DPAD_LEFT||keyCode==KeyEvent.KEYCODE_DPAD_RIGHT){
        switch (id) {
        case R.id.play_audio_hdmi:
        mType = PlayType.HDMI;
        RefreshText(mType,keyCode);
        break;
        case R.id.play_audio_spdif:
        mType = PlayType.SPDIF;
        RefreshText(mType,keyCode);
        break;
        case R.id.play_audio_hbr:
        mType = PlayType.HBR;
        RefreshText(mType,keyCode);
        break;
        case R.id.play_video_ratio:
        mType = PlayType.VIDEO_RATIO;
        RefreshText(mType,keyCode);
        break;
        case R.id.play_video_transform:
        mType = PlayType.VIDEO_TRAN;
        RefreshText(mType,keyCode);
        break;
        default:
        break;
        }
        }
        return false;
        }

    }
    private void OnClickRefreshText(PlayType type){
        switch (type) {
        case HDMI:
        if(mHdim_index>0){
        mHdim_index--;
        }else{
        mHdim_index = mHdmi_array.length -1;
        }
        if(mHdim_index==2){
        HideHbrLayout(true);
        }else{
        HideHbrLayout(false);
        }
        mHdmiTx.setText(mHdmi_array[mHdim_index]);
        break;
        case SPDIF:
        if(mSpdif_index>0){
        mSpdif_index--;
        }else{
        mSpdif_index = mSpdif_array.length -1;
        }
        mSpdifTx.setText(mSpdif_array[mSpdif_index]);
        break;
        case HBR:
        if(mHbr_index>0){
        mHbr_index--;
        }else{
        mHbr_index = mHbr_array.length -1;
        }
        mHbrTx.setText(mHbr_array[mHbr_index]);
        break;
        case VIDEO_RATIO:
        if(mRatio_index>0){
        mRatio_index--;
        }else{
        mRatio_index = mRatio_array.length -1;
        }
        mV_ratioTx.setText(mRatio_array[mRatio_index]);
        break;
        case VIDEO_TRAN:
        if(mTran_index>0){
        mTran_index--;
        }else{
        mTran_index = mTran_array.length -1;
        }
        mV_tranTx.setText(mTran_array[mTran_index]);
        break;
        default:
        break;
       }
        saveVideSet();
        setAudioHdmi(AUDIO_HDMI, mHdim_index);
        setAudioSpdif(AUDIO_SPDIF, mSpdif_index);
        setAudioHbr(mHbr_index);
    }
    private void RefreshText(PlayType type,int keycode){
        switch (keycode) {
        case KeyEvent.KEYCODE_DPAD_LEFT:
        switch (type) {
        case HDMI:
        if(mHdim_index>0){
        mHdim_index--;
        }else{
        mHdim_index = mHdmi_array.length -1;
        }
        if(mHdim_index==2){
        HideHbrLayout(true);
        }else{
        HideHbrLayout(false);
        }
        mHdmiTx.setText(mHdmi_array[mHdim_index]);
        mHdmi_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        break;
        case SPDIF:
        if(mSpdif_index>0){
        mSpdif_index--;
        }else{
        mSpdif_index = mSpdif_array.length -1;
        }
        mSpdifTx.setText(mSpdif_array[mSpdif_index]);
        mSpdif_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        break;
        case HBR:
        if(mHbr_index>0){
        mHbr_index--;
        }else{
        mHbr_index = mHbr_array.length -1;
        }
        mHbrTx.setText(mHbr_array[mHbr_index]);
        mHbr_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        break;
        case VIDEO_RATIO:
        if(mRatio_index>0){
        mRatio_index--;
        }else{
        mRatio_index = mRatio_array.length -1;
        }
        mV_ratioTx.setText(mRatio_array[mRatio_index]);
        mRatio_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);

        break;
        case VIDEO_TRAN:
        if(mTran_index>0){
        mTran_index--;
        }else{
        mTran_index = mTran_array.length -1;
        }
        mV_tranTx.setText(mTran_array[mTran_index]);
        mTran_Bn_l.setBackgroundResource(R.drawable.setting_second_wifi_switch_left_focused);
        break;
        default:
        break;
        }
        mhandler.removeMessages(FRESH_BUTTON_LEFT);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_LEFT, mDelayTime);
        break;
        case KeyEvent.KEYCODE_DPAD_RIGHT:
        switch (type) {
        case HDMI:
        if(mHdim_index<mHdmi_array.length-1){
        mHdim_index++;
        }else{
        mHdim_index = 0;
        }
        if(mHdim_index==2){
        HideHbrLayout(true);
        }else{
        HideHbrLayout(false);
        }
        mHdmiTx.setText(mHdmi_array[mHdim_index]);
        mHdmi_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        case SPDIF:
        if(mSpdif_index<mSpdif_array.length-1){
        mSpdif_index++;
        }else{
        mSpdif_index = 0;
        }
        mSpdifTx.setText(mSpdif_array[mSpdif_index]);
        mSpdif_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        case HBR:
        if(mHbr_index<mHbr_array.length-1){
        mHbr_index++;
        }else{
        mHbr_index = 0;
        }
        mHbrTx.setText(mHbr_array[mHbr_index]);
        mHbr_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        case VIDEO_RATIO:
        if(mRatio_index<mRatio_array.length-1){
        mRatio_index++;
        }else{
        mRatio_index = 0;
        }
        mV_ratioTx.setText(mRatio_array[mRatio_index]);
        mRatio_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        case VIDEO_TRAN:
        if(mTran_index<mTran_array.length-1){
        mTran_index++;
        }else{
        mTran_index = 0;
        }
        mV_tranTx.setText(mTran_array[mTran_index]);
        mTran_Bn_r.setBackgroundResource(R.drawable.setting_second_wifi_switch_right_focused);
        break;
        default:
        break;
        }
        mhandler.removeMessages(FRESH_BUTTON_RIGHT);
        mhandler.sendEmptyMessageDelayed(FRESH_BUTTON_RIGHT, mDelayTime);
        break;
        default:
        break;
        }
    }
    private void saveVideSet(){
        mDisplayManager.setAspectRatio(mRatio_index);
        mDisplayManager.setAspectCvrs(mTran_index);
    }
    private int setAudioHdmi(int type,int value){
        int ret = 0;
        ret = mAudioManager.setAudioOutput(type, value);
        return ret;
    }
    private int setAudioSpdif(int type,int value){
        int ret = 0;
        if(value!=0)
           value = value+1;
        ret = mAudioManager.setAudioOutput(type, value);
        return ret;
    }
    private int setAudioHbr(int value){
        int ret = 0;
        ret = mAudioManager.setBluerayHbr(value);
        return ret;
    }
    private void HideHbrLayout(Boolean hide){
        if(hide){
        mHbr_layout.setEnabled(false);
        mHbr_layout.setClickable(false);
        mSpdif_layout.setNextFocusDownId(R.id.play_video_ratio);
        mRatio_layout.setNextFocusUpId(R.id.play_audio_spdif);
        }else{
        mSpdif_layout.setNextFocusDownId(R.id.play_audio_hbr);
        mRatio_layout.setNextFocusUpId(R.id.play_audio_hbr);
        mHbr_layout.setEnabled(true);
        mHbr_layout.setClickable(true);
        }
    }
}
