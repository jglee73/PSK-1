#include "stdafx.h"
#include "JGLEE__STD_DATALOG.h"

#include "CObj__Log_List.h"
#include "CObj__Log_List__KEY_DEF.h"

#include "Dlg_Search_List.h"


extern void Macro__Get_List_From_String(const CString& str_data,CStringArray& l_data);


// ...
int  CObj__Log_List::
_Interface_Parameter()
{
	GObj__Parameter_Ctrl *p_para_ctrl = m_pGObj_Res->pGOBJ_PARA_CTRL;

	// ...
	{
		iPara_Flag__Group_Use = -1;
		sPara_List__Group_Item.RemoveAll();
	}

	// ...
	{
		CString key_name;
		CString def_data;

		//
		key_name = pKEY__DATA_CONFIG_PATH;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		mConfig_Path = def_data;

		key_name = pKEY__DATA_CONFIG_DIR;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		mConfig_Dir = def_data;

		key_name = pKEY__DATA_CONFIG_FILE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		mConfig_File = def_data;

		//
		key_name = pKEY__DATA_GROUP_USE;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		if(def_data.CompareNoCase("YES") == 0)		iPara_Flag__Group_Use = 1;

		key_name = pKEY__DATA_GROUP_LIST;
		p_para_ctrl->Get_Constant_Data(key_name, def_data);
		Macro__Get_List_From_String(def_data, sPara_List__Group_Item);
	}

	//----------------------------------------------------------------
	COLORREF fnc_color   = RGB(67,131,238);
	COLORREF press_color = RGB(37,101,188);
	COLORREF white_color = RGB(255,255,255);
	COLORREF black_color = RGB(0,0,0);

	mColor_Yellow = RGB(0,255,255);
	mColor_White  = RGB(255,255,255);

	//----------------------------------------------------------------
	POINT bttn_st, bttn_et;

	bttn_st.x = pST.x;
	bttn_st.y = pST.y;

	bttn_et.x = bttn_st.x + 100;
	bttn_et.y = bttn_st.y + 30;
	mI_BUTTON_Edit->SetTitle("EDIT");
	mI_BUTTON_Edit->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Edit->SetThick(1);
	mI_BUTTON_Edit->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Edit->SetReleasedColor(SPLL_BTN_FNC_COLOR);
	mI_BUTTON_Edit->SetPressedColor(press_color);
	mI_BUTTON_Edit->SetTextColor(white_color);

	bttn_st.x = bttn_et.x + 1;
	bttn_et.x = bttn_st.x + 100;
	mI_BUTTON_Undo->SetTitle("UNDO");
	mI_BUTTON_Undo->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Undo->SetThick(1);
	mI_BUTTON_Undo->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Undo->SetReleasedColor(SPLL_BTN_FNC_COLOR);
	mI_BUTTON_Undo->SetTextColor(white_color);

	bttn_st.x = bttn_et.x + 1;
	bttn_et.x = bttn_st.x + 100;
	mI_BUTTON_Save->SetTitle("SAVE");
	mI_BUTTON_Save->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Save->SetThick(1);
	mI_BUTTON_Save->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Save->SetReleasedColor(SPLL_BTN_FNC_COLOR);
	mI_BUTTON_Save->SetTextColor(white_color);

	bttn_st.x = bttn_et.x + 1;
	bttn_et.x = bttn_st.x + 100;
	mI_BUTTON_Search->SetTitle("SEARCH");
	mI_BUTTON_Search->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Search->SetThick(1);
	mI_BUTTON_Search->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Search->SetReleasedColor(SPLL_BTN_FNC_COLOR);
	mI_BUTTON_Search->SetTextColor(white_color);

	bttn_st.x = bttn_et.x + 1;
	bttn_et.x = bttn_st.x + 100;
	mI_BUTTON_Search_Box->SetTitle("Search Box");
	mI_BUTTON_Search_Box->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Search_Box->SetThick(1);	
	mI_BUTTON_Search_Box->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Search_Box->SetReleasedColor(SPLL_BTN_FNC_COLOR);
	mI_BUTTON_Search_Box->SetTextColor(white_color);

	bttn_st.x = pET.x - 244;
	bttn_et.x = bttn_st.x + 120;
	mI_BUTTON_Time->SetTitle("TIME (sec)");
	mI_BUTTON_Time->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Time->SetThick(1);
	mI_BUTTON_Time->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Time->SetReleasedColor(SPLL_BTN_FNC_COLOR);
	mI_BUTTON_Time->SetTextColor(white_color);

	bttn_st.x = bttn_et.x + 1;
	bttn_et.x = pET.x;
	mI_BUTTON_Time_String->SetTitle("1");
	mI_BUTTON_Time_String->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_Time_String->SetTextColor(RGB(255,255,255));
	mI_BUTTON_Time_String->SetThick(1);
	mI_BUTTON_Time_String->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_Time_String->SetReleasedColor(white_color);
	mI_BUTTON_Time_String->SetPressedColor(white_color);
	mI_BUTTON_Time_String->SetTextColor(black_color);
	mI_BUTTON_Time_String->SetUpColor(black_color);
	mI_BUTTON_Time_String->SetDownColor(black_color);

	Fnc_InActive();

	mI_BUTTON_Search->SetActive();
	mI_BUTTON_Search_Box->SetActive();
	return 1;
}

int CObj__Log_List::
_Interface_Show(HWND hwnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// ...
	{
		HDC hdc_front = m_pGObj_Res->hDC;
		HDC hdc_back  = m_pGObj_Res->hDC_BACK;
		HDC hdc_mem   = m_pGObj_Res->hDC_MEM;

		mI_BUTTON_Time_String->DrawPressed(hdc_front, hdc_back);
		Draw_Button(hdc_front, hdc_back);
	}

	if(iREAL_MODE > 0)
	{
		if(!bActive__Init_Table)
		{
			Init__Table(hwnd, false);
		}
	}
	else
	{
		Init__Table(hwnd, false);
	}
	
	if(pDlg_View != NULL)		pDlg_View->ShowWindow(SW_SHOW);
	return 1;
}
int  CObj__Log_List::_Interface_Hide()
{
	if(pDlg_View != NULL)
		pDlg_View->ShowWindow(SW_HIDE);

	return 1;
}

int  CObj__Log_List::
_WM_LButtonDown(const POINT& mouse_pt,
				const HWND& hwnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// ...
	HDC hdc_front = m_pGObj_Res->hDC;
	HDC hdc_back  = m_pGObj_Res->hDC_BACK;
	HDC hdc_mem   = m_pGObj_Res->hDC_MEM;

	// ...
	POINT pt = mouse_pt;

	if(mI_BUTTON_Edit->CheckArea(pt) > 0)
	{
		mI_BUTTON_Edit->DrawPressed(hdc_front, hdc_back);

		if(pDlg_View->iDATA_CHANGE_FLAG > 0)
		{
			CString msg;
			CString title;

			title = "EDIT CONFIRMATION";
			msg = "There is the data changed.\nPlease, convert edit mode after you save it.";

			MessageBox(NULL,
						msg,
						title,
						MB_OK|MB_TASKMODAL|MB_ICONERROR);
		}
		else
		{
			if(mEdit_Flag < 0)
			{
				Fnc_Active();
				Draw_Button(hdc_front, hdc_back);
			}
			else
			{
				Fnc_InActive();
				Draw_Button(hdc_front, hdc_back);
			}

			pDlg_View->iEDIT_MODE = mEdit_Flag;
			Sleep(100);
		}

		mI_BUTTON_Edit->DrawReleased(hdc_front, hdc_back);
		
		InvalidateRect(hwnd, NULL, FALSE);
		return 1;
	}

	if(mI_BUTTON_Undo->CheckArea(pt) > 0)
	{
		mI_BUTTON_Undo->DrawPressed(hdc_front, hdc_back);
		Sleep(100);
		mI_BUTTON_Undo->DrawReleased(hdc_front, hdc_back);

		if(Fnc_Undo() > 0)
		{
			pDlg_View->iEDIT_MODE = -1;

			Fnc_InActive();
			Draw_Button(hdc_front, hdc_back);
		}
		return 1;
	}

	if(mI_BUTTON_Save->CheckArea(pt) > 0)
	{
		mI_BUTTON_Save->DrawPressed(hdc_front, hdc_back);
		Sleep(100);
		mI_BUTTON_Save->DrawReleased(hdc_front, hdc_back);

		if(Fnc_Save() > 0)
		{
			pDlg_View->iDATA_CHANGE_FLAG = -1;
			pDlg_View->iEDIT_MODE = -1;

			Fnc_InActive();
			Draw_Button(hdc_front, hdc_back);
		}
		return 1;
	}

	if(mI_BUTTON_Search->CheckArea(pt) > 0)
	{
		mI_BUTTON_Search->DrawPressed(hdc_front, hdc_back);
		Sleep(100);
		mI_BUTTON_Search->DrawReleased(hdc_front, hdc_back);

		// ...
		CGX__UTILITY_CTRL cx_utility_ctrl;
		CString out_data;

		if(m_pStringPad->Popup("Input Channel-Name", "", out_data) == TRUE )
		{
			pDlg_View->Search_Item(out_data);
		}
		return 1;
	}
	if(mI_BUTTON_Search_Box->CheckArea(pt) > 0)
	{
		mI_BUTTON_Search_Box->DrawPressed(hdc_front, hdc_back);
		Sleep(100);
		mI_BUTTON_Search_Box->DrawReleased(hdc_front, hdc_back);

		// ...
		CGX__UTILITY_CTRL cx_utility_ctrl;
		CString out_data;

		if(m_pStringPad->Popup("Input Channel-Name", "", out_data) == TRUE )
		{
			CStringArray l_item;
			pDlg_View->Get_Search_Item(out_data,l_item);

			CDlg_Search_List dlg;
			dlg.sList_Item.Copy(l_item);

			if(dlg.DoModal() == IDOK)
			{						
				pDlg_View->Search_Item(dlg.sSel_Name);
			}
		}
		return 1;
	}

	if(mI_BUTTON_Time->CheckArea(pt) > 0)
	{
		mI_BUTTON_Time->DrawPressed(hdc_front, hdc_back);
		Sleep(100);
		mI_BUTTON_Time->DrawReleased(hdc_front, hdc_back);

		// ...
		CGX__UTILITY_CTRL cx_utility_ctrl;

		CString title = "Input Polling-Time";
		CString min = "0.1";
		CString max = "600";
		CString in_data;
		CString out_data;

		mI_BUTTON_Time_String->GetTitle(in_data);

		if(cx_utility_ctrl->Popup__ANALOG_PAD(title,min,max,in_data,out_data) > 0)
		{
			mI_BUTTON_Time_String->SetTitle(out_data);
			mI_BUTTON_Time_String->DrawPressed(hdc_front, hdc_back);

			InvalidateRect(hwnd, NULL, FALSE);
		}
		return 1;
	}

	return 1;
}

int  CObj__Log_List::
_WM_Timer(HWND hwnd)
{
	HDC hdc_front = m_pGObj_Res->hDC;
	HDC hdc_back  = m_pGObj_Res->hDC_BACK;
	HDC hdc_mem   = m_pGObj_Res->hDC_MEM;

	if(mEdit_Flag > 0)
	{
		if(mEdit_Blink > 0)
		{
			mEdit_Blink = -1;

			mI_BUTTON_Edit->SetTextColor(mColor_Yellow);
			mI_BUTTON_Edit->DrawPressed(hdc_front, hdc_back);
		}
		else
		{
			mEdit_Blink = 1;

			mI_BUTTON_Edit->SetTextColor(mColor_White);
			mI_BUTTON_Edit->DrawPressed(hdc_front, hdc_back);
		}
	}
	else if(mEdit_Flag == 0)
	{
		mEdit_Flag = -1;

		mI_BUTTON_Edit->SetTextColor(mColor_White);
		mI_BUTTON_Edit->DrawReleased(hdc_front, hdc_back);
	}

	return 1;
}
