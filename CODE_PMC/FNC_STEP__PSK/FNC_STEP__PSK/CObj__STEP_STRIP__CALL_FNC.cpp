#include "StdAfx.h"
#include "CObj__STEP_STRIP.h"
#include "CObj__STEP_STRIP__DEF.h"


// ...
int CObj__STEP_STRIP
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int CObj__STEP_STRIP
::Call__READY(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	// ...
	{
		sCH__INFO_STEP_CUR_NUM->Set__DATA("");
		sCH__INFO_STEP_PRE_TIME->Set__DATA("");
	}

	// EPD.INIT ...
	{
		EPD_OBJ__Call_INIT();
	}

	return _Fnc__END();
}
int CObj__STEP_STRIP
::Call__START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int r_flag = Fnc__HTR_STEP_START(p_variable, p_alarm);
	if(r_flag < 0)			return r_flag;

	return 1;
}

int CObj__STEP_STRIP
::Call__ABORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	_Fnc__END();

	sCH__OBJ_MSG->Set__DATA("Call__ABORT() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}
int CObj__STEP_STRIP
::Call__END(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	sCH__OBJ_MSG->Set__DATA("Call__END() : Start ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");

	_Fnc__END();

	sCH__OBJ_MSG->Set__DATA("Call__END() : End ...");
	sCH__OBJ_SUB_MSG->Set__DATA("");
	return 1;
}

int CObj__STEP_STRIP::_Fnc__END()
{
	int i;

	// EPD.IDLE ...
	{
		EPD_OBJ__Start_IDLE();
	}

	// HTR.CHUCK ...
	{
		HTR_CHUCK_OBJ__Init_DATA();
	}
	// HTR.WALL ...
	{
		HTR_WALL_OBJ__Init_DATA();
	}

	// RF_TOP ...
	{
		RF_TOP_OBJ__Call_OFF();
	}

	// MFC_X.CTRL ...
	for(i=0; i<iDATA__MFC_SIZE; i++)
	{
		MFC_OBJ__Call_CLOSE(i);
	}

	// APC.CTRL ...
	{
		APC_OBJ__Call_OPEN();
	}

	return 1;
}

