#include "StdAfx.h"
#include "CObj__NAVII_SERIAL.h"


// ...
int CObj__NAVII_SERIAL
::Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		ch_data = "0.0";

		sCH__INFO_CTRL_MODE_CH1->Set__DATA(ch_data);
		sCH__INFO_CTRL_MODE_CH2->Set__DATA(ch_data);

		sCH__INFO_LOAD_POS_CH1->Set__DATA(ch_data);
		sCH__INFO_LOAD_POS_CH2->Set__DATA(ch_data);

		sCH__INFO_TUNE_POS_CH1->Set__DATA(ch_data);
		sCH__INFO_TUNE_POS_CH2->Set__DATA(ch_data);

		sCH__INFO_CAP_POS_CH1->Set__DATA(ch_data);
		sCH__INFO_CAP_POS_CH2->Set__DATA(ch_data);

		sCH__INFO_CAP_CURRENT_CH1->Set__DATA(ch_data);
		sCH__INFO_CAP_CURRENT_CH2->Set__DATA(ch_data);

		sCH__INFO_R_SENSOR_CH1->Set__DATA(ch_data);
		sCH__INFO_R_SENSOR_CH2->Set__DATA(ch_data);

		sCH__INFO_X_SENSOR_CH1->Set__DATA(ch_data);
		sCH__INFO_X_SENSOR_CH2->Set__DATA(ch_data);

		//
		ch_data = "0.0";

		sCH__CUR_LOAD_POS_CH1->Set__DATA(ch_data);
		sCH__CUR_LOAD_POS_CH2->Set__DATA(ch_data);

		sCH__CUR_TUNE_POS_CH1->Set__DATA(ch_data);
		sCH__CUR_TUNE_POS_CH2->Set__DATA(ch_data);

		sCH__CUR_CAP_POS_CH1->Set__DATA(ch_data);
		sCH__CUR_CAP_POS_CH2->Set__DATA(ch_data);
	}

	int loop_count = 0;
	bActive__COMM_ONLINE = true;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		loop_count++;
		if(loop_count > 10)			loop_count = 1;

		if((loop_count == 1) || (loop_count == 6))
		{
			if(dCH__CFG_USE_CH2->Check__DATA(STR__YES) > 0)
			{
				siCH__CTRL_MODE_HEXA_CH2->Get__STRING();
				siCH__CAPACITOR_POS_HEXA_CH2->Get__STRING();
			}
		}

		if(loop_count == 1)
		{
			if(bActive__COMM_ONLINE)			dCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
			else								dCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);
		}

		if(dCH__MON_COMM_STS->Check__DATA(STR__OFFLINE) > 0)
		{
			int alarm_id = ALID__OFFLINE_ALARM;
			CString alm_msg;
			CString	r_act;

			alm_msg = sPROTOCOL_INFO;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
		}

		if(iActive_SIM > 0)
		{
			CString ch_data;

			// LOAD.POS ...
			{
				sCH__CUR_LOAD_POS_CH1->Get__DATA(ch_data);
				sCH__INFO_LOAD_POS_CH1->Set__DATA(ch_data);

				sCH__CUR_LOAD_POS_CH2->Get__DATA(ch_data);
				sCH__INFO_LOAD_POS_CH2->Set__DATA(ch_data);
			}
			// TUNE.POS ...
			{
				sCH__CUR_TUNE_POS_CH1->Get__DATA(ch_data);
				sCH__INFO_TUNE_POS_CH1->Set__DATA(ch_data);

				sCH__CUR_TUNE_POS_CH2->Get__DATA(ch_data);
				sCH__INFO_TUNE_POS_CH2->Set__DATA(ch_data);
			}
			// CAP.POS ...
			{
				sCH__CUR_CAP_POS_CH1->Get__DATA(ch_data);
				sCH__INFO_CAP_POS_CH1->Set__DATA(ch_data);

				sCH__CUR_CAP_POS_CH2->Get__DATA(ch_data);
				sCH__INFO_CAP_POS_CH2->Set__DATA(ch_data);
			}
		}
	}

	return 1;
}
