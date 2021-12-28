#include "StdAfx.h"
#include "CObj__OVATION_2560.h"


//--------------------------------------------------------------------------------
CObj__OVATION_2560::CObj__OVATION_2560()
{
	m_nAddress = 0;

	m_nCommSts    = OFFLINE;
	m_nRetryCount = 1;
	
	RF_Ps_Request = 0;
	RF_Ps_state = -1;
}
CObj__OVATION_2560::~CObj__OVATION_2560()
{

}


//--------------------------------------------------------------------------------
int CObj__OVATION_2560::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,		"INIT");

		ADD__CTRL_VAR(sMODE__REMOTE,	"REMOTE");
		ADD__CTRL_VAR(sMODE__LOCAL,		"LOCAL");

		ADD__CTRL_VAR(sMODE__RF_OFF,	"RF_OFF");
		ADD__CTRL_VAR(sMODE__SET_POWER,	"SET_POWER");

		ADD__CTRL_VAR(sMODE__SET_PULSING, "SET_PULSING");
	}
	return 1;
}
int CObj__OVATION_2560::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG Lee \n";

	return 1;
}


// ...
#define MON_ID__STATUS					1
#define MON_ID__STATUS_1				2
#define MON_ID__STATUS_2				3


int CObj__OVATION_2560::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString item_list;

	// ...
	{
		str_name = "CFG.RF.ON.TIMEOUT";
		STD__ADD_ANALOG(str_name, "sec", 1, 0, 5.0);
		LINK__VAR_ANALOG_CTRL(aCH__RF_ON_TIMEOUT, str_name);

		str_name = "DRV.LOG.PARAM.LOG.START";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STOP START","");
		LINK__VAR_DIGITAL_CTRL(dCH__DRV_LOG_PARAM_START_STOP,str_name);

		str_name = "PARA.PULSING.MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"STANDARD PULSING","");
		LINK__VAR_DIGITAL_CTRL(dCH__Pulsing_Mode,str_name);

		str_name = "APP.OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		//str_name = "CFG.FREQ.TUNE.DELAY";
		//STD__ADD_ANALOG(str_name, "msec", 0, 100, 10000);
		//LINK__VAR_ANALOG_CTRL(aCH__FREQ_TUNE_DELAY, str_name);

		//str_name = "SET.POWER";
		//STD__ADD_ANALOG(str_name, "Watt", 0, 0, 2500);
		//LINK__VAR_ANALOG_CTRL(aCH__SET_POWER, str_name);

		str_name = "PARA.TUNE.DELAY";
		STD__ADD_ANALOG(str_name, "msec", 0, 100, 10000);
		LINK__VAR_ANALOG_CTRL(aCH__FREQ_TUNE_DELAY, str_name);

		str_name = "PARA.SET.POWER";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Watt", 0, 0, 2500, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__SET_POWER, str_name);

		str_name = "CFG.RF.ON.CMD";
		STD__ADD_DIGITAL(str_name,"OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__RF_CMD, str_name);
	}

	// Pulsing parameter
	{
		str_name = "PARA.PULSING.FREQ.SET";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Hz", 0, 10, 100000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__Ps_Frequency_Set, str_name);

		str_name = "PARA.PULSING.DUTY.SET";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 0, 10, 90, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__Ps_Duty_Set, str_name);

		str_name = "MON.PULSING.FREQ";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Hz", 0, 10, 100000, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__Ps_Frequency, str_name);

		str_name = "MON.PULSING.DUTY.SET";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "%", 0, 10, 90, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__Ps_Duty, str_name);
	}

	// Dummy Not use
	{
		//str_name = "SET.TUNE.USE";
		//item_list = "Off On";
		//STD__ADD_DIGITAL(str_name, item_list);
		//LINK__VAR_DIGITAL_CTRL(dCH__SET_TUNE_USE, str_name);

		str_name = "PARA.TUNE.USE";
		item_list = "OFF ON";
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(dCH__SET_TUNE_USE, str_name);
	}

	// ...
	{
		str_name = "RAMP.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__RAMP_TIME, str_name);

		str_name = "PARA.RAMP.UP.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__RAMP_UP_TIME, str_name);

		str_name = "PARA.RAMP.DOWN.TIME";
		STD__ADD_ANALOG(str_name, "msec", 0, 0, 30000);
		LINK__VAR_ANALOG_CTRL(aCH__RAMP_DN_TIME, str_name);

		str_name = "MON.FORWARD.POWER";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Watt", 0, 0, 999999, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__FWD_Power, str_name);

		str_name = "MON.REFLECT.POWER";
		STD__ADD_ANALOG_WITH_OPTION(str_name, "Watt", 0, 0, 999999, -1, "L", "");
		LINK__VAR_ANALOG_CTRL(aCH__REFL_Power, str_name);

		//str_name = "SET.START.FREQUENCY";
		//STD__ADD_ANALOG(str_name, "kHz", 0, 0, 999999);
		//LINK__VAR_ANALOG_CTRL(aCH__SET_START_FREQUENCY, str_name);

		//str_name = "SET.OUTPUT.FREQUENCY";
		//STD__ADD_ANALOG(str_name, "kHz", 0, 0, 999999);
		//LINK__VAR_ANALOG_CTRL(aCH__SET_OUTPUT_FREQUENCY, str_name);

		str_name = "PARA.START.FREQUENCY";
		STD__ADD_ANALOG(str_name, "kHz", 0, 0, 999999);
		LINK__VAR_ANALOG_CTRL(aCH__SET_START_FREQUENCY, str_name);

		str_name = "PARA.OUTPUT.FREQUENCY";
		STD__ADD_ANALOG(str_name, "kHz", 0, 0, 999999);
		LINK__VAR_ANALOG_CTRL(aCH__SET_OUTPUT_FREQUENCY, str_name);

		str_name = "FREQ.VALUE";
		STD__ADD_ANALOG(str_name, "KHz", 0, 0, 999999);
		LINK__VAR_ANALOG_CTRL(aCH__FREQ_Value, str_name);
	}

	// Monitor flag ...
	{
		str_name.Format("MONITOR.FLAG");
		item_list.Format("Off On");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(dCH__MONITOR_FLAG, str_name);

		str_name.Format("APP.CSR.CODE.NUM");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CSR_CODE_NUM, str_name);
	}

	// ...
	{
		str_name.Format("vdo.Ramp.Mode");
		item_list.Format("Disable WattSec Timed");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdoCH__Ramp_Mode, str_name);

		str_name.Format("vdo.Output.Regulation.Mode");
		item_list.Format("Unknown DeliveredOrLoad");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Output_Regulation_Mode, str_name);

		str_name.Format("vdi.Output.Regulation.Mode");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Output_Regulation_Mode, str_name);

		str_name.Format("vai.Ramp.Up");
		STD__ADD_ANALOG(str_name, "Watt", 1, 0, 9999);
		LINK__VAR_ANALOG_CTRL(vaiCH__Ramp_Up, str_name);

		str_name.Format("vai.Ramp.Down");
		STD__ADD_ANALOG(str_name, "Watt", 1, 0, 9999);
		LINK__VAR_ANALOG_CTRL(vaiCH__Ramp_Down, str_name);
	}

	// Process Status
	{
		// Byte[0]
		str_name.Format("vdi.Tunning.Status");
		item_list.Format("Unknown NotTuned Tuned");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Tunning_Status, str_name);

		str_name.Format("vdi.SetPoint.Ramp");
		item_list.Format("Unknown RampInProgress");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__SetPoint_Ramp, str_name);

		str_name.Format("vdi.RFOutput.Power");
		item_list.Format("Unknown Off On");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__RFOutput_Power, str_name);

		str_name.Format("vdi.RFON.Request");
		item_list.Format("Unknown Off On");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__RFOn_Request, str_name);

		str_name.Format("vdi.SetPoint.Tolerance");
		item_list.Format("Unknown InTolerance OutOfTolerance");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__SetPoint_Tolerance, str_name);

		// Byte[1]
		str_name.Format("vdi.ColdPlate.OverTemp.Fault");
		item_list.Format("Unknown Normal Fault");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__ColdPlate_OverTemp_Fault, str_name);

		str_name.Format("vdi.Interlock.Open");
		item_list.Format("Unknown Closed Open");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Interlock_Open, str_name);

		// Byte[2] Reserved..

		// Byte[3]
		str_name.Format("vdi.Inverter.Ready");
		item_list.Format("Unknown Ready NotReady");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Inverter_Ready, str_name);

		str_name.Format("vdi.Fault.Status");
		item_list.Format("Unknown Normal Fault");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Fault_Status, str_name);

		str_name.Format("vdi.Warning.Status");
		item_list.Format("Unknown Normal Warning");
		STD__ADD_DIGITAL(str_name, item_list);
		LINK__VAR_DIGITAL_CTRL(vdiCH__Warning_Status, str_name);
	}

	// Impedance
	{
		str_name.Format("vsi.Impedance.Real");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(vsiCH__Impedance_Real, str_name);

		str_name.Format("vsi.Impedance.Imaginary");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(vsiCH__Impedance_Imaginary, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(2.0, MON_ID__STATUS);
		p_variable->Add__MONITORING_PROC(5.0, MON_ID__STATUS_1);
		p_variable->Add__MONITORING_PROC(5.0, MON_ID__STATUS_2);
	}
	return 1;
}

int CObj__OVATION_2560::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += " - RF SYSTEM : AE RF Generator Offline.";

		alarm_msg = "Check the Online !";
	
		l_act.RemoveAll();
		l_act.Add("CHECK");
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__REMOTE_ALARM;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : AE RF Generator Remote.";

		alarm_msg = "Please, check RF Control Mode.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__SEND_COMMAND_FAIL;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : AE RF Generator Command Send Fail.";

		alarm_msg = "Please, check RF Controller Online.";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_CONTACTOR_ALARM;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : RF AC Contactor Alarm.";
	
		alarm_msg = "RF AC Contactor is not Enable.";
		alarm_msg += "Please. Check the RF AC COntactor Status";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_ON_TIMEOUT_ALARM;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : RF On Timeout Alarm.";
	
		alarm_msg = "RF Sensor is not On.";
		alarm_msg += "Please. Check RF Sensor Status";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INTERLOCK_ALARM;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : RF Interlock Alarm.";
	
		alarm_msg = "RF Interlock Switch is not True.";
		alarm_msg += "Please. Check RF Interlock Switch Status";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_WATERFLOW_ALARM;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : RF Water Flow Alarm.";
	
		alarm_msg = "RF Water Flow Switch is not On.";
		alarm_msg += "Please. Check RF Water Flow Switch Status";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_OVERTEMP_ALARM;
	
		alarm_title = title;
		alarm_title += " - RF SYSTEM : RF Over Temp Alarm.";
	
		alarm_msg = "RF Over Temp Switch is not Normal.";
		alarm_msg += "Please. Check RF Over Temp Switch Status";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_OVERTIME_ALARM;

		alarm_title = title;
		alarm_title += " - RF SYSTEM : RF On Over Time Alarm.";

		alarm_msg = "RF has been On for too long.";
		alarm_msg += "Please. Check RF Generator";
		alarm_msg += "Please. Check RS232 Communication";

		l_act.RemoveAll();
		l_act.Add("CHECK");

		ADD__ALARM_EX(alarm_id, alarm_title, alarm_msg, l_act);
	}

	return 1;
}

int CObj__OVATION_2560
::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	// ...
	CString str_name;
	CString item_list;

	// AO ...
 	{
		str_name = "ao.Set.Power";
		IO__ADD_ANALOG_WRITE__WITH_OPTION(str_name, "Watt", 3, 0, 9999, "-", "", "", -1, "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__SetPower, str_name);

		str_name = "ao.Power.Limit";
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "Watt", 3, 0, 9999, "-", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Power_Limit, str_name);

		str_name = "ao.RampUp.Time";
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "msec", 1, 8, 65534, "-", "", "");	// Default : 0.008 sec
		LINK__IO_VAR_ANALOG_CTRL(aoCH__RampUp_Time, str_name);

		str_name = "ao.RampDown.Time";
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "msec", 1, 8, 65534, "-", "", "");	// Default : 0.008 sec
		LINK__IO_VAR_ANALOG_CTRL(aoCH__RampDown_Time, str_name);

		str_name = "ao.RF.Freq";			// Fixed Mode에서 Output Frequency
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "kHz", 0, 0, 65534, "61", "", "");	// 32 bit이므로...(65534)
		LINK__IO_VAR_ANALOG_CTRL(aoCH__RF_Freq, str_name);

		str_name = "ao.Start.Freq";			// Tune Frequency
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "kHz", 0, 0, 65534, "46", "", "");	// 32 bit이므로...(65534)
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Start_Freq, str_name);

		// Tunning
		str_name = "ao.Set.Tunning.Timeout";
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "msec", 0, 0, 65534, "38", "", "");	// 32 bit이므로...(65534)
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Set_Tuning_Timeout, str_name);

		str_name = "ao.HostPort.Timeout";
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "msec", 0, 0, 65534, "40", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__HostPort_Timeout, str_name);

		str_name = "ao.Tune.Delay";			// Tune Delay
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "msec", 0, 0, 32767, "60", "", "");	// 16 bit이므로...(32767)
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Tune_Delay, str_name);

		// Pulsing...
		str_name = "ao.PULSING.FREQ.SET";			// Pulsing Frequency
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "Hz", 0, 10, 100000, "93", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Ps_Frequency_Set, str_name);

		str_name = "ao.PULSING.DUTY.SET";			// Pulsing Duty
		IO__ADD_ANALOG_WRITE__MANUAL_EX(str_name, "%", 0, 10, 90, "96", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aoCH__Ps_Duty_Set, str_name);
		//
	}

	// AI ...
	{
		str_name = "ai.Forward.Power";
		IO__ADD_ANALOG_READ__WITH_OPTION(str_name, "Watt", 1, 0, 9999, "-", "", "", -1, "");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__ForwardPower, str_name);
		
		str_name = "ai.Reflect.Power";
		IO__ADD_ANALOG_READ__WITH_OPTION(str_name, "Watt", 1, 0, 9999, "-", "", "", -1, "");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__ReflectPower, str_name);

		str_name = "ai.Delivered.Power";
		IO__ADD_ANALOG_READ__WITH_OPTION(str_name, "Watt", 1, 0, 9999, "-", "", "", -1, "");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__DeliveredPower, str_name);

		str_name = "ai.WhenOn.Actual.Frequency";
		IO__ADD_ANALOG_READ__MANUAL_EX(str_name, "kHz", 0, 0, 65534, "147", "", "");	// 32 bit이므로...(65534)
		LINK__IO_VAR_ANALOG_CTRL(aiCH__WhenOn_Actual_Frequency, str_name);

		// Pulsing...
		str_name = "ai.PULSING.FREQ";			// Pulsing Frequency
		IO__ADD_ANALOG_READ__MANUAL_EX(str_name, "Hz", 0, 10, 100000, "93", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__Ps_Frequency, str_name);

		str_name = "ai.PULSING.DUTY";			// Pulsing Duty
		IO__ADD_ANALOG_READ__MANUAL_EX(str_name, "%", 0, 10, 90, "96", "", "");
		LINK__IO_VAR_ANALOG_CTRL(aiCH__Ps_Duty, str_name);
		//
	}
	
	// DO ...
	{
		str_name  = "do.RF.Cmd";
		item_list = "Off On";
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "-", "","");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__RF_CMD, str_name);

		str_name  = "do.Control.Mode";
		item_list = "Local Remote";
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "-", "","");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__CONTROL_MODE, str_name);

		str_name  = "do.Frequency.Control.Mode";
		item_list = "Fixed Variable";
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "-", "","");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__FREQUENCY_CONTROL_MODE, str_name);

		str_name  = "do.Pulsing.Mode.Set";
		item_list = "Standard Pulsing";
		IO__ADD_DIGITAL_WRITE__MANUAL_EX(str_name, item_list, "-", "","");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__Pulsing_Mode_Set, str_name);
	}
	// DI ...
	{
		str_name  = "di.Comm.Sts";
		item_list = "Unknown Offline Online";
		IO__ADD_DIGITAL_READ__MANUAL_EX(str_name, item_list, "-", "","");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);

		str_name  = "di.Control.Mode";
		item_list = "Unknown Local Remote";
		IO__ADD_DIGITAL_READ__MANUAL_EX(str_name, item_list, "-", "","");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__CONTROL_MODE, str_name);

		str_name  = "di.Process.Status";
		item_list = "Unknown ReadOk";
		IO__ADD_DIGITAL_READ__MANUAL_EX(str_name, item_list, "162", "","");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__Process_Status, str_name);

		str_name  = "di.Pulsing.Status";
		item_list = "Disable Enable";
		IO__ADD_DIGITAL_READ__MANUAL_EX(str_name, item_list, "172", "","");
		LINK__IO_VAR_DIGITAL_CTRL(diCH__Pulsing_Status, str_name);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__OVATION_2560
::__INITIALIZE__OBJECT(p_variable, p_ext_obj_create)
{
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xAPP_LOG_CTRL->DISABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);

		xAPP_LOG_CTRL->ENABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_Drv.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString obj_name;
	CString var_name;

	// IO Channel
	{
		def_name = "IO__OBJ";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_name = "VAR__RF_OVERTIME_SNS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_OVERTIME_SNS, obj_name,var_name);

		def_name = "VAR__RF_ALIVE_INTLK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__RF_ALIVE_INTLK, obj_name,var_name);
	}

	return 1;
}

int CObj__OVATION_2560
::__INITIALIZE__IO(p_io_para)
{
	int com_port  = -1;
	
	int nBaudRate = 19200;
	int nDataBit  =     8;
	int nParity   =     1;		// 0, 1, 2, 3, 4  // 0 ~ 4 : No, Odd, Even, Mark, Space
	int nStopBit  =     1;

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
		CString msg;
		CString bff;

		msg  = "\n";
		msg += "Connect to Serial ...";
		msg += "\n";

		bff.Format("  * Com Port  : %1d \n", com_port);
		msg += bff;

		bff.Format("  * Baud Rate : %1d \n", nBaudRate);
		msg += bff;

		bff.Format("  * Data Bit  : %1d \n", nDataBit);
		msg += bff;

		bff.Format("  * Parity    : %1d \n", nParity);
		msg += bff;

		bff.Format("  * Stop Bit  : %1d \n", nStopBit);
		msg += bff;

		bff.Format("  * Retry Count : %1d \n", m_nRetryCount);
		msg += bff;

		m_nTimeout = 1000;
		bff.Format("  * Timeout   : %1d msec \n", m_nTimeout);
		msg += bff;

		m_nAddress = 1;
		bff.Format("  * Address   : %1d \n", m_nAddress);
		msg += bff;

		Fnc__WRITE_LOG(msg);
	}

	// ...
	{
		CString msg;

		mX_Serial->RTS__CHECK_SKIP();

		if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
		{
			msg.Format("INIT__COMPORT(%d) : Error !", com_port);
			return -1;
		}
		else
		{
			msg.Format("RS232 Completed ...");
		}

		Fnc__WRITE_LOG(msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__OVATION_2560
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;
		
	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);
		//ELSE_IF__CTRL_MODE(sMODE__RF_OFF)			flag = Call__RF_OFF(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RF_OFF)			flag = Call__OFF(p_variable, p_alarm);
		//ELSE_IF__CTRL_MODE(sMODE__SET_POWER)		flag = Call__SET_POWER(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SET_POWER)		flag = FNC__PROC_SEQ(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__REMOTE)			flag = Call__REMOTE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__LOCAL)			flag = Call__LOCAL(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SET_PULSING)		flag = FNC__PULSING_SEQ(p_variable, p_alarm);
		else
		{
			flag = -1;

			Fnc__WRITE_LOG("Invalid Function Mode (%s)", mode);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);	
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);
		
		sCH__OBJ_MSG->Set__DATA(log_msg);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__OVATION_2560
::__CALL__MONITORING(id, p_variable, p_alarm)
{
	if		(id == MON_ID__STATUS)
	{
		Call__STATUS_MON(p_variable, p_alarm);
	}
	else if (id == MON_ID__STATUS_1)
	{
		Call__STATUS_MON_1(p_variable, p_alarm);
	}
	else if (id == MON_ID__STATUS_2)
	{
		Call__Alive_Signal(p_variable, p_alarm);
	}

	return 1;
}

