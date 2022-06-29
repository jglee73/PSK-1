#include "StdAfx.h"
#include "CObj__VAC_NET.h"
#include "CObj__VAC_NET__DEF.h"
#include "CCommon_DEF.h"

#include "Macro_Function.h"


//------------------------------------------------------------------------------------
int CObj__VAC_NET
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{

	return -1;
}

int CObj__VAC_NET
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{

	return -1;
}

int CObj__VAC_NET
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{
	CString set_cmmd = "";

	if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "IDN";
	}
	else if(siCH__PUMP_STATE->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "STA";
	}
	else
	{
		return -1;
	}

	// ...
	CString r_data = "";

	int r_flag = _Drv__CMMD_SEND(set_cmmd, &r_data);

	// ...
	CString log_msg;
	CString log_bff;

	log_msg.Format("DATA(%1d) : [%s] \n", r_flag,r_data);
	WRITE__DRV_LOG_MSG(log_msg);

	if(r_flag < 0)
	{
		read_data = "Error";
		return -1;
	}

	// ...
	CString rsp_data1 = "";
	CString rsp_data2 = "";
	CString rsp_data3 = "";
	CString ch_data;

	// ...
	{
		CStringArray l_rsp;
		Macro__Get_Para_List_From_String(r_data, l_rsp);

		log_msg = "Data.Parsing \n";

		int r_size = l_rsp.GetSize();
		if(r_size > 0)
		{
			rsp_data1 = l_rsp[0];

			log_bff.Format(" 1. [%s] \n", rsp_data1);
			log_msg += log_bff;
		}
		if(r_size > 1)
		{
			rsp_data2 = l_rsp[1];

			log_bff.Format(" 2. [%s] \n", rsp_data2);
			log_msg += log_bff;
		}
		if(r_size > 2)
		{
			rsp_data3 = l_rsp[2];

			log_bff.Format(" 3. [%s] \n", rsp_data3);
			log_msg += log_bff;
		}

		WRITE__DRV_LOG_MSG(log_msg);
	}

	if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		rsp_data1.Trim();
		ch_data.Format("Ver.%s", rsp_data1);

		sCH__MON_VERSION->Set__DATA(ch_data);
	}
	else if(siCH__PUMP_STATE->Check__VARIABLE_NAME(var_name) > 0)
	{
		// Pump.State ...
		_Update__PUMP_STATE(rsp_data1);

		sCH__MON_STATE_PRESSURE_mBAR->Set__DATA(rsp_data2);
		sCH__MON_STATE_FB_POWER->Set__DATA(rsp_data3);
	}

	read_data = "OK";
	return 1;
}


//------------------------------------------------------------------------------------
int CObj__VAC_NET
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{

	return -1;
}

int CObj__VAC_NET
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CString set_cmmd = "";

	if(doCH__MODE_SET->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(_Cmmd_IO__Pump_Stop) == 0)
		{
			set_cmmd = "SYS OFF";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Pump_Start) == 0)
		{
			set_cmmd = "SYS ON";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Roots_Stop) == 0)
		{
			set_cmmd = "ROO OFF";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Roots_Start) == 0)
		{
			set_cmmd = "ROO ON";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Purge_Stop) == 0)
		{
			set_cmmd = "PUR OFF";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Purge_Start) == 0)
		{
			set_cmmd = "PUR ON";
		}
		else
		{
			return -1;
		}
	}
	else if(doCH__PUMP_ADDRESS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(_Cmmd_IO__Set) == 0)
		{
			set_cmmd.Format("ADR %03d", iPara__ADDR_ID);
		}
		else
		{
			return -1;
		}
	}
	else if(doCH__SERPERATOR_CHAR->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase(_Cmmd_IO__Set) == 0)
		{
			set_cmmd.Format("SEP %03d", ' ');
		}
		else
		{
			return -1;
		}
	}
	else
	{
		return -1;
	}

	// ...
	CString r_data = "";
	int r_flag = _Drv__CMMD_SEND(set_cmmd, &r_data);

	if(r_flag < 0)
	{
		return -1;
	}

	return 1;
}

int CObj__VAC_NET
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return -1;
}


// ...
int  CObj__VAC_NET
::_Drv__CMMD_SEND(const CString& cmmd_data, CString* p_recv)
{
	CString log_msg = "";
	CString log_bff = "";

	CString cmmd_addr;
	CString cmmd_org;

	int i_addr = iPara__ADDR_ID;
	int rty_cnt = 0;

	cmmd_addr.Format("#%03d", i_addr);
	cmmd_org.Format("%s%s", cmmd_addr,cmmd_data);

LOOP_RETRY:

	// ...
	{
		CString err_msg;

		mX_Net->CLEAR__BUFFER(&err_msg);
		if(err_msg.GetLength() > 0)
		{
			log_msg.Format("Clear__Buffer() .. \n");
			log_msg += " * Clear_Msg : ";
			log_msg += err_msg;
			log_msg += "\n";

			WRITE__DRV_LOG_MSG(log_msg);
		}

		mX_Net->CLEAR__MEM_BUFFER(&err_msg);
		if(err_msg.GetLength() > 0)
		{
			log_msg.Format(" Clear__Mem_Buffer() .. \n");
			log_msg += " * Clear_Mem_Buffer : ";
			log_msg += err_msg;
			log_msg += "\n";

			WRITE__DRV_LOG_MSG(log_msg);
		}
	}

	// ...
	{
		log_msg = "SEND >> \n";

		log_bff.Format("%s<CR>\n", cmmd_org);
		log_msg += log_bff;

		WRITE__DRV_LOG_MSG(log_msg);
	}

	// ...
	CString r_err;

	mX_Net->DATA__SEND(cmmd_org, 1, &r_err);

	while(1)
	{
		CString r_data;

		int r_flag = mX_Net->DATA__RECV_QUEUE(&r_data, 1, &r_err);

		// ...
		{
			log_msg.Format("RECV << [%1d] \n", r_flag);

			log_bff.Format("%s\n", r_data);
			log_msg += log_bff;

			WRITE__DRV_LOG_MSG(log_msg);
		}

		if(r_flag < 0)
		{
			rty_cnt++;	
			if (rty_cnt < 3)
			{
				log_msg.Format("Error retry [%d] !", rty_cnt);
				log_bff.Format(" * r_err <- [%s] \n", r_err);
				log_msg += log_bff;

				WRITE__DRV_LOG_MSG(log_msg);

				goto LOOP_RETRY;
			}

			log_msg.Format( "Error timeout ! \n");
			WRITE__DRV_LOG_MSG(log_msg);

			bActive__COMM_ONLINE = false;
			return -1;
		}

		bActive__COMM_ONLINE = true;

		if(r_data.Find(cmmd_org) != 0)
		{
			int s_index = r_data.Find(cmmd_addr);
			if(s_index < 0)		return -11;

			r_data.Delete(0, s_index+cmmd_addr.GetLength());
			p_recv->Format("%s", r_data);
			return 1;
		}

		log_msg.Format("Echo Mode ! \n");
		WRITE__DRV_LOG_MSG(log_msg);
	}

	return -21;
}

int CObj__VAC_NET
::_Update__PUMP_STATE(const CString& rsp_data)
{
	int i_limit = rsp_data.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		CString ch_data = "";
		ch_data += rsp_data[i];

		int i_data = atoi(ch_data);

		if(i == 0)
		{
			if(i_data > 0)		sCH__MON_STATE_PUMP_RUNNING->Set__DATA(STR__ON);
			else				sCH__MON_STATE_PUMP_RUNNING->Set__DATA(STR__OFF);

			continue;
		}
		if(i == 1)
		{
			if(i_data > 0)		sCH__MON_STATE_ROOTS_RUNNING->Set__DATA(STR__ON);
			else				sCH__MON_STATE_ROOTS_RUNNING->Set__DATA(STR__OFF);

			continue;
		}
		if(i == 2)
		{
			if(i_data > 0)		sCH__MON_STATE_N2_VALVE->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_N2_VALVE->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 3)
		{
			if(i_data > 0)		sCH__MON_STATE_STDBY_VALVE->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_STDBY_VALVE->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 4)
		{
			if(i_data > 0)		sCH__MON_STATE_WATER_VALVE->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_WATER_VALVE->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 5)
		{
			if(i_data > 0)		sCH__MON_STATE_INLET_VALVE->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_INLET_VALVE->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 6)
		{
			if(i_data > 0)		sCH__MON_STATE_PERMIT_VALVE->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_PERMIT_VALVE->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 7)
		{
			if(i_data > 0)		sCH__MON_STATE_HP_FB_VALVE->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_HP_FB_VALVE->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 8)
		{
			if(i_data > 0)		sCH__MON_STATE_HEAT1_POWER->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_HEAT1_POWER->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 9)
		{
			if(i_data > 0)		sCH__MON_STATE_FAULT->Set__DATA(STR__OPEN);
			else				sCH__MON_STATE_FAULT->Set__DATA(STR__CLOSE);

			continue;
		}
		if(i == 10)
		{
			CString str_data;

			if(i_data == 0)		str_data = "No Control";
			else if(i_data == 1)		str_data = "Remote";
			else if(i_data == 3)		str_data = "Serial Link";
			else if(i_data == 4)		str_data = "User";
			else if(i_data == 5)		str_data = "HHR";
			else						str_data.Format("%1d", i_data);

			sCH__MON_STATE_CONTROL_MODE->Set__DATA(str_data);
			continue;
		}
	}

	return 1;
}
