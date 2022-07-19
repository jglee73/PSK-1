#include "stdafx.h"
#include "CObj__VERITY_STD.h"


// ...
int CObj__VERITY_STD
::Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{

	return 1;
}

// ...
int CObj__VERITY_STD
::Call__COMM_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int s_flag = doCH__Control_SET->Set__DATA(STR__Comm_Test);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__INFO_DRV_CONTROL_STS->Get__CHANNEL_NAME(),
						sCH__INFO_DRV_CONTROL_STS->Get__STRING());
		log_msg += log_bff;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}

// ...
int CObj__VERITY_STD
::Call__CFG_LIST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int s_flag = doCH__CFG_LIST_REQ->Set__DATA(STR__ON);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__INFO_DRV_CFG_LIST_STS->Get__CHANNEL_NAME(),
						sCH__INFO_DRV_CFG_LIST_STS->Get__STRING());
		log_msg += log_bff;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}
int CObj__VERITY_STD
::Call__CFG_VALIDATE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int s_flag = doCH__Control_SET->Set__DATA(STR__Cfg_Validate);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__INFO_DRV_CONTROL_STS->Get__CHANNEL_NAME(),
						sCH__INFO_DRV_CONTROL_STS->Get__STRING());
		log_msg += log_bff;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}

// ...
int CObj__VERITY_STD
::Call__WAFER_INFO(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg  = "\n";
		log_msg += "Wafer Info ...  \n";

		// 1. LotID
		{
			log_bff.Format(" * %s <- %s \n", 
				sCH__PARA_WAFER_LOTID->Get__VARIABLE_NAME(),
				sCH__PARA_WAFER_LOTID->Get__STRING());
			log_msg += log_bff;
		}
		// 2. LotID
		{
			log_bff.Format(" * %s <- %s \n", 
				sCH__PARA_WAFER_SLOTID->Get__VARIABLE_NAME(),
				sCH__PARA_WAFER_SLOTID->Get__STRING());
			log_msg += log_bff;
		}
		// 3. Cassette
		{
			log_bff.Format(" * %s <- %s \n", 
				sCH__PARA_WAFER_CSTID->Get__VARIABLE_NAME(),
				sCH__PARA_WAFER_CSTID->Get__STRING());
			log_msg += log_bff;
		}
		// 4. Wafer
		{
			log_bff.Format(" * %s <- %s \n", 
				sCH__PARA_WAFER_ID->Get__VARIABLE_NAME(),
				sCH__PARA_WAFER_ID->Get__STRING());
			log_msg += log_bff;
		}
		// 5. Recipe
		{
			log_bff.Format(" * %s <- %s \n", 
				sCH__PARA_WAFER_RECIPE->Get__VARIABLE_NAME(),
				sCH__PARA_WAFER_RECIPE->Get__STRING());
			log_msg += log_bff;
		}
		// 6. Step
		{
			log_bff.Format(" * %s <- %s \n", 
				sCH__PARA_WAFER_STEP->Get__VARIABLE_NAME(),
				sCH__PARA_WAFER_STEP->Get__STRING());
			log_msg += log_bff;
		}

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}

	int s_flag = doCH__WAFER_INFO_SET->Set__DATA(STR__ON);

	// ...
	{
		CString log_msg;
		CString log_bff;

		// Resu;t ...
		{	
			log_msg  = "\n";
			log_msg += "Send Result ... \n";

			log_bff.Format(" * %s <- %s \n", 
							sCH__INFO_DRV_WAFER_INFO_STS->Get__CHANNEL_NAME(),
							sCH__INFO_DRV_WAFER_INFO_STS->Get__STRING());
			log_msg += log_bff;
		}

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}

// ...
int CObj__VERITY_STD
::Call__STEP_START(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int s_flag = doCH__Control_SET->Set__DATA(STR__Start);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__INFO_DRV_CONTROL_STS->Get__CHANNEL_NAME(),
						sCH__INFO_DRV_CONTROL_STS->Get__STRING());
		log_msg += log_bff;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}
int CObj__VERITY_STD
::Call__STEP_STOP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int s_flag = doCH__Control_SET->Set__DATA(STR__Stop);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__INFO_DRV_CONTROL_STS->Get__CHANNEL_NAME(),
						sCH__INFO_DRV_CONTROL_STS->Get__STRING());
		log_msg += log_bff;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}

int CObj__VERITY_STD
::Call__COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	int s_flag = doCH__Control_SET->Set__DATA(STR__Complete);

	// ...
	{
		CString log_msg;
		CString log_bff;

		log_bff.Format(" * %s <- %s \n", 
						sCH__INFO_DRV_CONTROL_STS->Get__CHANNEL_NAME(),
						sCH__INFO_DRV_CONTROL_STS->Get__STRING());
		log_msg += log_bff;

		mX__Log_Ctrl->WRITE__LOG(log_msg);
	}
	return s_flag;
}

// ...
int CObj__VERITY_STD
::Call__GET_NET_BUFFER(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	dCH__PARA_ACTIVE_NET_BUFFER_CHECK->Set__DATA(STR__ON);

	dCH__PARA_ACTIVE_NET_BUFFER_CHECK->When__DATA(STR__OFF);
	return 1;
}
