#include "StdAfx.h"
#include "CObj__EDWARD_IPX.h"


//------------------------------------------------------------------------------------
void CObj__EDWARD_IPX::
Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// ONLINE, OFFLINE ...
		if(iActive_SIM > 0)
		{
 			if(sCH__COMM_STS->Check__DATA(STR__ONLINE) < 0)
			{
				sCH__COMM_STS->Set__DATA(STR__ONLINE);
			}
		}
		else
		{
			if(dEXT_CH__DI_IO_COMM_STS->Check__DATA(STR__ONLINE) < 0)
			{
				sCH__COMM_STS->Set__DATA(STR__OFFLINE);

				// ...
				{
					CString r_act;
					int alarm_id = ALID__OFFLINE_ALARM;
				
					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
			}

			CString var_data = dEXT_CH__DI_IO_COMM_STS->Get__STRING();
			sCH__COMM_STS->Set__DATA(var_data);
		}

		// PUMP ON STS ...
		if(dEXT_CH__DI_PUMP_RUN_STS->Check__DATA(STR__ON) > 0)
		{
			sCH__PUMP_STS->Set__DATA(STR__ON);
		}
		else
		{
			sCH__PUMP_STS->Set__DATA(STR__OFF);
		}
	}	
}

void CObj__EDWARD_IPX::
Mon__WATER_LEAK_DETECT_MONITOR(CII_OBJECT__VARIABLE* p_variable,
							   CII_OBJECT__ALARM* p_alarm)
{
	int alm_cnt = 0;
	

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);
		

		if(dEXT_CH__DI_IO_COMM_STS->Check__DATA(STR__ONLINE) < 0)
		{
			continue;
		}
		if(dCFG_CH__WATER_LEAK_DETECT_PUMP_OFF->Check__DATA(STR__OFF) > 0)
		{
			continue;
		}

		if(dEXT_CH__DI_PUMP_LEAK_DETECT_STS->Check__DATA(STR__ON) > 0)
		{
			alm_cnt++;
		}
		else
		{
			alm_cnt = 0;
		}

		if(alm_cnt >= 3)
		{
			if(dEXT_CH__DI_PUMP_RUN_STS->Check__DATA(STR__ON) > 0)
			{
				dEXT_CH__DO_PUMP_ON_OFF->Set__DATA(STR__OFF);
			}

			// ...
			{
				CString r_act;
				int alarm_id = ALID__WATER_LEAK_DETECT_PUMP_OFF_ALARM;
			
				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}		
	}	
}
