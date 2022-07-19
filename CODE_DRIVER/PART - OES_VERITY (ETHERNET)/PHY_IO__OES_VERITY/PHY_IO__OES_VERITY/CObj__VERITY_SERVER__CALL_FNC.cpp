#include "stdafx.h"
#include "CObj__VERITY_SERVER.h"

#include "CMng__MSG_CTRL.h"


// ...
int CObj__VERITY_SERVER
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

// ...
int CObj__VERITY_SERVER
::Call__TEST_VTY_FAIL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_name;
	var_name = "TEST.VTY_FAIL";

	short int cmd_id = VTY_CMD_CFG_VALIDATE;
	CString err_msg;

	err_msg = "Fail State - Test !!!";

	return _Fnc__ERROR_TEST(p_variable, p_alarm, var_name, cmd_id, err_msg);
}
int CObj__VERITY_SERVER
::Call__TEST_TIMEOUT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_name;
	var_name = "TEST.TIMEOUT";

	short int cmd_id = VTY_CMD_CFG_VALIDATE;
	CString err_msg;

	err_msg = "Timeout";

	return _Fnc__ERROR_TEST(p_variable, p_alarm, var_name, cmd_id, err_msg);
}

int CObj__VERITY_SERVER
::_Fnc__ERROR_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const CString& var_name, const short cmd_id, const CString& err_msg)
{
	CMng__MGS_CTRL x_msg_ctrl;

	char s_packet[256] = { 0, };

	int s_len = x_msg_ctrl.Make__PACKET_INFO_SERVER(cmd_id, s_packet, err_msg, true);

	return SEND__COMMAND(var_name, s_packet, s_len);
}

// ...
int CObj__VERITY_SERVER
::Call__EVENT_NOTREADY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_name;
	var_name = "Event.NotReady";

	short int cmd_id = VTY_EVENT_NOTREADY;

	return _Fnc__EVENT_ENDPOINT(p_variable, p_alarm, var_name, cmd_id);
}
int CObj__VERITY_SERVER
::Call__EVENT_READY(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_name;
	var_name = "Event.Ready";

	short int cmd_id = VTY_EVENT_READY;

	return _Fnc__EVENT_ENDPOINT(p_variable, p_alarm, var_name, cmd_id);
}
int CObj__VERITY_SERVER
::Call__EVENT_ENDPOINT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_name;
	var_name = "Event.EndPoint";

	short int cmd_id = VTY_EVENT_ENDPOINT;

	return _Fnc__EVENT_ENDPOINT(p_variable, p_alarm, var_name, cmd_id);
}
int CObj__VERITY_SERVER
::_Fnc__EVENT_ENDPOINT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm, const CString& var_name, const short cmd_id)
{
	CMng__MGS_CTRL x_msg_ctrl;

	char s_packet[256] = { 0, };

	int s_len = x_msg_ctrl.Make__PACKET_INFO_SERVER(cmd_id, s_packet);

	return SEND__COMMAND(var_name, s_packet, s_len);
}
