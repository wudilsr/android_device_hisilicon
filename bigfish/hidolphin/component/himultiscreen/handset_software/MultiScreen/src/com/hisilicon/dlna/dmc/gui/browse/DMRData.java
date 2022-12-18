package com.hisilicon.dlna.dmc.gui.browse;

public class DMRData {
	private static DMRData mDMRData;
	
	private DMRData(){
		
	}
	
	public static DMRData getInstance(){
		if(mDMRData==null)
			mDMRData = new DMRData();
		return mDMRData;
	}

}
