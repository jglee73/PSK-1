#include "StdAfx.h"
#include "CObj__APS_8301.h"


//------------------------------------------------------------------------------------
int CObj__APS_8301
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	return -1;
}

int CObj__APS_8301
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	return -1;
}

int CObj__APS_8301
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString s_cmmd;
	CString r_data;

	if(siCH__ESC_VOLTAGE->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "*RV";

		int r_val = _Send__Command(s_cmmd, &r_data);
		if(r_val < 0)		return -1;

		read_data = r_data;
		return 1;
	}
	if(siCH__ESC_LEAK_CURRENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "*RI";

		int r_val = _Send__Command(s_cmmd, &r_data);
		if(r_val < 0)		return -1;

		read_data = r_data;
		return 1;
	}
	if(siCH__ESC_SYSTEM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "*RS";

		int r_val = _Send__Command(s_cmmd, &r_data);
		if(r_val < 0)		return -1;

		int r_hexa = _Get__HexToDec(r_data);

		// BIT 00 : 0x01
		if(r_hexa & 0x01)			sCH__INFO_POWER_STS->Set__DATA(STR__ON);
		else						sCH__INFO_POWER_STS->Set__DATA(STR__OFF);

		// BIT 01 : 0x02 
		if(r_hexa & 0x02)			sCH__INFO_HIGH_VOLTAGE_STS->Set__DATA(STR__ON);
		else						sCH__INFO_HIGH_VOLTAGE_STS->Set__DATA(STR__OFF);

		// BIT 03 : 0x08
		if(r_hexa & 0x08)			sCH__INFO_REVERSE_VOLTAGE_STS->Set__DATA(STR__ON);
		else						sCH__INFO_REVERSE_VOLTAGE_STS->Set__DATA(STR__OFF);

		// BIT 04 : 0x010
		if(r_hexa & 0x010)			sCH__INFO_OVER_CURRENT_ALARM_STS->Set__DATA(STR__ON);
		else						sCH__INFO_OVER_CURRENT_ALARM_STS->Set__DATA(STR__OFF);

		// BIT 15 : 0x0F000
		if(r_hexa & 0x0F000)		sCH__INFO_SYSTEM_ALARM_STS->Set__DATA(STR__ON);
		else						sCH__INFO_SYSTEM_ALARM_STS->Set__DATA(STR__OFF);

		read_data = r_data;
		return 1;
	}

	if(siCH__ESC_FIRMWARE_VER->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "*FV";

		int r_val = _Send__Command(s_cmmd, &r_data);
		if(r_val < 0)
		{
			read_data = "ERROR.1";
			return 1;
		}

		if(r_data.GetLength() != 4)
		{
			read_data = "ERROR.2";
			return 2;
		}

		r_data.Insert(2, '.');
		sCH__INFO_FIRMWARE_VER->Set__DATA(r_data);

		read_data = "OK";
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__APS_8301
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString s_cmmd;
	CString s_sign;
	CString r_data;

	if(aoCH__ESC_VOLTAGE_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data < 0)		s_sign = "-";
		else					s_sign = "+";

		s_cmmd.Format("*SV%s%04.0f", s_sign,abs(set_data));

		return _Send__Command(s_cmmd, &r_data);
	}
	if(aoCH__ESC_CURRENT_LIMIT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data < 0)		s_sign = "-";
		else					s_sign = "+";

		s_cmmd.Format("*SI%s%04.0f", s_sign,abs(set_data));

		return _Send__Command(s_cmmd, &r_data);
	}
	if(aoCH__ESC_TIME_DELAY_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd.Format("*DT%%04.0f", abs(set_data));

		return _Send__Command(s_cmmd, &r_data);
	}
	if(aoCH__ESC_RAMP_TIME_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data < 0)		s_sign = "-";
		else					s_sign = "+";

		s_cmmd.Format("*P%s%04.0f", s_sign,abs(set_data));

		return _Send__Command(s_cmmd, &r_data);
	}

	return -1; 
}

int CObj__APS_8301
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString s_cmmd;
	CString r_data;
	
	if(doCH__ESC_POWER_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(STR__ON) == 0)		s_cmmd = "*EP";
		else											s_cmmd = "*DP";

		return _Send__Command(s_cmmd, &r_data);
	}
	if(doCH__ESC_VOLTAGE_OUTPUT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(STR__ON) == 0)		s_cmmd = "*EV";
		else											s_cmmd = "*DV";

		return _Send__Command(s_cmmd, &r_data);
	}
	if(doCH__ESC_DISCHARGE_MODE_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(STR__ON) == 0)		s_cmmd = "*ED";
		else											s_cmmd = "*DD";

		return _Send__Command(s_cmmd, &r_data);
	}
	if(doCH__ESC_ALARM_RESET_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		s_cmmd = "*RA";

		return _Send__Command(s_cmmd, &r_data);
	}

	return -1;
}

int CObj__APS_8301
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__APS_8301
::_Send__Command(const CString& org_cmd, CString* r_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	CString r_bff;
	mX_Serial->CLEAR__BUFFER(&r_bff);

	// ...
	CString s_cmd;

	s_cmd  = org_cmd;
	s_cmd += sTerm_Str;

	// ...
	{
		log_msg = "Send >> \n";
		log_bff.Format("%s<%s>\n", org_cmd, sTerm_Exp);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);		
	}

	// ...
	int cfg__to_msec = 500;

	int r_len = mX_Serial->DATA__RECV(sTerm_Str, &s_cmd, cfg__to_msec);
	if (r_len < 0)
	{
		// ...
		{
			log_msg = "Recv << \n";
			log_bff.Format("Error (%1d)\n", r_len);
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}

		bActive__COMM_ONLINE = false;
		return -1;
	}

	// ...
	bActive__COMM_ONLINE = true;

	int s_index = s_cmd.Find(org_cmd);
	if(s_index < 0)
	{
		// ...
		{
			log_msg = "Recv << \n";
			log_bff.Format("%s\n", s_cmd);
			log_msg += log_bff;
			log_bff.Format("Error (No Command)\n");
			log_msg += log_bff;

			Write__DRV_LOG(log_msg);		
		}
		return -2;
	}

	CString ch_data = s_cmd.Mid(s_index + org_cmd.GetLength());
	r_data = &ch_data;

	// ...
	{
		log_msg = "Recv << \n";
		log_bff.Format("%s\n", s_cmd);
		log_msg += log_bff;
		log_bff.Format("Data : %s\n", ch_data);
		log_msg += log_bff;

		Write__DRV_LOG(log_msg);		
	}

	return 1;
}
