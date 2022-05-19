#include "StdAfx.h"
#include "CObj__VAC_SERIAL.h"

#include "CObj__VAC_SERIAL__DEF.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj__VAC_SERIAL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	if(iActive__SIM_MODE > 0)
	{
		m_nCommState = ONLINE;
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.5);

		if(m_nCommState == OFFLINE)
		{
			sCH__MON_COMM_STS->Set__DATA(STR__OFFLINE);

			// ...
			{
				int alarm_id = ALID__OFFLINE_ALARM;
				CString alm_msg;
				CString r_act;

				alm_msg = sPROTOCOL_INFO;

				p_alarm->Check__ALARM(alarm_id,r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alarm_id,alm_msg);
			}
		}
		else
		{
			sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);			
		}
	}
}
