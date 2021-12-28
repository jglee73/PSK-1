#include "stdafx.h"

#include "CObj__LPx_CTRL__DEF.h"
#include "CObj__LPx_CTRL__ALID.h"
#include "CObj__LPx_CTRL.h"


// ...
void CObj__LPx_CTRL::
Mon__STATE_MONITOR(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	bool active__pio_check = false;
	bool active__init_mode_req = true;

	CString ch_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		if(bActive__SIM_MODE)
		{

		}

		if(sEXT_CH__MON_COMMUNICATION_STATE->Check__DATA(STR__OFFLINE) > 0)
		{
			int alarm_id = ALID__OFFLINE;
			CString r_act;

			p_alarm->Check__ALARM(alarm_id,r_act);
			p_alarm->Post__ALARM(alarm_id);
		}

		if(sEXT_CH__LP_INFO__AGV_STATUS->Check__DATA(STR__BUSY) > 0)
		{
			active__pio_check = true;

			dCH__MON_LPx_PIO_RUN_SNS->Set__DATA(STR__RUN);
			dCH__MON_LPx_PIO_TRANSFER_SNS->Set__DATA(STR__YES);
		}
		else
		{
			if(sEXT_CH__LP_INFO__AGV_STATUS->Check__DATA(STR__ERROR) > 0)
			{
				doEXT_CH__PIO_RESET->Set__DATA("SET");

				Sleep(500);
			}

			dCH__MON_LPx_PIO_TRANSFER_SNS->Set__DATA(STR__NO);

			if(active__pio_check)		dCH__MON_LPx_PIO_RUN_SNS->Set__DATA(STR__DONE);
			else						dCH__MON_LPx_PIO_RUN_SNS->Set__DATA(STR__STOP);
		}

		// MODE Check ...
		{
			bool active__mode_change = false;

			ch_data = sCH__PARA_LP_MODE->Get__STRING();
			if(dEXT_CH__CFG_LP_MODE->Check__DATA(ch_data) < 0)
			{
				if((ch_data.CompareNoCase(STR__MANUAL) == 0)
				|| (ch_data.CompareNoCase(STR__AMHS)   == 0))
				{
					dEXT_CH__CFG_LP_MODE->Set__DATA(ch_data);

					active__mode_change = true;
				}
			}

			ch_data = sCH__PARA_LP_RFID->Get__STRING();
			if(dEXT_CH__CFG_LP_RFID->Check__DATA(ch_data) < 0)
			{
				if((ch_data.CompareNoCase(STR__DISABLE) == 0)
				|| (ch_data.CompareNoCase(STR__READING) == 0))
				{
					dEXT_CH__CFG_LP_RFID->Set__DATA(ch_data);

					active__mode_change = true;
				}
			}

			ch_data = sCH__PARA_LP_USE->Get__STRING();
			if(dEXT_CH__CFG_LP_USE->Check__DATA(ch_data) < 0)
			{
				if((ch_data.CompareNoCase(STR__YES) == 0)
				|| (ch_data.CompareNoCase(STR__NO)  == 0))
				{
					dEXT_CH__CFG_LP_USE->Set__DATA(ch_data);

					active__mode_change = true;
				}
			}

			ch_data = sCH__PARA_LP_CLOSE_MAPPING->Get__STRING();
			if(dEXT_CH__CFG_LP_CLOSE_MAPPING->Check__DATA(ch_data) < 0)
			{
				if((ch_data.CompareNoCase(STR__YES) == 0)
				|| (ch_data.CompareNoCase(STR__NO)  == 0))
				{
					dEXT_CH__CFG_LP_CLOSE_MAPPING->Set__DATA(ch_data);

					active__mode_change = true;
				}
			}
			
			if(active__init_mode_req)
			{
				active__init_mode_req = false;
				active__mode_change = true;
			}

			if(active__mode_change)
			{
				doEXT_CH__LP_MODE->Set__DATA("SET");
			}
		}

		// ...
	}	
}
