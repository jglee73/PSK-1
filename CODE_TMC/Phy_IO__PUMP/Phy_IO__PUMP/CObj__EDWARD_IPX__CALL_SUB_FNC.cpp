#include "StdAfx.h"
#include "CObj__EDWARD_IPX.h"


// ...
int  CObj__EDWARD_IPX::
Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString title;
	CString msg;

COMM_RTY:

	if(sCH__COMM_STS->Check__DATA(STR__OFFLINE) > 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)		goto 	COMM_RTY;
		else										return -1;
	}

	return 1;
}
