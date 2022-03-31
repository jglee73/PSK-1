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
		sADS_NAME = "";

		iMD_ID = -1;
		iCH_ID = -1;

		iADS_INDEX = -1;
	}

	// ...
	int iIO_TYPE;

	CString sIO_NAME;
	CString sADS_NAME;

	int iMD_ID;
	int iCH_ID;

	int iADS_INDEX;
};

class CCH__ADS_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList_CH;

	// ...
	int _Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_name, const int md_id, const int ch_id);

	CString _Get__ADS_INFO();
	//

public:
	CCH__ADS_CTRL();
	~CCH__ADS_CTRL();

	// ...
	void Clear__ADS_CH();

	int  Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_name, const int md_id = -1, const int ch_id = -1);
	
	int  Get__ADS_NAME_LIST(CStringArray& l__ads_name);
	int  Link__ADS_INDEX(const int db_index, const int ads_index);

	int  Set__ADS_CH(const int io_type, const CString& io_name, const int md_id, const int ch_id, const CString& set_data);

	CString Get__ADS_INFO();
};
