#pragma once


class CCls__Error_Mng
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CUIntArray   iList__ALM_ID;
	CStringArray sList__ERR_MSG;

public:
	CCls__Error_Mng()
	{
		InitializeCriticalSection(&mCS_LOCK);

	}
	~CCls__Error_Mng()
	{

		DeleteCriticalSection(&mCS_LOCK);
	}

	void Load__Error_Info(const int alm_id, const CString& err_msg)
	{
		EnterCriticalSection(&mCS_LOCK);

		bool active__alm_check = false;

		int i_limit = iList__ALM_ID.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(alm_id != (int) iList__ALM_ID[i])			continue;

			active__alm_check = true;
			break;
		}

		if(!active__alm_check)
		{
			iList__ALM_ID.Add(alm_id);
			sList__ERR_MSG.Add(err_msg);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	bool Check__Error_Info(int& alm_id, CString& err_msg)
	{
		EnterCriticalSection(&mCS_LOCK);

		bool active__err_info = false;

		if(iList__ALM_ID.GetSize() > 0)
		{
			active__err_info = true;

			alm_id  = (int) iList__ALM_ID[0];
			err_msg = sList__ERR_MSG[0];
		
			iList__ALM_ID.RemoveAt(0);
			sList__ERR_MSG.RemoveAt(0);
		}

		LeaveCriticalSection(&mCS_LOCK);
		return active__err_info;
	}
};

