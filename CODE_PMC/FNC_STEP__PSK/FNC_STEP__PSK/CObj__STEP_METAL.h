#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__STEP_METAL__ALID.h"
#include "CObj__STEP_METAL__DEF.h"


class CObj__STEP_METAL : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xLOG_CTRL;
	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;
	CX__VAR_STRING_CTRL  sCH__OBJ_SUB_MSG;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_STEP_CUR_NUM;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_STEP_EXCEPTION_ACT;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_STEP_ALARM_TEST_ACTIVE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_STABLE_MIN_SEC;
	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_OBJECT_OVER_TIME_ERRPR_REF_SEC;
	
	CX__VAR_ANALOG_CTRL  aCH__CFG_CHM_PRESSURE_HIGH_LIMIT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_DELAY_RF_OFF;
	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_DELAY_MFC_CLOSE;

	//
	CX__VAR_DIGITAL_CTRL dCH__CFG_STEP_READY_HEATER_MODE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_READY_CHECK_TIME_MIN;
	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_READY_CHECK_TIME_MAX;

	CX__VAR_DIGITAL_CTRL dCH__CFG_STEP_CTRL_HEATER_MODE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_STEP_CTRL_ERROR_CONTROL;

	// RCP ...
	CX__VAR_STRING_CTRL  sCH__RCP_STEP_MESSAGE;		
	CX__VAR_DIGITAL_CTRL dCH__RCP_STEP_MODE;	
	CX__VAR_ANALOG_CTRL	 aCH__RCP_STEP_TIME;	

	CX__VAR_STRING_CTRL  sCH__RCP_EPD_ALGORITHM_ID;
	CX__VAR_STRING_CTRL  sCH__RCP_EPD_ALGORITHM_LIST;

	CX__VAR_DIGITAL_CTRL dCH__RCP_APC_MODE;		
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_PRESSURE_mTORR;		
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_POSITION;		
	CX__VAR_STRING_CTRL  sCH__RCP_APC_LEARNED_POS;
	CX__VAR_STRING_CTRL  sCH__RCP_APC_HOLD_DELAY;
	CX__VAR_STRING_CTRL  sCH__RCP_APC_TOL_WARNING;
	CX__VAR_STRING_CTRL  sCH__RCP_APC_TOL_ALARM;

	CX__VAR_STRING_CTRL  sCH__RCP_GAS_FLOW_X[_CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_GAS_RAMP_SEC_X[_CFG__MFC_SIZE];

	CX__VAR_STRING_CTRL  sCH__RCP_RF_SOURCE_POWER;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_SOURCE_TOL_WARNING;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_SOURCE_TOL_ALARM;

	CX__VAR_STRING_CTRL  sCH__RCP_RF_BIAS_WAIT_TIME;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_BIAS_POWER;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_BIAS_TOL_WARNING;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_BIAS_TOL_ALARM;

	//
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_SOURCE_SHUNT;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_SOURCE_SERIES;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_SOURCE_CAPACITY;

	CX__VAR_STRING_CTRL  sCH__RCP_MAT_SOURCE_LEARNED_SHUNT;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_SOURCE_LEARNED_SERIES;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_SOURCE_LEARNED_CAPACITY;

	//
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_BIAS_SHUNT;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_BIAS_SERIES;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_BIAS_CAPACITY;

	CX__VAR_STRING_CTRL  sCH__RCP_MAT_BIAS_LEARNED_SHUNT;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_BIAS_LEARNED_SERIES;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_BIAS_LEARNED_CAPACITY;

	//
	CX__VAR_DIGITAL_CTRL dCH__RCP_ESC_CTRL_MODE;
	CX__VAR_STRING_CTRL  sCH__RCP_DPC_CENTER_PRESSURE;
	CX__VAR_STRING_CTRL  sCH__RCP_DPC_CENTER_ZONE_FLOW_MAX_THRESHOLD;
	CX__VAR_STRING_CTRL  sCH__RCP_DPC_CENTER_ZONE_FLOW_MIN_THRESHOLD;

	CX__VAR_STRING_CTRL  sCH__RCP_ESC_CHUCK_TEMP_X[_CFG__CHUCK_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_ESC_CHUCK_OFFSET_X[_CFG__CHUCK_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_ESC_CHUCK_WARNING_X[_CFG__CHUCK_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_ESC_CHUCK_ALARM_X[_CFG__CHUCK_SIZE];

	CX__VAR_STRING_CTRL  sCH__RCP_WALL_MAIN_TEMP;
	CX__VAR_STRING_CTRL  sCH__RCP_WALL_MAIN_OFFSET;
	CX__VAR_STRING_CTRL  sCH__RCP_WALL_MAIN_WARNING;
	CX__VAR_STRING_CTRL  sCH__RCP_WALL_MAIN_ALARM;

	CX__VAR_DIGITAL_CTRL dCH__RCP_LIFT_PIN_MODE;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// DB INF ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__SLOT01_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__CUR_LOTID;

	// DB_SYS ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_SYSTEM_PROCESS_ACTIVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_SYSTEM;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_SYSTEM;

	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_HEAVY_ACTIVE_CHAMBER;
	CX__VAR_DIGITAL_CTRL dEXT_CH__MON_INTERLOCK_LIGHT_ACTIVE_CHAMBER;

	// OBJ APC ...
	int APC_OBJ__Start_MODE(const CString& obj_mode,const CString& para_data, const double para_hold_sec,const double para_hold_pos);
	int APC_OBJ__Start_OPEN();	
	int APC_OBJ__Check_ERROR();
	int APC_OBJ__Check_ABORTED();
	int APC_OBJ__Check_STABLE();

	bool bActive__OBJ_CTRL__APC;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__APC;

	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_PRESSURE;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_POSITION;
	CX__VAR_ANALOG_CTRL	 aEXT_CH__APC_OBJ__PARA_HOLD_SEC;

	CX__VAR_STRING_CTRL  sEXT_CH__APC_OBJ__MON_PRESSURE_TORR;

	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__MON_PROC_PRESSURE_STABLE_ACTIVE;

	CX__VAR_ANALOG_CTRL  aEXT_CH__APC_OBJ__CFG_PROC_PRESSURE_WARNING_BAND;
	CX__VAR_ANALOG_CTRL  aEXT_CH__APC_OBJ__CFG_PROC_PRESSURE_ABORT_BAND;

	// OBJ PT_X ...
	int PT_OBJ__Check_ERROR();

	int iDATA__PT_SIZE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__PT_X__MON_ABORT_ACTIVE[_CFG__PT_SIZE];

	// OBJ MFC_X ...
	int MFC_OBJ__Start_CONTROL(const int mfc_index, const CString& para_flow,const CString& para_ramp_sec);
	int MFC_OBJ__Start_CLOSE(const int mfc_index);
	int MFC_OBJ__Check_ERROR();
	int MFC_OBJ__Check_ABORTED();

	int iDATA__MFC_SIZE;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MFC_X[_CFG__MFC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__MFC_X__PARA_SET_FLOW[_CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__MFC_X__PARA_RAMP_SEC[_CFG__MFC_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__MFC_X__MON_MFC_ABORT_ACTIVE[_CFG__MFC_SIZE];

	// OBJ RF_SOURCE ...
	int RF_SRC_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data, const CString& para_warning,const CString& para_alarm);
	int RF_SRC_OBJ__Start_OFF();
	int RF_SRC_OBJ__Check_ERROR();
	int RF_SRC_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__RF_SRC;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_SRC;

	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_SRC__PARA_SET_POWER;
	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_SRC__PARA_HOLD_TIME;

	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_SRC__CFG_PROC_POWER_WARNING_BAND;
	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_SRC__CFG_PROC_POWER_ABORT_BAND;

	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_SRC__MON_IDLE_POWER_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_SRC__MON_PROC_POWER_ABORT_ACTIVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_SRC__MON_REFLECT_HIGH_LIMIT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_SRC__MON_REFLECT_MAX_COEFFICIENT_ACTIVE;

	// OBJ RF_BIAS ...
	int RF_BIAS_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data, const CString& para_warning,const CString& para_alarm);
	int RF_BIAS_OBJ__Start_OFF();
	int RF_BIAS_OBJ__Check_ERROR();
	int RF_BIAS_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__RF_BIAS;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_BIAS;

	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_BIAS__PARA_SET_POWER;
	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_BIAS__PARA_HOLD_TIME;

	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_BIAS__CFG_PROC_POWER_WARNING_BAND;
	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_BIAS__CFG_PROC_POWER_ABORT_BAND;

	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_BIAS__MON_IDLE_POWER_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_BIAS__MON_PROC_POWER_ABORT_ACTIVE;

	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_BIAS__MON_REFLECT_HIGH_LIMIT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_BIAS__MON_REFLECT_MAX_COEFFICIENT_ACTIVE;

	// OBJ MATCHER ...
	int MAT_OBJ__Start_MODE(const CString& obj_mode);
	int MAT_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__MAT;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MAT;

	CX__VAR_ANALOG_CTRL  aEXT_CH__MAT__PARA_LOAD_POS_CH1;
	CX__VAR_ANALOG_CTRL  aEXT_CH__MAT__PARA_LOAD_POS_CH2;

	CX__VAR_ANALOG_CTRL  aEXT_CH__MAT__PARA_TUNE_POS_CH1;
	CX__VAR_ANALOG_CTRL  aEXT_CH__MAT__PARA_TUNE_POS_CH2;

	CX__VAR_ANALOG_CTRL  aEXT_CH__MAT__PARA_CAP_POS_CH1;
	CX__VAR_ANALOG_CTRL  aEXT_CH__MAT__PARA_CAP_POS_CH2;

	// OBJ ESC ...
	int ESC_OBJ__Init_DATA();
	int ESC_OBJ__Start_MODE(const CString& obj_mode);
	int ESC_OBJ__Start_HE_CLOSE();
	int ESC_OBJ__Check_ERROR();
	int ESC_OBJ__Check_ABORTED();
	int ESC_OBJ__Wait();
	int ESC_OBJ__Is_BUSY();

	bool bActive__OBJ_CTRL__ESC;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__ESC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__ESC__MON_FAULT_ACTIVE;

	CX__VAR_STRING_CTRL  sEXT_CH__ESC__RCP_He_CENTER_PRESSURE_SETPOINT_TORR;
	CX__VAR_STRING_CTRL  sEXT_CH__ESC__RCP_He_CENTER_FLOW_MIN_THRESHOLD;
	CX__VAR_STRING_CTRL  sEXT_CH__ESC__RCP_He_CENTER_FLOW_MAX_THRESHOLD;

	// OBJ LIFT_PIN ...
	int LIFT_PIN_OBJ__Start_MODE(const CString& obj_mode);
	int LIFT_PIN_OBJ__Check_ABORTED();
	int LIFT_PIN_OBJ__Wait();
	int LIFT_PIN_OBJ__Is_BUSY();

	bool bActive__OBJ_CTRL__LIFT_PIN;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LIFT_PIN;

	// OBJ.HTR_CHUCK ...
	int HTR_CHUCK_OBJ__Start_MODE(const CString& obj_mode);
	int HTR_CHUCK_OBJ__Call_MODE(const CString& obj_mode);
	int HTR_CHUCK_OBJ__Init_DATA();
	int HTR_CHUCK_OBJ__Check_ABORTED();
	int HTR_CHUCK_OBJ__Is_BUSY();
	int HTR_CHUCK_OBJ__Check_STABLE_ERROR();

	bool bActive__OBJ_CTRL__HTR_CHUCK;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__HTR_CHUCK;

	CX__VAR_STRING_CTRL  sEXT_CH__HTR_CHUCK__PARA_PROC_REF_SP_X[_CFG__CHUCK_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_CHUCK__PARA_TARGET_SP_X[_CFG__CHUCK_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_CHUCK__MON_IDLE_STABLE_ACTIVE_X[_CFG__CHUCK_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_CHUCK__MON_IDLE_ABORT_ACTIVE_X[_CFG__CHUCK_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_CHUCK__MON_PROC_STABLE_ACTIVE_X[_CFG__CHUCK_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_CHUCK__MON_PROC_ABORT_ACTIVE_X[_CFG__CHUCK_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_CHUCK__CFG_PROC_SOFT_TOLERANCE_X[_CFG__CHUCK_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_CHUCK__CFG_PROC_HARD_TOLERANCE_X[_CFG__CHUCK_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_CHUCK__MON_IO_PV_X[_CFG__CHUCK_SIZE];

	// OBJ.HTR_WALL ...
	int HTR_WALL_OBJ__Start_MODE(const CString& obj_mode);
	int HTR_WALL_OBJ__Call_MODE(const CString& obj_mode);
	int HTR_WALL_OBJ__Init_DATA();
	int HTR_WALL_OBJ__Check_ABORTED();
	int HTR_WALL_OBJ__Is_BUSY();
	int HTR_WALL_OBJ__Check_STABLE_ERROR();

	bool bActive__OBJ_CTRL__HTR_WALL;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__HTR_WALL;

	CX__VAR_STRING_CTRL  sEXT_CH__HTR_WALL__PARA_PROC_REF_SP_X[_CFG__WALL_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_WALL__PARA_TARGET_SP_X[_CFG__WALL_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_WALL__MON_IDLE_STABLE_ACTIVE_X[_CFG__WALL_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_WALL__MON_IDLE_ABORT_ACTIVE_X[_CFG__WALL_SIZE];

	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_WALL__MON_PROC_STABLE_ACTIVE_X[_CFG__WALL_SIZE];
	CX__VAR_DIGITAL_CTRL dEXT_CH__HTR_WALL__MON_PROC_ABORT_ACTIVE_X[_CFG__WALL_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_WALL__CFG_PROC_SOFT_TOLERANCE_X[_CFG__WALL_SIZE];
	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_WALL__CFG_PROC_HARD_TOLERANCE_X[_CFG__WALL_SIZE];

	CX__VAR_ANALOG_CTRL  aEXT_CH__HTR_WALL__MON_IO_PV_X[_CFG__WALL_SIZE];
	//


	//-------------------------------------------------------------------------
	// OBJ.MODE ...

	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__READY;
	int Call__READY(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__START;
	int Call__START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PROC;
	int Call__PROC(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int _Fnc__PROC_LOG();

	CString sMODE__ABORT;
	int Call__ABORT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__END;
	int Call__END(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);
	int _Fnc__END();

	// ...
	double Fnc__OBJ_OVERTIME_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	int Fnc__HTR_STEP_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int _Fnc__HTR_STABLE_CONTROL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);
	int _Fnc__HTR_STABLE_CHECK(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM* p_alarm);

	int Get__STEP_CTRL();
	//

public:
	CObj__STEP_METAL();
	~CObj__STEP_METAL();

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
