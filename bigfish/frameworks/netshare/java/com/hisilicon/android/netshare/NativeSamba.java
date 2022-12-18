package com.hisilicon.android.netshare;

/**
* NativeSamba interface<br>
* CN: NativeSamba接口
*/
public class NativeSamba {

    /**
     * start samba server.
     * <br>
     * CN:启动samba服务
     * @return int result 0:  sucess -1:  failed<br>
     *      CN:返回结果 0:成功 -1:失败
     */
    public native int startSambaServer();

    /**
     * stop samba server.
     * <br>
     * CN:停止samba服务
     * @return int result 0: sucess -1: failed<br>
     *      CN:返回结果 0:成功 -1:失败
     */
    public native int stopSambaServer();

    static {
        System.loadLibrary("netshare_jni");
    }

    /**
     * set user.
     * <br>
     * 设置用户名
     * @return int result 0: sucess -1: failed<br>
     *      CN:返回结果 0:成功 -1:失败
     */
    public native int setUser(String user);

    /**
     * set user's passwd.
     * <br>
     * CN:设置用户密码
     * @return int result 0: sucess -1: failed<br>
     *      CN:返回结果 0:成功 -1:失败
     */
    public native int setPasswd(String passwd);

    /**
     * Set global parameters.
     * <br>
     * CN:设置全局参数
     * @param workgroup<br>
     *        CN:工作组
     * @param server_string<br>
     *        CN:服务器
     * @param security<br>
     *        CN:安全
     * @param maxLogSize<br>
     *        CN:最大日志文件大小
     * @param netBiosName<br>
     *        CN:主机名
     * @return
     */
    public native int setGlobal(String workgroup, String server_string, String security,
            int maxLogSize, String netBiosName);

    /**
     * New share.
     * <br>
     * CN:新建共享
     * @param head<br>
     *     CN:共享文件
     * @param path<br>
     *     CN:共享文件路径
     * @param createMask<br>
     *     CN:文件权限
     * @param directoryMask<br>
     *     CN:目录权限
     * @param available<br>
     *     CN:是有效的 yes no
     * @param browseable<br>
     *     CN:是否允许浏览  yes no
     * @param writable<br>
     *     CN:是可写的
     * @param validUsers<br>
     *     CN:用启名 默认：administrator
     * @return
     */
    public native int addProperty(String head, String path, String createMask,
            String directoryMask, String available, String browseable, String writable,
            String validUsers);

    /**
     * Compiling shared configuration.
     * <br>
     * CN:编译共享配置
     * @param head<br>
     *     CN:共享文件
     * @param path<br>
     *     CN:共享文件路径
     * @param createMask<br>
     *     CN:文件权限
     * @param directoryMask<br>
     *     CN:目录权限
     * @param available<br>
     *     CN:是有效的 yes no
     * @param browseable<br>
     *     CN:是否允许浏览  yes no
     * @param writable<br>
     *     CN:是可写的
     * @param validUsers<br>
     *     CN:用启名 默认：administrator
     * @return
     */
    public native int editShare(String head, String path, String createMask, String directoryMask,
            String available, String browseable, String writable, String validUsers);

    /**
     * Delete the configuration.
     * <br>
     * CN:删除配置
     * @param head Sharing the file name<br>
     * CN:共享文件名
     * @return
     */
    public native int deleteShare(String head);

    /**
     * get Shared file name.
     * <br>
     * CN:获取共享文件名
     * @return Shared file name<br>
     *         CN:返回共享文件名
     */
    public native String getProperty();

    /**
     * get Configuration parameters.
     * <br>
     * CN:获取配置参数
     * @param head Sharing the file name<br>
     * CN:共享文件名
     * @return Configuration parameters<br>
     *        CN:返回配置参数
     */
    public native String getParameter(String head);

    /**
     * get Samba process turned.
     * <br>
     * CN:获取samba进程状态
     * @return int 0 Indicates that the process is not open
     *             1 Indicates that the process is open<br>
     *     CN:返回 0：关闭
     *             1: 打开
     */
    public native int getSambaProcessState();

}
