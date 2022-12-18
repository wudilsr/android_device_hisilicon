

 #ifndef _DX_VOS_SEM_H
#define _DX_VOS_SEM_H
#if 0
/*! \file DX_VOS_Sem.h
\brief This file enables semaphore operations.

All functions that return DxStatus will return:
- DX_SUCCESS - on success
- DX_BAD_ARGUMENTS - if there were bad parameters.
- DX_VOS_SEM_ERROR - if operation fails.

*/
#include "DX_VOS_BaseTypes.h"

#ifdef __cplusplus
extern "C"
{
#endif

	/*************************** DEFINES ***********************/

	/* For using by DX_VOS_SemWait */

#define DX_VOS_SEM_NO_WAIT          0
#define DX_VOS_SEM_FREE				1
#define DX_VOS_SEM_LOCKED			0

	/*************************** Typedefs *********************/

	typedef struct _DxVosSem*  DxVosSem;


	/*!	Creates the semaphore. */
	DxStatus DX_VOS_SemCreate (
		DxVosSem  *aSemId,       /*!< [in] Pointer to where the handle to the created semaphore will be stored */
		DxUint  aInitialValue, /*!< [in] Initial semaphore value */
		const DxChar* aSemName	 /*!< [in] Semaphore name for debugging purpose only.
									  Two calls to DX_VOS_SemCreate with the same semaphore
									  name will create two separate semaphores.
									  This parameter may be NULL if no name is required. */
		);

	/*!	Creates a global semaphore with the specifies global id. If a semaphore with the same
		global id already exists the function returns a handle to this existing semaphore instead
		of creating a new one.*/
	DxStatus DX_VOS_SemCreateGlobal (
		DxVosSem  *aSemId,      /*!< [in] Pointer to where the handle to the created semaphore will be stored */
		DxUint  aInitialValue,	/*!< [in] Initial semaphore value */
		const DxChar* aSemGlobalName	/*!< [in] Global name of the semaphore to create. */
								 );

	/*!	Terminates and deallocates resources associated with the specified semaphore.
		This function should be called when there are no threads that waits on the semaphore.
		If there are threads that waits on this semaphore the system behavior is undefined.
		\note If aSemId is NULL the function succeeds.
	*/
	DxStatus DX_VOS_SemDelete (DxVosSem  aSemId);

    /*!	Terminates and deallocates resources associated with the specified semaphore.
    This function should be called when there are no threads that waits on the semaphore.
    If there are threads that waits on this semaphore the system behavior is undefined.
    On exit *aSemId == DX_NULL
    \note If aSemId is NULL or *aSemId the function succeeds.
    */
    DxStatus DX_VOS_SemDestroy (DxVosSem*  aSemId);

	/*!	Wait for semaphore with timeout. timeout is specified in milliseconds.
        \note If aSemId is NULL the function returns immediately with DX_SUCCESS.

		\return
		- DX_SUCCESS - if semaphore where obtained.
		- DX_TIMEOUT_EXPIRED - if timeout expires.
		- DX_VOS_SEM_ERROR - if operation fails.
	**/
	DxStatus DX_VOS_SemWait(
		DxVosSem aSemId,  /*!< [in] SemID for create */
		DxUint32 aTimeout /*!< [in] timeout in mSec, or DX_INFINITE */
		);

	/*! Signals the semaphore.
    \note If aSemId is NULL the function returns immediately with DX_SUCCESS.
    \return
    - DX_SUCCESS - if semaphore where obtained.
    - DX_VOS_SEM_ERROR - if operation fails.

    */
	DxStatus DX_VOS_SemGive(DxVosSem aSemId);

#ifdef DX_USE_LEGACY_VOS
#define DX_VOS_SEM_WAIT_INFINITY DX_INFINITE
typedef DxVosSem DxVosSemID;
#endif

#ifdef  __cplusplus
}
#endif

#endif
#endif /* ifndef _DX_VOS_SEM_H */
