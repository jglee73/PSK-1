#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__STEP_STRIP__ALID.h"
#include "CObj__STEP_STRIP__DEF.h"


class CObj__STEP_STRIP : public __IOBJ__STD_TYPE
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

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_STEP_EXCEPTION_ACT;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_STEP_ALARM_TEST_ACTIVE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_STEP_STABLE_MIN_SEC;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CHM_PRESSURE_HIGH_LIMIT;

	// RCP ...
	CX__VAR_STRING_CTRL  sCH__RCP_STEP_MESSAGE;		
	CX__VAR_DIGITAL_CTRL dCH__RCP_STEP_MODE;	
	CX__VAR_ANALOG_CTRL	 aCH__RCP_STEP_TIME;

	CX__VAR_STRING_CTRL  sCH__RCP_EPD_ALGORITHM_ID;
	CX__VAR_STRING_CTRL  sCH__RCP_EPD_ALGORITHM_LIST;

	CX__VAR_DIGITAL_CTRL dCH__RCP_APC_MODE;		
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_POSITION;		
	CX__VAR_ANALOG_CTRL  aCH__RCP_APC_PRESSURE;		
	CX__VAR_STRING_CTRL  sCH__RCP_APC_LEARNED_POS;
	CX__VAR_STRING_CTRL  sCH__RCP_APC_HOLD_DELAY;
	CX__VAR_STRING_CTRL  sCH__RCP_APC_TOL_WARNING;
	CX__VAR_STRING_CTRL  sCH__RCP_APC_TOL_ALARM;

	CX__VAR_STRING_CTRL  sCH__RCP_RF_TOP_POWER;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_TOP_TOL_WARNING;
	CX__VAR_STRING_CTRL  sCH__RCP_RF_TOP_TOL_ALARM;

	CX__VAR_STRING_CTRL  sCH__RCP_MAT_TOP_SHUNT;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_TOP_SERIES;
	CX__VAR_STRING_CTRL  sCH__RCP_MAT_TOP_CAPACITY;

	CX__VAR_STRING_CTRL  sCH__RCP_GAS_FLOW_X[_CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_GAS_RAMP_SEC_X[_CFG__MFC_SIZE];

	CX__VAR_STRING_CTRL  sCH__RCP_VAPOR_TEMPERATURE;
	CX__VAR_DIGITAL_CTRL dCH__RCP_VAPOR_VALVE;
	CX__VAR_STRING_CTRL  sCH__RCP_VAPOR_FLOW;

	CX__VAR_STRING_CTRL  sCH__RCP_CHUCK_TEMP_X[_CFG__CHUCK_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_CHUCK_OFFSET_X[_CFG__CHUCK_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_CHUCK_WARNING_X[_CFG__CHUCK_SIZE];
	CX__VAR_STRING_CTRL  sCH__RCP_CHUCK_ALARM_X[_CFG__CHUCK_SIZE];

	CX__VAR_DIGITAL_CTRL dCH__RCP_TEMPDROP_CHECK;

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

	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__MON_PRESSURE_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__APC_OBJ__MON_PRESSURE_STABLE_ACTIVE;

	// OBJ PT_X ...
	int PT_OBJ__Check_ERROR();

	int iDATA__PT_SIZE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__PT_X__MON_ABORT_ACTIVE[_CFG__PT_SIZE];

	// OBJ RF_TOP ...
	int RF_TOP_OBJ__Start_MODE(const CString& obj_mode, const CString& para_data);
	int RF_TOP_OBJ__Start_OFF();
	int RF_TOP_OBJ__Check_ERROR();
	int RF_TOP_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__RF_TOP;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__RF_TOP;

	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_TOP__PARA_SET_POWER;
	CX__VAR_ANALOG_CTRL  aEXT_CH__RF_TOP__PARA_HOLD_TIME;

	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_TOP__MON_POWER_ABORT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_TOP__MON_REFLECT_HIGH_LIMIT_ACTIVE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_TOP__MON_REFLECT_MAX_COEFFICIENT_ACTIVE;

	// OBJ MATCHER ...
	int MAT_OBJ__Start_MODE(const CString& obj_mode);
	int MAT_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__MAT;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__MAT;

	CX__VAR_ANALOG_CTRL aEXT_CH__MAT__PARA_LOAD_POS_CH1;
	CX__VAR_ANALOG_CTRL aEXT_CH__MAT__PARA_LOAD_POS_CH2;

	CX__VAR_ANALOG_CTRL aEXT_CH__MAT__PARA_TUNE_POS_CH1;
	CX__VAR_ANALOG_CTRL aEXT_CH__MAT__PARA_TUNE_POS_CH2;

	CX__VAR_ANALOG_CTRL aEXT_CH__MAT__PARA_CAP_POS_CH1;
	CX__VAR_ANALOG_CTRL aEXT_CH__MAT__PARA_CAP_POS_CH2;

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

	// OBJ VAPORIZER ...
	int LFC_OBJ__Start_CONTROL(const CString& para_flow);
	int LFC_OBJ__Start_CLOSE();
	int LFC_OBJ__Start_DUMP();
	int LFC_OBJ__Check_ERROR();
	int LFC_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__LFC;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LFC;

	CX__VAR_STRING_CTRL  sEXT_CH__LFC__PARA_SET_FLOW;
	CX__VAR_STRING_CTRL  sEXT_CH__LFC__PARA_RAMP_SEC;

	CX__VAR_DIGITAL_CTRL dEXT_CH__LFC__MON_LFC_ABORT_ACTIVE;

	// OBJ LIFT_PIN ...
	int LIFT_PIN_OBJ__Start_MODE(const CString& obj_mode);
	int LIFT_PIN_OBJ__Check_ABORTED();

	bool bActive__OBJ_CTRL__LIFT_PIN;
	CII_EXT_OBJECT__CTRL *pOBJ_CTRL__LIFT_PIN;
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
	int Get__STEP_CTRL();
	//

public:
	CObj__STEP_STRIP();
	~CObj__STEP_STRIP();

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
