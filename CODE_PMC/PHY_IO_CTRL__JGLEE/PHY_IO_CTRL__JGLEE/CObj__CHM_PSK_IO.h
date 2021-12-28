#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


class CObj__CHM_PSK_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;
	int iSIM_MODE;


	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL   sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL   sCH__OBJ_STATUS;


	//-------------------------------------------------------------------------
	// OBJ : DB_INF
	CX__VAR_STRING_CTRL   sEXT_CH__CHM_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL   sEXT_CH__CHM_PRESSURE_mTORR;

	CX__VAR_STRING_CTRL   sEXT_CH__CHM_VAC_SNS;
	CX__VAR_STRING_CTRL   sEXT_CH__CHM_ATM_SNS;

	CX__VAR_STRING_CTRL   sEXT_CH__PMP_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL   sEXT_CH__PMP_PRESSURE_STATE;
	CX__VAR_STRING_CTRL   sEXT_CH__PMP_VAC_SNS;

	// OBJ : DB_SYS
	CX__VAR_DIGITAL_CTRL  dEXT_CH__CFG_INTERLOCK_USE_MODE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__CFG_INTERLOCK_USE__CHM_MANOMETER_ISO;

	CX__VAR_STRING_CTRL   sEXT_CH__SIM_PRESSURE_TORR;

	CX__VAR_STRING_CTRL   sEXT_CH__SYSTEM_SETUP_REQ;

	CX__VAR_ANALOG_CTRL   aEXT_CH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR;
	CX__VAR_ANALOG_CTRL   aEXT_CH__CFG_PROCESS_MANOMETER_ISO_PRESSURE_mTORR;

	// LINK : IO Channel 
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_VAC_SNS;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__DI_ATM_SNS;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__DO_MANOMETER_ISO_VLV;
	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_MANOMETER_TORR;
	CX__VAR_ANALOG_CTRL   aEXT_CH__AI_FORELINE_PRESSURE_TORR;

	/*
	// LINK : State Channel 
	CX__VAR_STRING_CTRL   sEXT_CH__PROC_STATE;

	CX__VAR_STRING_CTRL   sEXT_CH__RF_ON_STATE;
	CX__VAR_ANALOG_CTRL   aEXT_CH__PLASMA_RF_POWER;
	CX__VAR_ANALOG_CTRL   aEXT_CH__BIAS_RF_POWER;
	*/
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

	// ...
	int Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//

public:
	CObj__CHM_PSK_IO();
	~CObj__CHM_PSK_IO();

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
