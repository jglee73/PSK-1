#pragma once

#include "Interface_Code.h"
#include "VTYRemoteMessages.h"

#include "CObj__VERITY_STD__DEF.h"


class CCheck__Msg_Info
{
public:
	short int iCMD_ID;
	unsigned short int iSS_INFO;

	bool bActive__RECV_CMD;
};

class CCheck__Msg_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__MSG_INFO;

	// ...
	int _Wait__COMMAND_ID(const short int cmd_id, unsigned short int& ss_info)
	{
		int i_limit = pList__MSG_INFO.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCheck__Msg_Info* p_info = (CCheck__Msg_Info*) pList__MSG_INFO[i];

			if(cmd_id != p_info->iCMD_ID)		continue;
			if(!p_info->bActive__RECV_CMD)		continue;

			ss_info = p_info->iSS_INFO;

			// ...
			{
				pList__MSG_INFO.RemoveAt(i);
				delete p_info;
			}
			return 1;
		}
		return -1;
	}

public:
	CCheck__Msg_Ctrl()
	{
		InitializeCriticalSection(&mCS_LOCK);

	}
	~CCheck__Msg_Ctrl()
	{
		
		DeleteCriticalSection(&mCS_LOCK);
	}

	// ...
	void Load__COMMAND_ID(const short int cmd_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		CCheck__Msg_Info* p_info = new CCheck__Msg_Info;
		pList__MSG_INFO.Add(p_info);

		p_info->iCMD_ID = cmd_id;
		p_info->iSS_INFO = 0xff;
		p_info->bActive__RECV_CMD = false;

		if(pList__MSG_INFO.GetSize() > 10)
		{
			p_info = (CCheck__Msg_Info*) pList__MSG_INFO[0];
			delete p_info;

			pList__MSG_INFO.RemoveAt(0);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	void Recv__COMMAND_ID(const short int cmd_id, unsigned short int ss_info)
	{
		EnterCriticalSection(&mCS_LOCK);

		int i_limit = pList__MSG_INFO.GetSize();

		for(int i=0; i<i_limit; i++)
		{
			CCheck__Msg_Info* p_info = (CCheck__Msg_Info*) pList__MSG_INFO[i];

			if(cmd_id != p_info->iCMD_ID)		continue;
			
			p_info->iSS_INFO = ss_info;
			p_info->bActive__RECV_CMD = true;
			break;;
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	
	int Wait__COMMAND_ID(const short int cmd_id, unsigned short int& ss_info)
	{
		// double cfg_sec = 1.0; 
		double cfg_sec = 5.0; 
		int r_flag = -1;
		
		SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
		x_timer_ctrl->START__COUNT_UP(9999.0);

		while(r_flag < 0)
		{
			if(x_timer_ctrl->Get__CURRENT_TIME() > cfg_sec)
			{
				return -1;
			}

			EnterCriticalSection(&mCS_LOCK);

			r_flag = _Wait__COMMAND_ID(cmd_id, ss_info);

			LeaveCriticalSection(&mCS_LOCK);
		}
		return 1;
	}
};


class CObj__VERITY_STD : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL  mX__Log_Ctrl;

	int iActive__SIM_MODE;

	SCX__ETHERNET_JGLEE mX__Net_Client;
	CCheck__Msg_Ctrl mCheck__Msg_Ctrl;

	bool bActive__COMM_ONLINE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STATE;

	CX__VAR_DIGITAL_CTRL dCH__MON_ACTIVE_NOTREADY;
	CX__VAR_DIGITAL_CTRL dCH__MON_ACTIVE_READY;
	CX__VAR_DIGITAL_CTRL dCH__MON_ACTIVE_ENDPOINT;

	CX__VAR_STRING_CTRL  sCH__MON_WAVE_INTENSITY_VALUE;

	// PARA ...
	CX__VAR_STRING_CTRL  sCH__PARA_CONNECT_INFO;

	CX__VAR_STRING_CTRL  sCH__PARA_CFG_VALIDATE_INFO;
	CX__VAR_STRING_CTRL  sCH__PARA_STEP_START_CFG_NAME;

	CX__VAR_STRING_CTRL  sCH__PARA_WAFER_LOTID;
	CX__VAR_STRING_CTRL  sCH__PARA_WAFER_SLOTID;
	CX__VAR_STRING_CTRL  sCH__PARA_WAFER_CSTID;
	CX__VAR_STRING_CTRL  sCH__PARA_WAFER_ID;
	CX__VAR_STRING_CTRL  sCH__PARA_WAFER_RECIPE;
	CX__VAR_STRING_CTRL  sCH__PARA_WAFER_STEP;

	CX__VAR_DIGITAL_CTRL dCH__PARA_ACTIVE_NET_BUFFER_CHECK;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_VERSION;

	CX__VAR_STRING_CTRL  sCH__INFO_CFG_LIST_STR;
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_NAME_X[_SIZE__CFG_LIST];
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_DATE_X[_SIZE__CFG_LIST];
	CX__VAR_STRING_CTRL  sCH__INFO_CFG_SIZE_X[_SIZE__CFG_LIST];

	// INFO.DRV ...
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_CONTROL_STS;

	CX__VAR_STRING_CTRL  sCH__INFO_DRV_VERSION_STS;
	CX__VAR_STRING_CTRL  sCH__INFO_DRV_CFG_LIST_STS;

	CX__VAR_STRING_CTRL  sCH__INFO_DRV_WAFER_INFO_STS;
	//

	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__COMM_TEST;
	int Call__COMM_TEST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__CFG_LIST;
	int Call__CFG_LIST(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__CFG_VALIDATE;
	int Call__CFG_VALIDATE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__WAFER_INFO;
	int Call__WAFER_INFO(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__STEP_START;
	int Call__STEP_START(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__STEP_STOP;
	int Call__STEP_STOP(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__COMPLETE;
	int Call__COMPLETE(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	//
	CString sMODE__GET_NET_BUUFER;
	int Call__GET_NET_BUFFER(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

	// ...
	void Mon__IO_MONITORING(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	void Mon__DRV_PROC(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	int  SEND__COMMAND(const CString& var_name,const CString& set_data, const int cmd_id, const char *p_send,const int s_len, unsigned short int& ss_info);
	//

	// ...
	CX__VAR_DIGITAL_CTRL doCH__Control_SET;

	CX__VAR_DIGITAL_CTRL doCH__VERSION_REQ;
	CX__VAR_DIGITAL_CTRL doCH__CFG_LIST_REQ;

	CX__VAR_DIGITAL_CTRL doCH__WAFER_INFO_SET;
	//

public:
	CObj__VERITY_STD();
	~CObj__VERITY_STD();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);

};
