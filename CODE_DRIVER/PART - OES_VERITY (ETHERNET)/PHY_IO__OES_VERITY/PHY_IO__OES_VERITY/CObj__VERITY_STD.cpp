#include "stdafx.h"

#include "CObj__VERITY_STD__ALID.h"
#include "CObj__VERITY_STD.h"


//--------------------------------------------------------------------------------
CObj__VERITY_STD::CObj__VERITY_STD()
{

}
CObj__VERITY_STD::~CObj__VERITY_STD()
{

}

//--------------------------------------------------------------------------------
int CObj__VERITY_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__COMM_TEST, "COMM.TEST");

		ADD__CTRL_VAR(sMODE__CFG_LIST,     "CFG.LIST");
		ADD__CTRL_VAR(sMODE__CFG_VALIDATE, "CFG.VALIDATE");

		ADD__CTRL_VAR(sMODE__WAFER_INFO, "WAFER.INFO");

		ADD__CTRL_VAR(sMODE__STEP_START, "STEP.START");
		ADD__CTRL_VAR(sMODE__STEP_STOP,  "STEP.STOP");
		ADD__CTRL_VAR(sMODE__COMPLETE,   "COMPLETE");

		ADD__CTRL_VAR(sMODE__GET_NET_BUUFER, "GET.NET_BUFFER");
	}
	return 1;
}
int CObj__VERITY_STD::__DEFINE__VERSION_HISTORY(version)
{
	version = "\n";

	return 1;
}

// ...
#define _MON_ID__IO_MONITORING								1
#define _MON_ID__DRV_PROC									2


int CObj__VERITY_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString var_name;
	int i;

	// OBJ ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);
	}

	// MON ...
	{
		var_name = "MON.COMM.STATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STATE, var_name);

		//
		var_name = "MON.ACTIVE.NOTREADY";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ACTIVE_NOTREADY, var_name);

		var_name = "MON.ACTIVE.READY";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ACTIVE_READY, var_name);

		var_name = "MON.ACTIVE.ENDPOINT";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ACTIVE_ENDPOINT, var_name);

		//
		var_name = "MON.WAVE.INTENSITY.VALUE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WAVE_INTENSITY_VALUE, var_name);
	}

	// PARA ...
	{
		var_name = "PARA.CONNECT.INFO";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_CONNECT_INFO, var_name);

		var_name = "PARA.CFG_VALIDATE.INFO";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_CFG_VALIDATE_INFO, var_name);

		var_name = "PARA.STEP_START.CFG_NAME";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_STEP_START_CFG_NAME, var_name);

		//
		var_name = "PARA.WAFER.LOTID";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_WAFER_LOTID, var_name);

		var_name = "PARA.WAFER.SLOTID";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_WAFER_SLOTID, var_name);

		var_name = "PARA.WAFER.CSTID";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_WAFER_CSTID, var_name);

		var_name = "PARA.WAFER.ID";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_WAFER_ID, var_name);

		var_name = "PARA.WAFER.RECIPE";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_WAFER_RECIPE, var_name);

		var_name = "PARA.WAFER.STEP";
		STD__ADD_STRING_WITH_X_OPTION(var_name, "");
		LINK__VAR_STRING_CTRL(sCH__PARA_WAFER_STEP, var_name);

		//
		var_name = "PARA.ACTIVE.NET_BUFFER.CHECK";
		STD__ADD_DIGITAL(var_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_ACTIVE_NET_BUFFER_CHECK, var_name);
	}

	// INFO ...
	{
		//
		{
			var_name = "INFO.VERSION";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_VERSION, var_name);

			//
			var_name = "INFO.CFG_LIST.STR";
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_CFG_LIST_STR, var_name);
		}

		for(i=0; i<_SIZE__CFG_LIST; i++)
		{
			int id = i +1;

			var_name.Format("INFO.CFG.NAME.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_CFG_NAME_X[i], var_name);

			var_name.Format("INFO.CFG.DATE.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_CFG_DATE_X[i], var_name);

			var_name.Format("INFO.CFG.SIZE.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_CFG_SIZE_X[i], var_name);
		}
	}

	// INFO.DRV ...
	{
		var_name = "INFO.DRV.CONTROL.STS";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_CONTROL_STS, var_name);

		//
		var_name = "INFO_DRV.VERSION.STS";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_VERSION_STS, var_name);

		var_name = "INFO_DRV.CFG_LIST.STS";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_CFG_LIST_STS, var_name);

		//
		var_name = "INFO.DRV.WAFER_INFO.STS";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_WAFER_INFO_STS, var_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3, _MON_ID__IO_MONITORING);
		p_variable->Add__MONITORING_PROC(1, _MON_ID__DRV_PROC);
	}
	return 1;
}
int CObj__VERITY_STD::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;
	
	CString str_name;
	CString str_list;

	// DO ...
	{
		str_name = "do.Control.SET";
		IO__ADD_DIGITAL_WRITE(str_name, "Connect Comm.Test Reset Start Stop Complete Cfg.Validate");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__Control_SET, str_name);

		//
		str_name = "do.VERSION.REQ";
		IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__VERSION_REQ, str_name);

		str_name = "do.CFG_LIST.REQ";
		IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CFG_LIST_REQ, str_name);

		//
		str_name = "do.WAFER_INFO.SET";
		IO__ADD_DIGITAL_WRITE(str_name, "OFF ON");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__WAFER_INFO_SET, str_name);
	}
	return 1;
}

int CObj__VERITY_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__OFFLINE;

		alarm_title  = title;
		alarm_title += "Communication Offline !";

		alarm_msg = "Please, check Communication State. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__SS_FAIL;

		alarm_title  = title;
		alarm_title += "SS Fail !";

		alarm_msg = "Please, check VTY. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__NET_BODY_TIMEOUT;

		alarm_title  = title;
		alarm_title += "Body Data Timeout !";

		alarm_msg = "Please, check VTY. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__VERITY_STD
::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s-APP.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		// ...
		{
			mX__Log_Ctrl->CREATE__SUB_DIRECTORY(sObject_Name);
			mX__Log_Ctrl->SET__PROPERTY(file_name,24*5,60);

			mX__Log_Ctrl->DISABLE__TIME_LOG();
			mX__Log_Ctrl->WRITE__LOG(log_msg);

			mX__Log_Ctrl->ENABLE__TIME_LOG();
			mX__Log_Ctrl->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__VERITY_STD
::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter
	//------------------------------------------------------

	CString net_ip   = "127.0.0.1";
	CString net_port = "10001";

	// ...
	{
		CString para_cmmd;
		CString para_data;

		// 1. IP
		{
			para_cmmd = "IP";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_ip = para_data;

			}
		}
		// 2. Port
		{
			para_cmmd = "PORT";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_port = para_data;
			}
		}		
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		// ...
		{
			log_msg = "Connect to Ethernet ... \n";

			log_bff.Format("Net_IP : %s \n", net_ip);
			log_msg += log_bff;

			log_bff.Format("Net_Port : %s \n", net_port);
			log_msg += log_bff;

			log_bff.Format("End_String(Out) : %s \n", mX__Net_Client->GET__TERMINAL_InSTRING());
			log_msg += log_bff;

			log_bff.Format("End_String(In ) : %s \n", mX__Net_Client->GET__TERMINAL_OutSTRING());
			log_msg += log_bff;
		}

		if(iActive__SIM_MODE > 0)
		{
			log_msg += "\n";
			log_msg += "Simulation Mode ! \n";
		}
		else
		{
			CString err_msg;
		
			mX__Net_Client->SET__TERMINAL_InSTRING("",  0);
			mX__Net_Client->SET__TERMINAL_OutSTRING("", 0);
			mX__Net_Client->SET__ETHERNET_TYPE__CLIENT();

			mX__Net_Client->INIT__PROPERTY(net_ip, atoi(net_port));

			if(mX__Net_Client->CONNECT(&err_msg) < 0)
			{
				log_bff.Format("Fail to do INIT__ETHERNET: %s(%s), ret(-1) \n", net_ip,net_port);
				log_msg += log_bff;

				log_bff.Format(" * Error Message <- %s \n", err_msg);
				log_msg += log_bff;
			}
			else
			{
				log_msg += "Initialization Completed ... \n";
			}
		}

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VERITY_STD
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg.Format("Start [%s] ... By %s", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());
		sCH__OBJ_MSG->Set__DATA(log_msg);

		log_msg += "\n";
		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}

	IF__CTRL_MODE(sMODE__INIT)
	{
		flag = Call__INIT(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__COMM_TEST)
	{
		flag = Call__COMM_TEST(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__CFG_LIST)
	{
		flag = Call__CFG_LIST(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__CFG_VALIDATE)
	{
		flag = Call__CFG_VALIDATE(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__WAFER_INFO)
	{
		flag = Call__WAFER_INFO(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__STEP_START)
	{
		flag = Call__STEP_START(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__STEP_STOP)
	{
		flag = Call__STEP_STOP(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__COMPLETE)
	{
		flag = Call__COMPLETE(p_variable, p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__GET_NET_BUUFER)
	{
		flag = Call__GET_NET_BUFFER(p_variable, p_alarm);
	}

	//
	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("Aborted ... :  [%s]", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg.Format("Completed ... :  [%s]", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return flag;
}

int CObj__VERITY_STD
::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == _MON_ID__IO_MONITORING)			Mon__IO_MONITORING(p_variable, p_alarm);
	if(id == _MON_ID__DRV_PROC)					Mon__DRV_PROC(p_variable, p_alarm);

	return 1;
}
