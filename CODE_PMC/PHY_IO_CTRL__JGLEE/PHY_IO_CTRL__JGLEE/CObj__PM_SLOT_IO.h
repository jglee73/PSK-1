#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__PM_SLOT_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	int iActive__SIM_MODE;
	//

	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL   sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL   sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL   sCH__OBJ_TIME_COUNT;

	CX__VAR_ANALOG_CTRL   aCH__CFG_OPEN_TIMEOUT;
	CX__VAR_ANALOG_CTRL   aCH__CFG_CLOSE_TIMEOUT;
	//

	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL   sEXT_CH__MON_DOOR_STATE;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_DOOR_CLOSE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_DOOR_OPEN;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_DOOR_CLOSE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_DOOR_OPEN;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__DOOR_OPEN;
	int Call__DOOR_OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__DOOR_CLOSE;
	int Call__DOOR_CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__PM_SLOT_IO();
	~CObj__PM_SLOT_IO();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
