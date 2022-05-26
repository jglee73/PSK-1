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
	CString rcp__step_overetch_per;

	CString rcp__apc_mode;
	CString rcp__apc_pressure_torr;
	CString rcp__apc_position;
	CString rcp__apc_learned_pos;
	CString rcp__apc_hold_sec;
	CString rcp__apc_tol_warning;
	CString rcp__apc_tol_alarm;

	CString rcp__rf_top_power;
	CString rcp__rf_top_warning;
	CString rcp__rf_top_alarm;

	//
	CString rcp__mat_top_shunt;
	CString rcp__mat_top_series;
	CString rcp__mat_top_capacity;

	CString rcp__mat_top_learned_shunt;
	CString rcp__mat_top_learned_series;
	CString rcp__mat_top_learned_capacity;

	//
	CString rcp__mfc_x_flow[_CFG__MFC_SIZE];
	CString rcp__mfc_x_ramp_sec[_CFG__MFC_SIZE];

	CString rcp__lfc_temp;
	CString rcp__lfc_valve;
	CString rcp__lfc_flow;

	CString rcp__lift_pin_mode;

	//
	CString rcp__epd_mode;
	CString rcp__epd_value_to_change;
	CString rcp__epd_percent_to_change;
	
	CString rcp__epd_delay_time;
	CString rcp__epd_normalize_time;
	
	CString rcp__epd_min_time;
	CString rcp__epd_max_time;

	CString rcp__epd_min_threshold;
	CString rcp__epd_max_threshold;

	CString rcp__epd_slope_value;
	CString rcp__epd_slope_type;
	CString rcp__epd_valid_time;
	//


	// ...
	bool active__rcp_log = false;

	SCX__ASYNC_TIMER_CTRL x_obj_timer_ctrl;
	x_obj_timer_ctrl->START__COUNT_UP(9999);

	CString cur__step_ud = sCH__INFO_STEP_CUR_NUM->Get__STRING();

	// ...
	bool active__mfc_delay_off = false;
	bool active__rfx_delay_off = false;

	double cfg_delay__rf_off    = aCH__CFG_STEP_DELAY_RF_OFF->Get__VALUE();
	double cfg_delay__mfc_close = aCH__CFG_STEP_DELAY_MFC_CLOSE->Get__VALUE();
	double cfg_delay__ref_sec = 0.05;

	if(cfg_delay__mfc_close > cfg_delay__ref_sec)		active__mfc_delay_off = true;
	if(cfg_delay__rf_off    > cfg_delay__ref_sec)		active__rfx_delay_off = true;


	// RCP ...
	{
		sCH__RCP_STEP_MESSAGE->Get__DATA(rcp__step_msg);
		dCH__RCP_STEP_MODE->Get__DATA(rcp__step_mode);
		aCH__RCP_STEP_TIME->Get__DATA(rcp__step_time);
		aCH__RCP_STEP_OVERETCH_PERCENT->Get__DATA(rcp__step_overetch_per);

		//
		dCH__RCP_APC_MODE->Get__DATA(rcp__apc_mode);

		ch_data = aCH__RCP_APC_PRESSURE_mTORR->Get__STRING();
		rcp__apc_pressure_torr.Format("%.3f", atof(ch_data) * 0.001);

		aCH__RCP_APC_POSITION->Get__DATA(rcp__apc_position);
		sCH__RCP_APC_LEARNED_POS->Get__DATA(rcp__apc_learned_pos);
		sCH__RCP_APC_HOLD_DELAY->Get__DATA(rcp__apc_hold_sec);

		rcp__apc_tol_warning = sCH__RCP_APC_TOL_WARNING->Get__STRING();
		rcp__apc_tol_alarm   = sCH__RCP_APC_TOL_ALARM->Get__STRING();

		//
		sCH__RCP_RF_TOP_POWER->Get__DATA(rcp__rf_top_power);
		sCH__RCP_RF_TOP_TOL_WARNING->Get__DATA(rcp__rf_top_warning);
		sCH__RCP_RF_TOP_TOL_ALARM->Get__DATA(rcp__rf_top_alarm);

		//
		rcp__mat_top_shunt    = sCH__RCP_MAT_TOP_SHUNT->Get__STRING();
		rcp__mat_top_series   = sCH__RCP_MAT_TOP_SERIES->Get__STRING(); 
		rcp__mat_top_capacity = sCH__RCP_MAT_TOP_CAPACITY->Get__STRING();

		sCH__RCP_MAT_TOP_LEARNED_SHUNT->Get__DATA(rcp__mat_top_learned_shunt);
		sCH__RCP_MAT_TOP_LEARNED_SERIES->Get__DATA(rcp__mat_top_learned_series);
		sCH__RCP_MAT_TOP_LEARNED_CAPACITY->Get__DATA(rcp__mat_top_learned_capacity);

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
		rcp__lift_pin_mode = dCH__RCP_LIFT_PIN_MODE->Get__STRING();

		//
		rcp__epd_mode = dCH__RCP_EPD_EPD_MODE->Get__STRING();
		
		rcp__epd_value_to_change   = aCH__RCP_EPD_VALUE_TO_CHANGE->Get__STRING();
		rcp__epd_percent_to_change = aCH__RCP_EPD_PERCENT_TO_CHANGE->Get__STRING();
		
		rcp__epd_delay_time = aCH__RCP_EPD_DELAY_TIME->Get__STRING();
		rcp__epd_normalize_time = aCH__RCP_EPD_NORMALIZE_TIME->Get__STRING();
		
		rcp__epd_min_time = aCH__RCP_EPD_MIN_TIME->Get__STRING();
		rcp__epd_max_time = aCH__RCP_EPD_MAX_TIME->Get__STRING();

		rcp__epd_min_threshold = aCH__RCP_EPD_MIN_THRESHOLD->Get__STRING();
		rcp__epd_max_threshold = aCH__RCP_EPD_MAX_THRESHOLD->Get__STRING();

		rcp__epd_slope_value = aCH__RCP_EPD_SLOPE_VALUE->Get__STRING();
		rcp__epd_slope_type  = dCH__RCP_EPD_SLOPE_TYPE->Get__STRING();
		rcp__epd_valid_time  = aCH__RCP_EPD_SLOPE_VALID_TIME->Get__STRING();
	}

	// LOG ...
	if(active__rcp_log)
	{
		_Fnc__PROC_LOG();
	}

	
	// ...
	bool active__stable_mode = false;
	bool active__fast_vac  = false;
	bool active__end_point = false;
	bool active__over_etch = false;

	if(rcp__step_mode.CompareNoCase(STR__Stable) == 0)
	{
		active__stable_mode = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__High_Vac) == 0)
	{
		active__fast_vac = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__EndPT) == 0)
	{
		active__end_point = true;
	}
	else if(rcp__step_mode.CompareNoCase(STR__OverEtch) == 0)
	{
		active__over_etch = true;

		ch_data = sCH__INFO_STEP_PRE_TIME->Get__STRING();
		double cur__step_sec = atof(ch_data);
		double cur__over_per = atof(rcp__step_overetch_per);

		rcp__step_time.Format("%.1f", (cur__step_sec * cur__over_per) * 0.01);
		aCH__RCP_STEP_TIME->Set__DATA(rcp__step_time);
	}
	else if(rcp__step_mode.CompareNoCase(STR__End) == 0)
	{
		return 1;
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
			para_data = rcp__apc_pressure_torr;
		}

		if(obj_mode.GetLength() > 0)
		{
			double value__hold_sec = atof(rcp__apc_hold_sec);
			double value__hold_pos = atof(rcp__apc_position);
			if(value__hold_pos < 0.01)			value__hold_pos = atof(rcp__apc_learned_pos);			

			aEXT_CH__APC_OBJ__CFG_PROC_PRESSURE_WARNING_BAND->Set__DATA(rcp__apc_tol_warning);
			aEXT_CH__APC_OBJ__CFG_PROC_PRESSURE_ABORT_BAND->Set__DATA(rcp__apc_tol_alarm);

			APC_OBJ__Start_MODE(obj_mode,para_data, value__hold_sec,value__hold_pos);
		}
	}

	// MFC_X.CTRL ...
	if(active__mfc_delay_off)
	{
		int mfc_ctrl_count = 0;

		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			double para__set_flow = atof(rcp__mfc_x_flow[i]);
			if(para__set_flow < 0.001)			continue;

			MFC_OBJ__Start_CONTROL(i, rcp__mfc_x_flow[i],rcp__mfc_x_ramp_sec[i]);

			// ...
			{
				mfc_ctrl_count++;		
				if(mfc_ctrl_count == 1)		
					log_msg.Format("MFCx Control ... \n");

				log_bff.Format("  * MFC%1d Control(%s, %s) \n", i+1, rcp__mfc_x_flow[i],rcp__mfc_x_ramp_sec[i]);
				log_msg += log_bff;
			}
		}

		if(mfc_ctrl_count > 0)
		{
			xLOG_CTRL->WRITE__LOG(log_msg);		
		}
	}
	else
	{
		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			MFC_OBJ__Start_CONTROL(i, rcp__mfc_x_flow[i],rcp__mfc_x_ramp_sec[i]);
		}
	}

	// RF_TOP ...
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_top_power);

		if(set_power >= 0.001)			obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		if(active__rfx_delay_off)
		{
			if(obj_mode.CompareNoCase(_RF_CMD__OFF) != 0)
			{
				RF_TOP_OBJ__Start_MODE(obj_mode, rcp__rf_top_power, rcp__rf_top_warning,rcp__rf_top_alarm);

				// ...
				{
					log_msg = "RF.TOP Control ... \n";

					log_bff.Format("  * RF.Source Control(%s, %s) \n", obj_mode,rcp__rf_top_power);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);		
				}
			}
		}
		else
		{
			RF_TOP_OBJ__Start_MODE(obj_mode, rcp__rf_top_power, rcp__rf_top_warning,rcp__rf_top_alarm);
		}
	}

	// MAT_TOP ...
	if(bActive__OBJ_CTRL__MAT)
	{
		CString obj_mode = _MAT_CMD__PROC_CTRL;
		double para__rcp_value = 0;

		// ...
		{
			para__rcp_value = atof(rcp__mat_top_shunt);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_top_learned_shunt);

			aEXT_CH__MAT__PARA_LOAD_POS_CH1->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_top_series);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_top_learned_series);

			aEXT_CH__MAT__PARA_TUNE_POS_CH1->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_top_capacity);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_top_learned_capacity);

			aEXT_CH__MAT__PARA_CAP_POS_CH1->Set__VALUE(para__rcp_value);
		}

		MAT_OBJ__Start_MODE(obj_mode);
	}

	// VAPORIZER ...
	if(bActive__OBJ_CTRL__LFC)
	{
			 if(rcp__lfc_valve.CompareNoCase(STR__Open)  == 0)				LFC_OBJ__Start_CONTROL(rcp__lfc_flow);
		else if(rcp__lfc_valve.CompareNoCase(STR__Dump)  == 0)				LFC_OBJ__Start_DUMP();
		else																LFC_OBJ__Start_CLOSE();
	}

	// HTR.STABLE_CHECK ...
	if(dCH__CFG_STEP_CTRL_HEATER_MODE->Check__DATA(STR__ONLY_CHECK) > 0)
	{
		_Fnc__HTR_STABLE_CHECK(p_variable,p_alarm);
	}

	// LIFT_PIN.CTRL ...
	bool active__pin_ctrl = false;

	if(bActive__OBJ_CTRL__LIFT_PIN)
	{
		CString obj_mode;

			 if(rcp__lift_pin_mode.CompareNoCase(STR__Down)   == 0)			obj_mode  = _PIN_CMD__DOWN;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Middle) == 0)			obj_mode  = _PIN_CMD__MIDDLE;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Up)     == 0)			obj_mode  = _PIN_CMD__UP;

		if(obj_mode.GetLength() > 0)
		{
			LIFT_PIN_OBJ__Start_MODE(obj_mode);

			if(active__end_point)
			{
				if(obj_mode.CompareNoCase(_PIN_CMD__DOWN) != 0)
				{
					active__pin_ctrl  = true;
					active__end_point = false;
				}
			}
		}
	}

	// EPD ...
	{
		bool active__epd_idle   = false;
		bool active__epd_check  = false;
		bool active__epd_detect = false;
		bool active__err_check  = false;

		if(rcp__epd_mode.CompareNoCase("Idle") == 0)
		{
			if(active__end_point)			active__err_check = true;
			else							active__epd_idle  = true;
		}
		else if(rcp__epd_mode.CompareNoCase("Error.Check") == 0)
		{
			if(active__end_point)			active__err_check = true;
			else							active__epd_check = true;
		}
		else
		{
			if(active__end_point)
			{
				active__epd_detect = true;

				//
				dEXT_CH__EPD__PARA_EPD_MODE->Set__DATA(rcp__epd_mode);

				sEXT_CH__EPD__PARA_VALUE_TO_CHANGE->Set__DATA(rcp__epd_value_to_change);
				sEXT_CH__EPD__PARA_PERCENT_TO_CHANGE->Set__DATA(rcp__epd_percent_to_change);
	
				aEXT_CH__EPD__PARA_DELAY_TIME->Set__DATA(rcp__epd_delay_time);
				sEXT_CH__EPD__PARA_NORMALIZE_TIME->Set__DATA(rcp__epd_normalize_time);

				aEXT_CH__EPD__PARA_EPD_TIMEOUT_MINIMUM->Set__DATA(rcp__epd_min_time);
				aEXT_CH__EPD__PARA_EPD_TIMEOUT_MAXIMUM->Set__DATA(rcp__epd_max_time);
	
				sEXT_CH__EPD__PARA_EPD_THRESHOLD_MIN->Set__DATA(rcp__epd_min_threshold);
				sEXT_CH__EPD__PARA_EPD_THRESHOLD_MAX->Set__DATA(rcp__epd_max_threshold);

				sEXT_CH__EPD__PARA_SLOPE_COUNT->Set__DATA(rcp__epd_slope_value);
				sEXT_CH__EPD__PARA_SLOPE_DIRECTION->Set__DATA(rcp__epd_slope_type);
				sEXT_CH__EPD__PARA_VALID_TIME->Set__DATA(rcp__epd_valid_time);
			}
			else
			{
				active__epd_idle = true;
			}
		}

		if(active__err_check)
		{
			int alm_id = ALID__STEP_PARAMETER__SETTING_ERROR;

			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_bff.Format("Current Step.No <- %s \n", sCH__INFO_STEP_CUR_NUM->Get__STRING());
			alm_msg += alm_bff;

			alm_bff.Format("  Step.Mode <- %s \n", rcp__step_mode);
			alm_msg += alm_bff;
			alm_bff.Format("  EPD.Mode  <- %s \n", rcp__epd_mode);
			alm_msg += alm_bff;

			p_alarm->Check__ALARM(alm_id, r_act);
			p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			return -101;
		}

			 if(active__epd_idle)			EPD_OBJ__Start_IDLE();
		else if(active__epd_check)			EPD_OBJ__Start_CHECK();
		else if(active__epd_detect)			EPD_OBJ__Start_DETECT();
	}

	
	// ...
	double cfg__stable_min_sec = aCH__CFG_STEP_STABLE_MIN_SEC->Get__VALUE();

	// ...
	bool active__htr_error_check = false;

	if(dCH__CFG_STEP_CTRL_ERROR_CONTROL->Check__DATA(STR__ENABLE) > 0)
	{
		active__htr_error_check = true;
	}

	// ...
	SCX__STEP_TIMER_CTRL x_step_timer;
	x_step_timer->START__TIMER();

	double para__step_sec = atof(rcp__step_time);
	double cur_sec  = 0.0;

	// ...
	{
		log_msg.Format("Step(%s) Start - Mode(%s) Time(%s sec) \n", cur__step_ud, rcp__step_mode,rcp__step_time);

		log_bff.Format("  * cfg_delay__rf_off : %.1f sec \n", cfg_delay__rf_off);
		log_msg += log_bff;
		log_bff.Format("  * cfg_delay__mfc_close : %.1f sec \n", cfg_delay__mfc_close);
		log_msg += log_bff;
		log_bff.Format("  * cfg_delay__ref_sec : %.1f sec \n", cfg_delay__ref_sec);
		log_msg += log_bff;

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

		// Turn.Off De;ay ...
		{
			// MFC_X.CTRL ...
			if(active__mfc_delay_off)
			{
				if(cur_sec >= cfg_delay__mfc_close)
				{
					active__mfc_delay_off = false;

					//
					int mfc_ctrl_count = 0;

					for(i=0; i<iDATA__MFC_SIZE; i++)
					{
						double para__set_flow = atof(rcp__mfc_x_flow[i]);
						if(para__set_flow >= 0.001)		continue;

						MFC_OBJ__Start_CLOSE(i);

						// ...
						{
							mfc_ctrl_count++;		
							if(mfc_ctrl_count == 1)		
								log_msg.Format("MFCx Close ... \n");

							log_bff.Format("  * MFC%1d Close(%s, %s) \n", i+1, rcp__mfc_x_flow[i],rcp__mfc_x_ramp_sec[i]);
							log_msg += log_bff;
						}
					}

					if(mfc_ctrl_count > 0)
					{
						xLOG_CTRL->WRITE__LOG(log_msg);		
					}
				}
			}

			// RFx.CTRL ...
			if(active__rfx_delay_off)
			{
				if(cur_sec >= cfg_delay__rf_off)
				{
					active__rfx_delay_off = false;

					//
					int rfx_ctrl_count = 0;

					log_msg.Format("RFx Off ... \n");

					// RF_TOP ...
					{
						double set_power = atof(rcp__rf_top_power);

						if(set_power < 0.001)
						{
							RF_TOP_OBJ__Start_OFF();

							// ...
							{
								rfx_ctrl_count++;

								log_bff.Format("  * RF.Top Off(%s) \n", rcp__rf_top_power);
								log_msg += log_bff;
							}
						}
					}

					if(rfx_ctrl_count > 0)
					{
						xLOG_CTRL->WRITE__LOG(log_msg);		
					}
				}
			}
		}

		// ERROR CHECK ...
		{
			if(MFC_OBJ__Check_ERROR() > 0)							return -111;
			if(APC_OBJ__Check_ERROR() > 0)							return -112;
			if(PT_OBJ__Check_ERROR()  > 0)							return -113;
			if(LFC_OBJ__Check_ERROR() > 0)							return -114;

			if(RF_TOP_OBJ__Check_ERROR()  > 0)						return -121;

			if(active__htr_error_check)
			{
				if(HTR_CHUCK_OBJ__Check_STABLE_ERROR() > 0)			return -141;
				if(HTR_WALL_OBJ__Check_STABLE_ERROR()  > 0)			return -142;
			}

			if(active__over_etch)
			{
				if(EPD_OBJ__Check_ERROR() > 0)						return -151;
			}
		}
		// ABORTEDR CHECK ...
		{
			if(MFC_OBJ__Check_ABORTED() > 0)						return -211;
			if(APC_OBJ__Check_ABORTED() > 0)						return -212;

			if(RF_TOP_OBJ__Check_ABORTED()  > 0)					return -221;
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
				double ref__pressure = atof(rcp__apc_pressure_torr);

				if(cur__pressure <= ref__pressure)
				{
					break;
				}
			}
		}
		else if(active__end_point)
		{
			if(EPD_OBJ__Is_BUSY() < 0)
			{
				break;
			}
		}
		else if(active__pin_ctrl)
		{
			if(LIFT_PIN_OBJ__Is_BUSY() < 0)
			{
				break;
			}
		}

		if(cur_ctrl == _CMD_ID__START)
		{
			if(x_step_timer->Check__CURRENT_TIME(para__step_sec, cur_sec))
			{
				if((active__stable_mode)
				|| (active__fast_vac)
				|| (active__end_point)
				|| (active__pin_ctrl))
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

	// ...
	{
		ch_data.Format("%.1f", x_step_timer->Get__CURRENT_SEC());
		sCH__INFO_STEP_PRE_TIME->Set__DATA(ch_data);
	}

	// Object Over-Time Check ...
	double cur__obj_delay_sec = Fnc__OBJ_OVERTIME_CHECK(p_variable, p_alarm);

	// ...
	{
		log_msg.Format("Step(%s) End - Object Delay (%.2f sec)", cur__step_ud, cur__obj_delay_sec);

		xLOG_CTRL->WRITE__LOG(log_msg);		
	}

	// OBJ.Abort Check ...
	{
		if(LIFT_PIN_OBJ__Check_ABORTED() > 0)					return -302;
		if(EPD_OBJ__Check_ABORTED() > 0)						return -303;
	}
	return 1;
}

double CObj__STEP_STRIP
::Fnc__OBJ_OVERTIME_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_obj_timer_ctrl;
	x_obj_timer_ctrl->START__COUNT_UP(9999);

	bool active__pin_obj = false;
	bool active__epd_obj = false;

	while(1)
	{
		bool active__obj_budy = false;

		if(LIFT_PIN_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__pin_obj = true;
		}
		if(EPD_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__epd_obj  = true;
		}

		if(active__obj_budy)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			break;

			Sleep(1);
			continue;
		}

		break;
	}

	//
	double cfg__err_ref = aCH__CFG_STEP_OBJECT_OVER_TIME_ERRPR_REF_SEC->Get__VALUE();

	if(x_obj_timer_ctrl->Get__CURRENT_TIME() > cfg__err_ref)
	{
		int alm_id = ALID__OBJECT_OVERTIME;

		CString alm_msg;
		CString alm_bff;
		CString r_act;

		CString cur__step_id = sCH__INFO_STEP_CUR_NUM->Get__STRING();

		//
		CString cur__step_time = aCH__RCP_STEP_TIME->Get__STRING();
		CString cur__step_mode = dCH__RCP_STEP_MODE->Get__STRING();
		CString cur__pin_mode  = dCH__RCP_LIFT_PIN_MODE->Get__STRING();
		CString cur__epd_mode  = dCH__RCP_EPD_EPD_MODE->Get__STRING();

		//
		alm_bff.Format(" Object over-time is %.1f (sec). \n", x_obj_timer_ctrl->Get__CURRENT_TIME());
		alm_msg += alm_bff;

		alm_bff.Format(" Object over-time error-ref is %.2f (sec). \n", cfg__err_ref);
		alm_msg += alm_bff;

		//
		alm_msg += "\n";
		alm_bff.Format(" The current step ID is %s. \n", cur__step_id);
		alm_msg += alm_bff;

		alm_bff.Format(" The step information is as follows : \n");
		alm_msg += alm_bff;

		alm_bff.Format("   * Step-time is %s (sec). \n", cur__step_time);
		alm_msg += alm_bff;

		alm_bff.Format("   * Step-mode is \"%s\". \n", cur__step_mode);
		alm_msg += alm_bff;

		if(active__pin_obj)
		{
			alm_bff.Format("   * Lift-pin control is \"%s\". \n", cur__pin_mode);
			alm_msg += alm_bff;
		}
		if(active__epd_obj)
		{
			alm_bff.Format("   * EPD control is \"%s\". \n", cur__epd_mode);
			alm_msg += alm_bff;
		}

		alm_msg += "\n";

		if(active__pin_obj)
		{
			alm_bff.Format(" Please, check the actual operation time of lift-pin (%s). \n", cur__pin_mode);
			alm_msg += alm_bff;
		}
		if(active__epd_obj)
		{
			alm_bff.Format(" Please, check the actual operation time of EPD (%s). \n", cur__epd_mode);
			alm_msg += alm_bff;
		}

		//
		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}

	return x_obj_timer_ctrl->Get__CURRENT_TIME();
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
						aCH__RCP_APC_PRESSURE_mTORR->Get__CHANNEL_NAME(),
						aCH__RCP_APC_PRESSURE_mTORR->Get__STRING());
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

	// EPD ...
	{
		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_EPD_EPD_MODE->Get__CHANNEL_NAME(),
						dCH__RCP_EPD_EPD_MODE->Get__STRING());
		log_msg += log_bff;

		//
		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_VALUE_TO_CHANGE->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_VALUE_TO_CHANGE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_PERCENT_TO_CHANGE->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_PERCENT_TO_CHANGE->Get__STRING());
		log_msg += log_bff;

		//
		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_DELAY_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_DELAY_TIME->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_NORMALIZE_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_NORMALIZE_TIME->Get__STRING());
		log_msg += log_bff;

		//
		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_MIN_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_MIN_TIME->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_MAX_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_MAX_TIME->Get__STRING());
		log_msg += log_bff;

		//
		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_SLOPE_VALUE->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_SLOPE_VALUE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						dCH__RCP_EPD_SLOPE_TYPE->Get__CHANNEL_NAME(),
						dCH__RCP_EPD_SLOPE_TYPE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_EPD_SLOPE_VALID_TIME->Get__CHANNEL_NAME(),
						aCH__RCP_EPD_SLOPE_VALID_TIME->Get__STRING());
		log_msg += log_bff;
	}

	xLOG_CTRL->WRITE__LOG(log_msg);		
	return 1;
}
