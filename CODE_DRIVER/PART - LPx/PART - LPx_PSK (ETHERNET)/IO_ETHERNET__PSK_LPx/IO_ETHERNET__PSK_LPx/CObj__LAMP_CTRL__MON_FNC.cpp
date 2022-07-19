#include "StdAfx.h"
#include "CObj__LAMP_CTRL.h"
#include "CObj__LAMP_CTRL__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__LAMP_CTRL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString cur__lamp_red;
	CString cur__lamp_yellow;
	CString cur__lamp_green;
	CString cur__lamp_blue;
	CString cur__alm_buzzer;
	CString cur__cfg_buzzer_use;

	CString ch_data;


	while(1)
	{
		// ...
		{
			double cfg_sec = aCH__CFG_BLINK_PERIOD_SEC->Get__VALUE();

			p_variable->Wait__SINGLE_OBJECT(cfg_sec);
		}

		// LINK.LIGHT ...
		if(dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE) > 0)			
		{
			if(dCH__LINK_LIGHT_RED_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)				cur__lamp_red = STR__BLINK;
			else																		cur__lamp_red = dCH__LINK_LIGHT_RED_ON_OFF_ACTIVE->Get__STRING();

			if(dCH__LINK_LIGHT_YELLOW_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)			cur__lamp_yellow = STR__BLINK;
			else																		cur__lamp_yellow = dCH__LINK_LIGHT_YELLOW_ON_OFF_ACTIVE->Get__STRING();
			
			if(dCH__LINK_LIGHT_GREEN_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)			cur__lamp_green = STR__BLINK;
			else																		cur__lamp_green = dCH__LINK_LIGHT_GREEN_ON_OFF_ACTIVE->Get__STRING();
			
			if(dCH__LINK_LIGHT_BLUE_ON_OFF_ACTIVE->Check__DATA(STR__ON) > 0)			cur__lamp_blue = STR__BLINK;
			else																		cur__lamp_blue = dCH__LINK_LIGHT_BLUE_ON_OFF_ACTIVE->Get__STRING();

			// Alarm.Buzzer ...
			{
				cur__alm_buzzer = dCH__LINK_ALARM_BUZZER->Get__STRING();
			}
		}
		else
		{
			if(dCH__LOCAL_LINK_LIGHT_RED_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)		cur__lamp_red = STR__BLINK;
			else																		cur__lamp_red = dCH__LOCAL_LINK_LIGHT_RED_ON_OFF_ACTIVE->Get__STRING();

			if(dCH__LOCAL_LINK_LIGHT_YELLOW_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)		cur__lamp_yellow = STR__BLINK;
			else																		cur__lamp_yellow = dCH__LOCAL_LINK_LIGHT_YELLOW_ON_OFF_ACTIVE->Get__STRING();

			if(dCH__LOCAL_LINK_LIGHT_GREEN_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)		cur__lamp_green = STR__BLINK;
			else																		cur__lamp_green = dCH__LOCAL_LINK_LIGHT_GREEN_ON_OFF_ACTIVE->Get__STRING();;

			if(dCH__LOCAL_LINK_LIGHT_BLUE_BLINK_ACTIVE->Check__DATA(STR__ON) > 0)		cur__lamp_blue = STR__BLINK;
			else																		cur__lamp_blue = dCH__LOCAL_LINK_LIGHT_BLUE_ON_OFF_ACTIVE->Get__STRING();

			// Alarm.Buzzer ...
			{
				cur__alm_buzzer = dCH__LOCAL_LINK_ALARM_BUZZER->Get__STRING();
			}
		}

		// CFG.Buzzer ...
		{
			cur__cfg_buzzer_use = dCH__CFG_BUZZER_USE->Get__STRING();
		}

		// IO.Update ...
		{
			sCH__LINK_SET_LIGHT_RED->Set__DATA(cur__lamp_red);
			sCH__LINK_SET_LIGHT_YELLOW->Set__DATA(cur__lamp_yellow);
			sCH__LINK_SET_LIGHT_GREEN->Set__DATA(cur__lamp_green);
			sCH__LINK_SET_LIGHT_BLUE->Set__DATA(cur__lamp_blue);

			dEXT_CH__PARA_LAMP_RED->Set__DATA(cur__lamp_red);
			dEXT_CH__PARA_LAMP_YELLOW->Set__DATA(cur__lamp_yellow);
			dEXT_CH__PARA_LAMP_GREEN->Set__DATA(cur__lamp_green);
			dEXT_CH__PARA_LAMP_BLUE->Set__DATA(cur__lamp_blue);

			//
			if(cur__cfg_buzzer_use.CompareNoCase(STR__NO) == 0)
			{
				sCH__LINK_SET_ALARM_BUZZER->Set__DATA(STR__OFF);

				dEXT_CH__PARA_ALARM_BUZZER->Set__DATA(STR__OFF);
			}
			else 
			{
				sCH__LINK_SET_ALARM_BUZZER->Set__DATA(cur__alm_buzzer);

				dEXT_CH__PARA_ALARM_BUZZER->Set__DATA(cur__alm_buzzer);
			}

			doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
		}

		// ...
	}	
}

