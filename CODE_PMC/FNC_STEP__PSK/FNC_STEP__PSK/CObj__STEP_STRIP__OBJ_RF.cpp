#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"
#include "CObj__STEP_STRIP__DEF.h"


// ...
int CObj__STEP_STRIP
::RF_TOP_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_TOP)					return 1;

	aEXT_CH__RF_TOP__PARA_SET_POWER->Set__DATA(para_data);
	aEXT_CH__RF_TOP__PARA_HOLD_TIME->Set__VALUE(0.0);

	return pOBJ_CTRL__RF_TOP->Run__OBJECT(obj_mode);
}
int CObj__STEP_STRIP
::RF_TOP_OBJ__Start_OFF()
{
	if(!bActive__OBJ_CTRL__RF_TOP)					return 1;

	CString obj_mode = _RF_CMD__OFF;

	return pOBJ_CTRL__RF_TOP->Run__OBJECT(obj_mode);
}

int CObj__STEP_STRIP
::RF_TOP_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_TOP)					return -11;

	if(dEXT_CH__RF_TOP__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}
	if(dEXT_CH__RF_TOP__MON_REFLECT_HIGH_LIMIT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 2;
	}
	if(dEXT_CH__RF_TOP__MON_REFLECT_MAX_COEFFICIENT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 3;
	}

	return -1;
}
int CObj__STEP_STRIP
::RF_TOP_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__RF_TOP)					return -1;

	int obj_sts = pOBJ_CTRL__RF_TOP->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}

