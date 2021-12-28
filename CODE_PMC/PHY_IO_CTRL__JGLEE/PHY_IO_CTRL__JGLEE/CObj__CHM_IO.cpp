#include "StdAfx.h"
#include "CObj__CHM_IO.h"
#include "CObj__CHM_IO__ALID.h"


//-------------------------------------------------------------------------
CObj__CHM_IO::CObj__CHM_IO()
{

}
CObj__CHM_IO::~CObj__CHM_IO()
{

}

//-------------------------------------------------------------------------
int CObj__CHM_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
	}
	return 1;
}
int CObj__CHM_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATUS							1


int CObj__CHM_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;

	// ...
	{
		str_name = "APP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "APP.OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATUS);
	}
	return 1;
}

int CObj__CHM_IO::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__MONITORING_INTERLOCK__DISABLE;

		alarm_title  = title;
		alarm_title += "Monitoring Interlock Disable !";

		alarm_msg  = "Config Page에서 Monitoring Interlock를 Disable 설정했습니다.\n";
		alarm_msg += "이 Object에서 관리하는 모든 Monitoring Alarm들이 정지 됩니다.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__CHM_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
	CString ch_name;
	CString obj_name;
	CString var_name;

	// OBJ DB_INF ...
	{
		def_name = "OBJ__DB_INF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "CHM.PRESSURE.VALUE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_VALUE, obj_name,var_name);

		var_name = "CHM.PRESSURE.mTORR";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_PRESSURE_mTORR, obj_name,var_name);

		//
		var_name = "CHM.VAC.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_VAC_SNS, obj_name,var_name);

		var_name = "CHM.ATM.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CHM_ATM_SNS, obj_name,var_name);

		//
		var_name = "PMP.PRESSURE.VALUE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_PRESSURE_VALUE, obj_name,var_name);

		var_name = "PMP.PRESSURE.STATE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_PRESSURE_STATE, obj_name,var_name);

		var_name = "PMP.VAC.SNS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PMP_VAC_SNS, obj_name,var_name);
	}

	// OBJ DB_SYS ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		//
		var_name = "CFG.INTERLOCK.USE.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_USE_MODE, obj_name,var_name);

		var_name = "CFG.INTERLOCK.USE.CHM_MANOMETER_ISO";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_INTERLOCK_USE__CHM_MANOMETER_ISO, obj_name,var_name);

		//
		var_name = "SIM.PRESSURE.TORR";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SIM_PRESSURE_TORR, obj_name,var_name);

		//
		var_name = "SYSTEM.SETUP.REQ";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_SETUP_REQ, obj_name,var_name);

		//
		var_name = "CFG.PROCESS.MANOMETER.MAX.PRESSURE.mTORR";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR, obj_name,var_name);

		var_name = "CFG.PROCESS.MANOMETER.ISO.PRESSURE.mTORR";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_PROCESS_MANOMETER_ISO_PRESSURE_mTORR, obj_name,var_name);
	}

	// LINK : IO_Chammel
	{
		def_name = "CH__DI_VAC_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_VAC_SNS, obj_name,var_name);

		def_name = "CH__DI_ATM_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_ATM_SNS, obj_name,var_name);

		//
		def_name = "CH__DO_MANOMETER_ISO_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_MANOMETER_ISO_VLV, obj_name,var_name);
		
		def_name = "CH__AI_MANOMETER_TORR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_MANOMETER_TORR, obj_name,var_name);

		def_name = "CH__AI_FORELINE_PRESSURE_TORR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__AI_FORELINE_PRESSURE_TORR, obj_name,var_name);
	}

	// LINK : State Channel
	{
		def_name = "CH__PROC_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PROC_STATE, obj_name,var_name);

		//
		def_name = "CH__RF_ON_STATE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RF_ON_STATE, obj_name,var_name);

		def_name = "CH__HF_RF_POWER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__HF_RF_POWER, obj_name,var_name);

		def_name = "CH__LF_RF_POWER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__LF_RF_POWER, obj_name,var_name);

		def_name = "CH__BIAS_RF_POWER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__BIAS_RF_POWER, obj_name,var_name);
	}

	// ...
	{
		SCX__SEQ_INFO seq_info;

		if(seq_info->Is__SIMULATION_MODE() > 0)			iSIM_MODE =  1;
		else											iSIM_MODE = -1;
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__CHM_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
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

		else									
		{
			CString log_msg;
			log_msg.Format("Invalid Mode: [%s]", mode);
			flag = -1;
		}
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

int CObj__CHM_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATUS)		Mon__STATUS(p_variable, p_alarm);

	return 1;
}
