#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"

#include "math.h"



//------------------------------------------------------------------------------------
int  CObj__STP_SERIAL::Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	if(sCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Check__ALARM(alarm_id,r_act);
		p_alarm->Post__ALARM(alarm_id);

		return -1;
	}
	return 1;
}
