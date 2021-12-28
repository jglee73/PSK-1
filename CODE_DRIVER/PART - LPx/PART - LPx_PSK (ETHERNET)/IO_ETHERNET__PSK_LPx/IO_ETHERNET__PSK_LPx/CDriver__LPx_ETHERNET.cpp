#include "StdAfx.h"
#include "CDriver__LPx_ETHERNET.h"
#include "CDriver__LPx_ETHERNET__DEF.h"
#include "CDriver__LPx_ETHERNET__ALID.h"

#include "CCommon_DEF.h"


//--------------------------------------------------------------------------------
CDriver__LPx_ETHERNET::CDriver__LPx_ETHERNET()
{
	m_nCommState = ONLINE;
}
CDriver__LPx_ETHERNET::~CDriver__LPx_ETHERNET()
{

}

//--------------------------------------------------------------------------------
int CDriver__LPx_ETHERNET::__DEFINE__CONTROL_MODE(obj,l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");	

		ADD__CTRL_VAR(sMODE__CHECK_CMMD,     "CHECK.CMMD");
		ADD__CTRL_VAR(sMODE__CHECK_ERR_CODE, "CHECK.ERR_CODE");

		ADD__CTRL_VAR(sMODE__CHECK_LPx_STATE, "CHECK.LPx_STATE");
	}
	return 1;
}
int CDriver__LPx_ETHERNET::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee \n";

	return 1;
}


// ...
#define  MON_ID__IO_MONITOR									1
#define  MON_ID__RECV_PROC									2


// ...
#define APP_DSP__LP_WFR_SLOT_STS							\
"UNKNOWN INVALID ABSENT PRESENT DOUBLE CROSSED"

#define APP_DSP__DSlot										\
"1  2  3  4  5  6  7  8  9  10								\
11 12 13 14 15 16 17 18 19 20								\
21 22 23 24 25 26 27 28 29 30"


int CDriver__LPx_ETHERNET::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	CString str_list;
	int i;


	// DRV ...
	{
		str_list = "DRV.CANCEL_CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__DRV_CANCEL_CODE, str_name);
	}

	// MON ...
	{
		str_name = "MON.COMMUNICATION.STATE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__MON_COMMUNICATION_STATE, str_name);
	}

	// PARA ...
	{
		// LAMP & BUZZER ...
		{
			str_list = "OFF  ON  BLINK";

			str_name = "PARA.LAMP_RED";
			STD__ADD_DIGITAL(str_name, str_list);
			LINK__VAR_DIGITAL_CTRL(dCH__PARA_LAMP_RED, str_name);

			str_name = "PARA.LAMP_YELLOW";
			STD__ADD_DIGITAL(str_name, str_list);
			LINK__VAR_DIGITAL_CTRL(dCH__PARA_LAMP_YELLOW, str_name);

			str_name = "PARA.LAMP_GREEN";
			STD__ADD_DIGITAL(str_name, str_list);
			LINK__VAR_DIGITAL_CTRL(dCH__PARA_LAMP_GREEN, str_name);

			str_name = "PARA.LAMP_BLUE";
			STD__ADD_DIGITAL(str_name, str_list);
			LINK__VAR_DIGITAL_CTRL(dCH__PARA_LAMP_BLUE, str_name);

			//
			str_name = "PARA.ALARM_BUZZER";
			STD__ADD_DIGITAL(str_name, "OFF  ON.1  ON.2");
			LINK__VAR_DIGITAL_CTRL(dCH__PARA_ALARM_BUZZER, str_name);
		}

		// LP_PARA ...
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("PARA.RFID.PAGE_ID.%1d", id);
			STD__ADD_ANALOG(str_name, "page", 0, 0, 17);
			LINK__VAR_ANALOG_CTRL(aCH__PARA_RFID_PAGE_ID_X[i], str_name);
		}
	}

	// CFG ...
	{
		str_name = "CFG.COMM_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "EVENT  POLLING", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_COMM_MODE, str_name);

		//
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.LP_MODE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "MANUAL  AMHS", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_MODE_X[i], str_name);

			str_name.Format("CFG.LP_RFID.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "DISABLE  ENABLE", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_RFID_X[i], str_name);

			str_name.Format("CFG.LP_USE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO  YES", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_USE_X[i], str_name);

			str_name.Format("CFG.LP_CLOSE_MAPPING.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "NO  YES", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_CLOSE_MAPPING_X[i], str_name);
		}

		// N2 ...
		for(i=0; i<CFG_LPx__SIZE; i++)
		{
			int id = i + 1;

			str_name.Format("CFG.LP_N2_NOZZLE_1.VALVE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "0  1  2  3", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_N2_NOZZLE_1__VALVE_X[i], str_name);

			str_name.Format("CFG.LP_N2_NOZZLE_1.MFC.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LP_N2_NOZZLE_1__MFC_X[i], str_name);

			str_name.Format("CFG.LP_N2_NOZZLE_2.VALVE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "0  1  2  3", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_N2_NOZZLE_2__VALVE_X[i], str_name);

			str_name.Format("CFG.LP_N2_NOZZLE_2.MFC.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LP_N2_NOZZLE_2__MFC_X[i], str_name);

			str_name.Format("CFG.LP_N2_NOZZLE_3.VALVE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "0  1  2  3", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_N2_NOZZLE_3__VALVE_X[i], str_name);

			str_name.Format("CFG.LP_N2_NOZZLE_3.MFC.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sccm", 0, 0, 100, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LP_N2_NOZZLE_3__MFC_X[i], str_name);

			//
			str_name.Format("CFG.LP_N2_EHHAUST_NOZZLE.%1d", id);
			STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "0FF  ON", "");
			LINK__VAR_DIGITAL_CTRL(dCH__CFG_LP_N2_EHHAUST_NOZZLE_X[i], str_name);

			str_name.Format("CFG.LP_N2_DELAY_TIME.%1d", id);
			STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 0, 300, "");
			LINK__VAR_ANALOG_CTRL(aCH__CFG_LP_N2_DELAY_TIME_X[i], str_name);
		}
	}

	// PIO_TP INFO ...
	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		int id = i + 1;

		str_name.Format("PIO_INFO.TP%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PIO_INFO__TP_X[i], str_name);
	}

	// LPx INFO ...
	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		int id = i + 1;

		//
		str_name.Format("LP_INFO.ALM_TXT.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__ALM_TXT_X[i], str_name);

		str_name.Format("LP_INFO.ALM_MSG.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__ALM_MSG_X[i], str_name);

		//
		str_name.Format("LP_INFO.RFID_RSP.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__RFID_RSP_X[i], str_name);

		//
		str_name.Format("LP_INFO.INITIAL.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__INITIAL_X[i], str_name);

		str_name.Format("LP_INFO.STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__STATUS_X[i], str_name);

		str_name.Format("LP_INFO.FOUP_EXIST.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__FOUP_EXIST_X[i], str_name);

		str_name.Format("LP_INFO.DOOR_STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__DOOR_STATUS_X[i], str_name);

		str_name.Format("LP_INFO.CLAMP_STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__CLAMP_STATUS_X[i], str_name);

		str_name.Format("LP_INFO.RFID_STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__RFID_STATUS_X[i], str_name);

		str_name.Format("LP_INFO.AGV_STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__AGV_STATUS_X[i], str_name);

		str_name.Format("LP_INFO.ENABLE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__ENABLE_X[i], str_name);

		str_name.Format("LP_INFO.RFID_ENABLE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__RFID_ENABLE_X[i], str_name);

		str_name.Format("LP_INFO.CLOSE_MAPPING_ENABLE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__CLOSE_MAPPING_ENABLE_X[i], str_name);

		str_name.Format("LP_INFO.ONLINE_MODE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__ONLINE_MODE_X[i], str_name);

		str_name.Format("LP_INFO.LOAD_BUTTON_STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__LOAD_BUTTON_STATUS_X[i], str_name);

		str_name.Format("LP_INFO.UNLOAD_BUTTON_STATUS.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__UNLOAD_BUTTON_STATUS_X[i], str_name);

		//
		str_name.Format("LP_INFO.PIO_INPUT.HIGH_WORD.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT_HIGH_WORD_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_7.CONT.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_7__CONT_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_6.COMPTT.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_6__COMPTT_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_5.BUSY.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_5__BUSY_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_4.TR_REQ.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_4__TR_REQ_X[i], str_name);

		//
		str_name.Format("LP_INFO.PIO_INPUT.LOW_WORD.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT_LOW_WORD_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_3.NC.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_3__NC_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_2.CS_1.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_2__CS_1_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_1.CS_0.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_1__CS_0_X[i], str_name);

		str_name.Format("LP_INFO.PIO_INPUT.BIT_0.VALID.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_INPUT__BIT_0__VALID_X[i], str_name);

		//
		str_name.Format("LP_INFO.PIO_OUTPUT.HIGH_WORD.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT_HIGH_WORD_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_7.ES.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_7__ES_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_6.HO_AVBL.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_6__HO_AVBL_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_5.NC.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_5__NC_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_4.NC.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_4__NC_X[i], str_name);

		//
		str_name.Format("LP_INFO.PIO_OUTPUT.LOW_WORD.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT_LOW_WORD_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_3.READY.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_3__READY_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_2.NC_2.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_2__NC_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_1.U_REQ.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_1__U_REQ_X[i], str_name);

		str_name.Format("LP_INFO.PIO_OUTPUT.BIT_0.L_REQ.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__PIO_OUTPUT__BIT_0__L_REQ_X[i], str_name);

		//
		str_name.Format("LP_INFO.FOUP_TYPE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__LP_INFO__FOUP_TYPE_X[i], str_name);
	}

	// MAP RESULT ...
	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		int id = i + 1;

		for(int k=0; k<CFG_LPx__SLOT_SIZE; k++)
		{
			int slot = k + 1;

			str_name.Format("LP_MAP.RESULT.%1d.SLOT%02d", id, slot);
			STD__ADD_DIGITAL_WITH_COMMENT(str_name,APP_DSP__LP_WFR_SLOT_STS,"");
			LINK__VAR_DIGITAL_CTRL(dCH__LPx_MAP__RESULT_XY[i][k], str_name);
		}
	}

	// N2 STATUS ...
	for(i=0; i<CFG_LPx__SIZE; i++)
	{
		int id= i + 1;

		str_name.Format("N2_INFO.TIME.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__TIME_X[i], str_name);

		//
		str_name.Format("N2_INFO.NOZZLE_1.FLOW.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_1__FLOW_X[i], str_name);

		str_name.Format("N2_INFO.NOZZLE_2.FLOW.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_2__FLOW_X[i], str_name);

		str_name.Format("N2_INFO.NOZZLE_3.FLOW.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_3__FLOW_X[i], str_name);

		//
		str_name.Format("N2_INFO.NOZZLE_1.PRESSURE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_1__PRESSURE_X[i], str_name);

		str_name.Format("N2_INFO.NOZZLE_2.PRESSURE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_2__PRESSURE_X[i], str_name);

		str_name.Format("N2_INFO.NOZZLE_3.PRESSURE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_3__PRESSURE_X[i], str_name);

		str_name.Format("N2_INFO.NOZZLE_4.PRESSURE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__NOZZLE_4__PRESSURE_X[i], str_name);

		//
		str_name.Format("N2_INFO.OXYGEN.DENSITY.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__OXYGEN_DENSITY_X[i], str_name);

		//
		str_name.Format("N2_INFO.CASSETTE.TYPE.%1d", id);
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__N2_INFO__CASSETTE_TYPE_X[i], str_name);
	}

	// Simulation ...
	{
		str_name = "SIM.CFG.REAL.TEST";
		STD__ADD_DIGITAL(str_name, "NO YES");
		LINK__VAR_DIGITAL_CTRL(dCH__SIM_CFG__REAL_TEST, str_name);

		str_name = "SIM.CFG.ALIGN.TIME";
		STD__ADD_STRING_WITH_X_OPTION(str_name, "");
		LINK__VAR_STRING_CTRL(sCH__SIM_CFG__ALIGN_TIME, str_name);
	}

	// ...
	{
		str_name = "INR.RB1.ACT.MSG";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__ACT_MSG, str_name);

		str_name = "INR.sERROR.ID.DEC";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INR__ERROR_ID_DEC,str_name);

		str_name = "INR.sERROR.ID.HEXA";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INR__ERROR_ID_HEXA,str_name);

		str_name = "INR.sALGINER.ERROR.ID";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__INR__ALGINER_ERROR_ID,str_name);

		str_name = "INR.FLAG.dALGN.STS";
		STD__ADD_DIGITAL(str_name, "ALIGNING ALIGNED");
		LINK__VAR_DIGITAL_CTRL(dCH__INR_FLAG__ALGN_STS,str_name);
	}

	// CONFIG CHANNEL ...
	{
		str_name = "CFG.ACTION.CONFIRM.FLAG";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"DISABLE ENABLE","");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG_ACTION_CONFIRM_FLAG,str_name);
	}

	// ATMPickTime
	str_name = "CFG.aPICK.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:4.2 sec");
	LINK__VAR_ANALOG_CTRL(aCH__CFG__PICK_TIMEOUT, str_name);

	// ATMPlaceTime
	str_name = "CFG.aPLACE.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name,"sec",1,0.5,100.0,"recommand:4.4 sec");
	LINK__VAR_ANALOG_CTRL(aCH__CFG__PLACE_TIMEOUT, str_name);

	// CheckWaferSlideOut
	str_name = "CFG.dMAPPING.ACTION.SLIDEOUT.CHECK";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"NO YES","");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_MAPPING_ACTION_SLIDE_OUT_CHECK,str_name);

	// ...
	str_name = "CFG.aPADDLE.DOWN.CHECK.TIMEOUT";
	STD__ADD_ANALOG_WITH_X_OPTION(str_name, "sec", 0, 1, 12, "rec:2");
	LINK__VAR_ANALOG_CTRL(aCH__CFG_LP__PADDLE_CHECK_TIME,str_name);

	// ...
	str_name = "CFG.dMAPPING.DISABLE";
	STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
	LINK__VAR_DIGITAL_CTRL(dCH__CFG_MAPPING_DISABLE,str_name);


	// CHECK CMMD & ERR_CODE
	{
		str_name = "PARA.CHECK.CMMD";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_CHECK_CMMD, str_name);

		str_name = "PARA.CHECK.ERR_CODE";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__PARA_CHECK_ERR_CODE, str_name);
	}

	// TEST PARA ...
	{
		str_name = "TEST_PARA.LPx.ID";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"1 2 3","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_PARA_LPx_ID, str_name);

		// 1.
		str_name = "TEST_STATE.LPx_INITAL";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__LPx_INITAL, str_name);

		// 2.
		str_name = "TEST_STATE.LPx_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3 4","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__LPx_STATUS, str_name);

		// 3.
		str_name = "TEST_STATE.FOUP_EXIST";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__FOUP_EXIST, str_name);

		// 4.
		str_name = "TEST_STATE.DOOR_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__DOOR_STATUS, str_name);

		// 5.
		str_name = "TEST_STATE.CLAMP_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__CLAMP_STATUS, str_name);

		// 6.
		str_name = "TEST_STATE.RFID_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3 4 5 6","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__RFID_STATUS, str_name);

		// 7.
		str_name = "TEST_STATE.AGV_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 3 4","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__AGV_STATUS, str_name);

		// 8.
		str_name = "TEST_STATE.LPx_ENABLE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__LPx_ENABLE, str_name);

		// 9.
		str_name = "TEST_STATE.RFID_ENABLE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__RFID_ENABLE, str_name);

		// 10.
		str_name = "TEST_STATE.CLOSE_MAPPING_ENABLE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__CLOSE_MAPPING_ENABLE, str_name);

		// 11.
		str_name = "TEST_STATE.ONLINE_MODE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__ONLINE_MODE, str_name);

		// 12.
		str_name = "TEST_STATE.LOAD_BUTTON_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__LOAD_BUTTON_STATUS, str_name);

		// 13.
		str_name = "TEST_STATE.UNLOAD_BUTTON_STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__UNLOAD_BUTTON_STATUS, str_name);

		// 14.
		str_name = "TEST_STATE.PIO_INPUT_HIGH_WORD";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3 4 5 6 7 8 9 A B C D E F","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__PIO_INPUT_HIGH_WORD, str_name);

		// 15.
		str_name = "TEST_STATE.PIO_INPUT_LOW_WORD";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3 4 5 6 7 8 9 A B C D E F","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__PIO_INPUT_LOW_WORD, str_name);

		// 16.
		str_name = "TEST_STATE.PIO_OUTPUT_HIGH_WORD";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3 4 5 6 7 8 9 A B C D E F","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__PIO_OUTPUT_HIGH_WORD, str_name);

		// 17.
		str_name = "TEST_STATE.PIO_OUTPUT_LOW_WORD";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3 4 5 6 7 8 9 A B C D E F","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__PIO_OUTPUT_LOW_WORD, str_name);

		// 18.
		str_name = "TEST_STATE.FOUP_TYPE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name,"0 1 2 3","");
		LINK__VAR_DIGITAL_CTRL(dCH__TEST_STATE__FOUP_TYPE, str_name);
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__IO_MONITOR);
		p_variable->Add__MONITORING_PROC(1.0, MON_ID__RECV_PROC);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");

#define  ACT__ABORT_ALARM						\
l_act.RemoveAll();								\
l_act.Add("ABORT");

#define  ACT__NO_YES_ALARM						\
l_act.RemoveAll();								\
l_act.Add("NO");								\
l_act.Add("YES");


int CDriver__LPx_ETHERNET::__DEFINE__ALARM(p_alarm)
{
	DECLARE__ALARM;

	// ...
	CString title;
	title.Format("%s - ",sObject_Name);

	CString alarm_title;
	CString alarm_msg;
	CString alarm_bff;
	CStringArray l_act;
	int alarm_id;
	int i;

	// ...
	{
		alarm_id = ALID__OFFLINE_ALARM;

		alarm_title  = title;
		alarm_title += "Offline.";

		alarm_msg  = "Controller is Offline.\n";
		alarm_msg += "Please, Check Communication Status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__ERROR_CODE_POPUP;

		alarm_title  = title;
		alarm_title += "Error Code !";

		alarm_msg = "Please, check HW status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__ABORT);
		l_act.Add(ACT__RETRY);
		l_act.Add(ACT__IGNORE);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}
	// ...
	{
		alarm_id = ALID__ERROR_CODE_POST;

		alarm_title  = title;
		alarm_title += "Error Code !";

		alarm_msg = "Please, check HW status !\n";

		l_act.RemoveAll();
		l_act.Add(ACT__CHECK);

		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);	
	}

	// ...
	{
		alarm_id = ALID__ALGN_AND_PICK_TIMEOUT_ALARM;

		alarm_title  = title;
		alarm_title += "Align and Pick Action Timeout Occur.";

		alarm_msg  = "Align and Pick Action Timeout Occur.\n";
		alarm_msg += "Please, Check ATM Robot Status !\n";

		ACT__ABORT_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__MAPPING_DISABLE_CONFIG_ALARM;

		alarm_title  = title;
		alarm_title += "Config Option, Mapping Disable Alarm.";

		alarm_msg  = "Now, Mapping Disable Config Option Selected.\n";
		alarm_msg += "Would you like to continue ??\n";

		ACT__NO_YES_ALARM;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


// ...
#define APP_DSP__Arm_ID				"A  B"
#define APP_DSP__Wfr    			"Unknown  Absent  Present"
#define APP_DSP__StrLoc 			"Normal  Retract2  NoRetract"
#define APP_DSP__Axises				"ALL  R  T  Z  W  S"

#define APP_DSP__Stn									\
"1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__CurStn									\
"0														\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__DDnUp				"DN  UP"
#define APP_DSP__OffOn              "OFF ON"
#define APP_DSP__RetExt             "RE  EX"
#define APP_DSP__ComSts             "Offline Online"
#define APP_DSP__YesNo              "Y   N"
#define APP_DSP__PrsAbs				"ON  OFF"
#define APP_DSP__ALWfr				"?  NO  YES"

#define APP_DSP__Material								\
"? 0 1 2 3 4 5 6 7 20 21 22 23 FP"

#define APP_DSP__Substrates								\
"1 2 3 4 5 6 7 20 21 22 23"

#define APP_DSP__FDCLs				"None  Flat  Ntch"
#define APP_DSP__WfrShapes			"Round  Square"
#define APP_DSP__CCDPos				"1  2  3"
#define APP_DSP__DOffOn				"Off  On"
#define APP_DSP__DZPos				"Unknown  Up  Down"
#define APP_DSP__DRPos				"Unknown  Retract  Extend"

#define APP_DSP__DTPos									\
"Unknown												\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"

#define APP_DSP__DSPos									\
"Unknown												\
1  2  3  4  5  6  7  8  9  10							\
11 12 13 14 15 16 17 18 19 20							\
21 22 23 24 25 26 27 28 29 30"


int CDriver__LPx_ETHERNET::__DEFINE__VARIABLE_IO(p_io_variable)
{
	DECLARE__IO_VARIABLE;

	CString str_name;
	CString str_list;
	int i;

	// Digital ...
	{
		// AO  ----------
		{
			// PIO TP ... 
			{
				for(i=0; i<CFG_LPx__SIZE; i++)
				{
					int id = i + 1;

					str_name.Format("ao.PIO.TP%1d", id);
					IO__ADD_ANALOG_WRITE(str_name, "sec", 0, 1, 999);
					LINK__IO_VAR_ANALOG_CTRL(aoCH__PIO_TP_X[i], str_name);
				}
			}
		}

		// DO  -----------------------------
		{
			// EFEM_MODE ...
			{
				str_name = "do.EFEM_MODE";
				IO__ADD_DIGITAL_WRITE(str_name, "SET");
				LINK__IO_VAR_DIGITAL_CTRL(doCH__EFEM_MODE, str_name);
			}
			// LAMP & BUZZER ...
			{
				str_name = "do.EFEM_LAMP_BUZZER";
				IO__ADD_DIGITAL_WRITE(str_name, "SET");
				LINK__IO_VAR_DIGITAL_CTRL(doCH__EFEM_LAMP_BUZZER, str_name);
			}

			// LP_MODE ...
			for(i=0; i<CFG_LPx__SIZE; i++)
			{
				str_name.Format("do.LP_MODE.%1d", i+1);
				IO__ADD_DIGITAL_WRITE(str_name, "SET");
				LINK__IO_VAR_DIGITAL_CTRL(doCH__LP_MODE_X[i], str_name);
			}
			// LP_CMMD ...
			{
				str_list  = _CMD__INIT;
				str_list += " ";
				str_list += _CMD__LOAD;
				str_list += " ";
				str_list += _CMD__UNLOAD;
				str_list += " ";
				str_list += _CMD__OPEN;
				str_list += " ";
				str_list += _CMD__CLOSE;
				str_list += " ";
				str_list += _CMD__CLAMP;
				str_list += " ";
				str_list += _CMD__UNCLAMP;

				for(i=0; i<CFG_LPx__SIZE; i++)
				{
					str_name.Format("do.LP_CMMD.%1d", i+1);
					IO__ADD_DIGITAL_WRITE(str_name, str_list);
					LINK__IO_VAR_DIGITAL_CTRL(doCH__LP_CMMD_X[i], str_name);
				}
			}

			// PIO RESET ...
			for(i=0; i<CFG_LPx__SIZE; i++)
			{
				str_name.Format("do.PIO.RESET.%1d", i+1);
				IO__ADD_DIGITAL_WRITE(str_name, "SET");
				LINK__IO_VAR_DIGITAL_CTRL(doCH__PIO_RESET_X[i], str_name);
			}

			// N2_RUN ...
			for(i=0; i<CFG_LPx__SIZE; i++)
			{
				str_name.Format("do.LP_N2_RUN.%1d", i+1);
				IO__ADD_DIGITAL_WRITE(str_name, "STOP START");
				LINK__IO_VAR_DIGITAL_CTRL(doCH__LP_N2_RUN_X[i], str_name);
			}
		}

		// DI  -----------------------------
		{
			str_name = "di.ComSts";
			IO__ADD_DIGITAL_READ(str_name, APP_DSP__ComSts);
			LINK__IO_VAR_DIGITAL_CTRL(diCH__COMM_STS, str_name);
		}
	}

	// String ...
	{
		// SO  -----------------------------
		{
			str_name = "so.Check.Cmmd";
			IO__ADD_STRING_WRITE(str_name);
			LINK__IO_VAR_STRING_CTRL(soCH__CHECK_CMMD, str_name);

			//
			for(i=0; i<CFG_LPx__SIZE; i++)
			{
				int id = i + 1;

				str_name.Format("so.RFID_WRITE.%1d", id);
				IO__ADD_STRING_WRITE(str_name);
				LINK__IO_VAR_STRING_CTRL(soCH__RFID_WRITE_X[i], str_name);
			}
		}

		// SI  -----------------------------
		{
			// PIO_TP INFO ...
			{
				str_name = "si.PIO_TP.INFO";
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__PIO_TP_INFO, str_name);
			}

			//
			for(i=0; i<CFG_LPx__SIZE; i++)
			{
				int id = i + 1;

				str_name.Format("si.LP_STATE.%1d", id);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__LP_STATE_X[i], str_name);

				str_name.Format("si.LP_MAP_DATA.%1d", id);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__LP_MAP_DATA_X[i], str_name);

				//
				str_name.Format("si.LP_ALARM_MSG.%1d", id);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__LP_ALARM_MSG_X[i], str_name);

				str_name.Format("si.LP_ALARM_TXT.%1d", id);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__LP_ALARM_TXT_X[i], str_name);

				//
				str_name.Format("si.LP_N2_STATUS.%1d", id);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__LP_N2_STATUS_X[i], str_name);

				//
				str_name.Format("si.RFID_READ.%1d", id);
				IO__ADD_STRING_READ__MANUAL(str_name);
				LINK__IO_VAR_STRING_CTRL(siCH__RFID_READ_X[i], str_name);
			}
		}
	}

	return 1;
}

//--------------------------------------------------------------------------------
int CDriver__LPx_ETHERNET::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// APP LOG ...
	{
		iFlag__APP_LOG = 1;

		// ...
		CString file_name;
		CString log_msg;

		file_name.Format("%s_App.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xAPP_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xAPP_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xAPP_LOG_CTRL->DISABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);

		xAPP_LOG_CTRL->ENABLE__TIME_LOG();
		xAPP_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	// DRV LOG ...
	{
		iFlag__DRV_LOG = 1;

		// ...
		CString file_name;
		CString log_msg;

		file_name.Format("%s_Drv.log", sObject_Name);

		log_msg  = "\n\n";
		log_msg += "//------------------------------------------------------------------------";

		xDRV_LOG_CTRL->CREATE__SUB_DIRECTORY(sObject_Name);
		xDRV_LOG_CTRL->SET__PROPERTY(file_name,24*5,60);

		xDRV_LOG_CTRL->DISABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);

		xDRV_LOG_CTRL->ENABLE__TIME_LOG();
		xDRV_LOG_CTRL->WRITE__LOG("   START   \n");
	}

	return 1;
}
int CDriver__LPx_ETHERNET::__INITIALIZE__IO(p_io_para)
{
	//-------------------------------------------------------
	// Set Driver Parameter
	//------------------------------------------------------

	CString net_ip   = "127.0.0.1";
	CString net_port = "10001";

	// ...
	{
		CString para_cmmd;
		CString para_data;

		// 1. IP
		{
			para_cmmd = "IP";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_ip = para_data;
			}
		}
		// 2. Port
		{
			para_cmmd = "PORT";

			if(p_io_para->Get__PARAMETER_DATA(para_cmmd, para_data) > 0)
			{
				net_port = para_data;
			}
		}
	}

	// ...
	{
		CString end_str = "";

		end_str = (char) __CR;

		int end_len = end_str.GetLength();

		mX_Net->SET__TERMINAL_InSTRING( end_str, end_len);
		mX_Net->SET__TERMINAL_OutSTRING(end_str, end_len);
	}

	// ...
	CString log_msg;
	CString log_bff;

	CString str_data;

	// ...
	{
		sEnd_InStr  = mX_Net->GET__TERMINAL_InSTRING();	
		sEnd_OutStr = mX_Net->GET__TERMINAL_OutSTRING();
	}

	// ...
	{
		log_msg.Format("Connecting to Ethernet ... \n");

		log_bff.Format("Net_IP : %s \n", net_ip);
		log_msg += log_bff;

		log_bff.Format("Net_Port : %s \n", net_port);
		log_msg += log_bff;

		//
		m_nRetryCount = 2;

		log_bff.Format(" * Retry Count: %1d \n", m_nRetryCount);
		log_msg += log_bff;

		//
		m_nTimeout = 1;			// 1 sec
		m_Rcv_Time = m_nTimeout;

		log_bff.Format(" * Recv_Timeout: %1d sec \n", m_nTimeout);
		log_msg += log_bff;

		//
		m_Out_Time = 10;		// 10 sec

		log_bff.Format("Action_Timeout: %1d sec \n", m_Out_Time);
		log_msg += log_bff;

		//
		log_bff.Format("End_InStr  : %s \n", sEnd_InStr);
		log_msg += log_bff;

		log_bff.Format("End_OutStr : %s \n", sEnd_OutStr);
		log_msg += log_bff;

		//
		xAPP_LOG_CTRL->WRITE__LOG(log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);
	}

	// ...
	CString err_msg;
	printf("%s : Connecting (%s %s) ... \n", sObject_Name, net_ip,net_port);

	mX_Net->INIT__PROPERTY(net_ip, atoi(net_port));
	if(mX_Net->CONNECT(&err_msg) < 0)
	{
		log_msg = "Connection Result ... \n";
		log_bff.Format("Fail to do INIT__ETHERNET: %s(%s), ret(-1) \n", net_ip,net_port);
		log_msg += log_bff;
		log_bff.Format(" * Error Message <- \"%s\" \n", err_msg);
		log_msg += log_bff;

		printf("%s : %s", sObject_Name, log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);

		diCH__COMM_STS->Set__DATA(STR__OFFLINE);
	}
	else
	{
		log_msg = "Connection Result ... \n";
		log_msg += "Init-Ethernet Completed ... \n";

		printf("%s : %s", sObject_Name, log_msg);
		xDRV_LOG_CTRL->WRITE__LOG(log_msg);

		diCH__COMM_STS->Set__DATA(STR__ONLINE);
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		bActive_SIM = x_seq_info->Is__SIMULATION_MODE();
	}
	return 1;
}


//--------------------------------------------------------------------------------
int CDriver__LPx_ETHERNET::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
LOOP_RETRY:

	// ...
	int flag = -1;

	CString para__arm_type;
	CString para__stn_name;
	CString para__stn_slot;
	CString para__align_angle;

	// ...
	int seq_flag = 1;

	if(dCH__CFG_ACTION_CONFIRM_FLAG->Check__DATA(STR__ENABLE) > 0)
	{
		CString log_msg;

		CString str_title;
		CString str_msg;
		CString str_bff;
		CStringArray l_act;
		CString r_act;

		str_title.Format("%s - Action Confirm Flag", sObject_Name);

		str_bff.Format("Object Mode : [%s] \n", mode);
		str_msg += str_bff;
		str_bff.Format("Arm Type : [%s] \n", para__arm_type);
		str_msg += str_bff;
		str_bff.Format("Station Name : [%s] \n", para__stn_name);
		str_msg += str_bff;
		str_bff.Format("Station Slot : [%s] \n", para__stn_slot);
		str_msg += str_bff;

		l_act.RemoveAll();
		l_act.Add(STR__YES);
		l_act.Add(STR__NO);

		p_alarm->Popup__MESSAGE_BOX(str_title,str_msg,l_act,r_act);

		if(r_act.CompareNoCase(STR__NO) == 0)
		{
			seq_flag = -1;

			CString log_msg = "Confirm : Action No Clicked !";

			Fnc__APP_LOG(log_msg);
			Fnc__ACT_MSG(log_msg);
		}
	}

	if(seq_flag > 0)
	{
		pII__EXT_MODE_CTRL = p_variable->Get__EXT_FNC_MODE_CTRL();
		pII__EXT_VAR_CTRL  = p_variable->Get__EXT_FNC_VAR_CTRL();
		pII__EXT_FNC_CTRL  = p_variable->Get__EXT_USER_FNC_CTRL();

		// ...
		{
			CString upper_obj = pII__EXT_MODE_CTRL->Get__UPPER_OBJECT_NAME();	

			CString log_msg;
			log_msg.Format("Object Call: [%s] ==> [%s]",  upper_obj,sObject_Name);

			Fnc__APP_LOG(log_msg);
		}

		     IF__CTRL_MODE(sMODE__INIT)					flag = Call__INIT(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CHECK_CMMD)			flag = Call__CHECK_CMMD(p_variable, p_alarm);
		ELSE_IF__CTRL_MODE(sMODE__CHECK_ERR_CODE)		flag = Call__CHECK_ERR_CODE(p_variable, p_alarm);		
		ELSE_IF__CTRL_MODE(sMODE__CHECK_LPx_STATE)		flag = Call__CHECK_LPx_STATE(p_variable, p_alarm);
	}
	else
	{
		flag = -1;
	}

	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;	
		log_msg.Format("Aborted ... :  [%s]\n", mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}
	else
	{
		CString log_msg;
		log_msg.Format("Completed ... :  [%s]\n", mode);

		Fnc__APP_LOG(log_msg);
		Fnc__ACT_MSG(log_msg);
	}

	return flag;
}

int CDriver__LPx_ETHERNET::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__IO_MONITOR:
			Mon__IO_MONITOR(p_variable,p_alarm);
			break;

		case MON_ID__RECV_PROC:
			Mon__RECV_PROC(p_variable, p_alarm);
			break;
	}

	return 1;
}
