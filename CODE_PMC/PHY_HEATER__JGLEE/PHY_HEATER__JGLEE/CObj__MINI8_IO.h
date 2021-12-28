#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CClass__Error_Timer.h"

#include "CObj__MINI8_IO__DEF.h"


class CObj__MINI8_IO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	SCX__USER_LOG_CTRL xI_LOG_CTRL;

	int iLOOP_SIZE;
	int iActive__SIM_MODE;

	//-------------------------------------------------------------------------
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_TIMER;

	// Parameter ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_LOOP_ID;
	CX__VAR_ANALOG_CTRL  aCH__PARA_TARGET_SP;

	CX__VAR_ANALOG_CTRL  aCH__CFG_TARGET_SP__LOOP_X[CFG__LOOP_SIZE];

	// CFG : ERROR CHECK ...
	CX__VAR_STRING_CTRL  sCH__CFG_NAME__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_USE__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG_MIN_VALUE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_MAX_VALUE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_DEC_VALUE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_UNIT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_PV_OFFSET__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG_STABLE_CHECK_TIMEOUT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_DELAY_CHECK_TIMEOUT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_TOLERANCE_TIMEOUT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_HARD_TOLERANCE_TIMEOUT__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG_SOFT_TOLERANCE_THRESHOLD__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_HARD_TOLERANCE_THRESHOLD__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_ANALOG_CTRL  aCH__CFG_ERROR_CHECK_TIMEOUT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_TEMP_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_OP_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_MAX_DEVIATION__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_DI_OVER_TEMP__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_DI_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];

	// CFG : Ramping ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMPING_RATE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMPING_RANGE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMPING_STABLE_TIME;

	CX__VAR_STRING_CTRL  sCH__CUR_RAMPING_RATE;
	CX__VAR_STRING_CTRL  sCH__CUR_RAMPING_RANGE;
	CX__VAR_STRING_CTRL  sCH__CUR_RAMPING_STABLE_TIME_COUNT;

	//
	CX__VAR_ANALOG_CTRL  aCH__CFG_HEATING_TIMEOUT;
	CX__VAR_STRING_CTRL  sCH__CUR_HEATING_TIMEOUT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_TEMPERATURE_DIFF_MAX;

	CX__VAR_DIGITAL_CTRL dCH__CFG_SP_RANGE_INTERLOCK_USE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_SP_RANGE_INTERLOCK_VALUE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_ALARM_RESET_ON_TIME;
	CX__VAR_STRING_CTRL  sCH__CUR_ALARM_RESET_ON_TIME_COUNT;

	CX__VAR_DIGITAL_CTRL dCH__CFG_AI_ALARM_MC_OFF__LOOP_ALL;
	CX__VAR_DIGITAL_CTRL dCH__CFG_DI_ALARM_MC_OFF__LOOP_ALL;

	// SET : IO.Output ...
	CX__VAR_ANALOG_CTRL  aCH__MON_IO_SET_SP__LOOP_X[CFG__LOOP_SIZE];

	// MON : IO.Input ...
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_PV__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_WORKING_SP__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_WORKING_OP__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_PV_OFFSET__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_OP_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_FORWARD_OP__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_ALARM_STATUS_BIT_X[CFG__ALARM_BIT_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_ALARM_MESSAGE_BIT_X[CFG__ALARM_BIT_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_IO_GET_ALARM_STATUS_ACTIVE;

	// CFG : INITIAL ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_INITIAL_MODE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_INITIAL_HEATING_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_INITIAL_TARTGET_TEMP__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_DIGITAL_CTRL dCH__CFG_AI_ALARM_MC_OFF__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_DI_ALARM_MC_OFF__LOOP_X[CFG__LOOP_SIZE];

	// MON.ACTIVE ...
	CX__VAR_STRING_CTRL  sCH__MON_HEATING_ACTIVE;

	// MON.STABLE ...
	CX__VAR_DIGITAL_CTRL dCH__MON_ERROR_CHECK_ACTIVE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__MON_ABORT_ACTIVE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dCH__MON_STABLE_ACTIVE__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_STRING_CTRL  sCH__MON_STABLE_CHECK_TIME__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_DELAY_CHECK_TIME__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_MIN__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_MAX__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_WARNING_CHECK_TIME__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_MIN__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_MAX__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_ABORT_CHECK_TIME__LOOP_X[CFG__LOOP_SIZE];

	//
	CX__VAR_STRING_CTRL  sCH__MON_TEMP_HIGH_LIMIT_CHECK_TIME__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_OP_HIGH_LIMIT_CHECK_TIME__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_MAX_DEVIATION_CHECK_TIME_LOOP_X[CFG__LOOP_SIZE];

	//
	CX__VAR_STRING_CTRL  sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_TEMP_HIGH_LIMIT_ACTIVE__LOOP_ALL;

	CX__VAR_STRING_CTRL  sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_OP_HIGH_LIMIT_ACTIVE__LOOP_ALL;

	CX__VAR_STRING_CTRL  sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_MAX_DEVIATION_ACTIVE__LOOP_ALL;

	//
	CX__VAR_STRING_CTRL  sCH__MON_DI_OVER_TEMP_STATE_LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_DI_OVER_TEMP_STATE_LOOP_ALL;

	CX__VAR_STRING_CTRL  sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_STRING_CTRL  sCH__MON_DI_HIGH_LIMIT_STATE_LOOP_ALL;

	//
	CX__VAR_STRING_CTRL  sCH__MON_DO_HEATER_POWER__LOOP_X[CFG__LOOP_SIZE];
	//

	//-------------------------------------------------------------------------
	bool bActive__CTRL_ACTIVE__LOOP_X[CFG__LOOP_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__AO_TEMPERATURE_SET__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_TEMPERATURE_READ__LOOP_X[CFG__LOOP_SIZE];

	//
	bool bActive__AI_TEMPERATURE_SET__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_TEMPERATURE_SET__LOOP_X[CFG__LOOP_SIZE];
	
	bool bActive__AI_TEMPERATURE_POWER__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_TEMPERATURE_POWER__LOOP_X[CFG__LOOP_SIZE];

	//
	bool bActive__AI_PV_OFFSET__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_PV_OFFSET__LOOP_X[CFG__LOOP_SIZE];
	
	bool bActive__AI_OP_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_OP_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];
	
	bool bActive__AI_OP_FORWARD__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__AI_OP_FORWARD__LOOP_X[CFG__LOOP_SIZE];

	//
	bool bActive__DO_HEATER_POWER__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_HEATER_POWER__LOOP_X[CFG__LOOP_SIZE];

	bool bActive__DI_OVER_TEMP__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_OVER_TEMP__LOOP_X[CFG__LOOP_SIZE];

	bool bActive__DI_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_HIGH_LIMIT__LOOP_X[CFG__LOOP_SIZE];

	//
	bool bActive__SI_ALARM_STATE_HEXA;
	CX__VAR_STRING_CTRL  sEXT_CH__SI_ALARM_STATE_HEXA;

	bool bActive__SO_ALARM_RESET_HEXA;
	CX__VAR_STRING_CTRL  sEXT_CH__SO_ALARM_RESET_HEXA;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__ALARM_RESET;
	int Call__ALARM_RESET(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__ALARM_RESET(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__HEATING;
	int Call__HEATING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__HEATING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int htr_type);
	int _Fnc__HEATING(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm, const int htr_type);

	// ...
	CString sMODE__POWER_OFF;
	int Call__POWER_OFF(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int Mon__STATE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Fnc__MC_OFF_BY_AI(const int index);
	int Fnc__MC_OFF_BY_DI(const int index);
	int Fnc__ALL_MC_OFF_BY_AI();
	int Fnc__ALL_MC_OFF_BY_DI();
	void Fnc__AO_TEMPERATURE_SET(const int index);

	int Mon__ERROR_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	CString Get__ERROR_MSG(const CString& loop_name, CClass__Error_Timer* p_error);
	//


public:
	CObj__MINI8_IO();
	~CObj__MINI8_IO();

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
