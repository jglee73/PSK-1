#include "StdAfx.h"
#include "CObj__Recipe_Select_STD.h"
#include "CObj__Recipe_Select_STD__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Recipe_Select_STD::CObj__Recipe_Select_STD()
{
	p_Utility = New_UTILITY();
	p_Button  = New_BUTTON();
}
CObj__Recipe_Select_STD::~CObj__Recipe_Select_STD()
{
	delete p_Utility;
	delete p_Button;
}


//-------------------------------------------------------------------------------------
void CObj__Recipe_Select_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_EQP_ID, "ListBox", "0 1 2 3 4 5 6 7 8 LOCAL_ID", "LOCAL_ID");
	p_obj_para_def->Register_Channel(pKEY__CH_RECIPE_NAME);

	p_obj_para_def->Register_Command(pKEY__DATA_DIR_SUB);
	p_obj_para_def->Register_Command(pKEY__DATA_FILE_EXT);

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_WIDTH, "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_HEIGHT, "", "", "15");

	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH, "", "", "1");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(244,245,249)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(174,175,179)");

	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_TEXT);
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_COLOR, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_COLOR, "Color", "", "RGB(210,210,210)");

	//
	p_obj_para_def->Register_Command(pKEY__TEST_CH_RECIPE_NAME);
	p_obj_para_def->Register_Command(pKEY__TEST_POPUP_MODE, "ListBox", "NO YES", "NO");
}
void CObj__Recipe_Select_STD
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

		COLORREF color;
		CString ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_EQP_ID, ch_data);
		if(ch_data.CompareNoCase("LOCAL_ID") == 0)		iEQP_ID = module_id;
		else											iEQP_ID = atoi(ch_data);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_DIR_SUB, ch_data);
		sData__Dir_Sub = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_FILE_EXT, ch_data);
		sData__File_Ext = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_NAME, ch_data);
		CString font_name = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_WIDTH, ch_data);
		int font_width = atoi(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_HEIGHT, ch_data);
		int font_height = atoi(ch_data);

		p_Button->SetFont(font_name, font_width, font_height);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_WIDTH, ch_data);
		int edge_width = 2;
		if(ch_data.GetLength() > 0)		edge_width = atoi(ch_data);
		p_Button->SetThick(edge_width);

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_UP_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(255,255,255)";
		p_Button->SetUpColor(p_Utility->GetColor(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_DOWN_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(174,175,179)";
		p_Button->SetDownColor(p_Utility->GetColor(ch_data));

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_TEXT, ch_data);
		p_Button->SetTitle(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_COLOR, ch_data);
		color = p_Utility->GetColor(ch_data);
		p_Button->SetTextColorReleased(color);
		p_Button->SetTextColorPressed(color);

		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR, ch_data);
		color = p_Utility->GetColor(ch_data);
		p_Button->SetReleasedColor(color);
		p_Button->SetPressedColor(color);

		//		
		p_Button->SetPosition(pSt, pEt);
	}
}

void CObj__Recipe_Select_STD
::Show_GObj(const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	p_Button->DrawReleased(hdc_front, hdc_back);
}
void CObj__Recipe_Select_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Recipe_Select_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Recipe_Select_STD::
WM_Timer(const HWND& hwnd)
{

}

void CObj__Recipe_Select_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	POINT pt = mouse_pt;

	if(p_Button->CheckArea(pt) >= 0)
	{
		GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;

		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		// ...
		CGX_FILE__PM_CTRL x_pm_ctrl;
		CString in__file_name;
		CString out__file_name;
		CString ch_data;
		bool active_popup = true;

		if(iREAL_MODE > 0)
		{
			p_gobj->Get_Channel_Data(pKEY__CH_RECIPE_NAME, ch_data);
		}	
		else
		{
			p_gobj->Get_Constant_Data(pKEY__TEST_POPUP_MODE, ch_data);
			if(ch_data.CompareNoCase("NO") == 0)		active_popup = false;

			p_gobj->Get_Constant_Data(pKEY__TEST_CH_RECIPE_NAME, ch_data);
		}

		p_Button->DrawPressed(hdc_front, hdc_back);
		
		if(active_popup)
		{
			in__file_name = ch_data;

			if(x_pm_ctrl->Popup_File_Select(iEQP_ID,
											sData__Dir_Sub,
											sData__File_Ext,
											in__file_name,
											out__file_name) > 0)
			{
				p_gobj->Set_Suffix_Feedback(pKEY__CH_RECIPE_NAME, out__file_name);
			}
		}
		else
		{
			Sleep(200);
		}

		p_Button->DrawReleased(hdc_front, hdc_back);
	}

}
void CObj__Recipe_Select_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Recipe_Select_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Recipe_Select_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Recipe_Select_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

