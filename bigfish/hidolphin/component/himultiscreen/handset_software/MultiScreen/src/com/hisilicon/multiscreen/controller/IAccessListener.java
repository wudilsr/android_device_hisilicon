package com.hisilicon.multiscreen.controller;

/**
 * Interface of access listener.
 */
public interface IAccessListener
{
    /**
     * Caller of IAccessListener interface.<br>
     * CN:接入状态监听接口调用者。
     */
    public enum Caller
    {
        AccessPing, ReAccess, KeepAlive, Others
    };

    /**
     * Network not well callback.
     */
    void dealNetWorkNotWellEvent();

    /**
     * Network lost event callback.
     * @param caller
     */
    void dealNetWorkLostEvent(Caller caller);

    /**
     * Reave callback.
     * @param caller
     */
    void dealReaveEvent(Caller caller);

    /**
     * STB leave callback.
     * @param caller
     */
    void dealSTBLeaveEvent(Caller caller);

    /**
     * STB suspend callback.
     * @param caller
     */
    void dealSTBSuspendEvent(Caller caller);
}
