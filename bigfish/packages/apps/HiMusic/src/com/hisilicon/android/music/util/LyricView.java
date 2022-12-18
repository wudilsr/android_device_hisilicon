package com.hisilicon.android.music.util;

import java.util.List;

import android.content.Context;
import android.graphics.Canvas;
import android.graphics.Color;
import android.graphics.Paint;
import android.graphics.Typeface;
import android.util.AttributeSet;
import android.util.Log;
import android.widget.TextView;

/**
 * @author
 */
public class LyricView extends TextView {
    private Paint NotCurrentPaint; // Not Cuurent Lyric Paint
    private Paint CurrentPaint; // Cuurent Lyric Paint

    private int notCurrentPaintColor = Color.WHITE;// Not Cuurent Lyric color of
                                                   // the Paint
    private int CurrentPaintColor = Color.RED; // Cuurent Lyric color of the
                                               // Paint

    private Typeface Texttypeface = Typeface.SERIF;
    private Typeface CurrentTexttypeface = Typeface.DEFAULT_BOLD;
    private float width;
    private static Lyric mLyric;
    private int brackgroundcolor = 0xf000000; // Brackground color
    private float lrcTextSize = 22; // Lyric Text Size
    private float CurrentTextSize = 24;

    public float mTouchHistoryY;

    private int height;
    private long currentDunringTime; // The duration of the current line of
                                     // lyrics, use the time to sleep
    private int TextHeight = 50; // Each row spacing
    private boolean lrcInitDone = false;// Is initialised.
    public int index = 0;
    private int lastIndex = 0;
    private List<Sentence> Sentencelist; // Lyric List

    private long currentTime;

    private long sentenctTime;

    public Paint getNotCurrentPaint() {
        return NotCurrentPaint;
    }

    public void setNotCurrentPaint(Paint notCurrentPaint) {
        NotCurrentPaint = notCurrentPaint;
    }

    public boolean isLrcInitDone() {
        return lrcInitDone;
    }

    public Typeface getCurrentTexttypeface() {
        return CurrentTexttypeface;
    }

    public void setCurrentTexttypeface(Typeface currrentTexttypeface) {
        CurrentTexttypeface = currrentTexttypeface;
    }

    public void setLrcInitDone(boolean lrcInitDone) {
        this.lrcInitDone = lrcInitDone;
    }

    public float getLrcTextSize() {
        return lrcTextSize;
    }

    public void setLrcTextSize(float lrcTextSize) {
        this.lrcTextSize = lrcTextSize;
    }

    public float getCurrentTextSize() {
        return CurrentTextSize;
    }

    public void setCurrentTextSize(float currentTextSize) {
        CurrentTextSize = currentTextSize;
    }

    public static Lyric getmLyric() {
        return mLyric;
    }

    public void setmLyric(Lyric mLyric) {
        LyricView.mLyric = mLyric;
    }

    public Paint getCurrentPaint() {
        return CurrentPaint;
    }

    public void setCurrentPaint(Paint currentPaint) {
        CurrentPaint = currentPaint;
    }

    public List<Sentence> getSentencelist() {
        return Sentencelist;
    }

    public void setSentencelist(List<Sentence> sentencelist) {
        Sentencelist = sentencelist;
    }

    public int getNotCurrentPaintColor() {
        return notCurrentPaintColor;
    }

    public void setNotCurrentPaintColor(int notCurrentPaintColor) {
        this.notCurrentPaintColor = notCurrentPaintColor;
    }

    public int getCurrentPaintColor() {
        return CurrentPaintColor;
    }

    public void setCurrentPaintColor(int currrentPaintColor) {
        CurrentPaintColor = currrentPaintColor;
    }

    public Typeface getTexttypeface() {
        return Texttypeface;
    }

    public void setTexttypeface(Typeface texttypeface) {
        Texttypeface = texttypeface;
    }

    public int getBrackgroundcolor() {
        return brackgroundcolor;
    }

    public void setBrackgroundcolor(int brackgroundcolor) {
        this.brackgroundcolor = brackgroundcolor;
    }

    public int getTextHeight() {
        return TextHeight;
    }

    public void setTextHeight(int textHeight) {
        TextHeight = textHeight;
    }

    public LyricView(Context context) {
        super(context);
        init();
    }

    public LyricView(Context context, AttributeSet attr) {
        super(context, attr);
        init();
    }

    public LyricView(Context context, AttributeSet attr, int i) {
        super(context, attr, i);
        init();
    }

    private void init() {
        setFocusable(true);

        // Non highlighted
        NotCurrentPaint = new Paint();
        NotCurrentPaint.setAntiAlias(true);

        NotCurrentPaint.setTextAlign(Paint.Align.CENTER);

        // highlighted Current Lyric
        CurrentPaint = new Paint();
        CurrentPaint.setAntiAlias(true);

        CurrentPaint.setTextAlign(Paint.Align.CENTER);

    }

    protected void onDraw(Canvas canvas) {
        super.onDraw(canvas);
        canvas.drawColor(brackgroundcolor);
        NotCurrentPaint.setColor(notCurrentPaintColor);
        CurrentPaint.setColor(CurrentPaintColor);

        NotCurrentPaint.setTextSize(lrcTextSize);
        NotCurrentPaint.setTypeface(Texttypeface);

        CurrentPaint.setTextSize(CurrentTextSize);
        CurrentPaint.setTypeface(CurrentTexttypeface);

        if (index == -1)
            return;

        float plus = currentDunringTime == 0 ? 30
                : 30
                        + (((float) currentTime - (float) sentenctTime) / (float) currentDunringTime)
                        * (float) 30;

        // Scroll up to this is based on the length of time the lyrics to
        // rolling, the overall shift
        canvas.translate(0, -plus);
        // First draw the current line, then draw the front and the back of his,
        // so as to maintain the current line in the middle of the position
        try {
            if (Sentencelist == null)
                return;
            if (Sentencelist.get(index) == null)
                return;
            canvas.drawText(Sentencelist.get(index).getContent(), width / 2,
                    height / 2, CurrentPaint);
            float tempY = height / 2;
            // Draw the sentence before the sentence
            for (int i = index - 1; i >= 0; i--) {
                // Goes up
                tempY = tempY - TextHeight;
                if (tempY < 0) {
                    break;
                }
                canvas.drawText(Sentencelist.get(i).getContent(), width / 2,
                        tempY, NotCurrentPaint);
            }

            tempY = height / 2;
            // Draw the sentence after sentence
            for (int i = index + 1; i < Sentencelist.size(); i++) {
                // Goes down
                tempY = tempY + TextHeight;
                if (tempY > height) {
                    break;
                }
                canvas.drawText(Sentencelist.get(i).getContent(), width / 2,
                        tempY, NotCurrentPaint);
            }
        } catch (Exception ex) {
            ex.printStackTrace();
        }

    }

    protected void onSizeChanged(int w, int h, int ow, int oh) {
        super.onSizeChanged(w, h, ow, oh);
        width = w; // remember the center of the screen
        height = h;
        // middleY = h * 0.5f;
    }

    //
    /**
     * @param time
     *            The time axis current lyrics
     * @return null
     */
    public void updateIndex(long time) {

        this.currentTime = time;
        if (null == mLyric)
            return;
        index = mLyric.getNowSentenceIndex(time);
        if (index != -1) {
            if (Sentencelist == null)
                return;
            Sentence sen = Sentencelist.get(index);
            sentenctTime = sen.getFromTime();
            currentDunringTime = sen.getDuring();
        }
    }

}
