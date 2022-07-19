#pragma once

#include "Interface_Code.h"

#include "CCommon_Error.h"
#include "CCommon_System.h"
#include "CCommon_DEF.h"

#include "CObj__OHT_CTRL__DEF.h"


class CObj__OHT_CTRL : public __IOBJ__STD_TYPE
{
private:
	CCommon_Error__USER_FNC mERROR__USER_FNC;

	//-------------------------------------------------------------------------
	CString sObject_Name;

	SCX__USER_LOG_CTRL xLOG_CTRL;


	//-------------------------------------------------------------------------
	// INTERNAL PROPERTY

	// REPORT ...
	CX__VAR_DIGITAL_CTRL dCH__REPORT_PIO_E84_RUN_STATE;

	// USER_REQ ...
	CX__VAR_DIGITAL_CTRL dCH__USER_REQ_PIO_RESET;
	//

	//-------------------------------------------------------------------------
	// EXTERNAL PROPERTY

	// LINK DRIVER ...
	CX__VAR_STRING_CTRL  sEXT_CH__LP_INFO__AGV_STATUS;
	CX__VAR_DIGITAL_CTRL doEXT_CH__LP__PIO_RESET;

	// LINK_PIO ...
	CX__VAR_DIGITAL_CTRL dEXT_CH__LINK_PIO_TRANSFER_STATE;
	CX__VAR_DIGITAL_CTRL dEXT_CH__LINK_PIO_ACTIVE_RUN;
	CX__VAR_DIGITAL_CTRL dEXT_CH__LINK_PIO_ACTIVE_FA_AUTO;
	CX__VAR_DIGITAL_CTRL dEXT_CH__LINK_PIO_ACTIVE_LOAD_REQ;
	CX__VAR_DIGITAL_CTRL dEXT_CH__LINK_PIO_ACTIVE_UNLOAD_REQ;
	//


	//------------------------------------------------------------------------------
	// INIT ...
	CString sMODE__INIT;
	int  Call__INIT();
	//

	//------------------------------------------------------------------------------
	void Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm);
	//


public:
	CObj__OHT_CTRL();
	~CObj__OHT_CTRL();

	//-------------------------------------------------------------------------
	int __DEFINE__CONTROL_MODE(obj,l_mode);
	int __DEFINE__VERSION_HISTORY(version);

	int __DEFINE__VARIABLE_STD(p_variable);
	int __DEFINE__ALARM(p_alarm);

	int __Define__USER_FUNCTION(CII_DEFINE__FUNCTION *p_fnc_ctrl);

	//-------------------------------------------------------------------------
	int __INITIALIZE__OBJECT(p_variable,p_ext_obj_create);

	//-------------------------------------------------------------------------
	int __CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm);
	int __CALL__MONITORING(id,p_variable,p_alarm);
};
