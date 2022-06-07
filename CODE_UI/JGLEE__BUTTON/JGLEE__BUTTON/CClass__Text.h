#pragma once

#include "Afxwin.h"


class CClass__Text
{
private:
	CRITICAL_SECTION mCS_Lock;
	int	mInit_Flag;

	// ...
	HDC		xHDC_IMG;
	HBITMAP	mBIT_IMG;

	HDC		xHDC_BFF;
	HBITMAP	mBIT_BFF;

	POINT	mSt;
	POINT	mEt;
	POINT	mSize;
	POINT	mPt_Text;

	int	mText_Width;
	int	mText_Height;
	int	mText_Weight;

	CString	 mTitle;
	CString	 mTitle_Pre;
	COLORREF mColor_Text;
	CString	 mMode;
	CString  mFormat;
	CString  mFont_Name;
	//

public:
	CClass__Text();
	~CClass__Text();

	// ...
	void Create_DC();
	void Delete_DC();

	void Init(const POINT& st,const POINT& et);
	void Init(HDC hdc_back);

	void Set_FontName(const CString& font_name);
	void Set_Fonmat(const CString& str_format);

	void Text_Width(int width);
	void Text_Height(int height);
	void Text_Weight(int height);
	void Color_Text(COLORREF color);
	void Align_Mode(const CString& mode);

	int  CheckArea(const POINT& pt);

	// ...
	void Title(const CString& title);
	void Draw(HDC hdc,HDC hdc_back);
	void Refresh(HDC hdc,HDC hdc_back);
};
