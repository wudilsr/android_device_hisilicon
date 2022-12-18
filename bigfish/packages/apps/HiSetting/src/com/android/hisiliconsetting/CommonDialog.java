package com.android.hisiliconsetting;
import android.app.Dialog;
import android.content.Context;
import android.os.Bundle;
import android.view.View;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.TextView;

/**
 *
 */
public class CommonDialog extends Dialog{
    private TextView mTitle = null;
    private OnCallback mCall = null;
    private Button mConfirmButton = null;
    private Button mCancleButton = null;
    private Button mMidButton = null;
    private TextView mTextView = null;
    private ImageView mIcon = null;

    public static interface OnCallback {
        public void OkcallBack();
        public void CancelcallBack();
        public void MidcallBack();
    }

    public CommonDialog(Context context, int theme,OnCallback call) {
        super(context, theme);
        mCall = call;
    }
    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.common_dialog);
        mTitle = (TextView)findViewById(R.id.common_dialog_title);
        mTextView = (TextView)findViewById(R.id.common_dialog_text);
        mIcon = (ImageView)findViewById(R.id.common_dialog_image);
        mConfirmButton = (Button)findViewById(R.id.common_dialog_positive_btn);
        mCancleButton = (Button)findViewById(R.id.common_dialog_negative_btn);
        mMidButton = (Button)findViewById(R.id.common_dialog_mid_btn);
        mCancleButton.requestFocus();
        mConfirmButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
        // TODO Auto-generated method stub
        if(mCall!=null){
        mCall.OkcallBack();
        dismiss();
        }
        }

        });
        mCancleButton.setOnClickListener(new View.OnClickListener() {
        @Override
        public void onClick(View v) {
        mCall.CancelcallBack();
        dismiss();
        }
        });
        mMidButton.setOnClickListener(new View.OnClickListener() {
			@Override
			public void onClick(View arg0) {
				mCall.MidcallBack();
				mMidButton.setVisibility(View.GONE);
		        dismiss();
			}
		});
    }
    public void SetTitle(String title){
        mTitle.setText(title);
    }
    public void SetText(String text){
        mTextView.setText(text);
    }
    public void SetHintImage(int imageid){
        mIcon.setImageResource(imageid);
    }
    public void SetPositiveText(String text){
        mConfirmButton.setText(text);
    }
    public void SetCancleText(String text){
        mCancleButton.setText(text);
    }
    public void SetMidText(String text){
        mMidButton.setText(text);
        mMidButton.setVisibility(View.VISIBLE);
    }
//    public void setSelectedListSize(int size) {
//        mTextView.setTextSize(size);
//    }
}
