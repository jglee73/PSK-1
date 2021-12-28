#include "StdAfx.h"
#include "CCommon_SYSTEM.h"


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

int  Macro__Get_String_List(const CString& str_data, 
							const char ch_check,
							CStringArray& l_para)
{
	l_para.RemoveAll();

	// ...
	CString word = "";
	char ch;

	int i_limit = str_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		ch = str_data.GetAt(i);

		if(ch == ch_check)
		{
			if(word.GetLength() > 0)
				l_para.Add(word);

			word = "";
		}
		else
		{
			word += ch;
		}
	}

	if(word.GetLength() > 0)
		l_para.Add(word);

	return 1;
}
