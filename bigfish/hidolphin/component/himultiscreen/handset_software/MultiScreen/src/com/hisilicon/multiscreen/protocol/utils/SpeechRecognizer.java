package com.hisilicon.multiscreen.protocol.utils;
import android.app.Activity;
import android.content.Context;
import android.content.DialogInterface;
import android.content.DialogInterface.OnCancelListener;

import com.iflytek.cloud.InitListener;
import com.iflytek.cloud.RecognizerResult;
import com.iflytek.cloud.SpeechConstant;
import com.iflytek.cloud.SpeechError;
import com.iflytek.cloud.SpeechUtility;
import com.iflytek.cloud.ui.RecognizerDialog;
import com.iflytek.cloud.ui.RecognizerDialogListener;
/**
 * Helper for speech recognition.<br>
 */
public class SpeechRecognizer
{

    /**
     * Id for login recognize speech server.
     */
    private static final String FLY_APP_ID = "538d83c8";

    private static final int RECOGNIZE_ERROR_RESULT_TYPE = 0;

    private static final int RECOGNIZE_CORRECT_RESULT_TYPE = 1;


    public ISpeechMsgDealer mISpeechMsgDealer = null;

    /**
     * Speech result buffer.
     */
    public StringBuffer mSpeechResult = null;

    /**
     * Recognizer dialog.
     */
    private RecognizerDialog mRecognizerDialog = null;

    private InitListener mInitListener = new InitListener()
    {

        @Override
        public void onInit(int arg0)
        {
            LogTool.d("init arg " + arg0);
        }
    };

    private OnCancelListener mRecognizerCancelListener = new OnCancelListener()
    {

        @Override
        public void onCancel(DialogInterface arg0)
        {
            LogTool.d("");
            mISpeechMsgDealer.speakError("Cancel Dialog");
        }
    };
    /**
     * Recognizer dialog listener.
     */
    private RecognizerDialogListener mRecognizerDialogListener =
        new RecognizerDialogListener()
    {
        /**
         * recognizer return result callback.
         */
        public void onResult(RecognizerResult results, boolean isLast)
        {
            LogTool.d("");
                if (mSpeechResult != null)
                {
                    mSpeechResult.append(results.getResultString());
                }
                if ((mISpeechMsgDealer != null) && (isLast))
                {
                    LogTool.d("" + mSpeechResult.toString());
                mISpeechMsgDealer.pushSpeechInfo(mSpeechResult.toString(),
                    RECOGNIZE_CORRECT_RESULT_TYPE);
                    mSpeechResult = null;
                }
        }

        /**
         * recognizer error callback.
         */
        public void onError(SpeechError error)
        {
            LogTool.e(error.getPlainDescription(true));
            mISpeechMsgDealer.pushSpeechInfo(error.getErrorDescription(),
                RECOGNIZE_ERROR_RESULT_TYPE);
            // mISpeechMsgDealer.speakError(error.getPlainDescription(true));
            mRecognizerDialog.dismiss();
        }

    };

    /**
     * Set Speech dealer.
     * @param dealer
     */
    public void setSpeechDeal(ISpeechMsgDealer dealer)
    {
        mISpeechMsgDealer = dealer;
    }

    /**
     * Run speech recognition activity.<br>
     */
    public void run(Activity ownerActivity)
    {
        startRecognitionOnUiMode(ownerActivity);
    }

    /**
     * Login speech recognizer server.
     * @param context
     */
    public static void loginServer(Context context)
    {
        SpeechUtility.createUtility(context, SpeechConstant.APPID + "=" + FLY_APP_ID);
    }

    /**
     * Start speech recognition on ui mode.
     * @param ownerActivity
     */
    private void startRecognitionOnUiMode(Activity ownerActivity)
    {
        new Thread(new Runnable()
        {
            @Override
            public void run()
            {
                mISpeechMsgDealer.startSpeaking();
            }
        }).start();

        if (mSpeechResult != null)
        {
            mSpeechResult = null;
        }
        mSpeechResult = new StringBuffer();
        mRecognizerDialog = new RecognizerDialog(ownerActivity, mInitListener);
        // set speech recognizer domain
        mRecognizerDialog.setParameter(SpeechConstant.DOMAIN, "iat");
        mRecognizerDialog.setParameter(SpeechConstant.LANGUAGE, "zh_cn");
        mRecognizerDialog.setParameter(SpeechConstant.ACCENT, "mandarin");
        mRecognizerDialog.setParameter(SpeechConstant.NLP_VERSION, "2.0");
        mRecognizerDialog.setParameter(SpeechConstant.ASR_NBEST, "1");

        // set asr_sch to add speech understand func
        mRecognizerDialog.setParameter("asr_sch", "1");
        // set return result format
        mRecognizerDialog.setParameter("rst", "json");
        // register reconizer listener.
        mRecognizerDialog.setListener(mRecognizerDialogListener);
        mRecognizerDialog.setOnCancelListener(mRecognizerCancelListener);
        mRecognizerDialog.show();
    }
}
