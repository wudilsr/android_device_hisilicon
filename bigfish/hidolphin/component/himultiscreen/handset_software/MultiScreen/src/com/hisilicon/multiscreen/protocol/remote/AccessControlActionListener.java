package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.protocol.message.Action;

/**
 * The interface should be implement by the action dealer.<br>
 * CN:接入控制处理回调接口。
 * @since HiMultiScreen_V2.0.1.1
 */
public interface AccessControlActionListener
{
    /**
     * Handle action of request.<br>
     * CN:处理请求消息。
     * @param request - action of request.
     * @return - action of response.
     */
    Action onRequestAction(Action request);
}
