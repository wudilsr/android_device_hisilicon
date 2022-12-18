/**
 * @file DxTzCommon.h
 * @brief Common platform-independent definitions for TEE Service and Client sides.
 */
#ifndef	__DXTZCOMMON_H__
#define	__DXTZCOMMON_H__

#include "DX_VOS_Errors.h"
#include "DxTypes.h"


#define DX_TZ_OPERATION_NUM_PARAMS	4

/**
 * Parameter types used to encode the parameters and their types and pass them from TEE Client to the service.
 * The type of each parameter determines whether the parameter is used or not,
 * whether it is a value or a memory reference,
 * and the direction of data flow between the client and the service: input (client to service),
 * output (service to client) or both input and output.
 *
 * Use macros DX_TZ_PARAM_GET and DX_TZ_PARAM_TYPES to encode and decode the four parameter types into one value.
 *
 * DX_TZ_PARAM_TYPE_NONE			- the pParams[i] content is ignored
 * DX_TZ_PARAM_TYPE_VALUE_INPUT		- pParams[i].value.a and b contain the 2 integers sent by the client
 * DX_TZ_PARAM_TYPE_VALUE_OUTPUT	- 2 integers answered by the server
 * DX_TZ_PARAM_TYPE_VALUE_INOUT		- 2 integers sent by the client  and modified by the server
 * DX_TZ_PARAM_TYPE_MEMREF_INPUT	- pParams[i].tmpref.buffer is a pointer to memory buffer shared by the client (passed for read-only purpose)
 * DX_TZ_PARAM_TYPE_MEMREF_OUTPUT	- a pointer to memory buffer passed for write-only purpose
 * DX_TZ_PARAM_TYPE_MEMREF_INOUT	- a pointer to memory buffer passed for read and write purpose
 * DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT - pParams[i].memref.handle is a handle of secure memory buffer shared by the client,passed for read and write purpose
 */
#define	DX_TZ_PARAM_TYPE_NONE 0
#define	DX_TZ_PARAM_TYPE_VALUE_INPUT 1
#define	DX_TZ_PARAM_TYPE_VALUE_OUTPUT 2
#define	DX_TZ_PARAM_TYPE_VALUE_INOUT 3
#define	DX_TZ_PARAM_TYPE_MEMREF_INPUT 5
#define	DX_TZ_PARAM_TYPE_MEMREF_OUTPUT 6
#define	DX_TZ_PARAM_TYPE_MEMREF_INOUT 7
#define	DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT 8

/**
 * Use this macro to compound 4 types of parameter into one value paramTypes
*/
#define DX_TZ_PARAM_TYPES(t0,t1,t2,t3) \
    ((t0) | ((t1) << 4) | ((t2) << 8) | ((t3) << 12))

/**
 * Use this macro as shorthand for void input/output params
 */
#define DX_TZ_PARAMS_TYPES_VOID     DX_TZ_PARAM_TYPES( \
        DX_TZ_PARAM_TYPE_NONE, DX_TZ_PARAM_TYPE_NONE, DX_TZ_PARAM_TYPE_NONE, DX_TZ_PARAM_TYPE_NONE)

/**
 * Use this macro to decode specified parameter type from the value
*/
#define DX_TZ_PARAM_TYPE_GET(t, i) (((t) >> ((i)*4)) & 0xF)

/**
 * Use this macro to test if there are no parameters - ea input is "void"
 */
#define DX_TZ_PARAM_ALL_NONE(t) ((t) == DX_TZ_PARAMS_TYPES_VOID)

/**
 * Use this macro to set specified parameter type to the value
*/
#define DX_TZ_PARAM_TYPE_SET(t, i, val) (t = (t & (~(0xF << (i*4)))) | ((val & 0xF) << (i*4)))

#define DX_TZ_MAKE_ERR(num) (DX_TZ_FAILURE + num)

/**
 * TZ Service error code
*/
typedef enum {
    DX_TZ_FAILURE                      = (DX_SUBSYSTEM_TZ << ERROR_CODE_BITS),  //!< DX_TZ_FAILURE
    DX_TZ_BAD_PARAMETERS               = DX_TZ_MAKE_ERR(0x01),                  //!< DX_TZ_BAD_PARAMETERS
    DX_TZ_NO_MEMORY                    = DX_TZ_MAKE_ERR(0x02),                  //!< DX_TZ_NO_MEMORY
    DX_TZ_NO_COMMUNICATION             = DX_TZ_MAKE_ERR(0x03),                  //!< DX_TZ_NO_COMMUNICATION
    DX_TZ_BAD_STATE                    = DX_TZ_MAKE_ERR(0x04),                  //!< DX_TZ_BAD_STATE
    DX_TZ_ACCESS_DENIED                = DX_TZ_MAKE_ERR(0x05),                  //!< DX_TZ_ACCESS_DENIED
    DX_TZ_ITEM_NOT_FOUND               = DX_TZ_MAKE_ERR(0x06),                  //!< DX_TZ_ITEM_NOT_FOUND
    DX_TZ_BAD_FORMAT                   = DX_TZ_MAKE_ERR(0x07),                  //!< DX_TZ_BAD_FORMAT
    DX_TZ_NOT_IMPLEMENTED              = DX_TZ_MAKE_ERR(0x08),                  //!< DX_TZ_NOT_IMPLEMENTED
    DX_TZ_SFS_FAILURE                  = DX_TZ_MAKE_ERR(0x09),                  //!< DX_TZ_SFS_FAILURE
    DX_TZ_BUFFER_IS_NOT_BIG_ENOUGH     = DX_TZ_MAKE_ERR(0x0A),                  //!< DX_TZ_BUFFER_IS_NOT_BIG_ENOUGH
    DX_TZ_MEM_ALLOCATION_ERROR         = DX_TZ_MAKE_ERR(0x0B),                  //!< DX_TZ_MEM_ALLOCATION_ERROR
    DX_TZ_OVERFLOW                     = DX_TZ_MAKE_ERR(0x0C),                  //!< DX_TZ_OVERFLOW
    DX_TZ_END_OF_FILE                  = DX_TZ_MAKE_ERR(0x0D),                  //!< DX_TZ_END_OF_FILE
    DX_TZ_FILE_ERROR                   = DX_TZ_MAKE_ERR(0x0E),                  //!< DX_TZ_FILE_ERROR
    DX_TZ_UNSUPPORTED_PLATFORM_COMMAND = DX_TZ_MAKE_ERR(0x0F),                  //!< DX_TZ_UNSUPPORTED_PLATFORM_COMMAND
    DX_TZ_INVALID_GLOBAL_INSTANCE      = DX_TZ_MAKE_ERR(0x10),                  //!< DX_TZ_INVALID_GLOBAL_INSTANCE
    DX_TZ_DEVICE_KEY_STORAGE_CORRUPTED = DX_TZ_MAKE_ERR(0x11),                  //!< DX_TZ_DEVICE_KEY_STORAGE_CORRUPTED
    DX_TZ_INSUFFICIENT_RESOURCES       = DX_TZ_MAKE_ERR(0x12),                  //!< not enough resources available
    DX_TZ_PLATFORM_ERROR               = DX_TZ_MAKE_ERR(0x13),                  //!< unexpected platform API failure
} EDxTzErrors;

#define	DX_TZ_SUCCESS			DX_SUCCESS
#define DX_UUID_VALUE_D_LENGTH	8
#define DX_TZ_APPNAME_LENGTH	11  /* Limitation on Qualcomm platform */

/**
 * Structure used to be a type of DX_TZ_PARAM_TYPE_VALUE_INPUT
 * and DX_TZ_PARAM_TYPE_VALUE_OUTPUT parameter,
 * to be used at the TZ client side.
*/
typedef struct
{
    DxUint32 a;
    DxUint32 b;
} Dx_Client_Tz_Value;

/**
 * Structure used to be a type of  DX_TZ_PARAM_TYPE_MEMREF_INPUT, DX_TZ_PARAM_TYPE_MEMREF_OUTPUT, DX_TZ_PARAM_TYPE_MEMREF_INOUT,
 * to be used at the TZ client side.
 *  - a memory buffer passed for read and write purpose
 *	- the memory buffer size
*/
typedef struct
{
    void* buffer;
    DxUint32 size;
} Dx_Client_Tz_MemRef;


typedef void*	Dx_Client_Tz_PlatformHandle1;
typedef void*	Dx_Client_Tz_PlatformHandle2;
/**
 * Structure used to be a type of  DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT,
 * to be used at the CLIENT side of TZ application. It contains TZ shared memory buffer
 * representation for client side of application.
 *
 * handle1 (platform-dependent) - a first  handle of shared memory buffer passed for read/write purpose
 * handle2 (platform-dependent) - a second handle of shared memory buffer passed for read/write purpose
 * size - the memory buffer size
 * offset - offset from start of buffer
 *			Note : offset - In parameter for TZ. Can not be updated by TZ.
 *
 * Note : Fields <offset> and <size> define "memory window" available for TZ client and service application.
 * (In other words, memory region available starts on <offset> bytes from start of buffer
 * and has size of <size> bytes.)
*/
typedef struct
{
    Dx_Client_Tz_PlatformHandle1 handle1;
    Dx_Client_Tz_PlatformHandle2 handle2;
	DxUint32 offset;
    DxUint32 size;
} Dx_Client_Tz_SharedMemRef;


/**
 * Union used to contain any type of parameter passed to the TZ service API,
 * to be used at the TZ client side.
*/
typedef union
{
    Dx_Client_Tz_MemRef			memRef;
    Dx_Client_Tz_SharedMemRef	sharedMemRef;
    Dx_Client_Tz_Value			value;

} Dx_Client_Tz_Parameter;


/**
 * Structure containing usually 4 different parameters to be sent to the TZ service API,
 * to be used at the TZ client side.
 * paramTypes describes the type of each parameter.
 * params is an array of the client-side parameters.
*/
typedef struct
{
    DxUint32             		paramTypes;
    Dx_Client_Tz_Parameter		params[DX_TZ_OPERATION_NUM_PARAMS];
} Dx_Client_Tz_Operation;



/**
 * Structure used to be a type of DX_TZ_PARAM_TYPE_VALUE_INPUT
 * and DX_TZ_PARAM_TYPE_VALUE_OUTPUT parameter,
 * to be used at the TZ service side.
*/
typedef struct
{
    DxUint32 a;
    DxUint32 b;
} DxTzServiceValue;

/**
 * Structure used to be a type of  DX_TZ_PARAM_TYPE_MEMREF_INPUT, DX_TZ_PARAM_TYPE_MEMREF_OUTPUT, DX_TZ_PARAM_TYPE_MEMREF_INOUT,
 * to be used at the TZ service side.
 *  handle1 (platform-dependent) - a handle of secured memory buffer passed for read/write purpose
 *								 - a physical memory address of shared memory buffer
 *  handle2 (platform-dependent) - local usage
 *								 - a virtual memory address of shared memory buffer in TEE
 *	size - the memory buffer size
*/
typedef struct
{
    void* pBuffer;
    DxUint32 nSize;
} DxTzServiceMemRef;

typedef void* DxTzServiceMemHandle1;
typedef void* DxTzServiceMemHandle2;


/**
 * Structure used to be a type of  DX_TZ_PARAM_TYPE_SHARED_MEMREF_INOUT,
 * to be used at the SERVICE side of TZ application. It contains TZ shared memory buffer
 * representation for client side of application.
 *
 * handle1 (platform-dependent) - a first  handle of shared memory buffer passed for read/write purpose
 * handle2 (platform-dependent) - a second handle of shared memory buffer passed for read/write purpose
 * size - the memory buffer size
 * offset - offset from start of buffer.
 *			Note : offset - In parameter for TZ. Can not be updated by TZ.
 *
 * Note : Fields <offset> and <size> define "memory window" available for TZ service application.
 * (In other words, memory region available starts on <offset> bytes from start of buffer
 * and has size of <size> bytes.)
*/
typedef struct
{
    DxTzServiceMemHandle1 handle1;
	DxTzServiceMemHandle2 handle2;
	DxUint32 offset;
    DxUint32 nSize;
} DxTzServiceSharedMemRef;


/**
 * Union used to contain any type of parameter passed to the TZ service API,
 * to be used at the TZ service side.
*/
typedef union
{
    DxTzServiceMemRef memRef;
    DxTzServiceSharedMemRef sharedMemRef;
    DxTzServiceValue value;

} DxTzServiceParameter;



/**
 * Shorter definition of the TZ service parameter.
*/
typedef DxTzServiceParameter DX_TZ_PARAM;

/**
 * Structure containing usually 4 different parameters to be sent to the TZ service API,
 * to be used at the TZ service side.
 * paramTypes describes the type of each parameter.
 * params is an array of the client-side parameters.
 *
 * The service must not attempt to write into a memory buffer of type INPUT;
 *
 * for a memory reference buffer marked as OUTPUT or INOUT, the service can write the entire range
 * described by the initial content of params[i].memref.nSize.
 * The final value of the params[i].memref.nSize may be modified by the service.
 * However, the system only guarantees that the client will observe the modifications below the final value of nSize
 * and only if the final value is equal or less than the original value.
 *
 * For example, assume the original value of nSize is 100 (set by HLOS size):
 * If the service does not modify this value, the complete buffer is synchronized and the client is guaranteed to observe all the changes;
 * If The service writes 50 in nSize, then the client is only guaranteed to observe the changes within the range from index 0 to index 49;
 * If the service writes 200 in nSize, then no data is guaranteed to be synchronized with the client.
 * However, the client will receive the new value of nSize. The service can typically use this feature to tell the client that the memory reference
 * was too small and request that the client retry with a memory reference of at least 200 bytes.
 */

typedef struct DxTzServiceOperation_t
{
    DxUint32             	paramTypes;
    DxTzServiceParameter	params[DX_TZ_OPERATION_NUM_PARAMS];
} DxTzServiceOperation;

/**
 *	UUID structure.
*/
typedef struct
{
    DxUint32	a;
    DxUint16	b;
    DxUint16	c;
    DxUint8		d[DX_UUID_VALUE_D_LENGTH]; /**< Value of the UUID. */
} Dx_UUID;

/**
 *	Structure used as a parameter type when creating TZ context.
 *
 *	The appname is a null-terminated string, containing a name of the application running in the TEE.
 *  The maximum length of the appname must be DX_TZ_APPNAME_LENGTH-1.
 *
 *	uuid usually points Unique ID identifying the service to be instantiated.
 *	Depending on current platform implementation, it may have another meaning.
 *
 *	The appname and uuid fields can be used or unused, depending on specific platform implementation.
*/
typedef struct
{
    DxChar	appname[DX_TZ_APPNAME_LENGTH];
    Dx_UUID	uuid;
} Dx_TzAppId;

#endif

