extern "C"
{
#include "libavcodec/avcodec.h"
#include "Hies_proto.h"
}

#include "HiRtspClient.h"
#include "HiMLoger.h"

#define TAG "HiRtspClient"

HiRtspClient::HiRtspClient(const char* url)
:HiProtocol(url)
{
    bConnected = 0;
}

HiRtspClient::~HiRtspClient()
{

}

int HiRtspClient::connect()
{
    int ret  = 0;
    char* url = mUrl;
    ret= HI_HIES_Init_Proto();
    if(ret != 0)
    {
        MMLOGE(TAG, "HI_HIES_Init_Proto error\n");
        return -1;
    }
    ret = HI_HIES_Connect(url);
    if(ret != 0)
    {
        MMLOGE(TAG, "HI_HIES_Connect error\n");
        HI_HIES_DeInit_Proto();
        return -1;
    }
    bConnected = 1;
    return ret;
}

int HiRtspClient::disconnect()
{
    int ret  = 0;
    MMLOGI(TAG, "HiRtspClient disconnect\n");
    if(bConnected)
    {
        ret= HI_HIES_DeInit_Proto();
        if(ret != 0)
        {
            MMLOGE(TAG, "HI_HIES_DeInit_Proto error\n");
            return -1;
        }
        bConnected = 0;
    }
}

int HiRtspClient::getSPSPPS(void* sps, int *spsSize, void* pps, int* ppsSize)
{
    int ret = 0;
    ret = HI_HIES_GetParameterFrame((HI_U8*)sps, spsSize,(HI_U8*)pps, ppsSize);
    if(ret != 0)
    {
        MMLOGE(TAG, "HI_HIES_GetParameterFrame error\n");
        return -1;
    }
    return 0;
}

int HiRtspClient::getVideoWidth()
{
    return HI_HIES_GetVideoWidth();
}

int HiRtspClient::getVideoHeight()
{
    return HI_HIES_GetVideoHeight();
}

int HiRtspClient::readVideoStream(void* ptr, int& dataSize, int64_t& pts, int& ptype)
{
    int iSize = dataSize;
    int64_t  iPts = 0;
    int iPtype = 0;
    if(HI_HIES_read_video_stream(ptr, &iSize, &iPts, &iPtype) <0)
    {
        MMLOGE(TAG, "HI_HIES_read_video_stream failed");
        return -1;
    }

    dataSize = iSize;
    pts = iPts;
    ptype = iPtype;
    return 0;
}

int HiRtspClient::readAudioStream(void* ptr, int& dataSize, int64_t& pts)
{
    int iSize = dataSize;
    int64_t  iPts = 0;
    int iPtype = 0;
    if(HI_HIES_read_audio_stream(ptr, &iSize, &iPts) <0)
    {
        MMLOGE(TAG, "HI_HIES_read_audio_stream failed");
        return -1;
    }

    dataSize = iSize;
    pts = iPts;
    return 0;
}


