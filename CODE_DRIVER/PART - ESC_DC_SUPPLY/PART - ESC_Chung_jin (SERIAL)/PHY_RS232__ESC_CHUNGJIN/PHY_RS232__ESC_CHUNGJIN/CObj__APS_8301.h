#pragma once

#include "Interface_Code.h"

#include "CObj__APS_8301__ALID.h"
#include "CObj__APS_8301__DEF.h"


class CObj__APS_8301 : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	int iActive_SIM;

	// ...	
	SCX__SERIAL_JG mX_Serial;

	CString sTerm_Str;
	CString sTerm_Exp;

	int	 m_Rcv_Time;
	int	 m_RetryCnt;

	bool bActive__COMM_ONLINE;
	//


	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	int iFLAG__DRV_FLAG;

	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_PARAMETER;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STS;
	CX__VAR_STRING_CTRL  sCH__MON_SYSTEM_ABORT;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_VOLTAGE_SET;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_POWER_STS;
	CX__VAR_STRING_CTRL  sCH__INFO_HIGH_VOLTAGE_STS;
	CX__VAR_STRING_CTRL  sCH__INFO_REVERSE_VOLTAGE_STS;
	CX__VAR_STRING_CTRL  sCH__INFO_OVER_CURRENT_ALARM_STS;
	CX__VAR_STRING_CTRL  sCH__INFO_SYSTEM_ALARM_STS;

	CX__VAR_STRING_CTRL  sCH__INFO_FIRMWARE_VER;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_LEAK_CURRUNT_LIMIT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_START_VOLTAGE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_UP_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RAMP_DOWN_TIME;

	CX__VAR_DIGITAL_CTRL dCH__CFG_AUTO_TOGGLE_USE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_COUNT;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_START_VOLTAGE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_AUTO_TOGGLE_DOWN_RATE;
	//

	// IO CHANNEL  -----------------------------------
	// AO ...
	CX__VAR_ANALOG_CTRL aoCH__ESC_VOLTAGE_SET;
	CX__VAR_ANALOG_CTRL aoCH__ESC_CURRENT_LIMIT_SET;
	CX__VAR_ANALOG_CTRL aoCH__ESC_TIME_DELAY_SET;
	CX__VAR_ANALOG_CTRL aoCH__ESC_RAMP_TIME_SET;

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__ESC_POWER_SET;
	CX__VAR_DIGITAL_CTRL doCH__ESC_VOLTAGE_OUTPUT_SET;
	CX__VAR_DIGITAL_CTRL doCH__ESC_DISCHARGE_MODE_SET;
	CX__VAR_DIGITAL_CTRL doCH__ESC_ALARM_RESET_SET;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__ESC_VOLTAGE;
	CX__VAR_STRING_CTRL  siCH__ESC_LEAK_CURRENT;
	CX__VAR_STRING_CTRL  siCH__ESC_SYSTEM_STS;

	CX__VAR_STRING_CTRL  siCH__ESC_FIRMWARE_VER;
	//	


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ON;
	int  Call__ON(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__OFF;
	int  Call__OFF(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM*	p_alarm);

	CString sMODE__RAMP_UP;
	int  Call__RAMP_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__RAMP_DOWN;
	int  Call__RAMP_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ALARM_RESET;
	int  Call__ALARM_RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	int  _Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm);
	int  _Fnc__Ramping_Ctrl(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_up);
	int  _Fnc__Abort_Ctrl();

	int _Send__Command(const CString& s_cmd, CString* r_data);
	int _Get__HexToDec(const CString& str_hexa);
	
	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//

public:
	CObj__APS_8301();
	~CObj__APS_8301();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_rs232_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
