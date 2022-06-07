#pragma once

#include "Interface_Header.h"

#include "CClass__Macro_Fnc.h"
#include "Dlg__Ctrl_List.h"


class CObj__Ctrl_LIST : public GObj__Interface_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	//-------------------------------------------------------------------------------------
	int iMODULE_ID;

	RECT  rAREA;
	POINT pSt;
	POINT pEt;

	POINT pSt_Out;
	POINT pEt_Out;

	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	CI_BUTTON* p_Button;

	CClass__Macro_Fnc mFnc;

	CString sData__Set_Para;
	CString sData__Set_1;
	CString sData__Set_2;

	CString sData__Display_Sts_1;
	CString sData__Display_Sts_2;
	CString sData__Display_Sts_3;
	CString sData__Display_Sts_4;
	CString sData__Display_Sts_5;

	CString sData__Lock_Condition;
	bool bLock__Condition_AND;
	bool bLock__Condition_OR;

	CString sData__Lock_Sts1_1;
	CString sData__Lock_Sts1_2;
	CString sData__Lock_Sts1_3;
	CString sData__Lock_Sts1_4;
	CString sData__Lock_Sts1_5;
	CString sData__Lock_Sts1_6;
	CString sData__Lock_Sts1_7;
	CString sData__Lock_Sts1_8;

	CString sData__Lock_Sts2_1;
	CString sData__Lock_Sts2_2;
	CString sData__Lock_Sts2_3;
	CString sData__Lock_Sts2_4;
	CString sData__Lock_Sts2_5;
	CString sData__Lock_Sts2_6;
	CString sData__Lock_Sts2_7;
	CString sData__Lock_Sts2_8;

	COLORREF cColor_Inactive;

	CString sData__Title_1;
	CString sData__Title_2;
	COLORREF cColor__Title_1;
	COLORREF cColor__Title_2;
	COLORREF cColor__Background_1;
	COLORREF cColor__Background_2;

	bool bActive_Outline;
	COLORREF cColor__Outline;

	bool bActivve_Confirm;
	bool bActivve_Debug_Mode;

	CString sData__Comment;

	int iPara__ITEM_SIZE;

	//-------------------------------------------------------------------------------------
	int iActive_Flag;
	int iButton_Flag;

	void Draw_Button();
	//

public:
	//-------------------------------------------------------------------------------------
	CObj__Ctrl_LIST();
	~CObj__Ctrl_LIST();

	//---------------------------------------------------------
	void Get_Parameter(GObj__Parameter_Def* p_obj_para_def);

	void Set_Parameter(const int& module_id,
						const POINT& st,
						const POINT& et,
						const HWND& hwnd,
						GObj__Resource_Info *p_obj_res);

	void Show_GObj(const HWND& hwnd);
	void Hide_GObj();

	//---------------------------------------------------------
	void WM_Paint(const HWND& hwnd);
	void WM_Timer(const HWND& hwnd);

	void WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd);
	void WM_LButtonUp(const HWND& hwnd);

	void WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd);
	void WM_RButtonUp(const HWND& hwnd);

	void WM_Notify(UINT message,const WPARAM wparam,LPARAM lparam);
};
