#include "StdAfx.h"
#include "CObj__PARAMOUNT_HF.h"


// ...
int CObj__PARAMOUNT_HF
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	dCH__MON_COMM_STS->Set__DATA(STR__ONLINE); 


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iActive_SIM > 0)
		{
			CString ch_data;

			aoCH__POWER_SET->Get__DATA(ch_data);
			sCH__INFO_FORWARD_POWER_READ->Set__DATA(ch_data);
		}

		if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			// ...
			int alarm_id = ALID__GEN_OFFLINE_ALARM;
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
