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

	// CFG ...
	{
		str_name = "CFG.TAG_READ_ID_INSTALLED_CHECK_SKIP";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_TAG_READ_ID_INSTALLED_CHECK_SKIP, str_name);
	}

	// RSP: PARA ...
	{
		str_name = "PARA.PAGE.ID";
		STD__ADD_ANALOG(str_name, "page", 0, 1, 17);
		LINK__VAR_ANALOG_CTRL(aCH__PARA_PAGE_ID, str_name);

		str_name = "PARA.CID.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_CID_DATA, str_name);

		str_name = "PARA.PAGE.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_PAGE_DATA, str_name);
	}

	// RSP: PAGE ...
	{
		str_name = "RSP.CID.DATA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__RSP_CID_DATA, str_name);

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
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "RF Reader : Offline";

		alarm_msg  = "1. Check the Serial cable.\n";
		alarm_msg += "2. Check the RF Reader power.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Offline [Full Auto]";

		alarm_msg  = "1. Check the Serial cable.\n";
		alarm_msg += "2. Check the RF Reader power.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Offline [Not Full Auto]";

		alarm_msg  = "1. Check the Serial cable.\n";
		alarm_msg += "2. Check the RF Reader power.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__IGNORE);
		l_act.Add(ACT__ABORT);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_AUTOFAIL;

		alarm_title  = title;
		alarm_title += "RF Reader : Auto Fail";

		alarm_msg = "1. Automatic reading is not possible.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_AUTOFAIL_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Auto Fail [Full Auto]";

		alarm_msg = "1. Automatic reading is not possible.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_AUTOFAIL_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Auto Fail [Not Full Auto]";

		alarm_msg = "1. Automatic reading is not possible.\n";
	
		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__RF_EXFAIL;

		alarm_title  = title;
		alarm_title += "RF Reader :  Ex-Fail";

		alarm_msg  = "1. read of write initiated from the terminal respectively other.\n";
		alarm_msg += "  actions cannot be carried out.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_EXFAIL_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader :  Ex-Fail [Full Auto]";

		alarm_msg  = "1. read of write initiated from the terminal respectively other.\n";
		alarm_msg += "  actions cannot be carried out.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_EXFAIL_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader :  Ex-Fail [Not Full Auto]";

		alarm_msg  = "1. read of write initiated from the terminal respectively other.\n";
		alarm_msg += "  actions cannot be carried out.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_WRITEFAIL;

		alarm_title  = title;
		alarm_title += "RF Reader :  Write-Fail";

		alarm_msg  = "1. data transfer to the tag not possible.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_WRITEFAIL_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader :  Write-Fail [Full Auto]";

		alarm_msg  = "1. data transfer to the tag not possible.\n";
	
		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_WRITEFAIL_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader :  Write-Fail [Not Full Auto]";

		alarm_msg  = "1. data transfer to the tag not possible.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_NOTAG;

		alarm_title  = title;
		alarm_title += "RF Reader : NO Tag";

		alarm_msg  = "1. NO Tag or antenna installed.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_NOTAG_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : NO Tag [Full Auto]";

		alarm_msg  = "1. NO Tag or antenna installed.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_NOTAG_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : NO Tag [Not Full Auto]";

		alarm_msg  = "1. NO Tag or antenna installed.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INVALID1;

		alarm_title  = title;
		alarm_title += "RF Reader : Invalid1";

		alarm_msg  = "1. Invalid paramter or command.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INVALID1_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Invalid1 [Full Auto]";

		alarm_msg  = "1. Invalid paramter or command.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INVALID1_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Invalid1 [Not Full Auto]";

		alarm_msg  = "1. Invalid paramter or command.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_UNKNOWN;

		alarm_title  = title;
		alarm_title += "RF Reader : Unknown";

		alarm_msg  = "1. Unknown failure.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_UNKNOWN_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Unknown [Full Auto]";

		alarm_msg  = "1. Unknown failure.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_UNKNOWN_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Unknown [Not Full Auto]";

		alarm_msg  = "1. Unknown failure.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_UNCONFIG;

		alarm_title  = title;
		alarm_title += "RF Reader : Unconfig";

		alarm_msg  = "1. The device is not configured.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);
	
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_UNCONFIG_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Unconfig [Full Auto]";

		alarm_msg  = "1. The device is not configured.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_UNCONFIG_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Unconfig [Not Full Auto]";

		alarm_msg  = "1. The device is not configured.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_CHECK;

		alarm_title  = title;
		alarm_title += "RF Reader : Check";

		alarm_msg  = "1. Parity or and checksum failure.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_CHECK_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Check [Full Auto]";

		alarm_msg  = "1. Parity or and checksum failure.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_CHECK_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Check [Not Full Auto]";

		alarm_msg  = "1. Parity or and checksum failure.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_VOIDACKNE;

		alarm_title  = title;
		alarm_title += "RF Reader : Void Ackn";

		alarm_msg  = "1. No Valid Acknowledge.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_VOIDACKNE_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Void Ackn [Full Auto]";

		alarm_msg  = "1. No Valid Acknowledge.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_VOIDACKNE_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Void Ackn [Not Full Auto]";

		alarm_msg  = "1. No Valid Acknowledge.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_LOCKED;

		alarm_title  = title;
		alarm_title += "RF Reader : Locked";

		alarm_msg  = "1. Locked Page cannot be written.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_LOCKED_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Locked [Full Auto]";

		alarm_msg  = "1. Locked Page cannot be written.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_LOCKED_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Locked [Not Full Auto]";

		alarm_msg  = "1. Locked Page cannot be written.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_MSGLEN;

		alarm_title  = title;
		alarm_title += "RF Reader : Msg Len";

		alarm_msg  = "1. Message too long.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_MSGLEN_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Msg Len [Full Auto]";

		alarm_msg  = "1. Message too long.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_MSGLEN_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Msg Len [Not Full Auto]";

		alarm_msg  = "1. Message too long.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INVALID2;

		alarm_title  = title;
		alarm_title += "RF Reader : Invalid2";

		alarm_msg  = "1. Invalid Parameter or Command.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INVALID2_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Invalid2 [Full Auto]";

		alarm_msg  = "1. Invalid Parameter or Command.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_INVALID2_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : Invalid2 [Not Full Auto]";

		alarm_msg  = "1. Invalid Parameter or Command.\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_NOACKN;

		alarm_title  = title;
		alarm_title += "RF Reader : No Ackn";

		alarm_msg  = "1. The Message which has to be confirmed has been sent maximally.\n";
		alarm_msg += "   (RS232 maxrepeat) and has not been confirmed by the terminal.\n";
		alarm_msg += "   within the defined thme frame (see paramter 5).\n";

		l_act.RemoveAll();
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_NOACKN_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : No Ackn [Full Auto]";

		alarm_msg  = "1. The Message which has to be confirmed has been sent maximally.\n";
		alarm_msg += "   (RS232 maxrepeat) and has not been confirmed by the terminal.\n";
		alarm_msg += "   within the defined thme frame (see paramter 5).\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__RF_NOACKN_NOT_FULL_AUTO;

		alarm_title  = title;
		alarm_title += "RF Reader : No Ackn [Not Full Auto]";

		alarm_msg  = "1. The Message which has to be confirmed has been sent maximally.\n";
		alarm_msg += "   (RS232 maxrepeat) and has not been confirmed by the terminal.\n";
		alarm_msg += "   within the defined thme frame (see paramter 5).\n";

		l_act.RemoveAll();
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__IGNORE);

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
	CString ch_name;
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

		var_name.Format("LP_INFO.RFID_ERROR_CODE.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__RFID_ERROR_CODE, obj_name,var_name);

		// IO
		var_name.Format("si.RFID_READ.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(siEXT_CH__RFID_READ, obj_name,var_name);

		var_name.Format("so.RFID_WRITE.%1d", id);
		LINK__EXT_VAR_STRING_CTRL(soEXT_CH__RFID_WRITE, obj_name,var_name);
	}

	// LINK_PIO ...
	{
		def_name = "CH.LINK_PIO.ACTIVE.FA_AUTO";						// OFF ON
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LINK_PIO_ACTIVE_FA_AUTO, obj_name,var_name);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq;

		iActive__SIM_MODE = x_seq->Is__SIMULATION_MODE();
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
