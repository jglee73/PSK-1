#include "StdAfx.h"
#include "CObj__AFC_RTU.h"
#include "CObj__AFC_RTU__ALID.h"
#include "CObj__AFC_RTU__DEF.h"


//-------------------------------------------------------------------------	
int  CObj__AFC_RTU
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

int  CObj__AFC_RTU
::Call__AUTO(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s",  
						aCH__PARA_LOAD_POSITION->Get__CHANNEL_NAME(),
						aCH__PARA_LOAD_POSITION->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s",  
						aCH__PARA_TUNE_POSITION->Get__CHANNEL_NAME(),
						aCH__PARA_TUNE_POSITION->Get__STRING());
		log_msg += log_bff;

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		aCH__PARA_LOAD_POSITION->Get__DATA(ch_data);
		aoCH__Preset_Load_Position->Set__DATA(ch_data);

		aCH__PARA_TUNE_POSITION->Get__DATA(ch_data);
		aoCH__Preset_Tune_Position->Set__DATA(ch_data);

		dCH__PARA_DRV_CTRL_MODE->Set__DATA(STR__AUTO);
		dCH__PARA_DRV_PRESET->Set__DATA(STR__ENABLE);

		doCH__OP_Mode->Set__DATA(STR__ON);
	}
	return 1;
}

int  CObj__AFC_RTU
::Call__MANUAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s",  
						aCH__PARA_LOAD_POSITION->Get__CHANNEL_NAME(),
						aCH__PARA_LOAD_POSITION->Get__STRING());
		log_msg += log_bff;

		log_bff.Format(" * %s <- %s",  
						aCH__PARA_TUNE_POSITION->Get__CHANNEL_NAME(),
						aCH__PARA_TUNE_POSITION->Get__STRING());
		log_msg += log_bff;

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		aCH__PARA_LOAD_POSITION->Get__DATA(ch_data);
		aoCH__Preset_Load_Position->Set__DATA(ch_data);

		aCH__PARA_TUNE_POSITION->Get__DATA(ch_data);
		aoCH__Preset_Tune_Position->Set__DATA(ch_data);

		dCH__PARA_DRV_CTRL_MODE->Set__DATA(STR__MANUAL);
		dCH__PARA_DRV_PRESET->Set__DATA(STR__ENABLE);

		doCH__OP_Mode->Set__DATA(STR__ON);
	}
	return 1;
}


// ...
#define POLYNORMIAL			0xA001

unsigned int CObj__AFC_RTU
::_Make__READ_PACKET(unsigned char* s_data,
				     const unsigned char addr_id,
				     const unsigned char cmmd_id,
				     const unsigned int  start_addr,
					 const unsigned char read_num)
{
	int i = 0;

	s_data[i++] = 0x0ff & addr_id;				// 0
	s_data[i++] = 0x0ff & cmmd_id;				// 1
	s_data[i++] = 0x0ff & (start_addr >> 8);	// 2
	s_data[i++] = 0x0ff & (start_addr >> 0);	// 3
	s_data[i++] = 0x00;							// 4
	s_data[i++] = 0x0ff & read_num;				// 5	

	unsigned short crc = _Get__CRC16(s_data, i);
	/*
	s_data[i++] = 0x0ff & (crc >> 8);			// 6
	s_data[i++] = 0x0ff & (crc >> 0);			// 7		
	*/
	s_data[i++] = 0x0ff & (crc >> 0);			// 6
	s_data[i++] = 0x0ff & (crc >> 8);			// 7		

	return i;
}
unsigned int CObj__AFC_RTU
::_Recv__READ_PACKET(unsigned char* s_data,
					 const int s_len)
{
	CString r_msg;
	mX_Serial->CLEAR__BUFFER(&r_msg);

	// ...
	int s_cmmd = 0x0ff & s_data[1];		// 1
	int s_reg  = 0x0ff & s_data[5];		// 5

	if(mX_Serial->CHAR__SEND(s_data, s_len) < 0)
	{
		return -1;
	}

	// ...
	int r_len;

	if(s_cmmd == _CMMD_ID__READ)
	{
		r_len = 3 + (s_reg * 2);
	}
	else if(s_cmmd == _CMMD_ID__WRITE)
	{
		r_len = 6;
	}

	s_data[0] = 0;
	if(mX_Serial->CHAR__RECV(s_data, &r_len, 500) < 0)
	{
		return -2;
	}

	return r_len;
}

unsigned int CObj__AFC_RTU
::_Make__WRITE_PACKET(unsigned char* s_data,
					  const unsigned char addr_id,
					  const unsigned char cmmd_id,
					  const unsigned int  start_addr,
					  const unsigned char write_num,
					  const int data_type,
					  const unsigned short set_ui,
					  const short set_i)
{
	int i = 0;

	s_data[i++] = 0x0ff & addr_id;					// 0
	s_data[i++] = 0x0ff & cmmd_id;					// 1
	s_data[i++] = 0x0ff & (start_addr >> 8);		// 2
	s_data[i++] = 0x0ff & (start_addr >> 0);		// 3
	s_data[i++] = 0x00;								// 4
	s_data[i++] = 0x0ff & write_num;				// 5	

	s_data[i++] = 0x0ff & (write_num * 2);			// 6

	if(data_type == _DATA_TYPE__UI2)
	{
		JG_UI2 set_data;
		set_data.uiValue = set_ui;

		s_data[i++] = 0x0ff & set_data.uData[1];	// 7
		s_data[i++] = 0x0ff & set_data.uData[0];	// 8
	}
	else if(data_type == _DATA_TYPE__I2)
	{
		JG_I2 set_data;
		set_data.iValue = set_ui;

		s_data[i++] = 0x0ff & set_data.cData[1];	// 7
		s_data[i++] = 0x0ff & set_data.cData[0];	// 8
	}

	//
	unsigned short crc = _Get__CRC16(s_data, i);

	s_data[i++] = 0x0ff & (crc >> 0);				// 9
	s_data[i++] = 0x0ff & (crc >> 8);				// 10		

	return i;
}

unsigned short  CObj__AFC_RTU
::_Get__CRC16(unsigned char* s_data, const int data_len)
{
	unsigned short crc, flag;
	int count = data_len;

	crc = 0xffff;

	while(count--)
	{
		crc ^= *s_data++;
	
		for (int i=0; i<8; i++)
		{
			flag = crc & 0x0001;
			crc >>= 1;
			if(flag) crc ^= POLYNORMIAL;
		}
	}
	return crc;
}