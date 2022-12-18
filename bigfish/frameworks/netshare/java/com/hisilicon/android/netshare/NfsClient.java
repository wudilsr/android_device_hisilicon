package com.hisilicon.android.netshare;


/**
* NfsClient interface<br>
* CN: NfsClient接口
*/
public class NfsClient
{
    static {
        System.loadLibrary("netshare_jni");
        nfsInit();
    }

    /**
     * Get server list string.
     * <br>
     * CN:获取服务器列表
     * @param
     * @return ips separated by "|"<br>
     *       CN:IP列表以"|"分隔
     */
    public native String getWorkgroups();

    /**
     * Get server folders by given ip.
     * <br>
     * CN:根据给定IP，获取服务器文件夹列表
     * @param ip<br>
     * @return folders separated by "|"
     *     CN:返回服务器文件夹列表以"|"分隔
     */
    public native String getShareFolders(String ip);

    /**
     * Mount nfs.
     * <br>
     * CN:挂载服务器
     * @param path format: ip/folder<br>
     *     CN:路径格式 IP/文件夹
     * @return 0:success -1:fail
     */
    public native int mount(String path);

    /**
     * Unmount nfs.
     * <br>
     * CN:卸载挂载点
     * @param mntPoint geted by getMountPoint
     *        CN:挂载点
     * @return 0:success -1:fail
     */
    public native int unmount(String mntPoint);

    /**
     * getMountPoint by path.
     * <br>
     * CN:根据路径获取挂载点
     * @param path format: ip/folder
     *        CN:路径格式 IP/文件夹
     * @return mntPoint
     *        CN:返回挂载点
     */
    public native String getMountPoint(String path);

    private static native final int nfsInit();
}
