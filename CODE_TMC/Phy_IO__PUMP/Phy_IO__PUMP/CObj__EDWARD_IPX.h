#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__EDWARD_IPX__DEF.h"


class CObj__EDWARD_IPX : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;

	int iFlag__APP_LOG;
	int iActive_SIM;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// VIRTUAL CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__SEQUENCE_MSG;
	CX__VAR_STRING_CTRL  sCH__COMM_STS;
	CX__VAR_STRING_CTRL  sCH__PUMP_STS;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PUMP_ON_DELAY_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PUMP_ON_OFF_TIMEOUT;
	CX__VAR_STRING_CTRL  sCH__PUMP_ON_TIME_COUNT;

	CX__VAR_DIGITAL_CTRL dCFG_CH__PUMP_ON_SIGNAL_CHK_SKIP;
	CX__VAR_DIGITAL_CTRL dCFG_CH__WATER_LEAK_DETECT_PUMP_OFF;

	// IO CHANNEL ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_IO_COMM_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_RUN_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_WARNING_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_ALARM_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_WATER_FLOW_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DI_PUMP_LEAK_DETECT_STS;
	CX__VAR_DIGITAL_CTRL dEXT_CH__DO_PUMP_ON_OFF;

	// ...
	SCX__ASYNC_TIMER_CTRL m_xAsncTimer;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	//

	
	//-------------------------------------------------------------------------
	// Init ----
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm);

	// Pump On -----
	CString sMODE__PUMP_ON;
	int  Call__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm);
	int  Fnc__PUMP_ON(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm);

	// Pump Off -----
	CString sMODE__PUMP_OFF;
	int  Call__PUMP_OFF(CII_OBJECT__VARIABLE* p_variable,
					    CII_OBJECT__ALARM* p_alarm);
	int  Fnc__PUMP_OFF(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm);


	//.....
	void Mon__ANI_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	void Mon__WATER_LEAK_DETECT_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  Is__OFFLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//.....
	void Fnc__APP_LOG(const CString& log_msg);

	//
	

public:
	CObj__EDWARD_IPX();
	~CObj__EDWARD_IPX();

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
