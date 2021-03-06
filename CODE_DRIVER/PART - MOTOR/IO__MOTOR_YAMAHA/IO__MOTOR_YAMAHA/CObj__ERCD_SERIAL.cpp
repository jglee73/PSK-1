#include "StdAfx.h"
#include "CObj__ERCD_SERIAL.h"


//--------------------------------------------------------------------------------
CObj__ERCD_SERIAL::CObj__ERCD_SERIAL()
{
	m_Rcv_Time	= 1000;
}
CObj__ERCD_SERIAL::~CObj__ERCD_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__ERCD_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__RESET, "RESET");

		ADD__CTRL_VAR(sMODE__GOTO_POS,  "GOTO.POS");
		ADD__CTRL_VAR(sMODE__GOTO_UP,   "GOTO.UP");
		ADD__CTRL_VAR(sMODE__GOTO_DOWN, "GOTO.DOWN");

		ADD__CTRL_VAR(sMODE__JOG_UP,   "JOG.UP");
		ADD__CTRL_VAR(sMODE__JOG_DOWN, "JOG.DOWN");
	}

	return 1;
}
int CObj__ERCD_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "By JGLEE \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR				1


#define _LIST__OFF_ON					"OFF  ON"
#define _LIST__NO_YES					"NO  YES"


int CObj__ERCD_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// INFO.DRV ...
	{
		str_name = "INFO.DRV.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_COM_PORT, str_name);

		str_name = "INFO.DRV.PARAMETER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV_PARAMETER, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STS, str_name);

		str_name = "MON.SYSTEM.ABORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYSTEM_ABORT, str_name);

		//
		str_name = "MON.ACTIVE.JOG.UP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ACTIVE_JOG_UP, str_name);

		str_name = "MON.ACTIVE.JOG.DOWN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ACTIVE_JOG_DOWN, str_name);

		//
		str_name = "MON.ACTIVE.GOTO.UP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ACTIVE_GOTO_UP, str_name);

		str_name = "MON.ACTIVE.GOTO.DOWN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ACTIVE_GOTO_DOWN, str_name);
	}

	// PARA.USER ...
	{
		str_name = "PARA.USER.GOTO.POS";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 0, 0, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_USER_GOTO_POS, str_name);

		str_name = "PARA.USER.GOTO.SPEED";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_USER_GOTO_SPEED, str_name);
	}
	// PARA.SET ...
	{
		str_name = "PARA.SET.GOTO.POS";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 0, 0, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_GOTO_POS, str_name);

		str_name = "PARA.SET.GOTO.VEL";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_GOTO_VEL, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.ROM_VER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ROM_VER, str_name);

		str_name = "INFO.ROBOT_TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ROBOT_TYPE, str_name);

		str_name = "INFO.EMG_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_EMG_STS, str_name);

		//
		str_name = "INFO.SERVO_STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_SERVO_STS, str_name);

		str_name = "INFO.CUR_POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CUR_POS, str_name);

		str_name = "INFO.ROBOT_IDLE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ROBOT_IDLE, str_name);

		str_name = "INFO.ROBOT_HOME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_ROBOT_HOME, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.INIT.SPEED";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_INIT_SPEED, str_name);

		//
		str_name = "CFG.GOTO.SPEED";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_GOTO_SPEED, str_name);

		str_name = "CFG.JOG.SPEED";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_JOG_SPEED, str_name);

		//
		str_name = "CFG.GOTO.UP.ABS_POS";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 0, 0, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_GOTO_UP_ABS_POS, str_name);

		str_name = "CFG.GOTO.DOWN.ABS_POS";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mm", 0, 0, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_GOTO_DOWN_ABS_POS, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__IO_MONITOR);
	}
	return 1;
}
int CObj__ERCD_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "Communication Offline !";

		alarm_msg = "Controller Offline !";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	// ...
	{
		alarm_id = ALID__GOTO_POS_ERROR;

		alarm_title  = title;
		alarm_title += "Goto position error !";

		alarm_msg = "Please, check the current position.";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	return 1;
}

// ...
int CObj__ERCD_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	//-------------------------------------------------------
	CString str_name;

	// Digital ...
	{
		// DO ...
		{
			str_name = "do.CTRL.SET";
			IO__ADD_DIGITAL_WRITE(str_name, "IDLE HOME GOTO MOVE.INC MOVE.DEC SERVO.OFF SERBO.ON RESET INIT.ALM INIT.ERR");	
			LINK__IO_VAR_DIGITAL_CTRL(doCH__CTRL_SET, str_name);

			str_name = "do.ABORT.SET";
			IO__ADD_DIGITAL_WRITE(str_name, "IDLE STOP");	
			LINK__IO_VAR_DIGITAL_CTRL(doCH__ABORT_SET, str_name);
		}
	}

	// String ...
	{
		// SI ...
		{
			str_name = "si.ROM_VER";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__ROM_VER, str_name);
			
			str_name = "si.ROBOT_TYPE";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__ROBOT_TYPE, str_name);

			str_name = "si.EMG_STS";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__EMG_STS, str_name);

			//
			str_name = "si.SERVO_STS";
			IO__ADD_STRING_READ(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__SERVO_STS, str_name);

			str_name = "si.CUR_POS";
			IO__ADD_STRING_READ_WITH_OPTION(str_name, "", "", "", 0.1, "");
			LINK__IO_VAR_STRING_CTRL(siCH__CUR_POS, str_name);

			//
			str_name = "si.ROBOT_STS.AUTO";
			IO__ADD_STRING_READ_WITH_OPTION(str_name, "", "", "", 0.1, "");
			LINK__IO_VAR_STRING_CTRL(siCH__ROBOT_STS_AUTO, str_name);

			str_name = "si.ROBOT_STS.MANUAL";
			IO__ADD_STRING_READ_WITH_OPTION(str_name, "", "", "", 0.1, "");
			LINK__IO_VAR_STRING_CTRL(siCH__ROBOT_STS_MANUAL, str_name);

			//
			str_name = "si.ORG_STS";
			IO__ADD_STRING_READ_WITH_OPTION(str_name, "", "", "", 0.1, "");
			LINK__IO_VAR_STRING_CTRL(siCH__ORG_STS, str_name);
		}
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__ERCD_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}

		// DRV Log ...
		{
			file_name.Format("%s__DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__DRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__DRV_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__DRV_LOG_CTRL->DISABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			xI__DRV_LOG_CTRL->ENABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		iFLAG__DRV_FLAG = 1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}

int CObj__ERCD_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 9600;
	int nByte   = 8;			// 5, 6, 7, 8
	int nStop   = 1;			// 1, 2
	int nParity = 1;			// 0 ~ 4 : None, Odd, Even, Mark, Space

	sTerm_Str  = (char) CR;	
	sTerm_Str += (char) LF;	
	
	sTerm_Exp = "<CR><LF>";	

	// ...
	{
		CString str_cmmd;
		CString str_data;

		// 1.
		{
			str_cmmd = "COM_PORT";

			if(p_io_para->Get__PARAMETER_DATA(str_cmmd, str_data) > 0)
			{
				com_port = atoi(str_data);
			}
		}

		// ...
		CString str_info;

		str_info.Format("%1d", com_port);
		sCH__INFO_DRV_COM_PORT->Set__DATA(str_info);
	}

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "Connect to Serial \n";

		log_bff.Format("Com Port: %1d \n", com_port);
		log_msg += log_bff;

		log_bff.Format("Baud Rate: %1d \n", nRate);
		log_msg += log_bff;

		log_bff.Format("Data Bit: %1d \n", nByte);
		log_msg += log_bff;

		log_bff.Format("Parity Bit: %1d \n", nParity);
		log_msg += log_bff;

		log_bff.Format("Stop Bit: %1d \n", nStop);
		log_msg += log_bff;

		//
		log_msg += "Terminal String : Byte Count \n";							  
	}

	// ...
	{
		CString str_info;

		str_info.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d]",
						nRate, 
						nByte, 
						nStop, 
						nParity);

		sCH__INFO_DRV_PARAMETER->Set__DATA(str_info);

		//
		log_bff.Format("Terminal String : [%s] \n", sTerm_Exp);
		log_msg += log_bff;
	}

	if(iActive_SIM > 0)
	{
		log_msg += "Initialize RS-232 Complete \n";
		log_msg += "Simulation Mode !!! \n";

		Write__APP_LOG(log_msg);
		Write__DRV_LOG(log_msg);
		return -1;
	}

	if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
	{
		log_bff.Format("Fail to do INIT__COMPORT: %d, ret:-1\n", com_port);
		log_msg += log_bff;

		Write__APP_LOG(log_msg);
		Write__DRV_LOG(log_msg);
		return -1;
	}
	else
	{
		log_msg += "Initialize RS-232 Complete \n";

		Write__APP_LOG(log_msg);
		Write__DRV_LOG(log_msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ERCD_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString log_msg;
	int flag = -1;

	// ...
	{
		log_msg.Format("%s Started...", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);

		Write__APP_LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RESET)			flag = Call__RESET(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__GOTO_POS)
		{
			flag = Call__GOTO_POS(p_variable, p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__GOTO_UP)
		{
			sCH__MON_ACTIVE_GOTO_UP->Set__DATA(STR__ON);

			flag = Call__GOTO_UP(p_variable, p_alarm);

			sCH__MON_ACTIVE_GOTO_UP->Set__DATA(STR__OFF);
		}
		ELSE_IF__CTRL_MODE(sMODE__GOTO_DOWN)
		{
			sCH__MON_ACTIVE_GOTO_DOWN->Set__DATA(STR__ON);

			flag = Call__GOTO_DOWN(p_variable, p_alarm);

			sCH__MON_ACTIVE_GOTO_DOWN->Set__DATA(STR__OFF);
		}

		ELSE_IF__CTRL_MODE(sMODE__JOG_UP)
		{
			sCH__MON_ACTIVE_JOG_UP->Set__DATA(STR__ON);

			flag = Call__JOG_UP(p_variable, p_alarm);

			sCH__MON_ACTIVE_JOG_UP->Set__DATA(STR__OFF);
		}
		ELSE_IF__CTRL_MODE(sMODE__JOG_DOWN)
		{
			sCH__MON_ACTIVE_JOG_DOWN->Set__DATA(STR__ON);

			flag = Call__JOG_DOWN(p_variable, p_alarm);

			sCH__MON_ACTIVE_JOG_DOWN->Set__DATA(STR__OFF);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		_Fnc__Abort_Ctrl();

		log_msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		log_msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(log_msg);

		Write__APP_LOG(log_msg);
	}
	return flag;
}

int CObj__ERCD_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable, p_alarm);
			break;
	}

	return 1;
}
