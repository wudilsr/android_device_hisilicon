package com.ctcims.avcodec;

public class PhonePlayer {
    static int RESOLUTION_176_144 = 0;
    static int RESOLUTION_320_240 = 1;
    static int RESOLUTION_352_288 = 2;
    static int RESOLUTION_640_480 = 3;
    static int RESOLUTION_1280_720 = 4;
    static int WINDOWN_LOCAL = 1;
    static int WINDOWN_REMOTE = 2;

    static {
        System.loadLibrary("videophone");
    }

    public native int AVInit();

    public native int AVDeinit();

    //checkspan:In milliseconds
    public native int setPacketCheckSpan(int checkspan);

    /*audioorvideo: 0 AUDIO  1 VIDEO
     *return: received:1  not:0
     */
    public native int checkPacket(int audioorvideo);

    /*item: PACKET_INRATE
     *      PACKET_OUTRATE
     *      PACKET_INLOSTRATE
     *      PACKET_INDELAYTIME
     *      VIDEO_WIDTH
     *      VIDEO_HEIGHT
    */
    public native double getStatics(String item);

    public native int initVideo(int resolution, int inX, int inY, int inWidth,
        int inHeight, int outX, int outY, int outWidth, int outHeight,
        int displayInit, int localFramerate);

    public native int videoStart(String localIp, int localPort,
        String remoteIp, int remotePort, int frmRate, int payload, int vbrrate,
        int gop);

    public native int videoStop();

    public native int deInitVideo();

    public native int disableLocalVideo();

    public native int enableLocalVideo();

    public native int disableRemoteVideo();

    public native int enableRemoteVideo();

    public native int showWindow(int window, int showorhide);

    public native int setWindowZorder(int window, int zorder);

    public native int moveWindow(int window, int destx, int desty,
        int destWidth, int height);

    public native int getOptionalConfig(int optionaltype);

    public native int setOptionalConfig(int optionaltype, int value);

    public native int initAudio();

    public native int deInitAudio();

    public native int audioStart(String localip, int localport,
        String remoteip, int remoteport);

    public native int audioStop();

    public native int setAudioCodec(String codecname, int codecnumber,
        int samlerate, int samplesize, int framerate, int framesize,
        int channelcount);

    public native int setAudioParam(String paramname, String paramvalue);

    public native int setVolume(int stream, int volume);

    public native int getVolume(int stream);

    public native int mute(int stream);

    public native int unmute(int stream);

    public native int enableAEC(int enable);

    public native int enableANS(int enable);

    public native int enableAGC(int enable);

    public native int enableVAD(int enable);

    public native int sendDTMF(int type, int payloadtype, char dtmf);
}
