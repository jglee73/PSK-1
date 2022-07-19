#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"
#include "CObj_NET__VAC_PERSIMMON__ALID.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj_NET__VAC_PERSIMMON
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(iSim_Flag > 0)
	{
		m_nCommState = ONLINE;
	}
	else
	{
		m_nCommState = OFFLINE;
	}

	// ...
	{
		CString log_msg;

		log_msg.Format(" * %s <- %s \n", 
						siCH__VERSION->Get__CHANNEL_NAME(),
						siCH__VERSION->Get__STRING());
		log_msg += "\n";

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);


		if(m_nCommState == ONLINE)
		{
			sCH__OTR_OUT_MON__COMM_STS->Set__DATA(STR__ONLINE);
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
		else
		{
			sCH__OTR_OUT_MON__COMM_STS->Set__DATA(STR__OFFLINE);
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

			// ...
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString r_act;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM(alarm_id);
			}
		}

		// ...
	}	
}

