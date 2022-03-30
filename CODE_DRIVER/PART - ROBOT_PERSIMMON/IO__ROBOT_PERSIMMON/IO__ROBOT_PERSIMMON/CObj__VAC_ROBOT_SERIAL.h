#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__VAC_ROBOT_SERIAL__DEF.h"


class CObj__VAC_ROBOT_SERIAL : public __IOBJ__IO_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	CCommon_Error__USER_FNC mERROR__USER_FNC;

	// ..
	SCX__USER_LOG_CTRL xAPP_LOG_CTRL;
	SCX__USER_LOG_CTRL xDRV_LOG_CTRL;

	//
	SCX__SERIAL_JG	mX_Serial;

	char m_Term_Str[7];

	int	 m_nCommState;
	int	 m_Rcv_Time;
	int	 m_Out_Time;

	//
	int  iFlag__APP_LOG;
	int  iFlag__DRV_LOG;
	
	int  iActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// ...
	CX__VAR_STRING_CTRL  sCH__ACT_MSG;

	// PARA CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_NAME;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_SLOT;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__ARM_TYPE;

	// PARA : RB ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_RB_ARM_TYPE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RB_POS_CODE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RB_SLOT_CODE;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_RB_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_ID;
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_MSG;

	CX__VAR_STRING_CTRL  sCH__MON_SW_VERSION;

	// MON.WAFER.CEN 
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__RT_RL;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__RT_TL;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__RT_RT;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__RT_TT;

	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__LFT_RL;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__LFT_TL;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__LFT_RT;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__LFT_TT;

	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__CEN_RL;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__CEN_TL;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__CEN_RT;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__CEN_TT;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__CEN_RO;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN__CEN_TO;

	// MON.CEN_OFFSET
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN_RO__ARM_A;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN_TO__ARM_A;

	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN_RO__ARM_B;
	CX__VAR_STRING_CTRL  sCH__MON_WFR_CEN_TO__ARM_B;

	CX__VAR_STRING_CTRL  sCH__DA_RESULT_R_OFFSET_DEG;
	CX__VAR_STRING_CTRL  sCH__DA_RESULT_T_OFFSET_MM;

	// MON.POS.STN
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__R_INFO__ARM_A;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__Z_INFO__ARM_A;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__T_INFO__ARM_A;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__STATION_INFO__ARM_A;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__SLOT_INFO__ARM_A;

	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__R_INFO__ARM_B;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__Z_INFO__ARM_B;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__T_INFO__ARM_B;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__STATION_INFO__ARM_B;
	CX__VAR_STRING_CTRL  sCH__MON_POS_STN__SLOT_INFO__ARM_B;

	// MON.COMM ...
	CX__VAR_STRING_CTRL  sCH__MON_COMM_MODE;
	CX__VAR_STRING_CTRL  sCH__MON_COMM_FLOW;
	CX__VAR_STRING_CTRL  sCH__MON_COMM_LF;
	CX__VAR_STRING_CTRL  sCH__MON_COMM_ECHO;
	CX__VAR_STRING_CTRL  sCH__MON_COMM_CHECKSUM;
	CX__VAR_STRING_CTRL  sCH__MON_COMM_DREP;
	CX__VAR_STRING_CTRL  sCH__MON_COMM_BAUD;


	// CONFIG CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_ACTION_CONFIRM_FLAG;

	// CFG.STN_NUM
	CX__VAR_ANALOG_CTRL  aCH__CFG__LL1_1_STN_NUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG__LL1_2_STN_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG__LL2_1_STN_NUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG__LL2_2_STN_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG__PMx_STN_NUM[CFG_PMx__MD_SIZE];

	// CFG.CPTR.SNS
	CX__VAR_ANALOG_CTRL  aCH__CFG_CPTR_SNS__LL1_1_NUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CPTR_SNS__LL1_2_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG_CPTR_SNS__LL2_1_NUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG_CPTR_SNS__LL2_2_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG_CPTR_SNS__PMx_NUM[CFG_PMx__MD_SIZE];

	// CFG.DA ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_DA_USE;

	CX__VAR_ANALOG_CTRL  aCH__CFG_R_OFFSET_WARNING_ERROR[CFG_PMx__MD_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_R_OFFSET_ABORT_ERROR[CFG_PMx__MD_SIZE];
	
	CX__VAR_ANALOG_CTRL  aCH__CFG_T_OFFSET_WARNING_ERROR[CFG_PMx__MD_SIZE];
	CX__VAR_ANALOG_CTRL  aCH__CFG_T_OFFSET_ABORT_ERROR[CFG_PMx__MD_SIZE];


	// HYPER TERMINAL ...
	CX__VAR_STRING_CTRL  soCH__HYPER_TERMINAL_CMD;

	CX__VAR_STRING_CTRL  xCH__UPDATE_FLAG;
	CX__VAR_DIGITAL_CTRL xCH__LOCK_FLAG;
	CX__VAR_STRING_CTRL  sCH__HYPER_TERMINAL_RECV_MSG;
	CX__VAR_ANALOG_CTRL  aCH__HYPER_TERMINAL_CMD_TIMEOUT;
	CX__VAR_STRING_CTRL  sCH__HYPER_TERMINAL_SEND_MSG;
	CX__VAR_DIGITAL_CTRL dCH__HYPER_TERMINAL_SEND_REQ;

	// SIMULATION CHANNEL ...
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ROTATE_TIME;

	// LBx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LBx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LBx_PLACE_TIME;

	// PMx 
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__PMx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__PMx_PLACE_TIME;

	// MATERIAL CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS;

	CX__VAR_STRING_CTRL  sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE;
	CX__VAR_STRING_CTRL  sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE;

	// CFG ...
	CX__VAR_ANALOG_CTRL  aCH__CFG__PICK_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG__PLACE_TIMEOUT;

	CX__VAR_ANALOG_CTRL  aCH__CFG__EXTEND_TIMEOUT;
	CX__VAR_ANALOG_CTRL  aCH__CFG__RETRACT_TIMEOUT;

	// CFG.COMM ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_MODE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_FLOW;
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_LF;
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_ECHO;
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_CHECKSUM;
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_DREP;
	CX__VAR_DIGITAL_CTRL dCH__CFG_COMM_BAUD;
	//


	// IO CHANNEL  -----------------------------------

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__RB_COMMAND;

	// DI ...
	CX__VAR_DIGITAL_CTRL diCH__COMM_STS;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__RB_STATE_AUTO;
	CX__VAR_STRING_CTRL  siCH__RB_STATE_MANUAL;

	CX__VAR_STRING_CTRL  siCH__VERSION_MANUAL;
	CX__VAR_STRING_CTRL  siCH__RQ_COMM_MANUAL;

	CX__VAR_STRING_CTRL  siCH__WAF_CEN_DATA_MANUAL;
	CX__VAR_STRING_CTRL  siCH__RQ_POS_STN_MANUAL;
	//


	//-------------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int  Call__INIT(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	CString sMODE__HOME;
	int  Call__HOME(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__PICK;
	int  Call__PICK(CII_OBJECT__VARIABLE* p_variable,
					CII_OBJECT__ALARM* p_alarm,
					const CString& arm_type,
					const CString& stn_name,
					const CString& stn_slot);

	CString sMODE__PLACE;
	int  Call__PLACE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	CString sMODE__ROTATE;
	int  Call__ROTATE(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	//
	int  _Check__POS_STN(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm,
						 const CString& arm_type,
						 const CString& stn_name,
						 const CString& stn_slot,
						 const bool active__arm_extend);

	int  _Check__WAF_CEN(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm,
						 const CString& arm_type,
						 const CString& stn_name,
						 const CString& stn_slot);

	int  _Check__DA_ERROR(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm,
						  const CString& arm_type,
						  const CString& stn_name,
						  const CString& stn_slot);

	// ...
	CString sMODE__RETRACT;
	int  Call__RETRACT(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	CString sMODE__EXTEND;
	int  Call__EXTEND(CII_OBJECT__VARIABLE* p_variable,
						CII_OBJECT__ALARM* p_alarm,
						const CString& arm_type,
						const CString& stn_name,
						const CString& stn_slot);

	// ...
	int  _Wait__RB_ACTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__HYPER_TERMINAL_SEND(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int  Get__CFG_STN_NUM(const CString& stn_name,const CString& stn_slot, CString& stn_id);	
	int  Get__CFG_STN_NAME(const int para__stn_id, CString& stn_name,CString& stn_slot);	

	// ...
	int  Is__ONLINE(CII_OBJECT__ALARM* p_alarm);

	// ...
	int  Drv__SEND_COMMAND(const CString& var_name, const CString& str_cmmd,const CString& str_para, CString& recv_data);

	// ...
	int  Fnc__HexToDec(const CString& str_dec);

	// ...
	void Fnc__APP_LOG(const CString& log_msg);
	void Fnc__DRV_LOG(const CString& log_msg);
	void Fnc__DRV_LOG_FORMAT(const char *fmt, ...);
	void Fnc__ACT_MSG(const CString& act_msg);

	// ...
	int m_nRetryCount;
	int m_nTimeout;
	
	// ...
	CString Get__ERROR_MSG(const int err_id);

	// ...
	int  Update__ROBOT_STATE(const CString& str_data);
	int  Update__VERSION(const CString& str_data);
	int  Update__RQ_COMM_INFO(const CString& str_data);
	int  Update__WAF_CEN_DATA(const CString& str_data);
	int  Update__RQ_POS_STN_DATA(const CString& str_data);
	//


public:
	CObj__VAC_ROBOT_SERIAL();
	~CObj__VAC_ROBOT_SERIAL();

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
