package com.hisilicon.multiscreen.server.speech.action;

import android.content.ActivityNotFoundException;
import android.content.Context;
import android.content.Intent;
import android.net.Uri;
import android.os.Handler;

import com.hisilicon.multiscreen.server.speech.SpeechDialog;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;
import com.hisilicon.multiscreen.server.speech.responsemessage.VOD;
import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage.Semantic;
import com.hisilicon.multiscreen.server.R;
import com.hisilicon.multiscreen.protocol.utils.LogTool;
import com.hisilicon.multiscreen.protocol.utils.PronounceCoverter;

/**
 * the VOD speech action ,used to search video.<br>
 * 视频点播类，用于视频搜索。
 *
 */
public class VODSpeechAction implements ISpeechAction
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
        mContext = context;
        mHandler = handler;
        VOD vod = null;
        Semantic sm = msg.getSemantic();
        if (sm != null)
        {
            vod = (VOD) sm.getSlots();
        }
        LogTool.d("VOD info, channel=" + vod.getChannel() + ", keywords=" + vod.getKeywords()
                + ", actor=" + vod.getActor());
        String keyword = vod.getKeywords();
        if (keyword != null)
        {
            LogTool.d("keyword is " + keyword);
            return searchVideo(keyword);
        }
        else
        {
            return mContext.getString(R.string.fuction_not_support);
        }
    }

    /**
     * search video.<br>
     * CN:搜索视频。
     *
     * @param keyword -the name of video
     * @return null
     */
    private String searchVideo(String keyword)
    {
        String pinyin = PronounceCoverter.getInstance().getPingYin(keyword);
        String Data = "page=search&keyword=" + pinyin;
        LogTool.d("keyword " + Data);
        String ReturnMode = "0";
        Intent intent = new Intent();
        intent.setAction("moretv.action.applaunch"); // action 名称 必选
        intent.putExtra("Data", Data); // Date 透传字段，必选
        intent.putExtra("ReturnMode", ReturnMode); // ReturnMode 返回方式 0:
                                                   // 返回时退出MoreTV应用 1:
                                                   // 返回时返回MoreTV上层页面 非必选参数
        intent.addFlags(Intent.FLAG_ACTIVITY_CLEAR_TOP);
        intent.addFlags(Intent.FLAG_ACTIVITY_NEW_TASK);
        try
        {
            mContext.startActivity(intent);
        }
        catch (ActivityNotFoundException e)
        {
            e.printStackTrace();
            return mContext.getString(R.string.tv_cat_not_installed);
        }
        mHandler.sendEmptyMessage(SpeechDialog.MSG_SPEECH_DIALOG_DISMISS);
        return null;
    }
}
