#include "stdafx.h"
#include "CMng__MSG_CTRL.h"

#include "CObj__VERITY_STD__DEF.h"


// ...
int  CMng__MGS_CTRL::Parse__BODY_INFO_CLIENT()
{
	if(!bActive__Header_Check)			return -1;

	// ...
	int ref_len = mInfo_Header.iSIZE;

	if(ref_len > iNET__DATA_SIZE)
	{
		return -1;
	}

	xI_Net_Timer->STOP_ZERO();

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

	if(mInfo_Header.iSTATE == VTY_FAIL)
	{
		if(ref_len >= 130)
		{
			CString str_err;

			_Parse__STRING_HEXA(0, ref_len, str_err);
			sLast__ERROR_MSG = str_err;
		}
	}
	else
	{
		switch(mInfo_Header.iCOMMAND)
		{
			case VTY_CMD_VERSION:
				{
					CString str_version;

					_Parse__STRING_HEXA(0, ref_len, str_version);
					mMng__VERSION.sINFO = str_version;
				}
				break;

			case VTY_CMD_CFG_LIST:
				{
					mMng__CFG_LIST.Clear();

					// ...
					CString str_file;
					CString str_date;

					int cfg_size = ref_len / 264;
					int s_index = 0;
					int str_max = 130;
					
					for(int cfg_i=0; cfg_i<cfg_size; cfg_i++)
					{
						_Parse__STRING_HEXA(s_index, str_max, str_file);
					
						s_index += str_max;
						_Parse__STRING_HEXA(s_index, str_max, str_date);

						s_index += str_max;
						unsigned int cfg_byte = _Parse__DWORD_HEXA(s_index);

						s_index += 4;

						//
						mMng__CFG_LIST.sList__NAME.Add(str_file);
						mMng__CFG_LIST.sList__DATE.Add(str_date);
						mMng__CFG_LIST.iList__SIZE.Add(cfg_byte);
					}
				}
				break;
		}
	}

	sNET__DATA_MEM.Delete(0, ref_len);
	iNET__DATA_SIZE -= ref_len;

	bActive__Header_Check = false;
	bActive__Response_Check = true;
	return 1;
}

// ...
int  CMng__MGS_CTRL::Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet)
{
	CString str_info;
	CStringArray l_item;
	CStringArray l_data;

	return _Make__PACKET_INFO_CLIENT(cmd_id, s_packet, str_info, l_item,l_data);
}
int  CMng__MGS_CTRL::Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet, const CString& str_info)
{
	CStringArray l_item;
	CStringArray l_data;

	return _Make__PACKET_INFO_CLIENT(cmd_id, s_packet, str_info, l_item,l_data);
}
int  CMng__MGS_CTRL::Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet, const CStringArray& l_item,const CStringArray& l_data)
{
	CString str_info;

	return _Make__PACKET_INFO_CLIENT(cmd_id, s_packet, str_info, l_item,l_data);
}

int  CMng__MGS_CTRL::_Make__PACKET_INFO_CLIENT(const short int cmd_id, 
											   char* s_packet, 
											   const CString& str_info,
											   const CStringArray& l_item,
											   const CStringArray& l_data)
{
	UNION_2_BYTE__INT x_cmd_id;
	x_cmd_id.siDATA = cmd_id;

	int db_i = 0;
	s_packet[db_i++] = VTY_LP_TOURI % 256;
	s_packet[db_i++] = VTY_LP_TOURI / 256;
	s_packet[db_i++] = x_cmd_id.cBYTE[0];
	s_packet[db_i++] = x_cmd_id.cBYTE[1];
	s_packet[db_i++] = 0x00;
	s_packet[db_i++] = 0x00;

	if((cmd_id == VTY_CMD_TEST)
	|| (cmd_id == VTY_CMD_VERSION)
	|| (cmd_id == VTY_CMD_CFG_LIST)
	|| (cmd_id == VTY_CMD_RESET)
	|| (cmd_id == VTY_CMD_COMPLETE )
	|| (cmd_id == VTY_CMD_STOP ))
	{
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
	}
	else if((cmd_id == VTY_CONNECT)
		 || (cmd_id == VTY_CMD_CFG_VALIDATE)
		 || (cmd_id == VTY_CMD_START))
	{
		int str_max  = 130;

		s_packet[db_i++] = 0x0ff & str_max;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;

		char* p_body = &s_packet[db_i];
		db_i += _Make__STRING_HEXA(str_info, p_body);
	}
	else if(cmd_id == VTY_CMD_WAFERINFO)
	{
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;
		s_packet[db_i++] = 0x00;

		// ...
		UNION_4_BYTE__UINT x_data;
		char* p_body;

		int item_count = 0;

		int k_limit = l_item.GetSize();
		int k;

		for(k=0; k<k_limit; k++)
		{
			CString str_item = l_item[k];
			CString str_data = l_data[k];

			// ...
			bool active__item_check = false;
			unsigned int field_type = 0x00; 

			int t_limit = 6;
			for(int t=0; t<t_limit; t++)
			{
				CString str_keyword;

				if(t == 0)
				{
					str_keyword = STR__LotID;
					field_type  = _ID__LotID;
				}
				else if(t == 1)
				{
					str_keyword = STR__SlotID;
					field_type  = _ID__SlotID;
				}
				else if(t == 2)
				{
					str_keyword = STR__Cassette;
					field_type  = _ID__Cassette;
				}
				else if(t == 3)
				{
					str_keyword = STR__Wafer;
					field_type  = _ID__Wafer;
				}
				else if(t == 4)
				{
					str_keyword = STR__Recipe;
					field_type  = _ID__Recipe;
				}
				else if(t == 5)
				{
					str_keyword = STR__Step;
					field_type  = _ID__Step;
				}
				else
				{
					continue;
				}

				if(str_item.CompareNoCase(str_keyword) != 0)
				{
					continue;
				}
				
				active__item_check = true;
				item_count++;
				break;
			}

			if(active__item_check)
			{
				p_body = &s_packet[db_i];
				db_i += _Make__STRING_HEXA(str_item, p_body);

				p_body = &s_packet[db_i];
				db_i += _Make__STRING_HEXA(str_data, p_body);

				//
				x_data.uiDATA = field_type;

				s_packet[db_i++] = x_data.cBYTE[0];
				s_packet[db_i++] = x_data.cBYTE[1];
				s_packet[db_i++] = x_data.cBYTE[2];
				s_packet[db_i++] = x_data.cBYTE[3];
			}
		}

		//
		int str_max = 264 * item_count;
		x_data.uiDATA = str_max;

		s_packet[6] = x_data.cBYTE[0];
		s_packet[7] = x_data.cBYTE[1];
		s_packet[8] = x_data.cBYTE[2];
		s_packet[9] = x_data.cBYTE[3];
	}
	else
	{
		return -1;
	}

	return db_i;
}
