#include "StdAfx.h"
#include "CObj__PSK.h"
#include "CObj__PSK__DEF.h"
#include "CObj__PSK__ALID.h"

#include "Macro_Function.h"


// ...
int  CObj__PSK
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ROBOT.CTRL ...
	{
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__INIT);

		int r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	// ALIGNER.CTRL ...
	{
		doCH__AL_COMMAND->Set__DATA(_AL_MODE__INIT);

		int r_flag = _Wait__AL_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -21;
	}

	return 1;
}

int  CObj__PSK
::Call__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ROBOT.CTRL ...
	{
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__INIT);

		int r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	// ALIGNER.CTRL ...
	{
		doCH__AL_COMMAND->Set__DATA(_AL_MODE__INIT);

		int r_flag = _Wait__AL_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -21;
	}

	return 1;
}

// ...
int  CObj__PSK
::Call__VAC_ON(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm,
			   const CString& arm_type)
{
	int r_flag;

	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// VAC.ON ...
	{
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		//
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__CHUCK_ON);

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	return 1;
}
int  CObj__PSK
::Call__VAC_OFF(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm,
				const CString& arm_type)
{
	int r_flag;

	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// VAC.OFF ...
	{
		dCH__PARA_RB_ARM_TYPE->Set__DATA(arm_type);

		//
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__CHUCK_OFF);

		r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	return 1;
}

int  CObj__PSK
::Call__MAP(CII_OBJECT__VARIABLE* p_variable,
			CII_OBJECT__ALARM* p_alarm)
{
	int r_flag = Call__VAC_ON(p_variable,p_alarm, ARM_AB);
	if(r_flag < 0)			return -11;

	//
	CString ch_data = siCH__RB_STATE_MANUAL->Get__STRING();

	if(sCH__MON_A_ARM_GRIPPER_STATE->Check__DATA("Wafer") > 0)			dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__EXIST);
	else																dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Set__DATA(STR__NONE);

	if(sCH__MON_B_ARM_GRIPPER_STATE->Check__DATA("Wafer") > 0)			dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__EXIST);
	else																dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Set__DATA(STR__NONE);

	//
	if(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)
	{
		Call__VAC_OFF(p_variable,p_alarm, ARM_A);
	}
	if(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Check__DATA(STR__NONE) > 0)
	{
		Call__VAC_OFF(p_variable,p_alarm, ARM_B);
	}

	return 1;
}


// ...
int  CObj__PSK::_Wait__RB_ACTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = siCH__RB_STATE_MANUAL->Get__STRING();

	while(1)
	{
		Sleep(50);

		if(p_variable->Check__CTRL_ABORT() > 0)			return -11;

		if(iActive__SIM_MODE > 0)
		{
			sCH__MON_COMMAND_RUN->Set__DATA(STR__OFF);
			sCH__MON_RB_TASK_STATE->Set__DATA(STR__OFF);
		}

		// ...
		{
			ch_data = sCH__MON_COMMAND_RUN->Get__STRING();
			if(ch_data.CompareNoCase(STR__OFF) != 0)		continue;

			ch_data = sCH__MON_RB_TASK_STATE->Get__STRING();
			if(ch_data.CompareNoCase(STR__OFF) != 0)		continue;
		}
		break;
	}
	return 1;
}
int  CObj__PSK::_Wait__AL_ACTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = siCH__RB_STATE_MANUAL->Get__STRING();

	while(1)
	{
		Sleep(50);

		if(p_variable->Check__CTRL_ABORT() > 0)			return -11;

		if(iActive__SIM_MODE > 0)
		{
			sCH__MON_COMMAND_RUN->Set__DATA(STR__OFF);

			sCH__MON_AL_TASK_STATE->Set__DATA(STR__OFF);
		}

		// ...
		{
			ch_data = sCH__MON_COMMAND_RUN->Get__STRING();
			if(ch_data.CompareNoCase(STR__OFF) != 0)		continue;

			ch_data = sCH__MON_AL_TASK_STATE->Get__STRING();
			if(ch_data.CompareNoCase(STR__OFF) != 0)		continue;
		}
		break;
	}
	return 1;
}

// ...
int  CObj__PSK::Is__ONLINE(CII_OBJECT__ALARM* p_alarm)
{
LOOP_RETRY:

	if(diCH__COMM_STS->Check__DATA(STR__OFFLINE) > 0)
	{
		int alarm_id = ALID__OFFLINE_ALARM;
		CString r_act;

		p_alarm->Popup__ALARM(alarm_id,r_act);

		if(r_act.CompareNoCase("RETRY") == 0)
		{
			goto LOOP_RETRY;
		}
		return -1;
	}

	return 1;
}

int  CObj__PSK::Get__CFG_STN_NUM(const CString& stn_name,const CString& stn_slot, CString& stn_id)
{
	CString cfg_stn_num;

		 if(stn_name.CompareNoCase(STR__AL1) == 0)		    aCH__CFG__AL1_STN_NUM->Get__DATA(cfg_stn_num);

	else if(stn_name.CompareNoCase(STR__LBA) == 0)
	{	
			 if(stn_slot.CompareNoCase("1") == 0)			aCH__CFG__LL1_1_STN_NUM->Get__DATA(cfg_stn_num);
		else if(stn_slot.CompareNoCase("2") == 0)			aCH__CFG__LL1_2_STN_NUM->Get__DATA(cfg_stn_num);
	}
	else if(stn_name.CompareNoCase(STR__LBB) == 0)
	{
			 if(stn_slot.CompareNoCase("1") == 0)			aCH__CFG__LL2_1_STN_NUM->Get__DATA(cfg_stn_num);
		else if(stn_slot.CompareNoCase("2") == 0)			aCH__CFG__LL2_2_STN_NUM->Get__DATA(cfg_stn_num);
	}

	else if(stn_name.CompareNoCase(STR__BUFF1) == 0)	    aCH__CFG__ST1_STN_NUM->Get__DATA(cfg_stn_num);

	else if(stn_name.CompareNoCase(STR__LP1) == 0)		    aCH__CFG__LPx_STN_NUM[INT__LP1]->Get__DATA(cfg_stn_num);
	else if(stn_name.CompareNoCase(STR__LP2) == 0)		    aCH__CFG__LPx_STN_NUM[INT__LP2]->Get__DATA(cfg_stn_num);
	else if(stn_name.CompareNoCase(STR__LP3) == 0)		    aCH__CFG__LPx_STN_NUM[INT__LP3]->Get__DATA(cfg_stn_num);
	else if(stn_name.CompareNoCase(STR__LP4) == 0)		    aCH__CFG__LPx_STN_NUM[INT__LP4]->Get__DATA(cfg_stn_num);
	else if(stn_name.CompareNoCase(STR__LP5) == 0)		    aCH__CFG__LPx_STN_NUM[INT__LP5]->Get__DATA(cfg_stn_num);	
	else													return -1;

	stn_id = cfg_stn_num;
	return 1;
}
