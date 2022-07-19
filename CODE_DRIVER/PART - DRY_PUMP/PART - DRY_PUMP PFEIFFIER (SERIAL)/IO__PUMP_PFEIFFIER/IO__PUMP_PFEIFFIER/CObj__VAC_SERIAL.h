#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__VAC_SERIAL__DEF.h"


class CObj__VAC_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	// ...
	int iActive__SIM_MODE;

	// ...
	SCX__SERIAL_JG mX_Serial;

	bool bActive__COMM_ONLINE;
	int iPara__ADDR_ID;
	//

	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xAPP__LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV__LOG_CTRL;

	void WRITE__APP_LOG_MSG(const CString& log_msg);
	void WRITE__DRV_LOG_MSG(const CString& log_msg);
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;	
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_PARAMETER;	

	// IMON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STS;	
	CX__VAR_STRING_CTRL  sCH__MON_VERSION;

	CX__VAR_STRING_CTRL  sCH__MON_ACTIVE_FAULT;

	// IMON.STATE ...
	CX__VAR_STRING_CTRL  sCH__MON_STATE_PUMP_RUNNING;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_ROOTS_RUNNING;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_N2_VALVE;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_STDBY_VALVE;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_WATER_VALVE;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_INLET_VALVE;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_PERMIT_VALVE;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_HP_FB_VALVE;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_HEAT1_POWER;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_FAULT;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_CONTROL_MODE;

	CX__VAR_STRING_CTRL  sCH__MON_STATE_PRESSURE_mBAR;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_PRESSURE_TORR;
	CX__VAR_STRING_CTRL  sCH__MON_STATE_FB_POWER;
	//

	// IO CHANNEL  ...
	// DO
	CX__VAR_DIGITAL_CTRL doCH__PUMP_ADDRESS;
	CX__VAR_DIGITAL_CTRL doCH__SERPERATOR_CHAR;

	CX__VAR_DIGITAL_CTRL doCH__MODE_SET;

	// SI
	CX__VAR_STRING_CTRL  siCH__VERSION;
	CX__VAR_STRING_CTRL  siCH__PUMP_STATE;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LOCAL;
	int  Call__LOCAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__REMOTE;
	int  Call__REMOTE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__PUMP_START;
	int  Call__PUMP_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PUMP_STOP;
	int  Call__PUMP_STOP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__ROOTS_START;
	int  Call__ROOTS_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ROOTS_STOP;
	int  Call__ROOTS_STOP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__PURGE_START;
	int  Call__PURGE_START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PURGE_STOP;
	int  Call__PURGE_STOP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int _Drv__CMMD_SEND(const CString& set_cmmd, CString* r_data);

	int _Update__PUMP_STATE(const CString& rsp_data);
	//


public:
	CObj__VAC_SERIAL();
	~CObj__VAC_SERIAL();

	// ...
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_rs232_variable);

	int __DEFINE__ALARM(p_alarm);

	// ...
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	// ...
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	// ...
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
