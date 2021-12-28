#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"
#include "CCommon_DEF.h"

#include "CObj__RFID_CTRL__DEF.h"


class CObj__RFID_CTRL : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString	sObject_Name;

	// ...
	CCommon_Error__USER_FNC mERROR__USER_FNC;	

	SCX__USER_LOG_CTRL xAPP__LOG_CTRL;

	// ...
	bool bActive__SIM_MODE;
	//


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// OBJ ...
	CX__VAR_DIGITAL_CTRL dCH__OBJ_STATUS;
	CX__VAR_STRING_CTRL  sCH__OBJ_MSG;

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

	// MON
	CX__VAR_STRING_CTRL  sEXT_CH__MON_COMMUNICATION_STATE;

	// PARA 
	CX__VAR_ANALOG_CTRL  aEXT_CH__PARA_RFID_PAGE_ID;

	// LP_INFO
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__RFID_STATUS;
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__RFID_RSP;

	// IO
	CX__VAR_STRING_CTRL  siEXT_CH__RFID_READ;
	CX__VAR_STRING_CTRL  soEXT_CH__RFID_WRITE;
	//


	//-------------------------------------------------------------------------
	// ...
	CString sMODE__INIT;
	int	 Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

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
	int  Is__ONLINE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);

	int  Wait__RFID_READ(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	int  Wait__RFID_WRITE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__RFID_CTRL();
	~CObj__RFID_CTRL();

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
