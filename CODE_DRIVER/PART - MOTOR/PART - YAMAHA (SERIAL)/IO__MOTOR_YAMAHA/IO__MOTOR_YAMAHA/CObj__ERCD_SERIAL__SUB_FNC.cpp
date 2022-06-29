#include "StdAfx.h"
#include "CObj__ERCD_SERIAL.h"


// ...
int CObj__ERCD_SERIAL
::_Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm)
{
	if(sCH__MON_COMM_STS->Check__DATA(STR__ONLINE) > 0)
	{
		return 1;
	}

	return -1;
}

int CObj__ERCD_SERIAL
::_Fnc__Abort_Ctrl()
{
	doCH__ABORT_SET->Set__DATA(_IO_Cmd__STOP);
	return 1;
}

int CObj__ERCD_SERIAL
::_Get__HexToDec(const CString& str_hexa)
{
	CString str_data = str_hexa;
	str_data.MakeUpper();

	int dec_value = 0;
	int i_limit = str_data.GetLength();

	for(int i=0; i<i_limit; i++)
	{
		if(i > 0)		dec_value *= 16;

		char ch = str_data.GetAt(i);

		if(((ch >= '0')&&(ch <= '9')))			dec_value += (ch - '0');
		else if(ch == 'A')						dec_value += 10;
		else if(ch == 'B')						dec_value += 11;
		else if(ch == 'C')						dec_value += 12;
		else if(ch == 'D')						dec_value += 13;
		else if(ch == 'E')						dec_value += 14;
		else if(ch == 'F')						dec_value += 15;		
	}

	return dec_value;
}
