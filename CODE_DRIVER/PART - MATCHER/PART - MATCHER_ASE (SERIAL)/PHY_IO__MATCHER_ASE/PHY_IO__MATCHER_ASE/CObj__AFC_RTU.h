#pragma once

#include "Interface_Code.h"

#include "CObj__AFC_RTU__DEF.h"


union  JG_F4
{
	unsigned char uData[4];
	float fValue;
};

union  JG_UI2
{
	unsigned char  uData[2];
	unsigned short uiValue;
};

union  JG_I2
{
	char  cData[2];
	short iValue;
};


#define _DATA_TYPE__UI2				1
#define _DATA_TYPE__I2				2
#define _DATA_TYPE__F4				3


class CObj__AFC_RTU : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	SCX__SERIAL_JG mX_Serial;
	
	int iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	SCX__USER_LOG_CTRL xI__APP_LOG_CTRL;
	SCX__USER_LOG_CTRL xI__DRV_LOG_CTRL;

	bool bActive__COMM_ONLINE;
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_LOAD_POSITION;
	CX__VAR_ANALOG_CTRL  aCH__PARA_TUNE_POSITION;

	// PARA.DRV ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_DRV_CTRL_MODE;
	CX__VAR_DIGITAL_CTRL dCH__PARA_DRV_PRESET;

	// INFO ...
	unsigned char iPara__Slave_ID;

	CX__VAR_STRING_CTRL  sCH__INFO_COM_PORT;
	CX__VAR_STRING_CTRL  sCH__INFO_PROTOCOL;
	CX__VAR_STRING_CTRL  sCH__INFO_MODBUS_ADDR;
	CX__VAR_STRING_CTRL  sCH__INFO_BAUD_RATE;
	CX__VAR_STRING_CTRL  sCH__INFO_COMM_PARITY;
	CX__VAR_STRING_CTRL  sCH__INFO_DATA_BIT;
	CX__VAR_STRING_CTRL  sCH__INFO_STOP_BIT;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_STATE;

	//
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_MANUAL_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_PRESET_ENABLE_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_ALARM_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_RFON_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_TUNE_MATCHED_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_COAXIAL_ALARM_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_COVER_ALARM_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_MOTOR_ALARM_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_FAN1_ALARM_ACTIVE;
	CX__VAR_DIGITAL_CTRL dCH__MON_MAT_STS_FAN2_ALARM_ACTIVE;

	//
	CX__VAR_STRING_CTRL  sCH__MON_CUR_LOAD_POSITION;
	CX__VAR_STRING_CTRL  sCH__MON_CUR_TUNE_POSITION;
	CX__VAR_STRING_CTRL  sCH__MON_CUR_VPP;
	CX__VAR_STRING_CTRL  sCH__MON_CUR_VRMS;
	CX__VAR_STRING_CTRL  sCH__MON_CUR_IRMS;
	CX__VAR_STRING_CTRL  sCH__MON_CUR_Phase;

	//
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_CODE;
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_MSG;
	//

	// IO CHANNEL  -----------------------------------
	// ...
	CX__VAR_STRING_CTRL  siCH__Matcher_State;

	CX__VAR_STRING_CTRL  siCH__Load_Position;
	CX__VAR_STRING_CTRL  siCH__Tune_Position;
	CX__VAR_STRING_CTRL  siCH__VPP;
	CX__VAR_STRING_CTRL  siCH__VRMS;
	CX__VAR_STRING_CTRL  siCH__IRMS;
	CX__VAR_STRING_CTRL  siCH__Phase;

	//
	CX__VAR_DIGITAL_CTRL doCH__OP_Mode;

	CX__VAR_ANALOG_CTRL  aoCH__Preset_Load_Position;
	CX__VAR_ANALOG_CTRL  aoCH__Preset_Tune_Position;
	//

	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	//


	//-------------------------------------------------------------------------
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	//
	CString sMODE__AUTO;
	int  Call__AUTO(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__MANUAL;
	int  Call__MANUAL(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	unsigned int _Make__READ_PACKET(unsigned char* s_data, 
		                            const unsigned char addr_id,
	                                const unsigned char cmmd_id,
							        const unsigned int  start_addr,
									const unsigned char read_num);
	unsigned int _Recv__READ_PACKET(unsigned char* s_data, 
								    const int s_len);

	unsigned int _Make__WRITE_PACKET(unsigned char* s_data, 
									const unsigned char addr_id,
									const unsigned char cmmd_id,
									const unsigned int  start_addr,
									const unsigned char write_num,
									const int data_type,
									const unsigned short set_ui,
									const short set_i);

	unsigned short _Get__CRC16(unsigned char* s_data, const int data_len);

	// ...
	void Mon__MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString _Get__Error_Code(const int err_code);
	//


public:
	CObj__AFC_RTU();
	~CObj__AFC_RTU();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj, l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_io_variable);

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

