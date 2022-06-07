#include "StdAfx.h"
#include "CObj__Active_STD.h"
#include "CObj__Active_STD__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Active_STD::CObj__Active_STD()
{
	p_Button  = New_BUTTON();
}
CObj__Active_STD::~CObj__Active_STD()
{
	delete p_Button;
}


//-------------------------------------------------------------------------------------
void CObj__Active_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_COMMENT);

	p_obj_para_def->Register_Channel(pKEY__CH_FEEDBACK_1);
	p_obj_para_def->Register_Channel(pKEY__CH_FEEDBACK_2);
	p_obj_para_def->Register_Command(pKEY__DATA_SET_DATA_1);
	p_obj_para_def->Register_Command(pKEY__DATA_SET_DATA_2);

	p_obj_para_def->Register_Channel(pKEY__CH_DISPLAY_1);
	p_obj_para_def->Register_Channel(pKEY__CH_DISPLAY_2);
	p_obj_para_def->Register_Channel(pKEY__CH_DISPLAY_3);
	p_obj_para_def->Register_Channel(pKEY__CH_DISPLAY_4);
	p_obj_para_def->Register_Channel(pKEY__CH_DISPLAY_5);
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_STS_1);
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_STS_2);
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_STS_3);
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_STS_4);
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_STS_5);

	p_obj_para_def->Register_Channel(pKEY__CH_SET_1);
	p_obj_para_def->Register_Channel(pKEY__CH_SET_2);

	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_CONDITION, "ListBox", "AND OR", "AND");
	p_obj_para_def->Register_Channel(pKEY__CH_ACTIVE_1);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_1);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_2);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_3);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_4);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_5);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_6);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_7);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_1_STS_8);
	p_obj_para_def->Register_Channel(pKEY__CH_ACTIVE_2);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_1);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_2);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_3);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_4);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_5);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_6);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_7);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE_2_STS_8);

	p_obj_para_def->Register_Command(pKEY__DATA_INACTIVE_COLOR, "Color", "", "RGB(155,155,155)");

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_WIDTH, "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_HEIGHT, "", "", "15");

	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH, "", "", "1");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(244,245,249)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(174,175,179)");

	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_TEXT_1);
	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_TEXT_2);
	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_COLOR_1, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_COLOR_2, "Color", "", "RGB(210,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_COLOR_1, "Color", "", "RGB(210,210,210)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_COLOR_2, "Color", "", "RGB(210,210,210)");
	p_obj_para_def->Register_Command(pKEY__DATA_OUTLINE_COLOR, "Color", "", "");

	p_obj_para_def->Register_Command(pKEY__DATA_ACTION_CONFIRM, "ListBox", "NO YES", "NO");

	//...
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_1);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_2);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_3);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_4);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_5);

	p_obj_para_def->Register_Command(pKEY__TEST_CH_ACTIVE_1);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_ACTIVE_2);

	p_obj_para_def->Register_Command(pKEY__TEST_POPUP_MODE, "ListBox", "NO YES", "NO");
}
void CObj__Active_STD
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

		rAREA.left   = pSt_Out.x;
		rAREA.top    = pSt_Out.y;
		rAREA.right  = pEt_Out.x;
		rAREA.bottom = pEt_Out.y;

		//
		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();
		pGObj_Res  = p_obj_res;
	}

	// ...
	CI_UTILITY* p_utility = New_UTILITY();

	// ...
	{
		GObj__Parameter_Ctrl* p_gobj = p_obj_res->pGOBJ_PARA_CTRL;
		CString ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_SET_DATA_1, ch_data);
		sData__Set_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_SET_DATA_2, ch_data);
		sData__Set_2 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_STS_1, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Display_Sts_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_STS_2, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Display_Sts_2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_STS_3, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Display_Sts_3 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_STS_4, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Display_Sts_4 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_STS_5, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Display_Sts_5 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_CONDITION, ch_data);
		sData__Active_Condition = ch_data;
		
		if(ch_data.CompareNoCase("AND") == 0)		bActivve__Condition_AND = true;
		else										bActivve__Condition_AND = false;

		if(ch_data.CompareNoCase("OR") == 0)		bActivve__Condition_OR = true;
		else										bActivve__Condition_OR = false;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_1, ch_data);
		sData__Active_1_Sts_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_2, ch_data);
		sData__Active_1_Sts_2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_3, ch_data);
		sData__Active_1_Sts_3 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_4, ch_data);
		sData__Active_1_Sts_4 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_5, ch_data);
		sData__Active_1_Sts_5 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_6, ch_data);
		sData__Active_1_Sts_6 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_7, ch_data);
		sData__Active_1_Sts_7 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_1_STS_8, ch_data);
		sData__Active_1_Sts_8 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_1, ch_data);
		sData__Active_2_Sts_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_2, ch_data);
		sData__Active_2_Sts_2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_3, ch_data);
		sData__Active_2_Sts_3 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_4, ch_data);
		sData__Active_2_Sts_4 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_5, ch_data);
		sData__Active_2_Sts_5 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_6, ch_data);
		sData__Active_2_Sts_6 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_7, ch_data);
		sData__Active_2_Sts_7 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE_2_STS_8, ch_data);
		sData__Active_2_Sts_8 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_INACTIVE_COLOR, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "RGB(150,150,150)";
		cColor_Inactive = p_utility->GetColor(ch_data);
		p_Button->SetInActiveColor(cColor_Inactive);

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
		p_Button->SetUpColor(p_utility->GetColor(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_DOWN_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(174,175,179)";
		p_Button->SetDownColor(p_utility->GetColor(ch_data));

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_TEXT_1, ch_data);
		sData__Title_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_TEXT_2, ch_data);
		sData__Title_2 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_COLOR_1, ch_data);
		cColor__Title_1 = p_utility->GetColor(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_COLOR_2, ch_data);
		cColor__Title_2 = p_utility->GetColor(ch_data);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR_1, ch_data);
		cColor__Background_1 = p_utility->GetColor(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR_2, ch_data);
		cColor__Background_2 = p_utility->GetColor(ch_data);

		//
		bActive_Outline = false;
		p_gobj->Get_Constant_Data(pKEY__DATA_OUTLINE_COLOR, ch_data);
		if(ch_data.Find("RGB") >= 0)
		{
			bActive_Outline = true;
			cColor__Outline = p_utility->GetColor(ch_data);
		}

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTION_CONFIRM, ch_data);
		if(ch_data.CompareNoCase("YES") == 0)			bActivve_Confirm = true;
		else											bActivve_Confirm = false;

		//		
		p_Button->SetPosition(pSt, pEt);
	}

	delete p_utility;
}

void CObj__Active_STD
::Show_GObj(const HWND& hwnd)
{
	iActive_Flag = 0;
	iButton_Flag = 0;

	Draw_Button();
}
void CObj__Active_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Active_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Active_STD::
WM_Timer(const HWND& hwnd)
{
	Draw_Button();
}

void CObj__Active_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	POINT pt = mouse_pt;

	if(p_Button->CheckArea(pt) >= 0)
	{
		if(iActive_Flag <= 0)		
		{
			return;
		}

		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		if(bActivve_Confirm)
		{
			CString err_title;
			CString err_msg;

			if(iButton_Flag == 1)
			{
				CString ch_name;
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Name(pKEY__CH_FEEDBACK_1, ch_name);

				err_title = "CONFIRM BUTTON";
				err_msg.Format("%s -> %s", ch_name,sData__Set_1);
			}
			else if(iButton_Flag == 2)
			{
				CString ch_name;
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Name(pKEY__CH_FEEDBACK_2, ch_name);

				err_title = "CONFIRM BUTTON";				
				err_msg.Format("%s -> %s", ch_name,sData__Set_2);
			}
			else
			{
				return;
			}

			// ...
			bool active_check = true;

			if(iREAL_MODE < 0)
			{
				CString ch_data;

				pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__TEST_POPUP_MODE, ch_data);
				if(ch_data.CompareNoCase("NO") == 0)		active_check = false;
			}

			p_Button->DrawPressed(hdc_front, hdc_back);

			if(active_check)
			{
				int flag = MessageBox(hwnd, 
									  err_msg, 
									  err_title, 
									  MB_YESNO|MB_TOPMOST|MB_TASKMODAL|MB_ICONINFORMATION);

				if(flag != IDYES)
				{
					p_Button->DrawReleased(hdc_front, hdc_back);

					InvalidateRect(hwnd, &rAREA, TRUE);
					return;
				}
			}
			else
			{
				Sleep(200);
			}
		}
		else
		{
			p_Button->DrawPressed(hdc_front, hdc_back);
			Sleep(200);
		}

		p_Button->DrawReleased(hdc_front, hdc_back);

		// ...
		GObj__Parameter_Ctrl* p_para_ctrl = pGObj_Res->pGOBJ_PARA_CTRL;
		CString str_comment;

		p_para_ctrl->Get_Constant_Data(pKEY__DATA_COMMENT, str_comment);

		if(iButton_Flag == 1)
		{
			p_para_ctrl->Set_Suffix_Feedback_With_Comment(pKEY__CH_FEEDBACK_1, sData__Set_1, str_comment);
		}
		else if(iButton_Flag == 2)
		{
			p_para_ctrl->Set_Suffix_Feedback_With_Comment(pKEY__CH_FEEDBACK_2, sData__Set_2, str_comment);
		}

		InvalidateRect(hwnd, &rAREA, TRUE);
	}
}
void CObj__Active_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Active_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Active_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Active_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Active_STD::
Draw_Button()
{
	GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;

	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	// ...
	int draw_flag = -1;
	
	int active_flag  = -1;
	int active_flag1 = -1;
	int active_flag2 = -1;

	// Active Check ...
	{
		CString ch_active1;
		CString ch_active2;

		if(iREAL_MODE > 0)
		{
			p_gobj->Get_Channel_Data(pKEY__CH_ACTIVE_1, ch_active1);
			p_gobj->Get_Channel_Data(pKEY__CH_ACTIVE_2, ch_active2);
		}	
		else
		{
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_ACTIVE_1, ch_active1);
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_ACTIVE_2, ch_active2);
		}

		if(ch_active1.GetLength() > 0)
		{
			if((ch_active1.CompareNoCase(sData__Active_1_Sts_1) == 0)
 			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_2) == 0)
			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_3) == 0)
			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_4) == 0)
			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_5) == 0)
			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_6) == 0)
			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_7) == 0)
			|| (ch_active1.CompareNoCase(sData__Active_1_Sts_8) == 0))
			{
				active_flag1 = 1;
			}
		}
		else
		{
			active_flag1 = 0;
		}

		if(ch_active2.GetLength() > 0)
		{
			if((ch_active2.CompareNoCase(sData__Active_2_Sts_1) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_2) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_3) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_4) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_5) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_6) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_7) == 0)
			|| (ch_active2.CompareNoCase(sData__Active_2_Sts_8) == 0))
			{
				active_flag2 = 1;
			}
		}
		else
		{
			active_flag2 = 0;
		}

		if(bActivve__Condition_AND)
		{
			if((active_flag1 > 0)
			|| (active_flag2 > 0))
			{
				if((active_flag1 < 0)
				|| (active_flag2 < 0))
				{

				}
				else
				{
					active_flag = 1;
				}
			}
		}
		else if(bActivve__Condition_OR)
		{
			if((active_flag1 > 0)
			|| (active_flag2 > 0))
			{
				active_flag = 1;
			}
		}

		if(active_flag < 0)
		{
			if(iActive_Flag >= 0)
			{
				iActive_Flag = -1;
				
				p_Button->SetInActive();
				draw_flag = 1;
			}
		}
		else
		{
			if(iActive_Flag <= 0)
			{
				iActive_Flag = 1;
				
				p_Button->SetActive();
				draw_flag = 1;
			}
		}
	}

	// Display Check ...
	{
		CString ch_data1;
		CString ch_data2;
		CString ch_data3;
		CString ch_data4;
		CString ch_data5;

		if(iREAL_MODE > 0)
		{
			p_gobj->Get_Channel_Data(pKEY__CH_DISPLAY_1, ch_data1);
			p_gobj->Get_Channel_Data(pKEY__CH_DISPLAY_2, ch_data2);
			p_gobj->Get_Channel_Data(pKEY__CH_DISPLAY_3, ch_data3);
			p_gobj->Get_Channel_Data(pKEY__CH_DISPLAY_4, ch_data4);
			p_gobj->Get_Channel_Data(pKEY__CH_DISPLAY_5, ch_data5);
		}	
		else
		{
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_DISPLAY_1, ch_data1);
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_DISPLAY_2, ch_data2);
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_DISPLAY_3, ch_data3);
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_DISPLAY_4, ch_data4);
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_DISPLAY_5, ch_data5);
		}

		if((ch_data1.CompareNoCase(sData__Display_Sts_1) == 0)
		|| (ch_data2.CompareNoCase(sData__Display_Sts_2) == 0)
		|| (ch_data3.CompareNoCase(sData__Display_Sts_3) == 0)
		|| (ch_data4.CompareNoCase(sData__Display_Sts_4) == 0)
		|| (ch_data5.CompareNoCase(sData__Display_Sts_5) == 0))
		{
			if(iButton_Flag != 1)
			{
				iButton_Flag = 1;

				p_Button->SetTitle(sData__Title_1);
				p_Button->SetTextColor(cColor__Title_1);
				p_Button->SetReleasedColor(cColor__Background_1);

				draw_flag = 1;
			}
		}	
		else
		{
			if(iButton_Flag != 2)
			{
				iButton_Flag = 2;

				p_Button->SetTitle(sData__Title_2);
				p_Button->SetTextColor(cColor__Title_2);
				p_Button->SetReleasedColor(cColor__Background_2);

				draw_flag = 1;
			}
		}
	}

	if(draw_flag > 0)
	{
		p_Button->DrawReleased(hdc_front, hdc_back);

		if(bActive_Outline)
		{
			mFnc.Draw_Rectangle(hdc_back,  pSt_Out,pEt_Out, 1, cColor__Outline, cColor__Outline);
			mFnc.Draw_Rectangle(hdc_front, pSt_Out,pEt_Out, 1, cColor__Outline, cColor__Outline);
		}
	}
}
