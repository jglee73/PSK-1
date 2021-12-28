#include "StdAfx.h"
#include "CObj__MANUAL_PROC.h"


// ...
#define PROC_CMMD__MNT_READY				"MNT_READY"
#define PROC_CMMD__MNT_START				"MNT_START"

#define CHM_CMMD__HIGH_VAC_PUMP				"HIGH_VAC_PUMP"


int CObj__MANUAL_PROC::Call__MANUAL_PROCESS(CII_OBJECT__VARIABLE* p_variable)
{
	// ...
	{
		CString var_data = sCH__SEL_RECIPE_NAME->Get__STRING();
		sEXT_CH__RCP_NAME->Set__DATA(var_data);
	}

	// ...
	int flag = pOBJ_CTRL__PROC->Call__OBJECT(PROC_CMMD__MNT_READY);
	if(flag < 0)		return -1;

	flag = pOBJ_CTRL__PROC->Call__OBJECT(PROC_CMMD__MNT_START);
	if(flag < 0)		return -2;

	return flag;
}

int CObj__MANUAL_PROC::Call__ABORTL_DECHUCK(CII_OBJECT__VARIABLE* p_variable)
{
	// ...
	{
		CString var_data = sEXT_CH__RCP_ABORT_DECHUCK->Get__STRING();
		sEXT_CH__RCP_NAME->Set__DATA(var_data);
	}

	// ...
	int flag = pOBJ_CTRL__PROC->Call__OBJECT(PROC_CMMD__MNT_READY);
	if(flag < 0)		return -1;

	flag = pOBJ_CTRL__PROC->Call__OBJECT(PROC_CMMD__MNT_START);
	if(flag < 0)		return -2;

	return flag;
}
