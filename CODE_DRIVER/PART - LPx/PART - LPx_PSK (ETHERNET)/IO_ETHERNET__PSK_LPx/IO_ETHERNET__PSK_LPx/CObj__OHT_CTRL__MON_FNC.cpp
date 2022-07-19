#include "StdAfx.h"
#include "CObj__OHT_CTRL.h"
#include "CObj__OHT_CTRL__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__OHT_CTRL
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		
		// PIO.CHECK ...
		{
			CString cur_sts = sEXT_CH__LP_INFO__AGV_STATUS->Get__STRING();

		    if(cur_sts.CompareNoCase(STR__BUSY) == 0)
			{
			   dCH__REPORT_PIO_E84_RUN_STATE->Set__DATA(STR__RUN);
			   dEXT_CH__LINK_PIO_TRANSFER_STATE->Set__DATA(STR__YES);
		    }
			else if(cur_sts.CompareNoCase(STR__READY) == 0)
			{
				if(dEXT_CH__LINK_PIO_ACTIVE_RUN->Check__DATA(STR__ON) > 0)			ch_data = STR__DONE;
				else																ch_data = STR__STOP;

				dCH__REPORT_PIO_E84_RUN_STATE->Set__DATA(ch_data);
				dEXT_CH__LINK_PIO_TRANSFER_STATE->Set__DATA(STR__NO);
			}
			else
			{
				if(cur_sts.CompareNoCase(STR__ERROR) == 0)			ch_data = STR__STOP;
				else												ch_data = STR__UNKNOWN;
			
				dCH__REPORT_PIO_E84_RUN_STATE->Set__DATA(ch_data);
			}
		}

		// USER_REQ ...
		if(dCH__USER_REQ_PIO_RESET->Check__DATA(STR__ON) > 0)
		{
			dCH__USER_REQ_PIO_RESET->Set__DATA(STR__OFF);

			doEXT_CH__LP__PIO_RESET->Set__DATA(STR__SET);
		}

		// FA_AUTO ...
		if(dEXT_CH__LINK_PIO_ACTIVE_FA_AUTO->Check__DATA(STR__ON) > 0)
		{

		}

		// LOAD.REQ ...
		if(dEXT_CH__LINK_PIO_ACTIVE_LOAD_REQ->Check__DATA(STR__ON) > 0)
		{

		}
		// UNLOAD.REQ ...
		if(dEXT_CH__LINK_PIO_ACTIVE_UNLOAD_REQ->Check__DATA(STR__ON) > 0)
		{

		}
	}	
}

