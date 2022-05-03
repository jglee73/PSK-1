#include "stdafx.h"
#include "CCls__ADS_CTRL.h"

#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CCH__ADS_CTRL.h"
CCH__ADS_CTRL mCH__ADS_IN;
CCH__ADS_CTRL mCH__ADS_OUT;


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

	CPtrArray* p_list = &pList_CH;

	int i_limit = p_list->GetSize();
	for(int i=0; i<i_limit; i++)
	{
		CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) p_list->GetAt(i);

		delete p_ch;
	}
	p_list->RemoveAll();

	LeaveCriticalSection(&mCS_LOCK);
}

// ...
int  CCH__ADS_CTRL::
Add__ADS_CH(const int io_type, const CString& io_name, const CString& ads_header, const CString& ads_name, const int md_id, const int ch_id)
{
	EnterCriticalSection(&mCS_LOCK);

	int r_flag = _Add__ADS_CH(io_type, io_name, ads_header, ads_name, md_id, ch_id);

	LeaveCriticalSection(&mCS_LOCK);
	return r_flag;
}

// ...
int  CCH__ADS_CTRL::Get__ADS_FULL_NAME_LIST(CStringArray& l__io_name, CStringArray& l__ads_full_name)
{
	EnterCriticalSection(&mCS_LOCK);

	l__io_name.RemoveAll();
	l__ads_full_name.RemoveAll();

	// ...
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			l__io_name.Add(p_ch->sIO_NAME);
			l__ads_full_name.Add(p_ch->sADS__FULL_NAME);
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

			if(p_ch->iIO_TYPE != io_type)		continue;
		
			if(p_ch->iMD_ID != md_id)			continue;
			if(p_ch->iCH_ID != ch_id)			continue;

			if(p_ch->sIO_NAME.CompareNoCase(io_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			check_flag = mDB__ADS_CTRL.Set__ADS_OUT_DATA(ads_index, set_data);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CCH__ADS_CTRL::Set__LOCAL_AO_CH(const CString& ads_name, const int md_id, const int ch_id, const double set_data)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__AIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__AIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__AIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Set__AO_DATA(ads_index, ch_id, set_data);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Set__AO_DATA(ads_index, ch_id, set_data);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CCH__ADS_CTRL::Get__LOCAL_AO_CH(const CString& ads_name, const int md_id, const int ch_id, CString& str_data)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__AIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__AIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__AIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Get__AO_DATA(ads_index, ch_id, str_data);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Get__AO_DATA(ads_index, ch_id, str_data);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CCH__ADS_CTRL::Get__LOCAL_AI_CH(const CString& ads_name, const int md_id, const int ch_id, double& read_data)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__AIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__AIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__AIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Get__AI_DATA(ads_index, ch_id, read_data);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Get__AI_DATA(ads_index, ch_id, read_data);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CCH__ADS_CTRL::Set__LOCAL_DO_CH(const CString& ads_name, const int md_id, const int ch_id, const int item_index)
{
	EnterCriticalSection(&mCS_LOCK);

	 bool active__db_add = true;
	 int check_flag = -11;

	 // ...
	 CUIntArray* pl__md_id = &iList__DIO_MD_ID;
	 CUIntArray* pl__ch_id = &iList__DIO_CH_ID;
	 CUIntArray* pl__ads_index = &iList__DIO_ADS_INDEX;

	 // ...
	 {
		 int i_limit = pl__md_id->GetSize();

		 for(int i=0; i<i_limit; i++)
		 {
			 if(md_id != pl__md_id->GetAt(i))		continue;
			 if(ch_id != pl__ch_id->GetAt(i))		continue;

			 int ads_index = pl__ads_index->GetAt(i);

			 check_flag = mDB__ADS_CTRL.Set__DO_DATA(ads_index, ch_id, item_index);

			 active__db_add = false;
			 break;
		 }
	 }

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Set__DO_DATA(ads_index, ch_id, item_index);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CCH__ADS_CTRL::Get__LOCAL_DO_CH(const CString& ads_name, const int md_id, const int ch_id, int& item_index)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__DIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__DIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__DIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Get__DO_DATA(ads_index, ch_id, item_index);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Get__DO_DATA(ads_index, ch_id, item_index);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CCH__ADS_CTRL::Get__LOCAL_DI_CH(const CString& ads_name, const int md_id, const int ch_id, int& item_index)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__DIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__DIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__DIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Get__DI_DATA(ads_index, ch_id, item_index);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Get__DI_DATA(ads_index, ch_id, item_index);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CCH__ADS_CTRL::Set__LOCAL_SO_CH(const CString& ads_name, const int md_id, const int ch_id, const int set_data)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__SIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__SIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__SIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Set__SO_DATA(ads_index, ch_id, set_data);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Set__SO_DATA(ads_index, ch_id, set_data);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CCH__ADS_CTRL::Get__LOCAL_SO_CH(const CString& ads_name, const int md_id, const int ch_id, CString& str_hexa)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__SIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__SIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__SIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Get__SO_DATA(ads_index, ch_id, str_hexa);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Get__SO_DATA(ads_index, ch_id, str_hexa);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}
int  CCH__ADS_CTRL::Get__LOCAL_SI_CH(const CString& ads_name, const int md_id, const int ch_id, CString& str_hexa)
{
	EnterCriticalSection(&mCS_LOCK);

	bool active__db_add = true;
	int check_flag = -11;

	// ...
	CUIntArray* pl__md_id = &iList__SIO_MD_ID;
	CUIntArray* pl__ch_id = &iList__SIO_CH_ID;
	CUIntArray* pl__ads_index = &iList__SIO_ADS_INDEX;

	// ...
	{
		int i_limit = pl__md_id->GetSize();

		for(int i=0; i<i_limit; i++)
		{
			if(md_id != pl__md_id->GetAt(i))		continue;
			if(ch_id != pl__ch_id->GetAt(i))		continue;

			int ads_index = pl__ads_index->GetAt(i);

			check_flag = mDB__ADS_CTRL.Get__SI_DATA(ads_index, ch_id, str_hexa);

			active__db_add = false;
			break;
		}
	}

	if(active__db_add)
	{
		int i_limit = pList_CH.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCH__ADS_INFO* p_ch = (CCH__ADS_INFO*) pList_CH[i];

			if(p_ch->sADS__CFG_NAME.CompareNoCase(ads_name) != 0)		continue;

			int ads_index = p_ch->iADS_INDEX;	
			if(ads_index < 0)			break;

			// ...
			{
				pl__md_id->Add(md_id);
				pl__ch_id->Add(ch_id);
				pl__ads_index->Add(ads_index);
			}

			check_flag = mDB__ADS_CTRL.Get__SI_DATA(ads_index, ch_id, str_hexa);
			break;
		}
	}

	LeaveCriticalSection(&mCS_LOCK);
	return check_flag;
}

int  CCH__ADS_CTRL::
_Add__ADS_CH(const int io_type,const CString& io_name, const CString& ads_header,const CString& ads_name, const int md_id,const int ch_id)
{
	CPtrArray* p_list = &pList_CH;

	// ...
	{
		CCH__ADS_INFO* p_ch = new CCH__ADS_INFO;
		p_list->Add(p_ch);

		p_ch->iIO_TYPE  = io_type;
		p_ch->sIO_NAME  = io_name;

		p_ch->sADS__FULL_NAME.Format("%s%s", ads_header,ads_name);
		p_ch->sADS__CFG_NAME = ads_name;

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

		log_bff.Format("   %02d) %s [%s] : [%1d] [%1d.%1d] \n", 
			           i+1, 
					   p_ch->sIO_NAME,
					   p_ch->sADS__CFG_NAME,
					   p_ch->iADS_INDEX, 
					   p_ch->iMD_ID,
					   p_ch->iCH_ID);

		log_msg += log_bff;
	}
	log_msg += "\n";

	return log_msg;
}
