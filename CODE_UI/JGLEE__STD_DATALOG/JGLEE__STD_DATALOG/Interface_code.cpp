#include "StdAfx.h"

#include "CObj__Log_List.h"
#include "CObj__Log_View.h"


// ...
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	CString cls_name = str_gobj;
	CString gobj_name;
	
	// ...
	{
		gobj_name = "LOG_LIST";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Log_List);
		}
	}
	// ...
	{
		gobj_name = "LOG_VIEW";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Log_View);
		}
	}
	
	return NULL;
}


