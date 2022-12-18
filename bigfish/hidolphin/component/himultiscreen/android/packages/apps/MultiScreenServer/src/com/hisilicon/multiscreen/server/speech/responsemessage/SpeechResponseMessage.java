package com.hisilicon.multiscreen.server.speech.responsemessage;

import java.io.Serializable;

import org.json.JSONException;
import org.json.JSONObject;

import android.util.Log;

import com.hisilicon.multiscreen.protocol.utils.LogTool;

/**
 * The response message of speech.<br>
 * CN:语音返回信息。
 * @see Open Semantic Platform API Documents.pdf
 */
public class SpeechResponseMessage implements Serializable
{
    private static final long serialVersionUID = 1L;

    private static final String Tag = "SpeechResponseMessage";

    /* must fields */
    private ResponseCode mResponseCode;

    private String mOriginText;

    private String mService;

    private String mOperation;

    /* optional fields */
    private Error mError;

    private String mHistory;

    private Semantic mSemantic;

    private Data mData;

    private WebPage mWebPage;

    private Answer mAnswer;

    public SpeechResponseMessage(JSONObject jo)
    {
        // do NOT change the parse sequence, or will got wrong results

        /* must fields */
        try
        {
            mResponseCode = ResponseCode.values()[jo.getInt("rc")];
            mOriginText = jo.getString("text");
            mService = jo.getString("service");
            mOperation = jo.getString("operation");

            LogTool.i("response message, rc=" + mResponseCode + ", text=" + mOriginText
                + ", service=" + mService + ", operation=" + mOperation);
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }

        /* optional fields */
        try
        {
            mHistory = jo.getString("history");
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }

        if (mResponseCode != ResponseCode.SUCCESS)
        {
            JSONObject joError;
            try
            {
                joError = jo.getJSONObject("error");
                mError = new Error(joError);
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }
        }

        JSONObject joSemantic;
        try
        {
            joSemantic = jo.getJSONObject("semantic");
            if (joSemantic != null && mService != null)
            {
                mSemantic = new Semantic(joSemantic, mService);
            }
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }

        JSONObject joData;
        try
        {
            joData = jo.getJSONObject("data");
            if (joData != null)
            {
                mData = new Data(joData);
            }
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }

        JSONObject joWebPage;
        try
        {
            joWebPage = jo.getJSONObject("webPage");
            if (joWebPage != null)
            {
                mWebPage = new WebPage(joWebPage);
            }
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }

        JSONObject joAnswer;
        try
        {
            joAnswer = jo.getJSONObject("answer");
            if (joAnswer != null)
            {
                mAnswer = new Answer(joAnswer);
            }
        }
        catch (JSONException e)
        {
            LogTool.e(e.getMessage());
        }
    }

    public enum ResponseCode implements Serializable
    {
        SUCCESS, INVALID_REQUEST, INTERNAL_ERROR, SERVICE_FAIL, UNDERSTAND_FAIL
    }

    public class Error implements Serializable
    {
        private static final long serialVersionUID = 1L;

        private String mCode;

        private String mMessage;

        public Error(JSONObject jo)
        {
            /* must area */
            try
            {
                mCode = jo.getString("code");
            }
            catch (JSONException e)
            {
                // TODO Auto-generated catch block
                e.printStackTrace();
            }

            /* optional area */
            try
            {
                mMessage = jo.getString("message");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }
        };

        public String getCode()
        {
            return mCode;
        }

        public String getMessage()
        {
            return mMessage;
        }
    }

    public class Semantic implements Serializable
    {
        private static final long serialVersionUID = 1L;

        private String mNormalPrompt;

        private String mNormalPromptTts;

        private String mNoDataPrompt;

        private String mNoDataPromptTts;

        private SemanticSlot mSlots;

        public Semantic(JSONObject jo, String service)
        {
            JSONObject joSlots;
            /* must area */
            try
            {
                joSlots = jo.getJSONObject("slots");
                LogTool.i("service is:" + service);

                if (service.equals("app"))
                {
                    mSlots = new App(joSlots);
                }
                else if (service.equals("baike"))
                {
                    // baike return Answer directly, no semantic
                }
                else if (service.equals("calc"))
                {
                    // calc return Answer directly, no semantic
                }
                else if (service.equals("cookbook"))
                {
                    mSlots = new CookBook(joSlots);
                }
                else if (service.equals("datetime"))
                {
                    // datetime return Answer directly, no semantic
                }
                else if (service.equals("faq"))
                {
                    // FAQ return Answer directly, no semantic
                }
                else if (service.equals("flight"))
                {
                    mSlots = new Flight(joSlots);
                }
                else if (service.equals("hotel"))
                {
                    mSlots = new Hotel(joSlots);
                }
                else if (service.equals("map"))
                {
                    mSlots = new Map(joSlots);
                }
                else if (service.equals("music"))
                {
                    mSlots = new Music(joSlots);
                }
                else if (service.equals("radio"))
                {
                    mSlots = new Radio(joSlots);
                }
                else if (service.equals("restaurant"))
                {
                    mSlots = new Restaurant(joSlots);
                }
                else if (service.equals("schedule"))
                {
                    mSlots = new Schedule(joSlots);
                }
                else if (service.equals("stock"))
                {
                    mSlots = new Stock(joSlots);
                }
                else if (service.equals("train"))
                {
                    mSlots = new Train(joSlots);
                }
                else if (service.equals("translation"))
                {
                    mSlots = new Translation(joSlots);
                }
                else if (service.equals("tv"))
                {
                    mSlots = new TV(joSlots);
                }
                else if (service.equals("video"))
                {
                    mSlots = new VOD(joSlots);
                }
                else if (service.equals("weather"))
                {
                    mSlots = new Weather(joSlots);
                }
                else if (service.equals("websearch"))
                {
                    mSlots = new WebSearch(joSlots);
                }
                else if (service.equals("website"))
                {
                    mSlots = new WebSite(joSlots);
                }
                else if (service.equals("weibo"))
                {
                    mSlots = new Weibo(joSlots);
                }
                else
                {
                    LogTool.e("not supported service type");
                }
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }

            /* optional area */
            try
            {
                mNormalPrompt = jo.getString("normalPrompt");
                mNormalPromptTts = jo.getString("normalPromptTts");
                mNoDataPrompt = jo.getString("noDataPrompt");
                mNoDataPromptTts = jo.getString("noDataPromptTts");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }
        }

        public String getNormalPrompt()
        {
            return mNormalPrompt;
        }

        public String getNormalPromptTts()
        {
            return mNormalPromptTts;
        }

        public String getNoDataPrompt()
        {
            return mNoDataPrompt;
        }

        public String getNoDataPromptTts()
        {
            return mNoDataPromptTts;
        }

        public SemanticSlot getSlots()
        {
            return mSlots;
        }
    }

    public class Data implements Serializable
    {
        /**
         *
         */
        private static final long serialVersionUID = 1L;

        private String mHeader;

        private String mHeaderTts;

        public Data(JSONObject jo)
        {
            /* must area */
            // TODO: add Result parse code

            /* optional area */
            try
            {
                mHeader = jo.getString("header");
                mHeaderTts = jo.getString("headerTts");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }
        }

        public String getHeader()
        {
            return mHeader;
        }

        public String getHeaderTts()
        {
            return mHeaderTts;
        }
    }

    public class WebPage implements Serializable
    {
        private static final long serialVersionUID = 1L;

        private String mHeader;

        private String mHeaderTts;

        private String mUrl;

        public WebPage(JSONObject jo)
        {
            /* must area */
            try
            {
                mUrl = jo.getString("url");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }

            /* optional area */
            try
            {
                mHeader = jo.getString("header");
                mHeaderTts = jo.getString("headerTts");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }
        }

        public String getHeader()
        {
            return mHeader;
        }

        public String getHeaderTts()
        {
            return mHeaderTts;
        }

        public String getUrl()
        {
            return mUrl;
        }
    }

    public class Answer implements Serializable
    {
        private static final long serialVersionUID = 1L;

        private String mType;

        private String mText;

        private String mImgUrl;

        private String mImgDesc;

        private String mUrl;

        private String mUrlDesc;

        public Answer(JSONObject jo)
        {
            /* must area */
            try
            {
                mType = jo.getString("type");
                mText = jo.getString("text");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }

            /* optional area */
            try
            {
                mImgUrl = jo.getString("imgUrl");
                mImgDesc = jo.getString("imgDesc");
                mUrl = jo.getString("url");
                mUrlDesc = jo.getString("urlDesc");
            }
            catch (JSONException e)
            {
                LogTool.e(e.getMessage());
            }
        }

        public String getType()
        {
            return mType;
        }

        public String getText()
        {
            return mText;
        }

        public String getImgUrl()
        {
            return mImgUrl;
        }

        public String getImgDesc()
        {
            return mImgDesc;
        }

        public String getUrl()
        {
            return mUrl;
        }

        public String getUrlDesc()
        {
            return mUrlDesc;
        }
    }

    public ResponseCode getResponseCode()
    {
        return mResponseCode;
    }

    public String getOriginText()
    {
        return mOriginText;
    }

    public String getHistory()
    {
        return mHistory;
    }

    public String getService()
    {
        return mService;
    }

    public String getOperation()
    {
        return mOperation;
    }

    public Error getError()
    {
        return mError;
    }

    public Semantic getSemantic()
    {
        return mSemantic;
    }

    public Data getData()
    {
        return mData;
    }

    public WebPage getWebPage()
    {
        return mWebPage;
    }

    public Answer getAnswer()
    {
        return mAnswer;
    }
}
