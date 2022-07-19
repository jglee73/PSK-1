#include "StdAfx.h"
#include "CObj__STEP_METAL.h"
#include "CObj__STEP_METAL__DEF.h"


// SOURCE ...
int CObj__STEP_METAL
::MAT_SRC_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__MAT_SRC)					return 1;

	return pOBJ_CTRL__MAT_SRC->Run__OBJECT(obj_mode);
}

int CObj__STEP_METAL
::MAT_SRC_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__MAT_SRC)					return -1;

	int obj_sts = pOBJ_CTRL__MAT_SRC->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}

// BIAS ...
int CObj__STEP_METAL
::MAT_BIAS_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__MAT_BIAS)				return 1;

	return pOBJ_CTRL__MAT_BIAS->Run__OBJECT(obj_mode);
}

int CObj__STEP_METAL
::MAT_BIAS_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__MAT_BIAS)				return -1;

	int obj_sts = pOBJ_CTRL__MAT_BIAS->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)			return 1;

	return -1;
}
