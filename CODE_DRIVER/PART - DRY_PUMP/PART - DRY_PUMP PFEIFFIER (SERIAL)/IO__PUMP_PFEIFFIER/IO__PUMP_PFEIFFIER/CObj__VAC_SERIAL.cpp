#include "StdAfx.h"
#include "CObj__VAC_SERIAL.h"
#include "CObj__VAC_SERIAL__DEF.h"
#include "CCommon_DEF.h"



//--------------------------------------------------------------------------------
CObj__VAC_SERIAL::CObj__VAC_SERIAL()
{

}
CObj__VAC_SERIAL::~CObj__VAC_SERIAL()
{

}

//--------------------------------------------------------------------------------
int CObj__VAC_SERIAL::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	// ...
	{
		sObject_Name = obj;
	}

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__LOCAL,  "LOCAL");
		ADD__CTRL_VAR(sMODE__REMOTE, "REMOTE");

		//
		CString sMODE__PUMP_START;
		int  Call__PUMP_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

		CString sMODE__PUMP_STOP;
		int  Call__PUMP_STOP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

		//
		CString sMODE__ROOTS_START;
		int  Call__ROOTS_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

		CString sMODE__ROOTS_STOP;
		int  Call__ROOTS_STOP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

		//
		CString sMODE__PURGE_START;
		int  Call__PURGE_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

		CString sMODE__PURGE_STOP;
		int  Call__PURGE_STOP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	}

	return 1;
}
int CObj__VAC_SERIAL::__DEFINE__VERSION_HISTORY(version)
{
	version = "By JG Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR						1

int CObj__VAC_SERIAL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CString str_name;
	
	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		//
		str_name = "MON.COMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STS,str_name);
	}

	// MON...
	{
		str_name = "MON.VERSION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_VERSION, str_name);
	}

	// MON.STATE...
	{
		str_name = "MON.STATE.PUMP_RUNNING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_PUMP_RUNNING, str_name);

		str_name = "MON.STATE.ROOTS_RUNNING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_ROOTS_RUNNING, str_name);

		str_name = "MON.STATE.N2_VALVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_N2_VALVE, str_name);

		str_name = "MON.STATE.STDBY_VALVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_STDBY_VALVE, str_name);

		str_name = "MON.STATE.WATER_VALVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_WATER_VALVE, str_name);

		str_name = "MON.STATE.INLET_VALVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_INLET_VALVE, str_name);

		str_name = "MON.STATE.PERMIT_VALVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_PERMIT_VALVE, str_name);

		str_name = "MON.STATE.HP_FB_VALVE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_HP_FB_VALVE, str_name);

		str_name = "MON.STATE.HEAT1_POWER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_HEAT1_POWER, str_name);

		str_name = "MON.STATE.FAULT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_FAULT, str_name);

		str_name = "MON.STATE.CONTROL_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_STATE_CONTROL_MODE, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0,MON_ID__IO_MONITOR);
	}
	return 1;
}
int CObj__VAC_SERIAL::__DEFINE__ALARM(p_alarm)
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
		l_act.Add("RETRY");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	
	// ...
	{
		alarm_id = ALID__PUMP_ALARM;

		alarm_title  = title;
		alarm_title += "Pump Alarm !";

		alarm_msg = "Please, check the status of pump !";

		l_act.RemoveAll();
		l_act.Add("RETRY");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__BLOWER_WARNING;

		alarm_title  = title;
		alarm_title += "Blower Warning !";

		alarm_msg = "Please, check the status of blower !";

		l_act.RemoveAll();
		l_act.Add("RETRY");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PUMP_WARNING;

		alarm_title  = title;
		alarm_title += "Pump Warning !";

		alarm_msg = "Please, check the status of pump !";

		l_act.RemoveAll();
		l_act.Add("RETRY");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


// ...
#define _LIST__MODE_SET					\
"Pump.Stop   Pump.Start					\
 Roots.Stop  Roots.Start				\
 Purge.Stop  Purge.Start"


int CObj__VAC_SERIAL::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;

	// DO ...
	{
		str_name = "do.PUMP_ADDRESS";
		IO__ADD_DIGITAL_WRITE(str_name, "Set");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__PUMP_ADDRESS, str_name);

		str_name = "do.SERPERATOR_CHAR";
		IO__ADD_DIGITAL_WRITE(str_name, "Set");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__SERPERATOR_CHAR, str_name);

		//
		str_name = "do.MODE_SET";
		IO__ADD_DIGITAL_WRITE(str_name, _LIST__MODE_SET);
		LINK__IO_VAR_DIGITAL_CTRL(doCH__MODE_SET, str_name);
	}

	// SI ...
	{
		str_name = "esi.VERSION";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VERSION, str_name);

		str_name = "esi.PUMP_STATE";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__PUMP_STATE, str_name);
	}	

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VAC_SERIAL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	m_nCommState = OFFLINE;
	return 1;
}
int CObj__VAC_SERIAL
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

		// 2.
		{
			para_cmmd = "ADDRESS_ID";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				iPara__ADDR_ID = atoi(para_data);
			}
			else
			{
				iPara__ADDR_ID = 0;
			}
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		// ...
		{
			file_name.Format("%s-DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			// ...
			{
				xDRV__LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
				xDRV__LOG_CTRL->SET__PROPERTY(file_name, 2*3, 30);

				xDRV__LOG_CTRL->DISABLE__TIME_LOG();
				xDRV__LOG_CTRL->WRITE__LOG(log_msg);

				xDRV__LOG_CTRL->ENABLE__TIME_LOG();
				xDRV__LOG_CTRL->WRITE__LOG("   START   \n");
			}
		}
	}

	// ...
	CString log_msg;
	CString log_bff;

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

	// ...
	{
		sPROTOCOL_INFO.Format("Rate[%1d] DataBit[%1d] StopBit[%1d] Parity[%1d] \n",
								nBaudRate, 
								nDataBit, 
								nStopBit, 
								nParity);

		sPROTOCOL_INFO += "Terminal String : Byte Count \n";							  
	}

	if(iActive__SIM_MODE > 0)
	{
		log_msg += "Initialize RS-232 Complete \n";
		log_msg += "Simulation Mode !!! \n";

		WRITE__DRV_LOG_MSG(log_msg);
		return -1;
	}

	if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
	{
		log_bff.Format("Fail to do INIT__COMPORT: %d, ret:-1\n", com_port);
		log_msg += log_bff;

		WRITE__DRV_LOG_MSG(log_msg);
		return -1;
	}
	else
	{
		log_msg += "Initialize RS-232 Complete \n";

		WRITE__DRV_LOG_MSG(log_msg);
	}

	sCH__MON_COMM_STS->Set__DATA(STR__ONLINE);
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__VAC_SERIAL::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;	

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LOCAL)				flag = Call__LOCAL(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)				flag = Call__REMOTE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PUMP_START)			flag = Call__PUMP_START(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PUMP_STOP)			flag = Call__PUMP_STOP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ROOTS_START)			flag = Call__ROOTS_START(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ROOTS_STOP)			flag = Call__ROOTS_STOP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PURGE_START)			flag = Call__PURGE_START(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PURGE_STOP)			flag = Call__PURGE_STOP(p_variable, p_alarm);
	}

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
	
int CObj__VAC_SERIAL::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
	case MON_ID__IO_MONITOR:
		Mon__IO_MONITOR(p_variable,p_alarm);
		break;
	}
	return 1;
}
