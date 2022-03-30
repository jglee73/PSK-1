#include "StdAfx.h"
#include "CObj__VAC_ROBOT_SERIAL.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"
#include "CObj__VAC_ROBOT_SERIAL__ALID.h"

#include "CCommon_DEF.h"


// ...
void CObj__VAC_ROBOT_SERIAL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		diCH__COMM_STS->Set__DATA(STR__ONLINE);

		//
		sCH__MON_ERROR_ID->Set__DATA("0");
		sCH__MON_ERROR_MSG->Set__DATA("OK");
	}
	else
	{
		sCH__MON_ERROR_ID->Set__DATA("?");
		sCH__MON_ERROR_MSG->Set__DATA("??");
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		// ...
		{
			CString ch_data = diCH__COMM_STS->Get__STRING();

			if(ch_data.CompareNoCase(STR__OFFLINE) == 0)
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}

		// ERROR.CHECK ...
		{
			CString ch_data = sCH__MON_ERROR_ID->Get__STRING();
			int cur__err_id = atoi(ch_data);

			if(cur__err_id > 0)
			{
				int alarm_id = ALID__ERROR_STATE;
				CString alm_msg;
				CString alm_bff;
				CString r_act;
			
				CString err_msg = sCH__MON_ERROR_MSG->Get__STRING();

				alm_msg.Format(" * Error code is \"%1d\" ! \n", cur__err_id);
				alm_bff.Format(" * Error msg is \"%s\" \n", err_msg);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id, alm_msg);
			}
		}

		// ...
	}	
}

void CObj__VAC_ROBOT_SERIAL
::Mon__HYPER_TERMINAL_SEND(CII_OBJECT__VARIABLE* p_variable,
						   CII_OBJECT__ALARM* p_alarm)
{
	SCX__SEQ_INFO x_seq_info;

	CString str_msg;
	CString str_time;
	CString log_msg;
	CString var_data;
	int count = 0;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		if(dCH__HYPER_TERMINAL_SEND_REQ->Check__DATA("YES") > 0)
		{
			xCH__LOCK_FLAG->Set__DATA("YES");		// LockÀ» °Ç´Ù.

			// Do Action ...
			sCH__HYPER_TERMINAL_SEND_MSG->Get__DATA(var_data);
			log_msg.Format("COMMAND:%s \n\n", var_data);
			sCH__HYPER_TERMINAL_RECV_MSG->Set__DATA("");
			sCH__HYPER_TERMINAL_RECV_MSG->Set__DATA(log_msg);

			//
			xCH__UPDATE_FLAG->Get__DATA(str_msg);
			var_data.Format("%1d", atoi(str_msg)+1);
			xCH__UPDATE_FLAG->Set__DATA(var_data);
			_sleep(500);

			str_time = x_seq_info->Get__DATE_TIME_STRING();
			log_msg.Format("[%s] : <----- SEND -----> \n", str_time);
			sCH__HYPER_TERMINAL_RECV_MSG->Set__DATA("");
			sCH__HYPER_TERMINAL_RECV_MSG->Set__DATA(log_msg);

			//
			xCH__UPDATE_FLAG->Get__DATA(str_msg);
			var_data.Format("%1d", atoi(str_msg)+1);
			xCH__UPDATE_FLAG->Set__DATA(var_data);
			_sleep(500);

			// command
			sCH__HYPER_TERMINAL_SEND_MSG->Get__DATA(var_data);
			soCH__HYPER_TERMINAL_CMD->Set__DATA(var_data);

			dCH__HYPER_TERMINAL_SEND_REQ->Set__DATA("NO");
		}
	}	
}

