package com.explorer.common;

import com.explorer.R;

import android.content.Context;
import android.util.AttributeSet;
import android.view.LayoutInflater;
import android.view.View;
import android.view.View.OnFocusChangeListener;
import android.view.animation.Animation;
import android.view.animation.Animation.AnimationListener;
import android.view.animation.ScaleAnimation;
import android.widget.ImageView;
import android.widget.LinearLayout;
import android.widget.RelativeLayout;
import android.widget.TextView;

public class AnimationButton extends RelativeLayout implements OnFocusChangeListener {

//    private float animationX = 1.06f;
//    private float animationY = 1.06f;
	  private float animationX = 1.16f;
	  private float animationY = 1.22f;

    private ImageView animationBkImage;
    private ImageView animationImage;
    private TextView animationText;

    public AnimationButton(Context context) {
        super(context);
        initView();
    }

    public AnimationButton(Context context, AttributeSet attrs) {
        super(context, attrs);
        initView();
    }

    public AnimationButton(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        initView();
    }

    private void initView() {
        setLayoutParams(new LinearLayout.LayoutParams(
                LinearLayout.LayoutParams.MATCH_PARENT,
                LinearLayout.LayoutParams.WRAP_CONTENT));
        LayoutInflater inflater = (LayoutInflater) getContext()
                .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        inflater.inflate(R.layout.animation_button, this);
        animationBkImage = (ImageView) findViewById(R.id.animation_bk_image);
        animationImage = (ImageView) findViewById(R.id.animation_image);
        animationText = (TextView) findViewById(R.id.animation_text);
        setOnFocusChangeListener(this);
    }

    public void setText(String text) {
        animationText.setText(text);
    }

    public void setImage(int id) {
        animationImage.setImageResource(id);
    }

    public void setImageBg(int id) {
        this.animationBkImage.setImageResource(id);
    }

    public void setAnimationScale(float animationX, float animationY) {
        this.animationX = animationX;
        this.animationY = animationY;
    }

    @Override
    public void onFocusChange(View v, boolean hasFocus) {
        ScaleAnimation animation = null;
        if (hasFocus) {
            animation = new ScaleAnimation(1.0f, animationX, 1.0f, animationY,
                    Animation.RELATIVE_TO_SELF, 0.5f,
                    Animation.RELATIVE_TO_SELF, 0.5f);

        } else {
            animation = new ScaleAnimation(animationX, 1.0f, animationY, 1.0f,
                    Animation.RELATIVE_TO_SELF, 0.5f,
                    Animation.RELATIVE_TO_SELF, 0.5f);
        }
        bringToFront();
        animation.setDuration(200);
        animation.setFillAfter(true);
        animation.setAnimationListener(new MyAnimationListener(hasFocus));
        this.startAnimation(animation);
    }

    private class MyAnimationListener implements AnimationListener {
        private boolean hasFocus;

        public MyAnimationListener(boolean hasFocus) {
            this.hasFocus = hasFocus;
        }

        @Override
        public void onAnimationStart(Animation animation) {
            if (!hasFocus) {
                animationBkImage.setVisibility(View.GONE);
            }
        }

        @Override
        public void onAnimationEnd(Animation animation) {
            if (hasFocus) {
                animationBkImage.setVisibility(View.VISIBLE);
            }
        }

        @Override
        public void onAnimationRepeat(Animation animation) {
        }
    }

}
