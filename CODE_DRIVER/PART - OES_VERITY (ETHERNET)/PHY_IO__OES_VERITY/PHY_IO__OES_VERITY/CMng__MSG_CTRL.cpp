#include "stdafx.h"
#include "CMng__MSG_CTRL.h"


// ...
CMng__MGS_CTRL::CMng__MGS_CTRL()
{
	Clear();
}
CMng__MGS_CTRL::~CMng__MGS_CTRL()
{

}

// ...
void CMng__MGS_CTRL::Load__DATA_MEM(const char* r_data, const int r_len)
{
	for(int i=0; i<r_len; i++)
	{
		sNET__DATA_MEM += (char) (0x0ff & r_data[i]);
	}
	iNET__DATA_SIZE += r_len;
}
void CMng__MGS_CTRL::Clear()
{
	bActive__Header_Check = false;
	bActive__Response_Check = false;

	sNET__DATA_MEM  = "";
	iNET__DATA_SIZE = 0;

	xI_Net_Timer->STOP_ZERO();
}

// ...
bool CMng__MGS_CTRL::Check__NEXT_PARSING_CONDION()
{
	if(bActive__Header_Check)			return false;
	if(iNET__DATA_SIZE < 10)			return false;

	return true;
}

int  CMng__MGS_CTRL::Parse__HEADER_INFO()
{
	if(bActive__Header_Check)			return -11;

	// ...
	int ref_len = 10;

	if(iNET__DATA_SIZE < ref_len)
	{
		return -12;
	}
	
	// ID : 0 & 1
	{
		UNION_2_BYTE__UINT x_id;

		x_id.cBYTE[0] = (char) sNET__DATA_MEM.GetAt(0);
		x_id.cBYTE[1] = (char) sNET__DATA_MEM.GetAt(1);

		mInfo_Header.iID = x_id.uiDATA;
	}
	// COMMAND : 2 & 3
	{
		UNION_2_BYTE__INT x_cmd;

		x_cmd.cBYTE[0] = (char) sNET__DATA_MEM.GetAt(2);
		x_cmd.cBYTE[1] = (char) sNET__DATA_MEM.GetAt(3);

		short int cmd_id = x_cmd.siDATA;

		mInfo_Header.iCOMMAND = cmd_id;
		mInfo_Header.sCOMMAND = _Get__COMMAND_NAME(cmd_id);
	}
	// STATE : 4 & 5
	{
		UNION_2_BYTE__UINT x_sts;

		x_sts.cBYTE[0] = (char) sNET__DATA_MEM.GetAt(4);
		x_sts.cBYTE[1] = (char) sNET__DATA_MEM.GetAt(5);

		mInfo_Header.iSTATE = x_sts.uiDATA;
	}
	// SIZE : 6 ~ 9
	{
		UNION_4_BYTE__UINT x_size;

		x_size.cBYTE[0] = (char) sNET__DATA_MEM.GetAt(6);
		x_size.cBYTE[1] = (char) sNET__DATA_MEM.GetAt(7);
		x_size.cBYTE[2] = (char) sNET__DATA_MEM.GetAt(8);
		x_size.cBYTE[3] = (char) sNET__DATA_MEM.GetAt(9);

		mInfo_Header.iSIZE = x_size.uiDATA;
	}

	// HEXA ...
	{
		mInfo_Header.sHEXA = "";

		CString str_hexa;
		for(int i=0; i<ref_len; i++)
		{
			if((i > 0) && ((i % 10) == 0))			
			{
				mInfo_Header.sHEXA += "\n";
			}

			//
			unsigned char ch = 0x0ff & sNET__DATA_MEM.GetAt(i);

			str_hexa.Format("%02X ", ch);
			mInfo_Header.sHEXA += str_hexa;
		}
	}

	sNET__DATA_MEM.Delete(0, ref_len);
	iNET__DATA_SIZE -= ref_len;

	if(mInfo_Header.iSIZE > 0)
	{
		bActive__Header_Check = true;
		bActive__Response_Check = false;

		xI_Net_Timer->START__COUNT_UP(9999);
	}
	else
	{
		bActive__Header_Check = false;
		bActive__Response_Check = true;

		xI_Net_Timer->STOP_ZERO();
	}
	return 1;
}

bool CMng__MGS_CTRL::Check__TIMEOUT_ACTIVE(double& cur_sec)
{
	if(xI_Net_Timer->Get__CURRENT_TIME() >= 0.5)
	{
		cur_sec = xI_Net_Timer->Get__CURRENT_TIME();

		xI_Net_Timer->STOP_ZERO();
		return true;
	}

	cur_sec = 0.0;
	return false;
}

bool CMng__MGS_CTRL::Check__ACTIVE_REPLY()
{
	bool active_check = bActive__Response_Check;

	bActive__Response_Check = false;
	return active_check;
}
short int CMng__MGS_CTRL::Get__LAST_COMMAND_ID(unsigned short int& ss_info)
{
	ss_info = mInfo_Header.iSTATE;

	return mInfo_Header.iCOMMAND;
}
CString CMng__MGS_CTRL::Get__LAST_ERROR_INFO()
{
	CString log_msg;
	CString log_bff;

	log_bff.Format(" * COMMAND <- %1d (%s) \n", mInfo_Header.iCOMMAND, mInfo_Header.sCOMMAND);
	log_msg += log_bff;

	log_bff.Format(" * ERROR MESSAGE \n");
	log_msg += log_bff;

	log_msg += sLast__ERROR_MSG;
	log_msg += "\n";

	return log_msg;
}

int CMng__MGS_CTRL::Get__NETWORK_BUFFER_SIZE()
{
	return iNET__DATA_SIZE;
}
CString CMng__MGS_CTRL::Get__NETWORK_BUFFER()
{
	CString log_msg;
	CString log_bff;

	log_bff.Format("HEXA (%1d) \n", iNET__DATA_SIZE);
	log_msg += log_bff;

	for(int i=0; i<iNET__DATA_SIZE; i++)
	{
		if((i > 0) && ((i % 10) == 0))			log_msg += "\n";

		log_bff.Format("%02X ", 0x0ff & sNET__DATA_MEM.GetAt(i));
		log_msg += log_bff;
	}
	log_msg += "\n\n";

	log_bff.Format(" * bActive__Header_Check <- %02X \n", bActive__Header_Check);
	log_msg += log_bff;

	return log_msg;
}

CString CMng__MGS_CTRL::Get__HEADER_INFO()
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_bff.Format("HEXA \n");
		log_msg += log_bff;

		log_msg += mInfo_Header.sHEXA;
		log_msg += "\n\n";
	}

	// ...
	{
		log_bff.Format(" * ID <- %1d \n",      mInfo_Header.iID);
		log_msg += log_bff;

		log_bff.Format(" * COMMAND <- %1d (%s) \n", mInfo_Header.iCOMMAND, mInfo_Header.sCOMMAND);
		log_msg += log_bff;

		log_bff.Format(" * STATE <- 0x%04X \n", mInfo_Header.iSTATE);
		log_msg += log_bff;

		log_bff.Format(" * SIZE <- 0x%08X (%1d) \n", mInfo_Header.iSIZE, mInfo_Header.iSIZE);
		log_msg += log_bff;
	}

	return log_msg;
}
CString CMng__MGS_CTRL::Get__BODY_INFO()
{
	CString log_msg;
	CString log_bff;

	// ...
	{
		log_bff.Format("HEXA \n");
		log_msg += log_bff;

		log_msg += mInfo_Body.sHEXA;
		log_msg += "\n\n";
	}

	return log_msg;
}

// ...
int CMng__MGS_CTRL::_Make__STRING_HEXA(const CString& str_info, char* ch_hexa)
{
	int max_size = 130;
	int str_size = str_info.GetLength();
	int i;

	for(i=0; i<str_size; i++)			ch_hexa[i] = str_info.GetAt(i);
	for(   ; i<max_size; i++)			ch_hexa[i] = 0x00;

	ch_hexa[max_size - 1] = 0x0ff & str_size;

	return max_size;
}

int CMng__MGS_CTRL::_Parse__STRING_HEXA(const int s_index,const int db_size, CString& str_info)
{
	str_info = "";

	int e_index = s_index + db_size;
	for(int i=s_index; i<e_index; i++)
	{
		char ch = sNET__DATA_MEM.GetAt(i);
		if(ch == 0)		break;

		str_info += ch;
	}

	unsigned char ch_size = (unsigned char) sNET__DATA_MEM.GetAt(db_size - 1);
	if(ch_size != str_info.GetLength())			return -1;

	return 1;
}

unsigned int CMng__MGS_CTRL::_Parse__WORD_HEXA(const int s_index)
{
	UNION_2_BYTE__UINT x_data;

	int e_index = s_index + 2;
	for(int i=s_index; i<e_index; i++)
	{
		int i_index = i - s_index;

		x_data.cBYTE[i_index] = sNET__DATA_MEM.GetAt(i);
	}
	return x_data.uiDATA;
}
unsigned int CMng__MGS_CTRL::_Parse__DWORD_HEXA(const int s_index)
{
	UNION_4_BYTE__UINT x_data;

	int e_index = s_index + 4;
	for(int i=s_index; i<e_index; i++)
	{
		int i_index = i - s_index;

		x_data.cBYTE[i_index] = sNET__DATA_MEM.GetAt(i);
	}
	return x_data.uiDATA;
}

// ...
CString CMng__MGS_CTRL::_Get__COMMAND_NAME(const short int cmd_id)
{
	// Connection messages
	if(cmd_id == VTY_RECONNECT)						return "RECONNECT";
	if(cmd_id == VTY_CONNECT)						return "CONNECT";
	if(cmd_id == VTY_DISCONNECT)					return "DISCONNECT";

	// Command identifiers
	if(cmd_id == VTY_CMD_RESET)						return "RESET";
	if(cmd_id == VTY_CMD_TEST)						return "TEST";
	if(cmd_id == VTY_CMD_PRESENT)					return "PRESENT";
	if(cmd_id == VTY_CMD_VERSION)					return "VERSION";
	if(cmd_id == VTY_CMD_CFG_LIST)					return "CFG_LIST";
	if(cmd_id == VTY_CMD_GET_CFG)					return "GET_CFG";
	if(cmd_id == VTY_CMD_SET_CFG)					return "SET_CFG";
	if(cmd_id == VTY_CMD_DEL_CFG)					return "DEL_CFG";
	if(cmd_id == VTY_CMD_DEL_ALLCFG)				return "DEL_ALLCFG";
	if(cmd_id == VTY_CMD_SET_URI)					return "SET_URI";
	if(cmd_id == VTY_CMD_GET_URI)					return "GET_URI";
	if(cmd_id == VTY_CMD_TOOLISHOST)				return "TOOLISHOST";
	if(cmd_id == VTY_CMD_TOOLNOTHOST)				return "TOOLNOTHOST";
	if(cmd_id == VTY_CMD_WAFERINFO)					return "WAFERINFO";
	if(cmd_id == VTY_CMD_START)						return "START";
	if(cmd_id == VTY_CMD_STOP)						return "STOP";
	if(cmd_id == VTY_CMD_PAUSE)						return "PAUSE";
	if(cmd_id == VTY_CMD_CONTINUE)					return "CONTINUE";
	if(cmd_id == VTY_CMD_COMPLETE)					return "COMPLETE";
	if(cmd_id == VTY_CMDINTERNAL1)					return "CMDINTERNAL1";
	if(cmd_id == VTY_CMDINTERNAL2)					return "CMDINTERNAL2";
	if(cmd_id == VTY_CMD_CFG_VERIFY)				return "CFG_VERIFY";
	if(cmd_id == VTY_CMD_CFG_VALIDATE)				return "CFG_VALIDATE";
	if(cmd_id == VTY_CMD_SHUTDOWN)					return "SHUTDOWN";
	if(cmd_id == VTY_CMD_SET_VAR)					return "SET_VAR";
	if(cmd_id == VTY_CMD_GET_VAR)					return "GET_VAR";
	if(cmd_id == VTY_CMD_OPEN_DATAFILE)				return "OPEN_DATAFILE";
	if(cmd_id == VTY_CMD_GET_PROCESSDETAILS)		return "GET_PROCESSDETAILS";
	if(cmd_id == VTY_CMD_START_REPROCESS)			return "START_REPROCESS";
	if(cmd_id == VTY_CMD_RESERVED)					return "RESERVED";
	if(cmd_id == VTY_CMD_SETEVENTREPORTING)			return "SETEVENTREPORTING";
	if(cmd_id == VTY_CMD_ACK_USEREVENT)				return "ACK_USEREVENT";
	if(cmd_id == VTY_CMD_ACK_ERROR)					return "ACK_ERROR";
	if(cmd_id == VTY_CMD_GETSTATUSERRORS)			return "GETSTATUSERRORS";
	if(cmd_id == VTY_CMD_GETSTATUSUSEREVENTS)		return "GETSTATUSUSEREVENTS";
	if(cmd_id == VTY_CMD_AVAILABLE)					return "AVAILABLE";

	// Event identifiers
	if(cmd_id == VTY_EVENT_ENDPOINT)				return "EVENT.ENDPOINT";
	if(cmd_id == VTY_EVENT_LOCAL)					return "EVENT.LOCAL";
	if(cmd_id == VTY_EVENT_REMOTE)					return "EVENT.REMOTE";
	if(cmd_id == VTY_EVENT_RUNNING)					return "EVENT.RUNNING";
	if(cmd_id == VTY_EVENT_READY)					return "EVENT.READY";
	if(cmd_id == VTY_EVENT_NOTREADY)				return "EVENT.NOTREADY";
	if(cmd_id == VTY_EVENT_MARKEVENT)				return "EVENT.MARKEVENT";
	if(cmd_id == VTY_EVENT_USEREVENT)				return "EVENT.USEREVENT";
	if(cmd_id == VTY_EVENTINTERNAL1)				return "EVENTINTERNAL1";
	if(cmd_id == VTY_EVENT_MATRIX)					return "EVENT.MATRIX";
	if(cmd_id == VTY_EVENT_DATABLOCK)				return "EVENT.DATABLOCK";
	if(cmd_id == VTY_EVENT_ERROR)					return "EVENT.ERROR";
	if(cmd_id == VTY_EVENT_POWERUP)					return "EVENT.POWERUP";
	if(cmd_id == VTY_EVENT_RESERVED1)				return "EVENT.RESERVED1";
	if(cmd_id == VTY_EVENT_RESERVED2)				return "EVENT.RESERVED2";
	if(cmd_id == VTY_EVENT_RESERVED3)				return "EVENT.RESERVED3";
	if(cmd_id == VTY_EVENT_LAMPMISFIRE)				return "EVENT.LAMPMISFIRE";
	if(cmd_id == VTY_EVENT_ERROR_ACK)				return "EVENT.ERROR_ACK";
	if(cmd_id == VTY_EVENT_USEREVENT_ACK)			return "EVENT.USEREVENT_ACK";
	if(cmd_id == VTY_EVENT_AVAILABLE)				return "EVENT.AVAILABLE";

	return "???";
}

bool CMng__MGS_CTRL::Check__EVENT_COMMAND(const short int cmd_id)
{
	if((cmd_id >= VTY_EVENT_ENDPOINT)
	&& (cmd_id <= VTY_EVENT_AVAILABLE))
	{
		return true;
	}

	return false;
}

// ...
void CMng__MGS_CTRL::Get__MSG_VERSION(CMsg__VERSION& msg_info)
{
	CMsg__VERSION* p_info = &mMng__VERSION;

	msg_info.sINFO = p_info->sINFO;
}

void CMng__MGS_CTRL::Get__MSG_CFG_LIST(CMsg__CFG_LIST& msg_info)
{
	CMsg__CFG_LIST* p_info = &mMng__CFG_LIST;

	msg_info.sList__NAME.Copy(p_info->sList__NAME);
	msg_info.sList__DATE.Copy(p_info->sList__DATE);
	msg_info.iList__SIZE.Copy(p_info->iList__SIZE);
}
