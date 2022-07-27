#include "StdAfx.h"
#include "CObj__ERCD_SERIAL.h"


//------------------------------------------------------------------------------------
int CObj__ERCD_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	return -1;
}

int CObj__ERCD_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	return -1;
}

int CObj__ERCD_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString s_cmmd;
	CString r_data;

	if(siCH__ROM_VER->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "?VER";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		sCH__INFO_ROM_VER->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}
	if(siCH__ROBOT_TYPE->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "?ROBOT";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		sCH__INFO_ROBOT_TYPE->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}
	if(siCH__EMG_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "?EMG";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

			 if(r_data.CompareNoCase("0") == 0)			sCH__INFO_ROBOT_TYPE->Set__DATA(STR__OFF);
		else if(r_data.CompareNoCase("1") == 0)			sCH__INFO_ROBOT_TYPE->Set__DATA(STR__ON);
		else											sCH__INFO_ROBOT_TYPE->Set__DATA(STR__UNKNOWN);

		read_data = "OK";
		return 1;
	}

	if(siCH__SERVO_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "?SRVO";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

			 if(r_data.CompareNoCase("0") == 0)			sCH__INFO_SERVO_STS->Set__DATA(STR__OFF);
		else if(r_data.CompareNoCase("1") == 0)			sCH__INFO_SERVO_STS->Set__DATA(STR__ON);
		else											sCH__INFO_SERVO_STS->Set__DATA(STR__UNKNOWN);

		read_data = "OK";
		return 1;
	}
	if(siCH__CUR_POS->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "?POS";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		sCH__INFO_CUR_POS->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}
	if((siCH__ROBOT_STS_AUTO->Check__VARIABLE_NAME(var_name)   > 0)
	|| (siCH__ROBOT_STS_MANUAL->Check__VARIABLE_NAME(var_name) > 0))
	{
		s_cmmd = "?MODE";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		if(r_data.CompareNoCase("0") == 0)				sCH__INFO_ROBOT_IDLE->Set__DATA(STR__ON);
		else											sCH__INFO_ROBOT_IDLE->Set__DATA(STR__OFF);

		read_data = "OK";
		return 1;
	}
	if(siCH__ORG_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "?ORG";

		int r_val = _Send__Command(s_cmmd, &r_data, false);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		if(r_data.CompareNoCase("1") == 0)				sCH__INFO_ROBOT_HOME->Set__DATA(STR__ON);
		else											sCH__INFO_ROBOT_HOME->Set__DATA(STR__OFF);

		read_data = "OK";
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__ERCD_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return -1; 
}

int CObj__ERCD_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString s_cmmd;
	CString r_data;
	
	if(doCH__CTRL_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(_IO_Cmd__HOME) == 0)
		{
			s_cmmd = "ORG";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__GOTO) == 0)
		{
			CString para_pos = aCH__PARA_SET_GOTO_POS->Get__STRING();
			CString para_vel = aCH__PARA_SET_GOTO_VEL->Get__STRING();

			s_cmmd.Format("%s %s,%s", "MOVD", para_pos, para_vel);
		}
		else if(set_data.CompareNoCase(_IO_Cmd__MOVE_INC) == 0)
		{
			s_cmmd = "XINC";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__MOVE_DEC) == 0)
		{
			s_cmmd = "XDEC";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__SERVO_OFF) == 0)
		{
			s_cmmd = "SRVO 0";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__SERBO_ON) == 0)
		{
			s_cmmd = "SRVO 1";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__RESET) == 0)
		{
			s_cmmd = "RESET";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__INIT_ALM) == 0)
		{
			s_cmmd = "INIT ALM";
		}
		else if(set_data.CompareNoCase(_IO_Cmd__INIT_ERR) == 0)
		{
			s_cmmd = "INIT ERR";
		}
		else
		{
			return -11;
		}

		return _Send__Command(s_cmmd, &r_data, true);
	}

	if(doCH__ABORT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(_IO_Cmd__STOP) == 0)
		{
			s_cmmd = (char) ETX;
		}
		else
		{
			return -11;
		}

		return _Send__Command(s_cmmd, &r_data, true);
	}

	return -1;
}

int CObj__ERCD_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__ERCD_SERIAL
::_Send__Command(const CString& org_cmd, CString* r_data, const bool active__act_check)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		CString r_err;
		mX_Serial->CLEAR__BUFFER(&r_err);
	}

	// ...
	CString s_cmd;

	s_cmd  = '@';
	s_cmd += org_cmd;

	// ...
	{
		log_msg = "Send >> \n";
		log_bff.Format("%s%s\n", s_cmd, sTerm_Exp);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);		
	}

	s_cmd += sTerm_Str;

	// ...
	int cfg__to_msec = 200;

	if(active__act_check)		cfg__to_msec = 10000;

	int r_len = mX_Serial->DATA__RECV(sTerm_Str, &s_cmd, cfg__to_msec);
	if (r_len < 0)
	{
		// ...
		{
			log_msg = "Recv << \n";
			log_bff.Format("  Error (%1d)\n", r_len);
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}

		bActive__COMM_ONLINE = false;
		return -1;
	}

	bActive__COMM_ONLINE = true;

	// ..
	CString r__data_1 = s_cmd;
	CString r__data_2;
	mX_Serial->CLEAR__BUFFER(&r__data_2);

	// Recv.Log ...
	{
		// ...
		{
			log_msg.Format("Recv (%1d) << \n", r_len);
			log_bff.Format("  [%s] \n", r__data_1);
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}

		// ...
		{
			log_msg.Format("Buffer (%1d) << \n", r_len);
			log_bff.Format("  [%s] \n", r__data_2);
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}
	}

	// Data.Trim ...
	{
		r__data_1.Trim();
		*r_data = r__data_1;

		int s_index = r__data_2.Find(sTerm_Str);
		if(s_index > 0)
		{
			r__data_2.Delete(s_index, r__data_2.GetLength() - s_index);
			r__data_2.Trim();
		}
	}

	// ...
	int drv_delay_msec = 50;

	if(active__act_check)
	{
		if(r__data_1.CompareNoCase("OK") == 0)
		{
			Sleep(drv_delay_msec);
			return 1;
		}

		*r_data = r__data_2;
		return -11;
	}

	if(r__data_2.CompareNoCase("OK") == 0)
	{
		Sleep(drv_delay_msec);
		return 1;
	}
	return -12;
}
