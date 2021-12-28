#include "StdAfx.h"
#include "CObj__VIRTUAL_STD.h"
#include "CObj__VIRTUAL_STD__DEF.h"


//-------------------------------------------------------------------------	
// Init -----
int  CObj__VIRTUAL_STD
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__INIT(p_variable,p_alarm);
}

int  CObj__VIRTUAL_STD
::Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	m_xAsncTimer->STOP();

	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	if(iSim_Flag > 0)
	{
		dEXT_CH__DI_PUMP_ALARM_STS->Set__DATA("OFF");
		dEXT_CH__DI_PUMP_WARNING_STS->Set__DATA("OFF");
		dEXT_CH__DI_PUMP_WATER_FLOW_STS->Set__DATA("ON");

		dEXT_CH__DI_PUMP_RUN_STS->Set__DATA("ON");
	}

	return Fnc__PUMP_ON(p_variable,p_alarm);
}

// Pump On -----
int  CObj__VIRTUAL_STD
::Call__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PUMP_ON(p_variable,p_alarm);
}

int  CObj__VIRTUAL_STD
::Fnc__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__TIMER_CTRL xTimer;
	xTimer->REGISTER__ABORT_OBJECT(sObject_Name);

LOOP_RETRY:

	// ...
	CString title;
	CString msg;

	CString var_data;
	int state;

	if(dEXT_CH__DI_PUMP_RUN_STS->Check__DATA("ON") > 0)
	{
		Fnc__APP_LOG("   Already PUMP [ON] Sts...   \n");
		return 1;
	}

	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	if(dEXT_CH__DI_PUMP_ALARM_STS->Check__DATA("ON") > 0)
	{
		int alarm_id = ALID__BEFORE_PUMP_ON_ALARM_STS;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		     if(r_act.CompareNoCase("CHECK_RETRY") == 0)		goto LOOP_RETRY;
		else if(r_act.CompareNoCase("ABORT") == 0)				return OBJ_ABORT;
	}

	dEXT_CH__DO_PUMP_ON_OFF->Set__DATA("ON");

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1;
	}

	if(dCFG_CH__PUMP_ON_SIGNAL_CHK_SKIP->Check__DATA("TRUE") > 0)
	{
		Fnc__APP_LOG("PUMP ON Signal On Check Skip..ret 1");

		if(iSim_Flag > 0)
		{
			dEXT_CH__DI_PUMP_RUN_STS->Set__DATA("ON");
		}
		return 1;
	}

	if(iSim_Flag > 0)
	{
		dEXT_CH__DI_PUMP_RUN_STS->Set__DATA("ON");
	}

	aCH__CFG_PUMP_ON_OFF_TIMEOUT->Get__DATA(var_data);
	sCH__SEQUENCE_MSG->Set__DATA("Waiting... PUMP ON STS");

	state = dEXT_CH__DI_PUMP_RUN_STS->When__DATA("ON", atof(var_data));
	if(state < 0) 			// TimeOut
	{
		int alarm_id = ALID__PUMP_POWER_ON__TIMEOUT;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)
		{
			goto LOOP_RETRY;
		}
		return -1;
	}
	else if( state == 0)    // Abort
	{
		msg.Format("   Object Aborted...[ret:%d]", state);
		Fnc__APP_LOG(msg);
		return  -1;
	}

	// Pump On Delay Time !!
	{
		aCH__CFG_PUMP_ON_DELAY_TIME->Get__DATA(var_data);
		m_xAsncTimer->START__COUNT_DOWN(atof(var_data));
	}

	while (1)
	{
		Sleep(50);

		if(m_xAsncTimer->Get__CURRENT_TIME() <= 0.1)
		{
			break;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}
	}

	return 1;
}

// Pump Off -----
int  CObj__VIRTUAL_STD
::Call__PUMP_OFF(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return Fnc__PUMP_OFF(p_variable,p_alarm);
}

int  CObj__VIRTUAL_STD
::Fnc__PUMP_OFF(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	// ...
	CString var_data;
	int state;

	CString title;
	CString msg;

	m_xAsncTimer->STOP();

	if(dEXT_CH__DI_PUMP_RUN_STS->Check__DATA("OFF") > 0)
	{
		Fnc__APP_LOG("   Already PUMP [OFF] Sts...   \n");
		return 1;
	}

	if(Is__OFFLINE(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	dEXT_CH__DO_PUMP_ON_OFF->Set__DATA("OFF");

	if(p_variable->Check__CTRL_ABORT() > 0)
	{
		return -1;
	}

	if(iSim_Flag > 0)
	{
		dEXT_CH__DI_PUMP_RUN_STS->Set__DATA("OFF");
	}

	// ...
	{
		aCH__CFG_PUMP_ON_OFF_TIMEOUT->Get__DATA(var_data);
		sCH__SEQUENCE_MSG->Set__DATA("Waiting... PUMP OFF STS");
	}
	
	state = dEXT_CH__DI_PUMP_RUN_STS->When__DATA("OFF", atof(var_data));

	if(state < 0) 			// TimeOut
	{
		int alarm_id = ALID__PUMP_POWER_OFF__TIMEOUT;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)
		{
			goto LOOP_RETRY;
		}
		return -1;
	}
	else if( state == 0)    // Abort
	{
		msg.Format("   Object Aborted...[ret:%d]", state);
		Fnc__APP_LOG(msg);
		return  -1;
	}

	return 1;
}
