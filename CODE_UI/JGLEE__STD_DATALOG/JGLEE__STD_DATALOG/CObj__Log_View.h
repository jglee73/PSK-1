#pragma once

#include "Interface_Header.h"

#include "UltraFileConversionDlg.h"
#include "DataTableDlg.h"


class CObj__Log_View : public GObj__Interface_Ctrl   
{
private:
	// ...
	GObj__Resource_Info *m_pGObj_Res;

	// ...
	CX_Pad_String_CTRL m_pStringPad;

	CI_DRAW *mI_Draw;
	CI_PROGRAM_CONTROL *mI_Program;

	DataTableDlg *m_TableDlg;
	DataTableDlg *m_ViewDlg;

	CString sDir_Root;

	// ...
	bool bActive__Log_Graph;

	//.....
	CI_BUTTON *mI_BUTTON_ADD;
	CI_BUTTON *mI_BUTTON_SUB;

	CI_BUTTON *mI_BUTTON_Undo;
	CI_BUTTON *mI_BUTTON_Save;
	CI_BUTTON *mI_BUTTON_SaveAs;
	CI_BUTTON *mI_BUTTON_Clear;

	CI_BUTTON *mI_BUTTON_Date;
	CI_BUTTON *mI_BUTTON_Date_String;

	CI_BUTTON *mI_BUTTON_View;
	CI_BUTTON *mI_BUTTON_View_String;
	
	CI_BUTTON *mI_BUTTON_Log_View;
	// CI_BUTTON *mI_BUTTON_Log_Graph_Old;
	CI_BUTTON *mI_BUTTON_Log_Graph_New;

	CI_BUTTON *mI_BUTTON_Log_Conversion;
	CI_BUTTON *mI_BUTTON_Log_File_BackUp;

	CI_BUTTON *mI_BUTTON_Log_File_Reload;

	CI_BUTTON *mI_BUTTON_Search_String;
	CI_BUTTON *mI_BUTTON_Search;

	CStringArray m_arrDBChType;
	CStringArray m_arrVIEWChType;


	CStringArray  mFile_Data;
	CStringArray  mTable_Event_Data;
	CStringArray  mTable_Event_Item;
	CStringArray  mTable_Event_Title;
	CStringArray  mTable_Interval_Data;
	CStringArray  mTable_Interval_Item;
	CStringArray  mTable_Interval_Title;

	int mModule_Index;
	int mModule_Index_Pre;
	int iFlag__Remote_Disk;

	CString     mExt;
	CString     mFile_Ext;
	
	COLORREF    mPColor;
	COLORREF    mRColor;
	COLORREF    mWColor;
	COLORREF    mBColor;
	CString     mTitle;
	POINT       mTPt;
	LOGFONT		mLogFont;
	CString		mFontName;
	int			mTWidth;
	int			mTHeight;

	BOOL	m_ChMAX;
	BOOL    m_ChMIN;
	BOOL	m_ChAVG;


	//-------------------------------------------------------------------------------------
	int Init_Table();
	int Init_View();
	int Undo_Table(const HWND& hwnd);
	int Get_Title(CString channel,CString &title);

	int Add_Item(const HDC& hdc,const HDC& hdc_back);
	int Subtract_Item(const HDC& hdc,const HDC& hdc_back);
	int Clear_Item(const HDC& hdc,const HDC& hdc_back);

	int Undo_View(const HWND& hwnd,const HDC& hdc,const HDC& hdc_back);
	int Save_View(const HDC& hdc,const HDC& hdc_back);
	int SaveAs_View(const HDC& hdc,const HDC& hdc_back);

	int Log_Date_Table(const HDC& hdc,const HDC& hdc_back);
	int File_View(const HWND& hwnd,const HDC& hdc,const HDC& hdc_back);

	int Search_View(const HWND hwnd);
	int Search_String(const HDC& hdc,const HDC& hdc_back);

	//
	int Make_Log_File(const CString& log_file,
					  const CString& table_view,
					  const CString& file_data);
	int Make_CSVLog_File(const CString& log_file,
					     const CString& table_view,
						 const CString& file_data);

	//
	int Fnc__Log_Graph_View(const HWND& hwnd,
							const HDC& hdc,
							const HDC& hdc_back);

	int Make_ViewCSV_File(const CString& log_file,
						  const CString& table_view,
						  const CString& file_data);

	//
	int Fnc_FileConversion(int modulID,CString ext);

	int Read_File_from_SEQ(const HWND& hwnd,
						   const int& iModule, 
						   const CString& file_name,
						   const CString& file_ext,
						   CString& file_data);
	int Write_File_to_SEQ(const int& iModule, 
						  const CString& file_name,
						  const CString& file_ext,
						  CString& file_data);

	// ...
	int iINIT_FLAG;
	int iMODULE_ID;
	int iREAL_MODE;

	POINT pST;
	POINT pET;

	int table_pt[4];
	int view_pt[4];

	bool bActive__Page_Show;

	// ...
	CString sDir__Temp_Log;

	CString sPath__Log_Viewer_Inf;
	CString sPath__Log_Viewer_Txt;

	CString sPath__Graph_Log;
	CString sPath__Log_Conversion;
	//


public:
	CObj__Log_View();
	~CObj__Log_View();

	// ...
	void Get_Parameter(GObj__Parameter_Def* p_obj_para_def);
	
	void Set_Parameter(const int& module_id,
					   const POINT& st,
					   const POINT& et,
					   const HWND& hwnd,
					   GObj__Resource_Info *p_obj_res);
	
	void Show_GObj(const HWND& hwnd);
	void Hide_GObj();	
	void WM_Paint(const HWND& hwnd);
	void WM_Timer(const HWND& hwnd);

	void WM_LButtonDown(const POINT& mouse_pt,const HWND& hwnd);
};
