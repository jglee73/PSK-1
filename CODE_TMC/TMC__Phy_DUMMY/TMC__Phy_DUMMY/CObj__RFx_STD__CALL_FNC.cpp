#include "StdAfx.h"
#include "CObj__RFx_STD.h"


// ...
int  CObj__RFx_STD::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}

int  CObj__RFx_STD::
Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	sCH__CID_STRING->Set__DATA(sObject_Name);
	return 1;
}
