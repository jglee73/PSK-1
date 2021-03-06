#include "StdAfx.h"
#include "CObj__ERCD_SERIAL.h"


// ...
void CObj__ERCD_SERIAL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	if(iActive_SIM > 0)
	{
		bActive__COMM_ONLINE = true;
	}
	else
	{
		bActive__COMM_ONLINE = false;
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(bActive__COMM_ONLINE)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		}
		else
		{
			sCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);
		}

		if(sCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			int alarm_id = ALID__OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg  = "Please, check the communication state of ESC unit ! \n\n";
			alm_msg += sCH__INFO_DRV_PARAMETER->Get__STRING(); 

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
		}

		// ...
	}
}

