// DataTableDlg.cpp : implementation file
//

#include "stdafx.h"

#include "JGLEE__STD_DATALOG.h"
#include "DataTableDlg.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#undef THIS_FILE
static char THIS_FILE[] = __FILE__;
#endif


/////////////////////////////////////////////////////////////////////////////
// DataTableDlg dialog

DataTableDlg::DataTableDlg(CWnd* pParent /*=NULL*/)
	: CDialog(DataTableDlg::IDD, pParent)
{
	//{{AFX_DATA_INIT(DataTableDlg)
		// NOTE: the ClassWizard will add member initialization here
	//}}AFX_DATA_INIT

	m_bFirst = TRUE;
}

DataTableDlg::~DataTableDlg()
{
	DeleteObject(m_hFont);
}


void DataTableDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	//{{AFX_DATA_MAP(DataTableDlg)
	DDX_Control(pDX, IDC_LIST1, m_ListView);
	//}}AFX_DATA_MAP
}


BEGIN_MESSAGE_MAP(DataTableDlg, CDialog)
	//{{AFX_MSG_MAP(DataTableDlg)
	//}}AFX_MSG_MAP
END_MESSAGE_MAP()

/////////////////////////////////////////////////////////////////////////////
// DataTableDlg message handlers

BOOL DataTableDlg::OnInitDialog() 
{
	CDialog::OnInitDialog();

	//  [9/13/2013 Won]
	CFont font;
	font.CreatePointFont(100, _T("Arial"));
	LOGFONT lf;
	font.GetLogFont(&lf);
	m_hFont = CreateFontIndirect(&lf);
	m_ListView.SendMessage( WM_SETFONT, (WPARAM)m_hFont, (LPARAM)TRUE);
 	DeleteObject(font);

	return TRUE;  // return TRUE unless you set the focus to a control
	              // EXCEPTION: OCX Property Pages should return FALSE
}

void DataTableDlg::Interface_Show()
{
	if(m_bFirst)
	{
		RECT rc;
		GetClientRect(&rc);
		
		// ...
		int w;
		int h;

		w = rc.right - rc.left;
		h = rc.bottom - rc.top;
		
		m_ListView.MoveWindow(rc.left,rc.top,w,h,TRUE);
	
		m_bFirst=FALSE;
	}
	
	Invalidate();
}
