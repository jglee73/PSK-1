#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__ALID.h"
#include "CDriver__LPx_ETHERNET__DEF.h"

#include "math.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int  CDriver__LPx_ETHERNET
::Fnc__StrTo2Word(const CString& data,
				  const char section,
				  CString *p_str1,
				  CString *p_str2)
{
	CString word;
	char str_ch[2];
	char ch;

	int init_flag;
	int para;
	int limit;
	int i;

	// ...
	init_flag = 0;
	para = 0;
	str_ch[1] = 0;

	limit = data.GetLength();

	for(i=0; i<=limit; i++)
	{
		if(i<limit)		ch = data.GetAt(i);
		else			ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	return 1;
}
int  CDriver__LPx_ETHERNET
::Fnc__StrTo7Word(const CString& data,
				  const char section,
				  CString *p_str1,
				  CString *p_str2,
				  CString *p_str3,
				  CString *p_str4,
				  CString *p_str5,
				  CString *p_str6,
				  CString *p_str7)
{
	CString word;
	char str_ch[2];
	char ch;

	int init_flag;
	int para;
	int limit;
	int i;

	// ...
	init_flag = 0;
	para = 0;
	str_ch[1] = '\0';

	limit = data.GetLength();

	for(i=0;i<=limit;i++)
	{
		if(i<limit)		ch = data.GetAt(i);
		else			ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;
				else if(para == 2)  *p_str3 = word;
				else if(para == 3)  *p_str4 = word;
				else if(para == 4)  *p_str5 = word;
				else if(para == 5)  *p_str6 = word;
				else if(para == 6)  *p_str7 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	return 1;
}

int  CDriver__LPx_ETHERNET::
Fnc__IndexStrTo1Word(const CString& data,
					 const char section,
					 int index,
					 CString *p_str1)
{
	CString word;
	char str_ch[2];
	char ch;

	int init_flag;
	int para;
	int limit;
	int i;

	init_flag = 0;
	para = 0;
	str_ch[1] = '\0';

	limit = data.GetLength();
	index--;

	for(i=index;i<=limit;i++)
	{
		if(i<limit)		ch = data.GetAt(i);
		else			ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)		*p_str1 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	//
	return 1;
}
int  CDriver__LPx_ETHERNET::
Fnc__IndexStrTo4Word(const CString& data,
					 const char section,
					 int index,
					 CString *p_str1,
					 CString *p_str2,
					 CString *p_str3,
					 CString *p_str4)
{
	CString word;
	char str_ch[2];
	char ch;

	int  init_flag;
	int  para;
	int  limit;
	int  i;

	init_flag = 0;
	para = 0;
	str_ch[1] = 0;

	limit = data.GetLength();
	index--;

	for(i=index;i<=limit;i++)
	{
		if(i<limit)			ch = data.GetAt(i);
		else				ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;
				else if(para == 2)  *p_str3 = word;
				else if(para == 3)  *p_str4 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	return 1;
}
int  CDriver__LPx_ETHERNET::
Fnc__IndexStrTo5Word(const CString& data,
					 const char section,
					 int index,
					 CString *p_str1,
					 CString *p_str2,
					 CString *p_str3,
					 CString *p_str4,
					 CString *p_str5)
{
	CString word;
	char str_ch[2];
	char ch;

	int  init_flag;
	int  para;
	int  limit;
	int  i;

	init_flag = 0;
	para = 0;
	str_ch[1] = 0;

	limit = data.GetLength();
	index--;

	for(i=index;i<=limit;i++)
	{
		if(i<limit)			ch = data.GetAt(i);
		else				ch = section;

		if(ch == section)
		{
			if(word.GetLength() > 0)
			{
				if(para == 0)	*p_str1 = word;
				else if(para == 1)	*p_str2 = word;
				else if(para == 2)  *p_str3 = word;
				else if(para == 3)  *p_str4 = word;
				else if(para == 4)  *p_str5 = word;

				word = "";
			}

			para++;
		}
		else
		{
			str_ch[0] = ch;
			word += str_ch;
		}
	}

	//
	return 1;
}

int  CDriver__LPx_ETHERNET::
Fnc__HexToDec(const CString& str_dec)
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
		if(i > 0)		value *= 16;

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
int  CDriver__LPx_ETHERNET::
Fnc__DecToBin(int dec,
			  CString *p_str)
{
	CString str_result;
	CString word;
	int value;
	int bit;

	int flag = 1;

	while(flag > 0)
	{
		value = dec / 2;
		bit   = dec % 2;
		dec   = value;

		if(value >= 0)
		{
			word.Format("%1d",bit);
			str_result += word;
		}

		if(value == 0)
		{
			flag = 0;
		}
	}

	char str_ch[2];
	int limit;
	int i;

	str_ch[1] = 0;
	word = "";

	limit = str_result.GetLength();

	for(i=limit-1;i>=0;i--)
	{
		str_ch[0] = str_result.GetAt(i); 
		word += str_ch;
	}

	*p_str = word;
	return 1;
}


int  CDriver__LPx_ETHERNET
::Drv__GET_LPx_CMMD(const CString& var_name,
					const CString& fnc_cmmd,
					const CString& lp_id,
					const CString& set_para,
					CString& rsp_data) 
{
	printf("Drv__GET_LPx_CMMD() - Start ... \n");

	// ...
	double to_sec = 1.0;

	CString err_msg;
	CString log_msg;
	CString log_bff;

	CString str_cmmd;
	str_cmmd.Format("%s%s%s", fnc_cmmd,lp_id,set_para);

	log_msg.Format(" %s -> %s%s", var_name, str_cmmd, sEnd_OutStr);
	Fnc__DRV_LOG(log_msg);

	printf(" -> %s%s \n", str_cmmd, sEnd_OutStr);

	mDrv_Msg.Load__MSG_INFO(fnc_cmmd, lp_id);

	mX_Net->DATA__SEND(str_cmmd, 1, &err_msg);

	CString para_rsp;
	int r_flag = mDrv_Msg.Wait__MSG_INFO(fnc_cmmd,lp_id, to_sec, para_rsp,rsp_data);

	printf("Drv__GET_LPx_CMMD() - End (%s) ... r_flag (%1d) \n", para_rsp, r_flag);

	// ...
	{
		log_msg.Format("Drv__GET_LPx_CMMD() - Report (%1d) \n", r_flag);

		log_bff.Format(" * para_rsp <- [%s] \n", para_rsp);
		log_msg += log_bff;
		log_bff.Format(" * rsp_data <- [%s] \n", rsp_data);
		log_msg += log_bff;

		Fnc__DRV_LOG(log_msg);
	}

	if(para_rsp != "1")		return -1;
	return 1;
}

int  CDriver__LPx_ETHERNET
::Check__MSG_KEY_WORD(const CString& str_data, 
					  const CString& key_word, 
					  CStringArray& l_para)
{
	int s_index = str_data.Find(key_word);
	if(s_index < 0)			return -1;

	s_index += key_word.GetLength();
	l_para.RemoveAll();

	// ...
	CString word = "";
	char ch;

	int i_limit = str_data.GetLength();
	int i;

	for(i=s_index; i<i_limit; i++)
	{
		ch = str_data.GetAt(i);

		if((ch == '[') || (ch == ']'))
		{
			if(word.GetLength() > 0)
			{
				l_para.Add(word);
			}

			word = "";
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
CString CDriver__LPx_ETHERNET
::Get__STRING_OF_LIST(const CStringArray& l_str)
{
	CString str_line = "";

	int i_limit = l_str.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(i > 0)		str_line += " ";

		str_line += l_str[i];
	}
	return str_line;
}
