#include "StdAfx.h"
#include "CObj__PSK_TEST.h"
#include "CObj__PSK_TEST__ALID.h"
#include "CObj__PSK_TEST__DEF.h"


#include "CCls__ADS_CTRL.h"
extern CCls__ADS_CTRL mADS_CTRL;

#include "CMNG__ADS_CTRL.h"
extern CMNG__ADS_CTRL mMNG__ADS_CTRL; 


//--------------------------------------------------------------------------------
CObj__PSK_TEST::CObj__PSK_TEST()
{

}
CObj__PSK_TEST::~CObj__PSK_TEST()
{

}

//--------------------------------------------------------------------------------
int CObj__PSK_TEST::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");

		ADD__CTRL_VAR(sMODE__ADS_GET_INFO,       "ADS.GET_INFO");
		ADD__CTRL_VAR(sMODE__ADS_BLOCK_LINK,     "ADS.BLOCK_LINK");
		ADD__CTRL_VAR(sMODE__ADS_UPDATE_READING, "ADS.UPDATE_READING");
		ADD__CTRL_VAR(sMODE__ADS_UPDATE_SETTING, "ADS.UPDATE_SETTING");
	}

	return 1;
}
int CObj__PSK_TEST::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__MONITOR				1
#define  MON_ID__ADS_CHECK				2

#define  APP_DSP__MON_MODE				"IDLE  RUN"
#define  APP_DSP__DISABLE_ENABLE		"DISABLE  ENABLE"
#define  APP_DSP__OFF_ON				"OFF    ON"
#define  APP_DSP__CLOSE_OPEN			"CLOSE  OPEN"


int CObj__PSK_TEST::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	// ...
	CString str_name;
	int i;

	// OBJ ...
	{
		str_name = "OBJ.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_MSG, str_name);
	}

	// INFO ...
	{
		str_name = "INFO.PLC.NETID.STR";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLC_NETID_STR, str_name);

		for(i=0; i<_CFG__NETID_SIZE; i++)
		{
			str_name.Format("INFO.PLC.NETID.%1d", i+1);
			STD__ADD_STRING(str_name);
			LINK__VAR_STRING_CTRL(sCH__INFO_PLC_NETID_X[i], str_name);
		}

		//
		str_name = "INFO.PLC.PORT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLC_PORT, str_name);

		str_name = "INFO.PLC.ADS_NAME_OUTPUT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLC_ADS_NAME_OUTPUT, str_name);

		str_name = "INFO.PLC.ADS_NAME_INPUT";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_PLC_ADS_NAME_INPUT, str_name);

		//
		str_name = "INFO.IO_FILE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_IO_FILE, str_name);
	}

	// INFO_DRV ...
	{
		str_name = "INFO_DRV.DEV_NAME";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV__DEV_NAME, str_name);

		str_name = "INFO_DRV.VERSION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV__VERSION, str_name);

		str_name = "INFO_DRV.REVISION";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV__REVISION, str_name);

		str_name = "INFO_DRV.BUILD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INFO_DRV__BUILD, str_name);
	}

	// CFG ...
	{
		str_name = "CFG.IO_TEST_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__DISABLE_ENABLE, "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_IO_TEST_MODE, str_name);
	}

	/*
	// ADS ...
	{
		str_name = "di.ADS.ACTIVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);
		LINK__VAR_DIGITAL_CTRL(diCH__ADS_ACTIVE, str_name);

		str_name = "do.ADS.ACTIVE";
		STD__ADD_DIGITAL(str_name, APP_DSP__OFF_ON);
		LINK__VAR_DIGITAL_CTRL(doCH__ADS_ACTIVE, str_name);
	}
	*/

	// ...
	{
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__MONITOR);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__ADS_CHECK);
	}
	return 1;
}


// ...
#define  ACT__CLEAR								\
l_act.RemoveAll();								\
l_act.Add(STR__CLEAR);


int CObj__PSK_TEST::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CStringArray l_act;
	int alarm_id;

	CString str_bff;


	// PLC Offline ...
	{
		alarm_id = ALID__PLC_OFFLINE;

		alarm_title  = title;
		alarm_title += "PLC Offlne !";

		alarm_msg = "Please, check the state of PLC !";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// PLC AI Error ...
	{
		alarm_id = ALID__PLC_AI_ERROR;

		alarm_title  = title;
		alarm_title += "PLC AI Error !";

		alarm_msg = "Please, check the state of PLC !";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// PLC DI Error ...
	{
		alarm_id = ALID__PLC_DI_ERROR;

		alarm_title  = title;
		alarm_title += "PLC DI Error !";

		alarm_msg = "Please, check the state of PLC !";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// PLC SI Error ...
	{
		alarm_id = ALID__PLC_SI_ERROR;

		alarm_title  = title;
		alarm_title += "PLC SI Error !";

		alarm_msg = "Please, check the state of PLC !";

		ACT__CLEAR;

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


int CObj__PSK_TEST::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__PSK_TEST::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	CString def_name;
	CString def_data;
	CString ch_name;
	CString obj_name;
	CString var_name;

	// ...
	{
		CString file_name;
		CString log_msg;

		// APP Log ...
		{
			file_name.Format("%s__APP.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__APP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__APP_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__APP_LOG_CTRL->DISABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

			xI__APP_LOG_CTRL->ENABLE__TIME_LOG();
			xI__APP_LOG_CTRL->WRITE__LOG("   START   \n");
		}

		// DRV Log ...
		{
			file_name.Format("%s__DRV.log", sObject_Name);

			log_msg  = "\n\n";
			log_msg += "//------------------------------------------------------------------------";

			xI__DRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
			xI__DRV_LOG_CTRL->SET__PROPERTY(file_name,12*1,60);

			xI__DRV_LOG_CTRL->DISABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG(log_msg);

			xI__DRV_LOG_CTRL->ENABLE__TIME_LOG();
			xI__DRV_LOG_CTRL->WRITE__LOG("   START   \n");
		}
	}

	pOBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(sObject_Name);

	// ...
	{
		iFLAG__DRV_FLAG = -1;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	// PLC NETID ...
	{
		def_name = "PLC.NETID";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		sCH__INFO_PLC_NETID_STR->Set__DATA(def_data);

		//
		CStringArray l_id;
		Get__PLC_NETID(def_data, l_id);

		int k_limit = l_id.GetSize();
		for(int k=0; k<k_limit; k++)
		{		
			if(k < _CFG__NETID_SIZE)		sCH__INFO_PLC_NETID_X[k]->Set__DATA(l_id[k]);
		}

		mADS_CTRL.Set__NETID(l_id);
	}

	// ADS_INFO ...
	{
		def_name = "ADS.PORT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		
		iPARA__ADS_PORT = atoi(def_data);
		sCH__INFO_PLC_PORT->Set__DATA(def_data);

		//
		def_name = "ADS.NAME_OUTPUT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		sPARA__ADS_NAME_OUTPUT = def_data;
		sCH__INFO_PLC_ADS_NAME_OUTPUT->Set__DATA(def_data);

		//
		def_name = "ADS.NAME_INPUT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		sPARA__ADS_NAME_INPUT = def_data;
		sCH__INFO_PLC_ADS_NAME_INPUT->Set__DATA(def_data);
	}

	if(iActive__SIM_MODE > 0)
	{
		return -1;
	}

	// ADS Driver Init ...
	{	
		Init__ADS_DRIVER();
	}
	
	// ADS In & Out Channel List ...
	{
		Update__ADS_ALL_INFO();

		Update__ADS_IN_INFO(true);
		Update__ADS_OUT_INFO(true);
	}

	// ADS In & Out Block Link ...
	{
		mMNG__ADS_CTRL.Init__ADS_LINK(iActive__SIM_MODE);

		//
		CString log_msg;

		log_msg = mMNG__ADS_CTRL.Get__ADS_IN_INFO();
		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);

		log_msg = mMNG__ADS_CTRL.Get__ADS_OUT_INFO();
		xI__APP_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// Out-Channel ...
	{
		Update__ADS_OUTPUT_CHANNEL();
		Update__IO_OUTPUT_CHANNEL();
	}
	return 1;
}
int CObj__PSK_TEST::__INITIALIZE__IO(p_io_para)
{
	CString io_file = p_io_para->Get__IO_FILE();
	sCH__INFO_IO_FILE->Set__DATA(io_file);

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__PSK_TEST::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	CString msg;
	int flag = -1;

	// ...
	{
		msg.Format("%s Started...",mode);
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)						flag = Call__INIT(p_variable,p_alarm);
	    ELSE_IF__CTRL_MODE(sMODE__ADS_GET_INFO)				flag = Call__ADS_GET_INFO(p_variable,p_alarm);		
		ELSE_IF__CTRL_MODE(sMODE__ADS_BLOCK_LINK)			flag = Call__ADS_BLOCK_LINK(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ADS_UPDATE_READING)		flag = Call__ADS_UPDATE_READING(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__ADS_UPDATE_SETTING)		flag = Call__ADS_UPDATE_SETTING(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		msg.Format("%s Aborted (%1d)", mode, flag);
	}
	else
	{
		msg.Format("%s Completed (%1d)", mode, flag);
	}	

	// ...
	{
		sCH__OBJ_MSG->Set__DATA(msg);

		xI__APP_LOG_CTRL->WRITE__LOG(msg);
	}
	return flag;
}

int CObj__PSK_TEST::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__MONITOR:	
			Mon__MONITOR(p_variable, p_alarm);
			break;

		case MON_ID__ADS_CHECK:	
			Mon__ADS_CHECK(p_variable, p_alarm);
			break;
	}

	return 1;
}

int CObj__PSK_TEST::__Close__OBJECT()
{
	mADS_CTRL.Close__ADS_ADDR();
	return 1;
}
