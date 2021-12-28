#include "StdAfx.h"
#include "CObj__VAC_ROBOT_STD.h"
#include "CObj__VAC_ROBOT_STD__DEF.h"
#include "CObj__VAC_ROBOT_STD__ALID.h"

#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int  CObj__VAC_ROBOT_STD
::_Report__DA_OFFSET(CII_OBJECT__ALARM* p_alarm,
					 const CString& arm_type,
					 const CString& stn_name,
					 const CString& stn_slot)
{
	CString cfg_use = _Get__CFG_DYNAMIC_ALGN_USE(stn_name);
	if(cfg_use.CompareNoCase(STR__YES) != 0)		return 1;

	// ...
	CString ch__r_off;
	CString ch__t_off;

	double cfg__soft_r = 0.0;
	double cfg__hard_r = 0.0;
	double cfg__soft_t = 0.0;
	double cfg__hard_t = 0.0;

	CII__VAR_STRING_CTRL *pch__result_offset;

	if(iSim_Flag > 0)
	{
		ch__r_off = "0.0";
		ch__t_off = "0.0";
	}
	else
	{
		ch__r_off = sEXT_CH__ROBOT_DA_RESULT_R_OFFSET_DEG->Get__STRING();
		ch__t_off = sEXT_CH__ROBOT_DA_RESULT_T_OFFSET_MM->Get__STRING();
	}

	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		sCH__MON_R_OFFSET_A_ARM__ROBOT->Set__DATA(ch__r_off);
		sCH__MON_T_OFFSET_A_ARM__ROBOT->Set__DATA(ch__t_off);

		if(ll_i >= 0)
		{
			pch__result_offset = sCH__MON_RESULT_OFFSET_A_ARM__LLx[ll_i].Get__PTR();

			sCH__MON_R_OFFSET_A_ARM__LLx[ll_i]->Set__DATA(ch__r_off);
			sCH__MON_T_OFFSET_A_ARM__LLx[ll_i]->Set__DATA(ch__t_off);
		}
		else if(pm_i >= 0)
		{
			pch__result_offset = sCH__MON_RESULT_OFFSET_A_ARM__PMx[pm_i].Get__PTR();

			sCH__MON_R_OFFSET_A_ARM__PMx[pm_i]->Set__DATA(ch__r_off);
			sCH__MON_T_OFFSET_A_ARM__PMx[pm_i]->Set__DATA(ch__t_off);
		}

		_Get__CFG_STN_OFFSET_OF_A_ARM(stn_name, cfg__soft_r,cfg__hard_r, cfg__soft_t,cfg__hard_t);
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		sCH__MON_R_OFFSET_B_ARM__ROBOT->Set__DATA(ch__r_off);
		sCH__MON_T_OFFSET_B_ARM__ROBOT->Set__DATA(ch__t_off);

		if(ll_i >= 0)
		{
			pch__result_offset = sCH__MON_RESULT_OFFSET_B_ARM__LLx[ll_i].Get__PTR();

			sCH__MON_R_OFFSET_B_ARM__LLx[ll_i]->Set__DATA(ch__r_off);
			sCH__MON_T_OFFSET_B_ARM__LLx[ll_i]->Set__DATA(ch__t_off);
		}
		else if(pm_i >= 0)
		{
			pch__result_offset = sCH__MON_RESULT_OFFSET_B_ARM__PMx[pm_i].Get__PTR();

			sCH__MON_R_OFFSET_B_ARM__PMx[pm_i]->Set__DATA(ch__r_off);
			sCH__MON_T_OFFSET_B_ARM__PMx[pm_i]->Set__DATA(ch__t_off);
		}

		_Get__CFG_STN_OFFSET_OF_B_ARM(stn_name, cfg__soft_r,cfg__hard_r, cfg__soft_t,cfg__hard_t);
	}

	// Chart Report ...
	if(ll_i >= 0)
	{
		sCH__DA_CHART_R_OFFSET_DISPLAY__LLx[ll_i]->Set__DATA(ch__r_off);
		sCH__DA_CHART_T_OFFSET_DISPLAY__LLx[ll_i]->Set__DATA(ch__t_off);
	}
	else if(pm_i >= 0)
	{
		sCH__DA_CHART_R_OFFSET_DISPLAY__PMx[pm_i]->Set__DATA(ch__r_off);
		sCH__DA_CHART_T_OFFSET_DISPLAY__PMx[pm_i]->Set__DATA(ch__t_off);
	}

	// Error Check ...
	{
		double cur__r_off = atof(ch__r_off);
		double cur__t_off = atof(ch__t_off);

		bool active__soft_err = false;
		bool active__hart_err = false;

		CString alm__soft_err = "";
		CString alm__hard_err = "";
		CString err_msg;

		// Soft_R ...
		if((cfg__soft_r > 0) 
		&& (cfg__soft_r > cur__r_off))
		{
			active__soft_err = true;

			err_msg.Format(" * Current offset radial <- %.3f (deg) \n",    cur__r_off);
			alm__soft_err += err_msg;
			err_msg.Format(" * Config soft-error radial <- %.1f (deg) \n", cfg__soft_r);
			alm__soft_err += err_msg;
			alm__soft_err += "\n";
		}
		// Soft_T ...
		if((cfg__soft_t > 0) 
		&& (cfg__soft_t > cur__t_off))
		{
			active__soft_err = true;

			err_msg.Format(" * Current offset theta <- %.3f (mm) \n",    cur__t_off);
			alm__soft_err += err_msg;
			err_msg.Format(" * Config soft-error theta <- %.1f (mm) \n", cfg__soft_t);
			alm__soft_err += err_msg;
			alm__soft_err += "\n";
		}

		// Hard_R ...
		if((cfg__hard_r > 0) 
		&& (cfg__hard_r > cur__r_off))
		{
			active__hart_err = true;

			err_msg.Format(" * Current offset radial <- %.3f (deg) \n",    cur__r_off);
			alm__hard_err += err_msg;
			err_msg.Format(" * Config hard-error radial <- %.1f (deg) \n", cfg__hard_r);
			alm__hard_err += err_msg;
			alm__hard_err += "\n";
		}
		// Hard_T ...
		if((cfg__hard_t > 0) 
		&& (cfg__hard_t > cur__t_off))
		{
			active__hart_err = true;

			err_msg.Format(" * Current offset theta <- %.3f (deg) \n",    cur__t_off);
			alm__hard_err += err_msg;
			err_msg.Format(" * Config hard-error theta <- %.1f (deg) \n", cfg__hard_t);
			alm__hard_err += err_msg;
			alm__hard_err += "\n";
		}

		if(active__hart_err)
		{
			pch__result_offset->Set__DATA("Error");

			// ...
			int alm_id = ALID__DA_ERROR__HARD_OFFSET;
			CString r_act;

			p_alarm->Popup__ALARM_With_MESSAGE(alm_id, alm__hard_err, r_act);

			if(r_act.CompareNoCase(ACT__IGNORE) != 0)
			{
				return -1;
			}
		}
		else if(active__soft_err)
		{
			pch__result_offset->Set__DATA("Warning");

			// ...
			int alm_id = ALID__DA_ERROR__SOFT_OFFSET;
			CString r_act;

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm__soft_err);
		}
		else
		{
			pch__result_offset->Set__DATA("OK");
		}
	}

	return 1;
}

int  CObj__VAC_ROBOT_STD
::_Set__DA_RT_OFFSET(const CString& stn_name)
{
	CString ch__r_off = sEXT_CH__ROBOT_DA_RESULT_R_OFFSET_DEG->Get__STRING();
	CString ch__t_off = sEXT_CH__ROBOT_DA_RESULT_T_OFFSET_MM->Get__STRING();

	CString ch_data;
	ch_data.Format("%s_%s", ch__r_off,ch__t_off);

	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

	if(ll_i >= 0)
	{
		sCH__MON_DA_RT_OFFSET__LLx[ll_i]->Set__DATA(ch_data);
	}
	else if(pm_i >= 0)
	{
		sCH__MON_DA_RT_OFFSET__PMx[pm_i]->Set__DATA(ch_data);
	}
	return 1;
}
int  CObj__VAC_ROBOT_STD
::_Clear__DA_RT_OFFSET(const CString& stn_name)
{
	CString ch_data = "";

	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

	if(ll_i >= 0)
	{
		sCH__MON_DA_RT_OFFSET__LLx[ll_i]->Set__DATA(ch_data);
	}
	else if(pm_i >= 0)
	{
		sCH__MON_DA_RT_OFFSET__PMx[pm_i]->Set__DATA(ch_data);
	}
	return 1;
}

int  CObj__VAC_ROBOT_STD
::_Save__DA_OFFSET(const CString& arm_type,
				   const CString& stn_name,
				   const CString& stn_slot,
				   const bool active_place)
{
	CString cfg_use = _Get__CFG_DYNAMIC_ALGN_USE(stn_name);
	if(cfg_use.CompareNoCase(STR__YES) != 0)		return 1;

	// ...
	CString wfr__portid;
	CString wfr__slotid;
	CString wfr__lotid;
	CString wfr__ppid;
	CString wfr__mtrid;
	CString wfr__mdx;

	CString wfr__state;
	CString wfr__title;

	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		wfr__portid = sCH__WFR_INFO_PORTID__ARM_A->Get__STRING();
		wfr__slotid = sCH__WFR_INFO_SLOTID__ARM_A->Get__STRING();
		wfr__lotid  = sCH__WFR_INFO_LOTID__ARM_A->Get__STRING();
		wfr__ppid   = sCH__WFR_INFO_PPID__ARM_A->Get__STRING();
		wfr__mtrid  = sCH__WFR_INFO_MATERIALID__ARM_A->Get__STRING();

		if(!active_place)
		{
			wfr__state = dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Get__STRING();
			wfr__title = sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE->Get__STRING();
		}
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		wfr__portid = sCH__WFR_INFO_PORTID__ARM_B->Get__STRING();
		wfr__slotid = sCH__WFR_INFO_SLOTID__ARM_B->Get__STRING();
		wfr__lotid  = sCH__WFR_INFO_LOTID__ARM_B->Get__STRING();
		wfr__ppid   = sCH__WFR_INFO_PPID__ARM_B->Get__STRING();
		wfr__mtrid  = sCH__WFR_INFO_MATERIALID__ARM_B->Get__STRING();

		if(!active_place)
		{
			wfr__state = dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Get__STRING();
			wfr__title = sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE->Get__STRING();
		}
	}

	if(ll_i >= 0)
	{
		wfr__mdx.Format("LL%1d", ll_i+1);

		if(active_place)
		{
			wfr__state = dEXT_CH__LLx_SLOT_STATUS[ll_i][0]->Get__STRING();
			wfr__title = sEXT_CH__LLx_SLOT_TITLE[ll_i][0]->Get__STRING();
		}
	}
	else if(pm_i >= 0)
	{
		wfr__mdx.Format("PM%1d", pm_i+1);

		if(active_place)
		{
			wfr__state = dEXT_CH__PMx_SLOT01_STATUS[pm_i]->Get__STRING();
			wfr__title = sEXT_CH__PMx_SLOT01_TITLE[pm_i]->Get__STRING();
		}
	}

	if(wfr__portid.CompareNoCase("") == 0)
	{
		if(wfr__state.CompareNoCase(STR__NONE) != 0)
		{
			Macro__Get_PortID_SlotID_Of_Wafer_Title(wfr__title, wfr__portid,wfr__slotid);			
		}
	}

	// Config Error-Offset ...
	double cfg__soft_r = 0.0;
	double cfg__soft_t = 0.0;
	double cfg__hard_r = 0.0;
	double cfg__hard_t = 0.0;

	// Current Offset
	double cur__off_r = 0.0;
	double cur__off_t = 0.0;

	CString ch__da_r_deg;
	CString ch__da_t_mm;

	// DA Value ...
	{
		ch__da_r_deg = sEXT_CH__ROBOT_DA_RESULT_R_OFFSET_DEG->Get__STRING();
		ch__da_t_mm  = sEXT_CH__ROBOT_DA_RESULT_T_OFFSET_MM->Get__STRING();
	}

	// ...
	CString file__prc_name;
	CString file__mdx_name;
	
	CString file_date;
	CString file_time;
	CString file_log;

	// File : PRC+[PORTID]+[LOTID] ...
	if(wfr__lotid.GetLength() > 0)
	{
		file__prc_name.Format("PRC+%s+%s.log", wfr__portid,wfr__lotid);
	}
	
	// File : LLx-[PORTID] ...
	if(ll_i >= 0)
	{
		file__mdx_name.Format("LL%1d+%s+%s.log",  ll_i+1,wfr__portid,wfr__lotid);		
	}
	// File : PMx-[PORTID] ...
	else if(pm_i >= 0)
	{
		file__mdx_name.Format("PM%1d+%s+%s.log",  pm_i+1,wfr__portid,wfr__lotid);		
	}

	// ...
	{
		SYSTEMTIME file__sys_time;
		GetLocalTime(&file__sys_time);

		file_date.Format("%04d_%02d_%02d",		
						 file__sys_time.wYear,
						 file__sys_time.wMonth,
						 file__sys_time.wDay);

		file_time.Format("%02d:%02d:%02d",		
						 file__sys_time.wHour,
						 file__sys_time.wMinute,
						 file__sys_time.wSecond);

				         //     1/ 2/ 3/ 4/ 5/ 6/ 7/ 8/ 9/10/
		file_log.Format("#SLOT=%s/%s/%s/%s/%s/%s/%s/%s/%s/%s/\n",
						wfr__slotid,		// 01 : SlotID
						ch__da_r_deg,		// 02 : R_Offset
						ch__da_t_mm,		// 03 : T_Offset
						wfr__lotid,			// 04 : LOTID
						wfr__ppid,			// 05 : PPID
						wfr__mtrid,			// 06 : MaterialID
						wfr__state,			// 07 : Wafer_State
						wfr__title,			// 08 : Wafer_Title
						wfr__mdx,			// 09 : Wafer_MDx
						file_time);			// 10 : Place_Time
	}

	// Write log ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "_Save__DA_OFFSET() : Start ...";
		log_msg += "\n";
		log_msg += file_log;

		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
		SCX__FILE_CTRL x_file_ctrl;
		x_file_ctrl->DISABLE__TIME_LOG();

		//
		CString ref_root;

		ref_root  = sDir_Root;
		ref_root += "\\EQP_LOG";
		x_file_ctrl->Create__LOG_DIR(ref_root);

		ref_root += "\\DA_Data";
		x_file_ctrl->Create__LOG_DIR(ref_root);

		x_file_ctrl->Delete__LOG_DIR(ref_root, 30);

		ref_root += "\\";
		ref_root += file_date;
		x_file_ctrl->Create__LOG_DIR(ref_root);

		//
		CString file_path;

		if(file__prc_name.GetLength() > 0)
		{
			file_path.Format("%s\\%s", ref_root,file__prc_name);
			x_file_ctrl->Write__LOG_MSG(file_path, file_log);
		}

		// ...
		{
			file_path.Format("%s\\%s", ref_root,file__mdx_name);
			x_file_ctrl->Write__LOG_MSG(file_path, file_log);
		}
	}
	return 1;
}

int  CObj__VAC_ROBOT_STD
::_Active__DA_STS(const CString& arm_type,
				  const CString& stn_name,
				  const bool result_clear)
{
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
		if(ll_i >= 0)
		{
			sCH__MON_STS_OFFSET_A_ARM__LLx[ll_i]->Set__DATA(STR__YES);

			if(result_clear)
				sCH__MON_RESULT_OFFSET_A_ARM__LLx[ll_i]->Set__DATA("");
		}
		else if(pm_i >= 0)
		{
			sCH__MON_STS_OFFSET_A_ARM__PMx[pm_i]->Set__DATA(STR__YES);

			if(result_clear)
				sCH__MON_RESULT_OFFSET_A_ARM__PMx[pm_i]->Set__DATA("");
		}
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		if(ll_i >= 0)
		{
			sCH__MON_STS_OFFSET_B_ARM__LLx[ll_i]->Set__DATA(STR__YES);

			if(result_clear)
				sCH__MON_RESULT_OFFSET_B_ARM__LLx[ll_i]->Set__DATA("");
		}
		else if(pm_i >= 0)
		{
			sCH__MON_STS_OFFSET_B_ARM__PMx[pm_i]->Set__DATA(STR__YES);

			if(result_clear)
				sCH__MON_RESULT_OFFSET_B_ARM__PMx[pm_i]->Set__DATA("");
		}
	}

	return 1;
}
int  CObj__VAC_ROBOT_STD
::_Clear__DA_STS(const CString& arm_type,
				 const CString& stn_name)
{
	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

	if(arm_type.CompareNoCase(ARM_A) == 0)
	{
			 if(ll_i >= 0)		sCH__MON_STS_OFFSET_A_ARM__LLx[ll_i]->Set__DATA("");
		else if(pm_i >= 0)		sCH__MON_STS_OFFSET_A_ARM__PMx[pm_i]->Set__DATA("");
	}
	else if(arm_type.CompareNoCase(ARM_B) == 0)
	{
		if(ll_i >= 0)		sCH__MON_STS_OFFSET_B_ARM__LLx[ll_i]->Set__DATA("");
		else if(pm_i >= 0)		sCH__MON_STS_OFFSET_B_ARM__PMx[pm_i]->Set__DATA("");
	}

	return 1;
}

int  CObj__VAC_ROBOT_STD
::_Get__CFG_STN_OFFSET_OF_A_ARM(const CString& stn_name, 
							    double& cfg__soft_r,
							    double& cfg__hard_r,
							    double& cfg__soft_t,
							    double& cfg__hard_t)
{
	// ...
	{
		cfg__soft_r = 0.0;
		cfg__hard_r = 0.0;
		cfg__soft_t = 0.0;
		cfg__hard_t = 0.0;
	}

	// LLx ...
	{
		int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

		if(ll_i >= 0)
		{
			cfg__soft_r = aCH__CFG__R_OFFSET_SOFT_ERR_A_ARM__LLx[ll_i]->Get__VALUE();
			cfg__hard_r = aCH__CFG__R_OFFSET_HARD_ERR_A_ARM__LLx[ll_i]->Get__VALUE();

			cfg__soft_t = aCH__CFG__T_OFFSET_SOFT_ERR_A_ARM__LLx[ll_i]->Get__VALUE();
			cfg__hard_t = aCH__CFG__T_OFFSET_HARD_ERR_A_ARM__LLx[ll_i]->Get__VALUE();

			return 1;
		}
	}

	// PMx ...
	{
		int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

		if((pm_i >= 0)
			&& (pm_i <  m_nPM_LIMIT))
		{
			cfg__soft_r = aCH__CFG__R_OFFSET_SOFT_ERR_A_ARM__PMx[pm_i]->Get__VALUE();
			cfg__hard_r = aCH__CFG__R_OFFSET_HARD_ERR_A_ARM__PMx[pm_i]->Get__VALUE();

			cfg__soft_t = aCH__CFG__T_OFFSET_SOFT_ERR_A_ARM__PMx[pm_i]->Get__VALUE();
			cfg__hard_t = aCH__CFG__T_OFFSET_HARD_ERR_A_ARM__PMx[pm_i]->Get__VALUE();

			return 1;
		}
	}

	return -1;
}
int  CObj__VAC_ROBOT_STD
::_Get__CFG_STN_OFFSET_OF_B_ARM(const CString& stn_name, 
							    double& cfg__soft_r,
							    double& cfg__hard_r,
							    double& cfg__soft_t,
							    double& cfg__hard_t)
{
	// ...
	{
		cfg__soft_r = 0.0;
		cfg__hard_r = 0.0;
		cfg__soft_t = 0.0;
		cfg__hard_t = 0.0;
	}

	// LLx ...
	{
		int ll_i = Macro__CHECK_LLx_INDEX(stn_name);

		if(ll_i >= 0)
		{
			cfg__soft_r = aCH__CFG__R_OFFSET_SOFT_ERR_B_ARM__LLx[ll_i]->Get__VALUE();
			cfg__hard_r = aCH__CFG__R_OFFSET_HARD_ERR_B_ARM__LLx[ll_i]->Get__VALUE();

			cfg__soft_t = aCH__CFG__T_OFFSET_SOFT_ERR_B_ARM__LLx[ll_i]->Get__VALUE();
			cfg__hard_t = aCH__CFG__T_OFFSET_HARD_ERR_B_ARM__LLx[ll_i]->Get__VALUE();

			return 1;
		}
	}

	// PMx ...
	{
		int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

		if((pm_i >= 0)
			&& (pm_i <  m_nPM_LIMIT))
		{
			cfg__soft_r = aCH__CFG__R_OFFSET_SOFT_ERR_B_ARM__PMx[pm_i]->Get__VALUE();
			cfg__hard_r = aCH__CFG__R_OFFSET_HARD_ERR_B_ARM__PMx[pm_i]->Get__VALUE();

			cfg__soft_t = aCH__CFG__T_OFFSET_SOFT_ERR_B_ARM__PMx[pm_i]->Get__VALUE();
			cfg__hard_t = aCH__CFG__T_OFFSET_HARD_ERR_B_ARM__PMx[pm_i]->Get__VALUE();

			return 1;
		}
	}

	return -1;
}

CString CObj__VAC_ROBOT_STD
::_Get__CFG_DYNAMIC_ALGN_USE(const CString& stn_name)
{
	CString cfg_val = "";

	int ll_i = Macro__CHECK_LLx_INDEX(stn_name);
	int pm_i = Macro__CHECK_PMx_INDEX(stn_name);

	if(ll_i >= 0)
	{
		dEXT_CH__CFG_DA_USE__LLx[ll_i]->Get__DATA(cfg_val);
	}
	else if((pm_i >= 0) && (pm_i < m_nPM_LIMIT))
	{
		dEXT_CH__CFG_DA_USE__PMx[pm_i]->Get__DATA(cfg_val);
	}

	return cfg_val;
}
