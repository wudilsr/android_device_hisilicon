/*
 * MSPR.cpp
 *****************************************************************************

 *****************************************************************************/


#include "MSPR.h"

using namespace std;
using namespace dash::mpd;

MSPR::MSPR                              ():
    pro             (""),
    isEncrypted     (""),
    iv_size         (""),
    kid             ("")
{

}

MSPR::~MSPR                             ()
{

}

void        MSPR::SetPRO                (const string& pro)
{
    this->pro = pro;
}

string      MSPR::GetPRO                ()  const
{
    return this->pro;
}

void        MSPR::SetIsEncrypted        (const string& isEncrypted)
{
    this->isEncrypted = isEncrypted;
}

string      MSPR::GetIsEncrypted        ()  const
{
    return this->isEncrypted;
}

void        MSPR::SetIV_size            (const string& iv_size)
{
    this->iv_size = iv_size;
}

string      MSPR::GetIV_size            ()  const
{
    return this->iv_size;
}

void        MSPR::SetKID                (const string& kid)
{
    this->kid = kid;
}

string      MSPR::GetKID                ()  const
{
    return this->kid;
}