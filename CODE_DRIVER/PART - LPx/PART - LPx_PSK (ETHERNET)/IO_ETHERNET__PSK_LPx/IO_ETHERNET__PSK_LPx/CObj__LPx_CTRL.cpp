#include "stdafx.h"

#include "CObj__LPx_CTRL__ALID.h"
#include "CObj__LPx_CTRL__DEF.h"
#include "CObj__LPx_CTRL.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__LPx_CTRL::CObj__LPx_CTRL()
{

}
CObj__LPx_CTRL::~CObj__LPx_CTRL()
{

}

//--------------------------------------------------------------------------------
int CObj__LPx_CTRL::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");
		ADD__CTRL_VAR(sMODE__HOME,	"HOME");

		ADD__CTRL_VAR(sMODE__DOOR_OPEN,	 "DOOR_OPEN");
		ADD__CTRL_VAR(sMODE__DOOR_CLOSE, "DOOR_CLOSE");

		ADD__CTRL_VAR(sMODE__LOAD,	 "LOAD");
		ADD__CTRL_VAR(sMODE__UNLOAD, "UNLOAD");

		ADD__CTRL_VAR(sMODE__SHUTTLE_IN,  "SHUTTLE_IN");
		ADD__CTRL_VAR(sMODE__SHUTTLE_OUT, "SHUTTLE_OUT");

		ADD__CTRL_VAR(sMODE__CLAMP,	  "CLAMP");
		ADD__CTRL_VAR(sMODE__UNCLAMP, "UNCLAMP");

		ADD__CTRL_VAR(sMODE__MAP, "MAP");

		ADD__CTRL_VAR(sMODE__CID_READ,   "CID_READ");
		ADD__CTRL_VAR(sMODE__PAGE_READ,  "PAGE_READ");
		ADD__CTRL_VAR(sMODE__CID_WRITE,  "CID_WRITE");
		ADD__CTRL_VAR(sMODE__PAGE_WRITE, "PAGE_WRITE");

		ADD__CTRL_VAR(sMODE__AMHS_AUTO,       "AMHS.AUTO");
		ADD__CTRL_VAR(sMODE__AMHS_MANUAL,     "AMHS.MANUAL");
		ADD__CTRL_VAR(sMODE__AMHS_HO_ENABLE,  "AMHS.HO.ENABLE");
		ADD__CTRL_VAR(sMODE__AMHS_HO_DISABLE, "AMHS.HO.DISBLE");

		ADD__CTRL_VAR(sMODE__N2_PURGE_START, "N2_PURGE.START");
		ADD__CTRL_VAR(sMODE__N2_PURGE_STOP,  "N2_PURGE.STOP");

		ADD__CTRL_VAR(sMODE__SIM_FOUP_EXIST, "SIM.FOUP_EXIST");
		ADD__CTRL_VAR(sMODE__SIM_FOUP_NONE,  "SIM.FOUP_NONE");
	}
	return 1;
}
int CObj__LPx_CTRL::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__STATE_MONITOR				1


#define APP_DSP__LP_OFF_ON					"OFF ON"
#define APP_DSP__LP_UNLOCK_LOCK				"NONE UNLOCK LOCK"
#define APP_DSP__LP_WFR_SLOT_STS			"UNKNOWN ABSENT PRESENT DOUBLE CROSSED INVALID"
#define APP_DSP__RB_TARGET_MOVE				"UNKNOWN HOME READY LP1 LP2 LP3 LP4 LBA LBB VIS1 AL1"


int CObj__LPx_CTRL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		CString str_list;
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS", str_list);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, str_list, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// PARA ...
	{
		str_name = "PARA.N2_PURGE.MFC_SET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_N2_PURGE_MFC_SET, str_name);

		str_name = "PARA.N2_PURGE.DELAY_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__PARA_N2_PURGE_DELAY_TIME, str_name);

		str_name = "PARA.N2_PURGE.EHHAUST_NOZZLE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "OFF ON", "");
		LINK__VAR_DIGITAL_CTRL(dCH__PARA_N2_PURGE_EHHAUST_NOZZLE, str_name);
	}

	// CFG.N2_PURGE ...
	{
		str_name = "CFG.PURGE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PURGE_USE, str_name);

		//
		str_name = "CFG.PURGE.PRE_BLOW.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PURGE_PRE_BLOW_USE, str_name);

		str_name = "CFG.PURGE.PRE_BLOW.TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_PRE_BLOW_TIME, str_name);

		//
		str_name = "CFG.PURGE.PRE_PURGE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PURGE_PRE_PURGE_USE, str_name);

		str_name = "CFG.PURGE.PRE_PURGE.FLOW_SET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_PRE_PURGE_FLOW_SET, str_name);

		str_name = "CFG.PURGE.PRE_PURGE.DELAY_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_PRE_PURGE_DELAY_TIME, str_name);

		//
		str_name = "CFG.PURGE.PROCESS_PURGE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PURGE_PROCESS_PURGE_USE, str_name);

		str_name = "CFG.PURGE.POST_PURGE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PURGE_POST_PURGE_USE, str_name);

		//
		str_name = "CFG.PURGE.STNADBY_PURGE.USE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO YES", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_PURGE_STNADBY_PURGE_USE, str_name);

		str_name = "CFG.PURGE.STNADBY_PURGE.FLOW_SET";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_STNADBY_PURGE_FLOW_SET, str_name);

		str_name = "CFG.PURGE.STNADBY_PURGE.DELAY_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_STNADBY_PURGE_DELAY_TIME, str_name);

		//
		str_name = "CFG.PURGE.WARNING.FLOW_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_WARNING_FLOW_TIME, str_name);

		str_name = "CFG.PURGE.WARNING.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_WARNING_TIMEOUT, str_name);

		//
		str_name = "CFG.PURGE.ALARM.FLOW_TIME";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "slm", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_ALARM_FLOW_TIME, str_name);

		str_name = "CFG.PURGE.ALARM.TIMEOUT";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 100, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_PURGE_ALARM_TIMEOUT, str_name);
	}

	// MON.PIO ...
	{
		str_name = "MON.LPx_PIO.FA_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_LPx_PIO_FA_MODE, str_name);

		str_name = "MON.LPx_PIO.SERVICE_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_LPx_PIO_SERVICE_MODE, str_name);

		//
		str_name = "MON.LPx_PIO.RUN_SNS";
		STD__ADD_DIGITAL(str_name, "UNKNOWN RUN DONE STOP");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LPx_PIO_RUN_SNS, str_name);

		str_name = "MON.LPx_PIO.TRANSFER_SNS";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_LPx_PIO_TRANSFER_SNS, str_name);
	}
	// MON.STATUS ...
	{
		str_name = "MON.DOOR.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_DOOR_STATUS, str_name);

		str_name = "MON.FOUP.POS.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_FOUP_POS_STATUS, str_name);

		str_name = "MON.FOUP.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_FOUP_STATUS, str_name);

		str_name = "MON.CLAMP.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_CLAMP_STATUS, str_name);
	}

	// RES.MAP ...
	{
		for(int i=0; i<CFG_LPx__SLOT_SIZE; i++)
		{
			str_name.Format("RES.MAP.SLOT%002d", i+1);
			STD__ADD_DIGITAL(str_name, "UNKNOWN PRESENT ABSENT");
			LINK__VAR_DIGITAL_CTRL(dCH__RES_MAP_SLOT_X[i], str_name);			
		}
	}

	// MODE : PARA ...
	{
		str_name = "PARA.LP_MODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_LP_MODE, str_name);

		str_name = "PARA.LP_RFID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_LP_RFID, str_name);

		str_name = "PARA.LP_USE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_LP_USE, str_name);

		str_name = "PARA.LP_CLOSE_MAPPING";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_LP_CLOSE_MAPPING, str_name);
	}

	// RSP: PARA ...
	{
		str_name = "PARA.PAGE.CID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PAGE_CID, str_name);

		str_name = "PARA.PAGE.ID";
		STD__ADD_ANALOG(str_name, "page", 0, 1, 17);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PAGE_ID, str_name);

		str_name = "PARA.PAGE.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PAGE_DATA, str_name);
	}
	// RSP: PAGE ...
	{
		str_name = "RSP.PAGE.CID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RSP_PAGE_CID, str_name);

		str_name = "RSP.PAGE.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RSP_PAGE_DATA, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_MONITOR);
	}
	return 1;
}

int CObj__LPx_CTRL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s : ",sObject_Name);

	int alarm_id;
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// ...
	{
		alarm_id = ALID__OFFLINE;

		alarm_title  = title;
		alarm_title += "Offline !";

		alarm_msg = "Please, check communication line !\n";

		l_act.RemoveAll();
		l_act.Add(ALM_ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	// ...
	{
		alarm_id = ALID__LPx_ERROR_CODE;

		alarm_title  = title;
		alarm_title += "LPx Error Code !";

		alarm_msg = "Please, check HW status !\n";

		l_act.RemoveAll();
		l_act.Add(ALM_ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__LPx_CTRL
::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;

	CString obj_name;
	CString var_name;
	int i;

	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s-APP.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		// ...
		{
			xAPP__LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xAPP__LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

			xAPP__LOG_CTRL->DISABLE__TIME_LOG();
			xAPP__LOG_CTRL->WRITE__LOG(log_msg);

			xAPP__LOG_CTRL->ENABLE__TIME_LOG();
			xAPP__LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	// LINK DRIVER ...
	{
		def_name = "LINK.LPx_ID";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iLINK__LPx_ID = atoi(def_data);
		int id = iLINK__LPx_ID;

		def_name = "LINK.DRIVER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ__LPx_DRIVER = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		// PARA.N2_PURGE ...
		{
			var_name.Format("PARA.LP_N2_NOZZLE_1.VALVE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_LP_N2_NOZZLE_1__VALVE, obj_name,var_name);

			var_name.Format("PARA.LP_N2_NOZZLE_1.MFC.%1d", id);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_LP_N2_NOZZLE_1__MFC, obj_name,var_name);

			var_name.Format("PARA.LP_N2_NOZZLE_2.VALVE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_LP_N2_NOZZLE_2__VALVE, obj_name,var_name);

			var_name.Format("PARA.LP_N2_NOZZLE_2.MFC.%1d", id);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_LP_N2_NOZZLE_2__MFC, obj_name,var_name);

			var_name.Format("PARA.LP_N2_NOZZLE_3.VALVE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_LP_N2_NOZZLE_3__VALVE, obj_name,var_name);

			var_name.Format("PARA.LP_N2_NOZZLE_3.MFC.%1d", id);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_LP_N2_NOZZLE_3__MFC, obj_name,var_name);

			//
			var_name.Format("PARA.LP_N2_EHHAUST_NOZZLE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__PARA_LP_N2_EHHAUST_NOZZLE, obj_name,var_name);

			var_name.Format("PARA.LP_N2_DELAY_TIME.%1d", id);
			LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_LP_N2_DELAY_TIME, obj_name,var_name);
		}

		// MON ...
		{
			var_name = "MON.COMMUNICATION.STATE";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_COMMUNICATION_STATE, obj_name,var_name);
		}

		// CFG ...
		{
			var_name.Format("CFG.LP_MODE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LP_MODE, obj_name,var_name);

			var_name.Format("CFG.LP_RFID.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LP_RFID, obj_name,var_name);

			var_name.Format("CFG.LP_USE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LP_USE, obj_name,var_name);

			var_name.Format("CFG.LP_CLOSE_MAPPING.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LP_CLOSE_MAPPING, obj_name,var_name);
		}

		// LP_INFO ...
		{
			var_name.Format("LP_INFO.ALM_TXT.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__ALM_TXT, obj_name,var_name);

			var_name.Format("LP_INFO.ALM_MSG.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__ALM_MSG, obj_name,var_name);

			//
			var_name.Format("LP_INFO.INITIAL.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__INITIAL, obj_name,var_name);

			var_name.Format("LP_INFO.STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__STATUS, obj_name,var_name);

			var_name.Format("LP_INFO.FOUP_EXIST.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__FOUP_EXIST, obj_name,var_name);

			var_name.Format("LP_INFO.DOOR_STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__DOOR_STATUS, obj_name,var_name);

			var_name.Format("LP_INFO.CLAMP_STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__CLAMP_STATUS, obj_name,var_name);

			var_name.Format("LP_INFO.RFID_STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__RFID_STATUS, obj_name,var_name);

			var_name.Format("LP_INFO.AGV_STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__AGV_STATUS, obj_name,var_name);

			var_name.Format("LP_INFO.ENABLE.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__ENABLE, obj_name,var_name);

			var_name.Format("LP_INFO.RFID_ENABLE.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__RFID_ENABLE, obj_name,var_name);;

			var_name.Format("LP_INFO.CLOSE_MAPPING_ENABLE.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__CLOSE_MAPPING_ENABLE, obj_name,var_name);

			var_name.Format("LP_INFO.ONLINE_MODE.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__ONLINE_MODE, obj_name,var_name);

			var_name.Format("LP_INFO.LOAD_BUTTON_STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__LOAD_BUTTON_STATUS, obj_name,var_name);

			var_name.Format("LP_INFO.UNLOAD_BUTTON_STATUS.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__UNLOAD_BUTTON_STATUS, obj_name,var_name);
		}

		// MAP RESULT ...
		for(i=0; i<CFG_LPx__SLOT_SIZE; i++)
		{
			var_name.Format("LP_MAP.RESULT.%1d.SLOT%02d", id, i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_MAP__RESULT[i], obj_name,var_name);
		}

		// IO ...
		{
			var_name.Format("si.LP_ALARM_MSG.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(siEXT_CH__LP_ALARM_MSG, obj_name,var_name);

			var_name.Format("si.LP_ALARM_TXT.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(siEXT_CH__LP_ALARM_TXT, obj_name,var_name);

			//
			var_name.Format("do.LP_CMMD.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LP_CMMD, obj_name,var_name);

			var_name.Format("do.LP_MODE.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LP_MODE, obj_name,var_name);

			var_name.Format("do.PIO.RESET.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__PIO_RESET, obj_name,var_name);

			//
			var_name.Format("si.LP_STATE.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(siEXT_CH__LP_STATE, obj_name,var_name);

			var_name.Format("si.LP_MAP_DATA.%1d", id);
			LINK__EXT_VAR_STRING_CTRL(siEXT_CH__LP_MAP_DATA, obj_name,var_name);

			//
			var_name.Format("do.LP_N2_RUN.%1d", id);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LP_N2_RUN, obj_name,var_name);
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iActive__SIM_MODE = x_seq->Is__SIMULATION_MODE();
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__LPx_CTRL
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	// ...
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__HOME)					flag = Call__HOME(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__DOOR_OPEN)			flag = Call__DOOR_OPEN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOOR_CLOSE)			flag = Call__DOOR_CLOSE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LOAD)					flag = Call__LOAD(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UNLOAD)				flag = Call__UNLOAD(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__SHUTTLE_IN)			flag = Call__SHUTTLE_IN(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__SHUTTLE_OUT)			flag = Call__SHUTTLE_OUT(p_variable, p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__CLAMP)				flag = Call__CLAMP(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UNCLAMP)				flag = Call__UNCLAMP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__MAP)					flag = Call__MAP(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CID_READ)				flag = Call__CID_READ(p_variable,   p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PAGE_READ)			flag = Call__PAGE_READ(p_variable,  p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CID_WRITE)			flag = Call__CID_WRITE(p_variable,  p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PAGE_WRITE)			flag = Call__PAGE_WRITE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__AMHS_AUTO)			flag = Call__AMHS_AUTO(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AMHS_MANUAL)			flag = Call__AMHS_MANUAL(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AMHS_HO_ENABLE)		flag = Call__AMHS_HO_ENABLE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__AMHS_HO_DISABLE)		flag = Call__AMHS_HO_DISBLE(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__N2_PURGE_START)		flag = Call__N2_PURGE_CONTROL(p_variable, p_alarm, true);
		ELSE_IF__CTRL_MODE(sMODE__N2_PURGE_STOP)		flag = Call__N2_PURGE_CONTROL(p_variable, p_alarm, false);

		ELSE_IF__CTRL_MODE(sMODE__SIM_FOUP_EXIST)
		{
			flag = 1;

			sCH__MON_FOUP_STATUS->Set__DATA(STR__EXIST);
		}
		ELSE_IF__CTRL_MODE(sMODE__SIM_FOUP_NONE)
		{
			flag = 1;

			sCH__MON_FOUP_STATUS->Set__DATA(STR__NONE);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted (%1d)... :  [%s]", flag,mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);

		dCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		Fnc__APP_LOG(log_msg);
	}

	return flag;
}

int CObj__LPx_CTRL
::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__STATE_MONITOR:
			Mon__STATE_MONITOR(p_variable, p_alarm);
			break;
	}

	return 1;
}
