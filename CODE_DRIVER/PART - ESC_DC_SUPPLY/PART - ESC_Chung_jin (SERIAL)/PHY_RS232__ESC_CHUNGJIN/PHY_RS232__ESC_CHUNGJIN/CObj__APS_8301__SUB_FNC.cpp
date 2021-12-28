#include "StdAfx.h"
#include "CObj__APS_8301.h"


// ...
int CObj__APS_8301
::_Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm)
{
	if(sCH__MON_COMM_STS->Check__DATA(STR__ONLINE) > 0)
	{
		return 1;
	}

	return -1;
}

int CObj__APS_8301
::_Fnc__Ramping_Ctrl(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm, 
					 const bool active_up)
{
	double cfg_msec;

	if(active_up)		cfg_msec = aCH__CFG_RAMP_UP_TIME->Get__VALUE();
	else				cfg_msec = -1.0 * aCH__CFG_RAMP_DOWN_TIME->Get__VALUE();

	//
	doCH__ESC_VOLTAGE_OUTPUT_SET->Set__DATA(STR__OFF);

	double cfg_set = aCH__CFG_RAMP_START_VOLTAGE->Get__VALUE();
	aoCH__ESC_VOLTAGE_SET->Set__VALUE(cfg_set);

	aoCH__ESC_RAMP_TIME_SET->Set__VALUE(cfg_msec);

	doCH__ESC_VOLTAGE_OUTPUT_SET->Set__DATA(STR__ON);
	return 1;
}

int CObj__APS_8301
::_Fnc__Abort_Ctrl()
{
	doCH__ESC_POWER_SET->Set__DATA(STR__OFF);
	doCH__ESC_VOLTAGE_OUTPUT_SET->Set__DATA(STR__OFF);

	aoCH__ESC_VOLTAGE_SET->Set__VALUE(0.0);
	return 1;
}

int CObj__APS_8301
::_Get__HexToDec(const CString& str_hexa)
{
	CString str_data = str_hexa;
	str_data.MakeUpper();

	int dec_value = 0;
	int i_limit = str_data.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		if(i > 0)		dec_value *= 16;

		char ch = str_data.GetAt(i);

		if(((ch >= '0')&&(ch <= '9')))		dec_value += (ch - '0');
		else if(ch == 'A')						dec_value += 10;
		else if(ch == 'B')						dec_value += 11;
		else if(ch == 'C')						dec_value += 12;
		else if(ch == 'D')						dec_value += 13;
		else if(ch == 'E')						dec_value += 14;
		else if(ch == 'F')						dec_value += 15;		
	}

	return dec_value;
}
