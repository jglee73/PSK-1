#include "StdAfx.h"
#include "CObj__VAC_NET.h"
#include "CObj__VAC_NET__DEF.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CObj__VAC_NET
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(iActive__SIM_MODE > 0)
	{
		bActive__COMM_ONLINE = true;

		//
		sCH__MON_VERSION->Set__DATA("???");

		sCH__MON_ACTIVE_FAULT->Set__DATA(STR__OFF);

		sCH__MON_STATE_PUMP_RUNNING->Set__DATA(STR__ON);
		sCH__MON_STATE_ROOTS_RUNNING->Set__DATA(STR__ON);

		sCH__MON_STATE_N2_VALVE->Set__DATA(STR__OPEN);
		sCH__MON_STATE_STDBY_VALVE->Set__DATA(STR__OPEN);
		sCH__MON_STATE_WATER_VALVE->Set__DATA(STR__OPEN);
		sCH__MON_STATE_INLET_VALVE->Set__DATA(STR__OPEN);
		sCH__MON_STATE_PERMIT_VALVE->Set__DATA(STR__OPEN);
		sCH__MON_STATE_HP_FB_VALVE->Set__DATA(STR__OPEN);

		sCH__MON_STATE_HEAT1_POWER->Set__DATA(STR__ON);
		sCH__MON_STATE_FAULT->Set__DATA(STR__OFF);
		sCH__MON_STATE_CONTROL_MODE->Set__DATA(STR__REMOTE);

		sCH__MON_STATE_PRESSURE_mBAR->Set__DATA("0.001");
		sCH__MON_STATE_PRESSURE_TORR->Set__DATA("0.001");
		sCH__MON_STATE_FB_POWER->Set__DATA(STR__ON);
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
	}
}
