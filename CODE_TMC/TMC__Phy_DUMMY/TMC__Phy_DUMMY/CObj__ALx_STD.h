#pragma once

#include "Interface_Code.h"


class CObj__ALx_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY


	//-------------------------------------------------------------------------
	// INIT ----- 
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ALIGN -----
	CString sMODE__ALIGN;
	int  Call__ALIGN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


public:
	CObj__ALx_STD();
	~CObj__ALx_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);	

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);
};
