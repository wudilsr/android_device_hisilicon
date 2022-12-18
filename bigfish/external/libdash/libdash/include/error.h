#ifndef ERROR_H_
#define ERROR_H_

enum DashErrorType
{
    DashError_Success = 0,
    DashError_Unknown = -1,
    DashError_EmptyMPD = -2
};

//must be identical with those defined in libxml2:libxml.h
#define HISIURL_END                 "?HiSiUrlEnd"
#define HISIURL_HTTPHEADERS  "HiSiHTTPHeaders="

#endif

