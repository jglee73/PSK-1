// Dlg__Log_Dir_Copy.cpp : implementation file
//

#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__STD_DATALOG.h"
#include "Dlg__Log_Dir_Copy.h"
#include "Dlg__Log_Src_Dir.h"
#include "Dlg__Log_Trg_Dir.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


#define TIMER_ID__FILE_COPY					1


/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Dir_Copy dialog


CDlg__Log_Dir_Copy::CDlg__Log_Dir_Copy(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Log_Dir_Copy::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg__Log_Dir_Copy)
	m_Src_Dir_Path = _T("");
	m_Trg_Dir_Path = _T("");
	m_Copy_Process_Data = _T("");
	//}}AFX_DATA_INIT
}


void CDlg__Log_Dir_Copy::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg__Log_Dir_Copy)
	DDX_Control(pDX, IDCANCEL, m_Bttn_Cancel);
	DDX_Control(pDX, IDOK, m_Bttn_FileCopy);
	DDX_Text(pDX, IDC_EDIT_SRC_DIR, m_Src_Dir_Path);
	DDX_Text(pDX, IDC_EDIT_TRG_DIR, m_Trg_Dir_Path);
	DDX_Text(pDX, IDC_EDIT_COPY_PROCESS_DATA, m_Copy_Process_Data);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg__Log_Dir_Copy, CDialog)
	//{{AFX_MSG_MAP(CDlg__Log_Dir_Copy)
	ON_BN_CLICKED(IDC_BTTN_SRC_DIR, OnBttnSrcDir)
	ON_BN_CLICKED(IDC_BTTN_TRG_DIR, OnBttnTrgDir)
	ON_WM_TIMER()
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Dir_Copy message handlers

BOOL CDlg__Log_Dir_Copy::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// ...
	{
		iFlag_FileCopy = -1;
	}
	
	return TRUE;  
}

void CDlg__Log_Dir_Copy::OnBttnSrcDir() 
{
	// ...
	{
		CDlg__Log_Src_Dir dlg;

		dlg.iModuleID = iModuleID;
	
		if(dlg.DoModal() == IDOK)
		{
			m_Src_Dir_Path.Format("%s\\%s", dlg.sDir_Main,dlg.sDir_Sub);

			UpdateData(FALSE);
		}
	}
}

void CDlg__Log_Dir_Copy::OnBttnTrgDir() 
{
	// ...
	{
		CDlg__Log_Trg_Dir dlg;

		dlg.iModuleID = iModuleID;

		if(dlg.DoModal() == IDOK)
		{
			m_Trg_Dir_Path = dlg.sCur_Dir;

			UpdateData(FALSE);
		}
	}
}

void CDlg__Log_Dir_Copy::OnOK() 
{
	// ...
	if(iFlag_FileCopy < 0)
	{			
		m_Bttn_FileCopy.EnableWindow(FALSE);
		m_Bttn_Cancel.EnableWindow(FALSE);
			
		m_Copy_Process_Data = "Wait : Directory Coping ...";
		UpdateData(FALSE);
			
		SetTimer(TIMER_ID__FILE_COPY,100,NULL);	
	}
	
	// CDialog::OnOK();
}

void CDlg__Log_Dir_Copy::Fnc__File_Copy()
{
	// ...
	if(iFlag_FileCopy > 0)
	{
		return;
	}

	iFlag_FileCopy = 1;
	KillTimer(TIMER_ID__FILE_COPY);

	// ...
	{
		UpdateData(TRUE);
	
		//
		CString sub_dir = m_Src_Dir_Path;
		CString key_word = "*.*";

		int db_index = sub_dir.Find(key_word,0);
		
		if(db_index < 0)
		{
			Fnc__SubFile_Copy(m_Src_Dir_Path);
		}
		else
		{
			sub_dir.Delete(m_Src_Dir_Path.GetLength()-key_word.GetLength(),key_word.GetLength());

			// ...
			CGX__SYSTEM_CTRL x_sys_ctrl;

			int seq_id = iModuleID;
			CString dir_root;
			
			x_sys_ctrl->Get__SEQ_DIR_DATALOG(seq_id,dir_root);
			
			//
			CString dir_src;

			dir_src  = dir_root;
			dir_src += "\\";
			dir_src += sub_dir;
			dir_src += "\\";

			//
			UIX__FILE_ANALYSIS_CTRL x_file_ctrl;

			CString dir_ref;
			CStringArray l_dir_name;
			CStringArray l_dir_date;	

			x_file_ctrl->Get__Dir_Date_List(dir_src, l_dir_name,l_dir_date);

			int limit = l_dir_name.GetSize();
			int i;

			for(i=0;i<limit;i++)
			{
				dir_ref.Format("%s\\%s", sub_dir,l_dir_name[i]);
				Fnc__SubFile_Copy(dir_ref);
			}

			Fnc__SubFile_Copy(sub_dir);
		}
	}
			
	// ...
	{
		iFlag_FileCopy = -1;
			
		m_Bttn_FileCopy.EnableWindow(TRUE);
		m_Bttn_Cancel.EnableWindow(TRUE);
			
		m_Copy_Process_Data = "Complete ...";
		UpdateData(FALSE);
	}
	
	CDialog::OnOK();
}
void CDlg__Log_Dir_Copy::Fnc__SubFile_Copy(const CString& dir_sub)
{
	CGX__SYSTEM_CTRL x_sys_ctrl;
			
	CString dir_src;
	CString dir_trg;
			
	int seq_id = iModuleID;
	CString dir_root;
			
	x_sys_ctrl->Get__SEQ_DIR_DATALOG(seq_id,dir_root);
			
	//
	dir_src  = dir_root;
	dir_src += "\\";
	dir_src += dir_sub;
	dir_src += "\\";
			
	//
	dir_trg  = m_Trg_Dir_Path;
	dir_trg += "\\";
	dir_trg += dir_sub;
	dir_trg += "\\";
			
	Macro__CreateDir(dir_trg);
			
	// ...
	{
		UIX__FILE_ANALYSIS_CTRL x_file_ctrl;
				
		CStringArray l_file_name;
		CString file_name;
				
		CString file_src;
		CString file_trg;
				
		//
		x_file_ctrl->Get__File_List(dir_src,"d",l_file_name);

		int limit = l_file_name.GetSize();
		int i;
				
		for(i=0;i<limit;i++)
		{
			file_name = l_file_name[i];

			// d ...
			{
				file_src.Format("%s%s.d", dir_src,file_name);
				file_trg.Format("%s%s.d", dir_trg,file_name);

				CopyFile(file_src,file_trg, FALSE);
			}
			// rcp_inf ...
			{
				file_src.Format("%s%s.rcp_inf", dir_src,file_name);
				file_trg.Format("%s%s.rcp_inf", dir_trg,file_name);

				CopyFile(file_src,file_trg, FALSE);
			}
			// rcp_log ...
			{
				file_src.Format("%s%s.rcp_log", dir_src,file_name);
				file_trg.Format("%s%s.rcp_log", dir_trg,file_name);

				CopyFile(file_src,file_trg, FALSE);
			}
		}
	}

	// ...
}

void CDlg__Log_Dir_Copy::OnTimer(UINT nIDEvent) 
{
	if(nIDEvent == TIMER_ID__FILE_COPY)
	{
		Fnc__File_Copy();
	}
	
	CDialog::OnTimer(nIDEvent);
}


void CDlg__Log_Dir_Copy::Macro__CreateDir(const CString& str_path)
{
	int dir_flag = -1;
	
	CString sub_dir;
	char ch;
	
	int limit = str_path.GetLength();
	int i;
	
	for(i=0;i<limit;i++)
	{
		ch = str_path.GetAt(i);
		
		if(ch == '\\')
		{
			if(dir_flag < 0)
			{
				dir_flag = 1;
				
				sub_dir += "\\";
				CreateDirectory(sub_dir,NULL);
			}
		}
		else
		{
			dir_flag = -1;
			
			sub_dir += ch;
		}
	}
	
	// ...
}