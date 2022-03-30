#include "StdAfx.h"
#include "CObj__VAC_ROBOT_SERIAL.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"
#include "CObj__VAC_ROBOT_SERIAL__ALID.h"

#include "Macro_Function.h"


// ...
int  CObj__VAC_ROBOT_SERIAL
::Call__RETRACT(CII_OBJECT__VARIABLE* p_variable,
		        CII_OBJECT__ALARM* p_alarm,
				const CString& arm_type,
				const CString& stn_name,
				const CString& stn_slot)
{
	int r_flag;

	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ROBOT.RETRACT ...
	{
		CString str_pos;

		//
		r_flag = Get__CFG_STN_NUM(stn_name,stn_slot, str_pos);
		if(r_flag < 0)			return -11;

		aCH__PARA_RB_POS_CODE->Set__DATA(str_pos);
		aCH__PARA_RB_SLOT_CODE->Set__DATA(stn_slot);
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		//
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__RETRACT);

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -12;
	}

	// CHECK.POS_STN ...
	{
		int r_flag = _Check__POS_STN(p_variable, p_alarm, arm_type,stn_name,stn_slot, false);
		if(r_flag < 0)			return r_flag;
	}

	return 1;
}
int  CObj__VAC_ROBOT_SERIAL
::Call__EXTEND(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& arm_type,
			   const CString& stn_name,
			   const CString& stn_slot)
{
	int r_flag;

	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ...
	bool active__wafer_check = true;

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		if(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		active__wafer_check = false;
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		if(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		active__wafer_check = false;
	}

	// ROBOT.RETRACT ...
	{
		CString str_pos;

		//
		r_flag = Get__CFG_STN_NUM(stn_name,stn_slot, str_pos);
		if(r_flag < 0)			return -11;

		aCH__PARA_RB_POS_CODE->Set__DATA(str_pos);
		aCH__PARA_RB_SLOT_CODE->Set__DATA(stn_slot);
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		// ...
		{
			CString cmmd__set_load;

			if(active__wafer_check)			cmmd__set_load = _RB_MODE__LOAD_ON;
			else							cmmd__set_load = _RB_MODE__LOAD_OFF;

			doCH__RB_COMMAND->Set__DATA(cmmd__set_load);
		}

		// ...
		{
			CString cmmd__rb_act;

			if(dCH__CFG_DA_USE->Check__DATA(STR__YES) > 0)			cmmd__rb_act = _RB_MODE__EXTEND_OFFSET;
			else													cmmd__rb_act = _RB_MODE__EXTEND;

			doCH__RB_COMMAND->Set__DATA(cmmd__rb_act);
		}

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -12;
	}

	// CHECK.POS_STN ...
	{
		int r_flag = _Check__POS_STN(p_variable, p_alarm, arm_type,stn_name,stn_slot, true);
		if(r_flag < 0)			return r_flag;
	}

	// CHECK.DA_ERROR ...
	if(active__wafer_check)
	{
		if(_Check__DA_ERROR(p_variable,p_alarm, arm_type,stn_name,stn_slot) < 0)
		{
			return -101;
		}
	}

	return 1;
}

