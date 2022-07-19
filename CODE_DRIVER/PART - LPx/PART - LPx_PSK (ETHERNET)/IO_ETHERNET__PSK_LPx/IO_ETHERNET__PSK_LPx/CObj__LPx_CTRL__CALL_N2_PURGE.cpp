#include "stdafx.h"

#include "CObj__LPx_CTRL.h"
#include "CObj__LPx_CTRL__DEF.h"


// ...
int	CObj__LPx_CTRL
::Call__N2_PURGE_CONTROL(CII_OBJECT__VARIABLE* p_variable,
						 CII_OBJECT__ALARM* p_alarm, 
						 const bool active__purge_start)
{
	if(active__purge_start)
	{
		CString para__mfc_set   = aCH__PARA_N2_PURGE_MFC_SET->Get__STRING();
		CString para__delay_sec = aCH__PARA_N2_PURGE_DELAY_TIME->Get__STRING();

		return _Fnc__N2_PURGE_CONTROL(active__purge_start, para__mfc_set,para__delay_sec);
	}
	else
	{
		CString para__mfc_set   = "0";
		CString para__delay_sec = "0";

		return _Fnc__N2_PURGE_CONTROL(active__purge_start, para__mfc_set,para__delay_sec);
	}

	return 1;
}

int	CObj__LPx_CTRL
::_Fnc__N2_PURGE_CONTROL(const bool active__purge_start, const CString& mfc_set,const CString& delay_sec)
{
	if(active__purge_start)
	{
		aEXT_CH__PARA_LP_N2_NOZZLE_1__MFC->Set__DATA(mfc_set);
		aEXT_CH__PARA_LP_N2_NOZZLE_2__MFC->Set__DATA(mfc_set);
		aEXT_CH__PARA_LP_N2_NOZZLE_3__MFC->Set__DATA(mfc_set);

		dEXT_CH__PARA_LP_N2_EHHAUST_NOZZLE->Set__DATA(STR__ON);
		aEXT_CH__PARA_LP_N2_DELAY_TIME->Set__DATA(delay_sec);

		return doEXT_CH__LP_N2_RUN->Set__DATA(STR__START);
	}
	else
	{
		aEXT_CH__PARA_LP_N2_NOZZLE_1__MFC->Set__DATA(mfc_set);
		aEXT_CH__PARA_LP_N2_NOZZLE_2__MFC->Set__DATA(mfc_set);
		aEXT_CH__PARA_LP_N2_NOZZLE_3__MFC->Set__DATA(mfc_set);

		dEXT_CH__PARA_LP_N2_EHHAUST_NOZZLE->Set__DATA(STR__OFF);
		aEXT_CH__PARA_LP_N2_DELAY_TIME->Set__DATA(delay_sec);

		return doEXT_CH__LP_N2_RUN->Set__DATA(STR__STOP);
	}

	return -11;
}
