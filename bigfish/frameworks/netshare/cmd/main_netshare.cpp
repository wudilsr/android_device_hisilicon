#include <binder/IPCThreadState.h>
#include <pthread.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/BinderService.h>
#include <fcntl.h>
#include <HiNSService.h>

#include <utils/Log.h>

#define LOG_TAG "NetShareService"
using namespace android;

int main(int argc, char** argv)
{
    sp<ProcessState> proc(ProcessState::self());
    HiNSService::instantiate();
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
