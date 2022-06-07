#pragma once


class CClass__Btn_Display
{
private:
	HDC			mHDC;
	HDC			mHDC_Back;
	POINT		mSt;		
	POINT		mEt;		

	CString	sTitle;
	CString sPara_Title;

	CString		mChannel;			// 02 : Channel-Name
	COLORREF	mColor_Text;		// 04 : Text Color
	COLORREF	mColor_Background;	// 05 : Background Color	
	CString		mFontName;			// 06 : Font Name
	int 		mTextWidth;			// 07 : Text Width
	int 		mTextHeight;		// 08 : Text Height
	int 		mTextWeight;		// 09 : Text Weight
	int			mEdgeWidth;			// 10 : Edge Width
	COLORREF	mEdgeUpColor;		// 11 : Edge Upper-Color
	COLORREF	mEdgeDownColor;		// 12 : Edge Lower-Color
	CString		mButtonMode;		// 15 : Button Mode (Display, Setting)
	CString     mFormat;			// 16 : Display Format

	POINT		mPt_Text;
	int         mText_Y_Pos_Offset;
	int			mColor_Tr;
	int			mColor_Tg;
	int			mColor_Tb;
	int			mColor_Br;
	int			mColor_Bg;
	int			mColor_Bb;

	LOGFONT		mFontLog;
	int			mFontType;

	void		Set_TextPoint(HDC hdc);
	COLORREF	GetColor(CString mode,CString string);

public:
	CClass__Btn_Display();

	CStringArray mProperty;

	// ...
	int Set_Property__Font_Name(const CString& font_name);
	int Set_Property__Text_Color(const CString& str_rgb);
	int Set_Property__Back_Color(const CString& str_rgb);
	int Set_Property__Text_Width(const int width);
	int Set_Property__Text_Height(const int height);
	int Set_Property__Text_Weight(const int weight);
	int Set_Property__Edge_Width(const int width);
	int Set_Property__Edge_Up_Color(const CString& str_rgb);
	int Set_Property__Edge_Down_Color(const CString& str_rgb);
	int Set_Property__Text_Y_Pos_Offset(const int y_offset);
	int Set_Property__Bttn_Display();
	int Set_Property__Bttn_Setting();
	int End_Property();

	// ...
	int Init(HDC hdc,HDC hdc_back);
	int Init(HDC hdc,HDC hdc_back,POINT st,POINT et);

	int	WM_LButtonDown();
	int WM_LButtonUp();

	void Set_Title(const CString& str_title, const bool set_mode = false);
	int	WM_Timer();
};
