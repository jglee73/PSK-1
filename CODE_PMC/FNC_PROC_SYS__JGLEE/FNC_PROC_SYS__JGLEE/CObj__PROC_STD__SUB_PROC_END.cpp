#include "StdAfx.h"
#include "Ccommon_Def.h"

#include "CObj__PROC_STD.h"


// ...
int CObj__PROC_STD
::Sub__PROC_END(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString log_msg;

	// ...
	{
		log_msg = "Process End - Start ...";
		sCH__OBJ_MSG->Set__DATA(log_msg);
	}

	// Step.End ...
	{
		pOBJ_CTRL__STEP->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__STEP->Call__OBJECT(_STEP_CMD__END);

		pOBJ_CTRL__STEP->Link__UPPER_OBJECT();
	}

	// Chamber.Pumping ...
	{
		pOBJ_CTRL__CHM->Dislink__UPPER_OBJECT();

		pOBJ_CTRL__CHM->Call__OBJECT(_CHM_CMD__HIGH_VAC_PUMP);

		pOBJ_CTRL__CHM->Link__UPPER_OBJECT();
	}

	Save__LEARNED_MOCE();
	return 1;
}

int CObj__PROC_STD::Save__LEARNED_MOCE()
{
	CString ch_data;

	if(dCH__CFG_LEARNED_APPLY_MODE->Check__DATA(STR__ENABLE) < 0)
	{
		return -11;
	}

	if(sCH__RCP_FILE_UPLOAD_FLAG->Check__DATA(STR__YES) > 0)
	{
		return -12;
	}

	if(sCH__CUR_LEARNED_RESULT->Check__DATA(STR__OK) < 0)
	{
		ch_data = "Learned Result is not OK ...";
		sCH__CUR_LEARNED_APPLY_STATUS->Set__DATA(ch_data);
		return -13;
	}
	else
	{
		ch_data = "Leaned Mode Applied ...";
		sCH__CUR_LEARNED_APPLY_STATUS->Set__DATA(ch_data);
	}

	// ...
	{
		sEXT_CH__SLOT01_LOTID->Get__DATA(ch_data);
		sCH__PRE_LOTID->Set__DATA(ch_data);
	}

	// ...
	{
		SCX__FILE_RCP_CTRL x_file_ctrl;
		int change_flag = -1;

		CString file_path;
		sCH__CUR_RCP_FILE_PATH->Get__DATA(file_path);

		//
		CDS__LEARNED_STEP_DATA ds_data;
		int i = 0;

		while(mCTRL__LEARNED_ITEM.Get__STEP_DATA(i, &ds_data) > 0)
		{
			i++;
			
			if(change_flag < 0)
			{
				change_flag = 1;

				x_file_ctrl->Partial__INIT_FILE(file_path);
			}

			// ...
			int step_id = ds_data.iSTEP_ID;

			if(x_file_ctrl->Partial__STEP_JUMP(step_id) > 0)
			{
				CString ch_name = ds_data.sSTR__RCP_NAME;
				CString ch_data = ds_data.sSTR__IO_RESULT;
				CString ch_type = "A";

				x_file_ctrl->Partial__ADD_ITEM(ch_name,ch_type,ch_data);
			}
		}

		if(change_flag > 0)
		{
			x_file_ctrl->Partial__SAVE_FILE(file_path);
		}
	}

	sCH__CUR_LEARNED_RESULT->Set__DATA("");
	mCTRL__LEARNED_ITEM.Init__STEP_ITEM();
	return 1;
}

