#ifndef __TLS_ADP_H__
#define __TLS_ADP_H__

#include "hi_type.h"

#ifdef __cplusplus
#if __cplusplus
extern "C" {
#endif
#endif /* __cplusplus */

#define TLS_POLLIN     0x0001  /* any readable data available */
#define TLS_POLLOUT    0x0002  /* file descriptor is writeable */
/* revents only */
#define TLS_POLLERR    0x0004  /* errors pending */

HI_VOID TLS_init();
HI_VOID TLS_deinit();

/**
\brief create a tls handle
\attention \n
None
\param [in] fd socket handle
\param [in] host  host name
\param [in] port  connect port
\param [out] ptlsHdl tls handle

\retval ::1 tls handle create success
\retval ::<=0 The parameter is invalid.

\see \n
None
*/
HI_S32 TLS_create(HI_S32 fd, HI_CHAR *host, HI_S32 port, HI_U32 *ptlsHdl);

/**
\brief initiates the TLS/SSL handshake with a server.
\attention \n
None
\param [in] tlsHdl tls handle

\retval ::1 The TLS/SSL handshake was successfully completed
\retval ::0 The TLS/SSL handshake was not successful but was shut down controlled and by the specifications of the TLS/SSL protocol.
Call TLS_getConnectError() with the return value ret to find out the reason.
\retval ::<0 The TLS/SSL handshake was not successful, because a fatal error occurred.

\see \n
None
*/
HI_S32 TLS_connect(HI_U32 tlsHdl);

/**
\brief returns a result code (suitable for the C ``switch'' statement) for a preceding call to TLS_connect(), TLS_read(), TLS_write() on ssl.
\attention \n
if the result code is TLS_POLLIN) or allows writing data (TLS_POLLOUT), then some TLS/SSL protocol progress will take place, i.e. at least
part of an TLS/SSL record will be read or written.
\param [in] tlsHdl tls handle

\retval ::TLS_POLLIN  should be writing
\retval ::TLS_POLLOUT   should be reading
\retval ::TLS_POLLERR   an error
\retval ::others operation invalid

\see \n
None
*/
HI_S32 TLS_getConnectError(HI_U32 tlsHdl, HI_S32 ret);

/**
\brief tries to read num bytes from the specified ssl into the buffer buf.
\attention \n
none
\param [in] tlsHdl tls handle
\param [in] buf  input buffer addr
\param [in] size  buffer size

\retval ::>0  The read operation was successful; the return value is the number of bytes actually read from the TLS/SSL connection.
\retval ::0  The read operation was not successful.
\retval ::<0 The read operation was not successful, because either an error occurred or action must be taken by the calling process.

\see \n
None
*/
HI_S32 TLS_read(HI_U32 tlsHdl, HI_U8 *buf, HI_S32 size);

/**
\brief writes num bytes from the buffer buf into the specified ssl connection.
\attention \n
none
\param [in] tlsHdl tls handle
\param [in] buf  input buffer addr
\param [in] size  buffer size

\retval ::>0  The write operation was successful, the return value is the number of bytes actually written to the TLS/SSL connection.
\retval ::0  The write operation was not successful. Probably the underlying connection was closed.
\retval ::<0 The write operation was not successful, because either an error occurred or action must be taken by the calling process.

\see \n
None
*/
HI_S32 TLS_write(HI_U32 tlsHdl, HI_U8 *buf, HI_S32 size);

/**
\brief shuts down an active TLS/SSL connection.
\attention \n
none
\param [in] tlsHdl tls handle

\retval ::1 The shutdown was successfully completed.
\retval ::0  The shutdown is not yet finished.
\retval ::<0 The shutdown was not successful because a fatal error occurred either at the protocol level or a connection failure occurred.

\see \n
None
*/
HI_S32 TLS_shutdown(HI_U32 tlsHdl);

/**
\brief close tls connect and free tls handle
\attention \n
none
\param [in] tlsHdl tls handle

\retval ::none

\see \n
None
*/
HI_VOID TLS_free(HI_U32 tlsHdl);

#ifdef __cplusplus
#if __cplusplus
}
#endif
#endif /* __cplusplus */

#endif /* __TLS_ADP_H__ */
