#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"
#include "CObj__STEP_STRIP__DEF.h"


// ...
int CObj__STEP_STRIP
::LIFT_PIN_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__LIFT_PIN)				return 1;

	return pOBJ_CTRL__LIFT_PIN->Run__OBJECT(obj_mode);
}

int CObj__STEP_STRIP
::LIFT_PIN_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__LIFT_PIN)				return -1;

	int obj_sts = pOBJ_CTRL__LIFT_PIN->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}

