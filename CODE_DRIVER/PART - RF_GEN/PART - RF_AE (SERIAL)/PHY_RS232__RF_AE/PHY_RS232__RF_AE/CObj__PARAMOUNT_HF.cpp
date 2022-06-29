#include "StdAfx.h"
#include "CObj__PARAMOUNT_HF.h"



//--------------------------------------------------------------------------------
CObj__PARAMOUNT_HF::CObj__PARAMOUNT_HF()
{
	m_nCommState = OFFLINE;
	m_Rcv_Time	 = 250;
	m_RetryCnt	 = 3;
}
CObj__PARAMOUNT_HF::~CObj__PARAMOUNT_HF()
{

}

//--------------------------------------------------------------------------------
int CObj__PARAMOUNT_HF::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	   "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL,	   "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE,   "REMOTE");

		ADD__CTRL_VAR(sMODE__ON,	   "ON");
		ADD__CTRL_VAR(sMODE__OFF,	   "OFF");

		ADD__CTRL_VAR(sMODE__PROC_SET, "PROC_SET");
	}
	return 1;
}
int CObj__PARAMOUNT_HF::__DEFINE__VERSION_HISTORY(version)
{
	version = "2021.09.10 \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__MON_MODE				"IDLE	  RUN"
#define  APP_DSP__OFF_ON				"OFF	  ON"
#define  APP_DSP__HOST_ANALOG			"HOST	  ANALOG"
#define  APP_DSP__COMM_STATUS           "OFFLINE  ONLINE"
#define  APP_DSP__REGULATION            "FORWARD	LOAD	ETC"
#define  APP_DSP__READING				"1"


int CObj__PARAMOUNT_HF::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.SET.POWER";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Watt", 1, 0, 1500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_SET_POWER, str_name);

		//
		str_name = "PARA.TUNE.USE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_TUNE_USE, str_name);

		str_name = "PARA.TUNE.DELAY";
		STD__ADD_ANALOG(str_name, "msec", 0, 100, 10000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_FREQ_TUNE_DELAY, str_name);

		//
		str_name = "PARA.RAMP.UP.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_UP_TIME, str_name);

		str_name = "PARA.RAMP.DOWN.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RAMP_DN_TIME, str_name);

		//
		str_name = "PARA.START.FREQUENCY";
		STD__ADD_ANALOG(str_name, "kHz", 0, 0, 999999);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_START_FREQUENCY, str_name);

		str_name = "PARA.OUTPUT.FREQUENCY";
		STD__ADD_ANALOG(str_name, "kHz", 0, 0, 999999);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_OUTPUT_FREQUENCY, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM.STS";
		STD__ADD_DIGITAL(str_name, APP_DSP__COMM_STATUS);
		LINK__VAR_DIGITAL_CTRL(dCH__MON_COMM_STS, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.CTRL_MODE.READ";
		STD__ADD_STRING(str_name);	
		LINK__VAR_STRING_CTRL(sCH__INFO_CTRL_MODE_READ, str_name);

		//
		str_name = "INFO.FORWARD_POWER.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_FORWARD_POWER_READ, str_name);

		str_name = "INFO.REFLECTED_POWER.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_REFLECTED_POWER_READ, str_name);

		str_name = "INFO.DELIVERED_POWER.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DELIVERED_POWER_READ, str_name);

		//
		str_name = "INFO.POWER_SETPOINT.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_POWER_SETPOINT_READ, str_name);

		str_name = "INFO.REGULATION_MODE.READ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_REGULATION_MODE_READ, str_name);

		//
		str_name = "INFO.CSR.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CSR_HEXA, str_name);
		
		str_name = "INFO.CSR.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_CSR_MSG, str_name);
	}

	// INFO,STS ...
	{
		// BIT 0 :
		str_name = "INFO.STS.TUNING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_TUNING, str_name);
	
		str_name = "INFO.STS.SETPOINT_RAMPING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_SETPOINT_RAMPING, str_name);
		
		str_name = "INFO.STS.RECIPE_ACTIVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_RECIPE_ACTIVE, str_name);
		
		str_name = "INFO.STS.RECIPE_ENABLED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_RECIPE_ENABLED, str_name);
		
		str_name = "INFO.STS.RF_OUTPUT_ON";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_RF_OUTPUT_ON, str_name);
		
		str_name = "INFO.STS.RF_ON_REQUESTED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_RF_ON_REQUESTED, str_name);
		
		str_name = "INFO.STS.SETPOINT_TOLERANCE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_SETPOINT_TOLERANCE, str_name);

		// BIT 1 :
		str_name = "INFO.STS.OVERTEMPERATURE_FAULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_OVERTEMPERATURE_FAULT, str_name);
		
		str_name = "INFO.STS.FREQUENCY_VARIABLE_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_FREQUENCY_VARIABLE_MODE, str_name);
		
		str_name = "INFO.STS.PULSING_EMABLED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_PULSING_EMABLED, str_name);
		
		str_name = "INFO.STS.ARC_MANAGEMENT_ENABLED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_ARC_MANAGEMENT_ENABLED, str_name);

		str_name = "INFO.STS.INTERLOCK_OPEN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_INTERLOCK_OPEN, str_name);

		// BIT 2 :
		str_name = "INFO.STS.HIGH_AC_LINE_VOLTAGE_WARNING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_HIGH_AC_LINE_VOLTAGE_WARNING, str_name);
		
		str_name = "INFO.STS.LOW_AC_LINE_VOLTAGE_WARNING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_LOW_AC_LINE_VOLTAGE_WARNING, str_name);

		str_name = "INFO.STS.PROTECTION_LIMIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_PROTECTION_LIMIT, str_name);

		// BIT 3 :
		str_name = "INFO.STS.INVERTER_NOT_READY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_INVERTER_NOT_READY, str_name);
		
		str_name = "INFO.STS.FIELD_BUS_ERROR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_FIELD_BUS_ERROR, str_name);
		
		str_name = "INFO.STS.CCEX_ENABLED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_CEX_ENABLED, str_name);
		
		str_name = "INFO.STS.FAULT_PRESENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_FAULT_PRESENT, str_name);
		
		str_name = "INFO.STS.WARNING_PRESENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_WARNING_PRESENT, str_name);
		
		str_name = "INFO.STS.CEX_LOCKED";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STS_CEX_LOCKED, str_name);
	}
	
	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0,MON_ID__MONITOR);
	}
	return 1;
}
int CObj__PARAMOUNT_HF::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__GEN_OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Generator Offline";

		alarm_msg = "Generator Offline.";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__GEN_RETRY_OVER_ALARM;

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

int CObj__PARAMOUNT_HF::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// AO ...
	{
		str_name = "ao.POWER.SET";
		IO__ADD_ANALOG_WRITE(str_name, "W", 1, 0.0, 1500.0);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__POWER_SET, str_name);
	}

	// SI ...
	{
		str_name = "si.CTRL_MODE.HEXA";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__CTRL_MODE_HEXA, str_name);

		str_name = "si.SETPOINT_REGULATION.HEXA";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__SETPOINT_REGULATION_HEXA, str_name);

		//
		str_name = "si.REPORT_FORWARD_POWER.HEXA";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__REPORT_FORWARD_POWER_HEXA, str_name);
		
		str_name = "si.REPORT_REFLECTED_POWER.HEXA";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__REPORT_REFLECTED_POWER_HEXA, str_name);
		
		str_name = "si.REPORT_DELIVERED_POWER.HEXA";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__REPORT_DELIVERED_POWER_HEXA, str_name);

		//
		str_name = "si.REPORT_PROCESS_STATUS.HEXA";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__REPORT_PROCESS_STATUS_HEXA, str_name);
	}

	// DO ...
	{
		str_name = "do.CTRL.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__HOST_ANALOG);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CTRL_MODE, str_name);	

		str_name = "do.POWER.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__OFF_ON);	
		LINK__IO_VAR_DIGITAL_CTRL(doCH__POWER_MODE, str_name);

		str_name = "do.REGULATION.MODE";
		IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__REGULATION);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__REGULATION_MODE, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__PARAMOUNT_HF::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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

int CObj__PARAMOUNT_HF::__INITIALIZE__IO(p_io_para)
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

	if(iActive_SIM > 0)
	{
		return -1;
	}
	else
	{
		mX_Serial->INIT__COMPORT(com_port, nRate, nByte, nStop, nParity);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__PARAMOUNT_HF::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
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

		ELSE_IF__CTRL_MODE(sMODE__LOCAL)				flag = Call__CTRL_MODE(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)				flag = Call__CTRL_MODE(p_variable, p_alarm, true);

		ELSE_IF__CTRL_MODE(sMODE__ON)					flag = Call__POWER_SET(p_variable, p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__OFF)					flag = Call__POWER_SET(p_variable, p_alarm, false);

		ELSE_IF__CTRL_MODE(sMODE__PROC_SET)				flag = Call__PROC_SET(p_variable, p_alarm);
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

int CObj__PARAMOUNT_HF::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if(id == MON_ID__MONITOR)
	{
		return Mon__MONITOR(p_variable,p_alarm);
	}
	return 1;
}

