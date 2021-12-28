#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj__OVATION_2560__ALID.h"
#include "CObj__OVATION_2560__DEF.h"


class CObj__OVATION_2560: public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL	xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL	xLOG_CTRL;

	SCX__TIMER_CTRL		xI_TIMER;
	SCX__SEQ_INFO		xSEQ_INFO;

	SCX__SERIAL mX_Serial;

	enum { OFFLINE, ONLINE };
	
	int m_nCommSts;
	int m_nTimeout;
	int m_nRetryCount;

	int	RF_Ps_Request;
	int	RF_Ps_state;			// 0(false) : Standard Mode, 1(true) : Pulse Mode

	// Pulse Parameter
#define 	RF_Ps_Master		1			// 1	Pulsing mode		 : 1 Master , 2 Slave mode
#define		RF_Ps_Sync_Out		2			// 2	Pulse sync output	 : 0 Sync off, 1 Sync on
											// 3	Reserved
#define		RF_Ps_Slave_Delay	4			// 4	Slave input delay	 : 0 ~ 100000
#define		RF_Ps_Memory		5			// 5	Set memory mode		 : 0 RAM, 1 NVRAM(비휘발성)
#define		RF_Ps_Explicit		6			// 6	Explicit enable mode : 0 Implicit, 1 Explicit enable
#define		RF_Ps_Enable		7			// 7	Pulsing enable mode	 : 0 Off, 1 On
#define		RF_Ps_Mode			8			// 8	Generator mode		 : 0 Standard, 1 Pulse, 2 Arc management

	//

	//-------------------------------------------------------------------------
	// ...
	CX__VAR_DIGITAL_CTRL dCH__RF_CMD;
	CX__VAR_DIGITAL_CTRL dCH__MONITOR_FLAG;
	CX__VAR_DIGITAL_CTRL dCH__DRV_LOG_PARAM_START_STOP;

	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;	
	CX__VAR_ANALOG_CTRL  aCH__SET_POWER;
	CX__VAR_DIGITAL_CTRL dCH__SET_TUNE_USE;			
	CX__VAR_ANALOG_CTRL  aCH__SET_START_FREQUENCY;	
	CX__VAR_ANALOG_CTRL  aCH__SET_OUTPUT_FREQUENCY;	
	CX__VAR_ANALOG_CTRL  aCH__FREQ_TUNE_DELAY;		
	CX__VAR_ANALOG_CTRL  aCH__RF_ON_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__FREQ_Value;

	// Pulsing parameter
	// 20181218 @pck Pulsing Mode : Standard / Pulsing
	CX__VAR_ANALOG_CTRL  aCH__Ps_Frequency_Set;
	CX__VAR_ANALOG_CTRL  aCH__Ps_Duty_Set;
	CX__VAR_ANALOG_CTRL  aCH__Ps_Frequency;
	CX__VAR_ANALOG_CTRL  aCH__Ps_Duty;
	CX__VAR_ANALOG_CTRL  aoCH__Ps_Frequency_Set;
	CX__VAR_ANALOG_CTRL  aoCH__Ps_Duty_Set;
	CX__VAR_ANALOG_CTRL  aiCH__Ps_Frequency;
	CX__VAR_ANALOG_CTRL  aiCH__Ps_Duty;

	CX__VAR_DIGITAL_CTRL dCH__Pulsing_Mode;	
	CX__VAR_DIGITAL_CTRL diCH__Pulsing_Status; 
	CX__VAR_DIGITAL_CTRL doCH__Pulsing_Mode_Set; 

	// Configuration.
	CX__VAR_ANALOG_CTRL aCH__RAMP_TIME;
	CX__VAR_ANALOG_CTRL aCH__RAMP_UP_TIME;
	CX__VAR_ANALOG_CTRL aCH__RAMP_DN_TIME;

	// Status Channel
	CX__VAR_ANALOG_CTRL aCH__FWD_Power;
	CX__VAR_ANALOG_CTRL aCH__REFL_Power;

	// Driver Channel Controller
	CX__VAR_DIGITAL_CTRL diCH__COMM_STS;
	CX__VAR_DIGITAL_CTRL diCH__CONTROL_MODE;
	CX__VAR_DIGITAL_CTRL diCH__FREQUENCY_CONTROL_MODE;
	CX__VAR_DIGITAL_CTRL diCH__Ramp_Mode;
	CX__VAR_DIGITAL_CTRL diCH__Process_Status;
	

	CX__VAR_STRING_CTRL  siCH__Impedance;
	CX__VAR_STRING_CTRL  siCH__PowerSupply_Type;
	CX__VAR_STRING_CTRL  siCH__PowerSupply_Size;

	CX__VAR_ANALOG_CTRL aoCH__SetPower;
	CX__VAR_ANALOG_CTRL aoCH__Power_Limit;
	CX__VAR_ANALOG_CTRL aoCH__RampUp_Time;
	CX__VAR_ANALOG_CTRL aoCH__RampDown_Time;
	CX__VAR_ANALOG_CTRL aoCH__RF_Freq;
	CX__VAR_ANALOG_CTRL aoCH__Start_Freq;
	CX__VAR_ANALOG_CTRL aoCH__Set_Tuning_Timeout;
	CX__VAR_ANALOG_CTRL aoCH__HostPort_Timeout;
	CX__VAR_ANALOG_CTRL aoCH__Tune_Delay;
	CX__VAR_ANALOG_CTRL aoCH__Tune_Min_Freq;
	CX__VAR_ANALOG_CTRL aoCH__Tune_Max_Freq;
	CX__VAR_ANALOG_CTRL aoCH__Min_Freq_Tune_Step;
	CX__VAR_ANALOG_CTRL aoCH__Init_Fine_Tune_Step;
	CX__VAR_ANALOG_CTRL aoCH__Retruning_Threshold;

	CX__VAR_ANALOG_CTRL aiCH__ForwardPower;
	CX__VAR_ANALOG_CTRL aiCH__ReflectPower;
	CX__VAR_ANALOG_CTRL aiCH__DeliveredPower;
	CX__VAR_ANALOG_CTRL aiCH__Power_Limit;
	CX__VAR_ANALOG_CTRL aiCH__SetPower;
	CX__VAR_ANALOG_CTRL aiCH__Set_Fixed_Frequency;
	CX__VAR_ANALOG_CTRL aiCH__WhenOn_Actual_Frequency;
	CX__VAR_ANALOG_CTRL aiCH__Tuning_Start_Frequency;
	CX__VAR_ANALOG_CTRL aiCH__Set_Tuning_Timeout;
	CX__VAR_ANALOG_CTRL aiCH__HostPort_Timeout;
	CX__VAR_ANALOG_CTRL aiCH__Tune_Delay;
	CX__VAR_ANALOG_CTRL aiCH__Tune_Min_Freq;
	CX__VAR_ANALOG_CTRL aiCH__Tune_Max_Freq;
	CX__VAR_ANALOG_CTRL aiCH__Min_Freq_Tune_Step;
	CX__VAR_ANALOG_CTRL aiCH__Init_Fine_Tune_Step;
	CX__VAR_ANALOG_CTRL aiCH__Retruning_Threshold;
	CX__VAR_ANALOG_CTRL aiCH__Error_Status;

	CX__VAR_DIGITAL_CTRL doCH__RF_CMD;
	CX__VAR_DIGITAL_CTRL doCH__CONTROL_MODE;
	CX__VAR_DIGITAL_CTRL doCH__FREQUENCY_CONTROL_MODE;
	

	CX__VAR_DIGITAL_CTRL vdoCH__Ramp_Mode;
	CX__VAR_DIGITAL_CTRL vdiCH__Output_Regulation_Mode;

	CX__VAR_ANALOG_CTRL  vaiCH__Ramp_Up;
	CX__VAR_ANALOG_CTRL  vaiCH__Ramp_Down;

	// .......... // Process Status
	CX__VAR_DIGITAL_CTRL vdiCH__Tunning_Status;
	CX__VAR_DIGITAL_CTRL vdiCH__SetPoint_Ramp;
	CX__VAR_DIGITAL_CTRL vdiCH__RFOutput_Power;
	CX__VAR_DIGITAL_CTRL vdiCH__RFOn_Request;
	CX__VAR_DIGITAL_CTRL vdiCH__SetPoint_Tolerance;
	CX__VAR_DIGITAL_CTRL vdiCH__ColdPlate_OverTemp_Fault;
	CX__VAR_DIGITAL_CTRL vdiCH__Interlock_Open;
	CX__VAR_DIGITAL_CTRL vdiCH__Inverter_Ready;
	CX__VAR_DIGITAL_CTRL vdiCH__Fault_Status;
	CX__VAR_DIGITAL_CTRL vdiCH__Warning_Status;

	CX__VAR_STRING_CTRL vsiCH__Impedance_Real;
	CX__VAR_STRING_CTRL vsiCH__Impedance_Imaginary;

	CX__VAR_STRING_CTRL  sCH__CSR_CODE_NUM;

	// External Channel
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_OVERTIME_SNS;	//입력 : RF On상태에서 Alive 신호가 일정 시간 출력되지 않을 시, 해당 신호 On -> Hardware적 Timer Interlock
													//       Serial 통신 불량 또는 PC에 문제가 생겼다고 판단될 상황
													//		 해당 신호가 On이 되는 경우, Hardware Timer에서 Gen의 Interlock 신호를 해제하여 강제 RF Off로 전환
	CX__VAR_DIGITAL_CTRL dEXT_CH__RF_ALIVE_INTLK;	//출력 : Serial 통신이 Online인 동안 주기적으로 On/Off - RF On 상태에서, PC<->Gen. 또는 PC가 뻗는 현상 발생 시, RF Off시켜주기 위한 Alive신호



	//-------------------------------------------------------------------------
	// Control Mode ...
	CString sMODE__INIT;
	int Call__INIT(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__REMOTE;
	int Call__REMOTE(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__LOCAL;
	int Call__LOCAL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__RF_OFF;
	int Call__RF_OFF(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Call__OFF(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SET_POWER;
	int Call__SET_POWER(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	CString sMODE__SET_PULSING; //2018.12.18 @pck pulse mode set
	int FNC__PULSING_SEQ(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int FNC__PULSING_INIT_SEQ(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);

	// ...
	int Seq__RAMP_UPDOWN(CII_OBJECT__ALARM *p_alarm);
	int Seq__RAMP_UPDOWN_Ex(CII_OBJECT__VARIABLE *p_variable, 
							CII_OBJECT__ALARM *p_alarm, 
							const CString str_mode);

	int FNC__PROC_SEQ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int Fnc__doSTOP(CII_OBJECT__ALARM *p_alarm);

	int HexToDecimal(CString str_dec);
	int DecimalToBinary(int dec, CString &string);

	// MON ...
	int Call__STATUS_MON(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Call__STATUS_MON_1(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	int Call__Alive_Signal(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	//

	// Status Data;
	CString m_szStatus;
	int m_nAddress;

	// Driver Function.
	int SendCommand(unsigned char * str_cmd, unsigned char * str_recv, int nSendDataSize, int nRecvDataSize);
	int RecvCommand(unsigned char * str_cmd, unsigned char * str_recv, int nSendDataSize, int nRecvDataSize);

	int CheckRFContactor(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int CheckRFInterlock(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);

	unsigned char Check_Sum(unsigned char *bufferData, int Count);
	int Chk_CSR_CODE(UCHAR csr_code);
	int Get_Bit_Sts (BYTE source , int pos);
	//

public:
	// ...
	int IsSimulation();
	int CheckOnline(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int CheckRemote(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Fnc__DEFAULT_CONFIG_SET(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm);
	int Alarm__CHECK_RETRY_ABORT(CII_OBJECT__ALARM* p_alarm, CString msg, const int alarm_id);
	int Alarm__CHECK_POST(CII_OBJECT__ALARM* p_alarm,CString msg, const int alarm_id);

	// Log 
	void Fnc__WRITE_LOG(const char *fmt, ...);
	void Fnc__WRITE_APP_LOG( const char *fmt, ... );
	//

public:
	CObj__OVATION_2560();
	~CObj__OVATION_2560();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__VARIABLE_IO(p_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);
	int __INITIALIZE__IO(p_io_para);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id, p_variable, p_alarm);

	//-------------------------------------------------------------------------
	int __Read__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, double& read_data);
	int __Read__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, CString& read_data,int& item_index);
	int __Read__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, CString& read_data);

	int __Write__ANALOG(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const double set_data);
	int __Write__DIGITAL(const CString& var_name,const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data,const int item_index);
	int __Write__STRING(const CString& var_name, const CDS_IO__CHANNEL_INFO& io_info, const CString& set_data);
};
