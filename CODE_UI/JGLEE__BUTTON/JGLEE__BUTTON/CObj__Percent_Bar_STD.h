#pragma once

#include "Interface_Header.h"
#include "CClass__Btn_Display.h"


class CObj__Percent_Bar_STD : public GObj__Interface_Ctrl
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
	COLORREF cColor_Background;
	COLORREF cColor_Default;

	CString sData_State1;
	CString sData_State2;
	CString sData_State3;
	CString sData_State4;
	
	COLORREF cColor_State1;
	COLORREF cColor_State2;
	COLORREF cColor_State3;
	COLORREF cColor_State4;

	// ...
	bool bActive_Redraw;
	CString sPre_State;

	double dPre_Percent;
	//

public:
	//-------------------------------------------------------------------------------------
	CObj__Percent_Bar_STD();
	~CObj__Percent_Bar_STD();

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
