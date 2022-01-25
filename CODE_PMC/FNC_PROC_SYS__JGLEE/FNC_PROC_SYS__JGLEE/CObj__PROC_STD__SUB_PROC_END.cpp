#include "StdAfx.h"
#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Sub__PROC_END(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

	log_msg = "Process End - Start ...";
	sCH__OBJ_MSG->Set__DATA(log_msg);

	if(dEXT_CH__OBJ_CTRL->Check__DATA("ABORT") > 0)
	{
		dEXT_CH__OBJ_CTRL->Set__DATA("ABORTED");
	}

	// Chamber.Pumping ...
	{

	}
	return 1;
}
