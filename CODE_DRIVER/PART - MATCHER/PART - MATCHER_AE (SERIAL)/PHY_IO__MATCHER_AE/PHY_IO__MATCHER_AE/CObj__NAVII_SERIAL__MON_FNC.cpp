#include "StdAfx.h"
#include "CObj__NAVII_SERIAL.h"


// ...
int CObj__NAVII_SERIAL
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			// ...
			int alarm_id = ALID__OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg = sPROTOCOL_INFO;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}

		// ...
	}

	return 1;
}
