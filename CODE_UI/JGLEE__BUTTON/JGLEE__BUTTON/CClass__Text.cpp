#include "StdAfx.h"
#include "CClass__Text.h"
#include "CClass__Macro_Fnc.h"


CClass__Text::CClass__Text()
{
	InitializeCriticalSection(&mCS_Lock);

	mSt.x = 0;
	mSt.y = 0;
	mEt.x = 0;
	mEt.y = 0;

	mInit_Flag = -1;

	xHDC_IMG = NULL;
	mBIT_IMG = NULL;

	xHDC_BFF = NULL;
	mBIT_BFF = NULL;

	mTitle_Pre = "~";

	mTitle  = "Text";
	mFormat = "STRING";

	mFont_Name   = "Fixedsys";
	mText_Width  = 6; 
	mText_Height = 15;
	mText_Weight = FW_NORMAL;
}
CClass__Text::~CClass__Text()
{
	DeleteCriticalSection(&mCS_Lock);
}

void CClass__Text::Create_DC()
{
	Delete_DC();

	HDC hdc = GetDC(NULL);

	xHDC_IMG = CreateCompatibleDC(hdc);
	xHDC_BFF = CreateCompatibleDC(hdc);

	SelectObject(xHDC_IMG,mBIT_IMG);
	SelectObject(xHDC_BFF,mBIT_BFF);

	ReleaseDC(NULL,hdc);
}
void CClass__Text::Delete_DC()
{
	if(xHDC_IMG != NULL)
	{
		DeleteDC(xHDC_IMG);
		xHDC_IMG = NULL;
	}
	if(xHDC_BFF != NULL)
	{
		DeleteDC(xHDC_BFF);
		xHDC_BFF = NULL;
	}
}

void CClass__Text::Init(const POINT& st,const POINT& et)
{
	EnterCriticalSection(&mCS_Lock);

	//--------------------------------------------
	mSt = st;
	mEt = et;

	mSize.x = et.x - st.x;
	mSize.y = et.y - st.y;

	if(mSize.x > 300)	mSize.x = 300;
	if(mSize.y > 200)	mSize.y = 200;

	if(mMode.Compare("LEFT")  == 0)			mPt_Text.x = 2;
	else if(mMode.Compare("RIGHT") == 0)			mPt_Text.x = mSize.x - 2;
	else											mPt_Text.x = mSize.x / 2;

	mPt_Text.y = 3 * mSize.y / 4;
	//--------------------------------------------

	//---------------------------------------
	if(mBIT_IMG != NULL)	DeleteObject(mBIT_IMG);
	if(xHDC_IMG != NULL)	DeleteDC(xHDC_IMG);

	if(mBIT_BFF != NULL)	DeleteObject(mBIT_BFF);
	if(xHDC_BFF != NULL)	DeleteDC(xHDC_BFF);
	//---------------------------------------

	//---------------------------------------
	HDC hdc = GetDC(NULL);

	int x = mSize.x; 
	int y = mSize.y; 

	//===========================
	BITMAPINFO bi;
	void *lpBits;

	ZeroMemory(&bi,sizeof(BITMAPINFOHEADER));

	bi.bmiHeader.biSize        = sizeof(BITMAPINFOHEADER);
	bi.bmiHeader.biWidth       = x;
	bi.bmiHeader.biHeight      = y;
	bi.bmiHeader.biPlanes      = 1;
	bi.bmiHeader.biBitCount    = 32;
	bi.bmiHeader.biCompression = BI_RGB;

	mBIT_IMG = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,&lpBits,NULL,(DWORD)0);
	mBIT_BFF = CreateDIBSection(hdc,(BITMAPINFO *)&bi,DIB_RGB_COLORS,&lpBits,NULL,(DWORD)0);
	//===========================

	mInit_Flag = -1;

	ReleaseDC(NULL,hdc);
	//---------------------------------------

	LeaveCriticalSection(&mCS_Lock);
}
void CClass__Text::Init(HDC hdc_back)
{
	if(mInit_Flag > 0)		return;
	mInit_Flag = 1;

	EnterCriticalSection(&mCS_Lock);

	Create_DC();

	//---------------------------------------
	StretchBlt(xHDC_BFF,
		0,
		0,
		mSize.x,
		mSize.y,
		hdc_back,
		mSt.x,
		mSt.y,
		mSize.x,
		mSize.y,
		SRCCOPY);
	//---------------------------------------

	Delete_DC();

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Text::Set_FontName(const CString& font_name)
{
	EnterCriticalSection(&mCS_Lock);

	mFont_Name = font_name;

	LeaveCriticalSection(&mCS_Lock);
}
void CClass__Text::Set_Fonmat(const CString& str_format)
{
	EnterCriticalSection(&mCS_Lock);

	mFormat = str_format;

	LeaveCriticalSection(&mCS_Lock);
}

void CClass__Text::Text_Width(int width)
{
	mText_Width  = width;
}
void CClass__Text::Text_Height(int height)
{
	mText_Height = height;
}
void CClass__Text::Text_Weight(int weight)
{
	mText_Weight = weight;
}

void CClass__Text::Color_Text(COLORREF color)
{
	mColor_Text = color;
}
void CClass__Text::Align_Mode(const CString& mode)
{
	mMode = mode;
}

int  CClass__Text::CheckArea(const POINT& pt)
{
	POINT st = mSt;
	POINT et = mEt;

	if((pt.x >= st.x)&&(pt.x <= et.x)
		&& (pt.y >= st.y)&&(pt.y <= et.y))
	{
		return 1;
	}
	return -1;
}

// ...
void CClass__Text::Title(const CString& title)
{
	EnterCriticalSection(&mCS_Lock);

	mTitle = title;

	LeaveCriticalSection(&mCS_Lock);
}
void CClass__Text::Refresh(HDC hdc,HDC hdc_back)
{
	EnterCriticalSection(&mCS_Lock);

	mTitle_Pre = "~";

	LeaveCriticalSection(&mCS_Lock);

	Draw(hdc,hdc_back);
}
void CClass__Text::Draw(HDC hdc,HDC hdc_back)
{
	if(mTitle.Compare(mTitle_Pre) == 0)			return;
	mTitle_Pre = mTitle;

	EnterCriticalSection(&mCS_Lock);

	//------------------------------------------
	CString title;

	if(mFormat.Compare("EXPONENT") == 0)		title.Format("%1.2e",atof(mTitle));
	else										title = mTitle;

	Create_DC();

	//------------------------------------------
	CClass__Macro_Fnc fnc;

	// bff -> img
	StretchBlt(xHDC_IMG,
				0,
				0,
				mSize.x,
				mSize.y,
				xHDC_BFF,
				0,
				0,
				mSize.x,
				mSize.y,
				SRCCOPY);

	// text on img
	fnc.Draw_Text(xHDC_IMG,
					title,
					mPt_Text,
					mText_Width,
					mText_Height,
					mText_Weight,
					mColor_Text,
					mMode,
					mFont_Name);

	// img -> hdc_back
	StretchBlt(hdc_back,
				mSt.x,
				mSt.y,
				mSize.x,
				mSize.y,
				xHDC_IMG,
				0,
				0,
				mSize.x,
				mSize.y,
				SRCCOPY);

	// hdc_back -> hdc 
	if(hdc != hdc_back)
	{
		StretchBlt(hdc,
					mSt.x,
					mSt.y,
					mSize.x,
					mSize.y,
					hdc_back,
					mSt.x,
					mSt.y,
					mSize.x,
					mSize.y,
					SRCCOPY);
	}
	//------------------------------------------

	Delete_DC();
	LeaveCriticalSection(&mCS_Lock);
}
