#include "StdAfx.h"
#include "CObj__LIFT_PIN_IO.h"


// ...
int  CObj__LIFT_PIN_IO
::Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id,r_act);
	p_alarm->Popup__ALARM_With_MESSAGE(alarm_id, msg, r_act);

	if(r_act.CompareNoCase("RETRY") == 0)		return 1;

	return OBJ_ABORT;
}


int  CObj__LIFT_PIN_IO
::Alarm__POST_CHECK(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id)
{
	CString r_act;

	p_alarm->Check__ALARM(alarm_id, r_act);
	p_alarm->Post__ALARM_With_MESSAGE(alarm_id, msg);

	return OBJ_ABORT;
}

void CObj__LIFT_PIN_IO
::Fnc__WRITE_LOG(const CString& log_msg)
{
	xLOG_CTRL->WRITE__LOG(log_msg);
}

int CObj__LIFT_PIN_IO
::Fnc__CHECK_CHUCKING(CII_OBJECT__VARIABLE *p_variable,
					  CII_OBJECT__ALARM *p_alarm)
{
	CString str_data;
	CString msg;

	int nCfg_Esc_Pin_Up_Volt = 0;
	int nCur_Esc_Voltage = 0;

	// ESC Voltage Check (User Config) ...
	aCH__CFG_ESC_VOLTAGE_PIN_UP_THRESHOLD->Get__DATA(str_data);
	nCfg_Esc_Pin_Up_Volt = atoi(str_data);

	nCur_Esc_Voltage = (int) aEXT_CH__AI_ESC_VOLTAGE->Get__VALUE();
	nCur_Esc_Voltage = abs(nCur_Esc_Voltage);

	if(nCur_Esc_Voltage > nCfg_Esc_Pin_Up_Volt)
	{
		// Alarm Posting
		int alarm_id = ALID__CHUCKING_STATUS_ALARM;

		msg.Format("ESC Current Voltage: %d, PIN UP Threshold: %d",
			nCur_Esc_Voltage, nCfg_Esc_Pin_Up_Volt);

		Alarm__POST_CHECK(p_alarm, msg, alarm_id);
		return OBJ_ABORT;
	}

	// ESC Status Check ...
	if(sEXT_CH__CHUCK_STATE->Check__DATA("DECHUCKED") > 0)
	{
		return OBJ_AVAILABLE;
	}

	// ...
	{
		int alarm_id = ALID__CHUCKING_STATUS_ALARM;

		sEXT_CH__CHUCK_STATE->Get__DATA(str_data);
		msg.Format("Chuck Status:[%s]", str_data);

		Alarm__POST_CHECK(p_alarm, msg, alarm_id);
	}
	return OBJ_ABORT;
}

void CObj__LIFT_PIN_IO
::_Fnc__SIM_PIN_POD(const bool active_up, const bool active_down, const bool active_middle)
{
	Sleep(1000);

	// ...
	double cfg__up_min = 0.0;
	double cfg__up_max = 0.0;
	int i;

	for(i=0; i<iPIN__SIZE; i++)
	{
		if(active_up)
		{
			cfg__up_min = aCH__CFG_UP_POS_MIN__PIN_X[i]->Get__VALUE();
			cfg__up_max = aCH__CFG_UP_POS_MAX__PIN_X[i]->Get__VALUE();
		}
		else if(active_down)
		{
			cfg__up_min = aCH__CFG_DOWN_POS_MIN__PIN_X[i]->Get__VALUE();
			cfg__up_max = aCH__CFG_DOWN_POS_MAX__PIN_X[i]->Get__VALUE();
		}
		else if(active_middle)
		{
			cfg__up_min = aCH__CFG_MIDDLE_POS_MIN__PIN_X[i]->Get__VALUE();
			cfg__up_max = aCH__CFG_MIDDLE_POS_MAX__PIN_X[i]->Get__VALUE();
		}
		else
		{
			continue;
		}

		double ref__pin_pos = (cfg__up_min + cfg__up_max) * 0.5;
		aEXT_CH__AI_PIN_POS_X[i]->Set__VALUE(ref__pin_pos);
	}
}
