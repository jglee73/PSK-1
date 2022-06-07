#pragma once


class CClass__Macro_Font
{
public:
	LOGFONT		mFontLog[500];		
	int			mFontType[500];	
	int			mList_Num;

	// ...
	int  CALLBACK CallBack(ENUMLOGFONT FAR *lpelf, 
						   NEWTEXTMETRIC FAR *lpntm, 
						   int FontType, 
						   LPARAM lParam);

	void Search_Font(HWND hwnd);
	int  Get_Font(CString font_name,LOGFONT *r_font,int *f_type);
};
