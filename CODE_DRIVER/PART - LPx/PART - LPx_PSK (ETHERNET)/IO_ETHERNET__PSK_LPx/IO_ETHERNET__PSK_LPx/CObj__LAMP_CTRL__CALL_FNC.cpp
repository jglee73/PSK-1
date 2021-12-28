#include "StdAfx.h"
#include "CObj__LAMP_CTRL.h"
#include "CObj__LAMP_CTRL__DEF.h"
#include "CObj__LAMP_CTRL__ALID.h"


//----------------------------------------------------------------------------------------------------
// LIGHT RED -----
int CObj__LAMP_CTRL::
Call__RED_ON()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_RED->Set__DATA(STR__ON);
	else						dCH__LINK_LOCAL_LIGHT_RED->Set__DATA(STR__ON);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__RED_OFF()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_RED->Set__DATA(STR__OFF);
	else						dCH__LINK_LOCAL_LIGHT_RED->Set__DATA(STR__OFF);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__RED_BLINK()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_RED->Set__DATA(STR__BLINK);
	else						dCH__LINK_LOCAL_LIGHT_RED->Set__DATA(STR__BLINK);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}


// LIGHT YELLOW -----
int CObj__LAMP_CTRL::
Call__YELLOW_ON()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_YELLOW->Set__DATA(STR__ON);
	else						dCH__LINK_LOCAL_LIGHT_YELLOW->Set__DATA(STR__ON);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__YELLOW_OFF()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_YELLOW->Set__DATA(STR__OFF);
	else						dCH__LINK_LOCAL_LIGHT_YELLOW->Set__DATA(STR__OFF);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__YELLOW_BLINK()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_YELLOW->Set__DATA(STR__BLINK);
	else						dCH__LINK_LOCAL_LIGHT_YELLOW->Set__DATA(STR__BLINK);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}


// LIGHT GREEN -----
int CObj__LAMP_CTRL::
Call__GREEN_ON()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_GREEN->Set__DATA(STR__ON);
	else						dCH__LINK_LOCAL_LIGHT_GREEN->Set__DATA(STR__ON);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__GREEN_OFF()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_GREEN->Set__DATA(STR__OFF);
	else						dCH__LINK_LOCAL_LIGHT_GREEN->Set__DATA(STR__OFF);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__GREEN_BLINK()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_GREEN->Set__DATA(STR__BLINK);
	else						dCH__LINK_LOCAL_LIGHT_GREEN->Set__DATA(STR__BLINK);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}


// LIGHT BLUE -----
int CObj__LAMP_CTRL::
Call__BLUE_ON()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_BLUE->Set__DATA(STR__ON);
	else						dCH__LINK_LOCAL_LIGHT_BLUE->Set__DATA(STR__ON);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__BLUE_OFF()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_BLUE->Set__DATA(STR__OFF);
	else						dCH__LINK_LOCAL_LIGHT_BLUE->Set__DATA(STR__OFF);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__BLUE_BLINK()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)		dCH__LIGHT_BLUE->Set__DATA(STR__BLINK);
	else						dCH__LINK_LOCAL_LIGHT_BLUE->Set__DATA(STR__BLINK);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}

// LIGHT WHITE -----
int CObj__LAMP_CTRL::
Call__WHITE_ON()
{
	return -1;
}
int CObj__LAMP_CTRL::
Call__WHITE_OFF()
{
	return -1;
}
int CObj__LAMP_CTRL::
Call__WHITE_BLINK()
{
	return -1;
}


// ALARM BUZZER -----
int CObj__LAMP_CTRL::
Call__ALARM_BUZZER_ON()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)			dCH__ALARM_BUZZER->Set__DATA(STR__ON);
	else							dCH__LINK_LOCAL_ALARM_BUZZER->Set__DATA(STR__ON);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__ALARM_BUZZER_OFF()
{
	bool active__remote_mode = dCH__IO_MONITOR__ACTIVE_FLAG->Check__DATA(STR__ENABLE);

	if(active__remote_mode)			dCH__ALARM_BUZZER->Set__DATA(STR__OFF);
	else							dCH__LINK_LOCAL_ALARM_BUZZER->Set__DATA(STR__OFF);

	doEXT_CH__EFEM_LAMP_BUZZER->Set__DATA(CMD__SET);
	return 1;
}
int CObj__LAMP_CTRL::
Call__ALARM_BUZZER_RESET_ON()
{
	return -1;
}
int CObj__LAMP_CTRL::
Call__ALARM_BUZZER_RESET_OFF()
{
	return -1;
}


// MELODY -----
int CObj__LAMP_CTRL::
Call__MELODY_ON()
{
	return -1;
}

int CObj__LAMP_CTRL::
Call__MELODY_OFF()
{
	return -1;
}
