package com.hisilicon.multiscreen.server.speech.action;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;

import android.content.Context;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;

import com.hisilicon.multiscreen.server.speech.SpeechDialog;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.Weather;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSite;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;
import com.hisilicon.multiscreen.server.R;
import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * the Weather speech action ,used to get weather.<br>
 * 天气类，用于获取当天天气。
 *
 */
public class WeatherSpeechAction implements ISpeechAction
{

    private Context mContext;
    private Handler mHandler;

    @Override
    public String execute(Context context, Handler handler, SpeechResponseMessage msg)
    {

        if ((null == context) || (null == msg) || (null == handler))
        {
            return context.getString(R.string.fuction_not_support);
        }
        Weather weather = null;
        mContext = context;
        mHandler = handler;
        Semantic sm = msg.getSemantic();
        String city = null;
        if (sm != null)
        {
            weather = (Weather) sm.getSlots();
            city = weather.getLocation().getCityAddr();
        }
        else
        {
            return mContext.getString(R.string.fuction_not_support);
        }
        WeatherQuery wq = new WeatherQuery();
        String cityCode = wq.getCodeByCity(city);
        if (cityCode == null)
        {
            return mContext.getString(R.string.city_not_supported);
        }
        else
        {
            WeatherRequestThread wthrRq = new WeatherRequestThread(cityCode);
            wthrRq.start();
        }
        return null;
    }

    private class WeatherRequestThread extends Thread
    {
        private String mCityCode;

        public WeatherRequestThread(String cityCode)
        {
            mCityCode = cityCode;
        }

        @Override
        public void run()
        {
            String weatherUrl = "http://www.weather.com.cn/data/cityinfo/" + mCityCode + ".html";
            String weatherReturn = "";
            HttpGet httpRequest = new HttpGet(weatherUrl);
            // 获得HttpResponse对象
            HttpClient httpClient = new DefaultHttpClient();
            try
            {
                HttpResponse httpResponse = httpClient.execute(httpRequest);
                if (httpResponse.getStatusLine().getStatusCode() == HttpStatus.SC_OK)
                {
                    // 取得返回的数据
                    weatherReturn = EntityUtils.toString(httpResponse.getEntity());
                    LogTool.i("http response:" + weatherReturn);
                    Message msg = new Message();
                    msg.what = SpeechDialog.MSG_UPDATE_WEATHER_VIEW;
                    Bundle data = new Bundle();
                    data.putString("value", weatherReturn);
                    msg.setData(data);
                    mHandler.sendMessage(msg);
                }
                else
                {
                    Message msg = new Message();
                    msg.what = SpeechDialog.MSG_UPDATE_WEATHER_VIEW;
                    Bundle data = new Bundle();
                    data.putString("value", mContext.getString(R.string.obtain_weather_failed));
                    msg.setData(data);
                    mHandler.sendMessage(msg);
                }
            }
            catch (Exception e)
            {
                e.printStackTrace();
                Message msg = new Message();
                Bundle data = new Bundle();
                data.putString("value", mContext.getString(R.string.obtain_weather_net_failed));
                msg.setData(data);
                mHandler.sendMessage(msg);
            }
        }
    };

}
