#include "StdAfx.h"
#include "CObj__LOT_SERIAL.h"
#include "CObj__LOT_SERIAL__DEF.h"
#include "CCommon_DEF.h"



//--------------------------------------------------------------------------------
CObj__LOT_SERIAL::CObj__LOT_SERIAL()
{

}
CObj__LOT_SERIAL::~CObj__LOT_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__LOT_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL,  "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE, "REMOTE");

		ADD__CTRL_VAR(sMODE__ON, "ON");
		ADD__CTRL_VAR(sMODE__AUTO_SHUTDOWN, "AUTO_SHUTDOWN");
		ADD__CTRL_VAR(sMODE__FAST_SHUTDOWN, "FAST_SHUTDOWN");
	}

	return 1;
}
int CObj__LOT_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "By JG Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR						1


int CObj__LOT_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
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

	// INFO ...
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

		//
		str_name = "MON.PUMP.STS";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PUMP_STS, str_name);

		str_name = "MON.ACTIVE.FAULT";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ACTIVE_FAULT, str_name);

		str_name = "MON.ACTIVE.WARNING";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ACTIVE_WARNING, str_name);

		//
		str_name = "MON.MODE.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_MODE_STS, str_name);

		str_name = "MON.VERSION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_VERSION, str_name);
	}

	// PUMP WARNING ...
	{
		str_name = "MON.WARNING.PUMP_BODY_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PUMP_BODY_TEMPERATURE, str_name);

		str_name = "MON.WARNING.EXHAUST_PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_EXHAUST_PRESSURE, str_name);

		str_name = "MON.WARNING.OIL_PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_OIL_PRESSURE, str_name);

		str_name = "MON.WARNING.H2O_FLOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_H2O_FLOW, str_name);

		str_name = "MON.WARNING.PURGE_FLOW_ANALOG_1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PURGE_FLOW_ANALOG_1, str_name);

		str_name = "MON.WARNING.PURGE_FLOW_ANALOG_2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PURGE_FLOW_ANALOG_2, str_name);

		str_name = "MON.WARNING.PROCESS_TEMPERATURE_LOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PROCESS_TEMPERATURE_LOW, str_name);

		str_name = "MON.WARNING.PROCESS_TEMPERATURE_HIGH";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PROCESS_TEMPERATURE_HIGH, str_name);

		str_name = "MON.WARNING.PUMP_MOTOR_OVER_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PUMP_MOTOR_OVER_TEMPERATURE, str_name);

		str_name = "MON.WARNING.PUMP_VFD_DIGITAL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PUMP_VFD_DIGITAL, str_name);

		str_name = "MON.WARNING.EXHAUST_PRESSURE_LOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_EXHAUST_PRESSURE_LOW, str_name);

		str_name = "MON.WARNING.EXHAUST_PRESSURE_HIGH";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_EXHAUST_PRESSURE_HIGH, str_name);

		str_name = "MON.WARNING.PUMP_MOTOR_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PUMP_MOTOR_CURRENT, str_name);

		str_name = "MON.WARNING.HOT_N2_TEMPERAURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_HOT_N2_TEMPERAURE, str_name);

		str_name = "MON.WARNING.PUMP_VFD_ANALOG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_PUMP_VFD_ANALOG, str_name);
	}

	// BLOWER WARNING ...
	{
		str_name = "MON.WARNING.BLOWER_MOTOR_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_BLOWER_MOTOR_CURRENT, str_name);

		str_name = "MON.WARNING.INLET_PRESSURE_SWITCH";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_INLET_PRESSURE_SWITCH, str_name);

		str_name = "MON.WARNING.BLOWER_1_VFD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_BLOWER_1_VFD, str_name);

		str_name = "MON.WARNING.BLOWER_MOTOR_CONTACTOR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_BLOWER_MOTOR_CONTACTOR, str_name);

		str_name = "MON.WARNING.BLOWER_MOTOR_OVERLOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_BLOWER_MOTOR_OVERLOAD, str_name);

		str_name = "MON.WARNING.BLOWER_BODY_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_BLOWER_BODY_TEMPERATURE, str_name);

		str_name = "MON.WARNING.BLOWER_VFD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_WARNING_BLOWER_VFD, str_name);
	}

	// PUMP ALARM ...
	{
		str_name = "MON.ALARM.PUMP_BODY_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PUMP_BODY_TEMPERATURE, str_name);

		str_name = "MON.ALARM.EXHAUST_PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_EXHAUST_PRESSURE, str_name);

		str_name = "MON.ALARM.MISSING_OIL_TIMEOUT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_MISSING_OIL_TIMEOUT, str_name);

		str_name = "MON.ALARM.PUMP_MOTOR_CONTACTOR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PUMP_MOTOR_CONTACTOR, str_name);

		str_name = "MON.ALARM.PUMP_MOTOR_OVERLOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PUMP_MOTOR_OVERLOAD, str_name);

		str_name = "MON.ALARM.BLOWER_BODY_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_BLOWER_BODY_TEMPERATURE, str_name);

		str_name = "MON.ALARM.EMO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_EMO, str_name);

		str_name = "MON.ALARM.PUMP_MOTOR_OVER_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PUMP_MOTOR_OVER_TEMPERATURE, str_name);

		str_name = "MON.ALARM.BLOWER_MOTOR_CONTACTOR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_BLOWER_MOTOR_CONTACTOR, str_name);

		str_name = "MON.ALARM.EXHAUST_MANIFOLD_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_EXHAUST_MANIFOLD_TEMPERATURE, str_name);

		str_name = "MON.ALARM.BLOWER_MOTOR_OVERLOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_BLOWER_MOTOR_OVERLOAD, str_name);

		str_name = "MON.ALARM.PURGE_FLOW_ANALOG_1";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PURGE_FLOW_ANALOG_1, str_name);

		str_name = "MON.ALARM.PURGE_FLOW_ANALOG_2";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PURGE_FLOW_ANALOG_2, str_name);

		str_name = "MON.ALARM.BLOWER_MOTOR_OVER_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_BLOWER_MOTOR_OVER_TEMPERATURE, str_name);

		str_name = "MON.ALARM.H2O_FLOW";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_H2O_FLOW, str_name);

		str_name = "MON.ALARM.PUMP_MOTOR_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ALARM_PUMP_MOTOR_CURRENT, str_name);
	}

	// ANALOG VALUE ...
	{
		str_name = "MON.PUMP_BODY_TEMPERATURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMP_BODY_TEMPERATURE, str_name);

		str_name = "MON.EXHAUST_PRESSURE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_EXHAUST_PRESSURE, str_name);

		str_name = "MON.PUMP_MOTOR_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMP_MOTOR_CURRENT, str_name);

		str_name = "MON.BLOWER_MOTOR_CURRENT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_BLOWER_MOTOR_CURRENT, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0,MON_ID__IO_MONITOR);
	}
	return 1;
}
int CObj__LOT_SERIAL::__DEFINE__ALARM(p_alarm)
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
		alarm_title += "Pump Offline !";

		alarm_msg = "Check the status of communication !";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// ...
	{
		alarm_id = ALID__PUMP_ALARM;

		alarm_title  = title;
		alarm_title += "Pump Alarm !";

		alarm_msg = "Please, check the status of pump !";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BLOWER_WARNING;

		alarm_title  = title;
		alarm_title += "Blower Warning !";

		alarm_msg = "Please, check the status of blower !";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PUMP_WARNING;

		alarm_title  = title;
		alarm_title += "Pump Warning !";

		alarm_msg = "Please, check the status of pump !";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


// ...
#define _LIST__MODE_SET					\
"Stop  Start							\
 Stop.Slow  Flush"


int CObj__LOT_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// DO ...
	{
		str_name = "edo.MODE_SET";
		IO__ADD_DIGITAL_WRITE(str_name, _LIST__MODE_SET);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__MODE_SET, str_name);
	}

	// SI ...
	{
		str_name = "esi.MODE_STS";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__MODE_STS, str_name);

		str_name = "esi.VERSION";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VERSION, str_name);

		//
		str_name = "esi.PUMP_WARNING";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PUMP_WARNING, str_name);
		
		str_name = "esi.BLOWER_WARNING";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__BLOWER_WARNING, str_name);

		str_name = "esi.PUMP_ALARM";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PUMP_ALARM, str_name);

		//
		str_name = "esi.PUMP_BODY_TEMPERATURE";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PUMP_BODY_TEMPERATURE, str_name);
		
		str_name = "esi.EXHAUST_PRESSURE";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__EXHAUST_PRESSURE, str_name);
		
		str_name = "esi.PUMP_MOTOR_CURRENT";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PUMP_MOTOR_CURRENT, str_name);

		str_name = "esi.BLOWER_MOTOR_CURRENT";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__BLOWER_MOTOR_CURRENT, str_name);
	}	

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__LOT_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString file_name;
	CString log_msg;

	CString def_name;
	CString obj_name;
	CString ch_name;
	CString var_name;

	// ...
	{
		file_name.Format("%s_APP.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP__LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP__LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xAPP__LOG_CTRL->DISABLE__TIME_LOG();
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		xAPP__LOG_CTRL->ENABLE__TIME_LOG();
		xAPP__LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		file_name.Format("%s-DRV.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xDRV__LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xDRV__LOG_CTRL->SET__PROPERTY(file_name, 2*3, 30);

		xDRV__LOG_CTRL->DISABLE__TIME_LOG();
		xDRV__LOG_CTRL->WRITE__LOG(log_msg);

		xDRV__LOG_CTRL->ENABLE__TIME_LOG();
		xDRV__LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__LOT_SERIAL
::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter
	//------------------------------------------------------
	// ...
	int com_port = -1;

	int nBaudRate = 9600;
	int nDataBit  =    8;		// 5, 6, 7, 8
	int nParity   =    0;		// 0, 1, 2, 3, 4  // 0 ~ 4 : No, Odd, Even, Mark, Space
	int nStopBit  =    1;		// 1, 2

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

		log_bff.Format("Baud Rate: %1d \n", nBaudRate);
		log_msg += log_bff;

		log_bff.Format("Data Bit: %1d \n", nDataBit);
		log_msg += log_bff;

		log_bff.Format("Parity Bit: %1d \n", nParity);
		log_msg += log_bff;

		log_bff.Format("Stop Bit: %1d \n", nStopBit);
		log_msg += log_bff;

		//
		log_msg += "Terminal String : Out <CR>, In <CR><LF> \n";							  
	}

	// ...
	{
		CString str_info;

		str_info.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d]",
						nBaudRate, 
						nDataBit, 
						nStopBit, 
						nParity);

		sCH__INFO_DRV_PARAMETER->Set__DATA(str_info);
	}

	if(iActive__SIM_MODE > 0)
	{
		log_msg += "Initialize RS-232 Complete \n";
		log_msg += "Simulation Mode !!! \n";

		WRITE__APP_LOG_MSG(log_msg);
		WRITE__DRV_LOG_MSG(log_msg);
		return -1;
	}

	if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
	{
		log_bff.Format("Fail to do INIT__COMPORT: %d, ret:-1\n", com_port);
		log_msg += log_bff;

		WRITE__APP_LOG_MSG(log_msg);
		WRITE__DRV_LOG_MSG(log_msg);
		return -1;
	}
	else
	{
		log_msg += "Initialize RS-232 Complete \n";

		WRITE__APP_LOG_MSG(log_msg);
		WRITE__DRV_LOG_MSG(log_msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__LOT_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;	

		 IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable,p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__LOCAL)					flag = Call__LOCAL(p_variable,p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__REMOTE)					flag = Call__REMOTE(p_variable,p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__ON)						flag = Call__ON(p_variable,p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__AUTO_SHUTDOWN)			flag = Call__AUTO_SHUTDOWN(p_variable,p_alarm);
	ELSE_IF__CTRL_MODE(sMODE__FAST_SHUTDOWN)			flag = Call__FAST_SHUTDOWN(p_variable,p_alarm);

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		WRITE__APP_LOG_MSG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		WRITE__APP_LOG_MSG(log_msg);
	}

	return flag;
}

int CObj__LOT_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
	case MON_ID__IO_MONITOR:
		Mon__IO_MONITOR(p_variable,p_alarm);
		break;
	}
	return 1;
}
