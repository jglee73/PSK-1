#include "StdAfx.h"
#include "CObj__LOT_NET.h"


// ..
int CObj__LOT_NET
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__LOT_NET
::Call__LOCAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}
int CObj__LOT_NET
::Call__REMOTE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__LOT_NET
::Call__ON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Start);
}
int CObj__LOT_NET
::Call__AUTO_SHUTDOWN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Stop_Slow);
}
int CObj__LOT_NET
::Call__FAST_SHUTDOWN(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return doCH__MODE_SET->Set__DATA(_Cmmd_IO__Stop);
}
