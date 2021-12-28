#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"

#include "CCommon_DEF.h"
#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int CDriver__LPx_ETHERNET
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CDriver__LPx_ETHERNET
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommState == OFFLINE)			read_data = STR__OFFLINE;
		else								read_data = STR__ONLINE;

		return 1;
	}

	return -1;
}

int CDriver__LPx_ETHERNET
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str_cmmd;
	CString str_lp;
	CString set_para;
	CString rsp_data;
	int i;


	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		int lp_id = i + 1;
		str_lp.Format("%1d", lp_id);

		// LP_STATE ...
		if(siCH__LP_STATE_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = _DRV_GET__STATE;
			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				read_data = "Error";
				return 1;
			}

			printf(" ### rsp_data <- [%s] \n", rsp_data);

			_Update__LPx_STATE(lp_id, rsp_data);

			read_data = "OK";
			return 1;
		}

		// MAP DATA ...
		if(siCH__LP_MAP_DATA_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = _DRV_GET__LP_MAP;
			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				read_data = "Error";
				return 1;
			}

			_Update__LPx_MAP(lp_id, rsp_data);

			read_data = "OK";
			return 1;
		}

		// ALARM MSG ...
		if(siCH__LP_ALARM_MSG_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = _DRV_GET__ALM_MSG;
			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				read_data = "Error";
				return 1;
			}

			sCH__LP_INFO__ALM_MSG_X[i]->Set__DATA(rsp_data);

			read_data = "OK";
			return 1;   
		}
		// ALARM TXT ...
		if(siCH__LP_ALARM_TXT_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = _DRV_GET__ALM_TXT;
			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				read_data = "Error";
				return 1;
			}

			sCH__LP_INFO__ALM_TXT_X[i]->Set__DATA(rsp_data);

			read_data = "OK";
			return 1;   
		}

		// N2 STATUS ...
		if(siCH__LP_N2_STATUS_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = "@N2STS";
			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				read_data = "Error";
				return 1;
			}

			_Update__LPx_N2_STS(lp_id, rsp_data);

			read_data = "OK";
			return 1;   
		}

		// RFID ...
		if(siCH__RFID_READ_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			int page_id = (int) aCH__PARA_RFID_PAGE_ID_X[i]->Get__VALUE();

			str_cmmd = _DRV_GET__RFID_READ;			
			set_para.Format("[%02d]", page_id);

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				read_data = "Error";
				return 1;
			}

			sCH__LP_INFO__RFID_RSP_X[i]->Set__DATA(rsp_data);

			read_data = "OK";
			return 1;   
		}
	}

	// PIO_TP_INFO ...
	if(siCH__PIO_TP_INFO->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = _DRV_GET__TIME_READ;
		str_lp   = "0";
		set_para = "";

		int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
		if(r_flag < 0)
		{
			return -1;
		}

		// ...
		{
			char ch_check = '/';
			CStringArray l_para;

			Macro__Get_String_List(rsp_data, ch_check, l_para);

			int k_limit = l_para.GetSize();
			int k;

			for(k=0; k<k_limit; k++)
			{
				CString ch_data = l_para[k];

				if(k < CFG_PIO__TP_SIZE)		sCH__PIO_INFO__TP_X[k]->Set__DATA(ch_data);
			}

			for( ; k<CFG_PIO__TP_SIZE; k++)
			{
				sCH__PIO_INFO__TP_X[k]->Set__DATA("");
			}
		}
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CDriver__LPx_ETHERNET
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	CString str_cmmd;
	CString str_lp;
	CString set_para;
	CString rsp_data;
	int i;


	// PIO_TP ...
	for(i=0; i<CFG_PIO__TP_SIZE; i++)
	{
		int id = i + 1;
		
		if(aoCH__PIO_TP_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = _DRV_SET__AVG_TIMEOUT;
			str_lp   = "0";

			set_para.Format("[%1d%03d]", id, (int) set_data);

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data);
			if(r_flag < 0)
			{
				return -1;
			}

			return 1;			
		}
	}

	return 1;
}

int CDriver__LPx_ETHERNET
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	CString str_cmmd;
	CString str_lp;
	CString set_para;
	CString rsp_data;
	int i;


	// EFEM_MODE ...
	if(doCH__EFEM_MODE->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString para_comm = "0";
		if(dCH__CFG_COMM_MODE->Check__DATA(STR__POLLING) > 0)		para_comm = "1";

		str_cmmd = _DRV_SET__MODE;
		str_lp   = "0";
		set_para.Format("[00000%s0]", para_comm);

		int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
		if(r_flag < 0)
		{
			return -1;
		}

		return 1;
	}

	// LP_CHECK ...
	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		str_lp.Format("%1d", i + 1);

		// LP_MODE ...
		if(doCH__LP_MODE_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			CString para_01 = "0";
			CString para_03 = "0";
			CString para_04 = "0";
			CString para_05 = "0";

			if(dCH__CFG_LP_MODE_X[i]->Check__DATA(STR__AMHS)   > 0)				para_01 = "1";
			if(dCH__CFG_LP_RFID_X[i]->Check__DATA(STR__ENABLE) > 0)				para_03 = "1";
			if(dCH__CFG_LP_USE_X[i]->Check__DATA(STR__YES)     > 0)				para_04 = "1";
			if(dCH__CFG_LP_CLOSE_MAPPING_X[i]->Check__DATA(STR__YES) > 0)		para_05 = "1";

			str_cmmd = _DRV_SET__MODE;
			set_para.Format("[%s0%s%s%s00]", para_01,para_03,para_04,para_05);

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				return -1;
			}

			return 1;
		}

		// LP_CMMD ...
		if(doCH__LP_CMMD_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
				 if(set_data.CompareNoCase(_CMD__INIT)    == 0)			str_cmmd = _DRV_SET__INIT;
			else if(set_data.CompareNoCase(_CMD__LOAD)    == 0)			str_cmmd = _DRV_SET__LOAD;
			else if(set_data.CompareNoCase(_CMD__UNLOAD)  == 0)			str_cmmd = _DRV_SET__UNLOAD;
			else if(set_data.CompareNoCase(_CMD__OPEN)    == 0)			str_cmmd = _DRV_SET__OPEN;
			else if(set_data.CompareNoCase(_CMD__CLOSE)   == 0)			str_cmmd = _DRV_SET__CLOSE;
			else if(set_data.CompareNoCase(_CMD__CLAMP)   == 0)			str_cmmd = _DRV_SET__CLAMP;
			else if(set_data.CompareNoCase(_CMD__UNCLAMP) == 0)			str_cmmd = _DRV_SET__UCLAMP;
			else														return -1;				

			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				return -1;
			}

			return 1;   
		}

		// PIO_RESET ...
		if(doCH__PIO_RESET_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			str_cmmd = _DRV_SET__RESET;
			set_para = "";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				return -1;
			}

			return 1;
		}

		// N2_RUN ...
		if(doCH__LP_N2_RUN_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			CString para_00__run;
			CString para_01__vlv;
			CString para_01__mfc;
			CString para_02__vlv;
			CString para_02__mfc;
			CString para_03__vlv;
			CString para_03__mfc;
			CString para_04;
			CString para_05;

			if(set_data.CompareNoCase(STR__START) == 0)			para_00__run = "1";
			else												para_00__run = "0";

			dCH__CFG_LP_N2_NOZZLE_1__VALVE_X[i]->Get__DATA(para_01__vlv);
			aCH__CFG_LP_N2_NOZZLE_1__MFC_X[i]->Get__DATA(para_01__mfc);
			dCH__CFG_LP_N2_NOZZLE_2__VALVE_X[i]->Get__DATA(para_02__vlv);
			aCH__CFG_LP_N2_NOZZLE_2__MFC_X[i]->Get__DATA(para_02__mfc);
			dCH__CFG_LP_N2_NOZZLE_3__VALVE_X[i]->Get__DATA(para_03__vlv);
			aCH__CFG_LP_N2_NOZZLE_3__MFC_X[i]->Get__DATA(para_03__mfc);
			
			if(dCH__CFG_LP_N2_EHHAUST_NOZZLE_X[i]->Check__DATA(STR__ON) > 0)		para_04 = "1";
			else																	para_04 = "0";
			
			aCH__CFG_LP_N2_DELAY_TIME_X[i]->Get__DATA(para_05);

			//
			str_cmmd  = _DRV_SET__N2_RUN;

			set_para  = "[";
			set_para += para_00__run;
			set_para += "/";

			set_para += para_01__vlv;
			set_para += para_01__mfc;
			set_para += "/";

			set_para += para_02__vlv;
			set_para += para_02__mfc;
			set_para += "/";

			set_para += para_03__vlv;
			set_para += para_03__mfc;
			set_para += "/";

			set_para += para_04;
			set_para += "/";

			set_para += para_05;
			set_para += "]";

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				return -1;
			}

			return 1;
		}
	}

	// LAMP & BUZZER ...
	if(doCH__EFEM_LAMP_BUZZER->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString para_01 = "0";
		CString para_02 = "0";
		CString para_03 = "0";
		CString para_04 = "0";
		CString para_05 = "0";

			 if(dCH__PARA_LAMP_RED->Check__DATA(STR__ON)    > 0)			para_01 = "1";
		else if(dCH__PARA_LAMP_RED->Check__DATA(STR__BLINK) > 0)			para_01 = "2";

			 if(dCH__PARA_LAMP_YELLOW->Check__DATA(STR__ON)    > 0)			para_02 = "1";
		else if(dCH__PARA_LAMP_YELLOW->Check__DATA(STR__BLINK) > 0)			para_02 = "2";

			 if(dCH__PARA_LAMP_GREEN->Check__DATA(STR__ON)    > 0)			para_03 = "1";
		else if(dCH__PARA_LAMP_GREEN->Check__DATA(STR__BLINK) > 0)			para_03 = "2";

			 if(dCH__PARA_LAMP_BLUE->Check__DATA(STR__ON)    > 0)			para_04 = "1";
		else if(dCH__PARA_LAMP_BLUE->Check__DATA(STR__BLINK) > 0)			para_04 = "2";

			 if(dCH__PARA_ALARM_BUZZER->Check__DATA(STR__ON)   > 0)			para_05 = "1";
		else if(dCH__PARA_ALARM_BUZZER->Check__DATA(STR__ON_1) > 0)			para_05 = "2";
		else if(dCH__PARA_ALARM_BUZZER->Check__DATA(STR__ON_2) > 0)			para_05 = "3";

		str_cmmd = _DRV_SET__SIGNAL_LAMP;
		str_lp   = "0";

		set_para  = "[";
		set_para += para_01;
		set_para += para_02;
		set_para += para_03;
		set_para += para_04;
		set_para += para_05;
		set_para += "]";

		int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
		if(r_flag < 0)
		{
			return -1;
		}

		return 1;
	}

	return -1;
}

int CDriver__LPx_ETHERNET
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	CString str_cmmd;
	CString str_lp;
	CString set_para;
	CString rsp_data;
	int i;


	if(soCH__CHECK_CMMD->Check__VARIABLE_NAME(var_name) > 0)
	{
		str_cmmd = set_data;
		str_lp   = "";
		set_para = "";

		int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
		if(r_flag < 0)
		{
			return -1;
		}

		printf("__Write__STRING() <- [%s] \m", rsp_data);
		return 1;
	}

	// LPx CHECK ...
	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		str_lp.Format("%1d", i + 1);

		// RFID WRITE
		if(soCH__RFID_WRITE_X[i]->Check__VARIABLE_NAME(var_name) > 0)
		{
			int page_id = (int) aCH__PARA_RFID_PAGE_ID_X[i]->Get__VALUE();
			
			str_cmmd = _DRV_SET__RFID_WRITE;
			set_para.Format("[%02d%s]", page_id, set_data);

			int r_flag = Drv__GET_LPx_CMMD(var_name, str_cmmd,str_lp,set_para, rsp_data) ;
			if(r_flag < 0)
			{
				return -1;
			}

			return 1;
		}
	}

	return -1;
}
