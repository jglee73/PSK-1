#include "stdafx.h"
#include "CClass__Macro_Font.h"


CClass__Macro_Font	mMacro_Font;


int CALLBACK MacroFont_CallBack(ENUMLOGFONT FAR *lpelf, 
								NEWTEXTMETRIC FAR *lpntm, 
								int FontType, 
								LPARAM lParam)
{
	return mMacro_Font.CallBack(lpelf,lpntm,FontType,lParam);
}


int CALLBACK CClass__Macro_Font::CallBack(ENUMLOGFONT FAR *lpelf, 
										 NEWTEXTMETRIC FAR *lpntm, 
										 int FontType, LPARAM lParam)
{
	if(mList_Num < 500) 
	{
		mFontLog[mList_Num] = lpelf->elfLogFont;
		mFontType[mList_Num] = FontType;

		mList_Num++;
		return TRUE;
	}
	else 
	{
		return FALSE;
	}

	return TRUE;
}

void CClass__Macro_Font::Search_Font(HWND hwnd)
{
	if(mList_Num < 1)
	{
		HDC hdc = ::GetDC(hwnd);

		EnumFontFamilies(hdc, 
						 NULL, 
						 (FONTENUMPROC)MacroFont_CallBack, 
						 (LPARAM)NULL);
		::ReleaseDC(hwnd,hdc);
	}
}

int  CClass__Macro_Font::Get_Font(CString font_name,LOGFONT *r_font,int *f_type)
{
	Search_Font(NULL);

	// ...
	int i;

	for(i=0; i<mList_Num; i++)
	{
		if(strcmp(mFontLog[i].lfFaceName, font_name) == 0)
		{
			*r_font = mFontLog[i];
			*f_type = mFontType[i];
			return 1;
		}
	}

	// ...
	CString font_default = "Fixedsys";

	for(i=0; i<mList_Num; i++)
	{
		if(strcmp(mFontLog[i].lfFaceName, font_default) == 0)
		{
			*r_font = mFontLog[i];
			*f_type = mFontType[i];
			return 1;
		}
	}
	return -1;
}
