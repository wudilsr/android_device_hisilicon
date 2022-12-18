/*
 * LogTest.cpp
 *
 *  Created on: 2014Äê9ÔÂ22ÈÕ
 *      Author: z00187490
 */
#include <stdarg.h>
#include <gtest/gtest.h>
#include <hi_svr_utils.h>

#define SVR_LOG_TAG "LogTest"

HI_VOID write(HI_VOID* opaque, const HI_CHAR* tag, HI_S32 level,
        HI_CHAR* fmt, va_list var)
{
    char buf[1024];
    vsnprintf(buf, sizeof(buf), fmt, var);
    printf("%s\n", buf);
}

TEST(LogTest, testWrite)
{
    SVR_LOG_Write(SVR_LOG_TAG, SVR_LOG_VERBOSE, "test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOG_Write(SVR_LOG_TAG, SVR_LOG_DEBUG, "test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOG_Write(SVR_LOG_TAG, SVR_LOG_INFO, "test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOG_Write(SVR_LOG_TAG, SVR_LOG_WARN, "test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOG_Write(SVR_LOG_TAG, SVR_LOG_ERROR, "test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOG_Write(SVR_LOG_TAG, SVR_LOG_FATAL, "test log at[%s,%d]\n", __FUNCTION__, __LINE__);
}

TEST(LogTest, testMacro)
{
    SVR_LOGV("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGD("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGI("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGW("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGE("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGF("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
}

TEST(LogTest, testSetLevel)
{
    for (int i = SVR_LOG_QUIET; i < SVR_LOG_BUTT; i++)
    {
        SVR_LOG_SetLevel(i);
        SVR_LOGV("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
        SVR_LOGD("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
        SVR_LOGI("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
        SVR_LOGW("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
        SVR_LOGE("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
        SVR_LOGF("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    }
}


TEST(LogTest, testRepeate)
{
    SVR_LOG_SetLevel(SVR_LOG_ERROR);
    for ( int i = 0; i < 100; i++)
    {
        SVR_LOGE("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    }
    SVR_LOGE("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
}

TEST(LogTest, testWriter)
{
    SVR_LOG_WRITER_S writer;
    writer.write = write;
    writer.opaque = NULL;
    SVR_LOG_RegisterWriter(&writer);

    SVR_LOG_SetLevel(SVR_LOG_VERBOSE);
    SVR_LOGV("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGD("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGI("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGW("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGE("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
    SVR_LOGF("test log at[%s,%d]\n", __FUNCTION__, __LINE__);
}

