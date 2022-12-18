#include <stddef.h>
#include "hisidns.h"

SnifferFun gSnifferFun = {NULL, NULL};
IpFilterFun gIpFilterFun = {NULL};

mStatus mDNS_Init_With_Sniffer(mDNS *const m, mDNS_PlatformSupport *const p,
        CacheEntity *rrcachestorage, mDNSu32 rrcachesize,
        mDNSBool AdvertiseLocalAddresses,
        mDNSCallback *Callback, void *Context, SnifferFun sniffer)
{
    gSnifferFun = sniffer;
    return mDNS_Init(m, p, rrcachestorage, rrcachesize, AdvertiseLocalAddresses, Callback, Context);
}

mStatus mDNS_RegisterService_With_IpFilter(mDNS *const m, ServiceRecordSet *sr,
        const domainlabel *const name, const domainname *const type, const domainname *const domain,
        const domainname *const host, mDNSIPPort port, const mDNSu8 txtinfo[], mDNSu16 txtlen,
        AuthRecord *SubTypes, mDNSu32 NumSubTypes, mDNSInterfaceID InterfaceID,
        mDNSServiceCallback Callback, void *Context, mDNSu32 flags, IpFilterFun ipfilter)
{
    gIpFilterFun = ipfilter;
    return mDNS_RegisterService(m, sr, name, type, domain, host, port, txtinfo, txtlen, SubTypes, NumSubTypes, InterfaceID, Callback, Context, flags);
}
