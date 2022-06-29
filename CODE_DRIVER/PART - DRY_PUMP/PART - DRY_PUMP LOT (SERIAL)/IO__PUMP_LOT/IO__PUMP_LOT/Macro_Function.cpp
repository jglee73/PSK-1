#include "StdAfx.h"


// ...
int  Macro__Get_Para_List_From_String(const CString& str_data, CStringArray& l_para)
{
	l_para.RemoveAll();

	// ...
	CString word;

	int i_limit = str_data.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		char ch = str_data.GetAt(i);

		if((ch == ' ') || (ch == ','))
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

	if(word.GetLength() > 0)
	{
		l_para.Add(word);
	}
	return 1;
}

CString Macro__Delete_Null_Char(const CString& str_data)
{
	CString str_result;

	int i_limit = str_data.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		char ch = str_data.GetAt(i);		
		if(ch == 0x00)		continue;

		str_result += ch;
	}

	return str_result;
}
