package com.hisilicon.multiscreen.protocol.remote;

import com.hisilicon.multiscreen.protocol.message.Action;

/**
 * Handle request of start/end VIme activity on client.<br>
 * CN:处理启动/关闭VIME客户端页面的请求。
 * @since MultiScreen V2.0.1.1
 * @see VImeClientController
 */
public interface IVImeActivityHandler
{
    /**
     * @deprecated
     * @see MultiSettingActivity.<br>
     * This function is useless, UI changed.<br>
     * Open switch of VIME on client.<br>
     */
    public void openVimeSwitch();

    /**
     * Stop switch of VIME on client.<br>
     */
    public void closeVimeSwitch();

    /**
     * Start activity of input.<br>
     * @param action - action of callInput with some arguments
     */
    public void callInput(Action action);

    /**
     * End activity of input by client.<br>
     */
    public void endInputBySelf();

    /**
     * End activity of input by server.<br>
     */
    public void endInputByServer();

    /**
     * Check whether input activity is on top.
     * @return - true if acivity on top.
     */
    public boolean isInputActivityOnTop();
}
