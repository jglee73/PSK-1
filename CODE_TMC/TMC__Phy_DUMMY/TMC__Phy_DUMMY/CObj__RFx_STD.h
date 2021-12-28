#pragma once

#include "Interface_Code.h"
#include "CCommon_System.h"


class CObj__RFx_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL  sCH__CID_STRING;
	CX__VAR_STRING_CTRL  sCH__LP_FA_MODE;
	CX__VAR_STRING_CTRL  sCH__LP_FA_SERVICE_MODE;

	
	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY


	//-------------------------------------------------------------------------
	// INIT ----- 
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// CID_READ -----
	CString sMODE__CID_READ;
	int  Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


public:
	CObj__RFx_STD();
	~CObj__RFx_STD();

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
