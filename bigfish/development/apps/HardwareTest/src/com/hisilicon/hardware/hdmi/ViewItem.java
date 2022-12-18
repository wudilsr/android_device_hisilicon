package com.hisilicon.hardware.hdmi;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.hardwaretest.R;

public class ViewItem extends RelativeLayout {

    public static final int TYPE_1 = 1;
    public static final int TYPE_2 = 2;
    private TextView textTitle;
    private TextView textMessage;
    private ImageView imageLeft;
    private ImageView imageRight;
    private int type = TYPE_1;

    public ViewItem(Context context) {
        super(context);
        initView();
    }
    public ViewItem(Context context, int type) {
        super(context);
        this.type = type;
        initView();
    }

    public ViewItem(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public ViewItem(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        initView();
    }

    private void initView() {
        LayoutInflater inflater = (LayoutInflater) getContext()
                .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        if (TYPE_1 == type) {
        inflater.inflate(R.layout.hdmi_list_item, this);
        textTitle = (TextView) findViewById(R.id.text_title);
        textMessage = (TextView) findViewById(R.id.text_message);
        imageLeft = (ImageView) findViewById(R.id.image_left);
        imageRight = (ImageView) findViewById(R.id.image_right);
        } else {
            inflater.inflate(R.layout.hdmi_display_edid_view, this);
            textTitle = (TextView) findViewById(R.id.text_title);
    }
    }
    public void setTitle(String title) {
        if (null != textTitle)
        textTitle.setText(title);
    }

    public void setMessage(String message) {
        if (null != textMessage)
        textMessage.setText(message);
    }

    public void setLeftImageNormal() {
        imageLeft.setImageResource(R.drawable.left_normal);
    }

    public void setLeftImageFocus() {
        imageLeft.setImageResource(R.drawable.left_focused);
    }

    public void setRightImageNormal() {
        imageRight.setImageResource(R.drawable.right_normal);
    }

    public void setRightImageFocus() {
        imageRight.setImageResource(R.drawable.right_focused);
    }

}