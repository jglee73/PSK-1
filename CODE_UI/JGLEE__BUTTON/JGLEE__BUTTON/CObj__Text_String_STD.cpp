#include "StdAfx.h"
#include "CObj__Text_String_STD.h"
#include "CObj__Text_String_STD__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Text_String_STD::CObj__Text_String_STD()
{

}
CObj__Text_String_STD::~CObj__Text_String_STD()
{

}


//-------------------------------------------------------------------------------------
void CObj__Text_String_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Channel(pKEY__CH_MESSAGE);

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");

	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_COLOR, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_WIDTH,  "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_HEIGHT, "", "", "15");

	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_ALIGN,  "ListBox", "CENTER LEFT RIGHT", "CENTER");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_FORMAT, "ListBox", "STRING EXPONENT", "STRING");
}
void CObj__Text_String_STD
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

		int r_colot;
		int g_color;
		int b_color;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_NAME, ch_data);
		mMessage.Set_FontName(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_COLOR, ch_data);
		mMessage.Color_Text(p_gobj->Get_RGB_Color(ch_data, r_colot,g_color,b_color));

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_WIDTH, ch_data);
		mMessage.Text_Width(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_HEIGHT, ch_data);
		mMessage.Text_Height(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_ALIGN, ch_data);
		mMessage.Align_Mode(ch_data);
		
		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_FORMAT, ch_data);
		mMessage.Set_Fonmat(ch_data);

		//
		mMessage.Init(pSt, pEt);
	}
}

void CObj__Text_String_STD
::Show_GObj(const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	if(iREAL_MODE < 0)
	{
		CString ch_data = "Text";

		mMessage.Title(ch_data);
	}

	mMessage.Init(hdc_back);
	mMessage.Refresh(hdc_front, hdc_back);
}
void CObj__Text_String_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Text_String_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Text_String_STD::
WM_Timer(const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	// ...
	{	
		GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;
		CString ch_data;

		p_gobj->Get_Channel_Data(pKEY__CH_MESSAGE, ch_data);

		mMessage.Title(ch_data);
		mMessage.Draw(hdc_front, hdc_back);
	}
}

void CObj__Text_String_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Text_String_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Text_String_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Text_String_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Text_String_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

