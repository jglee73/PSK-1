#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"
#include "CObj__STEP_STRIP__DEF.h"


// ...
int CObj__STEP_STRIP
::Call__PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int i;

	// ...
	CString rcp__step_msg;
	CString rcp__step_mode;
	CString rcp__step_time;

	CString rcp__apc_mode;
	CString rcp__apc_position;
	CString rcp__apc_learned_pos;
	CString rcp__apc_pressure;
	CString rcp__apc_hold_sec;

	CString rcp__rf_top_power;
	CString rcp__rf_top_warning;
	CString rcp__rf_top_alarm;

	CString rcp__mat_top_shunt;
	CString rcp__mat_top_series;
	CString rcp__mat_top_capacity;

	CString rcp__mfc_x_flow[_CFG__MFC_SIZE];
	CString rcp__mfc_x_ramp_sec[_CFG__MFC_SIZE];

	CString rcp__lfc_temp;
	CString rcp__lfc_valve;
	CString rcp__lfc_flow;

	CString rcp__lift_pin_mode;

	// ...
	bool active__rcp_log = false;

	SCX__ASYNC_TIMER_CTRL x_obj_timer_ctrl;
	x_obj_timer_ctrl->START__COUNT_UP(9999);

	CString cur__step_ud = sCH__INFO_STEP_CUR_NUM->Get__STRING();


	// RCP ...
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(rcp__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(rcp__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(rcp__step_time);

		//
		dCH__RCP_APC_MODE->Get__DATA(rcp__apc_mode);
		aCH__RCP_APC_POSITION->Get__DATA(rcp__apc_position);
		sCH__RCP_APC_LEARNED_POS->Get__DATA(rcp__apc_learned_pos);
		aCH__RCP_APC_PRESSURE->Get__DATA(rcp__apc_pressure);
		sCH__RCP_APC_HOLD_DELAY->Get__DATA(rcp__apc_hold_sec);

		//
		sCH__RCP_RF_TOP_POWER->Get__DATA(rcp__rf_top_power);
		sCH__RCP_RF_TOP_TOL_WARNING->Get__DATA(rcp__rf_top_warning);
		sCH__RCP_RF_TOP_TOL_ALARM->Get__DATA(rcp__rf_top_alarm);

		//
		rcp__mat_top_shunt    = sCH__RCP_MAT_TOP_SHUNT->Get__STRING();
		rcp__mat_top_series   = sCH__RCP_MAT_TOP_SERIES->Get__STRING(); 
		rcp__mat_top_capacity = sCH__RCP_MAT_TOP_SHUNT->Get__STRING();

		//
		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			rcp__mfc_x_flow[i]     = sCH__RCP_GAS_FLOW_X[i]->Get__STRING();
			rcp__mfc_x_ramp_sec[i] = sCH__RCP_GAS_RAMP_SEC_X[i]->Get__STRING();
		}

		//
		rcp__lfc_temp  = sCH__RCP_VAPOR_TEMPERATURE->Get__STRING();
		rcp__lfc_valve = dCH__RCP_VAPOR_VALVE->Get__STRING();
		rcp__lfc_flow  = sCH__RCP_VAPOR_FLOW->Get__STRING();

		//
		dCH__RCP_LIFT_PIN_MODE->Get__DATA(rcp__lift_pin_mode);
	}

	// LOG ...
	if(active__rcp_log)
	{
		_Fnc__PROC_LOG();
	}

	// APC.CTRL ...
	{
		CString obj_mode;
		CString para_data;

		if(rcp__apc_mode.CompareNoCase(STR__Position) == 0)
		{
			obj_mode  = _APC_CMD__POSITION;
			para_data = rcp__apc_position;
		}
		else if(rcp__apc_mode.CompareNoCase(STR__Pressure) == 0)
		{
			obj_mode  = _APC_CMD__PRESSURE;
			para_data = rcp__apc_pressure;
		}

		double value__hold_sec = atof(rcp__apc_hold_sec);
		double value__hold_pos = atof(rcp__apc_position);
		if(value__hold_pos < 0.1)			value__hold_pos = atof(rcp__apc_learned_pos);

		APC_OBJ__Start_MODE(obj_mode,para_data, value__hold_sec,value__hold_pos);
	}

	// MFC_X.CTRL ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		MFC_OBJ__Start_CONTROL(i, rcp__mfc_x_flow[i],rcp__mfc_x_ramp_sec[i]);
	}

	// RF_TOP ...
	if(bActive__OBJ_CTRL__RF_TOP)
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_top_power);

		if(set_power > 0.1)				obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		RF_TOP_OBJ__Start_MODE(obj_mode, rcp__rf_top_power);
	}

	// MAT_TOP ...
	if(bActive__OBJ_CTRL__MAT)
	{
		CString obj_mode = _MAT_CMD__PROC_CTRL;
		CString ch_data;

		sCH__RCP_MAT_TOP_SHUNT->Get__DATA(ch_data);
		aEXT_CH__MAT__PARA_LOAD_POS_CH1->Set__DATA(ch_data);

		sCH__RCP_MAT_TOP_SERIES->Get__DATA(ch_data);
		aEXT_CH__MAT__PARA_TUNE_POS_CH1->Set__DATA(ch_data);

		sCH__RCP_MAT_TOP_CAPACITY->Get__DATA(ch_data);
		aEXT_CH__MAT__PARA_CAP_POS_CH1->Set__DATA(ch_data);

		MAT_OBJ__Start_MODE(obj_mode);
	}

	// VAPORIZER ...
	if(bActive__OBJ_CTRL__LFC)
	{
			 if(rcp__lfc_valve.CompareNoCase(STR__Open)  == 0)				LFC_OBJ__Start_CONTROL(rcp__lfc_flow);
		else if(rcp__lfc_valve.CompareNoCase(STR__Dump)  == 0)				LFC_OBJ__Start_DUMP();
		else																LFC_OBJ__Start_CLOSE();
	}

	// LIFT_PIN.CTRL ...
	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		CString obj_mode;

			 if(rcp__lift_pin_mode.CompareNoCase(STR__Down)   == 0)			obj_mode  = _PIN_CMD__DOWN;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Middle) == 0)			obj_mode  = _PIN_CMD__MIDDLE;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Up)     == 0)			obj_mode  = _PIN_CMD__UP;

		if(obj_mode.GetLength() > 0)
		{
			LIFT_PIN_OBJ__Start_MODE(obj_mode);
		}
		else
		{
			LIFT_PIN_OBJ__Wait();
		}
	}

	// Object Over-Time Check ...
	double cfg__err_ref = aCH__CFG_STEP_OBJECT_OVER_TIME_ERRPR_REF_SEC->Get__VALUE();

	x_obj_timer_ctrl->STOP();
	if(x_obj_timer_ctrl->Get__CURRENT_TIME() > cfg__err_ref)
	{
		int alm_id = ALID__OBJECT_OVERTIME;

		CString alm_msg;
		CString alm_bff;
		CString r_act;

		CString cur__step_id = sCH__INFO_STEP_CUR_NUM->Get__STRING();
		CString pre__step_id = sCH__INFO_STEP_PRE_NUM->Get__STRING();
		
		CString pre__step_time = sCH__INFO_STEP_PRE_TIME->Get__STRING();
		CString pre__step_mode = sCH__INFO_STEP_PRE_MODE->Get__STRING();
		CString pre__pin_ctrl = sCH__INFO_STEP_PRE_PIN_CTRL->Get__STRING();

		//
		alm_bff.Format(" Object over-time is %.1f (sec). \n", x_obj_timer_ctrl->Get__CURRENT_TIME());
		alm_msg += alm_bff;

		alm_bff.Format(" Object over-time error-ref is %.2f (sec). \n", cfg__err_ref);
		alm_msg += alm_bff;

		//
		alm_msg += "\n";
		alm_bff.Format(" The current step ID is %s. \n", cur__step_id);
		alm_msg += alm_bff;

		alm_bff.Format(" The information of previous step(%s) is as follows : \n", pre__step_id);
		alm_msg += alm_bff;

		alm_bff.Format("   * Step-time is %s (sec). \n", pre__step_time);
		alm_msg += alm_bff;

		alm_bff.Format("   * Step-mode is \"%s\". \n", pre__step_mode);
		alm_msg += alm_bff;

		alm_bff.Format("   * Lift-pin control is \"%s\". \n", pre__pin_ctrl);
		alm_msg += alm_bff;

		alm_msg += "\n";
		alm_bff.Format(" Please, check the actual operation time of lift-pin. \n");
		alm_msg += alm_bff;

		//
		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}

	// ...
	bool active__stable_mode = false;
	bool active__fast_vac = false;

	if(rcp__step_mode.CompareNoCase(STR__Stable) == 0)
	{
		active__stable_mode = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__High_Vac) == 0)
	{
		active__fast_vac = true;
	}

	// ...
	double cfg__stable_min_sec = aCH__CFG_STEP_STABLE_MIN_SEC->Get__VALUE();

	// ...
	SCX__STEP_TIMER_CTRL x_step_timer;
	x_step_timer->START__TIMER();

	double para__step_sec = atof(rcp__step_time);
	double cur_sec  = 0.0;

	// ...
	{
		log_msg.Format("Step(%s) Start - Object Delay (%.2f sec) \n", cur__step_ud, x_obj_timer_ctrl->Get__CURRENT_TIME());

		xLOG_CTRL->WRITE__LOG(log_msg);		
	}

	while(1)
	{
		// CHECK : STEP.ACT ...
		int cur_ctrl = Get__STEP_CTRL();

		if(cur_ctrl != _CMD_ID__START)
		{
			return cur_ctrl;
		}

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -1;
		}

		if(iActive__SIM_MODE > 0)
		{
			if(dCH__CFG_STEP_ALARM_TEST_ACTIVE->Check__DATA(STR__ON) > 0)
			{
				return -2;
			}
		}

		// ERROR CHECK ...
		{
			if(MFC_OBJ__Check_ERROR() > 0)				return -111;
			if(APC_OBJ__Check_ERROR() > 0)				return -112;
			if(PT_OBJ__Check_ERROR()  > 0)				return -113;

			if(RF_TOP_OBJ__Check_ERROR()  > 0)			return -121;
		}
		// ABORTEDR CHECK ...
		{
			if(MFC_OBJ__Check_ABORTED() > 0)			return -211;
			if(APC_OBJ__Check_ABORTED() > 0)			return -212;

			if(RF_TOP_OBJ__Check_ABORTED()  > 0)		return -221;
		}

		if(active__stable_mode)
		{
			if(cur_sec >= cfg__stable_min_sec)
			{
				if(APC_OBJ__Check_STABLE() > 0)	
				{
					break;
				}
			}
		}
		else if(active__fast_vac)
		{
			if(cur_sec >= cfg__stable_min_sec)
			{
				double cur__pressure = aEXT_CH__APC_OBJ__PARA_PRESSURE->Get__VALUE();
				double ref__pressure = atof(rcp__apc_pressure);

				if(cur__pressure <= ref__pressure)
				{
					break;
				}
			}
		}

		if(cur_ctrl == _CMD_ID__START)
		{
			if(x_step_timer->Check__CURRENT_TIME(para__step_sec, cur_sec))
			{
				if((active__stable_mode)
					|| (active__fast_vac))
				{
					int alm_id = ALID__STABLE_OVERTIME;
					CString alm_msg;
					CString r_act;

					alm_msg.Format("Stable Timeout Error (%.1f sec) \n", para__step_sec);

					p_alarm->Check__ALARM(alm_id, r_act);
					p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					return -1;
				}
				break;
			}
		}
	}

	// INFO.STEP_PRE ...
	{
		ch_data = sCH__INFO_STEP_CUR_NUM->Get__STRING();
		sCH__INFO_STEP_PRE_NUM->Set__DATA(ch_data);

		//
		ch_data = aCH__RCP_STEP_TIME->Get__STRING();
		sCH__INFO_STEP_PRE_TIME->Set__DATA(ch_data);

		ch_data = dCH__RCP_STEP_MODE->Get__STRING();
		sCH__INFO_STEP_PRE_MODE->Set__DATA(ch_data);

		ch_data = dCH__RCP_LIFT_PIN_MODE->Get__STRING();
		sCH__INFO_STEP_PRE_PIN_CTRL->Set__DATA(ch_data);
	}

	// ...
	{
		log_msg.Format("Step(%s) End ...", cur__step_ud);

		xLOG_CTRL->WRITE__LOG(log_msg);		
	}
	return 1;
}

int CObj__STEP_STRIP
::Get__STEP_CTRL()
{
	CString cur_act = sCH__MON_STEP_EXCEPTION_ACT->Get__STRING();

	if(cur_act.CompareNoCase(_ACT_CMD__ABORT) == 0)
	{
		printf(" * Fnc__STEP() - ABORT ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
				sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
				cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__ABORT;
	}
	if(cur_act.CompareNoCase(_ACT_CMD__SKIP) == 0)
	{
		printf(" * Fnc__STEP() - SKIP ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
				sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
				cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__SKIP;
	}

	if(cur_act.CompareNoCase(_ACT_CMD__PAUSE) == 0)
	{
		printf(" * Fnc__STEP() - PAUSE ... \n");

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg  = "\n";
			log_msg += "Step Exception Command ... \n";

			log_bff.Format(" * %s <- %s \n", 
				sCH__MON_STEP_EXCEPTION_ACT->Get__CHANNEL_NAME(),
				cur_act);
			log_msg += log_bff;

			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
		return _CMD_ID__PAUSE;
	}

	return _CMD_ID__START;
}

int CObj__STEP_STRIP::_Fnc__PROC_LOG()
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int i;

	log_msg  = "\n";
	log_msg += "Recipe Step-Info ... \n";

	// STEP ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_STEP_MESSAGE->Get__CHANNEL_NAME(),
						sCH__RCP_STEP_MESSAGE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_STEP_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_STEP_MODE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_STEP_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_STEP_TIME->Get__STRING());
		log_msg += log_bff;
	}

	// APC ...
	{
		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_APC_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_APC_MODE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_APC_POSITION->Get__CHANNEL_NAME(),
						aCH__RCP_APC_POSITION->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_APC_PRESSURE->Get__CHANNEL_NAME(),
						aCH__RCP_APC_PRESSURE->Get__STRING());
		log_msg += log_bff;
	}

	// MFC_X ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_GAS_FLOW_X[i]->Get__CHANNEL_NAME(),
						sCH__RCP_GAS_FLOW_X[i]->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_GAS_RAMP_SEC_X[i]->Get__CHANNEL_NAME(),
						sCH__RCP_GAS_RAMP_SEC_X[i]->Get__STRING());
		log_msg += log_bff;
	}

	// RF_TOP ...
	{
		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_TOP_POWER->Get__CHANNEL_NAME(),
						sCH__RCP_RF_TOP_POWER->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_TOP_TOL_WARNING->Get__CHANNEL_NAME(),
						sCH__RCP_RF_TOP_TOL_WARNING->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_RF_TOP_TOL_ALARM->Get__CHANNEL_NAME(),
						sCH__RCP_RF_TOP_TOL_ALARM->Get__STRING());
		log_msg += log_bff;
	}

	// LIFT_PIN ...
	{
		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_LIFT_PIN_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_LIFT_PIN_MODE->Get__STRING());
		log_msg += log_bff;
	}

	xLOG_CTRL->WRITE__LOG(log_msg);		
	return 1;
}
