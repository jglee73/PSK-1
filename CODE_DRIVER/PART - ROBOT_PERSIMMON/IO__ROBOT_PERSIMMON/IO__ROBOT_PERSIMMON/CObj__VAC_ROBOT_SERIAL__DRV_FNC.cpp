#include "StdAfx.h"
#include "CObj__VAC_ROBOT_SERIAL.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int CObj__VAC_ROBOT_SERIAL
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__VAC_ROBOT_SERIAL
::__Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index)
{
	CString str__recv_data;
	CString str__cmmd;
	int flag;

	if(diCH__COMM_STS->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(m_nCommState == OFFLINE)		read_data = STR__OFFLINE;
		else							read_data = STR__ONLINE;

		return 1;
	}
	
	return -1;
}

int CObj__VAC_ROBOT_SERIAL
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str__cmmd;
	CString str__para;
	CString r_data;

	CString ch_data;
	int r_flag;


	if((siCH__RB_STATE_AUTO->Check__VARIABLE_NAME(var_name)   > 0)
	|| (siCH__RB_STATE_MANUAL->Check__VARIABLE_NAME(var_name) > 0))
	{
		str__cmmd = "RQ";
		str__para = "BG";

		r_flag = Drv__SEND_COMMAND(var_name, str__cmmd,str__para, r_data);
		if(r_flag < 0)
		{
			read_data = STR__ERROR;
			return -11;
		}

		Update__ROBOT_STATE(r_data);

		read_data = STR__OK;
		return 1;
	}
	
	if(siCH__VERSION_MANUAL->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd = "RQ";
		str__para = "Version";

		r_flag = Drv__SEND_COMMAND(var_name, str__cmmd,str__para, r_data);
		if(r_flag < 0)
		{
			read_data = STR__ERROR;
			return -11;
		}

		Update__VERSION(r_data);

		read_data = STR__OK;
		return 1;
	}
	if(siCH__RQ_COMM_MANUAL->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd = "RQ";
		str__para = "COMM ALL";

		r_flag = Drv__SEND_COMMAND(var_name, str__cmmd,str__para, r_data);
		if(r_flag < 0)
		{
			read_data = STR__ERROR;
			return -11;
		}

		Update__RQ_COMM_INFO(r_data);

		read_data = STR__OK;
		return 1;
	}

	if(siCH__WAF_CEN_DATA_MANUAL->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd = "RQ";
		str__para = "WAF_CEN DATA";

		r_flag = Drv__SEND_COMMAND(var_name, str__cmmd,str__para, r_data);
		if(r_flag < 0)
		{
			read_data = STR__ERROR;
			return -11;
		}

		Update__WAF_CEN_DATA(r_data);

		read_data = STR__OK;
		return 1;
	}
	if(siCH__RQ_POS_STN_MANUAL->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd = "RQ";
		str__para = "POS STN";

		r_flag = Drv__SEND_COMMAND(var_name, str__cmmd,str__para, r_data);
		if(r_flag < 0)
		{
			read_data = STR__ERROR;
			return -11;
		}

		Update__RQ_POS_STN_DATA(r_data);

		read_data = STR__OK;
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__VAC_ROBOT_SERIAL
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	
	return -1;
}

int CObj__VAC_ROBOT_SERIAL
::__Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index)
{
	// ...
	{
		CString log_msg;
		CString log_bff;

		log_msg = "__Write__DIGITAL() ... \n";

		log_bff.Format(" *** var_name : %s \n", var_name);
		log_msg += log_bff;

		log_bff.Format(" *** set_data : %s \n", set_data);
		log_msg += log_bff;

		Fnc__DRV_LOG(log_msg);
	}

	// ...
	CString str__cmmd;
	CString str__para;

	CString r_data;

	
	if(doCH__RB_COMMAND->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString str_pos;
		CString str_slot;
		CString str_arm;

		str_arm = dCH__PARA_RB_ARM_TYPE->Get__STRING();
		str_pos.Format("%1d",  (int) aCH__PARA_RB_POS_CODE->Get__VALUE() );
		str_slot.Format("%1d", (int) aCH__PARA_RB_SLOT_CODE->Get__VALUE());

		//
		if(set_data.CompareNoCase(_RB_MODE__HOME) == 0)
		{
			str__cmmd = "Home";
			str__para = "ALL";
		}
		else if(set_data.CompareNoCase(_RB_MODE__GOTO_GET) == 0)
		{
			str__cmmd = "Goto";
			str__para.Format("N %s R RE Z DN SLOT 1 ARM %s", str_pos, str_arm);
		}
		else if(set_data.CompareNoCase(_RB_MODE__GOTO_PUT) == 0)
		{
			str__cmmd = "Goto";
			str__para.Format("N %s R RE Z UP SLOT 1 ARM %s", str_pos, str_arm);
		}
		else if(set_data.CompareNoCase(_RB_MODE__PICK) == 0)
		{
			str__cmmd = "Pick";
			str__para.Format("%s SLOT %s ARM %s ENRT NR", str_pos, str_slot, str_arm);
		}
		else if(set_data.CompareNoCase(_RB_MODE__PICK_APS) == 0)
		{
			str__cmmd = "Pick";
			str__para.Format("%s SLOT %s ARM %s ENRT NR APS", str_pos, str_slot, str_arm);
		}
		else if(set_data.CompareNoCase(_RB_MODE__PLACE) == 0)
		{
			str__cmmd = "Place";
			str__para.Format("%s SLOT %s ARM %s ENRT NR", str_pos, str_slot, str_arm);
		}
		else if(set_data.CompareNoCase(_RB_MODE__EXTEND) == 0)
		{
			str__cmmd = "Goto";
			str__para.Format("N %s R EX Z DN SLOT 1 ARM %s", str_pos, str_arm);	
		}
		else if(set_data.CompareNoCase(_RB_MODE__EXTEND_OFFSET) == 0)
		{
			CString str_ro = "0000";
			CString str_to = "0000";
			
			if(str_arm.CompareNoCase(ARM_A) == 0)
			{
				str_ro = sCH__MON_WFR_CEN_RO__ARM_A->Get__STRING();
				str_to = sCH__MON_WFR_CEN_TO__ARM_A->Get__STRING();
			}
			else if(str_arm.CompareNoCase(ARM_B) == 0)
			{
				str_ro = sCH__MON_WFR_CEN_RO__ARM_B->Get__STRING();
				str_to = sCH__MON_WFR_CEN_TO__ARM_B->Get__STRING();
			}

			str__cmmd = "Goto";
			str__para.Format("N %s R EX Z DN SLOT 1 ARM %s RO %s TO %s", str_pos, str_arm, str_ro, str_to);
		}
		else if(set_data.CompareNoCase(_RB_MODE__RETRACT) == 0)
		{
			str__cmmd = "Goto";
			str__para.Format("N %s R RE Z DN SLOT 1 ARM %s", str_pos, str_arm);	
		}
		else if(set_data.CompareNoCase(_RB_MODE__LOAD_OFF) == 0)
		{
			str__cmmd = "SET LOAD";
			str__para.Format("ARM %s OFF", str_arm);	
		}
		else if(set_data.CompareNoCase(_RB_MODE__LOAD_ON) == 0)
		{
			str__cmmd = "SET LOAD";
			str__para.Format("ARM %s ON", str_arm);	
		}
		else if(set_data.CompareNoCase(_RB_MODE__SET_COMM) == 0)
		{
			CString para__mode;
			CString para__flow;
			CString para__lf;
			CString para__echo;
			CString para__checksum;
			CString para__drep;
			CString para__baud;

			para__mode.Format("M/B %s",  dCH__CFG_COMM_MODE->Get__STRING());
			para__flow.Format("FLOW %s", dCH__CFG_COMM_FLOW->Get__STRING());
			para__lf.Format("LF %s",     dCH__CFG_COMM_LF->Get__STRING());
			para__echo.Format("ECHO %s", dCH__CFG_COMM_ECHO->Get__STRING());
			para__checksum.Format("CHECKSUM %s", dCH__CFG_COMM_CHECKSUM->Get__STRING());
			para__drep.Format("DREP %s", dCH__CFG_COMM_DREP->Get__STRING());
			para__baud.Format("BAUD %s", dCH__CFG_COMM_BAUD->Get__STRING());

			str__cmmd = "SET COMM";

			str__para  = para__mode;
			str__para += " ";
			str__para += para__flow;
			str__para += " ";
			str__para += para__lf;
			str__para += " ";
			str__para += para__echo;
			str__para += " ";
			str__para += para__checksum;
			str__para += " ";
			str__para += para__drep;
			str__para += " ";
			str__para += para__baud;
		}
		else
		{
			return -101;
		}

		return Drv__SEND_COMMAND(var_name, str__cmmd,str__para, r_data);
	}

	return -1;
}

int CObj__VAC_ROBOT_SERIAL
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
