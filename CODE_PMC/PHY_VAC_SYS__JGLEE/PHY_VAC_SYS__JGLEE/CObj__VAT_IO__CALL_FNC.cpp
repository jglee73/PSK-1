#include "StdAfx.h"
#include "CObj__VAT_IO.h"

#include "CCommon_Utility.h"


#define CTRL_MODE__NORMAL			0
#define CTRL_MODE__CLOSE			1
#define CTRL_MODE__OPEN				2
#define CTRL_MODE__HOLD				3
#define CTRL_MODE__RESET			4


// ...
int CObj__VAT_IO
::Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	sCH__OBJ_STATUS->Set__DATA("STANDBY");

	return OBJ_AVAILABLE;
}

int CObj__VAT_IO
::Call__CLOSE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CLOSE);

	if(iActive__SIM_MODE > 0)
	{
		aEXT_CH__AI_APC_POSITION->Set__DATA("0.0");

		if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__ON);
		if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
		if(bActive__DI_APC_VLV_STATE)		dEXT_CH__DI_APC_VLV_STATE->Set__DATA(STR__CLOSE);
	}
	return 1;
}
int CObj__VAT_IO
::Call__OPEN(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__OPEN);

	if(iActive__SIM_MODE > 0)
	{
		aEXT_CH__AI_APC_POSITION->Set__DATA("100.0");

		if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
		if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__ON);
		if(bActive__DI_APC_VLV_STATE)		dEXT_CH__DI_APC_VLV_STATE->Set__DATA(STR__OPEN);
	}
	return 1;
}

int CObj__VAT_IO
::Call__POSITION(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	aCH__PARA_POSITION->Get__DATA(ch_data);
	sCH__MON_SET_POSITION->Set__DATA(ch_data);
	aEXT_CH__AO_APC_SETPOINT_DATA->Set__DATA(ch_data);

	dEXT_CH__DO_APC_SETPOINT_TYPE->Set__DATA(STR__POSITION);
	dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);

	if(iActive__SIM_MODE > 0)
	{
		aEXT_CH__AI_APC_POSITION->Set__DATA(ch_data);

		if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
		if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
	}
	return 1;
}
int CObj__VAT_IO
::Call__PRESSURE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	aCH__PARA_PRESSURE->Get__DATA(ch_data);
	sCH__MON_SET_PRESSURE->Set__DATA(ch_data);
	aEXT_CH__AO_APC_SETPOINT_DATA->Set__DATA(ch_data);

	dEXT_CH__DO_APC_SETPOINT_TYPE->Set__DATA(STR__PRESSURE);
	dEXT_CH__DO_APC_CTRL_MODE->Set__DATA(STR__CONTROL);

	if(iActive__SIM_MODE > 0)
	{
		aEXT_CH__AI_APC_PRESSURE->Set__DATA(ch_data);

		if(bActive__DI_APC_VLV_CLOSE)		dEXT_CH__DI_APC_VLV_CLOSE->Set__DATA(STR__OFF);
		if(bActive__DI_APC_VLV_OPEN)		dEXT_CH__DI_APC_VLV_OPEN->Set__DATA(STR__OFF);
	}
	return 1;
}