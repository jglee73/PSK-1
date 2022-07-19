#include "stdafx.h"

#include "CObj__VERITY_STD__ALID.h"
#include "CObj__VERITY_STD__DEF.h"
#include "CObj__VERITY_STD.h"


// ...
void CObj__VERITY_STD
::Mon__IO_MONITORING(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;
	
	// ...
	{
		log_msg = "Mon__IO_MONITORING() - Sart ... \n";
		log_msg += "\n";

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}

	if(iActive__SIM_MODE > 0)
	{
		bActive__COMM_ONLINE = true;
	}
	else
	{
		bActive__COMM_ONLINE = false;

		// ...
		{
			log_msg = "EPD.Connect ... Start \n";

			mX__Log_Ctrl->WRITE__LOG(log_msg);
		}

		// ...
		bool active__connect_check = false;

		// ...
		{
			doCH__Control_SET->Set__DATA(STR__Connect);

			if(sCH__INFO_DRV_CONTROL_STS->Check__DATA(STR__OK) > 0)
			{
				active__connect_check = true;
			}
		}

		// ...
		{
			log_msg = "EPD.Connect ... End \n";
			
			if(active__connect_check)			log_msg += " * active__connect_check : OK ! \n";
			else								log_msg += " * active__connect_check : Error ! \n";

			log_msg += "\n";

			mX__Log_Ctrl->WRITE__LOG(log_msg);
		}
	}

	// ...
	{
		doCH__VERSION_REQ->Set__DATA(STR__ON);

		log_msg.Format(" * %s <- %s \n", 
						sCH__INFO_VERSION->Get__CHANNEL_NAME(),
						sCH__INFO_VERSION->Get__STRING());
		log_bff += log_msg;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


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
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}	
		}

		// ...
	}
}

