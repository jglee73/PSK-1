#include "StdAfx.h"
#include "CObj__PSK.h"
#include "CObj__PSK__DEF.h"

#include "math.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int CObj__PSK
::Drv__RECV_COMMAND(const CString& var_name, 
				    const CString& str_cmmd, 
					const CString& str_para, 
					CString& recv_data)
{
	recv_data = "";

	// ...
	CString str__log;

	CString str__send_data;
	CString str__send_log;

	int cfg_timeout = m_Rcv_Time;

	// ...
	{
		str__send_data.Format("C%s%s", str_cmmd,str_para);
		str__send_log.Format("%s<CR><LF>", str__send_data);

		str__log.Format("[%s] SEND => [%s], timeout:%d msec \n", var_name, str__send_log, cfg_timeout);
		Fnc__DRV_LOG(str__log);
	}

	// ...
	{
		CString str_bff;
		mX_Serial->CLEAR__BUFFER(&str_bff);
	}

	// ...
	{
		str__send_data += (char) CR;
		str__send_data += (char) LF;
	}

	int r_flag = mX_Serial->DATA__RECV(m_Term_Str, &str__send_data, cfg_timeout);

	str__log.Format("RECV <= [%s], r_flag [%d] \n", str__send_data, r_flag);
	Fnc__DRV_LOG(str__log);

	if(r_flag >= 0)
	{
		m_nCommState = ONLINE;

		CString r_cmmd = "R";

		if(str__send_data.Find(r_cmmd) == 0)
		{  
			recv_data = str__send_data;
			return 1;  
		}
		return -11;
	}

	m_nCommState = OFFLINE;
	return -1;
}

int CObj__PSK
::Drv__SEND_COMMAND(const CString& var_name, 
			        const CString& str_cmmd, 
					const CString& str_para)
{
	// ...
	CString str__log;

	CString str__send_data;
	CString str__send_log;

	int cfg_timeout = m_Out_Time;

	// ...
	{
		str__send_data.Format("C%s%s", str_cmmd,str_para);
		str__send_log.Format("%s<CR><LF>", str__send_data);

		str__log.Format("[%s] SEND => [%s], timeout:%d msec \n", var_name, str__send_log, cfg_timeout);
		Fnc__DRV_LOG(str__log);
	}

	// ...
	{
		CString str_bff;
		mX_Serial->CLEAR__BUFFER(&str_bff);
	}

	// ...
	{
		str__send_data += (char) CR;
		str__send_data += (char) LF;
	}

	int r_flag = mX_Serial->DATA__RECV(m_Term_Str, &str__send_data, cfg_timeout);

	str__log.Format("RECV <= [%s], r_flag [%d] \n", str__send_data, r_flag);
	Fnc__DRV_LOG(str__log);

	if(r_flag >= 0)
	{
		m_nCommState = ONLINE;

		CString r_cmmd;
		r_cmmd.Format("R%s", str_cmmd);

		if(str__send_data.Find(r_cmmd) == 0)
		{  
			return 1;  
		}
		return -11;
	}

	m_nCommState = OFFLINE;
	return -1;
}


// ...
int  CObj__PSK::Update__ROBOT_STATE(const CString& str_data)
{
	bool active__recv_ok = false;
	CString ch_data;

	CString str__error_sts;
	CString str__servo_sts;
	CString str__origin_req;
	CString str__command_run;
	CString str__a_gripper_sts;
	CString str__b_gripper_sts;
	CString str__fan_sts;
	CString str__rb_task_sts;
	CString str__al_task_sts;
	CString str__error_code;

	int i_limit = str_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_data[i];

		if(i == 0)			
		{
			if(ch == 'R')		active__recv_ok = true;
			else				active__recv_ok = false;

			continue;
		}
		if(i == 1)			// Error        [01] : 
		{		
				 if(ch == '1')			str__error_sts = STR__ON;
			else if(ch == '0')			str__error_sts = STR__OFF;
			else						str__error_sts = STR__UNKNOWN;

			continue;
		}
		if(i == 2)			// Servo ON     [02] : 
		{
				 if(ch == '1')			str__servo_sts = STR__ON;
			else if(ch == '0')			str__servo_sts = STR__OFF;
			else						str__servo_sts = STR__UNKNOWN;

			continue;
		}
		if(i == 3)			// 원점복귀 요구     [03] : 
		{
				 if(ch == '1')			str__origin_req = STR__ON;
			else if(ch == '0')			str__origin_req = STR__OFF;
			else						str__origin_req = STR__UNKNOWN;

			continue;
		}
		if(i == 4)			// Command 실행중     [04] : 
		{
				 if(ch == '1')			str__command_run = STR__ON;
			else if(ch == '0')			str__command_run = STR__OFF;
			else						str__command_run = STR__UNKNOWN;

			continue;
		}
		if((i == 5)	|| (i == 6))     // Gripper 상태     [05 06] : 
		{
				 if(ch == '0')			ch_data = "Error";
			else if(ch == '1')			ch_data = "Retract";
			else if(ch == '2')			ch_data = "Extend";
			else if(ch == '3')			ch_data = "Wafer";
			else						ch_data = STR__UNKNOWN;

				 if(i == 5)				str__a_gripper_sts = ch_data;
			else if(i == 6)				str__b_gripper_sts = ch_data;

			continue;
		}
		if(i == 7)			// Fan 정상     [07] : 
		{
				 if(ch == '1')			str__fan_sts = STR__ON;
			else if(ch == '0')			str__fan_sts = STR__OFF;
			else						str__fan_sts = STR__UNKNOWN;

			continue;
		}
		if(i == 8)			// Robot Task 동작중     [08] : 
		{
				 if(ch == '1')			str__rb_task_sts = STR__ON;
			else if(ch == '0')			str__rb_task_sts = STR__OFF;
			else						str__rb_task_sts = STR__UNKNOWN;

			continue;
		}
		if(i == 9)			// Aligner Task 동작중     [09] : 
		{
				 if(ch == '1')			str__al_task_sts = STR__ON;
			else if(ch == '0')			str__al_task_sts = STR__OFF;
			else						str__al_task_sts = STR__UNKNOWN;

			continue;
		}
		if((i == 15) || (i == 16))     // Error Code     [15 ~ 16] :
		{
			str__error_code += ch;

			continue;
		}
	}

	if(active__recv_ok)
	{
		sCH__MON_ERROR_STATE->Set__DATA(str__error_sts);
		sCH__MON_SERVO_STATE->Set__DATA(str__servo_sts);
		sCH__MON_ORIGIN_REQ->Set__DATA(str__origin_req);		

		sCH__MON_COMMAND_RUN->Set__DATA(str__command_run);

		sCH__MON_A_ARM_GRIPPER_STATE->Set__DATA(str__a_gripper_sts);
		sCH__MON_B_ARM_GRIPPER_STATE->Set__DATA(str__b_gripper_sts);

		sCH__MON_RB_FAN_STATE->Set__DATA(str__fan_sts);

		sCH__MON_RB_TASK_STATE->Set__DATA(str__rb_task_sts);
		sCH__MON_AL_TASK_STATE->Set__DATA(str__al_task_sts);

		sCH__MON_ERROR_CODE->Set__DATA(str__error_code);
	}
	else
	{
		ch_data = "___";

		sCH__MON_ERROR_STATE->Set__DATA(ch_data);
		sCH__MON_SERVO_STATE->Set__DATA(ch_data);
		sCH__MON_ORIGIN_REQ->Set__DATA(ch_data);

		sCH__MON_COMMAND_RUN->Set__DATA(ch_data);

		sCH__MON_A_ARM_GRIPPER_STATE->Set__DATA(ch_data);
		sCH__MON_B_ARM_GRIPPER_STATE->Set__DATA(ch_data);

		sCH__MON_RB_FAN_STATE->Set__DATA(ch_data);

		sCH__MON_RB_TASK_STATE->Set__DATA(ch_data);
		sCH__MON_AL_TASK_STATE->Set__DATA(ch_data);

		sCH__MON_ERROR_CODE->Set__DATA(ch_data);
	}

	return 1;
}

int  CObj__PSK::Update__VERSION(const CString& str_data)
{
	bool active__recv_ok = false;
	CString ch_data;

	CString str__app_version;
	CString str__revision;

	int i_limit = str_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_data[i];

		if(i == 0)			
		{
			if(ch == 'R')		active__recv_ok = true;
			else				active__recv_ok = false;

			continue;
		}
		if((i >= 1) || (i <= 7))     // App. Version     [01 ~ 07] : 
		{	
			str__app_version += ch;
			continue;
		}
		if(i == 8)      // Revision     [08] : 
		{
			str__revision += ch;
			continue;
		}
	}

	if(active__recv_ok)
	{
		sCH__MON_APP_VERSION->Set__DATA(str__app_version);
		sCH__MON_REVISION->Set__DATA(str__revision);
	}
	else
	{
		ch_data = "___";

		sCH__MON_APP_VERSION->Set__DATA(ch_data);
		sCH__MON_REVISION->Set__DATA(ch_data);
	}

	return 1;
}

int  CObj__PSK::Update__AL_MEASUREMENT(const CString& str_data)
{
	bool active__recv_ok = false;
	CString ch_data;

	CString str__al_sts;
	CString str__x_err;
	CString str__y_err;
	CString str__notch_angle;

	int i_limit = str_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_data[i];

		if(i == 0)			
		{
			if(ch == 'R')		active__recv_ok = true;
			else				active__recv_ok = false;

			continue;
		}
		if(i == 1)     // Aligner State     [01] :
		{
			     if(ch == '0')		str__al_sts = "Ready";
			else if(ch == '1')		str__al_sts = "Done";
			else					str__al_sts = "Error";

			continue;
		}
		if((i >= 2) || (i <= 5))     // X 방향 틀어짐     [02 ~ 05] : 
		{
			str__x_err += ch;
			continue;;
		}
		if((i >= 6) || (i <= 9))     // X 방향 틀어짐     [06 ~ 09] : 
		{
			str__y_err += ch;
			continue;;
		}
		if((i >= 10) || (i <= 14))     // Notch 각도     [10 ~ 14] : 
		{
			str__notch_angle += ch;
			continue;;
		}
	}

	if(active__recv_ok)
	{
		sCH__MON_AL_STATE->Set__DATA(str__al_sts);
		sCH__MON_AL_X_ERROR->Set__DATA(str__x_err);
		sCH__MON_AL_Y_ERROR->Set__DATA(str__y_err);
		sCH__MON_AL_NOTCH_ANGLE->Set__DATA(str__notch_angle);
	}
	else
	{
		ch_data = "___";

		sCH__MON_AL_STATE->Set__DATA(ch_data);
		sCH__MON_AL_X_ERROR->Set__DATA(ch_data);
		sCH__MON_AL_Y_ERROR->Set__DATA(ch_data);
		sCH__MON_AL_NOTCH_ANGLE->Set__DATA(ch_data);
	}

	return 1;
}


// ...
int  CObj__PSK::
Fnc__HexToDec(const CString& str_dec)
{
	CString string;
	char str_ch[2];
	char ch;

	int  value;
	int  limit;
	int  i;

	string = str_dec;
	string.MakeUpper();

	value = 0;
	str_ch[1] = 0;

	limit = string.GetLength();
	for(i=0;i<limit;i++)
	{
		if(i > 0)	value *= 16;

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
