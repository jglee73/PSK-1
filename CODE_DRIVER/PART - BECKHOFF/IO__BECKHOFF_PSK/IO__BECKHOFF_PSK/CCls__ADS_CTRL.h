#pragma once

#include <windows.h>
#include <conio.h>

// ADS headers for TwinCAT 3
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsDef.h"
#include "C:\TwinCAT\AdsApi\TcAdsDll\Include\TcAdsAPI.h"


#define _CFG__NETID_SIZE			6

#define _IO_TYPE__VR				0
#define _IO_TYPE__AI				1
#define _IO_TYPE__AO				2
#define _IO_TYPE__DI				3
#define _IO_TYPE__DO				4
#define _IO_TYPE__SI				5
#define _IO_TYPE__SO				6

#define _APC_SI__SIZE				21
#define _APC_SO__SIZE				99


#define _ADS_TYPE__BYTE				"BYTE"
#define _ADS_TYPE__USINT			"USINT"
#define _ADS_TYPE__UDINT			"UDINT"
#define _ADS_TYPE__INT				"INT"
#define _ADS_TYPE__DINT				"DINT"
#define _ADS_TYPE__REAL				"REAL"


#define _IO_NAME__diACTIVE			"diACTIVE"
#define _IO_NAME__doACTIVE			"doACTIVE"


class CCls__DEV_INFO
{
public:
	CString sDEV_NAME;
	int iVERSION;
	int iREVISION;
	int iBUILD;
};

class CCls__ADS_IO
{
public:
	CCls__ADS_IO()
	{
		iIO_TYPE  = _IO_TYPE__VR;
		sADS_NAME = "";
		sIO_NAME  = "";
		lVAR_ADDR = NULL;

		iMD_ID = -1;
		iCH_ID = -1;
	}

	// ...
	int iIO_TYPE;

	CString sADS_NAME;
	CString sIO_NAME;
	ULONG lVAR_ADDR; 

	int iMD_ID;
	int iCH_ID;
};

class CCls__ADS_CTRL
{
private:
	CRITICAL_SECTION mCS_LOCK;

	AmsAddr mAMS_ADDR; 
	CPtrArray pList_IO;

	CUIntArray iList_NETID;

	CString sDRV_INFO__DEV_NAME;
	int iDRV_INFO__VERSION;
	int iDRV_INFO__REVISION;
	int iDRV_INFO__BUILD;

	bool bDRV_ERROR;
	CString sDRV_ERR_VAR;

	// ...
	void _Add__ADS_IO(const int io_type, const CString& io_name, const CString& ads_name, const int md_id = -1, const int ch_id = -1);

	int  _Set__ADS_IO(const int io_type, const CString& io_name, bool set_data);
	int  _Get__ADS_IO(const int io_type, const CString& io_name, bool& get_data);

	int  _Set__ADS_IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const CString& set_data);	
	int  _Get__ADS_IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& r_data);	
	int  _Get__ADS_IO_SI(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& r_data);	

	int  _Set__ADS_IO_DO(const CString& io_name, const int md_id, const int ch_id, bool set_data);	
	int  _Get__ADS_IO_DO(const CString& io_name, const int md_id, const int ch_id, bool& r_data);	
	int  _Get__ADS_IO_DI(const CString& io_name, const int md_id, const int ch_id, bool& r_data);	

	int  _Set__ADS_IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, const double s_data);	
	int  _Get__ADS_IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, double& s_data);	
	int  _Get__ADS_IO_AI(const CString& io_name, const int md_id, const int ch_id, const int cnt_byte, double& r_data);	

	// ...
	void _Init__ADS_DRIVER(const int ads_port);
	int  _Init__ADS_ADDR();
	int  _Close__ADS_ADDR();

	void _Show__ADS_INFO();

	// ...
	int  _Set__VAR_ACTIVE(const bool set_data);
	int  _Get__VAR_ACTIVE();
	//

public:
	CCls__ADS_CTRL();
	~CCls__ADS_CTRL();

	// ...
	void Set__NETID(const CStringArray& l_id)
	{
		iList_NETID.RemoveAll();

		int i_limit = l_id.GetSize();
		for(int i=0; i<i_limit; i++)
		{
			int id = atoi(l_id[i]);

			iList_NETID.Add(id);
		}
	}
	
	// ...
	void Init__ADS_DRIVER(const int ads_port);
	int  Init__ADS_ADDR();
	int  Close__ADS_ADDR();

	// ...
	int  Link__ADS_VR_INFO(const CString& io_name,const CString& ads_name, const int md_id = -1,const int ch_id = -1);
	int  Link__ADS_DO_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id);
	int  Link__ADS_AO_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id);
	int  Link__ADS_SO_INFO(const CString& io_name,const CString& ads_name, const int md_id,const int ch_id);

	// ...
	bool  Check__DRV_ERROR(CString& err_var);
	void  Clear__DRV_ERROR();

	void Show__ADS_INFO();

	// ...
	AmsAddr* Get__AMS_ADDR();

	void Get__DEV_IINFO(CCls__DEV_INFO& dev_info);

	// ...
	int  Set__VAR_ACTIVE(const bool set_data);
	int  Get__VAR_ACTIVE();

	int  Set__IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const CString& s_data);
	int  Get__IO_SO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& s_data);
	int  Get__IO_SI(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, CString& r_data);

	int  Set__IO_DO(const CString& io_name, const int md_id, const int ch_id, bool set_data);
	int  Get__IO_DO(const CString& io_name, const int md_id, const int ch_id, bool& r_data);
	int  Get__IO_DI(const CString& io_name, const int md_id, const int ch_id, bool& r_data);

	int  Set__IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, const double s_data);
	int  Get__IO_AO(const CString& io_name, const int md_id, const int ch_id, const CString& ads_type, const int cnt_byte, double& r_data);
	int  Get__IO_AI(const CString& io_name, const int md_id, const int ch_id, const int cnt_byte, double& r_data);
};
