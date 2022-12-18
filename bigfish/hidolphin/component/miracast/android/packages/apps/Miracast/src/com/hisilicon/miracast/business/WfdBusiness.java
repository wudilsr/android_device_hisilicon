package com.hisilicon.miracast.business;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.Collection;
import java.util.Iterator;

import android.content.Context;
import android.net.wifi.p2p.WifiP2pDevice;
import android.net.wifi.p2p.WifiP2pDeviceList;
import android.net.wifi.p2p.WifiP2pGroup;
import android.net.wifi.p2p.WifiP2pGroupList;
import android.net.wifi.p2p.WifiP2pManager;
import android.net.wifi.p2p.WifiP2pWfdInfo;

import com.hisilicon.miracast.util.LogUtil;
import com.hisilicon.miracast.util.RegexUtil;

public final class WfdBusiness
{
    private static final int WFD_DEFAULT_PORT = 7236;
    private static final int WFD_MAX_THROUGHPUT = 50;

    private static final int MAX_GET_IP_COUNT = 30;
    private static final int GET_IP_DURATION = 500;

    private WifiP2pManager mManager;
    private WifiP2pManager.Channel mChannel;

    private Collection<WifiP2pDevice> mDeviceCollection;
    private WifiP2pDevice mSourceDevice;

    private Collection<WifiP2pGroup> mGroupCollection;

    private final Object mLock = new Object();
    private boolean mIsPeersUpdating = false;
    private boolean mIsWaiting = false;

    private int mBest2gChannel = 0;
    private int mBest5gChannel = 0;

    public WfdBusiness(Context context)
    {
        mManager = (WifiP2pManager) context.getSystemService(Context.WIFI_P2P_SERVICE);
        if (mManager != null)
        {
            mChannel =
                mManager.initialize(context, context.getMainLooper(), new WfdChannelListener());
        }
    }

    public void disconnectP2p()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            mManager.removeGroup(mChannel, new WfdActionListener(
                WfdActionListener.ACTION_ID_DISCONNECT_P2P));
        }
    }

    public void clearGroup()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            if (mGroupCollection != null)
            {
                final Iterator<WifiP2pGroup> iterator = mGroupCollection.iterator();
                while (iterator.hasNext())
                {
                    WifiP2pGroup group = (WifiP2pGroup) iterator.next();
                    LogUtil.i("persistent group network name: " + group.getNetworkName());

                    mManager.deletePersistentGroup(mChannel, group.getNetworkId(),
                        new WfdActionListener(WfdActionListener.ACTION_ID_CLEAR_GROUP));
                }

                mGroupCollection = null;
            }
        }
    }

    public void setDeviceName(String name)
    {
        LogUtil.d("");
        if (isInitialized())
        {
            mManager.setDeviceName(mChannel, name, new WfdActionListener(
                WfdActionListener.ACTION_ID_SET_DEVICE_NAME));
        }
    }

    public void setWfdInfo()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            final WifiP2pWfdInfo wfdInfo = new WifiP2pWfdInfo();
            wfdInfo.setWfdEnabled(true);
            wfdInfo.setSessionAvailable(true);
            wfdInfo.setCoupledSinkSupportAtSink(false);
            wfdInfo.setCoupledSinkSupportAtSource(false);
            wfdInfo.setDeviceType(WifiP2pWfdInfo.PRIMARY_SINK);
            wfdInfo.setControlPort(WFD_DEFAULT_PORT);
            wfdInfo.setMaxThroughput(WFD_MAX_THROUGHPUT);
            wfdInfo.setHDCPSupportedAtSink(true);
            mManager.setWFDInfo(mChannel, wfdInfo, new WfdActionListener(
                WfdActionListener.ACTION_ID_SET_WFD_INFO));
        }
    }

    public void clearWfdInfo()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            final WifiP2pWfdInfo wfdInfo = new WifiP2pWfdInfo();
            wfdInfo.setWfdEnabled(false);
            mManager.setWFDInfo(mChannel, wfdInfo, new WfdActionListener(
                WfdActionListener.ACTION_ID_CLEAR_WFD_INFO));
        }
    }

    /**
     * @hide
     */
    public void searchDevice()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            mManager.discoverPeers(mChannel, new WfdActionListener(
                WfdActionListener.ACTION_ID_SEARCH_DEVICE));
        }
    }

    public void updateGroup()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            mManager.requestGroupInfo(mChannel, new WfdGroupListener());
        }
    }

    public void updatePersistentGroup()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            mManager.requestPersistentGroupInfo(mChannel, new WfdPersistentGroupListener());
        }
    }

    public void updatePeers()
    {
        LogUtil.d("");
        if (isInitialized())
        {
            synchronized (mLock)
            {
                mIsPeersUpdating = true;

                mManager.requestPeers(mChannel, new WifiP2pManager.PeerListListener()
                {
                    @Override
                    public void onPeersAvailable(WifiP2pDeviceList peers)
                    {
                        synchronized (mLock)
                        {
                            mDeviceCollection = peers.getDeviceList();
                            updateSourceInfo();
                            mIsPeersUpdating = false;
                            if (mIsWaiting)
                            {
                                mLock.notifyAll();
                                mIsWaiting = false;
                            }
                        }
                    }
                });
            }
        }
    }

    private void updateSourceInfo()
    {
        LogUtil.d("");
        if (mDeviceCollection != null)
        {
            final Iterator<WifiP2pDevice> iterator = mDeviceCollection.iterator();
            while (iterator.hasNext())
            {
                WifiP2pDevice device = (WifiP2pDevice) iterator.next();

                boolean isMatched = (WifiP2pDevice.CONNECTED == device.status);
                isMatched |= (WifiP2pDevice.INVITED == device.status);
                if (isMatched)
                {
                    LogUtil.i("source device name: " + device.deviceName);
                    LogUtil.i("source device status: " + device.status);
                    mSourceDevice = device;
                    break;
                }
            }
        }
    }

    public boolean isSourceWfd()
    {
        LogUtil.d("");

//        boolean ret = false;
        waitForUpdatePeers();

        if (mSourceDevice != null)
        {
            WifiP2pWfdInfo wfdInfo = mSourceDevice.wfdInfo;
            if (wfdInfo != null)
            {
                LogUtil.i("source device isWfdEnabled: " + wfdInfo.isWfdEnabled());
                LogUtil.i("source device type: " + wfdInfo.getDeviceType());
//                ret = wfdInfo.isWfdEnabled();
            }
            else
            {
                LogUtil.w("no wfd info");
            }
        }

        return true;
    }

    public String getSourceIp()
    {
        LogUtil.d("");

        String ipAddr = "";
        waitForUpdatePeers();

        if (mSourceDevice != null)
        {
            try
            {
                ipAddr = getIpFromMac(mSourceDevice.deviceAddress);
            }
            catch (Exception e)
            {
                LogUtil.e(e.toString());
            }
        }

        return ipAddr;
    }

    private String getIpFromMac(String macAddr) throws IOException, InterruptedException
    {
        LogUtil.d("");

        String ipAddr = "";
        BufferedReader bufReader = null;
        Process proc = null;

        LogUtil.d(macAddr);

        int count = 0;
        while (ipAddr.isEmpty() && (count < MAX_GET_IP_COUNT))
        {
            count++;

            try
            {
                proc = Runtime.getRuntime().exec("busybox arp");
                bufReader = new BufferedReader(new InputStreamReader(proc.getInputStream()));
                String line = null;
                String softFilter = "p2p";
                while ((line = bufReader.readLine()) != null)
                {
                    LogUtil.d(line);
                    if (line.contains(softFilter) || line.contains(macAddr))
                    {
                        ipAddr = RegexUtil.findIpAddr(line);
                        break;
                    }
                }

                Thread.sleep(GET_IP_DURATION);
            }
            catch (IOException e)
            {
                throw e;
            }
            finally
            {
                if (bufReader != null)
                {
                    try
                    {
                        bufReader.close();
                        bufReader = null;
                    }
                    catch (IOException e)
                    {
                        throw e;
                    }
                }
            }
        }

        return ipAddr;
    }

    private void waitForUpdatePeers()
    {
        synchronized (mLock)
        {
            if (mIsPeersUpdating)
            {
                LogUtil.d("");

                try
                {
                    mIsWaiting = true;
                    mLock.wait(3000);
                }
                catch (InterruptedException e)
                {
                    LogUtil.e(e.toString());
                }
            }
        }
    }

    public int getSourcePort()
    {
        int port = WFD_DEFAULT_PORT;

        if (mSourceDevice != null)
        {
            WifiP2pWfdInfo wfdInfo = mSourceDevice.wfdInfo;
            if (wfdInfo != null)
            {
                port = wfdInfo.getControlPort();
                if (port == 0)
                {
                    LogUtil.w("set port WFD_DEFAULT_PORT");
                    port = WFD_DEFAULT_PORT;
                }
            }
            else
            {
                LogUtil.w("no wfd info");
            }
        }
        LogUtil.d("source port: " + port);

        return port;
    }


    public void setWifiP2pChannels(int bc2g, int bc5g)
    {
        if (isInitialized())
        {
            mBest2gChannel = bc2g;
            mBest5gChannel = bc5g;
            mManager.setWifiP2pChannels(mChannel, bc2g, 0, new WfdActionListener(
                WfdActionListener.ACTION_ID_WFD_SET_P2P_CHANNELS));
        }
    }

    private void setP2pBestChannels()
    {
        if (mBest2gChannel == 0)
        {
            return;
        }

        LogUtil.d("mBest2gChannel: " + mBest2gChannel + " mBest5gChannel: " + mBest5gChannel);

        if (isInitialized())
        {
            mManager.setP2pBestChannels(mChannel, mBest2gChannel, mBest5gChannel, new WfdActionListener(
                WfdActionListener.ACTION_ID_WFD_SET_P2P_BEST_CHANNELS));
        }
    }

    private boolean isInitialized()
    {
        return (mChannel != null);
    }

    class WfdChannelListener implements WifiP2pManager.ChannelListener
    {
        @Override
        public void onChannelDisconnected()
        {
            LogUtil.e("");
            mChannel = null;
        }
    }

    class WfdGroupListener implements WifiP2pManager.GroupInfoListener
    {
        @Override
        public void onGroupInfoAvailable(WifiP2pGroup group)
        {
            if (group != null)
            {
                LogUtil.i("group network name: " + group.getNetworkName());
            }
        }
    }

    class WfdPersistentGroupListener implements WifiP2pManager.PersistentGroupInfoListener
    {
        @Override
        public void onPersistentGroupInfoAvailable(WifiP2pGroupList groups)
        {
            if (groups != null)
            {
                mGroupCollection = groups.getGroupList();
                clearGroup();
            }
        }
    }

    class WfdActionListener implements WifiP2pManager.ActionListener
    {
        public static final int ACTION_ID_SET_DEVICE_NAME = 1001;
        public static final int ACTION_ID_SET_WFD_INFO = 1002;
        public static final int ACTION_ID_CLEAR_WFD_INFO = 1003;
        public static final int ACTION_ID_DISCONNECT_P2P = 1004;
        public static final int ACTION_ID_SEARCH_DEVICE = 1005;
        public static final int ACTION_ID_CLEAR_GROUP = 1006;
        public static final int ACTION_ID_WFD_ENABLE_P2P = 1007;
        public static final int ACTION_ID_WFD_DISABLE_P2P = 1008;
        public static final int ACTION_ID_WFD_SET_P2P_CHANNELS = 1009;
        public static final int ACTION_ID_WFD_SET_P2P_BEST_CHANNELS = 1010;

        private int mActionId;
        private String mAction = "";

        public WfdActionListener(int actionId)
        {
            mActionId = actionId;

            switch (mActionId)
            {
                case ACTION_ID_SET_DEVICE_NAME:
                    mAction = "SET_DEVICE_NAME";
                    break;

                case ACTION_ID_SET_WFD_INFO:
                    mAction = "SET_WFD_INFO";
                    break;

                case ACTION_ID_CLEAR_WFD_INFO:
                    mAction = "CLEAR_WFD_INFO";
                    break;

                case ACTION_ID_DISCONNECT_P2P:
                    mAction = "DISCONNECT_P2P";
                    break;

                case ACTION_ID_SEARCH_DEVICE:
                    mAction = "SEARCH_DEVICE";
                    break;

                case ACTION_ID_CLEAR_GROUP:
                    mAction = "CLEAR_GROUP";
                    break;

                case ACTION_ID_WFD_ENABLE_P2P:
                    mAction = "WFD_ENABLE_P2P";
                    break;

                case ACTION_ID_WFD_DISABLE_P2P:
                    mAction = "WFD_DISABLE_P2P";
                    break;

                case ACTION_ID_WFD_SET_P2P_CHANNELS:
                    mAction = "SET_P2P_CHANNELS";
                    break;

                case ACTION_ID_WFD_SET_P2P_BEST_CHANNELS:
                    mAction = "SET_P2P_BEST_CHANNELS";
                    break;

                default:
                    break;
            }
        }

        @Override
        public void onSuccess()
        {
            LogUtil.i(mAction);

            if (mAction.equals("SET_P2P_CHANNELS"))
            {
                setP2pBestChannels();
            }
        }

        @Override
        public void onFailure(int reason)
        {
            String reasonDescription = "";

            switch (reason)
            {
                case WifiP2pManager.ERROR:
                    reasonDescription = "ERROR";
                    break;
                case WifiP2pManager.P2P_UNSUPPORTED:
                    reasonDescription = "P2P_UNSUPPORTED";
                    break;
                case WifiP2pManager.BUSY:
                    reasonDescription = "BUSY";
                    break;

                default:
                    break;
            }

            LogUtil.e(mAction + " reason: " + reasonDescription);
        }
    }
}
