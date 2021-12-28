#include "StdAfx.h"
#include "CObj__TMP_IO.h"
#include "CObj__TMP_IO__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__TMP_IO::CObj__TMP_IO()
{

}
CObj__TMP_IO::~CObj__TMP_IO()
{

}

//-------------------------------------------------------------------------
int CObj__TMP_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__FULL_CLOSE, "FULL_CLOSE");
		ADD__CTRL_VAR(sMODE__FULL_OPEN,  "FULL_OPEN");

		ADD__CTRL_VAR(sMODE__EXHAUST_CLOSE, "EXHAUST_CLOSE");
		ADD__CTRL_VAR(sMODE__EXHAUST_OPEN,  "EXHAUST_OPEN");

		ADD__CTRL_VAR(sMODE__ON,  "ON");
		ADD__CTRL_VAR(sMODE__OFF, "OFF");
		ADD__CTRL_VAR(sMODE__OFF_NO_WAIT, "OFF_NO_WAIT");	
	}
	return 1;
}
int CObj__TMP_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1


int CObj__TMP_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STATE, str_name);

		str_name = "MON.PUMP.ON.SNS";
		STD__ADD_DIGITAL(str_name, "Off On");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PUMP_ON_SNS, str_name);

		str_name = "MON.PUMP.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMP_STATE, str_name);

		str_name = "MON.ERROR.STATE";
		STD__ADD_DIGITAL(str_name, "Off On");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ERROR_STATE, str_name);

		str_name = "MON.PUMP.RPM.VALUE";
		STD__ADD_ANALOG(str_name, "rpm", 1, 0.0, 50000.0);
		LINK__VAR_ANALOG_CTRL(aCH__MON_PUMP_RPM_VALUE, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.STOP.ERR.DELAY";	
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, -1, 60*60, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_STOP_ERR_DELAY,str_name);

		str_name = "CFG.TURBO.EXHAUST.VALVE.CLOSE.DELAY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TURBO_EXHAUST_VALVE_CLOSE_DELAY, str_name);

		str_name = "CFG.TURBO.N2.PURGE.CLOSE.DELAY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TURBO_N2_PURGE_CLOSE_DELAY, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
	}
	return 1;
}

int CObj__TMP_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__FORLINE_PRESSURE_UNSTABLE_ALARM;

		alarm_title  = title;
		alarm_title += "Forline Pressure Unstable Alarm !";

		alarm_msg  = "Forline Pressure Unstable Status\n";
		alarm_msg += "Check the Forline Vac Switch and Dry Pump On Status!\n";
		alarm_msg += "Now... Turbo Pump will be off..";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_STATE_ERROR;

		alarm_title  = title;
		alarm_title += "The state of TMP or dry-pump is error !";

		alarm_msg = "Check the state of TMP or dry-pump !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TMP_ON_ERROR;

		alarm_title  = title;
		alarm_title += "TMP�� On �� �� �����ϴ� !";

		alarm_msg = "���� Sensor ���¸� Ȯ�� �ٶ��ϴ�. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMP_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// TMP.OBJ  ...
	{
		def_name = "OBJ__TMP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__TMP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		def_name = "TMP_MODE.START";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		sTMP_MODE__START = def_data;
		
		//
		def_name = "TMP_MODE.STOP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		
		sTMP_MODE__STOP = def_data;

		//
		def_name = "TMP_MODE.STOP_NO_WAIT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		sTMP_MODE__STOP_NO_WAIT = def_data;
	}
	// TMP.IO ...
	{
		// DI.COMM_STATE ...
		{
			def_name = "CH__TMP_DI_COMM_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_COMM_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_COMM_STATE, obj_name,var_name);
			}
		}
		// DI.PUMP_STATE ...
		{
			def_name = "CH__TMP_DI_PUMP_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_PUMP_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_PUMP_STATE, obj_name,var_name);
			}
		}
		// DI.ERROR_STATE ...
		{
			def_name = "CH__TMP_DI_ERROR_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_ERROR_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_ERROR_STATE, obj_name,var_name);
			}
		}

		// AI.ROT_RPM ...
		{
			def_name = "CH__TMP_AI_ROT_RPM";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_AI_ROT_RPM = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__TMP_AI_ROT_RPM, obj_name,var_name);
			}
		}
	}

	// OBJ : VAT ...
	{
		def_name = "OBJ__VAT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__VAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}

	// LINK : IO ...
	{
		// DI.FORELINE_VAC_SNS ...
		{
			def_name = "CH__DI_FORELINE_VAC_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_FORELINE_VAC_SNS = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_FORELINE_VAC_SNS, obj_name,var_name);
			}
		}
		// DI.DRY_PUMP_ON ...
		{
			def_name = "CH__DI_DRY_PUMP_ON";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		
			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_DRY_PUMP_ON = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_DRY_PUMP_ON, obj_name,var_name);
			}
		}

		// DO.TMP_EXHAUST_VALVE ...
		{
			def_name = "CH__DO_TMP_EXHAUST_VALVE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DO_TMP_EXHAUST_VALVE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_TMP_EXHAUST_VALVE, obj_name,var_name);
			}
		}
		// DO.TMP_N2_VALVE ...
		{
			def_name = "CH__DO_TMP_N2_VALVE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DO_TMP_N2_VALVE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_TMP_N2_VALVE, obj_name,var_name);
			}
		}
	}

	// ...
	{
		sCH__OBJ_STATUS->Set__DATA("STANDBY");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMP_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__FULL_CLOSE)		flag = Call__FULL_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__FULL_OPEN)		flag = Call__FULL_OPEN(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_CLOSE)	flag = Call__EXHAUST_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_OPEN)		flag = Call__EXHAUST_OPEN(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ON)				flag = Call__ON(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__OFF)				flag = Call__OFF(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__OFF_NO_WAIT)		flag = Call__OFF(p_variable, p_alarm, true);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__TMP_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}