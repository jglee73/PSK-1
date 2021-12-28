#include "StdAfx.h"
#include "CObj__LV32_BLDC.h"


//------------------------------------------------------------------------------------
int CObj__LV32_BLDC
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Read__ANALOG()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	return -1;
}

int CObj__LV32_BLDC
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;
	int i;

	// ...
	{
		log_msg  = "__Read__DIGITAL()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...'
	unsigned char cmmd_byte = 0x00;

	if(diCH__FFU_BLOCK_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte = _CMMD_MODE__BLOCK_GET;
	}
	else if(diCH__FFU_UNIT_GET->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte = _CMMD_MODE__UNIT_GET;
	}

	if(cmmd_byte == 0x00)
	{
		log_msg = " * Variable Error !";

		Fnc__DRV_LOG_OF_MSG(log_msg);		
		return -1;
	}

	// ...
	unsigned char r_data[CFG__MAX_DATA];
	memset(r_data, 0, sizeof(r_data));

	int r_ret = _Recv_Command(cmmd_byte, r_data);
	if(r_ret < 0)
	{
		if((cmmd_byte == _CMMD_MODE__BLOCK_GET)
		|| (cmmd_byte == _CMMD_MODE__BLOCK_GET))
		{
			read_data = STR__ERROR;
		}
		return 1;
	}

	// ...
	if(cmmd_byte == _CMMD_MODE__BLOCK_GET)
	{
		for(i=0; i<CFG__FAN_SIZE; i++)
		{
			int i_offset = i * 4;

			CString str_hexa;
			int i_hex = 0;

			// HEXA ...
			{
				int k_limit = 4;
				int k;

				ch_data = "";

				for(k=0; k<k_limit; k++)
				{
					// 0 : ID
					// 1 : PV
					// 2 : ALARM
					// 3 : SV
					
					i_hex = 0x0ff & r_data[i_offset + k];
					str_hexa.Format("%01X ", i_hex);
					ch_data += str_hexa;
				}

				sCH__FFU_BLOCK__STATE_HEXA_X[i]->Set__DATA(ch_data);
			}

			// 0 : ID
			{
				byte id = 0x0ff & r_data[0 + i_offset];
				id -= 0x80;

				ch_data.Format("%1d", id);
				sCH__FFU_BLOCK__ID_X[i]->Set__DATA(ch_data);
			}
			// 1 : PV (RPM)
			{
				i_hex = 0x0ff & r_data[1 + i_offset];
				double value_pv = i_hex * 10.0;

				ch_data.Format("%.0f", value_pv);
				sCH__FFU_BLOCK__RPM_PV_X[i]->Set__DATA(ch_data);
			}
			// 2 : ALARM
			{
				i_hex = 0x0ff & r_data[2 + i_offset];

				// BIT 0 : 0x01
				{
					if(i_hex & _ALARM_STS__LOCAL_MODE__BIT_0)			ch_data = STR__ON;
					else												ch_data = STR__OFF;
				
					sCH__FFU_BLOCK__ALARM_LOCAL_MODE_X[i]->Set__DATA(ch_data);
				}
				// BIT 1 : 0x02
				{
					if(i_hex & _ALARM_STS__POWER_OFF__BIT_1)			ch_data = STR__ON;
					else												ch_data = STR__OFF;

					sCH__FFU_BLOCK__ALARM_POWER_OFF_X[i]->Set__DATA(ch_data);
				}
				// BIT 5 : 0x20
				{
					if(i_hex & _ALARM_STS__OVER_CURRENT__BIT_5)			ch_data = STR__ON;
					else												ch_data = STR__OFF;

					sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[i]->Set__DATA(ch_data);
				}
				// BIT 6 : 0x40
				{
					if(i_hex & _ALARM_STS__MOTOR_ERROR__BIT_6)			ch_data = STR__ON;
					else												ch_data = STR__OFF;

					sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[i]->Set__DATA(ch_data);
				}
				// BIT 7 : 0x80
				{
					if(i_hex & _ALARM_STS__CONNECTION_ERROR__BIT_7)		ch_data = STR__OFF;
					else												ch_data = STR__ON;

					sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[i]->Set__DATA(ch_data);
				}
			}
			// 3 : SV (RPM)
			{
				i_hex = 0x0ff & r_data[3 + i_offset];
				double value_sv = i_hex * 10.0;

				ch_data.Format("%.0f", value_sv);
				sCH__FFU_BLOCK__RPM_SV_X[i]->Set__DATA(ch_data);
			}
		}

		read_data = STR__ERROR;
		return 1;
	}
	else if(cmmd_byte == _CMMD_MODE__UNIT_GET)
	{
		int high_data = 0x0ff & r_data[0];
		int low_data  = 0x0ff & r_data[1];

		ch_data.Format("%01X %01X", high_data,low_data);
		sCH__FFU_UNIT__PRESSURE_HEXA->Set__DATA(ch_data);

		double pressure_value = 0.0;
		pressure_value = (high_data * 0x100) + low_data;
		pressure_value = (pressure_value - 50.0) / 100.0;

		ch_data.Format("%.2f", pressure_value);
		sCH__FFU_UNIT__PRESSURE_VALUE->Set__DATA(ch_data);

		read_data = STR__ERROR;
		return 1;
	}

	return -1;
}

int CObj__LV32_BLDC
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Read__STRING()";
		log_msg += "\n";

		log_bff.Format(" * %s", var_name); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__LV32_BLDC
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Write__ANALOG()";
		log_msg += "\n";

		log_bff.Format(" * %s <- [%.3f]", var_name,set_data); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	return -1;
}

int CObj__LV32_BLDC
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg  = "__Write__DIGITAL()";
		log_msg += "\n";

		log_bff.Format(" * %s <- [%s]", var_name,set_data); 
		log_msg += log_bff;

		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...
	unsigned char cmmd_byte = 0x00;	
	int set_sv = 0;

	if(doCH__FFU_BLOCK_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte  = _CMMD_MODE__BLOCK_SET;

		set_sv = (int) aCH__PARA_FFU_BLOCK_RPM_SV->Get__VALUE();
	}
	else if(doCH__FFU_UNIT_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		cmmd_byte  = _CMMD_MODE__UNIT_SET;

		set_sv = (int) aCH__PARA_FFU_UNIT_DIFF_PRESSURE->Get__VALUE();
	}

	if(cmmd_byte == 0x00)
	{
		log_msg = " * Variable Error !";

		Fnc__DRV_LOG_OF_MSG(log_msg);		
		return -1;
	}

	// ...
	unsigned char r_data[CFG__MAX_DATA];

	int r_ret = _Recv_Command(cmmd_byte, r_data, set_sv);
	if(r_ret < 0)		return -1;

	// ...
	if(cmmd_byte == _CMMD_MODE__BLOCK_SET)
	{
		byte i_hexa = r_data[0];

		if(i_hexa != 0xB9)			return -1;
		return 1;
	}
	else if(cmmd_byte == _CMMD_MODE__UNIT_SET)
	{
		return 1;
	}

	return -1;
}

int CObj__LV32_BLDC
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__LV32_BLDC::
_Recv_Command(const unsigned char cmmd_type, 
			  unsigned char* r_xxxx, 
			  const int set_sv)
{
	unsigned char s_data[CFG__MAX_DATA];
	unsigned char r_data[CFG__MAX_DATA];

	ZeroMemory(s_data, sizeof(s_data));
	ZeroMemory(r_data, sizeof(r_data));
	ZeroMemory(r_xxxx, sizeof(r_xxxx));

	// ...
	byte lv32_id = 0x0ff & (int) aCH__CFG_LV32_ID->Get__VALUE();

	byte id_cnt = 0x0ff & (int) aCH__CFG_RANGE_ICU_COUNT->Get__VALUE();
	byte s_id = 0x0ff & (int) aCH__CFG_START_ICU_ID->Get__VALUE();
	byte e_id = s_id + (id_cnt - 1);

	// ...
	int i_db;
	
	i_db = 0;
	s_data[i_db++] = STX;
	s_data[i_db++] = cmmd_type;

	if(cmmd_type == _CMMD_MODE__BLOCK_GET)
	{
		s_data[i_db++] = 0x87;
		s_data[i_db++] = 0x80 | lv32_id;
		s_data[i_db++] = 0x9f;

		s_data[i_db++] = 0x80 | s_id;
		s_data[i_db++] = 0x80 | e_id;
	}
	else if(cmmd_type == _CMMD_MODE__UNIT_GET)
	{
		s_data[i_db++] = 0x80 | lv32_id;
	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_SET)
	{
		s_data[i_db++] = 0x84;
		s_data[i_db++] = 0x80 | lv32_id;
		s_data[i_db++] = 0x9f;

		s_data[i_db++] = 0x80 | s_id;
		s_data[i_db++] = 0x80 | e_id;

		s_data[i_db++] = 0x0ff & (byte) (set_sv / 10.0);
	}
	else if(cmmd_type == _CMMD_MODE__UNIT_SET)
	{
		s_data[i_db++] = 0x80 | lv32_id;

		int set_hexa = (set_sv * 100) + 50;

		s_data[i_db++] = 0x0ff & (byte) (set_hexa / 0x100);
		s_data[i_db++] = 0x0ff & (byte) set_hexa;
	}
	else
	{
		return -1;
	}

	s_data[i_db++] = _Get_CheckSum(s_data,i_db);
	s_data[i_db++] = ETX;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "_Recv_Command() ... \n";
		log_msg += "  > ";

		for(int i=0; i<i_db; i++)
		{
			log_bff.Format("%02X ", 0x0ff&s_data[i]);
			log_msg += log_bff;
		}
		log_msg += "\n";
		
		Fnc__DRV_LOG_OF_MSG(log_msg);
	}

	// ...
	int check_flag = 1;
	int n_counter  = 0;

	int r_len = 0;
	int r_offset = 0;

	if(cmmd_type == _CMMD_MODE__BLOCK_GET)
	{
		r_len = 7 + (4 * id_cnt);
		r_offset = 5;
	}
	else if(cmmd_type == _CMMD_MODE__UNIT_GET)
	{
		r_len = 7;
		r_offset = 3;
	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_SET)
	{
		r_len = 10;
		r_offset = 7;
	}
	else if(cmmd_type == _CMMD_MODE__UNIT_SET)
	{
		r_len = 5;
		r_offset = 3;
	}

	do
	{
		// ...
		{
			CString str_log;
			mX_Serial->CLEAR__BUFFER(&str_log);
		}

		int s_ret = mX_Serial->CHAR__SEND(s_data, i_db);
		
		int ref_len = r_len;
		int r_count = mX_Serial->OnlyRecv__CHAR(r_data, &r_len, m_Rcv_Time);

		// ...
		{
			log_msg = "OnlyRecv__CHAR() ...\n";

			log_bff.Format(" * ref_len <- %1d \n", ref_len);
			log_msg += log_bff;

			log_bff.Format(" * r_len <- %1d \n", r_len);
			log_msg += log_bff;

			log_bff.Format(" * r_count <- %1d \n", r_count);
			log_msg += log_bff;

			log_msg += "  < ";

			for(int i=0; i<r_len; i++)
			{
				log_bff.Format("%02X ", r_data[i]);
				log_msg += log_bff;
			}

			Fnc__DRV_LOG_OF_MSG(log_msg);
		}

		if(ref_len == r_len)
		{
			int i_count = 0;

			for(int i=r_offset; i<ref_len; i++)
			{
				r_xxxx[i-r_offset] = r_data[i];
				i_count++;;
			}

			iCOMM_STATE = ONLINE;
			return i_count;
		}
	}
	while(++n_counter < m_nRetryCnt);

	iCOMM_STATE = OFFLINE;
	return -1;
}

int CObj__LV32_BLDC::
_Check_Command(const unsigned char cmmd_type, 
			  unsigned char* r_xxxx, 
			  const int set_sv)
{
	unsigned char s_data[CFG__MAX_DATA];
	unsigned char r_data[CFG__MAX_DATA];

	ZeroMemory(s_data, sizeof(s_data));
	ZeroMemory(r_data, sizeof(r_data));
	ZeroMemory(r_xxxx, sizeof(r_xxxx));

	// ...
	byte lv32_id = 0x0ff & (int) aCH__CFG_LV32_ID->Get__VALUE();

	byte id_cnt = 0x0ff & (int) aCH__CFG_RANGE_ICU_COUNT->Get__VALUE();
	byte s_id = 0x0ff & (int) aCH__CFG_START_ICU_ID->Get__VALUE();
	byte e_id = s_id + (id_cnt - 1);

	// ...
	int i_db;

	i_db = 0;
	s_data[i_db++] = STX;
	s_data[i_db++] = cmmd_type;

	if(cmmd_type == _CMMD_MODE__BLOCK_GET)
	{
		s_data[i_db++] = 0x87;
		s_data[i_db++] = 0x80 | lv32_id;
		s_data[i_db++] = 0x9f;

		s_data[i_db++] = 0x80 | s_id;
		s_data[i_db++] = 0x80 | e_id;
	}
	else if(cmmd_type == _CMMD_MODE__UNIT_GET)
	{
		s_data[i_db++] = 0x80 | lv32_id;
	}
	else if(cmmd_type == _CMMD_MODE__BLOCK_SET)
	{
		s_data[i_db++] = 0x84;
		s_data[i_db++] = 0x80 | lv32_id;
		s_data[i_db++] = 0x9f;

		s_data[i_db++] = 0x80 | s_id;
		s_data[i_db++] = 0x80 | e_id;

		s_data[i_db++] = 0x0ff & (byte) (set_sv / 10.0);
	}
	else if(cmmd_type == _CMMD_MODE__UNIT_SET)
	{
		s_data[i_db++] = 0x80 | lv32_id;

		int set_hexa = (set_sv * 100) + 50;

		s_data[i_db++] = 0x0ff & (byte) (set_hexa / 0x100);
		s_data[i_db++] = 0x0ff & (byte) set_hexa;
	}
	else
	{
		return -1;
	}

	s_data[i_db++] = _Get_CheckSum(s_data,i_db);
	s_data[i_db++] = ETX;

	// ...
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_msg = "_Check_Command() ... \n";
		log_msg += "  > ";

		for(int i=0; i<i_db; i++)
		{
			log_bff.Format("%02X ", 0x0ff&s_data[i]);
			log_msg += log_bff;
		}
		log_msg += "\n";

		printf(log_msg);
	}
	return 1;
}
