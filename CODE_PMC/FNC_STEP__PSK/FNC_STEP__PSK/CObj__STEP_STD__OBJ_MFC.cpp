#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::MFC_OBJ__Start_CONTROL(const int mfc_index, const CString& para_flow)
{
	if(mfc_index <  0)						return -11;
	if(mfc_index >= iDATA__MFC_SIZE)		return -12;

	// ...
	CString obj_mode;
	double  set_flow = atof(para_flow);

	if(set_flow > 0.1)
	{
		obj_mode = _MFC_CMD__CONTROL;

		sEXT_CH__MFC_X__PARA_SET_FLOW[mfc_index]->Set__DATA(para_flow);
		sEXT_CH__MFC_X__PARA_RAMP_SEC[mfc_index]->Set__DATA("0.0");
	}
	else
	{
		obj_mode = _MFC_CMD__CLOSE;

		sEXT_CH__MFC_X__PARA_SET_FLOW[mfc_index]->Set__DATA("0.0");
		sEXT_CH__MFC_X__PARA_RAMP_SEC[mfc_index]->Set__DATA("0.0");
	}

	return pOBJ_CTRL__MFC_X[mfc_index]->Run__OBJECT(obj_mode);
}

int CObj__STEP_STD
::MFC_OBJ__Check_ERROR()
{
	for(int i=0; i<iDATA__MFC_SIZE; i++)
	{
		if(dEXT_CH__MFC_X__MON_MFC_ABORT_ACTIVE[i]->Check__DATA(STR__ON) > 0)		return 1;
	}

	return -1;
}
