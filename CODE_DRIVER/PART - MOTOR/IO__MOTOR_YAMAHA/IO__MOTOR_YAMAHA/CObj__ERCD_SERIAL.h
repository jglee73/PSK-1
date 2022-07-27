#pragma once

#include "Interface_Code.h"

#include "CObj__ERCD_SERIAL__ALID.h"
#include "CObj__ERCD_SERIAL__DEF.h"


class CObj__ERCD_SERIAL : public __IOBJ__IO_TYPE
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

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// INFO.DRV ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_COM_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_PARAMETER;

	// MON
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STS;
	CX__VAR_STRING_CTRL  sCH__MON_SYSTEM_ABORT;

	CX__VAR_STRING_CTRL  sCH__MON_ACTIVE_JOG_UP;
	CX__VAR_STRING_CTRL  sCH__MON_ACTIVE_JOG_DOWN;

	CX__VAR_STRING_CTRL  sCH__MON_ACTIVE_GOTO_UP;
	CX__VAR_STRING_CTRL  sCH__MON_ACTIVE_GOTO_DOWN;

	// PARA.USER ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_USER_GOTO_POS;
	CX__VAR_ANALOG_CTRL  aCH__PARA_USER_GOTO_SPEED;

	// PARA.SET ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_SET_GOTO_POS;
	CX__VAR_ANALOG_CTRL  aCH__PARA_SET_GOTO_VEL;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_ROM_VER;
	CX__VAR_STRING_CTRL  sCH__INFO_ROBOT_TYPE;
	CX__VAR_STRING_CTRL  sCH__INFO_EMG_STS;

	CX__VAR_STRING_CTRL  sCH__INFO_SERVO_STS;
	CX__VAR_STRING_CTRL  sCH__INFO_CUR_POS;
	CX__VAR_STRING_CTRL  sCH__INFO_ROBOT_IDLE;
	CX__VAR_STRING_CTRL  sCH__INFO_ROBOT_HOME;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_INIT_SPEED;
	CX__VAR_ANALOG_CTRL  aCH__CFG_GOTO_SPEED;
	CX__VAR_ANALOG_CTRL  aCH__CFG_JOG_SPEED;

	CX__VAR_ANALOG_CTRL  aCH__CFG_GOTO_UP_ABS_POS;
	CX__VAR_ANALOG_CTRL  aCH__CFG_GOTO_DOWN_ABS_POS;
	//

	// IO CHANNEL  -----------------------------------
	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__CTRL_SET;
	CX__VAR_DIGITAL_CTRL doCH__ABORT_SET;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__ROM_VER;
	CX__VAR_STRING_CTRL  siCH__ROBOT_TYPE;
	CX__VAR_STRING_CTRL  siCH__EMG_STS;

	CX__VAR_STRING_CTRL  siCH__SERVO_STS;
	CX__VAR_STRING_CTRL  siCH__CUR_POS;
	CX__VAR_STRING_CTRL  siCH__ROBOT_STS_AUTO;
	CX__VAR_STRING_CTRL  siCH__ROBOT_STS_MANUAL;
	CX__VAR_STRING_CTRL  siCH__ORG_STS;
	//	


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__RESET;
	int  Call__RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__GOTO_POS;
	int  Call__GOTO_POS(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__GOTO_UP;
	int  Call__GOTO_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__GOTO_DOWN;
	int  Call__GOTO_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  Fnc__GOTO_POS(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__JOG_UP;
	int  Call__JOG_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__JOG_DOWN;
	int  Call__JOG_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	int  _Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm);
	int  _Fnc__Abort_Ctrl();

	int _Send__Command(const CString& s_cmd, CString* r_data, const bool active__act_check);
	int _Get__HexToDec(const CString& str_hexa);
	
	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//

public:
	CObj__ERCD_SERIAL();
	~CObj__ERCD_SERIAL();

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
