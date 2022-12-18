package com.hisilicon.multiscreen.mybox;

import android.content.Context;
import android.graphics.drawable.AnimationDrawable;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.widget.ImageView;
import android.widget.RelativeLayout;

/**
 * Speech record view.
 */
public class SpeechRecordView extends RelativeLayout
{
    private Context mContext;

    private AnimationDrawable mAnimationDrawable;

    View mView;
    public SpeechRecordView(Context context)
    {
        super(context);
        mContext = context;
        initViews(context);

    }

    public SpeechRecordView(Context context, AttributeSet attrs)
    {
        super(context, attrs);
        this.mContext = context;
        initViews(context);

    }
    /**
     * init view.
     */
    public void initViews(Context context)
    {

        View mView = LayoutInflater.from(mContext).inflate(R.layout.speech_record_layout, this);
        ImageView speechImage = (ImageView) findViewById(R.id.speech_img);
        speechImage.setBackgroundResource(R.anim.speech_record_anim);
        mAnimationDrawable = (AnimationDrawable) speechImage.getBackground();
    }

    public void show()
    {
        setVisibility(View.VISIBLE);
        mAnimationDrawable.start();
    }

    public void dismiss()
    {
        mAnimationDrawable.stop();
        setVisibility(View.INVISIBLE);
    }

}
