package com.hisilicon.android.videoplayer.activity;
import android.view.View;
import android.widget.ImageView;
import android.widget.TextView;

import com.hisilicon.android.videoplayer.R;

public class ViewCache
{
    private View baseView;
    private TextView textView;
    private ImageView imageView;

    public ViewCache(View baseView)
    {
        this.baseView = baseView;
    }

    public TextView getTextView()
    {
        if (textView == null)
        {
            textView = (TextView) baseView.findViewById(R.id.tv_movie2nd_thumbnailitem);
        }

        return textView;
    }

    public ImageView getImageView()
    {
        if (imageView == null)
        {
            imageView = (ImageView) baseView.findViewById(R.id.iv_movie2nd_thumbnailitem);
        }

        return imageView;
    }
}
