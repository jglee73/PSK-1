#include "StdAfx.h"
#include "CObj__NAVII_SERIAL.h"


// ...
int CObj__NAVII_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	doCH__CONTROL_MODE_CH1->Set__DATA(STR__HOST);
	doCH__CONTROL_MODE_CH2->Set__DATA(STR__HOST);

	doCH__INTERNAL_EXTERNAL_PRESET_CH1->Set__DATA(STR__INTERNAL);
	doCH__INTERNAL_EXTERNAL_PRESET_CH2->Set__DATA(STR__INTERNAL);

	doCH__CAPACITOR_LIMIT_CH1->Set__DATA(STR__SET);
	doCH__CAPACITOR_LIMIT_CH2->Set__DATA(STR__SET);

	doCH__ALL_CAPACITOR_INIT->Set__DATA(STR__SET);

	return flag;
}

//
int  CObj__NAVII_SERIAL
::Call__AUTO_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_all)
{
	CString ch_data;

	if(active_all)
	{
		sCH__CUR_SEL_CH->Set__DATA("ALL");

		doCH__CONTROL_MODE_CH1->Set__DATA(STR__AUTO);
		doCH__CONTROL_MODE_CH2->Set__DATA(STR__AUTO);
	}
	else
	{
		ch_data = dCH__PARA_SEL_CH->Get__STRING();
		sCH__CUR_SEL_CH->Set__DATA(ch_data);

		int ch_id = atoi(ch_data);

		if(ch_id == 1)			doCH__CONTROL_MODE_CH1->Set__DATA(STR__AUTO);
		if(ch_id == 2)			doCH__CONTROL_MODE_CH2->Set__DATA(STR__AUTO);
	}

	return 1;
}

int  CObj__NAVII_SERIAL
::Call__MANUAL_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_all)
{
	CString ch_data;

	if(active_all)
	{
		sCH__CUR_SEL_CH->Set__DATA("ALL");

		doCH__CONTROL_MODE_CH1->Set__DATA(STR__HOST);
		doCH__CONTROL_MODE_CH2->Set__DATA(STR__HOST);
	}
	else
	{
		ch_data = dCH__PARA_SEL_CH->Get__STRING();
		sCH__CUR_SEL_CH->Set__DATA(ch_data);

		int ch_id = atoi(ch_data);

		if(ch_id == 1)			doCH__CONTROL_MODE_CH1->Set__DATA(STR__HOST);
		if(ch_id == 2)			doCH__CONTROL_MODE_CH2->Set__DATA(STR__HOST);
	}

	return 1;
}

//
int  CObj__NAVII_SERIAL
::Call__CTRL_MODE_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id)
{
	CString ch_data;
	int flag = -1;

	if((ch_id == 0) || (ch_id == 1))
	{
		ch_data = dCH__PARA_CONTROL_MODE_CH1->Get__STRING();
		flag = doCH__CONTROL_MODE_CH1->Set__DATA(ch_data);
	}
	if((ch_id == 0) || (ch_id == 2))
	{
		ch_data = dCH__PARA_CONTROL_MODE_CH2->Get__STRING();
		flag = doCH__CONTROL_MODE_CH2->Set__DATA(ch_data);
	}

	return flag;
}

int  CObj__NAVII_SERIAL
::Call__PRESET_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id)
{
	CString ch_data;
	int flag = -1;

	if((ch_id == 0) || (ch_id == 1))
	{
		flag = doCH__ACTIVE_PRESET_CH1->Set__DATA(STR__SET);
	}
	
	if((ch_id == 0) || (ch_id == 2))
	{
		flag = doCH__ACTIVE_PRESET_CH2->Set__DATA(STR__SET);
	}

	return flag;
}

int  CObj__NAVII_SERIAL
::Call__LOAD_POS_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id)
{
	CString ch_data;
	int flag = -1;

	if((ch_id == 0) || (ch_id == 1))
	{
		flag = doCH__LOAD_POS_CH1->Set__DATA(STR__SET);
	}

	if((ch_id == 0) || (ch_id == 2))
	{
		flag = doCH__LOAD_POS_CH2->Set__DATA(STR__SET);
	}

	return flag;
}
int  CObj__NAVII_SERIAL
::Call__TUNE_POS_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id)
{
	CString ch_data;
	int flag = -1;

	if((ch_id == 0) || (ch_id == 1))
	{
		flag = doCH__TUNE_POS_CH1->Set__DATA(STR__SET);
	}

	if((ch_id == 0) || (ch_id == 2))
	{
		flag = doCH__TUNE_POS_CH2->Set__DATA(STR__SET);
	}

	return flag;
}

int  CObj__NAVII_SERIAL
::Call__CAP_MOTOR_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id)
{
	CString ch_data;
	int flag = -1;

	if((ch_id == 0) || (ch_id == 1))
	{
		flag = doCH__CAPACITOR_MOTOR_POS_CH1->Set__DATA(STR__SET);
	}

	if((ch_id == 0) || (ch_id == 2))
	{
		flag = doCH__CAPACITOR_MOTOR_POS_CH2->Set__DATA(STR__SET);
	}

	return flag;
}

int  CObj__NAVII_SERIAL
::Call__PROC_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// LOAD.POS ...
	{
		doCH__LOAD_POS_CH1->Set__DATA(STR__SET);
		doCH__LOAD_POS_CH2->Set__DATA(STR__SET);		
	}
	// TUNE.POS ...
	{
		doCH__TUNE_POS_CH1->Set__DATA(STR__SET);
		doCH__TUNE_POS_CH2->Set__DATA(STR__SET);
	}
	// CAP.POS ...
	{
		doCH__CAPACITOR_MOTOR_POS_CH1->Set__DATA(STR__SET);
		doCH__CAPACITOR_MOTOR_POS_CH2->Set__DATA(STR__SET);
	}

	return 1;
}
