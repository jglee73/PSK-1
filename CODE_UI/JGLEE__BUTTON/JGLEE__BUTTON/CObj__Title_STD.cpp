#include "StdAfx.h"
#include "CObj__Title_STD.h"
#include "CObj__Title_STD__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Title_STD::CObj__Title_STD()
{

}
CObj__Title_STD::~CObj__Title_STD()
{

}


//-------------------------------------------------------------------------------------
void CObj__Title_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__ACTIVE_DISPLAY_PRESSED, "ListBox", "NO YES", "NO");
	p_obj_para_def->Register_Channel(pKEY__CH_DISPLAY_PRESSED);
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_PRESSED);

	//
	p_obj_para_def->Register_Channel(pKEY__CH_SET_01);
	p_obj_para_def->Register_Channel(pKEY__CH_SET_02);

	//
	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_TEXT);

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_COLOR, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_COLOR, "Color", "", "RGB(255,255,255)");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_WIDTH,  "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_HEIGHT, "", "", "15");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_WEIGHT, "", "", "");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH,  "", "", "1");

	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(174,175,179)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(244,245,249)");

	p_obj_para_def->Register_Command(pKEY__DATA_OUTLINE_COLOR, "Color", "", "");

	//
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_Y_POS_OFFSET, "", "", "0");
}
void CObj__Title_STD
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

		p_gobj->Get_Constant_Data(pKEY__DATA_FONT_NAME, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "Fixedsys";
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

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_UP_COLOR, ch_data);
		mBtn.Set_Property__Edge_Up_Color(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_DOWN_COLOR, ch_data);
		mBtn.Set_Property__Edge_Down_Color(ch_data);

		bActive_Outline = false;
		p_gobj->Get_Constant_Data(pKEY__DATA_OUTLINE_COLOR, ch_data);
		if(ch_data.Find("RGB") >= 0)		
		{
			int r, g, b;

			bActive_Outline = true;
			cColor__Outline = p_gobj->Get_RGB_Color(ch_data, r,g,b);
		}

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TEXT_Y_POS_OFFSET, ch_data);
		mBtn.Set_Property__Text_Y_Pos_Offset(atoi(ch_data));

		//
		mBtn.Set_Property__Bttn_Setting();
		mBtn.End_Property();
	}

	// ...
	{
		CString ch_data;

		p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_TITLE_TEXT, ch_data);
		mBtn.Set_Title(ch_data, true);

		//
		bActive__Display_Pressed = false;
		
		p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__ACTIVE_DISPLAY_PRESSED, ch_data);
		if(ch_data.CompareNoCase("YES") == 0)
		{
			p_obj_res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__DATA_DISPLAY_PRESSED, ch_data);
			sData__Display_Pressed = ch_data;

			if(ch_data.GetLength() > 0)			bActive__Display_Pressed = true;
		}
	}

	bActive__Button_Pressed = false;
}

void CObj__Title_STD
::Show_GObj(const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	// ...
	{
		mBtn.Init(hdc_front,hdc_back, pSt,pEt);
		mBtn.WM_LButtonUp();	
	}
	
	if(bActive_Outline)
	{
		mFnc.Draw_Rectangle(hdc_back,  pSt_Out,pEt_Out, 1, cColor__Outline, cColor__Outline);
		mFnc.Draw_Rectangle(hdc_front, pSt_Out,pEt_Out, 1, cColor__Outline, cColor__Outline);
	}
}
void CObj__Title_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Title_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Title_STD::
WM_Timer(const HWND& hwnd)
{
	if(bActive__Display_Pressed)
	{
		CString ch_data;
		pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(pKEY__CH_DISPLAY_PRESSED, ch_data);

		if(ch_data.CompareNoCase(sData__Display_Pressed) == 0)
		{
			if(!bActive__Button_Pressed)
			{
				bActive__Button_Pressed = true;

				mBtn.WM_LButtonDown();
			}
		}
		else
		{
			if(bActive__Button_Pressed)
			{
				bActive__Button_Pressed = false;

				mBtn.WM_LButtonUp();
			}
		}
	}
}

void CObj__Title_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	if(bActive__Display_Pressed)
	{

	}
	else
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
	}
}
void CObj__Title_STD::
WM_LButtonUp(const HWND& hwnd)
{
	if(bActive__Display_Pressed)
	{

	}
	else
	{
		mBtn.WM_LButtonUp();	
	}
}

void CObj__Title_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Title_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Title_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

