/*
 **************************************************************************************
 *       Filename:  PipeMessage.h
 *    Description:  Pipe Message header file
 *
 *        Version:  1.0
 *        Created:  2012-05-24 20:14:54
 *         Author:
 *
 *       Revision:  initial draft;
 **************************************************************************************
 */

#ifndef PIPEMESSAGE_H_INCLUDED
#define PIPEMESSAGE_H_INCLUDED

namespace android {

class PipeMessage
{
public:
    PipeMessage();
    ~PipeMessage();

    int get(int*);
    int put(int*);

private:
    int mFdRead;
    int mFdWrite;
};

}; // namespace android

#endif /*PIPEMESSAGE_H_INCLUDED*/

/********************************* END ***********************************************/
