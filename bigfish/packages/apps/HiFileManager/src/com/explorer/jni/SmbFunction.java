package com.explorer.jni;

public class SmbFunction {

    static {
        System.loadLibrary("samba_quick_search");
    }

    public native static String Samba_NetBiosName2Ip(String NetBiosName);

    public native static int Samba_QueryDomainList(Object num);

    public native static int Samba_QueryServerList(Object num, String domain);

    public native static int Samba_QueryServerShareList(Object num, String ip,
            String username, String password, String domain);

    public native static String Samba_GetDomainList(int handle, int num);

    public native static String Samba_GetServerList(int handle, int num);

    public native static String Samba_GetServerShareList(int handle, int num,
            Object type);

    public native static void Samba_freeHandle(int handle);

}