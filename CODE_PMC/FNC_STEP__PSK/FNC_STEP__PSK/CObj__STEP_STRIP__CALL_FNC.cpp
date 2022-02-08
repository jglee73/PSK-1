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
	return _Fnc__END();
}
int CObj__STEP_STRIP
::Call__START(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString rcp__chuck_temp_x[_CFG__CHUCK_SIZE];
	CString rcp__chuck_offset_x[_CFG__CHUCK_SIZE];
	CString rcp__chuck_warning_x[_CFG__CHUCK_SIZE];
	CString rcp__chuck_alarm_x[_CFG__CHUCK_SIZE];

	CString rcp__wall_main_temp;
	CString rcp__wall_offset;
	CString rcp__wall_warning;
	CString rcp__wall_alarm;

	int i;

	// Chuck.Temperature ...
	for(i=0; i<_CFG__CHUCK_SIZE; i++)
	{
		rcp__chuck_temp_x[i]    = sCH__RCP_CHUCK_TEMP_X[i]->Get__STRING();
		rcp__chuck_offset_x[i]  = sCH__RCP_CHUCK_OFFSET_X[i]->Get__STRING();
		rcp__chuck_warning_x[i] = sCH__RCP_CHUCK_WARNING_X[i]->Get__STRING();
		rcp__chuck_alarm_x[i]   = sCH__RCP_CHUCK_ALARM_X[i]->Get__STRING();
	}
	// Wall.Temperature ...
	{
		rcp__wall_main_temp = sCH__RCP_WALL_MAIN_TEMP->Get__STRING();
		rcp__wall_offset    = sCH__RCP_WALL_MAIN_OFFSET->Get__STRING();	
		rcp__wall_warning   = sCH__RCP_WALL_MAIN_WARNING->Get__STRING();	
		rcp__wall_alarm     = sCH__RCP_WALL_MAIN_ALARM->Get__STRING();
	}

	// Temperature.Check ...
	{

	}
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

	// RF_TOP ...
	{
		RF_TOP_OBJ__Start_OFF();
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

