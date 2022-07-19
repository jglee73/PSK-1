#include "StdAfx.h"
#include "CObj__ATM_ROBOT_FUSION.h"
#include "CObj__ATM_ROBOT_FUSION__DEF.h"
#include "CObj__ATM_ROBOT_FUSION__ALID.h"

#include "Macro_Function.h"


//--------------------------------------------------------------------------------
CObj__ATM_ROBOT_FUSION::CObj__ATM_ROBOT_FUSION()
{

}
CObj__ATM_ROBOT_FUSION::~CObj__ATM_ROBOT_FUSION()
{

}

//--------------------------------------------------------------------------------
int CObj__ATM_ROBOT_FUSION::__DEFINE__CONTROL_MODE(obj, l_mode)
{
	sObject_Name = obj;

	// ...
	{
		ADD__CTRL_VAR(sMODE__INIT, "INIT");
		ADD__CTRL_VAR(sMODE__HOME, "HOME");

		ADD__CTRL_VAR(sMODE__PICK,	"PICK");
		ADD__CTRL_VAR(sMODE__PLACE,	"PLACE");
		ADD__CTRL_VAR(sMODE__ROTATE,"ROTATE");

		ADD__CTRL_VAR(sMODE__VACOFF_HOME, "VAC_OFF.HOME");
		ADD__CTRL_VAR(sMODE__MAP, "MAP");

		ADD__CTRL_VAR(sMODE__VACON,  "VACON");
		ADD__CTRL_VAR(sMODE__VACOFF, "VACOFF");

		ADD__CTRL_VAR(sMODE__RETRACT, "RETRACT");
		ADD__CTRL_VAR(sMODE__EXTEND,  "EXTEND");
		
		ADD__CTRL_VAR(sMODE__GOUP,   "GOUP");
		ADD__CTRL_VAR(sMODE__GODOWN, "GODOWN");

		ADD__CTRL_VAR(sMODE__ALGN, "ALGN");

		ADD__CTRL_VAR(sMODE__LP_MAP, "LP_MAP");

		ADD__CTRL_VAR(sMODE__TIME_TEST, "TIME_TEST");
	}
	return 1;
}
int CObj__ATM_ROBOT_FUSION::__DEFINE__VERSION_HISTORY(version)
{
	version = "JG.Lee ";

	return 1;
}


// ...
#define APP_DSP__RB_TARGET_MOVE						\
"UNKNOWN HOME READY									\
PM1 PM2 PM3 PM4 PM5 PM6								\
LBA LBB LBC LBD										\
AL1 AL2												\
VIS1 VIS2											\
LP1 LP2 LP3 LP4 LP5									\
BUFF1 BUFF2 FULL_BUFF								\
LBA-1  LBA-2										\
LBB-1  LBB-2"

#define APP_DSP__STN_NAME							\
"LP1 LP2 LP3 LP4 LP5								\
VIS1												\
LBA LBB LBC LBD										\
AL1 AL2												\
BUFF1 BUFF2 FULL_BUFF"

#define APP_DSP__ARM_TYPE							\
"A B"

#define APP_DSP__ARM_STS_ANI						\
"UNKNOWN RETRACT EXTEND"

#define APP_DSP__DSlot								\
"1  2  3  4  5  6  7  8  9  10						\
11 12 13 14 15 16 17 18 19 20						\
21 22 23 24 25 26 27 28 29 30"


// ...
#define MON_ID__STATE_MONITOR						1


int CObj__ATM_ROBOT_FUSION::__DEFINE__VARIABLE_STD(p_variable)
{
	DECLARE__STD_VARIABLE

	CCommon_Error__DEF_VARIABLE m_err_def_variable;
	p_variable->Link__DEF_VARIABLE__ERROR_FEEDBACK(&m_err_def_variable);

	// ...
	CString str_name;
	int i;
	int k;

	// LLx ...
	{
		CString def_name;
		CString def_data;

		def_name = "LLx.MULTI_DOOR_VALVE";
		p_variable->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_DOOR_VALVE = true;
		else											bActive__LLx_MULTI_DOOR_VALVE = false;
	}

	// ...
	{
		str_name = "OBJ.STATUS";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__OBJ_STATUS,str_name);
	}

	// PARA CHANNEL -----
	{
		str_name = "OTR.IN.PARA.dSTN.NAME";
		STD__ADD_DIGITAL(str_name, APP_DSP__STN_NAME);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_NAME,str_name);

		str_name = "OTR.IN.PARA.dSTN.SLOT";
		STD__ADD_DIGITAL(str_name, APP_DSP__DSlot);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__STN_SLOT,str_name);

		str_name = "OTR.IN.PARA.dARM.TYPE";
		STD__ADD_DIGITAL(str_name, APP_DSP__ARM_TYPE);
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_IN_PARA__ARM_TYPE,str_name);	
	}

	// MATERIAL CHANNEL -----
	{
		CString dsp_slot_sts;
		p_variable->Get__STD_DESCRIPTION("STD_SLOT_STATUS", dsp_slot_sts);

		// Material Status
		str_name = "OTR.OUT.MON.dARM_A.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts, "");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS,str_name);

		str_name = "OTR.OUT.MON.dARM_B.MATERIAL.STATUS";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, dsp_slot_sts,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS,str_name);

		// Material Title
		str_name = "OTR.OUT.MON.sARM_A.MATERIAL.TITLE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__ARM_A_MATERIAL_TITLE,str_name);

		str_name = "OTR.OUT.MON.sARM_B.MATERIAL.TITLE";
		STD__ADD_STRING_WITH_X_OPTION(str_name,"");
		LINK__VAR_STRING_CTRL(sCH__OTR_OUT_MON__ARM_B_MATERIAL_TITLE,str_name);
	}

	// ANIMATION CHANNEL -----
	{
		// Robot
		str_name = "OTR.OUT.MON.dACT.ARM";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_TYPE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ACT_ARM,str_name);

		str_name = "OTR.OUT.MON.dARM_A.ACT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_A_ACT,str_name);

		str_name = "OTR.OUT.MON.dARM_B.ACT";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__ARM_STS_ANI,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__ARM_B_ACT,str_name);

		str_name = "OTR.OUT.MON.dTRG.MOVE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__RB_TARGET_MOVE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__TRG_MOVE,str_name);

		str_name = "OTR.OUT.MON.dTRG.ROTATE";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, APP_DSP__RB_TARGET_MOVE,"");
		LINK__VAR_DIGITAL_CTRL(dCH__OTR_OUT_MON__TRG_ROTATE,str_name);
	}

	// Wafer Present Check [NO/YES]
	{
		str_name = "CFG.dWAFER.PRESENT.CHECK";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "YES NO", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG__WAFER_PRESENT_CHECK, str_name);

		str_name = "CFG.dWAFER.CROSSED.CHECK.AFTER.MAPPING";
		STD__ADD_DIGITAL_WITH_X_OPTION(str_name, "FALSE TRUE", "");
		LINK__VAR_DIGITAL_CTRL(dCH__CFG__WAFER_CROSSED_CHECK_AFTER_MAPPING, str_name);
	}

	// TAS Channel ...
	{
		str_name = "TAS.RESET.REQ";
		STD__ADD_STRING(str_name);
		LINK__VAR_STRING_CTRL(sCH__TAS_RESET_REQ, str_name);

		//
		for(i=0; i<CFG_ACT__SIZE; i++)
		{
			CString act_name;

				 if(i == _ACT_INDEX__PICK)			act_name = "PICK";			
			else if(i == _ACT_INDEX__PLACE)			act_name = "PLACE";			
			else if(i == _ACT_INDEX__ROTATE)		act_name = "ROTATE";			
			else									continue;

			// Robot ...
			{
				str_name.Format("TAS.%s.TIME.NOW.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__RB[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.MIN.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__RB[i], str_name);

				str_name.Format("TAS.%s.TIME.MAX.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__RB[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__RB[i], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F.RB", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__RB[i], str_name);

				str_name.Format("TAS.%s.TIME.CNT.RB", act_name);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__RB[i], str_name);
			}

			// LPx ...
			for(k=0; k<CFG_LPx__SIZE; k++)
			{
				int id = k + 1;

				str_name.Format("TAS.%s.TIME.NOW.LP%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__LPx[i][k], str_name);

				//
				str_name.Format("TAS.%s.TIME.MIN.LP%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__LPx[i][k], str_name);

				str_name.Format("TAS.%s.TIME.MAX.LP%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__LPx[i][k], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG.LP%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__LPx[i][k], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F.LP%1d", act_name,id);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__LPx[i][k], str_name);

				str_name.Format("TAS.%s.TIME.CNT.LP%1d", act_name,id);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__LPx[i][k], str_name);
			}

			// AL1 ...
			{
				str_name.Format("TAS.%s.TIME.NOW.AL1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__AL1[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.MIN.AL1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__AL1[i], str_name);

				str_name.Format("TAS.%s.TIME.MAX.AL1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__AL1[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG.AL1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__AL1[i], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F.AL1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__AL1[i], str_name);

				str_name.Format("TAS.%s.TIME.CNT.AL1", act_name);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__AL1[i], str_name);
			}

			// LLx ...
			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				for(k=0; k<CFG_LLx__SIZE; k++)
				{
					int id = k + 1;
					
					for(int t=0; t<CFG_LLx__SLOT_SIZE; t++)
					{
						int slot = t + 1;

						str_name.Format("TAS.%s.TIME.NOW.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__LLx_SLOT[i][k][t], str_name);

						//
						str_name.Format("TAS.%s.TIME.MIN.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__LLx_SLOT[i][k][t], str_name);

						str_name.Format("TAS.%s.TIME.MAX.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__LLx_SLOT[i][k][t], str_name);

						//
						str_name.Format("TAS.%s.TIME.AVG.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__LLx_SLOT[i][k][t], str_name);

						str_name.Format("TAS.%s.TIME.AVG_F.LL%1d.%1d", act_name,id,slot);
						STD__ADD_STRING(str_name);
						LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__LLx_SLOT[i][k][t], str_name);

						str_name.Format("TAS.%s.TIME.CNT.LL%1d.%1d", act_name,id,slot);
						STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
						LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__LLx_SLOT[i][k][t], str_name);
					}
				}
			}
			else
			{
				for(k=0; k<CFG_LLx__SIZE; k++)
				{
					int id = k + 1;

					str_name.Format("TAS.%s.TIME.NOW.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__LLx_X[i][k], str_name);

					//
					str_name.Format("TAS.%s.TIME.MIN.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__LLx_X[i][k], str_name);

					str_name.Format("TAS.%s.TIME.MAX.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__LLx_X[i][k], str_name);

					//
					str_name.Format("TAS.%s.TIME.AVG.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__LLx_X[i][k], str_name);

					str_name.Format("TAS.%s.TIME.AVG_F.LL%1d", act_name,id);
					STD__ADD_STRING(str_name);
					LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__LLx_X[i][k], str_name);

					str_name.Format("TAS.%s.TIME.CNT.LL%1d", act_name,id);
					STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
					LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__LLx_X[i][k], str_name);
				}
			}

			// ST1 ...
			{
				str_name.Format("TAS.%s.TIME.NOW.ST1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_NOW__ST1[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.MIN.ST1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MIN__ST1[i], str_name);

				str_name.Format("TAS.%s.TIME.MAX.ST1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_MAX__ST1[i], str_name);

				//
				str_name.Format("TAS.%s.TIME.AVG.ST1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG__ST1[i], str_name);

				str_name.Format("TAS.%s.TIME.AVG_F.ST1", act_name);
				STD__ADD_STRING(str_name);
				LINK__VAR_STRING_CTRL(sCH__TAS_ACTION_TIME_AVG_F__ST1[i], str_name);

				str_name.Format("TAS.%s.TIME.CNT.ST1", act_name);
				STD__ADD_ANALOG(str_name, "count", 0, 1, 100000);
				LINK__VAR_ANALOG_CTRL(aCH__TAS_ACTION_TIME_CNT__ST1[i], str_name);
			}
		}
	}

	// ...
	{
		p_variable->Add__MONITORING_PROC(3.0, MON_ID__STATE_MONITOR);
	}
	return 1;
}


// ...
#define  ACT__RETRY_ABORT						\
l_act.RemoveAll();								\
l_act.Add("RETRY");								\
l_act.Add("ABORT");

#define  ACT__IGNORE_ABORT						\
l_act.RemoveAll();								\
l_act.Add("IGNORE");							\
l_act.Add("ABORT");


int CObj__ATM_ROBOT_FUSION::__DEFINE__ALARM(p_alarm)
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
		alarm_id = ALID__ARM_A__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material on Robot's A-Arm.";

		alarm_msg = "Please, check material on Robot's A-Arm.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ARM_B__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material on Robot's B-Arm.";

		alarm_msg = "Please, check material on Robot's B-Arm.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__AFTER_MAPPING_CROSSED_WAFER_DETECTED;

		alarm_title  = title;
		alarm_title += "After Mapping Crossed Wafer Detected.";

		alarm_msg = "Please, check Wafer Status.\n";

		ACT__IGNORE_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	for(i=0;i<CFG_LPx__SIZE;i++)
	{
		alarm_id = ALID__LP1__MATERIAL_EXIST_ERROR + i;

		alarm_title  = title;
		alarm_bff.Format("There is material in LP%1d.",i+1);
		alarm_title += alarm_bff;

		alarm_msg.Format("Please, check material in LP%1d.\n",i+1);

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__AL1__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in AL1.";

		alarm_msg = "Please, check material in AL1.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LBA__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in LBA.";

		alarm_msg = "Please, check material in LBA.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LBB__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in LBB.";

		alarm_msg = "Please, check material in LBB.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__VIS1__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in VIS1.";

		alarm_msg = "Please, check material in VIS1.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// SIDE STORAGE 1 ...
	{
		alarm_id = ALID__SIDE_STORAGE1__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in side storage(1).";

		alarm_msg = "Please, check material in side storage(1).\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// SIDE STORAGE 2 ...
	{
		alarm_id = ALID__SIDE_STORAGE2__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in side storage(2).";

		alarm_msg = "Please, check material in side storage(2).\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}	

	//.....
	{
		alarm_id = ALID__PMx__MATERIAL_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "There is material in PMC.";

		alarm_msg = "Please, check material in PMC.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	//.....
	{
		alarm_id = ALID__ALx__SLOT_ID_ERROR;

		alarm_title  = title;
		alarm_title += "ALx Slot_ID Error !";

		alarm_msg = "Please, check the ALx slot parameter of command. \n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	//.....
	{
		alarm_id = ALID__LLx__SLOT_ID_ERROR;

		alarm_title  = title;
		alarm_title += "LLx Slot_ID Error !";

		alarm_msg = "Please, check the LLx slot parameter of command. \n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__ARM_A__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material on Robot's A-Arm.";

		alarm_msg = "Please, check material on Robot's A-Arm.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	//.....
	{
		alarm_id = ALID__ARM_B__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material on Robot's B-Arm.";

		alarm_msg = "Please, check material on Robot's B-Arm.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	for(i=0;i<CFG_LPx__SIZE;i++)
	{
		alarm_id = ALID__LP1__MATERIAL_NONE_ERROR + i;

		alarm_title  = title;
		alarm_bff.Format("There is no material in LP%1d.",i+1);
		alarm_title += alarm_bff;

		alarm_msg.Format("Please, check material in LP%1d.\n",i+1);

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__AL1__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in AL1.";

		alarm_msg = "Please, check material in AL1.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__LBA__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in LBA.";

		alarm_msg = "Please, check material in LBA.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	//.....
	{
		alarm_id = ALID__LBB__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in LBB.";

		alarm_msg = "Please, check material in LBB.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__VIS1__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in VIS1.";

		alarm_msg = "Please, check material in VIS1.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// SIDE STORAGE 1
	{
		alarm_id = ALID__SIDE_STORAGE1__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in side storage(1).";

		alarm_msg = "Please, check material in side storage(1).\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// SIDE STORAGE 2
	{
		alarm_id = ALID__SIDE_STORAGE2__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in side storage(2).";

		alarm_msg = "Please, check material in side storage(2).\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__PMx__MATERIAL_NONE_ERROR;

		alarm_title  = title;
		alarm_title += "There is no material in PMC.";

		alarm_msg = "Please, check material in PMC.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__STN__NOT_EXIST_ERROR;

		alarm_title  = title;
		alarm_title += "STN does not exist.";

		alarm_msg = "Please, check config page.\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	//.....
	{
		alarm_id = ALID__LBA__NOT_DOOR_OPEN;

		alarm_title  = title;
		alarm_title += "LBA's door status is not open.";

		alarm_msg = "Please, check LBA's door status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	//.....
	{
		alarm_id = ALID__LBB__NOT_DOOR_OPEN;

		alarm_title  = title;
		alarm_title += "LBB's door status is not open.";

		alarm_msg = "Please, check LBB's door status !\n";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	// ...
	{
		alarm_id = ALID__LPx__NOT_DOOR_OPEN;

		alarm_title  = title;
		alarm_title += "LPx's door status is not open.";

		alarm_msg = "";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LPx__FOUP_NOT_EXIST;

		alarm_title  = title;
		alarm_title += "LPx's foup does not exist.";

		alarm_msg = "";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LPx__FOUP_NOT_CLAMP;

		alarm_title  = title;
		alarm_title += "LPx's foup does not clamp.";

		alarm_msg = "";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__LPx__FOUP_NOT_LOAD;

		alarm_title  = title;
		alarm_title += "LPx's foup position is not load.";

		alarm_msg = "";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__INTLK__EFEM_DOOR_NOT_CLOSE;

		alarm_title  = title;
		alarm_title += "EFEM DOOR is not Close.";

		alarm_msg = "So... Robot Can't do any command.\n";
		alarm_msg += "Please..., Check EFEM Side Door Status";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__INTLK__LPx_CANNOT_MAP_WAFER_EXIST_ON_ARM;

		alarm_title  = title;
		alarm_title += "Material Exist On Arm.";

		alarm_msg = "So... Robot Can't do Mapping Action.\n";
		alarm_msg += "Please..., Check Robot's Arm Status";

		ACT__RETRY_ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}
	// ...
	{
		alarm_id = ALID__ATM_RB_HAS_NO_MAPPING_SENSOR;

		alarm_title  = title;
		alarm_title += "ATM_Robot has no mapping sensor !.";

		alarm_msg = "So, Robot Can't do Mapping Action.\n";

		ACT__ABORT;
		ADD__ALARM_EX(alarm_id,alarm_title,alarm_msg,l_act);
	}

	return 1;
}


//--------------------------------------------------------------------------------
int CObj__ATM_ROBOT_FUSION::__INITIALIZE__OBJECT(p_variable,p_ext_obj_create)
{
	// ...
	{
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

	// ...
	CString def_name;
	CString def_data;
	CString str_name;

	CString obj_name;
	CString var_name;
	int i;
	int j;

	// LLx ...
	{
		def_name = "LLx.MULTI_DOOR_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_DOOR_VALVE = true;
		else											bActive__LLx_MULTI_DOOR_VALVE = false;

		def_name = "LLx.MULTI_SLOT_VALVE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		if(def_data.CompareNoCase("YES") == 0)			bActive__LLx_MULTI_SLOT_VALVE = true;
		else											bActive__LLx_MULTI_SLOT_VALVE = false;

		def_name = "LLx.SLOT_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);

		iLLx_SLOT_SIZE = atoi(def_data);
		if(iLLx_SLOT_SIZE > CFG_LLx__SLOT_SIZE)		iLLx_SLOT_SIZE = CFG_LLx__SLOT_SIZE;

		//
		def_name = "DATA.LLx_SIZE";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		iSIZE_LLx = atoi(def_data);
		if(iSIZE_LLx > CFG_LLx__SIZE)		iSIZE_LLx = CFG_LLx__SIZE;

		for(int ll_i=0; ll_i<iSIZE_LLx; ll_i++)
		{
			def_name.Format("OBJ__LL%1d", ll_i+1);			
			p_variable->Get__DEF_CONST_DATA(def_name, obj_name);

			for(i=0; i<CFG_LLx__SLOT_SIZE; i++)
			{
				str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS", i+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_SLOT_STATUS[ll_i][i], obj_name,str_name);

				str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE", i+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LLx_SLOT_TITLE[ll_i][i], obj_name,str_name);
			}

			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				for(int k=0; k<iLLx_SLOT_SIZE; k++)
				{
					str_name.Format("OTR.OUT.MON.dDOOR.VALVE.STATUS.%1d", k+1);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_DOOR_STATUS_XX[ll_i][k], obj_name,str_name);		
				}
			}
			else
			{
				str_name = "OTR.OUT.MON.dDOOR.VALVE.STATUS";
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LLx_DOOR_STATUS_A[ll_i], obj_name,str_name);		
			}
		}
	}

	// DB_CFG ...
	{
		def_name = "OBJ__DB";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		for(i=0;i<CFG_LPx__SIZE;i++)
		{
			str_name.Format("CFG.LP%1d.EXIST.FLAG",i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LPx_EXIST_FLAG[i], def_data,str_name);

			str_name.Format("CFG.dLP%1d.DOOR_CLOSE_MODE.AFTER_MAPPING", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LPx_CLOSE_MOVE_AFTER_MAPPING[i], def_data,str_name);
		}

		// ...
		{
			str_name = "CFG.dALIGN.DEVICE";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_ALIGN_DEVICE, def_data,str_name);

			str_name = "CFG.AL1.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_AL1_EXIST_FLAG, def_data,str_name);

			str_name = "CFG.AL1.SLOT.MAX";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_AL1_SLOT_MAX, def_data,str_name);
		}
		
		for(i=0; i<CFG_LLx__SIZE; i++)
		{
			CString ll_name = Macro__GET_LLx_NAME(i);

			str_name.Format("CFG.%s.SLOT.MAX", ll_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_SLOT_MAX[i], def_data,str_name);

			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				int ll_id = i + 1;

				str_name.Format("CFG.LL%1d.1.EXIST.FLAG", ll_id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_1_EXIST_FLAG[i], def_data,str_name);

				str_name.Format("CFG.LL%1d.2.EXIST.FLAG", ll_id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_2_EXIST_FLAG[i], def_data,str_name);
			}
			else
			{
				str_name.Format("CFG.%s.EXIST.FLAG", ll_name);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_EXIST_FLAG[i], def_data,str_name);
			}
		}
		
		// ...
		{
			str_name = "CFG.VIS1.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_VIS1_EIXST_FLAG, def_data,str_name);

			//
			str_name = "CFG.BUFF1.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_BUFF1_EXIST_FLAG, def_data,str_name);

			str_name = "CFG.BUFF2.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_BUFF2_EXIST_FLAG, def_data,str_name);

			str_name = "CFG.FULL.BUFF.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_FULL_BUFF_EXIST_FLAG, def_data,str_name);
		}

		// ...
		{
			var_name = "MAINT.TARGET.LLx.NAME";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAINT_TARGT_LLx_NAME, def_data,var_name);

			var_name = "MAINT.TARGET.LLx.SLOT";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__MAINT_TARGT_LLx_SLOT, def_data,var_name);

			//
			var_name = "MODULE.LINK.sTARGET.LLx.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MODULE_LINK_TARGT_LLx_NAME, def_data,var_name);

			var_name = "MODULE.LINK.sTARGET.LLx.SLOT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__MODULE_LINK_TARGT_LLx_SLOT, def_data,var_name);

			//
			var_name = "CUR.AL1.TARGET.LLx.NAME";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_TARGET_LLx_NAME, def_data,var_name);

			var_name = "CUR.AL1.TARGET.LLx.SLOT";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_TARGET_LLx_SLOT, def_data,var_name);

			var_name = "CUR.AL1.CCD.POS";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__CUR_AL1_CCD_POS, def_data,var_name);
		}

		// LLx ...
		for(i=0; i<CFG_LLx__SIZE; i++)
		{
			int id = i + 1;

			// .CFG.SLOT.USE ..
			{
				for(int  k=0; k<CFG_LLx__SLOT_SIZE; k++)
				{
					int slot = k + 1;

					str_name.Format("CFG.LL%1d.SLOT%02d.USE", id, slot);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_SLOT_USE_X[i][k], def_data,str_name);
				}
			}

			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				for(int  k=0; k<CFG_LLx__SLOT_SIZE; k++)
				{
					int slot = k + 1;

					//
					str_name.Format("CFG.LL%1d.%1d.ALIGN.POS", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_ALIGN_ANGLE[i][k], def_data,str_name);

					str_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT[i][k], def_data,str_name);

					str_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT.RANGE", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_RANGE[i][k], def_data,str_name);

					str_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT.START.ANGLE", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_START_ANGLE[i][k], def_data,str_name);

					str_name.Format("CFG.LL%1d.%1d.POST.POSITION.INCREMENT.APPLY", id,slot);
					LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_APPLY[i][k], def_data,str_name);

					str_name.Format("CUR.LL%1d.%1d.POST.POSITION.INCREMENT.ANGLE", id,slot);
					LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[i][k], def_data,str_name);
				}

			}
			else
			{
				str_name.Format("CFG.LL%1d.ALIGN.POS", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_ALIGN_ANGLE[i], def_data,str_name);

				str_name.Format("CFG.aLL%1d.POST.POSITION.INCREMENT", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT[i], def_data,str_name);

				str_name.Format("CFG.aLL%1d.POST.POSITION.INCREMENT.RANGE", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_RANGE[i], def_data,str_name);

				str_name.Format("CFG.aLL%1d.POST.POSITION.INCREMENT.START.ANGLE", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_START_ANGLE[i], def_data,str_name);

				str_name.Format("CFG.LL%1d.POST.POSITION.INCREMENT.APPLY", id);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_APPLY[i], def_data,str_name);

				str_name.Format("CUR.aLL%1d.POST.POSITION.INCREMENT.ANGLE", id);
				LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[i], def_data,str_name);
			}
		}
	}

	// IO ...
	{
		def_name = "IO_CH__EFEM_DOOR";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name,def_data);
		p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,var_name);

		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__IO_EFEM_DOOR_STS, obj_name,var_name);
	}

	// ROBOT ...
	{
		def_name = "OBJ__ROBOT";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, obj_name);

		pROBOT__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(obj_name);

		// Arm-A
		str_name = "MON.ARM_A.MATERIAL.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS, obj_name,str_name);

		// Arm-B
		str_name = "MON.ARM_B.MATERIAL.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS, obj_name,str_name);

		// Angle Value
		str_name = "PARA.AL1.CCD.POS";
		LINK__EXT_VAR_ANALOG_CTRL(aEXT_CH__ALIGNER_ANGLE_PARA, obj_name,str_name);

	}

	// AL1 ...
	{
		def_name = "OBJ__AL1";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		pAL1__OBJ_CTRL = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

		// Slot Status
		str_name = "OTR.OUT.MON.dSLOT01.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__AL1_SLOT01_STATUS, def_data,str_name);

		str_name = "OTR.OUT.MON.dSLOT02.STATUS";
		LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__AL1_SLOT02_STATUS, def_data,str_name);

		// Slot Title
		str_name = "OTR.OUT.MON.sSLOT01.TITLE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__AL1_SLOT01_TITLE, def_data,str_name);

		str_name = "OTR.OUT.MON.sSLOT02.TITLE";
		LINK__EXT_VAR_STRING_CTRL(sEXT_CH__AL1_SLOT02_TITLE, def_data,str_name);
	}

	// LPx -----
	{
		def_name = "LP_SIZE";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		iLPx_SIZE = atoi(def_data);
		if(iLPx_SIZE > CFG_LPx__SIZE)		iLPx_SIZE = CFG_LPx__SIZE;

		for(i=0;i<iLPx_SIZE;i++)	
		{
			def_name.Format("OBJ__LP%1d",i+1);
			p_variable->Get__DEF_CONST_DATA(def_name,def_data);

			pLPx__OBJ_CTRL[i] = p_ext_obj_create->Create__OBJECT_CTRL(def_data);

			for(j=0;j<CFG_LPx__SLOT_SIZE;j++)
			{
				// Status
				str_name.Format("OTR.OUT.MON.dSLOT%002d.STATUS",j+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_SLOT_STATUS[i][j], def_data,str_name);

				// Title
				str_name.Format("OTR.OUT.MON.sSLOT%002d.TITLE",j+1);
				LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LPx_SLOT_TITLE[i][j], def_data,str_name);

				// Map Status
				str_name.Format("OTR.OUT.MON.dSLOT%02d.STATUS", j+1);
				LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_SLOT_MAP_STATUS[i][j], def_data,str_name);
			}

			// Door 
			str_name = "OTR.OUT.MON.dDOOR.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_DOOR_STATUS[i], def_data,str_name);

			// Foup Exist
			str_name = "OTR.OUT.MON.dFOUP.EXIST.FLAG";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_FOUP_EXIST_FLAG[i], def_data,str_name);

			// Foup Clamp
			str_name = "OTR.OUT.MON.dFOUP.CLAMP.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_FOUP_CLAMP_STATUS[i], def_data,str_name);

			// Foup Position
			str_name = "OTR.OUT.MON.dFOUP.POS.STATUS";
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__LPx_FOUP_POS_STATUS[i], def_data,str_name);

			//
			str_name = "MAP_SEQ.LOCK";
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__LPx_MAP_SEQ_LOCK[i], def_data,str_name);
		}
	}

	// SIDE STORAGE1 ...
	{
		def_name = "OBJ__SIDE_STORAGE1";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		for(i=0;i<CFG_LPx__SLOT_SIZE;i++)
		{
			str_name.Format("SLOT%002d.STATUS", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SIDE_STORAGE1_SLOT_STATUS[i], def_data,str_name);

			str_name.Format("SLOT%002d.TITLE", i+1);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SIDE_STORAGE1_SLOT_TITLE[i], def_data,str_name);
		}
	}
	// SIDE STORAGE2 ...
	{
		def_name = "OBJ__SIDE_STORAGE2";
		p_variable->Get__DEF_CONST_DATA(def_name,def_data);

		for(i=0;i<CFG_LPx__SLOT_SIZE;i++)
		{
			str_name.Format("SLOT%002d.STATUS", i+1);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__SIDE_STORAGE2_SLOT_STATUS[i], def_data,str_name);

			str_name.Format("SLOT%002d.TITLE", i+1);
			LINK__EXT_VAR_STRING_CTRL(sEXT_CH__SIDE_STORAGE2_SLOT_TITLE[i], def_data,str_name);
		}
	}

	// ARM_RNE.SENSOR ... 
	{
		def_name = "ROBOT.RNE_SNS.ARM_A";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if((def_data.CompareNoCase(STR__NO)   == 0)
		|| (def_data.CompareNoCase(STR__NULL) == 0))
		{
			bActive__ROBOT_RNE_SNS__ARM_A = false;
		}
		else
		{
			bActive__ROBOT_RNE_SNS__ARM_A = true;

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,str_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_RNE_SNS__ARM_A, obj_name,str_name);
		}

		//
		def_name = "ROBOT.RNE_SNS.ARM_B";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);

		if((def_data.CompareNoCase(STR__NO)   == 0)
		|| (def_data.CompareNoCase(STR__NULL) == 0))
		{
			bActive__ROBOT_RNE_SNS__ARM_B = false;
		}
		else
		{
			bActive__ROBOT_RNE_SNS__ARM_B = true;

			p_ext_obj_create->Get__CHANNEL_To_OBJ_VAR(def_data, obj_name,str_name);
			LINK__EXT_VAR_DIGITAL_CTRL(dEXT_CH__ROBOT_RNE_SNS__ARM_B, obj_name,str_name);
		}
	}
	// ARM_RNE.STATE ...
	{
		def_name = "DATA.RNE_ON";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sDATA__RNE_ON = def_data;

		def_name = "DATA.RNE_OFF";
		p_ext_obj_create->Get__DEF_CONST_DATA(def_name, def_data);
		sDATA__RNE_OFF = def_data;
	}

	// ...
	{
		SCX__SEQ_INFO x_seq_info;

		iActive__SIM_MODE = x_seq_info->Is__SIMULATION_MODE();
	}

	if(iActive__SIM_MODE > 0)
	{
		if(bActive__ROBOT_RNE_SNS__ARM_A)			dEXT_CH__ROBOT_RNE_SNS__ARM_A->Set__DATA(sDATA__RNE_ON);
		if(bActive__ROBOT_RNE_SNS__ARM_B)			dEXT_CH__ROBOT_RNE_SNS__ARM_B->Set__DATA(sDATA__RNE_ON);
	}

	iFlag__APP_LOG = 1;
	return 1;
}

//--------------------------------------------------------------------------------
int CObj__ATM_ROBOT_FUSION::__CALL__CONTROL_MODE(mode, p_debug, p_variable, p_alarm)
{
	int flag = -1;

	CString para__arm_type;
	CString para__stn_name;
	CString para__stn_slot;
	CString var_data;

	// ...
	CStringArray l_para;
	p_variable->Get__FNC_PARAMETER(l_para);

	if(l_para.GetSize() > 0)
	{
		CString para_data;

		int limit = l_para.GetSize();
		int i;

		for(i=0;i<limit;i++)
		{
			para_data = l_para[i];

			switch(i)
			{
				case 0:		
					dCH__OTR_IN_PARA__ARM_TYPE->Set__DATA(para_data);
					break;

				case 1:
					dCH__OTR_IN_PARA__STN_NAME->Set__DATA(para_data);
					break;

				case 2:
					dCH__OTR_IN_PARA__STN_SLOT->Set__DATA(para_data);
					break;
			}	
		}
	}

	dCH__OTR_IN_PARA__ARM_TYPE->Get__DATA(para__arm_type);
	dCH__OTR_IN_PARA__STN_NAME->Get__DATA(para__stn_name);
	dCH__OTR_IN_PARA__STN_SLOT->Get__DATA(para__stn_slot);

	// ...
	{
		CString log_msg;

		log_msg.Format("Start ... :  [%s] (%s,%s,%s)",
						mode,
						para__arm_type,
						para__stn_name,
						para__stn_slot);

		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
		dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Get__DATA(var_data);
		dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Set__DATA(var_data);

		dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Get__DATA(var_data);
		dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Set__DATA(var_data);
	}

	// ...
	bool active__align_pick = false;

	if(para__stn_name.CompareNoCase(STR__AL1) == 0)
	{
		if(mode.CompareNoCase(sMODE__PICK) == 0)
		{
			active__align_pick = true;
		}
	}

	if(active__align_pick)
	{
		CString log_msg;
		CString log_bff;

		CString llx_name;
		CString llx_slot;
		CString al_angle;

		if(sCH__OBJ_STATUS->Check__DATA(STR__MAINTMODE) > 0)
		{
			dEXT_CH__MAINT_TARGT_LLx_NAME->Get__DATA(llx_name);
			dEXT_CH__MAINT_TARGT_LLx_SLOT->Get__DATA(llx_slot);
		}
		else
		{
			sEXT_CH__MODULE_LINK_TARGT_LLx_NAME->Get__DATA(llx_name);	
			if(llx_name == "")		llx_name = _MODULE__LBA;

			sEXT_CH__MODULE_LINK_TARGT_LLx_SLOT->Get__DATA(llx_slot);	
			if(llx_slot == "")		llx_slot = "1";
		}

		int ll_i = Macro__CHECK_LLx_INDEX(llx_name);
		if(ll_i >= 0)
		{
			// ...
			{
				log_msg = "\n";

				log_bff.Format("%s(%s) Align Info ... \n", llx_name,llx_slot);
				log_msg += log_bff;
			}

			if(bActive__LLx_MULTI_DOOR_VALVE)
			{
				int slot_index = atoi(llx_slot) - 1;
				if(slot_index <  0)						return -11;
				if(slot_index >= CFG_LLx__SLOT_SIZE)	return -12;

				if(dEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_APPLY[ll_i][slot_index]->Check__DATA(STR__ENABLE) > 0)
				{
					aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[ll_i][slot_index]->Get__DATA(var_data);
					double cur_angle = atof(var_data);

					aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT[ll_i][slot_index]->Get__DATA(var_data);
					double cfg_inc = atof(var_data);

					aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_RANGE[ll_i][slot_index]->Get__DATA(var_data);
					double max_angle = atof(var_data);

					if(cur_angle > max_angle)		cur_angle = 0;

					// ...
					aEXT_CH__CFG_LLx_X_POST_POSITION_INCREMENT_START_ANGLE[ll_i][slot_index]->Get__DATA(var_data);
					double start_angle = atof(var_data);

					al_angle.Format("%.0f", (start_angle+cur_angle));

					// ...
					{
						double next_angle = cur_angle + cfg_inc;
						if(next_angle > max_angle)		next_angle = 0;

						var_data.Format("%.0f", next_angle);
						aEXT_CH__CUR_LLx_X_POST_POSITION_INCREMENT_ANGLE[ll_i][slot_index]->Set__DATA(var_data);
					}

					// ...
					{
						log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
						log_msg += log_bff;

						log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
						log_msg += log_bff;

						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}	
				else
				{
					aEXT_CH__CFG_LLx_X_ALIGN_ANGLE[ll_i][slot_index]->Get__DATA(al_angle);

					// ...
					{
						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}
			}
			else
			{
				if(dEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_APPLY[ll_i]->Check__DATA(STR__ENABLE) > 0)
				{
					aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[ll_i]->Get__DATA(var_data);
					double cur_angle = atof(var_data);

					aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT[ll_i]->Get__DATA(var_data);
					double cfg_inc = atof(var_data);

					aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_RANGE[ll_i]->Get__DATA(var_data);
					double max_angle = atof(var_data);

					if(cur_angle > max_angle)		cur_angle = 0;

					// ...
					aEXT_CH__CFG_LLx_POST_POSITION_INCREMENT_START_ANGLE[ll_i]->Get__DATA(var_data);
					double start_angle = atof(var_data);

					al_angle.Format("%.0f", (start_angle+cur_angle));
					
					// ...
					{
						double next_angle = cur_angle + cfg_inc;
						if(next_angle > max_angle)		next_angle = 0;

						var_data.Format("%.0f", next_angle);
						aEXT_CH__CUR_LLx_POST_POSITION_INCREMENT_ANGLE[ll_i]->Set__DATA(var_data);
					}

					// ...
					{
						log_bff.Format("   CFG Increment Apply <- [%s] \n", STR__ENABLE);
						log_msg += log_bff;

						log_bff.Format("   Current Increment Angle <- [%.0f] \n", cur_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Start Angle <- [%.0f] \n", start_angle);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Angle <- [%.0f] \n", cfg_inc);
						log_msg += log_bff;

						log_bff.Format("   CFG Increment Range <- [%.0f] \n", max_angle);
						log_msg += log_bff;

						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}	
				else
				{
					aEXT_CH__CFG_LLx_ALIGN_ANGLE[ll_i]->Get__DATA(al_angle);
				
					// ...
					{
						log_bff.Format("   Target Align Angle <- [%s] \n", al_angle);
						log_msg += log_bff;
					}
				}
			}
		}

		if(dEXT_CH__CFG_ALIGN_DEVICE->Check__DATA(STR__ATM_RB) > 0)
		{
			sEXT_CH__CUR_AL1_TARGET_LLx_NAME->Set__DATA(llx_name);
			sEXT_CH__CUR_AL1_TARGET_LLx_SLOT->Set__DATA(llx_slot);

			aEXT_CH__ALIGNER_ANGLE_PARA->Set__DATA(al_angle);
			sEXT_CH__CUR_AL1_CCD_POS->Set__DATA(al_angle);
		}
		else
		{
			active__align_pick = false;
		}

		Fnc__APP_LOG(log_msg);
	}

	if(mode.CompareNoCase(sMODE__PICK) == 0)
	{
		int lp_index = Macro__CHECK_LPx_INDEX(para__stn_name);

		if((lp_index <  iLPx_SIZE)	
		&& (lp_index >= 0))
		{
			sEXT_CH__LPx_MAP_SEQ_LOCK[lp_index]->Set__DATA("YES");
		}
	}

	IF__CTRL_MODE(sMODE__INIT)
	{
		CString pre_sts__arm_a;
		CString pre_sts__arm_b;
		CString pre_sts__al;

		// ...
		{
			dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Get__DATA(pre_sts__arm_a);
			dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Get__DATA(pre_sts__arm_b);

			dEXT_CH__AL1_SLOT01_STATUS->Get__DATA(pre_sts__al);
		}

		flag = Call__INIT(p_variable,p_alarm);

		if(flag > 0)
		{
			CString cur_sts__arm_a;
			CString cur_sts__arm_b;
			CString cur_sts__al;

			// Interlock Check ...
			{
				// Arm-A
				dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Get__DATA(cur_sts__arm_a);

				// Arm-B
				dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Get__DATA(cur_sts__arm_b);

				// AL-1
				dEXT_CH__AL1_SLOT01_STATUS->Get__DATA(cur_sts__al);

				// ...
				int check_flag = 1;

				if((cur_sts__arm_a.CompareNoCase("NONE") == 0)
				&& (pre_sts__arm_a.CompareNoCase("NONE") != 0))
				{
					check_flag = -1;
				}	
				if((cur_sts__arm_b.CompareNoCase("NONE") == 0)
				&& (pre_sts__arm_b.CompareNoCase("NONE") != 0))
				{
					check_flag = -1;
				}	

				if((cur_sts__al.CompareNoCase("NONE") == 0)
				&& (pre_sts__al.CompareNoCase("NONE") != 0))
				{
					check_flag = -1;
				}	

				if(check_flag < 0)
				{
					CString msg_title;
					CString msg_body;
					CString msg_bff;
					CStringArray l_act;
					CString r_act;

					//
					msg_title = "Wafer Check Error !";

					//
					msg_body  = "GUI���� Wafer ������ Initialize�� ���� Wafer ������ ��ġ���� �ʽ��ϴ�. \n";
					msg_bff.Format("Arm A : [%s] -> [%s] \n", pre_sts__arm_a,cur_sts__arm_a);
					msg_body += msg_bff;
					msg_bff.Format("Arm B : [%s] -> [%s] \n", pre_sts__arm_b,cur_sts__arm_b);
					msg_body += msg_bff;
					msg_bff.Format("AL : [%s] -> [%s] \n", pre_sts__al,cur_sts__al);
					msg_body += msg_bff;

					msg_body += "���� ATM Robot�� �ִ� Wafer ������ ������ ������ Ȯ�� �ٶ��ϴ�.\n";

					// Arm-A
					if(cur_sts__arm_a.CompareNoCase("NONE") != 0)
					{
						msg_body += "ATM Robot�� A Arm�� Wafer�� �ֽ��ϱ�? \n";
					}
					else
					{
						msg_body += "ATM Robot�� A Arm�� Wafer�� �����ϱ�? \n";
					}

					// Arm-B
					if(cur_sts__arm_b.CompareNoCase("NONE") != 0)
					{
						msg_body += "ATM Robot�� B Arm�� Wafer�� �ֽ��ϱ�? \n";
					}
					else
					{
						msg_body += "ATM Robot�� B Arm�� Wafer�� �����ϱ�? \n";
					}

					// AL-1
					if(cur_sts__al.CompareNoCase("NONE") != 0)
					{
						msg_body += "Aligner ���� Wafer�� �ֽ��ϱ�? \n";
					}
					else
					{
						msg_body += "Aligner ���� Wafer�� �����ϱ�? \n";
					}

					msg_body += "���� ������ �´ٸ�, \"YES\"�� �ƴϸ� \"NO\"�� �����Ͻʽÿ�.\n";

					//
					l_act.RemoveAll();
					l_act.Add(STR__YES);
					l_act.Add(STR__NO);

					//
					p_alarm->Popup__MESSAGE_BOX(msg_title,msg_body,l_act,r_act);

					if(r_act.CompareNoCase(STR__YES) != 0)
					{
						flag = -1;

						dEXT_CH__AL1_SLOT01_STATUS->Set__DATA(pre_sts__al);
					}
				}
			}

			if(flag > 0)
			{
				// Arm-A
				dEXT_CH__ROBOT_ARM_A_MATERIAL_STATUS->Get__DATA(var_data);
				dCH__OTR_OUT_MON__ARM_A_MATERIAL_STATUS->Set__DATA(var_data);

				// Arm-B
				dEXT_CH__ROBOT_ARM_B_MATERIAL_STATUS->Get__DATA(var_data);
				dCH__OTR_OUT_MON__ARM_B_MATERIAL_STATUS->Set__DATA(var_data);

				// AL-1
				dEXT_CH__AL1_SLOT01_STATUS->Set__DATA(cur_sts__al);
			}
		}	
	}	
	ELSE_IF__CTRL_MODE(sMODE__PICK)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			int lp_index = Macro__CHECK_LPx_INDEX(para__stn_name);

			if(lp_index >= 0)
			{
				if((dEXT_CH__LPx_FOUP_POS_STATUS[lp_index]->Check__DATA(STR__LOAD) > 0)
				&& (dEXT_CH__LPx_DOOR_STATUS[lp_index]->Check__DATA(STR__OPEN)     < 0))
				{	
					flag = pLPx__OBJ_CTRL[lp_index]->Call__OBJECT(CMMD__LP_OPENDOOR);

					// ...
					{
						CString log_msg;
						CString log_bff;

						CString obj_mode;
						CString lp_pos_sts;
						CString lp_door_sts;

						pLPx__OBJ_CTRL[lp_index]->Get__OBJ_MODE(obj_mode);
						dEXT_CH__LPx_FOUP_POS_STATUS[lp_index]->Get__DATA(lp_pos_sts);
						dEXT_CH__LPx_DOOR_STATUS[lp_index]->Get__DATA(lp_door_sts);

						//
						log_msg.Format("Sub LP%1d - Called ... \n", lp_index+1);

						log_bff.Format("   obj_mode    <- [%s] \n", obj_mode);
						log_msg += log_bff;

						log_bff.Format("   lp_pos_sts  <- [%s] \n", lp_pos_sts);
						log_msg += log_bff;

						log_bff.Format("   lp_door_sts <- [%s] \n", lp_door_sts);
						log_msg += log_bff;

						Fnc__APP_LOG(log_msg);
					}
				}
			}
		}

		if(flag > 0)
		{
			flag = Call__PICK(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot, active__align_pick);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__PLACE)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			int lp_index = Macro__CHECK_LPx_INDEX(para__stn_name);

			if(lp_index >= 0)
			{
				if((dEXT_CH__LPx_FOUP_POS_STATUS[lp_index]->Check__DATA(STR__LOAD) > 0)
				&& (dEXT_CH__LPx_DOOR_STATUS[lp_index]->Check__DATA(STR__OPEN)     < 0))
				{	
					flag = pLPx__OBJ_CTRL[lp_index]->Call__OBJECT(CMMD__LP_OPENDOOR);

					// ...
					{
						CString log_msg;
						CString log_bff;

						CString obj_mode;
						CString lp_pos_sts;
						CString lp_door_sts;

						pLPx__OBJ_CTRL[lp_index]->Get__OBJ_MODE(obj_mode);
						dEXT_CH__LPx_FOUP_POS_STATUS[lp_index]->Get__DATA(lp_pos_sts);
						dEXT_CH__LPx_DOOR_STATUS[lp_index]->Get__DATA(lp_door_sts);

						//
						log_msg.Format("Sub LP%1d - Called ... \n", lp_index+1);

						log_bff.Format("   obj_mode    <- [%s] \n", obj_mode);
						log_msg += log_bff;

						log_bff.Format("   lp_pos_sts  <- [%s] \n", lp_pos_sts);
						log_msg += log_bff;

						log_bff.Format("   lp_door_sts <- [%s] \n", lp_door_sts);
						log_msg += log_bff;

						Fnc__APP_LOG(log_msg);
					}
				}
			}
		}

		if(flag > 0)
		{
			flag = Call__PLACE(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__ROTATE)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			flag = Call__ROTATE(p_variable,
								p_alarm,
								para__arm_type,
								para__stn_name,
								para__stn_slot);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__MAP)
	{
		flag = Call__MAP(p_variable,p_alarm);

		if(flag > 0)
		{
			int lp_index = Macro__CHECK_LPx_INDEX(para__stn_name);

			if(lp_index >= 0)
			{
				if(dEXT_CH__CFG_LPx_CLOSE_MOVE_AFTER_MAPPING[lp_index]->Check__DATA(STR__ENABLE) > 0)
				{
					sEXT_CH__LPx_MAP_SEQ_LOCK[lp_index]->Set__DATA("");
					pLPx__OBJ_CTRL[lp_index]->Call__OBJECT(CMMD__LP_CLOSEDOOR);
				}
			}
		}	
	}
	ELSE_IF__CTRL_MODE(sMODE__HOME)
	{
		flag = Call__HOME(p_variable,p_alarm, -1);
	}
	ELSE_IF__CTRL_MODE(sMODE__VACOFF_HOME)
	{
		flag = Call__HOME(p_variable,p_alarm, 1);
	}
	ELSE_IF__CTRL_MODE(sMODE__VACON)
	{
		flag = Call__VACON(p_variable,p_alarm,para__arm_type);
	}
	ELSE_IF__CTRL_MODE(sMODE__VACOFF)
	{
		flag = Call__VACOFF(p_variable,p_alarm,para__arm_type);
	}
	ELSE_IF__CTRL_MODE(sMODE__RETRACT)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			flag = Call__RETRACT(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__EXTEND)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			flag = Call__EXTEND(p_variable,	p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__GOUP)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			flag = Call__GOUP(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__GODOWN)
	{
		flag = Check__STN_EXIST(p_alarm, para__stn_name,para__stn_slot);

		if(flag > 0)
		{
			flag = Call__GODOWN(p_variable,p_alarm, para__arm_type,para__stn_name,para__stn_slot);
		}
	}
	ELSE_IF__CTRL_MODE(sMODE__ALGN)
	{
		flag = Call__ALGN(p_variable,p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__LP_MAP)
	{
		flag = Call__LP_MAP(p_variable,p_alarm);
	}
	ELSE_IF__CTRL_MODE(sMODE__TIME_TEST)
	{
		flag = Call__TIME_TEST(p_variable,p_alarm);
	}


	if((flag < 0)||(p_variable->Check__CTRL_ABORT() > 0))
	{
		CString log_msg;

		log_msg.Format("Aborted ... :  [%s] [Flag : %1d]",mode,flag);
		Fnc__APP_LOG(log_msg);
	}
	else
	{
		CString log_msg;

		log_msg.Format("Completed ... :  [%s]",mode);
		Fnc__APP_LOG(log_msg);
	}

	// ...
	{
		int i;

		for(i=0;i<iLPx_SIZE;i++)
		{
			sEXT_CH__LPx_MAP_SEQ_LOCK[i]->Set__DATA("");
		}
	}

	return flag;
}

int CObj__ATM_ROBOT_FUSION::__CALL__MONITORING(id, p_variable, p_alarm)
{
	switch(id)
	{
		case MON_ID__STATE_MONITOR:
			Mon__STATE_MONITOR(p_variable,p_alarm);
			break;
	}	
	return 1;
}
