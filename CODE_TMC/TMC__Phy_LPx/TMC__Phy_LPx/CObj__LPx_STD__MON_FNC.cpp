#include "StdAfx.h"
#include "CObj__LPx_STD.h"
#include "CObj__LPx_STD__DEF.h"


//----------------------------------------------------------------------------------------------------
void CObj__LPx_STD
::Mon__IO_MONITOR(CII_OBJECT__VARIABLE* p_variable,CII_OBJECT__ALARM* p_alarm)
{
	CString var_data;

	while(1)
	{
		Sleep(9);

		sEXT_CH__LPx__CLAMP_STS->Get__DATA(var_data);
		sCH__CLAMP_STS->Set__DATA(var_data);

		sEXT_CH__LPx__FOUP_STS->Get__DATA(var_data);
		sCH__FOUP_STS->Set__DATA(var_data);

		sEXT_CH__LPx__FOUP_POS->Get__DATA(var_data);
		sCH__FOUP_POS->Set__DATA(var_data);

		sEXT_CH__LPx__DOOR_STS->Get__DATA(var_data);
		sCH__DOOR_STS->Set__DATA(var_data);

		sEXT_CH__TRANSFER_PIO_STATUS->Get__DATA(var_data);
		sCH__TRANSFER_PIO_STATUS->Set__DATA(var_data);

		// RELOAD FLAG !!
		sCH__CFG_RELOAD_FLAG->Get__DATA(var_data);
		sEXT_CH__RELOAD_FLAG->Set__DATA(var_data);

		// FA MODE !!
		sCH__CFG_FA_MODE->Get__DATA(var_data);	

		if((var_data.CompareNoCase("AUTO")   == 0)
		|| (var_data.CompareNoCase("MANUAL") == 0))
		{
			sEXT_CH__FA_MODE->Set__DATA(var_data);
			sEXT_CH__RFx__FA_MODE->Set__DATA(var_data);
		}

		// FA SERVICE REQ !!
		sCH__CFG_FA_SERVICE_MODE->Get__DATA(var_data);

		sEXT_CH__FA_SERVICE_MODE->Set__DATA(var_data);
		sEXT_CH__RFx__FA_SERVICE_MODE->Set__DATA(var_data);
	}	
}
