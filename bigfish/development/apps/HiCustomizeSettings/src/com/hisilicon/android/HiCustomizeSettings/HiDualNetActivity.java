package com.hisilicon.android.HiCustomizeSettings;

import android.app.Activity;
import android.app.AlertDialog;
import android.app.Dialog;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.DialogInterface;
import android.content.Intent;
import android.content.IntentFilter;

import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.Process;

import android.util.Log;

import android.view.LayoutInflater;
import android.view.View;

import android.view.View.OnClickListener;

import android.widget.Button;
import android.widget.EditText;
import android.widget.TextView;

import com.hisilicon.android.HiSettingsDemo.R;
import com.hisilicon.android.networkutils.*;

import java.net.InetAddress;
import java.net.MalformedURLException;
import java.net.URL;
import java.net.UnknownHostException;
import android.net.NetworkUtils;
import java.util.Collection;
import java.util.ArrayList;
import java.util.Iterator;

public class HiDualNetActivity extends Activity implements OnClickListener {
    private Button button1;
    private Button button2;
    private Button button3;
    private Button button4;
    private Button button5;
    private Button button6;
    private Button button7;
    private Button button8;
    private Button button9;
    private Button button10;

    private EditText editTExt1;
    private EditText editTExt2;
    private EditText editTExt3;

    private TextView textView1;

    private String Destination = null;
    private String gateway = null;
    private String netmask = null;
    private String resolvedIpaddress = null;
    private int nm;
    private int prefix_length;
    private InetAddress iNetmask;

    private MyBroadcastReceiver receiver;
    private HiNetworkUtils mHiNetworkUtils;
    private final String INTERFACE = "eth1";
    private final String TAG = "HiDualNetDemo";

    private Handler handler = new Handler() {
        public void handleMessage(android.os.Message msg) {
            textView1.setText(resolvedIpaddress);
        };
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.hi_dual_net_activity);
        init();
    }

    private void init() {
        textView1 = (TextView) findViewById(R.id.text_view1);
        textView1.setVisibility(View.VISIBLE);

        button1 = (Button) findViewById(R.id.button1);
        button2 = (Button) findViewById(R.id.button2);
        button3 = (Button) findViewById(R.id.button3);
        button4 = (Button) findViewById(R.id.button4);
        button5 = (Button) findViewById(R.id.button5);
        button6 = (Button) findViewById(R.id.button6);
        button7 = (Button) findViewById(R.id.button7);
        button8 = (Button) findViewById(R.id.button8);
        button9 = (Button) findViewById(R.id.button9);
        button10 = (Button) findViewById(R.id.button10);

        button1.setOnClickListener(this);
        button2.setOnClickListener(this);
        button3.setOnClickListener(this);
        button4.setOnClickListener(this);
        button5.setOnClickListener(this);
        button6.setOnClickListener(this);
        button7.setOnClickListener(this);
        button8.setOnClickListener(this);
        button9.setOnClickListener(this);
        button10.setOnClickListener(this);

        mHiNetworkUtils = new HiNetworkUtils(HiDualNetActivity.this);
        receiver = new MyBroadcastReceiver();
    }

    private Dialog buildDialog(final int id) {
        LayoutInflater inflater = LayoutInflater.from(this);
        final View textEntryView = inflater.inflate(R.layout.alert_dialog_1,
                null);
        AlertDialog.Builder builder = new AlertDialog.Builder(HiDualNetActivity.this);
        builder.setTitle("Please Input:");
        builder.setView(textEntryView);
        builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                editTExt1 = (EditText) textEntryView
                        .findViewById(R.id.edit_text_1);
                editTExt2 = (EditText) textEntryView
                        .findViewById(R.id.edit_text_2);
                editTExt3 = (EditText) textEntryView
                        .findViewById(R.id.edit_text_3);

                Destination = editTExt1.getText().toString();
                gateway = editTExt2.getText().toString();
                netmask = editTExt3.getText().toString();

                iNetmask = NetworkUtils.numericToInetAddress(netmask);
                nm = NetworkUtils.inetAddressToInt(iNetmask);
                prefix_length = NetworkUtils.netmaskIntToPrefixLength(nm);
                switch (id) {
                case R.id.button3:
                    mHiNetworkUtils.addRoute(INTERFACE, Destination,
                            prefix_length, gateway);
                    break;
                case R.id.button4:
                    mHiNetworkUtils.removeRoute(INTERFACE, Destination,
                            prefix_length, gateway);
                    break;
                default:
                    break;
                }
            }
        });
        builder.setNegativeButton("Cancel", null);
        return builder.create();
    }

    private Dialog buildDialog2() {
        LayoutInflater inflater = LayoutInflater.from(this);
        final View textEntryView = inflater.inflate(R.layout.alert_dialog_2,
                null);
        AlertDialog.Builder builder = new AlertDialog.Builder(HiDualNetActivity.this);
        // builder.setIcon(R.drawable.alert_dialog_icon);
        builder.setTitle("Please Input:");
        builder.setView(textEntryView);
        builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                editTExt1 = (EditText) textEntryView
                        .findViewById(R.id.edit_text_1);

                gateway = editTExt1.getText().toString();
                mHiNetworkUtils.setDefaultRoute(INTERFACE, gateway);
            }
        });
        builder.setNegativeButton("Cancel", null);
        return builder.create();
    }

    private Dialog buildDialog3() {
        LayoutInflater inflater = LayoutInflater.from(this);
        final View textEntryView = inflater.inflate(R.layout.alert_dialog_3,
                null);
        AlertDialog.Builder builder = new AlertDialog.Builder(HiDualNetActivity.this);
        builder.setTitle("Please Input:");
        builder.setView(textEntryView);
        builder.setPositiveButton("OK", new DialogInterface.OnClickListener() {
            public void onClick(DialogInterface dialog, int whichButton) {
                editTExt1 = (EditText) textEntryView
                        .findViewById(R.id.edit_text_1);

                String key = editTExt1.getText().toString();
                if (null != key && !"".equals(key)) {
                    getIPaddress(key);
                }
            }
        });
        builder.setNegativeButton("Cancel", null);
        return builder.create();
    }

    public void onClick(View v) {
        switch (v.getId()) {
        case R.id.button1:
            // enable second ethernet
            if (HiNetworkUtils.INTERFACE_STATUS_NO_INTERFACE == mHiNetworkUtils
                    .getNetlinkStatus(INTERFACE)) {
                Log.e(TAG, "interface " + INTERFACE + " not exist!!");

                // Toast.makeText().show();
                return;
            }

            mHiNetworkUtils.enableInterface(INTERFACE);
            mHiNetworkUtils.releaseDhcp(INTERFACE);
            mHiNetworkUtils.runDhcp(INTERFACE);
            break;
        case R.id.button2:
            // disable second ethernet
            mHiNetworkUtils.removeDnses(INTERFACE);
            mHiNetworkUtils.releaseDhcp(INTERFACE);
            mHiNetworkUtils.disableInterface(INTERFACE);
            break;
        case R.id.button3:
            // add route. Input: Destination address, gateway address, netmask
            // address

            buildDialog(R.id.button3).show();
            break;
        case R.id.button4:
            // delete route. Input: Destination address, gateway address,
            // netmask address

            buildDialog(R.id.button4).show();
            break;
        case R.id.button5:
            // add default route. Input: gateway address

            buildDialog2().show();
            break;
        case R.id.button6:
            // delete default route.
            mHiNetworkUtils.removeDefaultRoute(INTERFACE);
            break;
        case R.id.button7:
            // set dns for current app
            mHiNetworkUtils.setDnses(INTERFACE);
            break;
        case R.id.button8:
            // delete dns for current app
            mHiNetworkUtils.removeDnses(INTERFACE);
            break;
        case R.id.button9:
            // get all information for interface
            String ipaddr = mHiNetworkUtils.getIpaddr(INTERFACE);
            String netmask = mHiNetworkUtils.getNetmask(INTERFACE);
            String gateway = mHiNetworkUtils.getGateway(INTERFACE);
            Collection<String> mDnses = mHiNetworkUtils.getDnses(INTERFACE);
            Iterator<String> dnses = mDnses.iterator();
            if (!dnses.hasNext()) {
                Log.e(TAG, "getDnses:can not get DNS!!");
                return;
            }

            StringBuffer str = new StringBuffer();
            if (null != ipaddr && !"".equals(ipaddr)) {
                str.append("ipaddr : ").append(ipaddr).append("\r\n");
            }
            if (null != netmask && !"".equals(netmask)) {
                str.append("netmask : ").append(netmask).append("\r\n");
            }
            if (null != gateway && !"".equals(gateway)) {
                str.append("gateway : ").append(gateway).append("\r\n");
            }

            String dns = dnses.next();
            int i = 1;
            while (null != dns) {
                Log.i(TAG, "Dns" + i + ": " + dns);
                str.append("Dns" + i + " : ").append(dns).append("\r\n");
                i++;
                if (!dnses.hasNext()) {
                    Log.i(TAG, "getDnses:no Dns" + i);
                    break;
                }
                dns = dnses.next();
            }
            int defaultRoute = mHiNetworkUtils.getDefaultRoute(INTERFACE);
            if (defaultRoute != 0) {
                InetAddress idefaultRoute = NetworkUtils
                        .intToInetAddress(defaultRoute);
                String defRoute = idefaultRoute.getHostAddress();
                Log.i(TAG, "default Rouote: " + defRoute);
            }
            textView1.setText(str.toString());
            break;
        case R.id.button10:
            // getIp input url
            buildDialog3().show();
            break;
        default:
            break;
        }
    }

    public void getIPaddress(final String key) {
        new Thread() {
            @Override
            public void run() {
                Log.i(TAG, "getIPaddress myPid=" + Process.myPid());
                URL url = null;
                try {
                    url = new URL(key);
                } catch (MalformedURLException e1) {
                    e1.printStackTrace();
                }
                System.out.println(url.getHost());
                InetAddress address = null;
                try {
                    address = InetAddress.getByName(url.getHost());
                } catch (UnknownHostException e) {
                    e.printStackTrace();
                }
                if (null != address) {
                    resolvedIpaddress = address.toString();
                    Message msg = new Message();
                    handler.sendMessage(msg);
                    Log.i(TAG, "ipaddress=" + resolvedIpaddress);
                } else {
                    Log.i(TAG, "address is null");
                }
            }
        }.start();
    }

    @Override
    protected void onResume() {
        super.onResume();
        regist();
    }

    private void regist() {
        IntentFilter filter = new IntentFilter();
        filter.addAction(HiNetworkUtils.HINETWORKUTILS_NETWORK_STATE_CHANGED_ACTION);
        registerReceiver(receiver, filter);
    }

    @Override
    protected void onDestroy() {
    	super.onDestroy();
        if (null != receiver) {
            unregisterReceiver(receiver);
        } 
    }

    @Override
    protected void onStop() {
    	super.onStop();
    }

    private class MyBroadcastReceiver extends BroadcastReceiver {
        @Override
        public void onReceive(Context context, Intent intent) {
            String action = intent.getAction();

            if (HiNetworkUtils.HINETWORKUTILS_NETWORK_STATE_CHANGED_ACTION
                    .equals(action)) {
                // TODO
                int event = intent.getIntExtra(
                        HiNetworkUtils.EXTRA_NETWORK_STATE, -1);

                switch (event) {
                case HiNetworkUtils.EVENT_DHCP_CONNECT_SUCCESSED:
                    mHiNetworkUtils.setDnses(INTERFACE);
                    break;
                case HiNetworkUtils.EVENT_DHCP_DISCONNECT_SUCCESSED:
                    mHiNetworkUtils.removeDnses(INTERFACE);
                    break;
                default:
                    Log.i(TAG, "event = " + event);
                    break;
                }
            }
        }
    }
}
