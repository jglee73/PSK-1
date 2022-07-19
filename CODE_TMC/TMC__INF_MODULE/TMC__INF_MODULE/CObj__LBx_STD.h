#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__LBx_STD : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//------------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//------------------------------------------------------------------------------
	// INTRENAL PROPERTY

	CX__VAR_DIGITAL_CTRL dCH__PARA_SLOT_ID;

	CX__VAR_ANALOG_CTRL  aCH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_PREMATERIAL_SLOT;	


	//------------------------------------------------------------------------------
	// EXTRENAL PROPERTY

	CII_EXT_OBJECT__CTRL *pLBx__OBJ_CTRL;

	CX__VAR_DIGITAL_CTRL dEXT_CH__OBJ_STATUS;

	CX__VAR_DIGITAL_CTRL dEXT_CH__PARA_SLOT_ID;

	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREHEAT_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_COOLING_TIME;
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_PREMATERIAL_SLOT;	


	//------------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__MAINT;
	int  Call__MAINT(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PUMP;
	int  Call__PUMP(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__VENT;
	int  Call__VENT(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__DOOR_OPEN;
	int  Call__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__DOOR_CLOSE;
	int  Call__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__SLOT_OPEN;
	int  Call__SLOT_OPEN(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__SLOT_CLOSE;
	int  Call__SLOT_CLOSE(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__PIN_UP;
	int  Call__PIN_UP(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__PIN_DOWN;
	int  Call__PIN_DOWN(CII_OBJECT__VARIABLE* p_variable);

	//
	CString sMODE__PREPMATER;
	int  Call__PREPMATER(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__COMPMATER;
	CString sMODE__COMPMATER_EX;
	int  Call__COMPMATER(CII_OBJECT__VARIABLE* p_variable, const int ex_mode);

	CString sMODE__IN_PROC;
	int  Call__IN_PROC(CII_OBJECT__VARIABLE* p_variable);

	CString sMODE__OUT_PROC;
	int  Call__OUT_PROC(CII_OBJECT__VARIABLE* p_variable);

	// ...
	CString sMODE__PROC_READY;
	int  Call__PROC_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PROC_START;
	int  Call__PROC_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PRE_READY;
	int Call__PRE_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PRE_START;
	int Call__PRE_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CLN_READY;
	int Call__CLN_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CLN_START;
	int Call__CLN_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MNT_READY;
	int Call__MNT_READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MNT_START;
	int Call__MNT_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

public:
	CObj__LBx_STD();
	~CObj__LBx_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
