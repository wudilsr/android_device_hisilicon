#include <string.h>
#include <jni.h>
    int setIpMode(int flag);

    int getIpMode();

    int setAudioMode(int index);

    int getAudioMode();

    int getSaveMode();

    int setOutputFormat(int flag);

    int getOutputFormat();

    jintArray getPosition();

    int setPosition(int l, int t, int w, int h ,int mode);

    int restoreFactorySettings();

    int setDate(int year, int month, int day);

    int setTime(int hourOfDay, int minute);

    int setTimeFormat(int timeFormat );

    int getTimeFormat();

    int setDateFormat(jstring dateFormat);

    jstring getDateFormat();

    int setAutotime(int Autotime);

    int getAutotime();

    int setAutoTimeZone(int autoTimeZone);

    int getAutoTimeZone();

    int setTimeZone(jstring timeZone);

    jstring getTimeZone();

    int setResolution(int index);

    int getResolution();
