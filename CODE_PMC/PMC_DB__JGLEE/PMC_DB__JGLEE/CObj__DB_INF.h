#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"


#define DEF_SIZE__DECHUCK_PROCESS				10


class CObj__DB_INF : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;


	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	//  PMC --> CTC
	CX__VAR_DIGITAL_CTRL dCH__CHM_PRC_STS;
	CX__VAR_STRING_CTRL  sCH__CHM_PRC_TOTAL_TIME_TO_CTC;
	CX__VAR_STRING_CTRL  sCH__CHM_PRC_CHANGE_TIME_TO_CTC;

	CX__VAR_STRING_CTRL  sCH__CHM_PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  xCH__CHM_VAC_SNS;
	CX__VAR_STRING_CTRL  xCH__CHM_ATM_SNS;

	CX__VAR_STRING_CTRL  sCH__PMC_PROCESS_STATUS;

	CX__VAR_STRING_CTRL  xCH__SHUTTER_STATUS;
	CX__VAR_STRING_CTRL  xCH__LIFT_PIN_STATUS;
	CX__VAR_STRING_CTRL  xCH__RF_ON_STS;
	CX__VAR_STRING_CTRL  xCH__CHM_STAGE_REPORT_TO_CTC;

	CX__VAR_STRING_CTRL  sCH__CHM_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL  sCH__CHM_PRESSURE_mTORR;
	
	CX__VAR_STRING_CTRL  sCH__PMP_PRESSURE_VALUE;
	CX__VAR_STRING_CTRL  sCH__PMP_PRESSURE_STATE;
	CX__VAR_STRING_CTRL  sCH__PMP_VAC_SNS;

	CX__VAR_DIGITAL_CTRL dCH__CFG_DECHUCK_CTRL_MODE;
	CX__VAR_STRING_CTRL  sCH__CFG_DECHUCK_RECIPE_ABORT;
	CX__VAR_STRING_CTRL  sCH__CFG_DECHUCK_RECIPE_PROCESS_X[DEF_SIZE__DECHUCK_PROCESS];

	//  PMC <-> CTC
	CX__VAR_STRING_CTRL  xCH__TOTAL_PRC_TIME;
	CX__VAR_STRING_CTRL  xCH__CHANGE_PRC_TIME;

	//  PMC <-- CTC
	CX__VAR_DIGITAL_CTRL xCH__CFG_TRANSFER_MODE;
	CX__VAR_STRING_CTRL  xCH__CFG_REF_ATM_PRESSURE;
	CX__VAR_STRING_CTRL  xCH__CFG_REF_VAC_PRESSURE;

	CX__VAR_STRING_CTRL  xCH__MODULE_TIME;
	CX__VAR_DIGITAL_CTRL xCH__SLIT_VLV_STS;
	CX__VAR_DIGITAL_CTRL xCH__SLOT_NO;

	CX__VAR_STRING_CTRL  xCH__RECIPE;
	CX__VAR_STRING_CTRL  xCH__RECIPE_WITHOUT_FOLDER_NAME;
	CX__VAR_STRING_CTRL  xCH__LOTID;
	CX__VAR_STRING_CTRL  xCH__MATERIALID;

	CX__VAR_DIGITAL_CTRL xCH__SLOT01_STATUS;
	CX__VAR_STRING_CTRL  xCH__SLOT01_TITLE;

	CX__VAR_STRING_CTRL  xCH__SLOT01_PORTID;
	CX__VAR_STRING_CTRL  xCH__SLOT01_SLOTID;

	CX__VAR_STRING_CTRL  xCH__PMC_PROC_READY_FLAG;

	// PMC <-- TMC
	CX__VAR_STRING_CTRL  xCH__TMC_LINK_TEST_FLAG;

	CX__VAR_STRING_CTRL  xCH__TMC_ROBOT_ARM_STATE;


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	// ...
	void Mon__UPDATE_INFO(CII_OBJECT__VARIABLE *p_variable);
	//


public:
	CObj__DB_INF();
	~CObj__DB_INF();

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
