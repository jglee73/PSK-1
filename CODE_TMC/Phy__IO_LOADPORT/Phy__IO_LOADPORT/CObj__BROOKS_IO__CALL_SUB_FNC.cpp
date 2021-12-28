#include "StdAfx.h"
#include "CObj__BROOKS_IO.h"
#include "CObj__BROOKS_IO__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__BROOKS_IO::
Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;

	CString sMsg;
	CString str_log;
	CString fnc_name = "Fnc__INIT()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("INIT Starting ...");
	Fnc__APP_MSG(sMsg);
	
	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// Slot Init.
	if(dCH__CFG_INIT_SLOT_STATE_UNKNOWN->Check__DATA("YES") > 0)
	{
		for(int i=0; i<WAFER_SLOT_MAX; i++) 
		{
			dCH__LP_SLOT_STS[i]->Set__DATA("UNKNOWN");
		}
	}

	if(state > 0)
	{
		state = Seq_LAMP(LAMP_ALL, "OFF", "LAMP_ALL", "Fnc__INIT()");
	}

	if(state > 0)
	{
		Fnc__APP_LOG("1. Robot Arm Check !");
		state = IS_ROBOT_ARM_RETRACT(p_variable, p_alarm);
	}
	
	if(state > 0)
	{
		Fnc__APP_LOG("2. INIT Seq Start... !");
		state = Seq_INIT(p_variable, p_alarm, fnc_name);
	}

	if(state < 0)	sMsg = "INIT Failed..";
	else			sMsg = "INIT Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);
	
	return state;
}

int  CObj__BROOKS_IO::
Fnc__PREPLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	//.....
	int state = -1;

	CString sMsg;
	CString var_data;
	CString str_log;
	CString fnc_name = "Fnc__PREPLOAD()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("PREPLOAD Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	if(Is__ONLINE(p_variable, p_alarm) < 0)
	{
		sMsg = "PREPLOAD Failed..";
		Fnc__APP_MSG(sMsg);

		str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[-1]\n", str_caller, fnc_name);
		Fnc__APP_LOG(str_log);

		return -1;
	}

	// Wafer Exist 상태 초기화...
	for(int i=0; i<WAFER_SLOT_MAX; i++)  
	{
		dCH__LP_SLOT_STS[i]->Set__DATA("ABSENT");	// prepload이므로..
	}

	if((iSIM_FLAG > 0) && (Is__LP_AUTO_MODE() < 0))
	{
		diEXT_CH__LPx__FOUP_PRESENT->Set__DATA("ON");
		diEXT_CH__LPx__FOUP_PLACED->Set__DATA("ON");

		// Latch
		diEXT_CH__LPx__LATCH->Set__DATA("OFF");
		diEXT_CH__LPx__UNLATCH->Set__DATA("ON");

		// paddle
		diEXT_CH__LPx__DOOR_RET->Set__DATA("ON");
		diEXT_CH__LPx__DOOR_EXT->Set__DATA("OFF");

		//
		diEXT_CH__LPx__DOOR_UP->Set__DATA("ON");
		diEXT_CH__LPx__DOOR_DN->Set__DATA("OFF");

		// Shuttle
		diEXT_CH__LPx__SHUTTLE_IN->Set__DATA("OFF");
		diEXT_CH__LPx__SHUTTLE_OUT->Set__DATA("ON");

		if(dCH__OTR_OUT_MON_dLP_CLAMP_STS->Check__DATA("CLAMP") < 0)
		{
			if(dCH__INR_CFG_DYNAMIC_USE->Check__DATA("NO") > 0)
			{
				Fnc__APP_LOG("PrepLoad SimMode Waiting for button pushed... Clamp Box");
				if(IDOK == ::MessageBox(NULL, "Click  ""LOAD"" button if you want to clamp", sObject_Name, MB_TOPMOST | MB_SETFOREGROUND | MB_OK))
				{
					// Clamp
					//diEXT_CH__LPx__UNCLAMP_CLAMP->Set__DATA("ON");
					diEXT_CH__LPx__LOAD_BTN->Set__DATA("ON");
					Sleep(2000);
					diEXT_CH__LPx__LOAD_BTN->Set__DATA("OFF");
				}

			}
		}
	}

	// --------------
	do 
	{
		Sleep(200);

		if(Is__Abort(p_variable) > 0)
		{
			state = -1;
			Fnc__APP_LOG("Object Aborted...");
			break;
		}

		// Manual Mode
		if(Is__LP_AUTO_MODE() < 0)
		{
			// Foup Exist Check..
			if(dCH__OTR_OUT_MON_dLP_CST_STS->Check__DATA("EXIST") > 0)
			{
				// Dynamic Tracking Check...
				if(dCH__INR_CFG_DYNAMIC_USE->Check__DATA("YES") > 0)
				{
					state = Fnc__CLAMP(p_variable, p_alarm, fnc_name);
					if(state < 0)	Fnc__APP_LOG("CLAMP Failed..");
					
					break;
				}
				// Dynamic Tracking 아니면... Load Button Waiting !!
				else
				{
					Fnc__APP_LOG("Waiting for Clamp Status...");

					if(dCH__OTR_OUT_MON_dLP_CLAMP_STS->Check__DATA("CLAMP") > 0)
					{
						Fnc__APP_LOG("Clamp Completed...");
						state = 1;
						break;
					}
					/*
					if(diEXT_CH__LPx__LOAD_BTN->Check__DATA("ON") > 0)
					{
						state = Fnc__CLAMP(p_variable, p_alarm, fnc_name);
						if(state < 0)	Fnc__APP_LOG("CLAMP Failed..");
						
						break;
					}
					*/
				}
			}
		}
		// Auto Mode
		else
		{
			if( (dCH__OTR_OUT_MON_dLP_CST_STS->Check__DATA("EXIST") > 0) &&
				(dEXT_CH__PHY_LPx__PIO_RUN_SNS->Check__DATA("DONE") > 0) )
			{
				state = 1;
				Fnc__APP_LOG("AUTO MODE Foup Exist...state:1");
				break;
			}
		}

	} while(1);

	// --------------
	if(state < 0)	sMsg = "PREPLOAD Failed..";
	else			sMsg = "PREPLOAD Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);
	
	return state;
}

int  CObj__BROOKS_IO::
Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	// Msg Write !!
	CString fnc_name = "Fnc__LOAD()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	sMsg.Format("LOAD Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// 1. Clamp
	if(state > 0)	state = Fnc__CLAMP(p_variable, p_alarm, fnc_name);

	// 2. Retract Shuttle
	if(state > 0)	state = Fnc__RETRACTSHUTTLE(p_variable, p_alarm, fnc_name);

	// 3. Vac On
	if(state > 0)	state = Fnc__VACON(p_variable, p_alarm, fnc_name);

	// 4. Latch
	if(state > 0)	state = Fnc__LATCH(p_variable, p_alarm, fnc_name);

	// 5. Paddle Ext
	if(state > 0)	state = Fnc__EXTENDPADDLE(p_variable, p_alarm, fnc_name);

	// 6. Paddle Down
	if(state > 0)	state = Fnc__DOWNPADDLE(p_variable, p_alarm, fnc_name);

	if(state < 0)	sMsg = "LOAD Failed..";
	else			sMsg = "LOAD Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__DOCK_and_EXTEND(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	// Msg Write !!
	CString fnc_name = "Fnc__DOCK_and_EXTEND()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	sMsg.Format("DOCK and EXTEND Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// 1. Clamp
	if(state > 0)	state = Fnc__CLAMP(p_variable, p_alarm, fnc_name);

	// 2. Retract Shuttle
	if(state > 0)	state = Fnc__RETRACTSHUTTLE(p_variable, p_alarm, fnc_name);

	// 3. Vac On
	if(state > 0)	state = Fnc__VACON(p_variable, p_alarm, fnc_name);

	// 4. Latch
	if(state > 0)	state = Fnc__LATCH(p_variable, p_alarm, fnc_name);

	// 5. Paddle Ext
	if(state > 0)	state = Fnc__EXTENDPADDLE(p_variable, p_alarm, fnc_name);

	// 6. Paddle Down
	//if(state > 0)	state = Fnc__DOWNPADDLE(p_variable, p_alarm, fnc_name);

	if(state < 0)	sMsg = "DOCK and EXTEND Failed..";
	else			sMsg = "DOCK and EXTEND Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__UNLOAD()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	// Msg Write !!
	sMsg.Format("UNLOAD Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// 1. Paddle Up
	if(state > 0)	state = Fnc__UPPADDLE(p_variable, p_alarm, fnc_name);

	// 2. Paddle Ret
	if(state > 0)	state = Fnc__RETRACTPADDLE(p_variable, p_alarm, fnc_name);

	// 4. Unlatch
	if(state > 0)	state = Fnc__UNLATCH(p_variable, p_alarm, fnc_name);

	// 4. Vac Off
	if(state > 0)	state = Fnc__VACOFF(p_variable, p_alarm, fnc_name);

	// 5. Extract Shuttle
	if(state > 0)	state = Fnc__EXTENDSHUTTLE(p_variable, p_alarm, fnc_name);

	// 6. Unclamp
	if(state > 0)	state = Fnc__UNCLAMP(p_variable, p_alarm, fnc_name);

	if(state < 0)	sMsg = "UNLOAD CMD Failed..";
	else			sMsg = "UNLOAD CMD Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__RLSUNLOAD(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__RLSUNLOAD()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("RLSUNLOAD Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// 1. Paddle Up
	if(state > 0)	state = Fnc__UPPADDLE(p_variable, p_alarm, fnc_name);

	// 2. Paddle Ret
	if(state > 0)	state = Fnc__RETRACTPADDLE(p_variable, p_alarm, fnc_name);

	// 3. Vac Off
	if(state > 0)	state = Fnc__VACOFF(p_variable, p_alarm, fnc_name);

	// 4. Unlatch
	if(state > 0)	state = Fnc__UNLATCH(p_variable, p_alarm, fnc_name);

	// 5. Extend Shuttle
	if(state > 0)	state = Fnc__EXTENDSHUTTLE(p_variable, p_alarm, fnc_name);

	if(state < 0)	sMsg = "RLSUNLOAD Failed..";
	else			sMsg = "RLSUNLOAD Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__MAP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__MAP()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);
	
	// Msg Write !!
	sMsg.Format("MAP Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// do Mapping action..
// 	if(state > 0)
// 	{
// 		state = CMD_STAMP("ON", "MAP", doEXT_CH__LPx__MAP.Get__PTR(), 
// 								       diEXT_CH__LPx__MAP.Get__PTR(), p_alarm);
// 	}

	// Get Mapping Result..
	if(state > 0)
	{
		state = Fnc__MAP_RESULT(p_variable, p_alarm, fnc_name);
	}

	if(state < 0)	sMsg = "MAP Failed..";
	else			sMsg = "MAP Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__MAP_RESULT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__MAP_RESULT()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);


	// Msg Write !!
	sMsg.Format("MAP_RESULT Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// 2009, 6, 24 : Mapping Result 센서 IO가 없음.
	// To do below....
	
	if(iSIM_FLAG > 0)
	{
		state = 1;
		for (int i=0; i<WAFER_SLOT_MAX; i++)
		{
			dCH__LP_SLOT_STS[i]->Set__DATA("PRESENT");
		}
	}

	// ...
	if(state < 0)	sMsg = "MAP_RESULT Failed..";
	else			sMsg = "MAP_RESULT Completed..";
	
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__LATCH(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__LATCH()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("LATCH Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__UNLATCH->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "LATCH", doEXT_CH__LPx__LATCH.Get__PTR(), 
								         diEXT_CH__LPx__LATCH.Get__PTR(), p_alarm);
	}

	if((state > 0) && (iSIM_FLAG > 0))
	{
		// Latch
		diEXT_CH__LPx__LATCH->Set__DATA("ON");
		diEXT_CH__LPx__UNLATCH->Set__DATA("OFF");
	}

	if(state < 0)	sMsg = "LATCH Failed..";
	else			sMsg = "LATCH Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__UNLATCH(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__UNLATCH()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("UNLATCH Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__LATCH->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", 
						  "UNLATCH", 
						  doEXT_CH__LPx__UNLATCH.Get__PTR(), 
						  diEXT_CH__LPx__UNLATCH.Get__PTR(), 
						  p_alarm);
	}

	if((state > 0) && (iSIM_FLAG > 0))
	{
		// Latch
		diEXT_CH__LPx__LATCH->Set__DATA("OFF");
		diEXT_CH__LPx__UNLATCH->Set__DATA("ON");
	}

	if(state < 0)	sMsg = "UNLATCH Failed..";
	else			sMsg = "UNLATCH Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__RETRACTPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__RETRACTPADDLE()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("RETRACTPADDLE Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__DOOR_EXT->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "PADDLE_RET", doEXT_CH__LPx__DOOR_RET.Get__PTR(), 
											  diEXT_CH__LPx__DOOR_RET.Get__PTR(), p_alarm);
	}

	if((state > 0) && (iSIM_FLAG > 0))
	{
		// 
		diEXT_CH__LPx__DOOR_EXT->Set__DATA("OFF");
		diEXT_CH__LPx__DOOR_RET->Set__DATA("ON");
	}

	if(state < 0)	sMsg = "RETRACTPADDLE Failed..";
	else			sMsg = "RETRACTPADDLE Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__EXTENDPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__EXTENDPADDLE()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("EXTENDPADDLE Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__DOOR_RET->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "PADDLE_EXT", doEXT_CH__LPx__DOOR_EXT.Get__PTR(), 
											  diEXT_CH__LPx__DOOR_EXT.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__DOOR_EXT->Set__DATA("ON");
		diEXT_CH__LPx__DOOR_RET->Set__DATA("OFF");
	}

	if(state < 0)	sMsg = "EXTENDPADDLE Failed..";
	else			sMsg = "EXTENDPADDLE Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__UPPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__UPPADDLE()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("UPPADDLE Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// Interlock : Paddle이 Extend 되어 있어야 한다.
	if(state > 0)
	{
		if((diEXT_CH__LPx__DOOR_DN->Check__DATA("OFF") > 0)
	    && (diEXT_CH__LPx__DOOR_UP->Check__DATA("ON") > 0))
		{
			Fnc__APP_LOG("Already... Paddle Up Status..");
			return 1;
		}
		state = Is__Paddle_Up_Down_CND(p_variable, p_alarm);
	}
	
	if(state > 0)
	{
		state = Is__LP_CLOSE_CND(p_variable, p_alarm);
	}

	if(state > 0)
	{
		doEXT_CH__LPx__DOOR_DN->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "PADDLE_UP", doEXT_CH__LPx__DOOR_UP.Get__PTR(), 
								             diEXT_CH__LPx__DOOR_UP.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__DOOR_DN->Set__DATA("OFF");
		diEXT_CH__LPx__DOOR_UP->Set__DATA("ON");
	}

	if(state < 0)	sMsg = "UPPADDLE Failed..";
	else			sMsg = "UPPADDLE Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__DOWNPADDLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	CString sMsg;
	CString str_log;
	CString str_data;

	SCX__TIMER_CTRL xTimer;
	xTimer->REGISTER__ABORT_OBJECT(sObject_Name);

	// ...
	CString fnc_name = "Fnc__DOWNPADDLE()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("DOWNPADDLE Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);

	// Interlock : Paddle이 Extend 되어 있어야 한다.
	if(state > 0)
	{
		state = Is__Paddle_Up_Down_CND(p_variable, p_alarm);
	}

	if(state > 0)
	{
		doEXT_CH__LPx__DOOR_UP->Set__DATA("OFF");

		if(iSIM_FLAG > 0)
		{
			diEXT_CH__LPx__DOOR_UP->Set__DATA("OFF");
		}
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "PADDLE_DN", doEXT_CH__LPx__DOOR_DN.Get__PTR(), 
										     diEXT_CH__LPx__DOOR_DN.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__DOOR_DN->Set__DATA("ON");
		diEXT_CH__LPx__DOOR_UP->Set__DATA("OFF");
	}

	Fnc__APP_MSG("Delay.. Started");
	
	aCFG_PADDLE_DOWN_DELAY->Get__DATA(str_data);
	if(xTimer->WAIT(atof(str_data)) < 0)
	{
		return OBJ_ABORT;
	}

	Fnc__APP_LOG(str_log);

	if(state < 0)	sMsg = "DOWNPADDLE Failed..";
	else			sMsg = "DOWNPADDLE Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__EXTENDSHUTTLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	CString sMsg;
	CString str_log;

	// ...
	CString fnc_name = "Fnc__EXTENDSHUTTLE()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("EXTENDSHUTTLE Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	int state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__SHUTTLE_IN->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "SHUTTLE_OUT", doEXT_CH__LPx__SHUTTLE_OUT.Get__PTR(), 
											   diEXT_CH__LPx__SHUTTLE_OUT.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__SHUTTLE_IN->Set__DATA("OFF");
		diEXT_CH__LPx__SHUTTLE_OUT->Set__DATA("ON");
	}

	if(state < 0)	sMsg = "EXTENDSHUTTLE Failed..";
	else			sMsg = "EXTENDSHUTTLE Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__RETRACTSHUTTLE(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__RETRACTSHUTTLE()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("RETRACTSHUTTLE Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__SHUTTLE_OUT->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "SHUTTLE_IN", doEXT_CH__LPx__SHUTTLE_IN.Get__PTR(), 
											  diEXT_CH__LPx__SHUTTLE_IN.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__SHUTTLE_IN->Set__DATA("ON");
		diEXT_CH__LPx__SHUTTLE_OUT->Set__DATA("OFF");
	}

	if(state < 0)	sMsg = "RETRACTSHUTTLE Failed..";
	else			sMsg = "RETRACTSHUTTLE Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__VACON(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__VACON()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("VACON Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	// IO 1개로 제어.. 즉, ON 이면 VACON, OFF이면 VACOFF..
// 	if(state > 0)
// 	{
// 		state = CMD_STAMP("OFF", "VAC_OFF", doEXT_CH__LPx__DOOR_VAC.Get__PTR(), 
// 										    diEXT_CH__LPx__DOOR_VAC.Get__PTR(), p_alarm);
// 	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "VAC_ON", doEXT_CH__LPx__DOOR_VAC.Get__PTR(), 
										  diEXT_CH__LPx__DOOR_VAC.Get__PTR(), p_alarm);
	}

	if(dCFG__DOOR_CLOSE_VAC_ON_RECHECK->Check__DATA("TRUE") > 0)
	{
		diEXT_CH__LPx__DOOR_VAC->When__DATA("ON", 3);
	}
	
	if(state < 0)	sMsg = "VACON Failed..";
	else			sMsg = "VACON Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__VACOFF(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__VACOFF()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("VACOFF Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__DOOR_VAC->Set__DATA("OFF");
		// OFF센서가 들어왔더라도, 명령은 내보내야한다.
		// OFF센서가 들어온상태에서, VAC ON 동작은 계속 하고 있을수 있슴..
		state = CMD_STAMP("OFF", "VAC_OFF",  doEXT_CH__LPx__DOOR_VAC.Get__PTR(), 
										     diEXT_CH__LPx__DOOR_VAC.Get__PTR(), p_alarm);
	}

	// IO 1개로 제어.. 즉, ON 이면 VACON, OFF이면 VACOFF..
// 	if(state > 0)
// 	{
// 		state = CMD_STAMP("OFF", "VAC_OFF", doEXT_CH__LPx__DOOR_VAC.Get__PTR(), 
// 										    diEXT_CH__LPx__DOOR_VAC.Get__PTR(), p_alarm);
// 	}

	if(state < 0)	sMsg = "VACOFF Failed..";
	else			sMsg = "VACOFF Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__CLAMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__CLAMP()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("CLAMP Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__UNCLAMP->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "CLAMP", doEXT_CH__LPx__CLAMP.Get__PTR(), 
								         diEXT_CH__LPx__CLAMP.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__CLAMP->Set__DATA("ON");
		diEXT_CH__LPx__UNCLAMP->Set__DATA("OFF");
	}

	if(state < 0)	sMsg = "CLAMP Failed..";
	else			sMsg = "CLAMP Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__UNCLAMP(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__UNCLAMP()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("UNCLAMP Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)
	{
		doEXT_CH__LPx__CLAMP->Set__DATA("OFF");
	}

	if(state > 0)
	{
		state = CMD_STAMP("ON", "UNCLAMP", doEXT_CH__LPx__UNCLAMP.Get__PTR(), 
										   diEXT_CH__LPx__UNCLAMP.Get__PTR(), p_alarm);
	}

	if( (state > 0) && (iSIM_FLAG > 0) )
	{
		// 
		diEXT_CH__LPx__CLAMP->Set__DATA("OFF");
		diEXT_CH__LPx__UNCLAMP->Set__DATA("ON");
	}

	if(state < 0)	sMsg = "UNCLAMP Failed..";
	else			sMsg = "UNCLAMP Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__CLOSEDOOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__CLOSEDOOR()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("CLOSEDOOR Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	if(state > 0)	state = Fnc__UPPADDLE(p_variable, p_alarm, fnc_name);
	if(state > 0)	state = Fnc__RETRACTPADDLE(p_variable, p_alarm, fnc_name);
	
	if(state < 0)	sMsg = "CLOSEDOOR Failed..";
	else			sMsg = "CLOSEDOOR Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__OPENDOOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	int state = -1;
	CString sMsg;
	CString str_log;

	CString fnc_name = "Fnc__OPENDOOR()";

	str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
	Fnc__APP_LOG(str_log);

	// Msg Write !!
	sMsg.Format("OPENDOOR Starting ...");
	Fnc__APP_MSG(sMsg);

	// Check Online !!
	state = Is__ONLINE(p_variable, p_alarm);

	state = Fnc__UNLATCH(p_variable, p_alarm, fnc_name);

	if(state > 0)	state = Fnc__EXTENDPADDLE(p_variable, p_alarm, fnc_name);
	if(state > 0)	state = Fnc__DOWNPADDLE(p_variable, p_alarm, fnc_name);

	if(state < 0)	sMsg = "OPENDOOR Failed..";
	else			sMsg = "OPENDOOR Completed..";
	Fnc__APP_MSG(sMsg);

	str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
	Fnc__APP_LOG(str_log);

	return state;
}

int  CObj__BROOKS_IO::
Fnc__OPENDOOR_WITH_NO_UNLATCH(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const CString str_caller)
{
	// ...
	int state = -1;
	CString sMsg;
	CString str_log;
	
	CString fnc_name = "Fnc__OPENDOOR_WITH_NO_UNLATCH()";
	
	// ...
	{
		str_log.Format("---> From : [%s], CALL : [%s]", str_caller, fnc_name);
		Fnc__APP_LOG(str_log);
	
		sMsg.Format("OPENDOOR Starting ...");
		Fnc__APP_MSG(sMsg);
	}

	// ...
	{
		state = Is__ONLINE(p_variable, p_alarm);
	
		if(state > 0)	state = Fnc__EXTENDPADDLE(p_variable, p_alarm, fnc_name);
		if(state > 0)	state = Fnc__DOWNPADDLE(p_variable, p_alarm, fnc_name);
	
		if(state < 0)	sMsg = "OPENDOOR(No Unlatch) Failed..";
		else			sMsg = "OPENDOOR Completed..";
	
		Fnc__APP_MSG(sMsg);
	
		str_log.Format("<--- END : From : [%s], CALL : [%s], ret:[%d]\n", str_caller, fnc_name, state);
		Fnc__APP_LOG(str_log);
	}

	return state;
}
