#pragma once


class CMng_Title
{
private:
	POINT mSt;
	POINT mEt;
	POINT mPt_Text;

	CString	sTitle;

	int	mText_Width;
	int	mText_Height;
	int	mText_Weight;

	COLORREF mColor_Text;
	CString	 mMode;
	CString  mFormat;
	CString  mFont_Name;


public:
	CMng_Title();
	~CMng_Title();

	// ...
	void Init__Position(const POINT& st,const POINT& et);

	void Set__Font_Name(const CString& font_name);
	void Set__Text_Width(int width);
	void Set__Text_Height(int height);
	void Set__Text_Weight(int height);
	void Set__Color_Text(COLORREF color);
	void Set__Align_Mode(const CString& mode);

	int  Check__Title_Area(const POINT& pt);

	// ...
	void Set_Title(const CString& title);

	void Draw_Title(HDC hdc);
	void Draw_Title(HDC hdc,const CString& title);
};
