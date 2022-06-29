#include "StdAfx.h"

#include "CObj__ERCD_SERIAL.h"


//------------------------------------------------------------------------------------
void CObj__ERCD_SERIAL::Write__APP_LOG(const CString& log_msg)
{
	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
}

void CObj__ERCD_SERIAL::Write__DRV_LOG(const CString& log_msg)
{
	xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
}

