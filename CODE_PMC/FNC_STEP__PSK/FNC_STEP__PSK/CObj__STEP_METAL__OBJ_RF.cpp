#include "StdAfx.h"
#include "CObj__STEP_METAL.h"
#include "CObj__STEP_METAL__DEF.h"


// ...
int CObj__STEP_METAL
::RF_SRC_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data, const CString& para_warning,const CString& para_alarm)
{
	if(!bActive__OBJ_CTRL__RF_SRC)					return 1;

	aEXT_CH__RF_SRC__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_SRC__PARA_HOLD_TIME->Set__VALUE(0.0);

	aEXT_CH__RF_SRC__CFG_PROC_POWER_WARNING_BAND->Set__DATA(para_warning);
	aEXT_CH__RF_SRC__CFG_PROC_POWER_ABORT_BAND->Set__DATA(para_alarm);

	return pOBJ_CTRL__RF_SRC->Run__OBJECT(obj_mode);
}
int CObj__STEP_METAL
::RF_SRC_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_SRC)					return 1;
	
	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_SRC->Run__OBJECT(obj_mode);
}

int CObj__STEP_METAL
::RF_SRC_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_SRC)					return -11;

	if((dEXT_CH__RF_SRC__MON_IDLE_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	|| (dEXT_CH__RF_SRC__MON_PROC_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0))
	{
		return 1;
	}

	if(dEXT_CH__RF_SRC__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_SRC__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_METAL
::RF_SRC_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_SRC)					return -1;

	int obj_sts = pOBJ_CTRL__RF_SRC->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}


// ...
int CObj__STEP_METAL
::RF_BIAS_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data, const CString& para_warning,const CString& para_alarm)
{
	if(!bActive__OBJ_CTRL__RF_BIAS)					return 1;

	aEXT_CH__RF_BIAS__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_BIAS__PARA_HOLD_TIME->Set__VALUE(0.0);

	aEXT_CH__RF_BIAS__CFG_PROC_POWER_WARNING_BAND->Set__DATA(para_warning);
	aEXT_CH__RF_BIAS__CFG_PROC_POWER_ABORT_BAND->Set__DATA(para_alarm);

	return pOBJ_CTRL__RF_BIAS->Run__OBJECT(obj_mode);
}
int CObj__STEP_METAL
::RF_BIAS_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_BIAS)					return 1;

	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_BIAS->Run__OBJECT(obj_mode);
}

int CObj__STEP_METAL
::RF_BIAS_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_BIAS)					return -11;

	if((dEXT_CH__RF_BIAS__MON_IDLE_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	|| (dEXT_CH__RF_BIAS__MON_PROC_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0))
	{
		return 1;
	}

	if(dEXT_CH__RF_BIAS__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_BIAS__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_METAL
::RF_BIAS_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_BIAS)					return -1;

	int obj_sts = pOBJ_CTRL__RF_BIAS->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}

