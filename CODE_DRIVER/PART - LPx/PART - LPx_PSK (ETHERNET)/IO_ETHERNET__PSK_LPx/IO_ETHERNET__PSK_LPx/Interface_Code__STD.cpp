#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__LAMP_CTRL.h"
#include "CObj__LPx_CTRL.h"
#include "CObj__RFID_CTRL.h"


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
#define CLS__LAMP_CTRL				"LAMP.CTRL"
#define CLS__LPx_CTRL				"LPx.CTRL"
#define CLS__RFID_CTRL				"RFID.CTRL"


DECLARE_START__DLL_STD_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__LAMP_CTRL);
ADD__OBJ_CLS(CLS__LPx_CTRL);
ADD__OBJ_CLS(CLS__RFID_CTRL);

DECLARE_END__DLL_STD_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_STD_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__LAMP_CTRL)			return (new CObj__LAMP_CTRL);
IF__OBJ_CLS(CLS__LPx_CTRL)			return (new CObj__LPx_CTRL);
IF__OBJ_CLS(CLS__RFID_CTRL)			return (new CObj__RFID_CTRL);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
