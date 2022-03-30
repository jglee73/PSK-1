#include "StdAfx.h"
#include "CCommon_SYSTEM.h"


// ...
int  Macro__CHECK_PMx_INDEX(const CString& stn_name)
{
	CString pm_name;
	int i;

	for(i=0;i<CFG_PMx__MD_SIZE;i++)
	{
		pm_name.Format("PM%1d",i+1);
		if(stn_name.CompareNoCase(pm_name) != 0)		continue;

		return i;
	}
	return -1;
}

int  Macro__Get_Para_List_From_String(const CString& str_data,
									  CStringArray& l_para)
{
	l_para.RemoveAll();

	// ...
	CString word;

	int i_limit = str_data.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		char ch = str_data.GetAt(i);

		if(ch == ' ')
		{
			if(word.GetLength() > 0)
			{
				l_para.Add(word);
				word = "";
			}
		}
		else
		{
			word += ch;
		}
	}

	return 1;
}
int  Macro__Get_HexToDec(const CString& str_dec)
{
	CString string;
	char str_ch[2];
	char ch;

	int  value;
	int  limit;
	int  i;

	string = str_dec;
	string.MakeUpper();

	value = 0;
	str_ch[1] = 0;

	limit = string.GetLength();
	for(i=0;i<limit;i++)
	{
		if(i > 0)	value *= 16;

		ch = string.GetAt(i);
		str_ch[0] = ch;

		if(((ch >= '0')&&(ch <= '9')))		value += atoi(str_ch);
		else if(ch == 'A')						value += 10;
		else if(ch == 'B')						value += 11;
		else if(ch == 'C')						value += 12;
		else if(ch == 'D')						value += 13;
		else if(ch == 'E')						value += 14;
		else if(ch == 'F')						value += 15;		
	}

	return value;
}
