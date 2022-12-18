/*
 **************************************************************************************
 *       Filename:  CapabilityInterface.h
 *    Description:  Camera Parameter Interface header file
 *
 *        Version:  1.0
 *        Created:  2012-05-11 17:59:03
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */
#ifndef CAPABILITYINTERFACE_H_INCLUDED
#define CAPABILITYINTERFACE_H_INCLUDED

#include "CameraExtendedEnv.h"

namespace android
{

class CapabilityInterface
{
public:
    CapabilityInterface(void *env)
    {
        mEnv        = env;
        mCameraFd   = ((CameraExtendedEnv*)mEnv)->mCameraFd;
        changed     = 1;
    }

    virtual ~CapabilityInterface() { };
    virtual int queryCapability(CameraParameters& p) = 0;
    virtual int setParameter(CameraParameters& p) = 0;
    virtual int commitParameter() = 0;

protected:
    int     mCameraFd;
    int     changed;
    void*   mEnv;
};

class CameraParameterObserver
{
public:
    virtual ~CameraParameterObserver() {};
    virtual int onValueChanged(CapabilityInterface* who, CameraParameters& p) {return 0;};
};

class CameraParameterObject
{
public:
    virtual ~CameraParameterObject() {};
    virtual int registerObserver(CameraParameterObserver* obj) { mObservers.add(obj); return 0;}

protected:
    Vector<CameraParameterObserver*> mObservers;
};

};  /* namespace android */

#endif /*CAPABILITYINTERFACE_H_INCLUDED*/

/********************************* END ***********************************************/
