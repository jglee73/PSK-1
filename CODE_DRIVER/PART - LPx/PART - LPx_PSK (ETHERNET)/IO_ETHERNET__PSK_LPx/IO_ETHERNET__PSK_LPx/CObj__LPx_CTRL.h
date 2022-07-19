#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"
#include "CCommon_DEF.h"

#include "CObj__LPx_CTRL__DEF.h"


class CObj__LPx_CTRL : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xAPP__LOG_CTRL;

	// ...
	int iActive__SIM_MODE;
	//

	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

	// PARA ...
	CX__VAR_ANALOG_CTRL  aCH__PARA_N2_PURGE_MFC_SET;
	CX__VAR_ANALOG_CTRL  aCH__PARA_N2_PURGE_DELAY_TIME;
	CX__VAR_DIGITAL_CTRL dCH__PARA_N2_PURGE_EHHAUST_NOZZLE;

	// CFG.N2_PURGE ...
	CX__VAR_DIGITAL_CTRL dCH__CFG_PURGE_USE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PURGE_PRE_BLOW_USE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_PRE_BLOW_TIME;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PURGE_PRE_PURGE_USE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_PRE_PURGE_FLOW_SET;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_PRE_PURGE_DELAY_TIME;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PURGE_PROCESS_PURGE_USE;
	CX__VAR_DIGITAL_CTRL dCH__CFG_PURGE_POST_PURGE_USE;

	CX__VAR_DIGITAL_CTRL dCH__CFG_PURGE_STNADBY_PURGE_USE;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_STNADBY_PURGE_FLOW_SET;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_STNADBY_PURGE_DELAY_TIME;
	
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_WARNING_FLOW_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_WARNING_TIMEOUT;

	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_ALARM_FLOW_TIME;
	CX__VAR_ANALOG_CTRL  aCH__CFG_PURGE_ALARM_TIMEOUT;

	// MON.PIO ...
	CX__VAR_STRING_CTRL  sCH__MON_LPx_PIO_FA_MODE;
	CX__VAR_STRING_CTRL  sCH__MON_LPx_PIO_SERVICE_MODE;
	CX__VAR_DIGITAL_CTRL dCH__MON_LPx_PIO_RUN_SNS;
	CX__VAR_DIGITAL_CTRL dCH__MON_LPx_PIO_TRANSFER_SNS;

	// MON.STATUS ...
	CX__VAR_STRING_CTRL  sCH__MON_DOOR_STATUS;
	CX__VAR_STRING_CTRL  sCH__MON_FOUP_POS_STATUS;
	CX__VAR_STRING_CTRL  sCH__MON_FOUP_STATUS;
	CX__VAR_STRING_CTRL  sCH__MON_CLAMP_STATUS;

	// RES.MAP ...
	CX__VAR_DIGITAL_CTRL dCH__RES_MAP_SLOT_X[CFG_LPx__SLOT_SIZE];

	// MODE : PARA ...
	CX__VAR_STRING_CTRL  sCH__PARA_LP_MODE;
	CX__VAR_STRING_CTRL  sCH__PARA_LP_RFID;
	CX__VAR_STRING_CTRL  sCH__PARA_LP_USE;
	CX__VAR_STRING_CTRL  sCH__PARA_LP_CLOSE_MAPPING;

	// RSP : PARA ...
	CX__VAR_STRING_CTRL  sCH__PARA_PAGE_CID;
	CX__VAR_ANALOG_CTRL  aCH__PARA_PAGE_ID;
	CX__VAR_STRING_CTRL  sCH__PARA_PAGE_DATA;

	// RSP : PAGE ...
	CX__VAR_STRING_CTRL  sCH__RSP_PAGE_CID;
	CX__VAR_STRING_CTRL  sCH__RSP_PAGE_DATA;
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// LINK_DRIVER ...
	int iLINK__LPx_ID;
	CII_EXT_OBJECT__CTRL* pOBJ__LPx_DRIVER;

	// PARA.N2_PURGE ...
	CX__VAR_DIGITAL_CTRL  dEXT_CH__PARA_LP_N2_NOZZLE_1__VALVE;
	CX__VAR_ANALOG_CTRL   aEXT_CH__PARA_LP_N2_NOZZLE_1__MFC;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__PARA_LP_N2_NOZZLE_2__VALVE;
	CX__VAR_ANALOG_CTRL   aEXT_CH__PARA_LP_N2_NOZZLE_2__MFC;
	CX__VAR_DIGITAL_CTRL  dEXT_CH__PARA_LP_N2_NOZZLE_3__VALVE;
	CX__VAR_ANALOG_CTRL   aEXT_CH__PARA_LP_N2_NOZZLE_3__MFC;

	CX__VAR_DIGITAL_CTRL  dEXT_CH__PARA_LP_N2_EHHAUST_NOZZLE;
	CX__VAR_ANALOG_CTRL   aEXT_CH__PARA_LP_N2_DELAY_TIME;

	// MON
	CX__VAR_STRING_CTRL  sEXT_CH__MON_COMMUNICATION_STATE;

	// CFG
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_LP_MODE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_LP_RFID;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_LP_USE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__CFG_LP_CLOSE_MAPPING;

	// LP_INFO
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__ALM_TXT;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__ALM_MSG;

	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__INITIAL;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__FOUP_EXIST;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__DOOR_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__CLAMP_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__RFID_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__AGV_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__ENABLE;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__RFID_ENABLE;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__CLOSE_MAPPING_ENABLE;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__ONLINE_MODE;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__LOAD_BUTTON_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__UNLOAD_BUTTON_STATUS;

	// MAP RESULT
	CX__VAR_DIGITAL_CTRL dEXT_CH__LPx_MAP__RESULT[CFG_LPx__SLOT_SIZE];

	// IO ...
	CX__VAR_STRING_CTRL  siEXT_CH__LP_ALARM_MSG;
	CX__VAR_STRING_CTRL  siEXT_CH__LP_ALARM_TXT;

	CX__VAR_DIGITAL_CTRL doEXT_CH__LP_CMMD;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LP_MODE;
	CX__VAR_DIGITAL_CTRL doEXT_CH__PIO_RESET;

	CX__VAR_STRING_CTRL  siEXT_CH__LP_STATE;
	CX__VAR_STRING_CTRL  siEXT_CH__LP_MAP_DATA;

	CX__VAR_DIGITAL_CTRL doEXT_CH__LP_N2_RUN;
	//


	//-------------------------------------------------------------------------
	// INIT --
	CString sMODE__INIT;
	int	 Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Seq__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__HOME;
	int	 Call__HOME(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__HOME(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__DOOR_OPEN;
	int	 Call__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__DOOR_OPEN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__DOOR_CLOSE;
	int  Call__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__DOOR_CLOSE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__LOAD;
	int	 Call__LOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__LOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__UNLOAD;
	int  Call__UNLOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__UNLOAD(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__SHUTTLE_IN;
	int	 Call__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__SHUTTLE_IN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__SHUTTLE_OUT;
	int	 Call__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__SHUTTLE_OUT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CLAMP;
	int	 Call__CLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__CLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__UNCLAMP;
	int	 Call__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Fnc__UNCLAMP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__MAP;
	int	 Call__MAP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int	 Fnc__MAP(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__CID_READ;
	int	 Call__CID_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PAGE_READ;
	int	 Call__PAGE_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__CID_WRITE;
	int	 Call__CID_WRITE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__PAGE_WRITE;
	int	 Call__PAGE_WRITE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__AMHS_AUTO;
	int	 Call__AMHS_AUTO(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AMHS_MANUAL;
	int	 Call__AMHS_MANUAL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AMHS_HO_ENABLE;
	int	 Call__AMHS_HO_ENABLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__AMHS_HO_DISABLE;
	int	 Call__AMHS_HO_DISBLE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	// ...
	CString sMODE__N2_PURGE_START;
	CString sMODE__N2_PURGE_STOP;
	int	 Call__N2_PURGE_CONTROL(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm, const bool active__purge_start);

	int	 _Fnc__N2_PURGE_CONTROL(const bool active__purge_start, const CString& mfc_set,const CString& delay_sec);

	// ...
	CString sMODE__SIM_FOUP_EXIST;
	int  Call__SIM_FOUP_EXIST(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	CString sMODE__SIM_FOUP_NONE;
	int  Call__SIM_FOUP_NONE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//


	//-------------------------------------------------------------------------
	void Mon__STATE_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);

	void _Update__LPx_STATE();
	//

	//-------------------------------------------------------------------------
	// ...
	void Fnc__APP_LOG(const CString& log_msg);

	int  Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Wait__LP_STATE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__LPx_CTRL();
	~CObj__LPx_CTRL();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);

	int __DEFINE__ALARM(p_alarm);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
