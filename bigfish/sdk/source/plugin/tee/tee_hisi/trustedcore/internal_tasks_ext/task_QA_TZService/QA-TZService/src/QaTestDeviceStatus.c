#include "QaTestFuncDeclaration.h"
#include "DxTzServiceAPI.h"
#include "QaUtils.h"


DxStatus IsDeviceRooted(DxBool expectedResult)
{
    DxBool result = DX_FALSE;

    result = DxTzService_IsDeviceRooted();

    if (result != expectedResult){

        REPORT_ERROR2("DxTzService_IsDeviceRooted failed to return expected result. expected result=%d actual result=0x%08X",expectedResult,result);

        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus IsBootLoaderUnlock(DxBool expectedResult)
{
    DxBool result = DX_FALSE;

    result = DxTzService_IsBootLoaderUnlocked();

    if (result != expectedResult){

        REPORT_ERROR2("DxTzService_IsBootLoaderUnlocked failed to return expected result. expected result=%d actual result=0x%08X",expectedResult,result);

        return DX_FAILURE;
    }
    return DX_SUCCESS;
}

DxStatus GetSetHdcp2ConnectionStatus(void)
{
	EDxTzConnectionStatus_t ConnectionStatus = DX_TZ_CONNECTION_STATUS_UNSUPPORTED;
	DxStatus Result = DxTzService_SetHDCP2ConnectionStatus(DX_FALSE);
	if (Result != DX_SUCCESS)
	{
        REPORT_ERROR1("DxTzService_SetHDCP2ConnectionStatus(DX_FALSE) failed. Actual result=0x%08X", Result);

        return DX_FAILURE;
	}

	ConnectionStatus = DxTzService_GetHDCP2ConnectionStatus();
	if (ConnectionStatus != DX_TZ_CONNECTION_NOT_CONNECTED)
	{
        REPORT_ERROR2("DxTzService_GetHDCP2ConnectionStatus for not connected state failed. Expected result:0x%08X, Actual result:0x%08X", DX_TZ_CONNECTION_NOT_CONNECTED, ConnectionStatus);

        return DX_FAILURE;
	}

	Result = DxTzService_SetHDCP2ConnectionStatus(DX_TRUE);
	if (Result != DX_SUCCESS)
	{
        REPORT_ERROR1("DxTzService_SetHDCP2ConnectionStatus(DX_TRUE) failed. Actual result=0x%08X", Result);

        return DX_FAILURE;
	}

	ConnectionStatus = DxTzService_GetHDCP2ConnectionStatus();
	if (ConnectionStatus != DX_TZ_CONNECTION_CONNECTED)
	{
        REPORT_ERROR2("DxTzService_GetHDCP2ConnectionStatus for connected state failed. Expected result:0x%08X, Actual result:0x%08X", DX_TZ_CONNECTION_CONNECTED, ConnectionStatus);

        return DX_FAILURE;
	}

	Result = DxTzService_SetHDCP2ConnectionStatus(DX_FALSE);
	if (Result != DX_SUCCESS)
	{
        REPORT_ERROR1("DxTzService_SetHDCP2ConnectionStatus(DX_FALSE) failed (2nd try). Actual result=0x%08X", Result);

        return DX_FAILURE;
	}

	ConnectionStatus = DxTzService_GetHDCP2ConnectionStatus();
	if (ConnectionStatus != DX_TZ_CONNECTION_NOT_CONNECTED)
	{
        REPORT_ERROR2("DxTzService_GetHDCP2ConnectionStatus for not connected state failed (2nd try). Expected result:0x%08X, Actual result:0x%08X", DX_TZ_CONNECTION_NOT_CONNECTED, ConnectionStatus);

        return DX_FAILURE;
	}

    return DX_SUCCESS;
}


DxStatus hdmiStatusTest( DxTzServiceParameter pParams[4])
{
	pParams[0].value.a = DxTzService_Get_HDMI_HDCP1_Status();
	return DX_SUCCESS;
}


