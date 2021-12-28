#include "StdAfx.h"
#include "CObj__LAMP_CTRL.h"
#include "CObj__LAMP_CTRL__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__LAMP_CTRL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString pre__lamp_red;
	CString pre__lamp_yellow;
	CString pre__lamp_green;
	CString pre__lamp_blue;
	CString pre__alm_buzzer;
	CString pre__cfg_buzzer_use;
	CString ch_data;


	while(1)
	{
		// ...
		{
			double cfg_sec = aCH__CFG_BLINK_PERIOD_SEC->Get__VALUE();

			p_variable->Wait__SINGLE_OBJECT(cfg_sec);
		}

		// ...
		bool active__lamp_change = false;

		bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);
		if(active__remote_mode)
		{
			if(dCH__LIGHT_RED->Check__DATA(pre__lamp_red) < 0)
			{
				pre__lamp_red = dCH__LIGHT_RED->Get__STRING();

				active__lamp_change = true;
			}
			if(dCH__LIGHT_YELLOW->Check__DATA(pre__lamp_yellow) < 0)
			{
				pre__lamp_yellow = dCH__LIGHT_YELLOW->Get__STRING();

				active__lamp_change = true;
			}
			if(dCH__LIGHT_GREEN->Check__DATA(pre__lamp_green) < 0)
			{
				pre__lamp_green = dCH__LIGHT_GREEN->Get__STRING();

				active__lamp_change = true;
			}
			if(dCH__LIGHT_BLUE->Check__DATA(pre__lamp_blue) < 0)
			{
				pre__lamp_blue = dCH__LIGHT_BLUE->Get__STRING();

				active__lamp_change = true;
			}

			if(dCH__ALARM_BUZZER->Check__DATA(pre__alm_buzzer) < 0)
			{
				pre__alm_buzzer = dCH__ALARM_BUZZER->Get__STRING();

				active__lamp_change = true;
			}
		}
		else
		{
			if(dCH__LINK_LOCAL_LIGHT_RED->Check__DATA(pre__lamp_red) < 0)
			{
				pre__lamp_red = dCH__LINK_LOCAL_LIGHT_RED->Get__STRING();

				active__lamp_change = true;
			}
			if(dCH__LINK_LOCAL_LIGHT_YELLOW->Check__DATA(pre__lamp_yellow) < 0)
			{
				pre__lamp_yellow = dCH__LINK_LOCAL_LIGHT_YELLOW->Get__STRING();

				active__lamp_change = true;
			}
			if(dCH__LINK_LOCAL_LIGHT_GREEN->Check__DATA(pre__lamp_green) < 0)
			{
				pre__lamp_green = dCH__LINK_LOCAL_LIGHT_GREEN->Get__STRING();;

				active__lamp_change = true;
			}
			if(dCH__LINK_LOCAL_LIGHT_BLUE->Check__DATA(pre__lamp_blue) < 0)
			{
				pre__lamp_blue = dCH__LINK_LOCAL_LIGHT_BLUE->Get__STRING();

				active__lamp_change = true;
			}

			if(dCH__LINK_LOCAL_ALARM_BUZZER->Check__DATA(pre__alm_buzzer) < 0)
			{
				pre__alm_buzzer = dCH__LINK_LOCAL_ALARM_BUZZER->Get__STRING();

				active__lamp_change = true;
			}
		}

		if(dCH__CFG_BUZZER_USE->Check__DATA(pre__cfg_buzzer_use) < 0)
		{
			pre__cfg_buzzer_use = dCH__CFG_BUZZER_USE->Get__STRING();

			active__lamp_change = true;
		}

		if(active__lamp_change)
		{
			sCH__LINK_SET_LIGHT_RED->Set__DATA(pre__lamp_red);
			sCH__LINK_SET_LIGHT_YELLOW->Set__DATA(pre__lamp_yellow);
			sCH__LINK_SET_LIGHT_GREEN->Set__DATA(pre__lamp_green);
			sCH__LINK_SET_LIGHT_BLUE->Set__DATA(pre__lamp_blue);

			dEXT_CH__PARA_LAMP_RED->Set__DATA(pre__lamp_red);
			dEXT_CH__PARA_LAMP_YELLOW->Set__DATA(pre__lamp_yellow);
			dEXT_CH__PARA_LAMP_GREEN->Set__DATA(pre__lamp_green);
			dEXT_CH__PARA_LAMP_BLUE->Set__DATA(pre__lamp_blue);

			//
			if(pre__cfg_buzzer_use.CompareNoCase(STR__NO) == 0)
			{
				sCH__LINK_SET_ALARM_BUZZER->Set__DATA(STR__OFF);

				dEXT_CH__PARA_ALARM_BUZZER->Set__DATA(STR__OFF);
			}
			else 
			{
				sCH__LINK_SET_ALARM_BUZZER->Set__DATA(pre__alm_buzzer);

				dEXT_CH__PARA_ALARM_BUZZER->Set__DATA(pre__alm_buzzer);
			}

			doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
		}

		// ...
	}	
}

