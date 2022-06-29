#include "StdAfx.h"
#include "CObj__AFC_RTU.h"
#include "CObj__AFC_RTU__DEF.h"
#include "CObj__AFC_RTU__ALID.h"


//------------------------------------------------------------------------------------
void CObj__AFC_RTU
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	if(iActive__SIM_MODE > 0)
	{
		dCH__MON_MAT_STS_MANUAL_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_PRESET_ENABLE_ACTIVE->Set__DATA(STR__ON);
		dCH__MON_MAT_STS_ALARM_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_RFON_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_TUNE_MATCHED_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_COAXIAL_ALARM_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_COVER_ALARM_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_MOTOR_ALARM_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_FAN1_ALARM_ACTIVE->Set__DATA(STR__OFF);
		dCH__MON_MAT_STS_FAN2_ALARM_ACTIVE->Set__DATA(STR__OFF);

		bActive__COMM_ONLINE = true;
	}
	else
	{
		bActive__COMM_ONLINE = false;
	}

	int loop_count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		loop_count++;
		if(loop_count > 10)		loop_count = 1;


		if(loop_count == 1)
		{
			if(bActive__COMM_ONLINE)
			{
				sCH__MON_COMM_STATE->Set__DATA(STR__ONLINE);
			}
			else
			{
				sCH__MON_COMM_STATE->Set__DATA(STR__OFFLINE);

				// ...
				{
					int alarm_id = ALID__OFFLINE;
					CString	r_act;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alarm_id, "");
				}
			}
		}

		if(iActive__SIM_MODE > 0)
		{
			ch_data = aoCH__Preset_Load_Position->Get__STRING();
			sCH__MON_CUR_LOAD_POSITION->Set__DATA(ch_data);

			ch_data = aoCH__Preset_Tune_Position->Get__STRING();
			sCH__MON_CUR_TUNE_POSITION->Set__DATA(ch_data);
		}

		// ...
	}
}
