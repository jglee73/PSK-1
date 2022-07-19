#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"
#include "CDriver__LPx_ETHERNET__ALID.h"

#include "Macro_Function.h"


//-------------------------------------------------------------------------	
// INIT -----
int  CDriver__LPx_ETHERNET
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int status = -1;

	// ...
	{
		status = Fnc__ONLINE_CHECK(p_alarm,0);
		if(status <= 0)		return -1;
	}

	if(status <= 0)		return -1;
	return 1;
}

int  CDriver__LPx_ETHERNET
::Fnc__ONLINE_CHECK(CII_OBJECT__ALARM* p_alarm,
					const int alarm_check)
{
	SCX__TIMER_CTRL x_timer_ctrl;
	x_timer_ctrl->REGISTER__ABORT_OBJECT(sObject_Name);

	if(sCH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) > 0)
	{
		CString str__err_id;
		int i__err_id;

		sCH__INR__ERROR_ID_DEC->Get__DATA(str__err_id);
		i__err_id = atoi(str__err_id);

		if((i__err_id != 0)&&(alarm_check == 1))
		{
			// 
		}
		return 1;
	} 

	// Offline Alarm Post
	{
		int alarm_id = ALID__OFFLINE_ALARM;

		CString err_msg;
		CString r_act;

		err_msg  = "1. Check the ethernet cable\n";
		err_msg += "2. Check the robot power";

		p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,err_msg,r_act);

			 if(r_act.CompareNoCase("ABORT") == 0)		return -1;
		else if(r_act.CompareNoCase("RETRY") == 0)		return 0;
	}

	return -1;
}
