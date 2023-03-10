#ifndef UPNPINET_H
#define UPNPINET_H

/*!
 * \addtogroup Sock
 *
 * @{
 *
 * \file
 *
 * \brief Provides a platform independent way to include TCP/IP types and functions.
 */

/*lint -save -e* */

#include "UpnpUniStd.h" /* for close() */

#ifdef WIN32
    #include <stdarg.h>
    #include <windef.h>
    #include <winbase.h>
    #include <winsock2.h>
    #include <iphlpapi.h>
    #include <ws2tcpip.h>

    #define UpnpCloseSocket closesocket
#else /* WIN32 */
    #include <sys/param.h>
    #if defined(__sun)
        #include <fcntl.h>
        #include <sys/sockio.h>
    #elif (defined(BSD) && BSD >= 199306) || defined (__FreeBSD_kernel__)
        #include <ifaddrs.h>
        /* Do not move or remove the include below for "sys/socket"!
         * Will break FreeBSD builds. */
        #include <sys/socket.h>
    #endif
    #include <arpa/inet.h>  /* for inet_pton() */
    #include <net/if.h>
    #include <netinet/in.h>

    /*! This typedef makes the code slightly more WIN32 tolerant.
     * On WIN32 systems, SOCKET is unsigned and is not a file
     * descriptor. */
    typedef int SOCKET;

    /*! INVALID_SOCKET is unsigned on win32. */
    #define INVALID_SOCKET (-1)

    /*! select() returns SOCKET_ERROR on win32. */
    #define SOCKET_ERROR (-1)

    /*! Alias to close() to make code more WIN32 tolerant. */
    #define UpnpCloseSocket close
#endif /* WIN32 */

/* @} Sock */

/*lint -restore * */

#endif /* UPNPINET_H */
