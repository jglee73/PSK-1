#include "StdAfx.h"
#include "CObj__Display_STD.h"
#include "CObj__Display_STD__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Display_STD::CObj__Display_STD()
{

}
CObj__Display_STD::~CObj__Display_STD()
{

}


//-------------------------------------------------------------------------------------
void CObj__Display_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_BUTTON_TYPE, "ListBox", "DISPLAY SETTING", "DISPLAY");

	p_obj_para_def->Register_Channel(pKEY__CH_STATE);

	p_obj_para_def->Register_Command(pKEY__DATA_INIT_TITLE, "");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");

	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_COLOR, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_COLOR, "Color", "", "RGB(255,255,255)");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_WIDTH,  "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_HEIGHT, "", "", "15");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_WEIGHT, "", "", "");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH,  "", "", "1");

	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(174,175,179)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(244,245,249)");
	p_obj_para_def->Register_Command(pKEY__DATA_OUTLINE_COLOR,   "Color", "", "");

	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_Y_POS_OFFSET, "", "", "0");
}
void CObj__Display_STD
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

		pSt_Out = pSt;
		pEt_Out = pEt;

		pSt_Out.x -= 1;
		pSt_Out.y -= 1;
		pEt_Out.x += 1;
		pEt_Out.y += 1;

		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();
		pGObj_Res  = p_obj_res;
	}

	// ...
	CI_UTILITY* p_utility = New_UTILITY();

	// ...
	{
		GObj__Parameter_Ctrl* p_gobj = p_obj_res->pGOBJ_PARA_CTRL;
		CString ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_NAME, ch_data);
		mBtn.Set_Property__Font_Name(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_COLOR, ch_data);
		mBtn.Set_Property__Text_Color(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR, ch_data);
		mBtn.Set_Property__Back_Color(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_WIDTH, ch_data);
		mBtn.Set_Property__Text_Width(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_HEIGHT, ch_data);
		mBtn.Set_Property__Text_Height(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_WEIGHT, ch_data);
		mBtn.Set_Property__Text_Weight(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_WIDTH, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "2";
		mBtn.Set_Property__Edge_Width(atoi(ch_data));

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_UP_COLOR, ch_data);
		mBtn.Set_Property__Edge_Up_Color(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_DOWN_COLOR, ch_data);
		mBtn.Set_Property__Edge_Down_Color(ch_data);

		bActive_Outline = false;
		p_gobj->Get_Constant_Data(pKEY__DATA_OUTLINE_COLOR, ch_data);
		if(ch_data.Find("RGB") >= 0)
		{
			bActive_Outline = true;
			cColor__Outline = p_utility->GetColor(ch_data);
		}

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_Y_POS_OFFSET, ch_data);
		mBtn.Set_Property__Text_Y_Pos_Offset(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_BUTTON_TYPE, ch_data);
		if(ch_data.CompareNoCase("DISPLAY") == 0)		mBtn.Set_Property__Bttn_Display();
		else											mBtn.Set_Property__Bttn_Setting();

		mBtn.End_Property();
	}

	// ...
	{
		CString ch_data;
		p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_INIT_TITLE, ch_data);

		mBtn.Set_Title(ch_data, true);
	}

	delete p_utility;
}

void CObj__Display_STD
::Show_GObj(const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	mBtn.Init(hdc_front,hdc_back, pSt,pEt);
	mBtn.WM_LButtonUp();	

	_Fnc__Draw_Button();
}
void CObj__Display_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Display_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Display_STD::
WM_Timer(const HWND& hwnd)
{
	// ...
	{	
		GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;
		CString ch_data;

		p_gobj->Get_Channel_Data(pKEY__CH_STATE, ch_data);
		mBtn.Set_Title(ch_data);

		mBtn.WM_Timer();	
	}
}

void CObj__Display_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	mBtn.Init(hdc_front,hdc_back, pSt,pEt);
	if(mBtn.WM_LButtonDown() < 0)
	{
		return;
	}

	Sleep(200);

	mBtn.WM_LButtonUp();	
	_Fnc__Draw_Button();
}
void CObj__Display_STD::
WM_LButtonUp(const HWND& hwnd)
{
	mBtn.WM_LButtonUp();	
}

void CObj__Display_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Display_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Display_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

// ...
#include "CClass__Macro_Fnc.h"

void CObj__Display_STD::
_Fnc__Draw_Button()
{
	if(bActive_Outline)
	{
		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		CClass__Macro_Fnc x_fnc;

		x_fnc.Draw_Rectangle(hdc_back,  pSt_Out,pEt_Out, 1, cColor__Outline, cColor__Outline);
		x_fnc.Draw_Rectangle(hdc_front, pSt_Out,pEt_Out, 1, cColor__Outline, cColor__Outline);
	}
}
