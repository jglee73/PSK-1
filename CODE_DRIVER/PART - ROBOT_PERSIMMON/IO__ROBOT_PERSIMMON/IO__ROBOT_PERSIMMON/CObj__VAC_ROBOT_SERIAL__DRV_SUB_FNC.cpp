#include "StdAfx.h"
#include "CObj__VAC_ROBOT_SERIAL.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"

#include "math.h"
#include "CCommon_DEF.h"

#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int CObj__VAC_ROBOT_SERIAL
::Drv__SEND_COMMAND(const CString& var_name, 
			        const CString& str_cmmd, 
					const CString& str_para,
					CString& recv_data)
{
	recv_data = "";

	// ...
	CString str__log;

	CString str__send_data;
	CString str__send_log;

	int cfg_timeout = m_Out_Time;

	// ...
	{
		str__send_data.Format("C%s%s", str_cmmd,str_para);
		str__send_log.Format("%s<CR><LF>", str__send_data);

		str__log.Format("[%s] SEND => [%s], timeout:%d msec \n", var_name, str__send_log, cfg_timeout);
		Fnc__DRV_LOG(str__log);
	}

	// ...
	{
		CString str_bff;
		mX_Serial->CLEAR__BUFFER(&str_bff);
	}

	// ...
	{
		str__send_data += (char) CR;
		str__send_data += (char) LF;
	}

	int r_flag = mX_Serial->DATA__RECV(m_Term_Str, &str__send_data, cfg_timeout);

	str__log.Format("RECV <= [%s], r_flag [%d] \n", str__send_data, r_flag);
	Fnc__DRV_LOG(str__log);

	if(r_flag >= 0)
	{
		m_nCommState = ONLINE;

		// ...
		CString r_cmmd;
		int s_index;

		// ...
		{
			CString r_bff;

			Sleep(1);
			mX_Serial->CLEAR__BUFFER(&r_bff);

			r_cmmd  = str__send_data;
			r_cmmd += r_bff;
		}

		s_index = r_cmmd.Find("_RDY");
		if(s_index >= 0)
		{
			recv_data = r_cmmd;
			return 1;
		}
		
		s_index = r_cmmd.Find("_ERR");
		if(s_index >= 0)
		{
			// Error

			return -1;
		}

		return -11;
	}

	m_nCommState = OFFLINE;
	return -1;
}


// ...
int  CObj__VAC_ROBOT_SERIAL::Update__ROBOT_STATE(const CString& str_data)
{
	bool active__recv_ok = false;

	CString str__robot_sts;
	CString str__error_id;

	// ...
	CStringArray l_para;
	Macro__Get_Para_List_From_String(str_data, l_para);

	int i_limit = l_para.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)			
		{
			if(str_para.CompareNoCase("BG") == 0)			active__recv_ok = true;
			else											active__recv_ok = false;
		}
		else if(i == 1)	
		{		
				 if(str_para.CompareNoCase("Y") == 0)		str__robot_sts = STR__BUSY;
			else if(str_para.CompareNoCase("N") == 0)		str__robot_sts = STR__IDLE;
			else											str__robot_sts = STR__UNKNOWN;
		}
		else if(i == 2)
		{
			str__error_id = str_data;
		}
	}

	if(active__recv_ok)
	{
		sCH__MON_RB_STATE->Set__DATA(str__robot_sts);

		int err_id = atoi(str__error_id);
		CString str__error_msg = Get__ERROR_MSG(err_id);

		sCH__MON_ERROR_ID->Set__DATA(str__error_id);
		sCH__MON_ERROR_MSG->Set__DATA(str__error_msg);
	}
	else
	{
		CString ch_data = "___";

		sCH__MON_RB_STATE->Set__DATA(STR__UNKNOWN);

		sCH__MON_ERROR_ID->Set__DATA(ch_data);
		sCH__MON_ERROR_MSG->Set__DATA(ch_data);
	}

	return 1;
}

int  CObj__VAC_ROBOT_SERIAL::Update__VERSION(const CString& str_data)
{
	bool active__recv_ok = false;

	CString str__version;

	// ...
	CStringArray l_para;
	Macro__Get_Para_List_From_String(str_data, l_para);

	int i_limit = l_para.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)			
		{
			if(str_data.CompareNoCase("V") == 0)		active__recv_ok = true;
			else										active__recv_ok = false;
		}
		else if(i == 1)
		{
			str__version = str_para; 
		}
	}

	if(active__recv_ok)
	{
		sCH__MON_SW_VERSION->Set__DATA(str__version);
	}
	else
	{
		sCH__MON_SW_VERSION->Set__DATA("???");
	}

	return 1;
}
int  CObj__VAC_ROBOT_SERIAL::Update__RQ_COMM_INFO(const CString& str_data)
{
	bool active__recv_ok = false;

	CString str__mode;
	CString str__flow;
	CString str__lf;
	CString str__echo;
	CString str__checksum;
	CString str__drep;
	CString str__baud;

	// ...
	CStringArray l_para;
	Macro__Get_Para_List_From_String(str_data, l_para);

	int i_limit = l_para.GetSize();
	int i;

	// PKT   SEQ    OFF  OFF    OFF        REQ    9600
	// [M/B] [FLOW] [LF] [ECHO] [CHECKSUM] [DREP] [BAUD]
	for(i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)			
		{
			if(str_data.CompareNoCase("COMM") == 0)		active__recv_ok = true;
			else										active__recv_ok = false;
		}
		else if(i == 1)			str__mode = str_para;
		else if(i == 2)			str__flow = str_para;
		else if(i == 3)			str__lf   = str_para;
		else if(i == 4)			str__echo = str_para;
		else if(i == 5)			str__checksum = str_para;
		else if(i == 6)			str__drep = str_para;
		else if(i == 7)			str__baud = str_para;
	}

	if(active__recv_ok)
	{
		sCH__MON_COMM_MODE->Set__DATA(str__mode);
		sCH__MON_COMM_FLOW->Set__DATA(str__flow);
		sCH__MON_COMM_LF->Set__DATA(str__lf);
		sCH__MON_COMM_ECHO->Set__DATA(str__echo);
		sCH__MON_COMM_CHECKSUM->Set__DATA(str__checksum);
		sCH__MON_COMM_DREP->Set__DATA(str__drep);
		sCH__MON_COMM_BAUD->Set__DATA(str__baud);
	}
	else
	{
		CString ch_data = "??";

		sCH__MON_COMM_MODE->Set__DATA(ch_data);
		sCH__MON_COMM_FLOW->Set__DATA(ch_data);
		sCH__MON_COMM_LF->Set__DATA(ch_data);
		sCH__MON_COMM_ECHO->Set__DATA(ch_data);
		sCH__MON_COMM_CHECKSUM->Set__DATA(ch_data);
		sCH__MON_COMM_DREP->Set__DATA(ch_data);
		sCH__MON_COMM_BAUD->Set__DATA(ch_data);
	}

	return 1;
}

int  CObj__VAC_ROBOT_SERIAL::Update__WAF_CEN_DATA(const CString& str_data)
{
	bool active__recv_ok = false;

	CString str__rt_rl;
	CString str__rt_tl;
	CString str__rt_rt;
	CString str__rt_tt;

	CString str__lft_rl;
	CString str__lft_tl;
	CString str__lft_rt;
	CString str__lft_tt;

	CString str__cen_rl;
	CString str__cen_tl;
	CString str__cen_rt;
	CString str__cen_tt;
	CString str__cen_ro;
	CString str__cen_to;

	// ...
	CStringArray l_para;
	Macro__Get_Para_List_From_String(str_data, l_para);

	int i_limit = l_para.GetSize();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)			
		{
			if(str_data.CompareNoCase("WAF_CEN") == 0)			active__recv_ok = true;
			else												active__recv_ok = false;
		}
		else if(i == 1)
		{
			if(str_data.CompareNoCase("DATA") != 0)				active__recv_ok = false;
		}
		else if(i == 2)
		{
			if(str_data.CompareNoCase("RIGHT_SENS") != 0)		active__recv_ok = false;
		}
		else if(i == 3)				str__rt_rl = str_para;
		else if(i == 4)				str__rt_tl = str_para;
		else if(i == 5)				str__rt_rt = str_para;
		else if(i == 6)				str__rt_tt = str_para;
		else if(i == 7)
		{
			if(str_data.CompareNoCase("LEFT_SENS") != 0)		active__recv_ok = false;
		}
		else if(i == 8)				str__lft_rl = str_para;
		else if(i == 9)				str__lft_tl = str_para;
		else if(i == 10)			str__lft_rt = str_para;
		else if(i == 11)			str__lft_tt = str_para;
		else if(i == 12)
		{
			if(str_data.CompareNoCase("OFFSET") != 0)			active__recv_ok = false;
		}
		else if(i == 13)			str__cen_rl = str_para;
		else if(i == 14)			str__cen_tl = str_para;
		else if(i == 15)			str__cen_rt = str_para;
		else if(i == 16)			str__cen_tt = str_para;
		else if(i == 17)			str__cen_ro = str_para;
		else if(i == 18)			str__cen_to = str_para;
	}

	if(active__recv_ok)
	{
		sCH__MON_WFR_CEN__RT_RL->Set__DATA(str__rt_rl);
		sCH__MON_WFR_CEN__RT_TL->Set__DATA(str__rt_tl);
		sCH__MON_WFR_CEN__RT_RT->Set__DATA(str__rt_rt);
		sCH__MON_WFR_CEN__RT_TT->Set__DATA(str__rt_tt);

		sCH__MON_WFR_CEN__LFT_RL->Set__DATA(str__lft_rl);
		sCH__MON_WFR_CEN__LFT_TL->Set__DATA(str__lft_tl);
		sCH__MON_WFR_CEN__LFT_RT->Set__DATA(str__lft_rt);
		sCH__MON_WFR_CEN__LFT_TT->Set__DATA(str__lft_tt);

		sCH__MON_WFR_CEN__CEN_RL->Set__DATA(str__cen_rl);
		sCH__MON_WFR_CEN__CEN_TL->Set__DATA(str__cen_tl);
		sCH__MON_WFR_CEN__CEN_RT->Set__DATA(str__cen_rt);
		sCH__MON_WFR_CEN__CEN_TT->Set__DATA(str__cen_tt);
		sCH__MON_WFR_CEN__CEN_RO->Set__DATA(str__cen_ro);
		sCH__MON_WFR_CEN__CEN_TO->Set__DATA(str__cen_to);
	}
	else
	{
		CString ch_data = "??";

		sCH__MON_WFR_CEN__RT_RL->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__RT_TL->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__RT_RT->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__RT_TT->Set__DATA(ch_data);

		sCH__MON_WFR_CEN__LFT_RL->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__LFT_TL->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__LFT_RT->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__LFT_TT->Set__DATA(ch_data);

		sCH__MON_WFR_CEN__CEN_RL->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__CEN_TL->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__CEN_RT->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__CEN_TT->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__CEN_RO->Set__DATA(ch_data);
		sCH__MON_WFR_CEN__CEN_TO->Set__DATA(ch_data);
	}

	return 1;
}

int  CObj__VAC_ROBOT_SERIAL::Update__RQ_POS_STN_DATA(const CString& str_data)
{
	bool active__recv_ok = false;

	CString str__arm;
	CString str__r_info;
	CString str__stn_info;
	CString str__slot_info;
	CString str__z_info;
	CString str__t_info;

	// ...
	CStringArray l_para;
	Macro__Get_Para_List_From_String(str_data, l_para);

	int i_limit = l_para.GetSize();
	int i;

	// POS STN A (R) (Station) (Slot) (Z) (T)
	for(i=0; i<i_limit; i++)
	{
		CString str_para = l_para[i];

		if(i == 0)			
		{
			if(str_data.CompareNoCase("POS") == 0)			active__recv_ok = true;
			else											active__recv_ok = false;
		}
		else if(i == 1)
		{
			if(str_data.CompareNoCase("STN") != 0)			active__recv_ok = false;
		}
		else if(i == 2)			str__arm = str_para;
		else if(i == 3)			str__r_info    = str_para;
		else if(i == 4)			str__stn_info  = str_para;
		else if(i == 5)			str__slot_info = str_para;
		else if(i == 6)			str__z_info    = str_para;
		else if(i == 7)			str__t_info    = str_para;
	}

	if(active__recv_ok)
	{
		if(str__arm.CompareNoCase(ARM_A) == 0)
		{
			sCH__MON_POS_STN__R_INFO__ARM_A->Set__DATA(str__r_info);
			sCH__MON_POS_STN__STATION_INFO__ARM_A->Set__DATA(str__stn_info);
			sCH__MON_POS_STN__SLOT_INFO__ARM_A->Set__DATA(str__slot_info);
			sCH__MON_POS_STN__Z_INFO__ARM_A->Set__DATA(str__z_info);
			sCH__MON_POS_STN__T_INFO__ARM_A->Set__DATA(str__t_info);
		}
		else if(str__arm.CompareNoCase(ARM_B) == 0)
		{
			sCH__MON_POS_STN__R_INFO__ARM_B->Set__DATA(str__r_info);
			sCH__MON_POS_STN__STATION_INFO__ARM_B->Set__DATA(str__stn_info);
			sCH__MON_POS_STN__SLOT_INFO__ARM_B->Set__DATA(str__slot_info);
			sCH__MON_POS_STN__Z_INFO__ARM_B->Set__DATA(str__z_info);
			sCH__MON_POS_STN__T_INFO__ARM_B->Set__DATA(str__t_info);
		}
	}
	else
	{
		CString ch_data = "??";

		if(str__arm.CompareNoCase(ARM_A) == 0)
		{
			sCH__MON_POS_STN__R_INFO__ARM_A->Set__DATA(ch_data);
			sCH__MON_POS_STN__STATION_INFO__ARM_A->Set__DATA(ch_data);
			sCH__MON_POS_STN__SLOT_INFO__ARM_A->Set__DATA(ch_data);
			sCH__MON_POS_STN__Z_INFO__ARM_A->Set__DATA(ch_data);
			sCH__MON_POS_STN__T_INFO__ARM_A->Set__DATA(ch_data);
		}
		else if(str__arm.CompareNoCase(ARM_B) == 0)
		{
			sCH__MON_POS_STN__R_INFO__ARM_B->Set__DATA(ch_data);
			sCH__MON_POS_STN__STATION_INFO__ARM_B->Set__DATA(ch_data);
			sCH__MON_POS_STN__SLOT_INFO__ARM_B->Set__DATA(ch_data);
			sCH__MON_POS_STN__Z_INFO__ARM_B->Set__DATA(ch_data);
			sCH__MON_POS_STN__T_INFO__ARM_B->Set__DATA(ch_data);
		}
	}

	return 1;
}
