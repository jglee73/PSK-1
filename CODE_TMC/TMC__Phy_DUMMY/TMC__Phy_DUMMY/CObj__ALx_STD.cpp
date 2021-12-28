#include "StdAfx.h"
#include "CObj__ALx_STD.h"


//-------------------------------------------------------------------------
CObj__ALx_STD::CObj__ALx_STD()
{

}
CObj__ALx_STD::~CObj__ALx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,  "INIT");
		ADD__CTRL_VAR(sMODE__ALIGN, "ALGN");
	}
	return 1;
}
int CObj__ALx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}

int CObj__ALx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;
	
	return 1;
}
int CObj__ALx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__ALx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)			flag = Call__INIT(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ALIGN)		flag = Call__ALIGN(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{

	}
	else
	{

	}

	return flag;
}
int CObj__ALx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
