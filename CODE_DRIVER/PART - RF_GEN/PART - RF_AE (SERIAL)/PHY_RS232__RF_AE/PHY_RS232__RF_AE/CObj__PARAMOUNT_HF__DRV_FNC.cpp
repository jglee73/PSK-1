#include "StdAfx.h"
#include "CObj__PARAMOUNT_HF.h"


#define _DRV_CMMD__SET_RF_OFF								1
#define _DRV_CMMD__SET_RF_ON								2
#define _DRV_CMMD__SET_REGULATION_MODE						3
#define _DRV_CMMD__SET_POWER_SETPOINT						8
#define _DRV_CMMD__SET_ACTIVE_CONTROL_MODE					14

#define _DRV_CMMD__REPORT_ACTIVE_CONTROL_MODE				155
#define _DRV_CMMD__REPORT_PROCESS_STATUS					162
#define _DRV_CMMD__REPORT_SETPOINT_REGULATION				164
#define _DRV_CMMD__REPORT_FORWARD_POWER						165
#define _DRV_CMMD__REPORT_REFLECTED_POWER					166
#define _DRV_CMMD__REPORT_DELIVERED_POWER					167


//------------------------------------------------------------------------------------
int CObj__PARAMOUNT_HF
::__Read__ANALOG(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__PARAMOUNT_HF
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__PARAMOUNT_HF
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = iUNIT__ADDR_ID;


	if((siCH__CTRL_MODE_HEXA->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__SETPOINT_REGULATION_HEXA->Check__VARIABLE_NAME(var_name)  > 0)
	|| (siCH__REPORT_FORWARD_POWER_HEXA->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__REPORT_REFLECTED_POWER_HEXA->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__REPORT_DELIVERED_POWER_HEXA->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0;
		byte s_data_len = 0;
		byte r_data_len = 0;

		if(siCH__CTRL_MODE_HEXA->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__REPORT_ACTIVE_CONTROL_MODE;
			s_data_len = 0;
			r_data_len = 1;
		}
		else if(siCH__SETPOINT_REGULATION_HEXA->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__REPORT_SETPOINT_REGULATION;
			s_data_len = 0;
			r_data_len = 3;
		}
		else if(siCH__REPORT_FORWARD_POWER_HEXA->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__REPORT_FORWARD_POWER;
			s_data_len = 0;
			r_data_len = 2;
		}
		else if(siCH__REPORT_REFLECTED_POWER_HEXA->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__REPORT_REFLECTED_POWER;
			s_data_len = 0;
			r_data_len = 2;
		}
		else if(siCH__REPORT_DELIVERED_POWER_HEXA->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__REPORT_DELIVERED_POWER;
			s_data_len = 0;
			r_data_len = 2;
		}
		else
		{
			return -1;
		}

		int r_len = _Recv__Command(addr_id,cmmd_id,s_data_len,r_data_len,r_data);		
		if(r_len >= r_data_len)
		{
			if(cmmd_id == _DRV_CMMD__REPORT_ACTIVE_CONTROL_MODE)
			{
				byte byte_00 = 0x0ff & r_data[0];

				//
				CString str_mode = "";

				switch(byte_00)
				{
					case 2:		str_mode = STR__HOST;			break;
					case 4:		str_mode = STR__ANALOG;			break;
					case 8:		str_mode = STR__DIAGNOSTIC;		break;
					case 16:	str_mode = STR__DEVICENET;		break;
					case 32:	str_mode = STR__ETHERCET32;		break;

					default:	str_mode = STR__UNKNOWN;		break;
				}

				sCH__INFO_CTRL_MODE_READ->Set__DATA(str_mode);

				//
				read_data.Format("%02X", byte_00);
			}
			else if(cmmd_id == _DRV_CMMD__REPORT_SETPOINT_REGULATION)
			{
				byte byte_00 = 0x0ff & r_data[0];
				byte byte_01 = 0x0ff & r_data[1];
				byte byte_02 = 0x0ff & r_data[2];

				//
				int value  = (int) (0x0FF & byte_01);
				value = value << 8;
				value += (int) (0x0FF & byte_00);

				ch_data.Format("%1d", value);
				sCH__INFO_POWER_SETPOINT_READ->Set__DATA(ch_data);

				//
				CString str_regulation = "";

				switch(byte_02)
				{
					case 6:		str_regulation = STR__FORWARD;		break;
					case 7:		str_regulation = STR__LOAD;			break;
					case 8:		str_regulation = STR__EXTERNAL;		break;
					case 9:		str_regulation = STR__VA_LIMIT;		break;

					default:	str_regulation = STR__UNKNOWN;		break;
				}

				sCH__INFO_REGULATION_MODE_READ->Set__DATA(str_regulation);

				//
				read_data.Format("%02X%02X %02X", byte_00,byte_01,byte_02);
			}
			else if((cmmd_id == _DRV_CMMD__REPORT_FORWARD_POWER)
			     || (cmmd_id == _DRV_CMMD__REPORT_REFLECTED_POWER)
				 || (cmmd_id == _DRV_CMMD__REPORT_DELIVERED_POWER))
			{
				byte byte_00 = 0x0ff & r_data[0];
				byte byte_01 = 0x0ff & r_data[1];

				int value  = (int) (0x0FF & byte_01);
				value = value << 8;
				value += (int) (0x0FF & byte_00);

				ch_data.Format("%1d", value);

					 if(cmmd_id == _DRV_CMMD__REPORT_FORWARD_POWER)			sCH__INFO_FORWARD_POWER_READ->Set__DATA(ch_data);
				else if(cmmd_id == _DRV_CMMD__REPORT_REFLECTED_POWER)		sCH__INFO_REFLECTED_POWER_READ->Set__DATA(ch_data);
				else if(cmmd_id == _DRV_CMMD__REPORT_DELIVERED_POWER)		sCH__INFO_DELIVERED_POWER_READ->Set__DATA(ch_data);

				read_data.Format("%02X%02X", byte_00,byte_01);
			}
		}
		else
		{
			read_data = "ERROR";
		}
		return 1;
	}

	if(siCH__REPORT_PROCESS_STATUS_HEXA->Check__VARIABLE_NAME(var_name) > 0)
	{
		byte cmmd_id = _DRV_CMMD__REPORT_PROCESS_STATUS;
		byte s_data_len = 0;
		byte r_data_len = 4;

		int r_len = _Recv__Command(addr_id,cmmd_id,s_data_len,r_data_len,r_data);		
		if(r_len >= r_data_len)
		{
			byte byte_00 = 0x0ff & r_data[0];
			byte byte_01 = 0x0ff & r_data[1];
			byte byte_02 = 0x0ff & r_data[2];
			byte byte_03 = 0x0ff & r_data[3];

			// BYTE : 0
			{
				byte b_hexa = byte_00;

				// BIT 0
				if(b_hexa & 0x01)		sCH__INFO_STS_TUNING->Set__DATA(STR__ON);
				else					sCH__INFO_STS_TUNING->Set__DATA(STR__OFF);

				// BIT 1
				if(b_hexa & 0x02)		sCH__INFO_STS_SETPOINT_RAMPING->Set__DATA(STR__ON);
				else					sCH__INFO_STS_SETPOINT_RAMPING->Set__DATA(STR__OFF);

				// BIT 2
				if(b_hexa & 0x04)		sCH__INFO_STS_RECIPE_ACTIVE->Set__DATA(STR__ON);
				else					sCH__INFO_STS_RECIPE_ACTIVE->Set__DATA(STR__OFF);

				// BIT 3
				if(b_hexa & 0x08)		sCH__INFO_STS_RECIPE_ENABLED->Set__DATA(STR__ON);
				else					sCH__INFO_STS_RECIPE_ENABLED->Set__DATA(STR__OFF);

				// BIT 4 : Reserved 
 
				// BIT 5
				if(b_hexa & 0x20)		sCH__INFO_STS_RF_OUTPUT_ON->Set__DATA(STR__ON);
				else					sCH__INFO_STS_RF_OUTPUT_ON->Set__DATA(STR__OFF);

				// BIT 6
				if(b_hexa & 0x40)		sCH__INFO_STS_RF_ON_REQUESTED->Set__DATA(STR__ON);
				else					sCH__INFO_STS_RF_ON_REQUESTED->Set__DATA(STR__OFF);

				// BIT 7
				if(b_hexa & 0x80)		sCH__INFO_STS_SETPOINT_TOLERANCE->Set__DATA(STR__ON);
				else					sCH__INFO_STS_SETPOINT_TOLERANCE->Set__DATA(STR__OFF);
			}

			// BYTE : 1
			{
				byte b_hexa = byte_01;

				// BIT 0 to 2 : Reserved

				// BIT 3
				if(b_hexa & 0x08)		sCH__INFO_STS_OVERTEMPERATURE_FAULT->Set__DATA(STR__ON);
				else					sCH__INFO_STS_OVERTEMPERATURE_FAULT->Set__DATA(STR__OFF);

				// BIT 4
				if(b_hexa & 0x10)		sCH__INFO_STS_FREQUENCY_VARIABLE_MODE->Set__DATA(STR__ON);
				else					sCH__INFO_STS_FREQUENCY_VARIABLE_MODE->Set__DATA(STR__OFF);

				// BIT 5
				if(b_hexa & 0x20)		sCH__INFO_STS_PULSING_EMABLED->Set__DATA(STR__ON);
				else					sCH__INFO_STS_PULSING_EMABLED->Set__DATA(STR__OFF);

				// BIT 6
				if(b_hexa & 0x40)		sCH__INFO_STS_ARC_MANAGEMENT_ENABLED->Set__DATA(STR__ON);
				else					sCH__INFO_STS_ARC_MANAGEMENT_ENABLED->Set__DATA(STR__OFF);

				// BIT 7
				if(b_hexa & 0x80)		sCH__INFO_STS_INTERLOCK_OPEN->Set__DATA(STR__ON);
				else					sCH__INFO_STS_INTERLOCK_OPEN->Set__DATA(STR__OFF);
			}

			// BYTE : 2
			{
				byte b_hexa = byte_02;

				// BIT 0 to 1 : Reserved

				// BIT 2
				if(b_hexa & 0x04)		sCH__INFO_STS_HIGH_AC_LINE_VOLTAGE_WARNING->Set__DATA(STR__ON);
				else					sCH__INFO_STS_HIGH_AC_LINE_VOLTAGE_WARNING->Set__DATA(STR__OFF);

				// BIT 3 : Reserved

				// BIT 4
				if(b_hexa & 0x10)		sCH__INFO_STS_LOW_AC_LINE_VOLTAGE_WARNING->Set__DATA(STR__ON);
				else					sCH__INFO_STS_LOW_AC_LINE_VOLTAGE_WARNING->Set__DATA(STR__OFF);

				// BIT 5
				if(b_hexa & 0x20)		sCH__INFO_STS_PROTECTION_LIMIT->Set__DATA(STR__ON);
				else					sCH__INFO_STS_PROTECTION_LIMIT->Set__DATA(STR__OFF);

				// BIT 6 to 7 : Reserved
			}

			// BYTE : 3
			{
				byte b_hexa = byte_02;

				// BIT 0 : Reserved

				// BIT 1
				if(b_hexa & 0x02)		sCH__INFO_STS_INVERTER_NOT_READY->Set__DATA(STR__ON);
				else					sCH__INFO_STS_INVERTER_NOT_READY->Set__DATA(STR__OFF);

				// BIT 2
				if(b_hexa & 0x04)		sCH__INFO_STS_FIELD_BUS_ERROR->Set__DATA(STR__ON);
				else					sCH__INFO_STS_FIELD_BUS_ERROR->Set__DATA(STR__OFF);

				// BIT 3 : Reserved

				// BIT 4
				if(b_hexa & 0x10)		sCH__INFO_STS_CEX_ENABLED->Set__DATA(STR__ON);
				else					sCH__INFO_STS_CEX_ENABLED->Set__DATA(STR__OFF);

				// BIT 5
				if(b_hexa & 0x20)		sCH__INFO_STS_FAULT_PRESENT->Set__DATA(STR__ON);
				else					sCH__INFO_STS_FAULT_PRESENT->Set__DATA(STR__OFF);

				// BIT 6
				if(b_hexa & 0x40)		sCH__INFO_STS_WARNING_PRESENT->Set__DATA(STR__ON);
				else					sCH__INFO_STS_WARNING_PRESENT->Set__DATA(STR__OFF);

				// BIT 7
				if(b_hexa & 0x80)		sCH__INFO_STS_CEX_LOCKED->Set__DATA(STR__ON);
				else					sCH__INFO_STS_CEX_LOCKED->Set__DATA(STR__OFF);
			}

			read_data.Format("%02X %02X %02X %02X", byte_00,byte_01,byte_02,byte_03);
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
int CObj__PARAMOUNT_HF
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;
	
	byte addr_id = iUNIT__ADDR_ID;


	if(aoCH__POWER_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		byte cmmd_id = _DRV_CMMD__SET_POWER_SETPOINT;
		byte s_data_len = 2;
		byte r_data_len = 1;

		int r_len = _Recv__Command(addr_id,cmmd_id,s_data_len,r_data_len, r_data,(int) set_data);		
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

int CObj__PARAMOUNT_HF
::__Write__DIGITAL(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	unsigned char r_data[MAX_CHAR] = {0,};
	CString ch_data;

	byte addr_id = iUNIT__ADDR_ID;


	if((doCH__POWER_MODE->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__CTRL_MODE->Check__VARIABLE_NAME(var_name)  > 0)
	|| (doCH__REGULATION_MODE->Check__VARIABLE_NAME(var_name) > 0))
	{
		byte cmmd_id = 0;
		byte s_data_len = 0;
		byte r_data_len = 0;
		BYTE set_mode = 0;

		if(doCH__POWER_MODE->Check__VARIABLE_NAME(var_name) > 0)
		{
			s_data_len = 0;
			r_data_len = 1;

				 if(set_data.CompareNoCase(STR__ON)  == 0)				cmmd_id = _DRV_CMMD__SET_RF_ON;
			else if(set_data.CompareNoCase(STR__OFF) == 0)				cmmd_id = _DRV_CMMD__SET_RF_OFF;
			else														return -1;
		}
		else if(doCH__CTRL_MODE->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__SET_ACTIVE_CONTROL_MODE;

			s_data_len = 1;
			r_data_len = 1;

				 if(set_data.CompareNoCase(STR__HOST)   == 0)			set_mode = 2;
			else if(set_data.CompareNoCase(STR__ANALOG) == 0)			set_mode = 4;
			else if(set_data.CompareNoCase(STR__DIAGNOSTIC) == 0)		set_mode = 8;
			else if(set_data.CompareNoCase(STR__DEVICENET)  == 0)		set_mode = 16;
			else if(set_data.CompareNoCase(STR__ETHERCET32) == 0)		set_mode = 32;
			else														return -1;
		}
		else if(doCH__REGULATION_MODE->Check__VARIABLE_NAME(var_name) > 0)
		{
			cmmd_id = _DRV_CMMD__SET_REGULATION_MODE;
			s_data_len = 1;
			r_data_len = 1;

				 if(set_data.CompareNoCase(STR__FORWARD)  == 0)			set_mode = 6;
			else if(set_data.CompareNoCase(STR__LOAD)     == 0)			set_mode = 7;
			else if(set_data.CompareNoCase(STR__EXTERNAL) == 0)			set_mode = 8;
			else if(set_data.CompareNoCase(STR__VA_LIMIT) == 0)			set_mode = 9;
			else														return -1;
		}
		else
		{
			return -11;
		}

		int r_len = _Recv__Command(addr_id,cmmd_id,s_data_len,r_data_len, r_data,set_mode);		
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

int CObj__PARAMOUNT_HF
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}

