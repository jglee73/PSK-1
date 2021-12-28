#include "StdAfx.h"
#include "CObj__CHM_FNC.h"
#include "CObj__CHM_FNC__DEF.h"
#include "CObj__CHM_FNC__ALID.h"


// ...
void CObj__CHM_FNC::
Mon__PRESSURE_STATUS(CII_OBJECT__VARIABLE *p_variable, CII_OBJECT__ALARM *p_alarm)
{
	double  cur_chm_press;
	double  ref_atm_press;
	double  ref_vac_press;
	CString pre_slit_vlv_sts;

	CString var_data;


	while(1)
	{
		p_variable->Wait__SINGLE_OBJECT(0.1);	


		/*
		// ...
		{
			dEXT_CH__PMC_SLIT_VLV_STS->Get__DATA(var_data);
			if(var_data.CompareNoCase(STR__CLOSE) != 0)
			{
				if(pre_slit_vlv_sts != var_data)
				{
					if(sCH__TRANSFER_BALLAST_FLAG->Check__DATA(STR__YES) > 0)
					{
						sCH__TRANSFER_BALLAST_FLAG->Set__DATA("");

						// Fnc__BALLAST_POSITION(p_variable);
						Fnc__BALLAST_PRESSURE(p_variable);
					}
				}
			}
			pre_slit_vlv_sts = var_data;
		}
		*/

		// ...
		{
			ref_atm_press = aCH__CFG_ATM_PRESSURE->Get__VALUE();
			ref_vac_press = aCH__CFG_PUMPING_PRESSURE->Get__VALUE();
			cur_chm_press = aEXT_CH__CHM_PRESSURE_TORR->Get__VALUE();

				 if(cur_chm_press >= ref_atm_press)			sCH__CHM_PRESS_STS->Set__DATA(STR__ATM);
			else if(cur_chm_press <= ref_vac_press)			sCH__CHM_PRESS_STS->Set__DATA(STR__VAC);
			else											sCH__CHM_PRESS_STS->Set__DATA(STR__BTW);
		}
	}
}

