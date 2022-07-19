#include "stdafx.h"

#include "CObj__LPx_CTRL.h"
#include "CObj__LPx_CTRL__DEF.h"


// ...
int	CObj__LPx_CTRL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Fnc__INIT(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	xAPP__LOG_CTRL->WRITE__LOG("Initialized");
	return 1;
}

int	CObj__LPx_CTRL
::Call__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Fnc__INIT(p_variable, p_alarm) < 0)
	{
		return -11;
	}

	xAPP__LOG_CTRL->WRITE__LOG("Homed");
	return 1;
}

int	CObj__LPx_CTRL
:: Call__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(sEXT_CH__LP_INFO__DOOR_STATUS->Check__DATA(STR__OPEN) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Door opened");
		return 1;
	}

	return Fnc__DOOR_OPEN(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(sEXT_CH__LP_INFO__DOOR_STATUS->Check__DATA(STR__CLOSE) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Door closed");
		return 1;
	}

	return Fnc__DOOR_CLOSE(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__LOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	/*
	if(sEXT_CH__LP_INFO__LOAD_POS->Check__DATA(STR__OK) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Load");
		return 1;
	}
	*/

	return Fnc__LOAD(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	/*
	if(sEXT_CH__LP_INFO__UNLOAD_POS->Check__DATA(STR__OK) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Unload");
		return 1;
	}
	*/

	return Fnc__UNLOAD(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	/*
	if(sEXT_CH__LP_INFO__DOCK_STATUS->Check__DATA(STR__ON) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Dock");
		return 1;
	}
	*/

	return Fnc__SHUTTLE_IN(p_variable, p_alarm);
}

int	CObj__LPx_CTRL::
Call__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	/*
	if(sEXT_CH__LP_INFO__DOCK_STATUS->Check__DATA(STR__OFF) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Undock");
		return 1;
	}
	*/

	return Fnc__SHUTTLE_OUT(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__CLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(sEXT_CH__LP_INFO__CLAMP_STATUS->Check__DATA(STR__CLAMP) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Clamp");
		return 1;
	}

	return Fnc__CLAMP(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(sEXT_CH__LP_INFO__CLAMP_STATUS->Check__DATA(STR__UNCLAMP) > 0)
	{
		xAPP__LOG_CTRL->WRITE__LOG("Unclamp");
		return 1;
	}

	return Fnc__UNCLAMP(p_variable, p_alarm);
}

int	CObj__LPx_CTRL
::Call__MAP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;
	int i;

	if(iActive__SIM_MODE > 0)
	{
		for(i=0; i<CFG_LPx__SLOT_SIZE; i++)
		{
			dEXT_CH__LPx_MAP__RESULT[i]->Set__DATA(STR__PRESENT);
		}
	}

	// ...
	bool active__err_check = false;

	for(i=0; i<CFG_LPx__SLOT_SIZE; i++)
	{
		ch_data = dEXT_CH__LPx_MAP__RESULT[i]->Get__STRING();

		if((ch_data.CompareNoCase(STR__PRESENT) == 0)
		|| (ch_data.CompareNoCase(STR__ABSENT)  == 0))
		{
			dCH__RES_MAP_SLOT_X[i]->Set__DATA(ch_data);
		}
		else
		{
			active__err_check = true;

			dCH__RES_MAP_SLOT_X[i]->Set__DATA(STR__UNKNOWN);
		}
	}

	if(active__err_check)
	{
		// Error 

		return -1;
	}
	return 1;
}
