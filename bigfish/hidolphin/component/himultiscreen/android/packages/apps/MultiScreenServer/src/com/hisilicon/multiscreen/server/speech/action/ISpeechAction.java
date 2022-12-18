package com.hisilicon.multiscreen.server.speech.action;

import android.content.Context;
import android.os.Handler;

import com.hisilicon.multiscreen.server.speech.responsemessage.SpeechResponseMessage;

/**
 * the action interface ,used to deal with different situation.<br>
 * 处理类接口，用于处理不同的场景。
 *
 */
public interface ISpeechAction
{
    /**
     *
     * @param context --the context of activity.<br>
     *         CN:上下文对象
     * @param handler --the message handler of activity.<br>
     *         CN:消息循环
     * @param msg  --the Speech Response Message.<br>
     *         CN:语音返回消息
     * @return --the returned value.<br>
     *         CN:执行结果返回值
     */
    String execute(Context context, Handler handler, SpeechResponseMessage msg);
}
