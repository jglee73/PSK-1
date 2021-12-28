#include "stdafx.h"
#include "CObj__APS_8301.h"


// ...
int  CObj__APS_8301
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__ESC_ALARM_RESET_SET->Set__DATA(STR__ON);

	double cfg__current_limit = aCH__CFG_LEAK_CURRUNT_LIMIT->Get__VALUE();
	aoCH__ESC_CURRENT_LIMIT_SET->Set__VALUE(cfg__current_limit);

	siCH__ESC_FIRMWARE_VER->Get__STRING();
	doCH__ESC_DISCHARGE_MODE_SET->Set__DATA(STR__OFF);

	return 1;
}

int  CObj__APS_8301
::Call__ON(CII_OBJECT__VARIABLE*	p_variable, CII_OBJECT__ALARM* p_alarm)
{	
	double para__vol_set = aCH__PARA_VOLTAGE_SET->Get__VALUE();

	doCH__ESC_VOLTAGE_OUTPUT_SET->Set__DATA(STR__OFF);

	aoCH__ESC_TIME_DELAY_SET->Set__VALUE(0.0);
	aoCH__ESC_VOLTAGE_SET->Set__VALUE(para__vol_set);

	doCH__ESC_POWER_SET->Set__DATA(STR__ON);
	doCH__ESC_VOLTAGE_OUTPUT_SET->Set__DATA(STR__ON);

	return 1;
}
int  CObj__APS_8301
::Call__OFF(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__ESC_VOLTAGE_OUTPUT_SET->Set__DATA(STR__OFF);

	aoCH__ESC_TIME_DELAY_SET->Set__VALUE(0.0);
	aoCH__ESC_VOLTAGE_SET->Set__VALUE(0.0);

	return 1;
}

int  CObj__APS_8301
::Call__RAMP_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return _Fnc__Ramping_Ctrl(p_variable,p_alarm, true);
}
int  CObj__APS_8301
::Call__RAMP_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return _Fnc__Ramping_Ctrl(p_variable,p_alarm, false);
}

int  CObj__APS_8301
::Call__ALARM_RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__ESC_ALARM_RESET_SET->Set__DATA(STR__ON);
	
	siCH__ESC_SYSTEM_STS->Get__STRING();
	sCH__INFO_SYSTEM_ALARM_STS->When__DATA(STR__OFF, 2.0);
	
	if(sCH__INFO_SYSTEM_ALARM_STS->Check__DATA(STR__ON) > 0)
	{
		// Alarm 

		return -1;
	}
	return 1;
}
