#include "StdAfx.h"
#include "CObj__VIS_STD.h"


//-------------------------------------------------------------------------
CObj__VIS_STD::CObj__VIS_STD()
{

}
CObj__VIS_STD::~CObj__VIS_STD()
{

}

//-------------------------------------------------------------------------
int CObj__VIS_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,           "INIT");

		ADD__CTRL_VAR(sMODE__RUN_START,      "RUN_START");
		ADD__CTRL_VAR(sMODE__PRO_START,      "PRO_START");
		ADD__CTRL_VAR(sMODE__PRO_STOP,       "PRO_STOP");
		ADD__CTRL_VAR(sMODE__DOWNLOAD,       "DOWNLOAD");
		ADD__CTRL_VAR(sMODE__PRO_READY,      "PRO_READY");
		
		ADD__CTRL_VAR(sMODE__PLACE_READY,    "PLACE_READY");
		ADD__CTRL_VAR(sMODE__PLACE_COMPLETE, "PLACE_COMPLETE");
		ADD__CTRL_VAR(sMODE__PICK_READY,     "PICK_READY");
		ADD__CTRL_VAR(sMODE__PICK_COMPLETE,  "PICK_COMPLETE");
		ADD__CTRL_VAR(sMODE__EXCHANGE_READY, "EXCHANGE_READY");
		
		ADD__CTRL_VAR(sMODE__GET_RESULT,     "GET_RESULT");
		ADD__CTRL_VAR(sMODE__GET_FILE,       "GET_FILE");
	}
	return 1;
}
int CObj__VIS_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__VIS_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CString str_name;

	// ...
	str_name = "OTR.IN.sVIS1.SLOT.NO";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__SLOT_NO,str_name);
	
	str_name = "OTR.IN.sVIS1.LOTID";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__LOTID,str_name);

	str_name = "OTR.IN.sVIS1.PORTID";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__PORTID,str_name);

	str_name = "OTR.IN.sVIS1.PMID";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__PMID,str_name);

	str_name = "OTR.IN.sVIS1.SLOTID";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__SLOTID,str_name);

	str_name = "OTR.IN.sVIS1.RECIPE";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__RECIPE,str_name);

	str_name = "OTR.IN.sVIS1.RECIPE.UPLOAD";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__RECIPE_UPLOAD,str_name);
	

	str_name = "OTR.OUT.sVIS1.JUDGMENT";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__JUDGEMENT,str_name);

	str_name = "OTR.OUT.sVIS1.RECIPE.LIST";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__RECIPE_LIST,str_name);

	return 1;
}
int CObj__VIS_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__VIS_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__VIS_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RUN_START)			flag = Call__RUN_START(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRO_START)			flag = Call__PRO_START(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRO_STOP)				flag = Call__PRO_STOP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__DOWNLOAD)				flag = Call__DOWNLOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PRO_READY)			flag = Call__PRO_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_READY)			flag = Call__PLACE_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PLACE_COMPLETE)		flag = Call__PLACE_COMPLETE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_READY)			flag = Call__PICK_READY(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PICK_COMPLETE)		flag = Call__PICK_COMPLETE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__GET_RESULT)			flag = Call__GET_RESULT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__GET_FILE)				flag = Call__GET_FILE(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__EXCHANGE_READY)		flag = Call__EXCHANGE_READY(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{

	}
	else
	{

	}

	return flag;
}
int CObj__VIS_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
