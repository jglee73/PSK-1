#include "stdafx.h"
#include "CMng__MSG_CTRL.h"


// ...
int  CMng__MGS_CTRL::Parse__BODY_INFO_SERVER()
{
	if(!bActive__Header_Check)			return -1;

	// ...
	int ref_len = mInfo_Header.iSIZE;

	if(ref_len > iNET__DATA_SIZE)
	{
		return -1;
	}

	// ...
	{
		mInfo_Body.Clear();

		//
		CString str_hexa;

		for(int i=0; i<ref_len; i++)
		{
			if((i > 0) && ((i % 10) == 0))			
			{
				mInfo_Body.sHEXA += "\n";
			}

			//
			unsigned char ch = 0x0ff & sNET__DATA_MEM.GetAt(i);

			str_hexa.Format("%02X ", ch);
			mInfo_Body.sHEXA += str_hexa;
		}
	}

	sNET__DATA_MEM.Delete(0, ref_len);
	iNET__DATA_SIZE -= ref_len;

	bActive__Header_Check = false;
	bActive__Response_Check = true;
	return 1;
}

// ...
int  CMng__MGS_CTRL::Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet)
{
	CString str_info;
	CStringArray l_item;
	CStringArray l_data;

	return _Make__PACKET_INFO_SERVER(cmd_id, s_packet, str_info, l_item,l_data, false);
}
int  CMng__MGS_CTRL::Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet, const CString& str_info, const bool active__err_test)
{
	CStringArray l_item;
	CStringArray l_data;

	return _Make__PACKET_INFO_SERVER(cmd_id, s_packet, str_info, l_item,l_data, active__err_test);
}
int  CMng__MGS_CTRL::Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet, const CStringArray& l_item,const CStringArray& l_data)
{
	CString str_info;

	return _Make__PACKET_INFO_SERVER(cmd_id, s_packet, str_info, l_item,l_data, false);
}

int  CMng__MGS_CTRL::_Make__PACKET_INFO_SERVER(const short int cmd_id, 
											   char* s_packet, 
											   const CString& str_info,
											   const CStringArray& l_item,
											   const CStringArray& l_data,
											   const bool active__err_test)
{
	UNION_2_BYTE__INT x_cmd_id;
	x_cmd_id.siDATA = cmd_id;

	int db_i = 0;

	if(Check__EVENT_COMMAND(cmd_id))
	{
		s_packet[db_i++] = VTY_LP_FROMURI % 256;
		s_packet[db_i++] = VTY_LP_FROMURI / 256;
	}
	else
	{
		s_packet[db_i++] = VTY_LP_TOURI % 256;
		s_packet[db_i++] = VTY_LP_TOURI / 256;
	}

	s_packet[db_i++] = x_cmd_id.cBYTE[0];
	s_packet[db_i++] = x_cmd_id.cBYTE[1];

	if(active__err_test)
	{
		s_packet[db_i++] = 0x01;
		s_packet[db_i++] = 0x00;

		//
		int str_max  = 130;

		s_packet[db_i++] = 0x0ff & str_max;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;

		char* p_body = &s_packet[db_i];
		db_i += _Make__STRING_HEXA(str_info, p_body);			

		if(str_info.CompareNoCase("Timeout") == 0)
		{
			db_i -= 10;
		}

		return db_i;
	}
	else
	{
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
	}

	//
	if(cmd_id == VTY_CMD_VERSION)
	{
		int str_max  = 130;

		s_packet[db_i++] = 0x0ff & str_max;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;

		char* p_body = &s_packet[db_i];
		db_i += _Make__STRING_HEXA(str_info, p_body);
	}
	else if(cmd_id == VTY_CMD_CFG_LIST)
	{
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;

		//
		UNION_4_BYTE__UINT x_data;
		char* p_body;

		int k_limit = l_item.GetSize();
		for(int k=0; k<k_limit; k++)
		{
			CString str_name = l_item[k];
			CString str_date = l_data[k];

			p_body = &s_packet[db_i];
			db_i += _Make__STRING_HEXA(str_name, p_body);

			p_body = &s_packet[db_i];
			db_i += _Make__STRING_HEXA(str_date, p_body);

			//
			unsigned int cfg_size = str_name.GetLength() + str_date.GetLength();
			x_data.uiDATA = cfg_size;

			s_packet[db_i++] = x_data.cBYTE[0];
			s_packet[db_i++] = x_data.cBYTE[1];
			s_packet[db_i++] = x_data.cBYTE[2];
			s_packet[db_i++] = x_data.cBYTE[3];
		}
		
		//
		int str_max = 264 * k_limit;
		x_data.uiDATA = str_max;

		s_packet[6] = x_data.cBYTE[0];
		s_packet[7] = x_data.cBYTE[1];
		s_packet[8] = x_data.cBYTE[2];
		s_packet[9] = x_data.cBYTE[3];
	}
	else if((cmd_id == VTY_CONNECT)
		 || (cmd_id == VTY_CMD_TEST)
		 || (cmd_id == VTY_CMD_RESET)
		 || (cmd_id == VTY_CMD_WAFERINFO)
		 || (cmd_id == VTY_CMD_CFG_VALIDATE)
		 || (cmd_id == VTY_CMD_START)
		 || (cmd_id == VTY_CMD_STOP)
		 || (cmd_id == VTY_CMD_COMPLETE)
		 || (cmd_id == VTY_EVENT_NOTREADY)
		 || (cmd_id == VTY_EVENT_READY)
		 || (cmd_id == VTY_EVENT_ENDPOINT))
	{
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
	}
	else
	{
		return -1;
	}

	return db_i;
}
