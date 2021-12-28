#include "StdAfx.h"
#include "CObj__MANUAL_PROC.h"


//-------------------------------------------------------------------------
CObj__MANUAL_PROC::CObj__MANUAL_PROC()
{

}
CObj__MANUAL_PROC::~CObj__MANUAL_PROC()
{

}

//-------------------------------------------------------------------------
int CObj__MANUAL_PROC::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__MANUAL_PROCESS, "MANUAL_PROCESS");
		ADD__CTRL_VAR(sMODE__ABORT_DECHUCK,  "ABORT_DECHUCK");
	}
	return 1;
}
int CObj__MANUAL_PROC::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}

int CObj__MANUAL_PROC::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// ...
	{
		str_name.Format("OBJ.MSG");
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// ...
	{
		str_name = "AGING.TEST";
		STD__ADD_ANALOG(str_name,"num",0,1,9999);
		LINK__VAR_ANALOG_CTRL(aCH__AGING_TEST, str_name);

		str_name = "AGING.TRG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__AGING_TRG, str_name);

		str_name = "AGING.CUR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__AGING_CUR, str_name);

		//
		str_name = "SEL.RECIPE.NAME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SEL_RECIPE_NAME, str_name);

		str_name = "CFG.NEXT_STEP_CTRL.MODE";
		STD__ADD_DIGITAL(str_name, "DISABLE ENABLE");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_NEXT_STEP_CTRL_MODE, str_name);
	}

	return 1;
}
int CObj__MANUAL_PROC::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	/*
	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;

	// Process Recipe does not exist .....
	{
		alarm_title  = title;
		alarm_title += "Process recipe does not exist.";

		alarm_msg = "Please, check process recipe file.\n";

		l_act.RemoveAll();
		l_act.Add("ABORT");
		l_act.Add("RETRY");
	
		ADD__ALARM_EX(ALID__PROCESS_RECIPE_NOT_EXIST,alarm_title,alarm_msg,l_act);
	}
	*/
	return 1;
}

int CObj__MANUAL_PROC::__Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl)
{
	p_fnc_ctrl->Link__ERROR_FEEDBACK(&mERROR__USER_FNC);
	mERROR__USER_FNC.Set__OBJ_NAME(sObject_Name);

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MANUAL_PROC::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString str_name;
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
		xLOG_CTRL->SET__PROPERTY(file_name, 24*5, 60);
		
		xLOG_CTRL->DISABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG(log_msg);
		
		xLOG_CTRL->ENABLE__TIME_LOG();
		xLOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	{
		def_name = "OBJ__DB_SYS";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		//
		var_name = "SYSTEM.MSG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_MSG,def_data,var_name);

		var_name = "FUNCTION.MSG";		
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__FNC_MSG,def_data,var_name);
	}

	// CH LINK .....
	{
		def_name = "CH__SYSTEM_LOCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SYSTEM_LOCK, obj_name,var_name);

		def_name = "CH__RCP_NAME";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_NAME, obj_name,var_name);

		def_name = "CH__RCP_ABORT_DECHUCK";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,ch_name);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__RCP_ABORT_DECHUCK, obj_name,var_name);
	}

	// OBJ PROC .....
	{
		def_name = "OBJ__PROC";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);
		
		pOBJ_CTRL__PROC = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		//
		str_name = "NEXT_STEP_CTRL.FLAG";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__NEXT_STEP_CTRL_FLAG, obj_name,str_name);
		
		str_name = "NEXT_STEP_CTRL.REQ";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__NEXT_STEP_CTRL_REQ, obj_name,str_name);

		//
		str_name = "PARA.PROCESS.TYPE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__PARA_PROCESS_TYPE, obj_name,str_name);
	}

	/*
	// OBJ CHM .....
	{
		def_name = "OBJ__CHM";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pOBJ_CTRL__CHM = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
	}
	*/

	return 1;
}

//-------------------------------------------------------------------------
int CObj__MANUAL_PROC::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	// ...
	{
		CString log_msg;
		log_msg.Format("Start ... :  [%s]", mode);

		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	int flag = -1;

	// ...
	{
		IF__CTRL_MODE(sMODE__MANUAL_PROCESS)
		{
			sEXT_CH__PARA_PROCESS_TYPE->Set__DATA("MAINT");

			// ...
			CString var_data;

			aCH__AGING_TEST->Get__DATA(var_data);
			aCH__AGING_TEST->Set__DATA("1");
			
			sCH__AGING_TRG->Set__DATA(var_data);
			sCH__AGING_CUR->Set__DATA("");

			int trg_count = atoi(var_data);
			int cur_count = 0;

			while(1)
			{
				// ...
				{
					cur_count++;
					var_data.Format("%1d", cur_count);
					sCH__AGING_CUR->Set__DATA(var_data);
				}

				sEXT_CH__SYSTEM_MSG->Set__DATA("Manual Process Start ...");
				sEXT_CH__FNC_MSG->Set__DATA("");

				if(dCH__CFG_NEXT_STEP_CTRL_MODE->Check__DATA(STR__ENABLE) > 0)
				{
					sEXT_CH__NEXT_STEP_CTRL_FLAG->Set__DATA(STR__YES);
				}
				else
				{
					sEXT_CH__NEXT_STEP_CTRL_FLAG->Set__DATA("");
				}

				flag = Call__MANUAL_PROCESS(p_variable);

				dCH__CFG_NEXT_STEP_CTRL_MODE->Set__DATA(STR__DISABLE);
				sEXT_CH__NEXT_STEP_CTRL_FLAG->Set__DATA("");

				if(flag < 0)
				{
					break;
				}
				if(cur_count >= trg_count)
				{
					break;
				}
			}
		}
		ELSE_IF__CTRL_MODE(sMODE__ABORT_DECHUCK)
		{
			sEXT_CH__PARA_PROCESS_TYPE->Set__DATA("DECHUCK");

			flag = Call__ABORTL_DECHUCK(p_variable);
		}
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);
		
		xLOG_CTRL->WRITE__LOG(log_msg);
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}
	
	sEXT_CH__PARA_PROCESS_TYPE->Set__DATA("");
	sEXT_CH__SYSTEM_MSG->Set__DATA("");
	return flag;
}

int CObj__MANUAL_PROC::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
