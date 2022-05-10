#include "StdAfx.h"
#include "CObj__STEP_METAL.h"
#include "CObj__STEP_METAL__DEF.h"


// ...
int CObj__STEP_METAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	printf(" * %s : Call__INIT() - Start \n", sObject_Name);

	printf(" * %s : Call__INIT() - End \n", sObject_Name);
	return 1;
}

int CObj__STEP_METAL
::Call__READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__INFO_STEP_CUR_NUM->Set__DATA("");
	}

	return _Fnc__END();
}
int CObj__STEP_METAL
::Call__START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int r_flag = Fnc__HTR_STEP_START(p_variable, p_alarm);
	if(r_flag < 0)			return r_flag;

	return 1;
}

int CObj__STEP_METAL
::Call__ABORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	_Fnc__END();

	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}
int CObj__STEP_METAL
::Call__END(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__END() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	_Fnc__END();

	sCH__OBJ_MSG->Set__DATA("Call__END() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}

int CObj__STEP_METAL::_Fnc__END()
{
	int i;

	// HTR.CHUCK ...
	{
		HTR_CHUCK_OBJ__Init_DATA();
	}
	// HTR.WALL ...
	{
		HTR_WALL_OBJ__Init_DATA();
	}

	// RF_SOURCE ...
	{
		RF_SRC_OBJ__Start_OFF();
	}
	// RF_BIAS ...
	{
		RF_BIAS_OBJ__Start_OFF();
	}
	
	// ESC ...
	{
		ESC_OBJ__Start_HE_CLOSE();
		ESC_OBJ__Init_DATA();
	}

	// MFC_X.CTRL ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		MFC_OBJ__Start_CLOSE(i);
	}

	// APC.CTRL ...
	{
		APC_OBJ__Start_OPEN();
	}

	return 1;
}

