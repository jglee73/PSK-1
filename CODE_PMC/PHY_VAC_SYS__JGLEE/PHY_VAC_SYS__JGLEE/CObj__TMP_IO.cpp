#include "StdAfx.h"
#include "CObj__TMP_IO.h"
#include "CObj__TMP_IO__ALID.h"

#include "CCommon_Utility.h"


//-------------------------------------------------------------------------
CObj__TMP_IO::CObj__TMP_IO()
{

}
CObj__TMP_IO::~CObj__TMP_IO()
{

}

//-------------------------------------------------------------------------
int CObj__TMP_IO::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__FULL_CLOSE, "FULL_CLOSE");
		ADD__CTRL_VAR(sMODE__FULL_OPEN,  "FULL_OPEN");

		ADD__CTRL_VAR(sMODE__EXHAUST_CLOSE, "EXHAUST_CLOSE");
		ADD__CTRL_VAR(sMODE__EXHAUST_OPEN,  "EXHAUST_OPEN");

		ADD__CTRL_VAR(sMODE__ON,  "ON");
		ADD__CTRL_VAR(sMODE__OFF, "OFF");
		ADD__CTRL_VAR(sMODE__OFF_NO_WAIT, "OFF_NO_WAIT");	
	}
	return 1;
}
int CObj__TMP_IO::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define MON_ID__STATE_CHECK						1


int CObj__TMP_IO::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	// ...
	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);

		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS, str_name);

		str_name = "OBJ.TIMER";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_TIMER, str_name);
	}

	// MON.PART ...
	{
		str_name = "MON.PART.ERROR.ACTIVE";
		STD__ADD_DIGITAL(str_name, "OFF ON");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PART_ERROR_ACTIVE, str_name);
	}

	// MON ...
	{
		str_name = "MON.TMP.TYPE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_TMP_TYPE, str_name);

		//
		str_name = "MON.COMM.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMM_STATE, str_name);

		//
		str_name = "MON.PUMP.ON.SNS";
		STD__ADD_DIGITAL(str_name, "Off On");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_PUMP_ON_SNS, str_name);

		str_name = "MON.PUMP.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_PUMP_STATE, str_name);

		//
		str_name = "MON.ERROR.ON.SNS";
		STD__ADD_DIGITAL(str_name, "Off On");
		LINK__VAR_DIGITAL_CTRL(dCH__MON_ERROR_ON_SNS, str_name);

		str_name = "MON.ERROR.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_ERROR_STATE, str_name);

		//
		str_name = "MON.PUMP.RPM.VALUE";
		STD__ADD_ANALOG(str_name, "rpm", 1, 0.0, 50000.0);
		LINK__VAR_ANALOG_CTRL(aCH__MON_PUMP_RPM_VALUE, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.VAT_OPEN_DELAY.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_VAT_OPEN_DELAY_SEC, str_name);

		//
		str_name = "CFG.DI_FORELINE_ERR_CHECK.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DI_FORELINE_ERR_CHECK_SEC, str_name);

		str_name = "CFG.DI_PCW_ERR_CHECK.SEC";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 1, 0, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_DI_PCW_ERR_CHECK_SEC, str_name);

		//
		str_name = "CFG.TURBO.EXHAUST.VALVE.CLOSE.DELAY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 500, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TURBO_EXHAUST_VALVE_CLOSE_DELAY, str_name);

		str_name = "CFG.TURBO.N2.PURGE.CLOSE.DELAY";
		STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 10, "");
		LINK__VAR_ANALOG_CTRL(aCH__CFG_TURBO_N2_PURGE_CLOSE_DELAY, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__STATE_CHECK);
	}
	return 1;
}

int CObj__TMP_IO::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ", sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	iLIST_ALID__PART.RemoveAll();

	// ...
	{
		alarm_id = ALID__FORLINE_PRESSURE_UNSTABLE_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "Forline Pressure Unstable Alarm !";

		alarm_msg  = "Forline Pressure Unstable Status\n";
		alarm_msg += "Check the Forline Vac Switch and Dry Pump On Status!\n";
		alarm_msg += "Now... Turbo Pump will be off..";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PCW_UNSTABLE_ALARM;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "PCW Unstable Alarm !";

		alarm_msg  = "PCW Unstable Status \n";
		alarm_msg += "Check the state of PCW ! \n";
		alarm_msg += "Now, Turbo Pump will be off..";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_STATE_ERROR;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The state of TMP is error !";

		alarm_msg = "Check the state of TMP !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__TMP_ON_ERROR;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "TMP�� On �� �� �����ϴ� !";

		alarm_msg = "���� Sensor ���¸� Ȯ�� �ٶ��ϴ�. \n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__PUMP_ALARM_STATE;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The state of TMP is alarm !";

		alarm_msg = "Check the state of TMP !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__PUMP_WARNING_STATE;
		iLIST_ALID__PART.Add(alarm_id);

		alarm_title  = title;
		alarm_title += "The state of TMP is warning !";

		alarm_msg = "Check the state of TMP !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMP_IO::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{	
	// ...
	{
		CString file_name;
		CString log_msg;

		file_name.Format("%s.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xI_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xI_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

		xI_LOG_CTRL->DISABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG(log_msg);

		xI_LOG_CTRL->ENABLE__TIME_LOG();
		xI_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// ...
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	CCommon_Utility x_utility;
	bool def_check;

	// Init ...
	{
		bActive__TMP_DI_COMM_STATE = false;

		bActive__TMP_DO_START = false;
		bActive__TMP_DO_STOP  = false;
		bActive__TMP_DO_RESET = false;

		bActive__TMP_DI_NORMAL_SPEED  = false;
		bActive__TMP_DI_ACCELERATION  = false;
		bActive__TMP_DI_ALARM_STATE   = false;
		bActive__TMP_DI_WARNING_STATE = false;

		bActive__TMP_AI_ROT_RPM = false;

		//
		bActive__GV_USE  = false;
	    bActive__VAT_USE = false;

		bActive__DI_FORELINE_VAC_SNS  = false;
		bActive__DI_BACKING_PUMP_ON   = false;
		bActive__DO_TMP_EXHAUST_VALVE = false;
		bActive__DO_TMP_PURGE_VALVE   = false;
	}

	// DATA.TMP_TYPE ...
	{
		def_name = "DATA.TMP_TYPE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		sCH__MON_TMP_TYPE->Set__DATA(def_data);

			 if(def_data.CompareNoCase("IO")  == 0)		iDATA__TMP_TYPE = _TMP_TYPE__IO;
		else if(def_data.CompareNoCase("OBJ") == 0)		iDATA__TMP_TYPE = _TMP_TYPE__OBJ;
	}

	// TMP.IO INFO ...
	{
		// DI.COMM_STATE ...
		{
			def_name = "LINK_TMP.DI_COMM_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_COMM_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_COMM_STATE, obj_name,var_name);
			}
		}

		// DI.NORMAL_SPEED ...
		{
			def_name = "LINK_TMP.DI_NORMAL_SPEED";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_NORMAL_SPEED = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_NORMAL_SPEED, obj_name,var_name);
			}
		}
		// DI.ACCELERATION ...
		{
			def_name = "LINK_TMP.DI_ACCELERATION";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_ACCELERATION = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_ACCELERATION, obj_name,var_name);
			}
		}

		// DI.ALARM_STATE ...
		{
			def_name = "LINK_TMP.DI_ALARM_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_ALARM_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_ALARM_STATE, obj_name,var_name);
			}
		}
		// DI.WARNING_STATE ...
		{
			def_name = "LINK_TMP.DI_WARNING_STATE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DI_WARNING_STATE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DI_WARNING_STATE, obj_name,var_name);
			}
		}

		// AI.ROT_RPM ...
		{
			def_name = "LINK_TMP.AI_ROT_RPM";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_AI_ROT_RPM = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__TMP_AI_ROT_RPM, obj_name,var_name);
			}
		}
	}

	if(iDATA__TMP_TYPE == _TMP_TYPE__IO)
	{
		// DO.START ...
		{
			def_name = "LINK_TMP.DO_START";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DO_START = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DO_START, obj_name,var_name);
			}
		}
		// DO.STOP ...
		{
			def_name = "LINK_TMP.DO_STOP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DO_STOP = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DO_STOP, obj_name,var_name);
			}
		}
		// DO.RESET ...
		{
			def_name = "LINK_TMP.DO_RESET";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__TMP_DO_RESET = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__TMP_DO_RESET, obj_name,var_name);
			}
		}
	}
	else if(iDATA__TMP_TYPE == _TMP_TYPE__OBJ)
	{
		// OBJ.LINK ...
		{
			def_name = "OBJ__TMP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

			pOBJ_CTRL__TMP = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);
		}

		// OBJ.MODE ...
		{
			def_name = "TMP_MODE.START";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			sTMP_MODE__START = def_data;
		
			//
			def_name = "TMP_MODE.STOP";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		
			sTMP_MODE__STOP = def_data;

			//
			def_name = "TMP_MODE.STOP_NO_WAIT";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			sTMP_MODE__STOP_NO_WAIT = def_data;
		}
	}

	// GV.IO INFO ...
	{
		// USE ...
		{
			def_name = "DATA.GV_USE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

			def_check = x_utility.Check__Link(def_data);
			bActive__GV_USE = def_check;
		}

		if(bActive__GV_USE)
		{
			def_name = "LINK_GV.DO_OPEN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GV_DO_OPEN, obj_name,var_name);

			def_name = "LINK_GV.DO_CLOSE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GV_DO_CLOSE, obj_name,var_name);
			
			//
			def_name = "LINK_GV.DI_OPEN";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GV_DI_OPEN, obj_name,var_name);

			def_name = "LINK_GV.DI_CLOSE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__GV_DI_CLOSE, obj_name,var_name);
		}
	}

	// VAT.OBJ INFO ...
	{
		def_name = "OBJ__VAT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		def_check = x_utility.Check__Link(obj_name);
		bActive__VAT_USE = def_check;			

		if(def_check)
		{
			pOBJ_CTRL__VAT = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

			//
			var_name = "MON.POSITION";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__VAT_MON_POSITION, obj_name,var_name);
		}
	}

	// LINK.IO INFO ...
	{
		// DI.FORELINE_VAC_SNS ...
		{
			def_name = "LINK_IO.DI_FORELINE_VAC_SNS";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_FORELINE_VAC_SNS = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_FORELINE_VAC_SNS, obj_name,var_name);
			}
		}
		// DI.DRY_PUMP_ON ...
		{
			def_name = "LINK_IO.DI_BACKING_PUMP_ON";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);
		
			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_BACKING_PUMP_ON = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_BACKING_PUMP_ON, obj_name,var_name);
			}
		}

		// DI.PCW_ALARM ...
		{
			def_name = "LINK_IO.DI_PCW_ALARM";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_PCW_ALARM = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PCW_ALARM, obj_name,var_name);
			}
		}
		// DI.PCW_WATER_LEAK ...
		{
			def_name = "LINK_IO.DI_PCW_WATER_LEAK";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DI_PCW_WATER_LEAK = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DI_PCW_WATER_LEAK, obj_name,var_name);
			}
		}

		// DO.TMP_EXHAUST_VALVE ...
		{
			def_name = "LINK_IO.DO_TMP_EXHAUST_VALVE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DO_TMP_EXHAUST_VALVE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_TMP_EXHAUST_VALVE, obj_name,var_name);
			}
		}
		// DO.TMP_PURGE_VALVE ...
		{
			def_name = "LINK_IO.DO_TMP_PURGE_VALVE";
			p_ext_obj_create->Get__DEF_CONST_DATA(def_name, ch_name);

			def_check = x_utility.Check__Link(ch_name);
			bActive__DO_TMP_PURGE_VALVE = def_check;

			if(def_check)
			{
				p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(ch_name, obj_name,var_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__DO_TMP_PURGE_VALVE, obj_name,var_name);
			}
		}
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// ...
	{
		bActive__FORELINE_VLV_CHECK = true;

		sCH__OBJ_STATUS->Set__DATA("STANDBY");
	}
	return 1;
}

//-------------------------------------------------------------------------
int CObj__TMP_IO::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	DECLARE__EXT_CTRL(p_variable);

	int flag = -1;

	// ...
	{
		CString log_msg;
		log_msg.Format("Start [%s] ... By %s \n", mode, p_ext_mode_ctrl->Get__UPPER_OBJECT_NAME());

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	{
		     IF__CTRL_MODE(sMODE__INIT)				flag = Call__INIT(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__FULL_CLOSE)		flag = Call__FULL_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__FULL_OPEN)		flag = Call__FULL_OPEN(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_CLOSE)	flag = Call__EXHAUST_CLOSE(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__EXHAUST_OPEN)		flag = Call__EXHAUST_OPEN(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__ON)				flag = Call__ON(p_variable, p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__OFF)				flag = Call__OFF(p_variable, p_alarm, false);
		ELSE_IF__CTRL_MODE(sMODE__OFF_NO_WAIT)		flag = Call__OFF(p_variable, p_alarm, true);

		bActive__FORELINE_VLV_CHECK = true;
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;
		log_msg.Format("Aborted ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);		
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]",mode);

		sCH__OBJ_MSG->Set__DATA(log_msg);
		xI_LOG_CTRL->WRITE__LOG(log_msg);
	}

	return flag;
}

int CObj__TMP_IO::__CALL__MONITORING(id,p_variable,p_alarm)
{
	if(id == MON_ID__STATE_CHECK)			Mon__STATE_CHECK(p_variable, p_alarm);

	return 1;
}
