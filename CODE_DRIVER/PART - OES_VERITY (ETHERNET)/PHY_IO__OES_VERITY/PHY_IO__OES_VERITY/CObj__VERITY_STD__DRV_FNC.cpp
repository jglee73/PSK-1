#include "stdafx.h"
#include "CObj__VERITY_STD.h"

#include "CMng__MSG_CTRL.h"


//-------------------------------------------------------------------------------------
int CObj__VERITY_STD
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{

	return -1;
}

int CObj__VERITY_STD
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{

	return -1;
}

int CObj__VERITY_STD
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{
	
	return -1;
}


// ...
int CObj__VERITY_STD
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{

	return -1;
}

int CObj__VERITY_STD
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CMng__MGS_CTRL x_msg;

	CString str_rsp = "Error";

	//
	if(doCH__Control_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		char s_cmmd[256] = { 0 , };

		CString str_info;
		int cmd_id = 0;

		if(set_data.CompareNoCase(STR__Connect) == 0)
		{
			cmd_id = VTY_CONNECT;
			
			str_info = sCH__PARA_CONNECT_INFO->Get__STRING();
		}
		else if(set_data.CompareNoCase(STR__Comm_Test) == 0)			cmd_id = VTY_CMD_TEST;
		else if(set_data.CompareNoCase(STR__Reset) == 0)				cmd_id = VTY_CMD_RESET;
		else if(set_data.CompareNoCase(STR__Start) == 0)
		{
			cmd_id = VTY_CMD_START;

			str_info = sCH__PARA_STEP_START_CFG_NAME->Get__STRING();
		}
		else if(set_data.CompareNoCase(STR__Stop)  == 0)				cmd_id = VTY_CMD_STOP;
		else if(set_data.CompareNoCase(STR__Complete) == 0)				cmd_id = VTY_CMD_COMPLETE;
		else if(set_data.CompareNoCase(STR__Cfg_Validate) == 0)
		{
			cmd_id = VTY_CMD_CFG_VALIDATE;
			
			str_info = sCH__PARA_CFG_VALIDATE_INFO->Get__STRING();
		}
		else
		{
			sCH__INFO_DRV_CONTROL_STS->Set__DATA(str_rsp);
			return -1;
		}

		int s_len = x_msg.Make__PACKET_INFO_CLIENT(cmd_id, s_cmmd, str_info);
		unsigned short int ss_info;

		int r_flag = SEND__COMMAND(var_name,set_data, cmd_id, s_cmmd,s_len, ss_info);

		if(r_flag < 0)
		{
			str_rsp.Format("Error.%1d", r_flag);
		}
		else
		{
			if(ss_info != VTY_OK)			str_rsp = "Fail";
			else							str_rsp = STR__OK;
		}

		sCH__INFO_DRV_CONTROL_STS->Set__DATA(str_rsp);

		if(str_rsp.CompareNoCase(STR__OK) == 0)			return 1;
		return -1;
	}

	//
	if((doCH__VERSION_REQ->Check__VARIABLE_NAME(var_name) > 0)
	|| (doCH__CFG_LIST_REQ->Check__VARIABLE_NAME(var_name) > 0))
	{
		char s_cmmd[256] = { 0 , };

		bool active__ver_req = false;
		bool active__cfg_req = false;

			 if(doCH__VERSION_REQ->Check__VARIABLE_NAME(var_name)  > 0)			active__ver_req = true;
		else if(doCH__CFG_LIST_REQ->Check__VARIABLE_NAME(var_name) > 0)			active__cfg_req = true;

		// ...
		short int cmd_id = 0;

			 if(active__ver_req)			cmd_id = VTY_CMD_VERSION;
		else if(active__cfg_req)			cmd_id = VTY_CMD_CFG_LIST;

		if(cmd_id > 0)
		{
			int s_len = x_msg.Make__PACKET_INFO_CLIENT(cmd_id, s_cmmd);
			unsigned short int ss_info;

			int r_flag = SEND__COMMAND(var_name,set_data, cmd_id, s_cmmd,s_len, ss_info);
			
			if(r_flag < 0)
			{
				str_rsp.Format("Error.%1d", r_flag);
			}
			else
			{
				if(ss_info != VTY_OK)		str_rsp = "Fail";
				else						str_rsp = STR__OK;
			}
		}

			 if(active__ver_req)			sCH__INFO_DRV_VERSION_STS->Set__DATA(str_rsp);
		else if(active__cfg_req)			sCH__INFO_DRV_CFG_LIST_STS->Set__DATA(str_rsp);

		if(str_rsp.CompareNoCase(STR__OK) == 0)			return 1;
		return -1;
	}

	if(doCH__WAFER_INFO_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		char s_cmmd[4096] = { 0 , };

		int cmd_id = VTY_CMD_WAFERINFO;

		CStringArray l_item;
		CStringArray l_data;

		CString str_item;
		CString str_data;

		// 1. LotID
		{
			str_item = STR__LotID;
			str_data = sCH__PARA_WAFER_LOTID->Get__STRING();

			l_item.Add(str_item);
			l_data.Add(str_data);
		}
		// 2. LotID
		{
			str_item = STR__SlotID;
			str_data = sCH__PARA_WAFER_SLOTID->Get__STRING();

			l_item.Add(str_item);
			l_data.Add(str_data);
		}
		// 3. Cassette
		{
			str_item = STR__Cassette;
			str_data = sCH__PARA_WAFER_CSTID->Get__STRING();

			l_item.Add(str_item);
			l_data.Add(str_data);
		}
		// 4. Wafer
		{
			str_item = STR__Wafer;
			str_data = sCH__PARA_WAFER_ID->Get__STRING();

			l_item.Add(str_item);
			l_data.Add(str_data);
		}
		// 5. Recipe
		{
			str_item = STR__Recipe;
			str_data = sCH__PARA_WAFER_RECIPE->Get__STRING();

			l_item.Add(str_item);
			l_data.Add(str_data);
		}
		// 6. Step
		{
			str_item = STR__Step;
			str_data = sCH__PARA_WAFER_STEP->Get__STRING();

			l_item.Add(str_item);
			l_data.Add(str_data);
		}

		int s_len = x_msg.Make__PACKET_INFO_CLIENT(cmd_id, s_cmmd, l_item,l_data);
		unsigned short int ss_info;

		int r_flag = SEND__COMMAND(var_name,set_data, cmd_id, s_cmmd,s_len, ss_info);

		if(r_flag < 0)
		{
			str_rsp.Format("Error.%1d", r_flag);
		}
		else
		{
			if(ss_info != VTY_OK)			str_rsp = "Fail";
			else							str_rsp = STR__OK;
		}

		sCH__INFO_DRV_WAFER_INFO_STS->Set__DATA(str_rsp);

		if(str_rsp.CompareNoCase(STR__OK) == 0)			return 1;
		return -1;
	}

	return -1;
}

int CObj__VERITY_STD
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return -1;
}


// ...
int CObj__VERITY_STD
::SEND__COMMAND(const CString& var_name,
				const CString& set_data,
				const int cmd_id, 
				const char* p_send,
				const int s_len, 
				unsigned short int& ss_info)
{
	CString log_msg;
	CString log_bff;

	CString r_err;

	// ...
	{
		log_msg.Format("Var_Name <- %s \n", var_name); 

		if(set_data.GetLength() > 0)
		{
			log_bff.Format(" * Set_Data <- [%s] \n", set_data); 
			log_msg += log_bff;
		}

		//
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

	// ...
	mCheck__Msg_Ctrl.Load__COMMAND_ID(cmd_id);

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

	if(s_flag < 0)
	{
		bActive__COMM_ONLINE = false;
		return -11;
	}

	// ...
	int r_flag = mCheck__Msg_Ctrl.Wait__COMMAND_ID(cmd_id, ss_info);

	if(r_flag < 0)
	{
		log_msg.Format("Recv.Timeout !!!"); 

		mX__Log_Ctrl->WRITE__LOG(log_msg);

		bActive__COMM_ONLINE = false;
	}
	else
	{
		log_msg.Format("ss_info <- 0x%04X", ss_info); 

		mX__Log_Ctrl->WRITE__LOG(log_msg);

		bActive__COMM_ONLINE = true;
	}
	return r_flag;
}
