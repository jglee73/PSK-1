#include "stdafx.h"
#include "CDB__ADS_CTRL.h"


CDB__ADS_CTRL mDB__ADS_CTRL;


// ...
CDB__ADS_CTRL::CDB__ADS_CTRL()
{
	InitializeCriticalSection(&mDB_LOCK);

}
CDB__ADS_CTRL::~CDB__ADS_CTRL()
{

	DeleteCriticalSection(&mDB_LOCK);
}

void CDB__ADS_CTRL::Clear__ADS_TOTAL_ALL()
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_TOTAL.Clear__ADS_ALL();

	LeaveCriticalSection(&mDB_LOCK);
}
void CDB__ADS_CTRL::Clear__ADS_IN_ALL()
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_IN.Clear__ADS_ALL();

	LeaveCriticalSection(&mDB_LOCK);
}
void CDB__ADS_CTRL::Clear__ADS_OUT_ALL()
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_OUT.Clear__ADS_ALL();

	LeaveCriticalSection(&mDB_LOCK);
}

void CDB__ADS_CTRL::Load__ADS_TOTAL_INFO(const CString& ads_name, const int data_size,const CString& data_type)
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_TOTAL.Load__ADS_INFO("", ads_name, data_size,data_type);

	LeaveCriticalSection(&mDB_LOCK);
}
int  CDB__ADS_CTRL::Load__ADS_IN_INFO(const CString& io_name,const CString& ads_name, const int data_size,const CString& data_type)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_IN.Load__ADS_INFO(io_name,ads_name, data_size,data_type);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Load__ADS_OUT_INFO(const CString& io_name,const CString& ads_name, const int data_size,const CString& data_type)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Load__ADS_INFO(io_name,ads_name, data_size,data_type);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

void CDB__ADS_CTRL::Load__ERR_IN_INFO(const CStringArray& l_err_name, const CStringArray& l_err_code)
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_IN.Load__ERR_INFO(l_err_name, l_err_code);

	LeaveCriticalSection(&mDB_LOCK);
}

int  CDB__ADS_CTRL::Get__ADS_TOTAL_INFO(const CString& ads_name, int& data_size,CString& data_type)
{
	EnterCriticalSection(&mDB_LOCK);

	int ads_index = mDB__ADS_TOTAL.Get__ADS_INFO(ads_name, data_size,data_type);

	LeaveCriticalSection(&mDB_LOCK);
	return ads_index;
}
int  CDB__ADS_CTRL::Get__ADS_IN_INFO(const CString& ads_name, int& data_size,CString& data_type)
{
	EnterCriticalSection(&mDB_LOCK);

	int ads_index = mDB__ADS_IN.Get__ADS_INFO(ads_name, data_size,data_type);

	LeaveCriticalSection(&mDB_LOCK);
	return ads_index;
}

void CDB__ADS_CTRL::Get__ADS_IN_LIST(CStringArray& l_ads_name, CStringArray& l_data_type)
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_IN.Get__ADS_LIST(l_ads_name, l_data_type);

	LeaveCriticalSection(&mDB_LOCK);
}

void CDB__ADS_CTRL::Set__ADS_IN_DATA(const int ads_index, const int data_len, PBYTE p_data_res)
{
	EnterCriticalSection(&mDB_LOCK);

	mDB__ADS_IN.Set__ADS_DATA(ads_index, data_len,p_data_res);

	LeaveCriticalSection(&mDB_LOCK);
}

int  CDB__ADS_CTRL::Set__ADS_OUT_DATA(const CString& ads_name, const CString& ads_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Set__ADS_DATA(ads_name, ads_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Set__ADS_OUT_DATA(const int ads_index, const CString& ads_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Set__ADS_DATA(ads_index, ads_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

int  CDB__ADS_CTRL::Set__AO_DATA(const int ads_index, const int ch_id, const double set_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Set__AIO_DATA(ads_index, set_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Get__AO_DATA(const int ads_index, const int ch_id, CString& str_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Get__AIO_DATA(ads_index, str_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Get__AI_DATA(const int ads_index, const int ch_id, double& read_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_IN.Get__AIO_DATA(ads_index, read_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

int  CDB__ADS_CTRL::Set__DO_DATA(const int ads_index, const int ch_id, const int item_index, const bool active__byte_ctrl)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Set__DIO_DATA(ads_index, ch_id, item_index, active__byte_ctrl);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Get__DO_DATA(const int ads_index, const int ch_id, int& item_index, unsigned char& r_byte_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Get__DIO_DATA(ads_index, ch_id, item_index, r_byte_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Get__DI_DATA(const int ads_index, const int ch_id, int& item_index, unsigned char& r_byte_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_IN.Get__DIO_DATA(ads_index, ch_id, item_index, r_byte_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

int  CDB__ADS_CTRL::Set__SO_DATA(const int ads_index, const int ch_id, const int set_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Set__SIO_DATA(ads_index, ch_id, set_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Get__SO_DATA(const int ads_index, const int ch_id, CString& str_hexa)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_OUT.Get__SIO_DATA(ads_index, ch_id, str_hexa);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int  CDB__ADS_CTRL::Get__SI_DATA(const int ads_index, const int ch_id, CString& str_hexa)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag = mDB__ADS_IN.Get__SIO_DATA(ads_index, ch_id, str_hexa);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

int CDB__ADS_CTRL::Get__ADS_IN_DATA(const CString& ads_name, CString& ads_data)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag =  mDB__ADS_IN.Get__ADS_DATA(ads_name, ads_data);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
int CDB__ADS_CTRL::Get__ADS_IN_HEXA(const CString& ads_name, CString& ads_hexa)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag =  mDB__ADS_IN.Get__ADS_HEXA(ads_name, ads_hexa);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

int CDB__ADS_CTRL::Get__ADS_OUT_HEXA(const int ads_index, CString& ads_hexa,int& data_size)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag =  mDB__ADS_OUT.Get__ADS_HEXA(ads_index, ads_hexa,data_size);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}

int CDB__ADS_CTRL::Get__OUT_IO_HEXA_LIST(CStringArray& l_io_name, CStringArray& l_hexa)
{
	EnterCriticalSection(&mDB_LOCK);

	int r_flag =  mDB__ADS_OUT.Get__OUT_IO_HEXA_LIST(l_io_name, l_hexa);

	LeaveCriticalSection(&mDB_LOCK);
	return r_flag;
}
