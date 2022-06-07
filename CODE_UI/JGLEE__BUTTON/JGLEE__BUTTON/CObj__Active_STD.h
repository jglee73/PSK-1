#pragma once

#include "Interface_Header.h"

#include "CClass__Macro_Fnc.h"


class CObj__Active_STD : public GObj__Interface_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	//-------------------------------------------------------------------------------------
	int iMODULE_ID;

	POINT pSt;
	POINT pEt;

	RECT  rAREA;
	POINT pSt_Out;
	POINT pEt_Out;

	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	CI_BUTTON* p_Button;

	CClass__Macro_Fnc mFnc;

	CString sData__Set_1;
	CString sData__Set_2;

	CString sData__Display_Sts_1;
	CString sData__Display_Sts_2;
	CString sData__Display_Sts_3;
	CString sData__Display_Sts_4;
	CString sData__Display_Sts_5;

	CString sData__Active_Condition;
	CString sData__Active_1_Sts_1;
	CString sData__Active_1_Sts_2;
	CString sData__Active_1_Sts_3;
	CString sData__Active_1_Sts_4;
	CString sData__Active_1_Sts_5;
	CString sData__Active_1_Sts_6;
	CString sData__Active_1_Sts_7;
	CString sData__Active_1_Sts_8;
	CString sData__Active_2_Sts_1;
	CString sData__Active_2_Sts_2;
	CString sData__Active_2_Sts_3;
	CString sData__Active_2_Sts_4;
	CString sData__Active_2_Sts_5;
	CString sData__Active_2_Sts_6;
	CString sData__Active_2_Sts_7;
	CString sData__Active_2_Sts_8;

	COLORREF cColor_Inactive;

	CString sData__Title_1;
	CString sData__Title_2;
	COLORREF cColor__Title_1;
	COLORREF cColor__Title_2;
	COLORREF cColor__Background_1;
	COLORREF cColor__Background_2;

	bool bActive_Outline;
	COLORREF cColor__Outline;

	bool bActivve__Condition_AND;
	bool bActivve__Condition_OR;
	bool bActivve_Confirm;

	//-------------------------------------------------------------------------------------
	int iActive_Flag;
	int iButton_Flag;

	void Draw_Button();
	//

public:
	//-------------------------------------------------------------------------------------
	CObj__Active_STD();
	~CObj__Active_STD();

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
