package com.hisilicon.multiscreen.server.speech;

import java.util.ArrayList;
import java.lang.reflect.Field;

import org.json.JSONObject;

import android.content.Context;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.TextView;
import com.hisilicon.multiscreen.server.R;

/**
 *
 * the adapter file for ListView，used to display the weather
 *
 *
 */
public class WeatherAdapter extends BaseAdapter
{
    private static final String NIGHT_VIEW_TAG = "img2";
    private static final String DAY_VIEW_TAG = "img1";
    private static final String WEATHER_CITY_TAG = "city";
    private static final String DAY_TEMPERATURE_TAG = "temp1";
    private static final String NIGHT_TEMPERATURE_TAG = "temp2";
    private static final String WEATHER_TAG = "weather";

    private Context mContext;
    private ArrayList<SpeechContent> mContentList;

    public WeatherAdapter(Context context, ArrayList<SpeechContent> list)
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
        return mContentList.size();
    }

    public View getView(int position, View convertView, ViewGroup parent)
    {
        LayoutInflater mInflater = LayoutInflater.from(mContext);
        int type = getItemViewType(position);
        TextView textView = null;
        ImageView nightView = null;
        ImageView dayView = null;
        TextView weatherTem = null;
        TextView weatherMessageTextView = null;
        try
        {
            if (convertView == null)
            {
                switch (type)
                {
                    case 0:
                    {
                        convertView = mInflater.inflate(R.layout.speech_request, null);
                        textView = (TextView) convertView
                                .findViewById(R.id.request_messagedetail_row_text);
                        textView.setText(mContentList.get(position).getContent());
                        break;
                    }
                    case 1:
                    {
                        convertView = mInflater.inflate(R.layout.speech_weather_response, null);
                        textView = (TextView) convertView
                                .findViewById(R.id.response_messagedetail_row_text);
                        nightView = (ImageView) convertView.findViewById(R.id.night_image);
                        dayView = (ImageView) convertView.findViewById(R.id.day_image);
                        weatherTem = (TextView) convertView.findViewById(R.id.weather);
                        weatherMessageTextView = (TextView) convertView
                                .findViewById(R.id.weather_message);
                        JSONObject jo = new JSONObject(mContentList.get(position).getContent());
                        nightView.setImageResource(getWeatherView(jo.getString(NIGHT_VIEW_TAG)));
                        dayView.setImageResource(getWeatherView(jo.getString(DAY_VIEW_TAG)));
                        textView.setText(jo.getString(WEATHER_CITY_TAG));
                        weatherTem.setText(jo.getString(NIGHT_TEMPERATURE_TAG) + "/"
                                + jo.getString(DAY_TEMPERATURE_TAG));
                        weatherMessageTextView.setText(jo.getString(WEATHER_TAG));
                        break;
                    }
                }
            }
            else
            {
                switch (type)
                {
                    case 0:
                    {
                        textView = (TextView) convertView
                                .findViewById(R.id.request_messagedetail_row_text);
                        textView.setText(mContentList.get(position).getContent());
                        break;
                    }
                    case 1:
                    {
                        textView = (TextView) convertView
                                .findViewById(R.id.response_messagedetail_row_text);
                        nightView = (ImageView) convertView.findViewById(R.id.night_image);
                        dayView = (ImageView) convertView.findViewById(R.id.day_image);
                        weatherTem = (TextView) convertView.findViewById(R.id.weather);
                        JSONObject jo = new JSONObject(mContentList.get(position).getContent());
                        nightView.setImageResource(getWeatherView(jo.getString(NIGHT_VIEW_TAG)));
                        dayView.setImageResource(getWeatherView(jo.getString(DAY_VIEW_TAG)));
                        textView.setText(jo.getString(WEATHER_CITY_TAG));
                        weatherTem.setText(jo.getString(NIGHT_TEMPERATURE_TAG) + "/"
                                + jo.getString(DAY_TEMPERATURE_TAG));
                        weatherMessageTextView.setText(jo.getString(WEATHER_TAG));
                        break;
                    }
                }
            }
        }
        catch (Exception e)
        {
            ;
        }
        return convertView;
    }

    private int getWeatherView(String str)
    {
        R.drawable drawables = new R.drawable();
        int resId = R.drawable.d0;
        if (str == null)
        {
            return resId;
        }
        str = str.substring(0, str.indexOf('.'));
        try
        {

            Field field = R.drawable.class.getField(str);
            resId = (Integer) field.get(drawables);
        }
        catch (SecurityException e)
        {
            e.printStackTrace();
        }
        catch (NoSuchFieldException e)
        {
            e.printStackTrace();
        }
        catch (IllegalArgumentException e)
        {
            e.printStackTrace();
        }
        catch (IllegalAccessException e)
        {
            e.printStackTrace();
        }
        return resId;
    }
}
