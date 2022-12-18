/*
 **************************************************************************************
 *       Filename:  CameraExtendedEnv.h
 *    Description:  Camera Extended Env header file
 *
 *        Version:  1.0
 *        Created:  2012-05-16 16:45:31
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERAEXTENDEDENV_H_INCLUDED
#define CAMERAEXTENDEDENV_H_INCLUDED

#include <utils/RefBase.h>
#include <utils/KeyedVector.h>
#include <utils/threads.h>
#include <hardware/camera.h>
#include "CameraRuntimeEnv.h"
#include "CameraObject.h"

namespace android
{

enum
{
    ENV_KEYOBJ_CAPABILITY_MANAGER,
    ENV_KEYOBJ_MAX
};

class CameraExtendedEnv : public CameraRuntimeEnv, public virtual RefBase
{
public:
    CameraExtendedEnv()
    {
        mNotifyCb           = NULL;
        mDataCb             = NULL;
        mDataCbTimeStamp    = NULL;
        mRequestMemory      = NULL;
        mUser               = NULL;
        mOps                = NULL;
    }
    void registerCameraObject(int key, CameraObject* obj)
    {
        Mutex::Autolock lock(&mMutex);
        mKeyObjects.replaceValueFor(key, obj);
    }

    void unregisterCameraObject(int key)
    {
        Mutex::Autolock lock(&mMutex);
        mKeyObjects.removeItem(key);
    }

    CameraObject* getCameraObject(int key)
    {
        return mKeyObjects.valueFor(key);
    }

public:
    Mutex mMutex;
    struct preview_stream_ops* mOps;
    DefaultKeyedVector<int, CameraObject*> mKeyObjects;

    /* callbacks */
    camera_notify_callback          mNotifyCb;
    camera_data_callback            mDataCb;
    camera_data_timestamp_callback  mDataCbTimeStamp;
    camera_request_memory           mRequestMemory;
    void*                           mUser;
};

}; /* namespace android */

#endif /*CAMERAEXTENDEDENV_H_INCLUDED*/

/********************************* END ***********************************************/
