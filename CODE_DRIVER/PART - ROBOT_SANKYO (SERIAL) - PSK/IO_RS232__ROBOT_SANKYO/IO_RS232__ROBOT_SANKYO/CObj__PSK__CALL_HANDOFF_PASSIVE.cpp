#include "StdAfx.h"
#include "CObj__PSK.h"
#include "CObj__PSK__DEF.h"
#include "CObj__PSK__ALID.h"

#include "Macro_Function.h"


// ...
int  CObj__PSK
::Call__PICK(CII_OBJECT__VARIABLE* p_variable,
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

	// ROBOT.PICK ...
	{
		CString str_pos;

		//
		r_flag = Get__CFG_STN_NUM(stn_name,stn_slot, str_pos);
		if(r_flag < 0)			return -11;

		aCH__PARA_RB_POS_CODE->Set__DATA(str_pos);
		aCH__PARA_RB_SLOT_CODE->Set__DATA(stn_slot);
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		//
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__PICK);

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -12;
	}

	return 1;
}

int  CObj__PSK
::Call__ALIGN_PICK(CII_OBJECT__VARIABLE* p_variable, 
				   CII_OBJECT__ALARM* p_alarm,
				   const CString& arm_type,
				   const CString& stn_name,
				   const CString& stn_slot)
{
	int r_flag;

	r_flag = Call__ALIGN(p_variable, p_alarm);
	if(r_flag < 0)			return -11;

	r_flag = Call__PICK(p_variable,p_alarm, arm_type,stn_name,stn_slot);
	if(r_flag < 0)			return -12;

	return 1;
}

int  CObj__PSK
::Call__PLACE(CII_OBJECT__VARIABLE* p_variable,
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

	// ROBOT.PLACE ...
	{
		CString str_pos;

		//
		r_flag = Get__CFG_STN_NUM(stn_name,stn_slot, str_pos);
		if(r_flag < 0)			return -11;

		aCH__PARA_RB_POS_CODE->Set__DATA(str_pos);
		aCH__PARA_RB_SLOT_CODE->Set__DATA(stn_slot);
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		//
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__PLACE);

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -12;
	}

	return 1;
}

int  CObj__PSK
::Call__ROTATE(CII_OBJECT__VARIABLE* p_variable,
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

	// ROBOT.ROTATE ...
	{
		CString str_pos;

		//
		r_flag = Get__CFG_STN_NUM(stn_name,stn_slot, str_pos);
		if(r_flag < 0)			return -11;

		aCH__PARA_RB_POS_CODE->Set__DATA(str_pos);
		aCH__PARA_RB_SLOT_CODE->Set__DATA(stn_slot);
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		//
		CString rb_cmmd = "";

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			if(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		rb_cmmd = _RB_MODE__GOTO_GET;
			else																		rb_cmmd = _RB_MODE__GOTO_PUT;
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			if(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)		rb_cmmd = _RB_MODE__GOTO_GET;
			else																		rb_cmmd = _RB_MODE__GOTO_PUT;
		}

		if(rb_cmmd.GetLength() < 1)			return -10001;

		doCH__RB_COMMAND->Set__DATA(rb_cmmd);

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -12;
	}

	return 1;
}

