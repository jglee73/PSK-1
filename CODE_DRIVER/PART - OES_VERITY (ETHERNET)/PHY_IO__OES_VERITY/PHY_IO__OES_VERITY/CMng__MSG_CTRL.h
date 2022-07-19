#pragma once

#include "Interface_Code.h"
#include "VTYRemoteMessages.h"


// ...
union UNION_2_BYTE__INT
{
	short int siDATA;
	char cBYTE[2];
};

union UNION_2_BYTE__UINT
{
	unsigned short int uiDATA;
	char cBYTE[2];
};

union UNION_4_BYTE__UINT
{
	unsigned int uiDATA;
	char cBYTE[4];
};


// ...
class CInfo__HEADER
{
public:
	unsigned short int iID;				// 2 Byte
	short int iCOMMAND;					// 2 Byte
	unsigned short int iSTATE;			// 2 Byte
	unsigned int iSIZE;					// 4 Byte

	CString sCOMMAND;
	CString sHEXA;
};
class CInfo__BODY
{
public:
	CString sHEXA;

	//
	void Clear()
	{
		sHEXA = "";
	}
};


// ...
class CMsg__VERSION
{
public:
	CString sINFO;
};

class CMsg__CFG_LIST
{
public:
	CMsg__CFG_LIST()
	{
	}

	void Clear()
	{
		sList__NAME.RemoveAll();
		sList__DATE.RemoveAll();
		iList__SIZE.RemoveAll();
	}

	// ...
	CStringArray sList__NAME;
	CStringArray sList__DATE;
	CUIntArray   iList__SIZE;
};


// ...
class CMng__MGS_CTRL
{
private:
	CString sNET__DATA_MEM;
	int iNET__DATA_SIZE;

	//
	SCX__ASYNC_TIMER_CTRL xI_Net_Timer;

	bool bActive__Header_Check;
	bool bActive__Response_Check;

	CInfo__HEADER mInfo_Header;
	CInfo__BODY mInfo_Body;

	CString sLast__ERROR_MSG;

	CMsg__VERSION  mMng__VERSION;
	CMsg__CFG_LIST mMng__CFG_LIST;


	// ...
	CString _Get__COMMAND_NAME(const short int cmd_id);

	int _Parse__STRING_HEXA(const int s_index,const int db_size, CString& str_info);
	
	unsigned int _Parse__WORD_HEXA(const int s_index);
	unsigned int _Parse__DWORD_HEXA(const int s_index);

	// ...
	int _Make__STRING_HEXA(const CString& str_info, char* ch_hexa);

	int _Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet, const CString& str_info, const CStringArray& l_item,const CStringArray& l_data);
	int _Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet, const CString& str_info, const CStringArray& l_item,const CStringArray& l_data, const bool active__err_test);
	//

public:
	CMng__MGS_CTRL();
	~CMng__MGS_CTRL();

	// ...
	void Load__DATA_MEM(const char* r_data, const int r_len);
	void Clear();

	bool Check__NEXT_PARSING_CONDION();
	int  Parse__HEADER_INFO();
	int  Parse__BODY_INFO_CLIENT();
	int  Parse__BODY_INFO_SERVER();

	// ...
	bool Check__TIMEOUT_ACTIVE(double& cur_sec);

	bool Check__ACTIVE_REPLY();
	short int Get__LAST_COMMAND_ID(unsigned short int& ss_info);
	CString Get__LAST_ERROR_INFO();

	bool Check__EVENT_COMMAND(const short int cmd_id);

	// ...
	int Get__NETWORK_BUFFER_SIZE();
	CString Get__NETWORK_BUFFER();

	CString Get__HEADER_INFO();
	CString Get__BODY_INFO();

	// ...
	int  Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet);
	int  Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet, const CString& str_info);
	int  Make__PACKET_INFO_CLIENT(const short int cmd_id, char* s_packet, const CStringArray& l_item,const CStringArray& l_data);

	int  Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet);
	int  Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet, const CString& str_info, const bool active__err_test = false);
	int  Make__PACKET_INFO_SERVER(const short int cmd_id, char* s_packet, const CStringArray& l_item,const CStringArray& l_data);

	// ...
	void Get__MSG_VERSION(CMsg__VERSION& msg_info);
	void Get__MSG_CFG_LIST(CMsg__CFG_LIST& msg_info);
};

