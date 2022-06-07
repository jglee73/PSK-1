#include "StdAfx.h"
#include "CObj__FA_Property_STD.h"
#include "CObj__FA_Property_STD__KEY_DEF.h"

#include "Dlg__FA_Property.h"


//-------------------------------------------------------------------------------------
CObj__FA_Property_STD::CObj__FA_Property_STD()
{
	p_Utility = New_UTILITY();
	p_Button  = New_BUTTON();
}
CObj__FA_Property_STD::~CObj__FA_Property_STD()
{
	delete p_Utility;
	delete p_Button;
}


//-------------------------------------------------------------------------------------
void CObj__FA_Property_STD
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Channel(pKEY__CH_FEEDBACK);
	p_obj_para_def->Register_Command(pKEY__DATA_FEEDBACK);

	p_obj_para_def->Register_Command(pKEY__DATA_DIR_SUB);
	p_obj_para_def->Register_Command(pKEY__DATA_FILE_NAME);

	p_obj_para_def->Register_Command(pKEY__DATA_FONT_NAME, "FontBox", "", "Fixedsys");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_WIDTH, "", "", "6");
	p_obj_para_def->Register_Command(pKEY__DATA_FONT_HEIGHT, "", "", "15");

	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH, "", "", "1");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(244,245,249)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(174,175,179)");

	p_obj_para_def->Register_Command(pKEY__DATA_TITLE_TEXT);
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_P_COLOR, "Color", "", "RGB(110,110,110)");
	p_obj_para_def->Register_Command(pKEY__DATA_TEXT_R_COLOR, "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_P_COLOR, "Color", "", "RGB(155,155,155)");
	p_obj_para_def->Register_Command(pKEY__DATA_BACK_R_COLOR, "Color", "", "RGB(255,255,255)");
}
void CObj__FA_Property_STD
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

		rAREA.left   = pSt.x;
		rAREA.top    = pSt.y;
		rAREA.right  = pEt.x;
		rAREA.bottom = pEt.y;

		//
		iREAL_MODE = p_obj_res->pGOBJ_PARA_CTRL->Check__RealMode();
		pGObj_Res  = p_obj_res;
	}

	// ...
	{
		GObj__Parameter_Ctrl* p_gobj = p_obj_res->pGOBJ_PARA_CTRL;
		CString ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_FEEDBACK, ch_data);
		sData_Feedback = ch_data;

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
		p_gobj->Get_Constant_Data(pKEY__DATA_TITLE_TEXT, ch_data);
		p_Button->SetTitle(ch_data);

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
		p_Button->SetPosition(pSt, pEt);
	}

	// ...
	{
		GObj__Parameter_Ctrl* p_gobj = p_obj_res->pGOBJ_PARA_CTRL;

		CString dir_root;
		CString dir_sub;
		CString file_name;

		CGX__SYSTEM_CTRL x_sys_ctrl;				
		x_sys_ctrl->Get__SEQ_DIR_ROOT(0, dir_root);

		p_gobj->Get_Constant_Data(pKEY__DATA_DIR_SUB,   dir_sub);
		p_gobj->Get_Constant_Data(pKEY__DATA_FILE_NAME, file_name);

		if(dir_sub.GetLength() > 0)
		{
			sData_Path  = dir_root;
			sData_Path += "\\EQP_INF\\OBJ-FA\\";
			sData_Path += dir_sub;
			sData_Path += "\\";
			sData_Path += file_name; 
		}
		else
		{
			sData_Path  = dir_root;
			sData_Path += "\\EQP_INF\\OBJ-FA\\FA_INF\\";
			sData_Path += file_name; 
		}
	}
}

void CObj__FA_Property_STD
::Show_GObj(const HWND& hwnd)
{
	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	p_Button->DrawReleased(hdc_front, hdc_back);
}
void CObj__FA_Property_STD
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__FA_Property_STD
::WM_Paint(const HWND& hwnd)
{

}
void CObj__FA_Property_STD::
WM_Timer(const HWND& hwnd)
{

}

void CObj__FA_Property_STD::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{
	POINT pt = mouse_pt;

	if(p_Button->CheckArea(pt) >= 0)
	{
		AFX_MANAGE_STATE(AfxGetStaticModuleState());

		// ...
		HDC hdc_front = pGObj_Res->hDC;
		HDC hdc_back  = pGObj_Res->hDC_BACK;

		p_Button->DrawPressed(hdc_front, hdc_back);

		// ...
		CDlg__FA_Property dlg;

		dlg.mPath = sData_Path;
		
		if(IDOK == dlg.DoModal())
		{
			if(iREAL_MODE > 0)
			{
				WritePrivateProfileString("PROPERTY","CONNECTION", dlg.mStr_Connection, sData_Path);	
				WritePrivateProfileString("PROPERTY","COMM",       dlg.mStr_COMM_Port,  sData_Path);	

				WritePrivateProfileString("PROPERTY","HSMS_MODE",  dlg.mStr_HSMS_Mode, sData_Path);
				WritePrivateProfileString("PROPERTY","IP",         dlg.mStr_HSMS_IP,   sData_Path);
				WritePrivateProfileString("PROPERTY","PORT",       dlg.mStr_HSMS_Port, sData_Path);
			}

			pGObj_Res->pGOBJ_PARA_CTRL->Set_Suffix_Feedback(pKEY__CH_FEEDBACK, sData_Feedback);
		}

		p_Button->DrawReleased(hdc_front, hdc_back);

		InvalidateRect(hwnd, &rAREA, TRUE);
	}
}
void CObj__FA_Property_STD::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__FA_Property_STD::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__FA_Property_STD::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__FA_Property_STD::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

