#include "StdAfx.h"
#include "CObj__LOT_NET.h"
#include "CObj__LOT_NET__DEF.h"
#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int CObj__LOT_NET
::__Read__ANALOG(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 double& read_data)
{

	return -1;
}

int CObj__LOT_NET
::__Read__DIGITAL(const CString& var_name,
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  CString& read_data,
				  int& item_index)
{

	return -1;
}

int CObj__LOT_NET
::__Read__STRING(const CString& var_name, 
				 const CDS_IO__CHANNEL_INFO& io_info, 
				 CString& read_data)
{
	CString set_cmmd = "";

	if(siCH__MODE_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "MODR";
	}
	else if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "VERR";
	}
	else if(siCH__PUMP_WARNING->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "RWNR1";
	}
	else if(siCH__BLOWER_WARNING->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "RWNR2";
	}
	else if(siCH__PUMP_ALARM->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "RALR";
	}
	else if(siCH__PUMP_BODY_TEMPERATURE->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "PTMR";
	}
	else if(siCH__EXHAUST_PRESSURE->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "REPR";
	}
	else if(siCH__PUMP_MOTOR_CURRENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "RMCR1";
	}
	else if(siCH__BLOWER_MOTOR_CURRENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		set_cmmd = "RMCR2";
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

	log_msg.Format("RECV << [%1d] \n", r_flag);
	log_msg += r_data;
	log_msg += "\n";

	WRITE__DRV_LOG_MSG(log_msg);

	// ...
	CString rsp_cmmd  = "";
	CString rsp_data1 = "";
	CString rsp_data2 = "";
	CString ch_data;

	// ...
	{
		CStringArray l_rsp;
		_Get__STRING_ARRAY(r_data, ",", l_rsp);

		log_msg = "Data.Parsing \n";

		int r_size = l_rsp.GetSize();
		if(r_size > 0)
		{
			rsp_cmmd = l_rsp[0];

			log_bff.Format(" 1. [%s] \n", rsp_cmmd);
			log_msg += log_bff;
		}
		if(r_size > 1)
		{
			rsp_data1 = l_rsp[1];

			log_bff.Format(" 2. [%s] \n", rsp_data1);
			log_msg += log_bff;
		}
		if(r_size > 2)
		{
			rsp_data2 = l_rsp[2];

			log_bff.Format(" 3. [%s] \n", rsp_data2);
			log_msg += log_bff;
		}

		WRITE__DRV_LOG_MSG(log_msg);
	}

	//
	if(siCH__MODE_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data1;

		ch_data = _Get__MODE_STATUS(rsp_data1);
		sCH__MON_MODE_STS->Set__DATA(ch_data);
	}
	else if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_cmmd;

		ch_data = _Get__STRING_DATA(rsp_cmmd, "VER");

		sCH__MON_VERSION->Set__DATA(ch_data);
	}
	else if(siCH__PUMP_WARNING->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data2;
		_Update__PUMP_WARNING(rsp_data2);
	}
	else if(siCH__BLOWER_WARNING->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data2;
		_Update__BLOWER_WARNING(rsp_data2);
	}
	else if(siCH__PUMP_ALARM->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data1;
		_Update__PUMP_ALARM(rsp_data1);
	}
	else if(siCH__PUMP_BODY_TEMPERATURE->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data1;

		ch_data.Format("%.1f", atof(rsp_data1));
		sCH__MON_PUMP_BODY_TEMPERATURE->Set__DATA(ch_data);
	}
	else if(siCH__EXHAUST_PRESSURE->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data1;

		ch_data.Format("%.2f", atof(rsp_data1));
		sCH__MON_EXHAUST_PRESSURE->Set__DATA(ch_data);
	}
	else if(siCH__PUMP_MOTOR_CURRENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data2;

		ch_data.Format("%.1f", atof(rsp_data2));
		sCH__MON_PUMP_MOTOR_CURRENT->Set__DATA(ch_data);
	}
	else if(siCH__BLOWER_MOTOR_CURRENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		read_data = rsp_data2;

		ch_data.Format("%.1f", atof(rsp_data2));
		sCH__MON_BLOWER_MOTOR_CURRENT->Set__DATA(ch_data);
	}

	return 1;
}


//------------------------------------------------------------------------------------
int CObj__LOT_NET
::__Write__ANALOG(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const double set_data)
{

	return -1;
}

int CObj__LOT_NET
::__Write__DIGITAL(const CString& var_name,
				   const CDS_IO__CHANNEL_INFO& io_info, 
				   const CString& set_data,
				   const int item_index)
{
	CString set_cmmd = "";

	if(var_name.CompareNoCase(doCH__MODE_SET->Get__VARIABLE_NAME()) == 0)
	{
		if(set_data.CompareNoCase(_Cmmd_IO__Stop) == 0)
		{
			set_cmmd = "MODW 03";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Start) == 0)
		{
			set_cmmd = "MODW 05";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Stop_Slow) == 0)
		{
			set_cmmd = "MODW 04";
		}
		else if(set_data.CompareNoCase(_Cmmd_IO__Flush) == 0)
		{
			set_cmmd = "MODW 06";
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

int CObj__LOT_NET
::__Write__STRING(const CString& var_name, 
				  const CDS_IO__CHANNEL_INFO& io_info, 
				  const CString& set_data)
{

	return -1;
}


// ...
int  CObj__LOT_NET
::_Drv__CMMD_SEND(const CString& cmmd_org, CString* recv_data)
{
	CString log_msg = "";
	CString log_bff = "";

	int rty_cnt = 0;

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
		log_msg.Format("SEND >> [%s]<CR>", cmmd_org);
		WRITE__DRV_LOG_MSG(log_msg);
	}

	// ...
	CString r_err;

	mX_Net->DATA__SEND(cmmd_org, 1, &r_err);

	// ...
	CString r__data_1;
	int recv_cnt = 0;

	while(1)
	{
		CString r_data;
	
		int r_flag = mX_Net->DATA__RECV_QUEUE(&r_data, 1, &r_err);
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
		recv_cnt++;

		// Recv.Data ...
		{
			log_msg.Format("%1d.RECV << (%1d) \n", recv_cnt, r_flag);

			log_msg += r_data;
			log_msg += "\n";

			WRITE__DRV_LOG_MSG(log_msg);
		}
		
		if(recv_cnt == 1)
		{
			r__data_1 = r_data;
		}
		else if(recv_cnt >= 2)
		{
			if(r__data_1.CompareNoCase(cmmd_org) != 0)		return -11;

			log_msg.Format("RECV.OK !!!");
			WRITE__DRV_LOG_MSG(log_msg);

			recv_data->Format("%s", r_data);
			return 1;
		}
	}

	return -21;
}

int CObj__LOT_NET
::_Get__STRING_ARRAY(const CString& xxx_data,
					 const CString& str_delimiter,
					 CStringArray& l_data)
{
	l_data.RemoveAll();

	CString str_data = xxx_data;
	int del_size = str_delimiter.GetLength();

	while(1)
	{
		int s_index = str_data.Find(str_delimiter);
		if(s_index < 0)
		{
			l_data.Add(str_data);
			return 1;
		}

		// ...
		CString str_rsp = str_data;

		str_rsp.Delete(s_index, str_data.GetLength()-s_index);
		str_data.Delete(0, s_index+del_size);

		l_data.Add(str_rsp);
	}
	return -1;
}
CString CObj__LOT_NET
::_Get__STRING_DATA(const CString& xxx_data,
					const CString& str_delimiter)
{
	CString str_data = xxx_data;

	int s_index = str_data.Find(str_delimiter);
	if(s_index < 0)			return "";

	int del_size = str_delimiter.GetLength();
	str_data.Delete(0, s_index+del_size);

	//CString log_msg;
	//log_msg.Format("xxx_data [%s], [%s], [%d], [%d], [%s]", xxx_data, str_delimiter, s_index, del_size, str_data);
	//WRITE__DRV_LOG_MSG(log_msg);

	return str_data;
}

CString CObj__LOT_NET
::_Get__MODE_STATUS(const CString& rsp_data)
{
	CString i_data = "";
	int	i_val = 0;

	for (int i=0; i<9; i++)
	{
		i_data = rsp_data[i];
		i_val = atoi(i_data);

		if (i_val > 0)
		{
			switch(i)
			{
			case 0:		return "Ready";
			case 1:		return "Start";
			case 2:		return "Stopping";
			case 3:		return "Halt";
			case 4:		return "Wait";
			case 5:		return "Operating";
			case 6:		return "Standby";
			case 7:		return "Flush";
			case 8:		return "Stop Run Down";
			}
		}
	}

	return "Unknown";
}

int CObj__LOT_NET
::_Update__PUMP_WARNING(const CString& rsp_data)
{
	CString ch_data;

	int r_len = rsp_data.GetLength();

	int i_limit = 16;
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(i < r_len)
		{
			char ch = rsp_data.GetAt(i);

			if(ch == '1')			ch_data = STR__ON;
			else					ch_data = STR__OFF;
		}
		else
		{
			ch_data = "";
		}

		if(i == 0)		sCH__MON_WARNING_PUMP_BODY_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 1)		sCH__MON_WARNING_EXHAUST_PRESSURE->Set__DATA(ch_data);
		else if(i == 2)		sCH__MON_WARNING_OIL_PRESSURE->Set__DATA(ch_data);
		else if(i == 3)		sCH__MON_WARNING_H2O_FLOW->Set__DATA(ch_data);
		else if(i == 4)		sCH__MON_WARNING_PURGE_FLOW_ANALOG_1->Set__DATA(ch_data);
		else if(i == 5)		sCH__MON_WARNING_PURGE_FLOW_ANALOG_2->Set__DATA(ch_data);
		else if(i == 6)		sCH__MON_WARNING_PROCESS_TEMPERATURE_LOW->Set__DATA(ch_data);
		else if(i == 7)		sCH__MON_WARNING_PROCESS_TEMPERATURE_HIGH->Set__DATA(ch_data);
		else if(i == 8)		sCH__MON_WARNING_PUMP_MOTOR_OVER_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 9)		sCH__MON_WARNING_PUMP_VFD_DIGITAL->Set__DATA(ch_data);
		else if(i == 10)	sCH__MON_WARNING_EXHAUST_PRESSURE_LOW->Set__DATA(ch_data);
		else if(i == 11)	sCH__MON_WARNING_EXHAUST_PRESSURE_HIGH->Set__DATA(ch_data);
		else if(i == 12)	sCH__MON_WARNING_PUMP_MOTOR_CURRENT->Set__DATA(ch_data);
		else if(i == 13)	sCH__MON_WARNING_HOT_N2_TEMPERAURE->Set__DATA(ch_data);
		else if(i == 14)	sCH__MON_WARNING_PUMP_VFD_ANALOG->Set__DATA(ch_data);
	}
	return 1;
}
int CObj__LOT_NET
::_Update__BLOWER_WARNING(const CString& rsp_data)
{
	CString ch_data;

	int r_len = rsp_data.GetLength();

	int i_limit = 16;
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(i < r_len)
		{
			char ch = rsp_data.GetAt(i);

			if(ch == '1')			ch_data = STR__ON;
			else					ch_data = STR__OFF;
		}
		else
		{
			ch_data = "";
		}

		if(i == 0)		sCH__MON_WARNING_BLOWER_MOTOR_CURRENT->Set__DATA(ch_data);
		else if(i == 1)		sCH__MON_WARNING_INLET_PRESSURE_SWITCH->Set__DATA(ch_data);
		else if(i == 2)		sCH__MON_WARNING_BLOWER_1_VFD->Set__DATA(ch_data);
		else if(i == 3)		sCH__MON_WARNING_BLOWER_MOTOR_CONTACTOR->Set__DATA(ch_data);
		else if(i == 4)		sCH__MON_WARNING_BLOWER_MOTOR_OVERLOAD->Set__DATA(ch_data);
		else if(i == 5)		sCH__MON_WARNING_BLOWER_BODY_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 6)		sCH__MON_WARNING_BLOWER_VFD->Set__DATA(ch_data);
	}
	return 1;
}
int CObj__LOT_NET
::_Update__PUMP_ALARM(const CString& rsp_data)
{
	CString ch_data;

	int r_len = rsp_data.GetLength();

	int i_limit = 16;
	int i;

	for(i=0; i<i_limit; i++)
	{
		if(i < r_len)
		{
			char ch = rsp_data.GetAt(i);

			if(ch == '1')			ch_data = STR__ON;
			else					ch_data = STR__OFF;
		}
		else
		{
			ch_data = "";
		}

		if(i == 0)		sCH__MON_ALARM_PUMP_BODY_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 1)		sCH__MON_ALARM_EXHAUST_PRESSURE->Set__DATA(ch_data);
		else if(i == 2)		sCH__MON_ALARM_MISSING_OIL_TIMEOUT->Set__DATA(ch_data);
		else if(i == 3)		sCH__MON_ALARM_PUMP_MOTOR_CONTACTOR->Set__DATA(ch_data);
		else if(i == 4)		sCH__MON_ALARM_PUMP_MOTOR_OVERLOAD->Set__DATA(ch_data);
		else if(i == 5)		sCH__MON_ALARM_BLOWER_BODY_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 6)		sCH__MON_ALARM_EMO->Set__DATA(ch_data);
		else if(i == 7)		sCH__MON_ALARM_PUMP_MOTOR_OVER_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 8)		sCH__MON_ALARM_BLOWER_MOTOR_CONTACTOR->Set__DATA(ch_data);
		else if(i == 9)		sCH__MON_ALARM_EXHAUST_MANIFOLD_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 10)	sCH__MON_ALARM_BLOWER_MOTOR_OVERLOAD->Set__DATA(ch_data);
		else if(i == 11)	sCH__MON_ALARM_PURGE_FLOW_ANALOG_1->Set__DATA(ch_data);
		else if(i == 12)	sCH__MON_ALARM_PURGE_FLOW_ANALOG_2->Set__DATA(ch_data);
		else if(i == 13)	sCH__MON_ALARM_BLOWER_MOTOR_OVER_TEMPERATURE->Set__DATA(ch_data);
		else if(i == 14)	sCH__MON_ALARM_H2O_FLOW->Set__DATA(ch_data);
		else if(i == 15)	sCH__MON_ALARM_PUMP_MOTOR_CURRENT->Set__DATA(ch_data);
	}
	return 1;
}
