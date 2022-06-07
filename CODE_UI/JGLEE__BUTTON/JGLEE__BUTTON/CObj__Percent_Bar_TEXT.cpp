#include "StdAfx.h"
#include "CObj__Percent_Bar_TEXT.h"
#include "CObj__Percent_Bar_TEXT__KEY_DEF.h"


#include "CClass__Macro_Fnc.h"
extern CClass__Macro_Fnc mMacro_Fnc;


//-------------------------------------------------------------------------------------
CObj__Percent_Bar_TEXT::CObj__Percent_Bar_TEXT()
{

}
CObj__Percent_Bar_TEXT::~CObj__Percent_Bar_TEXT()
{

}


//-------------------------------------------------------------------------------------
void CObj__Percent_Bar_TEXT
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	//
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

	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_ALIGN, "LEFT RIGHT CENTER", "CENTER"); 
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_COLOR, "Color", "", "RGB(0,0,0)");

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_WIDTH, "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_HEIGHT, "", "", "15");

	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_UNIT);

	//
	p_obj_para_def->Register_Command(pKEY__TEST_PERCENT_VALUE);
	p_obj_para_def->Register_Command(pKEY__TEST_PERCENT_STATE);
}
void CObj__Percent_Bar_TEXT
::Set_Parameter(const int& module_id,
				const POINT& st,
				const POINT& et,
				const HWND& hwnd,
				GObj__Resource_Info *p_obj_res)
{
	// ...
	{
		iMODULE_ID = module_id;

		pSt = st;
		pEt = et;

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

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_ALIGN, ch_data); 
		mMng_Title.Set__Align_Mode(ch_data);
		
		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_COLOR, ch_data);
		COLORREF t_color = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);
		mMng_Title.Set__Color_Text(t_color);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_UNIT, ch_data);
		sText_Unit = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_NAME, ch_data);
		mMng_Title.Set__Font_Name(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_WIDTH, ch_data);
		mMng_Title.Set__Text_Width(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_HEIGHT, ch_data);
		mMng_Title.Set__Text_Height(atoi(ch_data));
	}

	// ...
	{
		mMng_Title.Set__Text_Weight(500);

		mMng_Title.Init__Position(pSt, pEt);
		mMng_Title.Set_Title(sText_Unit);
	}
}

void CObj__Percent_Bar_TEXT
::Show_GObj(const HWND& hwnd)
{
	bActive_Redraw = true;
	WM_Timer(hwnd);
}
void CObj__Percent_Bar_TEXT
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Percent_Bar_TEXT
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Percent_Bar_TEXT::
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
	|| (sPre_State.CompareNoCase(cur_state) != 0)
	|| (dPre_Percent != cur_percent))
	{
		bActive_Redraw = false;
		sPre_State = cur_state;
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

		// ...
		{
			CString str_data;

			if(sText_Unit.GetLength() > 0)		str_data.Format("%.1f %s", cur_percent,sText_Unit);
			else								str_data.Format("%.1f", cur_percent);

			mMng_Title.Draw_Title(hdc_back, str_data);
		}

		mMacro_Fnc.Copy(hdc_front,hdc_back, pSt,pEt);
	}
}

void CObj__Percent_Bar_TEXT::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Percent_Bar_TEXT::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Percent_Bar_TEXT::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Percent_Bar_TEXT::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Percent_Bar_TEXT::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

