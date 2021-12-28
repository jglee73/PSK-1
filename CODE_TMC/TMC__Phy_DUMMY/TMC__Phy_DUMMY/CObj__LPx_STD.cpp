#include "StdAfx.h"
#include "CObj__LPx_STD.h"


//-------------------------------------------------------------------------
CObj__LPx_STD::CObj__LPx_STD()
{

}
CObj__LPx_STD::~CObj__LPx_STD()
{

}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT,      "INIT");

		ADD__CTRL_VAR(sMODE__DOOR_OPEN, "DOOR_OPEN");
		ADD__CTRL_VAR(sMODE__CHECK_DOOR_OPEN, "CHECK_DOOR_OPEN");

		ADD__CTRL_VAR(sMODE__LOAD,      "LOAD");
		ADD__CTRL_VAR(sMODE__UNLOAD,    "UNLOAD");

		ADD__CTRL_VAR(sMODE__PREPLOAD,  "PREPLOAD");
		ADD__CTRL_VAR(sMODE__RLSUNLOAD, "RLSUNLOAD");

		ADD__CTRL_VAR(sMODE__MAP,		"MAP");
		ADD__CTRL_VAR(sMODE__CLAMP,		"CLAMP");
		ADD__CTRL_VAR(sMODE__UNCLAMP,   "UNCLAMP");
	}
	return 1;
}
int CObj__LPx_STD::__DEFINE__VERSION_HISTORY(version)
{

	return 1;
}


// ...
#define  APP_DSP__DOOR_STS				"UNKNOWN  CLOSE  OPEN"
#define  APP_DSP__FOUP_STS				"UNKNOWN  NONE   EXIST"
#define  APP_DSP__CLAMP_STS				"UNKNOWN  CLAMP  UNCLAMP"
#define  APP_DSP__FOUP_POS				"UNKNOWN  UNLOAD  LOAD"


int CObj__LPx_STD::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE;

	CString str_name;
	CString dsc_item_list;
	int i;

	// Door 
	str_name = "OTR.OUT.MON.dDOOR.STATUS";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__DOOR_STS,"");
	LINK__VAR_DIGITAL_CTRL(dCH__DOOR_STATUS,str_name);

	// Foup Exist
	str_name = "OTR.OUT.MON.dFOUP.EXIST.FLAG";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__FOUP_STS,"");
	LINK__VAR_DIGITAL_CTRL(dCH__FOUP_EXIST_FLAG,str_name);

	// Foup Clamp
	str_name = "OTR.OUT.MON.dFOUP.CLAMP.STATUS";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__CLAMP_STS,"");
	LINK__VAR_DIGITAL_CTRL(dCH__FOUP_CLAMP_STATUS,str_name);

	// Foup Position
	str_name = "OTR.OUT.MON.dFOUP.POS.STATUS";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,APP_DSP__FOUP_POS,"");
	LINK__VAR_DIGITAL_CTRL(dCH__FOUP_POS_STATUS,str_name);

	// Transfer PIO Status
	str_name = "OTR.OUT.MON.sTRANSFER.PIO.STATUS";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__TRANSFER_PIO_STATUS,str_name);

	// Foup Repload Flag
	str_name = "OTR.IN.sLP.RELOAD.FLAG";
	STD__ADD_STRING_WITH_COMMENT(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__FOUP_RELOAD_FLAG,str_name);

	// LPx FA MODE
	str_name = "OTR.IN.dLP.FA.MODE";
	STD__ADD_STRING_WITH_X_OPTION(str_name,"");
	LINK__VAR_STRING_CTRL(sCH__FA_MODE,str_name);

	// ...
	{
		p_variable->Get__STD_DESCRIPTION(DSP__SLOT_STATUS,dsc_item_list);

		for(i=0;i<CFG_LPx__SLOT_SIZE;i++)
		{
			// Slot Map
			str_name.Format("OTR.OUT.MON.dSLOT%002d.MAP.RESULT",i+1);
			STD__ADD_STRING_WITH_X_OPTION(str_name,"");
			LINK__VAR_STRING_CTRL(sCH__SLOT_MAP_RESULT[i],str_name);
		}
	}

	return 1;
}
int CObj__LPx_STD::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	
	return 1;
}

//-------------------------------------------------------------------------
int CObj__LPx_STD::__CALL__CONTROL_MODE(mode,p_debug,p_variable,p_alarm)
{
	int flag = -1;

	// ...
	{
			 IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable,p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__DOOR_OPEN)			flag = Call__DOOR_OPEN(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CHECK_DOOR_OPEN)		flag = Call__CHECK_DOOR_OPEN(p_variable,p_alarm);

		ELSE_IF__CTRL_MODE(sMODE__LOAD)					flag = Call__LOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UNLOAD)				flag = Call__UNLOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__PREPLOAD)				flag = Call__PREPLOAD(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__RLSUNLOAD)			flag = Call__RLSUNLOAD(p_variable,p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__MAP)					flag = Call__MAP(p_variable,p_alarm);
		
		ELSE_IF__CTRL_MODE(sMODE__CLAMP)				flag = Call__CLAMP(p_variable,p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__UNCLAMP)				flag = Call__UNCLAMP(p_variable,p_alarm);
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{

	}
	else
	{

	}

	return flag;
}
int CObj__LPx_STD::__CALL__MONITORING(id,p_variable,p_alarm)
{

	return 1;
}
