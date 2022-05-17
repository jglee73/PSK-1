#include "StdAfx.h"
#include "CObj__AFC_RTU.h"
#include "CObj__AFC_RTU__DEF.h"


//------------------------------------------------------------------------------------
int CObj__AFC_RTU
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__AFC_RTU
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	return -1;
}

int CObj__AFC_RTU
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString log_msg;
	CString log_bff;

	// ...
	CString ch_data;

	unsigned char s_data[256];	
	int data_len;

	if((siCH__Matcher_State->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__Load_Position->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__Tune_Position->Check__VARIABLE_NAME(var_name) > 0)
	|| (siCH__VPP->Check__VARIABLE_NAME(var_name)   > 0)
	|| (siCH__VRMS->Check__VARIABLE_NAME(var_name)  > 0)
	|| (siCH__IRMS->Check__VARIABLE_NAME(var_name)  > 0)
	|| (siCH__Phase->Check__VARIABLE_NAME(var_name) > 0))
	{
		unsigned char addr_id = iPara__Slave_ID;
		unsigned char cmmd_id = _CMMD_ID__READ;
		unsigned int  start_addr;
		unsigned char read_num = 1;
		int i;

		if(siCH__Matcher_State->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 0;
		}
		else if(siCH__Load_Position->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 1;
		}
		else if(siCH__Tune_Position->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 2;
		}
		else if(siCH__VPP->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 3;
		}
		else if(siCH__VRMS->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 5;
		}
		else if(siCH__IRMS->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 6;
		}
		else if(siCH__Phase->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 7;
		}

		data_len = _Make__READ_PACKET(s_data, addr_id,cmmd_id, start_addr, read_num);

		// ...
		{
			log_msg.Format(" [%s] ->> ", var_name);

			for(i=0; i<data_len; i++)
			{
				log_bff.Format("[%02X] ", s_data[i]);
				log_msg += log_bff;
			}

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}

		data_len = _Recv__READ_PACKET(s_data, data_len);

		// ...
		{
			log_msg.Format(" [%1d] <<- ", data_len);
			for(i=0; i<data_len; i++)
			{
				log_bff.Format("[%02X] ", s_data[i]);
				log_msg += log_bff;
			}

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}

		if(data_len < 0)
		{
			read_data = STR__OFFLINE;
			bActive__COMM_ONLINE = false;
			return 1;
		}
		if(data_len < 5)
		{
			unsigned char err_code = s_data[2];
			
			ch_data.Format("%02X", err_code);
			sCH__MON_ERROR_CODE->Set__DATA(ch_data);

			ch_data = _Get__Error_Code(err_code);
			sCH__MON_ERROR_MSG->Set__DATA(ch_data);

			// ...
			{
				log_msg.Format(" Error Info ... \n");

				log_bff.Format(" * %s <- %s \n",
								sCH__MON_ERROR_CODE->Get__VARIABLE_NAME(),
								sCH__MON_ERROR_CODE->Get__STRING());
				log_msg += log_bff;

				log_bff.Format(" * %s <- %s \n",
								sCH__MON_ERROR_MSG->Get__VARIABLE_NAME(),
								sCH__MON_ERROR_MSG->Get__STRING());
				log_msg += log_bff;

				xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
			}

			//
			read_data = STR__ERROR;
			bActive__COMM_ONLINE = true;
			return 1;
		}

		// ...
		int off_i = 3;
		unsigned char byte_00 = s_data[off_i + 0];
		unsigned char byte_01 = s_data[off_i + 1];

		JG_I2 get_i;
		get_i.cData[1] = byte_00;
		get_i.cData[0] = byte_01;

		JG_UI2 get_ui;
		get_ui.uData[1] = byte_00;
		get_ui.uData[0] = byte_01;

		//
		if(siCH__Matcher_State->Check__VARIABLE_NAME(var_name) > 0)
		{
			// Bit : 00 ~ 07
			{
				unsigned char byte_bit = byte_00;

				if(0x01 & byte_bit)			dCH__MON_MAT_STS_MANUAL_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_MANUAL_ACTIVE->Set__DATA(STR__OFF);

				if(0x02 & byte_bit)			dCH__MON_MAT_STS_PRESET_ENABLE_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_PRESET_ENABLE_ACTIVE->Set__DATA(STR__OFF);

				if(0x04 & byte_bit)			dCH__MON_MAT_STS_ALARM_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_ALARM_ACTIVE->Set__DATA(STR__OFF);

				if(0x08 & byte_bit)			dCH__MON_MAT_STS_RFON_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_RFON_ACTIVE->Set__DATA(STR__OFF);

				if(0x10 & byte_bit)			dCH__MON_MAT_STS_TUNE_MATCHED_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_TUNE_MATCHED_ACTIVE->Set__DATA(STR__OFF);
			}
			// Bit : 08 ~ 15
			{
				unsigned char byte_bit = byte_01;

				if(0x01 & byte_bit)			dCH__MON_MAT_STS_COAXIAL_ALARM_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_COAXIAL_ALARM_ACTIVE->Set__DATA(STR__OFF);

				if(0x04 & byte_bit)			dCH__MON_MAT_STS_COVER_ALARM_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_COVER_ALARM_ACTIVE->Set__DATA(STR__OFF);

				if(0x08 & byte_bit)			dCH__MON_MAT_STS_MOTOR_ALARM_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_MOTOR_ALARM_ACTIVE->Set__DATA(STR__OFF);

				if(0x10 & byte_bit)			dCH__MON_MAT_STS_FAN1_ALARM_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_FAN1_ALARM_ACTIVE->Set__DATA(STR__OFF);

				if(0x20 & byte_bit)			dCH__MON_MAT_STS_FAN2_ALARM_ACTIVE->Set__DATA(STR__ON);
				else						dCH__MON_MAT_STS_FAN2_ALARM_ACTIVE->Set__DATA(STR__OFF);
			}
		}
		else if(siCH__Load_Position->Check__VARIABLE_NAME(var_name) > 0)
		{
			ch_data.Format("%.2f", (get_i.iValue / 100.0));
			sCH__MON_CUR_LOAD_POSITION->Set__DATA(ch_data);
		}
		else if(siCH__Tune_Position->Check__VARIABLE_NAME(var_name) > 0)
		{
			ch_data.Format("%.2f", (get_i.iValue / 100.0));
			sCH__MON_CUR_TUNE_POSITION->Set__DATA(ch_data);
		}
		else if(siCH__VPP->Check__VARIABLE_NAME(var_name) > 0)
		{
			ch_data.Format("%1d", get_ui.uiValue);
			sCH__MON_CUR_VPP->Set__DATA(ch_data);
		}
		else if(siCH__VRMS->Check__VARIABLE_NAME(var_name) > 0)
		{
			ch_data.Format("%1d", get_ui.uiValue);
			sCH__MON_CUR_VRMS->Set__DATA(ch_data);
		}
		else if(siCH__IRMS->Check__VARIABLE_NAME(var_name) > 0)
		{
			ch_data.Format("%1d", get_ui.uiValue);
			sCH__MON_CUR_IRMS->Set__DATA(ch_data);
		}
		else if(siCH__Phase->Check__VARIABLE_NAME(var_name) > 0)
		{
			ch_data.Format("%.2f", (get_i.iValue / 10.0));
			sCH__MON_CUR_Phase->Set__DATA(ch_data);
		}

		read_data.Format("%02X %02X", byte_00,byte_01);
		bActive__COMM_ONLINE = true;
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__AFC_RTU
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString log_msg;
	CString log_bff;

	unsigned char s_data[256];	
	int data_len;

	if((aoCH__Preset_Load_Position->Check__VARIABLE_NAME(var_name) > 0)
	|| (aoCH__Preset_Tune_Position->Check__VARIABLE_NAME(var_name) > 0))
	{
		unsigned char addr_id = iPara__Slave_ID;
		unsigned char cmmd_id = _CMMD_ID__WRITE;
		unsigned int  start_addr = 0;
		unsigned int  write_num  = 1;	
		int i;

		if(aoCH__Preset_Load_Position->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 10001;
		}
		else if(aoCH__Preset_Tune_Position->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 10002;
		}

		//
		short int set_i = (int) (set_data * 100.0);

		data_len = _Make__WRITE_PACKET(s_data, addr_id,cmmd_id, start_addr, write_num, _DATA_TYPE__I2, 0, set_i);

		// ...
		{
			log_msg.Format(" [%s] ->> ", var_name);

			for(i=0; i<data_len; i++)
			{
				log_bff.Format("[%02X] ", s_data[i]);
				log_msg += log_bff;
			}

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}

		//
		data_len = _Recv__READ_PACKET(s_data, data_len);

		// ...
		{
			log_msg.Format(" [%1d] <<- ", data_len);

			for(i=0; i<data_len; i++)
			{
				log_bff.Format("[%02X] ", s_data[i]);
				log_msg += log_bff;
			}

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}

		if(data_len < 0)
		{
			return -1;
		}

		return 1;
	}

	return -1;
}

int CObj__AFC_RTU
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString log_msg;
	CString log_bff;

	unsigned char s_data[256];	
	int data_len;

	if(doCH__OP_Mode->Check__VARIABLE_NAME(var_name) > 0)
	{
		unsigned char addr_id = iPara__Slave_ID;
		unsigned char cmmd_id = _CMMD_ID__WRITE;
		unsigned int  start_addr;
		unsigned int  write_num  = 1;	
		unsigned short ui_data;
		int i;

		if(doCH__OP_Mode->Check__VARIABLE_NAME(var_name) > 0)
		{
			start_addr = 10000;
			ui_data = 0x00;

			if(dCH__PARA_DRV_CTRL_MODE->Check__DATA(STR__MANUAL) > 0)		ui_data += 0x01;
			if(dCH__PARA_DRV_PRESET->Check__DATA(STR__ENABLE) > 0)			ui_data += 0x02;

		}

		//
		data_len = _Make__WRITE_PACKET(s_data, addr_id,cmmd_id, start_addr, write_num, _DATA_TYPE__UI2, ui_data, 0);

		// ...
		{
			log_msg.Format(" [%s] ->> ", var_name);
			
			for(i=0; i<data_len; i++)
			{
				log_bff.Format("[%02X] ", s_data[i]);
				log_msg += log_bff;
			}

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}

		//
		data_len = _Recv__READ_PACKET(s_data, data_len);

		// ...
		{
			log_msg.Format(" [%1d] <<- ", data_len);
			
			for(i=0; i<data_len; i++)
			{
				log_bff.Format("[%02X] ", s_data[i]);
				log_msg += log_bff;
			}

			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);
		}

		if(data_len < 0)
		{
			return -1;
		}

		return 1;
	}

	return -1;
}

int CObj__AFC_RTU
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
