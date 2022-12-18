/******************************************************************
 *
 *    CyberHTTP for Java
 *
 *    Copyright (C) Satoshi Konno 2002-2003
 *
 *    File: HostInterface.java
 *
 *    Revision;
 *
 *    05/12/03
 *        - first revision.
 *    05/13/03
 *        - Added support for IPv6 and loopback address.
 *    02/15/04
 *        - Added the following methods to set only a interface.
 *        - setInterface(), getInterfaces(), hasAssignedInterface()
 *    06/30/04
 *        - Moved the package from org.cybergarage.http to org.cybergarage.net.
 *
 ******************************************************************/

package com.hisilicon.multiscreen.protocol.utils;

import java.net.Inet4Address;
import java.net.Inet6Address;
import java.net.InetAddress;
import java.net.NetworkInterface;
import java.util.ArrayList;
import java.util.Enumeration;

/**
 * Get Host IP address tools.<br>
 * CN:获取主机IP地址的工具类。
 * @since HiMultiScreen_V2.0.1.0 2013-1-25 created.<br>
 *        HiMultiScreen_V2.0.2.0 2013-5-13 modify for upnp.
 */

public class HostNetInterface
{
    /**
     * Separator between ip and port.<br>
     */
    public static final String SEPARATOR_BETWEEN_IP_AND_PORT = ":";

    /**
     * Separator between protocol head and port.<br>
     */
    public static final String SEPARATOR_BETWEEN_HEAD_AND_IP = "://";

    /**
     * whether is the loop address.<br>
     * CN:是否为循环IP地址
     */
    public static boolean USE_LOOPBACK_ADDR = false;

    // public static boolean USE_ONLY_IPV4_ADDR = false;

    /**
     * whether is the IPV4 address.<br>
     * CN:是否为IPV4地址
     */
    public static boolean USE_ONLY_IPV4_ADDR = true;

    /**
     * whether is the IPV6 address.<br>
     * CN:是否为IPV6地址
     */
    public static boolean USE_ONLY_IPV6_ADDR = false;

    // //////////////////////////////////////////////
    // Network Interfaces
    // //////////////////////////////////////////////

    private static String ifAddress = "";

    public final static void setInterface(String ifaddr)
    {
        ifAddress = ifaddr;
    }

    public final static String getInterface()
    {
        return ifAddress;
    }

    private final static boolean hasAssignedInterface()
    {
        return (0 < ifAddress.length()) ? true : false;
    }

    // //////////////////////////////////////////////
    // Network Interfaces
    // //////////////////////////////////////////////

    private final static boolean isUseAddress(InetAddress addr)
    {
        if (USE_LOOPBACK_ADDR == false)
        {
            if (addr.isLoopbackAddress() == true)
                return false;
        }
        if (USE_ONLY_IPV4_ADDR == true)
        {
            if (addr instanceof Inet6Address)
                return false;
        }
        if (USE_ONLY_IPV6_ADDR == true)
        {
            if (addr instanceof Inet4Address)
                return false;
        }
        return true;
    }

    public final static int getNHostAddresses()
    {
        if (hasAssignedInterface() == true)
            return 1;

        int nHostAddrs = 0;
        try
        {
            Enumeration<?> nis = NetworkInterface.getNetworkInterfaces();
            while (nis.hasMoreElements())
            {
                NetworkInterface ni = (NetworkInterface) nis.nextElement();
                Enumeration<?> addrs = ni.getInetAddresses();

                while (addrs.hasMoreElements())
                {
                    InetAddress addr = (InetAddress) addrs.nextElement();
                    if (isUseAddress(addr) == false)
                        continue;
                    nHostAddrs++;
                }
            }
        }
        catch (Exception e)
        {
        }
        ;
        return nHostAddrs;
    }

    public final static String getHostAddress(int n)
    {
        if (hasAssignedInterface() == true)
            return getInterface();

        int hostAddrCnt = 0;
        try
        {
            Enumeration<?> nis = NetworkInterface.getNetworkInterfaces();
            while (nis.hasMoreElements())
            {
                NetworkInterface ni = (NetworkInterface) nis.nextElement();
                Enumeration<?> addrs = ni.getInetAddresses();
                while (addrs.hasMoreElements())
                {
                    InetAddress addr = (InetAddress) addrs.nextElement();
                    if (isUseAddress(addr) == false)
                        continue;
                    if (hostAddrCnt < n)
                    {
                        hostAddrCnt++;
                        continue;
                    }
                    String host = addr.getHostAddress();
                    // if (addr instanceof Inet6Address)
                    // host = "[" + host + "]";
                    return host;
                }
            }
        }
        catch (Exception e)
        {
        }
        ;
        return "";
    }

    // //////////////////////////////////////////////
    // isIPv?Address
    // //////////////////////////////////////////////

    public final static boolean isIPv6Address(String host)
    {
        try
        {
            InetAddress addr = InetAddress.getByName(host);
            if (addr instanceof Inet6Address)
                return true;
            return false;
        }
        catch (Exception e)
        {
        }
        return false;
    }

    public final static boolean isIPv4Address(String host)
    {
        try
        {
            InetAddress addr = InetAddress.getByName(host);
            if (addr instanceof Inet4Address)
                return true;
            return false;
        }
        catch (Exception e)
        {
        }
        return false;
    }

    // //////////////////////////////////////////////
    // hasIPv?Interfaces
    // //////////////////////////////////////////////

    public final static boolean hasIPv4Addresses()
    {
        int addrCnt = getNHostAddresses();
        for (int n = 0; n < addrCnt; n++)
        {
            String addr = getHostAddress(n);
            if (isIPv4Address(addr) == true)
                return true;
        }
        return false;
    }

    public final static boolean hasIPv6Addresses()
    {
        int addrCnt = getNHostAddresses();
        for (int n = 0; n < addrCnt; n++)
        {
            String addr = getHostAddress(n);
            if (isIPv6Address(addr) == true)
                return true;
        }
        return false;
    }

    // //////////////////////////////////////////////
    // hasIPv?Interfaces
    // //////////////////////////////////////////////

    public final static ArrayList<String> getIPv4Address()
    {
        int addrCnt = getNHostAddresses();
        ArrayList<String> ipList = new ArrayList<String>();
        for (int n = 0; n < addrCnt; n++)
        {
            String addr = getHostAddress(n);
            if (isIPv4Address(addr) == true)
            {
                ipList.add(addr);
            }

        }
        return ipList;
    }

    public final static String getSameSegmentIp(String ip)
    {
        ArrayList<String> list = getIPv4Address();
        StringBuffer prefixBuf = null;
        if (list.size() <= 0 || ip == null)
        {
            return null;
        }

        // 特殊字符用到了转义，另外，如果是|也许要使用转义
        String[] ipSeg = ip.split("\\.");
        prefixBuf = new StringBuffer();
        prefixBuf.append(ipSeg[0]);
        prefixBuf.append(".");
        prefixBuf.append(ipSeg[1]);

        for (int index = 0; index < list.size(); index++)
        {
            System.out.println("[" + index + "]=" + list.get(index));
            if (list.get(index).contains(prefixBuf.toString()))
            {
                return list.get(index);
            }
        }

        return null;
    }

    public final static String getIPv6Address()
    {
        int addrCnt = getNHostAddresses();
        for (int n = 0; n < addrCnt; n++)
        {
            String addr = getHostAddress(n);
            if (isIPv6Address(addr) == true)
                return addr;
        }
        return "";
    }

    /**
     * Get format IP in uri.<br>
     * URI of upnp is like "Vinput://10.161.179.100:8822".<br>
     * Socket address is like "/10.161.179.100:42230".<br>
     * What we need is like "10.161.179.100".<br>
     * @param uri - uri of upnp.
     * @return
     */
    public final static String uri2Ip(String uri)
    {
        String ipAddress = null;
        if ((uri == null) || uri.equals(""))
        {
            LogTool.e("source location is null");
        }
        else
        {
            if (uri.split("/")[0].length() == 0)
            {
                // Socket address.
                ipAddress = uri.replace("/", "").split(":")[0];
            }
            else
            {
                // Uri of upnp.
                ipAddress = uri.replaceAll("/", "").split(":")[1];
            }
        }
        return ipAddress;
    }

    /**
     * Get format port in uri.<br>
     * Uri of upnp is like "Vinput://10.161.179.100:8822".<br>
     * What we need is like "8822".
     * @param uri - uri of upnp.
     * @return port
     */
    public final static int uri2port(String uri)
    {
        int port = -1;
        if ((uri == null) || uri.equals(""))
        {
            LogTool.e("source uri is null");
        }
        else
        {
            if (uri.split("/")[0].length() == 0)
            {
                // Socket address.
                port = Integer.parseInt(uri.split(":")[1].replaceAll("/", ""));
            }
            else
            {
                // Uri of upnp.
                port = Integer.parseInt(uri.split(":")[2].replaceAll("/", ""));
            }
        }
        return port;
    }

    /**
     * Convert ip and port to uri.<br>
     * Like head = "Vinput://",ip ="10.161.179.100",port = 8822,can be converted
     * to "Vinput://10.161.179.100:8822". <br>
     * @param head module head or protocol head.
     * @param ip ip address.<br>
     * @param port port number.<br>
     * @return uri string.<br>
     */
    public final static String ipAndPort2Uri(String head, String ip, int port)
    {
        StringBuilder uriStringBuilder = new StringBuilder();
        uriStringBuilder.append(head);
        uriStringBuilder.append(SEPARATOR_BETWEEN_HEAD_AND_IP);
        uriStringBuilder.append(ip);
        uriStringBuilder.append(SEPARATOR_BETWEEN_IP_AND_PORT);
        uriStringBuilder.append(String.valueOf(port));
        return uriStringBuilder.toString();
    }

    /**
     * Convert int IP to string.<br>
     */
    public final static String int2Ip(int ip)
    {
        StringBuffer ipAddressBuff = new StringBuffer();
        ipAddressBuff.append((ip & 0xFF));
        ipAddressBuff.append(".");
        ipAddressBuff.append(((ip >> 8) & 0xFF));
        ipAddressBuff.append(".");
        ipAddressBuff.append(((ip >> 16) & 0xFF));
        ipAddressBuff.append(".");
        ipAddressBuff.append(((ip >> 24) & 0xFF));
        return ipAddressBuff.toString();
    }

    /**
     * validate string is according to ip format.
     * @param ip the input string.
     * @return true the string is according to ip format,otherwise return false.
     */
    public static boolean isValidIp(String ip)
    {// 判断是否是一个IP
        boolean b = false;
        ip = ip.trim();
        if (ip.matches("\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}\\.\\d{1,3}"))
        {
            String s[] = ip.split("\\.");
            if (Integer.parseInt(s[0]) < 255)
                if (Integer.parseInt(s[1]) <= 255)
                    if (Integer.parseInt(s[2]) <= 255)
                        if (Integer.parseInt(s[3]) <= 255)
                            b = true;
        }
        return b;
    }
}
