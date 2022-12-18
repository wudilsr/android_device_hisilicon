/*
 **************************************************************************************
 *       Filename:  CameraTypes.h
 *    Description:  Camera Type header file
 *
 *        Version:  1.0
 *        Created:  2012-05-23 14:19:14
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef CAMERATYPES_H_INCLUDED
#define CAMERATYPES_H_INCLUDED

namespace android
{

struct cameraBuffer
{
    size_t  offset;
    void*   start;
    size_t  length;
};

struct previewBuffer
{
    unsigned int index;
    void*        viraddr;
    unsigned int phyaddr;
    unsigned int flags;
    unsigned int length;
};

enum command
{
    CMD_START_PREVIEW       = 0x01,
    CMD_STOP_PREVIEW        = 0x02,
    CMD_TAKE_PICTURE        = 0x04,
    CMD_KILL_STATE_THREAD   = 0x08,
};

enum ack
{
    ACK_OK,
    ACK_ERROR,
};

}; // namespace android

#endif /*CAMERATYPES_H_INCLUDED*/

/********************************* END ***********************************************/
