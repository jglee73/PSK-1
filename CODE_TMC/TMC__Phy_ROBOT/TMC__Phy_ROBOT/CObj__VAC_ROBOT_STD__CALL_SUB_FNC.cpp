#include "StdAfx.h"
#include "CObj__VAC_ROBOT_STD.h"
#include "CObj__VAC_ROBOT_STD__DEF.h"
#include "CObj__VAC_ROBOT_STD__ALID.h"

#include "math.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
void  CObj__VAC_ROBOT_STD::
Fnc__APP_LOG(const CString& log_msg)
{
	if(iFlag__APP_LOG < 1)		return;

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

// ...
void  CObj__VAC_ROBOT_STD::
Set_ANI__ROBOT_ARM_EXTEND(const CString& arm_type, const CString& stn_name)
{
	// ...
	{
		int pm_index = Macro__CHECK_PMx_INDEX(stn_name);

		if((pm_index >= 0)&&(pm_index < m_nPM_LIMIT))
		{
			dCH__OTR_OUT_MON__PMx_ARM_STATE[pm_index]->Set__DATA(STR__EXTEND);
		}
	}

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		dCH__OTR_OUT_MON__ARM_A_ACT->Set__DATA(STR__EXTEND);
		return;
	}
	if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		dCH__OTR_OUT_MON__ARM_B_ACT->Set__DATA(STR__EXTEND);
		return;
	}
}
void  CObj__VAC_ROBOT_STD::
Set_ANI__ROBOT_EXTEND(const CString& arm_type,
					  const CString& stn_name,
					  const CString& stn_slot)
{
	dCH__OTR_OUT_MON__ACT_ARM->Set__DATA(arm_type);

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		dCH__OTR_OUT_MON__ARM_A_ACT->Set__DATA(STR__EXTEND);

		int pm_index = Macro__CHECK_PMx_INDEX(stn_name);
		if((pm_index >= 0)&&(pm_index < m_nPM_LIMIT))
		{
			dCH__OTR_OUT_MON__PMx_ARM_STATE[pm_index]->Set__DATA(STR__EXTEND);
			dCH__OTR_OUT_MON__PMx_ARM_A_ACT[pm_index]->Set__DATA(STR__EXTEND);
		}

		int ll_index = Macro__CHECK_LLx_INDEX(stn_name);
		if(ll_index >= 0)
		{
			dCH__OTR_OUT_MON__LBx_ARM_A_ACT[ll_index]->Set__DATA(STR__EXTEND);
		}
		return;
	}
	if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		dCH__OTR_OUT_MON__ARM_B_ACT->Set__DATA(STR__EXTEND);

		int pm_index = Macro__CHECK_PMx_INDEX(stn_name);
		if((pm_index >= 0)&&(pm_index < m_nPM_LIMIT))
		{
			dCH__OTR_OUT_MON__PMx_ARM_STATE[pm_index]->Set__DATA(STR__EXTEND);
			dCH__OTR_OUT_MON__PMx_ARM_B_ACT[pm_index]->Set__DATA(STR__EXTEND);
		}

		int ll_index = Macro__CHECK_LLx_INDEX(stn_name);
		if(ll_index >= 0)
		{
			dCH__OTR_OUT_MON__LBx_ARM_B_ACT[ll_index]->Set__DATA(STR__EXTEND);
		}
		return;
	}
}

void  CObj__VAC_ROBOT_STD::
Set_ANI__ROBOT_ALL_RETRACT()
{
	dCH__OTR_OUT_MON__ARM_A_ACT->Set__DATA(STR__RETRACT);
	dCH__OTR_OUT_MON__ARM_B_ACT->Set__DATA(STR__RETRACT);

	for(int i=0; i<m_nPM_LIMIT; i++)
	{
		dCH__OTR_OUT_MON__PMx_ARM_STATE[i]->Set__DATA(STR__RETRACT);
		dCH__OTR_OUT_MON__PMx_ARM_A_ACT[i]->Set__DATA(STR__RETRACT);
		dCH__OTR_OUT_MON__PMx_ARM_B_ACT[i]->Set__DATA(STR__RETRACT);
	}
}
void  CObj__VAC_ROBOT_STD::
Set_ANI__ROBOT_ARM_RETRACT(const CString& arm_type, const CString& stn_name)
{
	// ...
	{
		int pm_index = Macro__CHECK_PMx_INDEX(stn_name);
		if((pm_index >= 0)&&(pm_index < m_nPM_LIMIT))
		{
			dCH__OTR_OUT_MON__PMx_ARM_STATE[pm_index]->Set__DATA(STR__RETRACT);
		}
	}

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		dCH__OTR_OUT_MON__ARM_A_ACT->Set__DATA(STR__RETRACT);
		return;
	}
	if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		dCH__OTR_OUT_MON__ARM_B_ACT->Set__DATA(STR__RETRACT);
		return;
	}
}
void  CObj__VAC_ROBOT_STD::
Set_ANI__ROBOT_RETRACT(const CString& arm_type,
					   const CString& stn_name,
					   const CString& stn_slot)
{
	int pm_index;

	dCH__OTR_OUT_MON__ACT_ARM->Set__DATA(arm_type);

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		dCH__OTR_OUT_MON__ARM_A_ACT->Set__DATA(STR__RETRACT);

		pm_index = Macro__CHECK_PMx_INDEX(stn_name);
		if((pm_index >= 0)&&(pm_index < m_nPM_LIMIT))
		{
			dCH__OTR_OUT_MON__PMx_ARM_STATE[pm_index]->Set__DATA(STR__RETRACT);
			dCH__OTR_OUT_MON__PMx_ARM_A_ACT[pm_index]->Set__DATA(STR__RETRACT);
		}

		int ll_index = Macro__CHECK_LLx_INDEX(stn_name);
		if(ll_index >= 0)
		{
			dCH__OTR_OUT_MON__LBx_ARM_A_ACT[ll_index]->Set__DATA(STR__RETRACT);
		}
		return;
	}
	if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		dCH__OTR_OUT_MON__ARM_B_ACT->Set__DATA(STR__RETRACT);

		pm_index = Macro__CHECK_PMx_INDEX(stn_name);
		if((pm_index >= 0)&&(pm_index < m_nPM_LIMIT))
		{
			dCH__OTR_OUT_MON__PMx_ARM_STATE[pm_index]->Set__DATA(STR__RETRACT);
			dCH__OTR_OUT_MON__PMx_ARM_B_ACT[pm_index]->Set__DATA(STR__RETRACT);
		}

		int ll_index = Macro__CHECK_LLx_INDEX(stn_name);
		if(ll_index >= 0)
		{
			dCH__OTR_OUT_MON__LBx_ARM_B_ACT[ll_index]->Set__DATA(STR__RETRACT);
		}
		return;
	}
}

void  CObj__VAC_ROBOT_STD::
Set_ANI__ROBOT_ROTATE(const CString& arm_type,
					  const CString& stn_name)
{
	dCH__OTR_OUT_MON__ACT_ARM->Set__DATA(arm_type);

	dCH__OTR_OUT_MON__ARM_A_ACT->Set__DATA(STR__RETRACT);
	dCH__OTR_OUT_MON__ARM_B_ACT->Set__DATA(STR__RETRACT);

	dCH__OTR_OUT_MON__TRG_MOVE->Set__DATA(stn_name);
	dCH__OTR_OUT_MON__TRG_ROTATE->Set__DATA(stn_name);
}


int  CObj__VAC_ROBOT_STD
::Check__STN_EXIST(CII_OBJECT__ALARM* p_alarm,const CString& stn_name)
{
	CString module_name;
	int i;

LOOP_CHECK:

	// LLx ...
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	if(ll_i >= 0)
	{
		if(dEXT_CH__CFG_LLx_EXIST_FLAG[ll_i]->Check__DATA(STR__YES) > 0)
		{
			return 1;
		}

		// ...
		{
			int alarm_id = ALID__STN__NOT_EXIST_ERROR + ll_i;
			CString alarm_msg;
			CString r_act;

			alarm_msg.Format("The exist flag of (%s) STN is not \"YES\", in config page.\n",stn_name);
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

			if(r_act == ACT__RETRY)			goto LOOP_CHECK;
		}
		return -1;
	}

	// PMx -----
	for(i=0;i<m_nPM_LIMIT;i++)
	{
		module_name.Format("PM%1d",i+1);
		if(module_name.CompareNoCase(stn_name) != 0)
		{
			continue;
		}

		if(dEXT_CH__CFG_PMx_EXIST_FLAG[i]->Check__DATA(STR__YES) > 0)
		{
			return 1;
		}

		//.....
		{
			int alarm_id = ALID__STN__NOT_EXIST_ERROR;
			CString alarm_msg;
			CString r_act;

			alarm_msg.Format("The exist flag of (%s) STN is not \"YES\", in config page.\n",stn_name);
			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,alarm_msg,r_act);

			if(r_act == ACT__RETRY)			goto LOOP_CHECK;
		}
		return -1;
	}

	return 1;
}
