#include "StdAfx.h"
#include "CObj__PSK.h"
#include "CObj__PSK__DEF.h"
#include "CObj__PSK__ALID.h"

#include "CCommon_DEF.h"


//--------------------------------------------------------------------------------
CObj__PSK::CObj__PSK()
{
	m_nCommState = ONLINE;
}
CObj__PSK::~CObj__PSK()
{

}

//--------------------------------------------------------------------------------
int CObj__PSK::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");		
		ADD__CTRL_VAR(sMODE__HOME, "HOME");

		ADD__CTRL_VAR(sMODE__PICK, "PICK");	
		ADD__CTRL_VAR(sMODE__ALIGN_PICK, "ALIGN_PICK");

		ADD__CTRL_VAR(sMODE__PLACE,	 "PLACE");	
		ADD__CTRL_VAR(sMODE__ROTATE, "ROTATE");	

		ADD__CTRL_VAR(sMODE__MAP, "MAP");

		ADD__CTRL_VAR(sMODE__VAC_ON,           "VAC_ON");	
		ADD__CTRL_VAR(sMODE__VAC_ON_OF_A_ARM,  "VAC_ON_OF_A_ARM");	
		ADD__CTRL_VAR(sMODE__VAC_ON_OF_B_ARM,  "VAC_ON_OF_B_ARM");	

		ADD__CTRL_VAR(sMODE__VAC_OFF,          "VAC_OFF");	
		ADD__CTRL_VAR(sMODE__VAC_OFF_OF_A_ARM, "VAC_OFF_OF_A_ARM");
		ADD__CTRL_VAR(sMODE__VAC_OFF_OF_B_ARM, "VAC_OFF_OF_B_ARM");

		ADD__CTRL_VAR(sMODE__AL_INIT, "AL.INIT");
		ADD__CTRL_VAR(sMODE__ALIGN,   "ALIGN");
	}

	return 1;
}
int CObj__PSK::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR									1
#define  MON_ID__HYPER_TERMINAL								2


// ...
#define APP_DSP__RB_TARGET_MOVE								\
"UNKNOWN HOME READY											\
PM1 PM2 PM3 PM4 PM5 PM6										\
LBA LBB														\
AL1 AL2														\
VIS1 VIS2													\
LP1 LP2 LP3 LP4 LP5											\
BUFF1 BUFF2"

#define APP_DSP__STN_NAME									\
"LP1 LP2 LP3 LP4 LP5										\
VIS1														\
LBA LBB														\
AL1 AL2														\
BUFF1 BUFF2 FULL_BUFF"

#define APP_DSP__ARM_TYPE									\
"A B"

#define APP_DSP__RET_EXT									\
"Retract Extend"

#define APP_DSP__DOWN_UP									\
"Down Up"

#define APP_DSP__ARM_STS_ANI								\
"UNKNOWN RETRACT EXTEND"

#define APP_DSP__LP_WFR_SLOT_STS							\
"UNKNOWN INVALID ABSENT PRESENT DOUBLE CROSSED"

#define APP_DSP__DSlot										\
"1  2  3  4  5  6  7  8  9  10								\
11 12 13 14 15 16 17 18 19 20								\
21 22 23 24 25 26 27 28 29 30"


int CObj__PSK::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// ...
	{
		str_name = "INR.RB1.ACT.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACT_MSG, str_name);
	}

	// PARA CHANNEL ...
	{
		str_name = "PARA.dSTN.NAME";
		STD__ADD_DIGITAL(str_name, APP_DSP__STN_NAME);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_NAME,str_name);

		str_name = "PARA.dSTN.SLOT";
		STD__ADD_DIGITAL(str_name, APP_DSP__DSlot);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_SLOT,str_name);

		str_name = "PARA.dARM.TYPE";
		STD__ADD_DIGITAL(str_name, APP_DSP__ARM_TYPE);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__ARM_TYPE,str_name);

		//
		str_name = "PARA.AL1.SLOT.ID";
		STD__ADD_DIGITAL(str_name, APP_DSP__DSlot);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__AL1_SLOT_ID, str_name);

		str_name = "PARA.AL1.CCD.POS";
		STD__ADD_ANALOG(str_name,"deg",1,0.0,360.0);
		LINK__VAR_ANALOG_CTRL(aCH__OTR_IN_PARA__AL1_CCD_POS,str_name);
	}

	// PARA : RB ...
	{
		str_name = "PARA.RB.ARM_TYPE";
		STD__ADD_DIGITAL(str_name, "A  B  AB");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_RB_ARM_TYPE, str_name);

		str_name = "PARA.RB.POS_CODE";
		STD__ADD_ANALOG(str_name, "pos", 0, 1, 16);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RB_POS_CODE, str_name);

		str_name = "PARA.RB.SLOT_CODE";
		STD__ADD_ANALOG(str_name, "pos", 0, 1, 99);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_RB_SLOT_CODE, str_name);
	}

	// PARA : AL ...
	{
		str_name = "PARA.AL.NOTCH_ANGLE";
		STD__ADD_ANALOG(str_name, "deg", 2, 0, 360);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_AL_NOTCH_ANGLE, str_name);

		str_name = "PARA.AL.RELATIVE_ANGLE";
		STD__ADD_ANALOG(str_name, "deg", 2, 0, 360);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_AL_RELATIVE_ANGLE, str_name);

		str_name = "PARA.AL.ABSOLUTE_ANGLE";
		STD__ADD_ANALOG(str_name, "deg", 2, 0, 360);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_AL_ABSOLUTE_ANGLE, str_name);
	}

	// MON ...
	{
		str_name = "MON.ERROR.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERROR_STATE, str_name);

		str_name = "MON.ERROR.CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERROR_CODE, str_name);

		//
		str_name = "MON.SERVO.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SERVO_STATE, str_name);

		str_name = "MON.ORIGIN.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ORIGIN_REQ, str_name);

		str_name = "MON.COMMAND.RUN";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMAND_RUN, str_name);

		//
		str_name = "MON.A_ARM.GRIPPER.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_A_ARM_GRIPPER_STATE, str_name);

		str_name = "MON.B_ARM.GRIPPER.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_B_ARM_GRIPPER_STATE, str_name);

		//
		str_name = "MON.RB.FAN.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_RB_FAN_STATE, str_name);

		//
		str_name = "MON.RB.TASK.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_RB_TASK_STATE, str_name);

		str_name = "MON.AL.TASK.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_AL_TASK_STATE, str_name);

		//
		str_name = "MON.APP_VERSION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_APP_VERSION, str_name);

		str_name = "MON.REVISION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_REVISION, str_name);

		//
		str_name = "MON.AL.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_AL_STATE, str_name);

		str_name = "MON.AL.X.ERROR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_AL_X_ERROR, str_name);

		str_name = "MON.AL.Y.ERROR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_AL_Y_ERROR, str_name);

		str_name = "MON.AL.NOTCH.ANGLE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_AL_NOTCH_ANGLE, str_name);
	}
	
	// CONFIG CHANNEL ...
	{
		str_name = "CFG.ACTION.CONFIRM.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ACTION_CONFIRM_FLAG,str_name);

		// AL1
		str_name = "CFG.AL1.STN.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG__AL1_STN_NUM, str_name);

		// LL1 : 1 & 2 
		str_name = "CFG.LL1.1.STN.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG__LL1_1_STN_NUM, str_name);

		str_name = "CFG.LL1.2.STN.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG__LL1_2_STN_NUM, str_name);

		// LL2 : 1 & 2
		str_name = "CFG.LL2.1.STN.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG__LL2_1_STN_NUM, str_name);

		str_name = "CFG.LL2.2.STN.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG__LL2_2_STN_NUM, str_name);

		// ST1 
		str_name = "CFG.ST1.STN.NUM";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG__ST1_STN_NUM,str_name);

		// LPx
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
			str_name.Format("CFG.LP%1d.STN.NUM", i+1);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG__LPx_STN_NUM[i], str_name);
		}
	}

	// HYPER TERMINAL ...
	{
		str_name = "sHYPER.TERMINAL.UPDATE.FLAG";
		STD__ADD_STRING_WITH_COMMENT(str_name, "");
		LINK__VAR_STRING_CTRL(xCH__UPDATE_FLAG, str_name);

		str_name = "dHYPER.TERMINAL.LOCK.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(xCH__LOCK_FLAG, str_name);

		str_name = "dHYPER.TERMINAL.SEND.REQ";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__HYPER_TERMINAL_SEND_REQ,str_name);

		str_name = "sHYPER.TERMINAL.SEND.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__HYPER_TERMINAL_SEND_MSG,str_name);

		str_name = "sHYPER.TERMINAL.RECV.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__HYPER_TERMINAL_RECV_MSG,str_name);

		str_name = "aHYPER.TERMINAL.CMD.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 60, "");
		LINK__VAR_ANALOG_CTRL(aCH__HYPER_TERMINAL_CMD_TIMEOUT,str_name);
	}

	// SIMULATION CHANNEL ...
	{
		str_name = "SIM.CFG.aROTATE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ROTATE_TIME, str_name);

		// LPx ...
		str_name = "SIM.CFG.aLPx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LPx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aLPx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LPx_PLACE_TIME, str_name);

		// ALx
		str_name = "SIM.CFG.aALx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ALx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aALx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ALx_PLACE_TIME, str_name);

		// LBx
		str_name = "SIM.CFG.aLBx.PICK.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LBx_PICK_TIME, str_name);

		str_name = "SIM.CFG.aLBx.PLACE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LBx_PLACE_TIME, str_name);
	}

	// MATERIAL CHANNEL ...
	{
		CString dsp_slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsp_slot_sts);

		//
		str_name = "MON.ARM_A.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS,str_name);

		str_name = "MON.ARM_B.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS,str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(5.0, MON_ID__IO_MONITOR);
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__HYPER_TERMINAL);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");

#define  ACT__ABORT_ALARM						\
l_act.RemoveAll();								\
l_act.Add("ABORT");

#define  ACT__NO_YES_ALARM						\
l_act.RemoveAll();								\
l_act.Add("NO");								\
l_act.Add("YES");

#define  ACT__CHECK_ALARM						\
l_act.RemoveAll();								\
l_act.Add("CHECK");


int CObj__PSK::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CString alarm_bff;
	CStringArray l_act;
	int alarm_id;
	int i;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Offline.";

		alarm_msg  = "Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ALGN_AND_PICK_TIMEOUT_ALARM;

		alarm_title  = title;
		alarm_title += "Align and Pick Action Timeout Occur.";

		alarm_msg  = "Align and Pick Action Timeout Occur.\n";
		alarm_msg += "Please, Check ATM Robot Status !\n";

		ACT__ABORT_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__MAPPING_DISABLE_CONFIG_ALARM;

		alarm_title  = title;
		alarm_title += "Config Option, Mapping Disable Alarm.";

		alarm_msg  = "Now, Mapping Disable Config Option Selected.\n";
		alarm_msg += "Would you like to continue ??\n";

		ACT__NO_YES_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ERROR_STATE;

		alarm_title  = title;
		alarm_title += "Error State";

		alarm_msg = "Error state must be \"OFF\". \n";

		ACT__CHECK_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__SERVO_STATE;

		alarm_title  = title;
		alarm_title += "Servo State";

		alarm_msg = "Servo state must be \"ON\". \n";

		ACT__CHECK_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RB_FAN_STATE;

		alarm_title  = title;
		alarm_title += "Robot's FAN State";

		alarm_msg = "Robot's FAN state must be \"ON\". \n";

		ACT__CHECK_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	Register__ALARM_INF(p_alarm);
	return 1;
}


// ...
#define APP_DSP__Cmd_Set								\
"Goto Pick ALPick AlgnPick Place PlaceAlgn				\
CheckLoad SetVac Home Reset MapStn GetMap				\
SetALStn StoALStn										\
InitAlgn ALSetComm ALStoComm ALAlign ALScan				\
ALHome ALReset ALResult ALLoadPP ALSetPP ALSetWfr		\
Reinit MapClear"

#define APP_DSP__Arm_ID				"A  B"
#define APP_DSP__Wfr    			"Unknown  Absent  Present"
#define APP_DSP__StrLoc 			"Normal  Retract2  NoRetract"
#define APP_DSP__Axises				"ALL  R  T  Z  W  S"

#define APP_DSP__Stn									\
"1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__CurStn									\
"0														\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__DDnUp				"DN  UP"
#define APP_DSP__OffOn              "OFF ON"
#define APP_DSP__RetExt             "RE  EX"
#define APP_DSP__ComSts             "Offline Online"
#define APP_DSP__YesNo              "Y   N"
#define APP_DSP__PrsAbs				"ON  OFF"
#define APP_DSP__ALWfr				"?  NO  YES"

#define APP_DSP__Material								\
"? 0 1 2 3 4 5 6 7 20 21 22 23 FP"

#define APP_DSP__Substrates								\
"1 2 3 4 5 6 7 20 21 22 23"

#define APP_DSP__FDCLs				"None  Flat  Ntch"
#define APP_DSP__WfrShapes			"Round  Square"
#define APP_DSP__CCDPos				"1  2  3"
#define APP_DSP__DOffOn				"Off  On"
#define APP_DSP__DZPos				"Unknown  Up  Down"
#define APP_DSP__DRPos				"Unknown  Retract  Extend"

#define APP_DSP__DTPos									\
"Unknown												\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__DSPos									\
"Unknown												\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"


int CObj__PSK::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;

	// DO ...
	{
		str_name = "do.RB.COMMAND";
		IO__ADD_DIGITAL_WRITE(str_name, "INIT  PICK  PLACE  CHUCK.ON  CHUCK.OFF  GOTO.GET  GOTO.PUT  ERROR.RESET");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__RB_COMMAND, str_name);

		str_name = "do.AL.COMMAND";
		IO__ADD_DIGITAL_WRITE(str_name, "INIT  MEASURE.START  CHUCK.ON  CHUCK.OFF  ROT.RELATIVE  ROT.ABSOLUTE  CAL");
		LINK__IO_VAR_DIGITAL_CTRL(doCH__AL_COMMAND, str_name);
	}

	// DI ...
	{
		str_name = "di.ComSts";
		IO__ADD_DIGITAL_READ(str_name, APP_DSP__ComSts);
		LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);
	}

	// SI ...
	{
		str_name = "si.RB.STATE.AUTO";
		IO__ADD_STRING_READ_WITH_OPTION(str_name, "","","", 0.1, "");
		LINK__IO_VAR_STRING_CTRL(siCH__RB_STATE_AUTO, str_name);

		str_name = "si.RB.STATE.MANUAL";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__RB_STATE_MANUAL, str_name);

		//
		str_name = "si.VERSION";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__VERSION, str_name);

		str_name = "si.AL.MEASUREMENT";
		IO__ADD_STRING_READ__MANUAL(str_name);
		LINK__IO_VAR_STRING_CTRL(siCH__AL_MEASUREMENT, str_name);
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__PSK::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;
	int i;
	int j;

	CString obj_name, var_name;

	// OBJ : DB_CFG ...
	{
		def_name = "OBJ__DB";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		// AL1 ...
		{
			str_name = "CFG.AL1.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_AL1_EXIST_FLAG, def_data,str_name);

			str_name = "CFG.dALIGN.DEVICE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_ALIGN_DEVICE, def_data,str_name);
		}
	}

	iFlag__APP_LOG = 1;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xAPP_LOG_CTRL->DISABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);

		xAPP_LOG_CTRL->ENABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	iFlag__DRV_LOG = 1;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_Drv.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xDRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xDRV_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xDRV_LOG_CTRL->DISABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);

		xDRV_LOG_CTRL->ENABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}
int CObj__PSK::__INITIALIZE__IO(p_io_para)
{
	memset(m_Term_Str, 0, sizeof(m_Term_Str));		

	//-------------------------------------------------------
	// Set Driver Parameter
	//------------------------------------------------------
	int com_port = -1;
	
	int nBaudRate = 115200;
	int nDataBit  = 8;
	int nParity   = 0;			// None
	int nStopBit  = 1;			// 0, 1, 2, 3, 4  // 0 ~ 4 : No, Odd, Even, Mark, Space

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
		m_Term_Str[0] = CR;
		m_Term_Str[1] = LF;  
		m_Term_Str[2] = 0;
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

		log_bff.Format(" * Baud Rate: %1d \n", nBaudRate);
		log_msg += log_bff;

		log_bff.Format(" * Data Bit: %1d \n", nDataBit);
		log_msg += log_bff;

		// ...
		{
			switch(nParity)
			{
				case 0:		str_data = "None";		break;;
				case 1:		str_data = "Odd";		break;;
				case 2:		str_data = "Even";		break;;
				case 3:		str_data = "Mark";		break;;
				case 4:		str_data = "Space";		break;;

				default:	str_data = "???";		break;;
			}

			log_bff.Format(" * Parity Bit: %s (%1d) \n", str_data,nParity);
			log_msg += log_bff;
		}

		log_bff.Format(" * Stop Bit: %1d \n", nStopBit);
		log_msg += log_bff;

		Fnc__DRV_LOG_FORMAT(log_msg);
	}

	if(iActive__SIM_MODE > 0)
	{

	}
	else
	{
		if(mX_Serial->INIT__COMPORT(com_port, nBaudRate, nDataBit, nStopBit, nParity) < 0)
		{
			log_msg.Format("Fail to do INIT__COMPORT: %d", com_port);
			Fnc__DRV_LOG_FORMAT(log_msg);
			return -1;
		}
		else
		{
			log_msg.Format("Initialize RS-232 Complete");
			Fnc__DRV_LOG_FORMAT(log_msg);
		}
	}

	// ...
	{
		m_nRetryCount = 2;

		log_msg = "\n";
		log_bff.Format(" * Retry Count: %1d \n", m_nRetryCount);
		log_msg += log_bff;
	
		//
		m_nTimeout = 2*1000;
		m_Rcv_Time = m_nTimeout;

		log_bff.Format(" * Recv_Timeout: %1d sec \n", m_nTimeout);
		log_msg += log_bff;

		//
		m_Out_Time = 10000;		// 10 sec
		
		log_bff.Format("Action_Timeout: %1d sec \n", m_Out_Time);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__PSK::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	CString para__arm_type;
	CString para__stn_name;
	CString para__stn_slot;

	CString szUpperObj;

	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		CString para_data;
		int limit = l_para.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			para_data = l_para[i];

			switch(i)
			{
				case 0:		
					dCH__OTR_IN_PARA__ARM_TYPE->Set__DATA(para_data);
					break;

				case 1:
					dCH__OTR_IN_PARA__STN_NAME->Set__DATA(para_data);
					break;

				case 2:
					dCH__OTR_IN_PARA__STN_SLOT->Set__DATA(para_data);
					break;
			}	
		}
	} 

	dCH__OTR_IN_PARA__ARM_TYPE->Get__DATA(para__arm_type);
	dCH__OTR_IN_PARA__STN_NAME->Get__DATA(para__stn_name);
	dCH__OTR_IN_PARA__STN_SLOT->Get__DATA(para__stn_slot);

	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s] (%s,%s,%s)",
						mode,
						para__arm_type,
						para__stn_name,
						para__stn_slot);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}

	// ...
	int seq_flag = 1;

	if(dCH__CFG_ACTION_CONFIRM_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		CString stn_id = "Error !";

		Get__CFG_STN_NUM(para__stn_name,para__stn_slot, stn_id);

		// ...
		CString log_msg;

		CString str_title;
		CString str_msg;
		CString str_bff;
		CStringArray l_act;
		CString r_act;

		str_title.Format("%s - Action Confirm Flag", sObject_Name);

		str_bff.Format("Object Mode : [%s] \n", mode);
		str_msg += str_bff;
		str_bff.Format("Arm Type : [%s] \n", para__arm_type);
		str_msg += str_bff;
		str_bff.Format("Station Name : [%s] \n", para__stn_name);
		str_msg += str_bff;
		str_bff.Format("Station Slot : [%s] \n", para__stn_slot);
		str_msg += str_bff;
		str_bff.Format("Station ID : [%s] \n", stn_id);
		str_msg += str_bff;

		l_act.RemoveAll();
		l_act.Add(STR__YES);
		l_act.Add(STR__NO);

		p_alarm->Popup__MESSAGE_BOX(str_title,str_msg,l_act,r_act);

		if(r_act.CompareNoCase(STR__NO) == 0)
		{
			seq_flag = -1;

			CString log_msg = "Confirm : Action No Clicked !";

			Fnc__APP_LOG(log_msg);
			Fnc__ACT_MSG(log_msg);
		}
	}

	if(seq_flag > 0)
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
	    ELSE_IF__CTRL_MODE(sMODE__HOME)					flag = Call__HOME(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__PICK)					flag = Call__PICK(p_variable,p_alarm,   para__arm_type,para__stn_name,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN_PICK)			flag = Call__ALIGN_PICK(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__PLACE)				flag = Call__PLACE(p_variable,p_alarm,  para__arm_type,para__stn_name,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__ROTATE)				flag = Call__ROTATE(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);

		ELSE_IF__CTRL_MODE(sMODE__MAP)					flag = Call__MAP(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__VAC_ON)	            flag = Call__VAC_ON(p_variable,p_alarm, ARM_AB);
		ELSE_IF__CTRL_MODE(sMODE__VAC_ON_OF_A_ARM)		flag = Call__VAC_ON(p_variable,p_alarm, ARM_A);
		ELSE_IF__CTRL_MODE(sMODE__VAC_ON_OF_B_ARM)		flag = Call__VAC_ON(p_variable,p_alarm, ARM_B);

		ELSE_IF__CTRL_MODE(sMODE__VAC_OFF)		        flag = Call__VAC_OFF(p_variable,p_alarm, ARM_AB);
		ELSE_IF__CTRL_MODE(sMODE__VAC_OFF_OF_A_ARM)		flag = Call__VAC_OFF(p_variable,p_alarm, ARM_A);
		ELSE_IF__CTRL_MODE(sMODE__VAC_OFF_OF_B_ARM)		flag = Call__VAC_OFF(p_variable,p_alarm, ARM_B);

		ELSE_IF__CTRL_MODE(sMODE__AL_INIT)				flag = Call__AL_INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN)				flag = Call__ALIGN(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;	
		log_msg.Format("Aborted ... :  [%s]\n", mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]\n", mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}

	return flag;
}

int CObj__PSK::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable, p_alarm);
			break;

		case MON_ID__HYPER_TERMINAL:
			Mon__HYPER_TERMINAL_SEND(p_variable,p_alarm);
			break;
	}

	return 1;
}
