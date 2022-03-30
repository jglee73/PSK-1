#include "StdAfx.h"
#include "CObj__VAC_ROBOT_SERIAL.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"
#include "CObj__VAC_ROBOT_SERIAL__ALID.h"

#include "Macro_Function.h"


// ...
int  CObj__VAC_ROBOT_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// SET.COMM ...
	{
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__SET_COMM);
	}
	// VERSION ...
	{
		siCH__VERSION_MANUAL->Get__STRING();
	}

	// ROBOT.CTRL ...
	{
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__HOME);

		int r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	return 1;
}

int  CObj__VAC_ROBOT_SERIAL
::Call__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	// ROBOT.CTRL ...
	{
		doCH__RB_COMMAND->Set__DATA(_RB_MODE__HOME);

		int r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	return 1;
}

// ...
int  CObj__VAC_ROBOT_SERIAL::_Wait__RB_ACTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = siCH__RB_STATE_MANUAL->Get__STRING();

	while(1)
	{
		Sleep(50);

		if(p_variable->Check__CTRL_ABORT() > 0)			return -11;

		if(iActive__SIM_MODE > 0)
		{
			sCH__MON_RB_STATE->Set__DATA(STR__IDLE);
		}

		// ...
		{
			ch_data = sCH__MON_RB_STATE->Get__STRING();
			if(ch_data.CompareNoCase(STR__IDLE) != 0)		continue;
		}
		break;
	}
	return 1;
}

//
int  CObj__VAC_ROBOT_SERIAL::
_Check__POS_STN(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm,
				 const CString& arm_type,
				 const CString& stn_name,
				 const CString& stn_slot,
				 const bool active__arm_extend)
{
	int check_ref   = 3;
	int check_count = 0;

	while(check_count < check_ref)
	{
		check_count++;

		CString ch_data = siCH__RQ_POS_STN_MANUAL->Get__STRING();

		if(iActive__SIM_MODE > 0)
		{
			CString cur__r_info;
			CString cur__stn_info;

			if(active__arm_extend)		cur__r_info = "EX";
			else						cur__r_info = "RE";

			cur__stn_info = aCH__PARA_RB_POS_CODE->Get__STRING();

			if(arm_type.CompareNoCase(ARM_A) == 0)		
			{
				sCH__MON_POS_STN__R_INFO__ARM_A->Set__DATA(cur__r_info);
				sCH__MON_POS_STN__STATION_INFO__ARM_A->Set__DATA(cur__stn_info);
			}
			else if(arm_type.CompareNoCase(ARM_B) == 0)		
			{
				sCH__MON_POS_STN__R_INFO__ARM_B->Set__DATA(cur__r_info);
				sCH__MON_POS_STN__STATION_INFO__ARM_B->Set__DATA(cur__stn_info);
			}

			//
			ch_data = STR__OK;
		}

		if(ch_data.CompareNoCase(STR__OK) == 0)
		{
			CString cur__r_info;
			CString cur__z_info;
			CString cur__t_info;
			CString cur__stn_info;
			CString cur__slot_info;

			if(arm_type.CompareNoCase(ARM_A) == 0)
			{
				cur__r_info = sCH__MON_POS_STN__R_INFO__ARM_A->Get__STRING();
				cur__z_info = sCH__MON_POS_STN__Z_INFO__ARM_A->Get__STRING();
				cur__t_info = sCH__MON_POS_STN__T_INFO__ARM_A->Get__STRING();

				cur__stn_info  = sCH__MON_POS_STN__STATION_INFO__ARM_A->Get__STRING();
				cur__slot_info = sCH__MON_POS_STN__SLOT_INFO__ARM_A->Get__STRING();
			}
			else if(arm_type.CompareNoCase(ARM_B) == 0)
			{
				cur__r_info = sCH__MON_POS_STN__R_INFO__ARM_B->Get__STRING();
				cur__z_info = sCH__MON_POS_STN__Z_INFO__ARM_B->Get__STRING();
				cur__t_info = sCH__MON_POS_STN__T_INFO__ARM_B->Get__STRING();

				cur__stn_info  = sCH__MON_POS_STN__STATION_INFO__ARM_B->Get__STRING();
				cur__slot_info = sCH__MON_POS_STN__SLOT_INFO__ARM_B->Get__STRING();
			}

			// ...
			CString cur__stn_name;
			CString cur__stn_slot;

			int para__stn_id = atoi(cur__stn_info);

			if(Get__CFG_STN_NAME(para__stn_id, cur__stn_name,cur__stn_slot) < 0)
			{
				// Error 

				return -101;
			}

			if(cur__stn_name.CompareNoCase(stn_name) != 0)
			{
				// Error 

				return -102;
			}

			if(active__arm_extend)
			{
				if(cur__r_info.CompareNoCase("EX") != 0)
				{
					// Error

					return -103;
				}
			}
			else
			{
				if(cur__r_info.CompareNoCase("RE") != 0)
				{
					// Error

					return -104;
				}
			}

			// OK
			return 1;
		}

		Sleep(100);
	}

	// Error ...
	{

	}
	return -1;
}
int  CObj__VAC_ROBOT_SERIAL::
_Check__WAF_CEN(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm,
				const CString& arm_type,
				const CString& stn_name,
				const CString& stn_slot)
{
	if(dCH__CFG_DA_USE->Check__DATA(STR__NO) > 0)
	{
		CString ch_data = "0000";

		if(arm_type.CompareNoCase(ARM_A) == 0)
		{
			sCH__MON_WFR_CEN_RO__ARM_A->Set__DATA(ch_data);
			sCH__MON_WFR_CEN_TO__ARM_A->Set__DATA(ch_data);
		}
		else if(arm_type.CompareNoCase(ARM_B) == 0)
		{
			sCH__MON_WFR_CEN_RO__ARM_B->Set__DATA(ch_data);
			sCH__MON_WFR_CEN_TO__ARM_B->Set__DATA(ch_data);
		}
		return 1;
	}

	// ...
	int check_ref   = 3;
	int check_count = 0;

	while(check_count < check_ref)
	{
		check_count++;

		CString ch_data = siCH__WAF_CEN_DATA_MANUAL->Get__STRING();
		
		if(iActive__SIM_MODE > 0)
		{
			double value_ro = (double) rand() / RAND_MAX;
			double value_to = (double) rand() / RAND_MAX;

			CString str_ro;
			CString str_to;

			str_ro.Format("%.0f", value_ro * 1000);
			str_to.Format("%.0f", value_to * 1000);

			sCH__MON_WFR_CEN__CEN_RO->Set__DATA(str_ro);
			sCH__MON_WFR_CEN__CEN_TO->Set__DATA(str_to);

			//
			ch_data = STR__OK;
		}

		if(ch_data.CompareNoCase(STR__OK) == 0)
		{
			CString str_ro;
			CString str_to;

			ch_data = sCH__MON_WFR_CEN__CEN_RO->Get__STRING();
			double value__r_mm = atof(ch_data) * 0.001;

			ch_data = sCH__MON_WFR_CEN__CEN_TO->Get__STRING();
			double value__t_deg = atof(ch_data) * 0.001;

			str_ro.Format("%.3f", value__r_mm);
			str_to.Format("%.3f", value__t_deg);

			if(arm_type.CompareNoCase(ARM_A) == 0)
			{
				sCH__MON_WFR_CEN_RO__ARM_A->Set__DATA(str_ro);
				sCH__MON_WFR_CEN_TO__ARM_A->Set__DATA(str_to);
			}
			else if(arm_type.CompareNoCase(ARM_B) == 0)
			{
				sCH__MON_WFR_CEN_RO__ARM_B->Set__DATA(str_ro);
				sCH__MON_WFR_CEN_TO__ARM_B->Set__DATA(str_to);
			}
			return 1;
		}
	}

	// Error ...
	{
		/*
		sCH__MON_WFR_CEN__CEN_RO;
		sCH__MON_WFR_CEN__CEN_TO;
		*/
	}
	return -1;
}

int  CObj__VAC_ROBOT_SERIAL::
_Check__DA_ERROR(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm,
				 const CString& arm_type,
				 const CString& stn_name,
				 const CString& stn_slot)
{
	if(dCH__CFG_DA_USE->Check__DATA(STR__YES) < 0)
	{
		sCH__DA_RESULT_T_OFFSET_MM->Set__DATA("0.0");
		sCH__DA_RESULT_R_OFFSET_DEG->Set__DATA("0.0");
		return 1;
	}

	// ...
	double cur__arm_r = 0.0;
	double cur__arm_t = 0.0;

	CString ch_data;

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		ch_data = sCH__MON_WFR_CEN_RO__ARM_A->Get__STRING();
		cur__arm_r = atof(ch_data);

		ch_data = sCH__MON_WFR_CEN_TO__ARM_A->Get__STRING();
		cur__arm_t = atof(ch_data);
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		ch_data = sCH__MON_WFR_CEN_RO__ARM_B->Get__STRING();
		cur__arm_r = atof(ch_data);

		ch_data = sCH__MON_WFR_CEN_TO__ARM_B->Get__STRING();
		cur__arm_t = atof(ch_data);
	}

	// ...
	int pm_index = Macro__CHECK_PMx_INDEX(stn_name);
	if(pm_index >= 0)
	{
		double cfg__warn_r  = aCH__CFG_R_OFFSET_WARNING_ERROR[pm_index]->Get__VALUE();
		double cfg__abort_r = aCH__CFG_R_OFFSET_ABORT_ERROR[pm_index]->Get__VALUE();

		double cfg__warn_t  = aCH__CFG_T_OFFSET_WARNING_ERROR[pm_index]->Get__VALUE();
		double cfg__abort_t = aCH__CFG_T_OFFSET_ABORT_ERROR[pm_index]->Get__VALUE();

		double abs__arm_r = fabs(cur__arm_r);
		double abs__arm_t = fabs(cur__arm_t);

		if((abs__arm_r > cfg__abort_r) || (abs__arm_t > cfg__abort_t))
		{
			int alm_id = ALID__WFR_CEN_OFFSET__ABORT_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			// ...
			{
				alm_bff.Format("After Picking & Before Placing, Wafer-center offset was misplaced in R or T. \n\n");
				alm_msg += alm_bff;

				alm_bff.Format("*** First of all, Must check wafer position or broken. \n");
				alm_msg += alm_bff;

				alm_bff.Format("[ABORT]: Robot will be down and maint mode..\n\n");
				alm_msg += alm_bff;

				alm_bff.Format("[DIRECTION]\n");
				alm_msg += alm_bff;
				alm_bff.Format("1. If Job Running, calibrate wafer position.\n");
				alm_msg += alm_bff;
				alm_bff.Format("2. You must check wafer position and broken or not. \n");
				alm_msg += alm_bff;
				alm_bff.Format("3. Push the robot \"INIT\" button in a TMC \"Operate Page\". \n");
				alm_msg += alm_bff;
				alm_bff.Format("4. Then Job will resume.\n");
				alm_msg += alm_bff;
				alm_bff.Format("5. Robot will not dynamic align but just place in a fixed position.\n");
				alm_msg += alm_bff;
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm_msg, r_act);		

			if(r_act.CompareNoCase(ACT__ABORT) == 0)
			{
				return -1;
			}
		}

		if((abs__arm_r > cfg__warn_r) || (abs__arm_t > cfg__warn_t))
		{
			int alm_id = ALID__WFR_CEN_OFFSET__WARNING_ERROR;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("Config warning R is %.1f mm \n", cfg__warn_r);
			alm_msg += alm_bff;
			alm_bff.Format("Current R offset is %.3f mm \n", cur__arm_r);
			alm_msg += alm_bff;

			alm_bff.Format("Config warning T is %.1f deg \n", cfg__warn_t);
			alm_msg += alm_bff;
			alm_bff.Format("Current T offset is %.3f deg \n", cur__arm_t);
			alm_msg += alm_bff;

			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
		}
	}

	// ...
	{
		ch_data.Format("%.3f", cur__arm_r);
		sCH__DA_RESULT_T_OFFSET_MM->Set__DATA(ch_data);

		ch_data.Format("%.3f", cur__arm_t);
		sCH__DA_RESULT_R_OFFSET_DEG->Set__DATA(ch_data);
	}
	return 1;
}


// ...
int  CObj__VAC_ROBOT_SERIAL::Is__ONLINE(CII_OBJECT__ALARM* p_alarm)
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

int  CObj__VAC_ROBOT_SERIAL::Get__CFG_STN_NUM(const CString& stn_name,const CString& stn_slot, CString& stn_id)
{
	CString cfg_stn_num = "??";

	if(stn_name.CompareNoCase(STR__LBA) == 0)
	{	
			 if(stn_slot.CompareNoCase("1") == 0)			aCH__CFG__LL1_1_STN_NUM->Get__DATA(cfg_stn_num);
		else if(stn_slot.CompareNoCase("2") == 0)			aCH__CFG__LL1_2_STN_NUM->Get__DATA(cfg_stn_num);
	}
	else if(stn_name.CompareNoCase(STR__LBB) == 0)
	{
			 if(stn_slot.CompareNoCase("1") == 0)			aCH__CFG__LL2_1_STN_NUM->Get__DATA(cfg_stn_num);
		else if(stn_slot.CompareNoCase("2") == 0)			aCH__CFG__LL2_2_STN_NUM->Get__DATA(cfg_stn_num);
	}
	else
	{
		int  pm_index = Macro__CHECK_PMx_INDEX(stn_name);
		if(pm_index >= 0)			aCH__CFG__PMx_STN_NUM[pm_index]->Get__DATA(cfg_stn_num);
	}

	stn_id = cfg_stn_num;
	return 1;
}
int  CObj__VAC_ROBOT_SERIAL::Get__CFG_STN_NAME(const int para__stn_id, CString& stn_name,CString& stn_slot)
{
	int cur__stn_id;

	// LL1.1 ...
	{
		cur__stn_id = (int) aCH__CFG__LL1_1_STN_NUM->Get__VALUE();
		if(cur__stn_id == para__stn_id)
		{
			stn_name = STR__LBA;
			stn_slot = "1";
			return 1;
		}
	}
	// LL1.2 ...
	{
		cur__stn_id = (int) aCH__CFG__LL1_2_STN_NUM->Get__VALUE();
		if(cur__stn_id == para__stn_id)
		{
			stn_name = STR__LBA;
			stn_slot = "2";
			return 1;
		}
	}

	// LL2.1 ...
	{
		cur__stn_id = (int) aCH__CFG__LL2_1_STN_NUM->Get__VALUE();
		if(cur__stn_id == para__stn_id)
		{
			stn_name = STR__LBB;
			stn_slot = "1";
			return 1;
		}
	}
	// LL2.2 ...
	{
		cur__stn_id = (int) aCH__CFG__LL2_2_STN_NUM->Get__VALUE();
		if(cur__stn_id == para__stn_id)
		{
			stn_name = STR__LBB;
			stn_slot = "2";
			return 1;
		}
	}

	for(int i=0; i<CFG_PMx__MD_SIZE; i++)
	{
		cur__stn_id = (int) aCH__CFG__PMx_STN_NUM[i]->Get__VALUE();
		if(cur__stn_id == para__stn_id)
		{
			stn_name.Format("PM%1d", i+1);
			stn_slot = "1";
			return 1;
		}
	}

	return -1;
}
