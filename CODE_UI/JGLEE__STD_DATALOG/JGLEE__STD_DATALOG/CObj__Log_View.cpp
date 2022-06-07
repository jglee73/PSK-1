#include "stdafx.h"

#include "JGLEE__STD_DATALOG.h"

#include "CObj__Log_View.h"
#include "CObj__Log_View__KEY_DEF.h"

#include "Dlg__Log_Dir_Copy.h"


extern int Macro__Get_File_Data(const CString& file_path, CString& file_data);


// ...
CObj__Log_View::CObj__Log_View()
{
	// ...
	{
		iINIT_FLAG = -1;
		iFlag__Remote_Disk = -1;
	}

	// ...
	mI_Draw = New_DRAW();
	mI_Program = New_PROGRAM_CONTROL();

	mI_BUTTON_Undo   = New_BUTTON();
	mI_BUTTON_Save   = New_BUTTON();
	mI_BUTTON_SaveAs = New_BUTTON();
	mI_BUTTON_Clear  = New_BUTTON();

	mI_BUTTON_Date        = New_BUTTON();
	mI_BUTTON_Date_String = New_BUTTON();

	mI_BUTTON_View        = New_BUTTON();
	mI_BUTTON_View_String = New_BUTTON();

	mI_BUTTON_Search_String = New_BUTTON();
	mI_BUTTON_Search= New_BUTTON();

	mI_BUTTON_Log_View       = New_BUTTON();
	mI_BUTTON_Log_Graph_New  = New_BUTTON();

	mI_BUTTON_Log_Conversion  = New_BUTTON();
	mI_BUTTON_Log_File_BackUp = New_BUTTON();

	mI_BUTTON_Log_File_Reload = New_BUTTON();
	
	mI_BUTTON_ADD = New_BUTTON();
	mI_BUTTON_SUB = New_BUTTON();


	mWColor = RGB(255,255,255);
	mBColor = RGB(0,0,0);
	mTitle = "T";

	mPColor = RGB(255,255,255);
	mRColor = RGB(150,150,150);

	mFontName = "Arial";  // "FixedSys";
	mTWidth   = 6;        // 7;
	mTHeight  = 15;       // 19;

	mModule_Index_Pre = -1;

	m_ChMIN = TRUE;
	m_ChMAX = TRUE;
	m_ChAVG = TRUE;
	
	m_TableDlg = NULL;
	m_ViewDlg = NULL;

	//
	bActive__Page_Show = false;
}

CObj__Log_View::~CObj__Log_View()
{
	if(m_TableDlg != NULL)
	{
		delete m_TableDlg;
		m_TableDlg = NULL;
	}
	if(m_ViewDlg != NULL)
	{
		delete m_ViewDlg;
		m_ViewDlg = NULL;
	}
}

void CObj__Log_View ::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString key_name;

	// ...
	{
		key_name = pKEY__MODULE_INDEX;
		p_obj_para_def->Register_Command(key_name, "ListBox", "0 1 2 3 4 5 6 7 8", "0");

		key_name = pKEY__REMOTE_DISK;
		p_obj_para_def->Register_Command(key_name, "ListBox", "NO YES", "NO");

		key_name = pKEY__SHOW_LOG_GRAPH;
		p_obj_para_def->Register_Command(key_name, "ListBox", "NO YES", "NO");
	}
}
	
void CObj__Log_View::
Set_Parameter(const int& module_id,
			  const POINT& st,
			  const POINT& et,
			  const HWND& hwnd,
			  GObj__Resource_Info *p_obj_res)
{
	// ...
	COLORREF fnc_color   = RGB(67,131,238);
	COLORREF white_color = RGB(255,255,255);
	COLORREF black_color = RGB(0,0,0);


	// ...
	{
		iMODULE_ID = module_id;
		pST = st;
		pET = et;

		m_pGObj_Res = p_obj_res;
		mModule_Index = 0;

		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();
	}

	// ...
	CString data;

	m_pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__MODULE_INDEX,data);	
	if(data.CompareNoCase("") != 0)				mModule_Index = atoi(data);

	m_pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__REMOTE_DISK,data);
	if(data.CompareNoCase("YES") == 0)			iFlag__Remote_Disk =  1;
	else										iFlag__Remote_Disk = -1;

	m_pGObj_Res->pGOBJ_PARA_CTRL->Get_Constant_Data(pKEY__SHOW_LOG_GRAPH, data);
	if(data.CompareNoCase("YES") == 0)			bActive__Log_Graph = true;
	else										bActive__Log_Graph = false;

	if(mModule_Index > 0)
	{
		mExt.Format("d%1d_inf", mModule_Index);
		mFile_Ext.Format("d%1d",mModule_Index);
	}
	else
	{
		mExt = "d_inf";
		mFile_Ext = "d";
	}

	// ...
	POINT bttn_st, bttn_et;

	bttn_st.x = pST.x;
	bttn_st.y = pST.y;

	bttn_st.x = (pST.x + pET.x) / 2 - 60;
	bttn_st.y = (pST.y + pET.y) / 2 - 20;
	bttn_et.x = (pST.x + pET.x) / 2 + 60;
	bttn_et.y = bttn_st.y + 40;
	// mI_BUTTON_ADD->SetTitle("▶ ▶ ▶");
	mI_BUTTON_ADD->SetTitle("ADD  >>");
	mI_BUTTON_ADD->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_ADD->SetThick(1);
	mI_BUTTON_ADD->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_ADD->SetTextColor(white_color);		//BLUE
	mI_BUTTON_ADD->SetReleasedColor(SPLS_BTN_LIGHT_COLOR);	//


	bttn_st.y = bttn_et.y + 5;
	bttn_et.y = bttn_st.y + 40;
	// mI_BUTTON_SUB->SetTitle("◀ ◀ ◀");
	mI_BUTTON_SUB->SetTitle("<<  DEL");
	mI_BUTTON_SUB->SetFont(mFontName,mTWidth,mTHeight);
	mI_BUTTON_SUB->SetThick(1);
	mI_BUTTON_SUB->SetPosition(bttn_st,bttn_et);
	mI_BUTTON_SUB->SetTextColor(white_color);		//ORANGE
	mI_BUTTON_SUB->SetReleasedColor(SPLS_BTN_LIGHT_COLOR);	//

	// ...
	POINT table_st, table_et;
	POINT view_st,  view_et;

	table_st.x = pST.x;
	table_st.y = pST.y + 35;//80;
	table_et.x = pST.x + 2 * (pET.x - pST.x) / 5;
	table_et.y = pET.y - 35;

	view_st.x = pET.x - 2 * (pET.x - pST.x) / 5;
	view_st.y = pST.y + 35;//80;
	view_et.x = pET.x;
	view_et.y = pET.y - 35;

	// ...
	{
		bttn_st.x = pST.x;
		bttn_st.y = pST.y;
		bttn_et.x = bttn_st.x + 100;
		bttn_et.y = bttn_st.y + 30;
	
		mI_BUTTON_Date->SetTitle("Log-Date");
		mI_BUTTON_Date->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_Date->SetThick(1);
		mI_BUTTON_Date->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Date->SetTextColor(white_color);
		mI_BUTTON_Date->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = bttn_et.x + 1;
		bttn_et.x = view_st.x - 10;
	
		mI_BUTTON_Date_String->SetTitle("");
		mI_BUTTON_Date_String->SetFont(mFontName,mTWidth,mTHeight);
		
		mI_BUTTON_Date_String->SetThick(1);
		mI_BUTTON_Date_String->SetPosition(bttn_st,bttn_et);	
		mI_BUTTON_Date_String->SetTextColor(white_color);
		mI_BUTTON_Date_String->SetPressedColor(SPLS_BTN_PRESS_COLOR);
		mI_BUTTON_Date_String->SetUpColor(black_color);
		mI_BUTTON_Date_String->SetDownColor(black_color);
	}

	// ...
	{
		bttn_st.x = view_st.x;
		bttn_et.x = bttn_st.x + 100;

		mI_BUTTON_View->SetTitle("View-File");
		mI_BUTTON_View->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_View->SetThick(1);
		mI_BUTTON_View->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_View->SetTextColor(white_color);
		mI_BUTTON_View->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = bttn_et.x + 1;
		bttn_et.x = view_et.x - 1;
	
		mI_BUTTON_View_String->SetTitle("");
		mI_BUTTON_View_String->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_View_String->SetThick(1);
		mI_BUTTON_View_String->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_View_String->SetTextColor(white_color);
		mI_BUTTON_View_String->SetPressedColor(SPLS_BTN_PRESS_COLOR);
		mI_BUTTON_View_String->SetUpColor(black_color);
		mI_BUTTON_View_String->SetDownColor(black_color);
	}

	// ...
	{
		bttn_st.x = table_st.x;
		bttn_et.x = table_et.x - 100;		
		bttn_st.y = table_et.y + 5;
		bttn_et.y = et.y;
	
		mI_BUTTON_Search_String->SetTitle("Input keyword for Searching in the item");
		mI_BUTTON_Search_String->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_Search_String->SetThick(1);
		mI_BUTTON_Search_String->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Search_String->SetTextColor(white_color);
		mI_BUTTON_Search_String->SetPressedColor(SPLS_BTN_PRESS_COLOR);
		mI_BUTTON_Search_String->SetUpColor(black_color);
		mI_BUTTON_Search_String->SetDownColor(black_color);
	}

	// ...
	{	
		bttn_st.x = table_et.x - 100;
		bttn_et.x = table_et.x;
	
		mI_BUTTON_Search->SetTitle("Search");
		mI_BUTTON_Search->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_Search->SetThick(1);
		mI_BUTTON_Search->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Search->SetTextColor(white_color);
		mI_BUTTON_Search->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = view_st.x;
		bttn_et.x = bttn_st.x + 80;
	
		mI_BUTTON_Undo->SetTitle("Undo");
		mI_BUTTON_Undo->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_Undo->SetThick(1);
		mI_BUTTON_Undo->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Undo->SetTextColor(white_color);
		mI_BUTTON_Undo->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = bttn_et.x + 5;
		bttn_et.x = bttn_st.x + 80;
	
		mI_BUTTON_Save->SetTitle("Save");
		mI_BUTTON_Save->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_Save->SetThick(1);
		mI_BUTTON_Save->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Save->SetTextColor(white_color);
		mI_BUTTON_Save->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = bttn_et.x + 5;
		bttn_et.x = bttn_st.x + 80;
	
		mI_BUTTON_SaveAs->SetTitle("SaveAs");
		mI_BUTTON_SaveAs->SetFont(mFontName,mTWidth,mTHeight);
		mI_BUTTON_SaveAs->SetThick(1);
		mI_BUTTON_SaveAs->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_SaveAs->SetTextColor(white_color);
		mI_BUTTON_SaveAs->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = pET.x - 80;
		bttn_et.x = pET.x;
	
		mI_BUTTON_Clear->SetTitle("Clear");
		mI_BUTTON_Clear->SetFont(mFontName,mTWidth,mTHeight);
	
		mI_BUTTON_Clear->SetThick(1);
		mI_BUTTON_Clear->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Clear->SetTextColor(white_color);
		mI_BUTTON_Clear->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.x = table_et.x + 10;
		bttn_st.y = table_st.y + 5;
		bttn_et.x = view_st.x - 10;
		bttn_et.y = bttn_st.y + 45;
		
		mI_BUTTON_Log_View->SetTitle("LOG-VIEW");
		mI_BUTTON_Log_View->SetFont(mFontName,mTWidth,mTHeight);

		mI_BUTTON_Log_View->SetThick(1);
		mI_BUTTON_Log_View->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Log_View->SetTextColor(white_color);
		mI_BUTTON_Log_View->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	if(bActive__Log_Graph)
	{
		bttn_st.y = bttn_et.y + 5;
		bttn_et.y = bttn_st.y + 45;

		mI_BUTTON_Log_Graph_New->SetTitle("LOG-GRAPH");
		mI_BUTTON_Log_Graph_New->SetFont(mFontName,mTWidth,mTHeight);

		mI_BUTTON_Log_Graph_New->SetThick(1);
		mI_BUTTON_Log_Graph_New->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Log_Graph_New->SetTextColor(white_color);
		mI_BUTTON_Log_Graph_New->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.y = bttn_et.y + 15;
		bttn_et.y = bttn_st.y + 45;
		
		mI_BUTTON_Log_Conversion->SetTitle("LOG-CONVERSION");
		mI_BUTTON_Log_Conversion->SetFont(mFontName,mTWidth,mTHeight);

		mI_BUTTON_Log_Conversion->SetThick(1);
		mI_BUTTON_Log_Conversion->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Log_Conversion->SetTextColor(white_color);
		mI_BUTTON_Log_Conversion->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		bttn_st.y = bttn_et.y + 5;
		bttn_et.y = bttn_st.y + 45;
		
		mI_BUTTON_Log_File_BackUp->SetTitle("LOG FILE-BACKUP");
		mI_BUTTON_Log_File_BackUp->SetFont(mFontName,mTWidth,mTHeight);

		mI_BUTTON_Log_File_BackUp->SetThick(1);
		mI_BUTTON_Log_File_BackUp->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Log_File_BackUp->SetTextColor(white_color);
		mI_BUTTON_Log_File_BackUp->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}

	// ...
	{
		mI_BUTTON_Log_File_Reload = New_BUTTON();

		bttn_st.y = bttn_et.y + 15;
		bttn_et.y = bttn_st.y + 45;
		
		mI_BUTTON_Log_File_Reload->SetTitle("LOG FILE-RELOAD");
		mI_BUTTON_Log_File_Reload->SetFont(mFontName,mTWidth,mTHeight);

		mI_BUTTON_Log_File_Reload->SetThick(1);
		mI_BUTTON_Log_File_Reload->SetPosition(bttn_st,bttn_et);
		mI_BUTTON_Log_File_Reload->SetTextColor(white_color);
		mI_BUTTON_Log_File_Reload->SetReleasedColor(SPLV_BTN_FNC_COLOR);
	}
	
	// ...
	{
		table_pt[0] = (int) table_st.x;
		table_pt[1] = (int) table_st.y;
		table_pt[2] = (int) table_et.x - table_pt[0];
		table_pt[3] = (int) table_et.y - table_pt[1];
		
		view_pt[0] = (int) view_st.x;
		view_pt[1] = (int) view_st.y;
		view_pt[2] = (int) view_et.x - view_pt[0];
		view_pt[3] = (int) view_et.y - view_pt[1];
	}

	mModule_Index_Pre = mModule_Index;

	// ...
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		HDC hdc      = m_pGObj_Res->hDC;
		HDC hdc_back = m_pGObj_Res->hDC_BACK;
		HDC hdc_mem  = m_pGObj_Res->hDC_MEM;
		
		if(m_TableDlg == NULL)
		{			
			m_TableDlg = new DataTableDlg((CWnd*)this);//CWnd::FromHandle(hwnd));
			m_TableDlg->Create(IDD_DIALOG1, CWnd::FromHandle(hwnd));
				
			Init_Table();
			
			m_TableDlg->MoveWindow(table_pt[0], table_pt[1],table_pt[2], table_pt[3],TRUE);	
			m_TableDlg->ShowWindow(SW_SHOW);
			m_TableDlg->Interface_Show();
		}
		if(m_ViewDlg == NULL)
		{
			m_ViewDlg = new DataTableDlg((CWnd*)this);//CWnd::FromHandle(hwnd));
			m_ViewDlg->Create(IDD_DIALOG1, CWnd::FromHandle(hwnd));	
				
			Init_View();
			
			m_ViewDlg->MoveWindow(view_pt[0], view_pt[1],view_pt[2], view_pt[3],TRUE);	
			m_ViewDlg->ShowWindow(SW_SHOW);
			m_ViewDlg->Interface_Show();
		}
	}

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		CString str_dir;

		x_sys_ctrl->Get__SEQ_DIR_DATALOG(iMODULE_ID, str_dir);		
		sDir_Root = str_dir;

		//
		CString dir__ui_root;
		x_sys_ctrl->Get__GUI_DIR_EXE(dir__ui_root);

		sDir__Temp_Log  = dir__ui_root;
		sDir__Temp_Log += "\\_TEMP_LOG";

		sPath__Log_Viewer_Inf.Format("%s\\%s", sDir__Temp_Log,"LogViewer.inf");
		sPath__Log_Viewer_Txt.Format("%s\\%s", sDir__Temp_Log,"LogViewer.txt");

		sPath__Graph_Log.Format("%s\\%s", sDir__Temp_Log,"ChartView.csv");
		sPath__Log_Conversion.Format("%s\\%s", sDir__Temp_Log,"UltraFileConversion.inf");
	}	
}

void CObj__Log_View ::Show_GObj(const HWND& hwnd)
{	
	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// ...
	HDC hdc      = m_pGObj_Res->hDC;
	HDC hdc_back = m_pGObj_Res->hDC_BACK;
	HDC hdc_mem  = m_pGObj_Res->hDC_MEM;

	// ...
	{
		mI_BUTTON_Undo->DrawReleased(hdc,hdc_back);
		mI_BUTTON_Save->DrawReleased(hdc,hdc_back);
		mI_BUTTON_SaveAs->DrawReleased(hdc,hdc_back);
		mI_BUTTON_Clear->DrawReleased(hdc,hdc_back);

		mI_BUTTON_Date->DrawReleased(hdc,hdc_back);
		mI_BUTTON_Date_String->DrawPressed(hdc,hdc_back);

		mI_BUTTON_View->DrawReleased(hdc,hdc_back);
		mI_BUTTON_View_String->DrawPressed(hdc,hdc_back);

		mI_BUTTON_Log_View->DrawReleased(hdc,hdc_back);
		
		if(bActive__Log_Graph)
		{
			mI_BUTTON_Log_Graph_New->DrawReleased(hdc,hdc_back);
		}

		mI_BUTTON_Log_Conversion->DrawReleased(hdc,hdc_back);
		mI_BUTTON_Log_File_BackUp->DrawReleased(hdc,hdc_back);

		mI_BUTTON_Log_File_Reload->DrawReleased(hdc,hdc_back);
	
		mI_BUTTON_ADD->DrawReleased(hdc,hdc_back);
		mI_BUTTON_SUB->DrawReleased(hdc,hdc_back);
		mI_BUTTON_Search_String->DrawPressed(hdc,hdc_back);
		mI_BUTTON_Search->DrawReleased(hdc,hdc_back);
	}

	bActive__Page_Show = true;
}
void CObj__Log_View ::Hide_GObj()
{
	bActive__Page_Show = false;
}

void CObj__Log_View ::WM_Paint(const HWND& hwnd)
{

}
void CObj__Log_View ::WM_Timer(const HWND& hwnd)
{
	if(iREAL_MODE < 0)			return;

	if(bActive__Page_Show)
	{
		if(iINIT_FLAG < 0)
		{
			iINIT_FLAG = 1;

			AFX_MANAGE_STATE(AfxGetStaticModuleState());

			Undo_Table(hwnd);
		}
	}
}
void CObj__Log_View ::WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	AFX_MANAGE_STATE(AfxGetStaticModuleState());
	
	//-------------------------------------------------------------------------
	POINT pt = mouse_pt;

	HDC hdc      = m_pGObj_Res->hDC;
	HDC hdc_back = m_pGObj_Res->hDC_BACK;
	HDC hdc_mem  = m_pGObj_Res->hDC_MEM;


	if(mI_BUTTON_Undo->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Undo->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Undo->DrawReleased(hdc,hdc_back);
		}

		Undo_View(hwnd,hdc,hdc_back);
		return;
	}
	if(mI_BUTTON_Save->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Save->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Save->DrawReleased(hdc,hdc_back);
		}

		if(Save_View(hdc,hdc_back) > 0)
		{
			InvalidateRect(hwnd,NULL,FALSE);
		}
		return;
	}
	if(mI_BUTTON_SaveAs->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_SaveAs->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_SaveAs->DrawReleased(hdc,hdc_back);
		}

		if(SaveAs_View(hdc,hdc_back) > 0)
		{
			InvalidateRect(hwnd,NULL,FALSE);
		}
		return;
	}
	if(mI_BUTTON_Clear->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Clear->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Clear->DrawReleased(hdc,hdc_back);
		}

		Clear_Item(hdc,hdc_back);
		return;
	}

	if(mI_BUTTON_ADD->CheckArea(pt)>0)
	{
		// ...
		{
			mI_BUTTON_ADD->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_ADD->DrawReleased(hdc,hdc_back);
		}
		
		Add_Item(hdc,hdc_back);
		return;
	}
	if(mI_BUTTON_SUB->CheckArea(pt)>0)
	{
		// ...
		{
			mI_BUTTON_ADD->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_ADD->DrawReleased(hdc,hdc_back);
		}

		Subtract_Item(hdc,hdc_back);
		return;
	}

	if(mI_BUTTON_Date->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Date->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Date->DrawReleased(hdc,hdc_back);
		}

		if(Log_Date_Table(hdc,hdc_back) > 0)
		{
			InvalidateRect(hwnd,NULL,FALSE);
		}
		return;
	}

	if(mI_BUTTON_View->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_View->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_View->DrawReleased(hdc,hdc_back);
		}

		if(File_View(hwnd,hdc,hdc_back) > 0)
		{
			InvalidateRect(hwnd,NULL,FALSE);
		}
		return;
	}

	if(mI_BUTTON_Log_View->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Log_View->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Log_View->DrawReleased(hdc,hdc_back);
		}

		// ...
		CString log_file;
		CString table_file;

		mI_BUTTON_Date_String->GetTitle(log_file);
		mI_BUTTON_View_String->GetTitle(table_file);

		if(log_file.GetLength() < 1)
		{
			CString msg, title;

			title = "LOG-VIEW OPEN : ERROR";
			msg   = "You must select the log-data.";

			MessageBox(hwnd,msg,title,MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
			return;
		}
		else if(table_file.GetLength() < 1)
		{
			CString msg, title;

			title = "LOG-VIEW OPEN : ERROR";
			msg   = "You must select the view-file.";

			MessageBox(hwnd,msg,title,MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
			return;
		}

		// ...
		{
			CString file_data;
			
			if(Read_File_from_SEQ(hwnd,iMODULE_ID,log_file,mFile_Ext,file_data) > 0)
			{
				Make_Log_File(log_file,table_file,file_data);
				// Make_CSVLog_File(log_file,table_file,file_data);
			}
		}

		// ...
		{
			CGX__SYSTEM_CTRL cx_sys_ctrl;
			
			CString dir_exe;
			cx_sys_ctrl->Get__GUI_DIR_EXE(dir_exe);

			mI_Program->Start_Program(dir_exe, "JGLEE__Process_Log_View");
		}

		return;
	}

	// ...
	int graph_flag = -1;

	if(bActive__Log_Graph)
	{
		if(mI_BUTTON_Log_Graph_New->CheckArea(pt) > 0)
		{
			graph_flag = 2;
		}
	}

	if(graph_flag > 0)
	{
		if(bActive__Log_Graph)
		{
			if(graph_flag == 2)
			{
				mI_BUTTON_Log_Graph_New->DrawPressed(hdc,hdc_back);
			}
		}

		if(Fnc__Log_Graph_View(hwnd,hdc,hdc_back) > 0)
		{
			CGX__SYSTEM_CTRL cx_sys_ctrl;
			CString dir_exe;
			CString file_info;

			cx_sys_ctrl->Get__GUI_DIR_EXE(dir_exe);
			dir_exe += "\\UTILITY_EXE";

			// ...
			CString log_file;
			CString table_file;
			
			mI_BUTTON_Date_String->GetTitle(log_file);
			mI_BUTTON_View_String->GetTitle(table_file);

			file_info.Format("%s/%s", log_file,table_file);
		
			if(graph_flag == 2)
			{
				mI_Program->Start_Program_Ex(dir_exe,
											 "DataLog_Chart",
											 sPath__Graph_Log,
											 file_info);
			}
		}
		else
		{
			Sleep(300);	
		}

		if(bActive__Log_Graph)
		{
			if(graph_flag == 2)
			{
				mI_BUTTON_Log_Graph_New->DrawReleased(hdc,hdc_back);
			}
		}
		return;
	}
	
	if(mI_BUTTON_Log_Conversion->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Log_Conversion->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Log_Conversion->DrawReleased(hdc,hdc_back);
		}

		// ...
		CString dir;
		CString table;

		mI_BUTTON_View_String->GetTitle(table);

		if(table.GetLength() < 1)
		{
			CString msg, title;

			title = "LOG-CONVERSION : ERROR";
			msg   = "You must select the view-file.";

			MessageBox(NULL,msg,title,MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
			return;
		}

		// ...
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());

			// ...
			CUltraFileConversionDlg dlg_conversion;

			dlg_conversion.m_Seq_ModuleID = iMODULE_ID;
			dlg_conversion.m_Dir_ModuleID_From_Out = mModule_Index;

			Fnc_FileConversion(iMODULE_ID, mFile_Ext);

			dlg_conversion.sPath__Log_Conversion = sPath__Log_Conversion;

			dlg_conversion.DoModal();
		}
		return;
	}

	if(mI_BUTTON_Log_File_BackUp->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Log_File_BackUp->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Log_File_BackUp->DrawReleased(hdc,hdc_back);
		}

		// ...
		{
			AFX_MANAGE_STATE(AfxGetStaticModuleState());
			
			// ...
			CDlg__Log_Dir_Copy dlg;

			dlg.iModuleID = iMODULE_ID;
			
			if(dlg.DoModal() == IDOK)
			{

			}
		}
		
		return;
	}

	if(mI_BUTTON_Log_File_Reload->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Log_File_Reload->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Log_File_Reload->DrawReleased(hdc,hdc_back);
		}
		
		Undo_Table(hwnd);
		return;
	}

	// ...
	if(mI_BUTTON_Search_String->CheckArea(pt) > 0)
	{
		if(Search_String(hdc,hdc_back) > 0)
		{
			InvalidateRect(hwnd,NULL,FALSE);
		}
		return;
	}

	if(mI_BUTTON_Search->CheckArea(pt) > 0)
	{
		// ...
		{
			mI_BUTTON_Search->DrawPressed(hdc,hdc_back);
			Sleep(100);
			mI_BUTTON_Search->DrawReleased(hdc,hdc_back);
		}

		if(Search_View(hwnd) > 0)
		{

		}
		return;
	}
}
int  CObj__Log_View::
Fnc__Log_Graph_View(const HWND& hwnd,
					const HDC& hdc,
					const HDC& hdc_back)
{
	CString log_file;
	CString table_file;
	
	mI_BUTTON_Date_String->GetTitle(log_file);
	mI_BUTTON_View_String->GetTitle(table_file);
	
	if(log_file.GetLength() < 1)
	{
		CString msg, title;
		
		title = "LOG-GRAPH OPEN : ERROR";
		msg   = "You must select the log-data.";
		
		MessageBox(hwnd,msg,title,MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
		return -1;
	}
	else if(table_file.GetLength() < 1)
	{
		CString msg, title;
		
		title = "LOG-GRAPH OPEN : ERROR";
		msg   = "You must select the view-file.";
		
		MessageBox(hwnd,msg,title,MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
		return -1;
	}
	
	// ...
	{
		CString file_data;

		int flag = Read_File_from_SEQ(hwnd,iMODULE_ID,log_file,mFile_Ext,file_data);

		if(flag > 0)
		{
			Make_ViewCSV_File(log_file,table_file,file_data);
		}
		else
		{
			return -1;
		}
	}

	return 1;
}

int  CObj__Log_View::Init_Table()
{
	LV_COLUMN lvcolumn;
	//int col_cnt = 5;
	
	char *listcolumn[5] = {"No.", "Title", "Type", "Channel", "Ch_Type"};
	int width[5] = {40,200,80,200,60};

	m_TableDlg->m_ListView.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//|LVS_SHOWSELALWAYS ); 
	
	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_CENTER;

	for(int col = 0; col<5; col++)
	{
		lvcolumn.pszText = listcolumn[col];
		lvcolumn.iSubItem = col;
		lvcolumn.cx = width[col];

		m_TableDlg->m_ListView.InsertColumn(col,&lvcolumn);	
	}

	//  [9/13/2013 Won]  delete
// 	CFont *font = new CFont;
// 	font->CreateFont(mTHeight+3,mTWidth+1,0,0,1,0,0,0,0,0,0,1,0,mFontName);
// 	m_TableDlg->m_ListView.SetFont(font,TRUE);
// 	delete font;

	return 1;

}
int  CObj__Log_View::Init_View()
{
	LV_COLUMN lvcolumn;
	
	char *listcolumn[5] = {"No.", "Title", "Type", "Channel", "Ch_Type"};
	int width[5] = {40,200,80,200,60};

	m_ViewDlg->m_ListView.SetExtendedStyle(LVS_EX_GRIDLINES | LVS_EX_FULLROWSELECT);//|LVS_SHOWSELALWAYS|LVS_SINGLESEL ); 

	lvcolumn.mask = LVCF_FMT | LVCF_SUBITEM | LVCF_TEXT | LVCF_WIDTH;
	lvcolumn.fmt = LVCFMT_CENTER;
	
	for(int col = 0; col<5; col++)
	{
		lvcolumn.pszText = listcolumn[col];
		lvcolumn.iSubItem = col;
		lvcolumn.cx = width[col];

		m_ViewDlg->m_ListView.InsertColumn(col,&lvcolumn);	
	}

	//  [9/13/2013 Won]  delete
// 	CFont *font = new CFont;
// 	font->CreateFont(mTHeight+3,mTWidth+1,0,0,1,0,0,0,0,0,0,1,0,mFontName);
// 	m_ViewDlg->m_ListView.SetFont(font,TRUE);
// 	delete font;

	return 1;
}

int  CObj__Log_View::Undo_Table(const HWND& hwnd)
{
	if(iREAL_MODE < 0)
	{
		return -1;
	}

	if(m_TableDlg == NULL)
	{
		return -2;
	}

	// ...
	CString file_data;

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		
		CString dir_log;
		CString dir_root;
		
		x_sys_ctrl->Get__SEQ_DIR_ROOT(iMODULE_ID, dir_root);

		dir_log  = dir_root;
		dir_log += "\\EQP_LOG";
		dir_log += "\\datalog";

		CString log_path;
		log_path.Format("%s\\%s", dir_log, "channel_list.csv");

		if(Macro__Get_File_Data(log_path, file_data) < 0)
		{	
			printf(" * CObj__Log_View::Undo_Table() - Error ! \n");
			printf(" ** log_path <- [%s] \n", log_path);
			return -11;
		}

		file_data += (char) EOF;
	}

	//-------------------------------------
	CStringArray list_channel;
	CStringArray list_type;
	CStringArray list_title;
	CStringArray list_mode;
	CStringArray list_index;
	CStringArray list_chtype;

	// ...
	{
		CString word;
		int para;
		
		int flag  =  1;

		int limit = file_data.GetLength();

		for(int i=0; i<limit; i++)
		{
			char ch = file_data.GetAt(i);

			if((ch == ',')
			|| (ch == '\n')
			|| (ch == EOF))
			{
				if(ch == ',')
				{
					para++;
				}

				if(word.GetLength() > 0)
				{
					if(para == 1)			// Channel
					{
						list_channel.Add(word);
						list_type.Add("");
						list_title.Add("");
						list_mode.Add("");
						list_index.Add("");
						list_chtype.Add("");
					}
					else if(para == 2)		// Type
					{
						int index = list_type.GetSize() - 1;

						if(index >= 0)	list_type[index] = word;
					}
					else if(para == 3)		// Title
					{
						int index = list_title.GetSize() - 1;

						if(index >= 0)	list_title[index] = word;
					}
					else if(para == 4)		// Mode
					{
						int index = list_mode.GetSize() - 1;

						if(index >= 0)	list_mode[index] = word;
					}
					else if(para == 5)		// Index
					{
						int index = list_index.GetSize() - 1;

						if(index >= 0)	list_index[index] = word;
					}
					else if(para == 6)
					{
						int index = list_chtype.GetSize() - 1;

						if(index >= 0)	list_chtype[index] = word;
					}

					word = "";
				}

				// ...
			}
			else
			{
				word += ch;
			}

			if(ch == '\n')
			{
				para = 0;
			}
			else if(ch == EOF)
			{
				flag = -1;
			}
		}	
	}

	//-------------------------------------
	{
		CString data;

		int column = 5;
		int count = 0;
			
		m_TableDlg->m_ListView.DeleteAllItems();
		m_TableDlg->m_ListView.SetRedraw(false);

		// ...	
		LV_ITEM lvitem;
		lvitem.mask = LVIF_TEXT;

		// ...
		int list_row = 0;

		int limit = list_channel.GetSize();

		for(int i=0; i<limit; i++)
		{
			if((strcmp(list_mode[i], "ENABLE") == 0)
			&& (atoi(list_index[i]) == mModule_Index))
			{
				for(int j=0; j<column; j++)
				{
					lvitem.iSubItem = j;
					
					if(j==0)
					{
						
						data.Format("%002d",count+1);
						lvitem.iItem = list_row;
						lvitem.pszText = LPSTR(LPCTSTR(data));
						m_TableDlg->m_ListView.InsertItem(&lvitem);
						//mI_Table->mDB[j][count] = data;
						list_row++;
					}
					else
					{
						//lvitem.iSubItem =j;
						if(j==1)	
						{
							if(list_title[i].GetLength() > 0)
								lvitem.pszText = LPSTR(LPCTSTR(list_title[i]));
							else
								lvitem.pszText = LPSTR(LPCTSTR(list_channel[i]));
						}
						else if(j==2)	lvitem.pszText = LPSTR(LPCTSTR(list_type[i]));
						else if(j==3)	lvitem.pszText = LPSTR(LPCTSTR(list_channel[i]));
						else if(j==4)	lvitem.pszText = LPSTR(LPCTSTR(list_chtype[i]));
						
						m_TableDlg->m_ListView.SetItem(&lvitem);

					}
				}

				count++;
			}
		}

		m_TableDlg->m_ListView.SetRedraw(true);
		m_TableDlg->Interface_Show();
	}
	
	return 1;
}

int  CObj__Log_View::Add_Item(const HDC& hdc,
							  const HDC& hdc_back)
{
	int index_cnt = m_TableDlg->m_ListView.GetSelectedCount();
	POSITION pos = m_TableDlg->m_ListView.GetFirstSelectedItemPosition();
	int index = m_TableDlg->m_ListView.GetNextSelectedItem(pos);

	// ...
	LV_ITEM lvitem;
	
	if(index < 0)	
	{
		MessageBox(NULL,
				   "Please, select the item to be appended.",
				   "ITEM ADDITION ERROR",
				   MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
		return -1;
	}

	// ...
	CString data, title, type, channel,chtype;
	int i, column;

	column = 5;	
		
	for(i=0;i<column;i++)
	{
			 if(i==1)		title = m_TableDlg->m_ListView.GetItemText(index,i);
		else if(i==2)		type = m_TableDlg->m_ListView.GetItemText(index,i);
		else if(i==3)		channel = m_TableDlg->m_ListView.GetItemText(index,i);
		else if(i==4)		chtype  = m_TableDlg->m_ListView.GetItemText(index,i);
	}

	index = m_ViewDlg->m_ListView.GetItemCount();

	for(i=0;i<index;i++)
	{
		if(m_ViewDlg->m_ListView.GetItemText(i,3) == channel)
		{
			CString msg;
			msg.Format("Already, there is any item for you to want to append the item (%s).",channel);

			MessageBox(NULL,
					   msg,
					   "ITEM ADDITION ERROR",
					   MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
			return -1;
		}
	}

	for(i=0;i<column;i++)
	{
		if(i==0)
		{
			data.Format("%002d",index);
			lvitem.mask = LVIF_TEXT ;
			//	lvitem.iImage =1;
			lvitem.iItem = index;
			lvitem.iSubItem =i;
			lvitem.pszText = LPSTR(LPCTSTR(data));
			m_ViewDlg->m_ListView.InsertItem(&lvitem);
		}
		else if(i==1)
		{
			//	data = title;
			lvitem.iSubItem =i;
			lvitem.pszText = LPSTR(LPCTSTR(title));
			m_ViewDlg->m_ListView.SetItem(&lvitem);
		}
		else if(i==2)
		{
			lvitem.iSubItem =i;
			lvitem.pszText = LPSTR(LPCTSTR(type));
			m_ViewDlg->m_ListView.SetItem(&lvitem);

			if(strcmp(type,"EVENT") == 0)
			{
				mTable_Event_Item.Add(channel);
				mTable_Event_Title.Add(title);
			}
			else
			{
				mTable_Interval_Item.Add(channel);
				mTable_Interval_Title.Add(title);
			}
		}
		else if(i==3)
		{
			lvitem.iSubItem =i;
			lvitem.pszText = LPSTR(LPCTSTR(channel));
			m_ViewDlg->m_ListView.SetItem(&lvitem);

			//	data = channel;
		}
		else if(i==4)
		{
			lvitem.iSubItem =i;
			lvitem.pszText = LPSTR(LPCTSTR(chtype));
			m_ViewDlg->m_ListView.SetItem(&lvitem);
			
			//	data = chtype;
		}
	}

	m_TableDlg->Interface_Show();
	return 1;
}

int  CObj__Log_View::Subtract_Item(const HDC& hdc,
									   const HDC& hdc_back)
{
	// ...
	int index_cnt = m_ViewDlg->m_ListView.GetSelectedCount();
	POSITION pos = m_ViewDlg->m_ListView.GetFirstSelectedItemPosition();
	int index = m_ViewDlg->m_ListView.GetNextSelectedItem(pos);

	if(index < 0)	
	{
		MessageBox(NULL,
				   "Please, select the item to be deleted.",
				   "ITEM SUBTRACTION ERROR",
				   MB_OK|MB_TOPMOST|MB_TASKMODAL|MB_ICONERROR);
		return -1;
	}

	// ...
	CString type, channel,chtype;

	int limit = m_ViewDlg->m_ListView.GetItemCount()-1;
	int i;

	type = m_ViewDlg->m_ListView.GetItemText(index,2);
	channel = m_ViewDlg->m_ListView.GetItemText(index,3);
	chtype = m_ViewDlg->m_ListView.GetItemText(index,4);

	m_ViewDlg->m_ListView.DeleteItem(index);

	if(strcmp(type,"EVENT") == 0)
	{
		limit = mTable_Event_Item.GetSize();

		for(i=0;i<limit;i++)
		{
			if(strcmp(channel,mTable_Event_Item[i]) == 0)
			{
				index = i;
				i = limit;
			}
		}
		
		limit--;
		for(i=index;i<limit;i++)
		{
			mTable_Event_Item[i]  = mTable_Event_Item[i+1];
			mTable_Event_Title[i] = mTable_Event_Title[i+1];
		}

		mTable_Event_Item.SetSize(limit);
		mTable_Event_Title.SetSize(limit);
	}
	else
	{
		limit = mTable_Interval_Item.GetSize();

		for(i=0;i<limit;i++)
		{
			if(strcmp(channel,mTable_Interval_Item[i]) == 0)
			{
				index = i;
				i = limit;
			}
		}
		
		limit--;
		for(i=index;i<limit;i++)
		{
			mTable_Interval_Item[i]  = mTable_Interval_Item[i+1];
			mTable_Interval_Title[i] = mTable_Interval_Title[i+1];
		}

		mTable_Interval_Item.SetSize(limit);
		mTable_Interval_Title.SetSize(limit);
	}
	
	m_TableDlg->Interface_Show();
	return 1;
}

int  CObj__Log_View::Clear_Item(const HDC& hdc,const HDC& hdc_back)
{
	// ...
	if(m_ViewDlg != NULL)	return -1;
	int column, limit;

	limit = m_ViewDlg->m_ListView.GetItemCount();
	if(limit < 1)	return -1;

	// ...
	column = 5;
	m_ViewDlg->m_ListView.DeleteAllItems();

	m_ViewDlg->Interface_Show();

	// ...
	{
		mTable_Event_Item.SetSize(0);
		mTable_Event_Title.SetSize(0);
		mTable_Interval_Item.SetSize(0);
		mTable_Interval_Title.SetSize(0);
	}
	return 1;
}

int  CObj__Log_View::Undo_View(const HWND& hwnd,const HDC& hdc,const HDC& hdc_back)
{
	if(m_ViewDlg == NULL)
	{
		return -1;
	}

	// ...
	CString file_name;
	CString file_data;
	
	mI_BUTTON_View_String->GetTitle(file_name);	

	while(file_name.GetLength() < 1)
	{
		CGX__UTILITY_CTRL cx_utility_ctrl;
		CString title;

		title = "Input file name !";

		if( m_pStringPad->Popup(title, "", file_name) != TRUE )
		{
			return -1;
		}

		mI_BUTTON_View_String->SetTitle(file_name);	
		mI_BUTTON_View_String->DrawPressed(hdc,hdc_back);
	}

	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;

		CString dir_log;
		CString dir_root;

		x_sys_ctrl->Get__SEQ_DIR_ROOT(iMODULE_ID, dir_root);

		dir_log  = dir_root;
		dir_log += "\\EQP_LOG";
		dir_log += "\\datalog";

		CString log_path;
		log_path.Format("%s\\%s.%s", dir_log, file_name,mExt);

		if(Macro__Get_File_Data(log_path, file_data) < 0)
		{	
			printf(" * CObj__Log_View::Undo_View() - Error ! \n");
			printf(" ** log_path <- [%s] \n", log_path);
			return -2;
		}
	}

	// ...
	CStringArray list_channel;
	CStringArray list_title;
	CStringArray list_type;
	CStringArray list_chtype;

	// ...
	{
		CString word;

		int para = 0;
		int flag = 1;
		
		int limit = file_data.GetLength();

		for(int i=0; i<limit; i++)
		{
			char ch = file_data.GetAt(i);

			if((ch == ',')
			|| (ch == '\n'))
			{
				para++;

				if(word.GetLength() > 0)
				{
					if(para == 1)
					{
						list_channel.Add(word);
						list_title.Add("");
						list_type.Add("");
						list_chtype.Add("");
							
					}
					else if(para == 2)
					{
						int index = list_type.GetSize() - 1;

						if(index >= 0)	list_title[index] = word;
					}
					else if(para == 3)
					{
						int index = list_title.GetSize() - 1;

						if(index >= 0)	list_type[index] = word;
					}
					else if(para == 4)
					{
						int index = list_chtype.GetSize() - 1;

						if(index >= 0)	list_chtype[index] = word;
					}
					
					word = "";
				}
			}
			else
			{
				word += ch;
			}

			if(ch == '\n')
			{
				para = 0;
			}
		}
	}

	// ...
	m_ViewDlg->m_ListView.DeleteAllItems();
	m_ViewDlg->m_ListView.SetRedraw(false);

	// ...
	{
		LV_ITEM lvitem;
		CString data;
		
		int column = 5;
		int event_count    = 0;
		int interval_count = 0;	

		int limit = list_channel.GetSize();

		mTable_Event_Item.SetSize(limit);
		mTable_Event_Title.SetSize(limit);
		mTable_Interval_Item.SetSize(limit);
		mTable_Interval_Title.SetSize(limit);

		// ...
		int change_flag = -1;
		
		lvitem.mask = LVIF_TEXT;
		
		for(int i=0; i<limit; i++)
		{
			for(int c=0; c<column; c++)
			{
				lvitem.iSubItem = c;

				if(c==0)	
				{
					data.Format("%002d",i+1);
			 		lvitem.iItem = i;
					lvitem.pszText = LPSTR(LPCTSTR(data));
					m_ViewDlg->m_ListView.InsertItem(&lvitem);
				}
				else if(c==1)
				{
					if(Get_Title(list_channel[i],data) < 0)
					{
						data = list_title[i];
					}
					else
					{
						if(strcmp(data,list_title[i]) != 0)
						{
							list_title[i] = data;
							change_flag = 1;
						}
					}
				}
				else if(c==2)
				{
					data = list_type[i];

					if(strcmp(data,"EVENT") == 0)
					{
						mTable_Event_Item[event_count]  = list_channel[i];
						mTable_Event_Title[event_count] = list_title[i];
						event_count++;
					}
					else 
					{
						mTable_Interval_Item[interval_count]  = list_channel[i];
						mTable_Interval_Title[interval_count] = list_title[i];
						interval_count++;
					}
				}
				else if(c==3)	data = list_channel[i];
				else if(c==4)
				{
					data = list_chtype[i];

					printf(" * %1d) [%s] [%s] \n", i, list_channel[i], list_chtype[i]);
				}

				if(c != 0)
				{
					lvitem.pszText = LPSTR(LPCTSTR(data));
					m_ViewDlg->m_ListView.SetItem(&lvitem);
				}		
			}
		}

		mTable_Event_Item.SetSize(event_count);
		mTable_Event_Title.SetSize(event_count);
		mTable_Interval_Item.SetSize(interval_count);
		mTable_Interval_Title.SetSize(interval_count);

		if(change_flag > 0)
		{
			Save_View(hdc,hdc_back);
		}
	}

	m_ViewDlg->m_ListView.SetRedraw(true);
	return 1;
}

int  CObj__Log_View::Get_Title(CString channel,CString &title)
{
	int limit = m_TableDlg->m_ListView.GetItemCount();
	int i;

	for(i=0;i<limit;i++)
	{
		if(m_TableDlg->m_ListView.GetItemText(i,3) == channel)
		{
			title = m_TableDlg->m_ListView.GetItemText(i,1);
			return 1;
		}
	}
	return -1;
}

int  CObj__Log_View::Save_View(const HDC& hdc,const HDC& hdc_back)
{
	if(m_ViewDlg == NULL)		return -1;

	// ...
	CString file_name;
	mI_BUTTON_View_String->GetTitle(file_name);	

	while(file_name.GetLength() < 1)
	{
		CGX__UTILITY_CTRL cx_utility_ctrl;
		CString title = "Input file name !";

		if(m_pStringPad->Popup(title, "", file_name) != TRUE)
		{
			return -1;
		}

		mI_BUTTON_View_String->SetTitle(file_name);	
		mI_BUTTON_View_String->DrawPressed(hdc,hdc_back);
	}

	// ...
	CString file_data;

	int limit = m_ViewDlg->m_ListView.GetItemCount();
	int i;

	for(i=0;i<limit;i++)
	{
		file_data += m_ViewDlg->m_ListView.GetItemText(i,3);//channel
		file_data += ",";
		file_data += m_ViewDlg->m_ListView.GetItemText(i,1);//title

		file_data += ",";
		file_data += m_ViewDlg->m_ListView.GetItemText(i,2);//type

		file_data += ",";
		file_data += m_ViewDlg->m_ListView.GetItemText(i,4);//ch_type

		file_data += ",\n";
	}

	// ...
	{
		Write_File_to_SEQ(iMODULE_ID,file_name,mExt,file_data);
	}

	m_ViewDlg->Interface_Show();
	return 1;
}

int  CObj__Log_View::SaveAs_View(const HDC& hdc,const HDC& hdc_back)
{
	CGX__UTILITY_CTRL cx_utility_ctrl;
	CString title;
	CString out_data;

	title = "Input file name !";

	if(m_pStringPad->Popup(title, "", out_data) != TRUE)
	{
		return -1;
	}

	mI_BUTTON_View_String->SetTitle(out_data);	
	mI_BUTTON_View_String->DrawPressed(hdc,hdc_back);

	Save_View(hdc,hdc_back);
	return 1;
}

int  CObj__Log_View::File_View(const HWND& hwnd,const HDC& hdc,const HDC& hdc_back)
{
	CGX_FILE__DATALOG_CTRL cx_datalog_ctrl;
	CString in_file;
	CString out_file;

	mI_BUTTON_View_String->GetTitle(in_file);

	if(cx_datalog_ctrl->Popup_File_Control(iMODULE_ID,"",mExt,in_file,out_file) < 0)
	{
		return -1;
	}

	mI_BUTTON_View_String->SetTitle(out_file);	
	mI_BUTTON_View_String->DrawPressed(hdc,hdc_back);

	Undo_View(hwnd,hdc,hdc_back);
	return 1;
}

int  CObj__Log_View::Log_Date_Table(const HDC& hdc,const HDC& hdc_back)
{
	CGX_FILE__DATALOG_CTRL cx_datalog_ctrl;
	CString out_file_name;

	if(iFlag__Remote_Disk < 0)
	{
		if(cx_datalog_ctrl->Popup_File_Explorer(iMODULE_ID,
												"",
												mFile_Ext,
												"",
												out_file_name) < 0)
		{
			return -1;
		}
	}
	else
	{			
		CGX__SYSTEM_CTRL cx_sys_ctrl;
		CString dir_root;

		cx_sys_ctrl->Get__SEQ_DIR_DATALOG(iMODULE_ID,dir_root);

		int flag = cx_datalog_ctrl->Popup_File_Explorer_Using_Remote_Disk(dir_root,
																		  mFile_Ext,
																		  "",
																          out_file_name);

		if(flag < 0)
		{
			return -1;
		}
	}

	mI_BUTTON_Date_String->SetTitle(out_file_name);	
	mI_BUTTON_Date_String->DrawPressed(hdc,hdc_back);
	return 1;
}

int CObj__Log_View::Search_View(const HWND hwnd)
{
	if(m_TableDlg == NULL)
	{
		return -1;
	}

	// ...
	CString item_keyword;
	CString item_row;
	CRect	rc;

	mI_BUTTON_Search_String->GetTitle(item_keyword);
	item_keyword.MakeLower();

	if(item_keyword.GetLength() < 1)
	{
		return -1;
	}

	// ...
	int index_cnt = m_TableDlg->m_ListView.GetSelectedCount();
	POSITION pos = m_TableDlg->m_ListView.GetFirstSelectedItemPosition();
	int start_index = m_TableDlg->m_ListView.GetNextSelectedItem(pos);

	if(start_index < 0)
	{
		start_index = 0;
	}

	// ...
	int row_cnt = m_TableDlg->m_ListView.GetItemCount();
	int i;

	for(i=start_index+1; i<row_cnt; i++)
	{
		item_row = m_TableDlg->m_ListView.GetItemText(i,1);
		item_row.MakeLower();

		if(item_row.Find(item_keyword,0) >=0)
		{
			m_TableDlg->m_ListView.SetSelectionMark(i);
			m_TableDlg->m_ListView.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
			m_TableDlg->m_ListView.SetFocus();
			m_TableDlg->m_ListView.GetItemRect(0,rc,LVIR_BOUNDS);
			int crr = m_TableDlg->m_ListView.GetScrollPos(SB_VERT);
			
			CSize size(0,rc.Height()*(i-crr));
			m_TableDlg->m_ListView.Scroll(size);
			return 1;
		}
	}

	for(i=0; i<start_index;i++)
	{
		item_row = m_TableDlg->m_ListView.GetItemText(i,1);
		item_row.MakeLower();
		if(item_row.Find(item_keyword,0) >=0)
		{
			m_TableDlg->m_ListView.SetSelectionMark(i);
			m_TableDlg->m_ListView.SetItemState(i,LVIS_SELECTED,LVIS_SELECTED);
			m_TableDlg->m_ListView.SetFocus();
			m_TableDlg->m_ListView.GetItemRect(0,rc,LVIR_BOUNDS);
			int crr = m_TableDlg->m_ListView.GetScrollPos(SB_VERT);
			
			CSize size(0,rc.Height()*(i-crr));
			m_TableDlg->m_ListView.Scroll(size);
			return 1;
		}
	}

	MessageBox(hwnd,"Can not find matching item","Notification",NULL);
	return -1;
}
int CObj__Log_View::Search_String(const HDC& hdc,const HDC& hdc_back)
{
	// ...
	CGX__UTILITY_CTRL cx_utility_ctrl;
	CString title;
	CString item_name;

	// ...
	{
		title = "Input Item Name for Searching !";

		if(m_pStringPad->Popup(title, "", item_name) != TRUE)
		{
			return -1;
		}
	}

	// ...
	{
		mI_BUTTON_Search_String->SetTitle(item_name);	
		mI_BUTTON_Search_String->DrawPressed(hdc,hdc_back);
	}
	return 1;
}


//.....
#define CFG__ITEM_MAX			300


int  CObj__Log_View::Make_Log_File(const CString& log_file,
								   const CString& table_file,
								   const CString& file_data)
{
	//-------------------------------------------------------------------------
	CString string;
	string.Format("%s\n%s\n%s\n%s\n",
				  "[VIEW]",  
				  "LogViewer.txt",
				  log_file,
				  table_file);

	mFile_Data.RemoveAll();
	mFile_Data.Add(string);	

	//-------------------------------------------------------------------------
	CString line_word;
	CString str_word;
	CString name_str;
	CString data_str;
	CString time_str;
	CString title_str;
	char ch;
	int fnc_num;
	int under_line;
	int para;
	int interval_flag;

	str_word = "";
	interval_flag = -1;
	fnc_num = -1;
	para = 0;
	under_line = 0;

	int i_ch;
	int limit_ch = file_data.GetLength();

	//////////////////////////////////////////////////////////////////////////

	int k;
	CString l_channel_data[CFG__ITEM_MAX];
	CString channel, event_channel, event_data;
	int k_limit;
	int channel_count;
	channel_count = 0;

	char	l_channel_min[CFG__ITEM_MAX][200];
	char	l_channel_max[CFG__ITEM_MAX][200];
	char	l_channel_avg[CFG__ITEM_MAX][200];
	CString getLine="";
	
	int  table_line;
	table_line = mFile_Data.GetSize();
	CString str_line = "";
	//////////////////////////////////////////////////////////////////////////

	for(i_ch=0;i_ch<limit_ch;i_ch++)
	{
		ch = file_data.GetAt(i_ch);

		if((ch == '\n')
		|| (ch ==  ',')
		|| (ch == ';')
		|| (ch ==  ' ')
		|| (ch == '$'))
		{
			if(str_word.GetLength() > 0)
			{
				if(str_word.Compare("#1") == 0)
				{
					fnc_num = 1;
				}
				else if(str_word.Compare("#2") == 0)
				{
					fnc_num = 2;
				}
				else if(str_word.Find("#STEP_MIN")>=0)
				{
					fnc_num = 4;
				}
				else if(str_word.Find("#STEP_MAX")>=0)
				{
					fnc_num = 5;
				}
				else if(str_word.Find("#STEP_AVG")>=0)
				{
					fnc_num = 6;
				}
				else
				{
					if(fnc_num == 1)
					{
						str_line += str_word;
						str_line += " ";
					}
					else if(fnc_num == 2)
					{
						
						time_str = str_word;
					}
					else if(fnc_num == 3)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;
							
							event_channel = str_word;	
						}
						else if(para == 2)
						{
							k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

							for(int k=0;k<k_limit;k++)
							{
								if(strcmp(mTable_Interval_Item[k],channel) == 0)
								{
									l_channel_data[k] = str_word;
									channel_count++;
								}
							}
							event_data = str_word;
						}
					}
					else if(fnc_num == 4 || fnc_num == 5 || fnc_num == 6)
					{
							para++;
							
							if(para == 1)
							{
								channel = str_word;
							}
							else if(para == 2)
							{
								k_limit = mTable_Interval_Item.GetSize();
								if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

								for(k=0;k<k_limit;k++)
								{
									if(strcmp(mTable_Interval_Item[k],channel) == 0)
									{
											 if(fnc_num == 4)	strcpy(l_channel_min[k],str_word);
										else if(fnc_num == 5)	strcpy(l_channel_max[k],str_word);
										else if(fnc_num == 6)	strcpy(l_channel_avg[k],str_word);

										channel_count++;
									}
								}							
							}
					}
					else // fnc_num == -1 $뒤 #없는 문자는 그냥 그대로 찍어 버려..
					{
						getLine += str_word;
					}
				}
			}

			str_word = "";
		}
		else 
		{
			str_word += ch;
		}

		if(ch == '\n') 
		{
			if(fnc_num == -1)
			{
				if(getLine.GetLength() > 0)
				{
					CString tmpline;
					tmpline = getLine;
					table_line = mFile_Data.GetSize();
					mFile_Data.SetSize(table_line+1);
					mFile_Data[table_line].Format("%s",tmpline);
					
					k_limit = mTable_Interval_Item.GetSize();
					for(k=1;k<k_limit;k++)
					{
						tmpline.Format("-----------------");
						mFile_Data[table_line] += tmpline;
					}

					table_line++;
					getLine = "";
				}
			}

			if(fnc_num == 1)
			{

				CString msg;

				msg.Format(" Datalog Report of File : ..\\%s",log_file);
				mFile_Data.Add(msg);
				
				msg.Format("  %s\n",str_line);
				mFile_Data.Add(msg);

				CString bff;
				int k;
				int k_limit = mTable_Interval_Item.GetSize();

				mTable_Interval_Item.SetSize(k_limit);
				msg = " hh:mm:ss  ";
				
				for(k=0;k<k_limit;k++)
				{
					bff.Format("%20s",mTable_Interval_Title[k]); 
					
					msg += bff;
				}
				msg += "\n"; 

				mFile_Data.Add(msg);

				//-------------------------------------------------------------------------
				under_line = msg.GetLength();
				msg = "";

				int i;
				for(i=0;i<under_line;i++)
				{
					msg += "-"; 
				}
				msg += "\n";
				
				mFile_Data.Add(msg);


				str_line = "";

				
				fnc_num = -1;
			}
			if(fnc_num == 2)	fnc_num = 3;

			para = 0;
			channel = "";
		}
		if(ch == '$')
		{
			if(fnc_num == 3)
			{
				if(channel_count == 0)
				{
					k_limit = mTable_Event_Item.GetSize();

					for(k=0;k<k_limit;k++)
					{
						if(strcmp(mTable_Event_Item[k],event_channel) == 0)
						{
							CString str;
							str.Format("%s : %s -> %s",
								       time_str,
									   mTable_Event_Title[k],
									   event_data);

							mFile_Data.Add(str);
							table_line++;

							break;
						}
					}
				}
				else 
				{
					CString str_bff;

					table_line = mFile_Data.GetSize();
					mFile_Data.SetSize(table_line+1);
					mFile_Data[table_line].Format("%s : ",time_str);

					k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					for(k=0;k<k_limit;k++)
					{
						str_bff.Format("%19s ", l_channel_data[k]);
						mFile_Data[table_line] += str_bff;
					}

					table_line++;
				}
			} 
			else if(fnc_num == 4 || fnc_num == 5 ||fnc_num == 6)
			{
				if(channel_count == 0)
				{
				
				}
				else 
				{
					CString ttmp;

					k_limit = mTable_Interval_Item.GetSize();					
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					if(fnc_num == 4)		
					{
						if(m_ChMIN == TRUE)
						{
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("         MIN : ");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%19s ", l_channel_min[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
							
						}
					} 
					else if(fnc_num == 5)		
					{
						if(m_ChMAX == TRUE)
						{	
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("         MAX : ");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%19s ", l_channel_max[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
						}
					}
					else if(fnc_num == 6)		
					{
						if(m_ChAVG == TRUE)
						{
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("         AVG : ");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%19s ", l_channel_avg[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
						}
					}
					
					ttmp = "";
				}
			}

			//
			channel_count = 0;
			str_line = "";
			time_str = "";
			fnc_num = -1;

			event_channel = "";
			event_data = "";
		
			//
			k_limit = mTable_Interval_Item.GetSize();
			if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

			for(k=0;k<k_limit;k++)
			{
				l_channel_data[k]="";
				
				strcpy(l_channel_min[k],"");
				strcpy(l_channel_max[k],"");
				strcpy(l_channel_avg[k],"");
			}				
		}
	}
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	FILE *out;
	int limit;
	int i;

	CreateDirectory(sDir__Temp_Log, NULL);

	out = fopen(sPath__Log_Viewer_Inf, "w");
	if(out != NULL)
	{
		fputs(mFile_Data[0],out);
		fclose(out);
	}

	out = fopen(sPath__Log_Viewer_Txt, "w");
	if(out != NULL)
	{
		limit = mFile_Data.GetSize();
		for(i=1;i<limit;i++)
		{
			fputs(mFile_Data[i],out);
			fputs("\n",out);
		}

		fclose(out);
	}
	//-------------------------------------------------------------------------

	mFile_Data.RemoveAll();
	return 1;
}

int  CObj__Log_View::Make_CSVLog_File(const CString& log_file,
									  const CString& table_file,
									  const CString& file_data)
{
	//-------------------------------------------------------------------------
	CString string;
	string.Format("%s\n%s\n%s\n%s\n",
				  "[VIEW]",  
				  "LogViewer.txt",
				  log_file,
				  table_file);

	mFile_Data.RemoveAll();
	mFile_Data.Add(string);	

	//////////////////////////////////////////////////////////////////////////

	int k;
	CString l_channel_data[CFG__ITEM_MAX];
	CString channel, event_channel, event_data;
	int k_limit;
	int channel_count;
	channel_count = 0;

	char	l_channel_min[CFG__ITEM_MAX][200];
	char	l_channel_max[CFG__ITEM_MAX][200];
	char	l_channel_avg[CFG__ITEM_MAX][200];
	CString getLine="";
	

	int  table_line;
	table_line = mFile_Data.GetSize();
	CString str_line = "";
	//////////////////////////////////////////////////////////////////////////

	//-------------------------------------------------------------------------

	CString line_word;
	CString str_word;
	CString name_str;
	CString data_str;
	CString time_str;
	CString title_str;
	char ch;
	int fnc_num;
	int under_line;
	int para;
	int interval_flag;

	str_word = "";
	interval_flag = -1;
	fnc_num = -1;
	para = 0;
	under_line = 0;

	int i_ch;
	int limit_ch = file_data.GetLength();

	for(i_ch=0;i_ch<limit_ch;i_ch++)
	{
		ch = file_data.GetAt(i_ch);

		if((ch == '\n')
		|| (ch ==  ',')
		|| (ch == ';')
		|| (ch ==  ' ')
		|| (ch == '$'))
		{
			if(str_word.GetLength() > 0)
			{
				if(str_word.Compare("#1") == 0)
				{
					fnc_num = 1;
				}
				else if(str_word.Compare("#2") == 0)
				{
					fnc_num = 2;
				}
				else if(str_word.Find("#STEP_MIN")>=0)
				{
					fnc_num = 4;
				}
				else if(str_word.Find("#STEP_MAX")>=0)
				{
					fnc_num = 5;
				}
				else if(str_word.Find("#STEP_AVG")>=0)
				{
					fnc_num = 6;
				}
				else
				{
					if(fnc_num == 1)
					{
						str_line += str_word;
						str_line += " ";
					}
					else if(fnc_num == 2)
					{
						
						time_str = str_word;
					}
					else if(fnc_num == 3)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;
							
							event_channel = str_word;
						}
						else if(para == 2)
						{
							k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

							for(int k=0;k<k_limit;k++)
							{
								if(strcmp(mTable_Interval_Item[k],channel) == 0)
								{
									l_channel_data[k] = str_word;
									channel_count++;
								}
							}
							event_data = str_word;
						}
					}
					else if(fnc_num == 4 || fnc_num == 5 || fnc_num == 6)
					{
							para++;
							
							if(para == 1)
							{
								channel = str_word;
							}
							else if(para == 2)
							{
								k_limit = mTable_Interval_Item.GetSize();
								if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

								for(k=0;k<k_limit;k++)
								{
									if(strcmp(mTable_Interval_Item[k],channel) == 0)
									{
											 if(fnc_num == 4)	strcpy(l_channel_min[k],str_word);
										else if(fnc_num == 5)	strcpy(l_channel_max[k],str_word);
										else if(fnc_num == 6)	strcpy(l_channel_avg[k],str_word);

										channel_count++;
									}
								}							
							}
					}
					else 
					{
						getLine += str_word;
					}
				}
			}

			str_word = "";
		}
		else 
		{
			str_word += ch;
		}

		if(ch == '\n') 
		{
			if(fnc_num == -1)
			{
				if(getLine.GetLength()>0)
				{
					CString tmpline;
					tmpline = getLine;
					table_line = mFile_Data.GetSize();
					mFile_Data.SetSize(table_line+1);
					mFile_Data[table_line].Format("%s,",tmpline);
					
					k_limit = mTable_Interval_Item.GetSize();
					for(k=1;k<k_limit;k++)
					{
						tmpline.Format("---------------,");
						mFile_Data[table_line] += tmpline;
					}

					table_line++;
					getLine = "";
				}
			}
			if(fnc_num == 1)
			{
				CString msg;

				msg.Format(" Datalog Report of File : ..\\%s",log_file);
				mFile_Data.Add(msg);

				msg.Format("  %s\n",str_line);
				mFile_Data.Add(msg);


				CString bff;
				int k;
				int k_limit = mTable_Interval_Item.GetSize();

				mTable_Interval_Item.SetSize(k_limit);
				msg = " hh:mm:ss  ";
				
				for(k=0;k<k_limit;k++)
				{
					bff.Format("%20s",mTable_Interval_Title[k]); 

					msg += ",";
					msg += bff;
				}
				msg += "\n"; 

				mFile_Data.Add(msg);

				//-------------------------------------------------------------------------
			
				str_line = "";

				
				fnc_num = -1;
			}
			if(fnc_num == 2)	fnc_num = 3;

			para = 0;
			channel = "";
		}
		if(ch == '$')
		{
			if(fnc_num == 3)
			{
				if(channel_count == 0)
				{
					k_limit = mTable_Event_Item.GetSize();

					for(k=0;k<k_limit;k++)
					{
						if(strcmp(mTable_Event_Item[k],event_channel) == 0)
						{
							CString str;
							str.Format("%s : %s -> %s",
								       time_str,
									   mTable_Event_Title[k],
									   event_data);

							mFile_Data.Add(str);

							break;
						}
					}
				}
				else 
				{
					CString str_bff;

					mFile_Data.SetSize(table_line+1);
					mFile_Data[table_line].Format("%s : ,",time_str);

					k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					for(k=0;k<k_limit;k++)
					{
						str_bff.Format("%19s ,", l_channel_data[k]);
						mFile_Data[table_line] += str_bff;
					}

					table_line++;
				}
			} 
			else if(fnc_num == 4 || fnc_num == 5 ||fnc_num == 6)
			{
				if(channel_count == 0)
				{

				}
				else 
				{
					CString ttmp;

					k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;
					
					if(fnc_num == 4)		
					{
						if(m_ChMIN == TRUE)
						{
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("\tMIN : ,");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%19s ,", l_channel_min[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
							
						}
					} 
					else if(fnc_num == 5)		
					{
						if(m_ChMAX == TRUE)
						{	
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("\tMAX : ,");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%19s ,", l_channel_max[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
						}
					}
					else if(fnc_num == 6)		
					{
						if(m_ChAVG == TRUE)
						{	
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("\tAVG : ,");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%19s ,", l_channel_avg[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
						}
					}
					ttmp = "";
				}
			}

			channel_count = 0;
			str_line = "";
			time_str = "";
			fnc_num = -1;

			event_channel = "";
			event_data = "";
		
			//.....
			k_limit = mTable_Interval_Item.GetSize();
			if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

			for(k=0;k<k_limit;k++)
			{
				l_channel_data[k]="";
				strcpy(l_channel_min[k],"");
				strcpy(l_channel_max[k],"");
				strcpy(l_channel_avg[k],"");
			}				
		}
	}
	//-------------------------------------------------------------------------

	//-------------------------------------------------------------------------
	FILE *out;

	CreateDirectory(sDir__Temp_Log, NULL);

	out = fopen(sPath__Log_Viewer_Inf, "w");
	if(out != NULL)
	{
		fputs(mFile_Data[0],out);
		fclose(out);
	}

	out = fopen(sPath__Log_Viewer_Txt, "w");
	if(out != NULL)
	{
		int limit = mFile_Data.GetSize();

		for(int i=1;i<limit;i++)
		{
			fputs(mFile_Data[i],out);
			fputs("\n",out);
		}

		fclose(out);
	}
	//-------------------------------------------------------------------------

	mFile_Data.RemoveAll();
	return 1;
}

int  CObj__Log_View::
Make_ViewCSV_File(const CString& log_file,
				  const CString& table_file,
			      const CString& file_data)
{
	mFile_Data.RemoveAll();

	// ...
	int k;
	CString channel_data[CFG__ITEM_MAX];
	CString channel, event_channel, event_data;
	int k_limit;
	int channel_count;
	channel_count = 0;

	char	channel_min[CFG__ITEM_MAX][200];
	char	channel_max[CFG__ITEM_MAX][200];
	char	channel_avg[CFG__ITEM_MAX][200];
	CString getLine="";
	
	int  table_line;
	table_line = mFile_Data.GetSize();
	CString str_line = "";

	// ...
	CString line_word;
	CString str_word;
	CString name_str;
	CString data_str;
	CString time_str;
	CString title_str;
	char ch;
	int fnc_num;
	int under_line;
	int para;
	int interval_flag;

	str_word = "";
	interval_flag = -1;
	fnc_num = -1;
	para = 0;
	under_line = 0;

	int i_ch;
	int limit_ch = file_data.GetLength();

	for(i_ch=0;i_ch<limit_ch;i_ch++)
	{
		ch = file_data.GetAt(i_ch);

		if((ch == '\n')
		|| (ch ==  ',')
		|| (ch == ';')
		|| (ch ==  ' ')
		|| (ch == '$'))
		{
			if(str_word.GetLength() > 0)
			{
				if(str_word.Compare("#1") == 0)
				{
					fnc_num = 1;
				}
				else if(str_word.Compare("#2") == 0)
				{
					fnc_num = 2;
				}
				else if(str_word.Find("#STEP_MIN")>=0)
				{
					fnc_num = 4;
				}
				else if(str_word.Find("#STEP_MAX")>=0)
				{
					fnc_num = 5;
				}
				else if(str_word.Find("#STEP_AVG")>=0)
				{
					fnc_num = 6;
				}
				else
				{
					if(fnc_num == 1)
					{
						str_line += str_word;
						str_line += " ";
					}
					else if(fnc_num == 2)
					{
						
						time_str = str_word;
					}
					else if(fnc_num == 3)
					{
						para++;

						if(para == 1)
						{
							channel = str_word;
							
							event_channel = str_word;	
						}
						else if(para == 2)
						{
							k_limit = mTable_Interval_Item.GetSize();
							if(k_limit > CFG__ITEM_MAX)			k_limit = CFG__ITEM_MAX;

							for(int k=0;k<k_limit;k++)
							{
								if(strcmp(mTable_Interval_Item[k],channel) == 0)
								{
									channel_data[k] = str_word;
									channel_count++;
								}
							}
							event_data = str_word;
						}
					}
					else if(fnc_num == 4 || fnc_num == 5 || fnc_num == 6)
					{
							para++;
							
							if(para == 1)
							{
								channel = str_word;
							}
							else if(para == 2)
							{
								k_limit = mTable_Interval_Item.GetSize();
								if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

								for(k=0;k<k_limit;k++)
								{
									if(strcmp(mTable_Interval_Item[k],channel) == 0)
									{
										if(fnc_num == 4)		strcpy(channel_min[k],str_word);
										else if(fnc_num == 5)	strcpy(channel_max[k],str_word);
										else if(fnc_num == 6)	strcpy(channel_avg[k],str_word);
										channel_count++;
									}
								}							
							}
					}
					else // fnc_num == -1 $뒤 #없는 문자는 그냥 그대로 찍어 버려..
					{
						getLine += str_word;
					}
				}
			}

			str_word = "";
		}
		else 
		{
			str_word += ch;
		}

		if(ch == '\n') 
		{
			if(fnc_num == -1)
			{
				if(getLine.GetLength()>0)
				{
					CString tmpline;
					tmpline = getLine;
					table_line = mFile_Data.GetSize();
					mFile_Data.SetSize(table_line+1);
					mFile_Data[table_line].Format("%s,",tmpline);
					
					k_limit = mTable_Interval_Item.GetSize();
					for(k=1;k<k_limit;k++)
					{
						tmpline.Format("---------------,");
						mFile_Data[table_line] += tmpline;
					}

					table_line++;
					getLine = "";
				}
			}
			if(fnc_num == 1)
			{
				CString msg;
				CString bff;

				int k_limit = mTable_Interval_Item.GetSize();
				int k;

				mTable_Interval_Item.SetSize(k_limit);
				msg = "hh:mm:ss,";
				
				for(k=0;k<k_limit;k++)
				{
					bff.Format("%s,",mTable_Interval_Title[k]); 
					msg += bff;
				}
				mFile_Data.Add(msg);

				str_line = "";
				
				fnc_num = -1;
			}
			if(fnc_num == 2)
			{
				fnc_num = 3;
			}

			para = 0;
			channel = "";
		}
		if(ch == '$')
		{
			if(fnc_num == 3)
			{
				if(channel_count != 0)
				{
					CString str_bff;

					mFile_Data.SetSize(table_line+1);
					mFile_Data[table_line].Format("%s,",time_str);

					k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

					for(k=0;k<k_limit;k++)
					{
						str_bff.Format("%s,",channel_data[k]);
						mFile_Data[table_line] += str_bff;
					}

					table_line++;
				}
			} 
			else if(fnc_num == 4 || fnc_num == 5 ||fnc_num == 6)
			{
				if(channel_count == 0)
				{
				}
				else 
				{
					CString ttmp;

					k_limit = mTable_Interval_Item.GetSize();
					if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;
					
					if(fnc_num == 4)		
					{
						if(m_ChMIN == TRUE)
						{
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("MIN,");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%s,",channel_min[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
							
						}
					} 
					else if(fnc_num == 5)		
					{
						if(m_ChMAX == TRUE)
						{	
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("MAX,");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%s,",channel_max[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
						}
					}
					else if(fnc_num == 6)		
					{
						if(m_ChAVG == TRUE)
						{
							
							mFile_Data.SetSize(table_line+1);
							mFile_Data[table_line].Format("AVG,");
							
							for(k=0;k<k_limit;k++)
							{
								ttmp.Format("%s,",channel_avg[k]);
								mFile_Data[table_line] += ttmp;
							}
							table_line++;
						}
					}
					ttmp = "";
				}
				
			}

			channel_count = 0;
			str_line = "";
			time_str = "";
			fnc_num = -1;

			event_channel = "";
			event_data = "";
		
			// ...
			k_limit = mTable_Interval_Item.GetSize();
			if(k_limit > CFG__ITEM_MAX)		k_limit = CFG__ITEM_MAX;

			for(k=0;k<k_limit;k++)
			{
				channel_data[k]="";
				strcpy(channel_min[k],"");
				strcpy(channel_max[k],"");
				strcpy(channel_avg[k],"");
			}				
		}
	}

	// ...
	CreateDirectory(sDir__Temp_Log, NULL);

	FILE* out = fopen(sPath__Graph_Log, "w");
	if(out != NULL)
	{
		int limit = mFile_Data.GetSize();

		for(int i=0;i<limit;i++)
		{
			fputs(mFile_Data[i],out);
			fputs("\n",out);
		}

		fclose(out);
	}

	mFile_Data.RemoveAll();
	return 1;
}

int  CObj__Log_View::Fnc_FileConversion(int modulID,CString ext)
{
	CreateDirectory(sDir__Temp_Log, NULL);

	FILE* out = fopen(sPath__Log_Conversion, "w");

	if(out != NULL)
	{
		fputs("@VERSION\n",out);
		fputs("2\n",out);

		fputs("@DIRECTORY\n",out);

		// ...
		CString ID;
		ID.Format("%d",modulID);

		fputs(ID,out);
		fputs("\n",out);

		fputs("@EXT\n",out);
		fputs(ext,out);
		fputs("\n",out);

		// ...
		{
			int limit = mTable_Interval_Item.GetSize();

			fputs("@INTERVAL_ITEM\n",out);
			
			for(int i=0;i<limit;i++)
			{
				fputs(mTable_Interval_Item[i],out);
				fputs(",",out);
				fputs(mTable_Interval_Title[i],out);
				fputs("\n",out);
			}
		}

		// ...
		{
			int limit = mTable_Event_Item.GetSize();

			fputs("@EVENT_ITEM\n",out);
			
			for(int i=0;i<limit;i++)
			{
				fputs(mTable_Event_Item[i],out);
				fputs(",",out);
				fputs(mTable_Event_Title[i],out);
				fputs("\n",out);
			}
		}

		fclose(out);
	}

	return 1;
}

int  CObj__Log_View::Read_File_from_SEQ(const HWND& hwnd,
									   const int& iModule,
									   const CString& file_name,
									   const CString& file_ext,
									   CString& file_data)
{
	CString str_dir_file;
	
	// ...
	{
		file_data = "";

		// str_dir_file.Format("%s\\%s.%s", sDir_Root,file_name,file_ext);
		str_dir_file.Format("%s\\%s", sDir_Root,file_name);

		printf(" * CObj__Log_View::Read_File_from_SEQ() ... \n");
		printf("   * Dir_Root  <- %s \n", sDir_Root);
		printf("   * File_Name <- %s \n", file_name);
		printf("   * File_Ext  <- %s \n", file_ext );
		printf("\n");
	}
	
	// ...
	{
		FILE *fp = fopen(str_dir_file, "r");
	
		if(fp == NULL)
		{
			MessageBox(hwnd,str_dir_file,"Read_File_from_SEQ() : File Path - Error !",MB_OK|MB_TOPMOST);
			return -1;
		}
		
		fseek(fp,0,SEEK_END);
		int totalbytes = ftell(fp);
		
		char *p_file = new char[totalbytes+1];
		if(p_file == NULL)
		{
			MessageBox(hwnd,str_dir_file,"Read_File_from_SEQ() : File Memory Allocation - Error !",MB_OK|MB_TOPMOST);
			return - 1;
		}
		
		rewind(fp);
		
		// ...
		int numread = fread(p_file,1,totalbytes,fp);
		p_file[numread] = 0;
		
		fclose(fp);
		
		file_data.Format("%s", p_file);
		delete [] p_file;
	}

	return 1;
}
int  CObj__Log_View::Write_File_to_SEQ(const int& iModule, 
									  const CString& file_name,
									  const CString& file_ext,
									  CString& file_data)
{
	CGX__SYSTEM_CTRL cgx_sys_ctrl;
	CString str_dir;
	CString str_dir_file;

	// ...
	{
		cgx_sys_ctrl->Get__SEQ_DIR_DATALOG(iModule,str_dir);
	
		str_dir_file.Format("%s\\%s.%s",str_dir,file_name,file_ext);
	}

	// ...
	{
		CStdioFile stdfile;
		CFileException e;
	
		if(!stdfile.Open(str_dir_file,CFile::modeReadWrite|CFile::modeCreate,&e))
		{	
			e.ReportError();
			return -1;
		}
	
		stdfile.WriteString(file_data);
		stdfile.Close();
	}

	return 1;
}
