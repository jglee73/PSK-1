#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__ALID.h"
#include "CObj__PSK_TEST__DEF.h"


#include "CDRV__ADS_CTRL.h"
extern CDRV__ADS_CTRL mDRV__ADS_CTRL; 


//-------------------------------------------------------------------------	
int  CObj__PSK_TEST
::Call__ADS_GET_INFO(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	bool active_print = true;

	CString log_msg = mDRV__ADS_CTRL.Get__ADS_IN_INFO(active_print);

	if(active_print)	xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	return 1;
}

int  CObj__PSK_TEST
::Call__ADS_INIT_DRIVER(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	mDRV__ADS_CTRL.Init__ADS_DRIVER(iActive__SIM_MODE);
	return 1;
}

int  CObj__PSK_TEST
::Call__ADS_UPDATE_READING(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	mDRV__ADS_CTRL.Update__ADS_READING(true, iActive__SIM_MODE);
	return 1;
}

int  CObj__PSK_TEST
::Call__ADS_UPDATE_SETTING(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	mDRV__ADS_CTRL.Update__ADS_SETTING(true, iActive__SIM_MODE);
	return 1;
}
