package com.hisilicon.miracast.business;

import java.util.Iterator;
import java.util.List;
import java.util.Arrays;

import android.content.Context;
import android.net.wifi.WifiConfiguration;
import android.net.wifi.WifiManager;
import android.net.wifi.ScanResult;
import android.net.DhcpInfo;

import com.hisilicon.miracast.util.LogUtil;

public class WifiBusiness
{
    private static final int MAX_SIGNAL_LEVEL = 5;

    private WifiManager mManager;

    private WifiConfiguration mCfg;

    private List<ScanResult> mScanResults = null;

    private int mConnectNetworkId = WifiConfiguration.INVALID_NETWORK_ID;

    /*2.4G Wifi Channel 1 - 13*/
    private static final int FREQUENCY_CHANNEL_1 = 2412;

    private static final int FREQUENCY_CHANNEL_2 = 2417;

    private static final int FREQUENCY_CHANNEL_3 = 2422;

    private static final int FREQUENCY_CHANNEL_4 = 2427;

    private static final int FREQUENCY_CHANNEL_5 = 2432;

    private static final int FREQUENCY_CHANNEL_6 = 2437;

    private static final int FREQUENCY_CHANNEL_7 = 2442;

    private static final int FREQUENCY_CHANNEL_8 = 2447;

    private static final int FREQUENCY_CHANNEL_9 = 2452;

    private static final int FREQUENCY_CHANNEL_10 = 2457;

    private static final int FREQUENCY_CHANNEL_11 = 2462;

    private static final int FREQUENCY_CHANNEL_12 = 2467;

    private static final int FREQUENCY_CHANNEL_13 = 2472;

    /*5G Wifi Channel 149 - 161*/
    private static final int FREQUENCY_CHANNEL_149 = 5745;

    private static final int FREQUENCY_CHANNEL_153 = 5765;

    private static final int FREQUENCY_CHANNEL_157 = 5785;

    private static final int FREQUENCY_CHANNEL_161 = 5805;

    /**adjacent frequency interference*/
    private static final int AFI_LEVEL_1 = 10;

    private static final int AFI_LEVEL_2 = 8;

    private static final int AFI_LEVEL_3 = 6;

    private static final int AFI_LEVEL_4 = 4;

    /**same frequency interference*/
    private static final int SFI_LEVEL_1 = 1;

    /**signal level interference*/
    private static final int SLI_LEVEL_1 = 4;

    private static final int SLI_LEVEL_2 = 3;

    private static final int SLI_LEVEL_3 = 2;

    private static final int SLI_LEVEL_4 = 1;

    public WifiBusiness(Context context)
    {
        mManager = (WifiManager) context.getSystemService(Context.WIFI_SERVICE);
    }

    public boolean isWifiEnabled()
    {
        LogUtil.d("");

        boolean ret = false;

        if (isInitialized())
        {
            final int state = mManager.getWifiState();
            ret =
                (WifiManager.WIFI_STATE_ENABLED == state)
                    || (WifiManager.WIFI_STATE_ENABLING == state);
        }

        return ret;
    }

    public boolean isWifiApEnabled()
    {
        LogUtil.d("");

        boolean ret = false;

        if (isInitialized())
        {
            ret = mManager.isWifiApEnabled();
        }

        return ret;
    }

    public boolean isWifiAvailable()
    {
        LogUtil.d("");

        boolean ret = false;

        if (isInitialized())
        {
            final int state = mManager.getWifiState();
            ret = (WifiManager.WIFI_STATE_UNKNOWN != state);
        }

        return ret;
    }

    public void enableWifi()
    {
        LogUtil.d("");

        if (isInitialized())
        {
            int wifiApState = mManager.getWifiApState();
            if ((wifiApState == WifiManager.WIFI_AP_STATE_ENABLING) ||
                (wifiApState == WifiManager.WIFI_AP_STATE_ENABLED))
            {
                 mManager.setWifiApEnabled(null, false);
            }

            mManager.setWifiEnabled(true);
        }
    }

    public void enableWifiAp()
    {
        LogUtil.d("");

        if (isInitialized())
        {
            mManager.setWifiApEnabled(null, true);
        }
    }

    public void disableWifi()
    {
        LogUtil.d("");

        if (isInitialized())
        {
            mManager.setWifiEnabled(false);
        }
    }

    public void connect()
    {
        LogUtil.d("");

        if (isInitialized() && isWifiEnabled())
        {
            if (mCfg == null)
            {
                LogUtil.e("no cfg saved");
                return;
            }

            final List<WifiConfiguration> cfgList = mManager.getConfiguredNetworks();
            if (cfgList == null)
            {
                LogUtil.w("no cfg got");
                return;
            }

            final Iterator<WifiConfiguration> iterator = cfgList.iterator();
            while (iterator.hasNext())
            {
                WifiConfiguration cfg = (WifiConfiguration) iterator.next();
                String status = "";
                if (WifiConfiguration.Status.CURRENT == cfg.status)
                {
                    status = "CURRENT";
                }
                else if (WifiConfiguration.Status.ENABLED == cfg.status)
                {
                    status = "ENABLED";

                    if ((cfg.SSID != null) && (mCfg.SSID != null))
                    {
                        if (cfg.SSID.equals(mCfg.SSID))
                        {
                            mManager.connect(cfg, new WifiActionListener(
                                WifiActionListener.ACTION_ID_CONNECT));
                        }
                    }
                }
                else if (WifiConfiguration.Status.DISABLED == cfg.status)
                {
                    status = "DISABLED";
                }

                LogUtil.i("ssid: " + cfg.SSID);
                LogUtil.i("status: " + status);
            }
        }
    }

    public void disconnect()
    {
        LogUtil.d("");

        if (isInitialized() && isWifiEnabled())
        {
            final List<WifiConfiguration> cfgList = mManager.getConfiguredNetworks();
            if (cfgList == null)
            {
                LogUtil.w("no cfg got");
                return;
            }

            final Iterator<WifiConfiguration> iterator = cfgList.iterator();
            while (iterator.hasNext())
            {
                WifiConfiguration cfg = (WifiConfiguration) iterator.next();
                String status = "";
                if (WifiConfiguration.Status.CURRENT == cfg.status)
                {
                    status = "CURRENT";
                    mCfg = cfg;
                    mManager.disconnect();
                }
                else if (WifiConfiguration.Status.ENABLED == cfg.status)
                {
                    status = "ENABLED";
                }
                else if (WifiConfiguration.Status.DISABLED == cfg.status)
                {
                    status = "DISABLED";
                }
                LogUtil.i("status: " + status);
                LogUtil.i("ssid: " + cfg.SSID);
            }
        }
    }

    public static int getSignalLevel(int rssi)
    {
        LogUtil.d("");
        return WifiManager.calculateSignalLevel(rssi, MAX_SIGNAL_LEVEL);
    }

    public int[] getWifiP2pChannel()
    {
        int channel1 = 0;
        int channel6 = 0;
        int channel11 = 0;

        int channel149 = 0;
        int channel153 = 0;
        int channel157 = 0;
        int channel161 = 0;

        int[] bestChannels = new int[2];
        bestChannels[0] = 1;
        bestChannels[1] = 149;

        mScanResults = mManager.getScanResults();

        if (mScanResults == null)
        {
            return bestChannels;
        }

        Iterator<ScanResult> iterator = mScanResults.iterator();

        while (iterator.hasNext())
        {
            ScanResult scanResult = (ScanResult) iterator.next();

            LogUtil.d("" + scanResult.toString());

            if (scanResult.level <= -90)
            {
                continue;
            }

            switch (scanResult.frequency)
            {
                case FREQUENCY_CHANNEL_1: //channel 1
                {
                    channel1 += getSameFreInterference();
                    channel1 += getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_2:
                {
                    channel1 += AFI_LEVEL_1 + getSignalInterference(scanResult);
                    channel6 += AFI_LEVEL_4 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_3:
                {
                    channel1 += AFI_LEVEL_2 + getSignalInterference(scanResult);
                    channel6 += AFI_LEVEL_3 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_4:
                {
                    channel1 += AFI_LEVEL_3 + getSignalInterference(scanResult);
                    channel6 += AFI_LEVEL_2 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_5:
                {
                    channel1 += AFI_LEVEL_4 + getSignalInterference(scanResult);
                    channel6 += AFI_LEVEL_1 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_6:    //channel 6
                {
                    channel6 += getSameFreInterference();
                    channel6 += getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_7:
                {
                    channel6 += AFI_LEVEL_1 + getSignalInterference(scanResult);
                    channel11 += AFI_LEVEL_4 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_8:
                {
                    channel6 += AFI_LEVEL_2 + getSignalInterference(scanResult);
                    channel11 += AFI_LEVEL_3 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_9:
                {
                    channel6 += AFI_LEVEL_3 + getSignalInterference(scanResult);
                    channel11 += AFI_LEVEL_2 + getSignalInterference(scanResult);
                    break;
                }
                case FREQUENCY_CHANNEL_10:
                {
                    channel6 += AFI_LEVEL_4 + getSignalInterference(scanResult);
                    channel11 += AFI_LEVEL_1 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_11: //channel 11
                {
                    channel11 += getSameFreInterference();
                    channel11 += getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_12:
                {
                    channel11 += AFI_LEVEL_1 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_13:
                {
                    channel11 += AFI_LEVEL_2 + getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_149:
                {
                    channel149 += getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_153:
                {
                    channel153 += getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_157:
                {
                    channel157 += getSignalInterference(scanResult);
                    break;
                }

                case FREQUENCY_CHANNEL_161:
                {
                    channel161 += getSignalInterference(scanResult);
                    break;
                }

                default:
                    break;
            }
        }

        int[] channels = new int[]{channel1, channel6, channel11};
        bestChannels[0] = getChannel_2_4(channels);

        channels = new int[]{channel149, channel153, channel157, channel161};
        bestChannels[1] = getChannel_5(channels);

        return bestChannels;
    }

    private int getChannel_2_4(int[] channels)
    {
        if (channels.length <= 0)
        {
            return -1;
        }

        int[] channelsClone = new int[channels.length];
        int bestChannel = 0;
        int bestChannelValue = 0;

        for (int i = 0; i < channels.length; i++)
        {
            channelsClone[i] = channels[i];
        }

        Arrays.sort(channels);
        bestChannelValue = channels[0];

        if (channelsClone[0] == bestChannelValue)
        {
            bestChannel = 1;
        }
        else if (channelsClone[1] == bestChannelValue)
        {
            bestChannel = 6;
        }
        else if (channelsClone[2] == bestChannelValue)
        {
            bestChannel = 11;
        }

        return bestChannel;
    }

    private int getChannel_5(int[] channels)
    {
        if (channels.length <= 0)
        {
            return -1;
        }

        int[] channelsClone = new int[channels.length];
        int bestChannel = 0;
        int bestChannelValue = 0;

        for (int i = 0; i < channels.length; i++)
        {
            channelsClone[i] = channels[i];
        }

        Arrays.sort(channels);
        bestChannelValue = channels[0];

        if (channelsClone[0] == bestChannelValue)
        {
            bestChannel = 149;
        }
        else if (channelsClone[1] == bestChannelValue)
        {
            bestChannel = 153;
        }
        else if (channelsClone[2] == bestChannelValue)
        {
            bestChannel = 157;
        }
        else if (channelsClone[3] == bestChannelValue)
        {
            bestChannel = 161;
        }

        return bestChannel;
    }

    private int getSignalInterference(ScanResult scanResult)
    {
        int si = 0;
        int level = scanResult.level;

        if (level <= -70)
        {
            si = SLI_LEVEL_4;
        }
        else if (level > -70 && level <= -50)
        {
            si = SLI_LEVEL_3;
        }
        else if (level > -50 && level <= -30)
        {
            si = SLI_LEVEL_2;
        }
        else if (level > -30)
        {
            si = SLI_LEVEL_1;
        }

        return si;
    }

    private int getSameFreInterference()
    {
        return SFI_LEVEL_1;
    }

    public void disableNetworks()
    {
        LogUtil.d("");

        if (isInitialized() && isWifiEnabled())
        {
            final List<WifiConfiguration> cfgList = mManager.getConfiguredNetworks();
            if (cfgList == null)
            {
                LogUtil.w("no cfg got");
                return;
            }

            final Iterator<WifiConfiguration> iterator = cfgList.iterator();
            while (iterator.hasNext())
            {
                WifiConfiguration cfg = (WifiConfiguration) iterator.next();
                String status = "";

                mManager.disableNetwork(cfg.networkId);

                if (cfg.status == WifiConfiguration.Status.CURRENT)
                {
                    mConnectNetworkId = cfg.networkId;
                }

                LogUtil.i("networkid: " + cfg.networkId);
                LogUtil.i("status: " + cfg.status);
                LogUtil.i("ssid: " + cfg.SSID);
            }
        }
    }

    public void enableNetworks()
    {
        LogUtil.d("");

        boolean isExistConnectNetworkId = false;

        if (isInitialized() && isWifiEnabled())
        {
            final List<WifiConfiguration> cfgList = mManager.getConfiguredNetworks();
            if (cfgList == null)
            {
                LogUtil.w("no cfg got");
                return;
            }

            final Iterator<WifiConfiguration> iterator = cfgList.iterator();
            while (iterator.hasNext())
            {
                WifiConfiguration cfg = (WifiConfiguration) iterator.next();
                String status = "";

                mManager.enableNetwork(cfg.networkId, true);

                if (cfg.networkId == mConnectNetworkId)
                {
                    isExistConnectNetworkId = true;
                }

                LogUtil.i("networkid: " + cfg.networkId);
                LogUtil.i("status: " + status);
                LogUtil.i("ssid: " + cfg.SSID);
            }

            if (isExistConnectNetworkId)
            {
                mManager.enableNetwork(mConnectNetworkId, true);
            }
        }
    }



    private boolean isInitialized()
    {
        return (mManager != null);
    }

    class WifiActionListener implements WifiManager.ActionListener
    {
        public static final int ACTION_ID_CONNECT = 1001;

        private int mActionId;
        private String mAction = "";

        public WifiActionListener(int actionId)
        {
            mActionId = actionId;

            switch (mActionId)
            {
                case ACTION_ID_CONNECT:
                    mAction = "CONNECT";
                    break;

                default:
                    break;
            }
        }

        @Override
        public void onSuccess()
        {
            LogUtil.i(mAction);
        }

        @Override
        public void onFailure(int reason)
        {
            String reasonDescription = "";

            switch (reason)
            {
                case WifiManager.ERROR:
                    reasonDescription = "ERROR";
                    break;
                case WifiManager.IN_PROGRESS:
                    reasonDescription = "IN_PROGRESS";
                    break;
                case WifiManager.BUSY:
                    reasonDescription = "BUSY";
                    break;

                default:
                    break;
            }

            LogUtil.e(mAction + " reason: " + reasonDescription);
        }
    }
}
