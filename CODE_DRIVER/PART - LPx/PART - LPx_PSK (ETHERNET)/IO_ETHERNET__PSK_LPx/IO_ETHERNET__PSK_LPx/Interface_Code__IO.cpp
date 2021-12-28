#include "StdAfx.h"
#include "Interface_Code.h"

#include "CDriver__LPx_ETHERNET.h"



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
#define CLS__DRIVER_LPx_ETHERNET			"DRIVER.LPx_ETHERNET"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__DRIVER_LPx_ETHERNET);

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__DRIVER_LPx_ETHERNET)		return (new CDriver__LPx_ETHERNET);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
