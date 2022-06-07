#pragma once

#include "Interface_Header.h"


class CObj__FA_Property_STD : public GObj__Interface_Ctrl
{
private:
	CRITICAL_SECTION mCS_LOCK;

	//-------------------------------------------------------------------------------------
	int iMODULE_ID;

	RECT  rAREA;
	POINT pSt;
	POINT pEt;

	int iREAL_MODE;
	GObj__Resource_Info *pGObj_Res;

	// ...
	CI_UTILITY* p_Utility;
	CI_BUTTON* p_Button;

	// ...
	CString sData_Feedback;
	CString sData_Path;
	//

public:
	//-------------------------------------------------------------------------------------
	CObj__FA_Property_STD();
	~CObj__FA_Property_STD();

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
