#include "mDNSEmbeddedAPI.h"
#include "mDNSPosix.h"

typedef void (*QuerySnifferFun)(const DNSMessage *const msg, mDNSu8 *end,
        const mDNSAddr *srcaddr, const mDNSAddr *dstaddr, const mDNSInterfaceID InterfaceID);

typedef void (*ResponseSnifferFun)(mDNS *const m, const DNSMessage *const response, mDNSu8 *end,
        const mDNSAddr *srcaddr, const mDNSAddr *dstaddr, const mDNSInterfaceID InterfaceID);

typedef mDNSBool (*BlackIpFilterFun)(const mDNSv4Addr *addr);

typedef struct __SnifferFun
{
    QuerySnifferFun queryFun;
    ResponseSnifferFun responseFun;
} SnifferFun;

typedef struct __IpFilterFun
{
    BlackIpFilterFun blackIpFun;
} IpFilterFun;

mStatus mDNS_Init_With_Sniffer(mDNS *const m, mDNS_PlatformSupport *const p,
        CacheEntity *rrcachestorage, mDNSu32 rrcachesize,
        mDNSBool AdvertiseLocalAddresses,
        mDNSCallback *Callback, void *Context, SnifferFun sniffer);

mStatus mDNS_RegisterService_With_IpFilter(mDNS *const m, ServiceRecordSet *sr,
        const domainlabel *const name, const domainname *const type, const domainname *const domain,
        const domainname *const host, mDNSIPPort port, const mDNSu8 txtinfo[], mDNSu16 txtlen,
        AuthRecord *SubTypes, mDNSu32 NumSubTypes, mDNSInterfaceID InterfaceID,
        mDNSServiceCallback Callback, void *Context, mDNSu32 flags, IpFilterFun ipfilter);
