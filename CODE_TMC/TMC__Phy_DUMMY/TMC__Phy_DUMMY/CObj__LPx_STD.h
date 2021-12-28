#pragma once

#include "Interface_Code.h"
#include "CCommon_System.h"


class CObj__LPx_STD : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL dCH__DOOR_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__FOUP_EXIST_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__FOUP_CLAMP_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__FOUP_POS_STATUS;
	CX__VAR_STRING_CTRL  sCH__TRANSFER_PIO_STATUS;
	CX__VAR_STRING_CTRL  sCH__FOUP_RELOAD_FLAG;
	CX__VAR_STRING_CTRL  sCH__FA_MODE;

	CX__VAR_STRING_CTRL  sCH__SLOT_MAP_RESULT[CFG_LPx__SLOT_SIZE];


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY


	//-------------------------------------------------------------------------
	// INIT ----- 
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// DOOR OPEN -----
	CString sMODE__DOOR_OPEN;
	int  Call__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// CHECK DOOR OPEN -----
	CString sMODE__CHECK_DOOR_OPEN;
	int  Call__CHECK_DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// LOAD -----
	CString sMODE__LOAD;
	int  Call__LOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// UNLOAD -----
	CString sMODE__UNLOAD;
	int  Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// PREPLOAD -----
	CString sMODE__PREPLOAD;
	int  Call__PREPLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// RLSUNLOAD ----- 
	CString sMODE__RLSUNLOAD;
	int  Call__RLSUNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// MAP -----
	CString sMODE__MAP;
	int  Call__MAP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// CLAMP -----
	CString sMODE__CLAMP;
	int  Call__CLAMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// UNCLAMP -----
	CString sMODE__UNCLAMP;
	int  Call__UNCLAMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);


public:
	CObj__LPx_STD();
	~CObj__LPx_STD();

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
