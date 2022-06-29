#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__PARAMOUNT_HF__ALID.h"
#include "CObj__PARAMOUNT_HF__DEF.h"


//...
#define MAX_CHAR						256

//...
#define HOST							0x02
#define ANALOG							0x04

// Header...
#define Header_NoData					0x08
#define Header_1ByteData				0x09
#define Header_2ByteData				0x0A
#define Header_3ByteData				0x0B

// Command...
#define CMD__ON							0x02	//  2 // RF Power ON
#define CMD__OFF						0x01	//  1 // RF Power OFF
#define CMD__REGULATION_SELECT			0x03	//	3 // Regulation select //6:Forward power, 7:Load(Delevery, 8:ext
#define CMD__SETPOINT					0x08	//  8 // RF Power Setpoint
#define CMD__MODE_SELECT				0x0E	// 14 // Mode Set  //Value 2:Host, 4:Analog
#define CMD__MODE_READ					0x9B    //155 // Mode Read //Value 2:Host, 4:Analog
#define CMD__STATUS_READ				0xA2	//162 // Status Read
#define CMD__SETPOINT_READ				0xA4	//164 // Setpoint Read
#define CMD__FORWARD_PWR_READ			0xA5	//165 // Forward Read
#define CMD__REFLECET_PWR_READ			0xA6	//166 // Reflect Read
#define CMD__DELIVERED_PWR_READ			0xA7	//167 // Delivered Read
//


class CObj__PARAMOUNT_HF : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	int iActive_SIM;

	SCX__SERIAL_JG mX_Serial;
	CString sPROTOCOL_INFO;

	char m_Term_Str[3];
	int	 m_nCommState;
	int	 m_Rcv_Time;
	int	 m_RetryCnt;
	CString  m_Command;

	unsigned char m_CRC_Table1[256];
	unsigned char m_CRC_Table2[256];

	int iResolution_type;
	int CSRCode;

	// ...
	void Fnc__Initial_CRC_ETC();
	void Fnc__Get_CRC(unsigned char *String,unsigned char Size,unsigned char *C0,unsigned char *C1);
	//


	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	byte iUNIT__ADDR_ID;
	int  iFLAG__DRV_FLAG;

	// ...
	void Write__APP_LOG(const CString& log_msg);
	void Write__DRV_LOG(const CString& log_msg);
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;		  

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_SET_POWER;

	CX__VAR_DIGITAL_CTRL dCH__PARA_TUNE_USE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_FREQ_TUNE_DELAY;

	CX__VAR_ANALOG_CTRL  aCH__PARA_RAMP_UP_TIME;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RAMP_DN_TIME;

	CX__VAR_ANALOG_CTRL  aCH__PARA_START_FREQUENCY;
	CX__VAR_ANALOG_CTRL  aCH__PARA_OUTPUT_FREQUENCY;

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_COMM_STS;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_CTRL_MODE_READ;	  
	CX__VAR_STRING_CTRL  sCH__INFO_FORWARD_POWER_READ;
	CX__VAR_STRING_CTRL  sCH__INFO_REFLECTED_POWER_READ;
	CX__VAR_STRING_CTRL  sCH__INFO_DELIVERED_POWER_READ;
	CX__VAR_STRING_CTRL	 sCH__INFO_POWER_SETPOINT_READ;
	CX__VAR_STRING_CTRL	 sCH__INFO_REGULATION_MODE_READ;

	CX__VAR_STRING_CTRL	 sCH__INFO_CSR_HEXA;
	CX__VAR_STRING_CTRL	 sCH__INFO_CSR_MSG;

	// BYTE : 0
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_TUNING;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_SETPOINT_RAMPING;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_RECIPE_ACTIVE;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_RECIPE_ENABLED;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_RF_OUTPUT_ON;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_RF_ON_REQUESTED;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_SETPOINT_TOLERANCE;

	// BYTE : 1
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_OVERTEMPERATURE_FAULT;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_FREQUENCY_VARIABLE_MODE;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_PULSING_EMABLED;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_ARC_MANAGEMENT_ENABLED;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_INTERLOCK_OPEN;

	// BYTE : 2
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_HIGH_AC_LINE_VOLTAGE_WARNING;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_LOW_AC_LINE_VOLTAGE_WARNING;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_PROTECTION_LIMIT;

	// BYTE : 3
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_INVERTER_NOT_READY;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_FIELD_BUS_ERROR;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_CEX_ENABLED;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_FAULT_PRESENT;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_WARNING_PRESENT;
	CX__VAR_STRING_CTRL	 sCH__INFO_STS_CEX_LOCKED;
	//

	// IO CHANNEL  -----------------------------------
	// AO ...
	CX__VAR_ANALOG_CTRL  aoCH__POWER_SET;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__CTRL_MODE_HEXA;
	CX__VAR_STRING_CTRL	 siCH__SETPOINT_REGULATION_HEXA;

	CX__VAR_STRING_CTRL	 siCH__REPORT_FORWARD_POWER_HEXA;
	CX__VAR_STRING_CTRL	 siCH__REPORT_REFLECTED_POWER_HEXA;
	CX__VAR_STRING_CTRL	 siCH__REPORT_DELIVERED_POWER_HEXA;

	CX__VAR_STRING_CTRL  siCH__REPORT_PROCESS_STATUS_HEXA;

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__CTRL_MODE;			// HOST  ANALOG
	CX__VAR_DIGITAL_CTRL doCH__POWER_MODE;			// OFF   ON
	CX__VAR_DIGITAL_CTRL doCH__REGULATION_MODE;		// FORWARD  LOAD  ETC
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__REMOTE;
	CString sMODE__LOCAL;
	int  Call__CTRL_MODE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_remote);

	CString sMODE__ON;
	CString sMODE__OFF;
	int  Call__POWER_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active_power);

	CString sMODE__PROC_SET;
	int  Call__PROC_SET(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void _Set_CheckSum(unsigned char *s_cmmd, const int s_len);
	int  _Recv__Command(const byte addr_id,const byte cmmd_id,const byte s_data_len,const byte r_data_len, unsigned char* r_data,const int set_data = 0);
	
	CString _Get__CSR_CODE(const byte csr_code);

	// ...
	int  Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void Fnc__Do_Abort(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm);

	int  Seq__Ramp_Up_Down(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const int zero_ctrl);
	//


public:
	CObj__PARAMOUNT_HF();
	~CObj__PARAMOUNT_HF();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_rs232_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};

