#include "stdafx.h"
#include "CObj__ERCD_SERIAL.h"


// ...
int  CObj__ERCD_SERIAL
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	siCH__ROM_VER->Get__STRING();
	siCH__ROBOT_TYPE->Get__STRING();
	siCH__EMG_STS->Get__STRING();

	doCH__CTRL_SET->Set__DATA(_IO_Cmd__INIT_ALM);
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__INIT_ERR);

	doCH__CTRL_SET->Set__DATA(_IO_Cmd__HOME);	
	return 1;
}

int  CObj__ERCD_SERIAL
::Call__RESET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__INIT_ALM);
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__INIT_ERR);

	doCH__CTRL_SET->Set__DATA(_IO_Cmd__RESET);	
	return 1;
}

int  CObj__ERCD_SERIAL
::Call__GOTO_POS(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	ch_data = aCH__PARA_USER_GOTO_POS->Get__STRING();
	aCH__PARA_SET_GOTO_POS->Set__DATA(ch_data);

	ch_data = aCH__PARA_USER_GOTO_SPEED->Get__STRING();
	aCH__PARA_SET_GOTO_VEL->Set__DATA(ch_data);

	return Fnc__GOTO_POS(p_variable, p_alarm);
}
int  CObj__ERCD_SERIAL
::Call__GOTO_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	ch_data = aCH__CFG_GOTO_UP_ABS_POS->Get__STRING();
	aCH__PARA_SET_GOTO_POS->Set__DATA(ch_data);

	ch_data = aCH__CFG_GOTO_SPEED->Get__STRING();
	aCH__PARA_SET_GOTO_VEL->Set__DATA(ch_data);

	return Fnc__GOTO_POS(p_variable, p_alarm);
}
int  CObj__ERCD_SERIAL
::Call__GOTO_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	ch_data = aCH__CFG_GOTO_DOWN_ABS_POS->Get__STRING();
	aCH__PARA_SET_GOTO_POS->Set__DATA(ch_data);

	ch_data = aCH__CFG_GOTO_SPEED->Get__STRING();
	aCH__PARA_SET_GOTO_VEL->Set__DATA(ch_data);

	return Fnc__GOTO_POS(p_variable, p_alarm);
}
int  CObj__ERCD_SERIAL
::Fnc__GOTO_POS(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__GOTO);;	
	siCH__ROBOT_STS_MANUAL->Get__STRING();

	int sim_count = 0;

	if(iActive_SIM > 0)
	{
		sCH__INFO_ROBOT_IDLE->Set__DATA(STR__OFF);
	}

	while(11)
	{
		Sleep(100);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}

		if(iActive_SIM > 0)
		{
			sim_count++;
			if(sim_count > 30)
			{
				sCH__INFO_ROBOT_IDLE->Set__DATA(STR__ON);
			
				CString ch_data = aCH__PARA_SET_GOTO_POS->Get__STRING();
				sCH__INFO_CUR_POS->Set__DATA(ch_data);

				printf(" * %s <- %s \n", 
						aCH__PARA_SET_GOTO_POS->Get__CHANNEL_NAME(),
						aCH__PARA_SET_GOTO_POS->Get__STRING());
			}
		}

		if(sCH__INFO_ROBOT_IDLE->Check__DATA(STR__ON) > 0)
		{
			double ref_pos = aCH__PARA_SET_GOTO_POS->Get__VALUE();
			double ref_min = ref_pos - 1.0;
			double ref_max = ref_pos + 1.0;

			CString ch_data = sCH__INFO_CUR_POS->Get__STRING();
			double cur_pos = atof(ch_data);

			if((cur_pos > ref_min) && (cur_pos < ref_max))
			{
				return 1;
			}

			// Alarm.Port ...
			{
				int alm_id = ALID__GOTO_POS_ERROR;
				CString alm_msg;
				CString alm_bff;
				CString r_act;

				alm_msg.Format(" * Target position is %.1f. \n", ref_pos);
				alm_bff.Format(" * Current position is %.1f. \n", cur_pos);
				alm_msg += alm_bff;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, alm_msg);
			}
			return -11;
		}
	}
	return 1;
}

int  CObj__ERCD_SERIAL
::Call__JOG_UP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__MOVE_INC);;	

	while(11)
	{
		Sleep(1);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}
	}
	return 1;
}
int  CObj__ERCD_SERIAL
::Call__JOG_DOWN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	doCH__CTRL_SET->Set__DATA(_IO_Cmd__MOVE_DEC);;	

	while(11)
	{
		Sleep(1);

		if(p_variable->Check__CTRL_ABORT() > 0)
		{
			return -11;
		}
	}
	return 1;
}
