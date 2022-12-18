package com.hisilicon.multiscreen.server;

/**
 * Interface for native method callback.<br>
 * 本地方法的回调接口。
 */
public interface MultisScreenNativeCallback
{
    /**
     * Native Invoke method.<br>
     * CN:本地调用的方法。
     * @param comandId callback method's id.<br>
     *        CN:回调方法的id。
     * @param param - callback's parameter.<br>
     *        CN:回调方法的参数。
     * @param reserve - callback's reserver parameter.<br>
     *        CN:回调方法的预留参数。
     * @return execute method 's return value.<br>
     *         CN:回调方法的返回值。
     */
    int nativeInvoke(int comandId, String param, String reserve);
}
