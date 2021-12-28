#include "StdAfx.h"
#include "CObj__VIRTUAL_STD.h"
#include "CObj__VIRTUAL_STD__DEF.h"


//------------------------------------------------------------------------------------
int  CObj__VIRTUAL_STD
::Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, 
			  CII_OBJECT__ALARM* p_alarm)
{
	CString title;
	CString msg;

LOOP_RETRY:

	if(sCH__COMM_STS->Check__DATA("OFFLINE") > 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)
		{
			goto LOOP_RETRY;
		}
		return -1;
	}
	return 1;
}
