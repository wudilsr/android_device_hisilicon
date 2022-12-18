package com.hisilicon.multiscreen.protocol.utils;


public interface ISpeechMsgDealer
{
    void pushSpeechInfo(String info, int type);

    void pushAudioData(byte[] audiodate, int seq);

    void startSpeaking();

    void stopSpeaking();

    void speakError(String error);
}
