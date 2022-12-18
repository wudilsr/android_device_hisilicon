package com.android.hisiliconsetting.normal;

import android.content.Context;
import android.util.AttributeSet;
import android.widget.TextView;

public class MarqueeText extends TextView{
    private boolean b_maquee = true;
    public MarqueeText(Context context) {
        super(context);
        // TODO Auto-generated constructor stub
    }
    public MarqueeText(Context context, AttributeSet attrs){
        super(context, attrs);
    }
    public MarqueeText(Context context, AttributeSet attrs, int defStyle){
        super(context, attrs,defStyle);
    }
    @Override
    public boolean isFocused() {
        // TODO Auto-generated method stub
        return b_maquee;
    }
    public void setMaquee(boolean maquee){
        b_maquee = maquee;
    }

}
