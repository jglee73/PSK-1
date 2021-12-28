#include "StdAfx.h"
#include "CObj__LBx_CHM_STD.h"
#include "CObj__LBx_CHM_STD__ALID.h"
#include "CObj__LBx_CHM_STD__DEF.h"


//-------------------------------------------------------------------------
CObj__LBx_CHM_STD::CObj__LBx_CHM_STD()
{

}
CObj__LBx_CHM_STD::~CObj__LBx_CHM_STD()
{

}

//-------------------------------------------------------------------------
int CObj__LBx_CHM_STD::
__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__ALL_GAS_VLV_CLOSE, "ALL_GAS_VLV_CLOSE");

		ADD__CTRL_VAR(sMODE__CL_PUMP_VLV, "CL.PUMP_VLV");
		ADD__CTRL_VAR(sMODE__OP_PUMP_VLV, "OP.PUMP_VLV");

		ADD__CTRL_VAR(sMODE__PUMP, "PUMP");
		ADD__CTRL_VAR(sMODE__VENT, "VENT");

		//
		ADD__CTRL_VAR(sMODE__DV_CLOSE,          "DV_CLOSE");
		ADD__CTRL_VAR(sMODE__DV_TRANSFER_CLOSE, "DV_TRANSFER.CLOSE");

		ADD__CTRL_VAR(sMODE__DV_OPEN,           "DV_OPEN");
		ADD__CTRL_VAR(sMODE__DV_TRANSFER_OPEN,  "DV_TRANSFER.OPEN");

		ADD__CTRL_VAR(sMODE__SV_CLOSE,          "SV_CLOSE");
		ADD__CTRL_VAR(sMODE__SV_TRANSFER_CLOSE, "SV_TRANSFER.CLOSE");

		ADD__CTRL_VAR(sMODE__SV_OPEN,           "SV_OPEN");
		ADD__CTRL_VAR(sMODE__SV_TRANSFER_OPEN,  "SV_TRANSFER.OPEN");

		//
		ADD__CTRL_VAR(sMODE__PREPMATER, "PREPMATER");
		ADD__CTRL_VAR(sMODE__COMPMATER, "COMPMATER");

		ADD__CTRL_VAR(sMODE__IN_PROC,  "IN_PROC");
		ADD__CTRL_VAR(sMODE__OUT_PROC, "OUT_PROC");

		ADD__CTRL_VAR(sMODE__AUTO_PUMP_VLV_CLOSE, "AUTO_PUMP_VLV_CLOSE");
	}
	return 1;
}
int CObj__LBx_CHM_STD::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR						2
#define  MON_ID__INTERLOCK						3
#define  MON_ID__PUMP_RUN_INTERLOCK				4
#define  MON_ID__SV_DV_OP_CL_STATUS				5

// ...
#define APP_DSP__CLOSE_OPEN				"UNKNOWN  CLOSE  OPEN"
#define APP_DSP__PRESS_STS				"UNKNOWN  ATM  BTW  VAC"


int CObj__LBx_CHM_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// ...
	str_name = "OTR.OUT.MSG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__MSG,str_name);

	// ...
	str_name = "OTR.OUT.MON.OBJ.STATUS";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS,str_name);

	str_name = "OTR.OUT.MON.PUMP.VLV.OPEN.FLAG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__PUMP_VLV_OPEN_FLAG,str_name);

	str_name = "OTR.OUT.MON.PRESSURE.CTRL.FLAG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__PRESSURE_CTRL_FLAG,str_name);

	//.....
	str_name = "OTR.IN.PARA.aPREHEAT.TIME";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__PARA_PREHEAT_TIME,str_name);

	str_name = "OTR.IN.PARA.aCOOLING.TIME";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__PARA_COOLING_TIME,str_name);

	str_name = "OTR.IN.PARA.aPREMATERIAL.SLOT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",1,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__PARA_PREMATERIAL_SLOT,str_name);

	//.....
	str_name = "OTR.IN.CFG.aDOOR.VALVE.OPEN.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_DOOR_VALVE_OPEN_TIMEOUT, str_name);

	str_name = "OTR.IN.CFG.aDOOR.VALVE.CLOSE.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_DOOR_VALVE_CLOSE_TIMEOUT, str_name);

	//
	str_name = "OTR.IN.CFG.aSLIT.VALVE.OPEN.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SLIT_VALVE_OPEN_TIMEOUT, str_name);

	str_name = "OTR.IN.CFG.aSLIT.VALVE.CLOSE.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SLIT_VALVE_CLOSE_TIMEOUT, str_name);

	//.....
	str_name = "OTR.IN.CFG.aSOFT.PUMP.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_TIMEOUT, str_name);

	//..... 
	str_name = "OTR.IN.CFG.aSOFT.PUMP.COMPLETE.STABLE.TIME";		// Soft Pump 완료 후 Fast Pump 전 Delay Time을 준다.
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,100,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_COMPLETE_STABLE_TIME, str_name);

	str_name = "OTR.IN.CFG.aFAST.PUMP.PRESSURE.TORR";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",3,0,500,"");		// ...
	LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_PUMP_PRESSURE_TORR, str_name);

	str_name = "OTR.IN.CFG.aFAST.PUMP.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_PUMP_TIMEOUT, str_name);

	str_name = "OTR.IN.CFG.aVAC.PRESSURE.TORR";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",3,0,100,"");	
	LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_PRESSURE_TORR, str_name);

	//
	str_name = "OTR.IN.CFG.aSOFT.VENT.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_TIMEOUT, str_name);

	str_name = "OTR.IN.CFG.aFAST.VENT.PRESSURE.TORR";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",3,0,1000,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_VENT_PRESSURE_TORR, str_name);

	str_name = "CFG.aATM.PRESS.STS.TOLERANCE";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",0,-20,20,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_ATM_PRESS_STS_TOLERANCE, str_name);

	str_name = "OTR.IN.CFG.aFAST.VENT.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_FAST_VENT_TIMEOUT, str_name);

	str_name = "OTR.IN.CFG.aATM.PRESSURE.TORR";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"torr",3,0,1000,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_ATM_PRESSURE_TORR, str_name);

	str_name = "OTR.IN.CFG.aOVER.VENT.TIME";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",3,0,60,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_OVER_VENT_TIME, str_name);

	//
	str_name = "OTR.IN.CFG.aSOFT.PUMP.DELAY.TIME";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",3,3,60,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_PUMP_DELAY_TIME, str_name);

	str_name = "OTR.IN.CFG.aSOFT.VENT.DELAY.TIME";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",3,3,60,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_SOFT_VENT_DELAY_TIME, str_name);

	//
	str_name = "OTR.IN.CFG.aVALVE.CLOSE.DELAY.TIME";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",3,0.3,1.0,"");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_VALVE_CLOSE_DELAY_TIME, str_name);

	// 
	str_name = "OTR.OUT.MON.aPRESSURE.TORR";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"torr",3,0,1000,"");
	LINK__VAR_ANALOG_CTRL(aCH__PRESSURE_TORR, str_name);

	str_name = "OTR.OUT.MON.dPRESSURE.STATUS";
	STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__PRESS_STS,"");
	LINK__VAR_DIGITAL_CTRL(dCH__PRESSURE_STATUS, str_name);

	//
	str_name = "OTR.OUT.MON.dSLIT.VALVE.STATUS";
	STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__CLOSE_OPEN,"");
	LINK__VAR_DIGITAL_CTRL(dCH__SLIT_VALVE_STATUS, str_name);

	str_name = "SLIT_VALVE.LOCK_FLAG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__SLIT_VALVE_LOCK_FLAG, str_name);

	//
	str_name = "OTR.OUT.MON.dDOOR.VALVE.STATUS";
	STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__CLOSE_OPEN,"");
	LINK__VAR_DIGITAL_CTRL(dCH__DOOR_VALVE_STATUS, str_name);

	//.....
	CString dsc_item_list;
	p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsc_item_list);

	for(i=0;i<CFG_LBx__SLOT_SIZE;i++)
	{
		// Slot Status
		str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS",i+1);
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,dsc_item_list,"");
		LINK__VAR_DIGITAL_CTRL(dCH__SLOT_STATUS[i],str_name);

		// Slot Title
		str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE",i+1);
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__SLOT_TITLE[i],str_name);
	}

	//
	str_name = "aTIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__TIME_COUNT,str_name);

	str_name = "aPUMPING.ELAPSED.TIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__PUMPING_ELAPSED_TIME,str_name);

	str_name = "aVENTING.ELAPSED.TIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH__VENTING_ELAPSED_TIME,str_name);

	str_name = "SV.UP.aTIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH_SV_UP__TIME_COUNT,str_name);

	str_name = "SV.DOWN.aTIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH_SV_DOWN__TIME_COUNT,str_name);

	str_name = "SV.OPEN.aTIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH_SV_OPEN__TIME_COUNT,str_name);

	str_name = "SV.CLOSE.aTIME.COUNT";
	STD__ADD_ANALOG_WITH_COMMENT(str_name,"sec",0,0,9999,"");
	LINK__VAR_ANALOG_CTRL(aCH_SV_CLOSE__TIME_COUNT,str_name);

	str_name = "CFG.aCONVECT.ATM.HIGH.PRESS";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"mtorr",0,0,80000000,"");
	LINK__VAR_ANALOG_CTRL(aCFG_CH_CONVECT_ATM_HIGH_PRESS,str_name);

	// ...
	{
		str_name.Format("CFG.aMAX.SV.OPEN.DIFFERENTIAL.PRESS");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"mtorr",0,10,1000,"200mtorr");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_MAX_SV_OPEN_DIFF_PRESS,str_name);

		str_name.Format("CFG.dINIT.PUMP.DOWN");
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PUMP_DOWN_OPTION,str_name);
	}

	// ...
	{
		// AL1_Convectron1LowerTolerance
		str_name.Format("CFG.aVAC.LOWER.TOLERANCE");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 0, 0, 50, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_LOWER_TOLERANCE,str_name);

		// AL1_Convectron1UpperTolerance
		str_name.Format("CFG.aVAC.UPPER.TOLERANCE");
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "mtorr", 0, 0, 50, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAC_UPPER_TOLERANCE,str_name);
	}

	// ...
	{
		str_name = "CFG.HEATER.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_HEATER_USE, str_name);

		str_name = "CFG.HEATING.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 9999, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_HEATING_TIME, str_name);

		str_name = "APP.HEATING.TIMECOUNT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__APP_HEATING_TIMECOUNT, str_name);

		str_name = "CFG.HEATING.SOFT_VENT.APPLY";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_HEATER_SOFT_VENT_USE, str_name);
	}

	// TAS Channel ...
	{
		str_name = "TAS.RESET.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TAS_RESET_REQ, str_name);

		//
		for(i=0; i<CFG_ACT__SIZE; i++)
		{
			CString act_name;

				 if(i == _ACT_INDEX__PUMP)				act_name = "PUMP";
			else if(i == _ACT_INDEX__VENT)				act_name = "VENT";
			else if(i == _ACT_INDEX__DV_OPEN)			act_name = "DV.OPEN";
			else if(i == _ACT_INDEX__DV_CLOSE)			act_name = "DV.CLOSE";
			else if(i == _ACT_INDEX__SV_OPEN)			act_name = "SV.OPEN";
			else if(i == _ACT_INDEX__SV_CLOSE)			act_name = "SV.CLOSE";
			else if(i == _ACT_INDEX__LIFT_PIN_UP)		act_name = "LIFT_PIN.UP";
			else if(i == _ACT_INDEX__LIFT_PIN_DOWN)		act_name = "LIFT_PIN.DOWN";
			else										continue;

			// ...
			{
				str_name.Format("TAS.%s.TIME.NOW", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW[i], str_name);

				str_name.Format("TAS.%s.TIME.MIN", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN[i], str_name);

				str_name.Format("TAS.%s.TIME.MAX", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG[i], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F[i], str_name);

				str_name.Format("TAS.%s.TIME.CNT", act_name);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT[i], str_name);
			}
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__IO_MONITOR);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__INTERLOCK);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__PUMP_RUN_INTERLOCK);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__SV_DV_OP_CL_STATUS);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");

#define  ACT__CHECK								\
l_act.RemoveAll();								\
l_act.Add("CHECK");

#define  ALARM_ACT__ABORT						\
l_act.RemoveAll();								\
l_act.Add("ABORT");		


int CObj__LBx_CHM_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	//.....
	alarm_id = ALID__DOOR_VALVE_OPEN__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Door Valve Open TimeOut.";

	alarm_msg = "Please, Check I/O Object !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__DOOR_VALVE_CLOSE__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Door Valve Close TimeOut.";

	alarm_msg = "Please, Check I/O Object !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SLIT_VALVE_OPEN__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Slit Valve Open TimeOut.";

	alarm_msg = "Please, Check I/O Object !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SLIT_VALVE_CLOSE__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Slit Valve Close TimeOut.";

	alarm_msg = "Please, Check I/O Object !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SLIT_CANNOT_CLOSE_NOT_EXIST;

	alarm_title  = title;
	alarm_title += "Slit Valve Can't Close Because Of not exist.";

	alarm_msg = "Please, Check Config Value !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SLIT_CANNOT_OPEN_NOT_EXIST;

	alarm_title  = title;
	alarm_title += "Slit Valve Can't Open Because Of not exist.";

	alarm_msg = "Please, Check Config Value !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SV_OPEN__NOT_ATM_ERROR;

	alarm_title  = title;
	alarm_title += "Slit Valve can not open, because of not ATM Pressure !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SV_OPEN__NOT_VAC_ERROR;

	alarm_title  = title;
	alarm_title += "Slit Valve can not open, because of not VAC Pressure !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__DV_OPEN__NOT_ATM_ERROR;

	alarm_title  = title;
	alarm_title += "Door Valve can not open, because of not ATM Pressure !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SOFT_PUMPING__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Soft Pumping Timeout !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__FAST_PUMPING__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Fast Pumping Timeout !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SOFT_VENTING__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Soft Venting Timeout !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__FAST_VENTING__TIMEOUT;

	alarm_title  = title;
	alarm_title += "Fast Venting Timeout !";

	alarm_msg.Format("Please, check %s's pressure.\n", m_sLBx__MODULE_NAME);

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__VENT_VALVE__PUMP_INTERLOCK;

	alarm_title  = title;
	alarm_title += "Vent Valve Interlock With Pumping Valve Open !";

	alarm_msg  = "All vent valve must be closed !\n";

	ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__DOOR_VALVE__PUMP_INTERLOCK;

	alarm_title  = title;
	alarm_title += "Pump Valve Interlock With Door open !";

	alarm_msg  = "All pump valve must be closed !\n";

	ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__DOOR_VALVE__NOT_CLOSE;

	alarm_title  = title;
	alarm_title += "Door Valve is not close !";

	alarm_msg = "Please, check door valve !\n";

	l_act.RemoveAll();
	l_act.Add("RETRY");
	l_act.Add("ABORT");
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__SLIT_VALVE__NOT_CLOSE;

	alarm_title  = title;
	alarm_title += "Slit Valve is not close !";

	alarm_msg = "Please, check slit valve !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__PUMP_OFFLINE_OFF_INTERLOCK;

	alarm_title  = title;
	alarm_title += "Dry Pump is Offline or Not Run Status !";

	alarm_msg.Format("LoadLock : [%s], Slow/Fast Rough Valve will be closed.. !\n", sObject_Name);
	alarm_msg += "Please, check pump status !\n";

	ACT__CHECK;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__VAC_RB_NOT_RETRACTED;

	alarm_title  = title;
	alarm_title += "VAC Robot's Arm not retracted sts.";

	alarm_msg = "Please, Check VAC Robot's Arm Status !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__ATM_RB_NOT_RETRACTED;

	alarm_title  = title;
	alarm_title += "ATM Robot's Arm not retracted sts.";

	alarm_msg = "Please, Check ATM Robot's Arm Status !\n";

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__MAX_DIFFER_PRESS_ALARM;

	alarm_title  = title;
	alarm_title += "Can't SV Open, Max Difference Press Alarm Occur !";

	alarm_msg.Format("Please, check LL and TM Pressure Status.\n");

	ACT__RETRY_ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	//.....
	alarm_id = ALID__CONVECTRON_ATM_HIGH_PRESS_ALARM;

	alarm_title  = title;
	alarm_title += "After Venting Complete, Atm High Press Alarm !";

	alarm_msg.Format("Please, check LL Pressure or Gauge Status.\n");

	ALARM_ACT__ABORT;
	ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_CHM_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	xI_ASYNC_TIMER->REGISTER__COUNT_CHANNEL(sObject_Name,aCH__TIME_COUNT->Get__VARIABLE_NAME());

	// ...
	CString def_name;
	CString def_data;
	CString str_name;

	CString obj_name, var_name;

	// OBJ INFO -----
	{
		def_name = "LBx_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		m_sLBx__MODULE_NAME = def_data;
	}

	// DB OBJECT -----
	{
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		//.....
		str_name = "CFG.TRANSFER.MODE";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_TRANSFER_MODE, def_data,str_name);

		str_name = "CFG.REF.ATM.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_REF_ATM_PRESSURE, def_data,str_name);

		str_name = "CFG.REF.VAC.PRESSURE";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_REF_VAC_PRESSURE, def_data,str_name);

		//.....
		str_name = "CFG.SIM.SLOT.VLV.CLOSE.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_SLOT_VLV_CLOSE_TIME, def_data,str_name);

		str_name = "CFG.SIM.SLOT.VLV.OPEN.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_SLOT_VLV_OPEN_TIME, def_data,str_name);

		str_name = "CFG.SIM.DOOR.VLV.CLOSE.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_DOOR_VLV_CLOSE_TIME, def_data,str_name);

		str_name = "CFG.SIM.DOOR.VLV.OPEN.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_DOOR_VLV_OPEN_TIME, def_data,str_name);

		str_name = "CFG.SIM.LLx.SLOW.VENT.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_LLx_SLOW_VENT_TIME, def_data,str_name);

		str_name = "CFG.SIM.LLx.FAST.VENT.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_LLx_FAST_VENT_TIME, def_data,str_name);

		str_name = "CFG.SIM.LLx.SLOW.PUMP.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_LLx_SLOW_PUMP_TIME, def_data,str_name);

		str_name = "CFG.SIM.LLx.FAST.PUMP.TIME";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_SIM_LLx_FAST_PUMP_TIME, def_data,str_name);

		str_name = "CFG.LBA.SV.EXIST.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL1_SV_EXIST_FLAG, def_data,str_name);

		str_name = "CFG.LBB.SV.EXIST.FLAG";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LL2_SV_EXIST_FLAG, def_data,str_name);
	}

	// I/O OBJECT -----
	{
		// VENT VLV -----
		def_name = "VAR__IO_DO_SOFT_VENT_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__SOFT_VENT_VLV__SET, obj_name,var_name);

		def_name = "VAR__IO_DO_FAST_VENT_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__FAST_VENT_VLV__SET, obj_name,var_name);

		def_name = "VAR__IO_DO_EQUAL_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__ATM_EQUAL_VLV__SET, obj_name,var_name);

		// PUMP VLV -----
		def_name = "VAR__IO_DO_SOFT_PUMP_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__SOFT_PUMP_VLV__SET, obj_name,var_name);

		def_name = "VAR__IO_DO_FAST_PUMP_VLV";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__FAST_PUMP_VLV__SET, obj_name,var_name);

		// DV -----
		// do
		def_name = "VAR__IO_DO_DV_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LBx__DV_OPEN, obj_name,var_name);

		def_name = "VAR__IO_DO_DV_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LBx__DV_CLOSE, obj_name,var_name);

		// di
		def_name = "VAR__IO_DI_DV_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__LBx__DV_OPEN, obj_name,var_name);

		def_name = "VAR__IO_DI_DV_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__LBx__DV_CLOSE, obj_name,var_name);

		// SV OP/CL -----
		// do
		def_name = "VAR__IO_DO_SV_TM_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LBx__SV_TM_OPEN, obj_name,var_name);

		def_name = "VAR__IO_DO_SV_TM_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LBx__SV_TM_CLOSE, obj_name,var_name);

		// di
		def_name = "VAR__IO_DI_SV_TM_OPEN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__LBx__SV_TM_OPEN, obj_name,var_name);

		def_name = "VAR__IO_DI_SV_TM_CLOSE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__LBx__SV_TM_CLOSE, obj_name,var_name);

		// SV UP/DN -----
		// do
		def_name = "VAR__IO_DO_SV_UP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LBx__SV_UP, obj_name,var_name);

		def_name = "VAR__IO_DO_SV_DOWN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LBx__SV_DOWN, obj_name,var_name);

		// di
		def_name = "VAR__IO_DI_SV_UP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__LBx__SV_UP, obj_name,var_name);

		def_name = "VAR__IO_DI_SV_DOWN";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__LBx__SV_DOWN, obj_name,var_name);

		// VAC Robot Arm Sns
		def_name = "VAR__IO_DI_VAC_RB_RNE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__VAC_RB_RNE, obj_name,var_name);

		// ATM Robot Arm Sns
		def_name = "VAR__IO_DI_ATM_RB_RNE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(diEXT_CH__ATM_RB_RNE, obj_name,var_name);
	}

	// PUMP OBJECT -----
	{
		def_name = "OBJ__PUMP";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		pPUMP__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		//
		str_name = "MON.PUMP.COMM_STS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_PUMP_COMM_STS, def_data,str_name);

		str_name = "MON.PUMP.RUN_STS";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_PUMP_RUN_STS, def_data,str_name);
	}

	// GAUGE IO OBJECT -----
	{
		CString obj_name, var_name;
		//
		def_name = "VAR__PRESSURE_TORR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
		LINK__EXT_VAR_ANALOG_CTRL(aiEXT_CH__LBx__PRESSURE_TORR, obj_name,var_name);
	}

	// PHY_TM : TM의 Pressure Status (ATM, VAC, BTW)
	str_name.Format("VAR__PHY_TM_PRESS_STS");
	p_ext_obj_create->Get__DEF_CONST_DATA(str_name,def_data);
	p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
	LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PHY_TM__PRESS_STS, obj_name,var_name);

	// PHY_TM : TM의 Pressure Torr
	str_name.Format("VAR__PHY_TM_PRESS_TORR");
	p_ext_obj_create->Get__DEF_CONST_DATA(str_name,def_data);
	p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name, var_name);
	LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PHY_TM__PRESS_TORR, obj_name,var_name);

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		if(x_seq_info->Is__SIMULATION_MODE() > 0)
		{
			iSim_Flag =  1;
		}
		else
		{
			iSim_Flag = -1;
		}
	}

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xLOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xLOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);

		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__LBx_CHM_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	// ...
	{
		CString log_msg;

		xLOG_CTRL->WRITE__LOG("------------------------------>");

		log_msg.Format("Start  [%s] ... Called By %s", 
						mode,
						p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		xLOG_CTRL->WRITE__LOG(log_msg);

		Fnc__MSG(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__ALL_GAS_VLV_CLOSE)
		{
			flag = Call__ALL_GAS_VLV_CLOSE(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__CL_PUMP_VLV)
		{
			flag = Call__CL_PUMP_VLV(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__OP_PUMP_VLV)
		{
			flag = Call__OP_PUMP_VLV(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PUMP)
		{
			sCH__PRESSURE_CTRL_FLAG->Set__DATA("PUMP");

			flag = Call__PUMP(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__VENT)
		{
			sCH__PRESSURE_CTRL_FLAG->Set__DATA("VENT");

			flag = Call__VENT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE1_MODE2(sMODE__DV_CLOSE, sMODE__DV_TRANSFER_CLOSE)
		{
			flag = Call__DV_CLOSE(p_variable,p_alarm);

			Update__DV_STS(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE1_MODE2(sMODE__DV_OPEN, sMODE__DV_TRANSFER_OPEN)
		{
			flag = Call__DV_OPEN(p_variable,p_alarm);

			Update__DV_STS(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE1_MODE2(sMODE__SV_CLOSE, sMODE__SV_TRANSFER_CLOSE)
		{
			sCH__SLIT_VALVE_LOCK_FLAG->Set__DATA(STR__YES);

			flag = Call__SV_CLOSE(p_variable,p_alarm);

			Update__SV_STS(p_variable,p_alarm);

			sCH__SLIT_VALVE_LOCK_FLAG->Set__DATA("");
		}
		ELSE_IF__CTRL_MODE1_MODE2(sMODE__SV_OPEN, sMODE__SV_TRANSFER_OPEN)
		{
			sCH__SLIT_VALVE_LOCK_FLAG->Set__DATA(STR__YES);

			flag = Call__SV_OPEN(p_variable,p_alarm);

			Update__SV_STS(p_variable,p_alarm);

			sCH__SLIT_VALVE_LOCK_FLAG->Set__DATA("");
		}
		ELSE_IF__CTRL_MODE(sMODE__PREPMATER)
		{
			flag = Call__PREPMATER(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__COMPMATER)
		{
			flag = Call__COMPMATER(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__IN_PROC)
		{
			flag = Call__IN_PROC(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__OUT_PROC)
		{
			flag = Call__OUT_PROC(p_variable,p_alarm);
		}

		// Remote Control -----
		ELSE_IF__CTRL_MODE(sMODE__AUTO_PUMP_VLV_CLOSE)
		{
			flag = Call__AUTO_PUMP_VLV_CLOSE(p_variable,p_alarm);
		}
	}

	xI_ASYNC_TIMER->STOP();

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]",mode);
		Fnc__MSG(log_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		Fnc__MSG(log_msg);

		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	xLOG_CTRL->WRITE__LOG("<------------------------------\n");
	return flag;
}

int CObj__LBx_CHM_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;

		case MON_ID__INTERLOCK:
			Mon__INTERLOCK(p_variable,p_alarm);
			break;

		case MON_ID__PUMP_RUN_INTERLOCK:
			Mon__PUMP_INTERLOCK(p_variable,p_alarm);
			break;

		case MON_ID__SV_DV_OP_CL_STATUS:
			Mon__SV_DV_OP_CL_STS(p_variable,p_alarm);
			break;
	}

	return 1;
}
