#include "StdAfx.h"
#include "CObj__VIRTUAL_STD.h"
#include "CObj__VIRTUAL_STD__DEF.h"


//------------------------------------------------------------------------------------
void CObj__VIRTUAL_STD
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var_data;

	while(1)
	{
		cx_timer_ctrl->WAIT(0.1);

		// ONLINE, OFFLINE ...
		if(iSim_Flag > 0)
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

			dEXT_CH__DI_IO_COMM_STS->Get__DATA(var_data);
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

void CObj__VIRTUAL_STD
::Mon__WATER_LEAK_DETECT_MONITOR(CII_OBJECT__VARIABLE* p_variable,
							     CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString var_data;
	int nCnt = 0;

	while(1)
	{
		cx_timer_ctrl->WAIT(1.0);

		if(dEXT_CH__DI_IO_COMM_STS->Check__DATA(STR__ONLINE) < 0)
		{
			continue;
		}

		if(dCFG_CH__WATER_LEAK_DETECT_PUMP_OFF->Check__DATA("FALSE") > 0)
		{
			continue;
		}

		if(dEXT_CH__DI_PUMP_LEAK_DETECT_STS->Check__DATA("ON") > 0)
		{
			nCnt++;
		}
		else
		{
			nCnt = 0;
		}

		if(nCnt >= 3)
		{
			// PUMP ON STS ...
			if(dEXT_CH__DI_PUMP_RUN_STS->Check__DATA(STR__ON) > 0)
			{
				dEXT_CH__DO_PUMP_ON_OFF->Set__DATA("OFF");
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
