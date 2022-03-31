#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__DEF.h"


#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CDB__ADS_CTRL.h"
extern CDB__ADS_CTRL mDB__ADS_CTRL;

#include "CCH__ADS_CTRL.h"
extern CCH__ADS_CTRL mCH__ADS_CTRL;


//------------------------------------------------------------------------------------
int CObj__PSK_TEST
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	CString ads_name = io_info.sCOMMAND3;
	CString ads_data;

	int r_flag = mDB__ADS_CTRL.Get__ADS_IN_DATA(ads_name, ads_data);
	if(r_flag > 0)
	{
		read_data = atof(ads_data);

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

		err_msg.Format(" var_name <- %s", var_name);

		mERR_MSG.Load__Error_Info(alm_id, err_msg);
	}
	return r_flag;
}

int CObj__PSK_TEST
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	CString ads_name = io_info.sCOMMAND3;
	CString ads_data;

	int r_flag = mDB__ADS_CTRL.Get__ADS_IN_DATA(ads_name, ads_data);
	if(r_flag > 0)		
	{
		int r_bit = atoi(ads_data);
		
		if(r_bit > 0)		item_index = 1;
		else				item_index = 0;

	}
	else
	{
		int alm_id = ALID__PLC_DI_ERROR;
		CString err_msg;

		err_msg.Format(" var_name <- %s", var_name);

		mERR_MSG.Load__Error_Info(alm_id, err_msg);
	}
	return r_flag;
}

int CObj__PSK_TEST
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;
	CString ads_type = io_info.sCOMMAND1;

	int r_flag = mADS_CTRL.Get__IO_SI(md_id, ch_id, ads_type, read_data);
	if(r_flag > 0)
	{
		/*
		if(md_id == 11)
		{
				 if(ch_id == 5)			iDRV_COUNT__SI_Node11_Ch5++;
			else if(ch_id == 10)		iDRV_COUNT__SI_Node11_Ch10++;
		}
		*/
	}
	else
	{
		int alm_id = ALID__PLC_SI_ERROR;
		CString err_msg;

		err_msg.Format(" var_name <- %s", var_name);

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

	if(bActive__DRV_PRINT)
	{
		printf(" * __Write__ANALOGL() ... \n");
		printf("   var_name <- [%s] \n", var_name);
		printf("   md_id <- [%1d] \n", md_id);
		printf("   ch_id <- [%1d] \n", ch_id);
		printf("   set_data <- [%.3f] \n", set_data);
		printf("\n");
	}

	// ...
	CString ads_data;
	ads_data.Format("%f", set_data);

	return mCH__ADS_CTRL.Set__ADS_CH(_CH_TYPE__AO,var_name, md_id,ch_id, ads_data);
}

int CObj__PSK_TEST
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;

	if(bActive__DRV_PRINT)
	{
		printf(" * __Write__DIGITAL() ... \n");
		printf("   var_name <- [%s] \n", var_name);
		printf("   md_id <- [%1d] \n", md_id);
		printf("   ch_id <- [%1d] \n", ch_id);
		printf("   set_data <- [%s] [%1d] \n", set_data,item_index);
		printf("\n");
	}
	
	// ...
	CString ads_data;
	ads_data.Format("%1d", item_index);

	return mCH__ADS_CTRL.Set__ADS_CH(_CH_TYPE__DO,var_name, md_id,ch_id, ads_data);
}

int CObj__PSK_TEST
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{
	int md_id = io_info.iMD_NO;
	int ch_id = io_info.iCH_NO;
	CString ads_type = io_info.sCOMMAND1;

	if(bActive__DRV_PRINT)
	{
		printf(" * __Write__STRING() ... \n");
		printf("   var_name <- [%s] \n", var_name);
		printf("   md_id <- [%1d] \n", md_id);
		printf("   ch_id <- [%1d] \n", ch_id);
		printf("   ads_type <- [%s] \n", ads_type);
		printf("   set_data <- [%s] \n", set_data);
		printf("\n");
	}
	return mADS_CTRL.Set__IO_SO(md_id, ch_id, ads_type, set_data);
}
