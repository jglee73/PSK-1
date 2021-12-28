#include "StdAfx.h"
#include "CObj__BROOKS_IO.h"
#include "CObj__BROOKS_IO__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__BROOKS_IO::
Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__INIT()";

	int state = Fnc__INIT(p_variable, p_alarm, fnc_name);
	if(state > 0)
	{
		dCH__OTR_OUT_dLP_STATUS->Set__DATA("STANDBY");
	}

	dPIO_COMM_READY_STS->Set__DATA("READY");
	return state;
}

int  CObj__BROOKS_IO::
Call__PREPLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__PREPLOAD";

	return Fnc__PREPLOAD(p_variable, p_alarm, fnc_name);
}

int  CObj__BROOKS_IO::
Call__LOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state = -1;
	CString fnc_name = "Call__LOAD";
	CString str_var;

	SCX__TIMER_CTRL xTimer;
	xTimer->REGISTER__ABORT_OBJECT(sObject_Name);

	if(dCFG__BEFORE_LOAD_CST_CHECK->Check__DATA("TRUE") > 0)
	{
		state = Is__LOAD_CONDITION(p_variable, p_alarm);
	}
	else
	{
		state = 1;
	}

	// ...
	dCFG__LOAD_MODE->Get__DATA(str_var);

	if(str_var.CompareNoCase("MODE1") == 0)
	{
		if(state > 0)
		{
			state = Fnc__LOAD(p_variable, p_alarm, fnc_name);
		}
	}
	else
	{
		if(state > 0)
		{
			state = Fnc__DOCK_and_EXTEND(p_variable, p_alarm, fnc_name);
		}
	}

	if(state > 0)	
	{
		aCH__OTR_IN_CFG__LOAD_COMPT_DELAY_TIME->Get__DATA(str_var);

		if(xTimer->WAIT(atof(str_var)) < 0)		return OBJ_ABORT;
	}
	return state;	
}

int  CObj__BROOKS_IO::
Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	int state;
	CString cfg_option;
	CString var_data;
	CString sMsg;
	CString fnc_name = "Call__UNLOAD";

	// Msg Write !!
	{
		sMsg.Format("UNLOAD Starting ...");	
		Fnc__APP_MSG(sMsg);
	}

	dCH__INR_CFG_UNLD_CLAMP_OPT->Get__DATA(cfg_option);
	
	if(Is__LP_AUTO_MODE() > 0)
	{
		state = Fnc__RLSUNLOAD(p_variable, p_alarm, fnc_name);
	}
	else if((Is__LP_AUTO_MODE() < 0) 
	     && (cfg_option.CompareNoCase("Type1") == 0))
	{
		state = Fnc__RLSUNLOAD(p_variable, p_alarm, fnc_name);
	}
	else
	{
		state = Fnc__UNLOAD(p_variable, p_alarm, fnc_name);
	}

	// Foup이 제거되기를 기다리는 부분..
	{
		sMsg.Format("FOUP Removed Waiting ..."); 
		Fnc__APP_MSG(sMsg);
	}

	do 
	{
		Sleep(20);

		if(Is__Abort(p_variable) > 0)
		{
			state = -1;
			break;
		}

		// Manual Mode
		if(Is__LP_AUTO_MODE() < 0)
		{
			dCH__INR_CFG_UNLD_CLAMP_OPT->Get__DATA(cfg_option);
			
			if((iSIM_FLAG > 0) 
			&& (cfg_option.CompareNoCase("Type1") == 0))
			{
				if(IDOK == ::MessageBox(NULL, "Click  ""UNLOAD"" button if you want to unclamp !!", sObject_Name, MB_TOPMOST | MB_SETFOREGROUND | MB_OK))

				diEXT_CH__LPx__UNLOAD_BTN->Set__DATA("ON");
				Sleep(2000);
				diEXT_CH__LPx__UNLOAD_BTN->Set__DATA("OFF");
			}

			if(iSIM_FLAG > 0)
			{
				if(IDOK == ::MessageBox(NULL, "Click  ""OK"" button if you want to FOUP_REMOVE", sObject_Name, MB_TOPMOST | MB_SETFOREGROUND | MB_OK))
				{
					// Foup Status...
					diEXT_CH__LPx__FOUP_PRESENT->Set__DATA("OFF");
					diEXT_CH__LPx__FOUP_PLACED->Set__DATA("OFF");
					Sleep(500);		// Monitorning 부분과 Sync 위해..
				}
			}
		
			if(dCH__OTR_OUT_MON_dLP_CST_STS->Check__DATA("NONE") > 0)
			{
				state = 1;
				Fnc__APP_LOG("MANUAL MODE Foup removed...state:1");
				break;
			}
		}
		// Auto Mode
		else
		{
			// 1. PIO Signal... COMPT [ON]
			// 2. FOUP [NONE]
			if((dCH__OTR_OUT_MON_dLP_CST_STS->Check__DATA("NONE")  > 0) 
			&& (dEXT_CH__PHY_LPx__PIO_RUN_SNS->Check__DATA("DONE") > 0))
			{
				state = 1;
				Fnc__APP_LOG("AUTO MODE Foup removed...state:1");
				break;
			}
		}
	} 
	while(1);

	if(state > 0)
	{
		// Slot Init.
		for(int i=0; i<WAFER_SLOT_MAX; i++)  
		{
			dCH__LP_SLOT_STS[i]->Set__DATA("UNKNOWN");
		}
	}

	if(state < 0)
	{
		sMsg = "UNLOAD Failed..";
	}
	else
	{
		sMsg = "UNLOAD Completed..";
	}
	
	Fnc__APP_MSG(sMsg);
	
	return state;
}

int  CObj__BROOKS_IO::
Call__RLSUNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call_RLSUNLOAD()";
	return Fnc__RLSUNLOAD(p_variable, p_alarm, fnc_name);	
}

int  CObj__BROOKS_IO::
Call__MAP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__MAP()";
	return Fnc__MAP(p_variable, p_alarm, fnc_name);	
}

int  CObj__BROOKS_IO::
Call__LATCH(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__LATCH()";
	return Fnc__LATCH(p_variable, p_alarm, fnc_name);
}

int  CObj__BROOKS_IO::
Call__UNLATCH(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__UNLATCH()";
	return Fnc__UNLATCH(p_variable, p_alarm, fnc_name);
}

int  CObj__BROOKS_IO::
Call__RETRACTPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__RETRACTPADDLE()";
	return Fnc__RETRACTPADDLE(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__EXTENDPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__EXTENDPADDLE()";
	return Fnc__EXTENDPADDLE(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__UPPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__UPPADDLE()";
	return Fnc__UPPADDLE(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__DOWNPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__DOWNPADDLE()";
	return Fnc__DOWNPADDLE(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__EXTENDSHUTTLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__EXTENDSHUTTLE()";
	return Fnc__EXTENDSHUTTLE(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__RETRACTSHUTTLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__RETRACTSHUTTLE()";
	return Fnc__RETRACTSHUTTLE(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__VACON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__VACON()";
	return Fnc__VACON(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__VACOFF(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__VACOFF()";
	return Fnc__VACOFF(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__CLAMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__CLAMP()";
	return Fnc__CLAMP(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__UNCLAMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__UNCLAMP()";
	return Fnc__UNCLAMP(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__CLOSEDOOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__CLOSEDOOR()";
	return Fnc__CLOSEDOOR(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__OPENDOOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__OPENDOOR()";
	return Fnc__OPENDOOR(p_variable, p_alarm,fnc_name);
}

int  CObj__BROOKS_IO::
Call__OPENDOOR_WITH_NO_UNLATCH(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString fnc_name = "Call__OPENDOOR_WITH_NO_UNLATCH()";
	return Fnc__OPENDOOR_WITH_NO_UNLATCH(p_variable, p_alarm,fnc_name);
}
