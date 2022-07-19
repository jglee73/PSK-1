#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj_NET__VAC_PERSIMMON.h"



//----------------------------------------------------------
DECLARE_START__DLL_IO_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

DECLARE_END__DLL_IO_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__PERSIMMON_NET					"PERSIMMON.NET"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

	ADD__OBJ_CLS(CLS__PERSIMMON_NET);

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

	IF__OBJ_CLS(CLS__PERSIMMON_NET)			return (new CObj_NET__VAC_PERSIMMON);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK

