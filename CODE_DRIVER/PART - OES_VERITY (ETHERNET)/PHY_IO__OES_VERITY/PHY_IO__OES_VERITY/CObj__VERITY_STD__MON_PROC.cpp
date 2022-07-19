#include "stdafx.h"

#include "CObj__VERITY_STD__ALID.h"
#include "CObj__VERITY_STD__DEF.h"
#include "CObj__VERITY_STD.h"

#include "CMng__MSG_CTRL.h"


// ...
void CObj__VERITY_STD
::Mon__DRV_PROC(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	CString log_msg;
	CString log_bff;

	CString ch_data;

	CMng__MGS_CTRL x_msg_ctrl;

	char r_net_bff[256];
	int  r_net_len = 255;

	bool active__net_err_check = true;

	// ...
	{
		log_msg = "Mon__DRV_PROC() - Sart ... \n";
		log_msg += "\n";

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}


	while(1)
	{
		int r_len = mX__Net_Client->READ__NETWORK_BUFFER(r_net_bff, r_net_len);			// -1 : Connection Error, or Return char_len

		if(dCH__PARA_ACTIVE_NET_BUFFER_CHECK->Check__DATA(STR__ON) > 0)
		{		
			// ...
			{
				log_msg = "Net.Buffer - Check ! \n";			

				log_msg +=x_msg_ctrl.Get__NETWORK_BUFFER();
				log_msg += "\n";

				mX__Log_Ctrl->WRITE__LOG(log_msg);
			}

			dCH__PARA_ACTIVE_NET_BUFFER_CHECK->Set__DATA(STR__OFF);
		}

		if(r_len < 0)
		{
			if(active__net_err_check)
			{
				active__net_err_check = false;

				log_msg = "Connect.Error !!! \n";			

				log_bff.Format(" * r_len <- %1d \n", r_len);
				log_msg += log_bff;
				log_msg += "\n";

				mX__Log_Ctrl->WRITE__LOG(log_msg);
			}

			x_msg_ctrl.Clear();

			Sleep(100);
			continue;
		}
		else
		{
			active__net_err_check = true;
		}

		// ...
		double cur__timeout_sec;

		if(x_msg_ctrl.Check__TIMEOUT_ACTIVE(cur__timeout_sec))
		{
			// ...
			{
				log_msg = "Body.Timeout ! \n";			

				log_bff.Format("Timeout <- %.3f (sec) \n", cur__timeout_sec);
				log_msg += log_bff;
				log_msg += "\n";

				log_msg +=x_msg_ctrl.Get__NETWORK_BUFFER();
				log_msg += "\n";

				mX__Log_Ctrl->WRITE__LOG(log_msg);
			}

			// ...
			{
				int alm_id = ALID__NET_BODY_TIMEOUT;
				CString r_act;

				CString err_msg = x_msg_ctrl.Get__HEADER_INFO();

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM_With_MESSAGE(alm_id, err_msg);
			}

			x_msg_ctrl.Clear();
			continue;
		}

		if(r_len == 0)
		{
			if(x_msg_ctrl.Get__NETWORK_BUFFER_SIZE() < 10)
			{
				Sleep(1);
				continue;
			}
		}

		// ...
		x_msg_ctrl.Load__DATA_MEM(r_net_bff, r_len);

		// ...
		{
			log_msg.Format("Load__DATA_HEXA() : Len(%1d) \n", r_len);			

			mX__Log_Ctrl->WRITE__LOG(log_msg);
		}

		//==================================================================================================
		while(1)
		{
			int r_check = x_msg_ctrl.Parse__HEADER_INFO();
			if(r_check > 0)
			{
				log_msg = "Header.Info ... \n";			

				log_msg += x_msg_ctrl.Get__HEADER_INFO();
				log_msg += "\n";

				mX__Log_Ctrl->WRITE__LOG(log_msg);
			}
			else
			{
				log_msg.Format("Header.Error (%1d) \n", r_check);			

				mX__Log_Ctrl->WRITE__LOG(log_msg);
			}

			if(x_msg_ctrl.Parse__BODY_INFO_CLIENT() > 0)
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

				mCheck__Msg_Ctrl.Recv__COMMAND_ID(cmd_id, ss_info);

				// ...
				bool active__event_check = x_msg_ctrl.Check__EVENT_COMMAND(cmd_id);

				if(active__event_check)
				{
					if(cmd_id == VTY_EVENT_NOTREADY)
					{
						log_msg = "Event.Active ! \n";			

						log_msg += "<< NOT_READYT";
						log_msg += "\n";

						mX__Log_Ctrl->WRITE__LOG(log_msg);
					}
					else if(cmd_id == VTY_EVENT_READY)
					{
						log_msg = "Event.Active ! \n";			

						log_msg += "<< READY";
						log_msg += "\n";

						mX__Log_Ctrl->WRITE__LOG(log_msg);
					}
					else if(cmd_id == VTY_EVENT_ENDPOINT)
					{
						log_msg = "Event.Active ! \n";			

						log_msg += "<< ENDPOINT";
						log_msg += "\n";

						mX__Log_Ctrl->WRITE__LOG(log_msg);
					}
				}
				else
				{
					// VTY_FAIL ...
					if(ss_info == VTY_FAIL)
					{
						// ...
						{
							log_msg = "Fail Report ... \n";			
		
							log_msg += x_msg_ctrl.Get__LAST_ERROR_INFO();			
							log_msg += "\n";

							mX__Log_Ctrl->WRITE__LOG(log_msg);
						}

						// ...
						{
							int alm_id = ALID__SS_FAIL;
							CString r_act;

							p_alarm->Check__ALARM(alm_id, r_act);
							p_alarm->Post__ALARM_With_MESSAGE(alm_id, log_msg);
						}
					}
					else if(ss_info == VTY_OK)
					{
						if(cmd_id == VTY_CMD_VERSION)
						{
							CMsg__VERSION m_info;
							x_msg_ctrl.Get__MSG_VERSION(m_info);

							CString str_ver = m_info.sINFO;
							sCH__INFO_VERSION->Set__DATA(str_ver);

							// ...
							{
								log_msg = "Parsing.Info ... \n";			

								log_bff.Format(" * Version <- %s \n", str_ver);
								log_msg += log_bff;
			
								mX__Log_Ctrl->WRITE__LOG(log_msg);
							}
						}
						else if(cmd_id == VTY_CMD_CFG_LIST)
						{
							CMsg__CFG_LIST m_info;
							x_msg_ctrl.Get__MSG_CFG_LIST(m_info);

							// 
							log_msg = "Parsing.Info ... \n";			

							CString str_info;

							int k_limit = m_info.sList__NAME.GetSize();
							int k;
							
							for(k=0; k<k_limit; k++)
							{
								CString str_name = m_info.sList__NAME[k];
								CString str_date = m_info.sList__DATE[k];
								int cfg_size = m_info.iList__SIZE[k];

								if(k > 0)		str_info += "/";
								str_info += str_name;

								// ...
								{
									log_bff.Format(" * %1d)  Size(%1d) \n", k+1, cfg_size);
									log_msg += log_bff;

									log_bff.Format("   * Name <- %s \n", str_name);
									log_msg += log_bff;

									log_bff.Format("   * Date <- %s \n", str_date);
									log_msg += log_bff;
								}
								
								sCH__INFO_CFG_NAME_X[k]->Set__DATA(str_name);
								sCH__INFO_CFG_DATE_X[k]->Set__DATA(str_date);

								ch_data.Format("%1d", cfg_size);
								sCH__INFO_CFG_SIZE_X[k]->Set__DATA(ch_data);
							}
							
							sCH__INFO_CFG_LIST_STR->Set__DATA(str_info);

							for( ; k<_SIZE__CFG_LIST; k++)
							{
								sCH__INFO_CFG_NAME_X[k]->Set__DATA("");
								sCH__INFO_CFG_DATE_X[k]->Set__DATA("");
								sCH__INFO_CFG_SIZE_X[k]->Set__DATA("");
							}

							mX__Log_Ctrl->WRITE__LOG(log_msg);
						}
					}
				}
			}

			bool active__check_next = x_msg_ctrl.Check__NEXT_PARSING_CONDION();
			if(!active__check_next)			break;
		}
		//==================================================================================================
	}

	// ...
}
