#include "StdAfx.h"
#include "CObj__NAVII_SERIAL.h"



//--------------------------------------------------------------------------------
CObj__NAVII_SERIAL::CObj__NAVII_SERIAL()
{
	m_nCommState = OFFLINE;
	m_Rcv_Time	 = 250;
	m_RetryCnt	 = 3;
}
CObj__NAVII_SERIAL::~CObj__NAVII_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__NAVII_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");

		ADD__CTRL_VAR(sMODE__CTRL_MODE_ALL, "CTRL_MODE.ALL");
		ADD__CTRL_VAR(sMODE__CTRL_MODE_CH1, "CTRL_MODE.CH1");
		ADD__CTRL_VAR(sMODE__CTRL_MODE_CH2, "CTRL_MODE.CH2");

		ADD__CTRL_VAR(sMODE__PRESET_ALL, "PRESET.ALL");
		ADD__CTRL_VAR(sMODE__PRESET_CH1, "PRESET.CH1");
		ADD__CTRL_VAR(sMODE__PRESET_CH2, "PRESET.CH2");

		ADD__CTRL_VAR(sMODE__LOAD_POS_ALL, "LOAD_POS.ALL");
		ADD__CTRL_VAR(sMODE__LOAD_POS_CH1, "LOAD_POS.CH1");
		ADD__CTRL_VAR(sMODE__LOAD_POS_CH2, "LOAD_POS.CH2");

		ADD__CTRL_VAR(sMODE__TUNE_POS_ALL, "TUNE_POS.ALL");
		ADD__CTRL_VAR(sMODE__TUNE_POS_CH1, "TUNE_POS.CH1");
		ADD__CTRL_VAR(sMODE__TUNE_POS_CH2, "TUNE_POS.CH2");

		ADD__CTRL_VAR(sMODE__CAP_MOTOR_ALL, "CAP_MOTOR.ALL");
		ADD__CTRL_VAR(sMODE__CAP_MOTOR_CH1, "CAP_MOTOR.CH1");
		ADD__CTRL_VAR(sMODE__CAP_MOTOR_CH2, "CAP_MOTOR.CH2");
	}
	return 1;
}
int CObj__NAVII_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "2021.09.10 \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__COMM_STATUS				"OFFLINE   ONLINE"
#define  APP_DSP__OFF_ON					"OFF   ON"
#define  APP_DSP__CONTROL_MODE				"USER  AUTO  HOST"
#define  APP_DSP__INTERNAL_EXTERNAL			"INTERNAL  EXTERNAL"


int CObj__NAVII_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString str_list;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.CONTROL_MODE.CH1";		
		STD__ADD_DIGITAL(str_name, APP_DSP__CONTROL_MODE);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_CONTROL_MODE_CH1, str_name);

		str_name = "PARA.CONTROL_MODE.CH2";		
		STD__ADD_DIGITAL(str_name, APP_DSP__CONTROL_MODE);
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_CONTROL_MODE_CH2, str_name);

		//
		str_name = "PARA.ACTIVE_PRESET.CH1";		
		STD__ADD_ANALOG(str_name, "__", 0, 1, 10);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_ACTIVE_PRESET_CH1, str_name);

		str_name = "PARA.ACTIVE_PRESET.CH2";		
		STD__ADD_ANALOG(str_name, "__", 0, 1, 10);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_ACTIVE_PRESET_CH2, str_name);

		//
		str_name = "PARA.LOAD_POS.CH1";
		STD__ADD_ANALOG(str_name, "%", 2, 0.0, 100.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_LOAD_POS_CH1, str_name);

		str_name = "PARA.LOAD_POS.CH2";
		STD__ADD_ANALOG(str_name, "%", 2, 0.0, 100.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_LOAD_POS_CH2, str_name);

		//
		str_name = "PARA.TUNE_POS.CH1";
		STD__ADD_ANALOG(str_name, "%", 2, 0.0, 100.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_TUNE_POS_CH1, str_name);
		
		str_name = "PARA.TUNE_POS.CH2";
		STD__ADD_ANALOG(str_name, "%", 2, 0.0, 100.0);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_TUNE_POS_CH2, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_DIGITAL(str_name, APP_DSP__COMM_STATUS);
		LINK__VAR_DIGITAL_CTRL(dCH__MON_COMM_STS, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.CTRL_MODE.CH1";
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_CTRL_MODE_CH1, str_name);

		str_name = "INFO.CTRL_MODE.CH2";
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_CTRL_MODE_CH2, str_name);

		//
		str_name = "INFO.LOAD_POS.CH1";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_LOAD_POS_CH1, str_name);

		str_name = "INFO.LOAD_POS.CH2";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_LOAD_POS_CH2, str_name);

		//
		str_name = "INFO.TUNE_POS.CH1";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_TUNE_POS_CH1, str_name);

		str_name = "INFO.TUNE_POS.CH2";	  
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_TUNE_POS_CH2, str_name);

		//
		str_name = "INFO.CSR.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CSR_HEXA, str_name);

		str_name = "INFO.CSR.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CSR_MSG, str_name);
	}

	// CFG ...
	{
		// Load ...
		{
			str_name = "CFG.LOAD_MIN.CH1";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LOAD_MIN_CH1, str_name);

			str_name = "CFG.LOAD_MAX.CH1";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LOAD_MAX_CH1, str_name);

			//
			str_name = "CFG.LOAD_MIN.CH2";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LOAD_MIN_CH2, str_name);

			str_name = "CFG.LOAD_MAX.CH2";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LOAD_MAX_CH2, str_name);
		}

		// Tune ...
		{
			str_name = "CFG.TUNE_MIN.CH1";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TUNE_MIN_CH1, str_name);

			str_name = "CFG.TUNE_MAX.CH1";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TUNE_MAX_CH1, str_name);

			//
			str_name = "CFG.TUNE_MIN.CH2";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TUNE_MIN_CH2, str_name);

			str_name = "CFG.TUNE_MAX.CH2";
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0.0, 100.0, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_TUNE_MAX_CH2, str_name);
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}
int CObj__NAVII_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "Generator Offline";

		alarm_msg = "Generator Offline.";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RETRY_OVER_ALARM;

		alarm_title  = title;
		alarm_title += "Generator Communication Retry Over";

		alarm_msg = "Generator Communication Retry Over";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

int CObj__NAVII_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// SI ...
	{
		str_name = "si.CTRL_MODE.HEXA.CH1";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CTRL_MODE_HEXA_CH1, str_name);

		str_name = "si.CTRL_MODE.HEXA.CH2";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CTRL_MODE_HEXA_CH2, str_name);

		//
		str_name = "si.CAPACITOR_POS.HEXA.CH1";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CAPACITOR_POS_HEXA_CH1, str_name);

		str_name = "si.CAPACITOR_POS.HEXA.CH2";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CAPACITOR_POS_HEXA_CH2, str_name);
	}

	// DO ...
	{
		str_name = "do.ALL_CAPACITOR_INIT";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ALL_CAPACITOR_INIT, str_name);

		//
		str_name = "do.CAPACITOR_LIMIT.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CAPACITOR_LIMIT_CH1, str_name);

		str_name = "do.CAPACITOR_LIMIT.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CAPACITOR_LIMIT_CH2, str_name);

		//
		str_name = "do.CONTROL_MODE.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__CONTROL_MODE);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CONTROL_MODE_CH1, str_name);

		str_name = "do.CONTROL_MODE.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__CONTROL_MODE);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CONTROL_MODE_CH2, str_name);

		//
		str_name = "do.INTERNAL_EXTERNAL_PRESET.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__INTERNAL_EXTERNAL);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__INTERNAL_EXTERNAL_PRESET_CH1, str_name);

		str_name = "do.INTERNAL_EXTERNAL_PRESET.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__INTERNAL_EXTERNAL);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__INTERNAL_EXTERNAL_PRESET_CH2, str_name);

		//
		str_name = "do.ACTIVE_PRESET.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ACTIVE_PRESET_CH1, str_name);

		str_name = "do.ACTIVE_PRESET.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__ACTIVE_PRESET_CH2, str_name);

		//
		str_name = "do.LOAD_POS.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__LOAD_POS_CH1, str_name);

		str_name = "do.LOAD_POS.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__LOAD_POS_CH2, str_name);

		//
		str_name = "do.TUNE_POS.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__TUNE_POS_CH1, str_name);

		str_name = "do.TUNE_POS.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__TUNE_POS_CH2, str_name);

		//
		str_name = "do.CAPACITOR_MOTOR_POS.CH1";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CAPACITOR_MOTOR_POS_CH1, str_name);
		
		str_name = "do.CAPACITOR_MOTOR_POS.CH2";		
		IO__ADD_DIGITAL_WRITE(str_name, "SET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CAPACITOR_MOTOR_POS_CH2, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__NAVII_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

	// ADDR_ID ...
	{
		iUNIT__ADDR_ID = 0x01;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;
		iActive_SIM = x_seq_info->Is__SIMULATION_MODE();

		iFLAG__DRV_FLAG = 1;
	}
	return 1;
}

int CObj__NAVII_SERIAL::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int nRate   = 19200;
	int nByte   = 8;			// 5, 6, 7, 8
	int nStop   = 1;			// 1, 2
	int nParity = 1;			// 0 ~ 4 : None, Odd, Even, Mark, Space

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
	}

	// ...
	{
		sPROTOCOL_INFO.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d] \n",
			nRate, nByte, nStop, nParity);

		sPROTOCOL_INFO += "Terminal String : [CR] \n";							  
	}

	mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__NAVII_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CTRL_MODE_ALL)		flag = Call__CTRL_MODE_CH_X(p_variable,p_alarm, 0);
		ELSE_IF__CTRL_MODE(sMODE__CTRL_MODE_CH1)		flag = Call__CTRL_MODE_CH_X(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__CTRL_MODE_CH2)		flag = Call__CTRL_MODE_CH_X(p_variable,p_alarm, 2);

		ELSE_IF__CTRL_MODE(sMODE__PRESET_ALL)			flag = Call__PRESET_CH_X(p_variable,p_alarm, 0);
		ELSE_IF__CTRL_MODE(sMODE__PRESET_CH1)			flag = Call__PRESET_CH_X(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__PRESET_CH2)			flag = Call__PRESET_CH_X(p_variable,p_alarm, 2);

		ELSE_IF__CTRL_MODE(sMODE__LOAD_POS_ALL)			flag = Call__LOAD_POS_CH_X(p_variable,p_alarm, 0);
		ELSE_IF__CTRL_MODE(sMODE__LOAD_POS_CH1)			flag = Call__LOAD_POS_CH_X(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__LOAD_POS_CH2)			flag = Call__LOAD_POS_CH_X(p_variable,p_alarm, 2);

		ELSE_IF__CTRL_MODE(sMODE__TUNE_POS_ALL)			flag = Call__TUNE_POS_CH_X(p_variable,p_alarm, 0);
		ELSE_IF__CTRL_MODE(sMODE__TUNE_POS_CH1)			flag = Call__TUNE_POS_CH_X(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__TUNE_POS_CH2)			flag = Call__TUNE_POS_CH_X(p_variable,p_alarm, 2);
	
		ELSE_IF__CTRL_MODE(sMODE__CAP_MOTOR_ALL)		flag = Call__CAP_MOTOR_CH_X(p_variable,p_alarm, 0);
		ELSE_IF__CTRL_MODE(sMODE__CAP_MOTOR_CH1)		flag = Call__CAP_MOTOR_CH_X(p_variable,p_alarm, 1);
		ELSE_IF__CTRL_MODE(sMODE__CAP_MOTOR_CH2)		flag = Call__CAP_MOTOR_CH_X(p_variable,p_alarm, 2);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		log_msg.Format("%s Aborted (%1d)", mode,flag);

	}
	else
	{
		log_msg.Format("%s Completed (%1d)", mode,flag);
	}	
	Write__APP_LOG(log_msg);

	sCH__OBJ_MSG->Set__DATA(log_msg);
	return flag;
}

int CObj__NAVII_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)
	{
		return Mon__MONITOR(p_variable,p_alarm);
	}
	return 1;
}

