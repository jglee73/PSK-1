#include "StdAfx.h"
#include "CObj__LV32_BLDC.h"


//--------------------------------------------------------------------------------
CObj__LV32_BLDC::CObj__LV32_BLDC()
{

}
CObj__LV32_BLDC::~CObj__LV32_BLDC()
{

}

//--------------------------------------------------------------------------------
int CObj__LV32_BLDC::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__CHECK_PACKET_FORMAT, "CHECK.PACKET_FORMAT");
	}
	return 1;
}
int CObj__LV32_BLDC::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__ALM_REPORT					1


#define  APP_DSP__RPM_PRESSURE				"RPM  PRESSURE"


int CObj__LV32_BLDC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CString var_name;
	int i;

	// ...
	{
		var_name = "OBJ.MSG";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, var_name);
	}

	// MON ...
	{
		var_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, var_name);

		var_name = "MON.COMMUNICATION.INFO";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_INFO, var_name);

		//
		var_name = "MON.SYSTEM.ABORT";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SYSTEM_ABORT, var_name);
	}

	// PARA ...
	{
		var_name = "PARA.FFU.BLOCK.RPM_SV";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "rpm", 0, 1, 1400, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FFU_BLOCK_RPM_SV, var_name);

		var_name = "PARA.FFU.UNIT.DIFF_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "mmAq", 2, 0.5, 12.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FFU_UNIT_DIFF_PRESSURE, var_name);
	}

	// CFG ...
	{
		var_name = "CFG.FFU.TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(var_name, APP_DSP__RPM_PRESSURE, "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_FFU_TYPE, var_name);

		//
		var_name = "CFG.FFU.INITIAL.RPM";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "rpm", 0, 1, 1400, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FFU_INITIAL_RPM, var_name);

		var_name = "CFG.FFU.LOW_LIMIT.RPM";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "rpm", 0, 1, 1400, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FFU_LOW_LIMIT_RPM, var_name);
		
		//
		var_name = "CFG.FFU.INITIAL.DIFF_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "mmAq", 2, 0.5, 12.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FFU_INITIAL_DIFF_PRESSURE, var_name);

		var_name = "CFG.FFU.LOW_LIMIT.DIFF_PRESSURE";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "mmAq", 2, 0.5, 12.0, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_FFU_LOW_LIMIT_DIFF_PRESSURE, var_name);

		//
		var_name = "CFG.LV32.ID";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "id", 0, 1, 32, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_LV32_ID, var_name);

		var_name = "CFG.START.ICU_ID";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "id", 0, 1, 32, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_START_ICU_ID, var_name);

		var_name = "CFG.RANGE.ICU_COUNT";
		STD__ADD_ANALOG_WITH_X_OPTION(var_name, "count", 0, 1, 4, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_RANGE_ICU_COUNT, var_name);
	}

	// UNIT ...
	{
		var_name = "FFU.UNIT.PRESSURE_HEXA";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_UNIT__PRESSURE_HEXA, var_name);
		
		var_name = "FFU.UNIT.PRESSURE_VALUE";
		STD__ADD_STRING(var_name);
		LINK__VAR_STRING_CTRL(sCH__FFU_UNIT__PRESSURE_VALUE, var_name);
	}
	// BLOCK ...
	{
		for(i=0; i<CFG__FAN_SIZE; i++)
		{
			int id = i + 1;

			//
			var_name.Format("FFU.BLOCK.STATE_HEXA.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__STATE_HEXA_X[i], var_name);

			//
			var_name.Format("FFU.BLOCK.ID.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__ID_X[i], var_name);

			var_name.Format("FFU.BLOCK.RPM_PV.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__RPM_PV_X[i], var_name);

			var_name.Format("FFU.BLOCK.RPM_SV.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__RPM_SV_X[i], var_name);

			//
			var_name.Format("FFU.BLOCK.ALARM.LOCAL_MODE.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__ALARM_LOCAL_MODE_X[i], var_name);

			var_name.Format("FFU.BLOCK.ALARM.POWER_OFF.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__ALARM_POWER_OFF_X[i], var_name);

			var_name.Format("FFU.BLOCK.ALARM.OVER_CURRENT.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[i], var_name);

			var_name.Format("FFU.BLOCK.ALARM.MOTOR_ERROR.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[i], var_name);

			var_name.Format("FFU.BLOCK.ALARM.CONNECTION_ERROR.%1d", id);
			STD__ADD_STRING(var_name);
			LINK__VAR_STRING_CTRL(sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[i], var_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__ALM_REPORT);
	}
	return 1;
}
int CObj__LV32_BLDC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	int alm_id;
	CString alm_title;
	CString alm_msg;
	CString alm_bff;
	CStringArray l_act;

	// ...
	{
		alm_id = ALID__FFU_OFFLINE;

		alm_title  = title;
		alm_title += "Offline !";

		alm_msg  = "FFU Controller is Offline.\n";
		alm_msg += "Please, Check Communication Status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
	}

	// ...
	{
		alm_id = ALID__FFU_UNIT_LOW_LIMIT_DIFF_PRESSURE;

		alm_title  = title;
		alm_title += "Low Limit differential pressure !";

		alm_msg = "The log limit differential pressure error has occurred. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
	}

	// FAN_X ...
	for(int i=0; i<CFG__FAN_SIZE; i++)
	{
		int id = i + 1;

		// Low Limit RPM ...
		{
			alm_id = ALID__FFU_FAN_LOW_LIMIT_RPM_X + i;

			alm_title  = title;
			alm_bff.Format("Fan(%1d) : Low Limit differential pressure !", id);
			alm_title += alm_bff;

			alm_msg = "The log limit differential pressure error has occurred. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
		}

		// Power Off ...
		{
			alm_id = ALID__FFU_FAN_ALARM_POWER_OFF_X + i;

			alm_title  = title;
			alm_bff.Format("Fan(%1d) : Power Off !", id);
			alm_title += alm_bff;

			alm_msg = "Power-Off error has occurred. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
		}
		// Over-Current ...
		{
			alm_id = ALID__FFU_FAN_ALARM_OVER_CURRENT_X + i;

			alm_title  = title;
			alm_bff.Format("Fan(%1d) : Over-Current !", id);
			alm_title += alm_bff;

			alm_msg = "Over-current error has occurred. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
		}
		// Motor Error ...
		{
			alm_id = ALID__FFU_FAN_ALARM_MOTOR_ERROR_X + i;

			alm_title  = title;
			alm_bff.Format("Fan(%1d) : Motor Error !", id);
			alm_title += alm_bff;

			alm_msg = "Motor error has occurred. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
		}
		// Connection Error ...
		{
			alm_id = ALID__FFU_FAN_ALARM_CONNECTION_ERROR_X + i;

			alm_title  = title;
			alm_bff.Format("Fan(%1d) : Connection Error !", id);
			alm_title += alm_bff;

			alm_msg = "Connection error has occurred. \n";

			l_act.RemoveAll();
			l_act.Add(ACT__CHECK);

			ADD__ALARM_EX(alm_id,alm_title,alm_msg,l_act);
		}
	}

	return 1;
}

//-------------------------------------------------------------------------
#define APP_DSP__OK_ERROR				"OK  ERROR"


int CObj__LV32_BLDC::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString var_name;

	// ...
	{
		var_name = "do.FFU.BLOCK.SET";
		IO__ADD_DIGITAL_WRITE(var_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__FFU_BLOCK_SET, var_name);

		var_name = "di.FFU.BLOCK.GET";
		IO__ADD_DIGITAL_READ__MANUAL(var_name, APP_DSP__OK_ERROR);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__FFU_BLOCK_GET, var_name);

		//
		var_name = "do.FFU.UNIT.SET";
		IO__ADD_DIGITAL_WRITE(var_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__FFU_UNIT_SET, var_name);

		var_name = "di.FFU.UNIT.GET";
		IO__ADD_DIGITAL_READ__MANUAL(var_name, APP_DSP__OK_ERROR);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__FFU_UNIT_GET, var_name);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__LV32_BLDC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__LV32_BLDC::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter

	// ...
	int com_port = -1;

	int nRate   = 9600;
	int nByte   = 8;			
	int nStop   = 1;			
	int nParity = 0;		// 0, 1, 2, 3, 4  :  None, Odd, Even, Mark, Space

	// ...
	{
		CString file_name;
		CString log_msg;
		CString dir_name;
		int nfile_size;
		int nfile_time;

		file_name.Format("%s_Drv.log", sObject_Name);
		dir_name = sObject_Name;
		nfile_size = 24;
		nfile_time = 60;	// minute

		// ...
		{
			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xLog_Ctrl__Drive->CREATE__SUB_DIRECTORY(dir_name);
			xLog_Ctrl__Drive->SET__PROPERTY(file_name,nfile_size,nfile_time);

			xLog_Ctrl__Drive->DISABLE__TIME_LOG();
			xLog_Ctrl__Drive->WRITE__LOG(log_msg);

			xLog_Ctrl__Drive->ENABLE__TIME_LOG();
			xLog_Ctrl__Drive->WRITE__LOG("   START   \n");
		}
	}

	// ...
	{
		CString para_cmmd;
		CString para_data;

		// 1.
		{
			para_cmmd = "COM_PORT";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				com_port = atoi(para_data);
			}
		}
	}

	// ...
	{
		m_nRetryCnt = 2;
		m_Rcv_Time = 300;		// ms
	}

	// ...
	{
		CString log_msg;
		CString msg;

		log_msg.Format("Connect to Serial ... \n");

		msg.Format("Com_Port : %d \n", com_port);
		log_msg += msg;

		msg.Format("nBaudRate : %1d \n", nRate);
		log_msg += msg;

		msg.Format("nDataBit  : %1d \n", nByte);
		log_msg += msg;

		msg.Format("nParity   : %1d \n", nParity);
		log_msg += msg;

		msg.Format("nStopBit  : %1d \n", nStop);
		log_msg += msg;

		msg.Format("m_nRetryCnt : %1d \n", m_nRetryCnt);
		log_msg += msg;

		msg.Format("m_Rcv_Time : %1d (msec) \n", m_Rcv_Time);
		log_msg += msg;

		xLog_Ctrl__Drive->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString str_info;

		str_info.Format("Com_Port(%1d) Buad_Rate(%1d) Data_Bit(%1d) Stop_Bit(%1d) Parity(%1d)",
						com_port,
						nRate,
						nByte,
						nStop,
						nParity);

		sCH__MON_COMMUNICATION_INFO->Set__DATA(str_info);
	}	

	m_nCommState = OFFLINE;

	if(iActive_SIM > 0)
	{
		CString msg;

		msg.Format("Simulation Mode !!!");

		xLog_Ctrl__Drive->WRITE__LOG(msg);
		return -1;
	}

	// ...
	{
		CString msg;

		mX_Serial->RTS__CHECK_SKIP();

		if(mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity) < 0)
		{
			msg.Format("Fail to do INIT__COMPORT: %d, ret:-1", com_port);
			xLog_Ctrl__Drive->WRITE__LOG(msg);
			return -1;
		}
		else
		{
			msg.Format("Initialize RS-232 Complete");
		}

		xLog_Ctrl__Drive->WRITE__LOG(msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__LV32_BLDC::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString log_msg;
	int flag = -1;

	// ...
	{
		log_msg.Format("%s Started...", mode);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CHECK_PACKET_FORMAT)		flag = Call__CHECK_PACKET_FORMAT(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		log_msg.Format("%s Completed (%1d)", mode, flag);
	}	

	sCH__OBJ_MSG->Set__DATA(log_msg);
	return flag;
}

int CObj__LV32_BLDC::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__ALM_REPORT)		Mon__ALM_REPORT(p_variable, p_alarm);

	return 1;
}

int CObj__LV32_BLDC::__CLOSE__OBJECT()
{

	return 1;
}
