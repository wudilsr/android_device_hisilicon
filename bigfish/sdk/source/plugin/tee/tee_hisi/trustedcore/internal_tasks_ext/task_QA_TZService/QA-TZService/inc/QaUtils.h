#ifndef QaUtils_h__
#define QaUtils_h__

#include "DxTzServiceAPI.h"
#include "QaErrorMessage.h"
#include "QaCallbackSequence.h"


DxUint32 power(DxUint32 number, DxUint32 power);

#define UNREFERENCED_PARAMETER(_var) if(_var != _var) {}

typedef struct _QaGlobalInstance{
    QaErrorMessage* qaErrMsg;
    DxUint32 muxNumOfLoops;

    QA_TZ_ClbSequenceData clbSequenceData;
}
QaGlobalInstance;

/*
* @brief report error message without arguments
*
* Call this function to propagate error occurred in TZService to caller HLOS test
* @param[in] file file name where error occurred
* @param[in] line line number where error occurred
* @param[in] func function name where error occurred
* @param[in] msg error message to be propagated
*/
void reportError (const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* msg);

/*
* @brief report error message with 1 argument
*
* Call this function to propagate error occurred in TZService to caller HLOS test.
* It assumes that error message contains printing template (such as %d or %x) passed via paramX argument
*
* @param[in] file file name where error occurred
* @param[in] line line number where error occurred
* @param[in] func function name where error occurred
* @param[in] msg error message to be propagated
* @param[in] param1 message argument to be expanded
*/
void reportError1(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* format, DxUint32 param1);

/*
* @brief report error message with 1 argument
*
* Call this function to propagate error occurred in TZService to caller HLOS test.
* It assumes that error message contains printing templates (such as %d or %x) passed via paramX arguments
*
* @param[in] file file name where error occurred
* @param[in] line line number where error occurred
* @param[in] func function name where error occurred
* @param[in] msg error message to be propagated
* @param[in] param1 message first argument to be expanded
* @param[in] param2 message second argument to be expanded
*/
void reportError2(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* format, DxUint32 param1, DxUint32 param2);

/*
* @brief report error message with 1 argument
*
* Call this function to propagate error occurred in TZService to caller HLOS test.
* It assumes that error message contains printing templates (such as %d or %x) passed via paramX arguments
*
* @param[in] file file name where error occurred
* @param[in] line line number where error occurred
* @param[in] func function name where error occurred
* @param[in] msg error message to be propagated
* @param[in] param1 message first argument to be expanded
* @param[in] param2 message second argument to be expanded
* @param[in] param3 message third argument to be expanded
*/
void reportError3(const DxChar* file, DxUint32 line, const DxChar* func, const DxChar* format, DxUint32 param1, DxUint32 param2, DxUint32 param3);

#ifdef WIN32
#define QA_FUNC __FUNCTION__
#else
#define QA_FUNC __func__
#endif

#define PERFORM_CLEANUP goto CLEANUP_SECTION

#define QA_PREFIX_ERR "<<<QA ERR>>> "
#define QA_PREFIX_DBG "<<<QA DBG>>> "

extern void uart_printf_func(const char *fmt, ...);

#define QA_LOG_MSG(fmt, args...) uart_printf_func("%s %s: " fmt "\n", QA_PREFIX_DBG, __FUNCTION__, ## args)
#define QA_ERR_MSG(fmt, args...) uart_printf_func("%s %s: " fmt "\n", QA_PREFIX_ERR, __FUNCTION__, ## args)

//#define QA_LOG_MSG(msg, ...) DxHwLogTrace(DX_FALSE, QA_PREFIX_DBG msg, ##__VA_ARGS__)
//#define QA_ERR_MSG(msg, ...) DxHwLogError(DX_FALSE, QA_PREFIX_ERR msg, ##__VA_ARGS__)

#define REPORT_ERROR0(msg) do{ \
								reportError(__FILE__, __LINE__, QA_FUNC, msg); \
								QA_ERR_MSG(msg); \
						   }while(0)
#define REPORT_ERROR1(msg, param1) do{ \
								        reportError1(__FILE__, __LINE__, QA_FUNC, msg, param1); \
								        QA_ERR_MSG(msg, param1); \
							         }while(0)
#define REPORT_ERROR2(msg, param1, param2) do{\
							        	         reportError2(__FILE__, __LINE__, QA_FUNC, msg, param1, param2);\
							        	         QA_ERR_MSG(msg, param1, param2); \
							                 }while(0)
#define REPORT_ERROR3(msg, param1, param2, param3) do{ \
	                                                     reportError3(__FILE__, __LINE__, QA_FUNC, msg, param1, param2, param3); \
	                                                     QA_ERR_MSG(msg, param1, param2, param3); \
	                                                 }while(0)




DxUint32 qaStrlen(const DxChar* str);

/**
 * Initializes global data for QA Tests.
 */
DxStatus initQaGlobalInstance(QaGlobalInstance* qaGlobal);

/**
 * Set <NumberOfLoops> for tests in global data.
 */
DxStatus setNumOfLoopsQaGlobalInstance( QaGlobalInstance* qaGlobal, DxUint32 numOfLoops);

/**
 * Finalizes global data for QA Tests.
 */
void terminateQaGlobalInstance(QaGlobalInstance* qaGlobal);


/*
 * Buffer extend direction used by ExpandTestingDataWithDummyBuffers
 */
typedef enum {
    eEXTEND_TO_BOTH_SIDE, ///extend buffer to both sides
    eEXTEND_TO_LEFT_SIDE, ///extend buffer only to left side
    eEXTEND_TO_RIGHT_SIDE ///extend buffer only to right side
} EExtendBufferSide;

/*
* @brief Clean memory at the end of the Expand buffer functions free up to 3 buffers
* @param buff1 buffer to be released
* @param buff3 buffer to be released
* @param buff2 buffer to be released
*/
void onCleenupExpandBuffers(DxUint8 * buff1,DxUint8 * buff2, DxUint8 * buff3 );

/*
* @brief Create an extended buffer part and fill it with ascending numbers between 0-MAX(DxUint8)
*
* @param size size of buffer to be created
* @return pointer to new buffer or DX_NULL in error case
*/
DxUint8 * createExtendedBuff(DxUint32 size);

/*
* @brief for the propose of releasing the buffer which was created with CreateExtendedBuff
*
* @param aBuff1 buffer to be released
* @return DX_SUCCESS
*/
DxStatus destroyExtendedBuff(DxUint8 * aBuff);

/*
* @brief returns a new buffer with extended dummy data on both side of the original data.
*
* new buffer will be in size of aOriginalBufferLength + aExtendedLength*(number of etended parts: left, right ot both)
* @param aBuffer original buffer
* @param aExtendedLength how much to extends in bytes
* @param aOriginalBufferLength original size of aBuffer
* @param leftOrRightSide extension directions according to EExtendBufferSide enum
*
* @return an new extended buffer or DX_NULL in error cases
*/
DxUint8 * expandTestingDataWithDummyBuffers(const DxUint8 *aBuffer, DxUint32 aOriginalBufferLength, DxUint32 aExtendedLength, EExtendBufferSide leftOrRightSide);

/*
* verify that extended buffer parts are not modified
*
* @param aBuffer extended full buffer to be checked
* @param aOriginalBufferLength original size of aBuffer
* @param aExtendedLength how much to extends in bytes
* @param leftOrRightSide extension directions according to EExtendBufferSide enum
* @return DX_SUCCESS if extended part are ok or DX_FAILURE
*/
DxStatus checkExtendedDummyBuffers(DxUint8 *aBuffer, DxUint32 aOriginalBufferLength, DxUint32 aExtendedLength, EExtendBufferSide leftOrRightSide);

DxUint32 getNumOfLoops(void);


/*
* Copies bufferSize bytes of data from offset in source shared memory
* reference (srcSharedMemRefPtr) in to destRegularBuffer and destSharedMemRefPtr.
* After this function, destRegularBuffer will be filled with data from destSharedMemRefPtr,
* and destRegularBuffer will be packed in to destSharedMemRefPtr.
*
* @param [out] destSharedMemRefPtr	-	pointer to SharedMemRef that will be filled.
* @param [out] destRegularBuffer	-	pointer to buffer allocated in caller function that has bufferSize bytes.
* @param [in]  srcSharedMemRefPtr	-	pointer to SharedMemRef source buffer. Data from this buffer will be copied
 *										in to destSharedMemRefPtr and destRegularBuffer.
* @param [in]  offsetInSrc			-	offset in source from where data will be copied.
* @param [in]  bufferSize			-	size of data that will be copied from source in to allocatedBufferDestPtr
* @return DX_SUCCESS if handle creation and memory copying were OK or errcode of operation failed otherwise
* *** Note : allocatedBufferDestPtr allocated by caller function (and must be free by caller), buffer has size bufferSize bytes
*/
DxStatus CreateAndCopySharedMemRef(DxTzServiceSharedMemRef *destSharedMemRefPtr, DxByte *destRegularBuffer,
								   DxTzServiceSharedMemRef *srcSharedMemRefPtr, unsigned int offsetInSrc,
								   unsigned int bufferSize);



#endif // QaUtils_h__
