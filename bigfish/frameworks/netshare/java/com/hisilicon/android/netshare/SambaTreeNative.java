package com.hisilicon.android.netshare;

/**
* SambaTreeNative interface<br>
* CN: SambaTreeNative接口
*/
public class SambaTreeNative {

    static {
        System.loadLibrary("netshare_jni");
    }
    /**
    * Get server list string.
    * <br>
    * CN:获取服器列表
    * @return servers
    *        CN:返回服务器列表
    */
    public native String getWorkgroups();

    /**
     * Obtained according to the specific working group.
     * <br>
     * CN:根据工作组获取服务器列表
     * @param workgroup<br>
     *       CN:工作组
     * @param name<br>
     *       CN:名字
     * @param pass<br>
     *       CN:密码
     * @return servers<br>
     *       CN:返回工作组列表
     */
    public native String getDetailsBy(String workgroup, String name, String pass);
}
