#pragma once

#include "Interface_Code.h"

#include "CObj__LV32_BLDC__ALID.h"
#include "CObj__LV32_BLDC__DEF.h"


// ...
union UNION_2_BYTE__UINT
{
	unsigned short int uiDATA;
	char		 cBYTE[2];
};
union UNION_3_BYTE__UINT
{
	unsigned int uiDATA;
	char		 cBYTE[3];
};
union UNION_4_BYTE__UINT
{
	unsigned long uiDATA;
	char		 cBYTE[4];
};
union UNION_4_BYTE__FLOAT
{
	float fDATA;
	unsigned long uiDATA;
	char  cBYTE[4];
};


class CObj__LV32_BLDC : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__USER_LOG_CTRL xLog_Ctrl__Drive;
	SCX__SERIAL	mX_Serial;

	int iActive_SIM;

	// ...
	int	m_nCommState;
	int	m_Rcv_Time;
	int m_nRetryCnt;
	//


	// ---------------------------------------------------------------------------------------------
	// INTERNAL PARAMETER ... 

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// MON ...
	int iCOMM_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_COMMUNICATION_INFO;

	CX__VAR_STRING_CTRL  sCH__MON_SYSTEM_ABORT;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_FFU_BLOCK_RPM_SV;
	CX__VAR_ANALOG_CTRL  aCH__PARA_FFU_UNIT_DIFF_PRESSURE;

	// CFG ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_FFU_TYPE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_FFU_INITIAL_RPM;
	CX__VAR_ANALOG_CTRL  aCH__CFG_FFU_LOW_LIMIT_RPM;

	CX__VAR_ANALOG_CTRL  aCH__CFG_FFU_INITIAL_DIFF_PRESSURE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_FFU_LOW_LIMIT_DIFF_PRESSURE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_LV32_ID;
	CX__VAR_ANALOG_CTRL  aCH__CFG_START_ICU_ID;
	CX__VAR_ANALOG_CTRL  aCH__CFG_RANGE_ICU_COUNT;

	// IO Channel ...
	CX__VAR_DIGITAL_CTRL diCH__FFU_BLOCK_GET;
	CX__VAR_DIGITAL_CTRL doCH__FFU_BLOCK_SET;

	CX__VAR_DIGITAL_CTRL diCH__FFU_UNIT_GET;
	CX__VAR_DIGITAL_CTRL doCH__FFU_UNIT_SET;

	//
	CX__VAR_STRING_CTRL  sCH__FFU_UNIT__PRESSURE_HEXA;
	CX__VAR_STRING_CTRL  sCH__FFU_UNIT__PRESSURE_VALUE;

	// 
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__STATE_HEXA_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__ID_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__RPM_PV_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__RPM_SV_X[CFG__FAN_SIZE];

	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__ALARM_LOCAL_MODE_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__ALARM_POWER_OFF_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__ALARM_OVER_CURRENT_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__ALARM_MOTOR_ERROR_X[CFG__FAN_SIZE];
	CX__VAR_STRING_CTRL  sCH__FFU_BLOCK__ALARM_CONNECTION_ERROR_X[CFG__FAN_SIZE];
	//

	// ---------------------------------------------------------------------------------------------
	// EXTERNAL PARAMETER ... 

	// 


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CHECK_PACKET_FORMAT;
	int  Call__CHECK_PACKET_FORMAT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);


	// ---------------------------------------------------------------------------------------------
	void Mon__ALM_REPORT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM *p_alarm);

	// ...
	unsigned char _Get_CheckSum(const unsigned char *s_data, const int s_len);

	int _Recv_Command(const unsigned char cmmd_type, unsigned char* r_data, const int set_sv = 0);
	int _Check_Command(const unsigned char cmmd_type, unsigned char* r_data, const int set_sv = 0);

	// ...
	void Fnc__DRV_LOG_OF_MSG(const CString& log_msg);
	void Fnc__DRV_LOG_OF_DATA_ERROR();
	//


public:
	CObj__LV32_BLDC();
	~CObj__LV32_BLDC();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);	
	int __DEFINE__ALARM(p_alarm);

	int __DEFINE__VARIABLE_IO(p_io_variable);

	//-------------------------------------------------------------------------	
	int __INITIALIZE__OBJECT(p_variable, p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------	
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);

	int __CLOSE__OBJECT();

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
