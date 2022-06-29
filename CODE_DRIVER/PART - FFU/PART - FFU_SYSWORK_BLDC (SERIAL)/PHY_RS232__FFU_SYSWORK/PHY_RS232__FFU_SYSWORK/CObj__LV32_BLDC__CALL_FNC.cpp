#include "StdAfx.h"
#include "CObj__LV32_BLDC.h"


// ...
int  CObj__LV32_BLDC
::Call__INIT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(dCH__CFG_FFU_TYPE->Check__DATA(STR__RPM) > 0)
	{
		double cfg_set = aCH__CFG_FFU_INITIAL_RPM->Get__VALUE();
		aCH__PARA_FFU_BLOCK_RPM_SV->Set__VALUE(cfg_set);

		if(iActive_SIM > 0)
		{
			CString ch_data;

			for(int i=0; i<CFG__FAN_SIZE; i++)
			{
				ch_data.Format("%.0f", cfg_set);

				sCH__FFU_BLOCK__RPM_PV_X[i]->Set__DATA(ch_data);
				sCH__FFU_BLOCK__RPM_SV_X[i]->Set__DATA(ch_data);
			}	
		}

		doCH__FFU_BLOCK_SET->Set__DATA(STR__SET);
	}
	else
	{
		double cfg_set = aCH__PARA_FFU_UNIT_DIFF_PRESSURE->Get__VALUE();
		aCH__CFG_FFU_INITIAL_DIFF_PRESSURE->Set__VALUE(cfg_set);

		if(iActive_SIM > 0)
		{
			CString ch_data;

			ch_data.Format("%.0f", cfg_set);
			sCH__FFU_UNIT__PRESSURE_VALUE->Set__DATA(ch_data);
		}

		doCH__FFU_UNIT_SET->Set__DATA(STR__SET);
	}

	// ...
	{
		CString ch_data = dCH__CFG_FFU_TYPE->Get__STRING();

		sCH__CUR_FFU_TYPE->Set__DATA(ch_data);
	}

	if(sCH__MON_COMMUNICATION_STATE->Check__DATA(STR__ONLINE) < 0)
	{
		return -1;
	}
	return 1;
}

int  CObj__LV32_BLDC
::Call__CHECK_PACKET_FORMAT(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	unsigned char r_data[CFG__MAX_DATA];
	unsigned char cmmd_byte;
	int set_sv;

	// UNIT_GET ...
	{
		cmmd_byte = _CMMD_MODE__UNIT_GET;

		_Check_Command(cmmd_byte, r_data);
	}
	// BLOCK_GET ...
	{
		cmmd_byte = _CMMD_MODE__BLOCK_GET;

		_Check_Command(cmmd_byte, r_data);
	}

	// UNIT_SET ...
	{
		cmmd_byte  = _CMMD_MODE__UNIT_SET;
		set_sv = (int) aCH__PARA_FFU_UNIT_DIFF_PRESSURE->Get__VALUE();
		
		_Check_Command(cmmd_byte, r_data, set_sv);
	}
	// BLOCK_SET ...
	{
		cmmd_byte  = _CMMD_MODE__BLOCK_SET;
		set_sv = (int) aCH__PARA_FFU_BLOCK_RPM_SV->Get__VALUE();
		
		_Check_Command(cmmd_byte, r_data, set_sv);
	}

	return 1;
}
