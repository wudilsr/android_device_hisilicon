package com.HiMediaSample;

import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.util.Properties;

import android.util.Log;

/**
 * read configuration file
 */

public class PropertyManager {

	private static final String TAG = "PropertyManager";
	// Maintain one instance of a PropertyManager object
	private static PropertyManager manager = null;
	// synchronize uses this to lock on
	private static Object managerLock = new Object();

	private static String propsconfig = "config.properties";

	private static Properties config = null;


	PropertyManager() {
		if (config == null)
			config = loadProps(propsconfig);
	}

	public final static PropertyManager getInstance() {
		if (manager == null) {
			synchronized (managerLock) {
				if (manager == null) {
					manager = new PropertyManager();
				}
			}
		}
		return manager;
	}

	private Properties loadProps(String name) {
		Properties props = new Properties();
		InputStream is = null;
		try {

			Runtime.getRuntime().exec("chmod 777" + "/data/data/config.properties");
			is = new FileInputStream(new File("/data/data/config.properties"));
			props.load(is);
			Log.d(TAG, "## load /data/data/config.properties sucess");
		} catch (IOException ioe) {
			System.err.println("Error reading  properties file " + name + " "
					+ ioe);
			ioe.printStackTrace();
		} finally {
			try {
				if (is != null)
					is.close();
			} catch (IOException e) {
			}
		}
		return props;
	}

	public String getConfigProperty(String name) {
		String value = config.getProperty(name);
		return value == null ? "" : value;
	}
}
