#include "StdAfx.h"
#include "CClass__Btn_Display.h"


#include "CClass__Macro_Fnc.h"
extern CClass__Macro_Fnc mMacro_Fnc;

#include "CClass__Macro_Font.h"
extern CClass__Macro_Font mMacro_Font; 


CClass__Btn_Display::CClass__Btn_Display()
{
	mChannel = "";
	sTitle	 = "";

	mFontName   = "Fixedsys";
	mTextWidth  =  9;	
	mTextHeight = 21;	
	mTextWeight = 100;

	mEdgeWidth     = 2;
	mEdgeUpColor   = RGB(250,250,250);
	mEdgeDownColor = RGB(50,50,50);

	mText_Y_Pos_Offset = 0;

	mColor_Tr = 250;
	mColor_Tg = 50;
	mColor_Tb = 50;
	mColor_Text = RGB(mColor_Tr,mColor_Tg,mColor_Tb);

	mColor_Br = 50;
	mColor_Bg = 50;
	mColor_Bb = 50;
	mColor_Background = RGB(mColor_Br,mColor_Bg,mColor_Bb);

	mButtonMode = "DISPLAY";
}


// ...
void CClass__Btn_Display::Set_TextPoint(HDC hdc)
{
	mMacro_Fnc.Get_TextPoint(hdc,mSt,mEt,&mPt_Text);
	
	mPt_Text.y += mText_Y_Pos_Offset;
}


int	 CClass__Btn_Display::Init(HDC hdc,HDC hdc_back,POINT st,POINT et)
{
	mHDC = hdc;
	mHDC_Back = hdc_back;
	mSt = st;
	mEt = et;

	Set_TextPoint(hdc_back);
	return 1;
}
int	 CClass__Btn_Display::Init(HDC hdc,HDC hdc_back)
{
	mHDC = hdc;
	mHDC_Back = hdc_back;
	return 1;
}

COLORREF CClass__Btn_Display::GetColor(CString mode,CString string)
{
	COLORREF color = RGB(mColor_Br,mColor_Bg,mColor_Bb);

	char ch, word[300];
	CString  word1, word2, word3, word4;

	int count = 0;
	int para  = 0;
	
	int limit = string.GetLength();
	int i;

	for(i=0; i<=limit; i++)
	{
		if(i != limit)		ch = string.GetAt(i);
		else				ch = '\0';

		if((ch == ' ')
		|| (ch == ',')
		|| (ch == '(')
		|| (ch == ')')
		|| (ch == '\0'))
		{
			if(count > 0)
			{
				count = 0;
				para++;

					 if(para == 1)		word1 = word;
				else if(para == 2)		word2 = word;
				else if(para == 3)		word3 = word;
				else if(para == 4)		word4 = word;
			}
		}
		else
		{
			word[count++] = ch;
			word[count]   = '\0';
		}
	}

	if(word1.CompareNoCase("RGB") == 0)	
	{
		if(mode.CompareNoCase("Text") == 0)
		{
			mColor_Tr = atoi(word2);
			mColor_Tg = atoi(word3);
			mColor_Tb = atoi(word4);
		}
		else if(mode.CompareNoCase("Background") == 0)
		{
			mColor_Br = atoi(word2);
			mColor_Bg = atoi(word3);
			mColor_Bb = atoi(word4);
		}

		color = RGB(atoi(word2),atoi(word3),atoi(word4)); 
	}
	else
	{
		if(mode.CompareNoCase("Text") == 0)
		{
			mColor_Tr = atoi(word1);
			mColor_Tg = atoi(word2);
			mColor_Tb = atoi(word3);
		}
		else if(mode.CompareNoCase("Background") == 0)
		{
			mColor_Br = atoi(word1);
			mColor_Bg = atoi(word2);
			mColor_Bb = atoi(word3);
		}

		color = RGB(atoi(word1),atoi(word2),atoi(word3)); 
	}

	return color;
}


int  CClass__Btn_Display::WM_LButtonUp()
{
	mMacro_Fnc.Draw_Text(mHDC_Back,sTitle,mSt,mEt,mPt_Text,
						 mColor_Text,mColor_Background,
						 mColor_Tr,mColor_Tg,mColor_Tb,
						 mColor_Br,mColor_Bg,mColor_Bb,
						 mFontLog,mFontType);

	mMacro_Fnc.Draw_Rectangle(mHDC_Back,mSt,mEt,mEdgeWidth,
							  mEdgeUpColor,mEdgeDownColor);

	mMacro_Fnc.Copy(mHDC,mHDC_Back,mSt,mEt);
	return 1;
}
int  CClass__Btn_Display::WM_LButtonDown()
{
	if(mButtonMode.CompareNoCase("DISPLAY") == 0)
	{
		return -1;
	}

	mMacro_Fnc.Draw_Rectangle(mHDC_Back,mSt,mEt,mEdgeWidth,
						      mEdgeDownColor,mEdgeUpColor);

	mMacro_Fnc.Copy(mHDC,mHDC_Back,mSt,mEt);
	return 1;
}

void CClass__Btn_Display::
Set_Title(const CString& str_title, const bool set_mode)
{
	sPara_Title = str_title;

	if(set_mode)		sTitle = sPara_Title;
}
int  CClass__Btn_Display::WM_Timer()
{
	if(sTitle.Compare(sPara_Title) == 0)	
	{
		return 1;
	}
	sTitle = sPara_Title;

	mMacro_Fnc.Draw_Text(mHDC_Back,
		                 sTitle,
						 mSt,mEt,mPt_Text,
						 mColor_Text,mColor_Background,
						 mColor_Tr,mColor_Tg,mColor_Tb,
						 mColor_Br,mColor_Bg,mColor_Bb,
						 mFontLog,mFontType);
	
	mMacro_Fnc.Draw_Rectangle(mHDC_Back,mSt,mEt,mEdgeWidth,
							  mEdgeUpColor,mEdgeDownColor);

	mMacro_Fnc.Copy(mHDC,mHDC_Back,mSt,mEt);
	return 1;
}

// ...
int  CClass__Btn_Display::
Set_Property__Font_Name(const CString& font_name)
{
	mFontName = font_name;
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Text_Color(const CString& str_rgb)
{
	mColor_Text = GetColor("Text", str_rgb);
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Back_Color(const CString& str_rgb)
{
	mColor_Background = GetColor("Background", str_rgb);
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Text_Width(const int width)
{
	mTextWidth = width;
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Text_Height(const int height)
{
	mTextHeight = height;
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Text_Weight(const int weight)
{
	mTextWeight = weight;
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Edge_Width(const int width)
{
	mEdgeWidth = width;
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Edge_Up_Color(const CString& str_rgb)
{
	mEdgeUpColor = GetColor("EdgeUp", str_rgb);
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Edge_Down_Color(const CString& str_rgb)
{
	mEdgeDownColor = GetColor("EdgeDown", str_rgb);
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Text_Y_Pos_Offset(const int y_offset)
{
	mText_Y_Pos_Offset = y_offset;
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Bttn_Display()
{
	mButtonMode = "DISPLAY";
	return 1;
}
int  CClass__Btn_Display::
Set_Property__Bttn_Setting()
{
	mButtonMode = "SETTING";
	return 1;
}

int  CClass__Btn_Display::
End_Property()
{
	mMacro_Font.Get_Font(mFontName, &mFontLog, &mFontType);

	if(mTextWidth  == 0)	mTextWidth  =  9;
	if(mTextHeight == 0)	mTextHeight = 21;
	if(mTextWeight == 0)	mTextWeight = 100;

	mFontLog.lfWidth  = mTextWidth;
	mFontLog.lfHeight = mTextHeight;
	mFontLog.lfWeight = mTextWeight;

	return 1;
}
