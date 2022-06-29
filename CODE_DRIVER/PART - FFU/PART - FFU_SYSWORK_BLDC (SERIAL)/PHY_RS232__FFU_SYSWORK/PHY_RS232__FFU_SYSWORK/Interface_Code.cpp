#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__LV32_BLDC.h"



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
#define CLS__LV32_BLDC						"LV32.BLDC"	


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__LV32_BLDC)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__LV32_BLDC)					return (new CObj__LV32_BLDC);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
