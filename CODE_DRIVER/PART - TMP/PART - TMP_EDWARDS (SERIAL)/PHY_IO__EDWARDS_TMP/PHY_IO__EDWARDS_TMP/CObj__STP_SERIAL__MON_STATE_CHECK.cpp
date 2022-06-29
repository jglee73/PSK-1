#include "StdAfx.h"
#include "CObj__STP_SERIAL.h"


// ...
void CObj__STP_SERIAL
::Mon__STATE_CHECK(CII_OBJECT__VARIABLE* p_variable,	CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	sCH__INFO_ERROR_COUNT->Set__DATA("0");

	if(iActive__SIM_MODE > 0)
	{
		bActive__COOM_ONLINE = true;
	}
	else
	{
		bActive__COOM_ONLINE = false;
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// ...
		bool active__manual_type = false;
		
		if(dCH__CFG_CONTROL_TYPE->Check__DATA(STR__MANUAL) > 0)		
		{
			active__manual_type = true;			
		}

		// ...
		if(bActive__COOM_ONLINE)			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		else								sCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);

		// ...
		if(active__manual_type)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
		}
		else
		{
			if(sCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}

		if(active__manual_type)
		{

		}
		else
		{
			siCH__ReadMeas_HEXA->Get__STRING();
			siCH__ReadModFonct->Get__STRING();
			siCH__ReadMotorTemp->Get__STRING();
		}

		if(iActive__SIM_MODE > 0)
		{
			if(active__manual_type)
			{

			}
			else
			{
				double cur_hz  = aoCH__SET_SPEED_HZ->Get__VALUE();
				double cur_rpm = cur_hz * 60.0;

				ch_data.Format("%.0f", cur_rpm);
				sCH__INFO_ROT_SPEED_RPM->Set__DATA(ch_data);
			}
		}

		if(active__manual_type)
		{
			ch_data = sCH__MANUAL_ROT_SPEED_RPM->Get__STRING();
			sCH__INFO_ROT_SPEED_RPM->Set__DATA(ch_data);

			int cur_rpm = atoi(ch_data);
			if(cur_rpm > 0)			sCH__MON_PUMP_STS->Set__DATA(STR__ON);
			else					sCH__MON_PUMP_STS->Set__DATA(STR__OFF);

			ch_data = sCH__MANUAL_ERROR_COUNT->Get__STRING();
			int cur_err = atoi(ch_data);
			if(cur_err > 0)			sCH__MON_ERROR_STS->Set__DATA(STR__ON);
			else					sCH__MON_ERROR_STS->Set__DATA(STR__OFF);
		}
		else
		{
			ch_data = sCH__INFO_ROT_SPEED_RPM->Get__STRING();
			int cur_rpm = atoi(ch_data);
			if(cur_rpm > 0)			sCH__MON_PUMP_STS->Set__DATA(STR__ON);
			else					sCH__MON_PUMP_STS->Set__DATA(STR__OFF);

			ch_data = sCH__INFO_ERROR_COUNT->Get__STRING();
			int cur_err = atoi(ch_data);
			if(cur_err > 0)			sCH__MON_ERROR_STS->Set__DATA(STR__ON);
			else					sCH__MON_ERROR_STS->Set__DATA(STR__OFF);
		}
	}	
}
