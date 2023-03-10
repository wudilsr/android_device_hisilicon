/**
 *  config.h
 *
 *  @brief      Standard includes that are used by the library
 *  @details    ...
 *
 *  @author     bitmovin Softwareentwicklung OG \n
 *              Email: libdash-dev@vicky.bitmovin.net
 *  @version    2.1
 *  @date       2013
 *  @copyright  bitmovin Softwareentwicklung OG, All Rights Reserved \n\n
 *              This source code and its use and distribution, is subject to the terms
 *              and conditions of the applicable license agreement.
 */

#ifndef CONFIG_H_
#define CONFIG_H_

/********************************
 * Pragmas
 ********************************/
#pragma warning( disable : 4250 ) // virtual inheritance
/********************************
 * Standard includes
 ********************************/
#include <stdlib.h>
#include <string>
#include <sstream>
#include <vector>
#include <stdint.h>
#include <map>
#include <deque>
#include <iostream>
#include <cstdlib>
#include <string.h>
#include "log.h"
#include "error.h"
#include <stdio.h>
#if defined ANDROID_VERSION
#include <unistd.h>
#endif

#define SLEEP_TIME      (10 * 1000)    //10ms
#ifndef UINT32_MAX
#define UINT32_MAX      0xffffffff
#endif

#endif /* CONFIG_H_ */
