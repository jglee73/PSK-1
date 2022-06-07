#include "StdAfx.h"
#include "CObj__Ctrl_LIST.h"
#include "CObj__Ctrl_LIST__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Ctrl_LIST::CObj__Ctrl_LIST()
{
	p_Button  = New_BUTTON();
}
CObj__Ctrl_LIST::~CObj__Ctrl_LIST()
{
	delete p_Button;
}


//-------------------------------------------------------------------------------------
void CObj__Ctrl_LIST
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString key_name;
	int i;

	// ...
	p_obj_para_def->Register_Command(pKEY__DATA_COMMENT);

	p_obj_para_def->Register_Channel(pKEY__CH_FEEDBACK_PARA);

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

	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_CONDITION, "ListBox", "AND OR", "AND");
	p_obj_para_def->Register_Channel(pKEY__CH_LOCK_STS);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_1);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_2);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_3);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_4);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_5);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_6);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_7);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS_8);
	p_obj_para_def->Register_Channel(pKEY__CH_LOCK_STS2);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_1);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_2);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_3);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_4);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_5);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_6);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_7);
	p_obj_para_def->Register_Command(pKEY__DATA_LOCK_STS2_8);

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

	// ...
	p_obj_para_def->Register_Command(pKEY__DATA_ITEM_SIZE, "ListBox", "5", "5");
	iPara__ITEM_SIZE = 5;

	for(i=0; i<iPara__ITEM_SIZE; i++)
	{
		int id = i + 1;

		key_name.Format("%s%1d", pKEY__CH_ITEM_USE_X, id);
		p_obj_para_def->Register_Channel(key_name);

		key_name.Format("%s%1d", pKEY__CH_ITEM_DATA_X, id);
		p_obj_para_def->Register_Channel(key_name);

		key_name.Format("%s%1d", pKEY__CH_ITEM_COMMENT_X, id);
		p_obj_para_def->Register_Channel(key_name);
	}

	//...
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_1);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_2);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_3);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_4);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_DISPLAY_5);

	p_obj_para_def->Register_Command(pKEY__TEST_CH_LOCK_STS);
	p_obj_para_def->Register_Command(pKEY__TEST_CH_LOCK_STS2);

	p_obj_para_def->Register_Command(pKEY__TEST_POPUP_MODE, "ListBox", "NO YES", "NO");

	p_obj_para_def->Register_Command(pKEY__TEST_DEBUG_MODE, "ListBox", "NO YES", "NO");
}
void CObj__Ctrl_LIST
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
		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_CONDITION, ch_data);
		sData__Lock_Condition = ch_data;

		if(ch_data.CompareNoCase("AND") == 0)		bLock__Condition_AND = true;
		else										bLock__Condition_AND = false;

		if(ch_data.CompareNoCase("OR") == 0)		bLock__Condition_OR = true;
		else										bLock__Condition_OR = false;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_1, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_2, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_3, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_3 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_4, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_4 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_5, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_5 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_6, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_6 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_7, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_7 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS_8, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts1_8 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_1, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_2, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_3, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_3 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_4, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_4 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_5, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_5 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_6, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_6 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_7, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_7 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_LOCK_STS2_8, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "~";
		sData__Lock_Sts2_8 = ch_data;

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
		if(ch_data.GetLength() < 1)		ch_data = "RGB(0,0,0)";
		cColor__Title_1 = p_utility->GetColor(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_COLOR_2, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(0,0,0)";
		cColor__Title_2 = p_utility->GetColor(ch_data);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR_1, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(230,230,230)";
		cColor__Background_1 = p_utility->GetColor(ch_data);

		p_gobj->Get_Constant_Data(pKEY__DATA_BACK_COLOR_2, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(230,230,230)";
		cColor__Background_2 = p_utility->GetColor(ch_data);

		bActive_Outline = false;
		p_gobj->Get_Constant_Data(pKEY__DATA_OUTLINE_COLOR, ch_data);
		if(ch_data.Find("RGB") >= 0)
		{
			bActive_Outline = true;
			cColor__Outline = p_utility->GetColor(ch_data);
		}

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_COMMENT, sData__Comment);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTION_CONFIRM, ch_data);
		if(ch_data.CompareNoCase("YES") == 0)			bActivve_Confirm = true;
		else											bActivve_Confirm = false;

		//
		p_gobj->Get_Constant_Data(pKEY__TEST_DEBUG_MODE, ch_data);
		if(ch_data.CompareNoCase("YES") == 0)			bActivve_Debug_Mode = true;
		else											bActivve_Debug_Mode = false;

		//		
		p_Button->SetPosition(pSt, pEt);
	}

	delete p_utility;
}

void CObj__Ctrl_LIST
::Show_GObj(const HWND& hwnd)
{
	iActive_Flag = 0;
	iButton_Flag = 0;

	Draw_Button();
}
void CObj__Ctrl_LIST
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Ctrl_LIST
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Ctrl_LIST::
WM_Timer(const HWND& hwnd)
{
	Draw_Button();
}

void CObj__Ctrl_LIST::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	if(iActive_Flag <= 0)		return;

	// ...
	POINT pt = mouse_pt;

	if(p_Button->CheckArea(pt) >= 0)
	{
		int btn_state = iButton_Flag;

		if((iREAL_MODE > 0)
		&& (btn_state == 1))
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());

			// ...
			CDlg__Ctrl_List dlg_list;

			CStringArray l__item_data;
			CStringArray l__item_comment;

			CString key_name;
			CString ch_data;
			int i;

			for(int i=0; i<iPara__ITEM_SIZE; i++)
			{
				int id = i + 1;

				//
				key_name.Format("%s%1d", pKEY__CH_ITEM_USE_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				if(ch_data.CompareNoCase("YES") != 0)		continue;
	
				//
				key_name.Format("%s%1d", pKEY__CH_ITEM_DATA_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				if(ch_data.GetLength() < 1)					continue;

				l__item_data.Add(ch_data);

				//
				key_name.Format("%s%1d", pKEY__CH_ITEM_COMMENT_X, id);
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Data(key_name, ch_data);

				l__item_comment.Add(ch_data);
			}

			dlg_list.sList__DATA.Copy(l__item_data);
			dlg_list.sList__COMMENT.Copy(l__item_comment);

			int r_data = dlg_list.DoModal();

			printf(" * Dlg.r_data <- [%1d] \n", r_data);
			printf(" * Dlg.IDOK   <- [%1d] \n", IDOK);

			if(r_data != IDOK)								return;
			if(dlg_list.iRESULT__SEL_INDEX < 0)				return;

			printf(" * Result.Sel_Index <- [%1d] \n", dlg_list.iRESULT__SEL_INDEX);
			printf(" * Result.Sel_Data  <- [%s]  \n", dlg_list.sRESULT__SEL_DATA);

			sData__Set_Para = dlg_list.sRESULT__SEL_DATA;
		}

		// ...
		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		if(bActivve_Confirm)
		{
			CString err_title;
			CString err_msg;
			CString err_bff;

			if(btn_state == 1)
			{
				CString ch_name;		
				pGObj_Res->pGOBJ_PARA_CTRL->Get_Channel_Name(pKEY__CH_FEEDBACK_1, ch_name);

				err_title = "CONFIRM BUTTON";

				err_msg.Format("%s \n", sData__Comment);
				err_bff.Format("%s -> %s \n", ch_name,sData__Set_1);
				err_msg += err_bff;
			}
			else if(btn_state == 2)
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
		CString str_comment = sData__Comment;

		if(btn_state == 1)
		{
			p_para_ctrl->Set_Suffix_Feedback_With_Comment(pKEY__CH_FEEDBACK_PARA, sData__Set_Para, "");
			p_para_ctrl->Set_Suffix_Feedback_With_Comment(pKEY__CH_FEEDBACK_1, sData__Set_1, str_comment);
		}
		else if(btn_state == 2)
		{
			p_para_ctrl->Set_Suffix_Feedback_With_Comment(pKEY__CH_FEEDBACK_2, sData__Set_2, str_comment);
		}

		InvalidateRect(hwnd, &rAREA, TRUE);
	}
}
void CObj__Ctrl_LIST::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Ctrl_LIST::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Ctrl_LIST::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Ctrl_LIST::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}


//-------------------------------------------------------------------------------------	
void CObj__Ctrl_LIST::
Draw_Button()
{
	GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;

	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	// ...
	int draw_flag = -1;

	// Lock Channel ...
	{
		CString ch_data1;
		CString ch_data2;

		if(iREAL_MODE > 0)
		{
			p_gobj->Get_Channel_Data(pKEY__CH_LOCK_STS,  ch_data1);
			p_gobj->Get_Channel_Data(pKEY__CH_LOCK_STS2, ch_data2);
		}	
		else
		{
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_LOCK_STS,  ch_data1);
			p_gobj->Get_Constant_Data(pKEY__TEST_CH_LOCK_STS2, ch_data2);
		}

		// ...
		int data_count = 0;
		bool active_lock_1 = false;
		bool active_lock_2 = false;

		if(ch_data1.GetLength() > 0)
		{
			data_count++;

			if((ch_data1.CompareNoCase(sData__Lock_Sts1_1) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_2) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_3) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_4) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_5) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_6) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_7) == 0)
			|| (ch_data1.CompareNoCase(sData__Lock_Sts1_8) == 0))
			{
				active_lock_1 = true;
			}
		}
		else
		{
				 if(bLock__Condition_AND)		active_lock_1 = true;
			else if(bLock__Condition_OR)		active_lock_1 = false;
		}

		if(ch_data2.GetLength() > 0)
		{
			data_count++;

			if((ch_data2.CompareNoCase(sData__Lock_Sts2_1) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_2) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_3) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_4) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_5) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_6) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_7) == 0)
			|| (ch_data2.CompareNoCase(sData__Lock_Sts2_8) == 0))
			{
				active_lock_2 = true;
			}
		}
		else
		{
				 if(bLock__Condition_AND)		active_lock_2 = true;
			else if(bLock__Condition_OR)		active_lock_2 = false;
		}

		// ...
		bool active_lock_btn = false;

		if(data_count > 0)
		{
			if(bLock__Condition_AND)
			{
				if((active_lock_1) && (active_lock_2))
				{
					active_lock_btn = true;
				}
			}
			else if(bLock__Condition_OR)
			{
				if((active_lock_1) || (active_lock_2))
				{
					active_lock_btn = true;
				}
			}
		}

		if(active_lock_btn)
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
				draw_flag = 2;
			}
		}

		if(bActivve_Debug_Mode)
		{
			CString log_msg;
			CString log_bff;

			log_bff.Format(" * ch_data_1 <- %s \n", ch_data1);
			log_msg += log_bff;
			log_bff.Format(" * ch_data_2 <- %s \n", ch_data2);
			log_msg += log_bff;

			log_bff.Format(" * bLock__Condition_AND <- %1d \n", bLock__Condition_AND);
			log_msg += log_bff;
			log_bff.Format(" * bLock__Condition_OR  <- %1d \n", bLock__Condition_OR);
			log_msg += log_bff;
			log_bff.Format(" * active_lock_btn <- %1d \n", active_lock_btn);
			log_msg += log_bff;
			log_bff.Format(" * active_lock_1 <- %1d \n", active_lock_1);
			log_msg += log_bff;
			log_bff.Format(" * active_lock_2 <- %1d \n", active_lock_2);
			log_msg += log_bff;
			log_msg += "\n";

			printf(log_msg);
		}
	}

	// Display Channel ...
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

		// ...
		bool active_sts = false; 

		// ...
		{
			if((ch_data1.GetLength() > 0)
			&& (ch_data1.CompareNoCase(sData__Display_Sts_1) == 0))
			{
				active_sts = true;
			}
			else if((ch_data2.GetLength() > 0)
				 && (ch_data2.CompareNoCase(sData__Display_Sts_2) == 0))
			{
				active_sts = true;
			}
			else if((ch_data3.GetLength() > 0)
				 && (ch_data3.CompareNoCase(sData__Display_Sts_3) == 0))
			{
				active_sts = true;
			}
			else if((ch_data4.GetLength() > 0)
				 && (ch_data4.CompareNoCase(sData__Display_Sts_4) == 0))
			{
				active_sts = true;
			}
			else if((ch_data5.GetLength() > 0)
				 && (ch_data5.CompareNoCase(sData__Display_Sts_5) == 0))
			{
				active_sts = true;
			}
			else if((ch_data1 == "")
				 && (ch_data2 == "")
				 && (ch_data3 == "")
				 && (ch_data4 == "")
				 && (ch_data5 == ""))
			{
				if(iREAL_MODE < 0)		active_sts = true;
			}
		}

		if(active_sts)
		{
			if(iButton_Flag != 1)
			{
				iButton_Flag = 1;

				p_Button->SetTitle(sData__Title_1);
				p_Button->SetTextColor(cColor__Title_1);
				p_Button->SetReleasedColor(cColor__Background_1);

				draw_flag = 11;
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

				draw_flag = 12;
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
