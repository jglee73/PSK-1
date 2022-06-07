// Dlg__Log_Src_Dir.cpp : implementation file
//

#include "stdafx.h"
#include "Interface_Header.h"

#include "JGLEE__STD_DATALOG.h"
#include "Dlg__Log_Src_Dir.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Src_Dir dialog

CDlg__Log_Src_Dir::CDlg__Log_Src_Dir(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Log_Src_Dir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg__Log_Src_Dir)
	//}}AFX_DATA_INIT
}


void CDlg__Log_Src_Dir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg__Log_Src_Dir)
	DDX_Control(pDX, IDC_2st_FOLDER, m_2st_List);
	DDX_Control(pDX, IDC_1st_FOLDER, m_1st_List);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg__Log_Src_Dir, CDialog)
	//{{AFX_MSG_MAP(CDlg__Log_Src_Dir)
	ON_CBN_EDITCHANGE(IDC_1st_FOLDER, OnEditchange1stFOLDER)
	ON_CBN_EDITCHANGE(IDC_2st_FOLDER, OnEditchange2stFOLDER)
	ON_CBN_SELCHANGE(IDC_1st_FOLDER, OnSelchange1stFOLDER)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Src_Dir message handlers

BOOL CDlg__Log_Src_Dir::OnInitDialog() 
{
	CDialog::OnInitDialog();
	
	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		
		int seq_id;
		CString dir_root;
		CString dir_log;
		
		// ...
		{
			seq_id = iModuleID;
			x_sys_ctrl->Get__SEQ_DIR_DATALOG(seq_id,dir_root);
			
			dir_log = dir_root;
			
			// ...
			{
				UIX__FILE_ANALYSIS_CTRL x_file_ctrl;
				CStringArray l_dir_name;
				CStringArray l_dir_date;
				int limit;
				int i;
				
				//
				x_file_ctrl->Get__Dir_Date_List(dir_log, l_dir_name,l_dir_date);
				limit = l_dir_name.GetSize();

				for(i=0;i<limit;i++)
				{
					m_1st_List.AddString(l_dir_name[i]);
				}

				if(limit > 0)
				{
					m_1st_List.SetCurSel(0);

					CString cur_dir;
					m_1st_List.GetLBText(0,cur_dir);

					CString dir_ref;
					dir_ref  = dir_log;
					dir_ref += "\\";
					dir_ref += cur_dir;
					dir_ref += "\\";

					CStringArray l_sub_dir_name;
					CStringArray l_sub_dir_date;

					x_file_ctrl->Get__Dir_Date_List(dir_ref, l_sub_dir_name,l_sub_dir_date);

					//
					m_2st_List.AddString("*.*");

					int k_limit = l_sub_dir_name.GetSize();
					int k;

					for(k=0;k<k_limit;k++)
					{
						m_2st_List.AddString(l_sub_dir_name[k]);
					}

					m_2st_List.SetCurSel(0);
				}
			}	
		}

		UpdateData(FALSE);
	}

	return TRUE; 
}
void CDlg__Log_Src_Dir::OnOK() 
{
	UpdateData(TRUE);

	// ...
	{
		int db_index;

		CString dir_main;
		CString dir_sub;

		// Main ...
		{
			db_index = m_1st_List.GetCurSel();

			if(db_index >= 0)		m_1st_List.GetLBText(db_index,dir_main);
		}

		// Sub ...
		{
			db_index = m_2st_List.GetCurSel();

			if(db_index >= 0)		m_2st_List.GetLBText(db_index,dir_sub);
		}

		// ...
		{
			sDir_Main = dir_main;
			sDir_Sub  = dir_sub;
		}
	}
	
	CDialog::OnOK();
}

void CDlg__Log_Src_Dir::OnEditchange1stFOLDER() 
{
	// ...
	{

	}
}
void CDlg__Log_Src_Dir::OnEditchange2stFOLDER() 
{
	// ...
	{

	}
}

void CDlg__Log_Src_Dir::OnSelchange1stFOLDER() 
{
	UpdateData(TRUE);
	
	// ...
	int db_index = m_1st_List.GetCurSel();
	if(db_index < 0)	return;
	
	CString cur_dir;
	m_1st_List.GetLBText(db_index,cur_dir);
	
	// ...
	{
		CGX__SYSTEM_CTRL x_sys_ctrl;
		
		int seq_id;
		CString dir_root;
		CString dir_log;
		
		// ...
		{
			seq_id = iModuleID;
			x_sys_ctrl->Get__SEQ_DIR_DATALOG(seq_id,dir_root);
			
			dir_log = dir_root;
			
			// ...
			{
				UIX__FILE_ANALYSIS_CTRL x_file_ctrl;
				
				CString dir_ref;
				dir_ref  = dir_log;
				dir_ref += "\\";
				dir_ref += cur_dir;
				dir_ref += "\\";
				
				CStringArray l_sub_dir_name;
				CStringArray l_sub_dir_date;
				
				x_file_ctrl->Get__Dir_Date_List(dir_ref, l_sub_dir_name,l_sub_dir_date);
				
				//
				m_2st_List.ResetContent();
				m_2st_List.AddString("*.*");
				
				int k_limit = l_sub_dir_name.GetSize();
				int k;
				
				for(k=0;k<k_limit;k++)
				{
					m_2st_List.AddString(l_sub_dir_name[k]);
				}
				
				m_2st_List.SetCurSel(0);
			}
		}
		
		UpdateData(FALSE);
	}
	
	// ...
}


