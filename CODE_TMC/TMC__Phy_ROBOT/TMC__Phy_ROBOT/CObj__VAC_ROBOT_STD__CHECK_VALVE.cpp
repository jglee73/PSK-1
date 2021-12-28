#include "StdAfx.h"
#include "CObj__VAC_ROBOT_STD.h"
#include "CObj__VAC_ROBOT_STD__DEF.h"
#include "CObj__VAC_ROBOT_STD__ALID.h"

#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int  CObj__VAC_ROBOT_STD::
Interlock__CHECK_VALVE_OPEN(CII_OBJECT__ALARM* p_alarm,
							const CString& stn_name,
							const CString& stn_slot,
							const CString& act_name)
{
LOOP__RETRY:

	// ...
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

	if(ll_i >= 0)
	{
		CII__VAR_DIGITAL_CTRL *p_lb_door;

		if(bActive__LLx_MULTI_SLOT_VALVE)
		{
			int p_index = atoi(stn_slot) - 1;
			if(p_index <  0)						return -11;
			if(p_index >= iLLx_SLOT_SIZE)			return -12;

			p_lb_door = dEXT_CH__LLx_SLIT_VALVE_STATUS_XX[ll_i][p_index].Get__PTR();
		}
		else
		{
			p_lb_door = dEXT_CH__LLx_SLIT_VALVE_STATUS_A[ll_i].Get__PTR();
		}

		if(p_lb_door->When__DATA(STR__OPEN, 2.0) == 0)
		{
			return -11;
		}

		if(p_lb_door->Check__DATA(STR__OPEN) < 0)
		{
			int alarm_id = ALID__LLx__NOT_VALVE_OPEN;
			CString err_msg;
			CString err_bff;
			CString r_act;

			err_msg.Format("Robot can not %s.\n", act_name);

			err_bff.Format("Please, check %s ! \n", stn_name);
			err_msg += err_bff;

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, err_msg, r_act);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				goto LOOP__RETRY;
			}
			return -12;
		}
		return 1;
	}

	// ...
	int pm_index = Macro__CHECK_PMx_INDEX(stn_name);

	if((pm_index >= 0)
	&& (pm_index <  m_nPM_LIMIT))
	{
		if(dEXT_CH__CFG_PMx_SV_USE[pm_index]->Check__DATA("NO") > 0)
		{
			return 1;
		}

		if(dEXT_CH__PMx_SLIT_VALVE_STATUS[pm_index]->When__DATA(STR__OPEN, 2.0) == 0)
		{
			return OBJ_ABORT;
		}

		if(dEXT_CH__PMx_SLIT_VALVE_STATUS[pm_index]->Check__DATA(STR__OPEN) < 0)
		{
			int alarm_id = ALID__PMx__NOT_VALVE_OPEN;
			CString err_msg;
			CString r_act;

			err_msg.Format("Robot can not %s.\n",act_name);

			p_alarm->Popup__ALARM_With_MESSAGE(alarm_id,err_msg,r_act);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				goto LOOP__RETRY;
			}
			return -1;			
		}
	}

	return 1;
}
