#include "StdAfx.h"
#include "CObj__LV32_BLDC.h"



//--------------------------------------------------------------------------------
void CObj__LV32_BLDC
::Mon__ALM_REPORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm)
{
	iCOMM_STATE = ONLINE;

	if(iActive_SIM > 0)
	{
		for(int i=0; i<CFG__FAN_SIZE; i++)
		{
			sCH__FFU_BLOCK__ALARM_LOCAL_MODE_X[i]->Set__DATA(STR__OFF);
			sCH__FFU_BLOCK__ALARM_POWER_OFF_X[i]->Set__DATA(STR__OFF);
			sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[i]->Set__DATA(STR__OFF);
			sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[i]->Set__DATA(STR__OFF);
			sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[i]->Set__DATA(STR__OFF);
		}	
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		if(iActive_SIM > 0)
		{
			iCOMM_STATE = ONLINE;
		}

		if(iCOMM_STATE == ONLINE)
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
		else
		{
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

			// ...
			{	
				int alm_id = ALID__FFU_OFFLINE;
				CString r_act;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM(alm_id);
			}
		}

		// Error Check ...
		{
			bool active_error = false;

			int alm_id;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			CString ch_data;
			int i;

			if(dCH__CFG_FFU_TYPE->Check__DATA(STR__RPM) > 0)
			{
				int i_size = (int) aCH__CFG_RANGE_ICU_COUNT->Get__VALUE();
				if(i_size > CFG__FAN_SIZE)			i_size = CFG__FAN_SIZE;

				double cfg__low_limit = aCH__CFG_FFU_LOW_LIMIT_RPM->Get__VALUE();

				for(i=0; i<i_size; i++)
				{
					ch_data = sCH__FFU_BLOCK__RPM_SV_X[i]->Get__STRING();
					double cur_value = atof(ch_data);
					if(cur_value > cfg__low_limit)			continue;

					active_error = true;

					// Alarm ...
					{
						alm_id = ALID__FFU_FAN_LOW_LIMIT_RPM_X + i;
			
						alm_bff.Format("The config low limit rpm is %.0f. \n", cfg__low_limit);
						alm_msg  = alm_bff;
						alm_bff.Format("The current rpm is %.0f. \n", cur_value);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}

				for(i=0; i<i_size; i++)
				{
					if(sCH__FFU_BLOCK__ALARM_POWER_OFF_X[i]->Check__DATA(STR__ON) > 0)
					{
						active_error = true;

						// Alarm ...
						{
							alm_id = ALID__FFU_FAN_ALARM_POWER_OFF_X + i;

							alm_msg.Format(" * %s <- %s. \n", 
										   sCH__FFU_BLOCK__ALARM_POWER_OFF_X[i]->Get__CHANNEL_NAME(),
										   sCH__FFU_BLOCK__ALARM_POWER_OFF_X[i]->Get__STRING());

							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
						}
					}
					if(sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[i]->Check__DATA(STR__ON) > 0)
					{
						active_error = true;

						// Alarm ...
						{
							alm_id = ALID__FFU_FAN_ALARM_OVER_CURRENT_X + i;

							alm_msg.Format(" * %s <- %s. \n", 
										   sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[i]->Get__CHANNEL_NAME(),
										   sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[i]->Get__STRING());

							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
						}
					}
					if(sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[i]->Check__DATA(STR__ON) > 0)
					{
						active_error = true;

						// Alarm ...
						{
							alm_id = ALID__FFU_FAN_ALARM_MOTOR_ERROR_X + i;

							alm_msg.Format(" * %s <- %s. \n", 
										   sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[i]->Get__CHANNEL_NAME(),
										   sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[i]->Get__STRING());

							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
						}
					}
					if(sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[i]->Check__DATA(STR__ON) > 0)
					{
						active_error = true;

						// Alarm ...
						{
							alm_id = ALID__FFU_FAN_ALARM_CONNECTION_ERROR_X + i;

							alm_msg.Format(" * %s <- %s. \n", 
										   sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[i]->Get__CHANNEL_NAME(),
										   sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[i]->Get__STRING());

							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
						}
					}
				}
			}
			else
			{
				double cfg__low_limit = aCH__CFG_FFU_LOW_LIMIT_DIFF_PRESSURE->Get__VALUE();

				ch_data = sCH__FFU_UNIT__PRESSURE_VALUE->Get__STRING();
				double cur_value = atof(ch_data);

				if(cur_value <= cfg__low_limit)
				{
					active_error = true;

					// Alarm ...
					{
						alm_id = ALID__FFU_UNIT_LOW_LIMIT_DIFF_PRESSURE;

						alm_bff.Format("The config low-limit differential pressure is %.0f. \n", cfg__low_limit);
						alm_msg  = alm_bff;
						alm_bff.Format("The current differential pressure is %.0f. \n", cur_value);
						alm_msg += alm_bff;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}
				}
			}
			
			if(active_error)			sCH__MON_SYSTEM_ABORT->Set__DATA(STR__YES);
			else						sCH__MON_SYSTEM_ABORT->Set__DATA(STR__NO);
		}

		// ...
	}
}
