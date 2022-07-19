#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_DEF.h"

#include "CDriver__LPx_ETHERNET__DEF.h"


class CObj__Driver_INFO
{
public:
	CObj__Driver_INFO()
	{
		bState_Run = TRUE;

		sFNC_CMMD = "";
		sPARA_ID  = "";

		sPARA_RSP  = "";
		sPARA_DATA = "";
	}

	// ...
	bool bState_Run;

	CString sFNC_CMMD;
	CString sPARA_ID;

	CString sPARA_RSP;
	CString sPARA_DATA;
};
class CObj__Driver_MSG
{
private:
	CRITICAL_SECTION mCS_LOCK;

	CPtrArray pList__MSG_INFO;

public:
	CObj__Driver_MSG()
	{
		InitializeCriticalSection(&mCS_LOCK);
	}
	~CObj__Driver_MSG()
	{
		DeleteCriticalSection(&mCS_LOCK);
	}

	void Load__MSG_INFO(const CString& fnc_cmmd, const CString& para_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		CObj__Driver_INFO *p_info = new CObj__Driver_INFO;
		pList__MSG_INFO.Add(p_info);

		// ...
		{
			p_info->sFNC_CMMD = fnc_cmmd;
			p_info->sPARA_ID  = para_id;
		}

		if(pList__MSG_INFO.GetSize() > 30)
		{
			p_info = (CObj__Driver_INFO*) pList__MSG_INFO[0];
			delete p_info;

			pList__MSG_INFO.RemoveAt(0);
		}

		LeaveCriticalSection(&mCS_LOCK);
	}
	int  Set__MSG_INFO_OF_RSP(const CString& key_word, 
		                      const CString& para_id, 
							  const CString& para_rsp, 
							  const CString& para_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		CObj__Driver_INFO *p_info;
		int r_flag = -1;

		int i_limit = pList__MSG_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_info = (CObj__Driver_INFO*) pList__MSG_INFO[i];

			if(p_info->sFNC_CMMD.CompareNoCase(key_word) != 0)		continue;
			if(p_info->sPARA_ID.CompareNoCase(para_id)   != 0)		continue;

			p_info->sPARA_RSP  = para_rsp;	
			p_info->sPARA_DATA = para_data;

			p_info->bState_Run = FALSE;

			r_flag = 1;
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return r_flag;
	}
	int  Get__MSG_INFO_END(const int db_index, 
						   CString& fnc_cmmd,
						   CString& para_id,
						   CString& para_rsp,
						   CString& para_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		CObj__Driver_INFO *p_info;
		int r_flag = -1;

		int i_limit = pList__MSG_INFO.GetSize();
		int i;

		for(i=db_index; i<i_limit; i++)
		{
			p_info = (CObj__Driver_INFO*) pList__MSG_INFO[i];
			if(p_info->bState_Run)				continue; 

			fnc_cmmd = p_info->sFNC_CMMD;
			para_id  = p_info->sPARA_ID;

			para_rsp  = p_info->sPARA_RSP;
			para_data = p_info->sPARA_DATA;

			r_flag = i;
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return r_flag;
	}
	bool Check__MSG_DB(const CString& fnc_cmmd,
					   const CString& para_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		bool active_db = false;

		int i_limit = pList__MSG_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			CObj__Driver_INFO *p_info = (CObj__Driver_INFO*) pList__MSG_INFO[i];

			if(p_info->sFNC_CMMD.CompareNoCase(fnc_cmmd) != 0)		continue;
			if(p_info->sPARA_ID.CompareNoCase(para_id)   != 0)		continue;

			active_db = true;
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return active_db;
	}
	int  Check__MSG_INFO(const CString& fnc_cmmd,
						 const CString& para_id, 
						 CString& para_rsp,
						 CString& para_data)
	{
		EnterCriticalSection(&mCS_LOCK);

		CObj__Driver_INFO *p_info;
		int r_flag = -1;

		int i_limit = pList__MSG_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_info = (CObj__Driver_INFO*) pList__MSG_INFO[i];

			if(p_info->sFNC_CMMD.CompareNoCase(fnc_cmmd) != 0)		continue;
			if(p_info->sPARA_ID.CompareNoCase(para_id)   != 0)		continue;

			if(p_info->bState_Run)		break;

			para_rsp  = p_info->sPARA_RSP;
			para_data = p_info->sPARA_DATA;

			pList__MSG_INFO.RemoveAt(i);
			delete p_info;

			r_flag = 1;
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
		return r_flag;
	}
	void Delete__MSG_INFO(const CString& fnc_cmmd, const CString& para_id)
	{
		EnterCriticalSection(&mCS_LOCK);

		CObj__Driver_INFO *p_info;

		int i_limit = pList__MSG_INFO.GetSize();
		int i;

		for(i=0; i<i_limit; i++)
		{
			p_info = (CObj__Driver_INFO*) pList__MSG_INFO[i];

			if(p_info->sFNC_CMMD.CompareNoCase(fnc_cmmd) != 0)		continue;
			if(p_info->sPARA_ID.CompareNoCase(para_id)   != 0)		continue;

			pList__MSG_INFO.RemoveAt(i);
			delete p_info;
			break;
		}

		LeaveCriticalSection(&mCS_LOCK);
	}

	int  Wait__MSG_INFO(const CString& fnc_cmmd, 
						const CString& para_id,
						const double to_sec,
						CString& para_rsp,
						CString& para_data)
	{
		int r_flag = _Wait__MSG_INFO(fnc_cmmd,para_id, to_sec, para_rsp,para_data);

		Delete__MSG_INFO(fnc_cmmd,para_id);
		return r_flag;
	}
	int  _Wait__MSG_INFO(const CString& fnc_cmmd, 
						 const CString& para_id,
						 const double to_sec,
						 CString& para_rsp,
						 CString& para_data)
	{
		int ref_tick = GetTickCount();

		while(1)
		{
			Sleep(10);

			int r_flag = Check__MSG_INFO(fnc_cmmd,para_id, para_rsp,para_data);
			if(r_flag > 0)			return  1;

			// ...
			int dif_tick = GetTickCount() - ref_tick;
			if(dif_tick < 0)
			{
				ref_tick = GetTickCount();
				continue;
			}

			double cur_sec = dif_tick / 1000.0;
			if(cur_sec >= to_sec)
			{
				return -11;
			}
		}
		return -1;
	}
};


class CDriver__LPx_ETHERNET : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;

	// ..
	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;
	
	int iActive__SIM_MODE;

	// ...
	bool bActive__COMM_ONLINE;

	CObj__Driver_MSG mDrv_Msg;

	SCX__ETHERNET_JGLEE mX_Net;
	CString sEnd_InStr;
	CString sEnd_OutStr;

	int	 m_Rcv_Time;
	int	 m_Out_Time;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// DRV ...
	CX__VAR_STRING_CTRL  sCH__DRV_CANCEL_CODE;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;

	// PARA ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_LAMP_RED;
	CX__VAR_DIGITAL_CTRL dCH__PARA_LAMP_YELLOW;
	CX__VAR_DIGITAL_CTRL dCH__PARA_LAMP_GREEN;
	CX__VAR_DIGITAL_CTRL dCH__PARA_LAMP_BLUE;
	CX__VAR_DIGITAL_CTRL dCH__PARA_ALARM_BUZZER;

	CX__VAR_ANALOG_CTRL  aCH__PARA_RFID_PAGE_ID_X[CFG_LPx__SIZE];

	// PARA.N2_PURGE ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_LP_N2_NOZZLE_1__VALVE_X[CFG_LPx__SIZE];
	CX__VAR_ANALOG_CTRL  aCH__PARA_LP_N2_NOZZLE_1__MFC_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL dCH__PARA_LP_N2_NOZZLE_2__VALVE_X[CFG_LPx__SIZE];
	CX__VAR_ANALOG_CTRL  aCH__PARA_LP_N2_NOZZLE_2__MFC_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL dCH__PARA_LP_N2_NOZZLE_3__VALVE_X[CFG_LPx__SIZE];
	CX__VAR_ANALOG_CTRL  aCH__PARA_LP_N2_NOZZLE_3__MFC_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL dCH__PARA_LP_N2_EHHAUST_NOZZLE_X[CFG_LPx__SIZE];
	CX__VAR_ANALOG_CTRL  aCH__PARA_LP_N2_DELAY_TIME_X[CFG_LPx__SIZE];

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_MODE;
	
	CX__VAR_DIGITAL_CTRL dCH__CFG_LP_MODE_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_LP_RFID_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_LP_USE_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL dCH__CFG_LP_CLOSE_MAPPING_X[CFG_LPx__SIZE];

	// PIO_TP CFG ...
	CX__VAR_ANALOG_CTRL  aCH__PIO_CFG__TP_X[CFG_PIO__TP_SIZE];

	// PIO_TP INFO ...
	CX__VAR_STRING_CTRL  sCH__PIO_INFO__TP_X[CFG_PIO__TP_SIZE];

	// LPx INFO ...
	CX__VAR_STRING_CTRL  sCH__LP_INFO__ALM_TXT_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__ALM_MSG_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__RFID_RSP_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__RFID_ERROR_CODE_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__INITIAL_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__STATUS_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__FOUP_EXIST_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__DOOR_STATUS_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__CLAMP_STATUS_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__RFID_STATUS_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__AGV_STATUS_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__ENABLE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__RFID_ENABLE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__CLOSE_MAPPING_ENABLE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__ONLINE_MODE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__LOAD_BUTTON_STATUS_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__UNLOAD_BUTTON_STATUS_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT_HIGH_WORD_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_7__CONT_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_6__COMPTT_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_5__BUSY_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_4__TR_REQ_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT_LOW_WORD_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_3__NC_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_2__CS_1_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_1__CS_0_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_INPUT__BIT_0__VALID_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT_HIGH_WORD_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_7__ES_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_6__HO_AVBL_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_5__NC_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_4__NC_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT_LOW_WORD_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_3__READY_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_2__NC_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_1__U_REQ_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__LP_INFO__PIO_OUTPUT__BIT_0__L_REQ_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  sCH__LP_INFO__FOUP_TYPE_X[CFG_LPx__SIZE];

	// MAP RESULT ...
	CX__VAR_DIGITAL_CTRL dCH__LPx_MAP__RESULT_XY[CFG_LPx__SIZE][CFG_LPx__SLOT_SIZE];

	// N2 STATUS ...
	CX__VAR_STRING_CTRL  sCH__N2_INFO__TIME_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_1__FLOW_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_2__FLOW_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_3__FLOW_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_1__PRESSURE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_2__PRESSURE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_3__PRESSURE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__NOZZLE_4__PRESSURE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__OXYGEN_DENSITY_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  sCH__N2_INFO__CASSETTE_TYPE_X[CFG_LPx__SIZE];

	// ...
	CX__VAR_STRING_CTRL  sCH__ACT_MSG;

	CX__VAR_STRING_CTRL  sCH__INR__ERROR_ID_DEC;
	CX__VAR_STRING_CTRL  sCH__INR__ERROR_ID_HEXA;

	CX__VAR_STRING_CTRL  sCH__INR__ALGINER_ERROR_ID;
	CX__VAR_DIGITAL_CTRL dCH__INR_FLAG__ALGN_STS;

	// CONFIG CHANNEL
	CX__VAR_DIGITAL_CTRL dCH__CFG_ACTION_CONFIRM_FLAG;

	// ...
	CX__VAR_ANALOG_CTRL  aCH__CFG__PICK_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG__PLACE_TIMEOUT;
	CX__VAR_DIGITAL_CTRL dCH__CFG_MAPPING_ACTION_SLIDE_OUT_CHECK;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LP__PADDLE_CHECK_TIME;

	CX__VAR_DIGITAL_CTRL dCH__CFG_MAPPING_DISABLE;

	// CHECK CMMD & ERR_CODE
	CX__VAR_STRING_CTRL  sCH__PARA_CHECK_CMMD;
	CX__VAR_STRING_CTRL  sCH__PARA_CHECK_ERR_CODE;

	// TEST PARA ...
	CX__VAR_DIGITAL_CTRL dCH__TEST_PARA_LPx_ID;

	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__LPx_INITAL;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__LPx_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__FOUP_EXIST;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__DOOR_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__CLAMP_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__RFID_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__AGV_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__LPx_ENABLE;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__RFID_ENABLE;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__CLOSE_MAPPING_ENABLE;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__ONLINE_MODE;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__LOAD_BUTTON_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__UNLOAD_BUTTON_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__PIO_INPUT_HIGH_WORD;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__PIO_INPUT_LOW_WORD;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__PIO_OUTPUT_HIGH_WORD;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__PIO_OUTPUT_LOW_WORD;
	CX__VAR_DIGITAL_CTRL dCH__TEST_STATE__FOUP_TYPE;
	//


	// IO CHANNEL  -----------------------------------

	// AO  ----------
	/*
		TP1 : L_REQ(U_REQ) On ~ TR_REQ On.
		TP2 : READY On ~ BUSY On.
		TP3 : BUSY On ~ Carrier detect. (remove).
		TP4 : L_REQ(U_REQ) Off ~ BUSY Off.
		TP5 : READY Off ~ VLID Off.
		TP6 : VALID Off ~ VALID On. (only continuous handoff)
	*/
	CX__VAR_ANALOG_CTRL  aoCH__PIO_TP_X[CFG_PIO__TP_SIZE];

	// DO  ----------
	CX__VAR_DIGITAL_CTRL doCH__EFEM_MODE;
	CX__VAR_DIGITAL_CTRL doCH__EFEM_LAMP_BUZZER;

	CX__VAR_DIGITAL_CTRL doCH__LP_MODE_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL doCH__LP_CMMD_X[CFG_LPx__SIZE];
	CX__VAR_DIGITAL_CTRL doCH__PIO_RESET_X[CFG_LPx__SIZE];

	CX__VAR_DIGITAL_CTRL doCH__LP_N2_RUN_X[CFG_LPx__SIZE];

	// SO ...
	CX__VAR_STRING_CTRL  soCH__CHECK_CMMD;

	CX__VAR_STRING_CTRL  soCH__RFID_WRITE_X[CFG_LPx__SIZE];

	// SI ...
	CX__VAR_STRING_CTRL  siCH__PIO_TP_INFO;

	CX__VAR_STRING_CTRL  siCH__LP_STATE_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  siCH__LP_MAP_DATA_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  siCH__LP_ALARM_MSG_X[CFG_LPx__SIZE];
	CX__VAR_STRING_CTRL  siCH__LP_ALARM_TXT_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  siCH__LP_N2_STATUS_X[CFG_LPx__SIZE];

	CX__VAR_STRING_CTRL  siCH__RFID_READ_X[CFG_LPx__SIZE];

	// ...
	int iMsg_ID;
	int Get__Msg_ID()
	{
		iMsg_ID++;

		if(iMsg_ID < 0)		iMsg_ID = 1;
		if(iMsg_ID > 999)	iMsg_ID = 1;

		return iMsg_ID;
	}


	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	CX__VAR_DIGITAL_CTRL dEXT_CH__CONFIG_SAVE;
	//


	//-------------------------------------------------------------------------
	// Init -----
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	int  Fnc__SIM_INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ... 
	CString sMODE__CHECK_CMMD;
	int  Call__CHECK_CMMD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CHECK_ERR_CODE;
	int  Call__CHECK_ERR_CODE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__CHECK_LPx_STATE;
	int  Call__CHECK_LPx_STATE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__RECV_PROC(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	int  Fnc__StrTo2Word(const CString& data,
							const char section,
							CString *p_str1,
							CString *p_str2);

	int  Fnc__StrTo7Word(const CString& data,
							const char section,
							CString *p_str1,
							CString *p_str2,
							CString *p_str3,
							CString *p_str4,
							CString *p_str5,
							CString *p_str6,
							CString *p_str7);

	int  Fnc__IndexStrTo1Word(const CString& data,
								const char section,
								int index,
								CString *p_str1);
	int  Fnc__IndexStrTo4Word(const CString& data,
								const char section,
								int index,
								CString *p_str1,
								CString *p_str2,
								CString *p_str3,
								CString *p_str4);
	int  Fnc__IndexStrTo5Word(const CString& data,
								const char section,
								int index,
								CString *p_str1,
								CString *p_str2,
								CString *p_str3,
								CString *p_str4,
								CString *p_str5);

	int  Fnc__HexToDec(const CString& str_dec);
	int  Fnc__DecToBin(int dec,CString *p_str);

	// ...
	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);
	void Fnc__ACT_MSG(const CString& act_msg);

	// ...
	int m_nRetryCount;
	int m_nTimeout;

	// ...
	CString Get__CANCEL_CODE_OF_NAK(const CString err_hexa);

	// ...
	int  Drv__GET_LPx_CMMD(const CString& var_name,
						   const CString& fnc_cmmd,
						   const CString& lp_id,
						   const CString& set_para,
						   CString& para_data) ;

	//
	int  Proc__RECV_RSP(CII_OBJECT__ALARM* p_alarm, const BOOL active_prt);

	int  Check__MSG_KEY_WORD(const CString& str_data, 
							 const CString& key_word, 
							 CStringArray& l_para);

	CString Get__STRING_OF_LIST(const CStringArray& l_str);

	int  Fnc__ONLINE_CHECK(CII_OBJECT__ALARM* p_alarm, const int alarm_check);

	// ...
	int  _Update__LPx_STATE(const int lp_id, const CString& str_rsp);
	int  _Update__LPx_MAP(const int lp_id, const CString& str_rsp);
	int  _Update__LPx_N2_STS(const int lp_id, const CString& str_rsp);

	// ...
	int  _Save__Config_Change();
	//

public:
	CDriver__LPx_ETHERNET();
	~CDriver__LPx_ETHERNET();

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
