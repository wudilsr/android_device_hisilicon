package com.hisilicon.multiscreen.server.speech;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import org.apache.http.HttpResponse;
import org.apache.http.HttpStatus;
import org.apache.http.client.HttpClient;
import org.apache.http.client.methods.HttpGet;
import org.apache.http.impl.client.DefaultHttpClient;
import org.apache.http.util.EntityUtils;
import org.json.JSONException;
import org.json.JSONObject;

import com.hisilicon.multiscreen.server.R;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;
import com.hisilicon.multiscreen.protocol.utils.PronounceCoverter;
import com.hisilicon.multiscreen.server.speech.action.ISpeechAction;
import com.hisilicon.multiscreen.server.speech.action.SpeechActionFactory;
import com.hisilicon.multiscreen.server.speech.action.WeatherQuery;
import com.hisilicon.multiscreen.server.speech.responsemessage.App;
import com.hisilicon.multiscreen.server.speech.responsemessage.SemanticSlot;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.VOD;
import com.hisilicon.multiscreen.server.speech.responsemessage.Weather;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSearch;
import com.hisilicon.multiscreen.server.speech.responsemessage.WebSite;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Answer;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.ResponseCode;

import android.R.integer;
import android.app.Dialog;
import android.app.SearchManager;
import android.content.ActivityNotFoundException;
import android.content.BroadcastReceiver;
import android.content.ComponentName;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;
import android.content.DialogInterface.OnDismissListener;
import android.content.DialogInterface.OnShowListener;
import android.content.Intent;
import android.content.IntentFilter;
import android.content.pm.ResolveInfo;
import android.media.AudioManager;
import android.net.Uri;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.Gravity;
import android.view.KeyEvent;
import android.view.View;
import android.view.Window;
import android.view.WindowManager;
import android.widget.BaseAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.ProgressBar;

public class SpeechDialog extends Dialog
{
    private static final int RECOGNIZE_ERROR_RESULT_TYPE = 0;

    private static final int RECOGNIZE_CORRECT_RESULT_TYPE = 1;

    // back key for dismiss dialog
    public static final int MSG_KEYDOWN_BACK = 0x200;

    // msg code for update speech view.
    public static final int MSG_UPDATE_SPEECH_VIEW = 0x210;

    // msg code for update weather view.
    public static final int MSG_UPDATE_WEATHER_VIEW = 0x220;

    public static final int MSG_DIALOG_TIMEOUT = 0x230;

    public static final int MSG_SPEECH_ERROR = 0x240;

    public static final int MSG_SPEECH_DIALOG_DISMISS = 0x250;

    public static final int DIALOG_RESULT_SHOW_DURATION = 40000;

    public static final int DIALOG_SHOW_TIMEOUT_DURATION = 62000;

    private Context mContext = null;

    private ListView speechListView;

    private ImageView voiceView = null;

    private ArrayList<SpeechContent> speechContentList;

    private ProgressBar progressBar;

    private ProgressBar speechWaveProgressBar;

    private AudioManager mAudioManager;

    private int mCurrentVolume = 0;

    private Handler mHandler = null;

    private SpeechAdapter mSpeechAdapter = null;

    private WeatherAdapter mWeatherAdapter = null;

    public void setHandler(Handler handler)
    {
        mHandler = handler;
    }

    public SpeechDialog(Context context)
    {
        super(context);
        mContext = context;
    }

    public SpeechDialog(Context context, boolean cancelable, OnCancelListener cancelListener)
    {
        super(context, cancelable, cancelListener);
        mContext = context;
    }

    public SpeechDialog(Context context, int theme, Handler handler)
    {
        super(context, theme);
        mContext = context;
        mHandler = handler;
    }

    @Override
    public void show()
    {
        // mute the voice,when start speaking
        mAudioManager = (AudioManager) (mContext.getSystemService(Context.AUDIO_SERVICE));
        if (isShowing())
        {
            mAudioManager.setStreamVolume(AudioManager.STREAM_SYSTEM, 0, 0);
        }

        if (mHandler.hasMessages(MSG_DIALOG_TIMEOUT))
        {
            mHandler.removeMessages(MSG_DIALOG_TIMEOUT);
        }
        mHandler.sendEmptyMessageDelayed(MSG_DIALOG_TIMEOUT, DIALOG_SHOW_TIMEOUT_DURATION);
        super.show();
    }

    @Override
    public boolean onKeyDown(int keyCode, KeyEvent event)
    {
        switch (keyCode)
        {
            case KeyEvent.KEYCODE_BACK:
            {
                mHandler.sendEmptyMessage(MSG_KEYDOWN_BACK);
                return true;
            }

            default:
                break;
        }
        return super.onKeyDown(keyCode, event);
    }

    @Override
    protected void onCreate(Bundle savedInstanceState)
    {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.speech_main);
        int marginRight = 0;
        Window window = getWindow();
        WindowManager.LayoutParams wmlp = window.getAttributes();
        wmlp.gravity = Gravity.RIGHT;
        wmlp.x = marginRight;
        window.setAttributes(wmlp);

        speechListView = (ListView) this.findViewById(R.id.speech_listview);
        voiceView = (ImageView) findViewById(R.id.imageView1);
        progressBar = (ProgressBar) findViewById(R.id.progressbar);
        speechWaveProgressBar = (ProgressBar) findViewById(R.id.progressbar_wave);
        speechWaveProgressBar.setProgress(30);
        speechContentList = new ArrayList<SpeechContent>();
        mSpeechAdapter = new SpeechAdapter(mContext, speechContentList);
        speechListView.setAdapter(mSpeechAdapter);

        addDialogListener();
    }

    public void updateSpeechAdapter()
    {
        speechListView.setAdapter(mSpeechAdapter);
        mSpeechAdapter.notifyDataSetChanged();
    }

    public void dealMscRespMsg(String result, int type)
    {
        // when receive result resume the volume
        mAudioManager.setStreamVolume(AudioManager.STREAM_SYSTEM, mCurrentVolume, 0);

        if (mHandler.hasMessages(MSG_DIALOG_TIMEOUT))
        {
            mHandler.removeMessages(MSG_DIALOG_TIMEOUT);
        }
        mHandler.sendEmptyMessageDelayed(MSG_DIALOG_TIMEOUT, DIALOG_RESULT_SHOW_DURATION);

        switch (type)
        {
            case RECOGNIZE_CORRECT_RESULT_TYPE:
            {
                dealRecogizeCorrectResult(result);
                break;
            }
            case RECOGNIZE_ERROR_RESULT_TYPE:
            {
                dealRecogizeErrorResult(result);
                break;
            }
            default:
            {
                LogTool.e("unknow speech result type");
                break;
            }
        }
    }

    public void updateWeatherData(String msgValue)
    {
        String result;
        try
        {
            JSONObject joReturn = new JSONObject(msgValue);
            JSONObject jo = joReturn.getJSONObject("weatherinfo");
            LogTool.i("http return:" + jo.toString());
            result =
                jo.getString("city") + " " + jo.getString("temp2") + "/" + jo.getString("temp1")
                    + " " + jo.getString("weather");
            LogTool.i(result);
            speechWaveProgressBar.setProgress(0);
            SpeechContent content = new SpeechContent();
            content.setContent(jo.toString());
            content.setContentType(ContentType.RESPONSE);
            content.setServiceType(ServiceType.WEATHER);
            speechContentList.add(content);
            mWeatherAdapter = new WeatherAdapter(mContext, speechContentList);
            speechListView.setAdapter(mWeatherAdapter);
            mSpeechAdapter.notifyDataSetChanged();
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
            speechWaveProgressBar.setProgress(0);
            SpeechContent content = new SpeechContent();
            content.setContent(mContext.getString(R.string.weather_prase_failed));
            content.setContentType(ContentType.RESPONSE);
            speechContentList.add(content);
            speechListView.setAdapter(mWeatherAdapter);
            mSpeechAdapter.notifyDataSetChanged();
        }
    }

    private void addDialogListener()
    {
        setOnShowListener(new OnShowListener()
        {
            @Override
            public void onShow(DialogInterface arg0)
            {
                mCurrentVolume = mAudioManager.getStreamVolume(AudioManager.STREAM_SYSTEM);
                mAudioManager.setStreamVolume(AudioManager.STREAM_SYSTEM, 0, 0);
            }
        });

        setOnDismissListener(new OnDismissListener()
        {

            @Override
            public void onDismiss(DialogInterface arg0)
            {
                LogTool.d("");
                if ((speechContentList != null) && (mHandler != null))
                {
                    speechContentList.clear();
                    mHandler.sendEmptyMessage(MSG_UPDATE_SPEECH_VIEW);
                }
                // when dialog dismiss resume voices.
                mAudioManager.setStreamVolume(AudioManager.STREAM_SYSTEM, mCurrentVolume, 0);
                if (mHandler.hasMessages(MSG_DIALOG_TIMEOUT))
                {
                    mHandler.removeMessages(MSG_DIALOG_TIMEOUT);
                }
            }
        });
    }

    private void dealRecogizeErrorResult(String error)
    {
        /* update request content */
        SpeechContent originContent = new SpeechContent();
        originContent.setContent(error);
        originContent.setContentType(ContentType.REQUEST);
        LogTool.i("the origin error result is:" + error);
        if (speechContentList == null)
        {
            speechContentList = new ArrayList<SpeechContent>();
        }
        speechContentList.clear();
        speechContentList.add(originContent);

        SpeechContent responseContent = new SpeechContent();

        String responseStr = mContext.getString(R.string.recongize_error_response);

        mSpeechAdapter = new SpeechAdapter(mContext, speechContentList);
        responseContent.setContent(responseStr);
        responseContent.setContentType(ContentType.RESPONSE);
        speechContentList.add(responseContent);
        mHandler.sendEmptyMessage(MSG_UPDATE_SPEECH_VIEW);
    }

    private void dealRecogizeCorrectResult(String resultJson)
    {
        SpeechResponseMessage respMsg = null;
        try
        {
            JSONObject jo = new JSONObject(resultJson);
            respMsg = new SpeechResponseMessage(jo);
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }

        if (respMsg == null)
        {
            LogTool.w("SpeechResponseMessage is null.");
            return;
        }

        /* update request content */
        SpeechContent originContent = new SpeechContent();
        originContent.setContent(respMsg.getOriginText());
        originContent.setContentType(ContentType.REQUEST);
        LogTool.i("the origin text is:" + respMsg.getOriginText());
        speechContentList.clear();
        speechContentList.add(originContent);

        SpeechContent responseContent = new SpeechContent();

        String responseStr = null;

        if (ResponseCode.SUCCESS != respMsg.getResponseCode())
        {
            // not according to slot
            LogTool.i("not accord to semantic slot");
            responseStr = mContext.getString(R.string.fuction_not_support);
        }

        Answer asr = respMsg.getAnswer();
        /* do action after UI refresh */
        SpeechActionFactory speechAction = new SpeechActionFactory();
        ISpeechAction ac = speechAction.getSpeechAction(respMsg);

        if (null != asr)
        {
            // smart faq
            LogTool.i("the faq answer is:" + asr.getText());
            responseStr = asr.getText();
        }

        if ((asr == null) && (null == ac))
        {
            // not support service
            LogTool.i("not support service ");
            responseStr = mContext.getString(R.string.fuction_not_support);
        }

        if ((asr == null) && (ac != null))
        {
            // not faq,but other support service need execute action
            String ret = ac.execute(mContext, mHandler, respMsg);
            if (ret != null)
            {
                // support service return some tips
                LogTool.i("support service return some tips ");
                responseStr = ret;
            }
            LogTool.i("support service do action ");
        }

        if (responseStr != null)
        {
            // has response content update response msg and ui
            LogTool.i("response content is  " + responseStr);
            mSpeechAdapter = new SpeechAdapter(mContext, speechContentList);
            responseContent.setContent(responseStr);
            responseContent.setContentType(ContentType.RESPONSE);
            speechContentList.add(responseContent);
            mHandler.sendEmptyMessage(MSG_UPDATE_SPEECH_VIEW);
        }

    }
}
