#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__NAVII_SERIAL.h"



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
#define CLS__NAVII_SERIAL						"NAVII.SERIAL"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__NAVII_SERIAL)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__NAVII_SERIAL)					return (new CObj__NAVII_SERIAL);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
