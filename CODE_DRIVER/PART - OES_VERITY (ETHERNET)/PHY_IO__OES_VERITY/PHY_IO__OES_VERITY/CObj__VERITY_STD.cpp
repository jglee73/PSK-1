#include "stdafx.h"

#include "CObj__VERITY_STD__ALID.h"
#include "CObj__VERITY_STD.h"


//--------------------------------------------------------------------------------
CObj__VERITY_STD::CObj__VERITY_STD()
{
	::InitializeCriticalSection( &mSc );

	g_bEndThread = false;
}
CObj__VERITY_STD::~CObj__VERITY_STD()
{
	g_bEndThread = true;

	::DeleteCriticalSection( &mSc );
}

//--------------------------------------------------------------------------------
int CObj__VERITY_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__START, "START");
		ADD__CTRL_VAR(sMODE__STOP, "STOP");
		ADD__CTRL_VAR(sMODE__RESET, "RESET");
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

int CObj__VERITY_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString var_name;

	// ...
	{
		var_name = "COMM.STATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__COMM_STATE, var_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1, _MON_ID__IO_MONITORING);
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
		str_name = "do.EPD_Start";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__EPD_Start, str_name);
		str_name = "do.EPD_Stop";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__EPD_Stop, str_name);
		str_name = "do.EPD_Reset";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__EPD_Reset, str_name);

	}
	// DI ...
	{
		str_name = "di.EPD_EndPoint";
		str_list = "Off";
		str_list += " ";
		str_list += "On";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_EndPoint, str_name);

		str_name = "di.EPD_Status";
		str_list = "Unknown";
		str_list += " ";
		str_list += "Idle";
		str_list += " ";
		str_list += "Running";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_Status, str_name);

		str_name = "di.EPD_SensorErr";
		str_list = "Normal";
		str_list += " ";
		str_list += "TempError";
		str_list += " ";
		str_list += "CommError";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_SensorErr, str_name);


		str_name = "di.EPD_GetRecipe";
		str_list = "Off";
		str_list += " ";
		str_list += "On";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_GetRecipe, str_name);

		str_name = "di.EPD_Nak_Command";
		str_list = "None";
		str_list += " ";
		str_list += "Start";
		str_list += " ";
		str_list += "Stop";
		str_list += " ";
		str_list += "Reset";
		str_list += " ";
		str_list += "WfrInfo";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_Nak_Command, str_name);

		str_name = "di.EPD_CommTest";
		str_list = "Alarm";
		str_list += " ";
		str_list += "Normal";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_CommTest, str_name);

		str_name = "di.EPD_EndOverEtch";
		str_list = "Off";
		str_list += " ";
		str_list += "On";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_EndOverEtch, str_name);

		str_name = "di.EPD_Finish";
		str_list = "Off";
		str_list += " ";
		str_list += "On";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_Finish, str_name);

		str_name = "di.EPD_TimeSync";
		str_list = "Off";
		str_list += " ";
		str_list += "On";
		IO__ADD_DIGITAL_WRITE(str_name, str_list);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__EPD_TimeSync, str_name);
	}

	// AO ...
	{
	}
	// AI ...
	{
		str_name = "ai.EPD_Monitor1";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor1, str_name);

		str_name = "ai.EPD_Monitor2";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor2, str_name);

		str_name = "ai.EPD_Monitor3";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor3, str_name);

		str_name = "ai.EPD_Monitor4";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor4, str_name);

		str_name = "ai.EPD_Monitor5";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor5, str_name);

		str_name = "ai.EPD_Monitor6";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor6, str_name);

		str_name = "ai.EPD_Monitor7";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor7, str_name);

		str_name = "ai.EPD_Monitor8";
		IO__ADD_ANALOG_WRITE(str_name, "W", 0, 0.0, 1000.0);
		LINK__IO_VAR_ANALOG_CTRL(aiCH__EPD_Monitor8, str_name);
	}

	// SO ...
	{
		str_name = "so.EPD_WAFER_INFO";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__EPD_WAFER_INFO, str_name);
		
		str_name = "so.EPD_Recipe_Name";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(soCH__EPD_Recipe_Name, str_name);
	}
	// SI ...
	{
		str_name = "si.EPD_Mon_Name1";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name1, str_name);
		
		str_name = "si.EPD_Mon_Name2";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name2, str_name);
		
		str_name = "si.EPD_Mon_Name3";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name3, str_name);
		
		str_name = "si.EPD_Mon_Name4";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name4, str_name);
		
		str_name = "si.EPD_Mon_Name5";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name5, str_name);
		
		str_name = "si.EPD_Mon_Name6";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name6, str_name);
		
		str_name = "si.EPD_Mon_Name7";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name7, str_name);
		
		str_name = "si.EPD_Mon_Name8";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EPD_Mon_Name8, str_name);
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
		alarm_id = ALID__EPD_COMMUNICATION_ALARM;

		alarm_title  = title;
		alarm_title += "Communication Fail.";

		alarm_msg  = "EPD is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		l_act.RemoveAll();
		//	l_act.Add("RETRY");
		//	l_act.Add("ABORT");
		l_act.Add("CHECK");

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
		// 3. End_String
		{
			CString str_end = "";

			para_cmmd = "END.STRING";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				if(para_data.CompareNoCase("CR") == 0)
				{
					str_end = (char) CR;
				}
				else if(para_data.CompareNoCase("LF") == 0)
				{
					str_end = (char) LF;
				}
				else if(para_data.CompareNoCase("CR_LF") == 0)
				{
					str_end  = (char) CR;
					str_end += (char) LF;
				}
				else 
				{
					str_end  = (char) CR;
					str_end += (char) LF;
				}
			}

			// ...
			int str_len = str_end.GetLength();

			mX__Net_Client->SET__TERMINAL_InSTRING(str_end,  str_len);
			mX__Net_Client->SET__TERMINAL_OutSTRING(str_end, str_len);
		}
	}

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "Connect to Ethernet ... \n";

		log_bff.Format("Net_IP : %s \n", net_ip);
		log_msg += log_bff;

		log_bff.Format("Net_Port : %s \n", net_port);
		log_msg += log_bff;

		log_bff.Format("End_String(Out) : %s \n", mX__Net_Client->GET__TERMINAL_InSTRING());
		log_msg += log_bff;

		log_bff.Format("End_String(In ) : %s \n", mX__Net_Client->GET__TERMINAL_OutSTRING());
		log_msg += log_bff;

		// ...
		CString err_msg;

		mX__Net_Client->INIT__PROPERTY(net_ip, atoi(net_port));
		if(mX__Net_Client->CONNECT(&err_msg) < 0)
		{
			log_bff.Format("Fail to do INIT__ETHERNET: %s(%s), ret(-1) \n", net_ip,net_port);
			log_msg += log_bff;

			mX__Log_Ctrl->WRITE__LOG(log_msg);
			return -1;
		}

		log_msg += "Initialization Completed ... \n";
		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VERITY_STD
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	IF__CTRL_MODE(sMODE__INIT)
	{
		flag = Call__INIT(p_variable, p_alarm);
	}

	return flag;
}

int CObj__VERITY_STD
::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == _MON_ID__IO_MONITORING)			Mon__IO_MONITORING(p_variable, p_alarm);

	return 1;
}
