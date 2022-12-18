package com.hisilicon.dlna.dmc.receiver;

import java.net.NetworkInterface;

import org.teleal.cling.android.AndroidNetworkAddressFactory;
import org.teleal.cling.transport.SwitchableRouter;

import android.content.BroadcastReceiver;
import android.content.Context;
import android.content.Intent;
import android.net.ConnectivityManager;
import android.net.wifi.WifiManager;
import com.hisilicon.multiscreen.mybox.R;

import com.hisilicon.dlna.dmc.processor.upnp.mediaserver.HttpServerUtil;

public class NetworkStateReceiver extends BroadcastReceiver {
	private SwitchableRouter m_router;
	private RouterStateListener m_routerStateListener;
	private boolean m_disableWifiPending;
	protected int DISABLE_STATE_TIMEOUT = 10; // seconds
	private NetworkInterface m_interfaceCache = null;

	public NetworkStateReceiver(SwitchableRouter router, RouterStateListener routerStateListener) {
		m_router = router;
		m_routerStateListener = routerStateListener;
	}

	@Override
	public void onReceive(final Context context, Intent intent) {
		if (!intent.getAction().equals("android.net.conn.TETHER_STATE_CHANGED")
				&& !intent.getAction().equals(ConnectivityManager.CONNECTIVITY_ACTION) && !intent.getAction().equals("android.net.wifi.WIFI_AP_STATE_CHANGED"))
			return;
		NetworkInterface ni = AndroidNetworkAddressFactory.getWifiNetworkInterface(
				(WifiManager) context.getSystemService(Context.WIFI_SERVICE),
				(ConnectivityManager) context.getSystemService(Context.CONNECTIVITY_SERVICE));
		
		HttpServerUtil.updateHostAddress(ni);
		
		if (ni == null) {
			m_router.disable();
			m_routerStateListener.onRouterDisabled();
			m_disableWifiPending = true;
			new Thread(new Runnable() {
				@Override
				public void run() {
					try {
						for (int i = 0; i < DISABLE_STATE_TIMEOUT; ++i) {
							Thread.sleep(1000);
							if (m_disableWifiPending) {
								if (i == DISABLE_STATE_TIMEOUT - 1)
									if (m_routerStateListener != null)
										m_routerStateListener.onRouterError(context
												.getString(R.string.no_network_found));
							} else {
								break;
							}
						}
					} catch (InterruptedException e) {
					}

				}
			}).start();
		} else {
			m_router.enable();
			m_routerStateListener.onRouterEnabled();

			if (m_interfaceCache == null || !ni.equals(m_interfaceCache)) {
				m_routerStateListener.onNetworkChanged(ni);
			}
			m_interfaceCache = ni;

			m_disableWifiPending = false;
		}
	}

	public interface RouterStateListener {
		void onRouterError(String cause);

		void onNetworkChanged(NetworkInterface ni);

		void onRouterEnabled();

		void onRouterDisabled();
	}
}
