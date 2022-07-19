#pragma once

#include "Interface_Code.h"
#include "VTYRemoteMessages.h"


class CObj__VERITY_SERVER : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL  mX__Log_Ctrl;

	int iActive__SIM_MODE;

	SCX__ETHERNET_JGLEE mX__Net_Client;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	CX__VAR_STRING_CTRL sCH__COMM_STATE;
	//

	//-------------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__TEST_VTY_FAIL;
	int Call__TEST_VTY_FAIL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__TEST_TIMEOUT;
	int Call__TEST_TIMEOUT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__EVENT_NOTREADY;
	int Call__EVENT_NOTREADY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	int _Fnc__ERROR_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const CString& var_name, const short cmd_id, const CString& err_msg);

	//
	CString sMODE__EVENT_READY;
	int Call__EVENT_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__EVENT_ENDPOINT;
	int Call__EVENT_ENDPOINT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	int _Fnc__EVENT_ENDPOINT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const CString& var_name, const short cmd_id);
	//

	// ...
	void Mon__DRV_PROC(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int  SEND__COMMAND(const CString& var_name, const char *p_send,const int s_len);
	//

public:
	CObj__VERITY_SERVER();
	~CObj__VERITY_SERVER();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);

};
