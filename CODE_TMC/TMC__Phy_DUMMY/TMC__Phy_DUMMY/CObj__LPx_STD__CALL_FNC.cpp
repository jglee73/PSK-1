#include "StdAfx.h"
#include "CObj__LPx_STD.h"
#include "CObj__LPx_STD__DEF.h"


//----------------------------------------------------------------------------------------------------
// INIT ----- 
int  CObj__LPx_STD::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{
	return 1;
}

// DOOR OPEN -----	
int  CObj__LPx_STD::
Call__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__DOOR_STATUS->Check__DATA(STR__OPEN) < 0)
	{
		dCH__DOOR_STATUS->Set__DATA(STR__OPEN);
	}

	return 1;
}

// CHECK DOOR OPEN -----
int  CObj__LPx_STD::
Call__CHECK_DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__DOOR_STATUS->Check__DATA(STR__OPEN) > 0)
	{
		return 1;
	}
	return -1;
}

// LOAD -----
int  CObj__LPx_STD::
Call__LOAD(CII_OBJECT__VARIABLE* p_variable,
		   CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"LOAD ",sObject_Name,MB_OK|MB_TOPMOST);

	dCH__DOOR_STATUS->Set__DATA(STR__OPEN);
	dCH__FOUP_CLAMP_STATUS->Set__DATA(STR__CLAMP);
	dCH__FOUP_POS_STATUS->Set__DATA(STR__LOAD);

	Sleep(1000);
	return 1;
}

// UNLOAD -----
int  CObj__LPx_STD::
Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable,
			 CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"UNLOAD - Start ?",sObject_Name,MB_OK|MB_TOPMOST);

	sCH__TRANSFER_PIO_STATUS->Set__DATA(STR__YES);

	dCH__FOUP_CLAMP_STATUS->Set__DATA(STR__UNCLAMP);
	dCH__FOUP_EXIST_FLAG->Set__DATA(STR__NONE);

	MessageBox(NULL,"UNLOAD - End ?",sObject_Name,MB_OK|MB_TOPMOST);
	sCH__TRANSFER_PIO_STATUS->Set__DATA(STR__NO);

	return 1;
}

// PREPLOAD -----
int  CObj__LPx_STD::
Call__PREPLOAD(CII_OBJECT__VARIABLE* p_variable,
			   CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"PRELOAD - Start ?",sObject_Name,MB_OK|MB_TOPMOST);

	sCH__TRANSFER_PIO_STATUS->Set__DATA(STR__YES);

	MessageBox(NULL,"PRELOAD - Foup Exist ?",sObject_Name,MB_OK|MB_TOPMOST);

	dCH__FOUP_CLAMP_STATUS->Set__DATA(STR__UNCLAMP);
	dCH__FOUP_EXIST_FLAG->Set__DATA(STR__EXIST);

	MessageBox(NULL,"PRELOAD - End ?",sObject_Name,MB_OK|MB_TOPMOST);
	sCH__TRANSFER_PIO_STATUS->Set__DATA(STR__NO);

	return 1;
}

// RLSUNLOAD ----- 
int  CObj__LPx_STD::
Call__RLSUNLOAD(CII_OBJECT__VARIABLE* p_variable,
				CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"RLSUNLOAD - Start ?",sObject_Name,MB_OK|MB_TOPMOST);

	dCH__DOOR_STATUS->Set__DATA(STR__CLOSE);
	dCH__FOUP_CLAMP_STATUS->Set__DATA(STR__CLAMP);
	dCH__FOUP_POS_STATUS->Set__DATA(STR__UNLOAD);

	return 1;
}

// MAP -----
int  CObj__LPx_STD::
Call__MAP(CII_OBJECT__VARIABLE* p_variable,
		  CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"MAP ",sObject_Name,MB_OK|MB_TOPMOST);

	for(int i=0;i<CFG_LPx__SLOT_SIZE;i++)
	{
		sCH__SLOT_MAP_RESULT[i]->Set__DATA(STR__PRESENT);
	}
	return 1;
}

// CLAMP -----
int  CObj__LPx_STD::
Call__CLAMP(CII_OBJECT__VARIABLE* p_variable,
			CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"CLAMP ",sObject_Name,MB_OK|MB_TOPMOST);

	dCH__FOUP_CLAMP_STATUS->Set__DATA(STR__CLAMP);
	return 1;
}

// UNCLAMP -----
int  CObj__LPx_STD::
Call__UNCLAMP(CII_OBJECT__VARIABLE* p_variable,
			  CII_OBJECT__ALARM* p_alarm)
{
	MessageBox(NULL,"UNCLAMP ",sObject_Name,MB_OK|MB_TOPMOST);

	dCH__FOUP_CLAMP_STATUS->Set__DATA(STR__UNCLAMP);
	return 1;
}
