package com.hisilicon.dlna.dmc.processor.upnp.mediaserver;

public class MediaInitException extends Exception {

	private static final long serialVersionUID = 1L;

	public MediaInitException(){
		super();
	}
	
	public MediaInitException(String msg){
		super(msg);
	}
	
	public MediaInitException(String msg, Throwable cause){
		super(msg, cause);
	}
	
	public MediaInitException(Throwable cause){
		super(cause);
	}
}
