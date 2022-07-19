#include "StdAfx.h"
#include "CObj_NET__VAC_PERSIMMON.h"
#include "CObj_NET__VAC_PERSIMMON__DEF.h"
#include "CObj_NET__VAC_PERSIMMON__ALID.h"

#include "CCommon_DEF.h"
#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj_NET__VAC_PERSIMMON::CObj_NET__VAC_PERSIMMON()
{
	m_sStationA =	"1";
	m_sStationB =	"1";
	m_sCptr_StationA = "1";
	m_sCptr_StationB = "1";
	m_sRPos     =	"RE"; 
	m_sZPos		=	"DN"; 
	m_sSlot		=	"1";

	m_sBefore_Stn_Retract_ArmA = "UNKNOWN";
	m_sBefore_Stn_Retract_ArmB = "UNKNOWN";
}
CObj_NET__VAC_PERSIMMON::~CObj_NET__VAC_PERSIMMON()
{
	
}

//--------------------------------------------------------------------------------
int CObj_NET__VAC_PERSIMMON::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,		"INIT");
	
		ADD__CTRL_VAR(sMODE__PICK,		"PICK");
		ADD__CTRL_VAR(sMODE__PLACE,		"PLACE");
		ADD__CTRL_VAR(sMODE__ROTATE,	"ROTATE");
		ADD__CTRL_VAR(sMODE__HOME,		"HOME");
		
		ADD__CTRL_VAR(sMODE__EXTEND,	"EXTEND");
		ADD__CTRL_VAR(sMODE__RETRACT,	"RETRACT");

		ADD__CTRL_VAR(sMODE__GOUP,		"GOUP");
		ADD__CTRL_VAR(sMODE__GODOWN,	"GODOWN");
		ADD__CTRL_VAR(sMODE__RQ_STN,	"RQ_STN");

		ADD__CTRL_VAR(sMODE__TEACHED_CPTR_SAVE, "TEACHED_CPTR_SAVE");

		ADD__CTRL_VAR(sMODE__RQ_WFR_CEN_DATA, "RQ.WFR_CEN_DATA");

		ADD__CTRL_VAR(sMODE__CHECK_ERROR_CODE, "CHECK.ERROR_CODE");
	}
	return 1;
}
int CObj_NET__VAC_PERSIMMON::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR				1

// ...
#define  APP_DSP__RB_TARGET_MOVE		\
"UNKNOWN HOME READY						\
 PM1 PM2 PM3 PM4 PM5 PM6				\
 LBA LBB LBC LBD"

#define  APP_DSP__STN_NAME				\
"PM1 PM2 PM3 PM4 PM5 PM6				\
 LBA LBB LBC LBD"

#define  APP_DSP__SLOT_NUM				"1 2 3 4"
#define  APP_DSP__RB_ARM				"A B"

#define  APP_DSP__RET_EXT				"Retract Extend"
#define  APP_DSP__DOWN_UP				"Down Up"
#define  APP_DSP__ARM_STS_ANI			"UNKNOWN RETRACT EXTEND"


int CObj_NET__VAC_PERSIMMON::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString str_comment;
	CString def_name;
	CString def_data;
	int i;

	// ...
	{
		str_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, str_name);

		str_name = "MON.COMMUNICATION.INFO";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_INFO, str_name);

		str_name = "OTR.OUT.MON.sCOMM.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__COMM_STS,str_name);
	}

	// ...
	{
		str_name = "dHYPER.TERMINAL.LOCK.FLAG";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, "YES NO","");
		LINK__VAR_DIGITAL_CTRL(xCH__LOCK_FLAG, str_name);
	}

	// ...
	{
		str_name = "INR.RB1.ACT.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACT_MSG, str_name);

		str_name = "INR.RB1.ERRID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERRID, str_name);

		str_name = "INR.RB1.VERSION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__VERSION, str_name);
	}

	// DRV_INFO ...
	{
		str_name = "DRV.INFO.ROBOT.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_INFO_ROBOT_STS, str_name);

		str_name = "DRV.INFO.ERROR.CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_INFO_ERROR_CODE, str_name);

		str_name = "DRV.INFO.SERVO.STS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_INFO_SERVO_STS, str_name);

		str_name = "DRV.INFO.ROT.POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_INFO_ROT_POS, str_name);

		str_name = "DRV.INFO.ARM_A.LOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_INFO_ARM_A_LOAD, str_name);

		str_name = "DRV.INFO.ARM_B.LOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_INFO_ARM_B_LOAD, str_name);
	}

	// PARA CHANNEL ...
	{
		str_name = "OTR.IN.PARA.dSTN.NAME";
		STD__ADD_DIGITAL(str_name, APP_DSP__STN_NAME);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_NAME,str_name);

		str_name = "OTR.IN.PARA.dSTN.SLOT";
		STD__ADD_DIGITAL(str_name, APP_DSP__SLOT_NUM);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_SLOT,str_name);

		str_name = "OTR.IN.PARA.dARM.TYPE";
		STD__ADD_DIGITAL(str_name, APP_DSP__RB_ARM);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__ARM_TYPE,str_name);

		str_name = "dACTION.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACTION_STS, str_name);

		str_name.Format("OTR.IN.sARM_A.BEFORE.MODE.STS");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ARM_A_BEFORE_MODE_STS,str_name);

		str_name.Format("OTR.IN.sARM_B.BEFORE.MODE.STS");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ARM_B_BEFORE_MODE_STS,str_name);

		str_name.Format("OTR.IN.aSET.STN.R.VALUE");
		STD__ADD_ANALOG(str_name, "microns", 0, -9999999, 9999999);
		LINK__VAR_ANALOG_CTRL(aCH__SET_STN_R_VALUE,str_name);

		str_name.Format("OTR.IN.aSET.STN.T.VALUE");
		STD__ADD_ANALOG(str_name, "microns", 0, -9999999, 9999999);
		LINK__VAR_ANALOG_CTRL(aCH__SET_STN_T_VALUE,str_name);

		str_name.Format("OTR.IN.sGUI.DISPLAY.R.OFFSET");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__Estimated_R_OFFSET,str_name);

		str_name.Format("OTR.IN.sGUI.DISPLAY.T.OFFSET");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__Estimated_T_OFFSET,str_name);
	}

	// LLx .. 
	{
		for(i=0; i<CFG_LLx__SIZE; i++)
		{
			CString ll_name = Macro__Get_LLx_NAME(i);
			int ll_id = i + 1;

			// STN NUM ...
			{
				str_name.Format("OTR.IN.CFG.a%s.STN.NUM", ll_name);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
				LINK__VAR_ANALOG_CTRL(aCH__OTR_IN_CFG__LLx_STN_NUM[i], str_name);			
			}

			// Sensor Number ...
			{	
				str_name.Format("OTR.IN.CFG.aCPTR.SNS.LL%1d.NUM", ll_id);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 10, "");
				LINK__VAR_ANALOG_CTRL(aCH__OTR_IN_CFG_LLx_CPTR_SNS_NUM[i], str_name);
			}
		}
	}
	// PMx ...
	{
		m_nPM_LIMIT = CFG_PMx__SIZE;

		for(i=0; i<CFG_PMx__SIZE; i++)
		{
			int pm_id = i + 1;

			// PMx ...
			{
				str_name.Format("OTR.IN.CFG.aPM%1d.STN.NUM", pm_id);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
				LINK__VAR_ANALOG_CTRL(aCH__OTR_IN_CFG__PMx_STN_NUM[i], str_name);

				str_name.Format("OTR.IN.CFG.VACRB.CPTR.SNS.PM%1d.NUM", pm_id);
				STD__ADD_ANALOG_WITH_X_OPTION(str_name, "num", 0, 1, 16, "");
				LINK__VAR_ANALOG_CTRL(aCH__OTR_IN_CFG_PMx_CPTR_SNS_NUM[i], str_name);
			}
		}
	}

	// MON ...
	{
		str_name = "MON.ROBOT.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ROBOT_STATE, str_name);

		//
		str_name = "MON.SERVO.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_SERVO_STATE, str_name);

		str_name = "MON.ROBOT.ROT.POS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ROBOT_ROT_POS, str_name);

		str_name = "MON.ROBOT.ARM_A.LOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ROBOT_ARM_A_LOAD, str_name);

		str_name = "MON.ROBOT.ARM_B.LOAD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ROBOT_ARM_B_LOAD, str_name);
	}

	// MATERIAL CHANNEL ...
	{
		CString dsp_slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsp_slot_sts);

		// Material Status
		{
			str_name = "OTR.OUT.MON.dARM_A.MATERIAL.STATUS";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS,str_name);
	
			str_name = "OTR.OUT.MON.dARM_B.MATERIAL.STATUS";
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts,"");
			LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS,str_name);
		}
		// Material Title
		{
			str_name = "OTR.OUT.MON.sARM_A.MATERIAL.TITLE";
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE,str_name);

			str_name = "OTR.OUT.MON.sARM_B.MATERIAL.TITLE";
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE,str_name);
		}
	}

	// DA Offset ...
	{
		str_name = "DA.RESULT.R_OFFSET.DEG";	// deg
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DA_RESULT_R_OFFSET_DEG, str_name);

		str_name = "DA.RESULT.T_OFFSET.MM";		// mm
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DA_RESULT_T_OFFSET_MM, str_name); 
	}

	// Simulation Channel ...
	{
		str_name = "SIM.CFG.aROTATE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__ROTATE_TIME, str_name);

		str_name = "SIM.CFG.aLLx.MOVE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__LLx_MOVE_TIME, str_name);

		str_name = "SIM.CFG.aPMx.MOVE.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0,9999,"");
		LINK__VAR_ANALOG_CTRL(aCH__SIM_CFG__PMx_MOVE_TIME, str_name);		
	}

	// ...
	{
		str_name = "GET.CPTR.SNS.FULL.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__CPTR_SNS_FULL_VAL, str_name);

		//
		str_name = "GET.RQ.STN.FULL.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RQ_STN_FULL_VAL, str_name);

		// R, T, Z
		str_name = "GET.RQSTN.SNS.R.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RQSTN_SNS_R_VALUE, str_name);

		str_name = "GET.RQSTN.SNS.T.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RQSTN_SNS_T_VALUE, str_name);

		str_name = "GET.RQSTN.SNS.Z.VALUE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RQSTN_SNS_Z_VALUE, str_name);
	}
	
	// WFR CEN DATA...
	{
		str_name = "GET.WFR_CEN_DATA.FULL.VAL";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WFR_CEN_DATA__FULL_VAL, str_name);

		// Right_Sensor ...
		str_name = "WCD.RSns_LeadEdge_RadialValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__RSns_LeadEdge_RadialValue, str_name);

		str_name = "WCD.RSns_LeadEdge_ThetaValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__RSns_LeadEdge_ThetaValue, str_name);

		str_name = "WCD.RSns_TrailEdge_RadialValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__RSns_TrailEdge_RadialValue, str_name);

		str_name = "WCD.RSns_TrailEdge_ThetaValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__RSns_TrailEdge_ThetaValue, str_name);

		// Left_Sensor ...
		str_name = "WCD.LSns_LeadEdge_RadialValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__LSns_LeadEdge_RadialValue, str_name);

		str_name = "WCD.LSns_LeadEdge_ThetaValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__LSns_LeadEdge_ThetaValue, str_name);

		str_name = "WCD.LSns_TrailEdge_RadialValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__LSns_TrailEdge_RadialValue, str_name);

		str_name = "WCD.LSns_TrailEdge_ThetaValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__LSns_TrailEdge_ThetaValue, str_name);

		// Center_Sensor ...
		str_name = "WCD.CSns_Offset_RadialValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__CSns_Offset_RadialValue, str_name);

		str_name = "WCD.CSns_Offset_ThetaValue";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__CSns_Offset_ThetaValue, str_name);

		str_name = "WCD.CSns_Offset_X_Value";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__CSns_Offset_X_Value, str_name);

		str_name = "WCD.CSns_Offset_Y_Value";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__WCD__CSns_Offset_Y_Value, str_name);
	}

	// ERROR TEST ...
	{
		str_name = "ERROR_TEST.ACTIVE";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__ERROR_TEST__ACTIVE, str_name);

		str_name = "ERROR_TEST.ERROR_CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ERROR_TEST__ERROR_CODE, str_name);
	}

	// ...
	{
  		p_variable->Add__MONITORING_PROC(3.0, MON_ID__IO_MONITOR);
	}
	return 1;
}


// ...
#define  _LALM__ABORT_RETRY						\
l_act.RemoveAll();								\
l_act.Add("ABORT");								\
l_act.Add("RETRY");

#define  _LALM__ABORT_RETRY_IGNORE				\
l_act.RemoveAll();								\
l_act.Add("ABORT");								\
l_act.Add("RETRY");								\
l_act.Add("IGNORE");

#define  _LALM__CHECK							\
l_act.RemoveAll();								\
l_act.Add("CHECK");

#define  _LALM__ABORT_IGNORE					\
l_act.RemoveAll();								\
l_act.Add("ABORT");								\
l_act.Add("IGNORE");

#define  _LALM__ABORT							\
l_act.RemoveAll();								\
l_act.Add("ABORT");


int CObj_NET__VAC_PERSIMMON::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_bff;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Offline.";

		alarm_msg  = "Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		_LALM__CHECK;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ERROR_CODE;

		alarm_title  = title;
		alarm_title += "Error Code !";

		alarm_msg = "Please, check HW status !\n";

		_LALM__ABORT_RETRY_IGNORE;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}
	// ...
	{
		alarm_id = ALID__FUNCTION_NOT_EXIST;

		alarm_title  = title;
		alarm_title += "Function dose not exist !";

		alarm_msg = "Please, check the object code !\n";

		_LALM__ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	return 1;
}


// ...
#define APP_DSP__COMM_STS						\
"OFFLINE  ONLINE"

#define APP_DSP__CMD_SET						\
"AGoto	AGoto_Offset							\
 HomeAll HomeR									\
 APick_Act APick_Extend APick_Retract           \
 APlace_Act APlace_Extend APlace_Retract        \
 APlace_Offset									\
 BPlace_Offset									\
 Reset											\
 BGoto	BGoto_Offset							\
 BPick_Act BPick_Extend BPick_Retract           \
 BPlace_Act BPlace_Extend BPlace_Retract        \
 APickAL APlaceAL								\
 BPickAL BPlaceAL								\
 LoadA LoadB UnloadA UnloadB					\
 ChkLoad ChkLoadA ChkLoadB						\
 WfrSnsIntk ComInit ASet_Cptr_On ASet_Cptr_Off	\
 BSet_Cptr_On BSet_Cptr_Off AGet_Cptr BGet_Cptr \
 AGet_Current_Stn BGet_Current_Stn              \
 ASet_Stn BSet_Stn                              \
 Wfr_Cen_Data                                   \
 SET_CPTR_21_ON SET_CPTR_21_OFF GET_CPTR_21"

#define APP_DSP__STN_NUM				"1 2 3 4 5 6 7 8 9 10 11 12 13 14 15 16"
#define APP_DSP__CPTR_STN_NUM			"1 2 3 4 5 6 7 8 9 10"
#define APP_DSP__MATERIAL				"Unknown Absent Present"
#define APP_DSP__WAFER_SNS				"Yes No"
#define APP_DSP__ARM_STS				"Unknown Retracted Extended"


int CObj_NET__VAC_PERSIMMON::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;
	CString fnc_name;


	// String ...
 	{
		// SI
		{
			str_name = "esi.RB1.Version";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__VERSION, str_name);

			//
			str_name = "si.RB1.Sts.AUTO";
			IO__ADD_STRING_READ_WITH_OPTION(str_name, "","","", 0.1, "");
			LINK__IO_VAR_STRING_CTRL(siCH__RB_STS_READ_AUTO, str_name);

			str_name = "si.RB1.Sts.MANUAL";
			IO__ADD_STRING_READ__MANUAL(str_name);
			LINK__IO_VAR_STRING_CTRL(siCH__RB_STS_READ_MANUAL, str_name);
		}
	}

	// Analog ...
 	{
		// AI
		{
			str_name = "eai.RB1.ErrId";
			IO__ADD_ANALOG_READ(str_name, "num", 0, 0, 100000);
			LINK__IO_VAR_ANALOG_CTRL(aiCH__ERRID, str_name);
		}

		// AO
		{
			str_name = "eao.RB1.RO.Offset";
			IO__ADD_ANALOG_WRITE(str_name, "", 0, -9999999, 9999999);
			LINK__IO_VAR_ANALOG_CTRL(aoCH_RO_OFFSET, str_name);

			str_name = "eao.RB1.TO.Offset";
			IO__ADD_ANALOG_WRITE(str_name, "", 0, -9999999, 9999999);
			LINK__IO_VAR_ANALOG_CTRL(aoCH_TO_OFFSET, str_name);

			str_name = "eao.RB1.STN.R.VAL";
			IO__ADD_ANALOG_WRITE(str_name, "", 0, -9999999, 9999999);
			LINK__IO_VAR_ANALOG_CTRL(aoCH_STN_R_VAL, str_name);

			str_name = "eao.RB1.STN.T.VAL";
			IO__ADD_ANALOG_WRITE(str_name, "", 0, -9999999, 9999999);
			LINK__IO_VAR_ANALOG_CTRL(aoCH_STN_T_VAL, str_name);
		}
	}

	// Digital ...
	{
		// DO
		{
			str_name = "edo.RB1.Command";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__CMD_SET);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__COMMAND, str_name);

			str_name = "edo.RB1.StnA";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__STN_NUM);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__STN_A, str_name);

			str_name = "edo.RB1.StnB";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__STN_NUM);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__STN_B, str_name);

			str_name = "edo.RB1.CPTR.StnA";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__CPTR_STN_NUM);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__CPTR_STN_A, str_name);

			str_name = "edo.RB1.CPTR.StnB";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__CPTR_STN_NUM);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__CPTR_STN_B, str_name);

			str_name = "edo.RB1.Slot";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__SLOT_NUM);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__SLOT, str_name);

			str_name = "edo.RB1.ZPos";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__DOWN_UP);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__ZPOS, str_name);

			str_name = "edo.RB1.RPos";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__RET_EXT);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__RPOS, str_name);
			
			str_name = "edo.RB1.ArmAMat";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__MATERIAL);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__ARM_A_MAT, str_name);

			str_name = "edo.RB1.ArmBMat";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__MATERIAL);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__ARM_B_MAT, str_name);

			str_name = "edo.RB1.WfrSns";
			IO__ADD_DIGITAL_WRITE(str_name, APP_DSP__WAFER_SNS);
			LINK__IO_VAR_DIGITAL_CTRL(doCH__ARM_WFR_SNS, str_name);
		}

		// DI
		{
			str_name = "edi.RB1.ArmARad";
			IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__ARM_STS);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__ARM_A_READ, str_name);

			str_name = "edi.RB1.ArmBRad";
			IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__ARM_STS);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__ARM_B_READ, str_name);
			
			str_name = "edi.RB1.ArmAMat.Read";
			IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__MATERIAL);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__ARM_A_MAT_READ, str_name);

			str_name = "edi.RB1.ArmBMat.Read";
			IO__ADD_DIGITAL_READ__MANUAL(str_name, APP_DSP__MATERIAL);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__ARM_B_MAT_READ, str_name);
		}
	}
	
	return 1;
}

//--------------------------------------------------------------------------------
int CObj_NET__VAC_PERSIMMON::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString str_name;
	CString obj_name;
	CString var_name;

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iSim_Flag = x_seq->Is__SIMULATION_MODE();

		iFlag__APP_LOG = 1;
		iFlag__DRV_LOG = 1;
	}

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
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s_DRV.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xDRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xDRV_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xDRV_LOG_CTRL->DISABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);

		xDRV_LOG_CTRL->ENABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	return 1;
}
int CObj_NET__VAC_PERSIMMON::__INITIALIZE__IO(p_io_para)
{
	//------------------------------------------------------
	CString net_ip   = "127.0.0.1";
	CString net_port = "10001";

	m_nCommState = ONLINE;

	// ...
	{
		CString para_cmmd;
		CString para_data;

		// 1. IP
		{
			para_cmmd = "IP";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_ip = para_data;
			}
		}
		// 2. Port
		{
			para_cmmd = "PORT";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_port = para_data;
			}
		}

		// ...
		CString str_end = "";
		int end_len;

		str_end += (char) __CR;
		str_end += (char) __LF;

		end_len = str_end.GetLength();

		mX_Net->SET__TERMINAL_InSTRING(str_end,  end_len);
		mX_Net->SET__TERMINAL_OutSTRING(str_end, end_len);
	}

	// ...
	CString log_msg;
	CString log_bff;

	CString str_data;

	// ...
	{
		sEnd_InStr  = mX_Net->GET__TERMINAL_InSTRING();	
		sEnd_OutStr = mX_Net->GET__TERMINAL_OutSTRING();
	}

	// ...
	{
		log_msg.Format("Connecting to Serial ... \n");

		log_msg = "Connect to Ethernet ... \n";

		log_bff.Format("Net_IP : %s \n", net_ip);
		log_msg += log_bff;

		log_bff.Format("Net_Port : %s \n", net_port);
		log_msg += log_bff;

		log_bff.Format("End_InStr  : %s \n", sEnd_InStr);
		log_msg += log_bff;

		log_bff.Format("End_OutStr : %s \n", sEnd_OutStr);
		log_msg += log_bff;

		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		CString str_info;

		str_info.Format("IP(%s) Port(%s)", net_ip,net_port);

		sCH__MON_COMMUNICATION_INFO->Set__DATA(str_info);
	}

	if(iSim_Flag > 0)
	{
		log_msg = "Simulation Mode !!! \n";

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
		return 1;
	}

	// ...
	CString err_msg;

	mX_Net->INIT__PROPERTY(net_ip, atoi(net_port));
	if(mX_Net->CONNECT(&err_msg) < 0)
	{
		log_msg = "Connection Result ... \n";
		log_bff.Format("Fail to do INIT__ETHERNET: %s(%s), ret(-1) \n", net_ip,net_port);
		log_msg += log_bff;
		log_bff.Format(" * Error Message <- \"%s\" \n", err_msg);
		log_msg += log_bff;

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		log_msg = "Connection Result ... \n";
		log_msg += "Init-Ethernet Completed ... \n";

		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj_NET__VAC_PERSIMMON::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	mMNG__ERR_CODE.Clear__Error_Code();

	// ...
	int flag = -1;

	CString para__arm_type;
	CString para__stn_name;
	CString para__stn_slot;

	CString szUpperObj;
	CString log_msg;

	// Driver���� timeout���� ����ȴ�.
	sCH__ACTION_STS->Set__DATA(mode);

	// ...
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
		log_msg.Format("--------> Start ... :  [%s] (%s,%s,%s)",
					   mode,
					   para__arm_type,
					   para__stn_name,
					   para__stn_slot);

		Fnc__APP_LOG(log_msg);
	}

	// ...
	pII__EXT_MODE_CTRL = p_variable->Get__EXT_FNC_MODE_CTRL();
	pII__EXT_VAR_CTRL  = p_variable->Get__EXT_FNC_VAR_CTRL();
	pII__EXT_FNC_CTRL  = p_variable->Get__EXT_USER_FNC_CTRL();

	// ...
	szUpperObj = pII__EXT_MODE_CTRL->Get__UPPER_OBJECT_NAME();	

	log_msg.Format("Object Call: [%s] ==> [%s]",  szUpperObj, sObject_Name);
	Fnc__APP_LOG(log_msg);

	//	Clear ...
	{
		sCH__ERRID->Set__DATA("");
	}

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)
		{
			flag = Call__INIT(p_variable,p_alarm);
		}
		ELSE_IF__CTRL_MODE(sMODE__PICK)
		{
			flag = Call__PICK(p_variable,p_alarm, para__stn_name,para__arm_type,para__stn_slot);

			// Save Before Info...
			if(para__arm_type.CompareNoCase(ARM_A) == 0)	m_sBefore_Stn_Retract_ArmA = para__stn_name;
			else											m_sBefore_Stn_Retract_ArmB = para__stn_name;
		}
		ELSE_IF__CTRL_MODE(sMODE__PLACE)				flag = Call__PLACE(p_variable,p_alarm, para__stn_name,para__arm_type,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__ROTATE)				flag = Call__ROTATE(p_variable,p_alarm, para__stn_name,para__arm_type,para__stn_slot);
		ELSE_IF__CTRL_MODE(sMODE__HOME)					flag = Call__HOME(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__RQ_WFR_CEN_DATA)		flag = Call__RQ_WFR_CEN_DATA(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CHECK_ERROR_CODE)		flag = Call__CHECK_ERROR_CODE(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__EXTEND)
		{
			flag = Call__EXTEND(p_variable,p_alarm, mode,para__stn_name,para__arm_type,para__stn_slot);
		}
		ELSE_IF__CTRL_MODE(sMODE__RETRACT)
		{
			flag = Call__RETRACT(p_variable,p_alarm, mode,para__stn_name,para__arm_type,para__stn_slot);

			// Save Before Info...
			if(para__arm_type.CompareNoCase(ARM_A) == 0)	m_sBefore_Stn_Retract_ArmA = para__stn_name;
			else											m_sBefore_Stn_Retract_ArmB = para__stn_name;
		}
		ELSE_IF__CTRL_MODE(sMODE__GOUP)
		{
			flag = Call__GOUP(p_variable,p_alarm, mode,para__stn_name,para__arm_type,para__stn_slot);
		}
		ELSE_IF__CTRL_MODE(sMODE__GODOWN)
		{
			flag = Call__GODOWN(p_variable,p_alarm, mode,para__stn_name,para__arm_type,para__stn_slot);
		}
		ELSE_IF__CTRL_MODE(sMODE__RQ_STN)
		{
			flag = Call__RQ_STN(p_variable,p_alarm, mode,para__stn_name,para__arm_type);
		}
		ELSE_IF__CTRL_MODE(sMODE__SET_STN)
		{
			flag = Call__SET_STN(p_variable,p_alarm, mode,para__stn_name,para__arm_type);
		}
		ELSE_IF__CTRL_MODE(sMODE__TEACHED_CPTR_SAVE)
		{
			flag = Call__TEACHED_CPTR_SAVE(p_variable,p_alarm, mode,para__stn_name,para__arm_type);
		}
	}

	// ERR_CHECK ...
	{
		CString err_code;
		CString err_msg;

		if(dCH__ERROR_TEST__ACTIVE->Check__DATA(STR__YES) > 0)
		{
			CString err_code = sCH__ERROR_TEST__ERROR_CODE->Get__STRING();
			_Check__ERROR_CODE(err_code);
		}

		while(mMNG__ERR_CODE.Get__Error_Code(err_code,err_msg) > 0)
		{
			int i_error = atoi(err_code);
			if(i_error == 0)		continue;

			sCH__ERRID->Set__DATA(err_code);

			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "Error_Code Occurred !!!";

				log_bff.Format("Error_Code : [%s] \n", err_code);
				log_msg += log_bff;
				log_bff.Format("Error_Msg  : [%s] \n", err_msg);
				log_msg += log_bff;

				Fnc__APP_LOG(log_msg);
			}

			// ...
			int alm_id = ALID__ERROR_CODE;
			CString alm_msg;
			CString alm_bff;
			CString r_act;

			alm_msg.Format("Control_Mode : %s \n", mode);

			alm_bff.Format("Error_Code : %s \n", err_code);
			alm_msg += alm_bff;
			alm_bff.Format("Error_Message \n");
			alm_msg += alm_bff;
			alm_msg += "  * ";
			alm_msg += err_msg;

			// ...
			{
				CString log_msg;

				log_msg.Format("Alarm Post : %1d \n", alm_id);
				log_msg += alm_msg;

				Fnc__APP_LOG(log_msg);
			}

			p_alarm->Popup__ALARM_With_MESSAGE(alm_id,alm_msg,r_act);			

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				CString log_msg = "Alarm Selection <- Retry";
				Fnc__APP_LOG(log_msg);

				goto LOOP_RETRY;
			}
			if(r_act.CompareNoCase(ACT__ABORT) == 0)
			{
				CString log_msg = "Alarm Selection <- Abort";
				Fnc__APP_LOG(log_msg);

				flag = -1;
				break;
			}

			if(r_act.CompareNoCase(ACT__IGNORE) == 0)
			{
				// ...
			}
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("<-- Aborted(%1d) ...  : [%s]", flag,mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);

		log_msg.Format("%s_Failed",mode);

		if(para__arm_type.CompareNoCase(ARM_A) == 0)		sCH__ARM_A_BEFORE_MODE_STS->Set__DATA(log_msg);
		else												sCH__ARM_B_BEFORE_MODE_STS->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("<-- Completed ... :  [%s]",mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);

		if(mode.CompareNoCase(sMODE__ROTATE) != 0)			// PICK �Ŀ� ROTATE �ϹǷ�.. Update ����..
		{
			log_msg.Format("%s_Success",mode);

			if(para__arm_type.CompareNoCase(ARM_A) == 0)	sCH__ARM_A_BEFORE_MODE_STS->Set__DATA(log_msg);
			else											sCH__ARM_B_BEFORE_MODE_STS->Set__DATA(log_msg);
		}
	}

	return flag;
}

int CObj_NET__VAC_PERSIMMON::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
