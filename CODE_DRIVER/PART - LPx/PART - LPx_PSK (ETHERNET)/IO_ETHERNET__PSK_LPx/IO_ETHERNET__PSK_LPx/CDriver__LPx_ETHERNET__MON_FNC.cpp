#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"
#include "CDriver__LPx_ETHERNET__ALID.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
void CDriver__LPx_ETHERNET
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;
	int i;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);


		// LP_STATE ...
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
			siCH__LP_STATE_X[i]->Get__STRING();
		}

		//
		if((dCH__SIM_CFG__REAL_TEST->Check__DATA(STR__YES) < 0)
		&& (iActive__SIM_MODE > 0))
		{
			iSim_Flag = 1;
		}
		else
		{
			iSim_Flag = -1;
		}

		if(iSim_Flag > 0)
		{
			diCH__COMM_STS->Set__DATA(STR__ONLINE);
			sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
		}
		else
		{
			if(diCH__COMM_STS->Check__DATA(STR__OFFLINE) > 0)
			{
				sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__OFFLINE);

				// ...
				{
					CString r_act;
					int alarm_id = ALID__OFFLINE_ALARM;

					p_alarm->Check__ALARM(alarm_id,r_act);
					p_alarm->Post__ALARM(alarm_id);
				}
			}
			else
			{
				sCH__MON_COMMUNICATION_STATE->Set__DATA(STR__ONLINE);
			}
		}

		// ...
	}	
}

void CDriver__LPx_ETHERNET
::Mon__RECV_PROC(CII_OBJECT__VARIABLE* p_variable,
				 CII_OBJECT__ALARM* p_alarm)
{

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.001);

		Proc__RECV_RSP(p_alarm, TRUE);
	}
}


int  CDriver__LPx_ETHERNET
::Proc__RECV_RSP(CII_OBJECT__ALARM* p_alarm, const BOOL active_prt)
{
	CStringArray l_rsp;
	CStringArray l_err;

	CString str_data;
	CString err_msg;
	CString key_word;
	CString fnc_name;
	CString log_msg;
	CString log_bff;

	int err_count = 0;

	while(1)
	{
		int r_len = mX_Net->DATA__RECV_QUEUE(&str_data, 1, &err_msg);
		if(r_len < 0)
		{
			Sleep(1);

			err_count++;
			if(err_count > 2)		m_nCommState = OFFLINE;

			continue;
		}

		err_count = 0;
		m_nCommState = ONLINE;

		// ...
		{
			log_msg.Format(" * Recv <- %s%s\n", str_data,sEnd_InStr);

			Fnc__DRV_LOG(log_msg);
		}

		if(active_prt)
		{
			printf(" <--- \n");
			printf(" * r_len : %1d \n", r_len);
			printf(" * err_msg  : %s \n",   err_msg);
			printf(" * str_data : %s%s \n", str_data,sEnd_InStr);
		}

		// ...
		int k_limit = 40;
		int k;

		for(k=0; k<k_limit; k++)
		{
			if(k == 0)
			{
				key_word = _RSP_GET__STATE;
				fnc_name = _DRV_GET__STATE;
			}
		    else if(k == 1)
			{
				key_word = _RSP_GET__LP_MAP;
				fnc_name = _DRV_GET__LP_MAP;
			}
			else if(k == 2)
			{
				key_word = _RSP_GET__ALM_TXT;
				fnc_name = _DRV_GET__ALM_TXT;
			}
			else if(k == 3)
			{
				key_word = _RSP_GET__ALM_MSG;
				fnc_name = _DRV_GET__ALM_MSG;
			}
			else if(k == 4)
			{
				key_word = _RSP_GET__N2_STS;
				fnc_name = _DRV_GET__N2_STS;
			}
			else if(k == 5)
			{
				key_word = _RSP_GET__RFID_READ;
				fnc_name = _DRV_GET__RFID_READ;
			}
			else if(k == 6)
			{
				key_word = _RSP_GET__TIME_READ;
				fnc_name = _DRV_GET__TIME_READ;
			}

			else if(k == 21)
			{
				key_word = _RSP_SET__INIT;
				fnc_name = _DRV_SET__INIT;
			}
			else if(k == 22)
			{
				key_word = _RSP_SET__LOAD;
				fnc_name = _DRV_SET__LOAD;
			}
			else if(k == 23)
			{
				key_word = _RSP_SET__UNLOAD;
				fnc_name = _DRV_SET__UNLOAD;
			}
			else if(k == 24)
			{
				key_word = _RSP_SET__OPEN;
				fnc_name = _DRV_SET__OPEN;
			}
			else if(k == 25)
			{
				key_word = _RSP_SET__CLOSE;
				fnc_name = _DRV_SET__CLOSE;
			}
			else if(k == 26)
			{
				key_word = _RSP_SET__CLAMP;
				fnc_name = _DRV_SET__CLAMP;
			}
			else if(k == 27)
			{
				key_word = _RSP_SET__UCLAMP;
				fnc_name = _DRV_SET__UCLAMP;
			}
			else if(k == 28)
			{
				key_word = _RSP_SET__MODE;
				fnc_name = _DRV_SET__MODE;
			}
			else if(k == 29)
			{
				key_word = _RSP_SET__SIGNAL_LAMP;
				fnc_name = _DRV_SET__SIGNAL_LAMP;
			}
			else if(k == 30)
			{
				key_word = _RSP_SET__RESET;
				fnc_name = _DRV_SET__RESET;
			}
			else if(k == 31)
			{
				key_word = _RSP_SET__N2_RUN;
				fnc_name = _DRV_SET__N2_RUN;
			}
			else if(k == 32)
			{
				key_word = _RSP_SET__AVG_TIMEOUT;
				fnc_name = _DRV_SET__AVG_TIMEOUT;
			}
			else if(k == 33)
			{
				key_word = _RSP_SET__RFID_WRITE;
				fnc_name = _RSP_SET__RFID_WRITE;
			}
			else
			{
				continue;
			}

			// Check : Keyword ...
			CStringArray l_para;

			if(Check__MSG_KEY_WORD(str_data, key_word, l_para) < 0)
			{
				continue;
			}

			if(active_prt)
			{
				printf(" * key_word : [%s] \n", key_word);

				// ...
				int t_limit = l_para.GetSize();

				printf(" ** para list (%1d) ... \n", t_limit);

				for(int t=0; t<t_limit; t++)
					printf("  * %1d) %1s \n", t,l_para[t]);
			}

			// ...
			CString str_para;

			CString para_id;
			CString para_rsp;
			CString para_data;

			int i_limit = l_para.GetSize();
			int i;

			for(i=0; i<i_limit; i++)
			{
				str_para = l_para[i];

				if(i == 0)
				{
					int str_len = str_para.GetLength();
					int str_i;

					for(str_i=0; str_i<str_len; str_i++)
					{
							 if(str_i == 0)		para_id  = str_para[0];
						else if(str_i == 1)		para_rsp = str_para[1];
					}
				}
				else if(i == 1)
				{
					para_data = str_para;
				}
			}

			// ...
			{
				log_msg = " * Result Report ... \n";

				log_bff.Format("  * para_id   <- %s \n", para_id);
				log_msg += log_bff;
				log_bff.Format("  * para_rsp  <- %s \n", para_rsp);
				log_msg += log_bff;
				log_bff.Format("  * para_data <- %s \n", para_data);
				log_msg += log_bff;

				if(para_rsp.CompareNoCase("2") == 0)
				{
					CString cancel_code = Get__CANCEL_CODE_OF_NAK(para_data);

					log_bff.Format("  ** Cancel_Code <- %s \n", cancel_code);
					log_msg += log_bff;

					sCH__DRV_CANCEL_CODE->Set__DATA(cancel_code);
				}
				log_msg += "\n";

				Fnc__DRV_LOG(log_msg);
			}

			if(mDrv_Msg.Check__MSG_DB(fnc_name, para_id))
			{
				int r_flag = mDrv_Msg.Set__MSG_INFO_OF_RSP(fnc_name, para_id, para_rsp, para_data);

				log_msg.Format("mDrv_Msg.Set__MSG_INFO_OF_RSP() ... r_flag (%1d) \n", r_flag);
				Fnc__DRV_LOG(log_msg);
			}
			else
			{
				log_msg.Format("mDrv_Msg.Check__MSG_DB(%s, %s) ... Error !!!! \n", fnc_name,para_id);
				Fnc__DRV_LOG(log_msg);

				if(para_rsp == "1")
				{
					if(fnc_name.CompareNoCase(_DRV_GET__STATE) == 0)
					{
						int lp_id = atoi(para_id);
						_Update__LPx_STATE(lp_id, para_data);
					}
				}

				mDrv_Msg.Delete__MSG_INFO(fnc_name, para_id);
			}
			break;
		}
	}

	return -1;
}
