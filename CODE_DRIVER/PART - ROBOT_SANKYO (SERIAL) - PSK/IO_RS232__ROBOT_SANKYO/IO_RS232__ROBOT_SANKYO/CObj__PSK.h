#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CObj__PSK__DEF.h"


class CObj__PSK : public __IOBJ__IO_TYPE
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

	CX__VAR_STRING_CTRL  sCH__ACT_MSG;

	// PARA CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_NAME;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__STN_SLOT;
	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__ARM_TYPE;

	CX__VAR_DIGITAL_CTRL dCH__OTR_IN_PARA__AL1_SLOT_ID;
	CX__VAR_ANALOG_CTRL  aCH__OTR_IN_PARA__AL1_CCD_POS;

	// PARA : RB ...
	CX__VAR_DIGITAL_CTRL dCH__PARA_RB_ARM_TYPE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RB_POS_CODE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_RB_SLOT_CODE;

	// PARA : AL ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_AL_NOTCH_ANGLE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_AL_RELATIVE_ANGLE;
	CX__VAR_ANALOG_CTRL  aCH__PARA_AL_ABSOLUTE_ANGLE;

	// MON ...
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_ERROR_CODE;
	CX__VAR_STRING_CTRL  sCH__MON_SERVO_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_ORIGIN_REQ;
	CX__VAR_STRING_CTRL  sCH__MON_COMMAND_RUN;
	CX__VAR_STRING_CTRL  sCH__MON_A_ARM_GRIPPER_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_B_ARM_GRIPPER_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_RB_FAN_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_RB_TASK_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_AL_TASK_STATE;

	CX__VAR_STRING_CTRL  sCH__MON_APP_VERSION;
	CX__VAR_STRING_CTRL  sCH__MON_REVISION;

	CX__VAR_STRING_CTRL  sCH__MON_AL_STATE;
	CX__VAR_STRING_CTRL  sCH__MON_AL_X_ERROR;
	CX__VAR_STRING_CTRL  sCH__MON_AL_Y_ERROR;
	CX__VAR_STRING_CTRL  sCH__MON_AL_NOTCH_ANGLE;

	// CONFIG CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_ACTION_CONFIRM_FLAG;

	CX__VAR_ANALOG_CTRL  aCH__CFG__AL1_STN_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG__LL1_1_STN_NUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG__LL1_2_STN_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG__LL2_1_STN_NUM;
	CX__VAR_ANALOG_CTRL  aCH__CFG__LL2_2_STN_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG__ST1_STN_NUM;

	CX__VAR_ANALOG_CTRL  aCH__CFG__LPx_STN_NUM[CFG_LPx__SIZE];

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

	// LPx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LPx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LPx_PLACE_TIME;

	// ALx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ALx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__ALx_PLACE_TIME;

	// LBx
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LBx_PICK_TIME;
	CX__VAR_ANALOG_CTRL  aCH__SIM_CFG__LBx_PLACE_TIME;

	// MATERIAL CHANNEL ...
	CX__VAR_DIGITAL_CTRL dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS;
	CX__VAR_DIGITAL_CTRL dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS;
	//


	// IO CHANNEL  -----------------------------------

	// DO ...
	CX__VAR_DIGITAL_CTRL doCH__RB_COMMAND;
	CX__VAR_DIGITAL_CTRL doCH__AL_COMMAND;

	// DI ...
	CX__VAR_DIGITAL_CTRL diCH__COMM_STS;

	// SI ...
	CX__VAR_STRING_CTRL  siCH__RB_STATE_AUTO;
	CX__VAR_STRING_CTRL  siCH__RB_STATE_MANUAL;

	CX__VAR_STRING_CTRL  siCH__VERSION;
	CX__VAR_STRING_CTRL  siCH__AL_MEASUREMENT;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// OBJ : DB_CFG ...

	// AL1 ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_AL1_EXIST_FLAG;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_ALIGN_DEVICE;
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

	CString sMODE__ALIGN_PICK;
	int  Call__ALIGN_PICK(CII_OBJECT__VARIABLE* p_variable,
						  CII_OBJECT__ALARM* p_alarm,
						  const CString& arm_type,
						  const CString& stn_name,
						  const CString& stn_slot);

	// ...
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

	// ...
	CString sMODE__MAP;
	int  Call__MAP(CII_OBJECT__VARIABLE* p_variable,
				   CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__VAC_ON;
	CString sMODE__VAC_ON_OF_A_ARM;
	CString sMODE__VAC_ON_OF_B_ARM;
	int  Call__VAC_ON(CII_OBJECT__VARIABLE* p_variable,
					  CII_OBJECT__ALARM* p_alarm,
					  const CString& arm_type);

	CString sMODE__VAC_OFF;
	CString sMODE__VAC_OFF_OF_A_ARM;
	CString sMODE__VAC_OFF_OF_B_ARM;
	int  Call__VAC_OFF(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm,
					   const CString& arm_type);

	// ...
	CString sMODE__AL_INIT;
	int  Call__AL_INIT(CII_OBJECT__VARIABLE* p_variable,
					   CII_OBJECT__ALARM* p_alarm);

	CString sMODE__ALIGN;
	int  Call__ALIGN(CII_OBJECT__VARIABLE* p_variable,
					 CII_OBJECT__ALARM* p_alarm);

	// ...
	int  _Wait__RB_ACTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	int  _Wait__AL_ACTION(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	void Mon__HYPER_TERMINAL_SEND(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	// ...
	int  Get__CFG_STN_NUM(const CString& stn_name,const CString& stn_slot, CString& stn_id);	

	// ...
	int  Is__ONLINE(CII_OBJECT__ALARM* p_alarm);

	int  Fnc__ROBOT_ALARM_POST(CII_OBJECT__ALARM* p_alarm,const int alarm_id);

	// ...
	int  Drv__RECV_COMMAND(const CString& var_name, const CString& str_cmmd,const CString& str_para, CString& recv_data);
	int  Drv__SEND_COMMAND(const CString& var_name, const CString& str_cmmd,const CString& str_para);

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
	void Register__ALARM_INF(CII_DEFINE__ALARM* p_alarm);

	// ...
	int  Update__ROBOT_STATE(const CString& str_data);
	int  Update__VERSION(const CString& str_data);
	int  Update__AL_MEASUREMENT(const CString& str_data);
	//


public:
	CObj__PSK();
	~CObj__PSK();

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
