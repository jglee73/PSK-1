#include "StdAfx.h"
#include "CObj__Percent_Bar_STD.h"
#include "CObj__Percent_Bar_STD__KEY_DEF.h"


#include "CClass__Macro_Fnc.h"
extern CClass__Macro_Fnc mMacro_Fnc;


//-------------------------------------------------------------------------------------
CObj__Percent_Bar_STD::CObj__Percent_Bar_STD()
{

}
CObj__Percent_Bar_STD::~CObj__Percent_Bar_STD()
{

}


//-------------------------------------------------------------------------------------
void CObj__Percent_Bar_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Channel(pKEY__CH_PERCENT_VALUE);
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_COLOR, "Color", "", "RGB(255,255,255)");
	p_obj_para_def->Register_Command(pKEY__DATA_DEFAULT_COLOR, "Color", "", "RGB(0,0,255)");

	p_obj_para_def->Register_Channel(pKEY__CH_PERCENT_STATE);
	p_obj_para_def->Register_Command(pKEY__DATA_STATE_1);
	p_obj_para_def->Register_Command(pKEY__DATA_STATE_2);
	p_obj_para_def->Register_Command(pKEY__DATA_STATE_3);
	p_obj_para_def->Register_Command(pKEY__DATA_STATE_4);
	p_obj_para_def->Register_Command(pKEY__DATA_COLOR_1, "Color", "", "RGB(0,255,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_COLOR_2, "Color", "", "RGB(155,155,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_COLOR_3, "Color", "", "RGB(255,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_COLOR_4, "Color", "", "RGB(0,155,155)");

	p_obj_para_def->Register_Command(pKEY__TEST_PERCENT_VALUE);
	p_obj_para_def->Register_Command(pKEY__TEST_PERCENT_STATE);
}
void CObj__Percent_Bar_STD
::Set_Parameter(const int& module_id,
				const POINT& st,
				const POINT& et,
				const HWND& hwnd,
				GObj__Resource_Info *p_obj_res)
{
	// ...
	{
		iMODULE_ID = module_id;

		pSt.x = st.x + 1;
		pSt.y = st.y + 1;
		pEt.x = et.x - 1;
		pEt.y = et.y - 1;

		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();
		pGObj_Res  = p_obj_res;
	}

	// ...
	{
		GObj__Parameter_Ctrl* p_gobj = p_obj_res->pGOBJ_PARA_CTRL;
		CString ch_data;
		
		int r_color;
		int g_color;
		int b_color;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR, ch_data);
		cColor_Background = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);

		p_gobj->Get_Constant_Data(pKEY__DATA_DEFAULT_COLOR, ch_data);
		cColor_Default = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_STATE_1, ch_data);
		sData_State1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_STATE_2, ch_data);
		sData_State2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_STATE_3, ch_data);
		sData_State3 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_STATE_4, ch_data);
		sData_State4 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_COLOR_1, ch_data);
		cColor_State1 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);

		p_gobj->Get_Constant_Data(pKEY__DATA_COLOR_2, ch_data);
		cColor_State2 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);

		p_gobj->Get_Constant_Data(pKEY__DATA_COLOR_3, ch_data);
		cColor_State3 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);

		p_gobj->Get_Constant_Data(pKEY__DATA_COLOR_4, ch_data);
		cColor_State4 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);
	}
}

void CObj__Percent_Bar_STD
::Show_GObj(const HWND& hwnd)
{
	bActive_Redraw = true;
	WM_Timer(hwnd);
}
void CObj__Percent_Bar_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Percent_Bar_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Percent_Bar_STD::
WM_Timer(const HWND& hwnd)
{
	GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;

	double  cur_percent;
	CString cur_state;
	CString ch_data;

	if(iREAL_MODE > 0)
	{
		p_gobj->Get_Channel_Data(pKEY__CH_PERCENT_VALUE, ch_data);
		cur_percent = atof(ch_data);
		if(dPre_Percent != cur_percent)			bActive_Redraw = true;

		p_gobj->Get_Channel_Data(pKEY__CH_PERCENT_STATE, ch_data);
		cur_state = ch_data;
	}
	else
	{
		p_gobj->Get_Constant_Data(pKEY__TEST_PERCENT_VALUE, ch_data);
		cur_percent = atof(ch_data);

		p_gobj->Get_Constant_Data(pKEY__TEST_PERCENT_STATE, ch_data);
		cur_state = ch_data;
	}

	if((bActive_Redraw)
	|| (sPre_State.CompareNoCase(cur_state) != 0))
	{
		bActive_Redraw = false;
		sPre_State   = cur_state;
		dPre_Percent = cur_percent;

		// ...
		COLORREF color;
		POINT    st, et;

		st = pSt;
		et = pEt;
		et.x = st.x + (et.x - st.x) * cur_percent / 100.0;

			 if(et.x > pEt.x)		et.x = pEt.x;
		else if(et.x < st.x )		et.x = st.x;

		if(cur_state.GetLength() > 0)
		{
			     if(cur_state.CompareNoCase(sData_State1) == 0)			color = cColor_State1;
			else if(cur_state.CompareNoCase(sData_State2) == 0)			color = cColor_State2;
			else if(cur_state.CompareNoCase(sData_State3) == 0)			color = cColor_State3;
			else if(cur_state.CompareNoCase(sData_State4) == 0)			color = cColor_State4;
			else														color = cColor_Default;
		}
		else
		{
			color = cColor_Default;
		}

		// ...
		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		mMacro_Fnc.Fill_Rectangle(hdc_back, pSt,pEt, cColor_Background);
		mMacro_Fnc.Fill_Rectangle(hdc_back, st,et, color);
		mMacro_Fnc.Copy(hdc_front,hdc_back, pSt,pEt);
	}
}

void CObj__Percent_Bar_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Percent_Bar_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Percent_Bar_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Percent_Bar_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Percent_Bar_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

