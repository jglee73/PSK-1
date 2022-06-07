#include "StdAfx.h"
#include "CMng_Title.h"

#include "CClass__Macro_Fnc.h"


// ...
CMng_Title::CMng_Title()
{
	mSt.x = 0;
	mSt.y = 0;
	mEt.x = 0;
	mEt.y = 0;

	mPt_Text.x = 0;
	mPt_Text.y = 0;

	sTitle = "Title";

	mFormat = "STRING";
	mMode   = "CENTER";

	mFont_Name   = "Fixedsys";
	mText_Width  = 6; 
	mText_Height = 15;
	mText_Weight = FW_NORMAL;
}
CMng_Title::~CMng_Title()
{

}

// ...
void CMng_Title::Init__Position(const POINT& st,const POINT& et)
{
	mSt = st;
	mEt = et;

		 if(mMode.CompareNoCase("LEFT")  == 0)		mPt_Text.x = st.x + 2;
	else if(mMode.CompareNoCase("RIGHT") == 0)		mPt_Text.x = et.x - 2;
	else											mPt_Text.x = (st.x + et.x) / 2.0;

	mPt_Text.y = st.y + (et.y - st.y) * (2 / 3.0);
}

void CMng_Title::Set__Font_Name(const CString& font_name)
{
	mFont_Name = font_name;
}
void CMng_Title::Set__Text_Width(int width)
{
	mText_Width  = width;
}
void CMng_Title::Set__Text_Height(int height)
{
	mText_Height = height;
}
void CMng_Title::Set__Text_Weight(int weight)
{
	mText_Weight = weight;
}

void CMng_Title::Set__Color_Text(COLORREF color)
{
	mColor_Text = color;
}
void CMng_Title::Set__Align_Mode(const CString& mode)
{
	mMode = mode;
}

int  CMng_Title::Check__Title_Area(const POINT& pt)
{
	POINT st = mSt;
	POINT et = mEt;

	if((pt.x >= st.x) && (pt.x <= et.x)
	&& (pt.y >= st.y) && (pt.y <= et.y))
	{
		return 1;
	}
	return -1;
}

// ...
void CMng_Title::Set_Title(const CString& title)
{
	sTitle = title;
}

void CMng_Title::Draw_Title(HDC hdc)
{
	Draw_Title(hdc, sTitle);
}
void CMng_Title::Draw_Title(HDC hdc, const CString& str_title)
{
	CClass__Macro_Fnc fnc;
	CString title;

	if(mFormat.CompareNoCase("EXPONENT") == 0)			title.Format("%1.2e", atof(str_title));
	else												title = str_title;

	sTitle = title;

	fnc.Draw_Text(hdc,
				  title,
				  mPt_Text,
				  mText_Width,
				  mText_Height,
				  mText_Weight,
				  mColor_Text,
				  mMode,
				  mFont_Name);
}
