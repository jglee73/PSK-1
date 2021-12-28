#include "StdAfx.h"
#include "CObj__CHM_IO.h"
#include "CObj__CHM_IO__ALID.h"
#include "CObj__CHM_IO__DEF.h"


// ...
int CObj__CHM_IO
::Mon__STATUS(CII_OBJECT__VARIABLE *p_variable,CII_OBJECT__ALARM *p_alarm)
{
	CString ch_data;

	if(iSIM_MODE > 0)
	{
		dEXT_CH__DI_VAC_SNS->Set__DATA(STR__ON);
		dEXT_CH__DI_ATM_SNS->Set__DATA(STR__OFF);
	}

	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);

		// ...
		int interlock__do_iso_vlv = 1;

		if((dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__DISABLE)     > 0)
		|| (dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__ALL_DISABLE) > 0))
		{
			interlock__do_iso_vlv = -1;

			if(dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__ALL_DISABLE) > 0)
			{
				int alm_id = ALID__MONITORING_INTERLOCK__DISABLE;
				CString r_act;

				p_alarm->Check__ALARM(alm_id, r_act);
				p_alarm->Post__ALARM(alm_id);
			}
		}
		else if(dEXT_CH__CFG_INTERLOCK_USE_MODE->Check__DATA(STR__CONTROL) > 0)
		{
			if(dEXT_CH__CFG_INTERLOCK_USE__CHM_MANOMETER_ISO->Check__DATA(STR__DISABLE) > 0)
			{
				interlock__do_iso_vlv = -1;
			}
		}

		// ...
		{
			int vac_flag = -1;
			int atm_flag = -1;

			if((dEXT_CH__DI_VAC_SNS->Check__DATA(STR__ON)  > 0)
			&& (dEXT_CH__DI_ATM_SNS->Check__DATA(STR__OFF) > 0))
			{
				vac_flag = 1;
			}
			else if((dEXT_CH__DI_VAC_SNS->Check__DATA(STR__OFF)  > 0)
				 && (dEXT_CH__DI_ATM_SNS->Check__DATA(STR__ON)   > 0))
			{
				atm_flag = 1;
			}

			if(interlock__do_iso_vlv > 0)
			{
				if(vac_flag > 0)		dEXT_CH__DO_MANOMETER_ISO_VLV->Set__DATA(STR__OPEN);
				else					dEXT_CH__DO_MANOMETER_ISO_VLV->Set__DATA(STR__CLOSE);
			}

			if(vac_flag > 0)			
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__ON);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);

				if(dEXT_CH__DO_MANOMETER_ISO_VLV->Check__DATA(STR__OPEN) > 0)
				{
					double cfg_max_torr = aEXT_CH__CFG_PROCESS_MANOMETER_MAX_PRESSURE_mTORR->Get__VALUE();
					cfg_max_torr = cfg_max_torr * 0.001;

					double cur_press = aEXT_CH__AI_MANOMETER_TORR->Get__VALUE();

					if(cur_press <= cfg_max_torr)
					{
						ch_data.Format("%.3f", cur_press);
						sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

						ch_data.Format("%.1f", cur_press*1000.0);
						sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);
					}
				}
			}
			else if(atm_flag > 0)			
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__ON);

				// ...
				double cur_press = 760.0;

				ch_data.Format("%.1f", cur_press);
				sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_press*1000.0);
				sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);

				sEXT_CH__SIM_PRESSURE_TORR->Set__DATA("760.0");
			}
			else
			{
				sEXT_CH__CHM_VAC_SNS->Set__DATA(STR__OFF);
				sEXT_CH__CHM_ATM_SNS->Set__DATA(STR__OFF);

				// ...
				double cur_press = 500.0;

				ch_data.Format("%.1f", cur_press);
				sEXT_CH__CHM_PRESSURE_VALUE->Set__DATA(ch_data);

				ch_data.Format("%.1f", cur_press*1000.0);
				sEXT_CH__CHM_PRESSURE_mTORR->Set__DATA(ch_data);

				sEXT_CH__SIM_PRESSURE_TORR->Set__DATA("10.0");
			}
		}

		// ...
		{
			sEXT_CH__CHM_PRESSURE_VALUE->Get__DATA(ch_data);
			double cur_chm_press = atof(ch_data);

			aEXT_CH__AI_FORELINE_PRESSURE_TORR->Get__DATA(ch_data);
			sEXT_CH__PMP_PRESSURE_VALUE->Set__DATA(ch_data);
			double cur_pmp_press = atof(ch_data);

			     if(cur_pmp_press < 10.0)		sEXT_CH__PMP_PRESSURE_STATE->Set__DATA("VAC");
			else if(cur_pmp_press < 730)		sEXT_CH__PMP_PRESSURE_STATE->Set__DATA("BTW");
			else								sEXT_CH__PMP_PRESSURE_STATE->Set__DATA("ATM");

			if(cur_pmp_press < 10.0)			sEXT_CH__PMP_VAC_SNS->Set__DATA(STR__ON);
			else								sEXT_CH__PMP_VAC_SNS->Set__DATA(STR__OFF);
		}

		// ...
		{
			double cur_ppwer = 0.0;

			cur_ppwer += aEXT_CH__HF_RF_POWER->Get__VALUE();
			cur_ppwer += aEXT_CH__LF_RF_POWER->Get__VALUE();
			cur_ppwer += aEXT_CH__BIAS_RF_POWER->Get__VALUE();

			if(cur_ppwer > 0.1)		sEXT_CH__RF_ON_STATE->Set__DATA(STR__ON);
			else					sEXT_CH__RF_ON_STATE->Set__DATA(STR__OFF);
		}
	}

	return 1;
}
