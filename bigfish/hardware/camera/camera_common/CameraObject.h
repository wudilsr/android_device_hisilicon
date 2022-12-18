/*
 **************************************************************************************
 *       Filename:  CameraObject.h
 *    Description:  Camera Object header file
 *
 *        Version:  1.0
 *        Created:  2011-05-16 16:24:18
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERAOBJECT_H_INCLUDED
#define CAMERAOBJECT_H_INCLUDED

class CameraObject
{
public:
    CameraObject(void* env)
    {
        mEnv = env;
    }
    virtual ~CameraObject()
    {
    }

protected:
    void* mEnv;
};

#endif /*CAMERAOBJECT_H_INCLUDED*/

/********************************* END ***********************************************/
