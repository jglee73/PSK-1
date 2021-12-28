#include "StdAfx.h"
#include "CObj__EDWARD_IPX.h"


// ...
void CObj__EDWARD_IPX::Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)
	{
		return;
	}

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}
