#include "StdAfx.h"
#include "CObj__NAVII_SERIAL.h"


#define _DRV_CMMD__SET_ALL_CAPACITOR_INIT					125
#define _DRV_CMMD__SET_CAPACITOR_LIMIT						84
#define _DRV_CMMD__SET_INTERNAL_EXTERNAL_PRESET             97
#define _DRV_CMMD__SET_ACTIVE_PRESET						91
#define _DRV_CMMD__SET_CONTROL_MODE							93
#define _DRV_CMMD__SET_LOAD_POS								112
#define _DRV_CMMD__SET_TUNE_POS								122
#define _DRV_CMMD__SET_CAPACITOR_MOTOR_POS					124

#define _DRV_CMMD__REPORT_CONTROL_MODE						163
#define _DRV_CMMD__REPORT_CAPACITOR_POS						180


//------------------------------------------------------------------------------------
int CObj__NAVII_SERIAL
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__NAVII_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__NAVII_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	unsigned char s_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = (byte) aCH__CFG_PART_ADDRES_ID->Get__VALUE();


	if((siCH__CTRL_MODE_HEXA_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__CTRL_MODE_HEXA_CH2->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__CAPACITOR_POS_HEXA_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__CAPACITOR_POS_HEXA_CH2->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0;
		byte s_data_len = 0;
		byte r_data_len = 0;

		int para_id  = 0;

		if((siCH__CTRL_MODE_HEXA_CH1->Check__VARIABLE_NAME(var_name) > 0)
		|| (siCH__CTRL_MODE_HEXA_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__REPORT_CONTROL_MODE;
			s_data_len = 2;
			r_data_len = 4;

				 if(siCH__CTRL_MODE_HEXA_CH1->Check__VARIABLE_NAME(var_name) > 0)			para_id = 1;
			else if(siCH__CTRL_MODE_HEXA_CH2->Check__VARIABLE_NAME(var_name) > 0)			para_id = 2;
			else																			return -1;

			s_data[0] = 0x0ff & para_id;
			s_data[1] = 0x00;
		}
		else if((siCH__CAPACITOR_POS_HEXA_CH1->Check__VARIABLE_NAME(var_name) > 0)
			 || (siCH__CAPACITOR_POS_HEXA_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__REPORT_CAPACITOR_POS;
			s_data_len = 2;
			r_data_len = 6;

				 if(siCH__CAPACITOR_POS_HEXA_CH1->Check__VARIABLE_NAME(var_name) > 0)		para_id = 1;
			else if(siCH__CAPACITOR_POS_HEXA_CH2->Check__VARIABLE_NAME(var_name) > 0)		para_id = 2;
			else																			return -1;

			s_data[0] = 0x0ff & para_id;
			s_data[1] = 0x00;
		}
		else
		{
			return -11;
		}

		int r_len = _Recv__Command(var_name, addr_id,cmmd_id,s_data_len,r_data_len, s_data,r_data);		
		if(r_len >= r_data_len)
		{
			if(cmmd_id == _DRV_CMMD__REPORT_CONTROL_MODE)
			{
				byte byte_00 = 0x0ff & r_data[0];
				byte byte_01 = 0x0ff & r_data[1];
				byte byte_02 = 0x0ff & r_data[2];
				byte byte_03 = 0x0ff & r_data[3];

				//
				CString str_mode = "";

				switch(byte_02)
				{
					case 0:		str_mode = STR__USER;			break;
					case 1:		str_mode = STR__AUTO;			break;
					case 2:		str_mode = STR__HOST;			break;

					default:	str_mode = STR__UNKNOWN;		break;
				}

					 if(para_id == 1)		sCH__INFO_CTRL_MODE_CH1->Set__DATA(str_mode);
				else if(para_id == 2)		sCH__INFO_CTRL_MODE_CH2->Set__DATA(str_mode);

				//
				read_data.Format("%02X%02X %02X%02X", byte_00, byte_01, byte_02, byte_03);
			}
			else if(cmmd_id == _DRV_CMMD__REPORT_CAPACITOR_POS)
			{
				byte byte_00 = 0x0ff & r_data[0];
				byte byte_01 = 0x0ff & r_data[1];
				byte byte_02 = 0x0ff & r_data[2];
				byte byte_03 = 0x0ff & r_data[3];
				byte byte_04 = 0x0ff & r_data[4];
				byte byte_05 = 0x0ff & r_data[5];

				//
				CString str__pos_load;
				CString str__pos_tune;
				int val__pos_load = 0;
				int val__pos_tune = 0;

				val__pos_load  = 0x0ff & byte_03;
				val__pos_load  = val__pos_load << 8;
				val__pos_load += 0x0ff & byte_02;
				str__pos_load.Format("%.2f", (double) val__pos_load / 100.0);

				val__pos_tune  = 0x0ff & byte_05;
				val__pos_tune  = val__pos_tune << 8;
				val__pos_tune += 0x0ff & byte_04;
				str__pos_tune.Format("%.2f", (double) val__pos_tune / 100.0);

			    if(para_id == 1)
				{
					sCH__INFO_LOAD_POS_CH1->Set__DATA(str__pos_load);
					sCH__INFO_TUNE_POS_CH1->Set__DATA(str__pos_tune);
				}
				else if(para_id == 2)
				{
					sCH__INFO_LOAD_POS_CH2->Set__DATA(str__pos_load);
					sCH__INFO_TUNE_POS_CH2->Set__DATA(str__pos_tune);
				}

				//
				read_data.Format("%02X%02X %02X%02X %02X%02X", byte_00,byte_01, byte_02,byte_03, byte_04,byte_05);
			}
		}
		else
		{
			read_data = "ERROR";
		}
		return 1;
	}

	return -1;
}

//------------------------------------------------------------------------------------
int CObj__NAVII_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{

	return -1;
}

int CObj__NAVII_SERIAL
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	unsigned char s_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = (byte) aCH__CFG_PART_ADDRES_ID->Get__VALUE();

	
	if(doCH__ALL_CAPACITOR_INIT->Check__VARIABLE_NAME(var_name) > 0)
	{
		byte cmmd_id = _DRV_CMMD__SET_ALL_CAPACITOR_INIT;
		byte s_data_len = 0;
		byte r_data_len = 1;

		int r_len = _Recv__Command(var_name, addr_id,cmmd_id,s_data_len,r_data_len, s_data,r_data);		
		if(r_len >= r_data_len)
		{
			byte byte_00 = 0x0ff & r_data[0];
			if(byte_00 == 0)			return 1;

			ch_data.Format("%02X", byte_00);
			sCH__INFO_CSR_HEXA->Set__DATA(ch_data);

			ch_data = _Get__CSR_CODE(byte_00);
			sCH__INFO_CSR_MSG->Set__DATA(ch_data);
		}
		return -1;
	}

	if((doCH__CAPACITOR_LIMIT_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__CAPACITOR_LIMIT_CH2->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = _DRV_CMMD__SET_CAPACITOR_LIMIT;
		byte s_data_len = 10;
		byte r_data_len = 1;

		int para_id  = 0;
		int para_load_min = 0;
		int para_load_max = 0;
		int para_tune_min = 0;
		int para_tune_max = 0;

		if(doCH__CAPACITOR_LIMIT_CH1->Check__VARIABLE_NAME(var_name) > 0)
		{
			para_id = 1;
			para_load_min = (int) aCH__CFG_LOAD_MIN_CH1->Get__VALUE();
			para_load_max = (int) aCH__CFG_LOAD_MAX_CH1->Get__VALUE();
			para_tune_min = (int) aCH__CFG_TUNE_MIN_CH1->Get__VALUE();
			para_tune_max = (int) aCH__CFG_TUNE_MAX_CH1->Get__VALUE();
		}
		else if(doCH__CAPACITOR_LIMIT_CH2->Check__VARIABLE_NAME(var_name) > 0)
		{
			para_id = 2;
			para_load_min = (int) aCH__CFG_LOAD_MIN_CH2->Get__VALUE();
			para_load_max = (int) aCH__CFG_LOAD_MAX_CH2->Get__VALUE();
			para_tune_min = (int) aCH__CFG_TUNE_MIN_CH2->Get__VALUE();
			para_tune_max = (int) aCH__CFG_TUNE_MAX_CH2->Get__VALUE();
		}
		else
		{
			return -1;
		}

		s_data[0] = 0x0ff & para_id;
		s_data[1] = 0x00;
		
		s_data[2] = 0x0ff & para_load_min;
		s_data[3] = 0x0ff & (para_load_min >> 8);
		s_data[4] = 0x0ff & para_load_max;
		s_data[5] = 0x0ff & (para_load_max >> 8);

		s_data[6] = 0x0ff & para_tune_min;
		s_data[7] = 0x0ff & (para_tune_min >> 8);
		s_data[8] = 0x0ff & para_tune_max;
		s_data[9] = 0x0ff & (para_tune_max >> 8);

		int r_len = _Recv__Command(var_name, addr_id,cmmd_id,s_data_len,r_data_len, s_data,r_data);		
		if(r_len >= r_data_len)
		{
			byte byte_00 = 0x0ff & r_data[0];
			if(byte_00 == 0)			return 1;

			ch_data.Format("%02X", byte_00);
			sCH__INFO_CSR_HEXA->Set__DATA(ch_data);

			ch_data = _Get__CSR_CODE(byte_00);
			sCH__INFO_CSR_MSG->Set__DATA(ch_data);
		}
		return -1;
	}

	if((doCH__CONTROL_MODE_CH1->Check__VARIABLE_NAME(var_name)  > 0)
	|| (doCH__CONTROL_MODE_CH2->Check__VARIABLE_NAME(var_name)  > 0)
	|| (doCH__ACTIVE_PRESET_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__ACTIVE_PRESET_CH2->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__INTERNAL_EXTERNAL_PRESET_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__INTERNAL_EXTERNAL_PRESET_CH2->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0;
		byte s_data_len = 4;
		byte r_data_len = 1;

		int para_id  = 0;
		int para_set = 0;

		if((doCH__CONTROL_MODE_CH1->Check__VARIABLE_NAME(var_name) > 0)
		|| (doCH__CONTROL_MODE_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__SET_CONTROL_MODE;

				 if(doCH__CONTROL_MODE_CH1->Check__VARIABLE_NAME(var_name) > 0)			para_id = 1;
			else if(doCH__CONTROL_MODE_CH2->Check__VARIABLE_NAME(var_name) > 0)			para_id = 2;

				 if(set_data.CompareNoCase(STR__USER) == 0)			para_set = 0;
			else if(set_data.CompareNoCase(STR__AUTO) == 0)			para_set = 1;	
			else if(set_data.CompareNoCase(STR__HOST) == 0)			para_set = 2;	
			else													return -11;
		}
		else if((doCH__ACTIVE_PRESET_CH1->Check__VARIABLE_NAME(var_name) > 0)
			 || (doCH__ACTIVE_PRESET_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__SET_ACTIVE_PRESET;

			if(doCH__ACTIVE_PRESET_CH1->Check__VARIABLE_NAME(var_name) > 0)
			{
				para_id = 1;
				para_set = (int) aCH__PARA_ACTIVE_PRESET_CH1->Get__VALUE();
			}
			else if(doCH__ACTIVE_PRESET_CH2->Check__VARIABLE_NAME(var_name) > 0)
			{
				para_id = 2;
				para_set = (int) aCH__PARA_ACTIVE_PRESET_CH2->Get__VALUE();			
			}
		}
		else if((doCH__INTERNAL_EXTERNAL_PRESET_CH1->Check__VARIABLE_NAME(var_name) > 0)
			 || (doCH__INTERNAL_EXTERNAL_PRESET_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__SET_INTERNAL_EXTERNAL_PRESET;

				 if(doCH__INTERNAL_EXTERNAL_PRESET_CH1->Check__VARIABLE_NAME(var_name) > 0)			para_id = 1;
			else if(doCH__INTERNAL_EXTERNAL_PRESET_CH2->Check__VARIABLE_NAME(var_name) > 0)			para_id = 2;

				 if(set_data.CompareNoCase(STR__INTERNAL) == 0)			para_set = 0;
			else if(set_data.CompareNoCase(STR__EXTERNAL) == 0)			para_set = 1;	
			else														return -11;
		}
		else
		{
			return -1;
		}

		s_data[0] = 0x0ff & para_id;
		s_data[1] = 0x00;
		s_data[2] = 0x0ff & para_set;
		s_data[3] = 0x0ff & (para_set >> 8);

		int r_len = _Recv__Command(var_name, addr_id,cmmd_id,s_data_len,r_data_len, s_data,r_data);		
		if(r_len >= r_data_len)
		{
			byte byte_00 = 0x0ff & r_data[0];
			if(byte_00 == 0)			return 1;

			ch_data.Format("%02X", byte_00);
			sCH__INFO_CSR_HEXA->Set__DATA(ch_data);

			ch_data = _Get__CSR_CODE(byte_00);
			sCH__INFO_CSR_MSG->Set__DATA(ch_data);
		}
		return -1;
	}

	if((doCH__LOAD_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__LOAD_POS_CH2->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__TUNE_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__TUNE_POS_CH2->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0;
		byte s_data_len = 4;
		byte r_data_len = 1;

		int para_id = 0;
		int para_pos = 0;

		if((doCH__LOAD_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)
		|| (doCH__LOAD_POS_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__SET_LOAD_POS;

			if(doCH__LOAD_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)		
			{
				para_id = 1;
				para_pos = (int) (100.0 * aCH__PARA_LOAD_POS_CH1->Get__VALUE());

				ch_data.Format("%1d", para_pos);
				sCH__CUR_LOAD_POS_CH1->Set__DATA(ch_data);
			}
			else if(doCH__LOAD_POS_CH2->Check__VARIABLE_NAME(var_name) > 0)
			{
				para_id = 2;
				para_pos = (int) (100.0 * aCH__PARA_LOAD_POS_CH2->Get__VALUE());

				ch_data.Format("%1d", para_pos);
				sCH__CUR_LOAD_POS_CH2->Set__DATA(ch_data);
			}
		}
		else if((doCH__TUNE_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)
			 || (doCH__TUNE_POS_CH2->Check__VARIABLE_NAME(var_name) > 0))
		{
			cmmd_id = _DRV_CMMD__SET_TUNE_POS;

			if(doCH__TUNE_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)		
			{
				para_id = 1;
				para_pos = (int) (100.0 * aCH__PARA_TUNE_POS_CH1->Get__VALUE());

				ch_data.Format("%1d", para_pos);
				sCH__CUR_TUNE_POS_CH1->Set__DATA(ch_data);
			}
			else if(doCH__TUNE_POS_CH2->Check__VARIABLE_NAME(var_name) > 0)
			{
				para_id = 2;
				para_pos = (int) (100.0 * aCH__PARA_TUNE_POS_CH2->Get__VALUE());

				ch_data.Format("%1d", para_pos);
				sCH__CUR_TUNE_POS_CH2->Set__DATA(ch_data);
			}
		}
		else
		{
			return -1;
		}

		s_data[0] = 0x0ff & para_id;
		s_data[1] = 0x00;
		s_data[2] = 0x0ff & para_pos;
		s_data[3] = 0x0ff & (para_pos >> 8);

		int r_len = _Recv__Command(var_name, addr_id,cmmd_id,s_data_len,r_data_len, s_data,r_data);		
		if(r_len >= r_data_len)
		{
			byte byte_00 = 0x0ff & r_data[0];
			if(byte_00 == 0)			return 1;

			ch_data.Format("%02X", byte_00);
			sCH__INFO_CSR_HEXA->Set__DATA(ch_data);

			ch_data = _Get__CSR_CODE(byte_00);
			sCH__INFO_CSR_MSG->Set__DATA(ch_data);
		}
		return -1;
	}

	if((doCH__CAPACITOR_MOTOR_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__CAPACITOR_MOTOR_POS_CH2->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = _DRV_CMMD__SET_CAPACITOR_MOTOR_POS;
		byte s_data_len = 6;
		byte r_data_len = 1;

		int para_id = 0;
		int para_load_pos = 0;
		int para_tune_pos = 0;

		if(doCH__CAPACITOR_MOTOR_POS_CH1->Check__VARIABLE_NAME(var_name) > 0)
		{
			para_id = 1;
			para_load_pos = (int) (100.0 * aCH__PARA_LOAD_POS_CH1->Get__VALUE());
			para_tune_pos = (int) (100.0 * aCH__PARA_TUNE_POS_CH1->Get__VALUE());

			ch_data.Format("%1d", para_load_pos);
			sCH__CUR_LOAD_POS_CH1->Set__DATA(ch_data);

			ch_data.Format("%1d", para_tune_pos);
			sCH__CUR_TUNE_POS_CH1->Set__DATA(ch_data);
		}
		else if(doCH__CAPACITOR_MOTOR_POS_CH2->Check__VARIABLE_NAME(var_name) > 0)
		{
			para_id = 2;
			para_load_pos = (int) (100.0 * aCH__PARA_LOAD_POS_CH2->Get__VALUE());
			para_tune_pos = (int) (100.0 * aCH__PARA_TUNE_POS_CH2->Get__VALUE());

			ch_data.Format("%1d", para_load_pos);
			sCH__CUR_LOAD_POS_CH2->Set__DATA(ch_data);

			ch_data.Format("%1d", para_tune_pos);
			sCH__CUR_TUNE_POS_CH2->Set__DATA(ch_data);
		}
		else
		{
			return -1;
		}

		s_data[0] = 0x0ff & para_id;
		s_data[1] = 0x00;
		s_data[2] = 0x0ff & para_load_pos;
		s_data[3] = 0x0ff & (para_load_pos >> 8);
		s_data[4] = 0x0ff & para_tune_pos;
		s_data[5] = 0x0ff & (para_tune_pos >> 8);

		int r_len = _Recv__Command(var_name, addr_id,cmmd_id,s_data_len,r_data_len, s_data,r_data);		
		if(r_len >= r_data_len)
		{
			byte byte_00 = 0x0ff & r_data[0];
			if(byte_00 == 0)			return 1;

			ch_data.Format("%02X", byte_00);
			sCH__INFO_CSR_HEXA->Set__DATA(ch_data);

			ch_data = _Get__CSR_CODE(byte_00);
			sCH__INFO_CSR_MSG->Set__DATA(ch_data);
		}
		return -1;
	}

	return -1;
}

int CObj__NAVII_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}

