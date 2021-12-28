#include "StdAfx.h"
#include "CObj__OVATION_2560.h"


int CObj__OVATION_2560
::Call__STATUS_MON(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString str_data;
	int		poll_cnt = 0;

	Fnc__WRITE_APP_LOG("Monitoring Thread Start");

	while(1)
	{
		cx_timer_ctrl->POLL(0.1);

		// 1. Real Status IO Polling
		aiCH__ForwardPower->Get__DATA(str_data);
		//aCH__FWD_Power->Set__DATA(str_data);

		aiCH__ReflectPower->Get__DATA(str_data);
		//aCH__REFL_Power->Set__DATA(str_data);

		//aiCH__WhenOn_Actual_Frequency->Get__DATA(str_data);
		//aCH__FREQ_Value->Set__DATA(str_data);

		/* // Pulsing Mode 재확인 필요
		if (RF_Ps_state == 1)	// Pulsing Mode 사용일 때만, Pulsing Frequency, Duty Reading
		{
			aiCH__Ps_Frequency->Get__DATA(str_data);
			aCH__Ps_Frequency->Set__DATA(str_data);

			aiCH__Ps_Duty->Get__DATA(str_data);
			aCH__Ps_Duty->Set__DATA(str_data);
		}
		*/

		if (poll_cnt == 10)		// 1sec 주기로 Gen 상태 Reading
		{
			diCH__Process_Status->Get__DATA(str_data);
			poll_cnt = 0;
		}
		else
		{
			poll_cnt++;
		}
	}

	return 1;
}

int CObj__OVATION_2560
::Call__STATUS_MON_1(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString str_data;

	Fnc__WRITE_APP_LOG("Monitoring_1 Thread Start");

	while(1)
	{
		cx_timer_ctrl->POLL(0.1);

		if(dCH__MONITOR_FLAG->Check__DATA("Off") > 0)
		{
			continue;
		}

		// 1. Real Status IO Polling
		//diCH__Process_Status->Get__DATA(str_data);

		// 2. RF Ramp Up/Down Monitor - coding 필요 2018.12.08
		dCH__RF_CMD->Get__DATA(str_data);
		if (str_data.CompareNoCase("ON") == 0)
		{
			CString str_data;
			double  dbCfg_Rf_On_Timeout = 1.0;
			double	dbRamp_msec_to_sec = 1.0;

			double dbRamp_Time;
			double dbPower_Set;
			double dbstep_set_val;
			double db_unit_val;
			double db_current_set_val;
			double db_different_set_val;
		}
	}

	return 1;
}

int CObj__OVATION_2560
::Call__Alive_Signal(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__TIMER_CTRL cx_timer_ctrl;
	CString str_data;
	int		send_flag = 0;

	Fnc__WRITE_APP_LOG("Alive_Signal Thread Start");

	while(1)
	{
		cx_timer_ctrl->POLL(3.0);

		if(diCH__COMM_STS->Check__DATA("Online") > 0)
		{
			if (send_flag == 0)
			{
				dEXT_CH__RF_ALIVE_INTLK->Set__DATA("On");
				send_flag++;
				//Fnc__WRITE_APP_LOG("Alive_Signal On");
			}
			else
			{
				dEXT_CH__RF_ALIVE_INTLK->Set__DATA("Off");
				send_flag--;
				//Fnc__WRITE_APP_LOG("Alive_Signal Off");
			}
		}
	}

	return 1;
}
