#ifndef QaTestDataStruct_h__
#define QaTestDataStruct_h__

#include "DxTypes.h"
#include "QaTestEnumeration.h"


#define TST_MAX_MOD_SIZE_IN_BYTES 384
#define TST_MAX_PRVT_EXP_SIZE_IN_BYTES 384
#define TST_MAX_PUB_EXP_SIZE_IN_BYTES 3
#define TST_MAX_P_SIZE_IN_BYTES TST_MAX_MOD_SIZE_IN_BYTES/2
#define TST_MAX_Q_SIZE_IN_BYTES TST_MAX_MOD_SIZE_IN_BYTES/2
#define TST_MAX_DP_SIZE_IN_BYTES TST_MAX_MOD_SIZE_IN_BYTES/2
#define TST_MAX_DQ_SIZE_IN_BYTES TST_MAX_MOD_SIZE_IN_BYTES/2
#define TST_MAX_QINV_SIZE_IN_BYTES TST_MAX_MOD_SIZE_IN_BYTES/2

#define TST_RSA_CRT_OPT 0x001
#define TST_RSA_NON_CRT_OPT 0x000
#define TST_RSA_ALIGNED_OPT	0x010
#define TST_RSA_NOT_ALIGNED_OPT	0x000
#define TST_RSA_MAX_OPT	(TST_RSA_CRT_OPT | TST_RSA_ALIGNED_OPT)

struct QaRSA_EncryptTestData {
	DxUint8					privetExponent_D[TST_MAX_PRVT_EXP_SIZE_IN_BYTES];
	DxUint8					publicExponent_E[TST_MAX_PUB_EXP_SIZE_IN_BYTES];
	DxUint8					modulus_N[TST_MAX_MOD_SIZE_IN_BYTES];
	DxUint8					P[TST_MAX_P_SIZE_IN_BYTES];
	DxUint8					Q[TST_MAX_Q_SIZE_IN_BYTES];
	DxUint8					dP[TST_MAX_DP_SIZE_IN_BYTES];
	DxUint8					dQ[TST_MAX_DQ_SIZE_IN_BYTES];
	DxUint8					Qinv[TST_MAX_QINV_SIZE_IN_BYTES];
	DxUint16				privExponentSize;
	DxUint16				pubExponentSize;
	DxUint16				modulusSize;
	DxUint16				PSize;
	DxUint16				QSize;
	DxUint16				dPSize;
	DxUint16				dQSize;
	DxUint16				QinvSize;
	DxUint8 				inputData[TST_MAX_MOD_SIZE_IN_BYTES+sizeof(DxUint32)];
	DxUint32				inputDataSize;
#ifndef WIN32
} __attribute__ ((__packed__));
#else
};
#endif


struct QaRSA_VerifySignTestData {
	DxUint8					publicExponent_E[TST_MAX_PUB_EXP_SIZE_IN_BYTES];
	DxUint8					modulus_N[TST_MAX_MOD_SIZE_IN_BYTES];
	DxUint16				pubExponentSize;
	DxUint16				modulusSize;
	DxUint8 				inputData[TST_MAX_MOD_SIZE_IN_BYTES+sizeof(DxUint32)];
	DxUint32				inputDataSize;
	DxUint8 				signature[TST_MAX_MOD_SIZE_IN_BYTES+sizeof(DxUint32)];
	DxUint32				signatureSize;
	DxUint32				saltLength;
#ifndef WIN32
} __attribute__ ((__packed__));
#else
};
#endif


typedef DxUint32 QaClbSecuenceValueArray[QA_MAX_CALLBACK_IDX];


#endif // QaErrorMessage_h__

