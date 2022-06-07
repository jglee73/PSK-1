#include "StdAfx.h"
#include "CObj__Status_Box.h"
#include "CObj__Status_Box__KEY_DEF.h"



//-------------------------------------------------------------------------------------
CObj__Status_Box::CObj__Status_Box()
{
	p_Button  = New_BUTTON();
}
CObj__Status_Box::~CObj__Status_Box()
{
	delete p_Button;
}


//-------------------------------------------------------------------------------------
void CObj__Status_Box
::Get_Parameter(GObj__Parameter_Def* p_obj_para_def)
{
	p_obj_para_def->Register_Command(pKEY__DATA_DISPLAY_MODE, "ListBox", "DEFAULT BLINK", "DEFAULT");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_WIDTH, "", "", "1");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_UP_COLOR,   "Color", "", "RGB(0,0,0)");
	p_obj_para_def->Register_Command(pKEY__DATA_EDGE_DOWN_COLOR, "Color", "", "RGB(0,0,0)");

	p_obj_para_def->Register_Channel(pKEY__CH_STATE);

	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE1_STS1);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE1_STS2);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE1_STS3);

	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE2_STS1);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE2_STS2);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE2_STS3);

	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE3_STS1);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE3_STS2);
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE3_STS3);

	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE1_COLOR,  "Color", "", "RGB(0,0,210)");
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE2_COLOR,  "Color", "", "RGB(0,0,210)");
	p_obj_para_def->Register_Command(pKEY__DATA_ACTIVE3_COLOR,  "Color", "", "RGB(0,0,210)");
	p_obj_para_def->Register_Command(pKEY__DATA_INACTIVE_COLOR, "Color", "", "RGB(190,190,190)");

	//
	p_obj_para_def->Register_Command(pKEY__TEST_CH_STATE);
}
void CObj__Status_Box
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

		int r_color;
		int g_color;
		int b_color;

		CString ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_DISPLAY_MODE, ch_data);
		if(ch_data.CompareNoCase("BLINK") == 0)			bActive__Blink_Mode = true;
		else											bActive__Blink_Mode = false;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE1_STS1, ch_data);
		sData__Active1_State1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE1_STS2, ch_data);
		sData__Active1_State2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE1_STS3, ch_data);
		sData__Active1_State3 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE2_STS1, ch_data);
		sData__Active2_State1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE2_STS2, ch_data);
		sData__Active2_State2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE2_STS3, ch_data);
		sData__Active2_State3 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE3_STS1, ch_data);
		sData__Active3_State1 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE3_STS2, ch_data);
		sData__Active3_State2 = ch_data;

		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE3_STS3, ch_data);
		sData__Active3_State3 = ch_data;

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE1_COLOR, ch_data);
		cColor__Active1 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);
		
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE2_COLOR, ch_data);
		cColor__Active2 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);
		
		p_gobj->Get_Constant_Data(pKEY__DATA_ACTIVE3_COLOR, ch_data);
		cColor__Active3 = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);
		
		p_gobj->Get_Constant_Data(pKEY__DATA_INACTIVE_COLOR, ch_data);
		cColor__InActive = p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color);

		//
		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_WIDTH, ch_data);
		if(ch_data.GetLength() < 1)			ch_data = "2";
		p_Button->SetThick(atoi(ch_data));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_UP_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(0,0,0)";
		p_Button->SetUpColor(p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color));

		p_gobj->Get_Constant_Data(pKEY__DATA_EDGE_DOWN_COLOR, ch_data);
		if(ch_data.GetLength() < 1)		ch_data = "RGB(0,0,0)";
		p_Button->SetDownColor(p_gobj->Get_RGB_Color(ch_data, r_color,g_color,b_color));

		//		
		p_Button->SetPosition(pSt, pEt);
	}
}

void CObj__Status_Box
::Show_GObj(const HWND& hwnd)
{
	sPre_State = "~";

	Draw_Button();
}
void CObj__Status_Box
::Hide_GObj()
{

}

//-------------------------------------------------------------------------------------	
void CObj__Status_Box
::WM_Paint(const HWND& hwnd)
{

}
void CObj__Status_Box::
WM_Timer(const HWND& hwnd)
{
	Draw_Button();
}

void CObj__Status_Box::
WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Status_Box::
WM_LButtonUp(const HWND& hwnd)
{

}

void CObj__Status_Box::
WM_RButtonDown(const POINT& mouse_pt,const HWND& hwnd)
{

}
void CObj__Status_Box::
WM_RButtonUp(const HWND& hwnd)
{

}

void CObj__Status_Box::
WM_Notify(UINT message,WPARAM wparam,LPARAM lparam)
{

}

//-------------------------------------------------------------------------------------	
void CObj__Status_Box::
Draw_Button()
{
	GObj__Parameter_Ctrl* p_gobj = pGObj_Res->pGOBJ_PARA_CTRL;

	HDC hdc_front = pGObj_Res->hDC;
	HDC hdc_back  = pGObj_Res->hDC_BACK;

	// ...
	CString ch_data;

	if(iREAL_MODE > 0)
	{
		p_gobj->Get_Channel_Data(pKEY__CH_STATE, ch_data);
	}	
	else
	{
		p_gobj->Get_Constant_Data(pKEY__TEST_CH_STATE, ch_data);
	}

	// ...
	COLORREF color;
	int active_flag = -1;

	if(sPre_State.CompareNoCase(ch_data) == 0)
	{
		if(bActive__Blink_Mode)
		{
			if(iBlink_Count == 0)		return;
		}
		else
		{
			return;
		}
	}
	sPre_State = ch_data;

	if(ch_data.GetLength() > 0)
	{
		if((ch_data.CompareNoCase(sData__Active1_State1) == 0)
		|| (ch_data.CompareNoCase(sData__Active1_State2) == 0)
		|| (ch_data.CompareNoCase(sData__Active1_State3) == 0))
		{
			active_flag = 1;
			color = cColor__Active1;
		}
		if(active_flag < 0)
		{
			if((ch_data.CompareNoCase(sData__Active2_State1) == 0)
			|| (ch_data.CompareNoCase(sData__Active2_State2) == 0)
			|| (ch_data.CompareNoCase(sData__Active2_State3) == 0))
			{
				active_flag = 1;
				color = cColor__Active2;
			}
		}
		if(active_flag < 0)
		{
			if((ch_data.CompareNoCase(sData__Active3_State1) == 0)
			|| (ch_data.CompareNoCase(sData__Active3_State2) == 0)
			|| (ch_data.CompareNoCase(sData__Active3_State3) == 0))
			{
				active_flag = 1;
				color = cColor__Active3;
			}
		}
	}

	if(active_flag < 0)
	{
		color = cColor__InActive;
		iBlink_Count = 0;
	}
	else
	{
		if(iBlink_Count == 0)		iBlink_Count = 1;
	}

	if(bActive__Blink_Mode)
	{
		if(iBlink_Count == 1)
		{
			iBlink_Count++;
		}
		else if(iBlink_Count == 2)
		{
			color = cColor__InActive;
			iBlink_Count = 1;
		}
	}

	p_Button->SetReleasedColor(color);
	p_Button->DrawReleased(hdc_front, hdc_back);
}
