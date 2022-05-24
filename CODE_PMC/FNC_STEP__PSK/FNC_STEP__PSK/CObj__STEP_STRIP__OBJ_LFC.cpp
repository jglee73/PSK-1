#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"
#include "CObj__STEP_STRIP__DEF.h"


// ...
int CObj__STEP_STRIP
::LFC_OBJ__Start_CONTROL(const CString& para_flow)
{
	if(!bActive__OBJ_CTRL__LFC)					return 1;

	// ...
	CString obj_mode;

	double  set_flow     = atof(para_flow);
	double  set_ramp_sec = 0.0;

	if(set_flow > 0.1)
	{
		if(set_ramp_sec > 0.1)		obj_mode = _LFC_CMD__RAMP_CTRL;
		else						obj_mode = _LFC_CMD__CONTROL;

		sEXT_CH__LFC__PARA_SET_FLOW->Set__DATA(para_flow);
		sEXT_CH__LFC__PARA_RAMP_SEC->Set__DATA("0.0");
	}
	else
	{
		obj_mode = _LFC_CMD__CLOSE;

		sEXT_CH__LFC__PARA_SET_FLOW->Set__DATA("0.0");
		sEXT_CH__LFC__PARA_RAMP_SEC->Set__DATA("0.0");
	}

	return pOBJ_CTRL__LFC->Run__OBJECT(obj_mode);
}
int CObj__STEP_STRIP
::LFC_OBJ__Start_CLOSE()
{
	if(!bActive__OBJ_CTRL__LFC)					return 1;

	// ...
	CString obj_mode = _LFC_CMD__CLOSE;

	return pOBJ_CTRL__LFC->Run__OBJECT(obj_mode);
}
int CObj__STEP_STRIP
::LFC_OBJ__Start_DUMP()
{
	if(!bActive__OBJ_CTRL__LFC)					return 1;

	// ...
	CString obj_mode = _LFC_CMD__DUMP;

	return pOBJ_CTRL__LFC->Run__OBJECT(obj_mode);
}
int CObj__STEP_STRIP
::LFC_OBJ__Call_DUMP()
{
	if(!bActive__OBJ_CTRL__LFC)					return 1;

	// ...
	CString obj_mode = _LFC_CMD__DUMP;

	return pOBJ_CTRL__LFC->Call__OBJECT(obj_mode);
}

int CObj__STEP_STRIP
::LFC_OBJ__Check_ERROR()
{
	if(!bActive__OBJ_CTRL__LFC)					return -1;

	if(dEXT_CH__LFC__MON_LFC_ABORT_ACTIVE->Check__DATA(STR__ON) > 0)
	{
		return 1;
	}
	return -1;
}
int CObj__STEP_STRIP
::LFC_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__LFC)					return -1;

	int obj_sts = pOBJ_CTRL__LFC->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)		return 1;		

	return -1;
}
