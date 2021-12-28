#include "stdafx.h"

#include "CObj__RFID_CTRL.h"

#include "CObj__RFID_CTRL__ALID.h"
#include "CObj__RFID_CTRL__DEF.h"


// ...
int	CObj__RFID_CTRL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int	CObj__RFID_CTRL
::Call__CID_READ(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = siEXT_CH__RFID_READ->Get__STRING();

	if(Wait__RFID_READ(p_variable, p_alarm) < 0)
	{
		return -1;
	}
	
	ch_data = sEXT_CH__LP_INFO__RFID_RSP->Get__STRING();
	return 1;
}
int	CObj__RFID_CTRL
::Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable, 
				  CII_OBJECT__ALARM* p_alarm)
{
	int page_id = (int) aCH__PARA_PAGE_ID->Get__VALUE();
	aEXT_CH__PARA_RFID_PAGE_ID->Set__VALUE(page_id);

	CString ch_data = siEXT_CH__RFID_READ->Get__STRING();

	if(Wait__RFID_READ(p_variable, p_alarm) < 0)
	{
		return -1;
	}

	ch_data = sEXT_CH__LP_INFO__RFID_RSP->Get__STRING();
	return 1;
}

int	CObj__RFID_CTRL
::Call__CID_WRITE(CII_OBJECT__VARIABLE* p_variable, 
				  CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = sCH__PARA_PAGE_CID->Get__STRING();
	int page_id = 0;

	aEXT_CH__PARA_RFID_PAGE_ID->Set__VALUE(page_id);
	soEXT_CH__RFID_WRITE->Set__DATA(ch_data);

	return Wait__RFID_WRITE(p_variable, p_alarm);
}
int	CObj__RFID_CTRL
::Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable, 
				   CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data = sCH__PARA_PAGE_DATA->Get__STRING();
	int page_id = (int) aCH__PARA_PAGE_ID->Get__VALUE();

	aEXT_CH__PARA_RFID_PAGE_ID->Set__VALUE(page_id);
	soEXT_CH__RFID_WRITE->Set__DATA(ch_data);

	return Wait__RFID_WRITE(p_variable, p_alarm);
}

// ...
int  CObj__RFID_CTRL
::Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(sEXT_CH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) < 0)
	{
		int alarm_id = ALID__OFFLINE;

		p_alarm->Post__ALARM(alarm_id);
		return -1;
	}
	return 1;
}

int  CObj__RFID_CTRL
::Wait__RFID_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	sEXT_CH__LP_INFO__RFID_STATUS->Set__DATA(STR__READING);

	while(1)
	{
		ch_data = sEXT_CH__LP_INFO__RFID_STATUS->Get__STRING();

		if(ch_data.CompareNoCase(STR__READY) == 0)				return 1;
		if(ch_data.CompareNoCase(STR__READ_COMPLETE) == 0)		return 2;

		if(ch_data.CompareNoCase(STR__ERROR)   == 0)			break;
		if(ch_data.CompareNoCase(STR__UNKNOWN) == 0)			break;
	}

	return -1;
}
int  CObj__RFID_CTRL
::Wait__RFID_WRITE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	sEXT_CH__LP_INFO__RFID_STATUS->Set__DATA(STR__WRITING);

	while(1)
	{
		ch_data = sEXT_CH__LP_INFO__RFID_STATUS->Get__STRING();

		if(ch_data.CompareNoCase(STR__READY) == 0)				return 1;
		if(ch_data.CompareNoCase(STR__WRITE_COMPLETE) == 0)		return 2;

		if(ch_data.CompareNoCase(STR__ERROR)   == 0)			break;
		if(ch_data.CompareNoCase(STR__UNKNOWN) == 0)			break;
	}

	return -1;
}
