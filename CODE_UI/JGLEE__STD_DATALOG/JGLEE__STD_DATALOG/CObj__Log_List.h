#pragma once

#include "Interface_Header.h"
#include "Dlg_Log_List.h"


// ...
#define SPLL_BTN_FNC_COLOR	RGB(54, 167, 192)


class CObj__Log_List : public GObj__Interface_Ctrl   
{
private:
	// ...
	GObj__Resource_Info *m_pGObj_Res;

	int iMODULE_ID;
	int iREAL_MODE;

	POINT pST;
	POINT pET;

	bool bActive__Show_Page;
	bool bActive__Init_Table;

	// ...
	int  _Interface_Parameter();

	int  _Interface_Show(HWND hwnd);
	int  _Interface_Hide();

	int  _WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd);
	int  _WM_Timer(HWND hwnd);
	//

private:
	//-------------------------------------------------------------------------------------
	//-------------------------------------------------------------------------------------
	//.....
	CI_DRAW *mI_Draw;

	CX_Pad_String_CTRL m_pStringPad;

	CI_BUTTON *mI_BUTTON_Edit;
	CI_BUTTON *mI_BUTTON_Undo;
	CI_BUTTON *mI_BUTTON_Save;
	CI_BUTTON *mI_BUTTON_Search;
	CI_BUTTON *mI_BUTTON_Search_Box;
	CI_BUTTON *mI_BUTTON_Time;
	CI_BUTTON *mI_BUTTON_Time_String;

	//
	CDlg_Log_List *pDlg_View;

	//
	CString mConfig_Path;
	CString mConfig_Dir;
	CString mOutput_Path;
	CString mConfig_File;

	int iPara_Flag__Group_Use;
	CStringArray sPara_List__Group_Item;

	//
	COLORREF mColor_Yellow;
	COLORREF mColor_White;

	COLORREF mPColor;
	COLORREF mRColor;
	COLORREF mWColor;
	COLORREF mBColor;
	CString  mTitle;
	POINT    mTPt;
	LOGFONT	 mLogFont;
	CString	 mFontName;
	int	mTWidth;
	int	mTHeight;

	int mEdit_Flag;
	int mEdit_Blink;

	CStringArray m_arrCHType;

	// ...
	int Fnc_Active();
	int Fnc_InActive();
	int Draw_Button(const HDC& hdc,const HDC& hdc_back);
	int Fnc_Save();
	int Fnc_Undo();

	int iInit_Flag;
	int Init__Table(HWND hwnd, const bool active_upload);
	//

public:
	CObj__Log_List();
	~CObj__Log_List();

	// ...
	void Get_Parameter(GObj__Parameter_Def* p_obj_para_def);

	void Set_Parameter(const int& module_id,
					   const POINT& st,
					   const POINT& et,
					   const HWND& hwnd,
					   GObj__Resource_Info *p_obj_res);

	void Show_GObj(const HWND& hwnd);
	void Hide_GObj();	

	void WM_Paint(const HWND& hwnd);
	void WM_Timer(const HWND& hwnd);
	void WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd);
};
