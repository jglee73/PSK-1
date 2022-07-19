#include "stdafx.h"

#include "CObj__VERITY_SERVER__DEF.h"
#include "CObj__VERITY_SERVER.h"

#include "CMng__MSG_CTRL.h"


// ...
void CObj__VERITY_SERVER
::Mon__DRV_PROC(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	CMng__MGS_CTRL x_msg_ctrl;

	char r_net_bff[256];
	int  r_net_len = 255;


	while(1)
	{
		int r_len = mX__Net_Client->READ__NETWORK_BUFFER(r_net_bff, r_net_len);			// -1 : Connection Error, or Return char_len

		if(r_len < 0)
		{
			x_msg_ctrl.Clear();

			Sleep(100);
			continue;
		}

		if(r_len == 0)
		{
			Sleep(1);
			continue;
		}

		// ...
		x_msg_ctrl.Load__DATA_MEM(r_net_bff, r_len);

		if(x_msg_ctrl.Parse__HEADER_INFO() > 0)
		{
			log_msg = "Header.Info ... \n";			

			log_msg += x_msg_ctrl.Get__HEADER_INFO();
			log_msg += "\n";

			mX__Log_Ctrl->WRITE__LOG(log_msg);
		}

		if(x_msg_ctrl.Parse__BODY_INFO_SERVER() > 0)
		{
			log_msg = "Body.Info ... \n";			

			log_msg += x_msg_ctrl.Get__BODY_INFO();
			log_msg += "\n";

			mX__Log_Ctrl->WRITE__LOG(log_msg);
		}

		if(x_msg_ctrl.Check__ACTIVE_REPLY())
		{
			unsigned short int ss_info;
			short int cmd_id = x_msg_ctrl.Get__LAST_COMMAND_ID(ss_info);

			if(cmd_id == VTY_CONNECT)
			{
				char s_packet[256] = { 0, };

				int s_len = x_msg_ctrl.Make__PACKET_INFO_SERVER(cmd_id,s_packet);

				SEND__COMMAND("To Client", s_packet, s_len);
			}
			else if(cmd_id == VTY_CMD_VERSION)
			{
				char s_packet[256] = { 0, };
				CString str_info;

				str_info = "JGLEE !!!";
				int s_len = x_msg_ctrl.Make__PACKET_INFO_SERVER(cmd_id,s_packet, str_info);

				SEND__COMMAND("To Client", s_packet, s_len);
			}
			else if(cmd_id == VTY_CMD_CFG_LIST)
			{
				char s_packet[4096] = { 0, };

				CStringArray l_name;
				CStringArray l_date;

				CString str_name;
				CString str_date;

				int k_limit = 5;
				for(int k=0; k<k_limit; k++)
				{
					int id = k + 1;

					str_name.Format("File Name.%1d", id);
					l_name.Add(str_name);

					str_date.Format("Date Info.%1d", id);
					l_date.Add(str_date);
				}

				int s_len = x_msg_ctrl.Make__PACKET_INFO_SERVER(cmd_id,s_packet, l_name,l_date);

				SEND__COMMAND("To Client", s_packet, s_len);
			}
			else if((cmd_id == VTY_CMD_TEST)
				 || (cmd_id == VTY_CMD_RESET)
				 || (cmd_id == VTY_CMD_CFG_VALIDATE)
				 || (cmd_id == VTY_CMD_WAFERINFO)
				 || (cmd_id == VTY_CMD_START)
				 || (cmd_id == VTY_CMD_STOP )
				 || (cmd_id == VTY_CMD_COMPLETE))
			{
				char s_packet[2048] = { 0, };

				int s_len = x_msg_ctrl.Make__PACKET_INFO_SERVER(cmd_id,s_packet);

				SEND__COMMAND("To Client", s_packet, s_len);
			}
		}
	}

	// ...
}
