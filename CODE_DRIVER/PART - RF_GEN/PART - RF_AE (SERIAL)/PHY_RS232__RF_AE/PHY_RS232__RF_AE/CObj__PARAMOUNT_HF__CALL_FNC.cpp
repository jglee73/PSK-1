#include "StdAfx.h"
#include "CObj__PARAMOUNT_HF.h"


// ...
int CObj__PARAMOUNT_HF
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	int flag = 1;

	Write__DRV_LOG("Initial_Start");

	if(Call__POWER_SET(p_variable, p_alarm, false) < 0) 
	{
		flag = -1;
	}

	aCH__PARA_POWER_SET->Set__DATA("0.0");
	doCH__REGULATION_MODE->Set__DATA(STR__FORWARD);

	if(Call__CTRL_MODE(p_variable, p_alarm, true) < 0) 
	{
		flag = -1;
	}
	if(Call__POWER_SET(p_variable, p_alarm, false) < 0)
	{
		flag = -1;
	}

	Write__DRV_LOG("Initial_End");
	return flag;
}

int  CObj__PARAMOUNT_HF
::Call__CTRL_MODE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_remote)
{
	int flag = -1;

	if(active_remote)		flag = doCH__CTRL_MODE->Set__DATA(STR__HOST);
	else					flag = doCH__CTRL_MODE->Set__DATA(STR__ANALOG);

	return flag;
}

int  CObj__PARAMOUNT_HF
::Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_set)
{
	CString ch_data;
	int	flag;

	if(active_set)
	{
		aCH__PARA_POWER_SET->Set__DATA(ch_data);
		aoCH__POWER_SET->Set__DATA(ch_data);

		flag = doCH__POWER_MODE->Set__DATA(STR__ON);
	}
	else
	{
		flag = doCH__POWER_MODE->Set__DATA(STR__OFF);

		aoCH__POWER_SET->Set__DATA("0.0");
	}
	return flag;
}

int CObj__PARAMOUNT_HF
::Call__PROC_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;
	int		flag = -1;

mode_sel:

	CString trg_value;
	aCH__PARA_POWER_SET->Get__DATA(trg_value);

	if(sCH__INFO_CTRL_MODE_READ->Check__DATA(STR__HOST) < 0)
	{
		flag = Call__CTRL_MODE(p_variable, p_alarm, true);		
		if(flag < 0)
		{
			CString r_act;

			p_alarm->Popup__ALARM_With_MESSAGE(ALID__GEN_RETRY_OVER_ALARM, "Call__CTRL_MODE", r_act);

			if(r_act.CompareNoCase(ACT__RETRY) == 0)
			{
				Write__DRV_LOG("goto_Retry\n");
				goto mode_sel;
			}
			return flag;
		}
	}	
	else
	{
		Write__DRV_LOG("SUB_FNC : Call__MODE_SEL : HOST");
	}

pwr_on :

	flag = Call__POWER_SET(p_variable, p_alarm, true);
	if (flag < 0)
	{
		CString r_act;

		p_alarm->Popup__ALARM_With_MESSAGE(ALID__GEN_RETRY_OVER_ALARM, "Call__POWER_SET", r_act);

		if (r_act.CompareNoCase(ACT__RETRY) == 0)
		{
			Write__DRV_LOG("goto_Retry\n");
			goto pwr_on;
		}
		return -1;
	}
	else
	{
		Write__DRV_LOG("SUB_FNC : Call__POWER_SEL_ON");
	}

	Write__DRV_LOG(log_msg);
	return 1;
}
