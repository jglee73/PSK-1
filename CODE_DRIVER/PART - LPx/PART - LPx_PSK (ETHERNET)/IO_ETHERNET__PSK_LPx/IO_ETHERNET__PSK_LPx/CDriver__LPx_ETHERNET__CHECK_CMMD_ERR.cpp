#include "StdAfx.h"

#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"
#include "CDriver__LPx_ETHERNET__ALID.h"


//------------------------------------------------------------------------------------
int  CDriver__LPx_ETHERNET
::Call__CHECK_CMMD(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm)
{
	printf("Call__CHECK_CMMD() : Started ... \n");

	CString str_cmmd = sCH__PARA_CHECK_CMMD->Get__STRING();
	int r_res = soCH__CHECK_CMMD->Set__DATA(str_cmmd);

	printf("Call__CHECK_CMMD() : End(%1d) ... \n", r_res);
	return 1;
}
int  CDriver__LPx_ETHERNET
::Call__CHECK_ERR_CODE(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm)
{
	printf("Call__CHECK_ERR_CODE() : Started ... \n");

	CString err_code = sCH__PARA_CHECK_ERR_CODE->Get__STRING();

	CString err_msg = Get__CANCEL_CODE_OF_NAK(err_code);

	printf(" * err_code [%s] \n", err_code);
	printf(" * err_msg ... \n");
	printf("_______________________________________________\n");
	printf(err_msg);
	printf("_______________________________________________\n");

	printf("Call__CHECK_ERR_CODE() : End ... \n");
	return 1;
}
