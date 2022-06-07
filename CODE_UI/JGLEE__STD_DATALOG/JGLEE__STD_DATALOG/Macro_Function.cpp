#include "StdAfx.h"


int Macro__Get_File_Data(const CString& file_path, 
						 CString& file_data)
{
	printf(" * Macro__Get_File_Data() ... \n");
	printf(" * file_path <- [%s] \n", file_path);

	// ...
	CFile file_ctrl;

	if(file_ctrl.Open(file_path, CFile::modeRead)) 
	{	
		int len = file_ctrl.GetLength();
		char *str_data = new char[len + 1];
		str_data[len] = 0;

		file_ctrl.Read(str_data, len);
		file_ctrl.Close();

		file_data.Format("%s", str_data);

		delete [] str_data;

		printf(" * OK ! \n");
		return 1;
	}

	printf(" * Error ! \n");
	return -1;
}

void Macro__Get_List_From_String(const CString& str_data,CStringArray& l_data)
{
	CString str_bff = "";
	l_data.RemoveAll();

	//
	char ch;

	int limit = str_data.GetLength();
	int i;

	for(i=0;i<limit;i++)
	{
		ch = str_data.GetAt(i);

		if(ch != ',')
		{
			str_bff += ch;
		}
		else
		{
			l_data.Add(str_bff);
			str_bff = "";
		}
	}

	if(str_bff.GetLength() > 0)
	{
		l_data.Add(str_bff);
	}
}
