#include "StdAfx.h"

#include "CObj__Active_STD.h"
#include "CObj__Ctrl_STD.h"
#include "CObj__Ctrl_LIST.h"
#include "CObj__Display_STD.h"
#include "CObj__FA_Property_STD.h"
#include "CObj__Percent_Bar_STD.h"
#include "CObj__Percent_Bar_TEXT.h"
#include "CObj__Recipe_Select_STD.h"
#include "CObj__Status_Box.h"
#include "CObj__Status_STD.h"
#include "CObj__Title_STD.h"
#include "CObj__Text_String_STD.h"


//--------------------------------------------------------------------------------------
extern "C" __declspec(dllexport) 
GObj__Interface_Ctrl* Create_GObj(const CString& str_gobj)
{
	CString cls_name = str_gobj;
	CString gobj_name;

	// ...
	{
		gobj_name = "ACTIVE.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Active_STD);
		}
	}
	// ...
	{
		gobj_name = "CTRL.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Ctrl_STD);
		}
	}
	// ...
	{
		gobj_name = "CTRL.LIST";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Ctrl_LIST);
		}
	}
	// ...
	{
		gobj_name = "DISPLAY.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Display_STD);
		}
	}
	// ...
	{
		gobj_name = "FA_PROPERTY.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__FA_Property_STD);
		}
	}
	// ...
	{
		gobj_name = "PERCENT_BAR.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Percent_Bar_STD);
		}
	}
	// ...
	{
		gobj_name = "PERCENT_BAR.TEXT";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Percent_Bar_TEXT);
		}
	}
	// ...
	{
		gobj_name = "RECIPE_SELECT.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Recipe_Select_STD);
		}
	}
	// ...
	{
		gobj_name = "STATUS.BOX";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Status_Box);
		}
	}
	// ...
	{
		gobj_name = "STATUS.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Status_STD);
		}
	}
	// ...
	{
		gobj_name = "TITLE.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Title_STD);
		}
	}
	// ...
	{
		gobj_name = "TEXT_STRING.STD";

		if(cls_name.CompareNoCase(gobj_name) == 0)
		{
			return (new CObj__Text_String_STD);
		}
	}

	return NULL;
}
