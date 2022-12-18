/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

package com.hisilicon.android.networkutils;

import java.util.Collection;
import java.util.ArrayList;
import java.util.Iterator;
import java.net.InetAddress;
import android.util.Log;
import android.content.Context;
import android.content.Intent;
import android.text.TextUtils;
import android.os.SystemProperties;
import android.os.Binder;

import com.hisilicon.android.hisysmanager.HiSysManager;

/**
 * hisislicon NDK methods for managing network interfaces.
 *
 * {@hide}
 */
public class HiNetworkUtils {

    private static final String TAG = "HiNetworkUtils";
    private static final String NET_DNS = "net.dns";
    private Context mContext;
    private HiSysManager hiSysManager;
    private boolean DEBUG = true;

    public static final String HINETWORKUTILS_NETWORK_STATE_CHANGED_ACTION =
        "com.hisilicon.android.net.NETWORK_STATE_CHANGE";
    public static final String EXTRA_NETWORK_STATE= "network_state";


    public static final int EVENT_DHCP_CONNECT_SUCCESSED        = 0;
    public static final int EVENT_DHCP_CONNECT_FAILED           = 1;
    public static final int EVENT_DHCP_DISCONNECT_SUCCESSED     = 2;
    public static final int EVENT_DHCP_DISCONNECT_FAILED        = 3;

    public static final int INTERFACE_STATUS_LINK_UP             = 1;
    public static final int INTERFACE_STATUS_LINK_DOWN           = 0;
    public static final int INTERFACE_STATUS_NO_INTERFACE        = -1;

    static {
        System.loadLibrary("hi_netutils");
    }

    public HiNetworkUtils(Context context)
    {
        mContext = context;
        hiSysManager = new HiSysManager();
    }

    /**
     * Bring the named network interface up.
     * @param interfaceName the name of the network interface
     */
    public void enableInterface(String interfaceName) {
        hiSysManager.enableInterface(interfaceName);
    }

    /**
     * Bring the named network interface down.
     * @param interfaceName the name of the network interface
     */
    public void disableInterface(String interfaceName) {
        hiSysManager.disableInterface(interfaceName);
    }

    /**
     * Start the DHCP client daemon, in order to have it request addresses
     * for the named interface, and then configure the interface with those
     * addresses. This call blocks until it obtains a result (either success
     * or failure) from the daemon.
     * @param interfaceName the name of the interface to configure
     */
    public void runDhcp(final String interfaceName) {
        Thread dhcpThread = new Thread(new Runnable() {
            public void run() {
                if(!startDhcp(interfaceName)){
                    Log.e(TAG, "HiNetUtils: DHCP request error:" + getDhcpError());
                    Log.e(TAG, "runDhcp fail, send EVENT_DHCP_CONNECT_FAILED");
                    postNotification(EVENT_DHCP_CONNECT_FAILED);
                    return ;
                }
                Log.i(TAG, "runDhcp success, send EVENT_DHCP_CONNECT_SUCCESSED");
                postNotification(EVENT_DHCP_CONNECT_SUCCESSED);
            }
        });
        dhcpThread.start();
    }

    /**
     * Shut down the DHCP client daemon.
     * @param interfaceName the name of the interface for which the daemon should be stopped
     */
    public void releaseDhcp(final String interfaceName){
        if(stopDhcp(interfaceName)) {
            Log.i(TAG, "releaseDhcp success, send message EVENT_DHCP_DISCONNECT_SUCCESSED");
            postNotification(EVENT_DHCP_DISCONNECT_SUCCESSED);
        } else {
            Log.e(TAG, "releaseDhcp fail, send message EVENT_DHCP_DISCONNECT_FAILED");
            postNotification(EVENT_DHCP_DISCONNECT_FAILED);
        }
    }

    /**
     * Set dns for caller pid
     * @param interfaceName the name of the interface for which the daemon
     */
    public void setDnses(String interfaceName) {
        int pid = Binder.getCallingPid();
        setDnsesForPid(interfaceName,pid);
    }

    /**
     * Set dns for special pid.
     * @param interfaceName the name of the interface for which the daemon
     * @param pid the pid for the application
     */
    public void setDnsesForPid(String interfaceName, int pid) {
        Collection<String> mDnses = getDnses(interfaceName);
        Iterator<String> dnses = mDnses.iterator();

        if (!dnses.hasNext()) {
            Log.e(TAG, "setDnses:can not get DNS!!");
            return ;
        }
        String dns = dnses.next();
        int i = 1;
        while(null != dns) {
            String keyname = NET_DNS + i + "." + pid;
            SystemProperties.set(keyname, dns);
            i++;
            if(!dnses.hasNext()) {
                Log.i(TAG, "setDnses:no dns" + i);
                return ;
            }
            dns = dnses.next();
        }
    }

    /**
     * Get the ip addresss of the interface.
     * @param interfaceName the name of the network interface
     */
    public native String getIpaddr(String interfaceName);

    /**
     * Get the netmask addresss of the interface.
     * @param interfaceName the name of the network interface
     */
    public native String getNetmask(String interfaceName);

    /**
     * Get the gateway address for the named interface.
     * @param interfaceName the name of the network interface
     */
    public String getGateway(String interfaceName) {
        String keyname = "dhcp." + interfaceName + ".gateway";
        if(DEBUG) Log.d(TAG, "getGateway keyname = " + keyname + " Gateway: " + SystemProperties.get(keyname));
        return SystemProperties.get(keyname);
    }

    /**
     * Get the dns address for the named interface.
     * @param interfaceName the name of the network interface
     * @return the dns address
     */
    public Collection<String> getDnses(String interfaceName) {
        Collection<String> mDnses = new ArrayList<String>();
        int i = 1;
        String keyname = "dhcp." + interfaceName + ".dns";
        while(!TextUtils.isEmpty(SystemProperties.get(keyname + i))) {
            if(DEBUG) Log.d(TAG, "dns: " + keyname + i + " = " + SystemProperties.get(keyname + i));
            mDnses.add(SystemProperties.get(keyname+i));
            i++;
        }
        if(i == 1) {
            Log.e(TAG, "no dns for interface: " + interfaceName);
        }
        return mDnses;
    }

    /**
     * Remove dns for caller pid.
     * @param interfaceName the name of the network interface
     */
    public void removeDnses(String interfaceName) {
        int pid = Binder.getCallingPid();
        removeDnsesForPid(interfaceName,pid);
    }

    /**
     * Remove dns for special pid.
     * @param interfaceName the name of the network interface
     * @param pid the pid for the application
     */
    public void removeDnsesForPid(String interfaceName, int pid) {
        int i = 1;
        String keyname = NET_DNS + i + "." + pid;
        if(DEBUG) Log.d(TAG, "removeDnsesForPid dns: " + keyname);
        while(!TextUtils.isEmpty(SystemProperties.get(keyname))) {
            if(DEBUG) Log.d(TAG, "removeDnsesForPid: pid= " + pid + " keyname=" + keyname + " dns=" + SystemProperties.get(keyname));
            SystemProperties.set(keyname, "");
            Log.i(TAG, "removeDnses: " + keyname + " for pid " + pid);
            i++;
            keyname = NET_DNS + i + "." + pid;
        }
    }

    /**
     * Get the Interface status: 1 for link up, 0 link down, -1 for no interface.
     * @param interfaceName the name of the network interface
     */
    public native int getNetlinkStatus(String interfaceName);

    /**
     * Set net route for interface
     * @param interfaceName the name of the network interface
     * @param dst the destination ip address
     * @param prefix_length the prefix_length
     * @param gw the gateway address
     */
    public void addRoute(String interfaceName, String dst, int prefix_length, String gw){
        hiSysManager.addRoute(interfaceName, dst, prefix_length, gw);
    }

    /**
     * Set default route for interface
     * @param interfaceName the name of the network interface
     * @param gateway the gateway address
     */
    public void setDefaultRoute(String interfaceName, String gateway) {
        InetAddress igw = numericToInetAddress(gateway);
        int gw = inetAddressToInt(igw);
        hiSysManager.setDefaultRoute(interfaceName, gw);
    }

    /**
     * Get default route for interface
     * @param interfaceName the name of the network interface
     */
    public native int getDefaultRoute(String interfaceName);

    /**
     * Remove the default route for the named interface.
     * @param interfaceName the name of the network interface
     */
    public void removeDefaultRoute(String interfaceName) {
        hiSysManager.removeDefaultRoute(interfaceName);
    }

    /**
     * Remove net route for the named interface.
     * @param interfaceName the name of the network interface
     */
    public void removeNetRoute(String interfaceName) {
        hiSysManager.removeNetRoute(interfaceName);
    }

    /**
     * Set net route for interface
     * @param interfaceName the name of the network interface
     * @param dst the destination ip address
     * @param prefix_length the prefix_length
     * @param gw the gateway address
     */
    public void removeRoute(String interfaceName, String dst, int prefix_length, String gw) {
        hiSysManager.removeRoute(interfaceName, dst, prefix_length, gw);
    }

    /* private interface */
    private native boolean startDhcp(String interfaceName);

    private native boolean stopDhcp(String interfaceName);

    private native String getDhcpError();


    /**
     * Convert a IPv4 address from an InetAddress to an integer
     * @param inetAddr is an InetAddress corresponding to the IPv4 address
     * @return the IP address as an integer in network byte order
     */
    private int inetAddressToInt(InetAddress inetAddr)
            throws IllegalArgumentException {
        byte [] addr = inetAddr.getAddress();
        if (addr.length != 4) {
            throw new IllegalArgumentException("Not an IPv4 address");
        }
        return ((addr[3] & 0xff) << 24) | ((addr[2] & 0xff) << 16) |
                ((addr[1] & 0xff) << 8) | (addr[0] & 0xff);
    }

    /**
     * Create an InetAddress from a string where the string must be a standard
     * representation of a V4 or V6 address.  Avoids doing a DNS lookup on failure
     * but it will throw an IllegalArgumentException in that case.
     * @param addrString
     * @return the InetAddress
     * @hide
     */
    private InetAddress numericToInetAddress(String addrString)
            throws IllegalArgumentException {
        return InetAddress.parseNumericAddress(addrString);
    }

    private void postNotification(int event) {
        final Intent intent = new Intent(HINETWORKUTILS_NETWORK_STATE_CHANGED_ACTION);
        intent.addFlags(Intent.FLAG_RECEIVER_REGISTERED_ONLY_BEFORE_BOOT);
        intent.putExtra(EXTRA_NETWORK_STATE, event);
        mContext.sendStickyBroadcast(intent);
    }
}
