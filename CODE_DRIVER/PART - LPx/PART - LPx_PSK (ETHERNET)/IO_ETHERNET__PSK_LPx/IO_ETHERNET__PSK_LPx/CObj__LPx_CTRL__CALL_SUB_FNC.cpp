#include "stdafx.h"

#include "CObj__LPx_CTRL__ALID.h"
#include "CObj__LPx_CTRL__DEF.h"
#include "CObj__LPx_CTRL.h"

#include "CDriver__LPx_ETHERNET__DEF.h"


//--------------------------------------------------------------------------------
void CObj__LPx_CTRL
::Fnc__APP_LOG(const CString& log_msg)
{
	xAPP__LOG_CTRL->WRITE__LOG(log_msg);
}

int  CObj__LPx_CTRL
::Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(sEXT_CH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) < 0)
	{
		int alarm_id = ALID__OFFLINE;

		p_alarm->Post__ALARM(alarm_id);
		return -1;
	}
	return 1;
}
int CObj__LPx_CTRL
::Wait__LP_STATE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int sim_count = 0;

	if(iActive__SIM_MODE > 0)
	{
		siEXT_CH__LP_STATE->Set__DATA(STR__OK);
		sEXT_CH__LP_INFO__STATUS->Set__DATA(STR__RUN);
	}

	while(1)
	{
		if(p_variable->Check__CTRL_ABORT() > 0)						return -1;

		if(siEXT_CH__LP_STATE->Check__DATA(STR__OK) < 0)			return -11;
		if(sEXT_CH__LP_INFO__STATUS->Check__DATA(STR__STOP) > 0)	return 1;

		Sleep(100);

		if(iActive__SIM_MODE > 0)
		{
			sim_count++;
			if(sim_count >= 10)
			{
				sEXT_CH__LP_INFO__STATUS->Set__DATA(STR__STOP);
			}
		}
	}

	return -11;
}


//--------------------------------------------------------------------------------
int CObj__LPx_CTRL
::Fnc__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__INIT);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sEXT_CH__LP_INFO__INITIAL->Set__DATA(STR__ON);
	}

	if(sEXT_CH__LP_INFO__INITIAL->Check__DATA(STR__ON) < 0)
	{
		return -12;
	}
	return 1;
}

int CObj__LPx_CTRL
::Fnc__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__OPEN);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sEXT_CH__LP_INFO__DOOR_STATUS->Set__DATA(STR__OPEN);
	}

	if(sEXT_CH__LP_INFO__DOOR_STATUS->Check__DATA(STR__OPEN) < 0)
	{
		return -12;
	}
	return 1;
}
int CObj__LPx_CTRL
::Fnc__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__CLOSE);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sEXT_CH__LP_INFO__DOOR_STATUS->Set__DATA(STR__CLOSE);
	}

	if(sEXT_CH__LP_INFO__DOOR_STATUS->Check__DATA(STR__CLOSE) < 0)
	{
		return -12;
	}
	return 1;
}

int CObj__LPx_CTRL
::Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__LOAD);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sCH__MON_FOUP_POS_STATUS->Set__DATA(STR__LOAD);

		sEXT_CH__LP_INFO__DOOR_STATUS->Set__DATA(STR__OPEN);
	}

	if(sEXT_CH__LP_INFO__DOOR_STATUS->Check__DATA(STR__OPEN) < 0)
	{
		return -12;
	}

	_Update__LPx_STATE();
	return 1;
}
int CObj__LPx_CTRL
::Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__UNLOAD);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sCH__MON_FOUP_POS_STATUS->Set__DATA(STR__UNLOAD);

		sEXT_CH__LP_INFO__DOOR_STATUS->Set__DATA(STR__CLOSE);
	}

	if(sEXT_CH__LP_INFO__DOOR_STATUS->Check__DATA(STR__CLOSE) < 0)
	{
		return -12;
	}

	_Update__LPx_STATE();
	return 1;
}

int CObj__LPx_CTRL
::Fnc__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return -1;
}
int CObj__LPx_CTRL
::Fnc__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return -1;
}

int CObj__LPx_CTRL
::Fnc__CLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__CLAMP);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sEXT_CH__LP_INFO__CLAMP_STATUS->Set__DATA(STR__CLAMP);
	}

	if(sEXT_CH__LP_INFO__CLAMP_STATUS->Check__DATA(STR__CLAMP) < 0)
	{
		return -12;
	}
	return 1;
}
int CObj__LPx_CTRL
::Fnc__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int state = Is__ONLINE(p_variable, p_alarm);
	if(state < 0)		return - 1;

	// ...
	doEXT_CH__LP_CMMD->Set__DATA(_CMD__UNCLAMP);

	if(Wait__LP_STATE(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	if(iActive__SIM_MODE > 0)
	{
		sEXT_CH__LP_INFO__CLAMP_STATUS->Set__DATA(STR__UNCLAMP);
	}

	if(sEXT_CH__LP_INFO__CLAMP_STATUS->Check__DATA(STR__UNCLAMP) < 0)
	{
		return -12;
	}
	return 1;
}
