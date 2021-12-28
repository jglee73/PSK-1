#include "StdAfx.h"
#include "CObj__PMC_SIMPLE.h"
#include "CObj__PMC_SIMPLE__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__PMC_SIMPLE
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	if(iSim_Flag > 0)
	{
		for(int i=0; i<m_nPM_LIMIT; i++)
		{
			if(dEXT_CH__CFG_PMx_EXIST_FLAG[i]->Check__DATA("YES") < 0)
			{
				dCH__SLIT_VALVE_STATUS[i]->Set__DATA(STR__CLOSE);
			}
			else
			{
				diEXT_CH__PMx__SV_OPEN[i]->Set__DATA(STR__OFF);
				diEXT_CH__PMx__SV_CLOSE[i]->Set__DATA(STR__ON);
			}
		}
	}

	
	while(1)
	{
		Sleep(500);


		// TAS RESET ...
		{
			for(int pm_i=0; pm_i<CFG_PMx__SIZE; pm_i++)
			{
				if(sCH__TAS_RESET_REQ__PMx[pm_i]->Check__DATA("") > 0)
				{
					continue;
				}
				sCH__TAS_RESET_REQ__PMx[pm_i]->Set__DATA("");
				
				for(int i=0; i<CFG_ACT__SIZE; i++)
				{
					sCH__TAS_ACTION_TIME_NOW__PMx[i][pm_i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MIN__PMx[i][pm_i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_MAX__PMx[i][pm_i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG__PMx[i][pm_i]->Set__DATA("");
					sCH__TAS_ACTION_TIME_AVG_F__PMx[i][pm_i]->Set__DATA("");
					aCH__TAS_ACTION_TIME_CNT__PMx[i][pm_i]->Set__VALUE(1);
				}
			}
		}

		Update__IO_MONITOR();
	}	
}

void CObj__PMC_SIMPLE
::Update__IO_MONITOR()
{
	CString str__sv_open;
	CString str__sv_close;

	CString str_atm_sns;
	CString str_vac_sns;

	int i;


	for(i=0; i<m_nPM_LIMIT; i++)
	{
		Sleep(10);


		if(dEXT_CH__CFG_PMx_EXIST_FLAG[i]->Check__DATA("YES") < 0)
		{
			dCH__SLIT_VALVE_STATUS[i]->Set__DATA(STR__CLOSE);		// SV가 NONE이면 CLOSE로 간주
		}
		else
		{
			diEXT_CH__PMx__SV_OPEN[i]->Get__DATA(str__sv_open);
			diEXT_CH__PMx__SV_CLOSE[i]->Get__DATA(str__sv_close);

			// ...
			int close_flag = -1;
			int open_flag  = -1;

			if(dEXT_CH__CFG_PMx_SV_USE[i]->Check__DATA("NO") > 0)
			{
				open_flag = 1;
			}
			else
			{
				if((str__sv_open.CompareNoCase(STR__OFF) == 0)
				&& (str__sv_close.CompareNoCase(STR__ON) == 0))
				{
					close_flag = 1;
				}
				else if((str__sv_open.CompareNoCase(STR__ON) == 0)
					 && (str__sv_close.CompareNoCase(STR__OFF) == 0))
				{
					open_flag = 1;
				}
			}

			/*
			// ...
			{
				CString log_msg;
				CString log_bff;

				log_msg = "CObj__PMC_SIMPLE::Update__IO_MONITOR() ... \n";
				
				log_bff.Format(" * PM%1d \n", i+1);
				log_msg += log_bff;
				log_bff.Format("  ** open_flag  [%1d] \n", open_flag);
				log_msg += log_bff;
				log_bff.Format("  ** close_flag [%1d] \n", close_flag);
				log_msg += log_bff;

				log_bff.Format("  ** %s <- [%s] \n", 
					           dEXT_CH__CFG_PMx_SV_USE[i]->Get__CHANNEL_NAME(),
							   dEXT_CH__CFG_PMx_SV_USE[i]->Get__STRING());
				log_msg += log_bff;

				printf(log_msg);
			}
			*/

			if(close_flag > 0)
			{
				dCH__SLIT_VALVE_STATUS[i]->Set__DATA(STR__CLOSE);
			}
			else if(open_flag > 0)
			{
				dCH__SLIT_VALVE_STATUS[i]->Set__DATA(STR__OPEN);
			}
			else
			{
				dCH__SLIT_VALVE_STATUS[i]->Set__DATA(STR__UNKNOWN);
			}
		}

		// PMx Pressure Sts...
		diEXT_CH__PMx__ATM_SNS[i]->Get__DATA(str_atm_sns);
		diEXT_CH__PMx__VAC_SNS[i]->Get__DATA(str_vac_sns);

		if(iSim_Flag > 0)
		{
			if(dEXT_CH__CFG_TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
			{
				diEXT_CH__PMx__ATM_SNS[i]->Set__DATA(STR__ON);
				diEXT_CH__PMx__VAC_SNS[i]->Set__DATA(STR__OFF);
			}
			else
			{
				diEXT_CH__PMx__ATM_SNS[i]->Set__DATA(STR__OFF);
				diEXT_CH__PMx__VAC_SNS[i]->Set__DATA(STR__ON);
			}
		}

		if(dEXT_CH__CFG_PMx_CHM_TYPE[i]->Check__DATA(STR__DUMMY) > 0)
		{
			if(dEXT_CH__CFG_TRANSFER_MODE->Check__DATA(STR__ATM) > 0)
			{
				dCH__PRESS_STATUS[i]->Set__DATA(STR__ATM);
			}
			else
			{
				dCH__PRESS_STATUS[i]->Set__DATA(STR__VAC);
			}
		}
		else
		{
			if((str_atm_sns.CompareNoCase("ON")  == 0) 
			&& (str_vac_sns.CompareNoCase("OFF") == 0))
			{
				dCH__PRESS_STATUS[i]->Set__DATA(STR__ATM);
			}
			else if((str_atm_sns.CompareNoCase("OFF") == 0) 
				 && (str_vac_sns.CompareNoCase("ON")  == 0) )
			{
				dCH__PRESS_STATUS[i]->Set__DATA(STR__VAC);
			}
			else
			{
				dCH__PRESS_STATUS[i]->Set__DATA(STR__BTW);
			}
		}
	}

	// ...
}
