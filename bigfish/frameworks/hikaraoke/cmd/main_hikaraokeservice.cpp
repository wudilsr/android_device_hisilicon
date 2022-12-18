#include <binder/IPCThreadState.h>
#include <pthread.h>
#include <binder/ProcessState.h>
#include <binder/IServiceManager.h>
#include <binder/BinderService.h>
#include <utils/Log.h>
#include <HikaraokeService.h>
using namespace android;




int main(int argc, char** argv)
{
    sp<ProcessState> proc(ProcessState::self());
    HiKaraokeService::instantiate();
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();
    return 0;
}
