#include "StdAfx.h"
#include "CObj__DRV_LINK_ALx.h"
#include "CObj__DRV_LINK_ALx__DEF.h"
#include "CObj__DRV_LINK_ALx__ALID.h"


//------------------------------------------------------------------------------------
void CObj__DRV_LINK_ALx
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,
				  CII_OBJECT__ALARM* p_alarm)
{
	SCX__SEQ_INFO x_seq;

	SCX__ASYNC_TIMER_CTRL x_timer_ctrl;
	double sec_wait = 0.0;

	while(1)
	{
		Sleep(90);

		if(x_seq->Is__SIMULATION_MODE() > 0)
		{
			if(dCH__SIM_CFG__REAL_TEST->Check__DATA(STR__YES) > 0)
				iSim_Mode = -1;
			else
				iSim_Mode = 1;
		}
		else
		{
			iSim_Mode = -1;
		}

		if(iSim_Mode > 0)
		{
			if(sEXT_CH__ALx_CMMD_STS->Check__DATA(STR__RUN) > 0)
			{
				sEXT_CH__ALx_CMMD_STS->Set__DATA(STR__WAIT);

				sec_wait = aCH__SIM_CFG__ALIGN_TIME->Get__VALUE();
				x_timer_ctrl->START__COUNT_UP(sec_wait + 100);
			}
			else if(sEXT_CH__ALx_CMMD_STS->Check__DATA(STR__WAIT) > 0)
			{
				if(x_timer_ctrl->Get__CURRENT_TIME() >= sec_wait)
				{
					x_timer_ctrl->STOP();

					sEXT_CH__ALx_CMMD_STS->Set__DATA(STR__IDLE);
				}
			}
		}
		else
		{

		}
	}	
}
