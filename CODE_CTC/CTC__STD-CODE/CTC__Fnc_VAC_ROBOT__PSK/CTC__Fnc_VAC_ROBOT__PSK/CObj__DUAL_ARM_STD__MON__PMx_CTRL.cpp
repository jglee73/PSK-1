#include "StdAfx.h"
#include "CObj__DUAL_ARM_STD.h"

#include "Macro_Function.h"


// ...
void CObj__DUAL_ARM_STD::Mon__PMx_CTRL(CII_OBJECT__VARIABLE *p_variable)
{
	int idle_flag  =  1;
	int abort_flag = -1;

	while(1)
	{
		while(xSCH_MATERIAL_CTRL->Get__MATERIAL_DB_SIZE() < 1)
		{
			if(idle_flag < 0)
			{
				if(xSCH_MATERIAL_CTRL->Check__SYSTEM_ABORT() > 0)
				{
					AUTO_CTRL__PMx_ABORT(p_variable);
				}
				else if(xSCH_MATERIAL_CTRL->Check__SYSTEM_STOP() > 0)
				{

				}
				else
				{
					try
					{
						AUTO_CTRL__LBo_PUMP(p_variable);
					}
					catch(int err_flag)
					{

					}
				}
			}

			Sleep(100);
			idle_flag = 1;
		}

		Sleep(1);

		if(idle_flag > 0)
		{
			idle_flag = -1;
		}

	}
}

void CObj__DUAL_ARM_STD::AUTO_CTRL__PMx_ABORT(CII_OBJECT__VARIABLE *p_variable)
{

	for(int i=0; i<iPMx_SIZE; i++)
	{
		if(xEXT_CH__CFG__PMx_USE[i]->Check__DATA("ENABLE") < 0)
		{
			continue;
		}
		if(xCH__PMx__OBJ_CTRL[i]->Check__DATA("ABORTED") > 0)
		{
			continue;
		}

		xCH__PMx__OBJ_CTRL[i]->Set__DATA("ABORT");
	}
}
void CObj__DUAL_ARM_STD::AUTO_CTRL__PMx_PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	CString log_id = "AUTO_CTRL__PMx_PUMP()";

	for(int i=0; i<iPMx_SIZE; i++)
	{
		if(PMx__Is_Available(i) < 0)
		{
			continue;
		}

		if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
		{
			if(PMx__Is_VAC(i) < 0)
			{
				Run__PMx_OBJ(i, CMMD__PUMP);
			}
		}
		else
		{
			if(PMx__Is_ATM(i) < 0)
			{
				Run__PMx_OBJ(i, CMMD__VENT);
			}
		}
	}
}
void CObj__DUAL_ARM_STD::AUTO_CTRL__TMC_PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	if(TMC_CHM__Is_Available() > 0)
	{
		if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("VAC") > 0)
		{
			if(TMC_CHM__Is_VAC() < 0)
			{
				Run__TMC_OBJ(CMMD__PUMP);
			}
		}
		else
		{
			if(TMC_CHM__Is_ATM() < 0)
			{
				Run__TMC_OBJ(CMMD__VENT);
			}
		}
	}
}
void CObj__DUAL_ARM_STD::AUTO_CTRL__LBo_PUMP(CII_OBJECT__VARIABLE *p_variable)
{
	if(xEXT_CH__CFG__TRANSFER_MODE->Check__DATA("ATM") > 0)
	{
		return;
	}

	// ...
	int ll_limit = iLLx_LIMIT;
	int ll_i;

	for(ll_i=0; ll_i<ll_limit; ll_i++)
	{
		if(xEXT_CH__SCH_DB_LLx_MODE_TYPE[ll_i]->Check__DATA(LBx_MODE__ONLY_OUTPUT) > 0)
		{
			if((LLx__Is_Available(ll_i)    > 0)
			&& (LLx__Check_All_Empty(ll_i) > 0))
			{
				SCH__LLx_PUMP(ll_i, p_variable);
			}
		}
	}
}

int  CObj__DUAL_ARM_STD::_Get__MIN_PMx_INDEX_OF_PMx_IN_COUNT(const CStringArray& l__pm_name)
{
	CUIntArray l__pm_index;

	int k_limit = l__pm_name.GetSize();
	int k;

	for(k=0; k<k_limit; k++)
	{
		int pm_index = Macro__Get_PMC_INDEX(l__pm_name[k]);
		l__pm_index.Add(pm_index);
	}

	return _Get__MIN_PMx_INDEX_OF_PMx_IN_COUNT(l__pm_index);
}
int  CObj__DUAL_ARM_STD::_Get__MIN_PMx_INDEX_OF_PMx_IN_COUNT(const CUIntArray& l__pm_index)
{
	int cur__pm_index = -1;
	int min__pm_count = -1;

	int k_limit = l__pm_index.GetSize();
	int k;

	for(k=0; k<k_limit; k++)
	{
		int pm_index = l__pm_index[k];

		CString ch_data = xCH__PMx__IN_COUNT[pm_index]->Get__STRING();
		int cur__pm_count = atoi(ch_data);

		if((min__pm_count < 0)
		|| (cur__pm_count < min__pm_count))
		{
			min__pm_count = cur__pm_count;
			cur__pm_index = pm_index;  
		}
	}

	return cur__pm_index;
}
