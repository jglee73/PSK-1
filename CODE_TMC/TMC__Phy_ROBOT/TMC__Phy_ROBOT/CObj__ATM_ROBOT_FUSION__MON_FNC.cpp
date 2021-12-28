#include "StdAfx.h"
#include "CObj__ATM_ROBOT_FUSION.h"
#include "CObj__ATM_ROBOT_FUSION__DEF.h"
#include "CObj__ATM_ROBOT_FUSION__ALID.h"


// ...
void CObj__ATM_ROBOT_FUSION::
Mon__STATE_MONITOR(CII_OBJECT__VARIABLE* p_variable, 
				   CII_OBJECT__ALARM *p_alarm)
{
	int i;
	int k;

	while(1)
	{
		Sleep(500);

		if(sCH__TAS_RESET_REQ->Check__DATA("") < 0)
		{
			sCH__TAS_RESET_REQ->Set__DATA("");

			for(i=0; i<CFG_ACT__SIZE; i++)
			{
				// Robot ...
				{
					sCH__TAS_ACTION_TIME_NOW__RB[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MIN__RB[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MAX__RB[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG__RB[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG_F__RB[i]->Set__DATA("");
					aCH__TAS_ACTION_TIME_CNT__RB[i]->Set__VALUE(1);
				}

				// LPx ...
				for(k=0; k<CFG_LPx__SIZE; k++)
				{
					sCH__TAS_ACTION_TIME_NOW__LPx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MIN__LPx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MAX__LPx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG__LPx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG_F__LPx[i][k]->Set__DATA("");
					aCH__TAS_ACTION_TIME_CNT__LPx[i][k]->Set__VALUE(1);
				}

				// AL1 ...
				{
					sCH__TAS_ACTION_TIME_NOW__AL1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MIN__AL1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MAX__AL1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG__AL1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG_F__AL1[i]->Set__DATA("");
					aCH__TAS_ACTION_TIME_CNT__AL1[i]->Set__VALUE(1);
				}

				// LLx ...
				for(k=0; k<CFG_LLx__SIZE; k++)
				{
					sCH__TAS_ACTION_TIME_NOW__LLx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MIN__LLx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MAX__LLx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG__LLx[i][k]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG_F__LLx[i][k]->Set__DATA("");
					aCH__TAS_ACTION_TIME_CNT__LLx[i][k]->Set__VALUE(1);
				}

				// ST1 ...
				{
					sCH__TAS_ACTION_TIME_NOW__ST1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MIN__ST1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MAX__ST1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG__ST1[i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG_F__ST1[i]->Set__DATA("");
					aCH__TAS_ACTION_TIME_CNT__ST1[i]->Set__VALUE(1);
				}
			}
		}

		// ...
	}
}
