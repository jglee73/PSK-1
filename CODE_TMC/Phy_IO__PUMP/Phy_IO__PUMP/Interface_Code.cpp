#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__EDWARD_IPX.h"
#include "CObj__VIRTUAL_STD.h"


//----------------------------------------------------------
DECLARE_START__DLL_STD_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

DECLARE_END__DLL_STD_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__EDWARD_IPX  				"EDWARD.IPX"
#define CLS__VIRTUAL_STD				"VIRTUAL.STD"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__EDWARD_IPX);
ADD__OBJ_CLS(CLS__VIRTUAL_STD);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__EDWARD_IPX)		return (new CObj__EDWARD_IPX);
IF__OBJ_CLS(CLS__VIRTUAL_STD)		return (new CObj__VIRTUAL_STD);

DECLARE_END__DLL_STD_OBJ__CREATE_LINK
