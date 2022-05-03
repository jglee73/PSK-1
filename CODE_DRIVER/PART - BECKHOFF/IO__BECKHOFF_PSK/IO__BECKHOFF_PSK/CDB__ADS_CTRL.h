#pragma once


union UNION_2_BYTE__UINT
{
	unsigned short int uiDATA;
	char cBYTE[2];
};
union UNION_2_BYTE__INT
{
	short int iDATA;
	char cBYTE[2];
};
union UNION_3_BYTE__UINT
{
	unsigned int uiDATA;
	char cBYTE[3];
};
union UNION_4_BYTE__UINT
{
	unsigned long uiDATA;
	char cBYTE[4];
};
union UNION_4_BYTE__FLOAT
{
	float fDATA;
	unsigned long uiDATA;
	char cBYTE[4];
};


class CDB__ADS_INFO
{
public:
	CStringArray sList__IO_NAME;
	
	CStringArray sList__ADS_NAME;
	CUIntArray   iList__DATA_SIZE;
	CStringArray sList__DATA_TYPE;

	CStringArray sList__ADS_DATA_HEXA;
	CStringArray sList__ADS_DATA_VALUE;

	CStringArray sList__ERR_NAME;
	CStringArray sList__ERR_CODE;

public:
	CDB__ADS_INFO()
	{

	}

	void Clear__ADS_ALL()
	{
		sList__IO_NAME.RemoveAll();

		// ADS ...
		sList__ADS_NAME.RemoveAll();
		iList__DATA_SIZE.RemoveAll();
		sList__DATA_TYPE.RemoveAll();

		sList__ADS_DATA_HEXA.RemoveAll();
		sList__ADS_DATA_VALUE.RemoveAll();

		// ERR ...
		sList__ERR_NAME.RemoveAll();
		sList__ERR_CODE.RemoveAll();
	}

	int Load__ADS_INFO(const CString& io_name,const CString& ads_name, const int data_size,const CString& data_type)
	{
		sList__IO_NAME.Add(io_name);

		sList__ADS_NAME.Add(ads_name);
		iList__DATA_SIZE.Add(data_size);
		sList__DATA_TYPE.Add(data_type);

		sList__ADS_DATA_HEXA.Add("");
		sList__ADS_DATA_VALUE.Add("");

		return (sList__ADS_NAME.GetSize() - 1);
	}
	void Load__ERR_INFO(const CStringArray& l_err_name, const CStringArray& l_err_code)
	{
		sList__ERR_NAME.RemoveAll();
		sList__ERR_CODE.RemoveAll();

		sList__ERR_NAME.Copy(l_err_name);
		sList__ERR_CODE.Copy(l_err_code);
	}

	void Get__ERR_INFO(CStringArray& l_err_name, CStringArray& l_err_code)
	{
		l_err_name.RemoveAll();
		l_err_code.RemoveAll();

		l_err_name.Copy(sList__ERR_NAME);
		l_err_code.Copy(sList__ERR_CODE);
	}
	int  Get__ADS_INFO(const CString& ads_name, int& data_size,CString& data_type)
	{
		int ads_index = -1;

		int i_limit = sList__ADS_NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(ads_name.CompareNoCase(sList__ADS_NAME[i]) != 0)			continue;

			data_size = iList__DATA_SIZE[i];
			data_type = sList__DATA_TYPE[i];
			
			ads_index = i;
			break;
		}

		return ads_index;
	}

	int  Get__OUT_IO_HEXA_LIST(CStringArray& l_io_name, CStringArray& l_data_hexa)
	{
		l_io_name.RemoveAll();
		l_data_hexa.RemoveAll();

		l_io_name.Copy(sList__IO_NAME);
		l_data_hexa.Copy(sList__ADS_DATA_HEXA);

		return 1;
	}
	void Get__ADS_LIST(CStringArray& l_ads_name, CStringArray& l_data_type)
	{
		l_ads_name.RemoveAll();
		l_data_type.RemoveAll();

		l_ads_name.Copy(sList__ADS_NAME);
		l_data_type.Copy(sList__DATA_TYPE);
	}

	void Set__ADS_DATA(const int ads_index, const int data_len, PBYTE p_data_res)
	{
		if((ads_index >= 0)
		&& (ads_index <  sList__ADS_DATA_HEXA.GetSize()))
		{
			CString ads_type = sList__DATA_TYPE[ads_index];

			CString str_hexa;
			CString str_data = "??";

			for(int t=0; t<data_len; t++)
			{
				str_data.Format("%02X ", 0x0ff & *(p_data_res + t));
				str_hexa += str_data;
			}

			if(data_len == 4)
			{
				if(ads_type.CompareNoCase("DWORD") == 0)
				{
					DWORD data = *(DWORD*) p_data_res;

					str_data.Format("%1d", data);
				}
				else if(ads_type.CompareNoCase("REAL") == 0)
				{
					UNION_4_BYTE__FLOAT data;

					data.cBYTE[0] = *(BYTE*) (p_data_res + 0);
					data.cBYTE[1] = *(BYTE*) (p_data_res + 1);
					data.cBYTE[2] = *(BYTE*) (p_data_res + 2);
					data.cBYTE[3] = *(BYTE*) (p_data_res + 3);

					str_data.Format("%f", data.fDATA);
				}
			}
			else if(data_len == 2)
			{
				if((ads_type.CompareNoCase("WORD") == 0)
				|| (ads_type.CompareNoCase("INT")  == 0))
				{
					WORD data = *(WORD*) p_data_res;
					str_data.Format("%1d", data);
				}
			}
			else if(data_len == 1)
			{
				BYTE data = *(BYTE*) p_data_res;
				str_data.Format("%1d", data);
			}

			sList__ADS_DATA_HEXA[ads_index]  = str_hexa;
			sList__ADS_DATA_VALUE[ads_index] = str_data;
		}
	}
	int Set__ADS_DATA(const CString& ads_name, const CString& ads_data)
	{
		int check_flag = -1;

		int i_limit = sList__ADS_DATA_HEXA.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(ads_name.CompareNoCase(sList__ADS_NAME[i]) != 0)			continue;

			Set__ADS_DATA(i, ads_data);

			check_flag = 1;
			break;
		}
		return check_flag;
	}
	int Set__ADS_DATA(const int ads_index, const CString& ads_data)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		// ...
		char ch_hexa[10];
		memset(ch_hexa, 0, 10);

		int data_len = iList__DATA_SIZE[ads_index];
		CString data_type = sList__DATA_TYPE[ads_index];

		if(data_len == 4)
		{
			if(data_type.CompareNoCase("REAL") == 0)
			{
				UNION_4_BYTE__FLOAT data;

				data.fDATA = (float) atof(ads_data);

				ch_hexa[0] = data.cBYTE[0];
				ch_hexa[1] = data.cBYTE[1];
				ch_hexa[2] = data.cBYTE[2];
				ch_hexa[3] = data.cBYTE[3];
			}
			else		// DWORD
			{
				UNION_4_BYTE__UINT data;

				data.uiDATA = atoi(ads_data);

				ch_hexa[0] = data.cBYTE[0];
				ch_hexa[1] = data.cBYTE[1];
				ch_hexa[2] = data.cBYTE[2];
				ch_hexa[3] = data.cBYTE[3];
			}
		}
		else if(data_len == 2)
		{
			if((data_type.CompareNoCase("WORD") == 0)
			|| (data_type.CompareNoCase("INT")  == 0))
			{
				UNION_2_BYTE__UINT data;

				data.uiDATA = atoi(ads_data);

				ch_hexa[0] = data.cBYTE[0];
				ch_hexa[1] = data.cBYTE[1];
			}
		}
		else if(data_len == 1)
		{
			ch_hexa[0] = 0x0ff & atoi(ads_data);
		}

		// ...
		CString str_hexa;
		CString str_data = "???";

		for(int t=0; t<data_len; t++)
		{
			str_data.Format("%02X ", 0x0ff & ch_hexa[t]);
			str_hexa += str_data;
		}

		sList__ADS_DATA_VALUE[ads_index] = ads_data;
		sList__ADS_DATA_HEXA[ads_index]  = str_hexa;
		return 1;
	}

	int Set__AIO_DATA(const int ads_index, const double set_data)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		// ...
		char ch_hexa[10];
		memset(ch_hexa, 0, 10);

		int data_len = iList__DATA_SIZE[ads_index];
		CString data_type = sList__DATA_TYPE[ads_index];

		if(data_len == 4)
		{
			if(data_type.CompareNoCase("REAL") == 0)
			{
				UNION_4_BYTE__FLOAT data;

				data.fDATA = (float) set_data;

				ch_hexa[0] = data.cBYTE[0];
				ch_hexa[1] = data.cBYTE[1];
				ch_hexa[2] = data.cBYTE[2];
				ch_hexa[3] = data.cBYTE[3];
			}
			else		// DWORD
			{
				UNION_4_BYTE__UINT data;

				data.uiDATA = (int) set_data;

				ch_hexa[0] = data.cBYTE[0];
				ch_hexa[1] = data.cBYTE[1];
				ch_hexa[2] = data.cBYTE[2];
				ch_hexa[3] = data.cBYTE[3];
			}
		}
		else if(data_len == 2)
		{
			if((data_type.CompareNoCase("WORD") == 0)
			|| (data_type.CompareNoCase("INT")  == 0))
			{
				UNION_2_BYTE__UINT data;

				data.uiDATA = (int) set_data;

				ch_hexa[0] = data.cBYTE[0];
				ch_hexa[1] = data.cBYTE[1];
			}
		}
		else if(data_len == 1)
		{
			ch_hexa[0] = 0x0ff & ((int) set_data);
		}

		// ...
		CString str_hexa;
		CString str_data = "???";

		for(int t=0; t<data_len; t++)
		{
			str_data.Format("%02X ", 0x0ff & ch_hexa[t]);
			str_hexa += str_data;
		}

		str_data.Format("%f", set_data);
		sList__ADS_DATA_VALUE[ads_index] = str_data;
		sList__ADS_DATA_HEXA[ads_index]  = str_hexa;
		return 1;
	}
	int Get__AIO_DATA(const int ads_index, CString& str_data)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		str_data = sList__ADS_DATA_VALUE[ads_index];
		return 1;
	}
	int Get__AIO_DATA(const int ads_index, double& read_data)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		read_data = atof(sList__ADS_DATA_VALUE[ads_index]);
		return 1;
	}

	int Set__DIO_DATA(const int ads_index, const int ch_id, const int item_index)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;
		
		if(ch_id < 0)			return -11;

		// ...
		char ch_hexa[10];
		memset(ch_hexa, 0, 10);

		CString ads_data = sList__ADS_DATA_VALUE[ads_index];	
		int data_len = iList__DATA_SIZE[ads_index];

		if(data_len > 2)
		{
			UNION_4_BYTE__UINT x_data;

			x_data.uiDATA = atoi(ads_data);

			ch_hexa[0] = x_data.cBYTE[0];
			ch_hexa[1] = x_data.cBYTE[1];
			ch_hexa[2] = x_data.cBYTE[2];
			ch_hexa[3] = x_data.cBYTE[3];
		}
		else if(data_len == 2)
		{
			UNION_2_BYTE__UINT x_data;

			x_data.uiDATA = atoi(ads_data);

			ch_hexa[0] = x_data.cBYTE[0];
			ch_hexa[1] = x_data.cBYTE[1];
		}
		else if(data_len == 1)
		{
			ch_hexa[0] = 0x0ff & atoi(ads_data);
		}

		// ...
		int db_index = ch_id / 8;
		int shift_count = ch_id % 8;

		if(db_index < data_len)
		{
			unsigned int set_mask = 0x01;
			set_mask = set_mask << shift_count; 

			if(item_index > 0)
			{
				ch_hexa[db_index] |= (0x0ff & set_mask);
			}
			else
			{
				ch_hexa[db_index] &= (0x0ff & ~set_mask);
			}
		}

		// ...
		unsigned int ads_value = 0;
		unsigned int cur_value = 0;

		CString str_hexa;
		CString str_data = "???";

		for(int t=0; t<data_len; t++)
		{
			ads_value = cur_value << 8;
			cur_value = 0x0ff & ch_hexa[t];
			ads_value += cur_value;

			str_data.Format("%02X ", 0x0ff & cur_value);
			str_hexa += str_data;
		}

		str_data.Format("%1d", ads_value);
		sList__ADS_DATA_VALUE[ads_index] = str_data;
		sList__ADS_DATA_HEXA[ads_index]  = str_hexa;
		return 1;
	}
	int Get__DIO_DATA(const int ads_index, const int ch_id, int& item_index)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		if(ch_id < 0)			return -11;

		// ...
		char ch_hexa[10];
		memset(ch_hexa, 0, 10);

		CString ads_data = sList__ADS_DATA_VALUE[ads_index];	
		int data_len = iList__DATA_SIZE[ads_index];

		if(data_len > 2)
		{
			UNION_4_BYTE__UINT x_data;

			x_data.uiDATA = atoi(ads_data);

			ch_hexa[0] = x_data.cBYTE[0];
			ch_hexa[1] = x_data.cBYTE[1];
			ch_hexa[2] = x_data.cBYTE[2];
			ch_hexa[3] = x_data.cBYTE[3];
		}
		else if(data_len == 2)
		{
			UNION_2_BYTE__UINT x_data;

			x_data.uiDATA = atoi(ads_data);

			ch_hexa[0] = x_data.cBYTE[0];
			ch_hexa[1] = x_data.cBYTE[1];
		}
		else if(data_len == 1)
		{
			ch_hexa[0] = 0x0ff & atoi(ads_data);
		}

		// ...
		int db_index = ch_id / 8;
		int shift_count = ch_id % 8;

		if(db_index < data_len)
		{
			unsigned int set_mask = 0x01;
			set_mask = set_mask << shift_count; 

			char check_bit = (0x0ff & ch_hexa[db_index]) & (0x0ff & set_mask);

			if(check_bit > 0)			item_index = 1;
			else						item_index = 0;
		}
		else
		{
			return -1;
		}

		return 1;
	}

	int Set__SIO_DATA(const int ads_index, const int ch_id, const int set_data)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		if(ch_id < 0)			return -11;

		// ...
		char ch_hexa[10];
		memset(ch_hexa, 0, 10);

		CString ads_data = sList__ADS_DATA_VALUE[ads_index];	
		int data_len = iList__DATA_SIZE[ads_index];

		// ...
		int cur_value = set_data;

		CString str_hexa;
		CString str_data = "???";

		for(int t=0; t<data_len; t++)
		{
			str_data.Format("%02X ", 0x0ff & cur_value);
			str_hexa += str_data;

			cur_value >>= 8;
		}

		str_data.Format("%1d", set_data);
		sList__ADS_DATA_VALUE[ads_index] = str_data;
		sList__ADS_DATA_HEXA[ads_index]  = str_hexa;
		return 1;
	}
	int Get__SIO_DATA(const int ads_index, const int ch_id, CString& str_hexa)
	{
		if(ads_index <  0)									return -1;
		if(ads_index >= sList__DATA_TYPE.GetSize())			return -2;

		if(ch_id < 0)			return -11;

		str_hexa = sList__ADS_DATA_HEXA[ads_index];	
		return 1;
	}

	int Get__ADS_DATA(const CString& ads_name, CString& ads_data)
	{
		int check_flag = -1;

		int i_limit = sList__ADS_NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(ads_name.CompareNoCase(sList__ADS_NAME[i]) != 0)
			{
				continue;
			}

			ads_data = sList__ADS_DATA_VALUE[i];

			check_flag = 1;
			break;
		}

		return check_flag;
	}

	int Get__ADS_HEXA(const CString& ads_name, CString& ads_hexa)
	{
		int check_flag = -1;

		int i_limit = sList__ADS_NAME.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			if(ads_name.CompareNoCase(sList__ADS_NAME[i]) != 0)
			{
				continue;
			}

			ads_hexa = sList__ADS_DATA_HEXA[i];

			check_flag = 1;
			break;
		}

		return check_flag;
	}
	int Get__ADS_HEXA(const int ads_index, CString& ads_hexa,int& data_size)
	{
		int check_flag = -1;

		if((ads_index >= 0)
		&& (ads_index <  sList__ADS_DATA_HEXA.GetSize()))
		{
			ads_hexa  = sList__ADS_DATA_HEXA[ads_index];
			data_size = iList__DATA_SIZE[ads_index];

			check_flag = 1;
		}

		return check_flag;
	}
};


class CDB__ADS_CTRL
{
private:
	CRITICAL_SECTION mDB_LOCK;

public:
	CDB__ADS_INFO mDB__ADS_TOTAL;
	CDB__ADS_INFO mDB__ADS_IN;
	CDB__ADS_INFO mDB__ADS_OUT;

public:
	CDB__ADS_CTRL();
	~CDB__ADS_CTRL();

	//
	void Clear__ADS_TOTAL_ALL();
	void Clear__ADS_IN_ALL();
	void Clear__ADS_OUT_ALL();

	void Load__ADS_TOTAL_INFO(const CString& ads_name, const int data_size,const CString& data_type);
	int  Load__ADS_IN_INFO(const CString& io_name,const CString& ads_name, const int data_size,const CString& data_type);
	int  Load__ADS_OUT_INFO(const CString& io_name,const CString& ads_name, const int data_size,const CString& data_type);

	void Load__ERR_IN_INFO(const CStringArray& l_err_name, const CStringArray& l_err_code);

	int  Get__ADS_TOTAL_INFO(const CString& ads_name, int& data_size,CString& data_type);
	int  Get__ADS_IN_INFO(const CString& ads_name, int& data_size,CString& data_type);
	void Get__ADS_IN_LIST(CStringArray& l_ads_name, CStringArray& l_data_type);

	//
	void Set__ADS_IN_DATA(const int ads_index, const int data_len, PBYTE p_data_res);
	
	int  Set__ADS_OUT_DATA(const CString& ads_name, const CString& ads_data);
	int  Set__ADS_OUT_DATA(const int ads_index, const CString& ads_data);

	//
	int  Set__AO_DATA(const int ads_index, const int ch_id, const double set_data);
	int  Get__AO_DATA(const int ads_index, const int ch_id, CString& str_data);
	int  Get__AI_DATA(const int ads_index, const int ch_id, double& read_data);

	//
	int  Set__DO_DATA(const int ads_index, const int ch_id, const int item_index);
	int  Get__DO_DATA(const int ads_index, const int ch_id, int& item_index);
	int  Get__DI_DATA(const int ads_index, const int ch_id, int& item_index);

	int  Set__SO_DATA(const int ads_index, const int ch_id, const int set_data);
	int  Get__SO_DATA(const int ads_index, const int ch_id, CString& str_hexa);
	int  Get__SI_DATA(const int ads_index, const int ch_id, CString& str_hexa);

	//
	int  Get__ADS_IN_DATA(const CString& ads_name, CString& ads_data);
	int  Get__ADS_IN_HEXA(const CString& ads_name, CString& ads_hexa);

	int  Get__ADS_OUT_HEXA(const int ads_index, CString& ads_hexa,int& data_size);
	int  Get__OUT_IO_HEXA_LIST(CStringArray& l_io_name, CStringArray& l_hexa);
};

