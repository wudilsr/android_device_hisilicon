/*
 * String.cpp
 *****************************************************************************
 * Copyright (C) 2012, bitmovin Softwareentwicklung OG, All Rights Reserved
 *
 * Email: libdash-dev@vicky.bitmovin.net
 *
 * This source code and its use and distribution, is subject to the terms
 * and conditions of the applicable license agreement.
 *****************************************************************************/

#include "String.h"

using namespace dash::helpers;

void    String::Split   (const std::string &s, char delim, std::vector<std::string>& vector)
{
    std::stringstream           ss(s);
    std::string                 item;

    while(std::getline(ss, item, delim))
        vector.push_back(item);
}
void    String::Split   (const std::string &s, char delim, std::vector<uint32_t>& vector)
{
    size_t lengthOfString = s.length();
    size_t pos = 0;
    size_t i = 0;
    uint32_t level = 0;

    while (pos != std::string::npos) 
    {
        pos = s.find(' ',i);

        if (i < lengthOfString)
        {
            level = strtoul(s.substr(i, pos-i).c_str(), NULL, 10);
            vector.push_back(level);
            i = pos + 1;
        }
    }
}
bool    String::ToBool  (const std::string &s)
{
    if (s == "true" || s == "True" || s == "TRUE") 
    {
        return true;
    }
    else
    {
        return false;
    }
}

double  String::timeToSeconds(const std::string& time)
{
    int      h = 0,m = 0;
    float    s = 0.0;
    double result;

    if (time.find("H") != std::string::npos)
    {
        sscanf(time.c_str(), "PT%dH%dM%fS", &h, &m, &s);
    }
    else if (time.find("M") != std::string::npos)
    {
        sscanf(time.c_str(), "PT%dM%fS" ,&m, &s);
    }
    else
    {
        sscanf(time.c_str(), "PT%fS" ,&s);
    }

    result = h*3600 + m * 60 + s;

  //  dash_log("[%s,%d] time:%s -> hour:%d,minute:%d, seconds:%f, covert to senconds %lf\n", __FUNCTION__, __LINE__, time.c_str(), h, m ,s, result);

    return result;
}

int  String::secondsToTime(std::string& time, double seconds)
{
    int      h = 0,m = 0;
    int64_t integer = (int64_t) seconds;
    float    decimal = seconds - integer;
    float    s = 0.0;
    char    str[16];//hhHmmMxx.xxxS

    h = integer/3600;
    m = (integer%3600)/60;
    s  = integer%60;
    s  = s + decimal;

    if (h == 0 && m == 0)
    {
        snprintf(str, sizeof(str), "PT%02.2fS", s);
    }
    else if (h == 0)
    {
        snprintf(str, sizeof(str), "PT%02dM%02.2fS", m, s);
    }
    else
    {
        snprintf(str, sizeof(str), "PT%02dH%02dM%02.2fS", h, m, s);
    }

    time.assign(str);

 //   dash_log("[%s,%d] senconds %lf(hour:%d,minute:%d, seconds:%f) ->time:%s \n", __FUNCTION__, __LINE__, seconds, h, m ,s, time.c_str());

    return 0;
}

