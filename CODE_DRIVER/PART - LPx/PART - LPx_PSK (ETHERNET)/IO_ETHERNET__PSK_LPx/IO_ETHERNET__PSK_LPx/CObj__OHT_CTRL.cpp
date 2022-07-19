#include "StdAfx.h"
#include "CObj__OHT_CTRL.h"
#include "CObj__OHT_CTRL__ALID.h"


//-------------------------------------------------------------------------
CObj__OHT_CTRL::CObj__OHT_CTRL()
{

}
CObj__OHT_CTRL::~CObj__OHT_CTRL()
{

}

//-------------------------------------------------------------------------
int CObj__OHT_CTRL::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
	}

	return 1;
}
int CObj__OHT_CTRL::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR				1

// ...
#define APP_DSP__OFF_ON					"OFF  ON"


int CObj__OHT_CTRL::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// REPORT ...
	{
		str_name = "REPORT_PIO.E84_RUN.STATE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "UNKNOWN RUN DONE STOP", "");
		LINK__VAR_DIGITAL_CTRL(dCH__REPORT_PIO_E84_RUN_STATE, str_name);
	}

	// USER_REQ ...
	{
		str_name = "USER_REQ.PIO.RESET";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__OFF_ON, "");
		LINK__VAR_DIGITAL_CTRL(dCH__USER_REQ_PIO_RESET, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__IO_MONITOR);
	}
	return 1;
}
int CObj__OHT_CTRL::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	return 1;
}

int CObj__OHT_CTRL::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__OHT_CTRL::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;


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

	// LINK DRIVER ...
	{
		def_name = "LINK.LPx_ID";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		int lp_id = atoi(def_data);

		//
		def_name = "LINK.DRIVER";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		// ...
		{
			var_name.Format("LP_INFO.AGV_STATUS.%1d", lp_id);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LP_INFO__AGV_STATUS, obj_name,var_name);

			var_name.Format("do.PIO.RESET.%1d", lp_id);
			LINK__EXT_VAR_DIGITAL_CTRL(doEXT_CH__LP__PIO_RESET, obj_name,var_name);
		}
	}

	// LINK_PIO ...
	{
		def_name = "CH.LINK_PIO.TRANSFER_STATE";			// NO  YES
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LINK_PIO_TRANSFER_STATE, obj_name,var_name);

		//
		def_name = "CH.LINK_PIO.ACTIVE.RUN";				// OFF ON
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LINK_PIO_ACTIVE_RUN, obj_name,var_name);

		def_name = "CH.LINK_PIO.ACTIVE.FA_AUTO";			// OFF ON
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LINK_PIO_ACTIVE_FA_AUTO, obj_name,var_name);

		def_name = "CH.LINK_PIO.ACTIVE.LOAD_REQ";			// OFF ON
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LINK_PIO_ACTIVE_LOAD_REQ, obj_name,var_name);

		def_name = "CH.LINK_PIO.ACTIVE.UNLOAD_REQ";			// OFF ON
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LINK_PIO_ACTIVE_UNLOAD_REQ, obj_name,var_name);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__OHT_CTRL::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT();
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]", mode);
		xLOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__OHT_CTRL::__CALL__MONITORING(id,p_variable,p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;
	}

	return 1;
}
