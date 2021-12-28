#include "StdAfx.h"
#include "CObj__NAVII_SERIAL.h"


//------------------------------------------------------------------------------------
void CObj__NAVII_SERIAL
::Write__APP_LOG(const CString& log_msg)
{
	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__NAVII_SERIAL
::Write__DRV_LOG(const CString& log_msg)
{
	if(iFLAG__DRV_FLAG < 0)
	{
		return;
	}

	xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
}
