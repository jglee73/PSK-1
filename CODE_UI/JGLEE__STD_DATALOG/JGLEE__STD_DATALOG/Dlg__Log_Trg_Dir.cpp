// Dlg__Log_Trg_Dir.cpp : implementation file
//

#include "stdafx.h"

#include "JGLEE__STD_DATALOG.h"
#include "Dlg__Log_Trg_Dir.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Trg_Dir dialog

CDlg__Log_Trg_Dir::CDlg__Log_Trg_Dir(CWnd* pParent /*=NULL*/)
	: CDialog(CDlg__Log_Trg_Dir::IDD, pParent)
{
	//{{AFX_DATA_INIT(CDlg__Log_Trg_Dir)
	m_Folder_Name = _T("");
	//}}AFX_DATA_INIT
}


void CDlg__Log_Trg_Dir::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(CDlg__Log_Trg_Dir)
	DDX_Control(pDX, IDC_CHECK_D_DIR, m_Check_D_Dir);
	DDX_Control(pDX, IDC_CHECK_C_DIR, m_Check_C_Dir);
	DDX_Text(pDX, IDC_EDIT_FOLDER_NAME, m_Folder_Name);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(CDlg__Log_Trg_Dir, CDialog)
	//{{AFX_MSG_MAP(CDlg__Log_Trg_Dir)
	ON_BN_CLICKED(IDC_CHECK_C_DIR, OnCheckCDir)
	ON_BN_CLICKED(IDC_CHECK_D_DIR, OnCheckDDir)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()


/////////////////////////////////////////////////////////////////////////////
// CDlg__Log_Trg_Dir message handlers

BOOL CDlg__Log_Trg_Dir::OnInitDialog() 
{
	CDialog::OnInitDialog();

	// ...
	{
		CString str_data;

		str_data.Format("C:\\LogPM%1d_Copy", iModuleID-1);
		m_Check_C_Dir.SetWindowText(str_data);

		str_data.Format("D:\\LogPM%1d_Copy", iModuleID-1);
		m_Check_D_Dir.SetWindowText(str_data);
	}

	// ...
	{
		m_Check_C_Dir.SetCheck(0);
		m_Check_D_Dir.SetCheck(1);
	}

	UpdateData(FALSE);
	return TRUE;  
}

void CDlg__Log_Trg_Dir::OnCheckCDir() 
{
	// ...
	{
		m_Check_D_Dir.SetCheck(0);
	}	
}

void CDlg__Log_Trg_Dir::OnCheckDDir() 
{
	// ...
	{
		m_Check_C_Dir.SetCheck(0);
	}		
}

void CDlg__Log_Trg_Dir::OnOK() 
{
	UpdateData(TRUE);

	// ...
	{
		CString dir_ref;

		if(m_Check_C_Dir.GetCheck() > 0)
		{
			dir_ref.Format("C:\\LogPM%1d_Copy\\", iModuleID-1);
		}
		else
		{
			dir_ref.Format("D:\\LogPM%1d_Copy\\", iModuleID-1);
		}

		dir_ref += m_Folder_Name;

		sCur_Dir = dir_ref;
	}

	CDialog::OnOK();
}


