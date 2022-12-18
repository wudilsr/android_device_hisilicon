/*
 * HiMediaLogger.h
 *
 *  Created on: 2014Äê5ÔÂ28ÈÕ
 *      Author: z00187490
 */

#ifndef HIMEDIALOGGER_H_
#define HIMEDIALOGGER_H_

#include <utils/threads.h>
#include <utils/Timers.h>
#include <utils/Looper.h>
#include <utils/String8.h>
#include <utils/Vector.h>
#include <stdio.h>

namespace android {
class WriteLogMsg;

class HiMediaLogger : public Thread
{
    class Handler : public MessageHandler {
        HiMediaLogger& mLogger;
    public:
        Handler(HiMediaLogger& logger) : mLogger(logger) { }
        virtual void handleMessage(const Message& message);
    };
    friend class Handler;
    friend class WriteLogMsg;
public:
    enum {
        MSG_WRITE_LOG = 0x1,
        MSG_SWICH_FILE = 0x2,
        MSG_CLEAR_FILE = 0x3,
        MSG_EXIT = 0x4,
    };
    status_t writeLog(const char* str);
    void exit();
    HiMediaLogger();
    HiMediaLogger(const char* logPath, int clearFilePeriodInS, int switchFilePeriodInS);
    ~HiMediaLogger();
private:
    void waitMessage();
    virtual bool threadLoop();
    virtual void onFirstRef();
    status_t postMessage(const sp<MessageHandler>& handler,
            const Message& msg, nsecs_t relTime);
    status_t handleWriteLog(const char* str);
    status_t handleSwitchFile();
    status_t handleClearFile();
    long long secondsToCalendar(int seconds);
    long long calendarToSeconds( long long  calendar);
    char* updateAsendListN(char **newestN, int size, int *empty, char *cur, int *needFree);

private:
    sp<Looper> mLooper;
    sp<Handler> mHandler;
    FILE* mFile;
    int mClearFilePeriod;
    int mSwitchFilePeriod;
    String8 mLogPath;
    Vector<String8> mFileVdec;
    int mExitRequested;
};


} /* namespace android */
#endif /* HIMEDIALOGGER_H_ */
