#include "stdafx.h"
#include "CObj__VERITY_SERVER.h"

#include "CMng__MSG_CTRL.h"


//-------------------------------------------------------------------------------------
int CObj__VERITY_SERVER
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{

	return -1;
}

int CObj__VERITY_SERVER
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{

	return -1;
}

int CObj__VERITY_SERVER
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{

	return -1;
}


// ...
int CObj__VERITY_SERVER
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{
	return -1;
}

int CObj__VERITY_SERVER
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{

	return -1;
}

int CObj__VERITY_SERVER
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return -1;
}


// ...
int CObj__VERITY_SERVER
::SEND__COMMAND(const CString& var_name, const char* p_send,const int s_len)
{
	CString log_msg;
	CString log_bff;

	CString r_err;

	// ...
	{
		log_msg.Format("Var_Name <- %s \n", var_name); 

		log_bff.Format("SEND >> [%1d] \n", s_len); 
		log_msg += log_bff;

		int i_limit = s_len;
		for(int i=0; i<i_limit; i++)
		{
			if((i > 0) && ((i % 10) == 0))
			{
				log_msg += "\n";
			}

			//
			unsigned char ch = 0x0ff & p_send[i];

			log_bff.Format("%02X ", ch);
			log_msg += log_bff;
		}
		log_msg += "\n";

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}

	int s_flag = mX__Net_Client->CHAR__SEND((char*) p_send, s_len, 1, &r_err);

	// ...
	{
		log_msg.Format("s_flag : [%1d] \n", s_flag); 
		log_msg += "\n";

		if(s_flag < 0)
		{
			log_bff.Format(" * r_err <- %s \n", r_err);
			log_msg += log_bff;
		}

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}
