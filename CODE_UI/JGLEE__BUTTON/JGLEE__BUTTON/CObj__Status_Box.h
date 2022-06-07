#pragma once

#include "Interface_Header.h"


class CObj__Status_Box : public GObj__Interface_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	//-------------------------------------------------------------------------------------
	int iMODULE_ID;
	POINT pSt;
	POINT pEt;

	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	CI_BUTTON* p_Button;

	CString sData__Active1_State1;
	CString sData__Active1_State2;
	CString sData__Active1_State3;

	CString sData__Active2_State1;
	CString sData__Active2_State2;
	CString sData__Active2_State3;

	CString sData__Active3_State1;
	CString sData__Active3_State2;
	CString sData__Active3_State3;

	COLORREF cColor__Active1;
	COLORREF cColor__Active2;
	COLORREF cColor__Active3;
	COLORREF cColor__InActive;

	//-------------------------------------------------------------------------------------
	bool bActive__Blink_Mode;
	int iBlink_Count;

	CString sPre_State;

	void Draw_Button();
	//

public:
	//-------------------------------------------------------------------------------------
	CObj__Status_Box();
	~CObj__Status_Box();

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
