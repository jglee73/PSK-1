#include "stdafx.h"

#include "CObj__RFID_CTRL__ALID.h"
#include "CObj__RFID_CTRL__DEF.h"
#include "CObj__RFID_CTRL.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__RFID_CTRL::CObj__RFID_CTRL()
{

}
CObj__RFID_CTRL::~CObj__RFID_CTRL()
{

}

//--------------------------------------------------------------------------------
int CObj__RFID_CTRL::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,	"INIT");

		ADD__CTRL_VAR(sMODE__CID_READ,   "CID_READ");
		ADD__CTRL_VAR(sMODE__PAGE_READ,  "PAGE_READ");
		ADD__CTRL_VAR(sMODE__CID_WRITE,  "CID_WRITE");
		ADD__CTRL_VAR(sMODE__PAGE_WRITE, "PAGE_WRITE");
	}
	return 1;
}
int CObj__RFID_CTRL::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define APP_DSP__LP_OFF_ON					"OFF ON"


int CObj__RFID_CTRL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString str_list;

	// OBJ ...
	{
		p_variable->Get__STD_DESCRIPTION("STD_OBJ_STATUS", str_list);

		str_name = "OBJ.STATUS";
		STD__ADD_DIGITAL_WITH_COMMENT(str_name, str_list, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OBJ_STATUS, str_name);

		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// MON ...
	{

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
	return 1;
}

int CObj__RFID_CTRL::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__ERROR_CODE;

		alarm_title  = title;
		alarm_title += "Error Code !";

		alarm_msg = "Please, check HW status !\n";

		l_act.RemoveAll();
		l_act.Add(ALM_ACT__ABORT);
		l_act.Add(ALM_ACT__RETRY);
		l_act.Add(ALM_ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__RFID_CTRL
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

	// ...
	{
		SCX__SEQ_INFO x_seq;

		bActive__SIM_MODE = x_seq->Is__SIMULATION_MODE();
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

		// MON
		var_name = "MON.COMMUNICATION.STATE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MON_COMMUNICATION_STATE, obj_name,var_name);

		// PARA
		var_name.Format("PARA.RFID.PAGE_ID.%1d", id);
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__PARA_RFID_PAGE_ID, obj_name,var_name);

		// LP_INFO
		var_name.Format("LP_INFO.RFID_STATUS.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__RFID_STATUS, obj_name,var_name);

		var_name.Format("LP_INFO.RFID_RSP.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__RFID_RSP, obj_name,var_name);

		// IO
		var_name.Format("si.RFID_READ.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(siEXT_CH__RFID_READ, obj_name,var_name);

		var_name.Format("so.RFID_WRITE.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(soEXT_CH__RFID_WRITE, obj_name,var_name);
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CObj__RFID_CTRL
::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	int flag = -1;

	// ...
	{
			IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__CID_READ)			flag = Call__CID_READ(p_variable,   p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PAGE_READ)		flag = Call__PAGE_READ(p_variable,  p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CID_WRITE)		flag = Call__CID_WRITE(p_variable,  p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PAGE_WRITE)		flag = Call__PAGE_WRITE(p_variable, p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted (%1d)... :  [%s]", flag,mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);

		dCH__OBJ_STATUS->Set__DATA(STR__MAINTMODE);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xAPP__LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__RFID_CTRL
::__CALL__MONITORING(id, p_variable, p_alarm)
{

	return 1;
}
