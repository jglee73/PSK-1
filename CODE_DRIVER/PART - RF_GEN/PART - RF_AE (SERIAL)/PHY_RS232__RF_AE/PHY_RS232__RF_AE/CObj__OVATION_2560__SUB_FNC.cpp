#include "StdAfx.h"
#include "CObj__OVATION_2560.h"
#include <math.h>


int CObj__OVATION_2560
::Seq__RAMP_UPDOWN(CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;
	double  dbCfg_Rf_On_Timeout = 1.0;
	double	dbRamp_msec_to_sec = 1.0;

	// ... FOR Set Command Delay
	// ... Forward / Reflect Reading Hold ...
	dCH__MONITOR_FLAG->Set__DATA("Off");

	// 1. RF Ramp SET
	aCH__RAMP_TIME->Get__DATA(str_data);					// msec
	dbRamp_msec_to_sec = atof(str_data);
	dbRamp_msec_to_sec = dbRamp_msec_to_sec * 0.001;		// sec

	aoCH__RampUp_Time->Set__VALUE(dbRamp_msec_to_sec);		// sec
	aoCH__RampDown_Time->Set__VALUE(dbRamp_msec_to_sec);	// sec

	// 2. RF Power SET
	aCH__SET_POWER->Get__DATA(str_data);
	aoCH__SetPower->Set__DATA(str_data);

	// 3. RF Power ON
	//if(dEXT_CH__RF_ON_SENSOR->Check__DATA("Off") > 0)
	if(vdiCH__RFOutput_Power->Check__DATA("Off") > 0)
	{
		doCH__RF_CMD->Set__DATA("On");
		//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("On");
	}

	// ... Forward / Reflect Reading Start ...
	dCH__MONITOR_FLAG->Set__DATA("On");

	// ... Simulator Code ...
	if(IsSimulation() > 0)
	{
		//dEXT_CH__RF_ON_SENSOR->Set__DATA("On");
		vdiCH__RFOutput_Power->Set__DATA("On");
	}

	// ... RF On Timeout Check ...
	aCH__RF_ON_TIMEOUT->Get__DATA(str_data);
	dbCfg_Rf_On_Timeout = atof(str_data);

	if(dbCfg_Rf_On_Timeout <= 0)
	{
		dbCfg_Rf_On_Timeout = 1.0;
	}

	//if(dEXT_CH__RF_ON_SENSOR->When__DATA("On", dbCfg_Rf_On_Timeout) < 0)
	if(vdiCH__RFOutput_Power->When__DATA("On", dbCfg_Rf_On_Timeout) < 0)
	{
		doCH__RF_CMD->Set__DATA("Off");
		//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("Off");

		int alarmid = ALID__RF_ON_TIMEOUT_ALARM;
		Alarm__CHECK_POST(p_alarm, "", alarmid);
		return OBJ_ABORT;
	}

	if(IsSimulation() > 0)
	{
		aoCH__SetPower->Get__DATA(str_data);
		aiCH__ForwardPower->Set__DATA(str_data);
	}
	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::Seq__RAMP_UPDOWN_Ex(CII_OBJECT__VARIABLE *p_variable, 
					  CII_OBJECT__ALARM *p_alarm, 
					  const CString str_mode)
{
	CString str_data;
	double  dbCfg_Rf_On_Timeout = 1.0;
	double	dbRamp_msec_to_sec = 1.0;

	double dbRamp_Time;
	double dbPower_Set;
	double dbstep_set_val;
	double db_unit_val;
	double db_current_set_val;
	double db_different_set_val;

	SCX__TIMER_CTRL xTimer;
	xTimer->REGISTER__ABORT_OBJECT(sObject_Name);

	// ... FOR Set Command Delay
	// ... Forward / Reflect Reading Hold ...
	dCH__MONITOR_FLAG->Set__DATA("Off");

	Fnc__WRITE_APP_LOG("Seq__RAMP_UPDOWN_Ex --> Start");

	// 1. RF Ramp SET Read..
	aCH__RAMP_TIME->Get__DATA(str_data);					// msec
	dbRamp_Time = atof(str_data);
	
	// 2. RF Power SET Read..
	aCH__SET_POWER->Get__DATA(str_data);
	dbPower_Set = atof(str_data);

	aoCH__SetPower->Get__DATA(str_data); // power set


	db_current_set_val = atof(str_data);

	db_different_set_val = dbPower_Set - db_current_set_val;

	Fnc__WRITE_APP_LOG("Set Power Val:%f w, Ramp Time:%f msec", dbPower_Set, dbRamp_Time);

	if(str_mode.CompareNoCase("RF_OFF") == 0)
	{
		dbRamp_msec_to_sec = dbRamp_Time * 0.001;		// sec
		db_unit_val = dbPower_Set / dbRamp_msec_to_sec;	// 100/2 초.. = 50
		
		dbPower_Set = 1;
		db_different_set_val = -1;	// while타고, ramp down위해..

		aiCH__ForwardPower->Get__DATA(str_data);
	
		if(atof(str_data) < 0.1)
		{
			Fnc__WRITE_APP_LOG("Already RF Off Status..Fwd Val:%s", str_data);
			return OBJ_AVAILABLE;			// 1 watt이하이면 RF Off로 간주..
		}
	}
	else if( (dbPower_Set > 0) && (dbRamp_Time > 0) )
	{
		dbRamp_msec_to_sec = dbRamp_Time * 0.001;							// sec
		db_unit_val = fabs(db_different_set_val) / dbRamp_msec_to_sec;		// 100/2 초.. = 50
	}
	else
	{
		db_unit_val = dbPower_Set;
	}
	
	// 3. RF Power SET
	if( (db_different_set_val != 0) 
	&&  (dbPower_Set > 0) 
	&&	(dbRamp_Time > 0))
	{
		if(str_mode.CompareNoCase("RF_ON") == 0)
		{
		
			//aoCH__SetPower->Set__VALUE(dbPower_Set);
			doCH__RF_CMD->Set__DATA("On");		// RF On
			//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("On");
		}

		while (1)
		{
			if(db_different_set_val > 0)	// Ramp Up
			{
				dbstep_set_val = db_current_set_val + db_unit_val;
			}
			else							// Ramp Down
			{
				dbstep_set_val = db_current_set_val - db_unit_val;
			}
			//aoCH__SetPower->Set__VALUE(dbstep_set_val);

			db_current_set_val = dbstep_set_val;
			dbRamp_msec_to_sec--;

			Fnc__WRITE_APP_LOG("unit_val:%f, step_set:%f, sec:%f", 
								db_unit_val, 
								dbstep_set_val, 
								dbRamp_msec_to_sec);

			if(dbRamp_msec_to_sec <= 0)
			{
				break;
			}

			if(p_variable->Check__CTRL_ABORT() > 0)
			{
				return OBJ_ABORT;
			}

			//Sleep(1000);
		}
		//doCH__RF_CMD->Set__DATA("On");		// RF On
	}

	//aoCH__SetPower->Set__VALUE(dbPower_Set);
	
	if(str_mode.CompareNoCase("RF_ON") == 0)
	{
		// ... Forward / Reflect Reading Start ...
		dCH__MONITOR_FLAG->Set__DATA("On");

		// ... Simulator Code ...
		if(IsSimulation() > 0)
		{
			doCH__RF_CMD->Set__DATA("On");
			//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("On");
			//dEXT_CH__RF_ON_SENSOR->Set__DATA("On");
			vdiCH__RFOutput_Power->Set__DATA("On");
			aCH__FWD_Power->Set__VALUE(dbPower_Set);	//2018.11.06 @pck Add
		}

		// ... RF On Timeout Check ...
		aCH__RF_ON_TIMEOUT->Get__DATA(str_data);
		dbCfg_Rf_On_Timeout = atof(str_data);

		if(dbCfg_Rf_On_Timeout <= 0)
		{
			dbCfg_Rf_On_Timeout = 1.0;
		}

		do 
		{
			aCH__FWD_Power->Get__DATA(str_data);
			if(atof(str_data) > 5)	
			{
				break;			// 5 kwatt이상이면 RF On으로 간주..
			}

			if(xTimer->WAIT(1.0) < 0)
			{
				doCH__RF_CMD->Set__DATA("Off");
				//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("Off");
				return OBJ_ABORT;
			}
		} 
		while(dbCfg_Rf_On_Timeout-- > 0);

		if(dbCfg_Rf_On_Timeout <= 0)
		{
			doCH__RF_CMD->Set__DATA("Off");
			//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("Off");

 			int alarmid = ALID__RF_ON_TIMEOUT_ALARM;
 			Alarm__CHECK_POST(p_alarm, "", alarmid);
 			return OBJ_ABORT;
		}

		if(IsSimulation() > 0)
		{
			aoCH__SetPower->Get__DATA(str_data);
			aiCH__ForwardPower->Set__DATA(str_data);
		}
	}
	else
	{
		// 4. RF Power OFF
		if(Fnc__doSTOP(p_alarm) < 0)
		{
			return OBJ_ABORT;
		}
	}

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::FNC__PROC_SEQ(CII_OBJECT__VARIABLE*	p_variable,
			  CII_OBJECT__ALARM*		p_alarm)
{
	CString str_data;
	double  dbCfg_Rf_On_Timeout = 1.0;
	double	dbRamp_msec_to_sec = 1.0;

	double dbRamp_Time;
	double dbPower_Set;
	double dbstep_set_val;
	double db_unit_val;
	double db_current_set_val;
	double db_different_set_val;

	CString trg_value;
	CString cur_mode_sel;

	CString log_msg;
	int		flag = -1;

	aCH__SET_POWER->Get__DATA(str_data);
	dbPower_Set = atoi(str_data);
	dCH__MONITOR_FLAG->Set__DATA("Off");

pwr_off :
		flag = doCH__RF_CMD->Set__DATA("OFF");
		dCH__MONITOR_FLAG->Set__DATA("Off");
		if (flag < 0)
		{	// 2018.12.12 @pck
			// 연속 step에서 RF Set할 경우, 이어지는 step에서 RF On을 감지하지 못하고 Alarm 발생 됨.,,,,,,,,,다른 Alarm방법을 찾아야 함.
			//flag = -1;
			//dCH__MONITOR_FLAG->Set__DATA("Off");
			//CString r_act;
			//p_alarm->Popup__ALARM_With_MESSAGE(ALID__RF_ON_TIMEOUT_ALARM, "RF_CMD_ON_NG", r_act);

			//if (r_act.CompareNoCase("RETRY") == 0)
			//{
			//	Fnc__WRITE_APP_LOG("goto_Retry\n");
			//	goto pwr_off;
			//}
			//dCH__RF_CMD->Set__DATA("OFF");
			//log_msg = "SUB_FNC : RF_CMD_ON_NG\n";
			//Fnc__WRITE_APP_LOG(log_msg);

			//return flag;
		}
		else
		{
			dCH__RF_CMD->Set__DATA("OFF");
			Fnc__WRITE_APP_LOG("SUB_FNC : RF_CMD_OFF");
		}

pwr_set :
	flag = aoCH__SetPower->Set__DATA(str_data);

	if (flag < 0) // Voltage Set
	{
		CString r_act;
		p_alarm->Popup__ALARM_With_MESSAGE(ALID__SEND_COMMAND_FAIL, "PWR_SETPOINT_NG", r_act);

		if (r_act.CompareNoCase("RETRY") == 0)
		{
			Fnc__WRITE_APP_LOG("goto_Retry\n");
			goto pwr_set;
		}
		log_msg = "SUB_FNC : PWR_SETPOINT_NG\n";
		Fnc__WRITE_APP_LOG(log_msg);

		return flag;
	}
	else
	{
		Fnc__WRITE_APP_LOG("SUB_FNC : PWR_SETPOINT");
	}

pwr_on :
	if (dbPower_Set <= 0)
	{
		Fnc__WRITE_APP_LOG("FNC__PROC_SEQ - SetPower is '0'");
		return 1;
	}
	else
	{
		flag = doCH__RF_CMD->Set__DATA("ON");
		dCH__MONITOR_FLAG->Set__DATA("On");
		if (flag < 0)
		{	// 2018.12.12 @pck
			// 연속 step에서 RF Set할 경우, 이어지는 step에서 RF On을 감지하지 못하고 Alarm 발생 됨.,,,,,,,,,다른 Alarm방법을 찾아야 함.
			//flag = -1;
			//dCH__MONITOR_FLAG->Set__DATA("Off");
			//CString r_act;
			//p_alarm->Popup__ALARM_With_MESSAGE(ALID__RF_ON_TIMEOUT_ALARM, "RF_CMD_ON_NG", r_act);

			//if (r_act.CompareNoCase("RETRY") == 0)
			//{
			//	Fnc__WRITE_APP_LOG("goto_Retry\n");
			//	goto pwr_on;
			//}
			//dCH__RF_CMD->Set__DATA("OFF");
			//log_msg = "SUB_FNC : RF_CMD_ON_NG\n";
			//Fnc__WRITE_APP_LOG(log_msg);

			//return flag;
		}
		else
		{
			dCH__RF_CMD->Set__DATA("ON");
			Fnc__WRITE_APP_LOG("SUB_FNC : RF_CMD_ON");
		}
	}

	return flag;
}

int CObj__OVATION_2560
::FNC__PULSING_SEQ(CII_OBJECT__VARIABLE*	p_variable,
				   CII_OBJECT__ALARM*		p_alarm)
{
	Fnc__WRITE_APP_LOG("FNC__PULSING_SEQ_START");
	CString str_data;
	CString Ps_Frequency;
	CString Ps_Duty;

	aCH__Ps_Frequency_Set->Get__DATA(Ps_Frequency);
	aCH__Ps_Duty_Set->Get__DATA(Ps_Duty);

	RF_Ps_Request = RF_Ps_Enable;
	if ((diCH__Pulsing_Status->Get__DATA(str_data)) < 0) // Disable / Enable
	{
		Fnc__WRITE_APP_LOG("Pulsing_Status_Reading_NG");
		return -1;
	}

	Fnc__WRITE_LOG("RF_Ps_state[%d], [%s]", RF_Ps_state, str_data);

	if		(RF_Ps_state <= 0) // (str_data.CompareNoCase("Disable") == 0)
	{
		if ((doCH__Pulsing_Mode_Set->Set__DATA("Enable")) < 0)
		{
			Fnc__WRITE_APP_LOG("Pulsing_Enable_Setting_NG");
			return -1;
		}
	}
	
	if		(RF_Ps_state == 1) // (str_data.CompareNoCase("Enable") == 0)
	{
		//if (aoCH__Ps_Frequency_Set->Set__DATA(str_data) < 0)	return -1;	// Pulsing Frequency Set
		//if (aoCH__Ps_Duty_Set->Set__DATA(str_data) < 0)			return -1;	// Pulsing Duty Set
	}
	else if (RF_Ps_state == 0)
	{
		Fnc__WRITE_APP_LOG("Pulsing Mode Not Enabled");
		return -1;
	}
	
	Fnc__WRITE_APP_LOG("FNC__PULSING_SEQ_END");
	return 1;
}

int CObj__OVATION_2560
::FNC__PULSING_INIT_SEQ(CII_OBJECT__VARIABLE*	p_variable,
						CII_OBJECT__ALARM*		p_alarm)
{
	Fnc__WRITE_APP_LOG("FNC__PULSING_INIT_SEQ_START");
	int flag;
	CString str_data;
	CString Ps_Frequency;
	CString Ps_Duty;

	// ... NVRAM Enable : 비휘발성 모드로 Memory Mode Set
	RF_Ps_Request = RF_Ps_Memory;
	if (doCH__Pulsing_Mode_Set->Set__DATA("Enable") < 0)
	{
		flag = -21;
		Fnc__WRITE_APP_LOG("FNC__PULSING_INIT_SEQ_NG - memory mode set");
		return flag;
	}

	Sleep(500);

	// ... PULSING Mode Enable : Pulsing Mode Enable Set
	RF_Ps_Request = RF_Ps_Mode;
	if (doCH__Pulsing_Mode_Set->Set__DATA("Pulsing") < 0);	// 0: Pulsing and Arc Disable(Standard), 1: Pulsing Enable, 2: Arc Enable
	{
		flag = -22;
		Fnc__WRITE_APP_LOG("FNC__PULSING_INIT_SEQ_NG - pulsing mode set");
		return flag;
	}

	Sleep(1000);

	// ... Explicit Mode Enable : Explicit Mode Enable Set //Explicit : Generator Parameter에 User접근 허용
	RF_Ps_Request = RF_Ps_Explicit;
	if (doCH__Pulsing_Mode_Set->Set__DATA("Enable") < 0);
	{
		flag = -23;
		Fnc__WRITE_APP_LOG("FNC__PULSING_INIT_SEQ_NG - Explicit mode set");
		return flag;
	}

	Sleep(500);

	// ... PULSING Off : Pulsing Off Set
	RF_Ps_Request = RF_Ps_Enable;
	if (doCH__Pulsing_Mode_Set->Set__DATA("Disable") < 0);
	{
		flag = -24;
		Fnc__WRITE_APP_LOG("FNC__PULSING_INIT_SEQ_NG - Pulsing Off set");
		return flag;
	}

	Fnc__WRITE_APP_LOG("FNC__PULSING_INIT_SEQ_END");
	return 1;
}

int CObj__OVATION_2560
::Fnc__doSTOP(CII_OBJECT__ALARM *p_alarm)
{
	// ... FOR Set Command Delay
	// ... Forward / Reflect Reading Hold ...

	doCH__RF_CMD->Set__DATA("Off");
	dCH__MONITOR_FLAG->Set__DATA("Off");

	aCH__SET_POWER->Set__DATA("0");
	aoCH__SetPower->Set__DATA("0");
	//dEXT_CH__RF_ALIVE_INTLK->Set__DATA("Off");

	// ... Forward / Reflect Reading Start ...
	dCH__MONITOR_FLAG->Set__DATA("On");

	// ... Simulator Code ...
	if(IsSimulation() > 0)
	{
		vdiCH__RFOutput_Power->Set__DATA("Off");
		aCH__SET_POWER->Set__DATA("0");
	}

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::CheckRemote(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(doCH__CONTROL_MODE->Check__DATA("Remote") > 0)
	{
		return OBJ_AVAILABLE;
	}

	Sleep(500);
	
	if(doCH__CONTROL_MODE->Check__DATA("Remote") > 0)
	{
		return OBJ_AVAILABLE;
	}

	// ...
	int alarm_id = ALID__REMOTE_ALARM;
	Alarm__CHECK_POST(p_alarm, "", alarm_id);	
	return OBJ_ABORT;
}

int CObj__OVATION_2560
::Fnc__DEFAULT_CONFIG_SET(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString var_data;
	double	ramp_time = 0;

	// 1. RF Ramp SET
	aCH__RAMP_TIME->Get__DATA(var_data);
	ramp_time = atof(var_data);			;	// sec

	if(ramp_time > 0)
	{
		vdoCH__Ramp_Mode->Set__DATA("Timed");

		aoCH__RampUp_Time->Set__VALUE(ramp_time);
		aoCH__RampDown_Time->Set__VALUE(ramp_time);
		Fnc__WRITE_APP_LOG("[Default] RF Power Ramping Enable. Time: %f", ramp_time);
	}
	else
	{
		vdoCH__Ramp_Mode->Set__DATA("Disable");

		//aoCH__RampUp_Time->Set__VALUE(1000.0);	// default
		//aoCH__RampDown_Time->Set__VALUE(1000.0);
		aoCH__RampUp_Time->Set__VALUE(100.0);	// default
		aoCH__RampDown_Time->Set__VALUE(100.0);

		Fnc__WRITE_APP_LOG("[Default] RF Power Ramping Disable.");
	}

	// 2. RF Start Frequency SET
	aCH__SET_START_FREQUENCY->Get__DATA(var_data);					// KHz
	aoCH__Start_Freq->Set__DATA(var_data);							// KHz
	Fnc__WRITE_APP_LOG("[Default] Set Start Frequency: %s kHz", var_data);

	// 3. RF Output Power Frequency SET
	aCH__SET_OUTPUT_FREQUENCY->Get__DATA(var_data);					// KHz
	aoCH__RF_Freq->Set__DATA(var_data);								// KHz
	Fnc__WRITE_APP_LOG("[Default] Set Output Power Frequency: %s kHz", var_data);

	// 4. Frequency Tune Delay SET
	aCH__FREQ_TUNE_DELAY->Get__DATA(var_data);					// "msec", 0, 100, 10000
	aoCH__Tune_Delay->Set__DATA(var_data);						// "msec", 0, 100, 10000
	Fnc__WRITE_APP_LOG("[Default] Set Frequency Tune Delay: %s msec", var_data);

	return OBJ_AVAILABLE;
}

int  CObj__OVATION_2560
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	CString r_act;
	
	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);

	if(r_act.CompareNoCase("RETRY") == 0)
	{
		return OBJ_RETRY;
	}	
	return OBJ_ABORT;
}
int  CObj__OVATION_2560
::Alarm__CHECK_POST(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id)
{
	CString r_act;
	
	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);
	
	return OBJ_ABORT;
}
int CObj__OVATION_2560
::HexToDecimal(CString str_dec)
{
	int     i, limit, value;
	CString string;
	char    ch, str_ch[2];
	
	string = str_dec;
	string.MakeUpper();
	limit = string.GetLength();
	value = 0;
	str_ch[1] = 0;
	
	for(i=0; i<limit; i++)
	{
		if(i > 0)
		{
			value *= 16;
		}
		
		ch = string.GetAt(i);
		str_ch[0] = ch;
		
			 if(((ch >= '0')&&(ch <= '9')))		value += atoi(str_ch);
		else if(ch == 'A')						value += 10;
		else if(ch == 'B')						value += 11;
		else if(ch == 'C')						value += 12;
		else if(ch == 'D')						value += 13;
		else if(ch == 'E')						value += 14;
		else if(ch == 'F')						value += 15;		
	}
	
	return value;
}

int CObj__OVATION_2560
::DecimalToBinary(int dec, CString &string)
{
	static char s[32 + 1] = { '0', };
	int count = 32;
	
	do 
	{
		s[--count] = '0' + (char) (dec & 1);
		dec = dec >> 1;
	} 
	while (count);
	
	string.Format("%s", s);
	return 1;
}

void CObj__OVATION_2560
::Fnc__WRITE_LOG(const char *fmt, ...)
{
	if(dCH__DRV_LOG_PARAM_START_STOP->Check__DATA("STOP") > 0)	
	{
		return;
	}

	// ...
	CString str_msg;
	va_list args;

	va_start(args, fmt);
	str_msg.FormatV(fmt, args);
	va_end(args);

	xLOG_CTRL->WRITE__LOG(str_msg);
}

void CObj__OVATION_2560
::Fnc__WRITE_APP_LOG( const char *fmt, ... )
{
	CString str_msg;	
	va_list args;
	
	va_start(args, fmt);
	str_msg.FormatV(fmt, args);
	va_end(args);
	
	CString log_msg;
	log_msg.Format("[%s]: %s\n", sObject_Name, str_msg);

	xAPP_LOG_CTRL->WRITE__LOG(log_msg);
}

int CObj__OVATION_2560
::IsSimulation()
{
	if(xSEQ_INFO->Is__SIMULATION_MODE() > 0)		return  1;
	return -1;
}

int CObj__OVATION_2560
::CheckOnline(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(IsSimulation() > 0)
	{
		diCH__COMM_STS->Set__DATA("Online");
	}

	if(diCH__COMM_STS->Check__DATA("Online") > 0)
	{
		return OBJ_AVAILABLE;
	}

	//Sleep(500);

	if(diCH__COMM_STS->Check__DATA("Online") > 0)
	{
		return OBJ_AVAILABLE;
	}

	// ...
	int alarm_id = ALID__OFFLINE_ALARM;
	Alarm__CHECK_POST(p_alarm, "", alarm_id);

	return OBJ_ABORT;
}

int CObj__OVATION_2560
::CheckRFContactor(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	return 1;

	/*
	if(IsSimulation() > 0)
	{
		dEXT_CH__RF_CONTACTOR->Set__DATA("Enable");
	}

	if(dEXT_CH__RF_CONTACTOR->Check__DATA("Enable") > 0)
	{
		return OBJ_AVAILABLE;
	}

	// ...
	int alarmid = ALID__RF_CONTACTOR_ALARM;
	Alarm__CHECK_POST(p_alarm, "", alarmid);

	return OBJ_ABORT;
	*/
}

int CObj__OVATION_2560
::CheckRFInterlock(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	if(IsSimulation() > 0)
	{
		//dEXT_CH__RF_INTLK_SNS->Set__DATA("True");
		//dEXT_CH__RF_WATER_SNS->Set__DATA("On");
		//dEXT_CH__RF_OVERTEMP_SNS->Set__DATA("Normal");
		vdiCH__Interlock_Open->Set__DATA("Open");
		vdiCH__ColdPlate_OverTemp_Fault->Set__DATA("Normal");
	}

	//if(dEXT_CH__RF_OVERTIME_SNS->Check__DATA("On") < 0)
	if(vdiCH__ColdPlate_OverTemp_Fault->Check__DATA("Normal") < 0)
	{
		int alarmid = ALID__RF_OVERTIME_ALARM;
		Alarm__CHECK_POST(p_alarm, "", alarmid);

		return OBJ_ABORT;
	}

	//if(dEXT_CH__RF_INTLK_SNS->Check__DATA("True") < 0)
	if(vdiCH__Interlock_Open->Check__DATA("Closed") < 0)
	{
		int alarmid = ALID__RF_INTERLOCK_ALARM;
		Alarm__CHECK_POST(p_alarm, "", alarmid);

		return OBJ_ABORT;
	}

	//if(dEXT_CH__RF_OVERTEMP_SNS->Check__DATA("Normal") < 0)
	if(vdiCH__ColdPlate_OverTemp_Fault->Check__DATA("Normal") < 0)
	{
		int alarmid = ALID__RF_OVERTEMP_ALARM;
		Alarm__CHECK_POST(p_alarm, "", alarmid);

		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

unsigned char CObj__OVATION_2560
::Check_Sum(unsigned char *bufferData, int Count)
{
	CString msg;
	CString buf;

	unsigned char Buffer=0x00;
	int ByteCount;
	
	for( ByteCount=0 ; ByteCount<Count ; ByteCount++)
	{
		Buffer^= bufferData[ByteCount];
	
		buf.Format("%02X ", bufferData[ByteCount]);
		msg = msg + buf;
	}

	return Buffer;
}

int CObj__OVATION_2560
::Chk_CSR_CODE(UCHAR csr_code)
{
	CString str_data;

	int n_csr_num = csr_code;
	str_data.Format("%d", n_csr_num);
	sCH__CSR_CODE_NUM->Set__DATA(str_data);		// Command 에 대한 Response...
	
	switch(n_csr_num)
	{
		case 0:
			Fnc__WRITE_LOG("Command accepted.");
			break;
		case 1:
			Fnc__WRITE_LOG("Unit is in the wrong control mode.");
			break;
		case 2:
			Fnc__WRITE_LOG("Output is on, change not allowed.");
			break;
		case 3:
			Fnc__WRITE_LOG("Output is off, change not allowed.");
			break;
		case 4:
			Fnc__WRITE_LOG("Data is out of range.");
			break;
		case 5:
			Fnc__WRITE_LOG("User port off signal is active.");
			break;
		case 6:
			Fnc__WRITE_LOG("Program source is incorrect");
			break;
		case 7:
			Fnc__WRITE_LOG("Oner or more faults are active in the unit.");
			break;
		case 8:
			Fnc__WRITE_LOG("Set point ramp is active.");
			break;
		case 9:
			Fnc__WRITE_LOG("Data byte count is incorrect.");
			break;
		case 10:
			Fnc__WRITE_LOG("User port has priority.");
			break;
		case 11:
			Fnc__WRITE_LOG("Busy is not ready.");
			break;
		case 12:
			Fnc__WRITE_LOG("This feature is not available on your unit.");
			break;
		case 16:
			Fnc__WRITE_LOG("Target life has been consumed.");
			break;
		case 17:
			Fnc__WRITE_LOG("Output OFF timer active (minimum off time is 50 ms).");
			break;
		case 19:
			Fnc__WRITE_LOG("Recipe is active(change not allowed).");
			break;
		case 21:
			Fnc__WRITE_LOG("Joule set point has not been reached.");
			break;
		case 25:
			Fnc__WRITE_LOG("Unit is configured as a slave.");
			break;
		case 28:
			Fnc__WRITE_LOG("Set point exceeds user limit.");
			break;
		case 29:
			Fnc__WRITE_LOG("Regulation mode is locked (you cannot switch between regulation modes while output power is on).");
			break;
		case 31:
			Fnc__WRITE_LOG("The User port is active (you muset de-assert the reset line on the User port).");
			break;
		case 33:
			Fnc__WRITE_LOG("Pulsing disabled (frequency = 0).");
			break;
		case 34:
			Fnc__WRITE_LOG("Unit is a Sync Pulse receiver.");
			break;
		case 36:
			Fnc__WRITE_LOG("User set point out of range.");
			break;
		case 99:
			Fnc__WRITE_LOG("Command not accepted (there is no such command).");
			break;
		default:
			Fnc__WRITE_LOG("Unknown CSR Code[%d]", n_csr_num);
	}

	return n_csr_num;
}
