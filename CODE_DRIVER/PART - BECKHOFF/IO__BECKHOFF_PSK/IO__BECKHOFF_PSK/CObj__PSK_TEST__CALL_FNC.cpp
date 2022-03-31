#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__ALID.h"
#include "CObj__PSK_TEST__DEF.h"


#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CDRV__ADS_CTRL.h"
extern CDRV__ADS_CTRL mDRV__ADS_CTRL; 

#include "CCH__ADS_CTRL.h"
extern CCH__ADS_CTRL mCH__ADS_CTRL;


//-------------------------------------------------------------------------	
int  CObj__PSK_TEST
::Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{

	return 1;
}

// ...
void CObj__PSK_TEST
::Get__PLC_NETID(const CString& str_netid, CStringArray& l_id)
{
	CString str_id;

	int i_limit = str_netid.GetLength();
	int i;

	for(i=0; i<i_limit; i++)
	{
		char ch = str_netid[i];

		if(ch == '.')
		{
			l_id.Add(str_id);

			str_id = "";
		}
		else
		{
			str_id += ch;
		}
	}

	if(str_id.GetLength() > 0)
	{
		l_id.Add(str_id);
	}
}

int  CObj__PSK_TEST
::Update__ADS_IN_INFO(const bool active_print)
{
	if(iActive__SIM_MODE > 0)
	{
		CString ads_name;
		int data_size;
		CString data_type;
		int i;

		mDB__ADS_CTRL.Clear__ADS_IN_ALL();

		// AO ...
		for(i=0; i<3; i++)
		{
			ads_name.Format("MAIN.AO_0_%1d", i);
			data_size = 2;
			data_type = "WORD";

			mDB__ADS_CTRL.Load__ADS_IN_INFO(ads_name, data_size,data_type);
		}
		// DO ...
		for(i=0; i<3; i++)
		{
			ads_name.Format("MAIN.DO_0_%02d", i);
			data_size = 1;
			data_type = "BOOL";

			mDB__ADS_CTRL.Load__ADS_IN_INFO(ads_name, data_size,data_type);
		}
	}
	else
	{
		mDRV__ADS_CTRL.Get__ADS_IN_INFO(false);
	}
	return 1;
}
int  CObj__PSK_TEST
::Update__ADS_OUT_INFO(const bool active_print)
{
	mCH__ADS_CTRL.Clear__ADS_CH();

	// ...
	{
		CStringArray l__var_name;
		CStringArray l__var_type;

		pOBJ_CTRL->Get__IO_OutVariable_Type_List(l__var_name, l__var_type);

		int k_limit = l__var_name.GetSize();

		for(int k=0; k<k_limit; k++)
		{
			CString var_name = l__var_name[k];
			CString var_type = l__var_type[k];

			CDS__IO_CHANNEL_INFO io_info;
			if(pOBJ_CTRL->Get__IO_OutVariable_Info(var_name, io_info) < 0)		continue;

			int md_id = io_info.iMD_NO;
			int ch_id = io_info.iCH_NO;

			int io_type = _CH_TYPE__VR;
			CString ads_name = io_info.sCOMMAND3;

				 if(var_type.CompareNoCase("D") == 0)		io_type = _CH_TYPE__DO;
			else if(var_type.CompareNoCase("A") == 0)		io_type = _CH_TYPE__AO;
			else if(var_type.CompareNoCase("S") == 0)		io_type = _CH_TYPE__SO;

			mCH__ADS_CTRL.Add__ADS_CH(io_type,var_name,ads_name, md_id,ch_id);
		}

		mDRV__ADS_CTRL.Link__ADS_OUT_INFO(active_print);
	}

	if(active_print)
	{
		CString log_msg;

		log_msg = "\n";
		log_msg += mCH__ADS_CTRL.Get__ADS_INFO();

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return 1;
}
int  CObj__PSK_TEST
::Update__IO_OUTPUT_CHANNEL()
{
	bActive__DRV_PRINT = true;

	// ...
	CStringArray l__var_name;
	CStringArray l__var_type;

	pOBJ_CTRL->Get__IO_OutVariable_Type_List(l__var_name, l__var_type);

	int k_limit = l__var_name.GetSize();
	int k;

	printf("==============================================\n");
	printf(" Update__IO_OUTPUT_CHANNEL() ... \n\n");
	printf(" ** IO_List <- [%1d] .... \n", k_limit);

	for(k=0; k<k_limit; k++)
	{
		CString var_name = l__var_name[k];
		CString var_type = l__var_type[k];

		printf(" * %1d) [%s] [%s] \n", k, var_name, var_type);

		CDS__IO_CHANNEL_INFO io_info;
		if(pOBJ_CTRL->Get__IO_OutVariable_Info(var_name, io_info) < 0)
		{
			continue;
		}

		int md_id = io_info.iMD_NO;
		int ch_id = io_info.iCH_NO;

		CString ads_type = io_info.sCOMMAND1;
		int cnt_byte = atoi(io_info.sCOMMAND2);

		printf("   -> [%1d] [%1d] [%s] [%1d] \n", md_id, ch_id, ads_type, cnt_byte);

		if(var_type.CompareNoCase("D") == 0)
		{
			bool r_data = false;

			if(iActive__SIM_MODE > 0)
			{

			}
			else
			{
				// if(mADS_CTRL.Get__IO_DO(md_id,ch_id, r_data) < 0)				continue;
			}

			int item_index = 0;
			if(r_data)		item_index = 1;

			pOBJ_CTRL->Set__Digital_Variable_With_Item_Index(var_name, item_index);

			printf("  OK : Set_DIGITAL (%1d) \n", item_index);
		}
		else if(var_type.CompareNoCase("A") == 0)
		{
			double r_data = 0.0;

			if(iActive__SIM_MODE > 0)
			{

			}
			else
			{
				// if(mADS_CTRL.Get__IO_AO(md_id,ch_id, ads_type, cnt_byte, r_data) < 0)		continue;
			}

			// ...
			double s_data = r_data;

			double delta_value = io_info.dMAX_VALUE - io_info.dMIN_VALUE;
			double delta_volt  = io_info.dMAX_VOLT  - io_info.dMIN_VOLT;

			if(delta_volt >= 1.0)
			{
				s_data = (delta_value / delta_volt) * (r_data - io_info.dMIN_VOLT) + io_info.dMIN_VALUE;
			}

			printf("   Value : [%.3f] [%1.3f] \n", io_info.dMIN_VALUE, io_info.dMAX_VALUE);
			printf("   Volt  : [%.3f] [%1.3f] \n", io_info.dMIN_VOLT,  io_info.dMAX_VOLT);
			printf("   r_data <- [%.3f] \n", r_data);
			printf("   s_data <- [%.3f] \n", s_data);

			CString ch_data;
			ch_data.Format("%.3f", s_data);

			pOBJ_CTRL->Set__VARIABLE_DATA(var_name, ch_data);
		}
		else if(var_type.CompareNoCase("S") == 0)
		{
			CString r_data;

			if(iActive__SIM_MODE > 0)
			{
				r_data.Format("%1d-%1d", md_id,ch_id);
			}
			else
			{
				// if(mADS_CTRL.Get__IO_SO(md_id,ch_id, ads_type, r_data) < 0)			continue;
			}

			// ...
			printf("   r_data <- [%s] \n", r_data);

			pOBJ_CTRL->Set__VARIABLE_DATA(var_name, r_data);
		}
	}

	printf("\n");
	printf("==============================================\n");
	printf("\n");

	bActive__DRV_PRINT = false;
	return 1;
}
