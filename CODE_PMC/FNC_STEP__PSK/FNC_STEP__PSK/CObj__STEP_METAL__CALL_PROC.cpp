#include "StdAfx.h"
#include "CObj__STEP_METAL.h"
#include "CObj__STEP_METAL__DEF.h"


// ...
int CObj__STEP_METAL
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
	CString rcp__apc_pressure_torr;
	CString rcp__apc_hold_sec;
	CString rcp__apc_tol_warning;
	CString rcp__apc_tol_alarm;

	CString rcp__mfc_x_flow[_CFG__MFC_SIZE];
	CString rcp__mfc_x_ramp_sec[_CFG__MFC_SIZE];

	CString rcp__rf_src_power;
	CString rcp__rf_src_warning;
	CString rcp__rf_src_alarm;

	CString rcp__rf_bias_wait_sec;
	CString rcp__rf_bias_power;
	CString rcp__rf_bias_warning;
	CString rcp__rf_bias_alarm;

	//
	CString rcp__mat_src_shunt;
	CString rcp__mat_src_series;
	CString rcp__mat_src_capacity;

	CString rcp__mat_src_learned_shunt;
	CString rcp__mat_src_learned_series;
	CString rcp__mat_src_learned_capacity;

	//
	CString rcp__mat_bias_shunt;
	CString rcp__mat_bias_series;
	CString rcp__mat_bias_capacity;

	CString rcp__mat_bias_learned_shunt;
	CString rcp__mat_bias_learned_series;
	CString rcp__mat_bias_learned_capacity;

	//
	CString rcp__esc_mode;
	CString rcp__dpc_pressure;
	CString rcp__dpc_flow_max;
	CString rcp__dpc_flow_min;

	CString rcp__lift_pin_mode;

	// ...
	bool active__rcp_log = false;
	// bool active__rcp_log = true;

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
		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			rcp__mfc_x_flow[i]     = sCH__RCP_GAS_FLOW_X[i]->Get__STRING();
			rcp__mfc_x_ramp_sec[i] = sCH__RCP_GAS_RAMP_SEC_X[i]->Get__STRING();
		}

		//
		sCH__RCP_RF_SOURCE_POWER->Get__DATA(rcp__rf_src_power);
		sCH__RCP_RF_SOURCE_TOL_WARNING->Get__DATA(rcp__rf_src_warning);
		sCH__RCP_RF_SOURCE_TOL_ALARM->Get__DATA(rcp__rf_src_alarm);

		sCH__RCP_RF_BIAS_WAIT_TIME->Get__DATA(rcp__rf_bias_wait_sec);
		sCH__RCP_RF_BIAS_POWER->Get__DATA(rcp__rf_bias_power);
		sCH__RCP_RF_BIAS_TOL_WARNING->Get__DATA(rcp__rf_bias_warning);
		sCH__RCP_RF_BIAS_TOL_ALARM->Get__DATA(rcp__rf_bias_alarm);

		//
		sCH__RCP_MAT_SOURCE_SHUNT->Get__DATA(rcp__mat_src_shunt);
		sCH__RCP_MAT_SOURCE_SERIES->Get__DATA(rcp__mat_src_series);
		sCH__RCP_MAT_SOURCE_CAPACITY->Get__DATA(rcp__mat_src_capacity);

		sCH__RCP_MAT_SOURCE_LEARNED_SHUNT->Get__DATA(rcp__mat_src_learned_shunt);
		sCH__RCP_MAT_SOURCE_LEARNED_SERIES->Get__DATA(rcp__mat_src_learned_series);
		sCH__RCP_MAT_SOURCE_LEARNED_CAPACITY->Get__DATA(rcp__mat_src_learned_capacity);

		//
		sCH__RCP_MAT_BIAS_SHUNT->Get__DATA(rcp__mat_bias_shunt);
		sCH__RCP_MAT_BIAS_SERIES->Get__DATA(rcp__mat_bias_series);
		sCH__RCP_MAT_BIAS_CAPACITY->Get__DATA(rcp__mat_bias_capacity);

		sCH__RCP_MAT_BIAS_LEARNED_SHUNT->Get__DATA(rcp__mat_bias_learned_shunt);
		sCH__RCP_MAT_BIAS_LEARNED_SERIES->Get__DATA(rcp__mat_bias_learned_series);
		sCH__RCP_MAT_BIAS_LEARNED_CAPACITY->Get__DATA(rcp__mat_bias_learned_capacity);

		//
		dCH__RCP_ESC_CTRL_MODE->Get__DATA(rcp__esc_mode);
		sCH__RCP_DPC_CENTER_PRESSURE->Get__DATA(rcp__dpc_pressure);
		sCH__RCP_DPC_CENTER_ZONE_FLOW_MAX_THRESHOLD->Get__DATA(rcp__dpc_flow_max);
		sCH__RCP_DPC_CENTER_ZONE_FLOW_MIN_THRESHOLD->Get__DATA(rcp__dpc_flow_min);

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

	// RF_SOURCE ...
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_src_power);

		if(set_power >= 0.001)			obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		if(active__rfx_delay_off)
		{
			if(obj_mode.CompareNoCase(_RF_CMD__OFF) != 0)
			{
				RF_SRC_OBJ__Start_MODE(obj_mode, rcp__rf_src_power, rcp__rf_src_warning,rcp__rf_src_alarm);

				// ...
				{
					log_msg = "RF.Source Control ... \n";

					log_bff.Format("  * RF.Source Control(%s, %s) \n", obj_mode,rcp__rf_src_power);
					log_msg += log_bff;
	
					xLOG_CTRL->WRITE__LOG(log_msg);		
				}
			}
		}
		else
		{
			RF_SRC_OBJ__Start_MODE(obj_mode, rcp__rf_src_power, rcp__rf_src_warning,rcp__rf_src_alarm);
		}
	}
	// RF_BIAS ...
	{
		CString obj_mode;
		double set_power = atof(rcp__rf_bias_power);

		if(set_power >= 0.001)			obj_mode = _RF_CMD__SET_POWER;
		else							obj_mode = _RF_CMD__OFF;

		if(active__rfx_delay_off)
		{
			if(obj_mode.CompareNoCase(_RF_CMD__OFF) != 0)
			{
				RF_BIAS_OBJ__Start_MODE(obj_mode, rcp__rf_bias_power, rcp__rf_bias_warning,rcp__rf_bias_alarm);

				// ...
				{
					log_msg = "RF.Bias Control ... \n";

					log_bff.Format("  * RF.Bias Control(%s, %s) \n", obj_mode,rcp__rf_src_power);
					log_msg += log_bff;

					xLOG_CTRL->WRITE__LOG(log_msg);		
				}
			}
		}
		else
		{
			RF_BIAS_OBJ__Start_MODE(obj_mode, rcp__rf_bias_power, rcp__rf_bias_warning,rcp__rf_bias_alarm);
		}
	}

	// HTR.STABLE_CHECK ...
	if(dCH__CFG_STEP_CTRL_HEATER_MODE->Check__DATA(STR__ONLY_CHECK) > 0)
	{
		_Fnc__HTR_STABLE_CHECK(p_variable,p_alarm);
	}

	// MATCHER ...
	{
		CString obj_mode = _MAT_CMD__PROC_CTRL;
		CString ch_data;

		double para__rcp_value = 0;
	
		// SOURCE ...
		{
			para__rcp_value = atof(rcp__mat_src_shunt);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_src_learned_shunt);

			aEXT_CH__MAT__PARA_LOAD_POS_CH1->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_src_series);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_src_learned_series);

			aEXT_CH__MAT__PARA_TUNE_POS_CH1->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_src_capacity);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_src_learned_capacity);

			aEXT_CH__MAT__PARA_CAP_POS_CH1->Set__VALUE(para__rcp_value);
		}
		// BIAS ...
		{
			para__rcp_value = atof(rcp__mat_bias_shunt);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_bias_learned_shunt);

			aEXT_CH__MAT__PARA_LOAD_POS_CH2->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_bias_series);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_bias_learned_series);

			aEXT_CH__MAT__PARA_TUNE_POS_CH2->Set__VALUE(para__rcp_value);

			//
			para__rcp_value = atof(rcp__mat_bias_capacity);
			if(para__rcp_value < 0.01)			para__rcp_value = atof(rcp__mat_bias_learned_capacity);

			aEXT_CH__MAT__PARA_CAP_POS_CH2->Set__VALUE(para__rcp_value);
		}

		MAT_OBJ__Start_MODE(obj_mode);
	}

	// ESC ...
	{
		CString obj_mode;
		CString ch_data;

			 if(rcp__esc_mode.CompareNoCase(STR__Chuck)    == 0)			obj_mode = _ESC_CMD__CHUCK_PROC;
		else if(rcp__esc_mode.CompareNoCase(STR__Chuck1)   == 0)			obj_mode = _ESC_CMD__CHUCK1_PROC;
		else if(rcp__esc_mode.CompareNoCase(STR__Chuck2)   == 0)			obj_mode = _ESC_CMD__CHUCK2_PROC;
		else if(rcp__esc_mode.CompareNoCase(STR__Dechuck)  == 0)			obj_mode = _ESC_CMD__DECHUCK;
		else if(rcp__esc_mode.CompareNoCase(STR__Dechuck1) == 0)			obj_mode = _ESC_CMD__DECHUCK1;
		else if(rcp__esc_mode.CompareNoCase(STR__Dechuck2) == 0)			obj_mode = _ESC_CMD__DECHUCK2;
		else if(rcp__esc_mode.CompareNoCase(STR__He_Set)   == 0)			obj_mode = _ESC_CMD__HE_SET_PROC;

		if(obj_mode.GetLength() > 0)			
		{
			sCH__RCP_DPC_CENTER_PRESSURE->Get__DATA(ch_data);
			sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR->Set__DATA(ch_data);

			//
			sCH__RCP_DPC_CENTER_ZONE_FLOW_MIN_THRESHOLD->Get__DATA(ch_data);
			sEXT_CH__ESC__RCP_He_CENTER_FLOW_MIN_THRESHOLD->Set__DATA(ch_data);

			sCH__RCP_DPC_CENTER_ZONE_FLOW_MAX_THRESHOLD->Get__DATA(ch_data);
			sEXT_CH__ESC__RCP_He_CENTER_FLOW_MAX_THRESHOLD->Set__DATA(ch_data);

			//
			ESC_OBJ__Start_MODE(obj_mode);
		}
	}

	// LIFT_PIN.CTRL ...
	{
		CString obj_mode = "";

		     if(rcp__lift_pin_mode.CompareNoCase(STR__Down)   == 0)			obj_mode  = _PIN_CMD__DOWN;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Middle) == 0)			obj_mode  = _PIN_CMD__MIDDLE;
		else if(rcp__lift_pin_mode.CompareNoCase(STR__Up)     == 0)			obj_mode  = _PIN_CMD__UP;

		if(obj_mode.GetLength() > 0)		
		{
			LIFT_PIN_OBJ__Start_MODE(obj_mode);
		}
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

					// RF_SOURCE ...
					{
						double set_power = atof(rcp__rf_src_power);
						
						if(set_power < 0.001)
						{
							RF_SRC_OBJ__Start_OFF();

							// ...
							{
								rfx_ctrl_count++;

								log_bff.Format("  * RF.Source Off(%s) \n", rcp__rf_src_power);
								log_msg += log_bff;
							}
						}
					}
					// RF_BIAS ...
					{
						double set_power = atof(rcp__rf_bias_power);

						if(set_power < 0.001)
						{
							RF_BIAS_OBJ__Start_OFF();

							// ...
							{
								rfx_ctrl_count++;

								log_bff.Format("  * RF.Bias Off(%s) \n", rcp__rf_bias_power);
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

			if(RF_SRC_OBJ__Check_ERROR()  > 0)						return -121;
			if(RF_BIAS_OBJ__Check_ERROR() > 0)						return -122;

			if(ESC_OBJ__Check_ERROR() > 0)							return -131;

			if(active__htr_error_check)
			{
				if(HTR_CHUCK_OBJ__Check_STABLE_ERROR() > 0)			return -141;
				if(HTR_WALL_OBJ__Check_STABLE_ERROR()  > 0)			return -142;
			}
		}
		// ABORTEDR CHECK ...
		{
			if(MFC_OBJ__Check_ABORTED() > 0)						return -211;
			if(APC_OBJ__Check_ABORTED() > 0)						return -212;

			if(RF_SRC_OBJ__Check_ABORTED()  > 0)					return -221;
			if(RF_BIAS_OBJ__Check_ABORTED() > 0)					return -222;
			if(MAT_OBJ__Check_ABORTED() > 0)						return -223;
			if(ESC_OBJ__Check_ABORTED() > 0)						return -224;
			if(LIFT_PIN_OBJ__Check_ABORTED() > 0)					return -225;
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

	// Object Over-Time Check ...
	double cur__obj_delay_sec = Fnc__OBJ_OVERTIME_CHECK(p_variable, p_alarm);

	// ...
	{
		log_msg.Format("Step(%s) End - Object Delay (%.2f sec)", cur__step_ud, cur__obj_delay_sec);

		xLOG_CTRL->WRITE__LOG(log_msg);		
	}

	// OBJ.Abort Check ...
	{
		if(ESC_OBJ__Check_ABORTED() > 0)						return -301;
		if(LIFT_PIN_OBJ__Check_ABORTED() > 0)					return -302;
	}
	return 1;
}

double CObj__STEP_METAL
::Fnc__OBJ_OVERTIME_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	SCX__ASYNC_TIMER_CTRL x_obj_timer_ctrl;
	x_obj_timer_ctrl->START__COUNT_UP(9999);

	bool active__esc_obj = false;
	bool active__pin_obj = false;

	while(1)
	{
		bool active__obj_budy = false;

		if(ESC_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__esc_obj = true;
		}
		if(LIFT_PIN_OBJ__Is_BUSY() > 0)
		{
			active__obj_budy = true;
			active__pin_obj = true;
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
		CString cur__esc_mode = dCH__RCP_ESC_CTRL_MODE->Get__STRING();
		CString cur__pin_mode = dCH__RCP_LIFT_PIN_MODE->Get__STRING();

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
		
		if(active__esc_obj)
		{
			alm_bff.Format("   * ESC control-mode is \"%s\". \n", cur__esc_mode);
			alm_msg += alm_bff;
		}
		if(active__pin_obj)
		{
			alm_bff.Format("   * Lift-pin control is \"%s\". \n", cur__pin_mode);
			alm_msg += alm_bff;
		}

		alm_msg += "\n";

		if(active__esc_obj)
		{
			alm_bff.Format(" Please, check the time of ESC (%s) config page. \n", cur__esc_mode);
			alm_msg += alm_bff;
		}
		if(active__pin_obj)
		{
			alm_bff.Format(" Please, check the actual operation time of lift-pin (%s). \n", cur__pin_mode);
			alm_msg += alm_bff;
		}

		//
		p_alarm->Check__ALARM(alm_id, r_act);
		p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
	}

	return x_obj_timer_ctrl->Get__CURRENT_TIME();
}

int CObj__STEP_METAL
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

int CObj__STEP_METAL::_Fnc__PROC_LOG()
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
						sCH__RCP_APC_LEARNED_POS->Get__CHANNEL_NAME(),
						sCH__RCP_APC_LEARNED_POS->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						aCH__RCP_APC_PRESSURE_mTORR->Get__CHANNEL_NAME(),
						aCH__RCP_APC_PRESSURE_mTORR->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__RCP_APC_HOLD_DELAY->Get__CHANNEL_NAME(),
						sCH__RCP_APC_HOLD_DELAY->Get__STRING());
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

	// RF_SOURCE ...
	{
		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_SOURCE_POWER->Get__CHANNEL_NAME(),
			sCH__RCP_RF_SOURCE_POWER->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_SOURCE_TOL_WARNING->Get__CHANNEL_NAME(),
			sCH__RCP_RF_SOURCE_TOL_WARNING->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_SOURCE_TOL_ALARM->Get__CHANNEL_NAME(),
			sCH__RCP_RF_SOURCE_TOL_ALARM->Get__STRING());
		log_msg += log_bff;
	}
	// RF_BIAS ...
	{
		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_BIAS_WAIT_TIME->Get__CHANNEL_NAME(),
			sCH__RCP_RF_BIAS_WAIT_TIME->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_BIAS_POWER->Get__CHANNEL_NAME(),
			sCH__RCP_RF_BIAS_POWER->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_BIAS_TOL_WARNING->Get__CHANNEL_NAME(),
			sCH__RCP_RF_BIAS_TOL_WARNING->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_RF_BIAS_TOL_ALARM->Get__CHANNEL_NAME(),
			sCH__RCP_RF_BIAS_TOL_ALARM->Get__STRING());
		log_msg += log_bff;
	}

	// MATCHER ...
	{
		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_MAT_SOURCE_SHUNT->Get__CHANNEL_NAME(),
			sCH__RCP_MAT_SOURCE_SHUNT->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_MAT_SOURCE_SERIES->Get__CHANNEL_NAME(),
			sCH__RCP_MAT_SOURCE_SERIES->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_MAT_SOURCE_CAPACITY->Get__CHANNEL_NAME(),
			sCH__RCP_MAT_SOURCE_CAPACITY->Get__STRING());
		log_msg += log_bff;

		//
		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_MAT_BIAS_SHUNT->Get__CHANNEL_NAME(),
			sCH__RCP_MAT_BIAS_SHUNT->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_MAT_BIAS_SERIES->Get__CHANNEL_NAME(),
			sCH__RCP_MAT_BIAS_SERIES->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_MAT_BIAS_CAPACITY->Get__CHANNEL_NAME(),
			sCH__RCP_MAT_BIAS_CAPACITY->Get__STRING());
		log_msg += log_bff;
	}

	// ESC ...
	{
		log_bff.Format(" * %s <- %s \n", 
			dCH__RCP_ESC_CTRL_MODE->Get__CHANNEL_NAME(),
			dCH__RCP_ESC_CTRL_MODE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_DPC_CENTER_PRESSURE->Get__CHANNEL_NAME(),
			sCH__RCP_DPC_CENTER_PRESSURE->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_DPC_CENTER_ZONE_FLOW_MAX_THRESHOLD->Get__CHANNEL_NAME(),
			sCH__RCP_DPC_CENTER_ZONE_FLOW_MAX_THRESHOLD->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s \n", 
			sCH__RCP_DPC_CENTER_ZONE_FLOW_MIN_THRESHOLD->Get__CHANNEL_NAME(),
			sCH__RCP_DPC_CENTER_ZONE_FLOW_MIN_THRESHOLD->Get__STRING());
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
