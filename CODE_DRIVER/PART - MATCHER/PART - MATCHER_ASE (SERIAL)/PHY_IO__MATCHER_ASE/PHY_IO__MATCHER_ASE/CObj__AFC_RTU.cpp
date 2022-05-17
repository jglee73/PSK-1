#include "StdAfx.h"
#include "CObj__AFC_RTU.h"
#include "CObj__AFC_RTU__ALID.h"
#include "CObj__AFC_RTU__DEF.h"


//--------------------------------------------------------------------------------
CObj__AFC_RTU::CObj__AFC_RTU()
{

}
CObj__AFC_RTU::~CObj__AFC_RTU()
{

}

//--------------------------------------------------------------------------------
int CObj__AFC_RTU::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,   "INIT");

		ADD__CTRL_VAR(sMODE__AUTO,   "POWER.ON");
		ADD__CTRL_VAR(sMODE__MANUAL, "POWER.OFF");
	}
	return 1;
}
int CObj__AFC_RTU::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1

#define  APP_DSP__MON_MODE				"IDLE  RUN"
#define  APP_DSP__OFF_ON				"OFF   ON"


int CObj__AFC_RTU::__DEFINE__VARIABLE_STD(p_variable)
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

	// PARA ...
	{
		str_name = "PARA.LOAD_POSITION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_LOAD_POSITION, str_name);

		str_name = "PARA.TUNE_POSITION";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "%", 2, 0, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_TUNE_POSITION, str_name);
	}

	// PARA.DRV ...
	{
		str_name = "PARA.DRV.CTRL_MODE";
		STD__ADD_DIGITAL(str_name, "AUTO  MANUAL");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_DRV_CTRL_MODE, str_name);

		str_name = "PARA.DRV.PRESET";
		STD__ADD_DIGITAL(str_name, "DISABLE  ENABLE");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_DRV_PRESET, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.COM_PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_COM_PORT, str_name);

		str_name = "INFO.PROTOCOL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PROTOCOL, str_name);

		str_name = "INFO.MODBUS_ADDR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_MODBUS_ADDR, str_name);

		str_name = "INFO.BAUD_RATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_BAUD_RATE, str_name);

		str_name = "INFO.COMM_PARITY";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_COMM_PARITY, str_name);

		str_name = "INFO.DATA_BIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DATA_BIT, str_name);
	
		str_name = "INFO.STOP_BIT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_STOP_BIT, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMM_STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STATE, str_name);

		//
		str_name = "MON.MAT_STS.MANUAL.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_MANUAL_ACTIVE, str_name);

		str_name = "MON.MAT_STS.PRESET_ENABLE.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_PRESET_ENABLE_ACTIVE, str_name);

		str_name = "MON.MAT_STS.ALARM.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_ALARM_ACTIVE, str_name);

		str_name = "MON.MAT_STS.RFON.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_RFON_ACTIVE, str_name);

		str_name = "MON.MAT_STS.TUNE_MATCHED.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_TUNE_MATCHED_ACTIVE, str_name);

		str_name = "MON.MAT_STS.COAXIAL_ALARM.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_COAXIAL_ALARM_ACTIVE, str_name);

		str_name = "MON.MAT_STS.COVER_ALARM.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_COVER_ALARM_ACTIVE, str_name);

		str_name = "MON.MAT_STS.MOTOR_ALARM.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_MOTOR_ALARM_ACTIVE, str_name);

		str_name = "MON.MAT_STS.FAN1_ALARM.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_FAN1_ALARM_ACTIVE, str_name);

		str_name = "MON.MAT_STS.FAN2_ALARM.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF  ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_MAT_STS_FAN2_ALARM_ACTIVE, str_name);

		//
		str_name = "MON.CUR.LOAD_POSITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_LOAD_POSITION, str_name);
	
		str_name = "MON.CUR.TUNE_POSITION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_TUNE_POSITION, str_name);

		str_name = "MON.CUR.VPP";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_VPP, str_name);

		str_name = "MON.CUR.VRMS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_VRMS, str_name);

		str_name = "MON.CUR.IRMS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_IRMS, str_name);

		str_name = "MON.CUR.Phase";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CUR_Phase, str_name);

		//
		str_name = "MON.ERROR.CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERROR_CODE, str_name);

		str_name = "MON.ERROR.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERROR_MSG, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__MONITOR);
	}
	return 1;
}


// ...
#define  ACT__CLEAR								\
l_act.RemoveAll();								\
l_act.Add(STR__CLEAR);


int CObj__AFC_RTU::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	CString str_bff;


	// Offline ...
	{
		alarm_id = ALID__OFFLINE;

		alarm_title  = title;
		alarm_title += "Offlne !";

		alarm_msg.Format("Please, check the heater cable !");

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// High limit ...
	{
		alarm_id = ALID__HIGH_LIMIT_ERROR;

		alarm_title  = title;
		alarm_title += "High limit Error !";

		str_bff.Format("Heater power will be turned off. \n");
		alarm_msg += str_bff;

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


int CObj__AFC_RTU::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;

	// SI ...
	{
		str_name = "si.Matcher_State";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__Matcher_State, str_name);

		//
		str_name = "si.Load_Position";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__Load_Position, str_name);

		str_name = "si.Tune_Position";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__Tune_Position, str_name);

		str_name = "si.VPP";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VPP, str_name);

		str_name = "si.VRMS";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VRMS, str_name);

		str_name = "si.IRMS";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__IRMS, str_name);

		str_name = "si.Phase";
		IO__ADD_STRING_READ(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__Phase, str_name);
	}

	// DD ...
	{
		str_name = "do.OP_Mode";
		IO__ADD_DIGITAL_WRITE(str_name, "ON");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__OP_Mode, str_name);
	}

	// AO ...
	{
		str_name = "ao.Preset.Load_Position";
		IO__ADD_ANALOG_WRITE(str_name, "%", 2, 0, 100);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Preset_Load_Position, str_name);
		
		str_name = "ao.Preset.Tune_Position";
		IO__ADD_ANALOG_WRITE(str_name, "%", 2, 0, 100);
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Preset_Tune_Position, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__AFC_RTU::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
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
		SCX__SEQ_INFO x_seq_info;

		iSIM_FLAG = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__AFC_RTU::__INITIALIZE__IO(p_io_para)
{
	int com_port = -1;

	int baud_rate = 19200;
	int data_bit  = 8;    // 8;
	int stop_bit  = 1;    // 1;
	int parity    = 2;    // 2 : Even

	CString str_parity;

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
			para_cmmd = "SLAVE_ID";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				iPara__Slave_ID = atoi(para_data);
			}
			else
			{
				iPara__Slave_ID = 1;
			}
		}
	}

	// ...
	CString log_msg;
	CString log_bff;

	CString str_data;

	// ...
	{
		log_msg.Format("Connecting to Serial ... \n");

		log_bff.Format(" * Com Port: %d \n", com_port);
		log_msg += log_bff;

		log_bff.Format(" * Baud Rate: %1d \n", baud_rate);
		log_msg += log_bff;

		log_bff.Format(" * Data Bit: %1d \n", data_bit);
		log_msg += log_bff;

		// ...
		{
			switch(parity)
			{
				case 0:		str_data = "None";		break;;
				case 1:		str_data = "Odd";		break;;
				case 2:		str_data = "Even";		break;;
				case 3:		str_data = "Mark";		break;;
				case 4:		str_data = "Space";		break;;

				default:	str_data = "???";		break;;
			}

			str_parity = str_data;

			log_bff.Format(" * Parity Bit: %s (%1d) \n", str_data,parity);
			log_msg += log_bff;
		}

		log_bff.Format(" * Stop Bit: %1d \n", stop_bit);
		log_msg += log_bff;

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
		xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		mX_Serial->INIT__COMPORT(com_port, baud_rate, data_bit, stop_bit, parity);
	}

	// ...
	{
		CString ch_data;

		//
		ch_data.Format("%1d", com_port);
		sCH__INFO_COM_PORT->Set__DATA(ch_data);

		ch_data = "Modbus RTU";
		sCH__INFO_PROTOCOL->Set__DATA(ch_data);

		ch_data.Format("%1d", iPara__Slave_ID);
		sCH__INFO_MODBUS_ADDR->Set__DATA(ch_data);

		ch_data.Format("%1d", baud_rate);
		sCH__INFO_BAUD_RATE->Set__DATA(ch_data);

		ch_data.Format("%s (%1d)", str_parity,parity);
		sCH__INFO_COMM_PARITY->Set__DATA(ch_data);

		ch_data.Format("%1d", data_bit);
		sCH__INFO_DATA_BIT->Set__DATA(ch_data);

		ch_data.Format("%1d", stop_bit);
		sCH__INFO_STOP_BIT->Set__DATA(ch_data);
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CObj__AFC_RTU::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;
	int flag = -1;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AUTO)				flag = Call__AUTO(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__MANUAL)			flag = Call__MANUAL(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}
	return flag;
}

int CObj__AFC_RTU::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__MONITOR:	
			Mon__MONITOR(p_variable, p_alarm);
			break;
	}

	return 1;
}

