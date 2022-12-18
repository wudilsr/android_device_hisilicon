#ifndef __RTKBT_COMMON_H__
#define __RTKBT_COMMON_H__

#define RTKBT_RCUID_MDT        (1)
#define RTKBT_RCUID_IFLYTEK    (2)

extern UINT32  remote_controller_id;
static inline UINT32  rtkbt_getRealRcuID(UINT32 remote_controller_id)
{
    if(remote_controller_id < 256)
        return remote_controller_id;
    else
        return (remote_controller_id >> 8);
}

#endif
