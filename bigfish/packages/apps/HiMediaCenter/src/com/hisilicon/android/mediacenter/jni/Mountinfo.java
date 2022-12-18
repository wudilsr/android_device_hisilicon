package com.hisilicon.android.mediacenter.jni;

public class Mountinfo {

	// services ip address
	private String szSvrIP;

	// services file path
	private String szSvrFold;

	// local file path
	private String szCltFold;

	// Whether automatically mount
	// CNcomment: 是否自动挂载
	private int ucIsAuto;

	// Whether automatically mount successful
	// CNcomment:是否挂载成功
	private int ucIsMounted;

	// server name
	private String pcName;

	/**
	 * Get whether to mount success-bit CNcomment: 获取是否挂载成功位
	 * @return 0:mount successful ; 1:mount fail
	 */
	public int getUcIsMounted() {
		return ucIsMounted;
	}

	/**
	 * set whether to mount successful CNcomment: 设置是否挂载成功
	 * @param ucIsMounted
	 *            0:successful；1:fail
	 */
	public void setUcIsMounted(int ucIsMounted) {
		this.ucIsMounted = ucIsMounted;
	}

	/**
	 * get server ip address
	 * @return
	 */
	public String getSzSvrIP() {
		return szSvrIP;
	}

	/**
	 * set server ip address
	 * @param szSvrIP
	 */
	public void setSzSvrIP(String szSvrIP) {
		this.szSvrIP = szSvrIP;
	}

	/**
	 * get server file path
	 * @return
	 */
	public String getSzSvrFold() {
		return szSvrFold;
	}

	/**
	 * set server file path
	 * @param szSvrFold
	 */
	public void setSzSvrFold(String szSvrFold) {
		this.szSvrFold = szSvrFold;
	}

	/**
	 * get local file path
	 * @return
	 */
	public String getSzCltFold() {
		return szCltFold;
	}

	/**
	 * set local file path
	 * @param szCltFold
	 */
	public void setSzCltFold(String szCltFold) {
		this.szCltFold = szCltFold;
	}

	/**
	 * was whether to automatically mount the logo
	 * CNcomment:获得是否自动挂载标识
	 * @return
	 */
	public int getUcIsAuto() {
		return ucIsAuto;
	}

	/**
	 * settings are automatically mounted logo
	 * @param ucIsAuto
	 */
	public void setUcIsAuto(int ucIsAuto) {
		this.ucIsAuto = ucIsAuto;
	}

	public String getPcName() {
		return pcName;
	}

	public void setPcName(String pcName) {
		this.pcName = pcName;
	}
}
