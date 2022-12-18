package com.hisilicon.dlna.player;

public interface IPlayerMainWnd
{
    /**
     * To close the main activity. <br>
     * CN: 关闭主应用. <br>
     *
     * @param isDelay is to delay close. true is delay,false no .<br>
     *        CN: isDelay 是否延迟关闭,true延时关闭,false立即关闭.<br>
     */
    public void closeActivity(boolean isDelay);

    /**
     * Cancel to delay close the main activity. <br>
     * CN: 取消延迟关闭主应用. <br>
     */
    public void cancelDelayCloseActivity();
}
