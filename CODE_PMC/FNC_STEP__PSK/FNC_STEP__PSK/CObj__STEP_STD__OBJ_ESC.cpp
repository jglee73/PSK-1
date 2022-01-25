#include "StdAfx.h"
#include "CObj__STEP_STD.h"
#include "CObj__STEP_STD__DEF.h"


// ...
int CObj__STEP_STD
::ESC_OBJ__Start_MODE(const CString& obj_mode)
{
	if(!bActive__OBJ_CTRL__ESC)			return 1;

	return pOBJ_CTRL__ESC->Run__OBJECT(obj_mode);
}
