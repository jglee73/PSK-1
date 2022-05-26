#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__STEP_STRIP::CObj__STEP_STRIP()
{

}
CObj__STEP_STRIP::~CObj__STEP_STRIP()
{

}

//-------------------------------------------------------------------------
int CObj__STEP_STRIP::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");

		ADD__CTRL_VAR(sMODE__READY,	"READY");
		ADD__CTRL_VAR(sMODE__START, "START");
		ADD__CTRL_VAR(sMODE__PROC,	"PROC");
		ADD__CTRL_VAR(sMODE__ABORT,	"ABORT");
		ADD__CTRL_VAR(sMODE__END,	"END");
	}
	return 1;
}
int CObj__STEP_STRIP::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__DISABLE_ENABLE					\
"DISABLE ENABLE"

#define  APP_DSP__ENABLE_DISABLE					\
"ENABLE DISABLE"


int CObj__STEP_STRIP::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString var_name;
	CString list_item;
	int i;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);

		var_name = "OBJ.SUB.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_SUB_MSG, var_name);
	}

	// INFO ...
	{
		var_name = "INFO.STEP.CUR_NUM";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STEP_CUR_NUM, var_name);

		var_name = "INFO.STEP.PRE_TIME";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STEP_PRE_TIME, var_name);
	}

	// MON ...
	{
		var_name = "MON.STEP.EXCEPTION.ACT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STEP_EXCEPTION_ACT, var_name);
	}

	// CFG ...
	{
		var_name = "CFG.STEP.ALARM_TEST.ACTIVE";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_ALARM_TEST_ACTIVE, var_name);

		//
		var_name = "CFG.STEP.STABLE.MIN.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_STABLE_MIN_SEC, var_name);

		var_name = "CFG.STEP.OBJECT_OVER_TIME.ERRPR_REF.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 2, 0.05, 1.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_OBJECT_OVER_TIME_ERRPR_REF_SEC, var_name);

		var_name = "CFG.CHM.PRESSURE.HIGH.LIMIT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "torr", 0, 1, 900, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_CHM_PRESSURE_HIGH_LIMIT, var_name);

		//
		var_name = "CFG.STEP_DELAY.RF_OFF";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_RF_OFF, var_name);

		var_name = "CFG.STEP_DELAY.MFC_CLOSE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 1, 0, 2, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_DELAY_MFC_CLOSE, var_name);

		//
		var_name = "CFG.STEP_READY.HEATER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ONLY.CHECK  CONTROL", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_READY_HEATER_MODE, var_name);

		var_name = "CFG.STEP_READY.CHECK.TIME.MIN";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_READY_CHECK_TIME_MIN, var_name);

		var_name = "CFG.STEP_READY.CHECK.TIME.MAX";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "sec", 0, 5, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STEP_READY_CHECK_TIME_MAX, var_name);

		//
		var_name = "CFG.STEP_CTRL.HEATER.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ONLY.CHECK", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_CTRL_HEATER_MODE, var_name);

		var_name = "CFG.STEP_CTRL.ERROR.CONTROL";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, "DISABLE  ENABLE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_STEP_CTRL_ERROR_CONTROL, var_name);
	}

	// RCP ...
	{
		// STEP ...
		{
			var_name = "RCP.STEP.MESSAGE";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_STEP_MESSAGE, var_name);

			var_name = "RCP.STEP.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Time Stable EndPT OverEtch End", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_STEP_MODE, var_name);

			var_name = "RCP.STEP.TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0, 9999, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_TIME, var_name);

			var_name = "RCP.STEP.OVERETCH.PERCENT";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_STEP_OVERETCH_PERCENT, var_name);
		}

		// EPD ...
		{
			var_name = "RCP.EPD.ALGORITHM.ID";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_EPD_ALGORITHM_ID, var_name);

			var_name = "RCP.EPD.ALGORITHM.LIST";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__RCP_EPD_ALGORITHM_LIST, var_name);
		}

		// APC ...
		{
			var_name = "RCP.APC.MODE";		
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "POSITION PRESSURE", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_APC_MODE, var_name);

			var_name = "RCP.APC.PRESSURE.mTORR";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "mtorr", 0, 0.0, 10000.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_PRESSURE_mTORR, var_name);

			var_name = "RCP.APC.POSITION";		
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, 0.0, 100.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_APC_POSITION, var_name);

			//
			var_name = "RCP.APC.LEARNED.POS";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_LEARNED_POS, var_name);

			var_name = "RCP.APC.HOLD.DELAY";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_HOLD_DELAY, var_name);

			var_name = "RCP.APC.TOL.WARNING";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_TOL_WARNING, var_name);

			var_name = "RCP.APC.TOL.ALARM";
			STD__ADD_STRING_WITH_OPTION(var_name, 0, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_APC_TOL_ALARM, var_name);
		}

		// RF_TOP ...
		{
			var_name = "RCP.RF.TOP.POWER";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_TOP_POWER, var_name);

			var_name = "RCP.RF.TOP.TOL.WARNING";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_TOP_TOL_WARNING, var_name);

			var_name = "RCP.RF.TOP.TOL.ALARM";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_RF_TOP_TOL_ALARM, var_name);
		}

		// MAT_TOP ...
		{
			var_name = "RCP.MAT.TOP.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_TOP_SHUNT, var_name);
			
			var_name = "RCP.MAT.TOP.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_TOP_SERIES, var_name);
			
			var_name = "RCP.MAT.TOP.CAPACITY";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_TOP_CAPACITY, var_name);

			//
			var_name = "RCP.MAT.TOP.LEARNED.SHUNT";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_TOP_LEARNED_SHUNT, var_name);

			var_name = "RCP.MAT.TOP.LEARNED.SERIES";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_TOP_LEARNED_SERIES, var_name);

			var_name = "RCP.MAT.TOP.LEARNED.CAPACITY";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_MAT_TOP_LEARNED_CAPACITY, var_name);
		}

		// MFC ...
		for(i=0; i<_CFG__MFC_SIZE; i++)
		{
			var_name.Format("RCP.GAS.%02d.FLOW", i+1);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_GAS_FLOW_X[i], var_name);

			var_name.Format("RCP.GAS.%02d.RAMP.SEC", i+1);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_GAS_RAMP_SEC_X[i], var_name);
		}

		// VAPORIZER ...
		{
			var_name = "RCP.VAPOR.TEMPERATURE";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_VAPOR_TEMPERATURE, var_name);

			var_name = "RCP.VAPOR.VALVE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Close Open Dump", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_VAPOR_VALVE, var_name);

			var_name = "RCP.VAPOR.FLOW";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_VAPOR_FLOW, var_name);
		}

		// CHUCK.TEMPERATURE ...
		for(i=0; i<_CFG__CHUCK_SIZE; i++)
		{
			int id = i + 1;

			var_name.Format("RCP.CHUCK%1d.TEMP", id);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_CHUCK_TEMP_X[i], var_name);

			var_name.Format("RCP.CHUCK%1d.OFFSET", id);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_CHUCK_OFFSET_X[i], var_name);

			var_name.Format("RCP.CHUCK%1d.WARNING", id);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_CHUCK_WARNING_X[i], var_name);

			var_name.Format("RCP.CHUCK%1d.ALARM", id);
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_CHUCK_ALARM_X[i], var_name);
		}

		// WALL.TEMPERATURE ...
		{
			var_name = "RCP.WALL.MAIN.TEMP";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_WALL_MAIN_TEMP, var_name);

			var_name = "RCP.WALL.MAIN.OFFSET";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_WALL_MAIN_OFFSET, var_name);

			var_name = "RCP.WALL.MAIN.WARNING";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_WALL_MAIN_WARNING, var_name);

			var_name = "RCP.WALL.MAIN.ALARM";
			STD__ADD_STRING_WITH_OPTION(var_name, -1, "E", "");
			LINK__VAR_STRING_CTRL(sCH__RCP_WALL_MAIN_ALARM, var_name);
		}

		// LIFT_PIN ...
		{
			var_name = "RCP.LIFT_PIN.MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Down Middle Up", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_LIFT_PIN_MODE, var_name);
		}

		// EPD ...
		{
			list_item = "Idle OverValue.Check UnderValue.Check OverValue.Slope UnderValue.Slope Error.Check ValueChange ValueSlope PercentChange PercentSlope";

			var_name = "RCP.EPD.EPD_MODE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, list_item, -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_EPD_EPD_MODE, var_name);

			//
			var_name = "RCP.EPD.VALUE_TO_CHANGE";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "intensity", 1, -1000, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_VALUE_TO_CHANGE, var_name);

			var_name = "RCP.EPD.PERCENT_TO_CHANGE";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "%", 1, -100, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_PERCENT_TO_CHANGE, var_name);

			//
			var_name = "RCP.EPD.DELAY_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 30, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_DELAY_TIME, var_name);

			var_name = "RCP.EPD.NORMALIZE_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 10, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_NORMALIZE_TIME, var_name);

			//
			var_name = "RCP.EPD.MIN_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MIN_TIME, var_name);

			var_name = "RCP.EPD.MAX_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.0, 100, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MAX_TIME, var_name);

			//
			var_name = "RCP.EPD.MIN_THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "intensity", 1, 0.0, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MIN_THRESHOLD, var_name);

			var_name = "RCP.EPD.MAX_THRESHOLD";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "intensity", 1, 0.0, 1000, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_MAX_THRESHOLD, var_name);

			//
			var_name = "RCP.EPD.SLOPE_VALUE";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "slope", 1, 0.1, 1.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_SLOPE_VALUE, var_name);
			
			var_name = "RCP.EPD.SLOPE_TYPE";
			STD__ADD_DIGITAL_WITH_OPTION(var_name, "Up Down Flat UpToFlat DownToFlat", -1, "E", "");
			LINK__VAR_DIGITAL_CTRL(dCH__RCP_EPD_SLOPE_TYPE, var_name);

			var_name = "RCP.EPD.SLOPE_VALID_TIME";
			STD__ADD_ANALOG_WITH_OPTION(var_name, "sec", 1, 0.5, 5.0, -1, "E", "");
			LINK__VAR_ANALOG_CTRL(aCH__RCP_EPD_SLOPE_VALID_TIME, var_name);
		}
	}

	return 1;
}

int CObj__STEP_STRIP::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__STEP_OVERTIME;

		alarm_title  = title;
		alarm_title += "STEP OVERTIME ALARM.";

		alarm_msg  = "Process Step Time-Over Alarm Message.\n";
		alarm_msg += "Check Process Step time and Control time.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STABLE_OVERTIME;

		alarm_title  = title;
		alarm_title += "STABLE OVERTIME ALARM.";

		alarm_msg = "Process Stable Step Time-over Alarm Message.\n";
		alarm_msg += "Check Process Stable Step time and Control time.";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__OBJECT_OVERTIME;

		alarm_title  = title;
		alarm_title += "OBJECT OVERTIME ALARM.";

		alarm_msg  = "Object control time must be less than process step time ! \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STEP_READY__TEMPERATURE_STABLE_TIMEOUT_ERROR;

		alarm_title  = title;
		alarm_title += "Temperature stable timeout error In the step preparation.";

		alarm_msg = "Please, check the current temperature of system and temperature parameter in 1st step recipe ! \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__STEP_READY__TEMPERATURE_STABLE_TIMEOUT_WARNING;

		alarm_title  = title;
		alarm_title += "Temperature stable timeout warning In the step preparation.";

		alarm_msg = "Please, check the current temperature of system and temperature parameter in 1st step recipe ! \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__STEP_PARAMETER__SETTING_ERROR;

		alarm_title  = title;
		alarm_title += "Step parameter setting error !";

		alarm_msg = "Please, check the step parameter in recipe. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CLEAR);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__STEP_STRIP::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_STRIP::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;
	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log",sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// DB INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		//
		var_name = "SLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SLOT01_STATUS, obj_name,var_name);

		var_name = "SLOT01.LOTID";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_LOTID, obj_name,var_name);
	}

	// OBJ APC ...
	{
		def_name = "OBJ__APC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__APC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__APC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.PRESSURE";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_PRESSURE, obj_name,var_name);

			var_name = "PARA.POSITION";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_POSITION, obj_name,var_name);

			var_name = "PARA.HOLD.SEC";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__PARA_HOLD_SEC, obj_name,var_name);

			//
			var_name = "MON.PRESSURE.TORR";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__APC_OBJ__MON_PRESSURE_TORR, obj_name,var_name);

			//
			var_name = "CFG.PRESSURE.WARNING.BAND";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__CFG_PROC_PRESSURE_WARNING_BAND, obj_name,var_name);

			var_name = "CFG.PRESSURE.ABORT.BAND";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__APC_OBJ__CFG_PROC_PRESSURE_ABORT_BAND, obj_name,var_name);

			//
			var_name = "MON.PROC.PRESSURE.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PROC.PRESSURE.STABLE.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_STABLE_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.IDLE.PRESSURE.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_IDLE_PRESSURE_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.IDLE.PRESSURE.STABLE.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__APC_OBJ__MON_IDLE_PRESSURE_STABLE_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ PT_X ...
	{
		def_name = "DATA.PT_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iDATA__PT_SIZE = atoi(def_data);
		if(iDATA__PT_SIZE > _CFG__PT_SIZE)			iDATA__PT_SIZE = _CFG__PT_SIZE;

		for(i=0; i<iDATA__PT_SIZE; i++)
		{
			def_name.Format("CH__PT_ERROR.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);

			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PT_X__MON_ABORT_ACTIVE[i], obj_name,var_name);
		}
	}

	// OBJ RF_TOP ...
	{
		def_name = "OBJ__RF_TOP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__RF_TOP = def_check;

		if(def_check)
		{
			pOBJ_CTRL__RF_TOP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.POWER";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_TOP__PARA_SET_POWER, obj_name,var_name);

			var_name = "PARA.HOLD.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_TOP__PARA_HOLD_TIME, obj_name,var_name);

			//
			var_name = "CFG.PROC.POWER.WARNING.BAND";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_TOP__CFG_PROC_POWER_WARNING_BAND, obj_name,var_name);

			var_name = "CFG.PROC.POWER.ABORT.BAND";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__RF_TOP__CFG_PROC_POWER_ABORT_BAND, obj_name,var_name);

			//
			var_name = "MON.IDLE.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_TOP__MON_IDLE_POWER_ABORT_ACTIVE, obj_name,var_name);

			var_name = "MON.PROC.POWER.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_TOP__MON_PROC_POWER_ABORT_ACTIVE, obj_name,var_name);

			//
			var_name = "MON.REFLECT.HIGH_LIMIT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_TOP__MON_REFLECT_HIGH_LIMIT_ACTIVE, obj_name,var_name);

			var_name = "MON.REFLECT.MAX_COEFFICIENT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_TOP__MON_REFLECT_MAX_COEFFICIENT_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ MATCHER ...
	{
		def_name = "OBJ__MATCHER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__MAT = def_check;

		if(def_check)
		{
			pOBJ_CTRL__MAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.LOAD_POS.CH1";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT__PARA_LOAD_POS_CH1, obj_name,var_name);

			var_name = "PARA.LOAD_POS.CH2";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT__PARA_LOAD_POS_CH2, obj_name,var_name);

			//
			var_name = "PARA.TUNE_POS.CH1";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT__PARA_TUNE_POS_CH1, obj_name,var_name);

			var_name = "PARA.TUNE_POS.CH2";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT__PARA_TUNE_POS_CH2, obj_name,var_name);

			//
			var_name = "PARA.CAP_POS.CH1";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT__PARA_CAP_POS_CH1, obj_name,var_name);

			var_name = "PARA.CAP_POS.CH2";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__MAT__PARA_CAP_POS_CH2, obj_name,var_name);
		}
	}

	// OBJ MFC_X ...
	{
		def_name = "DATA.MFC_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iDATA__MFC_SIZE = atoi(def_data);
		if(iDATA__MFC_SIZE > _CFG__MFC_SIZE)		iDATA__MFC_SIZE = _CFG__MFC_SIZE;

		for(i=0; i<iDATA__MFC_SIZE; i++)
		{
			def_name.Format("OBJ__MFC.%02d", i+1);
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

			pOBJ_CTRL__MFC_X[i] = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_X__PARA_SET_FLOW[i], obj_name,var_name);

			var_name = "PARA.RAMP.SEC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MFC_X__PARA_RAMP_SEC[i], obj_name,var_name);

			//
			var_name = "MON.MFC.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MFC_X__MON_MFC_ABORT_ACTIVE[i], obj_name,var_name);
		}
	}

	// OBJ LFC ...
	{
		def_name = "OBJ__LFC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__LFC = def_check;

		if(def_check)
		{
			pOBJ_CTRL__LFC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.SET.FLOW";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LFC__PARA_SET_FLOW, obj_name,var_name);

			var_name = "PARA.RAMP.SEC";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LFC__PARA_RAMP_SEC, obj_name,var_name);

			//
			var_name = "MON.LFC.ABORT.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LFC__MON_LFC_ABORT_ACTIVE, obj_name,var_name);
		}
	}

	// OBJ LIFT_PIN ...
	{
		def_name = "OBJ__LIFT_PIN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__LIFT_PIN = def_check;

		if(def_check)
		{
			pOBJ_CTRL__LIFT_PIN = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}
	}

	// OBJ__HTR_CHUCK ...
	{
		def_name = "OBJ__HTR_CHUCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__HTR_CHUCK = def_check;

		if(def_check)
		{
			pOBJ_CTRL__HTR_CHUCK = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			for(i=0; i<_CFG__CHUCK_SIZE; i++)
			{
				int id = i+1;

				//
				var_name.Format("PARA.PROC.REF.SP.%02d", id);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__HTR_CHUCK__PARA_PROC_REF_SP_X[i], obj_name,var_name);

				var_name.Format("PARA.TARGET.SP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_CHUCK__PARA_TARGET_SP_X[i], obj_name,var_name);

				//
				var_name.Format("MON.IDLE.STABLE.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_CHUCK__MON_IDLE_STABLE_ACTIVE_X[i], obj_name,var_name);

				var_name.Format("MON.IDLE.ABORT.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_CHUCK__MON_IDLE_ABORT_ACTIVE_X[i], obj_name,var_name);

				//
				var_name.Format("MON.PROC.STABLE.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_CHUCK__MON_PROC_STABLE_ACTIVE_X[i], obj_name,var_name);

				var_name.Format("MON.PROC.ABORT.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_CHUCK__MON_PROC_ABORT_ACTIVE_X[i], obj_name,var_name);

				//
				var_name.Format("CFG.PROC.SOFT.TOLERANCE.THRESHOLD.LOOP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_CHUCK__CFG_PROC_SOFT_TOLERANCE_X[i], obj_name,var_name);

				var_name.Format("CFG.PROC.HARD.TOLERANCE.THRESHOLD.LOOP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_CHUCK__CFG_PROC_HARD_TOLERANCE_X[i], obj_name,var_name);

				//
				var_name.Format("MON.IO.GET.PV.LOOP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_CHUCK__MON_IO_PV_X[i], obj_name,var_name);
			}
		}
	}
	// OBJ__HTR_WALL ...
	{
		def_name = "OBJ__HTR_WALL";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__HTR_WALL = def_check;

		if(def_check)
		{
			pOBJ_CTRL__HTR_WALL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			for(i=0; i<_CFG__WALL_SIZE; i++)
			{
				int id = i+1;

				//
				var_name.Format("PARA.PROC.REF.SP.%02d", id);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__HTR_WALL__PARA_PROC_REF_SP_X[i], obj_name,var_name);

				var_name.Format("PARA.TARGET.SP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_WALL__PARA_TARGET_SP_X[i], obj_name,var_name);

				//
				var_name.Format("MON.IDLE.STABLE.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_WALL__MON_IDLE_STABLE_ACTIVE_X[i], obj_name,var_name);

				var_name.Format("MON.IDLE.ABORT.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_WALL__MON_IDLE_ABORT_ACTIVE_X[i], obj_name,var_name);

				//
				var_name.Format("MON.PROC.STABLE.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_WALL__MON_PROC_STABLE_ACTIVE_X[i], obj_name,var_name);

				var_name.Format("MON.PROC.ABORT.ACTIVE.LOOP.%02d", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__HTR_WALL__MON_PROC_ABORT_ACTIVE_X[i], obj_name,var_name);

				//
				var_name.Format("CFG.PROC.SOFT.TOLERANCE.THRESHOLD.LOOP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_WALL__CFG_PROC_SOFT_TOLERANCE_X[i], obj_name,var_name);

				var_name.Format("CFG.PROC.HARD.TOLERANCE.THRESHOLD.LOOP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_WALL__CFG_PROC_HARD_TOLERANCE_X[i], obj_name,var_name);

				//
				var_name.Format("MON.IO.GET.PV.LOOP.%02d", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HTR_WALL__MON_IO_PV_X[i], obj_name,var_name);
			}
		}
	}

	// OBJ.EPD ...
	{
		def_name = "OBJ__EPD";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__OBJ_CTRL__EPD = def_check;

		if(def_check)
		{
			pOBJ_CTRL__EPD = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "PARA.EPD.MODE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__EPD__PARA_EPD_MODE, obj_name,var_name);

			//
			var_name = "PARA.VALUE_TO_CHANGE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_VALUE_TO_CHANGE, obj_name,var_name);

			var_name = "PARA.PERCENT_TO_CHANGE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_PERCENT_TO_CHANGE, obj_name,var_name);

			//
			var_name = "PARA.DELAY.TIME";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD__PARA_DELAY_TIME, obj_name,var_name);

			var_name = "PARA.NORMALIZE_TIME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_NORMALIZE_TIME, obj_name,var_name);

			//
			var_name = "PARA.EPD.TIMEOUT.MINIMUM";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD__PARA_EPD_TIMEOUT_MINIMUM, obj_name,var_name);
			
			var_name = "PARA.EPD.TIMEOUT.MAXIMUM";
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__EPD__PARA_EPD_TIMEOUT_MAXIMUM, obj_name,var_name);
			
			//
			var_name = "PARA.EPD.THRESHOLD.MIN";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_EPD_THRESHOLD_MIN, obj_name,var_name);
			
			var_name = "PARA.EPD.THRESHOLD.MAX";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_EPD_THRESHOLD_MAX, obj_name,var_name);
	
			//
			var_name = "PARA.SLOPE_COUNT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_SLOPE_COUNT, obj_name,var_name);

			var_name = "PARA.SLOPE_DIRECTION";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_SLOPE_DIRECTION, obj_name,var_name);

			var_name = "PARA.VALID_TIME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__EPD__PARA_VALID_TIME, obj_name,var_name);

			//
			var_name = "MON.IDLE.INTENSITY.ERROR.ACTIVE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__EPD__MON_ERROR_ACTIVE, obj_name,var_name);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// ...
	{
		CString str_list = "IDLE/AAA/BBB/CCC/Test.01";

		sCH__RCP_EPD_ALGORITHM_LIST->Set__DATA(str_list);
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__STEP_STRIP::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		xLOG_CTRL->WRITE__LOG(log_msg);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		sCH__OBJ_SUB_MSG->Set__DATA("");
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__READY)
		{
			flag = Call__READY(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__START)
		{
			flag = Call__START(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PROC)
		{
			flag = Call__PROC(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT)
		{
			flag = Call__ABORT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__END)
		{
			flag = Call__END(p_variable,p_alarm);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("[%s] Aborted ... [%d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);	
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("[%s] Completed .. [%d]", mode,flag);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	return flag;
}

int CObj__STEP_STRIP::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
