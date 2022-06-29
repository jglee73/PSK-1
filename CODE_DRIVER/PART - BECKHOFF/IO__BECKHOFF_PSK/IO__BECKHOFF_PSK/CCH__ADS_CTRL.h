#pragma once


#define _CH_TYPE__VR				0
#define _CH_TYPE__AI				1
#define _CH_TYPE__AO				2
#define _CH_TYPE__DI				3
#define _CH_TYPE__DO				4
#define _CH_TYPE__SI				5
#define _CH_TYPE__SO				6


class CCH__ADS_INFO
{
public:
	CCH__ADS_INFO()
	{
		iIO_TYPE  = _CH_TYPE__VR;
		
		sIO_NAME  = "";

		sADS__FULL_NAME = "";
		sADS__CFG_NAME  = "";

		iMD_ID  = -1;
		iCH_ID  = -1;

		iADS_INDEX = -1;
	}

	// ...
	int iIO_TYPE;

	CString sIO_NAME;

	CString sADS__FULL_NAME;
	CString sADS__CFG_NAME;

	int iMD_ID;
	int iCH_ID;

	int iADS_INDEX;
};

class CCH__ADS_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_CH;

	// AI
	CUIntArray iList__AI_MD_ID;
	CUIntArray iList__AI_CH_ID;
	CUIntArray iList__AI_CMD_ID;
	CUIntArray iList__AI_ADS_INDEX;

	// AO
	CUIntArray iList__AO_MD_ID;
	CUIntArray iList__AO_CH_ID;
	CUIntArray iList__AO_CMD_ID;
	CUIntArray iList__AO_ADS_INDEX;

	// DI 
	CUIntArray iList__DI_MD_ID;
	CUIntArray iList__DI_CH_ID;
	CUIntArray iList__DI_CMD_ID;
	CUIntArray iList__DI_ADS_INDEX;

	// DO
	CUIntArray iList__DO_MD_ID;
	CUIntArray iList__DO_CH_ID;
	CUIntArray iList__DO_CMD_ID;
	CUIntArray iList__DO_ADS_INDEX;

	// SI
	CUIntArray iList__SI_MD_ID;
	CUIntArray iList__SI_CH_ID;
	CUIntArray iList__SI_CMD_ID;
	CUIntArray iList__SI_ADS_INDEX;

	// SO
	CUIntArray iList__SO_MD_ID;
	CUIntArray iList__SO_CH_ID;
	CUIntArray iList__SO_CMD_ID;
	CUIntArray iList__SO_ADS_INDEX;

	// ...
	int _Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_header, const CString& ads_name, const int md_id, const int ch_id, const int cmd_id);

	CString _Get__ADS_INFO();
	//

public:
	CCH__ADS_CTRL();
	~CCH__ADS_CTRL();

	// ...
	void Clear__ADS_CH();

	int  Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_header, const CString& ads_name, const int md_id = -1, const int ch_id = -1, const int cmd_id = -1);
	
	int  Get__ADS_FULL_NAME_LIST(CStringArray& l__io_name, CStringArray& l__ads_full_name);
	int  Link__ADS_INDEX(const int db_index, const int ads_index);

	//
	int  Set__ADS_CH(const int io_type, const CString& io_name, const int md_id, const int ch_id, const CString& set_data);

	//
	int  Set__LOCAL_AO_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, const double set_data);
	int  Get__LOCAL_AO_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, CString& str_data);
	int  Get__LOCAL_AI_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, double& read_data);

	int  Set__LOCAL_DO_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, const int item_index, const bool active__byte_ctrl);
	int  Get__LOCAL_DO_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, int& item_index);
	int  Get__LOCAL_DI_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, int& item_index, unsigned char& r_byte_data);

	int  Set__LOCAL_SO_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, const int set_data);
	int  Get__LOCAL_SO_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, CString& str_hexa);
	int  Get__LOCAL_SI_CH(const CString& ads_name, const int md_id, const int ch_id, const int cmd_id, CString& str_hexa);

	//
	CString Get__ADS_INFO();
};
