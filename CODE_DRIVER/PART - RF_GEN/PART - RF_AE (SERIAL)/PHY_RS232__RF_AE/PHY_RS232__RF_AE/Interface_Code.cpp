#include "StdAfx.h"
#include "Interface_Code.h"

#include "CObj__OVATION_2560.h"
#include "CObj__PARAMOUNT_HF.h"



//----------------------------------------------------------
//DECLARE_START__DLL_STD_OBJ__GET_VERSION
DECLARE_START__DLL_IO_OBJ__GET_VERSION

#ifdef _DEBUG
debug_mode =  1;
#else
debug_mode = -1;			
#endif

//DECLARE_END__DLL_STD_OBJ__GET_VERSION
DECLARE_END__DLL_IO_OBJ__GET_VERSION
//----------------------------------------------------------


//----------------------------------------------------------
#define CLS__OVATION_2560						"OVATION.2560"
#define CLS__PARAMOUNT_HF						"PARAMOUNT.HF"


DECLARE_START__DLL_IO_OBJ__GET_CLASS_LIST

ADD__OBJ_CLS(CLS__OVATION_2560)
ADD__OBJ_CLS(CLS__PARAMOUNT_HF)

DECLARE_END__DLL_IO_OBJ__GET_CLASS_LIST


DECLARE_START__DLL_IO_OBJ__CREATE_LINK

IF__OBJ_CLS(CLS__OVATION_2560)					return (new CObj__OVATION_2560);
IF__OBJ_CLS(CLS__PARAMOUNT_HF)					return (new CObj__PARAMOUNT_HF);

DECLARE_END__DLL_IO_OBJ__CREATE_LINK
