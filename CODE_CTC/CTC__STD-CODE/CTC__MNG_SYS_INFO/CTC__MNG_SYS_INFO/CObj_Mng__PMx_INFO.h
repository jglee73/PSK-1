#pragma once

#include "Interface_Code.h"
#include "CCommon_Error.h"

#include "CObj_Mng__PMx_INFO__DEF.h"


// ...
#define  ALID__OBJECT_MODE_UNKNOWN					11


class CObj_Mng__PMx_INFO : public __IOBJ__STD_TYPE
{
private:
	//-------------------------------------------------------------------------
	CString sObject_Name;

	CCommon_Error__DEF_VARIABLE mERROR__DEF_VAR;
	CCommon_Error__USER_FNC     mERROR__USER_FNC;

	
	//-------------------------------------------------------------------------
	//  INTERNAL PROPERTY

	// PMx CTRL -----
	CX__VAR_STRING_CTRL  sCH__PMx_CTRL__SEL_ID;
	CX__VAR_STRING_CTRL  sCH__PMx_CTRL__LOCK_FLAG[CFG__PMC_SIZE];

	// PROCESS INFO -----
	CX__VAR_STRING_CTRL  sCH__PMC_PROC_LOTID;
	CX__VAR_STRING_CTRL  sCH__PMC_PROC_RECIPEID;

	CX__VAR_STRING_CTRL  sCH__PMC_PROC_CUR_TIME;
	CX__VAR_STRING_CTRL  sCH__PMC_PROC_TOTAL_TIME;

	CX__VAR_STRING_CTRL  sCH__PMC_PROC_CUR_STEP;
	CX__VAR_STRING_CTRL  sCH__PMC_PROC_TOTAL_STEP;

	//
	CX__VAR_STRING_CTRL  sCH__PMC_STEP_CUR_TIME;
	CX__VAR_STRING_CTRL  sCH__PMC_STEP_TOTAL_TIME;

	CX__VAR_STRING_CTRL  sCH__PMC_STEP_CUR_NAME;
	CX__VAR_STRING_CTRL  sCH__PMC_STEP_CUR_TYPE;

	CX__VAR_STRING_CTRL  sCH__PMC_STEP_EPD_DETECT_TIME;
	CX__VAR_STRING_CTRL  sCH__PMC_STEP_EPD_OVERETCH_TIME;
	CX__VAR_STRING_CTRL  sCH__PMC_STEP_EPD_OVERETCH_PERCENT;

	CX__VAR_STRING_CTRL  sCH__PMC_STEP_OBJ_MAIN_MSG;
	CX__VAR_STRING_CTRL  sCH__PMC_STEP_OBJ_SUB_MSG;

	// SYSTEM INFO -----
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_OBJ_STATUS;

	CX__VAR_STRING_CTRL  sCH__PMC_SYS_LIFT_PIN_STS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_CHUCK_STS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SLIT_VLV_STS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_PRC_STS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SLOT01_STATUS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_PRESSURE_STATUS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_PRESSURE_VALUE;

	CX__VAR_STRING_CTRL  sCH__PMC_SYS_RF_ON_STS;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_WAP_CUR_POS_STS;

	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_CHM_BALLAST;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_PIN_UP;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_PIN_MIDDLE;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_PIN_DOWN;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_ATM;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_VAC;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_500mTorr;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_SENSOR_100mTorr;

	CX__VAR_STRING_CTRL  sCH__PMC_SYS_APC_CUR_PRESSURE_mTORR;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_APC_CUR_POSITION_GET;
	CX__VAR_STRING_CTRL  sCH__PMC_SYS_APC_CUR_POSITION_PER;
	//

	// MFC ITEM ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MFC_NAME[CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MFC_FLOW_SET[CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MFC_FLOW_GET[CFG__MFC_SIZE];

	// RF ITEM ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RF_AC_CONTACTOR_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RF_AC_CONTACTOR_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_ON_STATUS_SET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_ON_STATUS_GET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_POWER_SET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_RAMP_SET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_FORWARD_POWER_GET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_REFLECT_POWER_GET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_MONITRING_STATUS[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_FREQUENCY_START_SET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_FREQUENCY_POWER_SET[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_RFx_FREQUENCY_POWER_GET[CFG__RF_SIZE];

	// MATCHER ITEM ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MATx_ON_STATUS[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MATx_TUNE_STATUS[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MATx_CONTROL_MODE[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MATx_CUR_LOAD_POS[CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_MATx_CUR_TUNE_POS[CFG__RF_SIZE];

	// WAP ITEM ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_WAP_POSITION_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_WAP_POSITION_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_WAP_PRESSURE_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_WAP_PRESSURE_GET;

	// TEMPERATURE ITEM ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_TOP_CHILLER_TEMP_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_TOP_CHILLER_TEMP_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_TEMP_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_TEMP_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_TOP_PLATE_TEMP_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_TOP_PLATE_TEMP_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_ANAFAZER_TOP_TEMP_GET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ANAFAZER_TOP_BOTTOM_GET;

	// ESC ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_TOTAL_VOLT_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_TOTAL_VOLT_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_BIAS_VOLT_SET;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_BIAS_VOLT_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_COOLANT_GET;

	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_POWER_ON_STATUS;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_REVERSE_POLARITY_STATUS;
	CX__VAR_STRING_CTRL  sCH__PMC_PART_ESC_COOLANT_FLOW_STATUS;

	// He CTRL : Inner / Outer ...
	CX__VAR_STRING_CTRL  sCH__PMC_PART_He_CTRL_PRESSURE_SET[CFG__He_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_He_CTRL_PRESSURE_GET[CFG__He_SIZE];
	CX__VAR_STRING_CTRL  sCH__PMC_PART_He_CTRL_FLOW_GET[CFG__He_SIZE];
	//


	//-------------------------------------------------------------------------
	//  EXTERNAL PROPERTY

	int iPMC_SIZE;

	// OBJ__DB ...
	CX__VAR_DIGITAL_CTRL xEXT_CH__PMx_USE_FLAG[CFG__PMC_SIZE];

	// OBJ__PMC ...
	// PROC INFO 
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROC_LOTID[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROC_RECIPEID[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROC_CUR_TIME[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROC_TOTAL_TIME[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROC_CUR_STEP[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PROC_TOTAL_STEP[CFG__PMC_SIZE];

	//
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_CUR_TIME[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_TOTAL_TIME[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_CUR_NAME[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_CUR_TYPE[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_EPD_DETECT_TIME[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_EPD_OVERETCH_TIME[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_EPD_OVERETCH_PERCENT[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_OBJ_MAIN_MSG[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_STEP_OBJ_SUB_MSG[CFG__PMC_SIZE];

	// SYSTEM INFO
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_OBJ_STATUS[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_LIFT_PIN_STS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_CHUCK_STS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SLIT_VLV_STS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_PRC_STS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SLOT01_STATUS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_PRESSURE_STATUS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_PRESSURE_VALUE[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_RF_ON_STS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_WAP_CUR_POS_STS[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_CHM_BALLAST[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_PIN_UP[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_PIN_MIDDLE[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_PIN_DOWN[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_ATM[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_VAC[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_500mTorr[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_SENSOR_100mTorr[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_APC_CUR_PRESSURE_mTORR[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_APC_CUR_POSITION_GET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_SYS_APC_CUR_POSITION_PER[CFG__PMC_SIZE];

	// MFC ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MFC_NAME[CFG__PMC_SIZE][CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MFC_FLOW_SET[CFG__PMC_SIZE][CFG__MFC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MFC_FLOW_GET[CFG__PMC_SIZE][CFG__MFC_SIZE];

	// RF ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RF_AC_CONTACTOR_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RF_AC_CONTACTOR_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_ON_STATUS_SET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_ON_STATUS_GET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_POWER_SET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_RAMP_SET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_FORWARD_POWER_GET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_REFLECT_POWER_GET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_MONITRING_STATUS[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_FREQUENCY_START_SET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_FREQUENCY_POWER_SET[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_RFx_FREQUENCY_POWER_GET[CFG__PMC_SIZE][CFG__RF_SIZE];

	// MATCHER ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MATx_ON_STATUS[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MATx_TUNE_STATUS[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MATx_CONTROL_MODE[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MATx_CUR_LOAD_POS[CFG__PMC_SIZE][CFG__RF_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_MATx_CUR_TUNE_POS[CFG__PMC_SIZE][CFG__RF_SIZE];

	// WAP ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_WAP_POSITION_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_WAP_POSITION_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_WAP_PRESSURE_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_WAP_PRESSURE_GET[CFG__PMC_SIZE];

	// TEMPERATURE ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_TOP_CHILLER_TEMP_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_TOP_CHILLER_TEMP_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_TEMP_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_TEMP_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_TOP_PLATE_TEMP_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_TOP_PLATE_TEMP_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ANAFAZER_TOP_TEMP_GET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ANAFAZER_TOP_BOTTOM_GET[CFG__PMC_SIZE];

	// ESC ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_TOTAL_VOLT_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_TOTAL_VOLT_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_BIAS_VOLT_SET[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_BIAS_VOLT_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_COOLANT_GET[CFG__PMC_SIZE];

	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_POWER_ON_STATUS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_REVERSE_POLARITY_STATUS[CFG__PMC_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_ESC_COOLANT_FLOW_STATUS[CFG__PMC_SIZE];

	// He Inner / Outer - ITEM ...
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_He_CTRL_PRESSURE_SET[CFG__PMC_SIZE][CFG__He_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_He_CTRL_PRESSURE_GET[CFG__PMC_SIZE][CFG__He_SIZE];
	CX__VAR_STRING_CTRL  sEXT_CH__PMC_PART_He_CTRL_FLOW_GET[CFG__PMC_SIZE][CFG__He_SIZE];
	//

	// ...
	void Mon__INFO_CTRL(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm);
	//


public:
	CObj_Mng__PMx_INFO();
	~CObj_Mng__PMx_INFO();

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
