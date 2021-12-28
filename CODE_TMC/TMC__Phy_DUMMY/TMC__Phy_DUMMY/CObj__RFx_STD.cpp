#include "StdAfx.h"
#include "CObj__RFx_STD.h"


//-------------------------------------------------------------------------
CObj__RFx_STD::CObj__RFx_STD()
{

}
CObj__RFx_STD::~CObj__RFx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__RFx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,     "INIT");
		ADD__CTRL_VAR(sMODE__CID_READ, "CID_READ");
	}
	return 1;
}
int CObj__RFx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__RFx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	CString str_name;
	CString dsc_item_list;

	// CID String
	str_name = "OTR.OUT.MON.sCID.STRING";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__CID_STRING,str_name);

	// FA MODE
	str_name = "OTR.IN.dLP.FA.MODE";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__LP_FA_MODE,str_name);

	// SERVICE MODE
	str_name = "OTR.IN.dLP.FA.SERVICE.MODE";
	STD__ADD_STRING(str_name);
	LINK__VAR_STRING_CTRL(sCH__LP_FA_SERVICE_MODE,str_name);

	return 1;
}
int CObj__RFx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__RFx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__RFx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CID_READ)		flag = Call__CID_READ(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{

	}
	else
	{

	}
	return flag;
}
int CObj__RFx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
