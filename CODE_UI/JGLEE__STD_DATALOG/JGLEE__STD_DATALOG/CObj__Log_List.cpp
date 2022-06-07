#include "stdafx.h"
#include "JGLEE__STD_DATALOG.h"

#include "CObj__Log_List.h"
#include "CObj__Log_List__KEY_DEF.h"


// ...
CObj__Log_List::CObj__Log_List()
{
	iInit_Flag = -1;

	//
	mI_Draw = New_DRAW();

	mI_BUTTON_Edit = New_BUTTON();
	mI_BUTTON_Undo = New_BUTTON();
	mI_BUTTON_Save = New_BUTTON();

	mI_BUTTON_Search     = New_BUTTON();
	mI_BUTTON_Search_Box = New_BUTTON();

	mI_BUTTON_Time        = New_BUTTON();
	mI_BUTTON_Time_String = New_BUTTON();

	//
	mWColor = RGB(255,255,255);
	mBColor = RGB(0,0,0);
	mTitle = "T";

	mPColor = RGB(255,255,255);
	mRColor = RGB(150,150,150);

	mFontName = "Arial";
	mTWidth   = 6;
	mTHeight  = 15;

	//
	pDlg_View = NULL;

	//
	bActive__Show_Page  = false;
	bActive__Init_Table = false;
}
CObj__Log_List::~CObj__Log_List()
{

}

void CObj__Log_List::
Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	CString key_name;

	// ...
	{
		key_name = pKEY__DATA_CONFIG_PATH;
		p_obj_para_def->Register_Command(key_name);

		key_name = pKEY__DATA_CONFIG_DIR;
		p_obj_para_def->Register_Command(key_name);

		key_name = pKEY__DATA_CONFIG_FILE;
		p_obj_para_def->Register_Command(key_name);

		//
		key_name = pKEY__DATA_GROUP_USE;
		p_obj_para_def->Register_Command(key_name, "ListBox", "NO YES", "YES");

		key_name = pKEY__DATA_GROUP_LIST;
		p_obj_para_def->Register_Command(key_name);
	}
}

void CObj__Log_List::
Set_Parameter(const int& module_id,
			  const POINT& st,
			  const POINT& et,
			  const HWND& hwnd,
			  GObj__Resource_Info *p_obj_res)
{
	// ...
	{
		m_pGObj_Res = p_obj_res;

		iMODULE_ID = module_id;
		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();

		pST = st;
		pET = et;
	}

	AFX_MANAGE_STATE(AfxGetStaticModuleState());

	// ...
	{
		POINT table_st;
		POINT table_et;

		table_st = st;
		table_et = et;

		if(pDlg_View == NULL)
		{
			pDlg_View = new CDlg_Log_List((CWnd*) this);
		}
		if(pDlg_View != NULL)
		{
			CString dir_log;

			// ...
			{
				CGX__SYSTEM_CTRL x_sys_ctrl;
				CString dir_root;

				x_sys_ctrl->Get__SEQ_DIR_ROOT(iMODULE_ID, dir_root);

				dir_log  = dir_root;
				dir_log += "\\EQP_LOG";
				dir_log += "\\datalog";
			}

			// ...
			pDlg_View->iMODULE_ID = iMODULE_ID;
			pDlg_View->iEDIT_MODE = mEdit_Flag;

			pDlg_View->iPos_SX = table_st.x;
			pDlg_View->iPos_SY = table_st.y;
			pDlg_View->iPos_EX = table_et.x;
			pDlg_View->iPos_EY = table_et.y;
	
			pDlg_View->sPara__DIR_LOG = dir_log;

			pDlg_View->iFlag__Group_Use = iPara_Flag__Group_Use;
			pDlg_View->sList__Group_Item.Copy(sPara_List__Group_Item);

			pDlg_View->Create(IDD_DLG_LOG_LIST, CWnd::FromHandle(hwnd));			
		}
	}

	_Interface_Parameter();
}

void CObj__Log_List::Show_GObj(const HWND& hwnd)
{	
	_Interface_Show(hwnd);

	bActive__Show_Page = true;
}
void CObj__Log_List::Hide_GObj()
{
	_Interface_Hide();

	bActive__Show_Page = false;
}

void CObj__Log_List::WM_Paint(const HWND& hwnd)
{

}
void CObj__Log_List::WM_Timer(const HWND& hwnd)
{
	_WM_Timer(hwnd);

	//
	if(iREAL_MODE > 0)
	{
		if(bActive__Show_Page)
		{
			if(! bActive__Init_Table)
			{
				bActive__Init_Table = true;

				AFX_MANAGE_STATE(AfxGetStaticModuleState());

				Init__Table(hwnd, true);

				if(pDlg_View != NULL)		pDlg_View->ShowWindow(SW_SHOW);
			}
		}
	}
}
void CObj__Log_List::WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	_WM_LButtonDown(mouse_pt, hwnd);
}
