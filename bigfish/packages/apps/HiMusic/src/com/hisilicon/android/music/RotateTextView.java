package com.hisilicon.android.music;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Paint;
import android.util.AttributeSet;
import android.widget.TextView;
import android.util.Log;

public class RotateTextView extends TextView {

    public RotateTextView(Context context) {
        super(context);
        // TODO Auto-generated constructor stub
    }

    public RotateTextView(Context context, AttributeSet attrs, int defStyle) {
        super(context, attrs, defStyle);
        // TODO Auto-generated constructor stub
    }

    public RotateTextView(Context context, AttributeSet attrs) {
        super(context, attrs);
        // TODO Auto-generated constructor stub
    }

    /*
     * (non-Javadoc)
     * @see android.widget.TextView#onDraw(android.graphics.Canvas)
     */
    @Override
    protected void onDraw(Canvas canvas) {
        // TODO Auto-generated method stub
        canvas.translate(0, 0);
        canvas.rotate(0);
        super.onDraw(canvas);
    }

    /*
     * (non-Javadoc)
     * @see android.widget.TextView#onMeasure(int, int)
     */
    @Override
    protected void onMeasure(int widthMeasureSpec, int heightMeasureSpec) {
        // TODO Auto-generated method stub
        super.onMeasure(widthMeasureSpec, heightMeasureSpec);
        // setMeasuredDimension(130, 130);
    }

}
