#include "StdAfx.h"
#include "CCommon_System.h"


// ...
int  Macro__CHECK_LPx_INDEX(const CString& stn_name)
{
	CString lp_name;
	int i;

	for(i=0;i<CFG_LPx__SIZE;i++)
	{
		lp_name.Format("LP%1d",i+1);
		if(stn_name.CompareNoCase(lp_name) != 0)		continue;

		return i;
	}
	return -1;
}
int  Macro__CHECK_PMx_INDEX(const CString& stn_name)
{
	CString pm_name;
	int i;

	for(i=0;i<CFG_PMx__SIZE;i++)
	{
		pm_name.Format("PM%1d",i+1);
		if(stn_name.CompareNoCase(pm_name) != 0)		continue;

		return i;
	}
	return -1;
}

CString Macro__GET_LLx_NAME(const int ll_index)
{
	if(ll_index == 0)			return _MODULE__LBA;
	if(ll_index == 1)			return _MODULE__LBB;
	if(ll_index == 2)			return _MODULE__LBC;
	if(ll_index == 3)			return _MODULE__LBD;

	return _MODULE__LLx;
}
int  Macro__CHECK_LLx_INDEX(const CString& stn_name)
{
	CString ll_name;
	int i;

	for(i=0; i<CFG_LLx__SIZE;i++)
	{
		ll_name.Format("LL%1d",i+1);
		if(ll_name.CompareNoCase(stn_name) == 0)		return i;

		ll_name = Macro__GET_LLx_NAME(i);
		if(ll_name.CompareNoCase(stn_name) == 0)		return i;
	}

	return -1;
}
bool Macro__CHECK_LLx_NAME(const CString& stn_name)
{
	CString ll_name;
	int i;

	for(i=0; i<CFG_LLx__SIZE;i++)
	{
		ll_name.Format("LL%1d",i+1);
		if(ll_name.CompareNoCase(stn_name) == 0)		return true;

		ll_name = Macro__GET_LLx_NAME(i);
		if(ll_name.CompareNoCase(stn_name) == 0)		return true;
	}

	return false;
}

