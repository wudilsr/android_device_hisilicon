package com.hisilicon.dlna.dmc.gui.customview;

public enum MediaType {
	IMAGE(0), VIDEO(1), MUSIC(2), LIVETV(3), UNKNOW(4);
	int index;
	
	private MediaType(int index) {
		this.index = index;
	}
	
	public int toInt() {
		return index;
	}
}
