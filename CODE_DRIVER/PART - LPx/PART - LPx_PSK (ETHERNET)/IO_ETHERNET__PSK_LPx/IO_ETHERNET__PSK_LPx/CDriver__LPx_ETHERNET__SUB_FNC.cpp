#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"

#include "math.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CDriver__LPx_ETHERNET
::Fnc__APP_LOG(const CString& log_msg)
{
	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CDriver__LPx_ETHERNET
::Fnc__DRV_LOG(const CString& log_msg)
{
	xDRV_LOG_CTRL->WRITE__LOG(log_msg);
}

void CDriver__LPx_ETHERNET
::Fnc__ACT_MSG(const CString& act_msg)
{
	sCH__ACT_MSG->Set__DATA(act_msg);
}
