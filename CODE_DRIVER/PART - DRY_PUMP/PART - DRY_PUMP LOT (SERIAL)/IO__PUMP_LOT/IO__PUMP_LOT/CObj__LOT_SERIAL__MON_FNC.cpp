#include "StdAfx.h"
#include "CObj__LOT_SERIAL.h"

#include "CObj__LOT_SERIAL__DEF.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj__LOT_SERIAL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		bActive__COMM_ONLINE = true;
	}
	else
	{
		bActive__COMM_ONLINE = false;
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		if(bActive__COMM_ONLINE)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);			
		}
		else
		{
			sCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);

			// ...
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString alm_msg;
				CString r_act;

				alm_msg = sCH__INFO_DRV_PARAMETER->Get__STRING();

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}

		// PUMP.State ...
		{
			CString ch_data = sCH__MON_MODE_STS->Get__STRING();

			if((ch_data.CompareNoCase(STR__Start) == 0)
			|| (ch_data.CompareNoCase(STR__Operating) == 0))
			{
				dCH__MON_PUMP_STS->Set__DATA(STR__ON);
			}
			else
			{
				dCH__MON_PUMP_STS->Set__DATA(STR__OFF);
			}
		}

		// Pump.Alarm ...
		{
			CString err_msg;

			if(sCH__MON_ALARM_PUMP_BODY_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump Body Temperature \n";
			}
			if(sCH__MON_ALARM_EXHAUST_PRESSURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Exhaust Pressure \n";
			}
			if(sCH__MON_ALARM_MISSING_OIL_TIMEOUT->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Missing Oil Timeout \n";
			}
			if(sCH__MON_ALARM_PUMP_MOTOR_CONTACTOR->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Missing Oil Timeout \n";
			}
			if(sCH__MON_ALARM_PUMP_MOTOR_OVERLOAD->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump Motor Overload \n";
			}
			if(sCH__MON_ALARM_BLOWER_BODY_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Body Temperature \n";
			}
			if(sCH__MON_ALARM_EMO->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * EMO \n";
			}
			if(sCH__MON_ALARM_PUMP_MOTOR_OVER_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump Motor Over-Temperature \n";
			}
			if(sCH__MON_ALARM_BLOWER_MOTOR_CONTACTOR->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Motor Contactor \n";
			}
			if(sCH__MON_ALARM_EXHAUST_MANIFOLD_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Exhaust Manifold Temperature \n";
			}
			if(sCH__MON_ALARM_BLOWER_MOTOR_OVERLOAD->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Motor Overload \n";
			}
			if(sCH__MON_ALARM_PURGE_FLOW_ANALOG_1->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Purge Flow Analog(1) \n";
			}
			if(sCH__MON_ALARM_PURGE_FLOW_ANALOG_2->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Purge Flow Analog(2) \n";
			}
			if(sCH__MON_ALARM_BLOWER_MOTOR_OVER_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Motor Ovver-Temperature \n";
			}
			if(sCH__MON_ALARM_H2O_FLOW->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * H2O Flow \n";
			}
			if(sCH__MON_ALARM_PUMP_MOTOR_CURRENT->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump Motor Current \n";
			}

			if(err_msg.GetLength() > 0)
			{
				dCH__MON_ACTIVE_FAULT->Set__DATA(STR__ON);

				// ...
				{
					int alm_id = ALID__PUMP_ALARM;
					CString r_act;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, err_msg);
				}
			}
			else
			{
				dCH__MON_ACTIVE_FAULT->Set__DATA(STR__OFF);
			}
		}

		// ...
		bool active__warning_check = false;

		// Pump.Warning ...
		{
			CString err_msg;

			if(sCH__MON_WARNING_PUMP_BODY_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump Body Temperature \n";
			}
			if(sCH__MON_WARNING_EXHAUST_PRESSURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Exhaust Pressure \n";
			}
			if(sCH__MON_WARNING_OIL_PRESSURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Oil Pressure \n";
			}
			if(sCH__MON_WARNING_H2O_FLOW->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * H2O Flow \n";
			}
			if(sCH__MON_WARNING_PURGE_FLOW_ANALOG_1->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Purge Flow Analog(1) \n";
			}
			if(sCH__MON_WARNING_PURGE_FLOW_ANALOG_2->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Purge Flow Analog(2) \n";
			}
			if(sCH__MON_WARNING_PROCESS_TEMPERATURE_LOW->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Process Temperature Low \n";
			}
			if(sCH__MON_WARNING_PROCESS_TEMPERATURE_HIGH->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Process Temperature High \n";
			}
			if(sCH__MON_WARNING_PUMP_MOTOR_OVER_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Process Temperature High \n";
			}
			if(sCH__MON_WARNING_PUMP_VFD_DIGITAL->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump VFD Digital \n";
			}
			if(sCH__MON_WARNING_EXHAUST_PRESSURE_LOW->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Exhaust Pressure High \n";
			}
			if(sCH__MON_WARNING_EXHAUST_PRESSURE_HIGH->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Exhaust Pressure Low \n";
			}
			if(sCH__MON_WARNING_PUMP_MOTOR_CURRENT->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump Motor Current \n";
			}
			if(sCH__MON_WARNING_HOT_N2_TEMPERAURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Hot N2 Temperature \n";
			}
			if(sCH__MON_WARNING_PUMP_VFD_ANALOG->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Pump VFD Analog \n";
			}

			if(err_msg.GetLength() > 0)
			{
				active__warning_check = true;

				// ...
				{
					int alm_id = ALID__PUMP_WARNING;
					CString r_act;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__WARNING_With_MESSAGE(alm_id, err_msg);
				}
			}
		}

		// Blower.Warning ...
		{
			CString err_msg;

			if(sCH__MON_WARNING_BLOWER_MOTOR_CURRENT->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Motor Current \n";
			}
			if(sCH__MON_WARNING_INLET_PRESSURE_SWITCH->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Inlet Pressure Switch \n";
			}
			if(sCH__MON_WARNING_BLOWER_1_VFD->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower 1 VFD Digital \n";
			}
			if(sCH__MON_WARNING_BLOWER_MOTOR_CONTACTOR->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Motor Contactor \n";
			}
			if(sCH__MON_WARNING_BLOWER_MOTOR_OVERLOAD->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Motor Overload \n";
			}
			if(sCH__MON_WARNING_BLOWER_BODY_TEMPERATURE->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower Body Temperature \n";
			}
			if(sCH__MON_WARNING_BLOWER_VFD->Check__DATA(STR__ON) > 0)
			{
				err_msg += " * Blower VFD Analog \n";
			}

			if(err_msg.GetLength() > 0)
			{
				active__warning_check = true;

				// ...
				{
					int alm_id = ALID__BLOWER_WARNING;
					CString r_act;

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__WARNING_With_MESSAGE(alm_id, err_msg);
				}
			}
		}

		if(active__warning_check)		dCH__MON_ACTIVE_WARNING->Set__DATA(STR__ON);
		else							dCH__MON_ACTIVE_WARNING->Set__DATA(STR__OFF);
	}
}
