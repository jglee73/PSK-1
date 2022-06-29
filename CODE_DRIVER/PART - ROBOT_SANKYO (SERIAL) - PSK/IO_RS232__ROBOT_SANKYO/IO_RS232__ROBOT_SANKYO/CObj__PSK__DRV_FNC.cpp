#include "StdAfx.h"
#include "CObj__PSK.h"
#include "CObj__PSK__DEF.h"

#include "CCommon_DEF.h"


//------------------------------------------------------------------------------------
int CObj__PSK
::__Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data)
{

	return -1;
}

int CObj__PSK
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

int CObj__PSK
::__Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data)
{
	CString str__cmmd;
	CString str__para;
	CString recv_data;

	CString ch_data;
	int r_flag;

	// CString para__data = "**********";
	CString para__data = "0000000000";


	if((siCH__RB_STATE_AUTO->Check__VARIABLE_NAME(var_name)   > 0)
	|| (siCH__RB_STATE_MANUAL->Check__VARIABLE_NAME(var_name) > 0))
	{
		str__cmmd = "0801";
		str__para = para__data;

		r_flag = Drv__RECV_COMMAND(var_name, str__cmmd,str__para, recv_data);

		// ...
		{
			CString log_msg;
			CString log_bff;

			log_msg.Format("Data (%1d) <- [%s] \n", r_flag, recv_data);
			Fnc__DRV_LOG(log_msg);
		}

		if(r_flag < 0)
		{
			read_data = "ERROR";
			return -11;
		}

		Update__ROBOT_STATE(recv_data);

		read_data = "OK";
		return 1;
	}
	
	if(siCH__VERSION->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd = "0802";
		str__para = para__data;

		r_flag = Drv__RECV_COMMAND(var_name, str__cmmd,str__para, recv_data);
		if(r_flag < 0)
		{
			read_data = "ERROR";
			return -11;
		}

		Update__VERSION(recv_data);

		read_data = "OK";
		return 1;
	}

	if(siCH__AL_MEASUREMENT->Check__VARIABLE_NAME(var_name) > 0)
	{
		str__cmmd = "0803";
		str__para = para__data;

		r_flag = Drv__RECV_COMMAND(var_name, str__cmmd,str__para, recv_data);
		if(r_flag < 0)
		{
			read_data = "ERROR";
			return -11;
		}

		Update__AL_MEASUREMENT(recv_data);

		read_data = "OK";
		return 1;
	}

	return -1;
}


//------------------------------------------------------------------------------------
int CObj__PSK
::__Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data)
{
	
	return -1;
}

int CObj__PSK
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
	CString str__recv_data;
	CString str_data;

	CString str__cmmd;
	CString str__para;

	CString ch_data;
    int flag;

	
	// INIT  PICK  PLACE  CHUCK.ON  CHUCK.OFF  GOTO.GET  GOTO.PUT  ERROR.RESET
	if(doCH__RB_COMMAND->Check__VARIABLE_NAME(var_name) > 0)
	{
		CString str_pos;
		CString str_slot;
		CString str_arm;

		str_pos.Format("%02d",  (int) aCH__PARA_RB_POS_CODE->Get__VALUE() );
		str_slot.Format("%02d", (int) aCH__PARA_RB_SLOT_CODE->Get__VALUE());

		ch_data = dCH__PARA_RB_ARM_TYPE->Get__STRING();
			 if(ch_data.CompareNoCase("A")  == 0)			str_arm = "01";
		else if(ch_data.CompareNoCase("B")  == 0)			str_arm = "10";
		else if(ch_data.CompareNoCase("AB") == 0)			str_arm = "11";

		//
		if(set_data.CompareNoCase("INIT") == 0)
		{
			str__cmmd = "01";
			str__para = "************";
		}
		else if(set_data.CompareNoCase("PICK") == 0)
		{
			str__cmmd = "0204";
			str__para.Format("01%s%s%s00", str_pos,str_slot,str_arm);
		}
		else if(set_data.CompareNoCase("PLACE") == 0)
		{
			str__cmmd = "0205";
			str__para.Format("01%s%s%s00", str_pos,str_slot,str_arm);
		}
		else if(set_data.CompareNoCase("CHUCK.ON") == 0)
		{
			str__cmmd = "0206";
			str__para.Format("******%s**", str_arm);
		}
		else if(set_data.CompareNoCase("CHUCK.OFF") == 0)
		{
			str__cmmd = "0207";
			str__para.Format("******%s**", str_arm);
		}
		else if(set_data.CompareNoCase("GOTO.GET") == 0)
		{
			str__cmmd = "0202";
			str__para.Format("01%s%s%s00", str_pos,str_slot,str_arm);
		}
		else if(set_data.CompareNoCase("GOTO.PUT") == 0)
		{
			str__cmmd = "0203";
			str__para.Format("01%s%s%s00", str_pos,str_slot,str_arm);
		}
		else if(set_data.CompareNoCase("ERROR.RESET") == 0)
		{
			str__cmmd = "09";
			str__para = "************";
		}
		else
		{
			return -101;
		}

		return Drv__SEND_COMMAND(var_name, str__cmmd,str__para);
	}

	// INIT  MEASURE.START  CHUCK.ON  CHUCK.OFF  ROT.RELATIVE  ROT.ABSOLUTE  CAL
	if(doCH__AL_COMMAND->Check__VARIABLE_NAME(var_name) > 0)
	{
		if(set_data.CompareNoCase("INIT") == 0)
		{
			str__cmmd = "1306";
			str__para = "vvvvv00000";
		}
		else if(set_data.CompareNoCase("MEASURE.START") == 0)
		{
			int para__notch_angle = (int) (aCH__PARA_AL_NOTCH_ANGLE->Get__VALUE() * 100.0);			
			str_data.Format("%05d", para__notch_angle);

			str__cmmd = "1301";
			str__para.Format("%s00000", str_data);			
		}
		else if(set_data.CompareNoCase("CHUCK.ON") == 0)
		{
			str__cmmd = "1302";			
			str__para = "vvvvv00000";			
		}
		else if(set_data.CompareNoCase("CHUCK.OFF") == 0)
		{
			str__cmmd = "1303";						
			str__para = "vvvvv00000";						
		}
		else if(set_data.CompareNoCase("ROT.RELATIVE") == 0)
		{
			int para__relativve_angle = (int) (aCH__PARA_AL_RELATIVE_ANGLE->Get__VALUE() * 100.0);
			str_data.Format("%05d", para__relativve_angle);

			str__cmmd = "1304";
			str__para.Format("%s00000", str_data);						
		}
		else if(set_data.CompareNoCase("ROT.ABSOLUTE") == 0)
		{
			int para__absolute_angle = (int) (aCH__PARA_AL_ABSOLUTE_ANGLE->Get__VALUE() * 100.0);
			str_data.Format("%05d", para__absolute_angle);

			str__cmmd = "1305";
			str__para.Format("%s00000", str_data);									
		}
		else if(set_data.CompareNoCase("CAL") == 0)
		{
			int para__notch_angle = (int) (aCH__PARA_AL_NOTCH_ANGLE->Get__VALUE() * 100.0);
			str_data.Format("%05d", para__notch_angle);

			str__cmmd = "1307";
			str__para.Format("%s00000", str_data);			
		}
		else
		{
			return -101;
		}

		return Drv__SEND_COMMAND(var_name, str__cmmd,str__para);
	}

	return -1;
}

int CObj__PSK
::__Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data)
{

	return -1;
}
