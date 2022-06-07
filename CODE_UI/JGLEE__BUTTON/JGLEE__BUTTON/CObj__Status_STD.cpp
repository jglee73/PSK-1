#include "StdAfx.h"
#include "CObj__Status_STD.h"
#include "CObj__Status_STD__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Status_STD::CObj__Status_STD()
{
	p_Utility = New_UTILITY();
	p_Button  = New_BUTTON();
}
CObj__Status_STD::~CObj__Status_STD()
{
	delete p_Utility;
	delete p_Button;
}


//-------------------------------------------------------------------------------------
void CObj__Status_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Channel(pKEY__CH_STATE);
	p_obj_para_def->Register_Channel(pKEY__CH_SUB_DATA);

	p_obj_para_def->Register_Command(pKEY__DATA_P_STATTE);
	p_obj_para_def->Register_Command(pKEY__DATA_P_SUB_STATTE);
	p_obj_para_def->Register_Command(pKEY__DATA_R_STATTE);
	p_obj_para_def->Register_Command(pKEY__DATA_P_TITLE);
	p_obj_para_def->Register_Command(pKEY__DATA_R_TITLE);

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_WIDTH, "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_HEIGHT, "", "", "15");

	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH, "", "", "1");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(244,245,249)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(174,175,179)");

	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_P_COLOR, "Color", "", "RGB(110,110,110)");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_R_COLOR, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_P_COLOR, "Color", "", "RGB(155,155,155)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_R_COLOR, "Color", "", "RGB(255,255,255)");

	p_obj_para_def->Register_Command(pKEY__DATA_OUTLINE_COLOR, "Color", "", "");

	//
	p_obj_para_def->Register_Command(pKEY__TEST_CH_STATE);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_SUB_STATE);
}
void CObj__Status_STD
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
	{
		GObj__Parameter_Ctrl* p_gobj = p_obj_res->pGOBJ_PARA_CTRL;
		CString ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_P_STATTE, ch_data);
		sData__P_State = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_P_SUB_STATTE, ch_data);
		sData__P_Sub_State = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_R_STATTE, ch_data);
		sData__R_State = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_P_TITLE, ch_data);
		sData__P_Title = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_R_TITLE, ch_data);
		sData__R_Title = ch_data;

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
		if(ch_data.GetLength() < 1)			ch_data = "2";
		p_Button->SetThick(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_UP_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(255,255,255)";
		p_Button->SetUpColor(p_Utility->GetColor(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_DOWN_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(174,175,179)";
		p_Button->SetDownColor(p_Utility->GetColor(ch_data));

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_P_COLOR, ch_data);
		p_Button->SetTextColorPressed(p_Utility->GetColor(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_R_COLOR, ch_data);
		p_Button->SetTextColorReleased(p_Utility->GetColor(ch_data));

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_P_COLOR, ch_data);
		p_Button->SetPressedColor(p_Utility->GetColor(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_R_COLOR, ch_data);
		p_Button->SetReleasedColor(p_Utility->GetColor(ch_data));

		//
		bActive_Outline = false;
		p_gobj->Get_Constant_Data(pKEY__DATA_OUTLINE_COLOR, ch_data);

		if(ch_data.Find("RGB") >= 0)
		{
			bActive_Outline = true;
			cColor_Outline = p_Utility->GetColor(ch_data);
		}

		//		
		p_Button->SetPosition(pSt, pEt);
	}
}

void CObj__Status_STD
::Show_GObj(const HWND& hwnd)
{
	iButton_State = 0;
	Draw_Button();
}
void CObj__Status_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Status_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Status_STD::
WM_Timer(const HWND& hwnd)
{
	Draw_Button();
}

void CObj__Status_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	POINT pt = mouse_pt;

	if(p_Button->CheckArea(pt) >= 0)
	{
		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		if(iButton_State < 1)
		{
			p_Button->DrawPressed(hdc_front, hdc_back);
			Sleep(200);
			p_Button->DrawReleased(hdc_front, hdc_back);
		}
	}
}
void CObj__Status_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Status_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Status_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Status_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Status_STD::
Draw_Button()
{
	GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;

	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	// ...
	CString ch_data;
	CString ch_sub_data;

	if(iREAL_MODE > 0)
	{
		p_gobj->Get_Channel_Data(pKEY__CH_STATE,    ch_data);
		p_gobj->Get_Channel_Data(pKEY__CH_SUB_DATA, ch_sub_data);
	}	
	else
	{
		p_gobj->Get_Constant_Data(pKEY__TEST_CH_STATE,     ch_data);
		p_gobj->Get_Constant_Data(pKEY__TEST_CH_SUB_STATE, ch_sub_data);
	}

	// ...
	bool active__p_state = false;

	if((sData__P_State.GetLength()     > 0)
	&& (sData__P_Sub_State.GetLength() > 0))
	{
		if((ch_data.CompareNoCase(sData__P_State) == 0)
		&& (ch_sub_data.CompareNoCase(sData__P_Sub_State) == 0))
		{
			active__p_state = true;
		}
	}
	else if(sData__P_State.GetLength() > 0)
	{
		if(ch_data.CompareNoCase(sData__P_State) == 0)					active__p_state = true;
	}
	else if(sData__P_Sub_State.GetLength() > 0)
	{
		if(ch_sub_data.CompareNoCase(sData__P_Sub_State) == 0)			active__p_state = true;
	}

	if(active__p_state)
	{
		if(iButton_State < 1)
		{
			iButton_State = 1;

			p_Button->SetTitle(sData__P_Title);
			p_Button->DrawPressed(hdc_front, hdc_back);
		}
	}
	else
	{
		if(iButton_State > -1)
		{
			iButton_State = -1;

			p_Button->SetTitle(sData__R_Title);
			p_Button->DrawReleased(hdc_front, hdc_back);
		}
	}

	if(bActive_Outline)
	{
		mFnc.Draw_Rectangle(hdc_back,  pSt_Out,pEt_Out, 1, cColor_Outline, cColor_Outline);
		mFnc.Draw_Rectangle(hdc_front, pSt_Out,pEt_Out, 1, cColor_Outline, cColor_Outline);
	}
}
