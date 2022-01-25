#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::RF_SRC_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_SRC)			return 1;

	return pOBJ_CTRL__RF_SRC->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::RF_SRC_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_SRC)			return -11;

	if(dEXT_CH__RF_SRC__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
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

// ...
int CObj__STEP_STD
::RF_BIAS_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data)
{
	if(!bActive__OBJ_CTRL__RF_BIAS)			return 1;

	return pOBJ_CTRL__RF_BIAS->Run__OBJECT(obj_mode);
}
int CObj__STEP_STD
::RF_BIAS_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__RF_BIAS)			return -11;

	if(dEXT_CH__RF_BIAS__MON_POWER_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
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

