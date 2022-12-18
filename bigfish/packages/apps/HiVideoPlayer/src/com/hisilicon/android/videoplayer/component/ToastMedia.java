package com.hisilicon.android.videoplayer.component;

import android.content.Context;
import android.view.Gravity;
import android.view.LayoutInflater;
import android.widget.LinearLayout;
import android.widget.TextView;
import android.widget.Toast;

import com.hisilicon.android.videoplayer.R;

public class ToastMedia extends Toast
{
    private static ToastMedia mToastMedia;

    private Context mContext;

    private TextView mTvToastMedia;

    private ToastMedia(Context pContext)
    {
        super(pContext);

        mContext = pContext;

        setDuration(LENGTH_SHORT);
        setGravity(Gravity.TOP | Gravity.LEFT, 25, 25);

        initView();
    }

    public static ToastMedia getInstance(Context pContext)
    {
        if (mToastMedia == null)
        {
            mToastMedia = new ToastMedia(pContext);
        }

        return mToastMedia;
    }

    private void initView()
    {
        LinearLayout _LayToastMedia =
            (LinearLayout) LayoutInflater.from(mContext).inflate(R.layout.toast_media, null);
        mTvToastMedia = (TextView) _LayToastMedia.findViewById(R.id.tvToastMedia);
        setView(_LayToastMedia);
    }

    @Override
    public void setText(int pResId)
    {
        setText(mContext.getString(pResId));
    }

    @Override
    public void setText(CharSequence pMsg)
    {
        mTvToastMedia.setText(pMsg);
    }
}
