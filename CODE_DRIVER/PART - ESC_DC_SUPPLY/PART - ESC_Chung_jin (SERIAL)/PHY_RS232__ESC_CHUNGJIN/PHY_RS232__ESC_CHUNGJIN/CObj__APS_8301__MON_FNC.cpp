#include "StdAfx.h"
#include "CObj__APS_8301.h"


// ...
void CObj__APS_8301
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iActive_SIM > 0)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		}

		if(sCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			int alarm_id = ALID__ESC_OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg = "Please, check the communication state of ESC unit !";

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
		}

		// Leak_Current Limit Check ...
		{
			double cfg__leak_limit = aCH__CFG_LEAK_CURRUNT_LIMIT->Get__VALUE();

			ch_data = siCH__ESC_LEAK_CURRENT->Get__STRING();
			double cur_value = atof(ch_data);

			if(cur_value > cfg__leak_limit)
			{
				sCH__MON_SYSTEM_ABORT->Set__DATA(STR__YES);

				_Fnc__Abort_Ctrl();

				//
				int alarm_id = ALID__ESC_HIGH_CURRENT_LIMIT;
				CString alm_msg;
				CString alm_bff;
				CString	r_act;

				alm_bff.Format("The config leak-current is %.0f (µA). \n", cfg__leak_limit);
				alm_msg = alm_bff;
				
				alm_bff.Format("Now, leak-current is %.0f (µA). \n", cur_value);
				alm_msg = alm_bff;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
			else
			{
				sCH__MON_SYSTEM_ABORT->Set__DATA(STR__NO);
			}
		}

		// ...
	}
}

