#include "stdafx.h"
#include "CCH__ADS_CTRL.h"

#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;


CCH__ADS_CTRL mCH__ADS_CTRL;


// ...
CCH__ADS_CTRL::CCH__ADS_CTRL()
{
	InitializeCriticalSection(&mCS_LOCK);

}
CCH__ADS_CTRL::~CCH__ADS_CTRL()
{

	DeleteCriticalSection(&mCS_LOCK);
}

// ...
void CCH__ADS_CTRL::Clear__ADS_CH()
{
	EnterCriticalSection(&mCS_LOCK);

	int i_limit = pList_CH.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

		delete p_ch;
	}
	pList_CH.RemoveAll();

	LeaveCriticalSection(&mCS_LOCK);
}

int  CCH__ADS_CTRL::Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_name, const int md_id, const int ch_id)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Add__ADS_CH(io_type, io_name, ads_name, md_id, ch_id);

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}

int  CCH__ADS_CTRL::Get__ADS_NAME_LIST(CStringArray& l__ads_name)
{
	EnterCriticalSection(&mCS_LOCK);

	l__ads_name.RemoveAll();

	// ...
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			l__ads_name.Add(p_ch->sADS_NAME);
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return 1;
}
int  CCH__ADS_CTRL::Link__ADS_INDEX(const int db_index, const int ads_index)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_flag = -1;

	if((db_index >= 0)
	&& (db_index <  pList_CH.GetSize()))
	{
		CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[db_index];

		p_ch->iADS_INDEX = ads_index;

		check_flag = 1;
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CCH__ADS_CTRL::Set__ADS_CH(const int io_type, const CString& io_name, const int md_id, const int ch_id, const CString& set_data)
{
	EnterCriticalSection(&mCS_LOCK);

	int check_flag = -11;

	// ...
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->iMD_ID != md_id)		continue;
			if(p_ch->iCH_ID != ch_id)		continue;

			if(p_ch->sIO_NAME.CompareNoCase(io_name) != 0)		continue;

			if(p_ch->iADS_INDEX >= 0)
			{
				check_flag = mDB__ADS_CTRL.Set__ADS_OUT_DATA(p_ch->iADS_INDEX, set_data);
			}
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CCH__ADS_CTRL::_Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_name, const int md_id, const int ch_id)
{
	CCH__ADS_INFO* p_ch = new CCH__ADS_INFO;
	pList_CH.Add(p_ch);

	// ...
	{
		p_ch->iIO_TYPE  = io_type;
		p_ch->sIO_NAME  = io_name;
		p_ch->sADS_NAME = ads_name;

		p_ch->iMD_ID = md_id;
		p_ch->iCH_ID = ch_id;
	}
	return 1;
}


// ...
CString CCH__ADS_CTRL::Get__ADS_INFO()
{
	EnterCriticalSection(&mCS_LOCK);

	CString log_msg = _Get__ADS_INFO();

	LeaveCriticalSection(&mCS_LOCK);
	return log_msg;
}
CString CCH__ADS_CTRL::_Get__ADS_INFO()
{
	CString log_msg;
	CString log_bff;

	log_msg.Format(" CCH__ADS_CTRL::_Get__ADS_INFO() ... \n");

	int i_limit = pList_CH.GetSize();

	for(int i=0; i<i_limit; i++)
	{
		CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

		log_bff.Format(" * %02d) %s [%s] : [%1d] [%1d.%1d] \n", 
			           i+1, 
					   p_ch->sIO_NAME,
					   p_ch->sADS_NAME,
					   p_ch->iADS_INDEX, 
					   p_ch->iMD_ID,
					   p_ch->iCH_ID);

		log_msg += log_bff;
	}
	log_msg += "\n";

	return log_msg;
}
