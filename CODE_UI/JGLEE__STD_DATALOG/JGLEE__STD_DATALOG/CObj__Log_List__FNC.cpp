#include "stdafx.h"
#include "JGLEE__STD_DATALOG.h"

#include "CObj__Log_List.h"
#include "CObj__Log_List__KEY_DEF.h"


// ...
int  CObj__Log_List::Fnc_Active()
{
	mEdit_Flag  = 1;
	mEdit_Blink = 1;

	mI_BUTTON_Undo->SetActive();
	mI_BUTTON_Save->SetActive();
	mI_BUTTON_Time->SetActive();
	return 1;
}
int  CObj__Log_List::Fnc_InActive()
{
	mEdit_Flag = 0;

	mI_BUTTON_Undo->SetInActive();
	mI_BUTTON_Save->SetInActive();
	mI_BUTTON_Time->SetInActive();
	return 1;
}
int  CObj__Log_List::Draw_Button(const HDC& hdc,const HDC& hdc_back)
{
	mI_BUTTON_Edit->DrawReleased(hdc,hdc_back);
	mI_BUTTON_Undo->DrawReleased(hdc,hdc_back);
	mI_BUTTON_Save->DrawReleased(hdc,hdc_back);

	mI_BUTTON_Search->DrawReleased(hdc,hdc_back);
	mI_BUTTON_Search_Box->DrawReleased(hdc,hdc_back);

	mI_BUTTON_Time->DrawReleased(hdc,hdc_back);
	mI_BUTTON_Time_String->DrawPressed(hdc,hdc_back);
	return 1;
}


int  CObj__Log_List::Fnc_Save()
{
	CString var_data;
	CString file_data;
	CString db_data;

	mI_BUTTON_Time_String->GetTitle(var_data);
	file_data += var_data;
	file_data += ",\n";

	pDlg_View->Get__SAVE_DATA(db_data);
	file_data += db_data;

	// ...
	CGX_FILE__DATALOG_CTRL cx_datalog_ctrl;

	if(cx_datalog_ctrl->Download__FILE(iMODULE_ID,"","csv","channel_list",file_data) < 0)
	{
		return 1;
	}
	return 1;
}
int  CObj__Log_List::Fnc_Undo()
{	
	CString time;
	pDlg_View->Undo_Page(time);

	if(atof(time) < 0.1)
	{
		time = "0.1";	
	}

	mI_BUTTON_Time_String->SetTitle(time);
	return 1;
}

int  CObj__Log_List::Init__Table(HWND hwnd, const bool active_upload)
{
	if(active_upload)
	{
		if(iInit_Flag > 0)			return 1;
		iInit_Flag = 1;
	}
	
	printf(" * CObj__Log_List::Init__Table() - [%1d] \n", active_upload);

	if(pDlg_View != NULL)
	{
		pDlg_View->Init_Page(active_upload);
	}

	if(active_upload)		Fnc_Undo();

	Fnc_InActive();
	return 1;
}
