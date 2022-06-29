#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__DEF.h"

#include "Macro_Function.h"


#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CCH__ADS_CTRL.h"
extern CCH__ADS_CTRL mCH__ADS_IN;
extern CCH__ADS_CTRL mCH__ADS_OUT;


//------------------------------------------------------------------------------------
int CObj__PSK_TEST
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	if(md_id < 1)
	{
		return -1;
	}

	CString ads_name;
	CString ads_data;

	int r_flag = -1;

	if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)
	{
		ads_name  = sPARA__ADS_NAME_INPUT;
		ads_name += io_info.sCOMMAND3;

		r_flag = mDB__ADS_CTRL.Get__ADS_IN_DATA(ads_name, ads_data);

		read_data = atof(ads_data);
	}
	else
	{
		int cmd_id = atof(io_info.sCOMMAND1);
		ads_name = io_info.sCOMMAND3;

		r_flag = mCH__ADS_IN.Get__LOCAL_AI_CH(ads_name, md_id,ch_id,cmd_id, read_data);
	}

	if(r_flag > 0)
	{
		if(io_info.sCOMMAND3.CompareNoCase("MAX.ZERO") == 0)
		{
			if(read_data > (io_info.dMAX_VOLT * 1.3))
				read_data = io_info.dMIN_VALUE;
		}
	}
	else
	{
		int alm_id = ALID__PLC_AI_ERROR;
		CString err_msg;
		CString err_bff;

		err_msg.Format(" var_name <- %s \n", var_name);
		err_bff.Format(" ads_name <- %s \n", ads_name);
		err_msg += err_bff;

		mERR_MSG.Load__Error_Info(alm_id, err_msg);
	}
	return r_flag;
}

int CObj__PSK_TEST
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	if(md_id < 1)
	{
		return -1;
	}

	CString ads_name;
	CString ads_data;

	int r_flag = -1;

	if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)
	{
		ads_name  = sPARA__ADS_NAME_INPUT;
		ads_name += io_info.sCOMMAND3;

		r_flag = mDB__ADS_CTRL.Get__ADS_IN_DATA(ads_name, ads_data);

		if(r_flag > 0)
		{
			int r_bit = atoi(ads_data);

			if(r_bit > 0)		item_index = 1;
			else				item_index = 0;
		}
	}
	else
	{
		int cmd_id = atof(io_info.sCOMMAND1);
		ads_name = io_info.sCOMMAND3;

		unsigned char r_byte_data;
		r_flag = mCH__ADS_IN.Get__LOCAL_DI_CH(ads_name, md_id,ch_id,cmd_id, item_index, r_byte_data);

		//
		CString cmmd_type = io_info.sCOMMAND2;

		if(cmmd_type.CompareNoCase("BOOL") == 0)
		{
			if(r_byte_data != 0)			item_index = 1;
			else							item_index = 0;
		}
		else if(cmmd_type.CompareNoCase("BYTE") == 0)
		{
			item_index = 0x0ff & r_byte_data;
		}
	}

	if(r_flag > 0)		
	{

	}
	else
	{
		int alm_id = ALID__PLC_DI_ERROR;
		CString err_msg;
		CString err_bff;

		err_msg.Format(" var_name <- %s \n", var_name);
		err_bff.Format(" ads_name <- %s \n", ads_name);
		err_msg += err_bff;

		mERR_MSG.Load__Error_Info(alm_id, err_msg);
	}
	return r_flag;
}

int CObj__PSK_TEST
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	CString ads_name;
	CString ads_hexa;

	if(md_id < 1)
	{
		return -1;
	}

	int r_flag = -1;

	if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)
	{
		ads_name  = sPARA__ADS_NAME_INPUT;
		ads_name += io_info.sCOMMAND3;

		r_flag = mDB__ADS_CTRL.Get__ADS_IN_HEXA(ads_name, ads_hexa);
		// r_flag = mDB__ADS_CTRL.Get__ADS_IN_DATA(ads_name, ads_hexa);
	}
	else
	{
		int cmd_id = atof(io_info.sCOMMAND1);
		ads_name = io_info.sCOMMAND3;

		r_flag = mCH__ADS_IN.Get__LOCAL_SI_CH(ads_name, md_id,ch_id,cmd_id, ads_hexa);		
	}

	if(r_flag > 0)
	{
		read_data = ads_hexa;
	}
	else
	{
		int alm_id = ALID__PLC_SI_ERROR;
		CString err_msg;
		CString err_bff;

		err_msg.Format(" var_name <- %s \n", var_name);
		err_bff.Format(" ads_name <- %s \n", ads_name);
		err_msg += err_bff;

		mERR_MSG.Load__Error_Info(alm_id, err_msg);
	}
	return r_flag;
}


//------------------------------------------------------------------------------------
int CObj__PSK_TEST
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	if(md_id < 1)
	{
		return 1;
	}

	int r_flag = -1;

	if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)
	{
		/*
		CString ads_data;
		ads_data.Format("%f", set_data);

		r_flag = mCH__ADS_CTRL.Set__ADS_CH(_CH_TYPE__AO,var_name, md_id,ch_id, ads_data);
		*/
		return 1;
	}
	else
	{
		int cmd_id = atof(io_info.sCOMMAND1);
		CString ads_name = io_info.sCOMMAND3;

		r_flag = mCH__ADS_OUT.Set__LOCAL_AO_CH(ads_name, md_id,ch_id,cmd_id, set_data);
	}

	if(r_flag < 0)
	{
		printf(" * __Write__ANALOGL() : r_flag(%1d) ... \n", r_flag);
		printf("   var_name <- [%s] \n", var_name);
		printf("   md_id <- [%1d] \n", md_id);
		printf("   ch_id <- [%1d] \n", ch_id);
		printf("   set_data <- [%.3f] \n", set_data);
		printf("\n");
	}
	return r_flag;
}

int CObj__PSK_TEST
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	if(md_id < 1)
	{
		return 1;
	}

	int r_flag = -1;

	if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)
	{
		/*
		CString ads_data;
		ads_data.Format("%1d", item_index);
		
		r_flag = mCH__ADS_CTRL.Set__ADS_CH(_CH_TYPE__DO,var_name, md_id,ch_id, ads_data);
		*/
		return 1;
	}
	else
	{
		int cmd_id = atof(io_info.sCOMMAND1);
		CString ads_name = io_info.sCOMMAND3;

		bool active__byte_ctrl = false;
		if(io_info.sCOMMAND2.CompareNoCase("BYTE") == 0)			active__byte_ctrl = true;

		r_flag = mCH__ADS_OUT.Set__LOCAL_DO_CH(ads_name, md_id,ch_id,cmd_id, item_index, active__byte_ctrl);
	}

	if(r_flag < 0)
	{
		printf(" * __Write__DIGITAL() : r_flag(%1d) ... \n", r_flag);
		printf("   var_name <- [%s] \n", var_name);
		printf("   md_id <- [%1d] \n", md_id);
		printf("   ch_id <- [%1d] \n", ch_id);
		printf("   set_data <- [%s] [%1d] \n", set_data,item_index);
		printf("\n");
	}
	return r_flag;
}

int CObj__PSK_TEST
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	/*
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg.Format("__Write__STRING() ... \n");
		log_bff.Format(" * var_name <- %s \n", var_name);
		log_msg += log_bff;
		log_bff.Format(" * md_id <- %1d \n", io_info.iMD_NO);
		log_msg += log_bff;
		log_bff.Format(" * ch_id <- %1d \n", io_info.iCH_NO);
		log_msg += log_bff;
		log_bff.Format(" * set_data <- [%s] \n", set_data);
		log_msg += log_bff;

		MessageBox(NULL, log_msg, "CHECK !!!", MB_OK);
	}
	*/

	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	if(md_id < 1)
	{
		return 1;
	}

	// ...
	int r_flag = -1;

	if(io_info.sCOMMAND2.CompareNoCase(_ADS) == 0)
	{
		// r_flag = mCH__ADS_CTRL.Set__ADS_CH(_CH_TYPE__SO,var_name, md_id,ch_id, set_data);
		return 1;
	}
	else
	{
		CStringArray l_data;
		Macro__StringArrray_From_String(set_data, " ", l_data);

		int i_len = l_data.GetSize();
		if(i_len > 100)		i_len = 100;

		int acc_data = 0;
		int cur_data = 0;

		for(int i=i_len-1; i>=0; i--)
		{
			acc_data <<= 8;
			cur_data = 0x0ff & Macro__Hexa_From_String(l_data[i]);
			acc_data += cur_data;
		}			

		// ...
		int cmd_id = atof(io_info.sCOMMAND1);
		CString ads_name = io_info.sCOMMAND3;

		r_flag = mCH__ADS_OUT.Set__LOCAL_SO_CH(ads_name, md_id,ch_id,cmd_id, acc_data);		
	}

	if(r_flag < 0)
	{
		printf(" * __Write__STRING() : r_flag(%1d) ... \n", r_flag);
		printf("   var_name <- [%s] \n", var_name);
		printf("   md_id <- [%1d] \n", md_id);
		printf("   ch_id <- [%1d] \n", ch_id);
		printf("   set_data <- [%s] \n", set_data);
		printf("\n");
	}
	return r_flag;
}
