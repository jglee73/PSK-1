#include "StdAfx.h"
#include "CObj__OVATION_2560.h"


int CObj__OVATION_2560
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;

	// 0. RF Power Off
	Fnc__doSTOP(p_alarm);

	// 1. Remote Mode Change
	if(doCH__CONTROL_MODE->Set__DATA("Remote") < 0)
	{
		int alarm_id = ALID__SEND_COMMAND_FAIL;
		CString msg;
		
		msg.Format("Send Command Failed (Remote)");

		Alarm__CHECK_POST(p_alarm, msg, alarm_id);
		return OBJ_ABORT;
	}

	// 2. Communication Online Check
	if(CheckOnline(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// 3. Ramping Initialize
	vdoCH__Ramp_Mode->Set__DATA("Disable");
	//aoCH__RampUp_Time->Set__DATA("1000.0");
	//aoCH__RampDown_Time->Set__DATA("1000.0");
	aCH__RAMP_UP_TIME->Get__DATA(str_data);
	aoCH__RampUp_Time->Set__DATA(str_data);

	aCH__RAMP_DN_TIME->Get__DATA(str_data);
	aoCH__RampDown_Time->Set__DATA(str_data);

	// 4. Default Config Parameter Set
	// Ramping Time, Frequency SET, Frequency Tune Delay
	if(Fnc__DEFAULT_CONFIG_SET(p_variable, p_alarm) < 0)
	{
		Fnc__WRITE_APP_LOG("Call__INIT::Fnc__DEFAULT_CONFIG_SET is Failed");
	}

	// 5. RF Power Off
	//Fnc__doSTOP(p_alarm);

	/* // Pulsing Mode 재확인 필요
	// 6. Pulsing Mode initial // 2018.12.19
	if (FNC__PULSING_INIT_SEQ(p_variable, p_alarm) < 0)
	{
		Fnc__WRITE_APP_LOG("Call__INIT::FNC__PULSING_INIT_SEQ is Failed");
	}
	*/

	// 7. Enable Monitoring
	dCH__MONITOR_FLAG->Set__DATA("On");

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::Call__REMOTE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;

	// 1. Remote Mode Change
	if(doCH__CONTROL_MODE->Set__DATA("Remote") < 0)
	{
		int alarm_id = ALID__SEND_COMMAND_FAIL;
		CString msg;

		msg.Format("Send Command Failed (Remote)");

		Alarm__CHECK_POST(p_alarm, msg, alarm_id);
		return OBJ_ABORT;
	}

	// 3. Communication Online Check
	if(CheckOnline(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	// 4. Enable Monitoring
	dCH__MONITOR_FLAG->Set__DATA("On");

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::Call__LOCAL(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	SCX__TIMER_CTRL xTimer;
	xTimer->REGISTER__ABORT_OBJECT(sObject_Name);

	dCH__MONITOR_FLAG->Set__DATA("Off");
	if(xTimer->WAIT(2.0) < 0)	return OBJ_ABORT;		// 지연시간을 둔다.

	// 1. Local Mode Change
	if(doCH__CONTROL_MODE->Set__DATA("Local") < 0)
	{
		int alarm_id = ALID__SEND_COMMAND_FAIL;
		CString msg;

		msg.Format("Send Command Failed (Local)");

		Alarm__CHECK_POST(p_alarm, msg, alarm_id);
		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::Call__RF_OFF(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// 1. Enable Monitoring
	dCH__MONITOR_FLAG->Set__DATA("On");

	if(CheckOnline(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}
	if(CheckRemote(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	if(Seq__RAMP_UPDOWN_Ex(p_variable, p_alarm, "RF_OFF") < 0)
	{
		Fnc__doSTOP(p_alarm);
		Fnc__WRITE_APP_LOG("Call__RF_OFF : Seq__RAMP_UPDOWN is Failed - RF Power OFF");
		
		dCH__MONITOR_FLAG->Set__DATA("On");
		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::Call__OFF(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// 1. Enable Monitoring
	dCH__MONITOR_FLAG->Set__DATA("On");

	if(CheckOnline(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}
	if(CheckRemote(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	//if(doCH__RF_CMD->Set__DATA("OFF") < 0)
	if (Fnc__doSTOP(p_alarm) < 0)
	{
		Fnc__WRITE_APP_LOG("Call__RF_OFF_NG : Fnc__doSTOP");

		dCH__MONITOR_FLAG->Set__DATA("On");
		return OBJ_ABORT;
	}
	else
	{
		Fnc__WRITE_APP_LOG("Call__RF_OFF : Fnc__doSTOP");
	}

	return OBJ_AVAILABLE;
}

int CObj__OVATION_2560
::Call__SET_POWER(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// RF ON Interlock Check
	//   1) RF Communication Online
	//	 2) RF Contactor
	//	 3) TopLid
	//	 4) Vacuum Switch
	//	 5) RF Fault Error (Not Use)
	//	 6) RF Overheat (Not Use)
	//	 7) RF Fan Fault (Not Use)
	//	 8) RF Power Limit (Not Use)

	//pck test...
	CString str_data;
	aCH__SET_POWER->Get__DATA(str_data);
	aoCH__SetPower->Set__DATA(str_data);
	//

	// 1. Enable Monitoring
	dCH__MONITOR_FLAG->Set__DATA("On");

	if(CheckOnline(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}
	if(CheckRemote(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	if(CheckRFInterlock(p_variable, p_alarm) < 0)
	{
		return OBJ_ABORT;
	}

	//if(sCH__RF_CONDUCTANCE_INTLK_SKIP->Check__DATA("SKIP") < 0)
	//{
	//	if(CheckRFContactor(p_variable, p_alarm) < 0)
	//	{
	//		return OBJ_ABORT;
	//	}
	//	if(CheckRFInterlock(p_variable, p_alarm) < 0)
	//	{
	//		return OBJ_ABORT;
	//	}
	//}

	if(Seq__RAMP_UPDOWN_Ex(p_variable, p_alarm, "RF_ON") < 0)
	{
		Fnc__doSTOP(p_alarm);
		Fnc__WRITE_APP_LOG("Call__SET_POWER : Seq__RAMP_UPDOWN is Failed - RF Power OFF");

		dCH__MONITOR_FLAG->Set__DATA("On");
		return OBJ_ABORT;
	}

	return OBJ_AVAILABLE;
}
