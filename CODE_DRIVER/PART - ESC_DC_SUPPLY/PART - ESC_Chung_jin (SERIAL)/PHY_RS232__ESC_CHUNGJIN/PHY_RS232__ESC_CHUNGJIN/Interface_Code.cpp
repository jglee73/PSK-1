#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__APS_8301.h"



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
#define CLS__APS_8301				"APS.8301"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__APS_8301);

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__APS_8301)		    return (new CObj__APS_8301);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK

