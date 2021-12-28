#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"

#include "math.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CDriver__LPx_ETHERNET
::Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)		return;

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CDriver__LPx_ETHERNET
::Fnc__DRV_LOG(const CString& log_msg)
{
	if(iFlag__DRV_LOG < 1)		return;

	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}

void CDriver__LPx_ETHERNET
::Fnc__DRV_LOG_FORMAT(const char *fmt, ...)
{
	CString str_msg;
	va_list args;

	va_start(args, fmt);
	str_msg.FormatV(fmt, args);
	va_end(args);

	xDRV_LOG_CTRL->WRITE__LOG(str_msg);
}

void CDriver__LPx_ETHERNET
::Fnc__ACT_MSG(const CString& act_msg)
{
	sCH__ACT_MSG->Set__DATA(act_msg);
}
