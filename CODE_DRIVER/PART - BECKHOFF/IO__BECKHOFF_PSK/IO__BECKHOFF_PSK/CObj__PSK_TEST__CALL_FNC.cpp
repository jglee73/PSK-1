#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__ALID.h"
#include "CObj__PSK_TEST__DEF.h"


#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CCH__ADS_CTRL.h"
extern CCH__ADS_CTRL mCH__ADS_IN;
extern CCH__ADS_CTRL mCH__ADS_OUT;

#include "CMNG__ADS_CTRL.h"
extern CMNG__ADS_CTRL mMNG__ADS_CTRL; 


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
::Init__ADS_DRIVER()
{
	CString ch_data;

	mADS_CTRL.Init__ADS_DRIVER(iPARA__ADS_PORT);

	// ...
	{
		CCls__DEV_INFO dev_info;
		mADS_CTRL.Get__DEV_IINFO(dev_info);

		ch_data = dev_info.sDEV_NAME;
		sCH__INFO_DRV__DEV_NAME->Set__DATA(ch_data);

		ch_data.Format("%1d", dev_info.iVERSION);
		sCH__INFO_DRV__VERSION->Set__DATA(ch_data);

		ch_data.Format("%1d", dev_info.iREVISION);
		sCH__INFO_DRV__REVISION->Set__DATA(ch_data);

		ch_data.Format("%1d", dev_info.iBUILD);
		sCH__INFO_DRV__BUILD->Set__DATA(ch_data);
	}
	return 1;
}
int  CObj__PSK_TEST
::Update__ADS_ALL_INFO()
{
	if(iActive__SIM_MODE > 0)
	{

	}
	else
	{
		CString log_msg = "ALL ADS Info ... \n";
		log_msg += mMNG__ADS_CTRL.Get__ADS_TOTAL_INFO(true);

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}
int  CObj__PSK_TEST
::Update__ADS_IN_INFO(const bool active_print)
{
	mCH__ADS_IN.Clear__ADS_CH();

	// ...
	{
		CStringArray l__var_name;
		CStringArray l__var_type;

		pOBJ_CTRL->Get__IO_InVariable_Type_List(l__var_name, l__var_type);

		int k_limit = l__var_name.GetSize();

		for(int k=0; k<k_limit; k++)
		{
			CString var_name = l__var_name[k];
			CString var_type = l__var_type[k];

			CDS__IO_CHANNEL_INFO io_info;
			if(pOBJ_CTRL->Get__IO_InVariable_Info(var_name, io_info) < 0)		continue;

			if(io_info.sCOMMAND2.CompareNoCase(_ADS) != 0)						continue;

			// ...
			int md_id = io_info.iMD_NO;
			int ch_id = io_info.iCH_NO;

			int io_type = _CH_TYPE__VR;
				
			CString ads_header = sPARA__ADS_NAME_INPUT;
			CString ads_name   = io_info.sCOMMAND3;

				 if(var_type.CompareNoCase("D") == 0)		io_type = _CH_TYPE__DI;
			else if(var_type.CompareNoCase("A") == 0)		io_type = _CH_TYPE__AI;
			else if(var_type.CompareNoCase("S") == 0)		io_type = _CH_TYPE__SI;
			else											continue;

			mCH__ADS_IN.Add__ADS_CH(io_type,var_name, ads_header,ads_name, md_id,ch_id);
		}

		mMNG__ADS_CTRL.Link__ADS_IN_INFO(active_print);
	}

	if(active_print)
	{
		CString log_msg;

		log_msg = "\n";
		log_msg += mCH__ADS_IN.Get__ADS_INFO();

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}
int  CObj__PSK_TEST
::Update__ADS_OUT_INFO(const bool active_print)
{
	mCH__ADS_OUT.Clear__ADS_CH();

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

			if(io_info.sCOMMAND2.CompareNoCase(_ADS) != 0)						continue;

			// ...
			int md_id = io_info.iMD_NO;
			int ch_id = io_info.iCH_NO;

			int io_type = _CH_TYPE__VR;

			CString ads_header = sPARA__ADS_NAME_OUTPUT;
			CString ads_name   = io_info.sCOMMAND3;

				 if(var_type.CompareNoCase("D") == 0)		io_type = _CH_TYPE__DO;
			else if(var_type.CompareNoCase("A") == 0)		io_type = _CH_TYPE__AO;
			else if(var_type.CompareNoCase("S") == 0)		io_type = _CH_TYPE__SO;
			else											continue;

			mCH__ADS_OUT.Add__ADS_CH(io_type,var_name, ads_header,ads_name, md_id,ch_id);
		}

		mMNG__ADS_CTRL.Link__ADS_OUT_INFO(active_print);
	}

	if(active_print)
	{
		CString log_msg;

		log_msg = "\n";
		log_msg += mCH__ADS_OUT.Get__ADS_INFO();

		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}
	return 1;
}

int  CObj__PSK_TEST
::Update__ADS_OUTPUT_CHANNEL()
{
	bActive__DRV_PRINT = true;

	/*
	// ACTIVE ...
	{
		CString var_name;
		CString ads_name;

		// diACTIVE ...
		{
			var_name = _IO_NAME__diACTIVE;

			ads_name  = sPARA__LINK_NAME;
			ads_name += var_name;
	
			mADS_CTRL.Link__ADS_VR_INFO(var_name,ads_name);
		}
		// doACTIVE ...
		{
			var_name = _IO_NAME__doACTIVE;

			ads_name  = sPARA__LINK_NAME;
			ads_name += var_name;

			mADS_CTRL.Link__ADS_VR_INFO(var_name,ads_name);
		}
	}
	*/

	// ...
	CStringArray l__io_name;
	CStringArray l__io_type;

	// ADS Out.Channel Loading ...
	{
		CStringArray l__var_name;
		CStringArray l__var_type;

		pOBJ_CTRL->Get__IO_OutVariable_Type_List(l__var_name, l__var_type);

		//
		int k_limit = l__var_name.GetSize();

		for(int k=0; k<k_limit; k++)
		{
			CString var_name = l__var_name[k];
			CString var_type = l__var_type[k];

			CDS__IO_CHANNEL_INFO io_info;
			if(pOBJ_CTRL->Get__IO_OutVariable_Info(var_name, io_info) < 0)		continue;

			if(io_info.sCOMMAND2.CompareNoCase(_ADS) != 0)						continue;

			// ...
			int md_id = io_info.iMD_NO;
			int ch_id = io_info.iCH_NO;

			CString ads_name = sPARA__ADS_NAME_OUTPUT;
			ads_name += io_info.sCOMMAND3;

			if(var_type.CompareNoCase("D") == 0)
			{
				mADS_CTRL.Link__ADS_DO_INFO(var_name, ads_name, md_id,ch_id);
			}
			else if(var_type.CompareNoCase("A") == 0)
			{
				mADS_CTRL.Link__ADS_AO_INFO(var_name, ads_name, md_id,ch_id);
			}
			else if(var_type.CompareNoCase("S") == 0)
			{
				mADS_CTRL.Link__ADS_SO_INFO(var_name, ads_name, md_id,ch_id);
			}
			else
			{
				continue;
			}

			// ...
			{
				l__io_name.Add(var_name);
				l__io_type.Add(var_type);
			}
		}
	}

	// Channel & ADS Link ...
	{
		mADS_CTRL.Init__ADS_ADDR();
	}

	// ADS Out.Channel Update ...
	{
		int k_limit = l__io_name.GetSize();

		for(int k=0; k<k_limit; k++)
		{
			CString var_name = l__io_name[k];
			CString var_type = l__io_type[k];

			CDS__IO_CHANNEL_INFO io_info;
			if(pOBJ_CTRL->Get__IO_OutVariable_Info(var_name, io_info) < 0)
			{
				continue;
			}

			// ...
			int md_id = io_info.iMD_NO;
			int ch_id = io_info.iCH_NO;

			CString ads_type = io_info.sCOMMAND1;
			int cnt_byte = atoi(io_info.sCOMMAND2);

			if(var_type.CompareNoCase("D") == 0)
			{
				bool r_data = false;

				if(iActive__SIM_MODE > 0)
				{

				}
				else
				{
					if(mADS_CTRL.Get__IO_DO(var_name, md_id,ch_id, r_data) < 0)
					{
						continue;
					}

					CString ads_data;
					ads_data.Format("%1d", r_data);

					mCH__ADS_OUT.Set__ADS_CH(_CH_TYPE__DO,var_name, md_id,ch_id, ads_data);
				}

				int item_index = 0;
				if(r_data)		item_index = 1;

				pOBJ_CTRL->Set__Digital_Variable_With_Item_Index(var_name, item_index);
			}
			else if(var_type.CompareNoCase("A") == 0)
			{
				double r_data = 0.0;

				if(iActive__SIM_MODE > 0)
				{

				}
				else
				{
					if(mADS_CTRL.Get__IO_AO(var_name, md_id,ch_id, ads_type, cnt_byte, r_data) < 0)
					{
						continue;
					}

					CString ads_data;
					ads_data.Format("%f", r_data);

					mCH__ADS_OUT.Set__ADS_CH(_CH_TYPE__AO,var_name, md_id,ch_id, ads_data);
				}

				// ...
				double s_data = r_data;

				double delta_value = io_info.dMAX_VALUE - io_info.dMIN_VALUE;
				double delta_volt  = io_info.dMAX_VOLT  - io_info.dMIN_VOLT;

				if(delta_volt >= 1.0)
				{
					s_data = (delta_value / delta_volt) * (r_data - io_info.dMIN_VOLT) + io_info.dMIN_VALUE;
				}

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
					if(mADS_CTRL.Get__IO_SO(var_name, md_id,ch_id, ads_type, r_data) < 0)
					{
						continue;
					}


					mCH__ADS_OUT.Set__ADS_CH(_CH_TYPE__SO,var_name, md_id,ch_id, r_data);
				}

				pOBJ_CTRL->Set__VARIABLE_DATA(var_name, r_data);
			}
		}
	}

	bActive__DRV_PRINT = false;
	return 1;
}
int  CObj__PSK_TEST
::Update__IO_OUTPUT_CHANNEL()
{
	CStringArray l__var_name;
	CStringArray l__var_type;

	pOBJ_CTRL->Get__IO_OutVariable_Type_List(l__var_name, l__var_type);

	//
	int k_limit = l__var_name.GetSize();

	for(int k=0; k<k_limit; k++)
	{
		CString var_name = l__var_name[k];
		CString var_type = l__var_type[k];

		CDS__IO_CHANNEL_INFO io_info;
		if(pOBJ_CTRL->Get__IO_OutVariable_Info(var_name, io_info) < 0)		continue;

		if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)						continue;

		// ...
		int md_id = io_info.iMD_NO;
		int ch_id = io_info.iCH_NO;

		CString ads_name = io_info.sCOMMAND3;

		if(var_type.CompareNoCase("D") == 0)
		{
			int item_index = 0;
			int r_flag = mCH__ADS_OUT.Get__LOCAL_DO_CH(ads_name, md_id,ch_id, item_index);

			pOBJ_CTRL->Set__Digital_Variable_With_Item_Index(var_name, item_index);
		}
		else if(var_type.CompareNoCase("A") == 0)
		{
			CString str_data;
			int r_flag = mCH__ADS_OUT.Get__LOCAL_AO_CH(ads_name, md_id,ch_id, str_data);

			//
			double r_data = atof(str_data);
			double s_data = r_data;

			double delta_value = io_info.dMAX_VALUE - io_info.dMIN_VALUE;
			double delta_volt  = io_info.dMAX_VOLT  - io_info.dMIN_VOLT;

			if(delta_volt >= 1.0)
			{
				s_data = (delta_value / delta_volt) * (r_data - io_info.dMIN_VOLT) + io_info.dMIN_VALUE;
			}

			CString ch_data;
			ch_data.Format("%.3f", s_data);

			pOBJ_CTRL->Set__VARIABLE_DATA(var_name, ch_data);
		}
		else if(var_type.CompareNoCase("S") == 0)
		{
			CString str_hexa;
			mCH__ADS_OUT.Get__LOCAL_SO_CH(ads_name, md_id,ch_id, str_hexa);

			pOBJ_CTRL->Set__VARIABLE_DATA(var_name, str_hexa);
		}
	}

	return 1;
}
