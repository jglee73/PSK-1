#include "StdAfx.h"
#include "CObj__VIRTUAL_STD.h"


//------------------------------------------------------------------------------------
void CObj__VIRTUAL_STD
::Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)
	{
		return;
	}

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}
