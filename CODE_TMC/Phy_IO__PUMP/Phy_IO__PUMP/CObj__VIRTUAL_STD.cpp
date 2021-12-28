#include "StdAfx.h"

#include "CObj__VIRTUAL_STD.h"
#include "CObj__VIRTUAL_STD__DEF.h"


//--------------------------------------------------------------------------------
CObj__VIRTUAL_STD::CObj__VIRTUAL_STD()
{

}
CObj__VIRTUAL_STD::~CObj__VIRTUAL_STD()
{

}

//--------------------------------------------------------------------------------
int CObj__VIRTUAL_STD::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	   "INIT");
		ADD__CTRL_VAR(sMODE__PUMP_ON,  "PUMP_ON");
		ADD__CTRL_VAR(sMODE__PUMP_OFF, "PUMP_OFF");
	}
	return 1;
}
int CObj__VIRTUAL_STD::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR						2
#define  MON_ID__WATER_LEAK_MONITOR				3


int CObj__VIRTUAL_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	CString str_name;
	CString dsc_item_list;

	// ...
	p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS",dsc_item_list);

	str_name = "OBJ.STATUS";
	STD__ADD_DIGITAL_WITH_COMMENT(str_name,dsc_item_list,"");
	LINK__VAR_DIGITAL_CTRL(dCH__OBJ_STATUS,str_name);

	// ...
	str_name = "INR.sMSG";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__SEQUENCE_MSG,str_name);

	str_name = "sAPP.COMM.STS";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__COMM_STS,str_name);

	str_name = "OTR.OUT.MON.sPUMP.STS";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__PUMP_STS,str_name);

	// ...
	str_name = "OTR.IN.CFG.aPUMP.ON.TIME.DELAY";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec", 0, 0, 600, "");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_PUMP_ON_DELAY_TIME,str_name);

	// ...
	str_name = "OTR.IN.CFG.aPUMP.ON.OFF.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec", 0, 0, 600, "");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_PUMP_ON_OFF_TIMEOUT,str_name);

	// ...
	str_name = "OTR.IN.sPUMP.ON.DELAY.TIME.DISPLAY";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__PUMP_ON_TIME_COUNT,str_name);

	// ...
	str_name = "CFG.dPUMP.ON.SIGNAL.CHECK.SKIP";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCFG_CH__PUMP_ON_SIGNAL_CHK_SKIP,str_name);

	// ...
	str_name = "CFG.dPUMP.WATER.LEAK.DETECT.PUMP.OFF";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCFG_CH__WATER_LEAK_DETECT_PUMP_OFF,str_name);


	// ...
	{
		p_variable->Add__MONITORING_PROC(7.0, MON_ID__IO_MONITOR);
		p_variable->Add__MONITORING_PROC(7.0, MON_ID__WATER_LEAK_MONITOR);
	}
	return 1;
}

int CObj__VIRTUAL_STD::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Offline.";

		alarm_msg  = "Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_POWER_OFF__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Power Off TimeOut.";

		alarm_msg  = "Power Sensor -> Off : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_POWER_ON__TIMEOUT;

		alarm_title  = title;
		alarm_title += "Pump Power On TimeOut.";

		alarm_msg  = "Power Sensor -> On : Timeout.\n";
		alarm_msg += "Please, Check Pump Status !\n";

		l_act.RemoveAll();
		l_act.Add("RETRY");
		l_act.Add("ABORT");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__BEFORE_PUMP_ON_ALARM_STS;

		alarm_title  = title;
		alarm_title += "Now... Pump is Alarm Status.";

		alarm_msg   = "Before Pump on, You must remove alarm status.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK_RETRY");
		l_act.Add("ABORT");
		l_act.Add("IGNORE");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__WATER_LEAK_DETECT_PUMP_OFF_ALARM;

		alarm_title  = title;
		alarm_title += "Now... IPX Pump Water Leak Detect Status.";

		alarm_msg   = "IPX Pump Will Be Off.\n";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VIRTUAL_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	CString obj_name;
	CString var_name;

	// IO
	{
		//
		str_name = "VAR__IO_DI_COMM_STS";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_IO_COMM_STS, obj_name, var_name);

		str_name = "VAR__IO_DI_PUMP_RUNNING";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_RUN_STS, obj_name, var_name);

		//
		str_name = "VAR__IO_DI_PUMP_WARNING";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_WARNING_STS, obj_name, var_name);

		//
		str_name = "VAR__IO_DI_PUMP_ALARM";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_ALARM_STS, obj_name, var_name);

		//
		str_name = "VAR__IO_DI_PUMP_WATER_FLOW";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_WATER_FLOW_STS, obj_name, var_name);

		//
		str_name = "VAR__IO_DI_PUMP_LEAK_DETECT";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PUMP_LEAK_DETECT_STS, obj_name, var_name);

		//
		str_name = "VAR__IO_DO_PUMP_ON_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(str_name, def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_PUMP_ON_OFF, obj_name, var_name);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		if(x_seq_info->Is__SIMULATION_MODE() > 0)
		{
			iSim_Flag = 1;
		}
		else
		{
			iSim_Flag = -1;
		}
	}

	iFlag__APP_LOG = 1;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xAPP_LOG_CTRL->DISABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);

		xAPP_LOG_CTRL->ENABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		dEXT_CH__DI_PUMP_RUN_STS->Link__UPPER_OBJECT_ABORT(sObject_Name);
		dEXT_CH__DI_PUMP_RUN_STS->Enable__UPPER_OBJECT_ABORT_CHECK();
	}
	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VIRTUAL_STD::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	m_xAsncTimer->REGISTER__COUNT_CHANNEL_NAME(sCH__PUMP_ON_TIME_COUNT->Get__CHANNEL_NAME());

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_ON)		flag = Call__PUMP_ON(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_OFF)		flag = Call__PUMP_OFF(p_variable,p_alarm);

		else									
		{

		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__SEQUENCE_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	m_xAsncTimer->STOP();
	return flag;
}

int CObj__VIRTUAL_STD::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;

		case MON_ID__WATER_LEAK_MONITOR:
			Mon__WATER_LEAK_DETECT_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
