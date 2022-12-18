package com.hisilicon.dlna.dmc.processor.upnp.mediaserver;

import org.teleal.cling.support.connectionmanager.ConnectionManagerService;
import org.teleal.cling.support.model.ProtocolInfo;
import org.teleal.cling.support.model.ProtocolInfos;

public class LocalConnectionManagerService extends ConnectionManagerService {
	public LocalConnectionManagerService() {
		super(
				new ProtocolInfos(
						new ProtocolInfo(
								"http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_LRG;DLNA.ORG_FLAGS=8cf00000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_MED;DLNA.ORG_FLAGS=8cf00000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:image/jpeg:DLNA.ORG_PN=JPEG_SM;DLNA.ORG_FLAGS=8cf00000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:audio/L16:DLNA.ORG_PN=LPCM;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:audio/mpeg:DLNA.ORG_PN=MP3;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=AVC_TS_HD_60_AC3_T;SONY.COM_PN=AVC_TS_HD_60_AC3_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=AVC_TS_HD_50_AC3_T;SONY.COM_PN=AVC_TS_HD_50_AC3_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=AVC_TS_HD_60_AC3;SONY.COM_PN=AVC_TS_HD_60_AC3;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=AVC_TS_HD_50_AC3;SONY.COM_PN=AVC_TS_HD_50_AC3;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=AVC_TS_HD_60_AC3_ISO;SONY.COM_PN=AVC_TS_HD_60_AC3_ISO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=AVC_TS_HD_50_AC3_ISO;SONY.COM_PN=AVC_TS_HD_50_AC3_ISO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=AVC_TS_HD_EU_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=AVC_TS_HD_EU;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=AVC_TS_HD_EU_ISO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_KO_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_KO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_NA_ISO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_KO_ISO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_JP_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_NA_MPEG1_L2_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_60_L2_T;SONY.COM_PN=HD2_60_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:DLNA.ORG_PN=MPEG_TS_HD_50_L2_T;SONY.COM_PN=HD2_50_T;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_NA_MPEG1_L2_ISO;DLNA.ORG_FLAGS=8d700000000000000000000000000000"),
						new ProtocolInfo(
								"http-get:*:video/mpeg:DLNA.ORG_PN=MPEG_TS_HD_60_L2_ISO;SONY.COM_PN=HD2_60_ISO"),
						new ProtocolInfo("http-get:*:image/jpeg:*"), new ProtocolInfo("http-get:*:audio/mpeg:*"),
						new ProtocolInfo("http-get:*:audio/L16:*"), new ProtocolInfo("http-get:*:audio/x-ms-wma:*"),
						new ProtocolInfo("http-get:*:video/mpeg:*"), new ProtocolInfo(
								"http-get:*:video/vnd.dlna.mpeg-tts:*"), new ProtocolInfo("http-get:*:video/mp4:*"),
						new ProtocolInfo("http-get:*:video/x-msvideo:*"),
						new ProtocolInfo("http-get:*:video/x-divx:*"), new ProtocolInfo("http-get:*:video/divx:*"),
						new ProtocolInfo("http-get:*:video/avi:*"), new ProtocolInfo("http-get:*:video/x-ms-wmv:*"),
						new ProtocolInfo("http-get:*:video/x-ms-asf:*"), new ProtocolInfo("http-get:*:video/*:*"),
						new ProtocolInfo("http-get:*:audio/*:*"), new ProtocolInfo("http-get:*:image/*:*")), null);
	}
}
