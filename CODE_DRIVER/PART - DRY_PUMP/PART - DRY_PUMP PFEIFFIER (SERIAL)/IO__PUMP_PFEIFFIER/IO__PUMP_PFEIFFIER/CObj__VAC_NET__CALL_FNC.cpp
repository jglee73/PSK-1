#include "StdAfx.h"
#include "CObj__VAC_NET.h"


// ..
int CObj__VAC_NET
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__VAC_NET
::Call__LOCAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}
int CObj__VAC_NET
::Call__REMOTE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__VAC_NET
::Call__PUMP_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Pump_Start);
}
int CObj__VAC_NET
::Call__PUMP_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Pump_Stop);
}

int CObj__VAC_NET
::Call__ROOTS_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Roots_Start);
}
int CObj__VAC_NET
::Call__ROOTS_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Roots_Stop);
}

int CObj__VAC_NET
::Call__PURGE_START(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Purge_Start);
}
int CObj__VAC_NET
::Call__PURGE_STOP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Purge_Stop);
}

