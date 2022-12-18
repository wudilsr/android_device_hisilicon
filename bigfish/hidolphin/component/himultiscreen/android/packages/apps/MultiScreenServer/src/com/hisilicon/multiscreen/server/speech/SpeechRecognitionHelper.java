package com.hisilicon.multiscreen.server.speech;

import java.io.File;
import java.io.FileOutputStream;
import java.io.FilenameFilter;
import org.json.JSONException;
import org.json.JSONObject;

import android.app.Activity;
import android.content.Context;
import android.content.Intent;
import android.os.Bundle;
import android.util.Log;
import android.widget.ImageView;

import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.MultiScreenIntentAction;

import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.VOD;
import com.iflytek.cloud.ErrorCode;
import com.iflytek.cloud.InitListener;
import com.iflytek.cloud.SpeechConstant;
import com.iflytek.cloud.SpeechError;
import com.iflytek.cloud.SpeechUnderstander;
import com.iflytek.cloud.SpeechUnderstanderListener;
import com.iflytek.cloud.SpeechUtility;
import com.iflytek.cloud.UnderstanderResult;
import com.hisilicon.multiscreen.server.R;
/**
 * Helper for speech recognition.<br>
 * CN:语音识别辅助类。<br>
 */
public class SpeechRecognitionHelper
{
    public static final String FLY_APP_ID = "538d83c8";

    private SpeechUnderstander mSpeechUnderstander = null;

    private static final String AudioName = "/sdcard/love.raw";

    private Context mContext = null;

    FileOutputStream fos = null;

    /**
     * 初始化监听器（语音到语义）。
     */
    private InitListener speechUnderstanderListener = new InitListener()
    {
        @Override
        public void onInit(int code)
        {
            LogTool.d("speechUnderstanderListener init() code = " + code);
            if (code == ErrorCode.SUCCESS)
            {
                LogTool.i("error code success");
            }
        }
    };

    /**
     * 识别回调。
     */
    public SpeechUnderstanderListener mRecognizerListener = new SpeechUnderstanderListener()
    {

        @Override
        public void onResult(final UnderstanderResult result)
        {
            LogTool.d("");
            LogTool.d(result.getResultString());
            try
            {
                JSONObject jo = new JSONObject(result.getResultString());
                SpeechResponseMessage respMsg = new SpeechResponseMessage(jo);
                Intent intent = new Intent();
                intent.setAction(MultiScreenIntentAction.SPEECH_RESULT);
                Bundle bundle = new Bundle();
                bundle.putSerializable("ResponseMessage",respMsg);

                intent.putExtras(bundle);
                mContext.sendBroadcast(intent);
            }
            catch (JSONException e)
            {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

        }
        @Override
        public void onVolumeChanged(int v)
        {
            LogTool.d("onVolumeChanged：" + v);
            Intent intent = new Intent();
            intent.setAction(MultiScreenIntentAction.SPEECH_VOLUME);
            Bundle bundle = new Bundle();
            bundle.putInt("volumeChanged",v);
            intent.putExtras(bundle);
            mContext.sendBroadcast(intent);
        }

        @Override
        public void onEndOfSpeech()
        {
            LogTool.d("onEndOfSpeech");
            Intent intent = new Intent();
            intent.setAction(MultiScreenIntentAction.SPEECH_STOP);
            mContext.sendBroadcast(intent);
        }

        @Override
        public void onBeginOfSpeech()
        {
            LogTool.d("onBeginOfSpeech");
        }

        @Override
        public void onError(SpeechError error)
        {
            LogTool.d("onError Code：" + error.getErrorCode());
        }

        @Override
        public void onEvent(int eventType, int arg1, int agr2, String msg)
        {
        }
    };



    /**
     * Run speech recognition activity.<br>
     * CN: 启动语音识别。
     */
    public void InitSpeechUnderStander(Context context)
    {
        mContext = context;
        loginServer(context);
        InitUnderStander(context);
    }

    public void loginServer(Context context)
    {
        SpeechUtility.createUtility(context, SpeechConstant.APPID + "=" + FLY_APP_ID);
    }

    public void startUnderStander()
    {
        // loginServer(context);
        LogTool.d("");
        if (mSpeechUnderstander.isUnderstanding())
        {
            // 开始前检查状态
            mSpeechUnderstander.stopUnderstanding();
        }
        else
        {
            mSpeechUnderstander.startUnderstanding(mRecognizerListener);
        }

        try
        {
            File file = new File(AudioName);
            if (file.exists())
            {
                file.delete();
            }
            fos = new FileOutputStream(file);
        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    public void writeAudioDate(byte[] audioDate)
    {
        if (mSpeechUnderstander != null)
        {
            boolean ret = mSpeechUnderstander.writeAudio(audioDate, 0, audioDate.length);
            LogTool.d("write audio date " + ret);
            try
            {
                fos.write(audioDate, 0, audioDate.length);
            }
            catch (Exception e)
            {
                // TODO: handle exception
            }
        }
    }

    public void stopUnderStander()
    {
        LogTool.d("");
        if (mSpeechUnderstander != null)
        {
            mSpeechUnderstander.stopUnderstanding();
        }
        try
        {
            fos.close();// 关闭写入流

        }
        catch (Exception e)
        {
            e.printStackTrace();
        }
    }

    private void InitUnderStander(Context context)
    {
        mSpeechUnderstander = SpeechUnderstander.createUnderstander(context,
                speechUnderstanderListener);
        mSpeechUnderstander.setParameter(SpeechConstant.DOMAIN, "iat");
        mSpeechUnderstander.setParameter(SpeechConstant.LANGUAGE, "zh_cn");
        mSpeechUnderstander.setParameter(SpeechConstant.AUDIO_SOURCE, "-1");
        mSpeechUnderstander.setParameter(SpeechConstant.ACCENT, "mandarin");
        mSpeechUnderstander.setParameter(SpeechConstant.VAD_BOS, "10000");
        mSpeechUnderstander.setParameter(SpeechConstant.VAD_EOS, "10000");
    }

}
