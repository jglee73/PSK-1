#include "StdAfx.h"
#include "CObj__STEP_METAL.h"
#include "CObj__STEP_METAL__DEF.h"


// ...
int CObj__STEP_METAL
::HTR_CHUCK_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__HTR_CHUCK)			return 1;

	return pOBJ_CTRL__HTR_CHUCK->Run__OBJECT(obj_mode);
}
int CObj__STEP_METAL
::HTR_CHUCK_OBJ__Call_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__HTR_CHUCK)			return 1;

	return pOBJ_CTRL__HTR_CHUCK->Call__OBJECT(obj_mode);
}

int CObj__STEP_METAL
::HTR_CHUCK_OBJ__Init_DATA()
{
	if(!bActive__OBJ_CTRL__HTR_CHUCK)			return 1;

	for(int i=0; i<_CFG__CHUCK_SIZE; i++)
	{
		sEXT_CH__HTR_CHUCK__PARA_PROC_REF_SP_X[i]->Set__DATA("");
	}
	return 1;
}

int CObj__STEP_METAL
::HTR_CHUCK_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__HTR_CHUCK)			return -1;

	int obj_sts = pOBJ_CTRL__HTR_CHUCK->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)		return 1;

	return -1;
}

int CObj__STEP_METAL
::HTR_CHUCK_OBJ__Is_BUSY()
{
	if(!bActive__OBJ_CTRL__HTR_CHUCK)			return -1;

	return pOBJ_CTRL__HTR_CHUCK->Is__OBJ_BUSY();
}

int CObj__STEP_METAL
::HTR_CHUCK_OBJ__Check_STABLE_ERROR()
{
	if(bActive__OBJ_CTRL__HTR_CHUCK)			return -1;

	for(int i=0; i<_CFG__CHUCK_SIZE; i++)
	{
		if(dEXT_CH__HTR_CHUCK__MON_IDLE_ABORT_ACTIVE_X[i]->Check__DATA(STR__ON) > 0)		return 1;
		if(dEXT_CH__HTR_CHUCK__MON_PROC_ABORT_ACTIVE_X[i]->Check__DATA(STR__ON) > 0)		return 2;
	}
	return -11;
}


// ...
int CObj__STEP_METAL
::HTR_WALL_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__HTR_WALL)			return 1;

	return pOBJ_CTRL__HTR_WALL->Run__OBJECT(obj_mode);
}
int CObj__STEP_METAL
::HTR_WALL_OBJ__Call_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__HTR_WALL)			return 1;

	return pOBJ_CTRL__HTR_WALL->Call__OBJECT(obj_mode);
}

int CObj__STEP_METAL
::HTR_WALL_OBJ__Init_DATA()
{
	if(!bActive__OBJ_CTRL__HTR_WALL)			return 1;

	for(int i=0; i<_CFG__WALL_SIZE; i++)
	{
		sEXT_CH__HTR_WALL__PARA_PROC_REF_SP_X[i]->Set__DATA("");
	}
	return 1;
}

int CObj__STEP_METAL
::HTR_WALL_OBJ__Check_ABORTED()
{
	if(!bActive__OBJ_CTRL__HTR_WALL)			return -1;

	int obj_sts = pOBJ_CTRL__HTR_WALL->Get__OBJECT_STATUS();
	if(obj_sts == OBJECT_STATUS__ABORTED)		return 1;

	return -1;
}

int CObj__STEP_METAL
::HTR_WALL_OBJ__Is_BUSY()
{
	if(!bActive__OBJ_CTRL__HTR_WALL)			return -1;

	return pOBJ_CTRL__HTR_WALL->Is__OBJ_BUSY();
}

int CObj__STEP_METAL
::HTR_WALL_OBJ__Check_STABLE_ERROR()
{
	if(bActive__OBJ_CTRL__HTR_WALL)				return -1;

	for(int i=0; i<_CFG__WALL_SIZE; i++)
	{
		if(dEXT_CH__HTR_WALL__MON_IDLE_ABORT_ACTIVE_X[i]->Check__DATA(STR__ON) > 0)		return 1;
		if(dEXT_CH__HTR_WALL__MON_PROC_ABORT_ACTIVE_X[i]->Check__DATA(STR__ON) > 0)		return 2;
	}
	return -11;
}

