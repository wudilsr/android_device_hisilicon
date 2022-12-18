package com.hisilicon.multiscreen.server.speech;

import java.util.ArrayList;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;
import com.hisilicon.multiscreen.server.R;

/**
 * the adapter file for ListView，used for the display items
 * 
 */
public class SpeechAdapter extends BaseAdapter
{
    private Context mContext;
    private ArrayList<SpeechContent> mContentList;
    private static final int REQUEST_ITEM = 0;
    private static final int RESPONSE_ITEM = 1;

    public SpeechAdapter(Context context, ArrayList<SpeechContent> list)
    {
        this.mContext = context;
        this.mContentList = list;
    }

    public int getCount()
    {
        return mContentList.size();
    }

    public Object getItem(int position)
    {
        return mContentList.get(position);
    }

    public long getItemId(int position)
    {
        return position;
    }

    public int getItemViewType(int position)
    {
        return mContentList.get(position).getContentType().ordinal();
    }

    public int getViewTypeCount()
    {
        return ContentType.values().length;
    }

    public View getView(int position, View convertView, ViewGroup parent)
    {
        LayoutInflater mInflater = LayoutInflater.from(mContext);
        int type = getItemViewType(position);
        TextView textView = null;
        if (convertView == null)
        {
            switch (type)
            {
                case REQUEST_ITEM:
                {
                    convertView = mInflater.inflate(R.layout.speech_request, null);
                    textView = (TextView) convertView
                            .findViewById(R.id.request_messagedetail_row_text);
                    break;
                }
                case RESPONSE_ITEM:
                {
                    convertView = mInflater.inflate(R.layout.speech_response, null);
                    textView = (TextView) convertView
                            .findViewById(R.id.response_messagedetail_row_text);
                    break;
                }
            }
        }
        else
        {
            switch (type)
            {
                case REQUEST_ITEM:
                {
                    textView = (TextView) convertView
                            .findViewById(R.id.request_messagedetail_row_text);
                    break;
                }
                case RESPONSE_ITEM:
                {
                    textView = (TextView) convertView
                            .findViewById(R.id.response_messagedetail_row_text);
                    break;
                }
            }
        }
        textView.setText(mContentList.get(position).getContent());
        return convertView;
    }

}
