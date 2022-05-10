#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_Def.h"

#include "CClass__Error_Timer.h"

#include "CObj__LFC_IO__DEF.h"
#include "CObj__LFC_IO__ALID.h"


class CObj__LFC_IO : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xLOG_CTRL;

	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// PARA ...
	CX__VAR_ANALOG_CTRL	 aCH__PARA_SET_VALUE;
	CX__VAR_ANALOG_CTRL	 aCH__PARA_RAMP_SEC;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_LINK_DATA__TYPE;
	CX__VAR_STRING_CTRL  sCH__INFO_LINK_DATA__MAX_FLOW;
	CX__VAR_STRING_CTRL  sCH__INFO_LINK_DATA__MAX_DEFAULT;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_LFC_STATE;

	//
	CX__VAR_ANALOG_CTRL  aCH__MON_LFC_SET_FLOW;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_SET_PERCENT;

	CX__VAR_ANALOG_CTRL  aCH__MON_LFC_READ_FLOW;	
	CX__VAR_STRING_CTRL  sCH__MON_LFC_FLOW_PERCENT;

	//
	CX__VAR_STRING_CTRL  sCH__MON_LFC_EXCEPTION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_EXCEPTION_INFO;

	CX__VAR_STRING_CTRL  sCH__MON_LFC_READ_VALVE_VOLTAGE;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_VALVE_VOLTAGE_PERCENT;

	CX__VAR_STRING_CTRL  sCH__MON_LFC_READ_INLET_PRESSURE;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_INLET_PRESSURE_PERCENT;

	CX__VAR_STRING_CTRL  sCH__MON_LFC_READ_TEMPERATURE;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_TEMPERATURE_PERCENT;

	// LFC.FLOW
	CX__VAR_DIGITAL_CTRL dCH__MON_LFC_PROC_ACTIVE;

	CX__VAR_DIGITAL_CTRL dCH__MON_ERROR_CHECK_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_LFC_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_LFC_STABLE_ACTIVE;

	CX__VAR_STRING_CTRL  sCH__MON_LFC_STABLE_MIN;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_STABLE_MAX;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_STABLE_DELAY_TIME;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_STABLE_CHECK_TIME;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_WARNING_CHECK_TIME;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_ABORT_MIN;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_ABORT_MAX;
	CX__VAR_STRING_CTRL  sCH__MON_LFC_ABORT_CHECK_TIME;

	// PT
	CX__VAR_DIGITAL_CTRL dCH__MON_ERROR_CHECK_ACTIVE_PT;
	CX__VAR_DIGITAL_CTRL dCH__MON_ABORT_ACTIVE_PT;
	CX__VAR_DIGITAL_CTRL dCH__MON_STABLE_ACTIVE_PT;

	CX__VAR_STRING_CTRL  sCH__MON_STABLE_CHECK_TIME_PT;
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_MIN_PT;
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_MAX_PT;
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_CHECK_TIME_PT;
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_MIN_PT;
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_MAX_PT;
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_CHECK_TIME_PT;

	// CFG ...
	CX__VAR_STRING_CTRL	 sCH__CFG_GAS_NAME;
	CX__VAR_DIGITAL_CTRL dCH__CFG_LFC_USE;

	CX__VAR_ANALOG_CTRL	 aCH__CFG_LFC_MIN_VALUE;
	CX__VAR_ANALOG_CTRL	 aCH__CFG_LFC_MAX_VALUE;
	CX__VAR_ANALOG_CTRL	 aCH__CFG_LFC_DEC_VALUE;

	CX__VAR_ANALOG_CTRL	 aCH__CFG_STABLE_DELAY_TIME;
	CX__VAR_ANALOG_CTRL	 aCH__CFG_STABLE_CHECK_TIME;

	CX__VAR_ANALOG_CTRL  aCH__CFG_TOL_WARN_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_TOL_ABORT_TIMEOUT;
	CX__VAR_ANALOG_CTRL	 aCH__CFG_WARN_BAND;
	CX__VAR_ANALOG_CTRL	 aCH__CFG_ABORT_BAND;
	CX__VAR_ANALOG_CTRL  aCH__CFG_IDLE_WARN_BAND;
	CX__VAR_ANALOG_CTRL  aCH__CFG_IDLE_ABORT_BAND;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LFC_Zero_Setpoint_Tolerance_Compensation;

	CX__VAR_DIGITAL_CTRL dCH__CFG_ABORT_TOLE_VALVE_CLOSE;

	// CFG - RANGE ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_RANGE_LFC_UNIT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_RANGE_MAX_PRESSURE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RANGE_DEC_PRESSURE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_RANGE_MAX_TEMPERATURE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RANGE_DEC_TEMPERATURE;

	// 3WAY.VLV ...
	CX__VAR_STRING_CTRL  sCH__REQ_3WAY_VLV;
	CX__VAR_STRING_CTRL  sCH__MON_3WAY_VLV;
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// DB_SYS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_SYSTEM;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_CHAMBER;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_GAS_BOX;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_GAS_BOX;

	// LINK.DATA ...
	int iLINK_DATA__TYPE;
	int iLINK_DATA__MAX_FLOW;
	int iLINK_DATA__MAX_DEFAULT;

	// LINK IO ...
	CX__VAR_STRING_CTRL   sEXT_CH__IO_LFC_SET;
	CX__VAR_STRING_CTRL   sEXT_CH__IO_LFC_READ;

	bool bActive__LFC_STATE;
	CX__VAR_STRING_CTRL   sEXT_CH__IO_LFC_STATE;

	bool bActive__LFC_VALVE_VOLTAGE;
	CX__VAR_STRING_CTRL   sEXT_CH__IO_LFC_VALVE_VOLTAGE;

	bool bActive__LFC_PRESSURE;
	CX__VAR_STRING_CTRL   sEXT_CH__IO_LFC_PRESSURE;

	bool bActive__LFC_TEMPERATURE;
	CX__VAR_STRING_CTRL   sEXT_CH__IO_LFC_TEMPERATURE;

	//
	bool bActive__VLV_PURGE;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__IO_VLV_PURGE;

	bool bActive__VLV_IN;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__IO_VLV_IN;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__IO_VLV_OUT;

	//
	bool bActive__3WAY_VLV;

	CX__VAR_DIGITAL_CTRL doEXT_CH__3WAY_VLV_FINAL;
	CX__VAR_DIGITAL_CTRL doEXT_CH__3WAY_VLV_DUMP;

	CString sDATA__3WAY_VLV_IDLE_STATE;
	//


	//------------------------------------------------------------------------------
	// CONTROL MODE ...

	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__OPEN;
	int  Call__OPEN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CLOSE;
	int  Call__CLOSE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__DUMP;
	int  Call__DUMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CONTROL;
	int  Call__CONTROL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Fnc__CONTROL(const double set_flow, const int open_mode, const double cfg_max, const bool active__purge_vlv = false);

	CString sMODE__RAMP_CTRL;
	int  Call__RAMP_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Fnc__RAMP_CTRL(CII_OBJECT__VARIABLE* p_variable, const double set_flow, const int open_mode, const double cfg_max);

	CString sMODE__SET_FLOW;
	int  Call__SET_FLOW(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Fnc__SET_FLOW(const double set_flow);

	CString sMODE__PURGE;
	int  Call__PURGE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	int  Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	int  Mon__ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);
	CString Get__ERROR_MSG(CClass__Error_Timer* p_error);
	//


public:
	CObj__LFC_IO();
	~CObj__LFC_IO();

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
