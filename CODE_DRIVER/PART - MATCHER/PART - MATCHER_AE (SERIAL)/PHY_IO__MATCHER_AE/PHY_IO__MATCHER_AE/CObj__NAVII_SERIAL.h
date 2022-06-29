#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__NAVII_SERIAL__ALID.h"
#include "CObj__NAVII_SERIAL__DEF.h"


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


class CObj__NAVII_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	bool bActive__COMM_ONLINE;

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

	// byte iUNIT__ADDR_ID;
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
	CX__VAR_DIGITAL_CTRL dCH__PARA_SEL_CH;		
	CX__VAR_STRING_CTRL  sCH__CUR_SEL_CH;		

	CX__VAR_DIGITAL_CTRL dCH__PARA_CONTROL_MODE_CH1;		
	CX__VAR_DIGITAL_CTRL dCH__PARA_CONTROL_MODE_CH2;		

	CX__VAR_ANALOG_CTRL  aCH__PARA_ACTIVE_PRESET_CH1;		
	CX__VAR_ANALOG_CTRL  aCH__PARA_ACTIVE_PRESET_CH2;		

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_LOAD_POS_CH1;
	CX__VAR_ANALOG_CTRL  aCH__PARA_LOAD_POS_CH2;

	CX__VAR_STRING_CTRL  sCH__CUR_LOAD_POS_CH1;
	CX__VAR_STRING_CTRL  sCH__CUR_LOAD_POS_CH2;

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_TUNE_POS_CH1;
	CX__VAR_ANALOG_CTRL  aCH__PARA_TUNE_POS_CH2;

	CX__VAR_STRING_CTRL  sCH__CUR_TUNE_POS_CH1;
	CX__VAR_STRING_CTRL  sCH__CUR_TUNE_POS_CH2;

	//
	CX__VAR_ANALOG_CTRL  aCH__PARA_CAP_POS_CH1;
	CX__VAR_ANALOG_CTRL  aCH__PARA_CAP_POS_CH2;

	CX__VAR_STRING_CTRL  sCH__CUR_CAP_POS_CH1;
	CX__VAR_STRING_CTRL  sCH__CUR_CAP_POS_CH2;
	//

	// MON ...
	CX__VAR_DIGITAL_CTRL dCH__MON_COMM_STS;

	// INFO ...
	CX__VAR_STRING_CTRL  sCH__INFO_CTRL_MODE_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_CTRL_MODE_CH2;	  

	CX__VAR_STRING_CTRL  sCH__INFO_LOAD_POS_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_LOAD_POS_CH2;	  

	CX__VAR_STRING_CTRL  sCH__INFO_TUNE_POS_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_TUNE_POS_CH2;	  

	CX__VAR_STRING_CTRL  sCH__INFO_CAP_POS_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_CAP_POS_CH2;	  

	CX__VAR_STRING_CTRL  sCH__INFO_CAP_CURRENT_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_CAP_CURRENT_CH2;	  

	CX__VAR_STRING_CTRL  sCH__INFO_R_SENSOR_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_R_SENSOR_CH2;	  

	CX__VAR_STRING_CTRL  sCH__INFO_X_SENSOR_CH1;	  
	CX__VAR_STRING_CTRL  sCH__INFO_X_SENSOR_CH2;	  

	CX__VAR_STRING_CTRL	 sCH__INFO_CSR_HEXA;
	CX__VAR_STRING_CTRL	 sCH__INFO_CSR_MSG;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG_PART_ADDRES_ID;

	CX__VAR_DIGITAL_CTRL dCH__CFG_USE_CH2;

	CX__VAR_ANALOG_CTRL  aCH__CFG_LOAD_MIN_CH1;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LOAD_MAX_CH1;

	CX__VAR_ANALOG_CTRL  aCH__CFG_LOAD_MIN_CH2;
	CX__VAR_ANALOG_CTRL  aCH__CFG_LOAD_MAX_CH2;

	CX__VAR_ANALOG_CTRL  aCH__CFG_TUNE_MIN_CH1;
	CX__VAR_ANALOG_CTRL  aCH__CFG_TUNE_MAX_CH1;

	CX__VAR_ANALOG_CTRL  aCH__CFG_TUNE_MIN_CH2;
	CX__VAR_ANALOG_CTRL  aCH__CFG_TUNE_MAX_CH2;
	//

	// IO CHANNEL  -----------------------------------
	// SI ...
	CX__VAR_STRING_CTRL  siCH__CTRL_MODE_HEXA_CH1;
	CX__VAR_STRING_CTRL  siCH__CTRL_MODE_HEXA_CH2;

	CX__VAR_STRING_CTRL  siCH__CAPACITOR_POS_HEXA_CH1;
	CX__VAR_STRING_CTRL  siCH__CAPACITOR_POS_HEXA_CH2;

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__ALL_CAPACITOR_INIT;		

	CX__VAR_DIGITAL_CTRL doCH__CAPACITOR_LIMIT_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__CAPACITOR_LIMIT_CH2;		

	CX__VAR_DIGITAL_CTRL doCH__CONTROL_MODE_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__CONTROL_MODE_CH2;		

	CX__VAR_DIGITAL_CTRL doCH__INTERNAL_EXTERNAL_PRESET_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__INTERNAL_EXTERNAL_PRESET_CH2;		

	CX__VAR_DIGITAL_CTRL doCH__ACTIVE_PRESET_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__ACTIVE_PRESET_CH2;		

	CX__VAR_DIGITAL_CTRL doCH__LOAD_POS_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__LOAD_POS_CH2;		

	CX__VAR_DIGITAL_CTRL doCH__TUNE_POS_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__TUNE_POS_CH2;		

	CX__VAR_DIGITAL_CTRL doCH__CAPACITOR_MOTOR_POS_CH1;		
	CX__VAR_DIGITAL_CTRL doCH__CAPACITOR_MOTOR_POS_CH2;		
	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__AUTO_ALL;
	CString sMODE__AUTO_CH;
	int  Call__AUTO_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_all);

	CString sMODE__MANUAL_ALL;
	CString sMODE__MANUAL_CH;
	int  Call__MANUAL_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const bool active_all);

	//
	CString sMODE__CTRL_MODE_ALL;
	CString sMODE__CTRL_MODE_CH1;
	CString sMODE__CTRL_MODE_CH2;
	int  Call__CTRL_MODE_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id);

	CString sMODE__PRESET_ALL;
	CString sMODE__PRESET_CH1;
	CString sMODE__PRESET_CH2;
	int  Call__PRESET_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id);

	CString sMODE__LOAD_POS_ALL;
	CString sMODE__LOAD_POS_CH1;
	CString sMODE__LOAD_POS_CH2;
	int  Call__LOAD_POS_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id);

	CString sMODE__TUNE_POS_ALL;
	CString sMODE__TUNE_POS_CH1;
	CString sMODE__TUNE_POS_CH2;
	int  Call__TUNE_POS_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id);

	CString sMODE__CAP_MOTOR_ALL;
	CString sMODE__CAP_MOTOR_CH1;
	CString sMODE__CAP_MOTOR_CH2;
	int  Call__CAP_MOTOR_CH_X(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm, const int ch_id);

	CString sMODE__PROC_CTRL;
	int  Call__PROC_CTRL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void _Set_CheckSum(unsigned char *s_cmmd, const int s_len);
	int  _Recv__Command(const CString& var_name, const byte addr_id,const byte cmmd_id,const byte s_data_len,const byte r_data_len, unsigned char* s_data,unsigned char* r_data);

	CString _Get__CSR_CODE(const byte csr_code);

	// ...
	int  Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	void Fnc__Do_Abort(CII_OBJECT__ALARM* p_alarm);
	int  Fnc__Is_Online(CII_OBJECT__ALARM* p_alarm);

	int  Seq__Ramp_Up_Down(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const int zero_ctrl);
	//


public:
	CObj__NAVII_SERIAL();
	~CObj__NAVII_SERIAL();

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

