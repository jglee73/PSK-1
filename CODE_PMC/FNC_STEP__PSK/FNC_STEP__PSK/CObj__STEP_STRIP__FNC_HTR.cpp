#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"
#include "CObj__STEP_STRIP__DEF.h"


// ...
int CObj__STEP_STRIP
::Fnc__HTR_STEP_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString rcp__chuck_temp_x[_CFG__CHUCK_SIZE];
	CString rcp__chuck_offset_x[_CFG__CHUCK_SIZE];
	CString rcp__chuck_warning_x[_CFG__CHUCK_SIZE];
	CString rcp__chuck_alarm_x[_CFG__CHUCK_SIZE];

	CString rcp__wall_main_temp;
	CString rcp__wall_offset;
	CString rcp__wall_warning;
	CString rcp__wall_alarm;

	CString ch_data;
	int i;

	// Recipe Parameter ...
	{
		// CHUCK ...
		for(i=0; i<_CFG__CHUCK_SIZE; i++)
		{
			rcp__chuck_temp_x[i]    = sCH__RCP_CHUCK_TEMP_X[i]->Get__STRING();
			rcp__chuck_offset_x[i]  = sCH__RCP_CHUCK_OFFSET_X[i]->Get__STRING();
			rcp__chuck_warning_x[i] = sCH__RCP_CHUCK_WARNING_X[i]->Get__STRING();
			rcp__chuck_alarm_x[i]   = sCH__RCP_CHUCK_ALARM_X[i]->Get__STRING();
		}

		// WALL ...
		{
			rcp__wall_main_temp = sCH__RCP_WALL_MAIN_TEMP->Get__STRING();
			rcp__wall_offset    = sCH__RCP_WALL_MAIN_OFFSET->Get__STRING();	
			rcp__wall_warning   = sCH__RCP_WALL_MAIN_WARNING->Get__STRING();	
			rcp__wall_alarm     = sCH__RCP_WALL_MAIN_ALARM->Get__STRING();
		}
	}

	// Temperature.Check ...
	bool active__htr_control = false;
	bool active__htr_check = false; 

	if(dCH__CFG_STEP_READY_HEATER_MODE->Check__DATA(STR__CONTROL) > 0)
	{
		active__htr_control = true;
		active__htr_check = true; 
	}
	else if(dCH__CFG_STEP_READY_HEATER_MODE->Check__DATA(STR__ONLY_CHECK) > 0)
	{
		active__htr_check = true; 
	}

	if(active__htr_control)
	{
		sCH__OBJ_SUB_MSG->Set__DATA("Temperature heating control.");

		int r_flag = _Fnc__HTR_STABLE_CONTROL(p_variable,p_alarm);
		if(r_flag < 0)
		{
			sCH__OBJ_SUB_MSG->Set__DATA("Temperature heating aborted.");
			return r_flag;
		}

		sCH__OBJ_SUB_MSG->Set__DATA("Temperature heating complete.");
	}

	if(active__htr_check)
	{
		sCH__OBJ_SUB_MSG->Set__DATA("Temperature stable check ...");

		//
		int active__stable_count = 0; 

		//
		double cfg__time_min = aCH__CFG_STEP_READY_CHECK_TIME_MIN->Get__VALUE();
		double cfg__time_max = aCH__CFG_STEP_READY_CHECK_TIME_MAX->Get__VALUE();

		SCX__ASYNC_TIMER_CTRL x_timer_stable;
		SCX__ASYNC_TIMER_CTRL x_timer_error;

		x_timer_stable->STOP_ZERO();
		x_timer_error->START__COUNT_UP(9999);

		while(1)
		{
			if(p_variable->Check__CTRL_ABORT() > 0)			return -11;

			// ...
			bool active__hard_stable = true;
			bool active__soft_stable = true;

			// Chuck.Temperature ...
			if(bActive__OBJ_CTRL__HTR_CHUCK)
			{
				for(i=0; i<_CFG__CHUCK_SIZE; i++)
				{
					double ref__off_temp = atof(rcp__chuck_offset_x[i]);
					double ref__set_temp = atof(rcp__chuck_temp_x[i]) - ref__off_temp;				
					double cfg__soft_tol = atof(rcp__chuck_warning_x[i]) * 0.01;
					double cfg__hard_tol = atof(rcp__chuck_alarm_x[i]) * 0.01;

					double ref__soft_min = ref__set_temp - cfg__soft_tol;
					double ref__soft_max = ref__set_temp + cfg__soft_tol;
					double ref__hard_min = ref__set_temp - cfg__hard_tol;
					double ref__hard_max = ref__set_temp + cfg__hard_tol;

					//
					double cur__temp_pv = aEXT_CH__HTR_CHUCK__MON_IO_PV_X[i]->Get__VALUE();

					if(cfg__soft_tol > 0.001)
					{
						if(cur__temp_pv < ref__soft_min) 		active__soft_stable = false;
						if(cur__temp_pv > ref__soft_max)		active__soft_stable = false;
					}
					if(cfg__hard_tol > 0.001)
					{
						if(cur__temp_pv < ref__hard_min) 		active__hard_stable = false;
						if(cur__temp_pv > ref__hard_max)		active__hard_stable = false;
					}
				}
			}
			// Wall.Temperature ...
			if(bActive__OBJ_CTRL__HTR_WALL)
			{
				double ref__off_temp = atof(rcp__wall_offset);
				double ref__set_temp = atof(rcp__wall_main_temp) - ref__off_temp;
				double cfg__soft_tol = atof(rcp__wall_warning) * 0.01;
				double cfg__hard_tol = atof(rcp__wall_alarm) * 0.01;

				double ref__soft_min = ref__set_temp - cfg__soft_tol;
				double ref__soft_max = ref__set_temp + cfg__soft_tol;
				double ref__hard_min = ref__set_temp - cfg__hard_tol;
				double ref__hard_max = ref__set_temp + cfg__hard_tol;

				for(i=0; i<_CFG__WALL_SIZE; i++)
				{
					double cur__temp_pv = aEXT_CH__HTR_WALL__MON_IO_PV_X[i]->Get__VALUE();

					if(cfg__soft_tol > 0.001)
					{
						if(cur__temp_pv < ref__soft_min) 		active__soft_stable = false;
						if(cur__temp_pv > ref__soft_max)		active__soft_stable = false;
					}
					if(cfg__hard_tol > 0.001)
					{
						if(cur__temp_pv < ref__hard_min) 		active__hard_stable = false;
						if(cur__temp_pv > ref__hard_max)		active__hard_stable = false;
					}
				}
			}

			if((active__hard_stable)
				|| (active__soft_stable))
			{
				if(active__stable_count <= 0)
				{
					active__stable_count = 1;
					x_timer_stable->START__COUNT_UP(9999);
				}
			}
			else
			{
				if(active__stable_count >= 0)
				{
					active__stable_count = -1;
					x_timer_stable->STOP_ZERO();
				}
			}

			// ...
			{
				double cur__stable_sec = x_timer_stable->Get__CURRENT_TIME();
				double cur__error_sec  = x_timer_error->Get__CURRENT_TIME();

				if(cur__stable_sec > cfg__time_min)
				{
					sCH__OBJ_SUB_MSG->Set__DATA("Temperature stable check end ...");
					break;
				}

				if(cur__error_sec > cfg__time_max)
				{
					int count__hard_err = 0;

					// ...
					int alm_id;
					CString alm_msg;
					CString alm_bff;
					CString r_act;

					// ...
					{
						alm_bff.Format(" Stable Check Time (Min) is %.1f (sec) \n", cfg__time_min);
						alm_msg += alm_bff;
						alm_bff.Format(" Stable Check Time (Max) is %.1f (sec) \n", cfg__time_max);
						alm_msg += alm_bff;
						alm_msg += "\n";
					}

					// Chuck.Temperature ...
					if(bActive__OBJ_CTRL__HTR_CHUCK)
					{
						for(i=0; i<_CFG__CHUCK_SIZE; i++)
						{
							double ref__off_temp = atof(rcp__chuck_offset_x[i]);
							double ref__set_temp = atof(rcp__chuck_temp_x[i]) - ref__off_temp;				
							double cfg__soft_tol = atof(rcp__chuck_warning_x[i]) * 0.01;
							double cfg__hard_tol = atof(rcp__chuck_alarm_x[i]) * 0.01;

							double ref__soft_min = ref__set_temp * (1.0 - cfg__soft_tol);
							double ref__soft_max = ref__set_temp * (1.0 + cfg__soft_tol);
							double ref__hard_min = ref__set_temp * (1.0 - cfg__hard_tol);
							double ref__hard_max = ref__set_temp * (1.0 + cfg__hard_tol);

							//
							bool active__soft_err = false;
							bool active__hard_err = false;

							double cur__temp_pv = aEXT_CH__HTR_CHUCK__MON_IO_PV_X[i]->Get__VALUE();

							if(cfg__soft_tol > 0.001)
							{
								if(cur__temp_pv < ref__soft_min)		active__soft_err = true;
								if(cur__temp_pv > ref__soft_max)		active__soft_err = true;
							}
							if(cfg__hard_tol > 0.001)
							{
								if(cur__temp_pv < ref__soft_min)		active__hard_err = true;
								if(cur__temp_pv > ref__soft_max)		active__hard_err = true;
							}

							if(active__hard_err)
							{
								count__hard_err++;
							}

							if((active__soft_err) 
								|| (active__hard_err))
							{
								int chuck_id = i + 1;

								alm_bff.Format(" * Chuck(%1d) temperature state is as follows: \n", chuck_id);
								alm_msg += alm_bff;
								alm_bff.Format("   -. Current temperature is %.1f (C) \n", cur__temp_pv);
								alm_msg += alm_bff;

								if(active__hard_err)
								{
									alm_bff.Format("   -. Hard tolerance range is (%.1f ~ %.1f) (C) \n", ref__hard_min,ref__hard_max);
									alm_msg += alm_bff;
								}
								else if(active__soft_err)
								{
									alm_bff.Format("   -. Soft tolerance range is (%.1f ~ %.1f) (C) \n", ref__soft_min,ref__soft_max);
									alm_msg += alm_bff;
								}

								alm_msg += "\n";
							}
						}
					}
					// Wall.Temperature ...
					if(bActive__OBJ_CTRL__HTR_WALL)
					{
						double ref__off_temp = atof(rcp__wall_offset);
						double ref__set_temp = atof(rcp__wall_main_temp) - ref__off_temp;
						double cfg__soft_tol = atof(rcp__wall_warning) * 0.01;
						double cfg__hard_tol = atof(rcp__wall_alarm) * 0.01;

						double ref__soft_min = ref__set_temp * (1.0 - cfg__soft_tol);
						double ref__soft_max = ref__set_temp * (1.0 + cfg__soft_tol);
						double ref__hard_min = ref__set_temp * (1.0 - cfg__hard_tol);
						double ref__hard_max = ref__set_temp * (1.0 + cfg__hard_tol);

						for(i=0; i<_CFG__WALL_SIZE; i++)
						{
							bool active__soft_err = false;
							bool active__hard_err = false;

							double cur__temp_pv = aEXT_CH__HTR_WALL__MON_IO_PV_X[i]->Get__VALUE();

							if(cfg__soft_tol > 0.001)
							{
								if(cur__temp_pv < ref__soft_min)		active__soft_err = true;
								if(cur__temp_pv > ref__soft_max)		active__soft_err = true;
							}
							if(cfg__hard_tol > 0.001)
							{
								if(cur__temp_pv < ref__soft_min)		active__hard_err = true;
								if(cur__temp_pv > ref__soft_max)		active__hard_err = true;
							}

							if(active__hard_err)
							{
								count__hard_err++;
							}

							if((active__soft_err) 
								|| (active__hard_err))
							{
								int wall_id = i + 1;

								if(wall_id == 1)
								{
									alm_bff.Format(" * Wall(main) temperature state is as follows: \n");
									alm_msg += alm_bff;
								}
								else
								{
									alm_bff.Format(" * Wall(%1d) temperature state is as follows: \n", wall_id-1);
									alm_msg += alm_bff;
								}
								alm_bff.Format("   -. Current temperature is %.1f (C) \n", cur__temp_pv);
								alm_msg += alm_bff;

								if(active__hard_err)
								{
									alm_bff.Format("   -. Hard tolerance range is (%.1f ~ %.1f) (C) \n", ref__hard_min,ref__hard_max);
									alm_msg += alm_bff;
								}
								else if(active__soft_err)
								{
									alm_bff.Format("   -. Soft tolerance range is (%.1f ~ %.1f) (C) \n", ref__soft_min,ref__soft_max);
									alm_msg += alm_bff;
								}

								alm_msg += "\n";
							}
						}
					}

					if(count__hard_err > 0)
					{
						alm_id = ALID__STEP_READY__TEMPERATURE_STABLE_TIMEOUT_ERROR;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);

						sCH__OBJ_SUB_MSG->Set__DATA("Temperature stable error !");
						return -21;
					}
					else
					{
						alm_id = ALID__STEP_READY__TEMPERATURE_STABLE_TIMEOUT_WARNING;

						p_alarm->Check__ALARM(alm_id, r_act);
						p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
					}

					sCH__OBJ_SUB_MSG->Set__DATA("Temperature stable warning !");
					break;
				}
			}

			Sleep(90);
		}
	}

	_Fnc__HTR_STABLE_CHECK(p_variable,p_alarm);
	return 1;
}

int CObj__STEP_STRIP
::_Fnc__HTR_STABLE_CONTROL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// Chuck.Temperature ...
	if(bActive__OBJ_CTRL__HTR_CHUCK)
	{
		for(int i=0; i<_CFG__CHUCK_SIZE; i++)
		{
			CString rcp__temp    = sCH__RCP_CHUCK_TEMP_X[i]->Get__STRING();
			CString rcp__offset  = sCH__RCP_CHUCK_OFFSET_X[i]->Get__STRING();
			CString rcp__warning = sCH__RCP_CHUCK_WARNING_X[i]->Get__STRING();
			CString rcp__alarm   = sCH__RCP_CHUCK_ALARM_X[i]->Get__STRING();

			double ref__off_temp = atof(rcp__offset);
			double ref__set_temp = atof(rcp__temp) - ref__off_temp;
			double cfg__soft_tol = atof(rcp__warning) * 0.01;
			double cfg__hard_tol = atof(rcp__alarm) * 0.01;

			//
			ch_data.Format("%.1f", ref__set_temp * cfg__soft_tol);
			aEXT_CH__HTR_CHUCK__CFG_PROC_SOFT_TOLERANCE_X[i]->Set__DATA(ch_data);

			ch_data.Format("%.1f", ref__set_temp * cfg__hard_tol);
			aEXT_CH__HTR_CHUCK__CFG_PROC_HARD_TOLERANCE_X[i]->Set__DATA(ch_data);

			//
			aEXT_CH__HTR_CHUCK__PARA_TARGET_SP_X[i]->Set__VALUE(ref__set_temp);
		}

		CString obj_mode = _HTR_CMD__HEATING_PROC;
		pOBJ_CTRL__HTR_CHUCK->Run__OBJECT(obj_mode);
	}

	// Wall.Temperature ...
	if(bActive__OBJ_CTRL__HTR_WALL)
	{
		CString rcp__main_temp = sCH__RCP_WALL_MAIN_TEMP->Get__STRING();
		CString rcp__offset    = sCH__RCP_WALL_MAIN_OFFSET->Get__STRING();	
		CString rcp__warning   = sCH__RCP_WALL_MAIN_WARNING->Get__STRING();	
		CString rcp__alarm     = sCH__RCP_WALL_MAIN_ALARM->Get__STRING();

		double ref__off_temp = atof(rcp__offset);
		double ref__set_temp = atof(rcp__main_temp) - ref__off_temp;
		double cfg__soft_tol = atof(rcp__warning) * 0.01;
		double cfg__hard_tol = atof(rcp__alarm) * 0.01;

		for(int i=0; i<_CFG__WALL_SIZE; i++)
		{
			ch_data.Format("%.1f", ref__set_temp * cfg__soft_tol);
			aEXT_CH__HTR_WALL__CFG_PROC_SOFT_TOLERANCE_X[i]->Set__DATA(ch_data);

			ch_data.Format("%.1f", ref__set_temp * cfg__hard_tol);
			aEXT_CH__HTR_WALL__CFG_PROC_HARD_TOLERANCE_X[i]->Set__DATA(ch_data);

			//
			aEXT_CH__HTR_WALL__PARA_TARGET_SP_X[i]->Set__VALUE(ref__set_temp);
		}

		CString obj_mode = _HTR_CMD__HEATING_PROC;
		pOBJ_CTRL__HTR_WALL->Run__OBJECT(obj_mode);
	}

	// Object.Busy Check ...
	while(1)
	{
		Sleep(90);

		if(p_variable->Check__CTRL_ABORT() > 0)				return -11;

		// ...
		bool active__obj_idle = true;

		if(bActive__OBJ_CTRL__HTR_CHUCK)
		{
			if(pOBJ_CTRL__HTR_CHUCK->Is__OBJ_BUSY() > 0)		active__obj_idle = false;
		}
		if(bActive__OBJ_CTRL__HTR_WALL)
		{
			if(pOBJ_CTRL__HTR_WALL->Is__OBJ_BUSY() > 0)			active__obj_idle = false;
		}

		if(active__obj_idle)
		{
			break;
		}
	}

	// Object.Abort Check ...
	{
		if(bActive__OBJ_CTRL__HTR_CHUCK)
		{
			if(HTR_CHUCK_OBJ__Check_ABORTED() > 0)			return -21;
		}
		if(bActive__OBJ_CTRL__HTR_WALL)
		{
			if(HTR_WALL_OBJ__Check_ABORTED() > 0)			return -31;
		}
	}
	return 1;
}
int CObj__STEP_STRIP
::_Fnc__HTR_STABLE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// Chuck.Temperature ...
	if(bActive__OBJ_CTRL__HTR_CHUCK)
	{
		for(int i=0; i<_CFG__CHUCK_SIZE; i++)
		{
			CString rcp__temp    = sCH__RCP_CHUCK_TEMP_X[i]->Get__STRING();
			CString rcp__offset  = sCH__RCP_CHUCK_OFFSET_X[i]->Get__STRING();
			CString rcp__warning = sCH__RCP_CHUCK_WARNING_X[i]->Get__STRING();
			CString rcp__alarm   = sCH__RCP_CHUCK_ALARM_X[i]->Get__STRING();

			double ref__off_temp = atof(rcp__offset);
			double ref__set_temp = atof(rcp__temp) - ref__off_temp;
			double cfg__soft_tol = atof(rcp__warning) * 0.01;
			double cfg__hard_tol = atof(rcp__alarm) * 0.01;

			//
			ch_data.Format("%.1f", ref__set_temp * cfg__soft_tol);
			aEXT_CH__HTR_CHUCK__CFG_PROC_SOFT_TOLERANCE_X[i]->Set__DATA(ch_data);

			ch_data.Format("%.1f", ref__set_temp * cfg__hard_tol);
			aEXT_CH__HTR_CHUCK__CFG_PROC_HARD_TOLERANCE_X[i]->Set__DATA(ch_data);

			//
			ch_data.Format("%.1f", ref__set_temp);
			sEXT_CH__HTR_CHUCK__PARA_PROC_REF_SP_X[i]->Set__DATA(ch_data);
		}

		CString obj_mode = _HTR_CMD__STABLE_CHECK;
		pOBJ_CTRL__HTR_CHUCK->Run__OBJECT(obj_mode);
	}

	// Wall.Temperature ...
	if(bActive__OBJ_CTRL__HTR_WALL)
	{
		CString rcp__main_temp = sCH__RCP_WALL_MAIN_TEMP->Get__STRING();
		CString rcp__offset    = sCH__RCP_WALL_MAIN_OFFSET->Get__STRING();	
		CString rcp__warning   = sCH__RCP_WALL_MAIN_WARNING->Get__STRING();	
		CString rcp__alarm     = sCH__RCP_WALL_MAIN_ALARM->Get__STRING();

		double ref__off_temp = atof(rcp__offset);
		double ref__set_temp = atof(rcp__main_temp) - ref__off_temp;
		double cfg__soft_tol = atof(rcp__warning) * 0.01;
		double cfg__hard_tol = atof(rcp__alarm) * 0.01;

		for(int i=0; i<_CFG__WALL_SIZE; i++)
		{
			ch_data.Format("%.1f", ref__set_temp * cfg__soft_tol);
			aEXT_CH__HTR_WALL__CFG_PROC_SOFT_TOLERANCE_X[i]->Set__DATA(ch_data);

			ch_data.Format("%.1f", ref__set_temp * cfg__hard_tol);
			aEXT_CH__HTR_WALL__CFG_PROC_HARD_TOLERANCE_X[i]->Set__DATA(ch_data);

			//
			ch_data.Format("%.1f", ref__set_temp);
			sEXT_CH__HTR_WALL__PARA_PROC_REF_SP_X[i]->Set__DATA(ch_data);
		}

		CString obj_mode = _HTR_CMD__STABLE_CHECK;
		pOBJ_CTRL__HTR_WALL->Run__OBJECT(obj_mode);
	}

	return 1;
}
