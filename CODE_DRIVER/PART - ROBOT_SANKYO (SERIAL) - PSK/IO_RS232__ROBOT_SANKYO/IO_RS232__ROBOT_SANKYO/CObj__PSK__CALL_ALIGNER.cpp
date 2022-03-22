#include "StdAfx.h"
#include "CObj__PSK.h"
#include "CObj__PSK__DEF.h"
#include "CObj__PSK__ALID.h"

#include "Macro_Function.h"


// ...
int  CObj__PSK
::Call__ALGN(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{
	if(Is__ONLINE(p_alarm) < 0)
	{
		return -1;
	}

	//
	{
		CString ch_data;

		ch_data = aCH__OTR_IN_PARA__AL1_CCD_POS->Get__STRING();
		aCH__PARA_AL_NOTCH_ANGLE->Set__DATA(ch_data);

		//
		doCH__AL_COMMAND->Set__DATA(_AL_MODE__MEASURE_START);

		int r_flag = _Wait__RB_ACTION(p_variable, p_alarm);
		if(r_flag < 0)			return -11;
	}

	return 1;
}

int  CObj__PSK
::Call__ALGNPLACE(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return -1;
}

int  CObj__PSK
::Call__PLACE_PICK(CII_OBJECT__VARIABLE* p_variable, CII_OBJECT__ALARM* p_alarm)
{

	return -1;
}

