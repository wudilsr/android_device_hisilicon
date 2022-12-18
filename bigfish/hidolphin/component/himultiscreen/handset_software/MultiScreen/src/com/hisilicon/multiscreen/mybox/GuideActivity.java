package com.hisilicon.multiscreen.mybox;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.graphics.Color;
import android.os.Bundle;
import android.view.Display;
import android.view.GestureDetector;
import android.view.GestureDetector.SimpleOnGestureListener;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.widget.BaseAdapter;
import android.widget.Gallery;
import android.widget.Gallery.LayoutParams;
import android.widget.ImageView;
import android.widget.RelativeLayout;
import android.widget.TextView;

import com.hisilicon.dlna.dmc.gui.activity.AppPreference;
import com.hisilicon.multiscreen.protocol.utils.ImageResourseDecodeUtils;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * Activity of guide page.<br>
 * CN:引导页面。
 */
public class GuideActivity extends Activity
{
    /**
     * Gallery
     */
    private GuideGallery mGallery = null;

    private int mDisplayWidth = 0;

    private int mDisplayHeight = 0;

    private GestureDetector mGestureDetector;

    private Integer[] mImage = new Integer[]
    {
        // R.drawable.guide_1,R.drawable.guide_2,
        R.drawable.guide_3, R.drawable.guide_4 };

    private String[] guideMsgArray;

    private int guideTxtColor = Color.rgb(240, 101, 60);

    @Override
    public void onCreate(Bundle savedInstanceState)
    {
        LogTool.d("onCreate");
        super.onCreate(savedInstanceState);
        initView();
        AppPreference.setAppAlreadyUse();
        guideMsgArray = getResources().getStringArray(R.array.guide_message_array);
    }

    @Override
    public void onResume()
    {
        LogTool.d("onResume");
        super.onResume();
    }

    @Override
    public void onDestroy()
    {
        LogTool.d("onDestroy");
        super.onDestroy();

    }

    /**
     * To provide the data for gallery object.<br>
     * CN:Gallery对象的适配器。
     */
    private class ImageAdapter extends BaseAdapter
    {
        private Context mContext;

        public ImageAdapter(Context c)
        {
            mContext = c;
        }

        @Override
        public int getCount()
        {
            return mImage.length;
        }

        @Override
        public Object getItem(int position)
        {
            return position;
        }

        @Override
        public long getItemId(int position)
        {
            return position;
        }

        @Override
        public View getView(final int position, View convertView, ViewGroup parent)
        {
            RelativeLayout layout = new RelativeLayout(GuideActivity.this);
            ImageView i = new ImageView(mContext);
            i.setImageBitmap(ImageResourseDecodeUtils.decodeSampledBitmapFromResource(
                getResources(), mImage[position], mDisplayWidth, mDisplayHeight));
            i.setScaleType(ImageView.ScaleType.FIT_XY);
            i.setLayoutParams(new Gallery.LayoutParams(LayoutParams.FILL_PARENT,
                LayoutParams.FILL_PARENT));
            layout.addView(i);
            TextView txt = new TextView(GuideActivity.this);
            try
            {
                txt.setText(guideMsgArray[position]);
            }
            catch (Exception e)
            {
                e.printStackTrace();
            }
            android.widget.RelativeLayout.LayoutParams params =
                new android.widget.RelativeLayout.LayoutParams(LayoutParams.WRAP_CONTENT,
                    LayoutParams.WRAP_CONTENT);
            params.addRule(RelativeLayout.CENTER_HORIZONTAL);
            params.addRule(RelativeLayout.ALIGN_PARENT_BOTTOM);
            txt.setPadding(20, 0, 20, 50);
            txt.setTextColor(guideTxtColor);
            txt.setGravity(Gravity.CENTER_HORIZONTAL);
            txt.setLayoutParams(params);
            txt.setTextSize(17);
            layout.addView(txt);
            // layout.setLayoutParams(params);
            return layout;
        }
    }

    @Override
    public boolean onTouchEvent(MotionEvent event)
    {

        return mGestureDetector.onTouchEvent(event);

    }

    @Override
    public boolean dispatchTouchEvent(MotionEvent ev)
    {

        mGestureDetector.onTouchEvent(ev);

        return super.dispatchTouchEvent(ev);

    }

    public class MyGesture extends SimpleOnGestureListener
    {

        public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY)
        {

            if (e1.getX() - e2.getX() > 0)
            {
                if (mGallery.getSelectedItemPosition() == mGallery.getCount() - 1)
                {
                    // if (AppPreference.isAppFirstUse()) {
                    // AppPreference.setAppAlreadyUse();

                    Intent intent = new Intent(GuideActivity.this, DeviceDiscoveryActivity.class);
                    startActivity(intent);
                    GuideActivity.this.finish();
                    // } else {
                    // GuideActivity.this.finish();
                    // }
                }
            }

            return false;

        }

    }

    private void initView()
    {
        WindowManager windowManager = getWindowManager();

        Display display = windowManager.getDefaultDisplay();

        mDisplayWidth = display.getWidth();

        mDisplayHeight = display.getHeight();

        setContentView(R.layout.guide);

        mGallery = (GuideGallery) findViewById(R.id.gallery);
        mGallery.setAdapter(new ImageAdapter(this));

        mGestureDetector = new GestureDetector(new MyGesture());
    }

    @Override
    public void onBackPressed()
    {
        int position = mGallery.getSelectedItemPosition() - 1;
        if (position >= 0)
        {
            mGallery.setSelection(position);
            mGallery.onKeyLeft();
            return;
        }
        super.onBackPressed();
    }

}